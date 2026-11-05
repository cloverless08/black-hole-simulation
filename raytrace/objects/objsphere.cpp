//
// Created by cdemin on 11/1/26.
//

#include "objsphere.h"

#include <cmath>

raytrace::ObjSphere::ObjSphere() {
    std::cout << "ObjSphere::ObjSphere(): Constructing Sphere Object" << std::endl;
};

raytrace::ObjSphere::~ObjSphere() {
    std::cout << "ObjSphere::~ObjSphere(): Destructing Sphere Object" << std::endl;
}


// define intersection test
bool raytrace::ObjSphere::TestIntersection(
    const Ray &castRay,
    qbVector<double> &intPoint,
    qbVector<double> &localNorm,
    qbVector<double> &localColor) {
    // ===================================


    // compute values of a b and c
    qbVector<double> vhat = castRay.m_lab;
    vhat.Normalize();

    // NOTE:
    // a is equal to the squared magnitude of the direction of the cast ray
    // since its unit value, the value of a will always be 1

    double b = 2.0 * qbVector<double>::dot(castRay.m_point1, vhat);
    double c = qbVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0; // start point of ray to itself

    // test for intersection
    double intTest = (b*b) - 4.0 * c; // remember a = 1

    if (intTest > 0.0) {
        // we have intersection
        double numRoot = sqrtf(intTest);
        double t1 = (-b + numRoot) / 2.0;
        double t2 = (-b - numRoot) / 2.0;

        // if either t1 or t2 is negatice, this part of objcet is behind the camera
        if ((t1 < 0.0) || (t2 < 0.0)) {
            return false;
        } else {
            // determine which point of intersection was closest to camera (bc intersects at two point on either side of sphere)
            if (t1 < t2) {
                intPoint = castRay.m_point1 + (vhat * t1);
            } else {
                intPoint = castRay.m_point1 + (vhat * t2);
            }

            // compute local normal
            localNorm = intPoint; // only works for sphere at origin
            localNorm.Normalize();

            return true;
        }
    } else {
        // we have not intersection
        return false;
    }


}
