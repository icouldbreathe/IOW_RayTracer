#pragma once

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable
{
  public:
    Sphere();
    Sphere(Point3 center, double radius, shared_ptr<Material> pMaterial);

    virtual bool hit(const Ray &ray, double tMin, double tMax,
                     HitRecord &record) const override;

  public:
    Point3 m_center;
    double m_radius;
    shared_ptr<Material> m_pMaterial;
};
