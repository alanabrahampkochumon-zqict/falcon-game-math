/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref fgm::Mat3x2 addition logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Mat3x2TestSetup.h>

/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat3x2Addition: public ::testing::Test
{
protected:
    fgm::Mat3x2<T> _matA;
    fgm::Mat3x2<T> _matB;
    fgm::Mat3x2<T> _expectedSum;

    void SetUp() override
    {
        _matA        = { fgm::Vec3<T>(1, 2, 3), fgm::Vec3<T>(4, 5, 6) };
        _matB        = { fgm::Vec3<T>(5, 6, 1), fgm::Vec3<T>(7, 8, 5) };
        _expectedSum = { fgm::Vec3<T>(6, 8, 4), fgm::Vec3<T>(11, 13, 11) };
    }
};
/** @brief Test fixture for @ref fgm::Mat3x2 addition, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Mat3x2Addition, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat3x2_Addition
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
    constexpr fgm::Mat3x2 MAT1(1, 2, 3, 4, 5, 6);
    constexpr fgm::Mat3x2 MAT2(5, 6, 7, 8, 10, 11);
    constexpr fgm::Mat3x2 BINARY_SUM = MAT1 + MAT2;

    static_assert(BINARY_SUM(0, 0) == 6);
    static_assert(BINARY_SUM(0, 1) == 8);
    static_assert(BINARY_SUM(1, 0) == 10);
    static_assert(BINARY_SUM(1, 1) == 12);
    static_assert(BINARY_SUM(2, 0) == 15);
    static_assert(BINARY_SUM(2, 1) == 17);

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
TYPED_TEST(Mat3x2Addition, PlusOperator_ReturnsMatrixSum)
{
    const fgm::Mat3x2 sum = this->_matA + this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


/**
 * @brief Verify that the binary addition operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Mat3x2Addition, MixedTypeAdditionPromotesType)
{
    const fgm::Mat3x2 mat1{ fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ -3.0f, -4.0f, 12.0f } };
    const fgm::Mat3x2 mat2{
        fgm::Vec3{ 10.0, 2.0, 2.5 },
        fgm::Vec3{ 3.0, 8.0, 3.5 },
    };
    [[maybe_unused]] const fgm::Mat3x2 sum = mat1 + mat2;

    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


/**
 * @brief Verify that the compound addition assignment operator perform a component-wise addition and
 *       mutates the matrix in-place.
 */
TYPED_TEST(Mat3x2Addition, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


/**
 * @brief Verify that the compound addition assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Mat3x2Addition, PlusEqualsOperator_MixedTypeDoesNotPromoteType)
{
    fgm::Mat3x2 mat1{ fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ -3.0f, -4.0f, 12.0f } };
    const fgm::Mat3x2 mat2{
        fgm::Vec3{ 10.0, 2.0, 2.5 },
        fgm::Vec3{ 3.0, 8.0, 3.5 },
    };
    mat1 += mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
