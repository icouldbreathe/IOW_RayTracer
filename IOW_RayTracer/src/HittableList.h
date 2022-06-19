#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable
{
  public:
    HittableList()
    {
    }
    HittableList(shared_ptr<Hittable> object)
    {
        add(object);
    }

    void clear()
    {
        objects.clear();
    }
    void add(shared_ptr<Hittable> object)
    {
        objects.push_back(object);
    }

    virtual bool hit(const Ray &r, double tMin, double tMax, HitRecord &rec) const override;

  public:
    std::vector<shared_ptr<Hittable>> objects;
};

bool HittableList::hit(const Ray &r, double tMin, double tMax, HitRecord &rec) const
{
    HitRecord tempRec;
    bool bHitAnything = false;
    auto closestSoFar = tMax;

    for (const auto &object : objects)
    {
        if (object->hit(r, tMin, closestSoFar, tempRec))
        {
            bHitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return bHitAnything;
}
