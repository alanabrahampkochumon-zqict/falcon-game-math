/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 28, 2026
 *
 * @brief Verify @ref fgm::Matrix3D transpose logic.
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
class Matrix3DTranspose: public ::testing::Test
{
protected:
    fgm::Matrix3D<T> _matrix, _expectedTranspose;

    void SetUp() override
    {
        _matrix = { { T(1), T(2), T(3) }, { T(4), T(5), T(6) }, { T(7), T(8), T(9) } };
        _expectedTranspose = { { T(1), T(4), T(7) }, { T(2), T(5), T(8) }, { T(3), T(6), T(9) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix3D transpose, parameterized @ref SupportedTypes */
TYPED_TEST_SUITE(Matrix3DTranspose, SupportedTypes);



/**
 * @addtogroup T_FGM_Mat3x3_Transpose
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
    constexpr fgm::Matrix3D MAT(1, 2, 3, 4, 5, 6, 7, 8, 9);

    // Verify matrix transpose (member function)
    constexpr fgm::Matrix3D TRANSPOSE_MAT = MAT.transpose();
    static_assert(TRANSPOSE_MAT(0, 0) == 1);
    static_assert(TRANSPOSE_MAT(0, 1) == 4);
    static_assert(TRANSPOSE_MAT(0, 2) == 7);

    static_assert(TRANSPOSE_MAT(1, 0) == 2);
    static_assert(TRANSPOSE_MAT(1, 1) == 5);
    static_assert(TRANSPOSE_MAT(1, 2) == 8);

    static_assert(TRANSPOSE_MAT(2, 0) == 3);
    static_assert(TRANSPOSE_MAT(2, 1) == 7);
    static_assert(TRANSPOSE_MAT(2, 2) == 9);


    // Verify matrix transpose (static function)
    constexpr fgm::Matrix3D TRANSPOSE_MAT_S = fgm::Matrix3D<int>::transpose(MAT);
    static_assert(TRANSPOSE_MAT_S(0, 0) == 1);
    static_assert(TRANSPOSE_MAT_S(0, 1) == 4);
    static_assert(TRANSPOSE_MAT_S(0, 2) == 7);

    static_assert(TRANSPOSE_MAT_S(1, 0) == 2);
    static_assert(TRANSPOSE_MAT_S(1, 1) == 5);
    static_assert(TRANSPOSE_MAT_S(1, 2) == 8);

    static_assert(TRANSPOSE_MAT_S(2, 0) == 3);
    static_assert(TRANSPOSE_MAT_S(2, 1) == 7);
    static_assert(TRANSPOSE_MAT_S(2, 2) == 9);
}



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/** @brief Verify that transposing a matrix exchanges row and column elements and returns a new matrix. */
TYPED_TEST(Matrix3DTranspose, ExchangesRowsAndColumnElements)
{
    EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose());
}


/**
 * @brief Verify that transposing a matrix using static variant of @ref fgm::Matrix3D::transpose exchanges row and
 *        column elements and returns a new matrix.
 */
TYPED_TEST(Matrix3DTranspose, StaticWrapper_ExchangesRowsAndColumnElements)
{
    EXPECT_MAT_EQ(this->_expectedTranspose, fgm::Matrix3D<TypeParam>::transpose(this->_matrix));
}

/** @} */
