/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//  v0.4.0
//
//  File:    src/main.cpp
//  Purpose: Program entry point; sets up SDL, the camera, scene objects and
//           lights, and runs the main render loop.
/* ========================================================================== */

// library includes
#include <SDL2/SDL.h>

#include <vector>
#include <array>
#include <string>
#include <cstdint>
#include <iomanip>
#include <memory>
#include <chrono>
#include <cmath>

// gnereal header file includes
#include "main_utils.h"
#include "vec.h"
#include "loop.h"
#include "keybinds.h"
#include "../raytrace/camera.h"
#include "../include/threading.h"
#include "../raytrace/rayintegrator.h"

#include "../raytrace/objects/objsphere.h"
#include "../raytrace/objects/pointlight.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define newline "\n"

// global constants
constexpr int  RESOLUTION_WIDTH = 640;
constexpr int RESOLUTION_HEIGHT = 480;

unsigned int static NUMBER_CORES = SDL_GetCPUCount();
unsigned int static AMOUNT_RAM = SDL_GetSystemRAM();

const math::Vec3 BLACK_HOLE_INITIAL_POSITION = {0.0, 0.0, 0.0}; // centers black hole in the middle of the world coordinates

const std::array<std::string, 4> msgType = {
    std::string("SYSTEM"),
    std::string("ERROR"),
    std::string("SETUP"),
    std::string("WARN")
}; // strOut() helpful labels

int main() {
    // put information and header into console
    TerminalInfoHeader();
    SDL_Delay(500);

    if (NUMBER_CORES == 0) {
        std::cout << "Could not detect core count. Falling back to 1.\n";
        NUMBER_CORES = 1;
    } else {
        std::cout << "Number of logical CPU cores: " << NUMBER_CORES << "\n";
    }

    if (AMOUNT_RAM == 0) {
        std::cerr << "Could not detect system ram.\n";
    } else {
        std::cout << "Total system RAM detected: " << AMOUNT_RAM << "MB\n";
    }

    // local variables
    bool running = true;

    constexpr double xFactor = 1.0 / (static_cast<double>(RESOLUTION_WIDTH) / 2.0);
    constexpr double yFactor = 1.0 / (static_cast<double>(RESOLUTION_HEIGHT) / 2.0);

    int frame = 0;
    //double THETA = 0;

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
        RESOLUTION_WIDTH, RESOLUTION_HEIGHT,
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
        RESOLUTION_WIDTH, RESOLUTION_HEIGHT // screen resolution
        );
    if (!pixelBufferTexture) {
        StrOut(std::string("CreateTexture failed: ") + SDL_GetError(), msgType[1]);
        return 1;
    }

    StrOut("SDL2 Structs Initialized.", msgType[2]);


    // create canvas pixel buffer in memory
    std::vector<uint32_t> pixelBuffer(RESOLUTION_WIDTH * RESOLUTION_HEIGHT, 0);
    StrOut("Pixel Buffer Initialized.", msgType[2]);


    // initialize raytracing
    StrOut("Initializing ray tracing structure.", msgType[2]);
    raytrace::Camera cam;
    // units are multiples of M: 30M out, slightly above the disk plane so the disk is seen tilted
    cam.SetPosition(qbVector<double>{std::vector<double>{0.0, -cam.GetDistanceFromOrigin(), 3.0}} );
    cam.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}); // look at origin
    cam.SetUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});

    cam.SetHorizontalSize(1.25);
    cam.SetAspectRatio(4.0 / 3.0);

    cam.UpdateCamera();
    StrOut("Ray Tracing Initialized.", msgType[2]);


    // create scene objects (test)
    // list of objects in scene
    // std::vector<std::shared_ptr<raytrace::ObjectBase>> objectList;
    //
    // // list of lights in scene
    // std::vector<std::shared_ptr<raytrace::LightBase>> lightList;
    //
    // // unit sphere on origin for testing
    // objectList.push_back(std::make_shared<raytrace::ObjSphere>(raytrace::ObjSphere(
    // std::vector<double>{1.0, 1.0, 0.0}, 1.0
    // )));
    // objectList.push_back(std::make_shared<raytrace::ObjSphere>(raytrace::ObjSphere(
    // std::vector<double>{0.0, -1.0, 0.0}, 2.0
    // )));


    // construct a test light source
    // lightList.push_back(std::make_shared<raytrace::PointLight>(raytrace::PointLight())); // calls default constructor
    // lightList.at(0) -> m_location = qbVector<double> {std::vector<double>{5.0, -10.0, -5.0}};
    // lightList.at(0) -> m_color = qbVector<double> {std::vector<double>{255.0, 255.0, 255.0}};
    // std::cout << objectList.data() << std::endl;
    // std::cout << lightList.data() << std::endl;

    auto lastTime = std::chrono::high_resolution_clock::now(); // initialize timestamp tracker for fps calculations
    // window loop
    StrOut("Starting Program Loop...", msgType[0]);
    while (running) {

        auto currentTime = std::chrono::high_resolution_clock::now(); // get first timestamp at start of loop
        std::chrono::duration<float> elapsed = currentTime - lastTime;
        float deltaTime = elapsed.count();
        lastTime = currentTime;

        std::cout << "frame rate: " << (1 / deltaTime) << "\n";

        // poll all events
        GetKeyPress(event, running, cam,
            RESOLUTION_HEIGHT, RESOLUTION_WIDTH, pixelBuffer);
        if (!running) {
            break;
        }


        // start multithreaded rendering
        CreateGeodesicThreads(pixelBuffer, NUMBER_CORES, cam,
            RESOLUTION_HEIGHT, RESOLUTION_WIDTH,
            xFactor, yFactor);


        // // spin the light in a circle
        // qbVector<double> oldLightPosition = lightList.at(0) -> m_location;
        // double radius = lightList.at(0) -> m_location.GetElement(2);
        //
        // double lightX = radius * std::cos(THETA);
        // double lightY = radius * std::sin(THETA);
        //
        // lightList.at(0) -> m_location = oldLightPosition + qbVector<double>{std::vector<double>{lightX, lightY, 0.0}}; // add
        // THETA += 0.5;


        // update render texture (pixel buffer)
        SDL_UpdateTexture(
            pixelBufferTexture,
            nullptr,                   // NULL updates the entire texture
            pixelBuffer.data(),            // Pointer to our raw CPU buffer
            RESOLUTION_WIDTH * sizeof(uint32_t)
        );

        // render loop
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, pixelBufferTexture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        //SDL_Delay(25);

        frame += 1;
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
