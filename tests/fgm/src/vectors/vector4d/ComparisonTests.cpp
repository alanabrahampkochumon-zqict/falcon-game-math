/**
 * @file ComparisonTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref fgm::Vector4<bool> comparison operator (>, >=, <, <=) and their functional counterpart's (gt,
 * gte, lt, lte) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4TestSetup.h"

#include <fgm/common/Constants.h>



constexpr auto NAN_F = fgm::constants::NaN;
constexpr auto INF   = fgm::constants::INFINITY_F;



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
class Vector4Comparison: public ::testing::Test
{
protected:
    fgm::Vector4<T> _vecA;
    fgm::Vector4<T> _vecB;
    fgm::Vec4B _expectedGT, _expectedGTE, _expectedLT,
        _expectedLTE; // GT-> Greater Than, GTE-> Greater Than or Equal, LT -> Less than, LTE -> Less than or equal

    void SetUp() override
    {
        _vecA        = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
        _vecB        = { T(5.1234568789), T(1.123458319), T(8.123412593891), T(123.123489172589) };
        _expectedGT  = { false, true, false, false };
        _expectedGTE = { false, true, false, true };
        _expectedLT  = { true, false, true, false };
        _expectedLTE = { true, false, true, true };
    }
};
/** @brief Test fixture for @fgm::Vector4 comparisons, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector4Comparison, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_GT_Comp
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
    constexpr fgm::Vector4 vec1(1, 2, 5, 2);
    constexpr fgm::Vector4 vec2(1, 3, 4, 4);
    constexpr auto gtVec      = vec1 > vec2;
    constexpr auto gtVecMask1 = vec1.gt(vec2);
    constexpr auto gtVecMask2 = fgm::Vector4<int>::gt(vec1, vec2);

    static_assert(gtVec.x() == false);
    static_assert(gtVec.y() == false);
    static_assert(gtVec.z() == true);
    static_assert(gtVec.w() == false);

    static_assert(gtVecMask1.x() == false);
    static_assert(gtVecMask1.y() == false);
    static_assert(gtVecMask1.z() == true);
    static_assert(gtVecMask1.w() == false);

    static_assert(gtVecMask2.x() == false);
    static_assert(gtVecMask2.y() == false);
    static_assert(gtVecMask2.z() == true);
    static_assert(gtVecMask2.w() == false);

} // namespace


/**
 * @brief Verify that the greater-than (gt) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vector4Comparison, GreaterThan_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const fgm::Vector4<bool> mask = this->_vecA.gt(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


/**
 * @brief Verify that the greater-than operator perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vector4Comparison, GreaterThanOperator_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const fgm::Vector4<bool> mask = this->_vecA > this->_vecB;

    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


/**
 * @brief Verify that the static variant of greater-than (gt) function performs a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vector4Comparison, StaticWrapper_GreaterThan_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const fgm::Vector4<bool> mask = fgm::Vector4<TypeParam>::gt(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


/**
 * @brief Verify that the greater-than (gt) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vector4Comparison, InfinityVector_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4 vec(1.2, 4.5, 6.8, 9.5);
    const fgm::Vector4 infVec(INF, INF, -INF, -INF);
    const fgm::Vector4 expected(false, false, true, true);

    const fgm::Vector4<bool> mask = vec.gt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the greater-than (gt) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vector4Comparison, NaNVector_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4 vec(1.2f, 4.5f, 6.8f, 9.5f);
    const fgm::Vector4 infVec(NAN_F, NAN_F, -5.9f, NAN_F);
    const fgm::Vector4 expected(false, false, true, false);

    const fgm::Vector4<bool> mask = vec.gt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the greater-than (gt) function perform a component-wise comparison
 *       when handling vectors of different types.
 */
TEST(Vector4Comparison, MixedType_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const fgm::Vector4 vecA(1.2, 4.5, 7.5, 9.5);
    const fgm::Vector4 vecB(5, 6, 7, 8);
    const fgm::Vector4 expected(false, false, true, true);

    // When compared with greater than or equal
    const fgm::Vector4<bool> mask = vecA.gt(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec4_GTE_Comp
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
    constexpr auto gteVecMask2 = fgm::Vector4<int>::gte(vec1, vec2);

    static_assert(gteVec.x() == true);
    static_assert(gteVec.y() == false);
    static_assert(gteVec.z() == true);
    static_assert(gteVec.w() == false);

    static_assert(gteVecMask1.x() == true);
    static_assert(gteVecMask1.y() == false);
    static_assert(gteVecMask1.z() == true);
    static_assert(gteVecMask1.w() == false);

    static_assert(gteVecMask2.x() == true);
    static_assert(gteVecMask2.y() == false);
    static_assert(gteVecMask2.z() == true);
    static_assert(gteVecMask2.w() == false);

} // namespace


/**
 * @brief Verify that the greater-than-or-equal (gte) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vector4Comparison, GreaterThanOrEqual_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const fgm::Vector4<bool> mask = this->_vecA.gte(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


/**
 * @brief Verify that the greater-than-or-equal operator performs a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vector4Comparison, GreaterThanOrEqualOperator_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const fgm::Vector4<bool> mask = this->_vecA >= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


/**
 * @brief Verify that the static variant of greater-than-or-equal (gte) function perform a component-wise
 *       comparison and returns the correct boolean mask.
 */
TYPED_TEST(Vector4Comparison, StaticWrapper_GreaterThanOrEqual_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const fgm::Vector4<bool> mask = fgm::Vector4<TypeParam>::gte(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


/**
 * @brief Verify that the greater-than-or-equal (gte) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vector4Comparison, InfinityVector_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4 vec(1.2f, 4.5f, 6.8f, 9.5f);
    const fgm::Vector4 infVec(INF, INF, -INF, -INF);
    const fgm::Vector4 expected(false, false, true, true);

    const fgm::Vector4<bool> mask = vec.gte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the greater-than-or-equal (gte) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vector4Comparison, NanVector_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4 vec(1.2, 4.5, 6.8, 9.5);
    const fgm::Vector4 infVec(NAN_F, NAN_F, -5.9f, NAN_F);
    const fgm::Vector4 expected(false, false, true, false);

    const fgm::Vector4<bool> mask = vec.gte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the greater-than-or-equal (gte) function performs a component-wise comparison
 *       when handling vectors of different types.
 */
TEST(Vector4Comparison, MixedType_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const fgm::Vector4 vecA(1.2, 4.5, 7.5, 9.5);
    const fgm::Vector4 vecB(5, 6, 7, 8);
    const fgm::Vector4 expected(false, false, true, true);

    // When compared with greater or equal than
    const fgm::Vector4<bool> mask = vecA.gte(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec4_LT_Comp
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
    constexpr auto ltVecMask2 = fgm::Vector4<int>::lt(vec1, vec2);

    static_assert(ltVec.x() == false);
    static_assert(ltVec.y() == true);
    static_assert(ltVec.z() == false);
    static_assert(ltVec.w() == true);

    static_assert(ltVecMask1.x() == false);
    static_assert(ltVecMask1.y() == true);
    static_assert(ltVecMask1.z() == false);
    static_assert(ltVecMask1.w() == true);

    static_assert(ltVecMask2.x() == false);
    static_assert(ltVecMask2.y() == true);
    static_assert(ltVecMask2.z() == false);
    static_assert(ltVecMask2.w() == true);

} // namespace


/**
 * @brief Verify that the less-than (lt) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vector4Comparison, LessThan_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const fgm::Vector4<bool> mask = this->_vecA.lt(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


/**
 * @brief Verify that the less-than operator perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vector4Comparison, LessThanOperator_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const fgm::Vector4<bool> mask = this->_vecA < this->_vecB;

    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


/**
 * @brief Verify that the static variant of less-than (lt) function perform a component-wise comparison and
 *		 returns the correct boolean mask.
 */
TYPED_TEST(Vector4Comparison, StaticWrapper_LessThan_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const fgm::Vector4<bool> mask = fgm::Vector4<TypeParam>::lt(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


/**
 * @brief Verify that the less-than (lt) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vector4Comparison, InfinityVector_LessThan_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4 vec(1.2, 4.5, 6.8, 9.5);
    const fgm::Vector4 infVec(INF, INF, -INF, -INF);
    const fgm::Vector4 expected(true, true, false, false);

    const fgm::Vector4<bool> mask = vec.lt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the less-than (lt) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vector4Comparison, NanVector_LessThan_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4 vec(1.2f, 4.5f, 6.8f, 9.5f);
    const fgm::Vector4 nanVec(NAN_F, NAN_F, -5.9f, NAN_F);
    const fgm::Vector4 expected(false, false, false, false);

#if defined(_MSC_VER) && !defined(__clang__)
    // MSVC constant evaluator incorrectly returns true for NAN_F comparisons.
    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
    // Resharper disable all
    const fgm::Vector4<bool> mask = vec.lt(nanVec);
    // Resharper restore all
#else
    // Clang and GCC follow IEEE 754 strictly at compile-time.
    const fgm::Vector4<bool> mask = vec.lt(nanVec);
#endif

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the less-than (lt) function perform a component-wise comparison
 *       when handling vectors of different types.
 */
TEST(Vector4Comparison, MixedType_LessThan_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const fgm::Vector4 vecA(1.2, 4.5, 7.5, 9.5);
    const fgm::Vector4 vecB(5, 6, 7, 8);
    const fgm::Vector4 expected(true, true, false, false);

    // When compared with less than or equal
    const fgm::Vector4<bool> mask = vecA.lt(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec4_LTE_Comp
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
    constexpr auto lteVecMask2 = fgm::Vector4<int>::lte(vec1, vec2);

    static_assert(lteVec.x() == true);
    static_assert(lteVec.y() == true);
    static_assert(lteVec.z() == false);
    static_assert(lteVec.w() == true);

    static_assert(lteVecMask1.x() == true);
    static_assert(lteVecMask1.y() == true);
    static_assert(lteVecMask1.z() == false);
    static_assert(lteVecMask1.w() == true);

    static_assert(lteVecMask2.x() == true);
    static_assert(lteVecMask2.x() == true);
    static_assert(lteVecMask2.z() == false);
    static_assert(lteVecMask2.w() == true);

} // namespace


/**
 * @brief Verify that the less-than-or-equal (lte) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vector4Comparison, LessThanOrEqual_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const fgm::Vector4<bool> mask = this->_vecA.lte(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


/**
 * @brief Verify that the less-than-or-equal operator perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vector4Comparison, LessThanOrEqualOperator_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const fgm::Vector4<bool> mask = this->_vecA <= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


/**
 * @brief Verify that the static variant of less-than-or-equal (lte) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vector4Comparison, StaticWrapper_LessThanOrEqual_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const fgm::Vector4<bool> mask = fgm::Vector4<TypeParam>::lte(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


/**
 * @brief Verify that the less-than-or-equal (lte) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vector4Comparison, InfinityVector_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4 vec(1.2, 4.5, 6.8, 9.5);
    const fgm::Vector4 infVec(INF, INF, -INF, -INF);
    const fgm::Vector4 expected(true, true, false, false);

    const fgm::Vector4<bool> mask = vec.lte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the less-than-or-equal (lte) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vector4Comparison, NanVector_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4 vec(1.2f, 4.5f, 6.8f, 9.5f);
    const fgm::Vector4 nanVec(NAN_F, NAN_F, -5.9f, NAN_F);
    const fgm::Vector4 expected(false, false, false, false);

#if defined(_MSC_VER) && !defined(__clang__)
    // MSVC constant evaluator incorrectly returns true for NAN_F comparisons.
    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
    // Resharper disable all
    const fgm::Vector4<bool> mask = vec.lte(nanVec);
    // Resharper restore all
#else
    // Clang and GCC follow IEEE 754 strictly at compile-time.
    const fgm::Vector4<bool> mask = vec.lte(nanVec);
#endif

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @brief Verify that the less-than-or-equal (lte) function perform a component-wise comparison
 *       when handling vectors of different types.
 */
TEST(Vector4Comparison, MixedType_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const fgm::Vector4 vecA(1.2, 4.5, 7.5, 9.5);
    const fgm::Vector4 vecB(5, 6, 7, 8);
    const fgm::Vector4 expected(true, true, false, false);

    // When compared with less than or equal
    const fgm::Vector4<bool> mask = vecA.lte(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}

/** @} */
