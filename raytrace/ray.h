/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    raytrace/ray.h
//  Purpose: Declares the Ray class, defined by two points and the vector
//           between them.
/* ========================================================================== */

#pragma once

#include "vec.h"
#include "../qbLinearAlgebra/qbVector.h"

namespace raytrace {
    class Ray {
    public:
        //defualt constructor
        Ray();
        Ray(const qbVector<double> &point1, const qbVector<double> &point2);

        // getter functions
        qbVector<double> GetPoint1() const;
        qbVector<double> GetPoint2() const;

        // --------------------------------
        qbVector<double> m_point1 = qbVector<double>(3);
        qbVector<double> m_point2 = qbVector<double>(3);
        qbVector<double> m_lab = qbVector<double>(3); // the vector *between* point 1 and 2

    };
}
//