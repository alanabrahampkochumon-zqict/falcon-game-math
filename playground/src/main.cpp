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
    //SDL_Window* window = SDL_CreateWindow("Engine", 800, 600, 0);
    SDL_CreateWindow("DEMO: FGM Software Rasterizer", 800, 600, 0);
    

    // Event Queue
    SDL_Event event;

    // Event Loop
    while (true)
    {
        while (SDL_PollEvent(&event))
        {
            
        }
    }

    // Shutdown all the initialized subsystems
    SDL_Quit();
}
