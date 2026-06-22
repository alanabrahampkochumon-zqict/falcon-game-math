/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify alias for @ref fgm::Matrix4D returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**
 * @addtogroup T_FGM_Mat4x4_Alias
 * @{
 */

/** @brief Verify that fgm::*Mat4 and fgm::mat4 are alias wrappers for integral and floating-point 4D matrix. */
namespace
{
    /** Verify @ref fgm::bMat4 has `bool` value_type. */
    static_assert(std::is_same_v<fgm::Mat4B::value_type, bool> && "bMat4 must contain boolean elements");
    static_assert(std::is_same_v<fgm::Mat4B, fgm::Matrix4D<bool>> && "bMat4 must be an alias of Matrix4D<bool>");


    /** Verify @ref fgm::iMat4 has `int` value_type. */
    static_assert(std::is_same_v<fgm::Mat4I::value_type, int> && "iMat4 must contain int elements");
    static_assert(std::is_same_v<fgm::Mat4I, fgm::Matrix4D<int>> && "iMat4 must be an alias of Matrix4D<int>");


    /** Verify @ref fgm::uMat4 has `unsigned int` value_type. */
    static_assert(std::is_same_v<fgm::Mat4U::value_type, unsigned int> && "uMat4 must contain unsigned int elements");
    static_assert(std::is_same_v<fgm::Mat4U, fgm::Matrix4D<unsigned int>> &&
                  "uMat4 must be an alias of Matrix4D<unsigned int>");


    /** Verify @ref fgm::lMat4 has `long long` value_type. */
    static_assert(std::is_same_v<fgm::Mat4F::value_type, float> && "mat4 must contain float elements");
    static_assert(std::is_same_v<fgm::Mat4F, fgm::Matrix4D<float>> && "mat4 must be an alias of Matrix4D<float>");


    /** Verify @ref fgm::lMat4 has `long long` value_type. */
    static_assert(std::is_same_v<fgm::Mat4LL::value_type, long long> && "lMat4 must contain long long elements");
    static_assert(std::is_same_v<fgm::Mat4LL, fgm::Matrix4D<long long>> &&
                  "lMat4 must be an alias of Matrix4D<long long>");


    /** Verify @ref fgm::dMat4 has `double` value_type. */
    static_assert(std::is_same_v<fgm::Mat4D::value_type, double> && "dMat4 must contain double elements");
    static_assert(std::is_same_v<fgm::Mat4D, fgm::Matrix4D<double>> && "dMat4 must be an alias of Matrix4D<double>");


    /** Verify @ref fgm::ulMat4 has `unsigned long long` value_type. */
    static_assert(std::is_same_v<fgm::Mat4ULL::value_type, unsigned long long> &&
                  "ulMat4 must contain unsigned long long elements");
    static_assert(std::is_same_v<fgm::Mat4ULL, fgm::Matrix4D<unsigned long long>> &&
                  "ulMat4 must be an alias of Matrix4D<unsigned long long>");
} // namespace

/** @} */
