#include "Camera.h"

Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 vUp,
               double vfov, // Vertical field of view in degrees
               double aspectRatio, double aperture, double focusDistance)
{
    auto theta          = degreesToRadians(vfov);
    auto h              = tan(theta / 2);
    auto viewportHeight = 2.0 * h;
    auto viewportWidth  = aspectRatio * viewportHeight;

    m_w = unitVector(lookFrom - lookAt);
    m_u = unitVector(cross(vUp, m_w));
    m_v = cross(m_w, m_u);

    m_origin     = lookFrom;
    m_horizontal = focusDistance * viewportWidth * m_u;
    m_vertical   = focusDistance * viewportHeight * m_v;
    m_lowerLeftCorner =
        m_origin - m_horizontal / 2 - m_vertical / 2 - focusDistance * m_w;

    m_lensRadius = aperture / 2;
}

Ray Camera::getRay(double s, double t) const
{
    Vec3 rd     = m_lensRadius * randomInUnitDisk();
    Vec3 offset = m_u * rd.x() + m_v * rd.y();

    return Ray(m_origin + offset, m_lowerLeftCorner + s * m_horizontal +
                                      t * m_vertical - m_origin - offset);
}