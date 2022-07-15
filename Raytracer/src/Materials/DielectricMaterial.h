#pragma once

#include "Material.h"

class DielectricMaterial : public Material
{
  public:
    DielectricMaterial(double indexOfRefraction);

    virtual bool scatter(const Ray &incidentRay, const HitRecord &record,
                         Color &attenuation, Ray &scatteredRay) const override;

  public:
    double m_ior;

  private:
    static double reflectance(double cosine, double ref_idx);
};