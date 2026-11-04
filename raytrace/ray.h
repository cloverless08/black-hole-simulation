#pragma once

#include "../include/cdVector.h"

namespace raytrace {
    class Ray {
    public:
        //defualt constructor
        Ray();
        Ray(const math::cdVector<double> &point1, const math::cdVector<double> &point2);

        // getter functions
        math::cdVector<double> GetPoint1() const;
        math::cdVector<double> GetPoint2() const;

        // --------------------------------
        math::cdVector<double> m_point1 = math::cdVector<double>(3);
        math::cdVector<double> m_point2 = math::cdVector<double>(3);
        math::cdVector<double> m_lab = math::cdVector<double>(3); // the vector *between* point 1 and 2


    };
}