/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    raytrace/objects/objsphere.h
//  Purpose: Declares ObjSphere, a sphere scene object with location and radius.
/* ========================================================================== */

#pragma once

#include "object_base.h"

namespace raytrace {
    class ObjSphere : public ObjectBase {
    public:
        // default constructor, will define a unit sphere at origin
        ObjSphere(const qbVector<double> m_location = std::vector<double>{0.0, 0.0, 0.0},
            const double radius = 1.0);

        // override the base destructor and functions
        virtual ~ObjSphere() override;

        virtual bool TestIntersection(const Ray &castRay,
            qbVector<double> &intPoint,
            qbVector<double> &localNorm,
            qbVector<double> &localColor) override;

        double GetRadius() const { return m_radius; }

    };
}