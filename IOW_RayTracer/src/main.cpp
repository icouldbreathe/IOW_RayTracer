#include <iostream>

#include "Camera.h"
#include "Color.h"
#include "HittableList.h"
#include "LambertianDiffuseMaterial.h"
#include "MetalMaterial.h"
#include "Sphere.h"
#include "common.h"

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
    auto t = 0.5 * (unitDirection.y() + 1.0);

    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const auto aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxColor = 255;
    const int maxDepth = 50;

    // World
    HittableList world;

    auto materialGround =
        make_shared<LambertianDiffuseMaterial>(Color(0.8, 0.8, 0.0));
    auto materialCenter =
        make_shared<LambertianDiffuseMaterial>(Color(0.7, 0.3, 0.3));
    auto materialLeft = make_shared<MetalMaterial>(Color(0.8, 0.8, 0.8), 0.1);
    auto materialRight = make_shared<MetalMaterial>(Color(0.8, 0.6, 0.2), 0.8);

    world.add(
        make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
    world.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, materialCenter));
    world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));

    // Camera

    Camera camera;

    // Render

    std::cout << "P3\n"
              << imageWidth << ' ' << imageHeight << "\n"
              << maxColor << "\n";

    for (int i = imageHeight - 1; i >= 0; --i)
    {
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
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
            writeColor(std::cout, pixelColor, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
}
