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

#include <fstream>
#include <string>


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

            std::string line;
            std::getline(modelStream, line);
            printf("First line %s\n", line.c_str());


            mesh.vertices = { fgm::vec3{ 10.0f, 2.0f, 1.0f }, fgm::vec3{ 240.0f, 300.0f, 1.0f },
                              fgm::vec3{ 10.0f, 580.0f, 1.0f }, fgm::vec3{ 700.0f, 550.0f, 1.0f } };
            mesh.indices  = { 0, 1, 2, 1, 3, 2 };

            return mesh;
        }
    };

} // namespace demo
