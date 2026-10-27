//
// Created by cdemin on 10/13/26.
//

#pragma once

#include "../include/structs.h"

namespace raytrace {
    class Camera {
    public:

        math::Vec3   eye;        // position in world space
        math::Vec3   forward;    // unit vector, direction of view
        math::Vec3   right;      // unit vector, camera-local +X
        math::Vec3   up;         // unit vector, camera-local +Y
        double fovY;       // vertical field of view, radians
        double aspect_ratio;

        // default constructor
        Camera() {
            eye = math::Vec3(0, 0, 0);
            forward = math::Vec3(0, 0, -1);
            right = math::Vec3(1, 0, 0);
            up = math::Vec3(0, 1, 0);
            fovY = 45.0;
            aspect_ratio = 1.0;
        };
    };
}