/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify alias for @ref fgm::Matrix4 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FGM_Mat4x4_Alias
 * @{
 */

/** @brief Verify that fgm::Mat4[] are alias wrappers for integral and floating-point 4D matrix. */
namespace
{
    /** Verify @ref fgm::Mat4B has `int8_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat4B::value_type, int8_t> && "Mat4B must contain int8_t elements");
    static_assert(std::is_same_v<fgm::Mat4B, fgm::Matrix4<int8_t>> && "Mat4B must be an alias of Matrix4<int8_t>");


    /** Verify @ref fgm::Mat4UB has `int8_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat4UB::value_type, uint8_t> && "Mat4UB must contain uint8_t elements");
    static_assert(std::is_same_v<fgm::Mat4UB, fgm::Matrix4<uint8_t>> && "Mat4UB must be an alias of Matrix4<uint8_t>");


    /** Verify @ref fgm::Mat4I has `int32_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat4I::value_type, int32_t> && "Mat4I must contain int32_t elements");
    static_assert(std::is_same_v<fgm::Mat4I, fgm::Matrix4<int32_t>> && "Mat4I must be an alias of Matrix4<int32_t>");


    /** Verify @ref fgm::Mat4U has `uint32_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat4U::value_type, uint32_t> && "Mat4U must contain uint32_t elements");
    static_assert(std::is_same_v<fgm::Mat4U, fgm::Matrix4<uint32_t>> && "Mat4U must be an alias of Matrix4<uint32_t>");


    /** Verify @ref fgm::Mat4F has `float` value_type. */
    static_assert(std::is_same_v<fgm::Mat4F::value_type, float> &&
                  "Mat4F must contain single precision floating point elements");
    static_assert(std::is_same_v<fgm::Mat4F, fgm::Matrix4<float>> && "Mat4F must be an alias of Matrix4<float>");


    /** Verify @ref fgm::Mat4LL has `int64_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat4LL::value_type, int64_t> && "Mat4LL must contain int64_t elements");
    static_assert(std::is_same_v<fgm::Mat4LL, fgm::Matrix4<int64_t>> && "Mat4LL must be an alias of Matrix4<int64_t>");


    /** Verify @ref fgm::Mat4D has `double` value_type. */
    static_assert(std::is_same_v<fgm::Mat4D::value_type, double> &&
                  "Mat4D must contain double precision floating point elements");
    static_assert(std::is_same_v<fgm::Mat4D, fgm::Matrix4<double>> && "Mat4D must be an alias of Matrix4<double>");


    /** Verify @ref fgm::Mat4ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat4ULL::value_type, uint64_t> && "Mat4ULL must contain uint64_t elements");
    static_assert(std::is_same_v<fgm::Mat4ULL, fgm::Matrix4<uint64_t>> &&
                  "Mat4ULL must be an alias of Matrix4<uint64_t>");

} // namespace

/** @} */
