/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    include/threading.h
//  Purpose: Declares the functions that render a frame across multiple
//           threads using the linear, marching or geodesic integrators.
/* ========================================================================== */

#pragma once

#include <thread>
#include <vector>

#include "loop.h"

void CreateLinearThreads(std::vector<uint32_t>& buffer, int numThreads,
    // arguments for the loop3D that has to get passed, fix this bc its sloppy
    raytrace::Camera& Cam,
    int height, int width,
    math::Vec3 backgroundColor,
    double factorX, double factorY,
    std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList);

void CreateMarchedThreads(std::vector<uint32_t>& buffer, int numThreads,
    // arguments for the loop3D that has to get passed, fix this bc its sloppy
    raytrace::Camera& Cam,
    int height, int width,
    math::Vec3 backgroundColor,
    double factorX, double factorY,
    std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList);

void CreateGeodesicThreads(std::vector<uint32_t>& buffer, int numThreads,
    // arguments for the loop3D that has to get passed, fix this bc its sloppy
    raytrace::Camera& Cam,
    int height, int width,
    math::Vec3 backgroundColor,
    double factorX, double factorY,
    std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList);
