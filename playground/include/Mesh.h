#pragma once
/**
 * @file Mesh.h
 * @author Alan Abraham P Kochumon
 * @date Created on: June 16, 2026
 *
 * @brief Defines a mesh object with vertices, indices, uv coordinates etc.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <fgm/Vec>
#include <vector>


namespace demo
{
    class Mesh
    {
    public:
        std::vector<fgm::Vec3F> vertices{};
        // std::vector<fgm::Vector3D<int>> colors{};
        std::vector<fgm::Vec3I> indices{};
        std::vector<fgm::Vec3<uint8_t>> colors{};
        float minVertexValue{ fgm::constants::INFINITY_F }, maxVertexValue{ -fgm::constants::INFINITY_F };
    };
} // namespace demo
