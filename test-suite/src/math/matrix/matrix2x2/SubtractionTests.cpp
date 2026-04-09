/**
 * @file SubtractionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 09, 2026
 *
 * @brief Verifies @ref fgm::Matrix2D subtraction logic.
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
class Matrix2DSubtraction: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _matA;
    fgm::Matrix2D<T> _matB;
    fgm::Matrix2D<T> _expectedDifference;

    void SetUp() override
    {
        _matA = { fgm::Vector2D<T>(5, 6), fgm::Vector2D<T>(7, 8) };
        _matB = { fgm::Vector2D<T>(1, 2), fgm::Vector2D<T>(3, 4) };
        _expectedDifference = { fgm::Vector2D<T>(4, 4), fgm::Vector2D<T>(4, 4) };
    }
};
/** @brief Test fixture for @ref fgm::Matrix2D subtraction, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix2DSubtraction, SupportedArithmeticTypes);


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
    constexpr fgm::Matrix2D s_Mat1(8, 2, 12, 4);
    constexpr fgm::Matrix2D s_Mat2(5, 6, 7, 8);
    constexpr fgm::Matrix2D s_BinaryDiff = s_Mat1 - s_Mat2;

    static_assert(s_BinaryDiff(0, 0) == 3);
    static_assert(s_BinaryDiff(0, 1) == -4);
    static_assert(s_BinaryDiff(1, 0) == 5);
    static_assert(s_BinaryDiff(1, 1) == -4);

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @test Verify that the binary subtraction operator perform an element-wise subtraction and
 *       returns a new matrix instance.
 */
TYPED_TEST(Matrix2DSubtraction, MinusOperator_ReturnsDifference)
{
    const fgm::Matrix2D difference = this->_matA - this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, difference);
}


/**
 * @test Verify that the binary subtraction operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Matrix2DSubtraction, MixedTypeSubtractionPromotesType)
{
    constexpr fgm::Matrix2D mat1(3.0f, -1.0f, 4.0f, -23.0f);
    constexpr fgm::Matrix2D mat2(9.0, 10.0, 3.0, 4.0);

    [[maybe_unused]] constexpr fgm::Matrix2D difference = mat1 - mat2;

    static_assert(std::is_same_v<decltype(difference)::value_type, double>);
}


/**
 * @test Verify that the compound subtraction assignment operator perform an element-wise subtraction
 *       and mutates the matrix in-place.
 */
TYPED_TEST(Matrix2DSubtraction, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_matA -= this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, this->_matA);
}


/**
 * @test Verify that the compound subtraction assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Matrix2DSubtraction, MixedTypeSubtractionAssignmentDoesNotPromoteType)
{
    fgm::Matrix2D mat1(3.0f, -1.0f, 4.0f, -23.0f);
    constexpr fgm::Matrix2D mat2(9.0, 10.0, 3.0, 4.0);

    mat1 -= mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */