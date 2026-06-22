/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify alias for @ref fgm::Matrix2D returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FGM_Mat2x2_Alias
 * @{
 */

/** @brief Verify that fgm::Mat2[] are alias wrappers for integral and floating-point 2D matrix. */
namespace
{
    /** Verify @ref fgm::Mat2B has `int8_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat2B::value_type, int8_t> && "Mat2B must contain int8_t elements");
    static_assert(std::is_same_v<fgm::Mat2B, fgm::Matrix2D<int8_t>> && "Mat2B must be an alias of Matrix2D<int8_t>");


    /** Verify @ref fgm::Mat2UB has `int8_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat2UB::value_type, uint8_t> && "Mat2UB must contain uint8_t elements");
    static_assert(std::is_same_v<fgm::Mat2UB, fgm::Matrix2D<uint8_t>> &&
                  "Mat2UB must be an alias of Matrix2D<uint8_t>");


    /** Verify @ref fgm::Mat2I has `int32_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat2I::value_type, int32_t> && "Mat2I must contain int32_t elements");
    static_assert(std::is_same_v<fgm::Mat2I, fgm::Matrix2D<int32_t>> && "Mat2I must be an alias of Matrix2D<int32_t>");


    /** Verify @ref fgm::Mat2U has `uint32_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat2U::value_type, uint32_t> && "Mat2U must contain uint32_t elements");
    static_assert(std::is_same_v<fgm::Mat2U, fgm::Matrix2D<uint32_t>> &&
                  "Mat2U must be an alias of Matrix2D<uint32_t>");


    /** Verify @ref fgm::Mat2F has `float` value_type. */
    static_assert(std::is_same_v<fgm::Mat2F::value_type, float> &&
                  "Mat2F must contain single precision floating point elements");
    static_assert(std::is_same_v<fgm::Mat2F, fgm::Matrix2D<float>> && "Mat2F must be an alias of Matrix2D<float>");


    /** Verify @ref fgm::Mat2LL has `int64_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat2LL::value_type, int64_t> && "Mat2LL must contain int64_t elements");
    static_assert(std::is_same_v<fgm::Mat2LL, fgm::Matrix2D<int64_t>> &&
                  "Mat2LL must be an alias of Matrix2D<int64_t>");


    /** Verify @ref fgm::Mat2D has `double` value_type. */
    static_assert(std::is_same_v<fgm::Mat2D::value_type, double> &&
                  "Mat2D must contain double precision floating point elements");
    static_assert(std::is_same_v<fgm::Mat2D, fgm::Matrix2D<double>> && "Mat2D must be an alias of Matrix2D<double>");


    /** Verify @ref fgm::Mat2ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<fgm::Mat2ULL::value_type, uint64_t> && "Mat2ULL must contain uint64_t elements");
    static_assert(std::is_same_v<fgm::Mat2ULL, fgm::Matrix2D<uint64_t>> &&
                  "Mat2ULL must be an alias of Matrix2D<uint64_t>");

} // namespace

/** @} */
