#include "HittableList.h"

HittableList::HittableList()
{
}

HittableList::HittableList(shared_ptr<Hittable> object)
{
    add(object);
}

void HittableList::clear()
{
    m_objects.clear();
}

void HittableList::add(shared_ptr<Hittable> object)
{
    m_objects.push_back(object);
}

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
            record       = tempRec;
        }
    }

    return bHitAnything;
}