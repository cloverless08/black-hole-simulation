//
// Created by cdemin on 11/7/26.
//

#include "rayintegrator.h"

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
                qbVector<double> marchPoint {std::vector<double>{
                camRay.GetPoint2().GetElement(0),
                camRay.GetPoint2().GetElement(1),
                camRay.GetPoint2().GetElement(2)
                }};

                for (auto object : objectList) {
                    // double mindistance = 1000000000
                    // disance between march point and origin of object (x^2 + y^2) - radius
                    // if distance < mindistance, mindistance = distance
                }
                // marchpoint steps 
            }
        }

    }
}