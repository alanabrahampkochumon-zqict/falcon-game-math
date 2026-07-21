/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref fgm::Mat4x3 scalar multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x3TestSetup.h"


template <typename T>
class Mat4x3ScalarMultiplication: public ::testing::Test
{
protected:
    fgm::Mat4x3<T> _mat;
    T _scalar;
    fgm::Mat4x3<T> _expectedFloatingMat;
    fgm::Mat4x3<T> _expectedIntegralMat;



    void SetUp() override
    {
        _mat                 = { fgm::Vec4{ T(7), T(13), T(11), T(22) }, fgm::Vec4{ T(5), T(4), T(2), T(12) },
                                 fgm::Vec4{ T(11), T(3), T(5), T(1) } };
        _scalar              = T(2.123456789123456);
        _expectedFloatingMat = {
            fgm::Vec4{ T(14.864197523864192), T(27.604938258604928), T(23.358024680358014), T(46.71604936071603) },
            fgm::Vec4{ T(10.61728394561728), T(8.493827156493824), T(4.246913578246912), T(25.481481469481473) },
            fgm::Vec4{ T(23.358024680358014), T(6.370370367370368), T(10.61728394561728), T(2.123456789123456) }
        };
        _expectedIntegralMat = { fgm::Vec4{ T(14), T(26), T(22), T(44) }, fgm::Vec4{ T(10), T(8), T(4), T(24) },
                                 fgm::Vec4{ T(22), T(6), T(10), T(2) } };
    }
};
/** @brief Test fixture for @ref fgm::Mat4x3 scalar multiplication, parameterized by @ref SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Mat4x3ScalarMultiplication, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Mat4x3_Multiplication
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
    constexpr fgm::Mat4x3 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);

    // Verify matrix * scalar multiplication
    constexpr fgm::Mat4x3 BINARY_PRODUCT_1 = MAT1 * 2;
    static_assert(BINARY_PRODUCT_1(0, 0) == 2);
    static_assert(BINARY_PRODUCT_1(0, 1) == 4);
    static_assert(BINARY_PRODUCT_1(0, 2) == 6);
    static_assert(BINARY_PRODUCT_1(1, 0) == 8);
    static_assert(BINARY_PRODUCT_1(1, 1) == 10);
    static_assert(BINARY_PRODUCT_1(1, 2) == 12);
    static_assert(BINARY_PRODUCT_1(2, 0) == 14);
    static_assert(BINARY_PRODUCT_1(2, 1) == 16);
    static_assert(BINARY_PRODUCT_1(2, 2) == 18);
    static_assert(BINARY_PRODUCT_1(3, 0) == 20);
    static_assert(BINARY_PRODUCT_1(3, 1) == 22);
    static_assert(BINARY_PRODUCT_1(3, 2) == 24);


    // Verify scalar * matrix multiplication
    constexpr fgm::Mat4x3 BINARY_PRODUCT_2 = 2 * MAT1;
    static_assert(BINARY_PRODUCT_2(0, 0) == 2);
    static_assert(BINARY_PRODUCT_2(0, 1) == 4);
    static_assert(BINARY_PRODUCT_2(0, 2) == 6);
    static_assert(BINARY_PRODUCT_2(1, 0) == 8);
    static_assert(BINARY_PRODUCT_2(1, 1) == 10);
    static_assert(BINARY_PRODUCT_2(1, 2) == 12);
    static_assert(BINARY_PRODUCT_2(2, 0) == 14);
    static_assert(BINARY_PRODUCT_2(2, 1) == 16);
    static_assert(BINARY_PRODUCT_2(2, 2) == 18);
    static_assert(BINARY_PRODUCT_2(3, 0) == 20);
    static_assert(BINARY_PRODUCT_2(3, 1) == 22);
    static_assert(BINARY_PRODUCT_2(3, 2) == 24);

} // namespace



/**************************************
 *                                    *
 *     SCALAR MULTIPLICATION TESTS    *
 *                                    *
 **************************************/

/** @brief Verify that scalar multiplication by zero returns a zero matrix. */
TEST(Mat4x3ScalarMultiplication, MultiplicationByZeroReturnsZeroMatrix)
{
    const fgm::Mat4x3 mat(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f);

    const fgm::Mat4x3 product = mat * 0;

    EXPECT_MAT_ZERO(product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Mat4x3ScalarMultiplication, MultiplicationByOneReturnsOriginalMatrix)
{
    const fgm::Mat4x3 mat(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f);

    const fgm::Mat4x3 product = mat * 1;

    EXPECT_MAT_EQ(mat, product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Mat4x3ScalarMultiplication, MultiplicationByNegativeScalarFlipsSigns)
{
    const fgm::Mat4x3 mat      = { 1.0f, -2.0f, -4.0f, 5.0f, 10.0f, -1.0f, -1.5f, 2.25f, 5.0f, 10.0f, -1.0f, -1.5f };
    const fgm::Mat4x3 expected = { -2.0f, 4.0f, 8.0f, -10.0f, -20.f, 2.0f, 3.0f, 4.5f, -10.0f, -20.f, 2.0f, 3.0f };
    const float scalar         = -2.0f;

    const fgm::Mat4x3<float> product = mat * scalar;

    EXPECT_MAT_EQ(expected, product);
}


/**
 * @brief Verify that the binary multiplication operator (matrix * scalar) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Mat4x3ScalarMultiplication, MatrixTimesScalarReturnsScaledMatrix)
{
    const fgm::Mat4x3 product = this->_mat * this->_scalar;

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
TYPED_TEST(Mat4x3ScalarMultiplication, ScalarTimesAMatrixReturnsScaledMatrix)
{
    const fgm::Mat4x3 product = this->_scalar * this->_mat;

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
TYPED_TEST(Mat4x3ScalarMultiplication, MatrixTimesEqualScalarIsTheSameMatrixScaled)
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
TYPED_TEST(Mat4x3ScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Mat4x3 product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}


/**
 * @brief Verify that the compound multiplication assignment operator (scalar) maintains the destination type and
 *        perform an implicit cast.
 */
TEST(Mat4x3ScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Mat4x3 mat(3.0f, -1.0f, -12.0f, 14.0f, 12.0f, 3.2f, 2.1f, 0.75f, -10.0f, -20.f, 2.0f, 3.0f);
    const double scalar = 5.0;
    mat *= scalar;

    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


/**
 * @brief Verify that the compound multiplication operator (scalar) for mixed type
 *        ensure minimal precision loss.
 */
TEST(Mat4x3ScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    fgm::Mat4x3 mat(3, -1, 10, 5, 50, 12, 0, 5, 2, 4, 8, 10);
    const double scalar = 2.5;
    const fgm::Mat4x3 expected(7, -2, 25, 12, 125, 30, 0, 12, 5, 10, 20, 25);

    mat *= scalar;

    EXPECT_MAT_EQ(expected, mat);
}

/** @} */
