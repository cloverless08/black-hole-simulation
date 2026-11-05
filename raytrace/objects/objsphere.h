//
// Created by cdemin on 11/1/26.
//

#pragma once

#include "object_base.h"

namespace raytrace {
    class ObjSphere : public ObjectBase {
    public:
        // default constructor, will define a unit sphere at origin
        ObjSphere();

        // override the base destructor and functions
        virtual ~ObjSphere() override;

        virtual bool TestIntersection(const Ray &castRay,
            qbVector<double> &intPoint,
            qbVector<double> &localNorm,
            qbVector<double> &localColor) override;

    private:

    };
}