//
// Created by cdemin on 9/10/26.
//
#pragma once

#include <array>
#include <vector>
#include "structs.h"

void loop3D(std::vector<uint32_t>& buffer,
    BlackHole& hole, Camera& cam,
    int xPixel, int yPixel,
    const int height, const int width,
    Vec3 backgroundColor);

void loop2D(std::vector<uint32_t>& buffer,
    BlackHole& hole,
    int pixelX, int pixelY,
    const int height, const int width,
    std::array<int,
    4> backgroundColor);

void test_loop(std::vector<uint32_t>& buffer, int pixelX, int pixelY, int height, int width);
