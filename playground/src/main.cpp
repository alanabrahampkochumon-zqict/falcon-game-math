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


void pollEvents(bool& runningState)
{
    // Event Queue
    SDL_Event event;

    // Event Loop
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_MOUSE_MOTION:
                SDL_Log("We got a motion event.");
                SDL_Log("Current mouse position is: (%f, %f)", event.motion.x, event.motion.y);
                break;
            case SDL_EVENT_QUIT:
                runningState = false;
                SDL_Log("Exiting application");
                break;
            default:
                SDL_Log("Unhandled Event!");
                break;
        }
    }
}

constexpr fgm::vec2 verts[] = { { 10, 2 }, { 20, 28 }, { 3, 21 } };


void putPixel(SDL_Surface* surface, std::size_t x, std::size_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF)
{
    // Packed the colors into a single value
    uint32_t packedColor = SDL_MapSurfaceRGBA(surface, r, g, b, a);

    // Cast row pointer to pixels to uint8_t
    uint8_t* rowPointer = static_cast<uint8_t*>(surface->pixels);

    // Navigate the columns
    rowPointer += (y * surface->pitch) + (x * 0); // Remove x * 0

    // Move the target color to the memory location
    *reinterpret_cast<uint32_t*>(rowPointer) = packedColor;
}

int main()
{
    // Setup the metadata for identifying the application
    SDL_SetAppMetadata("DEMO: FGM Software Rasterizer", "1.0.0", "com.fgm.demo.rasterizer");


    // Initialize the required SDL subsystems
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Create the SDL Windows
    // SDL_Window* window = SDL_CreateWindow("Engine", 800, 600, 0);
    SDL_Window* window = SDL_CreateWindow("DEMO: FGM Software Rasterizer", 128, 128, 0);

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    if (!surface)
    {
        SDL_Log("Couldn't initialize a SDL surface: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    bool runningState = true;

    while (runningState)
    {
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
        auto minX = static_cast<std::size_t>(std::min(verts[0].x(), std::min(verts[1].x(), verts[2].x())));
        auto minY = static_cast<std::size_t>(std::min(verts[0].y(), std::min(verts[1].y(), verts[2].y())));
        auto maxX = static_cast<std::size_t>(std::max(verts[0].x(), std::max(verts[1].x(), verts[2].x())));
        auto maxY = static_cast<std::size_t>(std::max(verts[0].y(), std::max(verts[1].y(), verts[2].y())));


        for (std::size_t i = minX; i < maxX; ++i)
        {
            for (std::size_t j = minY; j < maxY; ++j)
            {
                putPixel(surface, i, j, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
        


        pollEvents(runningState);
    }


    // Shutdown all the initialized subsystems
    SDL_Quit();
}
