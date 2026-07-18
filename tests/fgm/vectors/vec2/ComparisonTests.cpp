/**
 * @file ComparisonTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vec2<bool> comparison operator (>, >=, <, <=) and
 *        their functional counterpart's (gt, gte, lt, lte) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"

#include <fgm/common/Constants.h>



constexpr auto NAN_F = fgm::constants::NaN;
constexpr auto INF   = fgm::constants::INFINITY_F;



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
class Vec2Comparison: public ::testing::Test
{
protected:
    fgm::Vec2<T> _vecA;
    fgm::Vec2<T> _vecB;
    fgm::Vec2<bool> _expectedGT, _expectedGTE, _expectedLT,
        _expectedLTE; // GT-> Greater Than, GTE-> Greater Than or Equal, LT -> Less than, LTE -> Less than or equal

    void SetUp() override
    {
        _vecA        = { T(1.1234568789), T(2.123458319) };
        _vecB        = { T(5.1234568789), T(1.123458319) };
        _expectedGT  = { false, true };
        _expectedGTE = { false, true };
        _expectedLT  = { true, false };
        _expectedLTE = { true, false };
    }
};
/** @brief Test fixture for @fgm::Vec2 comparisons, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vec2Comparison, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec2_GT_Comp
 * @{
 */

/**************************************
 *                                    *
 *         GREATER THAN TESTS         *
 *                                    *
 **************************************/

/** @brief Verify that vector greater than operation is available at compile time. */
namespace
{
    constexpr fgm::Vec2 vec1(1, 2);
    constexpr fgm::Vec2 vec2(1, 3);
    constexpr auto gtVec      = vec1 > vec2;
    constexpr auto gtVecMask1 = vec1.gt(vec2);
    constexpr auto gtVecMask2 = fgm::Vec2<int>::gt(vec1, vec2);

    static_assert(gtVec.x() == false);
    static_assert(gtVec.y() == false);

    static_assert(gtVecMask1.x() == false);
    static_assert(gtVecMask1.y() == false);

    static_assert(gtVecMask2.x() == false);
    static_assert(gtVecMask2.y() == false);

} // namespace


/**
 * @brief Verify that the greater-than (gt) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec2Comparison, GreaterThan_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const fgm::Vec2<bool> mask = this->_vecA.gt(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


/**
 * @brief Verify that the greater-than operator perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec2Comparison, GreaterThanOperator_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const fgm::Vec2<bool> mask = this->_vecA > this->_vecB;

    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


/**
 * @brief Verify that the static variant of greater-than (gt) function performs a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec2Comparison, StaticWrapper_GreaterThan_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const fgm::Vec2<bool> mask = fgm::Vec2<TypeParam>::gt(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


/**
 * @brief Verify that the greater-than (gt) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vec2Comparison, InfinityVector_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vec2 vec(1.2, 4.5);
    const fgm::Vec2 infVec(INF, -INF);
    const fgm::Vec2 expected(false, true);

    const fgm::Vec2<bool> mask = vec.gt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the greater-than (gt) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vec2Comparison, NaNVector_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vec2 vec(1.2f, 4.5f);
    const fgm::Vec2 infVec(NAN_F, NAN_F);
    const fgm::Vec2 expected(false, false);

    const fgm::Vec2<bool> mask = vec.gt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the greater-than (gt) function perform a component-wise comparison
 *       when handling vectors of different types.
 */
TEST(Vec2Comparison, MixedType_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const fgm::Vec2 vecA(1.2, 7.5);
    const fgm::Vec2 vecB(5, 7);
    const fgm::Vec2 expected(false, true);

    // When compared with greater than or equal
    const fgm::Vec2<bool> mask = vecA.gt(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec2_GTE_Comp
 * @{
 */

/**************************************
 *                                    *
 *    GREATER THAN OR EQUALS TESTS    *
 *                                    *
 **************************************/

/** @brief Verify that vector greater than or equals operation is available at compile time. */
namespace
{
    constexpr auto gteVec      = vec1 >= vec2;
    constexpr auto gteVecMask1 = vec1.gte(vec2);
    constexpr auto gteVecMask2 = fgm::Vec2<int>::gte(vec1, vec2);

    static_assert(gteVec.x() == true);
    static_assert(gteVec.y() == false);

    static_assert(gteVecMask1.x() == true);
    static_assert(gteVecMask1.y() == false);

    static_assert(gteVecMask2.x() == true);
    static_assert(gteVecMask2.y() == false);

} // namespace


/**
 * @brief Verify that the greater-than-or-equal (gte) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec2Comparison, GreaterThanOrEqual_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const fgm::Vec2<bool> mask = this->_vecA.gte(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


/**
 * @brief Verify that the greater-than-or-equal operator performs a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec2Comparison, GreaterThanOrEqualOperator_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const fgm::Vec2<bool> mask = this->_vecA >= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


/**
 * @brief Verify that the static variant of greater-than-or-equal (gte) function perform a component-wise
 *       comparison and returns the correct boolean mask.
 */
TYPED_TEST(Vec2Comparison, StaticWrapper_GreaterThanOrEqual_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const fgm::Vec2<bool> mask = fgm::Vec2<TypeParam>::gte(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


/**
 * @brief Verify that the greater-than-or-equal (gte) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vec2Comparison, InfinityVector_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vec2 vec(1.2f, 6.8f);
    const fgm::Vec2 infVec(INF, -INF);
    const fgm::Vec2 expected(false, true);

    const fgm::Vec2<bool> mask = vec.gte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the greater-than-or-equal (gte) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vec2Comparison, NanVector_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vec2 vec(1.2, 6.8);
    const fgm::Vec2 infVec(NAN_F, -5.9f);
    const fgm::Vec2 expected(false, true);

    const fgm::Vec2<bool> mask = vec.gte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the greater-than-or-equal (gte) function performs a component-wise comparison
 *       when handling vectors of different types.
 */
TEST(Vec2Comparison, MixedType_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const fgm::Vec2 vecA(1.2, 7.5);
    const fgm::Vec2 vecB(5, 7);
    const fgm::Vec2 expected(false, true);

    // When compared with greater or equal than
    const fgm::Vec2<bool> mask = vecA.gte(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec2_LT_Comp
 * @{
 */

/**************************************
 *                                    *
 *          LESS THAN TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that vector less than operation is available at compile time. */
namespace
{
    constexpr auto ltVec      = vec1 < vec2;
    constexpr auto ltVecMask1 = vec1.lt(vec2);
    constexpr auto ltVecMask2 = fgm::Vec2<int>::lt(vec1, vec2);

    static_assert(ltVec.x() == false);
    static_assert(ltVec.y() == true);

    static_assert(ltVecMask1.x() == false);
    static_assert(ltVecMask1.y() == true);

    static_assert(ltVecMask2.x() == false);
    static_assert(ltVecMask2.y() == true);

} // namespace


/**
 * @brief Verify that the less-than (lt) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec2Comparison, LessThan_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const fgm::Vec2<bool> mask = this->_vecA.lt(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


/**
 * @brief Verify that the less-than operator perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec2Comparison, LessThanOperator_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const fgm::Vec2<bool> mask = this->_vecA < this->_vecB;

    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


/**
 * @brief Verify that the static variant of less-than (lt) function perform a component-wise comparison and
 *		 returns the correct boolean mask.
 */
TYPED_TEST(Vec2Comparison, StaticWrapper_LessThan_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const fgm::Vec2<bool> mask = fgm::Vec2<TypeParam>::lt(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


/**
 * @brief Verify that the less-than (lt) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vec2Comparison, InfinityVector_LessThan_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vec2 vec(1.2, 6.8);
    const fgm::Vec2 infVec(INF, -INF);
    const fgm::Vec2 expected(true, false);

    const fgm::Vec2<bool> mask = vec.lt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the less-than (lt) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vec2Comparison, NanVector_LessThan_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vec2 vec(1.2f, 6.8f);
    const fgm::Vec2 nanVec(NAN_F, -5.9f);
    const fgm::Vec2 expected(false, false);

#if defined(_MSC_VER) && !defined(__clang__)
    // MSVC constant evaluator incorrectly returns true for NAN_F comparisons.
    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
    // Resharper disable all
    const fgm::Vec2<bool> mask = vec.lt(nanVec);
    // Resharper restore all
#else
    // Clang and GCC follow IEEE 754 strictly at compile-time.
    const fgm::Vec2<bool> mask = vec.lt(nanVec);
#endif

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the less-than (lt) function perform a component-wise comparison
 *       when handling vectors of different types.
 */
TEST(Vec2Comparison, MixedType_LessThan_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const fgm::Vec2 vecA(1.2, 7.5);
    const fgm::Vec2 vecB(5, 7);
    const fgm::Vec2 expected(true, false);

    // When compared with less than or equal
    const fgm::Vec2<bool> mask = vecA.lt(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec2_LTE_Comp
 * @{
 */

/**************************************
 *                                    *
 *      LESS THAN OR EQUALS TESTS     *
 *                                    *
 **************************************/

/** @brief Verify that vector less than or equals operation is available at compile time. */
namespace
{
    constexpr auto lteVec      = vec1 <= vec2;
    constexpr auto lteVecMask1 = vec1.lte(vec2);
    constexpr auto lteVecMask2 = fgm::Vec2<int>::lte(vec1, vec2);

    static_assert(lteVec.x() == true);
    static_assert(lteVec.y() == true);

    static_assert(lteVecMask1.x() == true);
    static_assert(lteVecMask1.y() == true);

    static_assert(lteVecMask2.x() == true);
    static_assert(lteVecMask2.y() == true);

} // namespace


/**
 * @brief Verify that the less-than-or-equal (lte) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec2Comparison, LessThanOrEqual_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const fgm::Vec2<bool> mask = this->_vecA.lte(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


/**
 * @brief Verify that the less-than-or-equal operator perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec2Comparison, LessThanOrEqualOperator_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const fgm::Vec2<bool> mask = this->_vecA <= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


/**
 * @brief Verify that the static variant of less-than-or-equal (lte) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec2Comparison, StaticWrapper_LessThanOrEqual_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const fgm::Vec2<bool> mask = fgm::Vec2<TypeParam>::lte(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


/**
 * @brief Verify that the less-than-or-equal (lte) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vec2Comparison, InfinityVector_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vec2 vec(1.2, 6.8);
    const fgm::Vec2 infVec(INF, -INF);
    const fgm::Vec2 expected(true, false);

    const fgm::Vec2<bool> mask = vec.lte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the less-than-or-equal (lte) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vec2Comparison, NanVector_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vec2 vec(1.2f, 6.8f);
    const fgm::Vec2 nanVec(NAN_F, -5.9f);
    const fgm::Vec2 expected(false, false);

#if defined(_MSC_VER) && !defined(__clang__)
    // MSVC constant evaluator incorrectly returns true for NAN_F comparisons.
    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
    // Resharper disable all
    const fgm::Vec2<bool> mask = vec.lte(nanVec);
    // Resharper restore all
#else
    // Clang and GCC follow IEEE 754 strictly at compile-time.
    const fgm::Vec2<bool> mask = vec.lte(nanVec);
#endif

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the less-than-or-equal (lte) function perform a component-wise comparison
 *       when handling vectors of different types.
 */
TEST(Vec2Comparison, MixedType_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const fgm::Vec2 vecA(1.2, 7.5);
    const fgm::Vec2 vecB(5, 7);
    const fgm::Vec2 expected(true, false);

    // When compared with less than or equal
    const fgm::Vec2<bool> mask = vecA.lte(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}

/** @} */
