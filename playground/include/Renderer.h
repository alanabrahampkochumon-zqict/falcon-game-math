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


#include "Mesh.h"

#include <bit>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vectors/Vector2D.h>
#include <vectors/Vector3D.h>

namespace demo
{
    template <typename T>
    using Vec3 = fgm::Vector3D<T>;

    template <typename T>
    using Vec2 = fgm::Vector2D<T>;

    constexpr auto EPSILON = 1e-5;


    class Renderer
    {
    public:
        uint8_t* frameBuffer;
        uint8_t* depthBuffer;
        int _width, _height, _colorChannels;
        int clearColor = 0x000000;


        Renderer(const int width, const int height, const int colorChannels)
            : frameBuffer(new uint8_t[static_cast<std::size_t>(width * height * colorChannels)]),
              depthBuffer(new uint8_t[static_cast<std::size_t>(width * height * colorChannels)]),
              _width(width),
              _height(height),
              _colorChannels(colorChannels)
        { clearScreen(); }

        void clearScreen() { memset(frameBuffer, clearColor, static_cast<size_t>(_width * _height * _colorChannels)); }

        ~Renderer()
        {
            delete[] frameBuffer;
            delete[] depthBuffer;
        }

        template <typename T>
        T edgeCross(const Vec2<T>& vert0, const Vec2<T>& vert1, const Vec2<T>& point)
        {
            // We are assuming that the edges start from vert0
            const auto edge0 = vert1 - vert0;
            const auto edge1 = point - vert0;
            return edge0.cross(edge1);
        }


        bool isTopLeftEdge(const Vec3<float>& v0, const Vec3<float>& v1)
        {
            const auto edge = v1 - v0;

            // Top Left if edge's x coordinate is positive (negative is bottom edge due to clockwise convention used)
            // and if y coordinate is 0
            const auto isTopEdge = edge.x() >= EPSILON && std::abs(edge.y()) < EPSILON;
            // Left Edge if y coordinate is >=0
            const auto isLeftEdge = edge.y() >= 1e-5;

            return isTopEdge && isLeftEdge;
        }


        template <typename T>
        void renderTriangle(const Vec3<T>& v0, const Vec3<T>& v1, const Vec3<T>& v2, const uint8_t r = 0xff,
                            const uint8_t g = 0xff, const uint8_t b = 0xff, const uint8_t a = 0xff)
        {
            // Compute the bounding box
            const auto x0 = static_cast<std::size_t>(std::min({ v0.x(), v1.x(), v2.x() }));
            const auto y0 = static_cast<std::size_t>(std::min({ v0.y(), v1.y(), v2.y() }));
            const auto x1 = static_cast<std::size_t>(std::max({ v0.x(), v1.x(), v2.x() }));
            const auto y1 = static_cast<std::size_t>(std::max({ v0.y(), v1.y(), v2.y() }));

            const auto vert2D0 = v0.template swizzle<fgm::axis::X, fgm::axis::Y>();
            const auto vert2D1 = v1.template swizzle<fgm::axis::X, fgm::axis::Y>();
            const auto vert2D2 = v2.template swizzle<fgm::axis::X, fgm::axis::Y>();

            const auto isTopLeft0 = isTopLeftEdge(v0, v1);
            const auto isTopLeft1 = isTopLeftEdge(v1, v2);
            const auto isTopLeft2 = isTopLeftEdge(v2, v0);

            for (auto i = x0; i <= x1; ++i)
            {
                for (auto j = y0; j < y1; ++j)
                {
                    const auto offset =
                        static_cast<size_t>(_colorChannels) * (j * static_cast<std::size_t>(_width) + i);

                    const auto point = fgm::Vector2D<float>(i, j);

                    const bool eC0            = edgeCross(vert2D0, vert2D1, point) - (isTopLeft0 * EPSILON) >= EPSILON;
                    const bool eC1            = edgeCross(vert2D1, vert2D2, point) - (isTopLeft1 * EPSILON) >= EPSILON;
                    const bool eC2            = edgeCross(vert2D2, vert2D0, point) - (isTopLeft2 * EPSILON) >= EPSILON;
                    const bool insideTriangle = eC0 && eC1 && eC2;

                    if (insideTriangle)
                    {
                        if constexpr (std::endian::native == std::endian::big)
                        {
                            // RGBA
                            frameBuffer[offset]     = r;
                            frameBuffer[offset + 1] = g;
                            frameBuffer[offset + 2] = b;
                            frameBuffer[offset + 2] = a;
                        }
                        else if constexpr (std::endian::native == std::endian::little)
                        {
                            // BRGA
                            frameBuffer[offset]     = b;
                            frameBuffer[offset + 1] = r;
                            frameBuffer[offset + 2] = g;
                            frameBuffer[offset + 2] = a;
                        }
                        else
                        {
                            printf("Unknown endianness");
                        }
                    }
                }
            }
        }


        void render(const Mesh& mesh)
        {
            if (mesh.indices.size() % 3 == 0)
            {
                for (auto it = mesh.indices.begin(); it != mesh.indices.end(); it += 3)
                {
                    const auto i0 = static_cast<std::size_t>(*it);
                    const auto i1 = static_cast<std::size_t>(*(it + 1));
                    const auto i2 = static_cast<std::size_t>(*(it + 2));
                    // FIXME: Test code
                    const auto r    = static_cast<uint8_t>(std::rand() % 255);
                    const auto g    = static_cast<uint8_t>(std::rand() % 255);
                    const auto b    = static_cast<uint8_t>(std::rand() % 255);
                    const uint8_t a = 255;
                    renderTriangle(mesh.vertices[i0], mesh.vertices[i1], mesh.vertices[i2], r, g, b, a);
                }
            }
            else
            {
                std::printf("[Renderer]: Only triangulated meshes are supported.//WIP//");
            }
        }
    };
} // namespace demo
