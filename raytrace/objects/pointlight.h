/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    raytrace/objects/pointlight.h
//  Purpose: Declares PointLight, an omnidirectional light source.
/* ========================================================================== */

#pragma once

#include "lightbase.h"

namespace raytrace {
    class PointLight : public LightBase {
    public:
        // default constructor and destructor
        PointLight();
        virtual ~PointLight() override; // override default destructor

        // override function to compute illumination
        virtual bool ComputeIllumination(const qbVector<double> &intPoint,
            const qbVector<double> &localNorm,
            const std::vector<std::shared_ptr<raytrace::ObjectBase>> &objectList,
            const std::shared_ptr<raytrace::ObjectBase> &currentObject,
            qbVector<double> &color, double &intensity) override;
            // =======================================================
    };
}