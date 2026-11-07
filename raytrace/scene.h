//
// Created by cdemin on 11/7/26.
//

#pragma once

#include "camera.h"

#include "objects/objsphere.h"
#include "objects/pointlight.h"

namespace raytrace {
    class Scene {
    public:
        // default constructor and destructor
        Scene();
        ~Scene();

        // initialize and setup
        bool InitScene();

        // render function
        bool Render();

    private:
        // create camear in scene
        raytrace::Camera camera;

        // lists of all objects in scene
        std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList;

        // list of all light sources in scene
        std::vector<std::shared_ptr<raytrace::LightBase>> lightList;

        raytrace::ObjSphere m_testSphere; // test sphere at origin
    };
} // raytrace
