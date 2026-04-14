/**
 * @file InverseTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref fgm::Matrix2D inverse logic.
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
class Matrix2DInverse: public ::testing::Test
{
protected:
    using Mag = fgm::Magnitude<T>;
    fgm::Matrix2D<T> _matrix;
    fgm::Matrix2D<Mag> _expectedInverse;

    void SetUp() override
    {
        _matrix = { fgm::Vector2D{ T(5), T(4) }, fgm::Vector2D{ T(2), T(3) } };
        _expectedInverse = { fgm::Vector2D{ Mag(0.42857142857142855), Mag(-0.5714285714285714) },
                             fgm::Vector2D{ Mag(-0.2857142857142857), Mag(0.7142857142857143) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix2D inverse, parameterized @ref SupportedTypes */
TYPED_TEST_SUITE(Matrix2DInverse, SupportedTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Inverse
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that matrix inverse is available at compile time. */
// namespace
//{
//     constexpr fgm::Matrix2D MAT(1, 2, 3, 4);
//
//     // Verify matrix transpose (member function)
//     constexpr fgm::Matrix2D TRANS_MAT = MAT.transpose();
//     static_assert(TRANS_MAT(0, 0) == 1);
//     static_assert(TRANS_MAT(0, 1) == 3);
//     static_assert(TRANS_MAT(1, 0) == 2);
//     static_assert(TRANS_MAT(1, 1) == 4);
//
//     // Verify matrix transpose (static function)
//     constexpr fgm::Matrix2D TRANS_MAT_S = fgm::Matrix2D<int>::transpose(MAT);
//     static_assert(TRANS_MAT_S(0, 0) == 1);
//     static_assert(TRANS_MAT_S(0, 1) == 3);
//     static_assert(TRANS_MAT_S(1, 0) == 2);
//     static_assert(TRANS_MAT_S(1, 1) == 4);
// } // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/** @brief Verify that inverting a matrix returns the correct matrix. */
TYPED_TEST(Matrix2DInverse, ExchangesRowsAndColumnElements)
{
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.inverse());
}


/** @brief Verify that inverse of matrix times itself is an identity matrix. */
TYPED_TEST(Matrix2DInverse, InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.inverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Matrix2D::inverse exchanges row and
 *        column elements and returns a new matrix.
 */
TYPED_TEST(Matrix2DInverse, StaticWrapper_ExchangesRowsAndColumnElements)
{
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Matrix2D<TypeParam>::inverse(this->_matrix));
}


/** @brief Verify that inverse of matrix (using the static variant) times itself is an identity matrix. */
TYPED_TEST(Matrix2DInverse, StaticWrapper_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = fgm::Matrix2D<TypeParam>::inverse(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}

/** @} */