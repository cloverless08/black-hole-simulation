//
// Created by cdemin on 11/8/26.
//

#pragma once
#include "object_base.h"

class ObjPlane : public raytrace::ObjectBase {
public:
    ObjPlane();

    virtual ~ObjPlane() override;

    virtual bool TestIntersection(const raytrace::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNorm, qbVector<double> &localColor) override;

private:
    qbVector<double> m_corner1;
    qbVector<double> m_corner2;
    qbVector<double> m_corner3;
};