#pragma once

#include <cmath>
#include <limits>
#include <memory>

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
