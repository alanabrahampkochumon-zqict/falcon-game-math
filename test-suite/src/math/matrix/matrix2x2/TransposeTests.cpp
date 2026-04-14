/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verifies @ref fgm::Matrix2D transpose logic.
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
