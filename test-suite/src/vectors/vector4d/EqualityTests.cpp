/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref fgm::Vector4D equality operator (==, !=) and their functional counterpart's (eq, neq, allEq,
 * allNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"

#include <Config.h>

constexpr auto NaN = fgm::Config::NaN;
constexpr auto INF = fgm::Config::INFINITY_F;

using namespace testutils;


template <typename T>
class Vector4DEquality: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> eqVecA;
    fgm::Vector4D<T> eqVecB;
    fgm::Vector4D<T> dissimilarVec;
    fgm::Vector4D<bool> equalityMask;
    fgm::Vector4D<bool> inequalityMask;


    void SetUp() override
    {
        eqVecA = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
        eqVecB = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
        dissimilarVec = { T(7.1234568789), T(2.123458319), T(24.00), T(123.123489172589) };
        equalityMask = { false, true, false, true };
        inequalityMask = { true, false, true, false };
    }
};

/** @brief Test fixture for @ref fgm::Vector4D, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DEquality, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Equality
 * @{
 */

/**************************************
 *                                    *
 *           EQUALITY TESTS           *
 *                                    *
 **************************************/

/** @test Verify @ref fgm::Vector4D::allEq returns true for identical vectors. */
TYPED_TEST(Vector4DEquality, Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->eqVecA.allEq(this->eqVecB);

    EXPECT_TRUE(equality);
}


/** @test Verify @ref fgm::Vector4D::allEq returns false if any component differ. */
TYPED_TEST(Vector4DEquality, Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = this->eqVecA.allEq(this->dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @test Verify static variant of @ref fgm::Vector4D::allEq for identical vectors. */
TYPED_TEST(Vector4DEquality, StaticWrapper_Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = fgm::Vector4D<TypeParam>::allEq(this->eqVecA, this->eqVecB);

    EXPECT_TRUE(equality);
}


/** @test Verify static variant of @ref fgm::Vector4D::allEq for different vectors. */
TYPED_TEST(Vector4DEquality, StaticWrapper_Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = fgm::Vector4D<TypeParam>::allEq(this->eqVecA, this->dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @test Verify @ref fgm::Vector4D::allEq follows IEEE 754 for NaN comparisons. */
TEST(Vector4DEquality, NanEqualityReturnsFalse)
{
    constexpr fgm::Vector4D vecA = { NaN, NaN, NaN, NaN };
    constexpr fgm::Vector4D vecB = { 1.0, -5.88874789, fgm::Config::INFINITY_D, fgm::Config::NaN_D };

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify @ref fgm::Vector4D::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityEquality_IdenticalVectorsReturnsTrue)
{
    constexpr fgm::Vector4D vecA = { 
        INF, -INF, INF, -INF };
    constexpr fgm::Vector4D vecB = { INF, -INF, INF, -INF };

    constexpr bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify @ref fgm::Vector4D::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityEquality_DifferentVectorsReturnsFalse)
{
    constexpr fgm::Vector4D vecA = { INF, INF, INF, -INF };
    constexpr fgm::Vector4D vecB = { INF, -INF, INF, INF };

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify @ref fgm::Vector4D equality operator returns true for identical vectors. */
TYPED_TEST(Vector4DEquality, EqualityOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->eqVecA == this->eqVecB;

    EXPECT_TRUE(equality);
}


/** @test Verify @ref fgm::Vector4D::allEq works for different vector types with identical components. */
TYPED_TEST(Vector4DEquality, MixedType_Equality_IdenticalVectorsReturnsTrue)
{
    constexpr fgm::Vector4D vecA(1, 2, 3, 4);
    constexpr fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    constexpr bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify @ref fgm::Vector4D::allEq works for different vector types with different components. */
TYPED_TEST(Vector4DEquality, MixedType_Equality_DifferentVectorsReturnsFalse)
{
    constexpr fgm::Vector4D vecA(5, 6, 7, 8);
    constexpr fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}

/** @test Verify @ref fgm::Vector4D equality operator returns false if any component differ. */
TYPED_TEST(Vector4DEquality, EqualityOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->eqVecA == this->dissimilarVec;

    EXPECT_FALSE(equality);
}

/** @test Verify @ref fgm::Vector4D equality operator works for bool vector with identical components. */
TEST(Vector4DEquality, EqualityOperator_IdenticalBooleanVectorsReturnsTrue)
{
    constexpr fgm::Vector4D vecA(true, false, true, false);
    constexpr fgm::Vector4D vecB(true, false, true, false);

    constexpr bool equality = vecA == vecB;

    EXPECT_TRUE(equality);
}

/** @test Verify @ref fgm::Vector4D equality operator works for bool vector with different components. */
TEST(Vector4DEquality, EqualityOperator_DifferentBooleanVectorsReturnsFalse)
{
    constexpr fgm::Vector4D vecA(true, false, true, false);
    constexpr fgm::Vector4D vecB(true, true, true, false);

    constexpr bool equality = vecA == vecB;

    EXPECT_FALSE(equality);
}

/** @test Verify @ref fgm::Vector4D::eq returns @ref fgm::Vector4D<bool> mask for identical vectors. */
TYPED_TEST(Vector4DEquality, EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D<bool> mask = this->eqVecA.eq(this->dissimilarVec);

    EXPECT_VEC_EQ(this->equalityMask, mask);
}

/** @test Verify @ref fgm::Vector4D::eq returns @ref fgm::Vector4D<bool> mask for different vectors. */
TEST(Vector4DEquality, MixedType_EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D vecA = { 1, 2, 3, 4 };
    const fgm::Vector4D vecB = { 1.0, 4.0, 0.0, 4.0 };
    const fgm::Vector4D expectedMask = { true, false, false, true };

    const fgm::Vector4D<bool> mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}

/** @test Verify @ref fgm::Vector4D::eq follows IEEE 754 for NaN comparisons. */
TEST(Vector4DEquality, NanEqualityReturnsFalseBooleanMask)
{
    const fgm::Vector4D vecA = { NaN, NaN, NaN, NaN };
    const fgm::Vector4D<double> vecB = { 1.0, -5.88874789, INF, NaN };
    const fgm::Vector4D expectedMask = { false, false, false, false };

    const fgm::Vector4D mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}

/** @test Verify @ref fgm::Vector4D::eq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityEqualityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D vecA = { INF, -INF, INF, -INF };
    const fgm::Vector4D<double> vecB = { INF, INF, 10e11, 10e11 };
    const fgm::Vector4D expectedMask = { true, false, false, false };

    fgm::Vector4D mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}

/** @test Verify static variant of @ref fgm::Vector4D::eq returns @ref fgm::Vector4D<bool> mask for different vectors.
 */
TYPED_TEST(Vector4DEquality, StaticWrapper_EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D<bool> mask = fgm::Vector4D<TypeParam>::eq(this->eqVecA, this->dissimilarVec);

    EXPECT_VEC_EQ(this->equalityMask, mask);
}

/** @} */




/**
 * @addtogroup T_FGM_Vec4_Inequality
 * @{
 */

/**************************************
 *                                    *
 *          INEQUALITY TESTS          *
 *                                    *
 **************************************/


/** @test Verify @ref fgm::Vector4D::allNeq returns false for identical vectors. */
TYPED_TEST(Vector4DEquality, Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->eqVecA.allNeq(this->eqVecB);

    EXPECT_FALSE(equality);
}

/** @test Verify @ref fgm::Vector4D::allNeq returns true if any component differ. */
TYPED_TEST(Vector4DEquality, Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = this->eqVecA.allNeq(this->dissimilarVec);

    EXPECT_TRUE(equality);
}

/** @test Verify static variant of @ref fgm::Vector4D::allNeq for identical vectors. */
TYPED_TEST(Vector4DEquality, StaticWrapper_Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = fgm::Vector4D<TypeParam>::allNeq(this->eqVecA, this->eqVecB);

    EXPECT_FALSE(equality);
}

/** @test Verify static variant of @ref fgm::Vector4D::allNeq for different vectors. */
TYPED_TEST(Vector4DEquality, StaticWrapper_Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = fgm::Vector4D<TypeParam>::allNeq(this->eqVecA, this->dissimilarVec);

    EXPECT_TRUE(equality);
}

/** @test Verify @ref fgm::Vector4D::allNeq follows IEEE 754 for NaN comparisons. */
TEST(Vector4DEquality, NanInequalityReturnsTrue)
{
    const fgm::Vector4D vecA = { NaN, NaN, NaN, NaN };
    const fgm::Vector4D<double> vecB = { 1.0, -5.88874789, INF, NaN };

    const bool equality = vecA.allNeq(vecB);

    EXPECT_TRUE(equality);
}

/** @test Verify @ref fgm::Vector4D::allNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityInequality_IdenticalVectorsReturnsFalse)
{
    const fgm::Vector4D vecA = { INF, -INF, INF, -INF };
    const fgm::Vector4D vecB = { INF, -INF, INF, -INF };

    const bool equality = vecA.allNeq(vecB);

    EXPECT_FALSE(equality);
}

/** @test Verify @ref fgm::Vector4D::allNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityInequality_DifferentVectorsReturnsTrue)
{
    const fgm::Vector4D vecA = { INF, INF, INF, -INF };
    const fgm::Vector4D vecB = { INF, -INF, INF, INF };

    const bool equality = vecA.allNeq(vecB);

    EXPECT_TRUE(equality);
}

/** @test Verify @ref fgm::Vector4D::allNeq works for different vector types with identical components. */
TYPED_TEST(Vector4DEquality, MixedType_Inequality_IdenticalVectorsReturnsFalse)
{
    const fgm::Vector4D vecA(1, 2, 3, 4);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.allNeq(vecB);

    EXPECT_FALSE(equality);
}

/** @test Verify @ref fgm::Vector4D::allNeq works for different vector types with different components. */
TYPED_TEST(Vector4DEquality, MixedType_Inequality_DifferentVectorsReturnsTrue)
{
    const fgm::Vector4D vecA(5, 6, 7, 8);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.allNeq(vecB);

    EXPECT_TRUE(equality);
}

/** @test Verify @ref fgm::Vector4D inequality operator returns false for identical vectors. */
TYPED_TEST(Vector4DEquality, InEqualityOperator_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->eqVecA != this->eqVecB;

    EXPECT_FALSE(equality);
}

/** @test Verify @ref fgm::Vector4D inequality operator returns true for different vectors. */
TYPED_TEST(Vector4DEquality, InEqualityOperator_DifferentVectorsReturnsTrue)
{
    const bool equality = this->eqVecA != this->dissimilarVec;

    EXPECT_TRUE(equality);
}

/** @test Verify @ref fgm::Vector4D equality operator works for @ref fgm::Vector4D<bool> with identical components. */
TEST(Vector4DEquality, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, false, true, false);

    const bool equality = vecA != vecB;

    EXPECT_FALSE(equality);
}

/** @test Verify @ref fgm::Vector4D equality operator works for @ref fgm::Vector4D<bool> with different components. */
TEST(Vector4DEquality, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, true, true, false);

    const bool equality = vecA != vecB;

    EXPECT_TRUE(equality);
}

/** @test Verify @ref fgm::Vector4D::neq returns @ref fgm::Vector4D<bool> mask for identical vectors. */
TYPED_TEST(Vector4DEquality, InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D<bool> mask = this->eqVecA.neq(this->dissimilarVec);

    EXPECT_VEC_EQ(this->inequalityMask, mask);
}

/** @test Verify @ref fgm::Vector4D::neq returns @ref fgm::Vector4D<bool> mask for different vectors. */
TEST(Vector4DEquality, MixedType_InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D vecA = { 1, 2, 3, 4 };
    const fgm::Vector4D vecB = { 1.0, 4.0, 0.0, 4.0 };
    const fgm::Vector4D expectedMask = { false, true, true, false };

    const fgm::Vector4D<bool> mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}

/** @test Verify @ref fgm::Vector4D::neq follows IEEE 754 for NaN comparisons. */
TEST(Vector4DEquality, NanInequalityReturnsTrueBooleanMask)
{
    const fgm::Vector4D vecA = { NaN, NaN, NaN, NaN };
    const fgm::Vector4D<double> vecB = { 1.0, -5.88874789, INF, NaN };
    const fgm::Vector4D expectedMask = { true, true, true, true };

    const fgm::Vector4D mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}

/** @test Verify @ref fgm::Vector4D::neq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityInequalityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D vecA = { INF, -INF, INF, -INF };
    const fgm::Vector4D<double> vecB = { INF, INF, 10e11, 10e11 };
    const fgm::Vector4D expectedMask = { false, true, true, true };

    const fgm::Vector4D mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}

/**
 * @test Verify static variant of @ref fgm::Vector4D::neq returns @ref fgm::Vector4D<bool> mask for different vectors.
 */
TYPED_TEST(Vector4DEquality, StaticWrapper_InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D<bool> mask = fgm::Vector4D<TypeParam>::neq(this->eqVecA, this->dissimilarVec);

    EXPECT_VEC_EQ(this->inequalityMask, mask);
}

/** @} */