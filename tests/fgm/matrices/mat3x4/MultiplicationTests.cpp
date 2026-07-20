/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref fgm::Mat3x4 scalar multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x4TestSetup.h"


template <typename T>
class Mat3x4ScalarMultiplication: public ::testing::Test
{
protected:
    fgm::Mat3x4<T> _mat;
    T _scalar;
    fgm::Mat3x4<T> _expectedFloatingMat;
    fgm::Mat3x4<T> _expectedIntegralMat;



    void SetUp() override
    {
        _mat    = { fgm::Vec3{ T(7), T(13), T(11) }, fgm::Vec3{ T(5), T(4), T(2) }, fgm::Vec3{ T(15), T(41), T(22) },
                    fgm::Vec3{ T(55), T(41), T(13) } };
        _scalar = T(2.123456789123456);
        _expectedFloatingMat = { fgm::Vec3{ T(14.864197523864192), T(27.604938258604928), T(23.358024680358014) },
                                 fgm::Vec3{ T(10.61728394561728), T(8.493827156493824), T(4.246913578246912) },
                                 fgm::Vec3{ T(31.85185183685184), T(87.0617283540617), T(46.71604936071603) },
                                 fgm::Vec3{ T(116.79012340179007), T(87.0617283540617), T(27.60493825860493) } };
        _expectedIntegralMat = { fgm::Vec3{ T(14), T(26), T(22) }, fgm::Vec3{ T(10), T(8), T(4) },
                                 fgm::Vec3{ T(30), T(82), T(44) }, fgm::Vec3{ T(110), T(82), T(26) } };
    }
};
/** @brief Test fixture for @ref fgm::Mat3x4 scalar multiplication, parameterized by @ref SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Mat3x4ScalarMultiplication, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Mat3x4_Multiplication
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
    constexpr fgm::Mat3x4 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);

    // Verify matrix * scalar multiplication
    constexpr fgm::Mat3x4 BINARY_PRODUCT_1 = MAT1 * 2;
    static_assert(BINARY_PRODUCT_1(0, 0) == 2);
    static_assert(BINARY_PRODUCT_1(0, 1) == 4);
    static_assert(BINARY_PRODUCT_1(0, 2) == 6);
    static_assert(BINARY_PRODUCT_1(0, 3) == 8);

    static_assert(BINARY_PRODUCT_1(1, 0) == 10);
    static_assert(BINARY_PRODUCT_1(1, 1) == 12);
    static_assert(BINARY_PRODUCT_1(1, 2) == 14);
    static_assert(BINARY_PRODUCT_1(1, 3) == 16);

    static_assert(BINARY_PRODUCT_1(2, 0) == 18);
    static_assert(BINARY_PRODUCT_1(2, 1) == 20);
    static_assert(BINARY_PRODUCT_1(2, 2) == 22);
    static_assert(BINARY_PRODUCT_1(2, 3) == 24);


    // Verify scalar * matrix multiplication
    constexpr fgm::Mat3x4 BINARY_PRODUCT_2 = 2 * MAT1;
    static_assert(BINARY_PRODUCT_2(0, 0) == 2);
    static_assert(BINARY_PRODUCT_2(0, 1) == 4);
    static_assert(BINARY_PRODUCT_2(0, 2) == 6);
    static_assert(BINARY_PRODUCT_2(0, 3) == 8);

    static_assert(BINARY_PRODUCT_2(1, 0) == 10);
    static_assert(BINARY_PRODUCT_2(1, 1) == 12);
    static_assert(BINARY_PRODUCT_2(1, 2) == 14);
    static_assert(BINARY_PRODUCT_2(1, 3) == 16);

    static_assert(BINARY_PRODUCT_2(2, 0) == 18);
    static_assert(BINARY_PRODUCT_2(2, 1) == 20);
    static_assert(BINARY_PRODUCT_2(2, 2) == 22);
    static_assert(BINARY_PRODUCT_2(2, 3) == 24);

} // namespace



/**************************************
 *                                    *
 *     SCALAR MULTIPLICATION TESTS    *
 *                                    *
 **************************************/

/** @brief Verify that scalar multiplication by zero returns a zero matrix. */
TEST(Mat3x4ScalarMultiplication, MultiplicationByZeroReturnsZeroMatrix)
{
    const fgm::Mat3x4 mat(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f);

    const fgm::Mat3x4 product = mat * 0;

    EXPECT_MAT_ZERO(product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Mat3x4ScalarMultiplication, MultiplicationByOneReturnsOriginalMatrix)
{
    const fgm::Mat3x4 mat(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f);

    const fgm::Mat3x4 product = mat * 1;

    EXPECT_MAT_EQ(mat, product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Mat3x4ScalarMultiplication, MultiplicationByNegativeScalarFlipsSigns)
{
    const fgm::Mat3x4 mat      = { 1.0f, -2.0f, -4.0f, 5.0f, 10.0f, -1.0f, 3.5f, 4.0f, 12.5f, -1.0f, 33.0f, 12.0f };
    const fgm::Mat3x4 expected = { -2.0f, 4.0f, 8.0f, -10.0f, -20.f, 2.0f, 7.0f, 8.0f, 25.0f, -2.0f, 66.0f, 24.0f };
    const float scalar         = -2.0f;

    const fgm::Mat3x4<float> product = mat * scalar;

    EXPECT_MAT_EQ(expected, product);
}


/**
 * @brief Verify that the binary multiplication operator (matrix * scalar) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Mat3x4ScalarMultiplication, MatrixTimesScalarReturnsScaledMatrix)
{
    const fgm::Mat3x4 product = this->_mat * this->_scalar;

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
TYPED_TEST(Mat3x4ScalarMultiplication, ScalarTimesAMatrixReturnsScaledMatrix)
{
    const fgm::Mat3x4 product = this->_scalar * this->_mat;

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
TYPED_TEST(Mat3x4ScalarMultiplication, MatrixTimesEqualScalarIsTheSameMatrixScaled)
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
TYPED_TEST(Mat3x4ScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Mat3x4 product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}


/**
 * @brief Verify that the compound multiplication assignment operator (scalar) maintains the destination type and
 *        perform an implicit cast.
 */
TEST(Mat3x4ScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Mat3x4 mat(3.0f, -1.0f, -12.0f, 14.0f, 12.0f, 3.2f, 3.0f, -1.0f, -12.0f, 14.0f, 12.0f, 3.2f);
    const double scalar = 5.0;
    mat *= scalar;

    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


/**
 * @brief Verify that the compound multiplication operator (scalar) for mixed type
 *        ensure minimal precision loss.
 */
TEST(Mat3x4ScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    fgm::Mat3x4 mat(3, -1, 10, 5, 50, 12, 1, 0, 22, 12, 5, 11);
    const double scalar = 2.5;
    const fgm::Mat3x4 expected(7, -2, 25, 12, 125, 30, 2, 0, 55, 30, 12, 27);

    mat *= scalar;

    EXPECT_MAT_EQ(expected, mat);
}

/** @} */
