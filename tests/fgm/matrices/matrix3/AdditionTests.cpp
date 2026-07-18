/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 24, 2026
 *
 * @brief Verify @ref fgm::Matrix3 addition logic.
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
class Matrix3Addition: public ::testing::Test
{
protected:
    fgm::Matrix3<T> _matA;
    fgm::Matrix3<T> _matB;
    fgm::Matrix3<T> _expectedSum;

    void SetUp() override
    {
        _matA        = { fgm::Vec3<T>{ 1, 2, 3 }, fgm::Vec3<T>{ 4, 5, 6 }, fgm::Vec3<T>{ 7, 8, 9 } };
        _matB        = { fgm::Vec3<T>{ 10, 11, 12 }, fgm::Vec3<T>{ 13, 14, 15 }, fgm::Vec3<T>{ 16, 17, 18 } };
        _expectedSum = { fgm::Vec3<T>{ 11, 13, 15 }, fgm::Vec3<T>{ 17, 19, 21 }, fgm::Vec3<T>{ 23, 25, 27 } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix3 addition, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix3Addition, SupportedArithmeticTypes);



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
    constexpr fgm::Matrix3 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    constexpr fgm::Matrix3 MAT2(5, 6, 7, 8, 9, 10, 11, 12, 13);
    constexpr fgm::Matrix3 BINARY_SUM = MAT1 + MAT2;

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
 * @brief Verify that the binary addition operator perform a component-wise addition and
 *       returns a new matrix instance.
 */
TYPED_TEST(Matrix3Addition, PlusOperator_ReturnsMatrixSum)
{
    const fgm::Matrix3 sum = this->_matA + this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


/**
 * @brief Verify that the binary addition operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Matrix3Addition, PlusOperator_MixedTypePromotesType)
{
    const fgm::Matrix3 mat1{ fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ -3.0f, -4.0f, 10.0f },
                             fgm::Vec3{ 4.5f, 3.25f, 3.16f } };
    const fgm::Matrix3 mat2{ fgm::Vec3{ 10.0, 2.0, -1.0 }, fgm::Vec3{ 3.0, -8.0, 12.0 },
                             fgm::Vec3{ 3.25, 5.1, 0.0 } };
    [[maybe_unused]] const fgm::Matrix3 sum = mat1 + mat2;

    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


/**
 * @brief Verify that the compound addition assignment operator perform a component-wise addition and
 *       mutates the matrix in-place.
 */
TYPED_TEST(Matrix3Addition, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


/**
 * @brief Verify that the compound addition assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Matrix3Addition, PlusEqualsOperator_MixedTypeDoesNotPromoteType)
{
    fgm::Matrix3 mat1{ fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ -3.0f, -4.0f, 10.0f },
                       fgm::Vec3{ 4.5f, 3.25f, 3.16f } };
    constexpr fgm::Matrix3 mat2{ fgm::Vec3{ 10.0, 2.0, -1.0 }, fgm::Vec3{ 3.0, -8.0, 12.0 },
                                 fgm::Vec3{ 3.25, 5.1, 0.0 } };

    mat1 += mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
