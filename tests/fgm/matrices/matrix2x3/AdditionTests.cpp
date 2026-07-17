/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref fgm:: Matrix2x3 addition logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Matrix2x3TestSetup.h>

/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Matrix2x3Addition: public ::testing::Test
{
protected:
    fgm::Matrix2x3<T> _matA;
    fgm::Matrix2x3<T> _matB;
    fgm::Matrix2x3<T> _expectedSum;

    void SetUp() override
    {
        _matA        = { fgm::Vector2<T>(1, 2), fgm::Vector2<T>(3, 4), fgm::Vector2<T>(4, 6) };
        _matB        = { fgm::Vector2<T>(5, 6), fgm::Vector2<T>(7, 8), fgm::Vector2<T>(1, 3) };
        _expectedSum = { fgm::Vector2<T>(6, 8), fgm::Vector2<T>(10, 12), fgm::Vector2<T>(5, 9) };
    }
};
/** @brief Test fixture for @ref fgm:: Matrix2x3 addition, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix2x3Addition, SupportedArithmeticTypes);



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
    constexpr fgm::Matrix2x3 MAT1(1, 2, 3, 4, 5, 6);
    constexpr fgm::Matrix2x3 MAT2(5, 6, 7, 8, 10, 11);
    constexpr fgm::Matrix2x3 BINARY_SUM = MAT1 + MAT2;

    static_assert(BINARY_SUM(0, 0) == 6);
    static_assert(BINARY_SUM(0, 1) == 8);
    static_assert(BINARY_SUM(0, 2) == 10);
    static_assert(BINARY_SUM(1, 0) == 12);
    static_assert(BINARY_SUM(1, 1) == 15);
    static_assert(BINARY_SUM(1, 2) == 17);

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @brief Verify that the binary addition operator perform a component-wise addition and
 *       returns a new matrix instance.
 */
TYPED_TEST(Matrix2x3Addition, PlusOperator_ReturnsMatrixSum)
{
    const fgm::Matrix2x3 sum = this->_matA + this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


/**
 * @brief Verify that the binary addition operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Matrix2x3Addition, MixedTypeAdditionPromotesType)
{
    const fgm::Matrix2x3 mat1{ fgm::Vector2{ 1.0f, 2.0f }, fgm::Vector2{ -3.0f, -4.0f }, fgm::Vector2{ 5.0f, 12.0f } };
    const fgm::Matrix2x3 mat2{ fgm::Vector2{ 10.0, 2.0 }, fgm::Vector2{ 3.0, 8.0 }, fgm::Vector2{ -2.0, -12.0 } };
    [[maybe_unused]] const fgm::Matrix2x3 sum = mat1 + mat2;

    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


/**
 * @brief Verify that the compound addition assignment operator perform a component-wise addition and
 *       mutates the matrix in-place.
 */
TYPED_TEST(Matrix2x3Addition, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


/**
 * @brief Verify that the compound addition assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Matrix2x3Addition, PlusEqualsOperator_MixedTypeDoesNotPromoteType)
{
    fgm::Matrix2x3 mat1{ fgm::Vector2{ 1.0f, 2.0f }, fgm::Vector2{ -3.0f, -4.0f }, fgm::Vector2{ 5.0f, 12.0f } };
    const fgm::Matrix2x3 mat2{ fgm::Vector2{ 10.0, 2.0 }, fgm::Vector2{ 3.0, 8.0 }, fgm::Vector2{ -2.0, -12.0 } };

    mat1 += mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
