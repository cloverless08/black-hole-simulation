/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    include/loop.h
//  Purpose: Declares the test render loop and pulls in shared scene types.
/* ========================================================================== */

#pragma once

#include <array>
#include <vector>
#include <memory>

#include "../raytrace/objects/pointlight.h"
#include "../raytrace/objects/objsphere.h"
#include "vec.h"
#include "../raytrace/camera.h"

void test_loop(std::vector<uint32_t>& buffer, int pixelX, int pixelY, int height, int width);