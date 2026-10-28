/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//  v0.4.0
/* ========================================================================== */

#include <eigen3/Eigen/Dense>
#include <SDL2/SDL.h>
#include <vector>
#include <array>
#include <string>
#include <cstdint>
#include <iomanip>

#include "main_utils.h"
#include "structs.h"
#include "loop.h"
#include "keybinds.h"
#include "../raytrace/camera.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define newline "\n"

// global constants
enum SCREEN_RESOLUTION {
    // standard resolutions
    STANDARD_W = 640,
    MOVING_W = 320,

    // for while camera is moving, to act as a sort of preview
    STANDARD_H = 480,
    MOVING_H = 240,
};

constexpr int BLACK_HOLE_MASS = 100;
constexpr double BLACK_HOLE_RADIUS = 0.25;
const math::Vec3 BLACK_HOLE_INITIAL_POSITION;

const std::array<std::string, 4> msgType = {"SYSTEM", "ERROR", "SETUP", "WARN"}; // strOut() helpful labels
const math::Vec3 BACKGROUND_COLOR = {0, 0, 0};

int main() {

    TerminalInfoHeader();
    SDL_Delay(500);

    // local variables
    bool running = true;
    bool setupMessageSent = false;

    enum SCREEN_RESOLUTION resolutionWidth = STANDARD_W;
    enum SCREEN_RESOLUTION resolutionHeight = STANDARD_H;

    StrOut("Local Variables Initialized.", msgType[2]);


    // initial warnings and output
    StrOut("CSC1060 - Capstone Project", "info");
    StrOut("By Carrick De Min, Fall 2026", "info");
    StrOut("This program is under development and may not function as expected.", "warn");


    // initialize sdl2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        StrOut(std::string("SDL_Init failed: ") + SDL_GetError(), msgType[1]);
        return 1;
    }

    // built in event struct initialized as "event" from now on
    SDL_Event event;
    StrOut("SDL2 Initialized.", msgType[2]);


    // structs required for sdl2
    SDL_Window* window = SDL_CreateWindow(
        "CSC1060 Capstone Project",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        resolutionWidth, resolutionHeight,
        SDL_WINDOW_SHOWN
        );
    if (!window) {
        StrOut(std::string("CreateWindow failed: ") + SDL_GetError(), msgType[1]);
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );
    if (!renderer) {
        StrOut(std::string("CreateRenderer failed: ") + SDL_GetError(), msgType[1]);
        return 1;
    }

    SDL_Texture* pixelBufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888, // 32-bit format for 8 bits per channel
        SDL_TEXTUREACCESS_STREAMING, // allows fast cpu to gpu updates
        resolutionWidth, resolutionHeight // screen resolution
        );
    if (!pixelBufferTexture) {
        StrOut(std::string("CreateTexture failed: ") + SDL_GetError(), msgType[1]);
        return 1;
    }

    StrOut("SDL2 Structs Initialized.", msgType[2]);


    // create canvas pixel buffer in memory
    std::vector<uint32_t> pixelBuffer(resolutionWidth * resolutionHeight, 0);
    StrOut("Pixel Buffer Initialized.", msgType[2]);

    // initialize custom structs
    BlackHole hole;
    hole.mass = BLACK_HOLE_MASS;
    hole.position = BLACK_HOLE_INITIAL_POSITION;
    hole.radius = BLACK_HOLE_RADIUS;
    raytrace::Camera cam{};
    StrOut("Custom Structs Initialized.", msgType[2]);

    // window loop
    StrOut("Starting Program Loop...", msgType[0]);
    while (running) {

        // poll all events
        GetKeyPress(event, running, cam);
       
        // update pixel buffer
         for (int pixelY = 0; pixelY < resolutionHeight; pixelY++) {
             for (int pixelX = 0; pixelX< resolutionWidth; pixelX++) {
                loop3D(pixelBuffer, hole, cam, pixelX, pixelY, resolutionHeight, resolutionWidth, BACKGROUND_COLOR, setupMessageSent);
                 //test_loop(pixelBuffer, pixelX, pixelY, resolutionHeight, resolutionWidth);
             }
         }


        // update render texture (pixel buffer)
        SDL_UpdateTexture(
            pixelBufferTexture,
            nullptr,                   // NULL updates the entire texture
            pixelBuffer.data(),            // Pointer to our raw CPU buffer
            resolutionWidth * sizeof(uint32_t)
        );

        // render loop
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, pixelBufferTexture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        //SDL_Delay(25);

    }
    StrOut("Closing Program Loop...", msgType[0]);

    StrOut("Pixel Buffer Deleted", msgType[3]);

    SDL_DestroyTexture(pixelBufferTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    StrOut("SDL Structs Deleted", msgType[3]);

    return 0;
}
