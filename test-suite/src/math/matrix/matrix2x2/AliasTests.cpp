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



/**
 * @addtogroup T_FGM_Mat2x2_Alias
 * @{
 */

/** @brief Verify that fgm::*Mat2 and fgm::mat2 are alias wrappers for integral and floating-point 2D matrix. */
namespace
{
    /** Verify @ref fgm::bMat2 has `bool` value_type. */
    static_assert(std::is_same_v<fgm::bMat2::value_type, bool> && "bMat2 must contain boolean elements");
    static_assert(std::is_same_v<fgm::bMat2, fgm::Matrix2D<bool>> && "bMat2 must be an alias of Matrix2D<bool>");


    /** Verify @ref fgm::iMat2 has `int` value_type. */
    static_assert(std::is_same_v<fgm::iMat2::value_type, int> && "iMat2 must contain int elements");
    static_assert(std::is_same_v<fgm::iMat2, fgm::Matrix2D<int>> && "iMat2 must be an alias of Matrix2D<int>");


    /** Verify @ref fgm::uMat2 has `unsigned int` value_type. */
    static_assert(std::is_same_v<fgm::uMat2::value_type, unsigned int> && "uMat2 must contain unsigned int elements");
    static_assert(std::is_same_v<fgm::uMat2, fgm::Matrix2D<unsigned int>> &&
                  "uMat2 must be an alias of Matrix2D<unsigned int>");


    /** Verify @ref fgm::lMat2 has `long long` value_type. */
    static_assert(std::is_same_v<fgm::mat2::value_type, float> && "mat2 must contain float elements");
    static_assert(std::is_same_v<fgm::mat2, fgm::Matrix2D<float>> && "mat2 must be an alias of Matrix2D<float>");


    /** Verify @ref fgm::lMat2 has `long long` value_type. */
    static_assert(std::is_same_v<fgm::lMat2::value_type, long long> && "lMat2 must contain long long elements");
    static_assert(std::is_same_v<fgm::lMat2, fgm::Matrix2D<long long>> &&
                  "lMat2 must be an alias of Matrix2D<long long>");


    /** Verify @ref fgm::dMat2 has `double` value_type. */
    static_assert(std::is_same_v<fgm::dMat2::value_type, double> && "dMat2 must contain double elements");
    static_assert(std::is_same_v<fgm::dMat2, fgm::Matrix2D<double>> && "dMat2 must be an alias of Matrix2D<double>");


    /** Verify @ref fgm::ulMat2 has `unsigned long long` value_type. */
    static_assert(std::is_same_v<fgm::ulMat2::value_type, unsigned long long> &&
                  "ulMat2 must contain unsigned long long elements");
    static_assert(std::is_same_v<fgm::ulMat2, fgm::Matrix2D<unsigned long long>> &&
                  "ulMat2 must be an alias of Matrix2D<unsigned long long>");
} // namespace

/** @} */