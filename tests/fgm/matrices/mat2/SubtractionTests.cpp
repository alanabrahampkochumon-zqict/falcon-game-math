/**
 * @file SubtractionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 09, 2026
 *
 * @brief Verify @ref fgm::Mat2 subtraction logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat2Subtraction: public ::testing::Test
{
protected:
    fgm::Mat2<T> _matA;
    fgm::Mat2<T> _matB;
    fgm::Mat2<T> _expectedDifference;

    void SetUp() override
    {
        _matA               = { fgm::Vec2<T>(5, 6), fgm::Vec2<T>(7, 8) };
        _matB               = { fgm::Vec2<T>(1, 2), fgm::Vec2<T>(3, 4) };
        _expectedDifference = { fgm::Vec2<T>(4, 4), fgm::Vec2<T>(4, 4) };
    }
};
/** @brief Test fixture for @ref fgm::Mat2 subtraction, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Mat2Subtraction, SupportedArithmeticTypes);


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
    constexpr fgm::Mat2 MAT1(8, 2, 12, 4);
    constexpr fgm::Mat2 MAT2(5, 6, 7, 8);
    constexpr fgm::Mat2 BINARY_DIFF = MAT1 - MAT2;

    static_assert(BINARY_DIFF(0, 0) == 3);
    static_assert(BINARY_DIFF(0, 1) == -4);
    static_assert(BINARY_DIFF(1, 0) == 5);
    static_assert(BINARY_DIFF(1, 1) == -4);

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
TYPED_TEST(Mat2Subtraction, MinusOperator_ReturnsDifference)
{
    const fgm::Mat2 difference = this->_matA - this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, difference);
}


/**
 * @brief Verify that the binary subtraction operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Mat2Subtraction, MixedTypeSubtractionPromotesType)
{
    const fgm::Mat2 mat1(3.0f, -1.0f, 4.0f, -23.0f);
    const fgm::Mat2 mat2(9.0, 10.0, 3.0, 4.0);

    [[maybe_unused]] const fgm::Mat2 difference = mat1 - mat2;

    static_assert(std::is_same_v<decltype(difference)::value_type, double>);
}


/**
 * @brief Verify that the compound subtraction assignment operator perform an element-wise subtraction
 *       and mutates the matrix in-place.
 */
TYPED_TEST(Mat2Subtraction, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_matA -= this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, this->_matA);
}


/**
 * @brief Verify that the compound subtraction assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Mat2Subtraction, MixedTypeSubtractionAssignmentDoesNotPromoteType)
{
    fgm::Mat2 mat1(3.0f, -1.0f, 4.0f, -23.0f);
    const fgm::Mat2 mat2(9.0, 10.0, 3.0, 4.0);

    mat1 -= mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
