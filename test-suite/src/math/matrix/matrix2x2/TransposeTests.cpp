/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref fgm::Matrix2D transpose logic.
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
class Matrix2DTranspose: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _matrix, _expectedTranspose;

    void SetUp() override
    {
        _matrix = { fgm::Vector2D{ T(1), T(2) }, fgm::Vector2D{ T(3), T(4) } };
        _expectedTranspose = { fgm::Vector2D{ T(1), T(3) }, fgm::Vector2D{ T(2), T(4) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix2D transpose, parameterized @ref SupportedTypes */
TYPED_TEST_SUITE(Matrix2DTranspose, SupportedTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Transpose
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
    constexpr fgm::Matrix2D MAT(1, 2, 3, 4);

    // Verify matrix transpose (member function)
    constexpr fgm::Matrix2D TRANSPOSE_MAT = MAT.transpose();
    static_assert(TRANSPOSE_MAT(0, 0) == 1);
    static_assert(TRANSPOSE_MAT(0, 1) == 3);
    static_assert(TRANSPOSE_MAT(1, 0) == 2);
    static_assert(TRANSPOSE_MAT(1, 1) == 4);

    // Verify matrix transpose (static function)
    constexpr fgm::Matrix2D TRANSPOSE_MAT_S = fgm::Matrix2D<int>::transpose(MAT);
    static_assert(TRANSPOSE_MAT_S(0, 0) == 1);
    static_assert(TRANSPOSE_MAT_S(0, 1) == 3);
    static_assert(TRANSPOSE_MAT_S(1, 0) == 2);
    static_assert(TRANSPOSE_MAT_S(1, 1) == 4);
}



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/** @brief Verify that transposing a matrix exchanges row and column elements and returns a new matrix. */
TYPED_TEST(Matrix2DTranspose, ExchangesRowsAndColumnElements)
{
    EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose());
}


/**
 * @brief Verify that transposing a matrix using static variant of @ref fgm::Matrix2D::transpose exchanges row and
 *        column elements and returns a new matrix.
 */
TYPED_TEST(Matrix2DTranspose, StaticWrapper_ExchangesRowsAndColumnElements)
{
    EXPECT_MAT_EQ(this->_expectedTranspose, fgm::Matrix2D<TypeParam>::transpose(this->_matrix));
}

/** @} */
