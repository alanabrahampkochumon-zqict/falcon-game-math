/**
 * @file main.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 29, 2026
 *
 * @brief Demo application main entry point.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Application.h"

#include <SDL3/SDL.h>
#include <algorithm>
#include <array>
#include <bit>
#include <vectors/Vector2D.h>

static SDL_AppResult pollEvents(bool& runningState)
{
    // Event Queue
    SDL_Event event;

    // Event Loop
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
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


// class Triangle
// {
//     Triangle(const std::size_t index0, const std::size_t index1, const std::size_t index2): indices{ index0, index1,
//     index2 }
//     {
//         calculateArea();
//     }
//
//     void calculateArea()
//     {
//         // Private
//         // Calculate area and cache it for future use
//     }
//
//     // std::array<std::size_t, 3> indices;
//     // std::size_t _area;
// };


class SoftwareRenderer
{
public:
    SoftwareRenderer(SDL_Window* window): _window(window)
    {
        _surface = SDL_GetWindowSurface(_window);

        if (!_surface)
        {
            SDL_Log("Couldn't initialize a SDL surface: %s", SDL_GetError());
        }

        _bufferSize = static_cast<std::size_t>(_surface->w * _surface->h * _colorChannels);
        _buffer     = new uint8_t[_bufferSize];
        memset(_buffer, 0, _bufferSize);
    }

    template <typename T>
    void renderTriangle(const fgm::Vector2D<T>& v0, const fgm::Vector2D<T>& v1, const fgm::Vector2D<T>& v2,
                        const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
    {
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
        const auto minX = static_cast<int>(std::min({ v0.x(), v1.x(), v2.x() }));
        const auto minY = static_cast<int>(std::min({ v0.y(), v1.y(), v2.y() }));
        const auto maxX = static_cast<int>(std::max({ v0.x(), v1.x(), v2.x() }));
        const auto maxY = static_cast<int>(std::max({ v0.y(), v1.y(), v2.y() }));




        for (int i = minX; i < maxX; ++i)
        {
            for (int j = minY; j < maxY; ++j)
            {
                // putPixel(surface, i, j, 0xF0, 0x0F, 0xFF);
                // TODO: Replace with a faster function since this is slower
                const auto currentPoint = fgm::vec2(static_cast<T>(i), static_cast<T>(j));
                if (insideTriangle(v0, v1, v2, currentPoint))
                {
                    // SDL_WriteSurfacePixel(_surface, i, j, r, g, b, a); // NOTE: Left out for benchmarking
                    const auto bufferOffset = _colorChannels * (j * _surface->w + i); // 4 -> r, g, b, a
                    if constexpr (std::endian::native == std::endian::little)
                    {
                        _buffer[bufferOffset + 0] = b;
                        _buffer[bufferOffset + 1] = g;
                        _buffer[bufferOffset + 2] = r;
                        _buffer[bufferOffset + 3] = a;
                    }
                    else if constexpr (std::endian::native == std::endian::big)
                    {
                        _buffer[bufferOffset + 0] = r;
                        _buffer[bufferOffset + 1] = g;
                        _buffer[bufferOffset + 2] = b;
                        _buffer[bufferOffset + 3] = a;
                    }
                }
            }
        }


        // TODO: Separate out
        SDL_Surface* srcSurface =
            SDL_CreateSurfaceFrom(_surface->w, _surface->h, _surface->format, _buffer, _surface->w * _colorChannels);
        // SDL_ClearSurface(_surface, 0x00, 0x00, 0x00, 0x00);
        SDL_BlitSurface(srcSurface, nullptr, _surface, nullptr);
    }

    void renderLine(int ax, int ay, int bx, int by, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        for (float t = 0.0f; t <= 1.0f; t += 0.002f)
        {
            auto x            = static_cast<int>(std::round(ax + t * (bx - ax)));
            auto y            = static_cast<int>(std::round(ay + t * (by - ay)));
            auto bufferOffset = _colorChannels * (_surface->w * y + x);
            if constexpr (std::endian::native == std::endian::little)
            {
                _buffer[bufferOffset + 0] = b;
                _buffer[bufferOffset + 1] = g;
                _buffer[bufferOffset + 2] = r;
                _buffer[bufferOffset + 3] = a;
            }
            else if constexpr (std::endian::native == std::endian::big)
            {
                _buffer[bufferOffset + 0] = r;
                _buffer[bufferOffset + 1] = g;
                _buffer[bufferOffset + 2] = b;
                _buffer[bufferOffset + 3] = a;
            }
        }


        // TODO: Separate out
        SDL_Surface* srcSurface =
            SDL_CreateSurfaceFrom(_surface->w, _surface->h, _surface->format, _buffer, _surface->w * _colorChannels);
        // SDL_ClearSurface(_surface, 0x00, 0x00, 0x00, 0x00);
        SDL_BlitSurface(srcSurface, nullptr, _surface, nullptr);
    }

    void clearBuffer() { memset(_buffer, 0, _bufferSize); }


private:
    template <typename T>
    static bool isTopLeft(const fgm::Vector2D<T>& v0, const fgm::Vector2D<T>& v1)
    {
        // Since we are using clockwise winding order, we need to subtract v1 from v0 to get
        // the corresponding edge
        const auto edge = v1 - v0;
        // y > 0 -> Left edge
        // y == 0 -> flat line
        // x > 0 -> top edge(not bottom)
        // TODO: Adjust code for fp numbers
        return edge.y() > T(0) || (edge.y() == 0 && edge.x() > T(0));
    }

    template <typename T>
    static bool insideTriangle(const fgm::Vector2D<T>& v0, const fgm::Vector2D<T>& v1, const fgm::Vector2D<T>& v2,
                               const fgm::Vector2D<T>& point)
    {
        // Edges
        const auto e1  = v1 - v0;
        const auto v1p = point - v1;
        const auto e2  = v2 - v1;
        const auto v2p = point - v2;
        const auto e3  = v0 - v2;
        const auto v0p = point - v0;

        // TODO: Separate out the function to duplicate calculation
        const auto isTopLeftE1 = isTopLeft(v0, v1);
        const auto isTopLeftE2 = isTopLeft(v1, v2);
        const auto isTopLeftE3 = isTopLeft(v2, v0);

        // Return true if all point is bounded by all the three edges
        return e1.cross(v1p) - static_cast<int>(isTopLeftE1) >= T(0) &&
            e2.cross(v2p) - static_cast<int>(isTopLeftE2) >= T(0) &&
            e3.cross(v0p) - static_cast<int>(isTopLeftE3) >= T(0);
    }

    // Member variables
    SDL_Window* _window;
    SDL_Surface* _surface;
    uint8_t* _buffer;
    std::size_t _bufferSize;
    constexpr static int _colorChannels = 4;
};

// Note: Vertices are in screen space
// 0 to width, 0 to height
constexpr std::array VERTICES = { fgm::vec2{ 10.0f, 2.0f }, fgm::vec2{ 240.0f, 300.0f }, fgm::vec2{ 10.0f, 580.0f },
                                  fgm::vec2{ 700.0f, 550.0f } };

int main()
{
    demo::Application application("FGM Software Rasterizer", "1.0.0", "com.fgm.rasterizer");
    application.run();

    // Set up the metadata for identifying the application
    SDL_SetAppMetadata("DEMO: FGM Software Rasterizer", "1.0.0", "com.fgm.demo.rasterizer");


    // Initialize the required SDL subsystems
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Create the SDL Window
    SDL_Window* window = SDL_CreateWindow("DEMO: FGM Software Rasterizer", 800, 600, SDL_WINDOW_RESIZABLE);


    // Initialize the state
    SoftwareRenderer renderer(window);

    // FIXME: Update to true to see the running application
    bool runningState = false;

    while (runningState)
    {
        renderer.clearBuffer();
        renderer.renderTriangle(VERTICES[0], VERTICES[1], VERTICES[2], 0xbc, 0x10, 0x20, 0xff);
        renderer.renderTriangle(VERTICES[1], VERTICES[3], VERTICES[2], 0x12, 0xcc, 0x20, 0xff);
        renderer.renderLine(300, 200, 500, 500, 0x12, 0xcc, 0x20, 0xff);
        renderer.renderLine(300, 200, 500, 200, 0xf3, 0xcc, 0x20, 0xff);
        renderer.renderLine(500, 100, 500, 500, 0x33, 0x3c, 0xf0, 0xff);

        // Updates the SDL surface by copying it to the screen
        SDL_UpdateWindowSurface(window);

        pollEvents(runningState);
    }


    // Shutdown all the initialized subsystems
    SDL_Quit();
}
