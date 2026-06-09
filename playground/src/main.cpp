/**
 * @file main.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 29, 2026
 *
 * @brief Demo application main entry point.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <SDL3/SDL.h>
#include <vectors/Vector2D.h>
#include <algorithm>
#include <array>
#include <iostream>

static SDL_AppResult pollEvents(bool &runningState) {
    // Event Queue
    SDL_Event event;

    // Event Loop
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_MOUSE_MOTION:
                // SDL_Log("We got a motion event.");
                // SDL_Log("Current mouse position is: (%f, %f)", event.motion.x, event.motion.y);
                return SDL_APP_SUCCESS;

            case SDL_EVENT_QUIT:
                runningState = false;
                SDL_Log("Exiting application");
                return SDL_APP_SUCCESS;

            default:
                // SDL_Log("Unhandled Event!");
                return SDL_APP_CONTINUE;
        }
    }
    return SDL_APP_CONTINUE;
}


class SoftwareRenderer {
public:
    SoftwareRenderer(SDL_Window *window) : _window(window) {
        _surface = SDL_GetWindowSurface(_window);

        if (!_surface) {
            SDL_Log("Couldn't initialize a SDL surface: %s", SDL_GetError());
        }
    }

    template<typename T>
    void renderTriangle(const fgm::Vector2D<T> &v0, const fgm::Vector2D<T> &v1, const fgm::Vector2D<T> &v2) {
        // Calculate the bounding box of the triangle
        // (minX, minY)--------
        //       |____________|
        //       |\ \ \ \ \ \/|
        //       | \ \ \ \ \/ |
        //       |  \ \ \ \/  |
        //       |   \ \ \/   |
        //       |    \ \/    |
        //       |     \/     |
        //       --------(maxX, maxY)
        const auto minX = static_cast<int>(std::min({v0.x(), v1.x(), v2.x()}));
        const auto minY = static_cast<int>(std::min({v0.y(), v1.y(), v2.y()}));
        const auto maxX = static_cast<int>(std::max({v0.x(), v1.x(), v2.x()}));
        const auto maxY = static_cast<int>(std::max({v0.y(), v1.y(), v2.y()}));

        for (int i = minX; i < maxX; ++i) {
            for (int j = minY; j < maxY; ++j) {
                // putPixel(surface, i, j, 0xF0, 0x0F, 0xFF);
                // TODO: Replace with a faster function since this is slower
                const auto currentPoint = fgm::vec2(i, j);
                if (insideTriangle(v0, v1, v2, currentPoint))
                    SDL_WriteSurfacePixel(_surface, i, j, 0xf0, 0x0f, 0xff, 0xff);
            }
        }
    }


private:
    template<typename T>
    static bool insideTriangle(const fgm::Vector2D<T> &v0, const fgm::Vector2D<T> &v1, const fgm::Vector2D<T> &v2,
                               const fgm::Vector2D<T> &point) {
        // Edges
        const auto e1 = v1 - v0;
        const auto v1p = point - v1;
        const auto e2 = v2 - v1;
        const auto v2p = point - v2;
        const auto e3 = v0 - v2;
        const auto v0p = point - v0;

        // Return true if all point is bounded by all the three edges
        return e1.cross(v1p) >= T(0) && e2.cross(v2p) >= T(0) && e3.cross(v0p) >= T(0);
    }

    // Member variables
    SDL_Window *_window;
    SDL_Surface *_surface;
};

constexpr std::array VERTICES = {fgm::vec2{10.0f, 2.0f}, fgm::vec2{20.0f, 28.0f}, fgm::vec2{3.0f, 21.0f}};

int main() {
    // Set up the metadata for identifying the application
    SDL_SetAppMetadata("DEMO: FGM Software Rasterizer", "1.0.0", "com.fgm.demo.rasterizer");


    // Initialize the required SDL subsystems
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Create the SDL Windows
    // SDL_Window* window = SDL_CreateWindow("Engine", 800, 600, 0);
    SDL_Window *window = SDL_CreateWindow("DEMO: FGM Software Rasterizer", 128, 128, 0);


    // Initialize the state
    SoftwareRenderer renderer(window);

    bool runningState = true;

    while (runningState) {
        renderer.renderTriangle(VERTICES[0], VERTICES[1], VERTICES[2]);

        // for (int i = minX; i < maxX; ++i) {
        //     for (int j = minY; j < maxY; ++j) {
        //         putPixel(surface, i, j, 0xFF, 0xFF, 0xFF);
        //     }
        // }

        // Updates the SDL surface by copying it to the screen
        SDL_UpdateWindowSurface(window);

        pollEvents(runningState);
    }


    // Shutdown all the initialized subsystems
    SDL_Quit();
}
