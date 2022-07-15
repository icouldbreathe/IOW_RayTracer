#pragma once

#include "Material.h"

class MetalMaterial : public Material
{
  public:
    MetalMaterial(const Color &color, double roughness);

    virtual bool scatter(const Ray &incidentRay, const HitRecord &record,
                         Color &attenuation, Ray &scatteredRay) const override;

  public:
    Color m_albedo;
    double m_roughness;
};