#pragma once

#include "common.h"

class Material;

struct HitRecord
{
    Point3 hitPoint;
    Vec3 normal;
    shared_ptr<Material> pMaterial;
    double t;
    bool bFrontFace;

    inline void setFaceNormal(const Ray &ray, const Vec3 &outwardNormal)
    {
        bFrontFace = dot(ray.direction(), outwardNormal) < 0;
        normal = bFrontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
  public:
    virtual bool hit(const Ray &ray, double tMin, double tMax,
                     HitRecord &record) const = 0;
};
