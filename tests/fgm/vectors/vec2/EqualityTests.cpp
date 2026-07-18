/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vec2 equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"

#include <fgm/common/Constants.h>


const auto NAN_F = fgm::constants::NaN;
const auto INF   = fgm::constants::INFINITY_F;



template <typename T>
class Vec2Equality: public ::testing::Test
{
protected:
    fgm::Vec2<T> _eqVecA;
    fgm::Vec2<T> _eqVecB;
    fgm::Vec2<T> _dissimilarVec;
    fgm::Vec2<bool> _equalityMask;
    fgm::Vec2<bool> _inequalityMask;


    void SetUp() override
    {
        _eqVecA         = { T(1.1234568789), T(2.123458319) };
        _eqVecB         = { T(1.1234568789), T(2.123458319) };
        _dissimilarVec  = { T(7.1234568789), T(2.123458319) };
        _equalityMask   = { false, true };
        _inequalityMask = { true, false };
    }
};

/** @brief Test fixture for @ref fgm::Vec2, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec2Equality, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec2_Equality
 * @{
 */

/**************************************
 *                                    *
 *           EQUALITY TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that vector equality operations are available are at compile time. */
namespace
{
    constexpr fgm::Vec2 vec1(1, 2);
    constexpr fgm::Vec2 vec2(3, 2);
    constexpr fgm::Vec2 vec3(1, 2);

    // Equality tests
    constexpr auto allEqVec1 = vec1.allEq(vec2);
    static_assert(allEqVec1 == false);

    constexpr auto allEqVec2 = vec1.allEq(vec3);
    static_assert(allEqVec2 == true);

    constexpr auto allEqVec3 = fgm::Vec2<int>::allEq(vec1, vec2);
    static_assert(allEqVec3 == false);

    constexpr auto allEqVec4 = fgm::Vec2<int>::allEq(vec1, vec3);
    static_assert(allEqVec4 == true);

    constexpr auto allEqVec5 = vec1 == vec2;
    static_assert(allEqVec5 == false);

    constexpr auto allEqVec6 = vec1 == vec3;
    static_assert(allEqVec6 == true);

    constexpr auto maskEqVec = vec1.eq(vec2);
    static_assert(maskEqVec.x() == false);
    static_assert(maskEqVec.y() == true);


    // Inequality tests
    constexpr auto allNeqVec1 = vec1.anyNeq(vec2);
    static_assert(allNeqVec1 == true);

    constexpr auto allNeqVec2 = vec1.anyNeq(vec3);
    static_assert(allNeqVec2 == false);

    constexpr auto allNeqVec3 = fgm::Vec2<int>::anyNeq(vec1, vec2);
    static_assert(allNeqVec3 == true);

    constexpr auto allNeqVec4 = fgm::Vec2<int>::anyNeq(vec1, vec3);
    static_assert(allNeqVec4 == false);

    constexpr auto allNeqVec5 = vec1 != vec2;
    static_assert(allNeqVec5 == true);

    constexpr auto allNeqVec6 = vec1 != vec3;
    static_assert(allNeqVec6 == false);

    constexpr auto maskNeqVec = vec1.neq(vec2);
    static_assert(maskNeqVec.x() == true);
    static_assert(maskNeqVec.y() == false);

} // namespace


/** @brief Verify that @ref fgm::Vec2::allEq returns true for identical vectors. */
TYPED_TEST(Vec2Equality, Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.allEq(this->_eqVecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec2::allEq returns false if any component differ. */
TYPED_TEST(Vec2Equality, Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.allEq(this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vec2::allEq for identical vectors. */
TYPED_TEST(Vec2Equality, StaticWrapper_Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = fgm::Vec2<TypeParam>::allEq(this->_eqVecA, this->_eqVecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vec2::allEq for different vectors. */
TYPED_TEST(Vec2Equality, StaticWrapper_Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = fgm::Vec2<TypeParam>::allEq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec2::allEq follows IEEE 754 for NaN comparisons. */
TEST(Vec2Equality, NanEqualityReturnsFalse)
{
    const fgm::Vec2 vecA = { NAN_F, NAN_F };
    const fgm::Vec2 vecB = { 1.0, -5.88874789 };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality) << "NaN vector shouldn't equal anything!";
}


/** @brief Verify that @ref fgm::Vec2::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec2Equality, InfinityEquality_IdenticalVectorsReturnsTrue)
{
    const fgm::Vec2 vecA = { INF, -INF };
    const fgm::Vec2 vecB = { INF, -INF };

    const bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec2::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec2Equality, InfinityEquality_DifferentVectorsReturnsFalse)
{
    const fgm::Vec2 vecA = { INF, INF };
    const fgm::Vec2 vecB = { INF, -INF };

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator returns true for identical vectors. */
TYPED_TEST(Vec2Equality, EqualityOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA == this->_eqVecB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec2::allEq works for different vector types with identical components. */
TYPED_TEST(Vec2Equality, MixedType_Equality_IdenticalVectorsReturnsTrue)
{
    const fgm::Vec2 vecA(1, 2);
    const fgm::Vec2 vecB(1.0, 2.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec2::allEq works for different vector types with different components. */
TYPED_TEST(Vec2Equality, MixedType_Equality_DifferentVectorsReturnsFalse)
{
    const fgm::Vec2 vecA(5, 6);
    const fgm::Vec2 vecB(1.0, 2.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator returns false if any component differ. */
TYPED_TEST(Vec2Equality, EqualityOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA == this->_dissimilarVec;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator works for bool vector with identical components. */
TEST(Vec2Equality, EqualityOperator_IdenticalBooleanVectorsReturnsTrue)
{
    const fgm::Vec2 vecA(true, false);
    const fgm::Vec2 vecB(true, false);

    const bool equality = vecA == vecB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that the equality operator works for bool vector with different components. */
TEST(Vec2Equality, EqualityOperator_DifferentBooleanVectorsReturnsFalse)
{
    const fgm::Vec2 vecA(true, false);
    const fgm::Vec2 vecB(true, true);

    const bool equality = vecA == vecB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec2::eq returns @ref fgm::Vec2<bool> mask for identical vectors. */
TYPED_TEST(Vec2Equality, EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vec2<bool> mask = this->_eqVecA.eq(this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_equalityMask, mask);
}

/** @brief Verify that @ref fgm::Vec2::eq returns @ref fgm::Vec2<bool> mask for different vectors. */
TEST(Vec2Equality, MixedType_EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vec2 vecA         = { 1, 2 };
    const fgm::Vec2 vecB         = { 1.0, 4.0 };
    const fgm::Vec2 expectedMask = { true, false };

    const fgm::Vec2<bool> mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vec2::eq follows IEEE 754 for NaN comparisons. */
TEST(Vec2Equality, NanEqualityReturnsFalseBooleanMask)
{
    const fgm::Vec2 vecA         = { NAN_F, NAN_F };
    const fgm::Vec2 vecB         = { 1.0, -5.88874789 };
    const fgm::Vec2 expectedMask = { false, false };

    const fgm::Vec2 mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vec2::eq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec2Equality, InfinityEqualityReturnsCorrectBooleanMask)
{
    const fgm::Vec2 vecA         = { INF, -INF };
    const fgm::Vec2<double> vecB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D };
    const fgm::Vec2 expectedMask = { true, false };

    const fgm::Vec2 mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @brief Verify that the static variant of @ref fgm::Vec2::eq returns @ref fgm::Vec2<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vec2Equality, StaticWrapper_EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vec2<bool> mask = fgm::Vec2<TypeParam>::eq(this->_eqVecA, this->_dissimilarVec);

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


/** @brief Verify that @ref fgm::Vec2::anyNeq returns false for identical vectors. */
TYPED_TEST(Vec2Equality, Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.anyNeq(this->_eqVecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec2::anyNeq returns true if any component differ. */
TYPED_TEST(Vec2Equality, Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.anyNeq(this->_dissimilarVec);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vec2::anyNeq for identical vectors. */
TYPED_TEST(Vec2Equality, StaticWrapper_Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = fgm::Vec2<TypeParam>::anyNeq(this->_eqVecA, this->_eqVecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vec2::anyNeq for different vectors. */
TYPED_TEST(Vec2Equality, StaticWrapper_Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = fgm::Vec2<TypeParam>::anyNeq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec2::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Vec2Equality, NanInequalityReturnsTrue)
{
    const fgm::Vec2 vecA = { NAN_F, NAN_F };
    const fgm::Vec2 vecB = { 1.0, -5.88874789 };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec2::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec2Equality, InfinityInequality_IdenticalVectorsReturnsFalse)
{
    const fgm::Vec2 vecA = { INF, -INF };
    const fgm::Vec2 vecB = { INF, -INF };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec2::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec2Equality, InfinityInequality_DifferentVectorsReturnsTrue)
{
    const fgm::Vec2 vecA = { INF, INF };
    const fgm::Vec2 vecB = { INF, -INF };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec2::anyNeq works for different vector types with identical components. */
TYPED_TEST(Vec2Equality, MixedType_Inequality_IdenticalVectorsReturnsFalse)
{
    const fgm::Vec2 vecA(1, 2);
    const fgm::Vec2 vecB(1.0, 2.0);

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec2::anyNeq works for different vector types with different components. */
TYPED_TEST(Vec2Equality, MixedType_Inequality_DifferentVectorsReturnsTrue)
{
    const fgm::Vec2 vecA(5, 6);
    const fgm::Vec2 vecB(1.0, 2.0);

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the operator returns false for identical vectors. */
TYPED_TEST(Vec2Equality, InEqualityOperator_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA != this->_eqVecB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the inequality operator returns true for different vectors. */
TYPED_TEST(Vec2Equality, InEqualityOperator_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA != this->_dissimilarVec;

    EXPECT_TRUE(equality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Vec2<bool> with identical components. */
TEST(Vec2Equality, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    const fgm::Vec2 vecA(true, false);
    const fgm::Vec2 vecB(true, false);

    const bool equality = vecA != vecB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Vec2<bool> with different components. */
TEST(Vec2Equality, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    const fgm::Vec2 vecA(true, false);
    const fgm::Vec2 vecB(true, true);

    const bool equality = vecA != vecB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec2::neq returns @ref fgm::Vec2<bool> mask for identical vectors. */
TYPED_TEST(Vec2Equality, InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vec2<bool> mask = this->_eqVecA.neq(this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}


/** @brief Verify that @ref fgm::Vec2::neq returns @ref fgm::Vec2<bool> mask for different vectors. */
TEST(Vec2Equality, MixedType_InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vec2 vecA         = { 1, 2 };
    const fgm::Vec2 vecB         = { 1.0, 4.0 };
    const fgm::Vec2 expectedMask = { false, true };

    const fgm::Vec2<bool> mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vec2::neq follows IEEE 754 for NaN comparisons. */
TEST(Vec2Equality, NanInequalityReturnsTrueBooleanMask)
{
    const fgm::Vec2 vecA         = { NAN_F, NAN_F };
    const fgm::Vec2 vecB         = { 1.0, -5.88874789 };
    const fgm::Vec2 expectedMask = { true, true };

    const fgm::Vec2 mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vec2::neq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec2Equality, InfinityInequalityReturnsCorrectBooleanMask)
{
    const fgm::Vec2 vecA         = { INF, -INF };
    const fgm::Vec2 vecB         = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D };
    const fgm::Vec2 expectedMask = { false, true };

    const fgm::Vec2 mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @brief Verify that the static variant of @ref fgm::Vec2::neq returns @ref fgm::Vec2<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vec2Equality, StaticWrapper_InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vec2<bool> mask = fgm::Vec2<TypeParam>::neq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}

/** @} */
