/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    astronomy/blackhole.h
//  Purpose: Declares the BlackHole scene object, sized by its mass.
/* ========================================================================== */

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
