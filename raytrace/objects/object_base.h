/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    raytrace/objects/object_base.h
//  Purpose: Declares ObjectBase, the abstract base class for all
//           ray-traceable scene objects.
/* ========================================================================== */

#pragma once

#include "../qbLinearAlgebra/qbVector.h"
#include "../ray.h"

namespace raytrace {
    class ObjectBase {
    public:
        // constructors and deconstructors
        ObjectBase();
        virtual ~ObjectBase();

        // test for interceptions from ray
        virtual bool TestIntersection(const Ray &castRay,
            qbVector<double> &intPoint,
            qbVector<double> &localNorm,
            qbVector<double> &localColor); // bool: intercepted or not

        // test whether two flaoting points are close to being equal (truncation)
        bool CheckAreClose(const double float1, const double float2);

        // getter function for location
        qbVector<double> GetPosition() {
            return m_location;
        }

        double GetRadius() const { return m_radius; }


        // member variables
        qbVector<double> m_baseColor {3};
        qbVector<double> m_location {3};
        double m_radius;

    };
}