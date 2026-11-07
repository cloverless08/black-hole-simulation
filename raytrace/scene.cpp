//
// Created by cdemin on 11/7/26.
//

#include "scene.h"
#include "../include/main_utils.h"

namespace raytrace {
    raytrace::Scene::Scene() {
        std::cout << "constructing scene" << std::endl;
        raytrace::Scene::InitScene();
    }

    raytrace::Scene::~Scene() {
        std::cout << "destructing scene" << std::endl;
    }

    // initalize scene
    bool raytrace::Scene::InitScene() {
        // setup camera
        cam.SetPosition(qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}} );
        cam.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}); // look at origin
        cam.SetUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});

        cam.SetHorizontalSize(0.25);
        cam.SetAspectRatio(4.0 / 3.0);

        cam.UpdateCamera();

        // construct a test sphere at origin
        objectList.push_back(std::make_shared<raytrace::ObjSphere>(raytrace::ObjSphere()));

        // construct a test light source
        lightList.push_back(std::make_shared<raytrace::PointLight>(raytrace::PointLight())); // calls default constructor
        lightList.at(0) -> m_location = qbVector<double> {std::vector<double>{5.0, -10.0, -5.0}};
        lightList.at(0) -> m_color = qbVector<double> {std::vector<double>{255.0, 255.0, 255.0}};
        std::cout << objectList.data() << std::endl;
        std::cout << lightList.data() << std::endl;
    }

    // render function
    bool raytrace::Scene::Render() {

    }
} // raytrace