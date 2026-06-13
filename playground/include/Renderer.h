#pragma once
/**
 * @file Renderer.h
 * @author Alan Abraham P Kochumon
 * @date Created on: June 13, 2026
 *
 * @brief Manages application rendering.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstddef>
#include <cstdint>
#include <vectors/Vector3D.h>
#include <vector>


namespace demo
{
    class Renderer
    {
    public:
        uint8_t* frameBuffer;
        uint8_t* depthBuffer;
        std::size_t width, height, colorChannels;

        // TODO:Change to vector
        std::array<float, 5> vertices;
        fgm::Vector3D<int> indices;

        Renderer(const std::size_t width, const std::size_t height, const std::size_t colorChannels)
            : frameBuffer(new uint8_t[width * height * colorChannels]),
              depthBuffer(new uint8_t[width * height * colorChannels]),
              width(width),
              height(height),
              colorChannels(colorChannels)
        {}

        ~Renderer()
        {
            delete[] frameBuffer;
            delete[] depthBuffer;
        }
    };
} // namespace demo
