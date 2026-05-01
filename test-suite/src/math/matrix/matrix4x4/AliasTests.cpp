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



/**
 * @addtogroup T_FGM_Mat3x3_Alias
 * @{
 */

/** @brief Verify that fgm::*Mat3 and fgm::mat3 are alias wrappers for integral and floating-point 3D matrix. */
namespace
{
    /** Verify @ref fgm::bMat3 has `bool` value_type. */
    static_assert(std::is_same_v<fgm::bMat3::value_type, bool> && "bMat3 must contain boolean elements");
    static_assert(std::is_same_v<fgm::bMat3, fgm::Matrix3D<bool>> && "bMat3 must be an alias of Matrix3D<bool>");


    /** Verify @ref fgm::iMat3 has `int` value_type. */
    static_assert(std::is_same_v<fgm::iMat3::value_type, int> && "iMat3 must contain int elements");
    static_assert(std::is_same_v<fgm::iMat3, fgm::Matrix3D<int>> && "iMat3 must be an alias of Matrix3D<int>");


    /** Verify @ref fgm::uMat3 has `unsigned int` value_type. */
    static_assert(std::is_same_v<fgm::uMat3::value_type, unsigned int> && "uMat3 must contain unsigned int elements");
    static_assert(std::is_same_v<fgm::uMat3, fgm::Matrix3D<unsigned int>> &&
                  "uMat3 must be an alias of Matrix3D<unsigned int>");


    /** Verify @ref fgm::lMat3 has `long long` value_type. */
    static_assert(std::is_same_v<fgm::mat3::value_type, float> && "mat3 must contain float elements");
    static_assert(std::is_same_v<fgm::mat3, fgm::Matrix3D<float>> && "mat3 must be an alias of Matrix3D<float>");


    /** Verify @ref fgm::lMat3 has `long long` value_type. */
    static_assert(std::is_same_v<fgm::lMat3::value_type, long long> && "lMat3 must contain long long elements");
    static_assert(std::is_same_v<fgm::lMat3, fgm::Matrix3D<long long>> &&
                  "lMat3 must be an alias of Matrix3D<long long>");


    /** Verify @ref fgm::dMat3 has `double` value_type. */
    static_assert(std::is_same_v<fgm::dMat3::value_type, double> && "dMat3 must contain double elements");
    static_assert(std::is_same_v<fgm::dMat3, fgm::Matrix3D<double>> && "dMat3 must be an alias of Matrix3D<double>");


    /** Verify @ref fgm::ulMat3 has `unsigned long long` value_type. */
    static_assert(std::is_same_v<fgm::ulMat3::value_type, unsigned long long> &&
                  "ulMat3 must contain unsigned long long elements");
    static_assert(std::is_same_v<fgm::ulMat3, fgm::Matrix3D<unsigned long long>> &&
                  "ulMat3 must be an alias of Matrix3D<unsigned long long>");
} // namespace

/** @} */