//
// Created by cdemin on 11/1/26.
//

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


        // member variables
        qbVector<double> m_baseColor {3};

    };
}