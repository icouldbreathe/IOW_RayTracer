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
        m_objects.clear();
    }
    void add(shared_ptr<Hittable> object)
    {
        m_objects.push_back(object);
    }

    virtual bool hit(const Ray &ray, double tMin, double tMax,
                     HitRecord &record) const override;

  public:
    std::vector<shared_ptr<Hittable>> m_objects;
};

bool HittableList::hit(const Ray &ray, double tMin, double tMax,
                       HitRecord &record) const
{
    HitRecord tempRec;
    bool bHitAnything = false;
    auto closestSoFar = tMax;

    for (const auto &object : m_objects)
    {
        if (object->hit(ray, tMin, closestSoFar, tempRec))
        {
            bHitAnything = true;
            closestSoFar = tempRec.t;
            record = tempRec;
        }
    }

    return bHitAnything;
}
