#include "LambertianDiffuseMaterial.h"

LambertianDiffuseMaterial::LambertianDiffuseMaterial(const Color &color)
    : m_albedo(color)
{
}

bool LambertianDiffuseMaterial::scatter([[maybe_unused]] const Ray &incidentRay,
                                        const HitRecord &record,
                                        Color &attenuation,
                                        Ray &scatteredRay) const
{
    auto scatterDirection = record.normal + randomUnitVector();

    // Catch cases where Normal and RandomUnitVector cancel out
    if (scatterDirection.isNearZero())
    {
        scatterDirection = record.normal;
    }

    scatteredRay = Ray(record.hitPoint, scatterDirection);
    attenuation  = m_albedo;
    return true;
}