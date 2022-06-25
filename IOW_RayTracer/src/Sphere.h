#pragma once

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable
{
  public:
    Sphere()
    {
    }
    Sphere(Point3 center, double radius, shared_ptr<Material> pMaterial)
        : m_center(center), m_radius(radius), m_pMaterial(pMaterial)
    {
    }

    virtual bool hit(const Ray &ray, double tMin, double tMax,
                     HitRecord &record) const override;

  public:
    Point3 m_center;
    double m_radius;
    shared_ptr<Material> m_pMaterial;
};

bool Sphere::hit(const Ray &ray, double tMin, double tMax,
                 HitRecord &record) const
{
    Vec3 oc = ray.origin() - m_center;
    auto a = ray.direction().lengthSquared();
    auto half_b = dot(oc, ray.direction());
    auto c = oc.lengthSquared() - m_radius * m_radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    auto root = (-half_b - sqrtd) / a;
    if (root < tMin || tMax < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < tMin || tMax < root)
            return false;
    }
    record.t = root;
    record.hitPoint = ray.at(record.t);
    Vec3 outwardNormal = (record.hitPoint - m_center) / m_radius;
    record.setFaceNormal(ray, outwardNormal);
    record.pMaterial = m_pMaterial;

    return true;
}
