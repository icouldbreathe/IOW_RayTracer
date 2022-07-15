#pragma once

#include "common.h"

class Camera
{
  public:
    Camera(Point3 lookFrom, Point3 lookAt, Vec3 vUp,
           double vfov, // Vertical field of view in degrees
           double aspectRatio, double aperture, double focusDistance);

    Ray getRay(double s, double t) const;

  private:
    Point3 m_origin;
    Point3 m_lowerLeftCorner;
    Vec3 m_horizontal;
    Vec3 m_vertical;
    Vec3 m_u, m_v, m_w;
    double m_lensRadius;
};