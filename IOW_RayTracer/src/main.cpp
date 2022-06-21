#include <iostream>

#include "Camera.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "common.h"

Color rayColor(const Ray &r, const Hittable &world)
{
    HitRecord rec;
    if (world.hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + Color(1, 1, 1));
    }
    Vec3 unitDirection = unitVector(r.direction());
    auto t = 0.5 * (unitDirection.y() + 1.0);

    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const auto aspectRatio = 16.0 / 9.0;
    const int imageWidth = 800;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxColor = 255;

    // World
    HittableList world;
    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

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

                Ray r = camera.getRay(u, v);
                pixelColor += rayColor(r, world);
            }
            writeColor(std::cout, pixelColor, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
}
