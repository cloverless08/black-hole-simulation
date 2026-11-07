//
// Created by cdemin on 9/10/26.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <array>

#include "main_utils.h"
#include "structs.h"
#include "loop.h"
#include "../raytrace/camera.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define newline "\n"

// outputs gradient just to test render loop and display
void test_loop(std::vector<uint32_t>& buffer, int pixelX, int pixelY, const int height, const int width) { // old loop that draws a gradient as i was learning
    // normalize pixels into UV coordinates 0 through 1
    const double u = static_cast<double>(pixelX) / height;
    const double v = static_cast<double>(pixelY) / width;

    math::Vec2 rayDir = {u, v};

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