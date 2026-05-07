/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify @ref fgm::Matrix4D transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**************************************
 *                                    *
 *              SETUP                 *
 *                                    *
 **************************************/

template <typename T>
class Matrix4DTranspose: public ::testing::Test
{
protected:
    fgm::Matrix4D<T> _matrix, _expectedTranspose;

    void SetUp() override
    {
        _matrix = { { T(1), T(2), T(3), T(4) },
                    { T(5), T(6), T(7), T(8) },
                    { T(9), T(10), T(11), T(12) },
                    { T(13), T(14), T(15), T(16) } };
        _expectedTranspose = { { T(1), T(5), T(9), T(13) },
                               { T(2), T(7), T(10), T(14) },
                               { T(3), T(7), T(11), T(15) },
                               { T(4), T(8), T(12), T(16) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix4D transpose, parameterized @ref SupportedTypes */
TYPED_TEST_SUITE(Matrix4DTranspose, SupportedTypes);



/**
 * @addtogroup T_FGM_Mat4x4_Transpose
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that matrix transpose is available at compile time. */
namespace
{
    constexpr fgm::Matrix4D MAT(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    // Verify matrix transpose (member function)
    constexpr fgm::Matrix4D TRANSPOSE_MAT = MAT.transpose();
    // static_assert(TRANSPOSE_MAT(0, 0) == 1);
    // static_assert(TRANSPOSE_MAT(0, 1) == 5);
    // static_assert(TRANSPOSE_MAT(0, 2) == 9);
    // static_assert(TRANSPOSE_MAT(0, 3) == 13);
    //
    // static_assert(TRANSPOSE_MAT(1, 0) == 2);
    // static_assert(TRANSPOSE_MAT(1, 1) == 6);
    // static_assert(TRANSPOSE_MAT(1, 2) == 10);
    // static_assert(TRANSPOSE_MAT(1, 3) == 14);
    //
    // static_assert(TRANSPOSE_MAT(2, 0) == 3);
    // static_assert(TRANSPOSE_MAT(2, 1) == 7);
    // static_assert(TRANSPOSE_MAT(2, 2) == 11);
    // static_assert(TRANSPOSE_MAT(2, 3) == 15);
    //
    // static_assert(TRANSPOSE_MAT(3, 0) == 4);
    // static_assert(TRANSPOSE_MAT(3, 1) == 8);
    // static_assert(TRANSPOSE_MAT(3, 2) == 12);
    // static_assert(TRANSPOSE_MAT(3, 3) == 16);
    //
    //
    // // Verify matrix transpose (static function)
    // constexpr fgm::Matrix4D TRANSPOSE_MAT_S = fgm::Matrix4D<int>::transpose(MAT);
    // static_assert(TRANSPOSE_MAT_S(0, 0) == 1);
    // static_assert(TRANSPOSE_MAT_S(0, 1) == 5);
    // static_assert(TRANSPOSE_MAT_S(0, 2) == 9);
    // static_assert(TRANSPOSE_MAT_S(0, 3) == 13);
    //
    // static_assert(TRANSPOSE_MAT_S(1, 0) == 2);
    // static_assert(TRANSPOSE_MAT_S(1, 1) == 6);
    // static_assert(TRANSPOSE_MAT_S(1, 2) == 10);
    // static_assert(TRANSPOSE_MAT_S(1, 3) == 14);
    //
    // static_assert(TRANSPOSE_MAT_S(2, 0) == 3);
    // static_assert(TRANSPOSE_MAT_S(2, 1) == 7);
    // static_assert(TRANSPOSE_MAT_S(2, 2) == 11);
    // static_assert(TRANSPOSE_MAT_S(2, 3) == 15);
    //
    // static_assert(TRANSPOSE_MAT_S(3, 0) == 4);
    // static_assert(TRANSPOSE_MAT_S(3, 1) == 8);
    // static_assert(TRANSPOSE_MAT_S(3, 2) == 12);
    // static_assert(TRANSPOSE_MAT_S(3, 3) == 16);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/** @brief Verify that transposing a matrix exchanges row and column elements and returns a new matrix. */
TYPED_TEST(Matrix4DTranspose, ExchangesRowsAndColumnElements)
{ EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose()); }


/**
 * @brief Verify that transposing a matrix using static variant of @ref fgm::Matrix4D::transpose exchanges row and
 *        column elements and returns a new matrix.
 */
TYPED_TEST(Matrix4DTranspose, StaticWrapper_ExchangesRowsAndColumnElements)
{ EXPECT_MAT_EQ(this->_expectedTranspose, fgm::Matrix4D<TypeParam>::transpose(this->_matrix)); }

/** @} */
