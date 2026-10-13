//
// Created by cdemin on 10/13/26.
//

#pragma once

#endif //CSC1060_CAPSTONE_PROJECT_CAMERA_H

struct Camera {
    Vec3   eye;        // position in world space
    Vec3   forward;    // unit vector, direction of view
    Vec3   right;      // unit vector, camera-local +X
    Vec3   up;         // unit vector, camera-local +Y
    double fovY;       // vertical field of view, radians
    double aspect_ratio;

    Camera() {};

    Camera(Vec3 eye, Vec3 target, Vec3 worldUp, double fovY, double aspect);
};
