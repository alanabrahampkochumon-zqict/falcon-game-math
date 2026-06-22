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

#include <cstdint>



/**
 * @addtogroup T_FGM_Vec2_Alias
 * @{
 */

/** @brief Verify that fgm::Vec2[] are alias wrappers for integral and floating-point 2D vector. */
namespace
{
    /** Verify @ref fgm::Vec2B has `int8_t` value_type. */
    static_assert(std::is_same_v<fgm::Vec2B::value_type, int8_t> && "Vec2B must contain int8_t elements");
    static_assert(std::is_same_v<fgm::Vec2B, fgm::Vector2D<int8_t>> && "Vec2B must be an alias of Vector2D<int8_t>");


    /** Verify @ref fgm::Vec2UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<fgm::Vec2UB::value_type, uint8_t> && "Vec2UB must contain uint8_t elements");
    static_assert(std::is_same_v<fgm::Vec2UB, fgm::Vector2D<uint8_t>> &&
                  "Vec2UB must be an alias of Vector2D<uint8_t>");


    /** Verify @ref fgm::Vec2I has `int32_t` value_type. */
    static_assert(std::is_same_v<fgm::Vec2I::value_type, int32_t> && "Vec2I must contain int32_t elements");
    static_assert(std::is_same_v<fgm::Vec2I, fgm::Vector2D<int32_t>> && "Vec2I must be an alias of Vector2D<int32_t>");


    /** Verify @ref fgm::Vec2U has `uint32_t` value_type. */
    static_assert(std::is_same_v<fgm::Vec2U::value_type, uint32_t> && "Vec2U must contain uint32_t elements");
    static_assert(std::is_same_v<fgm::Vec2U, fgm::Vector2D<uint32_t>> &&
                  "Vec2U must be an alias of Vector2D<uint32_t>");


    /** Verify @ref fgm::Vec2F has `float` value_type. */
    static_assert(std::is_same_v<fgm::Vec2F::value_type, float> &&
                  "Vec2F must contain single precision floating point elements");
    static_assert(std::is_same_v<fgm::Vec2F, fgm::Vector2D<float>> && "Vec2F must be an alias of Vector2D<float>");


    /** Verify @ref fgm::Vec2LL has `int64t` value_type. */
    static_assert(std::is_same_v<fgm::Vec2LL::value_type, int64_t> && "Vec2LL must contain int64_t elements");
    static_assert(std::is_same_v<fgm::Vec2LL, fgm::Vector2D<int64_t>> && "Vec2LL must be an alias of Vector2D<int64_t>");


    /** Verify @ref fgm::Vec2D has `double` value_type. */
    static_assert(std::is_same_v<fgm::Vec2D::value_type, double> &&
                  "Vec2D must contain double precision floating point elements");
    static_assert(std::is_same_v<fgm::Vec2D, fgm::Vector2D<double>> && "Vec2D must be an alias of Vector2D<double>");


    /** Verify @ref fgm::Vec2ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<fgm::Vec2ULL::value_type, uint64_t> && "Vec2ULL must contain uint64_t elements");
    static_assert(std::is_same_v<fgm::Vec2ULL, fgm::Vector2D<uint64_t>> &&
                  "Vec2ULL must be an alias of Vector2D<uint64_t>");
} // namespace

/** @} */
