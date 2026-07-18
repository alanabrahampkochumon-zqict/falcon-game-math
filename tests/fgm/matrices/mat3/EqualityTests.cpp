/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Mat3 equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"

#include <fgm/common/Constants.h>



constexpr auto NAN_F = fgm::constants::NaN;
constexpr auto INF   = fgm::constants::INFINITY_F;


template <typename T>
class Mat3Equality: public ::testing::Test
{
protected:
    fgm::Mat3<T> _eqMatA;
    fgm::Mat3<T> _eqMatB;
    fgm::Mat3<T> _dissimilarMat;


    void SetUp() override
    {
        _eqMatA        = { { T(1.1234568789), T(2.123458319), T(3.323458319) },
                           { T(3.1234568789), T(4.123458319), T(7.123458319) },
                           { T(11.1234568789), T(3.123458319), T(5.123458319) } };
        _eqMatB        = { { T(1.1234568789), T(2.123458319), T(3.323458319) },
                           { T(3.1234568789), T(4.123458319), T(7.123458319) },
                           { T(11.1234568789), T(3.123458319), T(5.123458319) } };
        _dissimilarMat = { { T(1.1234568789), T(4.5238852912), T(3.123458319) },
                           { T(3.1234568789), T(6.123458319), T(4.123458319) },
                           { T(3.1234568789), T(4.123458319), T(7.123458319) } };
    }
};
/**
 * @brief Test fixture for @ref fgm::Mat3 equality and inequality checks, parameterized by
 *        @ref SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Mat3Equality, SupportedArithmeticTypes);


struct Mat3ElementParam
{
    fgm::Mat3<int> first, second;
    bool expected;
};


class Mat3PerElementEquality: public ::testing::TestWithParam<Mat3ElementParam>
{};
/** @brief Fixture for verifying matrix equality by making only one element unequal at a time. */
INSTANTIATE_TEST_SUITE_P(
    Mat3Tests, Mat3PerElementEquality,
    ::testing::Values(
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .expected = true },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 2, 2, 3, 4, 5, 6, 7, 8, 9 }, .expected = false },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 1, 3, 4, 5, 6, 7, 8, 9 }, .expected = false },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 1, 4, 5, 6, 7, 8, 9 }, .expected = false },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 1, 5, 6, 7, 8, 9 }, .expected = false },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 1, 6, 7, 8, 9 }, .expected = false },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 1, 7, 8, 9 }, .expected = false },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 1, 8, 9 }, .expected = false },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 7, 1, 9 }, .expected = false },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 1 }, .expected = false }));


class Mat3PerElementInequality: public ::testing::TestWithParam<Mat3ElementParam>
{};
/** @brief Fixture for verifying matrix inequality by making only one element unequal at a time. */
INSTANTIATE_TEST_SUITE_P(
    Mat3Tests, Mat3PerElementInequality,
    ::testing::Values(
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .expected = false },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 2, 2, 3, 4, 5, 6, 7, 8, 9 }, .expected = true },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 1, 3, 4, 5, 6, 7, 8, 9 }, .expected = true },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 1, 4, 5, 6, 7, 8, 9 }, .expected = true },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 1, 5, 6, 7, 8, 9 }, .expected = true },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 1, 6, 7, 8, 9 }, .expected = true },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 1, 7, 8, 9 }, .expected = true },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 1, 8, 9 }, .expected = true },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 7, 1, 9 }, .expected = true },
        Mat3ElementParam{
            .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 1 }, .expected = true }));



/**
 * @addtogroup T_FGM_Mat3x3_Equality
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{

    constexpr fgm::Mat3 MAT1(1, 2, 3);
    constexpr fgm::Mat3 MAT2(1, 2, 3);
    constexpr fgm::Mat3 MAT3(4, 2, 2);
    constexpr fgm::Mat3 INF_MAT1(-fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, -fgm::constants::INFINITY_F);
    constexpr fgm::Mat3 INF_MAT2(-fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, -fgm::constants::INFINITY_F);


    /** @brief Verify that matrix equality check is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(MAT1.allEq(MAT2) == true);
        static_assert(MAT1.allEq(MAT3) == false);
        static_assert(INF_MAT1.allEq(INF_MAT2) == true);


        // Static functions
        static_assert(fgm::Mat3<int>::allEq(MAT1, MAT2) == true);
        static_assert(fgm::Mat3<int>::allEq(MAT1, MAT3) == false);
        static_assert(fgm::Mat3<float>::allEq(INF_MAT1, INF_MAT2) == true);

    } // namespace

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Mat3::allEq returns  `true`  for identical matrices. */
TYPED_TEST(Mat3Equality, Equality_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA.allEq(this->_eqMatB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Mat3::allEq returns `false` if any component differ. */
TYPED_TEST(Mat3Equality, Equality_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA.allEq(this->_dissimilarMat);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Mat3::allEq for identical matrices. */
TYPED_TEST(Mat3Equality, StaticWrapper_Equality_IdenticalMatricesReturnTrue)
{
    const bool equality = fgm::Mat3<TypeParam>::allEq(this->_eqMatA, this->_eqMatB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Mat3::allEq for different matrices. */
TYPED_TEST(Mat3Equality, StaticWrapper_Equality_DifferentMatricesReturnFalse)
{
    const bool equality = fgm::Mat3<TypeParam>::allEq(this->_eqMatA, this->_dissimilarMat);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Mat3::allEq follows IEEE 754 for NaN comparisons. */
TEST(Mat3Equality, NanEqualityReturnsFalse)
{
    const fgm::Mat3 matA(NAN_F, NAN_F, NAN_F);
    const fgm::Mat3 matB(1.0f, -5.88874789f, 0.888749f);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Mat3::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Mat3Equality, InfinityEquality_IdenticalMatricesReturnTrue)
{
    const fgm::Mat3 matA(INF, -INF, INF);
    const fgm::Mat3 matB(INF, -INF, INF);

    const bool equality = matA.allEq(matB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Mat3::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Mat3Equality, InfinityEquality_DifferentMatricesReturnFalse)
{
    const fgm::Mat3 matA(INF, -INF, INF);
    const fgm::Mat3 matB(-INF, -INF, INF);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}

/** @brief Verify that @ref fgm::Mat3::allEq works for different vector types with identical components. */
TYPED_TEST(Mat3Equality, MixedType_Equality_IdenticalMatricesReturnTrue)
{
    const fgm::Mat3 matA(1, 2, 3);
    const fgm::Mat3 matB(1.0, 2.0, 3.0);

    const bool equality = matA.allEq(matB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Mat3::allEq works for different vector types with different components. */
TYPED_TEST(Mat3Equality, MixedType_Equality_DifferentMatricesReturnFalse)
{
    const fgm::Mat3 matA(5, 6, 7);
    const fgm::Mat3 matB(1.0, 2.0, 3.0);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}



/** @brief Verify that the equality operator returns `true` for identical matrices. */
TYPED_TEST(Mat3Equality, EqualityOperator_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA == this->_eqMatB;

    EXPECT_TRUE(equality);
}



/** @brief Verify that the equality operator returns `false` if any component differ. */
TYPED_TEST(Mat3Equality, EqualityOperator_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA == this->_dissimilarMat;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator works for bool matrix with identical components. */
TEST(Mat3Equality, EqualityOperator_IdenticalBooleanMatricesReturnTrue)
{
    const fgm::Mat3 matA(true, false, true);
    const fgm::Mat3 matB(true, false, true);

    const bool equality = matA == matB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that the equality operator works for bool matrix with different components. */
TEST(Mat3Equality, EqualityOperator_DifferentBooleanMatricesReturnFalse)
{
    const fgm::Mat3 matA(true, false, false);
    const fgm::Mat3 matB(true, true, false);

    const bool equality = matA == matB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that fgm::Mat3::allEq works for any element being unequal. */
TEST_P(Mat3PerElementEquality, AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat.allEq(secondMat));
}


/** @brief Verify that static variant of fgm::Mat3::allEq works for any element being unequal. */
TEST_P(Mat3PerElementEquality, StaticWrapper_AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat3<int>::allEq(firstMat, secondMat));
}


/** @brief Verify that static variant of fgm::Mat3::allEq works for any element being unequal. */
TEST_P(Mat3PerElementEquality, EqualityOperator_AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat == secondMat);
}

/** @} */



/**
 * @addtogroup T_FGM_Mat3x3_Inequality
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
    static_assert(fgm::Mat3<int>::anyNeq(MAT1, MAT2) == false);
    static_assert(fgm::Mat3<int>::anyNeq(MAT1, MAT3) == true);
    static_assert(fgm::Mat3<float>::anyNeq(INF_MAT1, INF_MAT2) == false);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Mat3::anyNeq returns `false` for identical matrices. */
TYPED_TEST(Mat3Equality, Inequality_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_eqMatB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that @ref fgm::Mat3::anyNeq returns `true` if any component differ. */
TYPED_TEST(Mat3Equality, Inequality_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_dissimilarMat);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that the static variant of @ref fgm::Mat3::anyNeq for identical matrices. */
TYPED_TEST(Mat3Equality, StaticWrapper_Inequality_IdenticalMatricesReturnFalse)
{
    const bool inequality = fgm::Mat3<TypeParam>::anyNeq(this->_eqMatA, this->_eqMatB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that the static variant of @ref fgm::Mat3::anyNeq for different matrices. */
TYPED_TEST(Mat3Equality, StaticWrapper_Inequality_DifferentMatricesReturnTrue)
{
    const bool inequality = fgm::Mat3<TypeParam>::anyNeq(this->_eqMatA, this->_dissimilarMat);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that @ref fgm::Mat3::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Mat3Equality, NanInequalityReturnsTrue)
{
    const fgm::Mat3 matA(NAN_F, NAN_F, NAN_F);
    const fgm::Mat3 matB(1.0f, INF, -INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that @ref fgm::Mat3::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Mat3Equality, InfinityInequality_IdenticalMatricesReturnFalse)
{
    const fgm::Mat3 matA(INF, -INF, INF);
    const fgm::Mat3 matB(INF, -INF, INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that @ref fgm::Mat3::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Mat3Equality, InfinityInequality_DifferentMatricesReturnTrue)
{
    const fgm::Mat3 matA(-INF, INF, INF);
    const fgm::Mat3 matB(INF, INF, -INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that @ref fgm::Mat3::anyNeq works for different vector types with identical components. */
TYPED_TEST(Mat3Equality, MixedType_Inequality_IdenticalMatricesReturnFalse)
{
    const fgm::Mat3 matA(1, 2, 3);
    const fgm::Mat3 matB(1.0, 2.0, 3.0);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that @ref fgm::Mat3::anyNeq works for different vector types with different components. */
TYPED_TEST(Mat3Equality, MixedType_Inequality_DifferentMatricesReturnTrue)
{
    const fgm::Mat3 matA(5, 6, 7);
    const fgm::Mat3 matB(1.0, 2.0, 7.0);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that the operator returns `false` for identical matrices. */
TYPED_TEST(Mat3Equality, InEqualityOperator_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA != this->_eqMatB;

    EXPECT_FALSE(inequality);
}


/** @brief Verify that the inequality operator returns `true` for different matrices. */
TYPED_TEST(Mat3Equality, InEqualityOperator_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA != this->_dissimilarMat;

    EXPECT_TRUE(inequality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Mat3<bool> with identical components. */
TEST(Mat3Equality, InequalityOperator_IdenticalBooleanMatricesReturnFalse)
{
    const fgm::Mat3 matA(true, false, true);
    const fgm::Mat3 matB(true, false, true);

    const bool inequality = matA != matB;

    EXPECT_FALSE(inequality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Mat3<bool> with different components. */
TEST(Mat3Equality, InequalityOperator_DifferentBooleanMatricesReturnTrue)
{
    const fgm::Mat3 matA(true, false, true);
    const fgm::Mat3 matB(true, true, false);

    const bool inequality = matA != matB;

    EXPECT_TRUE(inequality);
}


/** @brief Verify that fgm::Mat3::anyNeq works for any element being unequal. */
TEST_P(Mat3PerElementInequality, AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat.anyNeq(secondMat));
}


/** @brief Verify that static variant of fgm::Mat3::anyNeq works for any element being unequal. */
TEST_P(Mat3PerElementInequality, StaticWrapper_AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat3<int>::anyNeq(firstMat, secondMat));
}


/** @brief Verify that operator!= works for any element being unequal. */
TEST_P(Mat3PerElementInequality, InequalityOperator_AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat != secondMat);
}

/** @} */
