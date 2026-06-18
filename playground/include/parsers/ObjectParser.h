#pragma once
/**
 * @file ObjectParser.h
 * @author Alan Abraham P Kochumon
 * @date Created on: June 16, 2026
 *
 * @brief Parser for Obj/Wavefront files.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Mesh.h"

#include <charconv>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>

#include <fast_float/fast_float.h>


namespace demo
{
    class ObjectParser
    {
    public:
        /**
         * @brief Parse a .obj file into a @ref demo::Mesh object.
         * @param filename The name of the file to parse.
         * @return A mesh object.
         */
        Mesh parse(const std::string& filename)
        {

            Mesh mesh;
            std::ifstream modelStream(filename);


            if (!modelStream.is_open())
            {
                std::printf("Error opening file! Returning a default mesh.");
            }

            // TODO: Start with object parsing
            std::string line;
            while (std::getline(modelStream, line))
            {
                if (line.starts_with("vt"))
                {
                    // TODO: Texture coordinates
                }
                else if (line.starts_with("vn"))
                {
                    // TODO: Vertex normals
                }
                else if (line.starts_with("v"))
                {
                    // Vertex
                    auto vertexIterator = std::views::split(line, ' ') | std::views::drop(1);
                    Vec3<float> vertexData;
                    std::size_t index = 0;
                    for (const auto token : vertexIterator)
                    {
                        float vertex;
                        const auto [ptr, ec] = fast_float::from_chars(token.data(), token.data() + token.size(), vertex);
                        if (ec != std::errc())
                        {
                            printf("There was an error while parsing the vertex data.");
                        }
                        vertexData[index++] = vertex;
                    }
                    mesh.vertices.push_back(vertexData);
                }
                else if (line.starts_with("f"))
                {
                    // Faces
                    // Vertex/Texture/Normal
                    // printf("Faces %s\n", line.c_str());
                    // Only takes the face index for now
                    auto d1 =
                        line | std::views::split(' ') | std::views::transform([](auto&& packedIndex) {
                            return std::string_view(packedIndex.begin(), packedIndex.end()) | std::views::split('/');
                        });

                    // auto data = line | std::views::split(' ') | std::views::transform([](auto&& subrange) {
                    //                 return std::string(subrange.begin(), subrange.end()) | std::views::split('/') |
                    //                     std::views::take(1) | std::views::transform([](auto&& sub) {
                    //                            return std::string(sub.begin(), sub.end());
                    //                        });
                    //             });
                    for (auto d : d1)
                    {
                        std::cout << "Index: ";
                        for (auto c : d)
                        {
                            std::cout << std::string(c.begin(), c.end());
                        }
                        std::cout << '\n';
                    }
                    // for (const auto d : data)
                    // {
                    //
                    // }
                    // auto vertexIterator = std::views::split(line, ' ') | std::views::drop(1);
                    // vertexIterator.size();
                    // for (auto vertexIndex:)
                    // auto faceIterator = std::views::split(vertexIterator.data(), '\\');
                }
            }

            // TODO: Remove
            mesh.vertices = { fgm::vec3{ 10.0f, 2.0f, 1.0f }, fgm::vec3{ 240.0f, 300.0f, 1.0f },
                              fgm::vec3{ 10.0f, 580.0f, 1.0f }, fgm::vec3{ 700.0f, 550.0f, 1.0f } };
            mesh.indices  = { 0, 1, 2, 1, 3, 2 };

            return mesh;
        }
    };

} // namespace demo
