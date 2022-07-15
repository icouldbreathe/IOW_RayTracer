#include "MetalMaterial.h"

MetalMaterial::MetalMaterial(const Color &color, double roughness)
    : m_albedo(color), m_roughness(roughness < 1 ? roughness : 1)
{
}

bool MetalMaterial::scatter(const Ray &incidentRay, const HitRecord &record,
                            Color &attenuation, Ray &scatteredRay) const
{
    Vec3 reflected =
        reflect(unitVector(incidentRay.direction()), record.normal);
    scatteredRay =
        Ray(record.hitPoint, reflected + m_roughness * randomInUnitSphere());
    attenuation = m_albedo;
    return (dot(scatteredRay.direction(), record.normal) > 0);
}