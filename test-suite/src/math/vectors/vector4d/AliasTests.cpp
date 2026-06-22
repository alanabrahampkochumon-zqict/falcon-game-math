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


/**
 * @addtogroup T_FGM_Vec4_Alias
 * @{
 */

/** @brief Verify that fgm::*Vec3 and fgm::vec3 are alias wrappers for integral and floating-point 3D vector. */
namespace
{
    static_assert(std::is_same_v<fgm::Vec4B::value_type, bool> && "bVec4 must contain boolean elements");
    static_assert(std::is_same_v<fgm::Vec4B, fgm::Vector4D<bool>> && "bVec4 must be an alias of Vector4D<bool>");


    static_assert(std::is_same_v<fgm::Vec4I::value_type, int> && "iVec4 must contain int elements");
    static_assert(std::is_same_v<fgm::Vec4I, fgm::Vector4D<int>> && "iVec4 must be an alias of Vector4D<int>");

    static_assert(std::is_same_v<fgm::Vec4U::value_type, unsigned int> && "uVec4 must contain unsigned int elements");
    static_assert(std::is_same_v<fgm::Vec4U, fgm::Vector4D<unsigned int>> &&
                  "uVec4 must be an alias of Vector4D<unsigned int>");


    static_assert(std::is_same_v<fgm::Vec4F::value_type, float> && "vec4 must contain float elements");
    static_assert(std::is_same_v<fgm::Vec4F, fgm::Vector4D<float>> && "vec4 must be an alias of Vector4D<float>");


    static_assert(std::is_same_v<fgm::Vec4LL::value_type, long long> && "lVec4 must contain long long elements");
    static_assert(std::is_same_v<fgm::Vec4LL, fgm::Vector4D<long long>> &&
                  "lVec4 must be an alias of Vector4D<long long>");


    static_assert(std::is_same_v<fgm::Vec4D::value_type, double> && "dVec4 must contain double elements");
    static_assert(std::is_same_v<fgm::Vec4D, fgm::Vector4D<double>> && "dVec4 must be an alias of Vector4D<double>");


    static_assert(std::is_same_v<fgm::Vec4UL::value_type, unsigned long long> &&
                  "ulVec4 must contain unsigned long long elements");
    static_assert(std::is_same_v<fgm::Vec4UL, fgm::Vector4D<unsigned long long>> &&
                  "ulVec4 must be an alias of Vector4D<unsigned long long>");
} // namespace

/** @} */
