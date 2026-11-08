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

                int stepsIncreasing = 0;
                double lastDistanceToSphere = 0.0;

                raytrace::Ray camRay; // construct ray for this pixel
                qbVector<double> intersectionPoint(3);
                qbVector<double> localNorm(3);
                qbVector<double> localColor(3);

                double U = (static_cast<double>(x) * factorX) - 1.0;
                double V = (static_cast<double>(y) * factorY) - 1.0;

                Cam.GenerateRay(U, V, camRay);
                bool hit = false;
                std::shared_ptr<raytrace::ObjectBase> hitObject;
                for (auto& object : objectList) {
                    const qbVector<double> rayOrigin = camRay.GetPoint1();
                    qbVector<double> rayDirection = camRay.m_lab;
                    rayDirection.Normalize();

                    constexpr int maxMarchSteps = 128;
                    constexpr double maxMarchDistance = 10.0;
                    constexpr double hitThreshold = 0.025;
                    const qbVector<double> sphereCenter{std::vector<double>{0.0, 0.0, 0.0}};
                    double distanceAlongRay = 0.0;

                    if (stepsIncreasing >= 2) { // if there are more than 4 steps where the ray gets father away, cancel early
                        hit = false;
                        break;
                    }

                    for (int step = 0; step < maxMarchSteps; ++step) {
                        const qbVector<double> marchPoint = rayOrigin + distanceAlongRay * rayDirection;
                        const double distanceToSphere = Length3D(marchPoint, sphereCenter) - 1.0;

                        if (distanceToSphere > lastDistanceToSphere) {
                            stepsIncreasing += 1;
                        }
                        lastDistanceToSphere = distanceToSphere;

                        if (distanceToSphere <= hitThreshold) {
                            intersectionPoint = marchPoint;
                            localNorm = marchPoint;
                            localNorm.Normalize();
                            hit = true;
                            hitObject = object;
                            break;
                        }
                        if (distanceAlongRay > maxMarchDistance) {
                            break;
                        }
                        distanceAlongRay += distanceToSphere;
                    }
                    if (hit) {
                        break;
                    }
                }

                if (hit) {
                    double intensity;
                    qbVector<double> color {3};
                    bool validIllumination = false;
                    for (auto currentLight : lightList) { // currently hard-coded to only deal with one light source
                        validIllumination = currentLight -> ComputeIllumination(intersectionPoint,
                            localNorm,
                            objectList,
                            hitObject,
                            color,
                            intensity);
                    }

                    SetPixel(buffer.data(), width, height, x, y, 255 * intensity, 255 * intensity, 255 * intensity);
                } else {
                    SetPixel(buffer.data(), width, height, x, y, 0.0, 0.0, 0.0);
                }
            }
        }

    }
}