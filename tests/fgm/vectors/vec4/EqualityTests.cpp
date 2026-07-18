/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref fgm::Vec4 equality operator (==, !=) and their functional counterpart's (eq, neq, allEq,
 * anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"

#include <fgm/common/Constants.h>


constexpr auto NAN_F = fgm::constants::NaN;
constexpr auto INF   = fgm::constants::INFINITY_F;



template <typename T>
class Vec4Equality: public ::testing::Test
{
protected:
    fgm::Vec4<T> _eqVecA;
    fgm::Vec4<T> _eqVecB;
    fgm::Vec4<T> _dissimilarVec;
    fgm::Vec4<bool> _equalityMask;
    fgm::Vec4<bool> _inequalityMask;


    void SetUp() override
    {
        _eqVecA         = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
        _eqVecB         = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
        _dissimilarVec  = { T(7.1234568789), T(2.123458319), T(24.00), T(123.123489172589) };
        _equalityMask   = { false, true, false, true };
        _inequalityMask = { true, false, true, false };
    }
};

/** @brief Test fixture for @ref fgm::Vec4, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec4Equality, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Equality
 * @{
 */

/** @brief Verify that vector equality operations are available are at compile time. */
namespace
{
    constexpr fgm::Vec4 vec1(1, 2, 4, 12);
    constexpr fgm::Vec4 vec2(3, 2, 1, 7);
    constexpr fgm::Vec4 vec3(1, 2, 4, 12);

    // Equality tests
    constexpr auto allEqVec1 = vec1.allEq(vec2);
    static_assert(allEqVec1 == false);

    constexpr auto allEqVec2 = vec1.allEq(vec3);
    static_assert(allEqVec2 == true);

    constexpr auto allEqVec3 = fgm::Vec4<int>::allEq(vec1, vec2);
    static_assert(allEqVec3 == false);

    constexpr auto allEqVec4 = fgm::Vec4<int>::allEq(vec1, vec3);
    static_assert(allEqVec4 == true);

    constexpr auto allEqVec5 = vec1 == vec2;
    static_assert(allEqVec5 == false);

    constexpr auto allEqVec6 = vec1 == vec3;
    static_assert(allEqVec6 == true);

    constexpr auto maskEqVec = vec1.eq(vec2);
    static_assert(maskEqVec.x() == false);
    static_assert(maskEqVec.y() == true);
    static_assert(maskEqVec.z() == false);
    static_assert(maskEqVec.w() == false);


    // Inequality tests
    constexpr auto allNeqVec1 = vec1.anyNeq(vec2);
    static_assert(allNeqVec1 == true);

    constexpr auto allNeqVec2 = vec1.anyNeq(vec3);
    static_assert(allNeqVec2 == false);

    constexpr auto allNeqVec3 = fgm::Vec4<int>::anyNeq(vec1, vec2);
    static_assert(allNeqVec3 == true);

    constexpr auto allNeqVec4 = fgm::Vec4<int>::anyNeq(vec1, vec3);
    static_assert(allNeqVec4 == false);

    constexpr auto allNeqVec5 = vec1 != vec2;
    static_assert(allNeqVec5 == true);

    constexpr auto allNeqVec6 = vec1 != vec3;
    static_assert(allNeqVec6 == false);

    constexpr auto maskNeqVec = vec1.neq(vec2);
    static_assert(maskNeqVec.x() == true);
    static_assert(maskNeqVec.y() == false);
    static_assert(maskNeqVec.z() == true);
    static_assert(maskNeqVec.w() == true);

} // namespace


/**************************************
 *                                    *
 *           EQUALITY TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Vec4::allEq returns true for identical vectors. */
TYPED_TEST(Vec4Equality, Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.allEq(this->_eqVecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec4::allEq returns false if any component differ. */
TYPED_TEST(Vec4Equality, Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.allEq(this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vec4::allEq for identical vectors. */
TYPED_TEST(Vec4Equality, StaticWrapper_Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = fgm::Vec4<TypeParam>::allEq(this->_eqVecA, this->_eqVecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vec4::allEq for different vectors. */
TYPED_TEST(Vec4Equality, StaticWrapper_Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = fgm::Vec4<TypeParam>::allEq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec4::allEq follows IEEE 754 for NaN comparisons. */
TEST(Vec4Equality, NanEqualityReturnsFalse)
{
    const fgm::Vec4 vecA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Vec4<double> vecB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec4::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec4Equality, InfinityEquality_IdenticalVectorsReturnsTrue)
{
    const fgm::Vec4 vecA = { INF, -INF, INF, -INF };
    const fgm::Vec4 vecB = { INF, -INF, INF, -INF };

    const bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec4::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec4Equality, InfinityEquality_DifferentVectorsReturnsFalse)
{
    const fgm::Vec4 vecA = { INF, INF, INF, -INF };
    const fgm::Vec4 vecB = { INF, -INF, INF, INF };

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator returns true for identical vectors. */
TYPED_TEST(Vec4Equality, EqualityOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA == this->_eqVecB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec4::allEq works for different vector types with identical components. */
TYPED_TEST(Vec4Equality, MixedType_Equality_IdenticalVectorsReturnsTrue)
{
    const fgm::Vec4 vecA(1, 2, 3, 4);
    const fgm::Vec4 vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec4::allEq works for different vector types with different components. */
TYPED_TEST(Vec4Equality, MixedType_Equality_DifferentVectorsReturnsFalse)
{
    const fgm::Vec4 vecA(5, 6, 7, 8);
    const fgm::Vec4 vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator returns false if any component differ. */
TYPED_TEST(Vec4Equality, EqualityOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA == this->_dissimilarVec;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator works for bool vector with identical components. */
TEST(Vec4Equality, EqualityOperator_IdenticalBooleanVectorsReturnsTrue)
{
    const fgm::Vec4 vecA(true, false, true, false);
    const fgm::Vec4 vecB(true, false, true, false);

    const bool equality = vecA == vecB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that the equality operator works for bool vector with different components. */
TEST(Vec4Equality, EqualityOperator_DifferentBooleanVectorsReturnsFalse)
{
    const fgm::Vec4 vecA(true, false, true, false);
    const fgm::Vec4 vecB(true, true, true, false);

    const bool equality = vecA == vecB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec4::eq returns @ref fgm::Vec4<bool> mask for identical vectors. */
TYPED_TEST(Vec4Equality, EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vec4<bool> mask = this->_eqVecA.eq(this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_equalityMask, mask);
}

/** @brief Verify that @ref fgm::Vec4::eq returns @ref fgm::Vec4<bool> mask for different vectors. */
TEST(Vec4Equality, MixedType_EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vec4 vecA         = { 1, 2, 3, 4 };
    const fgm::Vec4 vecB         = { 1.0, 4.0, 0.0, 4.0 };
    const fgm::Vec4 expectedMask = { true, false, false, true };

    const fgm::Vec4<bool> mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vec4::eq follows IEEE 754 for NaN comparisons. */
TEST(Vec4Equality, NanEqualityReturnsFalseBooleanMask)
{
    const fgm::Vec4 vecA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Vec4 vecB         = { 1.0, -5.88874789, fgm::constants::INFINITY_D, fgm::constants::NaN_D };
    const fgm::Vec4 expectedMask = { false, false, false, false };

    const fgm::Vec4 mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vec4::eq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec4Equality, InfinityEqualityReturnsCorrectBooleanMask)
{
    const fgm::Vec4 vecA         = { INF, -INF, INF, -INF };
    const fgm::Vec4<double> vecB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11, 10e11 };
    const fgm::Vec4 expectedMask = { true, false, false, false };

    const fgm::Vec4 mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @brief Verify that the static variant of @ref fgm::Vec4::eq returns @ref fgm::Vec4<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vec4Equality, StaticWrapper_EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vec4<bool> mask = fgm::Vec4<TypeParam>::eq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_equalityMask, mask);
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


/** @brief Verify that @ref fgm::Vec4::anyNeq returns false for identical vectors. */
TYPED_TEST(Vec4Equality, Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.anyNeq(this->_eqVecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec4::anyNeq returns true if any component differ. */
TYPED_TEST(Vec4Equality, Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.anyNeq(this->_dissimilarVec);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vec4::anyNeq for identical vectors. */
TYPED_TEST(Vec4Equality, StaticWrapper_Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = fgm::Vec4<TypeParam>::anyNeq(this->_eqVecA, this->_eqVecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vec4::anyNeq for different vectors. */
TYPED_TEST(Vec4Equality, StaticWrapper_Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = fgm::Vec4<TypeParam>::anyNeq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec4::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Vec4Equality, NanInequalityReturnsTrue)
{
    const fgm::Vec4 vecA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Vec4<double> vecB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec4::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec4Equality, InfinityInequality_IdenticalVectorsReturnsFalse)
{
    const fgm::Vec4 vecA = { INF, -INF, INF, -INF };
    const fgm::Vec4 vecB = { INF, -INF, INF, -INF };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec4::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec4Equality, InfinityInequality_DifferentVectorsReturnsTrue)
{
    const fgm::Vec4 vecA = { INF, INF, INF, -INF };
    const fgm::Vec4 vecB = { INF, -INF, INF, INF };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec4::anyNeq works for different vector types with identical components. */
TYPED_TEST(Vec4Equality, MixedType_Inequality_IdenticalVectorsReturnsFalse)
{
    const fgm::Vec4 vecA(1, 2, 3, 4);
    const fgm::Vec4 vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vec4::anyNeq works for different vector types with different components. */
TYPED_TEST(Vec4Equality, MixedType_Inequality_DifferentVectorsReturnsTrue)
{
    const fgm::Vec4 vecA(5, 6, 7, 8);
    const fgm::Vec4 vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the operator returns false for identical vectors. */
TYPED_TEST(Vec4Equality, InEqualityOperator_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA != this->_eqVecB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the inequality operator returns true for different vectors. */
TYPED_TEST(Vec4Equality, InEqualityOperator_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA != this->_dissimilarVec;

    EXPECT_TRUE(equality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Vec4<bool> with identical components. */
TEST(Vec4Equality, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    const fgm::Vec4 vecA(true, false, true, false);
    const fgm::Vec4 vecB(true, false, true, false);

    const bool equality = vecA != vecB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Vec4<bool> with different components. */
TEST(Vec4Equality, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    const fgm::Vec4 vecA(true, false, true, false);
    const fgm::Vec4 vecB(true, true, true, false);

    const bool equality = vecA != vecB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vec4::neq returns @ref fgm::Vec4<bool> mask for identical vectors. */
TYPED_TEST(Vec4Equality, InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vec4<bool> mask = this->_eqVecA.neq(this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}


/** @brief Verify that @ref fgm::Vec4::neq returns @ref fgm::Vec4<bool> mask for different vectors. */
TEST(Vec4Equality, MixedType_InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vec4 vecA         = { 1, 2, 3, 4 };
    const fgm::Vec4 vecB         = { 1.0, 4.0, 0.0, 4.0 };
    const fgm::Vec4 expectedMask = { false, true, true, false };

    const fgm::Vec4<bool> mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vec4::neq follows IEEE 754 for NaN comparisons. */
TEST(Vec4Equality, NanInequalityReturnsTrueBooleanMask)
{
    const fgm::Vec4 vecA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Vec4<double> vecB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };
    const fgm::Vec4 expectedMask = { true, true, true, true };

    const fgm::Vec4 mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vec4::neq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec4Equality, InfinityInequalityReturnsCorrectBooleanMask)
{
    const fgm::Vec4 vecA         = { INF, -INF, INF, -INF };
    const fgm::Vec4 vecB         = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11, 10e11 };
    const fgm::Vec4 expectedMask = { false, true, true, true };

    const fgm::Vec4 mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @brief Verify that the static variant of @ref fgm::Vec4::neq returns @ref fgm::Vec4<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vec4Equality, StaticWrapper_InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vec4<bool> mask = fgm::Vec4<TypeParam>::neq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}

/** @} */
