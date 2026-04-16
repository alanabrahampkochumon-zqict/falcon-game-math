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
/** @brief Test fixture for @ref fgm::Matrix2D inverse, parameterized @ref SupportedSignedArithmeticTypes */
TYPED_TEST_SUITE(Matrix2DInverse, SupportedSignedArithmeticTypes);


/** @brief Test fixture for calculating @ref fgm::Matrix2D inverse with singular matrices */
class SingularMatrix2DInverse: public ::testing::TestWithParam<fgm::Matrix2D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Matrix2DInverseTestSuite, SingularMatrix2DInverse,
                         ::testing::Values(fgm::Matrix2D{ fgm::Vector2D{ 1.0f, 2.0f }, fgm::Vector2D{ 1.0f, 2.0f } },
                                           fgm::Matrix2D{ fgm::Vector2D{ 2.0f, 2.0f }, fgm::Vector2D{ 2.0f, 2.0f } },
                                           fgm::Matrix2D{ fgm::Vector2D{ 3.0f, 2.0f }, fgm::Vector2D{ 6.0f, 4.0f } },
                                           fgm::Matrix2D{ fgm::Vector2D{ 0.0f, 0.0f }, fgm::Vector2D{ 4.0f, 5.0f } },
                                           fgm::Matrix2D{ fgm::Vector2D{ 0.0f, 3.0f }, fgm::Vector2D{ 0.0f, 5.0f } }));




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
 *       INVERSE TESTS (RUNTIME)      *
 *                                    *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Matrix2D::inverse exchanges row and
 *        column elements and returns a new matrix.
 */
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


/**************************************
 *                                    *
 *          SAFE INVERSE TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Matrix2D::safeInverse exchanges row and
 *        column elements and returns a new matrix.
 */
TYPED_TEST(Matrix2DInverse, SafeInverse_ExchangesRowsAndColumnElements)
{
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.safeInverse());
}


/** @brief Verify that inverse of matrix (using @ref fgm::Matrix2D::safeInverse) times itself is an identity matrix. */
TYPED_TEST(Matrix2DInverse, SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.safeInverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


/** 
 * @brief Verify that inverting a singular matrix using @ref fgm::Matrix2D::safeInverse
 *         returns identity matrix by default.
 */
TEST_P(SingularMatrix2DInverse, SingularMatrixReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Matrix2D::safeInverse
 *         returns passed-in fallback.
 */
TEST_P(SingularMatrix2DInverse, SingularMatrixReturnsPassedInFallback)
{
    const auto& inverseMatrix = GetParam().safeInverse(fgm::mat2d::zero<ParamType::value_type>);
    EXPECT_MAT_ZERO(inverseMatrix);
}


/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Matrix2D::safeInverse exchanges row and
 *        column elements and returns a new matrix.
 */
TYPED_TEST(Matrix2DInverse, StaticWrapper_SafeInverse_ExchangesRowsAndColumnElements)
{
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Matrix2D<TypeParam>::safeInverseOf(this->_matrix));
}


/**
 * @brief Verify that inverse of matrix (using static variant of @ref fgm::Matrix2D::safeInverse) times itself is an
 *        identity matrix.
 */
TYPED_TEST(Matrix2DInverse, StaticWrapper_SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = fgm::Matrix2D<TypeParam>::safeInverseOf(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}

/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix2D::safeInverseOf
 *         returns identity matrix by default.
 */
TEST_P(SingularMatrix2DInverse, StaticWrapper_SingularMatrixReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix2D::safeInverseOf
 *         returns passed-in fallback.
 */
TEST_P(SingularMatrix2DInverse, StaticWrapper_SingularMatrixReturnsPassedInFallback)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::safeInverseOf(matrix, fgm::mat2d::zero<ParamType::value_type>));
}

/** @} */