//
// Created by cdemin on 11/7/26.
//

#include "rayintegrator.h"
#include "../include/main_utils.h"

#include <algorithm>

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

                double U = (static_cast<double>(x) * factorX) - 1.0;
                double V = (static_cast<double>(y) * factorY) - 1.0;

                Cam.GenerateRay(U, V, camRay);
                bool hit = false;
                if (!objectList.empty()) {
                    const qbVector<double> rayOrigin = camRay.GetPoint1();
                    qbVector<double> rayDirection = camRay.m_lab;
                    rayDirection.Normalize();

                    constexpr int maxMarchSteps = 256;
                    constexpr double maxMarchDistance = 100.0;
                    constexpr double hitThreshold = 0.001;
                    const qbVector<double> sphereCenter{std::vector<double>{0.0, 0.0, 0.0}};
                    double distanceAlongRay = 0.0;

                    for (int step = 0; step < maxMarchSteps; ++step) {
                        const qbVector<double> marchPoint = rayOrigin + distanceAlongRay * rayDirection;
                        const double distanceToSphere = Length3D(marchPoint, sphereCenter) - 1.0;
                        if (distanceToSphere <= hitThreshold) {
                            hit = true;
                            break;
                        }
                        if (distanceAlongRay > maxMarchDistance) {
                            break;
                        }
                        distanceAlongRay += distanceToSphere;
                    }
                }

                if (hit) {
                    SetPixel(buffer.data(), width, height, x, y, 255, 0, 0);
                } else {
                    SetPixel(buffer.data(), width, height, x, y,
                        static_cast<uint8_t>(std::clamp(backgroundColor.x(), 0.0, 255.0)),
                        static_cast<uint8_t>(std::clamp(backgroundColor.y(), 0.0, 255.0)),
                        static_cast<uint8_t>(std::clamp(backgroundColor.z(), 0.0, 255.0)));
                }
            }
        }

    }
}