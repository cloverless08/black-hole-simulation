#pragma once

#include "structs.h"
#include <SDL2/SDL.h>

void GetKeyPress(SDL_Event &event, bool &running, raytrace::Camera &cam);