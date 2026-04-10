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


template <typename T>
class Matrix2DVectorMultiplication: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _mat;
    fgm::Vector2D<T> _vec;
    fgm::Vector2D<T> _expectedFloatingColVector;
    fgm::Vector2D<T> _expectedIntegralColVector;

    void SetUp() override
    {
        _mat = { fgm::Vector2D{ T(7.12345678912345), T(13.12345678912345) },
                 fgm::Vector2D{ T(5.12345678912345), T(4.12345678912345) } };
        _vec = { T(2.123456789123456), T(3.123456832912) };
        _expectedFloatingColVector = { T(31.129248797008778), T(40.74653269883751) };
        _expectedIntegralColVector = { T(29), T(38) };
    }
};
/** @brief Test fixture for @ref fgm::Matrix2D vector multiplication, parameterized by @ref SupportedArithmeticTypes. */
//TYPED_TEST_SUITE(Matrix2DVectorMultiplication, SupportedArithmeticTypes);
TYPED_TEST_SUITE(Matrix2DVectorMultiplication, ::testing::Types<double>);



/**
 * @addtogroup T_FGM_Mat2x2_Multiplication
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that matrix multiplication operations are available at compile time. */
namespace
{
    constexpr fgm::Matrix2D s_Mat1(1, 2, 3, 4);
    constexpr fgm::Vector2D s_Vec(1, 2);

    // Verify matrix * scalar multiplication
    constexpr fgm::Matrix2D s_BinaryProduct1 = s_Mat1 * 2;
    static_assert(s_BinaryProduct1(0, 0) == 2);
    static_assert(s_BinaryProduct1(0, 1) == 4);
    static_assert(s_BinaryProduct1(1, 0) == 6);
    static_assert(s_BinaryProduct1(1, 1) == 8);


    // Verify scalar * matrix multiplication
    constexpr fgm::Matrix2D s_BinaryProduct2 = 2 * s_Mat1;
    static_assert(s_BinaryProduct2(0, 0) == 2);
    static_assert(s_BinaryProduct2(0, 1) == 4);
    static_assert(s_BinaryProduct2(1, 0) == 6);
    static_assert(s_BinaryProduct2(1, 1) == 8);

    // Verify matrix * vector multiplication
    constexpr fgm::Vector2D s_ColVecProduct = s_Mat1 * s_Vec;
    static_assert(s_ColVecProduct[0] == 5);
    static_assert(s_ColVecProduct[1] == 11);
} // namespace



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


/** @test Verify that scalar multiplication by one returns original matrix. */
TEST(Matrix2DScalarMultiplication, MultiplicationByNegativeScalarFlipsSigns)
{
    constexpr fgm::Matrix2D mat = { 1.0f, -2.0f, -4.0f, 5.0f };
    constexpr fgm::Matrix2D expected = { -2.0f, 4.0f, 8.0f, -10.0f };
    constexpr float scalar = -2.0f;

    constexpr fgm::Matrix2D<float> product = mat * scalar;

    EXPECT_MAT_EQ(expected, product);
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
 * @test Verify that the compound multiplication assignment operator (scalar) performs an element-wise product
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
 * @test Verify that the binary multiplication operator (scalar) perform automatic type promotion
 *       to the wider numeric type.
 */
TYPED_TEST(Matrix2DScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    constexpr double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Matrix2D product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}


/**
 * @test Verify that the compound multiplication assignment operator (scalar) maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Matrix2DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Matrix2D mat(3.0f, -1.0f, -12.0f, 14.0f);
    constexpr double scalar = 5.0;
    mat *= scalar;

    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


/**
 * @test Verify that the compound multiplication operator (scalar) for mixed type
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


/**
 * @brief Verify that the binary vector multiplication operation perform linear transformation
 *        and returns a new column vector.
 */
TYPED_TEST(Matrix2DVectorMultiplication, MatrixTimesVectorReturnsATransformedVector)
{
    const auto transformedVector = this->_mat * this->_vec;
    if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_VEC_EQ(this->_expectedFloatingColVector, transformedVector);
    else
        EXPECT_VEC_EQ(this->_expectedIntegralColVector, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation with identity matrix perform linear transformation
 *        and returns a new column vector.
 */
TEST(Matrix2DVectorMultiplication, IdentityMatrixTimesVectorReturnsOriginalVector)
{
    constexpr fgm::Matrix2D<float> iMatrix;
    constexpr fgm::vec2 vec(2.0f, 1.0f);

    constexpr fgm::vec2 transformedVector = iMatrix * vec;

    EXPECT_VEC_EQ(vec, transformedVector);
}

//TEST(Matrix2D_Product, VectorTimesAMatrixReturnsANewVectorWithCorrectValues)
//{
//    // Arrange
//    const fgm::Matrix2D mat = { 1.0f, 2.0f, 4.0f, 5.0f };
//    const fgm::vec2 vec(2.0f, 1.0f);
//    const fgm::vec2 expected(6.0f, 9.0f);
//
//    // Act
//    const fgm::vec2 actual = vec * mat;
//
//    // Assert
//    testutils::EXPECT_VEC_EQ(expected, actual);
//}
//
//TEST(Matrix2D_Product, VectorTimesIdentityMatrixReturnsTheSameMatrix)
//{
//    // Arrange
//    const fgm::Matrix2D<float> mat;
//    fgm::vec2 vec(2.0f, 1.0f);
//
//    // Act
//    const fgm::vec2 actual = vec * mat;
//
//    // Assert
//    testutils::EXPECT_VEC_EQ(vec, actual);
//}

/** @} */