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

void loop3D(std::vector<uint32_t>& buffer,
    BlackHole& hole, raytrace::Camera& Cam,
    int x, int y,
    const int height, const int width,
    math::Vec3 backgroundColor,
    bool& setupMessageSent,
    double factorX, double factorY,
    std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList);

void loop2D(std::vector<uint32_t>& buffer,
    const BlackHole& hole,
    int pixelX, int pixelY,
    const int height, const int width,
    std::array<int,4> backgroundColor);

void test_loop(std::vector<uint32_t>& buffer, int pixelX, int pixelY, int height, int width);