#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "Camera.h"
#include "Color.h"
#include "DielectricMaterial.h"
#include "HittableList.h"
#include "LambertianDiffuseMaterial.h"
#include "MetalMaterial.h"
#include "Sphere.h"
#include "common.h"

std::mutex mutexScanlines;

HittableList testScene()
{
    HittableList world;

    auto ground_material =
        make_shared<LambertianDiffuseMaterial>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = randomDouble();
            Point3 center(a + 0.9 * randomDouble(), 0.2,
                          b + 0.9 * randomDouble());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9)
            {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material =
                        make_shared<LambertianDiffuseMaterial>(albedo);
                    world.add(
                        make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // MetalMaterial
                    auto albedo     = Color::random(0.5, 1);
                    auto fuzz       = randomDouble(0, 0.5);
                    sphere_material = make_shared<MetalMaterial>(albedo, fuzz);
                    world.add(
                        make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = make_shared<DielectricMaterial>(1.5);
                    world.add(
                        make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<DielectricMaterial>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 =
        make_shared<LambertianDiffuseMaterial>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<MetalMaterial>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

Color rayColor(const Ray &ray, const Hittable &world, int depth);

void render(int startPos, int endPos, int imageHeight, int imageWidth,
            int samplesPerPixel, int maxDepth, HittableList &world,
            Camera &camera, std::stringstream &buffer, int &scanlines)
{
    for (int i = endPos - 1; i >= startPos; --i)
    {
        mutexScanlines.lock();
        std::cerr << "\rScanlines remaining: " << imageHeight - scanlines - 1
                  << ' ' << std::flush;
        ++scanlines;
        mutexScanlines.unlock();

        for (int j = 0; j < imageWidth; ++j)
        {
            Color pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s)
            {
                auto u = (j + randomDouble()) / (imageWidth - 1);
                auto v = (i + randomDouble()) / (imageHeight - 1);

                Ray ray = camera.getRay(u, v);
                pixelColor += rayColor(ray, world, maxDepth);
            }

            writeColor(buffer, pixelColor, samplesPerPixel);
        }
    }
}

int main()
{
    // Image
    const auto aspectRatio    = 3.0 / 2.0;
    const int imageWidth      = 200;
    const int imageHeight     = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 32;
    const int maxColor        = 255;
    const int maxDepth        = 50;

    // World
    auto world = testScene();

    // Camera
    Point3 lookFrom(13, 2, 3);
    Point3 lookAt(0, 0, 0);
    Vec3 vUp(0, 1, 0);
    auto distanceToFocus = 10.0;
    auto aperture        = 0.1;
    auto vfov            = 60;

    Camera camera(lookFrom, lookAt, vUp, vfov, aspectRatio, aperture,
                  distanceToFocus);

    // Threads
    int nThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(nThreads);
    std::stringstream buffer[nThreads];
    int scanlines{0};
    int nTasks    = 0;
    int remainder = 0;

    if (imageHeight <= nThreads)
    {
        nThreads = 1;
        nTasks   = imageHeight;
    }
    else
    {
        nTasks    = imageHeight / nThreads;
        remainder = imageHeight % nThreads;
    }

    std::cerr << "Threads: " << nThreads << "\n";

    // Render
    auto start = std::chrono::high_resolution_clock::now();

    // PPM preamble
    std::cout << "P3\n"
              << imageWidth << ' ' << imageHeight << "\n"
              << maxColor << "\n";

    // split work per thread
    for (int i = 0, startPos = 0, endPos = 0; i < nThreads; ++i)
    {
        if (remainder)
        {
            endPos = startPos + nTasks + 1;
            --remainder;
        }
        else
        {
            endPos = startPos + nTasks;
        }

        threads[i] = std::thread(render, startPos, endPos, imageHeight,
                                 imageWidth, samplesPerPixel, maxDepth,
                                 std::ref(world), std::ref(camera),
                                 std::ref(buffer[i]), std::ref(scanlines));

        startPos = endPos;
    }

    // join threads and print output
    for (int i = nThreads - 1; i >= 0; --i)
    {
        threads[i].join();
        std::cout << buffer[i].str();
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    std::cerr << "\nDone.\n";
    std::cerr << "Duration: " << duration.count() << " seconds\n";
}

Color rayColor(const Ray &ray, const Hittable &world, int depth)
{
    HitRecord record;

    // If ray bounce limit is exceeded, no more light is gathered
    if (depth <= 0)
    {
        return Color(0, 0, 0);
    }

    if (world.hit(ray, 0.001, infinity, record))
    {
        Ray scattered;
        Color attenuation;
        if (record.pMaterial->scatter(ray, record, attenuation, scattered))
        {
            return attenuation * rayColor(scattered, world, depth - 1);
        }
        else
        {
            return Color(0, 0, 0);
        }
    }
    Vec3 unitDirection = unitVector(ray.direction());
    auto t             = 0.5 * (unitDirection.y() + 1.0);

    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}
