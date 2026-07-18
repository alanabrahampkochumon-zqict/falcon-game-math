/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify @ref fgm::Mat4 equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"

#include <fgm/common/Constants.h>



constexpr auto NAN_F = fgm::constants::NaN;
constexpr auto INF   = fgm::constants::INFINITY_F;


template <typename T>
class Mat4Equality: public ::testing::Test
{
protected:
    fgm::Mat4<T> _eqMatA;
    fgm::Mat4<T> _eqMatB;
    fgm::Mat4<T> _dissimilarMat;


    void SetUp() override
    {
        _eqMatA        = { { T(1.1234568789), T(2.123458319), T(3.323458319), T(5.392489234) },
                           { T(3.1234568789), T(4.123458319), T(7.123458319), T(12.3492812) },
                           { T(11.1234568789), T(3.123458319), T(5.123458319), T(0.238491234) },
                           { T(5.0), T(33.123458319), T(5.5932023), T(9.823582394) } };
        _eqMatB        = { { T(1.1234568789), T(2.123458319), T(3.323458319), T(5.392489234) },
                           { T(3.1234568789), T(4.123458319), T(7.123458319), T(12.3492812) },
                           { T(11.1234568789), T(3.123458319), T(5.123458319), T(0.238491234) },
                           { T(5.0), T(33.123458319), T(5.5932023), T(9.823582394) } };
        _dissimilarMat = { { T(1.1234568789), T(4.5238852912), T(3.123458319), T(0.238491234) },
                           { T(3.1234568789), T(6.123458319), T(4.123458319), T(12.3492812) },
                           { T(3.1234568789), T(4.123458319), T(7.123458319), T(5.392489234) },
                           { T(5.0), T(33.123458319), T(5.5932023), T(9.823582394) } };
    }
};
/**
 * @brief Test fixture for @ref fgm::Mat4 equality and inequality checks, parameterized by
 *        @ref SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Mat4Equality, SupportedArithmeticTypes);


struct Mat4ElementParam
{
    fgm::Mat4<int> first, second;
    bool expected;
};


class Mat4PerElementEquality: public ::testing::TestWithParam<Mat4ElementParam>
{};
/** @brief Fixture for verifying matrix equality by making only one element unequal at a time. */
INSTANTIATE_TEST_SUITE_P(
    Mat4Tests, Mat4PerElementEquality,
    ::testing::Values(
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 1, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 1, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 1, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 1, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 10, 11, 12, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 11, 12, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 12, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 1, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 1, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1 }, .expected = false }));


class Mat4PerElementInequality: public ::testing::TestWithParam<Mat4ElementParam>
{};
/** @brief Fixture for verifying matrix inequality by making only one element unequal at a time. */
INSTANTIATE_TEST_SUITE_P(
    Mat4Tests, Mat4PerElementInequality,
    ::testing::Values(
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = false },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 1, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 1, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 1, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 1, 9, 10, 11, 12, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 10, 11, 12, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 11, 12, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 12, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 1, 13, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 14, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 15, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 1, 16 }, .expected = true },
        Mat4ElementParam{ .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1 }, .expected = true }));



/**
 * @addtogroup T_FGM_Mat4x4_Equality
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{

    constexpr fgm::Mat4 MAT1(1, 2, 3, 4);
    constexpr fgm::Mat4 MAT2(1, 2, 3, 4);
    constexpr fgm::Mat4 MAT3(4, 2, 2, 4);
    constexpr fgm::Mat4 INF_MAT1(-fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                    -fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);
    constexpr fgm::Mat4 INF_MAT2(-fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                    -fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);


    /** @brief Verify that matrix equality check is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(MAT1.allEq(MAT2) == true);
        static_assert(MAT1.allEq(MAT3) == false);
        static_assert(INF_MAT1.allEq(INF_MAT2) == true);


        // Static functions
        static_assert(fgm::Mat4<int>::allEq(MAT1, MAT2) == true);
        static_assert(fgm::Mat4<int>::allEq(MAT1, MAT3) == false);
        static_assert(fgm::Mat4<float>::allEq(INF_MAT1, INF_MAT2) == true);

    } // namespace

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Mat4::allEq returns  `true`  for identical matrices. */
TYPED_TEST(Mat4Equality, Equality_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA.allEq(this->_eqMatB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Mat4::allEq returns `false` if any component differ. */
TYPED_TEST(Mat4Equality, Equality_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA.allEq(this->_dissimilarMat);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Mat4::allEq for identical matrices. */
TYPED_TEST(Mat4Equality, StaticWrapper_Equality_IdenticalMatricesReturnTrue)
{
    const bool equality = fgm::Mat4<TypeParam>::allEq(this->_eqMatA, this->_eqMatB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Mat4::allEq for different matrices. */
TYPED_TEST(Mat4Equality, StaticWrapper_Equality_DifferentMatricesReturnFalse)
{
    const bool equality = fgm::Mat4<TypeParam>::allEq(this->_eqMatA, this->_dissimilarMat);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Mat4::allEq follows IEEE 754 for NaN comparisons. */
TEST(Mat4Equality, NanEqualityReturnsFalse)
{
    const fgm::Mat4 matA(NAN_F, NAN_F, NAN_F, NAN_F);
    const fgm::Mat4 matB(1.0f, -5.88874789f, 0.888749f, 0.38239f);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Mat4::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Mat4Equality, InfinityEquality_IdenticalMatricesReturnTrue)
{
    const fgm::Mat4 matA(INF, -INF, INF, -INF);
    const fgm::Mat4 matB(INF, -INF, INF, -INF);

    const bool equality = matA.allEq(matB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Mat4::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Mat4Equality, InfinityEquality_DifferentMatricesReturnFalse)
{
    const fgm::Mat4 matA(INF, -INF, INF, INF);
    const fgm::Mat4 matB(-INF, -INF, INF, -INF);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}

/** @brief Verify that @ref fgm::Mat4::allEq works for different vector types with identical components. */
TYPED_TEST(Mat4Equality, MixedType_Equality_IdenticalMatricesReturnTrue)
{
    const fgm::Mat4 matA(1, 2, 3, 4);
    const fgm::Mat4 matB(1.0, 2.0, 3.0, 4.0);

    const bool equality = matA.allEq(matB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Mat4::allEq works for different vector types with different components. */
TYPED_TEST(Mat4Equality, MixedType_Equality_DifferentMatricesReturnFalse)
{
    const fgm::Mat4 matA(5, 6, 7, 1);
    const fgm::Mat4 matB(1.0, 2.0, 3.0, 1.0);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}



/** @brief Verify that the equality operator returns `true` for identical matrices. */
TYPED_TEST(Mat4Equality, EqualityOperator_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA == this->_eqMatB;

    EXPECT_TRUE(equality);
}



/** @brief Verify that the equality operator returns `false` if any component differ. */
TYPED_TEST(Mat4Equality, EqualityOperator_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA == this->_dissimilarMat;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator works for bool matrix with identical components. */
TEST(Mat4Equality, EqualityOperator_IdenticalBooleanMatricesReturnTrue)
{
    const fgm::Mat4 matA(true, false, true, false);
    const fgm::Mat4 matB(true, false, true, false);

    const bool equality = matA == matB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that the equality operator works for bool matrix with different components. */
TEST(Mat4Equality, EqualityOperator_DifferentBooleanMatricesReturnFalse)
{
    const fgm::Mat4 matA(true, false, false, true);
    const fgm::Mat4 matB(true, true, false, false);

    const bool equality = matA == matB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that fgm::Mat4::allEq works for any element being unequal. */
TEST_P(Mat4PerElementEquality, AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat.allEq(secondMat));
}


/** @brief Verify that static variant of fgm::Mat4::allEq works for any element being unequal. */
TEST_P(Mat4PerElementEquality, StaticWrapper_AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat4<int>::allEq(firstMat, secondMat));
}


/** @brief Verify that static variant of fgm::Mat4::allEq works for any element being unequal. */
TEST_P(Mat4PerElementEquality, EqualityOperator_AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat == secondMat);
}

/** @} */



/**
 * @addtogroup T_FGM_Mat4x4_Inequality
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that matrix inequality check is available at compile time. */
namespace
{
    // Member functions
    static_assert(MAT1.anyNeq(MAT2) == false);
    static_assert(MAT1.anyNeq(MAT3) == true);
    static_assert(INF_MAT1.anyNeq(INF_MAT2) == false);


    // Static functions
    static_assert(fgm::Mat4<int>::anyNeq(MAT1, MAT2) == false);
    static_assert(fgm::Mat4<int>::anyNeq(MAT1, MAT3) == true);
    static_assert(fgm::Mat4<float>::anyNeq(INF_MAT1, INF_MAT2) == false);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Mat4::anyNeq returns `false` for identical matrices. */
TYPED_TEST(Mat4Equality, Inequality_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_eqMatB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that @ref fgm::Mat4::anyNeq returns `true` if any component differ. */
TYPED_TEST(Mat4Equality, Inequality_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_dissimilarMat);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that the static variant of @ref fgm::Mat4::anyNeq for identical matrices. */
TYPED_TEST(Mat4Equality, StaticWrapper_Inequality_IdenticalMatricesReturnFalse)
{
    const bool inequality = fgm::Mat4<TypeParam>::anyNeq(this->_eqMatA, this->_eqMatB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that the static variant of @ref fgm::Mat4::anyNeq for different matrices. */
TYPED_TEST(Mat4Equality, StaticWrapper_Inequality_DifferentMatricesReturnTrue)
{
    const bool inequality = fgm::Mat4<TypeParam>::anyNeq(this->_eqMatA, this->_dissimilarMat);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that @ref fgm::Mat4::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Mat4Equality, NanInequalityReturnsTrue)
{
    const fgm::Mat4 matA(NAN_F, NAN_F, NAN_F, NAN_F);
    const fgm::Mat4 matB(1.0f, INF, -INF, NAN_F);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that @ref fgm::Mat4::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Mat4Equality, InfinityInequality_IdenticalMatricesReturnFalse)
{
    const fgm::Mat4 matA(INF, -INF, INF, -INF);
    const fgm::Mat4 matB(INF, -INF, INF, -INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that @ref fgm::Mat4::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Mat4Equality, InfinityInequality_DifferentMatricesReturnTrue)
{
    const fgm::Mat4 matA(-INF, INF, INF, INF);
    const fgm::Mat4 matB(INF, INF, -INF, INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that @ref fgm::Mat4::anyNeq works for different vector types with identical components. */
TYPED_TEST(Mat4Equality, MixedType_Inequality_IdenticalMatricesReturnFalse)
{
    const fgm::Mat4 matA(1, 2, 3, 4);
    const fgm::Mat4 matB(1.0, 2.0, 3.0, 4.0);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that @ref fgm::Mat4::anyNeq works for different vector types with different components. */
TYPED_TEST(Mat4Equality, MixedType_Inequality_DifferentMatricesReturnTrue)
{
    const fgm::Mat4 matA(5, 6, 7, 8);
    const fgm::Mat4 matB(1.0, 2.0, 7.0, 8.0);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that the operator returns `false` for identical matrices. */
TYPED_TEST(Mat4Equality, InEqualityOperator_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA != this->_eqMatB;

    EXPECT_FALSE(inequality);
}


/** @brief Verify that the inequality operator returns `true` for different matrices. */
TYPED_TEST(Mat4Equality, InEqualityOperator_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA != this->_dissimilarMat;

    EXPECT_TRUE(inequality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Mat4<bool> with identical components. */
TEST(Mat4Equality, InequalityOperator_IdenticalBooleanMatricesReturnFalse)
{
    const fgm::Mat4 matA(true, false, true, false);
    const fgm::Mat4 matB(true, false, true, false);

    const bool inequality = matA != matB;

    EXPECT_FALSE(inequality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Mat4<bool> with different components. */
TEST(Mat4Equality, InequalityOperator_DifferentBooleanMatricesReturnTrue)
{
    const fgm::Mat4 matA(true, false, true, false);
    const fgm::Mat4 matB(true, true, false, false);

    const bool inequality = matA != matB;

    EXPECT_TRUE(inequality);
}


/** @brief Verify that fgm::Mat4::anyNeq works for any element being unequal. */
TEST_P(Mat4PerElementInequality, AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat.anyNeq(secondMat));
}


/** @brief Verify that static variant of fgm::Mat4::anyNeq works for any element being unequal. */
TEST_P(Mat4PerElementInequality, StaticWrapper_AnyNeq__VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat4<int>::anyNeq(firstMat, secondMat));
}


/** @brief Verify that operator!= works for any element being unequal. */
TEST_P(Mat4PerElementInequality, InequalityOperator_AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat != secondMat);
}

/** @} */
