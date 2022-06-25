#pragma once

#include "Material.h"

class MetalMaterial : public Material
{
  public:
    MetalMaterial(const Color &color) : m_albedo(color)
    {
    }

    virtual bool scatter(const Ray &incomingRay, const HitRecord &record,
                         Color &attenuation, Ray &scatteredRay) const override
    {
        Vec3 reflected =
            reflect(unitVector(incomingRay.direction()), record.normal);
        scatteredRay = Ray(record.hitPoint, reflected);
        attenuation = m_albedo;
        return (dot(scatteredRay.direction(), record.normal) > 0);
    }

  public:
    Color m_albedo;
};