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


#include "Mesh.h"
#include "Renderer.h"

#include <SDL3/SDL.h>
#include <string>

namespace demo
{
    class Application
    {
        SDL_Window* _window{ nullptr };
        bool _isRunning{ false };
        int _width = 1280, _height = 720, _colorChannels = 4; // TODO: Update to use ctd.
        Renderer _renderer;


    public:
        Application(const std::string& appname, const std::string& version, const std::string& identifier)
            : _renderer(_width, _height, _colorChannels)
        {
            SDL_SetAppMetadata(appname.c_str(), version.c_str(), identifier.c_str());

            if (!SDL_Init(SDL_INIT_VIDEO))
            {
                SDL_Log("There was an error initializing SDL application!");
                return;
            }

            // TODO: Make window resizeable
            _window = SDL_CreateWindow(appname.c_str(), _width, _height, 0);
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
            Mesh mesh;
            mesh.vertices = { fgm::vec3{ 10.0f, 2.0f, 1.0f }, fgm::vec3{ 240.0f, 300.0f, 1.0f },
                              fgm::vec3{ 10.0f, 580.0f, 1.0f }, fgm::vec3{ 700.0f, 550.0f, 1.0f } };
            mesh.indices  = { 0, 1, 2, 1, 3, 2 };

            _isRunning = true;

            SDL_Surface* renderingSurface = SDL_GetWindowSurface(_window);
            while (_isRunning)
            {
                _renderer.clearScreen();
                _renderer.render(mesh);

                SDL_Surface* imageSurface =
                    SDL_CreateSurfaceFrom(_width, _height, renderingSurface->format, _renderer.frameBuffer,
                                          _renderer._width * _renderer._colorChannels);
                SDL_BlitSurface(imageSurface, nullptr, renderingSurface, nullptr);
                SDL_UpdateWindowSurface(_window);
                pollEvent();
            }
        }
    };
} // namespace demo
