/**
 * @file SubtractionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref fgm::Mat4x3 subtraction logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x3TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat4x3Subtraction: public ::testing::Test
{
protected:
    fgm::Mat4x3<T> _matA;
    fgm::Mat4x3<T> _matB;
    fgm::Mat4x3<T> _expectedDifference;

    void SetUp() override
    {
        _matA               = { fgm::Vec4<T>(5, 6, 5, 7), fgm::Vec4<T>(7, 8, 12, 21), fgm::Vec4<T>(3, 4, 11, 12) };
        _matB               = { fgm::Vec4<T>(1, 2, 5, 5), fgm::Vec4<T>(3, 4, 11, 12), fgm::Vec4<T>(3, 1, 2, 5) };
        _expectedDifference = { fgm::Vec4<T>(4, 4, 0, 2), fgm::Vec4<T>(4, 4, 1, 9), fgm::Vec4<T>(0, 3, 9, 7) };
    }
};
/** @brief Test fixture for @ref fgm::Mat4x3 subtraction, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Mat4x3Subtraction, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Mat4x3_Subtraction
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
    constexpr fgm::Mat4x3 MAT1(8, 2, 12, 4, -5, 0, -1, 0, 1, 5, 2, 3);
    constexpr fgm::Mat4x3 MAT2(5, 6, 7, 8, -11, 5, 5, -32, -1, 5, 2, -5);
    constexpr fgm::Mat4x3 BINARY_DIFF = MAT1 - MAT2;

    static_assert(BINARY_DIFF(0, 0) == 3);
    static_assert(BINARY_DIFF(0, 1) == -4);
    static_assert(BINARY_DIFF(0, 2) == 5);
    static_assert(BINARY_DIFF(1, 0) == -4);
    static_assert(BINARY_DIFF(1, 1) == 6);
    static_assert(BINARY_DIFF(1, 2) == -5);
    static_assert(BINARY_DIFF(2, 0) == -6);
    static_assert(BINARY_DIFF(2, 1) == 32);
    static_assert(BINARY_DIFF(2, 2) == 2);
    static_assert(BINARY_DIFF(3, 0) == 0);
    static_assert(BINARY_DIFF(3, 1) == 0);
    static_assert(BINARY_DIFF(3, 2) == 8);

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
TYPED_TEST(Mat4x3Subtraction, MinusOperator_ReturnsDifference)
{
    const fgm::Mat4x3 difference = this->_matA - this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, difference);
}


/**
 * @brief Verify that the binary subtraction operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Mat4x3Subtraction, MixedTypeSubtractionPromotesType)
{
    const fgm::Mat4x3 mat1(3.0f, -1.0f, 4.0f, -23.0f, 5.0f, 3.0f, 1.5f, 2.0f, 5.0f, 3.0f, 1.5f, 2.0f);
    const fgm::Mat4x3 mat2(9.0, 10.0, 3.0, 4.0, 0.1, 2.5, 1.0, 2.25, 0.1, 2.5, 1.0, 2.25);

    [[maybe_unused]] const fgm::Mat4x3 difference = mat1 - mat2;

    static_assert(std::is_same_v<decltype(difference)::value_type, double>);
}


/**
 * @brief Verify that the compound subtraction assignment operator perform an element-wise subtraction
 *       and mutates the matrix in-place.
 */
TYPED_TEST(Mat4x3Subtraction, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_matA -= this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, this->_matA);
}


/**
 * @brief Verify that the compound subtraction assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Mat4x3Subtraction, MixedTypeSubtractionAssignmentDoesNotPromoteType)
{
    fgm::Mat4x3 mat1(3.0f, -1.0f, 4.0f, -23.0f, 5.0f, 3.0f, 1.5f, 2.0f, 5.0f, 3.0f, 1.5f, 2.0f);
    [[maybe_unused]] const fgm::Mat4x3 mat2(9.0, 10.0, 3.0, 4.0, 0.1, 2.5, 1.0, 2.25, 0.1, 2.5, 1.0, 2.25);

    mat1 -= mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
