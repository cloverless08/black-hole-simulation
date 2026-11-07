//
// Created by cdemin on 11/7/26.
//

#include "rayintegrator.h"

namespace raytrace {
    // linear ray tracing port:
    raytrace::LinearRayIntegrator::LinearRayIntegrator() {
        // empty for now
    }
    raytrace::LinearRayIntegrator::~LinearRayIntegrator() {
        // empty for now
    }

    void raytrace::LinearRayIntegrator::LinearRayTrace(std::vector<uint32_t>& buffer,
    raytrace::Camera& Cam,
    int startY, int endY,
    int height, int width,
    math::Vec3 backgroundColor,
    double factorX, double factorY,
    std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList) {
    /*
     * This should be repeated one time for every x and y pixel, each frame
     */

    for (int pixelY = startY; pixelY < endY; ++pixelY) {
        for (int pixelX = 0; pixelX < width; ++pixelX) {
            raytrace::Ray camRay;
            qbVector<double> intersectionPoint(3);
            qbVector<double> localNorm(3);
            qbVector<double> localColor(3);

            double minDistance = 1e6;
            double maxDistance = 0.0;

            /*
            std::cout << "x = " << pixelX << " y = " << pixelY << std::endl;
            std::cout << "Starting calculation..." << std::endl;
            */

            double U = (static_cast<double>(pixelX) * factorX) - 1.0;
            double V = (static_cast<double>(pixelY) * factorY) - 1.0;

            Cam.GenerateRay(U, V, camRay);

            // test for intersections with all objects in scene
            for (auto currentObject : objectList) { // loop through all objects in object list and return reference to that in currentObject
                bool validIntersection = currentObject -> TestIntersection(camRay, intersectionPoint, localNorm, localColor);

                if (validIntersection) {
                    // compute intensity of illumination
                    double intensity;
                    qbVector<double> color {3};
                    bool validIllumination = false;
                    for (auto currentLight : lightList) { // currently hard-coded to only deal with one light source
                        validIllumination = currentLight -> ComputeIllumination(intersectionPoint,
                            localNorm,
                            objectList,
                            currentObject,
                            color,
                            intensity);
                    }

                    // compute distance between camera and int
                    double dist = (intersectionPoint - camRay.m_point1).norm();
                    if (dist > maxDistance) { // check mainly for debugging
                        maxDistance = dist;
                    }

                    if (dist < minDistance) { // check mainly for debugging
                        minDistance = dist;
                    }

                    //outputImage.SetPixel(pixelX, pixelY, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
                    if (validIllumination) {
                        SetPixel(buffer.data(), width, height, pixelX, pixelY, 255.0 * intensity, 0.0, 0.0);
                    } else {
                        SetPixel(buffer.data(), width, height, pixelX, pixelY, 0.0, 0.0, 0.0); // sets black if theres no illumination
                    }


                    //std::cout << "true" << std::endl;
                } else {
                    SetPixel(buffer.data(), width, height, pixelX, pixelY, 0.0, 0.0, 0.0);
                    //std::cout << "false" << std::endl;
                }

                //std::cout << "done" << std::endl;
            }
        }
    }
}
} // raytrace