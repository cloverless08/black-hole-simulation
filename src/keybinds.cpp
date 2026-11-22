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

            constexpr double CHANGE_ANGLE = 5.0;
            constexpr int CHANNELS = 4;

            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                //std::cout << "Key Was Pressed" << std::endl;
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        StrOut("Escape Key Pressed", msgType[0]);
                        running = false;
                        break;
                    case SDLK_RIGHT:
                        StrOut("Right Arrow Pressed", msgType[0]);
                        //cam.SetPosition(cam.GetPosition() + qbVector<double>{std::vector{0.025, 0.0, 0.0}});
                        //cam.SetPosition(cam.GetPosition() + qbVector<double>{std::vector{0.0 + cos(10.0) * cam.GetDistanceFromOrigin(), 0.0 + sin(10.0) * cam.GetDistanceFromOrigin(), 0.0}});
                        cam.SetPosition(std::vector{camX + (cos(CHANGE_ANGLE) * cam.GetDistanceFromOrigin()), camY + (sin(CHANGE_ANGLE) * cam.GetDistanceFromOrigin()), camZ});
                        cam.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}); // look at origin
                        cam.UpdateCamera();
                        break;
                    case SDLK_LEFT:
                        StrOut("Left Arrow Pressed", msgType[0]);
                        cam.SetPosition(std::vector{camX - (cos(CHANGE_ANGLE) * cam.GetDistanceFromOrigin()), camY - (sin(CHANGE_ANGLE) * cam.GetDistanceFromOrigin()), camZ});
                        cam.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}); // look at origin
                        cam.UpdateCamera();
                        break;
                    case SDLK_UP:
                        StrOut("Up Arrow Pressed", msgType[0]);
                        cam.SetPosition(std::vector{camX + (cos(CHANGE_ANGLE) * cam.GetDistanceFromOrigin()), camY, camZ + (sin(CHANGE_ANGLE) * cam.GetDistanceFromOrigin())});
                        cam.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}); // look at origin
                        cam.UpdateCamera();
                        break;
                    case SDLK_DOWN:
                        StrOut("Down Arrow Pressed", msgType[0]);
                        cam.SetPosition(std::vector{camX - (cos(CHANGE_ANGLE) * cam.GetDistanceFromOrigin()), camY, camZ - (sin(CHANGE_ANGLE) * cam.GetDistanceFromOrigin())});
                        cam.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}); // look at origin
                        cam.UpdateCamera();
                        break;
                    case SDLK_s:
                        StrOut("S: Screenshot", msgType[0]);

                        // write buffer as jpeg (so that black isnt rendered invisible
                        stbi_write_jpg("output.jpg", width, height, CHANNELS, RenderScreenshot(buffer, width, height).data(), width * CHANNELS);

                        break;
                    default:
                        break;
                }
            }
        }
}