/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify alias for @ref fgm::Matrix3D returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FGM_Mat3x3_Alias
 * @{
 */

/** @brief Verify that fgm::Mat3[] are alias wrappers for integral and floating-point 3D matrix. */
namespace
{
    /** Verify @ref fgm::Mat3B has `int8_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat3B::value_type, int8_t> && "Mat3B must contain int8_t elements");
    static_assert(std::is_same_v<fgm::Mat3B, fgm::Matrix3<int8_t>> && "Mat3B must be an alias of Matrix3D<int8_t>");


    /** Verify @ref fgm::Mat3UB has `int8_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat3UB::value_type, uint8_t> && "Mat3UB must contain uint8_t elements");
    static_assert(std::is_same_v<fgm::Mat3UB, fgm::Matrix3<uint8_t>> &&
                  "Mat3UB must be an alias of Matrix3D<uint8_t>");


    /** Verify @ref fgm::Mat3I has `int32_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat3I::value_type, int32_t> && "Mat3I must contain int32_t elements");
    static_assert(std::is_same_v<fgm::Mat3I, fgm::Matrix3<int32_t>> && "Mat3I must be an alias of Matrix3D<int32_t>");


    /** Verify @ref fgm::Mat3U has `uint32_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat3U::value_type, uint32_t> && "Mat3U must contain uint32_t elements");
    static_assert(std::is_same_v<fgm::Mat3U, fgm::Matrix3<uint32_t>> &&
                  "Mat3U must be an alias of Matrix3D<uint32_t>");


    /** Verify @ref fgm::Mat3F has `float` value_type. */
    static_assert(std::is_same_v<fgm::Mat3F::value_type, float> &&
                  "Mat3F must contain single precision floating point elements");
    static_assert(std::is_same_v<fgm::Mat3F, fgm::Matrix3<float>> && "Mat3F must be an alias of Matrix3D<float>");


    /** Verify @ref fgm::Mat3LL has `int64_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat3LL::value_type, int64_t> && "Mat3LL must contain int64_t elements");
    static_assert(std::is_same_v<fgm::Mat3LL, fgm::Matrix3<int64_t>> &&
                  "Mat3LL must be an alias of Matrix3D<int64_t>");


    /** Verify @ref fgm::Mat3D has `double` value_type. */
    static_assert(std::is_same_v<fgm::Mat3D::value_type, double> &&
                  "Mat3D must contain double precision floating point elements");
    static_assert(std::is_same_v<fgm::Mat3D, fgm::Matrix3<double>> && "Mat3D must be an alias of Matrix3D<double>");


    /** Verify @ref fgm::Mat3ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat3ULL::value_type, uint64_t> && "Mat3ULL must contain uint64_t elements");
    static_assert(std::is_same_v<fgm::Mat3ULL, fgm::Matrix3<uint64_t>> &&
                  "Mat3ULL must be an alias of Matrix3D<uint64_t>");

} // namespace

/** @} */
