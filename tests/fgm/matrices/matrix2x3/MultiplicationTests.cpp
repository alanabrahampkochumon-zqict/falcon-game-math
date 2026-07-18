/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref fgm::Matrix2x3 scalar multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Matrix2x3TestSetup.h"


template <typename T>
class Matrix2x3ScalarMultiplication: public ::testing::Test
{
protected:
    fgm::Mat2x3<T> _mat;
    T _scalar;
    fgm::Mat2x3<T> _expectedFloatingMat;
    fgm::Mat2x3<T> _expectedIntegralMat;



    void SetUp() override
    {
        _mat                 = { fgm::Vec2{ T(7), T(13) }, fgm::Vec2{ T(5), T(4) }, fgm::Vec2{ T(11), T(2) } };
        _scalar              = T(2.123456789123456);
        _expectedFloatingMat = { fgm::Vec2{ T(14.864197523864192), T(27.604938258604928) },
                                 fgm::Vec2{ T(10.61728394561728), T(8.493827156493824) },
                                 fgm::Vec2{ T(23.358024680358014), T(4.246913578246912) } };
        _expectedIntegralMat = { fgm::Vec2{ T(14), T(26) }, fgm::Vec2{ T(10), T(8) },
                                 fgm::Vec2{ T(22), T(4) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix2x3 scalar multiplication, parameterized by @ref SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Matrix2x3ScalarMultiplication, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Mat2x3_Multiplication
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
    constexpr fgm::Mat2x3 MAT1(1, 2, 3, 4, 5, 6);

    // Verify matrix * scalar multiplication
    constexpr fgm::Mat2x3 BINARY_PRODUCT_1 = MAT1 * 2;
    static_assert(BINARY_PRODUCT_1(0, 0) == 2);
    static_assert(BINARY_PRODUCT_1(0, 1) == 4);
    static_assert(BINARY_PRODUCT_1(0, 2) == 6);
    static_assert(BINARY_PRODUCT_1(1, 0) == 8);
    static_assert(BINARY_PRODUCT_1(1, 1) == 10);
    static_assert(BINARY_PRODUCT_1(1, 2) == 12);


    // Verify scalar * matrix multiplication
    constexpr fgm::Mat2x3 BINARY_PRODUCT_2 = 2 * MAT1;
    static_assert(BINARY_PRODUCT_2(0, 0) == 2);
    static_assert(BINARY_PRODUCT_2(0, 1) == 4);
    static_assert(BINARY_PRODUCT_2(0, 2) == 6);
    static_assert(BINARY_PRODUCT_2(1, 0) == 8);
    static_assert(BINARY_PRODUCT_2(1, 1) == 10);
    static_assert(BINARY_PRODUCT_2(1, 2) == 12);

} // namespace



/**************************************
 *                                    *
 *     SCALAR MULTIPLICATION TESTS    *
 *                                    *
 **************************************/

/** @brief Verify that scalar multiplication by zero returns a zero matrix. */
TEST(Matrix2x3ScalarMultiplication, MultiplicationByZeroReturnsZeroMatrix)
{
    const fgm::Mat2x3 mat(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);

    const fgm::Mat2x3 product = mat * 0;

    EXPECT_MAT_ZERO(product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Matrix2x3ScalarMultiplication, MultiplicationByOneReturnsOriginalMatrix)
{
    const fgm::Mat2x3 mat(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);

    const fgm::Mat2x3 product = mat * 1;

    EXPECT_MAT_EQ(mat, product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Matrix2x3ScalarMultiplication, MultiplicationByNegativeScalarFlipsSigns)
{
    const fgm::Mat2x3 mat      = { 1.0f, -2.0f, -4.0f, 5.0f, 10.0f, -1.0f };
    const fgm::Mat2x3 expected = { -2.0f, 4.0f, 8.0f, -10.0f, -20.f, 2.0f };
    const float scalar            = -2.0f;

    const fgm::Mat2x3<float> product = mat * scalar;

    EXPECT_MAT_EQ(expected, product);
}


/**
 * @brief Verify that the binary multiplication operator (matrix * scalar) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix2x3ScalarMultiplication, MatrixTimesScalarReturnsScaledMatrix)
{
    const fgm::Mat2x3 product = this->_mat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


/**
 * @brief Verify that the binary multiplication operator (scalar * matrix) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix2x3ScalarMultiplication, ScalarTimesAMatrixReturnsScaledMatrix)
{
    const fgm::Mat2x3 product = this->_scalar * this->_mat;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


/**
 * @brief Verify that the compound multiplication assignment operator (scalar) performs an element-wise product
 *        and mutates the matrix in-place.
 */
TYPED_TEST(Matrix2x3ScalarMultiplication, MatrixTimesEqualScalarIsTheSameMatrixScaled)
{
    this->_mat *= this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, this->_mat);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, this->_mat);
    }
}


/**
 * @brief Verify that the binary multiplication operator (scalar) perform automatic type promotion
 *        to the wider numeric type.
 */
TYPED_TEST(Matrix2x3ScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Mat2x3 product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}


/**
 * @brief Verify that the compound multiplication assignment operator (scalar) maintains the destination type and
 *        perform an implicit cast.
 */
TEST(Matrix2x3ScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Mat2x3 mat(3.0f, -1.0f, -12.0f, 14.0f, 12.0f, 3.2f);
    const double scalar = 5.0;
    mat *= scalar;

    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


/**
 * @brief Verify that the compound multiplication operator (scalar) for mixed type
 *        ensure minimal precision loss.
 */
TEST(Matrix2x3ScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    fgm::Mat2x3 mat(3, -1, 10, 5, 50, 12);
    const double scalar = 2.5;
    const fgm::Mat2x3 expected(7, -2, 25, 12, 125, 30);

    mat *= scalar;

    EXPECT_MAT_EQ(expected, mat);
}

/** @} */
