/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    src/keybinds.cpp
//  Purpose: Polls SDL events and handles keyboard input for quitting and
//           moving the camera.
/* ========================================================================== */

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <array>

#include "main_utils.h"
#include "../raytrace/camera.h"
#include "../qbLinearAlgebra/qbVector.h"
#include "../include/stb_image_write.h"
#include "../include/screenshot.h"

#include <SDL2/SDL.h>

void GetKeyPress(SDL_Event &event, bool &running, raytrace::Camera &cam,
    int height, int width, std::vector<uint32_t>& buffer) {
    // poll all events
        while (SDL_PollEvent(&event)) {

            const std::array<std::string, 4> msgType = {"SYSTEM", "ERROR", "SETUP", "WARN"};
            const double camX = cam.GetPosition().GetElement(0);
            const double camY = cam.GetPosition().GetElement(1);
            const double camZ = cam.GetPosition().GetElement(2);

            constexpr double CHANGE_ANGLE_DEGREES = 5; // 15 degrees in radians
            constexpr double CHANGE_ANGLE_RADIANS = static_cast<double>(CHANGE_ANGLE_DEGREES) * M_PI / 180.0;
            constexpr int CHANNELS = 4;

            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                //std::cout << "Key Was Pressed" << std::endl;
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: // quit window and stop sim
                        StrOut("Escape Key Pressed", msgType[0]);
                        running = false;
                        break;
                    case SDLK_RIGHT: // yaw right (change azimuth)
                        StrOut("Right Arrow Pressed", msgType[0]);
                        cam.Orbit(CHANGE_ANGLE_RADIANS, 0.0);
                        break;
                    case SDLK_LEFT: // yaw left (change azimuth)
                        StrOut("Left Arrow Pressed", msgType[0]);
                        cam.Orbit(-CHANGE_ANGLE_RADIANS, 0.0);
                        break;
                    case SDLK_UP: // pitch up (change elevation)
                        StrOut("Up Arrow Pressed", msgType[0]);
                        cam.Orbit(0.0, -CHANGE_ANGLE_RADIANS);
                        break;
                    case SDLK_DOWN: // pitch down (change elevation
                        StrOut("Down Arrow Pressed", msgType[0]);
                        cam.Orbit(0.0, CHANGE_ANGLE_RADIANS);
                        break;
                    case SDLK_s: // take screenshot and write to file
                        StrOut("S: Screenshot", msgType[0]);

                        // write buffer as jpeg (so that black isnt rendered invisible
                        stbi_write_jpg(GenerateScreenshotName().c_str(), width, height, CHANNELS, RenderScreenshot(buffer, width, height).data(), width * CHANNELS);

                        break;
                    case SDLK_q: // move camera closer to origin
                        cam.SetDistanceFromOrigin(cam.GetDistanceFromOrigin() - 10.0);
                        cam.UpdateCamera();
                        break;
                    case SDLK_e: // move camera closer to origin
                        cam.SetDistanceFromOrigin(cam.GetDistanceFromOrigin() + 10.0);
                        cam.UpdateCamera();
                        break;
                    default:
                        break;
                }
            }
        }
}