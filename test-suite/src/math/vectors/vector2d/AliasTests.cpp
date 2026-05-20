/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify alias for @ref fgm::Vector2D returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"


/**
 * @addtogroup T_FGM_Vec2_Alias
 * @{
 */

/** @brief Verify that fgm::*Vec2 and fgm::vec4 are alias wrappers for integral and floating-point 2D vector. */
namespace
{
    static_assert(std::is_same_v<fgm::bVec2::value_type, bool> && "bVec2 must contain boolean elements");
    static_assert(std::is_same_v<fgm::bVec2, fgm::Vector2D<bool>> && "bVec2 must be an alias of Vector2D<bool>");


    static_assert(std::is_same_v<fgm::iVec2::value_type, int> && "iVec2 must contain int elements");
    static_assert(std::is_same_v<fgm::iVec2, fgm::Vector2D<int>> && "iVec2 must be an alias of Vector2D<int>");


    static_assert(std::is_same_v<fgm::uVec2::value_type, unsigned int> && "uVec2 must contain unsigned int elements");
    static_assert(std::is_same_v<fgm::uVec2, fgm::Vector2D<unsigned int>> &&
                  "uVec2 must be an alias of Vector2D<unsigned int>");


    static_assert(std::is_same_v<fgm::vec2::value_type, float> && "vec2 must contain float elements");
    static_assert(std::is_same_v<fgm::vec2, fgm::Vector2D<float>> && "vec2 must be an alias of Vector2D<float>");


    static_assert(std::is_same_v<fgm::lVec2::value_type, long long> && "lVec2 must contain long long elements");
    static_assert(std::is_same_v<fgm::lVec2, fgm::Vector2D<long long>> &&
                  "lVec2 must be an alias of Vector2D<long long>");


    static_assert(std::is_same_v<fgm::dVec2::value_type, double> && "dVec2 must contain double elements");
    static_assert(std::is_same_v<fgm::dVec2, fgm::Vector2D<double>> && "dVec2 must be an alias of Vector2D<double>");


    static_assert(std::is_same_v<fgm::ulVec2::value_type, unsigned long long> &&
                  "ulVec2 must contain unsigned long long elements");
    static_assert(std::is_same_v<fgm::ulVec2, fgm::Vector2D<unsigned long long>> &&
                  "ulVec2 must be an alias of Vector2D<unsigned long long>");
} // namespace

/** @} */
