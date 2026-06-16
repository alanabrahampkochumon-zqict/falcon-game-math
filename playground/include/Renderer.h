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

#include <cstdint>
#include <cstdio>
#include <utility>
#include <vectors/Vector2D.h>
#include <vectors/Vector3D.h>

namespace demo
{
    template <typename T>
    using Vec3 = fgm::Vector3D<T>;

    template <typename T>
    using Vec2 = fgm::Vector2D<T>;

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


        template <typename T>
        void renderTriangle(const Vec3<T>& v0, const Vec3<T>& v1, const Vec3<T>& v2)
        {
            // Compute the bounding box
            const auto x0 = static_cast<std::size_t>(std::min({ v0.x(), v1.x(), v2.x() }));
            const auto y0 = static_cast<std::size_t>(std::min({ v0.y(), v1.y(), v2.y() }));
            const auto x1 = static_cast<std::size_t>(std::max({ v0.x(), v1.x(), v2.x() }));
            const auto y1 = static_cast<std::size_t>(std::max({ v0.y(), v1.y(), v2.y() }));

            const auto vert2D0 = v0.template swizzle<fgm::axis::X, fgm::axis::Y>();
            const auto vert2D1 = v1.template swizzle<fgm::axis::X, fgm::axis::Y>();
            const auto vert2D2 = v2.template swizzle<fgm::axis::X, fgm::axis::Y>();

            for (auto i = x0; i <= x1; ++i)
            {
                for (auto j = y0; j < y1; ++j)
                {
                    const auto offset =
                        static_cast<size_t>(_colorChannels) * (j * static_cast<std::size_t>(_width) + i);

                    const auto point = fgm::Vector2D<float>(i, j);

                    const bool insideTriangle = edgeCross(vert2D0, vert2D1, point) >= 0.0f &&
                        edgeCross(vert2D1, vert2D2, point) >= 0.0f && edgeCross(vert2D2, vert2D0, point) >= 0.0f;

                    if (insideTriangle)
                    {
                        frameBuffer[offset]     = 0xff;
                        frameBuffer[offset + 1] = 0xff;
                        frameBuffer[offset + 2] = 0xff;
                        frameBuffer[offset + 2] = 0xff;
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
                    renderTriangle(mesh.vertices[i0], mesh.vertices[i1], mesh.vertices[i2]);
                }
            }
            else
            {
                std::printf("[Renderer]: Only triangulated meshes are supported.//WIP//");
            }
        }
    };
} // namespace demo
