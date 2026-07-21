/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref fgm::Mat2x4 addition logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Mat2x4TestSetup.h>

/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat2x4Addition: public ::testing::Test
{
protected:
    fgm::Mat2x4<T> _matA;
    fgm::Mat2x4<T> _matB;
    fgm::Mat2x4<T> _expectedSum;

    void SetUp() override
    {
        _matA        = { fgm::Vec2<T>(1, 2), fgm::Vec2<T>(3, 4), fgm::Vec2<T>(4, 6), fgm::Vec2<T>(1, 2) };
        _matB        = { fgm::Vec2<T>(5, 6), fgm::Vec2<T>(7, 8), fgm::Vec2<T>(1, 3), fgm::Vec2<T>(3, 2) };
        _expectedSum = { fgm::Vec2<T>(6, 8), fgm::Vec2<T>(10, 12), fgm::Vec2<T>(5, 9), fgm::Vec2<T>(4, 4) };
    }
};
/** @brief Test fixture for @ref fgm::Mat2x4 addition, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Mat2x4Addition, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x4_Addition
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
    constexpr fgm::Mat2x4 MAT1(1, 2, 3, 4, 5, 6, 7, 8);
    constexpr fgm::Mat2x4 MAT2(5, 6, 7, 8, 10, 11, 12, 13);
    constexpr fgm::Mat2x4 BINARY_SUM = MAT1 + MAT2;

    static_assert(BINARY_SUM(0, 0) == 6);
    static_assert(BINARY_SUM(0, 1) == 8);
    static_assert(BINARY_SUM(0, 2) == 10);
    static_assert(BINARY_SUM(0, 3) == 12);
    static_assert(BINARY_SUM(1, 0) == 15);
    static_assert(BINARY_SUM(1, 1) == 17);
    static_assert(BINARY_SUM(1, 2) == 19);
    static_assert(BINARY_SUM(1, 3) == 21);

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
TYPED_TEST(Mat2x4Addition, PlusOperator_ReturnsMatrixSum)
{
    const fgm::Mat2x4 sum = this->_matA + this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


/**
 * @brief Verify that the binary addition operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Mat2x4Addition, MixedTypeAdditionPromotesType)
{
    const fgm::Mat2x4 mat1{ fgm::Vec2{ 1.0f, 2.0f }, fgm::Vec2{ -3.0f, -4.0f }, fgm::Vec2{ 5.0f, 12.0f }, fgm::Vec2{ 2.0f, 8.0f } };
    const fgm::Mat2x4 mat2{ fgm::Vec2{ 10.0, 2.0 }, fgm::Vec2{ 3.0, 8.0 }, fgm::Vec2{ -2.0, -12.0 }, fgm::Vec2{ 13.0, 3.0 } };
    [[maybe_unused]] const fgm::Mat2x4 sum = mat1 + mat2;

    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


/**
 * @brief Verify that the compound addition assignment operator perform a component-wise addition and
 *       mutates the matrix in-place.
 */
TYPED_TEST(Mat2x4Addition, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


/**
 * @brief Verify that the compound addition assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Mat2x4Addition, PlusEqualsOperator_MixedTypeDoesNotPromoteType)
{
    fgm::Mat2x4 mat1{ fgm::Vec2{ 1.0f, 2.0f }, fgm::Vec2{ -3.0f, -4.0f }, fgm::Vec2{ 5.0f, 12.0f }, fgm::Vec2{ 3.0f, 1.0f }};
    const fgm::Mat2x4 mat2{ fgm::Vec2{ 10.0, 2.0 }, fgm::Vec2{ 3.0, 8.0 }, fgm::Vec2{ -2.0, -12.0 }, fgm::Vec2{ 1.0, 6.0 } };

    mat1 += mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
