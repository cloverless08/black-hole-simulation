//
// Created by cdemin on 11/7/26.
//

//
// Created by cdemin on 11/7/26.
//

#include "rayintegrator.h"
#include "../include/main_utils.h"

#include <algorithm>

namespace raytrace {
    raytrace::GeodesicRayIntegrator::GeodesicRayIntegrator() {

    }

    raytrace::GeodesicRayIntegrator::~GeodesicRayIntegrator() {

    }

    void raytrace::GeodesicRayIntegrator::GeodesicRayTrace(std::vector<uint32_t>& buffer,
    raytrace::Camera& Cam,
    int startY, int endY,
    int height, int width,
    math::Vec3 backgroundColor,
    double factorX, double factorY,
    std::vector<std::shared_ptr<raytrace::ObjectBase>>& objectList, std::vector<std::shared_ptr<raytrace::LightBase>>& lightList) {
        /*
         * This should be repeated one time for every x and y pixel, each frame
         */

        for (int y = startY; y < endY; ++y) {
            for (int x = 0; x < width; ++x) {

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

                    SetPixel(buffer.data(), width, height, x, y, 173 * intensity, 255 * intensity, 95 * intensity); // needs to change
                } else {
                    SetPixel(buffer.data(), width, height, x, y, 0.0, 0.0, 0.0); // needs to change (?)
                }
            }
        }

    }
}