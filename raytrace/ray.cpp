//
// Created by cdemin on 11/3/26.
//

#include "ray.h"

raytrace::Ray::Ray() {
    m_point1 = math::cdVector<double>(std::vector<double>{0.0, 0.0, 0.0});
    m_point2 = math::cdVector<double>(std::vector<double>{0.0, 0.0, 1.0}); // just sum different

    m_lab = m_point2 - m_point1;
};

raytrace::Ray::Ray(const math::cdVector<double> &point1, const math::cdVector<double> &point2) {
    m_point1 = point1;
    m_point2 = point2;
    m_lab = m_point2 - m_point1;
}

// getter funcitons
math::cdVector<double> raytrace::Ray::GetPoint1() const {
    return m_point1;
}

math::cdVector<double> raytrace::Ray::GetPoint2() const {
    return m_point2;
}
