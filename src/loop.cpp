//
// Created by cdemin on 9/10/26.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <array>

#include "../include/main_utils.h"
#include "../include/structs.h"
#include "../include/loop.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define newline "\n"

void loop3D(std::vector<uint32_t>& buffer,
    BlackHole& hole, Camera& cam,
    int xPixel, int yPixel,
    const int height, const int width,
    std::array<int, 4> backgroundColor) {

    unsigned long long time = 0;

    // normalize pixels into UV coordinates 0 through 1
    const double xPixelCentered = static_cast<double>((2.0 * xPixel - width) / height);
    const double yPixelCentered = static_cast<double>((2.0 * yPixel - height) / height);

    int pixelR = backgroundColor[0];
    int pixelG = backgroundColor[1];
    int pixelB = backgroundColor[2];
    const int pixelA = backgroundColor[3];

    double worldX;
    double worldY;
    double worldZ;

    Vec3 rayOrigin; // needs to be set to camera coordinates when called
    Vec3 rayDir{worldX, worldY, worldZ};

    // theres no way this equation is right bro
    double rayLength = sqrt((rayDir.x() * rayDir.x())+(rayDir.y() * rayDir.y())+(rayDir.z() * rayDir.z()));

    SetPixel(buffer.data(), width, height,
    xPixel, yPixel, pixelR, pixelG, pixelB,
    pixelA);
}

void loop2D(std::vector<uint32_t>& buffer, BlackHole& hole, int pixelX, int pixelY, const int height, const int width, std::array<int, 4> backgroundColor) { // loop for pixel color assignments

    // normalize pixels into UV coordinates 0 through 1
    const double xCentered = ((2.0 * pixelX - width) / height);
    const double yCentered = ((2.0 * pixelY - height) / height);
    const int pixelA = backgroundColor[3];

    int pixelR = backgroundColor[0];
    int pixelG = backgroundColor[1];
    int pixelB = backgroundColor[2];

    Vec2 rayDir = {xCentered, yCentered};

    double length = std::sqrt(rayDir.x() * rayDir.x() + rayDir.y() * rayDir.y());

    if (length <= hole.radius) {
        // pixel is withing black hole radius
        pixelR = 0;
        pixelG = 0;
        pixelB = 0;
    } else if (length > hole.radius) {
        // pixel is outside radius, render background
        pixelR = 255;
        pixelG = 255;
        pixelB = 255;
    }

    SetPixel(buffer.data(), width, height,
        pixelX, pixelY, pixelR, pixelG, pixelB,
        255);
}

void test_loop(std::vector<uint32_t>& buffer, int pixelX, int pixelY, const int height, const int width) { // old loop that draws a gradient as i was learning
    // normalize pixels into UV coordinates 0 through 1
    const double u = static_cast<double>(pixelX) / height;
    const double v = static_cast<double>(pixelY) / width;

    Vec2 rayDir = {u, v};

    if (double length = std::sqrt(rayDir.x() * rayDir.x() + rayDir.y() * rayDir.y()); length > 0.0001) { // avoids NaN or division by zero at the centerpoint
        rayDir[0] /= length;
        rayDir[1] /= length;
    }

    // convert back to rgba
    int pixelR = static_cast<int>((rayDir.x() * 0.5 + 0.5) * 255);
    int pixelG = static_cast<int>((rayDir.y() * 0.5 + 0.5) * 255);
    //int pixelB = i;
    int pixelB = 255;

    SetPixel(buffer.data(), width, height,
        pixelX, pixelY, pixelR, pixelG, pixelB,
        255);
}