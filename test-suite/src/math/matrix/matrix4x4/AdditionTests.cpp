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
class Matrix4DAddition: public testing::Test
{
protected:
    fgm::Matrix4D<T> _matA;
    fgm::Matrix4D<T> _matB;
    fgm::Matrix4D<T> _expectedSum;

    void SetUp() override
    {
        _matA = { { T(1), T(2), T(3), T(4) },
                  { T(5), T(6), T(7), T(8) },
                  { T(9), T(10), T(11), T(12) },
                  { T(13), T(14), T(15), T(16) } };
        _matB = { { T(10), T(20), T(30), T(40) },
                  { T(50), T(60), T(70), T(80) },
                  { T(90), T(100), T(110), T(120) },
                  { T(130), T(140), T(150), T(160) } };
        _expectedSum = {
            { T(11), T(22), T(33), T(44) },
            { T(55), T(66), T(77), T(88) },
            { T(99), T(110), T(121), T(132) },
            { T(143), T(154), T(165), T(176) },
        };
    }
};
/** @brief Test fixture for @ref fgm::Matrix4D addition, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix4DAddition, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat4x4_Addition
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
    constexpr fgm::Matrix4D matA(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    constexpr fgm::Matrix4D matB(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
    constexpr fgm::Matrix4D binarySum = matA + matB;

    static_assert(binarySum(0, 0) == 6);
    static_assert(binarySum(0, 1) == 8);
    static_assert(binarySum(0, 2) == 10);
    static_assert(binarySum(0, 3) == 12);
    static_assert(binarySum(1, 0) == 14);
    static_assert(binarySum(1, 1) == 16);
    static_assert(binarySum(1, 2) == 18);
    static_assert(binarySum(1, 3) == 20);
    static_assert(binarySum(2, 0) == 22);
    static_assert(binarySum(2, 1) == 24);
    static_assert(binarySum(2, 2) == 26);
    static_assert(binarySum(2, 3) == 28);
    static_assert(binarySum(3, 0) == 30);
    static_assert(binarySum(3, 1) == 32);
    static_assert(binarySum(3, 2) == 34);
    static_assert(binarySum(3, 3) == 36);

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
    constexpr fgm::Matrix4D mat1{ fgm::Vector4D{ 1.0f, 2.0f, 3.0f, 7.5f }, fgm::Vector4D{ -3.0f, -4.0f, 10.0f, -11.0f },
                                  fgm::Vector4D{ 4.5f, 3.25f, 3.16f, -22.0f },
                                  fgm::Vector4D{ 15.0f, 32.0f, 101.0f, 12.5f } };
    constexpr fgm::Matrix4D mat2{ fgm::Vector4D{ 11.0, 10.0, 2.0, -1.0 }, fgm::Vector4D{ 3.0, -8.0, 12.0, 11.0 },
                                  fgm::Vector4D{ 3.25, 5.1, 0.0, 0.25 }, fgm::Vector4D{ 12.0, 13.0, 14.0, 15.0 } };

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
    [[maybe_unused]] fgm::Matrix4D mat1{ fgm::Vector4D{ 1.0f, 2.0f, 3.0f, 7.5f },
                                         fgm::Vector4D{ -3.0f, -4.0f, 10.0f, -11.0f },
                                         fgm::Vector4D{ 4.5f, 3.25f, 3.16f, -22.0f },
                                         fgm::Vector4D{ 15.0f, 32.0f, 101.0f, 12.5f } };
    [[maybe_unused]] constexpr fgm::Matrix4D mat2{ fgm::Vector4D{ 11.0, 10.0, 2.0, -1.0 },
                                                   fgm::Vector4D{ 3.0, -8.0, 12.0, 11.0 },
                                                   fgm::Vector4D{ 3.25, 5.1, 0.0, 0.25 },
                                                   fgm::Vector4D{ 12.0, 13.0, 14.0, 15.0 } };

    (void)(mat1 += mat2);

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */