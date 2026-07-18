/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref fgm::Vec3 equality operator (==, !=) and their functional counterpart's (eq, neq, allEq,
 * anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"

#include <fgm/common/Constants.h>


constexpr auto NAN_F = fgm::constants::NaN;
constexpr auto INF   = fgm::constants::INFINITY_F;



template <typename T>
class Vec3Equality: public ::testing::Test
{
protected:
    fgm::Vec3<T> _eqVecA;
    fgm::Vec3<T> _eqVecB;
    fgm::Vec3<T> _dissimilarVec;
    fgm::Vec3<bool> _equalityMask;
    fgm::Vec3<bool> _inequalityMask;


    void SetUp() override
    {
        _eqVecA         = { T(1.1234568789), T(2.123458319), T(5.123412593891) };
        _eqVecB         = { T(1.1234568789), T(2.123458319), T(5.123412593891) };
        _dissimilarVec  = { T(7.1234568789), T(2.123458319), T(24.00) };
        _equalityMask   = { false, true, false };
        _inequalityMask = { true, false, true };
    }
};

/** @brief Test fixture for @ref fgm::Vec3, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec3Equality, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Equality
 * @{
 */

/** @brief Verify that vector equality operations are available are at compile time. */
namespace
{
    constexpr fgm::Vec3 vec1(1, 2, 4);
    constexpr fgm::Vec3 vec2(3, 2, 1);
    constexpr fgm::Vec3 vec3(1, 2, 4);

    // Equality tests
    constexpr auto allEqVec1 = vec1.allEq(vec2);
    static_assert(allEqVec1 == false);

    constexpr auto allEqVec2 = vec1.allEq(vec3);
    static_assert(allEqVec2 == true);

    constexpr auto allEqVec3 = fgm::Vec3<int>::allEq(vec1, vec2);
    static_assert(allEqVec3 == false);

    constexpr auto allEqVec4 = fgm::Vec3<int>::allEq(vec1, vec3);
    static_assert(allEqVec4 == true);

    constexpr auto allEqVec5 = vec1 == vec2;
    static_assert(allEqVec5 == false);

    constexpr auto allEqVec6 = vec1 == vec3;
    static_assert(allEqVec6 == true);

    constexpr auto maskEqVec = vec1.eq(vec2);
    static_assert(maskEqVec.x() == false);
    static_assert(maskEqVec.y() == true);
    static_assert(maskEqVec.z() == false);


    // Inequality tests
    constexpr auto allNeqVec1 = vec1.anyNeq(vec2);
    static_assert(allNeqVec1 == true);

    constexpr auto allNeqVec2 = vec1.anyNeq(vec3);
    static_assert(allNeqVec2 == false);

    constexpr auto allNeqVec3 = fgm::Vec3<int>::anyNeq(vec1, vec2);
    static_assert(allNeqVec3 == true);

    constexpr auto allNeqVec4 = fgm::Vec3<int>::anyNeq(vec1, vec3);
    static_assert(allNeqVec4 == false);

    constexpr auto allNeqVec5 = vec1 != vec2;
    static_assert(allNeqVec5 == true);

    constexpr auto allNeqVec6 = vec1 != vec3;
    static_assert(allNeqVec6 == false);

    constexpr auto maskNeqVec = vec1.neq(vec2);
    static_assert(maskNeqVec.x() == true);
    static_assert(maskNeqVec.y() == false);
    static_assert(maskNeqVec.z() == true);

} // namespace


/**************************************
 *                                    *
 *           EQUALITY TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Vec3::allEq returns true for identical vectors. */
TYPED_TEST(Vec3Equality, Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.allEq(this->_eqVecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec3::allEq returns false if any component differ. */
TYPED_TEST(Vec3Equality, Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.allEq(this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vec3::allEq for identical vectors. */
TYPED_TEST(Vec3Equality, StaticWrapper_Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = fgm::Vec3<TypeParam>::allEq(this->_eqVecA, this->_eqVecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vec3::allEq for different vectors. */
TYPED_TEST(Vec3Equality, StaticWrapper_Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = fgm::Vec3<TypeParam>::allEq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec3::allEq follows IEEE 754 for NaN comparisons. */
TEST(Vec3Equality, NanEqualityReturnsFalse)
{
    const fgm::Vec3 vecA = { NAN_F, NAN_F, NAN_F };
    const fgm::Vec3 vecB = { 1.0, -5.88874789, fgm::constants::INFINITY_D };

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec3::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec3Equality, InfinityEquality_IdenticalVectorsReturnsTrue)
{
    const fgm::Vec3 vecA = { INF, -INF, INF };
    const fgm::Vec3 vecB = { INF, -INF, INF };

    const bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec3::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec3Equality, InfinityEquality_DifferentVectorsReturnsFalse)
{
    const fgm::Vec3 vecA = { INF, INF, INF };
    const fgm::Vec3 vecB = { INF, -INF, INF };

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator returns true for identical vectors. */
TYPED_TEST(Vec3Equality, EqualityOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA == this->_eqVecB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec3::allEq works for different vector types with identical components. */
TYPED_TEST(Vec3Equality, MixedType_Equality_IdenticalVectorsReturnsTrue)
{
    const fgm::Vec3 vecA(1, 2, 3);
    const fgm::Vec3 vecB(1.0, 2.0, 3.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec3::allEq works for different vector types with different components. */
TYPED_TEST(Vec3Equality, MixedType_Equality_DifferentVectorsReturnsFalse)
{
    const fgm::Vec3 vecA(5, 6, 7);
    const fgm::Vec3 vecB(1.0, 2.0, 3.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator returns false if any component differ. */
TYPED_TEST(Vec3Equality, EqualityOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA == this->_dissimilarVec;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator works for bool vector with identical components. */
TEST(Vec3Equality, EqualityOperator_IdenticalBooleanVectorsReturnsTrue)
{
    const fgm::Vec3 vecA(true, false, true);
    const fgm::Vec3 vecB(true, false, true);

    const bool equality = vecA == vecB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that the equality operator works for bool vector with different components. */
TEST(Vec3Equality, EqualityOperator_DifferentBooleanVectorsReturnsFalse)
{
    const fgm::Vec3 vecA(true, false, true);
    const fgm::Vec3 vecB(true, true, true);

    const bool equality = vecA == vecB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec3::eq returns @ref fgm::Vec3<bool> mask for identical vectors. */
TYPED_TEST(Vec3Equality, EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vec3<bool> mask = this->_eqVecA.eq(this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_equalityMask, mask);
}

/** @brief Verify that @ref fgm::Vec3::eq returns @ref fgm::Vec3<bool> mask for different vectors. */
TEST(Vec3Equality, MixedType_EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vec3 vecA         = { 1, 2, 3 };
    const fgm::Vec3 vecB         = { 1.0, 4.0, 0.0 };
    const fgm::Vec3 expectedMask = { true, false, false };

    const fgm::Vec3<bool> mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vec3::eq follows IEEE 754 for NaN comparisons. */
TEST(Vec3Equality, NanEqualityReturnsFalseBooleanMask)
{
    const fgm::Vec3 vecA         = { NAN_F, NAN_F, NAN_F };
    const fgm::Vec3 vecB         = { 1.0, -5.88874789, fgm::constants::INFINITY_D };
    const fgm::Vec3 expectedMask = { false, false, false };

    const fgm::Vec3 mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vec3::eq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec3Equality, InfinityEqualityReturnsCorrectBooleanMask)
{
    const fgm::Vec3 vecA         = { INF, -INF, INF };
    const fgm::Vec3<double> vecB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11 };
    const fgm::Vec3 expectedMask = { true, false, false };

    const fgm::Vec3 mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @brief Verify that the static variant of @ref fgm::Vec3::eq returns @ref fgm::Vec3<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vec3Equality, StaticWrapper_EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vec3<bool> mask = fgm::Vec3<TypeParam>::eq(this->_eqVecA, this->_dissimilarVec);

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


/** @brief Verify that @ref fgm::Vec3::anyNeq returns false for identical vectors. */
TYPED_TEST(Vec3Equality, Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.anyNeq(this->_eqVecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec3::anyNeq returns true if any component differ. */
TYPED_TEST(Vec3Equality, Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.anyNeq(this->_dissimilarVec);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vec3::anyNeq for identical vectors. */
TYPED_TEST(Vec3Equality, StaticWrapper_Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = fgm::Vec3<TypeParam>::anyNeq(this->_eqVecA, this->_eqVecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vec3::anyNeq for different vectors. */
TYPED_TEST(Vec3Equality, StaticWrapper_Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = fgm::Vec3<TypeParam>::anyNeq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec3::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Vec3Equality, NanInequalityReturnsTrue)
{
    const fgm::Vec3 vecA         = { NAN_F, NAN_F, NAN_F };
    const fgm::Vec3<double> vecB = {
        1.0,
        -5.88874789,
        fgm::constants::INFINITY_D,
    };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec3::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec3Equality, InfinityInequality_IdenticalVectorsReturnsFalse)
{
    const fgm::Vec3 vecA = { INF, -INF, INF };
    const fgm::Vec3 vecB = { INF, -INF, INF };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec3::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec3Equality, InfinityInequality_DifferentVectorsReturnsTrue)
{
    const fgm::Vec3 vecA = { INF, INF, INF };
    const fgm::Vec3 vecB = { INF, -INF, INF };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec3::anyNeq works for different vector types with identical components. */
TYPED_TEST(Vec3Equality, MixedType_Inequality_IdenticalVectorsReturnsFalse)
{
    const fgm::Vec3 vecA(1, 2, 3);
    const fgm::Vec3 vecB(1.0, 2.0, 3.0);

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec3::anyNeq works for different vector types with different components. */
TYPED_TEST(Vec3Equality, MixedType_Inequality_DifferentVectorsReturnsTrue)
{
    const fgm::Vec3 vecA(5, 6, 7);
    const fgm::Vec3 vecB(1.0, 2.0, 3.0);

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the operator returns false for identical vectors. */
TYPED_TEST(Vec3Equality, InEqualityOperator_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA != this->_eqVecB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the inequality operator returns true for different vectors. */
TYPED_TEST(Vec3Equality, InEqualityOperator_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA != this->_dissimilarVec;

    EXPECT_TRUE(equality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Vec3<bool> with identical components. */
TEST(Vec3Equality, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    const fgm::Vec3 vecA(true, false, true);
    const fgm::Vec3 vecB(true, false, true);

    const bool equality = vecA != vecB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Vec3<bool> with different components. */
TEST(Vec3Equality, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    const fgm::Vec3 vecA(true, false, true);
    const fgm::Vec3 vecB(true, true, true);

    const bool equality = vecA != vecB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec3::neq returns @ref fgm::Vec3<bool> mask for identical vectors. */
TYPED_TEST(Vec3Equality, InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vec3<bool> mask = this->_eqVecA.neq(this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}


/** @brief Verify that @ref fgm::Vec3::neq returns @ref fgm::Vec3<bool> mask for different vectors. */
TEST(Vec3Equality, MixedType_InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vec3 vecA         = { 1, 2, 3 };
    const fgm::Vec3 vecB         = { 1.0, 4.0, 0.0 };
    const fgm::Vec3 expectedMask = { false, true, true };

    const fgm::Vec3<bool> mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vec3::neq follows IEEE 754 for NaN comparisons. */
TEST(Vec3Equality, NanInequalityReturnsTrueBooleanMask)
{
    const fgm::Vec3 vecA         = { NAN_F, NAN_F, NAN_F };
    const fgm::Vec3<double> vecB = { 1.0, -5.88874789, fgm::constants::INFINITY_D };
    const fgm::Vec3 expectedMask = { true, true, true };

    const fgm::Vec3 mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vec3::neq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec3Equality, InfinityInequalityReturnsCorrectBooleanMask)
{
    const fgm::Vec3 vecA         = { INF, -INF, INF };
    const fgm::Vec3 vecB         = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11 };
    const fgm::Vec3 expectedMask = { false, true, true };

    const fgm::Vec3 mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @brief Verify that the static variant of @ref fgm::Vec3::neq returns @ref fgm::Vec3<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vec3Equality, StaticWrapper_InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vec3<bool> mask = fgm::Vec3<TypeParam>::neq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}

/** @} */
