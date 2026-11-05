//
// Created by cdemin on 11/1/26.
//

#include  <math.h>

#include "object_base.h"

#define EPSILON 1e-21f;

// define default constructor and destructor
raytrace::ObjectBase::ObjectBase() {
    std::cout << "Constructing Object Base" << std::endl;
}
raytrace::ObjectBase::~ObjectBase() {
    std::cout << "Destructing Object Base" << std::endl;
}


bool raytrace::ObjectBase::TestIntersection(const Ray &castRay,
    qbVector<double> &intPoint,
    qbVector<double> &localNorm,
    qbVector<double> &localColor) {
    // --------------------------------

    return false; // will be overridden upon inheritance
}

bool raytrace::ObjectBase::CheckAreClose(const double float1, const double float2) {
    return false; // will be overridden upon inheritance
}
