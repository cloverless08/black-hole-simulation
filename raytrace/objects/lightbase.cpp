//
// Created by cdemin on 11/3/26.
//

#include "lightbase.h"

// constructor and destructor
raytrace::LightBase::LightBase() {
    std::cout << "LightBase::LightBase(): Constructed Light Base" << std::endl;
};

raytrace::LightBase::~LightBase() {
    std::cout << "LightBase::~LightBase(): Destroyed Light Base" << std::endl;
}


// function to compute illumination
bool raytrace::LightBase::ComputeIllumination(const qbVector<double> &intPoint,
    const qbVector<double> &localNorm,
    const std::vector<std::shared_ptr<raytrace::ObjectBase> > &objectList,
    const std::shared_ptr<raytrace::ObjectBase> &currentObject,
    qbVector<double> &color, double &intensity) {
    //======================================================================

    return false; // empty bc its a base, define script in each inherited class
}
