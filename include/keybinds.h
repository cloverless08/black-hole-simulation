/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    include/keybinds.h
//  Purpose: Declares GetKeyPress(), the SDL keyboard/event handler.
/* ========================================================================== */

#pragma once

#include "vec.h"
#include <SDL2/SDL.h>

void GetKeyPress(SDL_Event &event, bool &running, raytrace::Camera &cam, int height, int width, std::vector<uint32_t>& buffer);