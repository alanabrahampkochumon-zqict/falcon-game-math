/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 09, 2026
 *
 * @brief Verifies @ref fgm::Matrix2D addition logic.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <MatrixTestSetup.h>

/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Matrix2DAddition: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _matA;
    fgm::Matrix2D<T> _matB;
    fgm::Matrix2D<T> _expectedSum;

    void SetUp() override
    {
        _matA = { fgm::Vector2D<T>(1, 2), fgm::Vector2D<T>(3, 4) };
        _matB = { fgm::Vector2D<T>(5, 6), fgm::Vector2D<T>(7, 8) };
        _expectedSum = { fgm::Vector2D<T>(6, 8), fgm::Vector2D<T>(10, 12) };
    }
};
/** @brief Test fixture for @ref fgm::Matrix2D addition, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix2DAddition, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Addition
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that matrix addition operations are available at compile time. */
namespace 
{
    constexpr fgm::Matrix2D s_Mat1(1, 2, 3, 4);
    constexpr fgm::Matrix2D s_Mat2(5, 6, 7, 8);
    constexpr fgm::Matrix2D s_BinarySum = s_Mat1 + s_Mat2;

    static_assert(s_BinarySum(0, 0) == 6);
    static_assert(s_BinarySum(0, 1) == 8);
    static_assert(s_BinarySum(1, 0) == 10);
    static_assert(s_BinarySum(1, 1) == 12);

}


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @test Verify that the binary addition operator perform a component-wise addition and
 *       returns a new matrix instance.
 */
TYPED_TEST(Matrix2DAddition, PlusOperator_ReturnsMatrixSum)
{
    const fgm::Matrix2D sum = this->_matA + this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


/**
 * @test Verify that the binary addition operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Matrix2DAddition, MixedTypeAdditionPromotesType)
{
    constexpr fgm::Matrix2D mat1{ fgm::Vector2D{ 1.0f, 2.0f }, fgm::Vector2D{ -3.0f, -4.0f } };
    constexpr fgm::Matrix2D mat2{ fgm::Vector2D{ 10.0, 2.0 }, fgm::Vector2D{ 3.0, 8.0 } };
    [[maybe_unused]] constexpr fgm::Matrix2D sum = mat1 + mat2;

    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


/**
 * @test Verify that the compound addition assignment operator perform a component-wise addition and
 *       mutates the matrix in-place.
 */
 TYPED_TEST(Matrix2DAddition, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
     this->_matA += this->_matB;

     EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
 }


/**
 * @test Verify that the compound addition assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Matrix2DAddition, MixedTypeAdditionAssignmentDoesNotPromoteType)
{
    fgm::Matrix2D mat1{ fgm::Vector2D{ 1.0f, 2.0f }, fgm::Vector2D{ -3.0f, -4.0f } };
    constexpr fgm::Matrix2D mat2{ fgm::Vector2D{ 10.0, 2.0 }, fgm::Vector2D{ 3.0, 8.0 } };

    mat1 += mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */