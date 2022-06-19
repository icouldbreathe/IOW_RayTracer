#pragma once

#include "Ray.h"

struct HitRecord
{
    Point3 p;
    Vec3 normal;
    double t;
    bool bFrontFace;

    inline void setFaceNormal(const Ray &r, const Vec3 &outwardNormal)
    {
        bFrontFace = dot(r.direction(), outwardNormal) < 0;
        normal = bFrontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
  public:
    virtual bool hit(const Ray &r, double tMin, double tMax, HitRecord &rec) const = 0;
};
