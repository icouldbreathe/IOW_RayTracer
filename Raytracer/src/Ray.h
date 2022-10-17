#pragma once

#include "Vec3.h"

class Ray
{
  public:
    Ray();
    Ray(const Point3 &origin, const Vec3 &direction);

    Point3 origin() const;
    Vec3 direction() const;
    Point3 at(double t) const;

  public:
    Point3 m_origin;
    Vec3 m_direction;
};
