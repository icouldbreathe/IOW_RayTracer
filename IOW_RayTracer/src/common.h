#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Common Headers

#include "Ray.h"
#include "Vec3.h"

// Usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double randomDouble()
{
    static std::uniform_int_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}