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
#include "parsers/ObjectParser.h"

#include <SDL3/SDL.h>
#include <chrono>
#include <filesystem>
#include <string>
#include <thread>

namespace demo
{
    class Application
    {
        SDL_Window* _window{ nullptr };
        bool _isRunning{ false };
        int _width{ 1280 }, _height{ 720 }, _colorChannels{ 4 }; // TODO: Update to use ctd.
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
            auto modelPath = std::filesystem::path("models") / "utah_teapot.obj";
            // auto modelPath = std::filesystem::path("models") / "suzanne.obj";
            // auto modelPath = std::filesystem::path("models") / "Cube.obj";
            ObjectParser parser;
            auto mesh = parser.parse(modelPath.string());

            _isRunning = true;

            // const auto bufferSize = static_cast<std::size_t>(_width * _height * 4);
            // uint8_t* buffer = new uint8_t[bufferSize];

            SDL_Surface* renderingSurface = SDL_GetWindowSurface(_window);
            while (_isRunning)
            {
                _renderer.clearScreen();
                _renderer.render(mesh);

                SDL_Surface* imageSurface =
                    SDL_CreateSurfaceFrom(_width, _height, renderingSurface->format, _renderer.frameBuffer,
                                          _renderer.width * _renderer.colorChannels);

                // TODO: Remove test buffercode for depth buffer
                // for (std::size_t i = 0; i < bufferSize; i+= 4)
                // {
                //     const auto depth = _renderer.depthBuffer[i/4];
                //
                //     if constexpr (std::endian::native == std::endian::big)
                //     {
                //         // RGBA
                //         buffer[i] = depth;
                //         buffer[i + 1] = depth;
                //         buffer[i + 2] = depth;
                //         buffer[i + 2] = 255u;
                //     }
                //     else if constexpr (std::endian::native == std::endian::little)
                //     {
                //         // BRGA
                //         buffer[i] = depth;
                //         buffer[i + 1] = depth;
                //         buffer[i + 2] = depth;
                //         buffer[i + 2] = 0xff;
                //     }
                // }
                //
                // SDL_Surface* imageSurface =
                //     SDL_CreateSurfaceFrom(_width, _height, renderingSurface->format, buffer,
                //                           _renderer.width * _renderer.colorChannels);
                SDL_BlitSurface(imageSurface, nullptr, renderingSurface, nullptr);
                SDL_UpdateWindowSurface(_window);
                pollEvent();
            }
        }
    };
} // namespace demo
