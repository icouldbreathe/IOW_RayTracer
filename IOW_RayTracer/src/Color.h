#pragma once

#include "Vec3.h"

#include <iostream>

void writeColor(std::ostream &out, Color pixelColor)
{
    out << static_cast<int>(255.999 * pixelColor.x()) << ' ' << static_cast<int>(255.999 * pixelColor.y()) << ' '
        << static_cast<int>(255.999 * pixelColor.z()) << '\n';
}
