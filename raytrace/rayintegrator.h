//
// Created by cdemin on 11/7/26.
//

#pragma once

#include <cstdint>
#include <memory>

#include "camera.h"
#include "../qbLinearAlgebra/qbVector.h"

#include "../include/threading.h"
#include "../include/loop.h"
#include "../include/main_utils.h"

#include <functional>

namespace raytrace {
    class RayIntegrator {
    };

    class LinearRayIntegrator {
    // port from threading
    public:
        // default constructor and destructor
        LinearRayIntegrator();
        ~LinearRayIntegrator();

        // mono function for this class, nothing too fancy, basic straight line ray tracing (lifted previously from threading)
        static void LinearRayTrace(std::vector<uint32_t>& buffer,
        raytrace::Camera& Cam,
        int startY, int endY,
        int height, int width,
        math::Vec3 backgroundColor,
        double factorX, double factorY,
        std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList);
    };

    class MarchingRayIntegrator {
    public:
        // default constructor and destructor
        MarchingRayIntegrator();
        ~MarchingRayIntegrator();


        static void MarchRayTrace(std::vector<uint32_t>& buffer,
        raytrace::Camera& Cam,
        int startY, int endY,
        int height, int width,
        math::Vec3 backgroundColor,
        double factorX, double factorY,
        std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList);
    };

    class GeodesicRayIntegrator : public RayIntegrator {

    };
} // raytrace
