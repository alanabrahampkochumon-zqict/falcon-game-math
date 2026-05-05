/**
 * @file SubtractionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 05, 2026
 *
 * @brief Verify @ref fgm::Matrix4D subtraction logic.
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
class Matrix4DSubtraction: public ::testing::Test
{
protected:
    fgm::Matrix4D<T> _matA;
    fgm::Matrix4D<T> _matB;
    fgm::Matrix4D<T> _expectedDifference;

    void SetUp() override
    {
        _matA = { { T(20), T(21), T(22), T(23) },
                  { T(24), T(25), T(26), T(27) },
                  { T(28), T(29), T(30), T(31) },
                  { T(32), T(33), T(34), T(35) } };

        _matB = { { T(1), T(3), T(6), T(1) },
                  { T(15), T(11), T(5), T(12) },
                  { T(17), T(22), T(6), T(23) },
                  { T(16), T(14), T(32), T(35) } };

        _expectedDifference = { { T(19), T(18), T(16), T(22) },
                                { T(9), T(14), T(21), T(15) },
                                { T(11), T(7), T(24), T(8) },
                                { T(16), T(19), T(2), T(0) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix4D subtraction, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix4DSubtraction, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Mat4x4_Subtraction
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
    constexpr fgm::Matrix4D matA{ 8, 2, 12, 4, 15, -11, 23, -55, 12, 10, 11, 19, 20, 22, 15, 16 };
    constexpr fgm::Matrix4D matB{ 80, -5, 15, 3, 1, -13, 0, 55, 38, 33, -12, 10, 59, 11, 15, -16 };
    constexpr fgm::Matrix4D binaryDiff = matA - matB;

    static_assert(binaryDiff(0, 0) == -72);
    static_assert(binaryDiff(0, 1) == 7);
    static_assert(binaryDiff(0, 2) == -3);
    static_assert(binaryDiff(0, 3) == 1);
    static_assert(binaryDiff(1, 0) == 14);
    static_assert(binaryDiff(1, 1) == 2);
    static_assert(binaryDiff(1, 2) == 23);
    static_assert(binaryDiff(1, 3) == -110);
    static_assert(binaryDiff(2, 0) == -26);
    static_assert(binaryDiff(2, 1) == -23);
    static_assert(binaryDiff(2, 2) == 23);
    static_assert(binaryDiff(2, 3) == 9);
    static_assert(binaryDiff(3, 0) == -39);
    static_assert(binaryDiff(3, 1) == 11);
    static_assert(binaryDiff(3, 2) == 0);
    static_assert(binaryDiff(3, 3) == 32);

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
TYPED_TEST(Matrix4DSubtraction, MinusOperator_ReturnsDifference)
{
    const fgm::Matrix4D difference = this->_matA - this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, difference);
}


/**
 * @test Verify that the binary subtraction operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Matrix4DSubtraction, MixedTypeSubtractionPromotesType)
{
    constexpr fgm::Matrix4D mat1(3.0f, -1.0f, 4.0f, -23.0f, 4.0f, 5.0f, 3.0f, 3.0f, 12.0f, 7.0f, 3.0f, -12.0f, 15.0f,
                                 44.0f, 316.0f, 55.0f);
    constexpr fgm::Matrix4D mat2(9.0, 10.0, 3.0, 4.0, -1.0, 0.0, 5.0, 12.0, -22.0, 12.0, 316.0, 7.0, 4.0, -11.0, 21.0,
                                 11.0);

    [[maybe_unused]] constexpr fgm::Matrix4D difference = mat1 - mat2;

    static_assert(std::is_same_v<decltype(difference)::value_type, double>);
}


/**
 * @test Verify that the compound subtraction assignment operator perform an element-wise subtraction
 *       and mutates the matrix in-place.
 */
TYPED_TEST(Matrix4DSubtraction, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_matA -= this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, this->_matA);
}


/**
 * @test Verify that the compound subtraction assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Matrix4DSubtraction, MixedTypeSubtractionAssignmentDoesNotPromoteType)
{
    fgm::Matrix4D mat1(3.0f, -1.0f, 4.0f, -23.0f, 4.0f, 5.0f, 3.0f, 3.0f, 12.0f, 7.0f, 3.0f, -12.0f, 15.0f,
                                 44.0f, 316.0f, 55.0f);
    [[maybe_unused]] constexpr fgm::Matrix4D mat2(9.0, 10.0, 3.0, 4.0, -1.0, 0.0, 5.0, 12.0, -22.0, 12.0, 316.0, 7.0, 4.0, -11.0, 21.0,
                                 11.0);

    (void)(mat1 -= mat2); // Static cast to void is need to prevent compiler warning that not using mat2

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */