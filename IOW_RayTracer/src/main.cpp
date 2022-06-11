#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

double hitSphere(const point3& center, double radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0)
    {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

color rayColor(const ray& r)
{
    auto t = hitSphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        vec3 N = unitVector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    vec3 unitDirection = unitVector(r.direction());
    t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const auto aspectRatio = 16.0 / 9.0;
    const int imageWidth = 800;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    const int maxColor = 255;

    // Camera
    auto viewportHeight = 2.0;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewportWidth, 0, 0);
    auto vertical = vec3(0, viewportHeight, 0);
    auto lowerLeftCorner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focalLength);

    // Render

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n" << maxColor << "\n";
    
    for (int i = imageHeight-1; i >= 0; --i)
    {
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for (int j = 0; j < imageWidth; ++j)
        {
            auto u = double(j) / (imageWidth - 1);
            auto v = double(i) / (imageHeight - 1);
            ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            color pixelColor = rayColor(r);
            writeColor(std::cout, pixelColor);
        }
    }

    std::cerr << "\nDone.\n";
}
