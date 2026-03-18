/**
 * @file ComparisonTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref fgm::Vector4D<bool> comparison operator (>, >=, <, <=) and their functional counterpart's (gt, gte, lt, lte) logic.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;


/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
class Vector4DComparison: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> vecA;
    fgm::Vector4D<T> vecB;
    fgm::bVec4 expectedGT, expectedGTE, expectedLT,
        expectedLTE; // GT-> Greater Than, GTE-> Greater Than or Equal, LT -> Less than, LTE -> Less than or equal

    void SetUp() override
    {
        vecA = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
        vecB = { T(5.1234568789), T(1.123458319), T(8.123412593891), T(123.123489172589) };
        expectedGT = { false, true, false, false };
        expectedGTE = { false, true, false, true };
        expectedLT = { true, false, true, false };
        expectedLTE = { true, false, true, true };
    }
};
/** @brief Test fixture for @fgm::Vector4D comparisons, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector4DComparison, SupportedArithmeticTypes);


/**************************************
 *                                    *
 *         GREATER THAN TESTS         *
 *                                    *
 **************************************/

/**
 * @test Verify that the @ref fgm::Vector4D greater-than (gt) performs a component-wise comparison and returns the
 *		 correct boolean mask.
 */
TYPED_TEST(Vector4DComparison, GreaterThan_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const fgm::Vector4D<bool> mask = this->vecA.gt(this->vecB);

    EXPECT_VEC_EQ(this->expectedGT, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D greater-than operator performs a component-wise comparison and returns the
 *		  correct boolean mask.
 */
TYPED_TEST(Vector4DComparison, GreaterThanOperator_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const fgm::Vector4D<bool> mask = this->vecA > this->vecB;

    EXPECT_VEC_EQ(this->expectedGT, mask);
}


/**
 * @test Verify that the static greater-than (gt) wrapper of @ref fgm::Vector4D performs a component-wise comparison and returns the
 *		 correct boolean mask.
 */
TYPED_TEST(Vector4DComparison, StaticWrapper_GreaterThan_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const fgm::Vector4D<bool> mask = fgm::Vector4D<TypeParam>::gt(this->vecA, this->vecB);

    EXPECT_VEC_EQ(this->expectedGT, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D greater-than (gt) performs a component-wise comparison when handling
 *		 infinite values.
 */
TEST(Vector4DComparison, InfinityVector_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4D vec(1.2, 4.5, 6.8, 9.5);
    const fgm::Vector4D infVec(INFINITY, INFINITY, -INFINITY, -INFINITY);
    const fgm::Vector4D expected(false, false, true, true);

    const fgm::Vector4D<bool> mask = vec.gt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D greater-than (gt) performs a component-wise comparison when handling
 *		 NaN values.
 */
TEST(Vector4DComparison, NaNVector_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4D vec(1.2f, 4.5f, 6.8f, 9.5f);
    const fgm::Vector4D infVec(NAN, NAN, -5.9f, NAN);
    const fgm::Vector4D expected(false, false, true, false);

    const fgm::Vector4D<bool> mask = vec.gt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D greater-than (gt) performs a component-wise comparison when handling
 *		 vectors of different types.
 */
TEST(Vector4DComparison, MixedType_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const fgm::Vector4D vecA(1.2, 4.5, 7.5, 9.5);
    const fgm::Vector4D vecB(5, 6, 7, 8);
    const fgm::Vector4D expected(false, false, true, true);

    // When compared with greater than or equal
    const fgm::Vector4D<bool> mask = vecA.gt(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}




/**************************************
 *                                    *
 *    GREATER THAN OR EQUALS TESTS    *
 *                                    *
 **************************************/

/**
 * @test Verify that the @ref fgm::Vector4D greater-than-or-equal (gte) performs a component-wise comparison and returns the
 *		 correct boolean mask.
 */
TYPED_TEST(Vector4DComparison, GreaterThanOrEqual_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const fgm::Vector4D<bool> mask = this->vecA.gte(this->vecB);

    EXPECT_VEC_EQ(this->expectedGTE, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D greater-than-or-equal operator performs a component-wise comparison and returns the
 *		  correct boolean mask.
 */
TYPED_TEST(Vector4DComparison, GreaterThanOrEqualOperator_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const fgm::Vector4D<bool> mask = this->vecA >= this->vecB;

    EXPECT_VEC_EQ(this->expectedGTE, mask);
}


/**
 * @test Verify that the static greater-than-or-equal (gte) wrapper of @ref fgm::Vector4D performs a component-wise comparison and
 *		 returns the correct boolean mask.
 */
TYPED_TEST(Vector4DComparison,
           StaticWrapper_GreaterThanOrEqual_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const fgm::Vector4D<bool> mask = fgm::Vector4D<TypeParam>::gte(this->vecA, this->vecB);

    EXPECT_VEC_EQ(this->expectedGTE, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D greater-than-or-equal (gte) performs a component-wise comparison when handling
 *		 infinite values.
 */
TEST(Vector4DComparison, InfinityVector_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4D vec(1.2f, 4.5f, 6.8f, 9.5f);
    const fgm::Vector4D infVec(INFINITY, INFINITY, -INFINITY, -INFINITY);
    const fgm::Vector4D expected(false, false, true, true);

    const fgm::Vector4D<bool> mask = vec.gte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D greater-than-or-equal (gte) performs a component-wise comparison when
 *		 handling NaN values.
 */
TEST(Vector4DComparison, NanVector_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4D vec(1.2, 4.5, 6.8, 9.5);
    const fgm::Vector4D infVec(NAN, NAN, -5.9f, NAN);
    const fgm::Vector4D expected(false, false, true, false);

    const fgm::Vector4D<bool> mask = vec.gte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}

/**
 * @test Verify that the @ref fgm::Vector4D greater-than-or-equal (gte) performs a component-wise comparison when handling
 *		 vectors of different types.
 */
TEST(Vector4DComparison, MixedType_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const fgm::Vector4D vecA(1.2, 4.5, 7.5, 9.5);
    const fgm::Vector4D vecB(5, 6, 7, 8);
    const fgm::Vector4D expected(false, false, true, true);

    // When compared with greater or equal than
    const fgm::Vector4D<bool> mask = vecA.gte(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}




/**************************************
 *                                    *
 *          LESS THAN TESTS           *
 *                                    *
 **************************************/

/**
 * @test Verify that the @ref fgm::Vector4D less-than (lt) performs a component-wise comparison and returns the
 *		 correct boolean mask.
 */
TYPED_TEST(Vector4DComparison, LessThan_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const fgm::Vector4D<bool> mask = this->vecA.lt(this->vecB);

    EXPECT_VEC_EQ(this->expectedLT, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D less-than operator performs a component-wise comparison and returns the
 *		  correct boolean mask.
 */
TYPED_TEST(Vector4DComparison, LessThanOperator_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const fgm::Vector4D<bool> mask = this->vecA < this->vecB;

    EXPECT_VEC_EQ(this->expectedLT, mask);
}


/**
 * @test Verify that the static less-than (lt) wrapper of @ref fgm::Vector4D performs a component-wise comparison and
 *		 returns the correct boolean mask.
 */
TYPED_TEST(Vector4DComparison, StaticWrapper_LessThan_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const fgm::Vector4D<bool> mask = fgm::Vector4D<TypeParam>::lt(this->vecA, this->vecB);

    EXPECT_VEC_EQ(this->expectedLT, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D less-than (lt) performs a component-wise comparison when handling
 *		 infinite values.
 */
TEST(Vector4DComparison, InfinityVector_LessThan_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4D vec(1.2, 4.5, 6.8, 9.5);
    const fgm::Vector4D infVec(INFINITY, INFINITY, -INFINITY, -INFINITY);
    const fgm::Vector4D expected(true, true, false, false);

    const fgm::Vector4D<bool> mask = vec.lt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D less-than (lt) performs a component-wise comparison when handling
 *		 NaN values.
 */
TEST(Vector4DComparison, NanVector_LessThan_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4D vec(1.2f, 4.5f, 6.8f, 9.5f);
    const fgm::Vector4D infVec(NAN, NAN, -5.9f, NAN);
    const fgm::Vector4D expected(false, false, false, false);

    const fgm::Vector4D<bool> mask = vec.lt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D less-than (lt) performs a component-wise comparison when
 *		 handling vectors of different types.
 */
TEST(Vector4DComparison, MixedType_LessThan_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const fgm::Vector4D vecA(1.2, 4.5, 7.5, 9.5);
    const fgm::Vector4D vecB(5, 6, 7, 8);
    const fgm::Vector4D expected(true, true, false, false);

    // When compared with less than or equal
    const fgm::Vector4D<bool> mask = vecA.lt(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}




/**************************************
 *                                    *
 *      LESS THAN OR EQUALS TESTS     *
 *                                    *
 **************************************/

/**
 * @test Verify that the @ref fgm::Vector4D less-than-or-equal (lte) performs a component-wise comparison and returns the
 *		 correct boolean mask.
 */
TYPED_TEST(Vector4DComparison, LessThanOrEqual_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const fgm::Vector4D<bool> mask = this->vecA.lte(this->vecB);

    EXPECT_VEC_EQ(this->expectedLTE, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D less-than-or-equal operator performs a component-wise comparison and returns the
 *		  correct boolean mask.
 */
TYPED_TEST(Vector4DComparison, LessThanOrEqualOperator_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const fgm::Vector4D<bool> mask = this->vecA <= this->vecB;

    EXPECT_VEC_EQ(this->expectedLTE, mask);
}


/**
 * @test Verify that the static less-than-or-equal (lte) wrapper of @ref fgm::Vector4D performs a component-wise comparison and
 *		 returns the correct boolean mask.
 */
TYPED_TEST(Vector4DComparison, StaticWrapper_LessThanOrEqual_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const fgm::Vector4D<bool> mask = fgm::Vector4D<TypeParam>::lte(this->vecA, this->vecB);

    EXPECT_VEC_EQ(this->expectedLTE, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D less-than-or-equal (lte) performs a component-wise comparison when handling
 *		 infinite values.
 */
TEST(Vector4DComparison, InfinityVector_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4D vec(1.2, 4.5, 6.8, 9.5);
    const fgm::Vector4D infVec(INFINITY, INFINITY, -INFINITY, -INFINITY);
    const fgm::Vector4D expected(true, true, false, false);

    const fgm::Vector4D<bool> mask = vec.lte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D less-than-or-equal (lte) performs a component-wise comparison when handling
 *		 NaN values.
 */
TEST(Vector4DComparison, NanVector_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    const fgm::Vector4D vec(1.2f, 4.5f, 6.8f, 9.5f);
    const fgm::Vector4D infVec(NAN, NAN, -5.9f, NAN);
    const fgm::Vector4D expected(false, false, false, false);

    const fgm::Vector4D<bool> mask = vec.lte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D less-than-or-equal (lte) performs a component-wise comparison when
 *		 handling vectors of different types.
 */
TEST(Vector4DComparison, MixedType_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const fgm::Vector4D vecA(1.2, 4.5, 7.5, 9.5);
    const fgm::Vector4D vecB(5, 6, 7, 8);
    const fgm::Vector4D expected(true, true, false, false);

    // When compared with less than or equal
    const fgm::Vector4D<bool> mask = vecA.lte(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}
