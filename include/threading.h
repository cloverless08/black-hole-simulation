//
// Created by cdemin on 11/5/26.
//

#pragma once

#include <thread>
#include <vector>

#include "loop.h"


void RenderFromThread(std::vector<uint32_t>& buffer,
raytrace::Camera& Cam,
    int x, int y,
    const int height, const int width,
    math::Vec3 backgroundColor,
    double factorX, double factorY,
    std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList);

void CreateThreads(std::vector<uint32_t>& buffer, int numThreads,
    // arguments for the loop3D that has to get passed, fix this bc its sloppy
    raytrace::Camera& Cam,
    int height, int width,
    math::Vec3 backgroundColor,
    double factorX, double factorY,
    std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList);
