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


constexpr std::array vertices = {fgm::vec2{10.0f, 2.0f}, fgm::vec2{20.0f, 28.0f}, fgm::vec2{3.0f, 21.0f}};


static void putPixel(SDL_Surface *surface, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    // Packed the colors into a single value
    // uint32_t packedColor = SDL_MapRGBA(surface->format, nullptr, r, g, b, a);
    // SDL_Palette* palette = SDL_GetSurfacePalette(surface);
    uint32_t packedColor = SDL_MapSurfaceRGB(surface, r, g, b);
    auto bytesPerPixel = SDL_BYTESPERPIXEL(surface->format);

    // Cast row pointer to pixels to uint8_t
    auto *pixelAddress = static_cast<uint8_t *>(surface->pixels)
                               + (y * surface->pitch)
                               + (x * bytesPerPixel);

    switch (bytesPerPixel) {
        case 1:
            *pixelAddress = static_cast<uint8_t>(packedColor);
            break;
        case 2:
            *reinterpret_cast<uint16_t*>(pixelAddress) = static_cast<uint16_t>(packedColor);
            break;
        case 3:
            // 24-bit surfaces store RGB separately depending on system byte order
            #if SDL_BYTEORDER == SDL_BIG_ENDIAN
                pixelAddress[0] = (packedColor >> 16) & 0xFF;
                pixelAddress[1] = (packedColor >> 8) & 0xFF;
                pixelAddress[2] = packedColor & 0xFF;
            #else
                pixelAddress[0] = packedColor & 0xFF;
                pixelAddress[1] = (packedColor >> 8) & 0xFF;
                pixelAddress[2] = (packedColor >> 16) & 0xFF;
            #endif
            break;
        case 4:
            *reinterpret_cast<uint32_t*>(pixelAddress) = packedColor;
            break;
    }
}

int main() {
    // Setup the metadata for identifying the application
    SDL_SetAppMetadata("DEMO: FGM Software Rasterizer", "1.0.0", "com.fgm.demo.rasterizer");


    // Initialize the required SDL subsystems
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Create the SDL Windows
    // SDL_Window* window = SDL_CreateWindow("Engine", 800, 600, 0);
    SDL_Window *window = SDL_CreateWindow("DEMO: FGM Software Rasterizer", 128, 128, 0);

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    if (!surface) {
        SDL_Log("Couldn't initialize a SDL surface: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    bool runningState = true;

    while (runningState) {
        // Calculate the bounding box of the triangle
        // (minX, minY)--------
        //      |____________|
        //      |\ \ \ \ \ \/|
        //      | \ \ \ \ \/ |
        //      |  \ \ \ \/  |
        //      |   \ \ \/   |
        //      |    \ \/    |
        //      |     \/     |
        //      --------(maxX, maxY)
        auto minX = static_cast<int>(std::min(vertices[0].x(), std::min(vertices[1].x(), vertices[2].x())));
        auto minY = static_cast<int>(std::min(vertices[0].y(), std::min(vertices[1].y(), vertices[2].y())));
        auto maxX = static_cast<int>(std::max(vertices[0].x(), std::max(vertices[1].x(), vertices[2].x())));
        auto maxY = static_cast<int>(std::max(vertices[0].y(), std::max(vertices[1].y(), vertices[2].y())));

        SDL_Log("(minX, minY): (%d, %d)\n(maxX, maxY): (%d, %d)", minX, minY, maxX, maxY);
        for (int i = 0; i < surface->w; ++i) {
            for (int j = 0; j < surface->h; ++j) {
                putPixel(surface, i, j, 0xF0, 0x0F, 0xFF);
            }
        }
        // for (int i = minX; i < maxX; ++i) {
        //     for (int j = minY; j < maxY; ++j) {
        //         putPixel(surface, i, j, 0xFF, 0xFF, 0xFF);
        //     }
        // }


        pollEvents(runningState);
    }


    // Shutdown all the initialized subsystems
    SDL_Quit();
}
