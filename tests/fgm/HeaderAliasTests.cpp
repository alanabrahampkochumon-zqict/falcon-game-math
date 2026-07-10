/**
 * @file HeaderAliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: June 19, 2026
 *
 * @brief Verify Header Alias point to correct structs and functions.
 *
 * @copyright Copyright(c) 2026 Alan Abraham P Kochumon
 */


#include <fgm/Mat>
#include <fgm/Vec>
#include <type_traits>

/**
 * @addtogroup T_FGM_Header_Alias
 * @{
 */

namespace
{
    /**
     * @brief Verify that Vec header alias is the full vector struct.
     */
    static_assert(std::is_same_v<fgm::Vec2<int>, fgm::Vector2<int>>);
    static_assert(std::is_same_v<fgm::Vec2<float>, fgm::Vector2<float>>);


    static_assert(std::is_same_v<fgm::Vec3<int>, fgm::Vector3<int>>);
    static_assert(std::is_same_v<fgm::Vec3<float>, fgm::Vector3<float>>);

    static_assert(std::is_same_v<fgm::Vec4<int>, fgm::Vector4<int>>);
    static_assert(std::is_same_v<fgm::Vec4<float>, fgm::Vector4<float>>);


    /**
     * @brief Verify that Mat header alias is the full matrix struct.
     */
    static_assert(std::is_same_v<fgm::Mat2<int>, fgm::Matrix2<int>>);
    static_assert(std::is_same_v<fgm::Mat2<float>, fgm::Matrix2<float>>);


    static_assert(std::is_same_v<fgm::Mat3<int>, fgm::Matrix3<int>>);
    static_assert(std::is_same_v<fgm::Mat3<float>, fgm::Matrix3<float>>);

    static_assert(std::is_same_v<fgm::Mat4<int>, fgm::Matrix4<int>>);
    static_assert(std::is_same_v<fgm::Mat4<float>, fgm::Matrix4<float>>);

} // namespace


/** @} */
