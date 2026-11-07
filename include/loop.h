//
// Created by cdemin on 9/10/26.
//
#pragma once

#include <array>
#include <vector>
#include <memory>

#include "../raytrace/objects/pointlight.h"
#include "../raytrace/objects/objsphere.h"
#include "structs.h"
#include "../raytrace/camera.h"

void test_loop(std::vector<uint32_t>& buffer, int pixelX, int pixelY, int height, int width);