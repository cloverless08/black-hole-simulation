//
// Created by cdemin on 11/22/26.
//

#pragma once

#include <array>
#include <vector>
#include <cstdint>

#include <main_utils.h>

// called when s is pressed
inline std::vector<uint32_t> RenderScreenshot(std::vector<uint32_t> inputBuffer, int width, int height) {

    // creates new
    std::vector<uint32_t> outputBuffer(inputBuffer.size(), 0);

    // gets each pixel's color from screen and repacks it into the proper color chanell for screenshjots
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            uint32_t oldColor = inputBuffer[y * width + x];
            int newR = oldColor >> 24;
            int newG = oldColor >> 16;
            int newB = oldColor >> 8;

            // borrowing packing from setpixel, but in reverse order
            uint32_t newColor = newR | newG | newB;
            outputBuffer[y * width + x] = newColor;
        }
    }

    // returns repacked buffer for screenshots
    return outputBuffer;
}