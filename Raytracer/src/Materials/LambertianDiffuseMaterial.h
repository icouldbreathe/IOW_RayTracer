#pragma once

#include "Material.h"

class LambertianDiffuseMaterial : public Material
{
  public:
    LambertianDiffuseMaterial(const Color &color);

    virtual bool scatter([[maybe_unused]] const Ray &incidentRay,
                         const HitRecord &record, Color &attenuation,
                         Ray &scatteredRay) const override;

  public:
    Color m_albedo;
};