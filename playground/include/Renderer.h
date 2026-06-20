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
#include <cstdlib>
#include <cstring>
#include <fgm/Mat>
#include <fgm/Vec>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

namespace demo
{
    template <typename T>
    using Vec3 = fgm::Vector3D<T>;

    template <typename T>
    using Vec2 = fgm::Vector2D<T>;

    constexpr auto EPSILON = 1e-6;


    class Renderer
    {
    public:
        uint8_t* frameBuffer;
        uint8_t* depthBuffer;
        int width, height, colorChannels;
        int clearColor = 0x000000;

        /**
         * @brief Construct a renderer with the given size.
         * @param w The width of the render.
         * @param h The height of the render.
         * @param numColorChannels The number of color channels the renderer support. Eg: 4 -> RGBA
         */
        Renderer(const int w, const int h, const int numColorChannels)
            : frameBuffer(new uint8_t[static_cast<std::size_t>(w * h * numColorChannels)]),
              depthBuffer(new uint8_t[static_cast<std::size_t>(w * h * numColorChannels)]),
              width(w),
              height(h),
              colorChannels(numColorChannels)
        { clearScreen(); }

        void renderLine(float ax, float ay, float bx, float by, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        {
            for (float t = 0.0f; t <= 1.0f; t += 0.002f)
            {
                auto x            = static_cast<int>(std::round(ax + t * (bx - ax)));
                auto y            = static_cast<int>(std::round(ay + t * (by - ay)));
                auto bufferOffset = colorChannels * (width * y + x);
                if constexpr (std::endian::native == std::endian::little)
                {
                    frameBuffer[bufferOffset + 0] = b;
                    frameBuffer[bufferOffset + 1] = g;
                    frameBuffer[bufferOffset + 2] = r;
                    frameBuffer[bufferOffset + 3] = a;
                }
                else if constexpr (std::endian::native == std::endian::big)
                {
                    frameBuffer[bufferOffset + 0] = r;
                    frameBuffer[bufferOffset + 1] = g;
                    frameBuffer[bufferOffset + 2] = b;
                    frameBuffer[bufferOffset + 3] = a;
                }
            }
        }

        template <typename T>
        void renderTriangleWireframe(const Vec2<T>& v0, const Vec2<T>& v1, const Vec2<T>& v2)
        {
            renderLine(v0.x(), v0.y(), v1.x(), v1.y(), 0xff, 0xff, 0xff, 0xff);
            renderLine(v1.x(), v1.y(), v2.x(), v2.y(), 0xff, 0xff, 0xff, 0xff);
            renderLine(v2.x(), v2.y(), v0.x(), v0.y(), 0xff, 0xff, 0xff, 0xff);
        }


        /**
         * @brief Update the renderer's clear color.
         * @note Must call @ref clearScreen to clear the buffer.
         *
         * @warning The endianness of the clear color is not managed and the user must specify the clear color bits
         *          following the endianness of target CPU.
         *
         * @param color The new clear color.
         */
        void setClearColor(const int color) { clearColor = color; }

        /**
         * @brief Clear the FrameBuffer with @ref clearColor.
         */
        void clearScreen() const
        { std::memset(frameBuffer, clearColor, static_cast<size_t>(width * height * colorChannels)); }

        ~Renderer()
        {
            delete[] frameBuffer;
            delete[] depthBuffer;
        }

        /**
         * @brief Compute the edge cross of 2 vertices and a point.
         *
         * @tparam T The numeric type of vertices.
         *
         * @param vert0 The first vertex.
         * @param vert1 The second vertex.
         * @param point The point.
         * @return A positive number if the point is above the edge formed by @p vert0 and @p vert1,
         *         negative number if the poit is below the edge and 0 if the point is on the edge.
         */
        template <typename T>
        T edgeCross(const Vec2<T>& vert0, const Vec2<T>& vert1, const Vec2<T>& point)
        {
            // We are assuming that the edges start from vert0
            const auto edge0 = vert1 - vert0;
            const auto edge1 = point - vert0;
            return edge0.cross(edge1);
        }


        /**
         * @brief Compute if the edge formed by @p v0 and @p v1 is a left or top edge.
         * @param v0 The first vertex of the edge.
         * @param v1 The second vertex of the edge.
         * @return `true` if the edge is a top or left edge else `false`.
         */
        bool isTopLeftEdge(const Vec2<float>& v0, const Vec2<float>& v1)
        {
            const auto edge = v1 - v0;
            // Top Left if edge's x coordinate is positive (negative is bottom edge due to clockwise convention used)
            // and if y coordinate is 0
            const auto isTopEdge = edge.x() >= EPSILON && std::abs(edge.y()) < EPSILON;
            // Left Edge if y coordinate is >=0
            const auto isLeftEdge = edge.y() >= 1e-5;

            return isTopEdge && isLeftEdge;
        }

        // minValue-> Lowest vertex value
        // maxValue -> Highest vertex value
        template <typename T>
        fgm::Vec2<T> toScreenSpace(const fgm::Vec3<T>& vec, float minValue, float maxValue) const
        {
            // TODO: Remove
            const auto factorX = 2;
            const auto factorY = 2;
            return Vec2{ static_cast<T>((vec.x() - minValue) * width / factorX / maxValue),
                         static_cast<T>((vec.y() - minValue) * height / factorY / maxValue) };
        }


        // TODO: Add docs
        template <typename T>
        void renderTriangle(const Vec2<T>& v0, const Vec2<T>& v1, const Vec2<T>& v2, const uint8_t r = 0xff,
                            const uint8_t g = 0xff, const uint8_t b = 0xff, const uint8_t a = 0xff)
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
            const auto x0 = static_cast<std::size_t>(std::min({ v0.x(), v1.x(), v2.x() }));
            const auto y0 = static_cast<std::size_t>(std::min({ v0.y(), v1.y(), v2.y() }));
            const auto x1 = static_cast<std::size_t>(std::max({ v0.x(), v1.x(), v2.x() }));
            const auto y1 = static_cast<std::size_t>(std::max({ v0.y(), v1.y(), v2.y() }));

            // Get the 2D vertices
            const auto vert2D0 = v0.template swizzle<fgm::axis::X, fgm::axis::Y>();
            const auto vert2D1 = v1.template swizzle<fgm::axis::X, fgm::axis::Y>();
            const auto vert2D2 = v2.template swizzle<fgm::axis::X, fgm::axis::Y>();

            // Compute top left for each edge (vertex pair)
            const auto isTopLeft0 = isTopLeftEdge(v0, v1);
            const auto isTopLeft1 = isTopLeftEdge(v1, v2);
            const auto isTopLeft2 = isTopLeftEdge(v2, v0);

            // Looping in reverse order for better cache locality
            for (auto y = y0; y <= y1; ++y)
            {
                for (auto x = x0; x <= x1; ++x)
                {
                    const auto offset =
                        static_cast<std::size_t>(colorChannels) * (y * static_cast<std::size_t>(width) + x);
                    const auto point = fgm::Vector2D(static_cast<float>(x), static_cast<float>(y));


                    const bool eC0 = edgeCross(vert2D0, vert2D1, point) - (isTopLeft0 * EPSILON) >= EPSILON;
                    const bool eC1 = edgeCross(vert2D1, vert2D2, point) - (isTopLeft1 * EPSILON) >= EPSILON;
                    const bool eC2 = edgeCross(vert2D2, vert2D0, point) - (isTopLeft2 * EPSILON) >= EPSILON;

                    if (eC0 && eC1 && eC2)
                    {
                        if constexpr (std::endian::native == std::endian::big)
                        {
                            // RGBA
                            frameBuffer[offset]     = r;
                            frameBuffer[offset + 1] = g;
                            frameBuffer[offset + 2] = b;
                            frameBuffer[offset + 3] = a;
                        }
                        else if constexpr (std::endian::native == std::endian::little)
                        {
                            // BRGA
                            frameBuffer[offset]     = b;
                            frameBuffer[offset + 1] = g;
                            frameBuffer[offset + 2] = r;
                            frameBuffer[offset + 3] = a;
                        }
                    }
                }
            }
        }


        /**
         * @brief Renders a mesh to the current @p frameBuffer.
         *
         * @note Blitting is not performed by the renderer, the user will need to blit the framebuffer
         *       to the target surface.
         *
         * @param mesh The mesh to render.
         */
        void render(const Mesh& mesh)
        {
            std::vector<Vec2<float>> vertices;

            std::transform(mesh.vertices.cbegin(), mesh.vertices.cend(), std::inserter(vertices, vertices.begin()),
                           [this, mesh](const Vec3<float> vertex) {
                               return toScreenSpace(vertex, mesh.minVertexValue, mesh.maxVertexValue);
                           });

            [[maybe_unused]] std::size_t i = 0;
            for (const auto& index : mesh.indices)
            {
                const auto i0 = static_cast<std::size_t>(index.x());
                const auto i1 = static_cast<std::size_t>(index.y());
                const auto i2 = static_cast<std::size_t>(index.z());
                // FIXME: Test code
                const auto faceColor = mesh.colors[i++];
                renderTriangle(vertices[i0], vertices[i1], vertices[i2], faceColor.r(), faceColor.g(), faceColor.b(),
                               0xff);
                // renderTriangleWireframe(vertices[i0], vertices[i1], vertices[i2]);
            }
        }
    };
} // namespace demo
