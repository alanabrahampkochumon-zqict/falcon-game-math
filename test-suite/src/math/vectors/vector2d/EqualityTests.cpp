/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vector2D equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"

#include <common/Constants.h>


constexpr auto NAN_F = fgm::constants::NaN;
constexpr auto INF = fgm::constants::INFINITY_F;



template <typename T>
class Vector2DEquality: public ::testing::Test
{
protected:
    fgm::Vector2D<T> _eqVecA;
    fgm::Vector2D<T> _eqVecB;
    fgm::Vector2D<T> _dissimilarVec;
    fgm::Vector2D<bool> _equalityMask;
    fgm::Vector2D<bool> _inequalityMask;


    void SetUp() override
    {
        _eqVecA = { T(1.1234568789), T(2.123458319) };
        _eqVecB = { T(1.1234568789), T(2.123458319) };
        _dissimilarVec = { T(7.1234568789), T(2.123458319) };
        _equalityMask = { false, true };
        _inequalityMask = { true, false };
    }
};

/** @brief Test fixture for @ref fgm::Vector2D, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector2DEquality, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec2_Equality
 * @{
 */

/**************************************
 *                                    *
 *           EQUALITY TESTS           *
 *                                    *
 **************************************/

/** @test Verify that @ref fgm::Vector2D::allEq returns true for identical vectors. */
TYPED_TEST(Vector2DEquality, Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.allEq(this->_eqVecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector2D::allEq returns false if any component differ. */
TYPED_TEST(Vector2DEquality, Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.allEq(this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @test Verify that the static variant of @ref fgm::Vector2D::allEq for identical vectors. */
TYPED_TEST(Vector2DEquality, StaticWrapper_Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = fgm::Vector2D<TypeParam>::allEq(this->_eqVecA, this->_eqVecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that the static variant of @ref fgm::Vector2D::allEq for different vectors. */
TYPED_TEST(Vector2DEquality, StaticWrapper_Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = fgm::Vector2D<TypeParam>::allEq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Vector2D::allEq follows IEEE 754 for NaN comparisons. */
TEST(Vector2DEquality, NanEqualityReturnsFalse)
{
    constexpr fgm::Vector2D vecA = { NAN_F, NAN_F };
    constexpr fgm::Vector2D vecB = { 1.0, -5.88874789 };

    constexpr bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality) << "NaN vector shouldn't equal anything!";
}


/** @test Verify that @ref fgm::Vector2D::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector2DEquality, InfinityEquality_IdenticalVectorsReturnsTrue)
{
    constexpr fgm::Vector2D vecA = { INF, -INF };
    constexpr fgm::Vector2D vecB = { INF, -INF };

    const bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector2D::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector2DEquality, InfinityEquality_DifferentVectorsReturnsFalse)
{
    constexpr fgm::Vector2D vecA = { INF, INF };
    constexpr fgm::Vector2D vecB = { INF, -INF };

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator returns true for identical vectors. */
TYPED_TEST(Vector2DEquality, EqualityOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA == this->_eqVecB;

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector2D::allEq works for different vector types with identical components. */
TYPED_TEST(Vector2DEquality, MixedType_Equality_IdenticalVectorsReturnsTrue)
{
    constexpr fgm::Vector2D vecA(1, 2);
    constexpr fgm::Vector2D vecB(1.0, 2.0);

    constexpr bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector2D::allEq works for different vector types with different components. */
TYPED_TEST(Vector2DEquality, MixedType_Equality_DifferentVectorsReturnsFalse)
{
    constexpr fgm::Vector2D vecA(5, 6);
    constexpr fgm::Vector2D vecB(1.0, 2.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator returns false if any component differ. */
TYPED_TEST(Vector2DEquality, EqualityOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA == this->_dissimilarVec;

    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator works for bool vector with identical components. */
TEST(Vector2DEquality, EqualityOperator_IdenticalBooleanVectorsReturnsTrue)
{
    constexpr fgm::Vector2D vecA(true, false);
    constexpr fgm::Vector2D vecB(true, false);

    constexpr bool equality = vecA == vecB;

    EXPECT_TRUE(equality);
}


/** @test Verify that the equality operator works for bool vector with different components. */
TEST(Vector2DEquality, EqualityOperator_DifferentBooleanVectorsReturnsFalse)
{
    constexpr fgm::Vector2D vecA(true, false);
    constexpr fgm::Vector2D vecB(true, true);

    constexpr bool equality = vecA == vecB;

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Vector2D::eq returns @ref fgm::Vector2D<bool> mask for identical vectors. */
TYPED_TEST(Vector2DEquality, EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vector2D<bool> mask = this->_eqVecA.eq(this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_equalityMask, mask);
}

/** @test Verify that @ref fgm::Vector2D::eq returns @ref fgm::Vector2D<bool> mask for different vectors. */
TEST(Vector2DEquality, MixedType_EqualityReturnsCorrectBooleanMask)
{
    constexpr fgm::Vector2D vecA = { 1, 2 };
    constexpr fgm::Vector2D vecB = { 1.0, 4.0 };
    constexpr fgm::Vector2D expectedMask = { true, false };

    const fgm::Vector2D<bool> mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref fgm::Vector2D::eq follows IEEE 754 for NaN comparisons. */
TEST(Vector2DEquality, NanEqualityReturnsFalseBooleanMask)
{
    constexpr fgm::Vector2D vecA = { NAN_F, NAN_F };
    constexpr fgm::Vector2D vecB = { 1.0, -5.88874789 };
    constexpr fgm::Vector2D expectedMask = { false, false };

    const fgm::Vector2D mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref fgm::Vector2D::eq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector2DEquality, InfinityEqualityReturnsCorrectBooleanMask)
{
    constexpr fgm::Vector2D vecA = { INF, -INF };
    constexpr fgm::Vector2D<double> vecB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D };
    constexpr fgm::Vector2D expectedMask = { true, false };

    const fgm::Vector2D mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @test Verify that the static variant of @ref fgm::Vector2D::eq returns @ref fgm::Vector2D<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vector2DEquality, StaticWrapper_EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vector2D<bool> mask = fgm::Vector2D<TypeParam>::eq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_equalityMask, mask);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec2_Inequality
 * @{
 */

/**************************************
 *                                    *
 *          INEQUALITY TESTS          *
 *                                    *
 **************************************/


/** @test Verify that @ref fgm::Vector2D::anyNeq returns false for identical vectors. */
TYPED_TEST(Vector2DEquality, Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.anyNeq(this->_eqVecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Vector2D::anyNeq returns true if any component differ. */
TYPED_TEST(Vector2DEquality, Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.anyNeq(this->_dissimilarVec);

    EXPECT_TRUE(equality);
}


/** @test Verify that the static variant of @ref fgm::Vector2D::anyNeq for identical vectors. */
TYPED_TEST(Vector2DEquality, StaticWrapper_Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = fgm::Vector2D<TypeParam>::anyNeq(this->_eqVecA, this->_eqVecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that the static variant of @ref fgm::Vector2D::anyNeq for different vectors. */
TYPED_TEST(Vector2DEquality, StaticWrapper_Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = fgm::Vector2D<TypeParam>::anyNeq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector2D::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Vector2DEquality, NanInequalityReturnsTrue)
{
    constexpr fgm::Vector2D vecA = { NAN_F, NAN_F };
    constexpr fgm::Vector2D vecB = { 1.0, -5.88874789 };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector2D::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector2DEquality, InfinityInequality_IdenticalVectorsReturnsFalse)
{
    constexpr fgm::Vector2D vecA = { INF, -INF };
    constexpr fgm::Vector2D vecB = { INF, -INF };

    constexpr bool equality = vecA.anyNeq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Vector2D::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector2DEquality, InfinityInequality_DifferentVectorsReturnsTrue)
{
    constexpr fgm::Vector2D vecA = { INF, INF };
    constexpr fgm::Vector2D vecB = { INF, -INF };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector2D::anyNeq works for different vector types with identical components. */
TYPED_TEST(Vector2DEquality, MixedType_Inequality_IdenticalVectorsReturnsFalse)
{
    constexpr fgm::Vector2D vecA(1, 2);
    constexpr fgm::Vector2D vecB(1.0, 2.0);

    constexpr bool equality = vecA.anyNeq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Vector2D::anyNeq works for different vector types with different components. */
TYPED_TEST(Vector2DEquality, MixedType_Inequality_DifferentVectorsReturnsTrue)
{
    constexpr fgm::Vector2D vecA(5, 6);
    constexpr fgm::Vector2D vecB(1.0, 2.0);

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that the operator returns false for identical vectors. */
TYPED_TEST(Vector2DEquality, InEqualityOperator_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA != this->_eqVecB;

    EXPECT_FALSE(equality);
}


/** @test Verify that the inequality operator returns true for different vectors. */
TYPED_TEST(Vector2DEquality, InEqualityOperator_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA != this->_dissimilarVec;

    EXPECT_TRUE(equality);
}


/** @test Verify that the inequality operator works for @ref fgm::Vector2D<bool> with identical components. */
TEST(Vector2DEquality, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    constexpr fgm::Vector2D vecA(true, false);
    constexpr fgm::Vector2D vecB(true, false);

    constexpr bool equality = vecA != vecB;

    EXPECT_FALSE(equality);
}


/** @test Verify that the inequality operator works for @ref fgm::Vector2D<bool> with different components. */
TEST(Vector2DEquality, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    constexpr fgm::Vector2D vecA(true, false);
    constexpr fgm::Vector2D vecB(true, true);

    constexpr bool equality = vecA != vecB;

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector2D::neq returns @ref fgm::Vector2D<bool> mask for identical vectors. */
TYPED_TEST(Vector2DEquality, InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vector2D<bool> mask = this->_eqVecA.neq(this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}


/** @test Verify that @ref fgm::Vector2D::neq returns @ref fgm::Vector2D<bool> mask for different vectors. */
TEST(Vector2DEquality, MixedType_InequalityReturnsCorrectBooleanMask)
{
    constexpr fgm::Vector2D vecA = { 1, 2 };
    constexpr fgm::Vector2D vecB = { 1.0, 4.0};
    constexpr fgm::Vector2D expectedMask = { false, true };

    const fgm::Vector2D<bool> mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref fgm::Vector2D::neq follows IEEE 754 for NaN comparisons. */
TEST(Vector2DEquality, NanInequalityReturnsTrueBooleanMask)
{
    constexpr fgm::Vector2D vecA = { NAN_F, NAN_F };
    constexpr fgm::Vector2D vecB = { 1.0, -5.88874789 };
    constexpr fgm::Vector2D expectedMask = { true, true };

    const fgm::Vector2D mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref fgm::Vector2D::neq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector2DEquality, InfinityInequalityReturnsCorrectBooleanMask)
{
    constexpr fgm::Vector2D vecA = { INF, -INF };
    constexpr fgm::Vector2D vecB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D };
    constexpr fgm::Vector2D expectedMask = { false, true };

    const fgm::Vector2D mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @test Verify that the static variant of @ref fgm::Vector2D::neq returns @ref fgm::Vector2D<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vector2DEquality, StaticWrapper_InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vector2D<bool> mask = fgm::Vector2D<TypeParam>::neq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}

/** @} */