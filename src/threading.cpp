
//
// Created by cdemin on 11/5/26.
//

#include "../include/threading.h"
#include "../include/loop.h"
#include "../include/main_utils.h"

#include "../raytrace/rayintegrator.h"

#include <SDL2/SDL.h>

#include <functional>
#include <SDL_events.h>

void CreateLinearThreads(std::vector<uint32_t>& buffer, int numThreads,
                   // arguments for the loop3D that has to get passed, fix this bc its sloppy
                   raytrace::Camera& Cam,
                   int height, int width,
                   math::Vec3 backgroundColor,
                   double factorX, double factorY,
                   std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList) {
    // -------------------------------------------------

    //std::cout << "Initializing MultiThreading..." << std::endl;
    std::vector<std::thread> threads;
    raytrace::LinearRayIntegrator linearRayIntegrator;

    // integer division distributes any remainder across the ranges.
    for (int i = 0; i < numThreads; ++i) {
        int startY = i * height / numThreads;
        int endY = (i + 1) * height / numThreads;

        threads.emplace_back(linearRayIntegrator.LinearRayTrace, std::ref(buffer), std::ref(Cam),
            startY, endY, height, width, backgroundColor,
            factorX, factorY, objectList, lightList);
    }

    // wait for all threads to finish rendering
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void CreateMarchedThreads(std::vector<uint32_t>& buffer, int numThreads,
                   // arguments for the loop3D that has to get passed, fix this bc its sloppy
                   raytrace::Camera& Cam,
                   int height, int width,
                   math::Vec3 backgroundColor,
                   double factorX, double factorY,
                   std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList) {
    // -------------------------------------------------

    //std::cout << "Initializing MultiThreading..." << std::endl;
    std::vector<std::thread> threads;
    raytrace::MarchingRayIntegrator marchingRayIntegrator;

    // integer division distributes any remainder across the ranges.
    for (int i = 0; i < numThreads; ++i) {
        int startY = i * height / numThreads;
        int endY = (i + 1) * height / numThreads;

        threads.emplace_back(marchingRayIntegrator.MarchRayTrace, std::ref(buffer), std::ref(Cam),
            startY, endY, height, width, backgroundColor,
            factorX, factorY, objectList, lightList);
    }

    // wait for all threads to finish rendering
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void CreateGeodesicThreads(std::vector<uint32_t>& buffer, int numThreads,
    // arguments for the loop3D that has to get passed, fix this bc its sloppy
    raytrace::Camera& Cam,
    int height, int width,
    math::Vec3 backgroundColor,
    double factorX, double factorY,
    std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList, std::vector<std::shared_ptr<raytrace::LightBase>> lightList) {
    //-------------------------------------

    //std::cout << "Initializing MultiThreading..." << std::endl;
    std::vector<std::thread> threads;
    raytrace::GeodesicRayIntegrator GeodesicRayIntegrator;

    // integer division distributes any remainder across the ranges.
    for (int i = 0; i < numThreads; ++i) {
        int startY = i * height / numThreads;
        int endY = (i + 1) * height / numThreads;

        threads.emplace_back(GeodesicRayIntegrator.GeodesicRayTrace, std::ref(buffer), std::ref(Cam),
            startY, endY, height, width, backgroundColor,
            factorX, factorY, objectList, lightList);
    }

    // wait for all threads to finish rendering
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}
