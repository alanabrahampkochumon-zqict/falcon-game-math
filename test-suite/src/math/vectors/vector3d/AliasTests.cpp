/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify alias for @ref fgm::Vector3D returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3DTestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FGM_Vec3_Alias
 * @{
 */

/** @brief Verify that fgm::Vec3[] are alias wrappers for integral and floating-point 3D vector. */
namespace
{
    static_assert(std::is_same_v<fgm::Vec3B::value_type, int8_t> && "Vec3B must contain int8_t elements");
    static_assert(std::is_same_v<fgm::Vec3B, fgm::Vector3D<int8_t>> && "Vec3B must be an alias of Vector3D<int8_t>");


    static_assert(std::is_same_v<fgm::Vec3UB::value_type, uint8_t> && "Vec3UB must contain uint8_t elements");
    static_assert(std::is_same_v<fgm::Vec3UB, fgm::Vector3D<uint8_t>> &&
                  "Vec3UB must be an alias of Vector3D<uint8_t>");


    static_assert(std::is_same_v<fgm::Vec3I::value_type, int32_t> && "Vec3I must contain int32_t elements");
    static_assert(std::is_same_v<fgm::Vec3I, fgm::Vector3D<int32_t>> && "Vec3I must be an alias of Vector3D<int32_t>");


    static_assert(std::is_same_v<fgm::Vec3U::value_type, uint32_t> && "Vec3U must contain uint32_t elements");
    static_assert(std::is_same_v<fgm::Vec3U, fgm::Vector3D<uint32_t>> &&
                  "Vec3U must be an alias of Vector3D<uint32_t>");


    static_assert(std::is_same_v<fgm::Vec3F::value_type, float> &&
                  "Vec3F must contain single precision floating point elements");
    static_assert(std::is_same_v<fgm::Vec3F, fgm::Vector3D<float>> && "Vec3F must be an alias of Vector3D<float>");


    static_assert(std::is_same_v<fgm::Vec3LL::value_type, int64_t> && "Vec3LL must contain int64_t elements");
    static_assert(std::is_same_v<fgm::Vec3LL, fgm::Vector3D<int64_t>> && "Vec3LL must be an alias of Vector3D<int64_t>");


    static_assert(std::is_same_v<fgm::Vec3D::value_type, double> &&
                  "Vec3D must contain double precision floating point elements");
    static_assert(std::is_same_v<fgm::Vec3D, fgm::Vector3D<double>> && "Vec3D must be an alias of Vector3D<double>");


    static_assert(std::is_same_v<fgm::Vec3ULL::value_type, uint64_t> && "Vec3ULL must contain uint64_t elements");
    static_assert(std::is_same_v<fgm::Vec3ULL, fgm::Vector3D<uint64_t>> &&
                  "Vec3ULL must be an alias of Vector3D<uint64_t>");
} // namespace

/** @} */
