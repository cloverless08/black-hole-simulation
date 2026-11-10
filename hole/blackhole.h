//
// Created by cdemin on 11/5/26.
//

#pragma once

#include "../raytrace/objects/object.h"

class BlackHole : public ObjectBase {
public:
    // default destructor and constructor
    BlackHole(double eventHorizon, double mass);
    virtual ~BlackHole();

private:
    double eventHorizon; // acts as radius where light cannot escape
    double mass; // linear proportional to event horizon, essentially defines size
};