#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable
{
  public:
    HittableList();
    HittableList(shared_ptr<Hittable> object);

    void clear();
    void add(shared_ptr<Hittable> object);

    virtual bool hit(const Ray &ray, double tMin, double tMax,
                     HitRecord &record) const override;

  public:
    std::vector<shared_ptr<Hittable>> m_objects;
};
