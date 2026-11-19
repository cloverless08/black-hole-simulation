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

                // actual geodesic shit
                



                    SetPixel(buffer.data(), width, height, x, y, 173, 255, 95); // needs to change
                }
            }
        }

    }