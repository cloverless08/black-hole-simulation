/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    raytrace/rayintegrator.h
//  Purpose: Declares the ray integrators: linear (straight-line), marching,
//           and geodesic (curved-spacetime) ray tracing.
/* ========================================================================== */

#pragma once

#include <cstdint>
#include <memory>

#include "camera.h"
#include "../qbLinearAlgebra/qbVector.h"
#include "../include/vec.h"

#include "../include/threading.h"
#include "../include/loop.h"
#include "../include/main_utils.h"

#include <functional>

namespace raytrace {
    class RayIntegrator { // deprecated
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
    public:
        // default constructor and destructor
        GeodesicRayIntegrator();
        ~GeodesicRayIntegrator();


        static void GeodesicRayTrace(std::vector<uint32_t>& buffer,
        raytrace::Camera& Cam,
        int startY, int endY,
        int height, int width,
        math::Vec3 backgroundColor,
        double factorX, double factorY,
        std::vector<std::shared_ptr<raytrace::ObjectBase>>& objectList, std::vector<std::shared_ptr<raytrace::LightBase>>& lightList);

    private:
        // photon acceleration in Schwarzschild spacetime, written as a 3D cartesian ODE: a = -3 M h^2 pos / r^5
        static math::Vec3 Accel(const math::Vec3& pos, double h2);

        // advances pos/vel by one RK4 step of size dt
        static void RK4Step(math::Vec3& pos, math::Vec3& vel, double h2, double dt);

        // color of the sky in a given (unit) direction; checkerboard + stars so lensing is visible
        static math::Vec3 RenderBackground(const math::Vec3& dir);

        // color of the accretion disk at radius r
        static math::Vec3 AccretionDisk(double r);

        int NUM_CHECKERBOARD_ROWS = 36;
        int NUM_CHECKERBOARD_COLS = 72;
    };
} // raytrace
