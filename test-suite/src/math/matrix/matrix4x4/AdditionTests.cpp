/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 04, 2026
 *
 * @brief Verify @ref fgm::Matrix4D addition logic.
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
class Matrix4DAddition: public ::testing::Test
{
protected:
    fgm::Matrix4D<T> _matA;
    fgm::Matrix4D<T> _matB;
    fgm::Matrix4D<T> _expectedSum;

    void SetUp() override
    {
        _matA = { fgm::Vector4D<T>{ 1, 2, 3 }, fgm::Vector4D<T>{ 4, 5, 6 }, fgm::Vector4D<T>{ 7, 8, 9 } };
        _matB = { fgm::Vector4D<T>{ 10, 11, 12 }, fgm::Vector4D<T>{ 13, 14, 15 }, fgm::Vector4D<T>{ 16, 17, 18 } };
        _expectedSum = { fgm::Vector4D<T>{ 11, 13, 15 }, fgm::Vector4D<T>{ 17, 19, 21 },
                         fgm::Vector4D<T>{ 23, 25, 27 } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix4D addition, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix4DAddition, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat3x3_Addition
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
    constexpr fgm::Matrix4D MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    constexpr fgm::Matrix4D MAT2(5, 6, 7, 8, 9, 10, 11, 12, 13);
    constexpr fgm::Matrix4D BINARY_SUM = MAT1 + MAT2;

    static_assert(BINARY_SUM(0, 0) == 6);
    static_assert(BINARY_SUM(0, 1) == 8);
    static_assert(BINARY_SUM(0, 2) == 10);
    static_assert(BINARY_SUM(1, 0) == 12);
    static_assert(BINARY_SUM(1, 1) == 14);
    static_assert(BINARY_SUM(1, 2) == 16);
    static_assert(BINARY_SUM(2, 0) == 18);
    static_assert(BINARY_SUM(2, 1) == 20);
    static_assert(BINARY_SUM(2, 2) == 22);

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @test Verify that the binary addition operator perform a component-wise addition and
 *       returns a new matrix instance.
 */
TYPED_TEST(Matrix4DAddition, PlusOperator_ReturnsMatrixSum)
{
    const fgm::Matrix4D sum = this->_matA + this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


/**
 * @test Verify that the binary addition operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Matrix4DAddition, MixedTypeAdditionPromotesType)
{
    constexpr fgm::Matrix4D mat1{ fgm::Vector4D{ 1.0f, 2.0f, 3.0f }, fgm::Vector4D{ -3.0f, -4.0f, 10.0f }, fgm::Vector4D{4.5f, 3.25f, 3.16f} };
    constexpr fgm::Matrix4D mat2{ fgm::Vector4D{ 10.0, 2.0, -1.0 }, fgm::Vector4D{ 3.0, -8.0, 12.0 }, fgm::Vector4D {3.25, 5.1, 0.0} };
    [[maybe_unused]] constexpr fgm::Matrix4D sum = mat1 + mat2;

    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


/**
 * @test Verify that the compound addition assignment operator perform a component-wise addition and
 *       mutates the matrix in-place.
 */
TYPED_TEST(Matrix4DAddition, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


/**
 * @test Verify that the compound addition assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Matrix4DAddition, MixedTypeAdditionAssignmentDoesNotPromoteType)
{
    fgm::Matrix4D mat1{ fgm::Vector4D{ 1.0f, 2.0f, 3.0f }, fgm::Vector4D{ -3.0f, -4.0f, 10.0f },
                                  fgm::Vector4D{ 4.5f, 3.25f, 3.16f } };
    constexpr fgm::Matrix4D mat2{ fgm::Vector4D{ 10.0, 2.0, -1.0 }, fgm::Vector4D{ 3.0, -8.0, 12.0 },
                                  fgm::Vector4D{ 3.25, 5.1, 0.0 } };

    mat1 += mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */