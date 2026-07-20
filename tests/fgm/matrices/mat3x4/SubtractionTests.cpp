/**
 * @file SubtractionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref fgm::Mat3x4 subtraction logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x4TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat3x4Subtraction: public ::testing::Test
{
protected:
    fgm::Mat3x4<T> _matA;
    fgm::Mat3x4<T> _matB;
    fgm::Mat3x4<T> _expectedDifference;

    void SetUp() override
    {
        _matA = { fgm::Vec3<T>(5, 6, 5), fgm::Vec3<T>(7, 8, 12), fgm::Vec3<T>(17, 81, 22), fgm::Vec3<T>(22, 32, 11) };
        _matB = { fgm::Vec3<T>(1, 2, 5), fgm::Vec3<T>(3, 4, 11), fgm::Vec3<T>(0, 1, 19), fgm::Vec3<T>(21, 14, 11) };
        _expectedDifference = { fgm::Vec3<T>(4, 4, 0), fgm::Vec3<T>(4, 4, 1), fgm::Vec3<T>(17, 80, 3),
                                fgm::Vec3<T>(1, 18, 0) };
    }
};
/** @brief Test fixture for @ref fgm::Mat3x4 subtraction, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Mat3x4Subtraction, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Mat2x2_Subtraction
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that matrix subtraction operations are available at compile time. */
namespace
{
    constexpr fgm::Mat3x4 MAT1(8, 2, 12, 4, -5, 0, -12, 5, 11, 23, 11, 5);
    constexpr fgm::Mat3x4 MAT2(5, 6, 7, 8, -11, 5, -12, -5, 0, 2, -1, -3);
    constexpr fgm::Mat3x4 BINARY_DIFF = MAT1 - MAT2;

    static_assert(BINARY_DIFF(0, 0) == 3);
    static_assert(BINARY_DIFF(0, 1) == -4);
    static_assert(BINARY_DIFF(0, 2) == 5);
    static_assert(BINARY_DIFF(0, 3) == -4);
    static_assert(BINARY_DIFF(1, 0) == 6);
    static_assert(BINARY_DIFF(1, 1) == -5);
    static_assert(BINARY_DIFF(1, 2) == 0);
    static_assert(BINARY_DIFF(1, 3) == 10);
    static_assert(BINARY_DIFF(2, 0) == 11);
    static_assert(BINARY_DIFF(2, 1) == 21);
    static_assert(BINARY_DIFF(2, 2) == 12);
    static_assert(BINARY_DIFF(2, 3) == 8);

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @brief Verify that the binary subtraction operator perform an element-wise subtraction and
 *       returns a new matrix instance.
 */
TYPED_TEST(Mat3x4Subtraction, MinusOperator_ReturnsDifference)
{
    const fgm::Mat3x4 difference = this->_matA - this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, difference);
}


/**
 * @brief Verify that the binary subtraction operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Mat3x4Subtraction, MixedTypeSubtractionPromotesType)
{
    const fgm::Mat3x4 mat1(3.0f, -1.0f, 4.0f, -23.0f, 5.0f, 3.0f, 1.2f, 2.25f, 3.0f, 15.0f, 22.0f, 1.0f);
    const fgm::Mat3x4 mat2(9.0, 10.0, 3.0, 4.0, 0.1, 2.5, 0.5, 1.25, 22.0, 3.15, 15.0, 11.0);

    [[maybe_unused]] const fgm::Mat3x4 difference = mat1 - mat2;

    static_assert(std::is_same_v<decltype(difference)::value_type, double>);
}


/**
 * @brief Verify that the compound subtraction assignment operator perform an element-wise subtraction
 *       and mutates the matrix in-place.
 */
TYPED_TEST(Mat3x4Subtraction, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_matA -= this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, this->_matA);
}


/**
 * @brief Verify that the compound subtraction assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Mat3x4Subtraction, MixedTypeSubtractionAssignmentDoesNotPromoteType)
{
    fgm::Mat3x4 mat1(3.0f, -1.0f, 4.0f, -23.0f, 5.0f, 3.0f, 1.2f, 2.25f, 3.0f, 15.0f, 22.0f, 1.0f);
    [[maybe_unused]] const fgm::Mat3x4 mat2(9.0, 10.0, 3.0, 4.0, 0.1, 2.5, 0.5, 1.25, 22.0, 3.15, 15.0, 11.0);

    mat1 -= mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
