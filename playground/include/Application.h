#pragma once
/**
 * @file Application.h
 * @author Alan Abraham P Kochumon
 * @date Created on: June 13, 2026
 *
 * @brief Manages the entire application core and running loop.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <SDL3/SDL.h>
#include <string>

namespace demo
{
    class Application
    {
        // FIXME: Remove maybe_unused
        [[maybe_unused]] SDL_Window* _window{ nullptr };
        [[maybe_unused]] bool _isRunning{ false };

    public:
        Application(const std::string& appname, const std::string& version, const std::string& identifier)
        {
            SDL_SetAppMetadata(appname.c_str(), version.c_str(), identifier.c_str());

            if (!SDL_Init(SDL_INIT_VIDEO))
            {
                SDL_Log("There was an error initializing SDL application!");
                return;
            }

            // TODO: Make window resizeable
            _window = SDL_CreateWindow(appname.c_str(), 1280, 720, 0);
        }


        void pollEvent()
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_EVENT_QUIT:
                        _isRunning = false;
                        break;
                    default:
                        SDL_Log("[EVENT]: Unhandled"); // TODO: Remove
                }
            }
        }

        void run()
        {
            _isRunning = true;
            while (_isRunning)
            {
                pollEvent();
            }
        }
    };
} // namespace demo
