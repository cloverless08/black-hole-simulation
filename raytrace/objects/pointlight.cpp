//
// Created by cdemin on 11/3/26.
//

#include "pointlight.h"

// default constructor and destructor
raytrace::PointLight::PointLight() {
    std::cout << "PointLight::PointLight(): Constructing Point Light" << std::endl;

    m_color = qbVector<double> {std::vector<double>{1.0, 1.0, 1.0}};
    m_intensity = 1.0;
}

raytrace::PointLight::~PointLight() {
    std::cout << "PointLight::~PointLight(): Destructing Point Light" << std::endl;
}


// function to compute illumination
bool raytrace::PointLight::ComputeIllumination(const qbVector<double> &intPoint,
    const qbVector<double> &localNorm,
    const std::vector<std::shared_ptr<raytrace::ObjectBase> > &objectList,
    const std::shared_ptr<raytrace::ObjectBase> &currentObject,
    qbVector<double> &color, double &intensity) {
    // ===========================================================

    // construct a vector pointing from intersection point to the light
    qbVector<double> lightDirection = (m_location - intPoint).Normalized(); // "unit vector in that direction"

    // compute a starting point
    qbVector<double> startPoint = intPoint; // replace later

    // compute angle between local normal and the light ray
    // Note: we assume local normal is a *unit vector* (magnitude of 1)
    double angle = acos(qbVector<double>::dot(localNorm, lightDirection));;

    // if normal is pointing away from the light, no illumination
    if (angle > 1.5708) { // pi/2 ~= 1.5708
        // no illumination
        color = m_color;
        intensity = 0.0;
        return false;
    } else {
        color = m_color;
        intensity = m_intensity * (1.0 - (angle / 1.5708)); // pi/2 ~= 1.5708
        return true;
    }

}
