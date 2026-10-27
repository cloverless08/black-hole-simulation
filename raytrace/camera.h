//
// Created by cdemin on 10/13/26.
//

#pragma once

#include "../include/structs.h"

struct Camera {
    Vec3   eye;        // position in world space
    Vec3   forward;    // unit vector, direction of view
    Vec3   right;      // unit vector, camera-local +X
    Vec3   up;         // unit vector, camera-local +Y
    double fovY;       // vertical field of view, radians
    double aspect_ratio;

    // default constructor
    Camera() {
        eye = Vec3(0, 0, 0);
        forward = Vec3(0, 0, -1);
        right = Vec3(1, 0, 0);
        up = Vec3(0, 1, 0);
        fovY = 45.0;
        aspect_ratio = 1.0;
    };
};
