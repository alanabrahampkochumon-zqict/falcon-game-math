/**
 * @file HeaderAliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: June 19, 2026
 * @brief Verify Header Alias point to correct structs and functions.
 * @copyright Copyright(c) 2026 Alan Abraham P Kochumon
 */


#include <fgm/vec>
#include <type_traits>


/**
 * @addtogroup T_FGM_Header_Alias
 * @{
 */

namespace
{
    /**
     * @brief Verify that Vec header alias is the full vector class
     */
    static_assert(std::is_same_v<fgm::Vec2<int>, fgm::Vector2D<int>>);
    static_assert(std::is_same_v<fgm::Vec2<float>, fgm::Vector2D<float>>);


    static_assert(std::is_same_v<fgm::Vec3<int>, fgm::Vector3D<int>>);
    static_assert(std::is_same_v<fgm::Vec3<float>, fgm::Vector3D<float>>);

    static_assert(std::is_same_v<fgm::Vec4<int>, fgm::Vector4D<int>>);
    static_assert(std::is_same_v<fgm::Vec4<float>, fgm::Vector4D<float>>);

}


/** @} */

