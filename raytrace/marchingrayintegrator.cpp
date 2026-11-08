//
// Created by cdemin on 11/7/26.
//

#include "rayintegrator.h"
#include "../include/main_utils.h"

namespace raytrace {
    raytrace::MarchingRayIntegrator::MarchingRayIntegrator() {

    }

    raytrace::MarchingRayIntegrator::~MarchingRayIntegrator() {

    }

    void raytrace::MarchingRayIntegrator::MarchRayTrace(std::vector<uint32_t>& buffer,
    raytrace::Camera& Cam,
    int startY, int endY,
    int height, int width,
    math::Vec3 backgroundColor,
    double factorX, double factorY,
    std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList) {
        /*
         * This should be repeated one time for every x and y pixel, each frame
         */

        for (int y = startY; y < endY; ++y) {
            for (int x = 0; x < width; ++x) {

                raytrace::Ray camRay; // construct ray for this pixel

                bool running = true;

                double U = (static_cast<double>(x) * factorX) - 1.0;
                double V = (static_cast<double>(y) * factorY) - 1.0;

                Cam.GenerateRay(U, V, camRay);
                qbVector<double> marchPoint {std::vector<double>{
                    camRay.GetPoint2().GetElement(0),
                    camRay.GetPoint2().GetElement(1),
                    camRay.GetPoint2().GetElement(2)
                    }};

                while (running) {
                    double distance = 0.0;
                    double minDistance = 8008.5;
                    for (auto object : objectList) {
                        distance = Length3D(marchPoint, qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}) - 1.0; // only works for sphere at origin

                        if (distance < 0.001) { // means there is an intersection, implement this isnt right twin
                            running = false;
                            SetPixel(buffer.data(), width, height, x, y, 255.0, 0.0, 0.0);
                        } else {
                            SetPixel(buffer.data(), width, height, x, y, 0.0, 0.0, 0.0);
                        }

                        if (distance < minDistance) {
                            minDistance = distance;
                        }
                    }

                   // P(t) = O + t * D
                    // D = V / ||V||

                    // move down the ray a scalar amount
                    qbVector<double> direction = marchPoint.Normalized();
                    marchPoint = marchPoint + distance * direction;
                }

            }
        }

    }
}