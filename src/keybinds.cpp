//
// Created by cdemin on 9/15/26.
//

#include <iostream>
#include <ostream>
#include <array>
#include <thread>

#include "main_utils.h"
#include "structs.h"

#include <SDL2/SDL.h>

void GetKeyPress(SDL_Event &event, bool &running, Camera &cam) {

    const std::array<std::string, 4> msgType = {"SYSTEM", "ERROR", "SETUP", "WARN"}; // strOut() helpful labels

        // poll all events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                //std::cout << "Key Was Pressed" << std::endl;
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        StrOut("Escape Key Pressed", msgType[0]);
                        break;
                    case SDLK_RIGHT:
                        StrOut("Right Arrow Pressed", msgType[0]);
                       //cam.yaw = ((cam.yaw + 10) % 361);
                        break;
                    case SDLK_LEFT:
                        StrOut("Left Arrow Pressed", msgType[0]);
                        //cam.yaw = ((cam.yaw - 10) % 361);
                        break;
                    case SDLK_UP:
                        StrOut("Up Arrow Pressed", msgType[0]);
                        //cam.pitch = ((cam.pitch + 10) % 361);
                        break;
                    case SDLK_DOWN:
                        StrOut("Down Arrow Pressed", msgType[0]);
                        //cam.pitch = ((cam.pitch - 10) % 361);
                        break;
                    case SDLK_q:
                        StrOut("Q: Camera Position", msgType[0]);
                        //std::cout << cam.pitch << " " << cam.yaw << std::endl;
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                //std::cout << "Key Was Pressed" << std::endl;
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        StrOut("Escape Key Released", msgType[0]);
                        running = false;
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
                }
            }
        }
}