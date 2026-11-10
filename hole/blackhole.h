//
// Created by cdemin on 11/5/26.
//

#pragma once

#include "../raytrace/objects/object.h"

class BlackHole : public ObjectBase {
public:
    // default destructor and constructor
    BlackHole(double eventHorizon, double mass);
    virtual ~BlackHole() override;

private:
    double eventHorizon;
    double mass;
};