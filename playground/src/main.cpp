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
    while (runningState)
    {
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
    SDL_CreateWindow("DEMO: FGM Software Rasterizer", 800, 600, 0);

    bool runningState = true;

    pollEvents(runningState);


    // Shutdown all the initialized subsystems
    SDL_Quit();
}
