//
// Created by cdemin on 11/22/26.
//

#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include <chrono>
#include <format>
#include <string>

#include <main_utils.h>

// called when s is pressed
inline std::vector<uint32_t> RenderScreenshot(std::vector<uint32_t> inputBuffer, int width, int height) {

    // creates new
    std::vector<uint32_t> outputBuffer(inputBuffer.size(), 0);

    // gets each pixel's color from screen and repacks it into the proper color chanell for screenshjots
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            uint32_t oldColor = inputBuffer[y * width + x];
            uint8_t newR = oldColor >> 24;
            uint8_t newG = oldColor >> 16;
            uint8_t newB = oldColor >> 8;

            // borrowing packing from setpixel, but in reverse order
            uint32_t newColor = newB << 16 | newG << 8 | newR;
            outputBuffer[y * width + x] = newColor;
        }
    }

    // returns repacked buffer for screenshots
    return outputBuffer;
}

// creates name for the screenshot based on current time and date
inline std::string GenerateScreenshotName() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << "screenshotBHS_" << std::put_time(std::gmtime(&now_c), "%Y-%m-%d_%H-%M-%S.jpg");
    return ss.str();
}