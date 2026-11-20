/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    src/keybinds.cpp
//  Purpose: Polls SDL events and handles keyboard input for quitting and
//           moving the camera.
/* ========================================================================== */

#include <array>

#include "main_utils.h"
#include "../raytrace/camera.h"
#include "../qbLinearAlgebra/qbVector.h"

#include <SDL2/SDL.h>

void GetKeyPress(SDL_Event &event, bool &running, raytrace::Camera &cam) {
    // poll all events
        while (SDL_PollEvent(&event)) {
            const std::array<std::string, 4> msgType = {"SYSTEM", "ERROR", "SETUP", "WARN"};
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
                        cam.SetPosition(std::vector{0.0 + cos(10.0) * cam.GetDistanceFromOrigin(), 0.0 + sin(10.0) * cam.GetDistanceFromOrigin(), 0.0});
                        cam.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}); // look at origin
                        cam.UpdateCamera();
                        break;
                    case SDLK_LEFT:
                        StrOut("Left Arrow Pressed", msgType[0]);
                        cam.SetPosition(std::vector{0.0 - cos(10.0) * cam.GetDistanceFromOrigin(), 0.0 - sin(10.0) * cam.GetDistanceFromOrigin(), 0.0});
                        cam.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}); // look at origin
                        cam.UpdateCamera();
                        break;
                    case SDLK_UP:
                        StrOut("Up Arrow Pressed", msgType[0]);
                        cam.SetPosition(std::vector{0.0 + cos(10.0) * cam.GetDistanceFromOrigin(), 0.0, 0.0 + sin(10.0) * cam.GetDistanceFromOrigin(),});
                        cam.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}); // look at origin
                        cam.UpdateCamera();
                        break;
                    case SDLK_DOWN:
                        StrOut("Down Arrow Pressed", msgType[0]);
                        cam.SetPosition(std::vector{0.0 - cos(10.0) * cam.GetDistanceFromOrigin(), 0.0, 0.0 - sin(10.0) * cam.GetDistanceFromOrigin(),});
                        cam.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}); // look at origin
                        cam.UpdateCamera();
                        break;
                    case SDLK_d:
                        StrOut("D: Diagnostics Output", msgType[0]);
                        break;
                    case SDLK_s:
                        StrOut("S: Screenshot", msgType[0]);
                        break;
                    case SDLK_p:
                        StrOut("P: Pause", msgType[0]);
                    default:
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                //std::cout << "Key Was Pressed" << std::endl;
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        StrOut("Escape Key Released", msgType[0]);
                        break;
                    case SDLK_RIGHT:
                        StrOut("Right Arrow Released", msgType[0]);
                        break;
                    case SDLK_LEFT:
                        StrOut("Left Arrow Released", msgType[0]);
                        break;
                    case SDLK_UP:
                        StrOut("Up Arrow Released", msgType[0]);
                        break;
                    case SDLK_DOWN:
                        StrOut("Down Arrow Released", msgType[0]);
                        break;
                    default:
                        break;
                }
            }
        }
}