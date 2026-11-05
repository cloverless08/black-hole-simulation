//
// Created by cdemin on 11/3/26.
//

#pragma once

#include <memory>

#include "../qbLinearAlgebra/qbVector.h"
#include "../ray.h"
#include "object_base.h"

namespace raytrace {
    class LightBase {
    public:
        // constructor and destructor
        LightBase();
        virtual ~LightBase(); // needs to be inherited

        // compute illumination contribution
        virtual bool ComputeIllumination(const qbVector<double> &intPoint,
            const qbVector<double> &localNorm,
            const std::vector<std::shared_ptr<raytrace::ObjectBase>> &objectList,
            const std::shared_ptr<raytrace::ObjectBase> &currentObject,
            qbVector<double> &color, double &intensity);

    //private:
        qbVector<double> m_color{3};
        qbVector<double> m_location{3};
        double m_intensity{3};
    };
}