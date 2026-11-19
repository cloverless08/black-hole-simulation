//
// Created by cdemin on 11/5/26.
//

#pragma once

#include "../raytrace/objects/object_base.h"

class BlackHole : public ObjectBase {
public:
    // default destructor and constructor
    BlackHole(double mass);
    virtual ~BlackHole();

private:
    double mass; // linear proportional to event horizon, essentially defines size
};