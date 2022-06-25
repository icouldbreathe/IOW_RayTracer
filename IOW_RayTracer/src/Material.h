#pragma once

#include "common.h"

struct HitRecord;

class Material
{
  public:
    virtual bool scatter(const Ray &incomingRay, const HitRecord &record,
                         Color &attenuation, Ray &scatteredRay) const = 0;
};
