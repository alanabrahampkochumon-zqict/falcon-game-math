/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref fgm::Vector4D equality operator (==, !=) and their functional counterpart's (eq, neq, allEq,
 * anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"

#include <fgm/common/Constants.h>


constexpr auto NAN_F = fgm::constants::NaN;
constexpr auto INF   = fgm::constants::INFINITY_F;



template <typename T>
class Vector4DEquality: public ::testing::Test
{
protected:
    fgm::Vector4D<T> _eqVecA;
    fgm::Vector4D<T> _eqVecB;
    fgm::Vector4D<T> _dissimilarVec;
    fgm::Vector4D<bool> _equalityMask;
    fgm::Vector4D<bool> _inequalityMask;


    void SetUp() override
    {
        _eqVecA         = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
        _eqVecB         = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
        _dissimilarVec  = { T(7.1234568789), T(2.123458319), T(24.00), T(123.123489172589) };
        _equalityMask   = { false, true, false, true };
        _inequalityMask = { true, false, true, false };
    }
};

/** @brief Test fixture for @ref fgm::Vector4D, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DEquality, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Equality
 * @{
 */

/** @brief Verify that vector equality operations are available are at compile time. */
namespace
{
    constexpr fgm::Vector4D vec1(1, 2, 4, 12);
    constexpr fgm::Vector4D vec2(3, 2, 1, 7);
    constexpr fgm::Vector4D vec3(1, 2, 4, 12);

    // Equality tests
    constexpr auto allEqVec1 = vec1.allEq(vec2);
    static_assert(allEqVec1 == false);

    constexpr auto allEqVec2 = vec1.allEq(vec3);
    static_assert(allEqVec2 == true);

    constexpr auto allEqVec3 = fgm::Vector4D<int>::allEq(vec1, vec2);
    static_assert(allEqVec3 == false);

    constexpr auto allEqVec4 = fgm::Vector4D<int>::allEq(vec1, vec3);
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

    constexpr auto allNeqVec3 = fgm::Vector4D<int>::anyNeq(vec1, vec2);
    static_assert(allNeqVec3 == true);

    constexpr auto allNeqVec4 = fgm::Vector4D<int>::anyNeq(vec1, vec3);
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

/** @brief Verify that @ref fgm::Vector4D::allEq returns true for identical vectors. */
TYPED_TEST(Vector4DEquality, Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.allEq(this->_eqVecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::allEq returns false if any component differ. */
TYPED_TEST(Vector4DEquality, Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.allEq(this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vector4D::allEq for identical vectors. */
TYPED_TEST(Vector4DEquality, StaticWrapper_Equality_IdenticalVectorsReturnsTrue)
{
    const bool equality = fgm::Vector4D<TypeParam>::allEq(this->_eqVecA, this->_eqVecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vector4D::allEq for different vectors. */
TYPED_TEST(Vector4DEquality, StaticWrapper_Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = fgm::Vector4D<TypeParam>::allEq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::allEq follows IEEE 754 for NaN comparisons. */
TEST(Vector4DEquality, NanEqualityReturnsFalse)
{
    const fgm::Vector4D vecA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Vector4D<double> vecB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityEquality_IdenticalVectorsReturnsTrue)
{
    const fgm::Vector4D vecA = { INF, -INF, INF, -INF };
    const fgm::Vector4D vecB = { INF, -INF, INF, -INF };

    const bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityEquality_DifferentVectorsReturnsFalse)
{
    const fgm::Vector4D vecA = { INF, INF, INF, -INF };
    const fgm::Vector4D vecB = { INF, -INF, INF, INF };

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator returns true for identical vectors. */
TYPED_TEST(Vector4DEquality, EqualityOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA == this->_eqVecB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::allEq works for different vector types with identical components. */
TYPED_TEST(Vector4DEquality, MixedType_Equality_IdenticalVectorsReturnsTrue)
{
    const fgm::Vector4D vecA(1, 2, 3, 4);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::allEq works for different vector types with different components. */
TYPED_TEST(Vector4DEquality, MixedType_Equality_DifferentVectorsReturnsFalse)
{
    const fgm::Vector4D vecA(5, 6, 7, 8);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator returns false if any component differ. */
TYPED_TEST(Vector4DEquality, EqualityOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA == this->_dissimilarVec;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator works for bool vector with identical components. */
TEST(Vector4DEquality, EqualityOperator_IdenticalBooleanVectorsReturnsTrue)
{
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, false, true, false);

    const bool equality = vecA == vecB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that the equality operator works for bool vector with different components. */
TEST(Vector4DEquality, EqualityOperator_DifferentBooleanVectorsReturnsFalse)
{
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, true, true, false);

    const bool equality = vecA == vecB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::eq returns @ref fgm::Vector4D<bool> mask for identical vectors. */
TYPED_TEST(Vector4DEquality, EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D<bool> mask = this->_eqVecA.eq(this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_equalityMask, mask);
}

/** @brief Verify that @ref fgm::Vector4D::eq returns @ref fgm::Vector4D<bool> mask for different vectors. */
TEST(Vector4DEquality, MixedType_EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D vecA         = { 1, 2, 3, 4 };
    const fgm::Vector4D vecB         = { 1.0, 4.0, 0.0, 4.0 };
    const fgm::Vector4D expectedMask = { true, false, false, true };

    const fgm::Vector4D<bool> mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vector4D::eq follows IEEE 754 for NaN comparisons. */
TEST(Vector4DEquality, NanEqualityReturnsFalseBooleanMask)
{
    const fgm::Vector4D vecA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Vector4D vecB         = { 1.0, -5.88874789, fgm::constants::INFINITY_D, fgm::constants::NaN_D };
    const fgm::Vector4D expectedMask = { false, false, false, false };

    const fgm::Vector4D mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vector4D::eq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityEqualityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D vecA         = { INF, -INF, INF, -INF };
    const fgm::Vector4D<double> vecB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11, 10e11 };
    const fgm::Vector4D expectedMask = { true, false, false, false };

    const fgm::Vector4D mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @brief Verify that the static variant of @ref fgm::Vector4D::eq returns @ref fgm::Vector4D<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vector4DEquality, StaticWrapper_EqualityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D<bool> mask = fgm::Vector4D<TypeParam>::eq(this->_eqVecA, this->_dissimilarVec);

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


/** @brief Verify that @ref fgm::Vector4D::anyNeq returns false for identical vectors. */
TYPED_TEST(Vector4DEquality, Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.anyNeq(this->_eqVecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::anyNeq returns true if any component differ. */
TYPED_TEST(Vector4DEquality, Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.anyNeq(this->_dissimilarVec);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vector4D::anyNeq for identical vectors. */
TYPED_TEST(Vector4DEquality, StaticWrapper_Inequality_IdenticalVectorsReturnsFalse)
{
    const bool equality = fgm::Vector4D<TypeParam>::anyNeq(this->_eqVecA, this->_eqVecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Vector4D::anyNeq for different vectors. */
TYPED_TEST(Vector4DEquality, StaticWrapper_Inequality_DifferentVectorsReturnsTrue)
{
    const bool equality = fgm::Vector4D<TypeParam>::anyNeq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Vector4DEquality, NanInequalityReturnsTrue)
{
    const fgm::Vector4D vecA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Vector4D<double> vecB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityInequality_IdenticalVectorsReturnsFalse)
{
    const fgm::Vector4D vecA = { INF, -INF, INF, -INF };
    const fgm::Vector4D vecB = { INF, -INF, INF, -INF };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityInequality_DifferentVectorsReturnsTrue)
{
    const fgm::Vector4D vecA = { INF, INF, INF, -INF };
    const fgm::Vector4D vecB = { INF, -INF, INF, INF };

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::anyNeq works for different vector types with identical components. */
TYPED_TEST(Vector4DEquality, MixedType_Inequality_IdenticalVectorsReturnsFalse)
{
    const fgm::Vector4D vecA(1, 2, 3, 4);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::anyNeq works for different vector types with different components. */
TYPED_TEST(Vector4DEquality, MixedType_Inequality_DifferentVectorsReturnsTrue)
{
    const fgm::Vector4D vecA(5, 6, 7, 8);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.anyNeq(vecB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the operator returns false for identical vectors. */
TYPED_TEST(Vector4DEquality, InEqualityOperator_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA != this->_eqVecB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the inequality operator returns true for different vectors. */
TYPED_TEST(Vector4DEquality, InEqualityOperator_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA != this->_dissimilarVec;

    EXPECT_TRUE(equality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Vector4D<bool> with identical components. */
TEST(Vector4DEquality, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, false, true, false);

    const bool equality = vecA != vecB;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Vector4D<bool> with different components. */
TEST(Vector4DEquality, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, true, true, false);

    const bool equality = vecA != vecB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Vector4D::neq returns @ref fgm::Vector4D<bool> mask for identical vectors. */
TYPED_TEST(Vector4DEquality, InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D<bool> mask = this->_eqVecA.neq(this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}


/** @brief Verify that @ref fgm::Vector4D::neq returns @ref fgm::Vector4D<bool> mask for different vectors. */
TEST(Vector4DEquality, MixedType_InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D vecA         = { 1, 2, 3, 4 };
    const fgm::Vector4D vecB         = { 1.0, 4.0, 0.0, 4.0 };
    const fgm::Vector4D expectedMask = { false, true, true, false };

    const fgm::Vector4D<bool> mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vector4D::neq follows IEEE 754 for NaN comparisons. */
TEST(Vector4DEquality, NanInequalityReturnsTrueBooleanMask)
{
    const fgm::Vector4D vecA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Vector4D<double> vecB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };
    const fgm::Vector4D expectedMask = { true, true, true, true };

    const fgm::Vector4D mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @brief Verify that @ref fgm::Vector4D::neq follows IEEE 754 for INFINITY comparisons. */
TEST(Vector4DEquality, InfinityInequalityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D vecA         = { INF, -INF, INF, -INF };
    const fgm::Vector4D vecB         = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11, 10e11 };
    const fgm::Vector4D expectedMask = { false, true, true, true };

    const fgm::Vector4D mask = vecA.neq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @brief Verify that the static variant of @ref fgm::Vector4D::neq returns @ref fgm::Vector4D<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vector4DEquality, StaticWrapper_InequalityReturnsCorrectBooleanMask)
{
    const fgm::Vector4D<bool> mask = fgm::Vector4D<TypeParam>::neq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}

/** @} */
