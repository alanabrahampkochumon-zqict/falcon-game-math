/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify alias for @ref fgm::Vector4D returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FGM_Vec4_Alias
 * @{
 */

/** @brief Verify that fgm::Vec4[] are alias wrappers for integral and floating-point 4D vector. */
namespace
{
    /** Verify @ref fgm::Vec4B has `int8_t` value_type. */
    static_assert(std::is_same_v<fgm::Vec4B::value_type, int8_t> && "Vec4B must contain int8_t elements");
    static_assert(std::is_same_v<fgm::Vec4B, fgm::Vector4D<int8_t>> && "Vec4B must be an alias of Vector4D<int8_t>");


    /** Verify @ref fgm::Vec4UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<fgm::Vec4UB::value_type, uint8_t> && "Vec4UB must contain uint8_t elements");
    static_assert(std::is_same_v<fgm::Vec4UB, fgm::Vector4D<uint8_t>> &&
                  "Vec4UB must be an alias of Vector4D<uint8_t>");


    /** Verify @ref fgm::Vec4I has `int32_t` value_type. */
    static_assert(std::is_same_v<fgm::Vec4I::value_type, int32_t> && "Vec4I must contain int32_t elements");
    static_assert(std::is_same_v<fgm::Vec4I, fgm::Vector4D<int32_t>> && "Vec4I must be an alias of Vector4D<int32_t>");


    /** Verify @ref fgm::Vec4U has `uint32_t` value_type. */
    static_assert(std::is_same_v<fgm::Vec4U::value_type, uint32_t> && "Vec4U must contain uint32_t elements");
    static_assert(std::is_same_v<fgm::Vec4U, fgm::Vector4D<uint32_t>> &&
                  "Vec4U must be an alias of Vector4D<uint32_t>");


    /** Verify @ref fgm::Vec4F has `float` value_type. */
    static_assert(std::is_same_v<fgm::Vec4F::value_type, float> &&
                  "Vec4F must contain single precision floating point elements");
    static_assert(std::is_same_v<fgm::Vec4F, fgm::Vector4D<float>> && "Vec4F must be an alias of Vector4D<float>");


    /** Verify @ref fgm::Vec4LL has `int64t` value_type. */
    static_assert(std::is_same_v<fgm::Vec4LL::value_type, int64_t> && "Vec4LL must contain int64_t elements");
    static_assert(std::is_same_v<fgm::Vec4LL, fgm::Vector4D<int64_t>> &&
                  "Vec4LL must be an alias of Vector4D<int64_t>");


    /** Verify @ref fgm::Vec4D has `double` value_type. */
    static_assert(std::is_same_v<fgm::Vec4D::value_type, double> &&
                  "Vec4D must contain double precision floating point elements");
    static_assert(std::is_same_v<fgm::Vec4D, fgm::Vector4D<double>> && "Vec4D must be an alias of Vector4D<double>");


    /** Verify @ref fgm::Vec4ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<fgm::Vec4ULL::value_type, uint64_t> && "Vec4ULL must contain uint64_t elements");
    static_assert(std::is_same_v<fgm::Vec4ULL, fgm::Vector4D<uint64_t>> &&
                  "Vec4ULL must be an alias of Vector4D<uint64_t>");
} // namespace

/** @} */
