#pragma once

#include "Vec3.h"

#include <iostream>

void writeColor(std::ostream &out, Color pixelColor, int samplesPerPixel)
{
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    // Divide color by the number of samples
    auto scale = 1.0 / samplesPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;

    out << static_cast<int>(255 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255 * clamp(b, 0.0, 0.999)) << '\n';
}
