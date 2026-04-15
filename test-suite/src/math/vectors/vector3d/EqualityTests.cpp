/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref fgm::Vector3D equality operator (==, !=) and their functional counterpart's (eq, neq, allEq,
 * anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3DTestSetup.h"

#include <common/Constants.h>


constexpr auto NAN_F = fgm::constants::NaN;
constexpr auto INF = fgm::constants::INFINITY_F;



template <typename T>
class Vector3DEquality: public ::testing::Test
{
protected:
    fgm::Vector3D<T> _eqVecA;
    fgm::Vector3D<T> _eqVecB;
    fgm::Vector3D<T> _dissimilarVec;
    fgm::Vector3D<bool> _equalityMask;
    fgm::Vector3D<bool> _inequalityMask;


    void SetUp() override
    {
        _eqVecA = { T(1.1234568789), T(2.123458319), T(5.123412593891) };
        _eqVecB = { T(1.1234568789), T(2.123458319), T(5.123412593891) };
        _dissimilarVec = { T(7.1234568789), T(2.123458319), T(24.00) };
        _equalityMask = { false, true, false };
        _inequalityMask = { true, false, true };
    }
};

/** @brief Test fixture for @ref fgm::Vector3D, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector3DEquality, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Equality
 * @{
 */

/**************************************
 *                                    *
 *           EQUALITY TESTS           *
 *                                    *
 **************************************/

/** @test Verify that @ref fgm::Vector3D::allEq returns true for identical vectors. */
TYPED_TEST(Vector3DEquality, Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.allEq(this->_eqVecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector3D::allEq returns false if any component differ. */
TYPED_TEST(Vector3DEquality, Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.allEq(this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @test Verify that the static variant of @ref fgm::Vector3D::allEq for identical vectors. */
TYPED_TEST(Vector3DEquality, StaticWrapper_Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = fgm::Vector3D<TypeParam>::allEq(this->_eqVecA, this->_eqVecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that the static variant of @ref fgm::Vector3D::allEq for different vectors. */
TYPED_TEST(Vector3DEquality, StaticWrapper_Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = fgm::Vector3D<TypeParam>::allEq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Vector3D::allEq follows IEEE 754 for NaN comparisons. */
TEST(Vector3DEquality, NanEqualityReturnsFalse)
{
    constexpr fgm::Vector3D vecA = { NAN_F, NAN_F, NAN_F };
    constexpr fgm::Vector3D vecB = { 1.0, -5.88874789, fgm::constants::INFINITY_D };

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Vector3D::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector3DEquality, InfinityEquality_IdenticalVectorsReturnsTrue)
{
    constexpr fgm::Vector3D vecA = { INF, -INF, INF };
    constexpr fgm::Vector3D vecB = { INF, -INF, INF};

    constexpr bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector3D::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector3DEquality, InfinityEquality_DifferentVectorsReturnsFalse)
{
    constexpr fgm::Vector3D vecA = { INF, INF, INF };
    constexpr fgm::Vector3D vecB = { INF, -INF, INF };

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator returns true for identical vectors. */
TYPED_TEST(Vector3DEquality, EqualityOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA == this->_eqVecB;

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector3D::allEq works for different vector types with identical components. */
TYPED_TEST(Vector3DEquality, MixedType_Equality_IdenticalVectorsReturnsTrue)
{
    constexpr fgm::Vector3D vecA(1, 2, 3);
    constexpr fgm::Vector3D vecB(1.0, 2.0, 3.0);

    constexpr bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector3D::allEq works for different vector types with different components. */
TYPED_TEST(Vector3DEquality, MixedType_Equality_DifferentVectorsReturnsFalse)
{
    constexpr fgm::Vector3D vecA(5, 6, 7);
    constexpr fgm::Vector3D vecB(1.0, 2.0, 3.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator returns false if any component differ. */
TYPED_TEST(Vector3DEquality, EqualityOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA == this->_dissimilarVec;

    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator works for bool vector with identical components. */
TEST(Vector3DEquality, EqualityOperator_IdenticalBooleanVectorsReturnsTrue)
{
    constexpr fgm::Vector3D vecA(true, false, true);
    constexpr fgm::Vector3D vecB(true, false, true);

    constexpr bool equality = vecA == vecB;

    EXPECT_TRUE(equality);
}


/** @test Verify that the equality operator works for bool vector with different components. */
TEST(Vector3DEquality, EqualityOperator_DifferentBooleanVectorsReturnsFalse)
{
    constexpr fgm::Vector3D vecA(true, false, true);
    constexpr fgm::Vector3D vecB(true, true, true);

    constexpr bool equality = vecA == vecB;

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Vector3D::eq returns @ref fgm::Vector3D<bool> mask for identical vectors. */
TYPED_TEST(Vector3DEquality, EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vector3D<bool> mask = this->_eqVecA.eq(this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_equalityMask, mask);
}

/** @test Verify that @ref fgm::Vector3D::eq returns @ref fgm::Vector3D<bool> mask for different vectors. */
TEST(Vector3DEquality, MixedType_EqualityReturnsCorrectBooleanMask)
{
    constexpr fgm::Vector3D vecA = { 1, 2, 3};
    constexpr fgm::Vector3D vecB = { 1.0, 4.0, 0.0 };
    constexpr fgm::Vector3D expectedMask = { true, false, false };

    const fgm::Vector3D<bool> mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref fgm::Vector3D::eq follows IEEE 754 for NaN comparisons. */
TEST(Vector3DEquality, NanEqualityReturnsFalseBooleanMask)
{
    constexpr fgm::Vector3D vecA = { NAN_F, NAN_F, NAN_F };
    constexpr fgm::Vector3D vecB = { 1.0, -5.88874789, fgm::constants::INFINITY_D};
    constexpr fgm::Vector3D expectedMask = { false, false, false };

    const fgm::Vector3D mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref fgm::Vector3D::eq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector3DEquality, InfinityEqualityReturnsCorrectBooleanMask)
{
    constexpr fgm::Vector3D vecA = { INF, -INF, INF };
    constexpr fgm::Vector3D<double> vecB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11 };
    constexpr fgm::Vector3D expectedMask = { true, false, false };

    const fgm::Vector3D mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @test Verify that the static variant of @ref fgm::Vector3D::eq returns @ref fgm::Vector3D<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vector3DEquality, StaticWrapper_EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vector3D<bool> mask = fgm::Vector3D<TypeParam>::eq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_equalityMask, mask);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec3_Inequality
 * @{
 */

/**************************************
 *                                    *
 *          INEQUALITY TESTS          *
 *                                    *
 **************************************/


/** @test Verify that @ref fgm::Vector3D::anyNeq returns false for identical vectors. */
TYPED_TEST(Vector3DEquality, Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.anyNeq(this->_eqVecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Vector3D::anyNeq returns true if any component differ. */
TYPED_TEST(Vector3DEquality, Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.anyNeq(this->_dissimilarVec);

    EXPECT_TRUE(equality);
}


/** @test Verify that the static variant of @ref fgm::Vector3D::anyNeq for identical vectors. */
TYPED_TEST(Vector3DEquality, StaticWrapper_Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = fgm::Vector3D<TypeParam>::anyNeq(this->_eqVecA, this->_eqVecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that the static variant of @ref fgm::Vector3D::anyNeq for different vectors. */
TYPED_TEST(Vector3DEquality, StaticWrapper_Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = fgm::Vector3D<TypeParam>::anyNeq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector3D::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Vector3DEquality, NanInequalityReturnsTrue)
{
    constexpr fgm::Vector3D vecA = { NAN_F, NAN_F, NAN_F };
    constexpr fgm::Vector3D<double> vecB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector3D::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector3DEquality, InfinityInequality_IdenticalVectorsReturnsFalse)
{
    constexpr fgm::Vector3D vecA = { INF, -INF, INF };
    constexpr fgm::Vector3D vecB = { INF, -INF, INF };

    constexpr bool equality = vecA.anyNeq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Vector3D::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector3DEquality, InfinityInequality_DifferentVectorsReturnsTrue)
{
    constexpr fgm::Vector3D vecA = { INF, INF, INF };
    constexpr fgm::Vector3D vecB = { INF, -INF, INF };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector3D::anyNeq works for different vector types with identical components. */
TYPED_TEST(Vector3DEquality, MixedType_Inequality_IdenticalVectorsReturnsFalse)
{
    constexpr fgm::Vector3D vecA(1, 2, 3);
    constexpr fgm::Vector3D vecB(1.0, 2.0, 3.0);

    constexpr bool equality = vecA.anyNeq(vecB);

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Vector3D::anyNeq works for different vector types with different components. */
TYPED_TEST(Vector3DEquality, MixedType_Inequality_DifferentVectorsReturnsTrue)
{
    constexpr fgm::Vector3D vecA(5, 6, 7);
    constexpr fgm::Vector3D vecB(1.0, 2.0, 3.0);

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @test Verify that the operator returns false for identical vectors. */
TYPED_TEST(Vector3DEquality, InEqualityOperator_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA != this->_eqVecB;

    EXPECT_FALSE(equality);
}


/** @test Verify that the inequality operator returns true for different vectors. */
TYPED_TEST(Vector3DEquality, InEqualityOperator_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA != this->_dissimilarVec;

    EXPECT_TRUE(equality);
}


/** @test Verify that the inequality operator works for @ref fgm::Vector3D<bool> with identical components. */
TEST(Vector3DEquality, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    constexpr fgm::Vector3D vecA(true, false, true);
    constexpr fgm::Vector3D vecB(true, false, true);

    constexpr bool equality = vecA != vecB;

    EXPECT_FALSE(equality);
}


/** @test Verify that the inequality operator works for @ref fgm::Vector3D<bool> with different components. */
TEST(Vector3DEquality, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    constexpr fgm::Vector3D vecA(true, false, true);
    constexpr fgm::Vector3D vecB(true, true, true);

    constexpr bool equality = vecA != vecB;

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Vector3D::neq returns @ref fgm::Vector3D<bool> mask for identical vectors. */
TYPED_TEST(Vector3DEquality, InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vector3D<bool> mask = this->_eqVecA.neq(this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}


/** @test Verify that @ref fgm::Vector3D::neq returns @ref fgm::Vector3D<bool> mask for different vectors. */
TEST(Vector3DEquality, MixedType_InequalityReturnsCorrectBooleanMask)
{
    constexpr fgm::Vector3D vecA = { 1, 2, 3 };
    constexpr fgm::Vector3D vecB = { 1.0, 4.0, 0.0 };
    constexpr fgm::Vector3D expectedMask = { false, true, true };

    const fgm::Vector3D<bool> mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref fgm::Vector3D::neq follows IEEE 754 for NaN comparisons. */
TEST(Vector3DEquality, NanInequalityReturnsTrueBooleanMask)
{
    constexpr fgm::Vector3D vecA = { NAN_F, NAN_F, NAN_F };
    constexpr fgm::Vector3D<double> vecB = { 1.0, -5.88874789, fgm::constants::INFINITY_D };
    constexpr fgm::Vector3D expectedMask = { true, true, true };

    const fgm::Vector3D mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref fgm::Vector3D::neq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector3DEquality, InfinityInequalityReturnsCorrectBooleanMask)
{
    constexpr fgm::Vector3D vecA = { INF, -INF, INF };
    constexpr fgm::Vector3D vecB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11 };
    constexpr fgm::Vector3D expectedMask = { false, true, true };

    const fgm::Vector3D mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @test Verify that the static variant of @ref fgm::Vector3D::neq returns @ref fgm::Vector3D<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vector3DEquality, StaticWrapper_InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vector3D<bool> mask = fgm::Vector3D<TypeParam>::neq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}

/** @} */