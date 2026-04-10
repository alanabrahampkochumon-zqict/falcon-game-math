/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 10, 2026
 *
 * @brief Verifies @ref fgm::Matrix2D multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix2DScalarMultiplication: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _mat;
    T _scalar;
    fgm::Matrix2D<T> _expectedFloatingMat;
    fgm::Matrix2D<T> _expectedIntegralMat;

    void SetUp() override
    {
        _mat = { fgm::Vector2D{ T(7), T(13) }, fgm::Vector2D{ T(5), T(4) } };
        _scalar = T(2.123456789123456);
        _expectedFloatingMat = { fgm::Vector2D{ T(14.864197523864192), T(27.604938258604928) },
                                 fgm::Vector2D{ T(10.61728394561728), T(8.493827156493824) } };
        _expectedIntegralMat = { fgm::Vector2D{ T(14), T(26) }, fgm::Vector2D{ T(10), T(8) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix2D scalar multiplication, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix2DScalarMultiplication, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Multiplication
 * @{
 */

/**************************************
 *                                    *
 *     SCALAR MULTIPLICATION TESTS    *
 *                                    *
 **************************************/

/** @test Verify that scalar multiplication by zero returns a zero matrix. */
TEST(Matrix2DScalarMultiplication, MultiplicationByZeroReturnsZeroMatrix)
{
    constexpr fgm::Matrix2D mat(3.0f, 4.0f, 5.0f, 6.0f);

    constexpr fgm::Matrix2D product = mat * 0;

    EXPECT_MAT_ZERO(product);
}


/** @test Verify that scalar multiplication by one returns original matrix. */
TEST(Matrix2DScalarMultiplication, MultiplicationByOneReturnsOriginalMatrix)
{
    constexpr fgm::Matrix2D mat(3.0f, 4.0f, 5.0f, 6.0f);

    constexpr fgm::Matrix2D product = mat * 1;

    EXPECT_MAT_EQ(mat, product);
}


/**
 * @test Verify that the binary multiplication operator (matrix * scalar) perform an element-wise product
 *       and returns a new matrix instance.
 */
TYPED_TEST(Matrix2DScalarMultiplication, MatrixTimesScalarReturnsScaledMatrix)
{
    const fgm::Matrix2D product = this->_mat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
}


/**
 * @test Verify that the binary multiplication operator (scalar * matrix) perform an element-wise product
 *       and returns a new matrix instance.
 */
TYPED_TEST(Matrix2DScalarMultiplication, ScalarTimesAMatrixReturnsScaledMatrix)
{
    const fgm::Matrix2D product = this->_scalar * this->_mat;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
}


/**
 * @test Verify that the compound multiplication assignment operator performs an element-wise product
 *       and mutates the matrix in-place.
 */
TYPED_TEST(Matrix2DScalarMultiplication, MatrixTimesEqualScalarIsTheSameMatrixScaled)
{
    this->_mat *= this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, this->_mat);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, this->_mat);
}


/**
 * @test Verify that the binary multiplication operator perform automatic type promotion
 *       to the wider numeric type.
 */
TYPED_TEST(Matrix2DScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    constexpr double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Matrix2D product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}


/**
 * @test Verify that the compound multiplication assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Matrix2DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Matrix2D mat(3.0f, -1.0f);
    constexpr double scalar = 5.0;
    mat *= scalar;

    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


/**
 * @test Verify that the compound multiplication operator for mixed types
 *       ensure minimal precision loss.
 */
TEST(Matrix2DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    fgm::Matrix2D mat(3, -1);
    constexpr double scalar = 2.5;
    constexpr fgm::Matrix2D expected(7, -2);

    mat *= scalar;

    EXPECT_MAT_EQ(expected, mat);
}

/** @} */