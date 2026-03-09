/**
 * @file ComparisonTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief `Vector4D` comparision operation (>, <, <=, >= and their functional counterparts like greaterThanOrEqual) tests.
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
    math::Vector4D<T> vecA;
    math::Vector4D<T> vecB;
    math::bVec4 expectedGT, expectedGTE, expectedLT,
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
TYPED_TEST_SUITE(Vector4DComparison, SupportedArithmeticTypes);


/**************************************
 *                                    *
 *         GREATER THAN TESTS         *
 *                                    *
 **************************************/

TYPED_TEST(Vector4DComparison, GreaterThan_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    // Given two arbitrary vectors
    // When compared with greater than
    const math::Vector4D<bool> result = this->vecA.greaterThan(this->vecB);

    // Then, the resulting elements are true iff first elements are greater than second
    EXPECT_VEC_EQ(this->expectedGT, result);
}

TYPED_TEST(Vector4DComparison, GreaterThanOperator_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    // Given two arbitrary vectors
    // When compared with greater than operator
    const math::Vector4D<bool> result = this->vecA > this->vecB;

    // Then, the resulting elements are true iff first elements are greater than second
    EXPECT_VEC_EQ(this->expectedGT, result);
}

TYPED_TEST(Vector4DComparison, StaticWrapper_GreaterThan_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    // Given two arbitrary vectors
    // When compared with greater than static wrapper
    const math::Vector4D<bool> result = math::Vector4D<TypeParam>::greaterThan(this->vecA, this->vecB);

    // Then, the resulting elements are true iff first elements are greater than second
    EXPECT_VEC_EQ(this->expectedGT, result);
}

TEST(Vector4DComparison, InfinityVector_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
{
    // Given an arbitrary vector and an infinity vector
    math::Vector4D vec(1.2, 4.5, 6.8, 9.5);
    math::Vector4D infVec(INFINITY, INFINITY, -INFINITY, -INFINITY);
    math::Vector4D expected(false, false, true, true);

    // When compared with greater than
    const math::Vector4D<bool> result = vec.greaterThan(infVec);

    // Then, the resulting elements are true for INFINITY and FALSE FOR -INFINITY
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DComparison, NanVector_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
{
    // Given an arbitrary vector and a nan vector
    double nan = std::numeric_limits<double>::quiet_NaN();
    math::Vector4D vec(1.2, 4.5, 6.8, 9.5);
    math::Vector4D infVec(nan, nan, -5.9, nan);
    math::Vector4D expected(false, false, true, false);

    // When compared with greater than
    const math::Vector4D<bool> result = vec.greaterThan(infVec);

    // Then, the resulting elements are false for Nan
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DComparison, MixedType_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    math::Vector4D vecA(1.2, 4.5, 7.5, 9.5);
    math::Vector4D vecB(5, 6, 7, 8);
    math::Vector4D expected(false, false, true, true);

    // When compared with greater than or equal
    const math::Vector4D<bool> result = vecA.greaterThan(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, result);
}


/**************************************
 *                                    *
 *    GREATER THAN OR EQUALS TESTS    *
 *                                    *
 **************************************/

TYPED_TEST(Vector4DComparison, GreaterThanOrEqual_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    // Given two arbitrary vectors
    // When compared with greater than or equal
    const math::Vector4D<bool> result = this->vecA.greaterThanOrEqual(this->vecB);

    // Then, the resulting elements are true iff first elements are greater than second
    EXPECT_VEC_EQ(this->expectedGTE, result);
}

TYPED_TEST(Vector4DComparison, GreaterThanOrEqualOperator_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    // Given two arbitrary vectors
    // When compared with greater than or equal
    const math::Vector4D<bool> result = this->vecA >= this->vecB;

    // Then, the resulting elements are true iff first elements are greater than second
    EXPECT_VEC_EQ(this->expectedGTE, result);
}

TYPED_TEST(Vector4DComparison,
           StaticWrapper_GreaterThanOrEqual_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    // Given two arbitrary vectors
    // When compared with greater than or equal static wrapper
    const math::Vector4D<bool> result = math::Vector4D<TypeParam>::greaterThanOrEqual(this->vecA, this->vecB);

    // Then, the resulting elements are true iff first elements are greater or equal to second
    EXPECT_VEC_EQ(this->expectedGTE, result);
}

TEST(Vector4DComparison, InfinityVector_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    // Given an arbitrary vector and an infinity vector
    math::Vector4D vec(1.2, 4.5, 6.8, 9.5);
    math::Vector4D infVec(INFINITY, INFINITY, -INFINITY, -INFINITY);
    math::Vector4D expected(false, false, true, true);

    // When compared with greater than or equal
    const math::Vector4D<bool> result = vec.greaterThanOrEqual(infVec);

    // Then, the resulting elements are true for INFINITY and FALSE FOR -INFINITY
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DComparison, NanVector_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    // Given an arbitrary vector and a nan vector
    double nan = std::numeric_limits<double>::quiet_NaN();
    math::Vector4D vec(1.2, 4.5, 6.8, 9.5);
    math::Vector4D infVec(nan, nan, -5.9, nan);
    math::Vector4D expected(false, false, true, false);

    // When compared with greater than or equal
    const math::Vector4D<bool> result = vec.greaterThanOrEqual(infVec);

    // Then, the resulting elements are false for Nan
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DComparison, MixedType_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    math::Vector4D vecA(1.2, 4.5, 7.5, 9.5);
    math::Vector4D vecB(5, 6, 7, 8);
    math::Vector4D expected(false, false, true, true);

    // When compared with greater or equal than
    const math::Vector4D<bool> result = vecA.greaterThanOrEqual(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, result);
}


/**************************************
 *                                    *
 *          LESS THAN TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Vector4DComparison, LessThan_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    // Given two arbitrary vectors
    // When compared with less than
    const math::Vector4D<bool> result = this->vecA.lessThan(this->vecB);

    // Then, the resulting elements are true iff first elements are less than second
    EXPECT_VEC_EQ(this->expectedLT, result);
}

TYPED_TEST(Vector4DComparison, LessThanOperator_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    // Given two arbitrary vectors
    // When compared with less than operator
    const math::Vector4D<bool> result = this->vecA < this->vecB;

    // Then, the resulting elements are true iff first elements are less than second
    EXPECT_VEC_EQ(this->expectedLT, result);
}

TYPED_TEST(Vector4DComparison, StaticWrapper_LessThan_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    // Given two arbitrary vectors
    // When compared with less than static wrapper
    const math::Vector4D<bool> result = math::Vector4D<TypeParam>::lessThan(this->vecA, this->vecB);

    // Then, the resulting elements are true iff first elements are less than second
    EXPECT_VEC_EQ(this->expectedLT, result);
}

TEST(Vector4DComparison, InfinityVector_LessThan_ReturnsBooleanVectorWithCorrectValues)
{
    // Given an arbitrary vector and an infinity vector
    math::Vector4D vec(1.2, 4.5, 6.8, 9.5);
    math::Vector4D infVec(INFINITY, INFINITY, -INFINITY, -INFINITY);
    math::Vector4D expected(true, true, false, false);

    // When compared with less than
    const math::Vector4D<bool> result = vec.lessThan(infVec);

    // Then, the resulting elements are FALSE for INFINITY and TRUE FOR -INFINITY
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DComparison, NanVector_LessThan_ReturnsBooleanVectorWithCorrectValues)
{
    // Given an arbitrary vector and a nan vector
    double nan = std::numeric_limits<double>::quiet_NaN();
    math::Vector4D vec(1.2, 4.5, 6.8, 9.5);
    math::Vector4D infVec(nan, nan, -5.9, nan);
    math::Vector4D expected(false, false, false, false);

    // When compared with less than
    const math::Vector4D<bool> result = vec.lessThan(infVec);

    // Then, the resulting elements are false for Nan
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DComparison, MixedType_LessThan_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    math::Vector4D vecA(1.2, 4.5, 7.5, 9.5);
    math::Vector4D vecB(5, 6, 7, 8);
    math::Vector4D expected(true, true, false, false);

    // When compared with less than or equal
    const math::Vector4D<bool> result = vecA.lessThan(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, result);
}


/**************************************
 *                                    *
 *      LESS THAN OR EQUALS TESTS     *
 *                                    *
 **************************************/

TYPED_TEST(Vector4DComparison, LessThanOrEqual_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    // Given two arbitrary vectors
    // When compared with less than or equal
    const math::Vector4D<bool> result = this->vecA.lessThanOrEqual(this->vecB);

    // Then, the resulting elements are true iff first elements are less than or equal to second
    EXPECT_VEC_EQ(this->expectedLTE, result);
}

TYPED_TEST(Vector4DComparison, LessThanOrEqualOperator_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    // Given two arbitrary vectors
    // When compared with less than or equal operator
    const math::Vector4D<bool> result = this->vecA <= this->vecB;

    // Then, the resulting elements are true iff first elements are less than or equal to second
    EXPECT_VEC_EQ(this->expectedLTE, result);
}

TYPED_TEST(Vector4DComparison, StaticWrapper_LessThanOrEqual_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    // Given two arbitrary vectors
    // When compared with less than or equals static wrapper
    const math::Vector4D<bool> result = math::Vector4D<TypeParam>::lessThanOrEqual(this->vecA, this->vecB);

    // Then, the resulting elements are true iff first elements are less than or equal to second
    EXPECT_VEC_EQ(this->expectedLTE, result);
}

TEST(Vector4DComparison, InfinityVector_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    // Given an arbitrary vector and an infinity vector
    math::Vector4D vec(1.2, 4.5, 6.8, 9.5);
    math::Vector4D infVec(INFINITY, INFINITY, -INFINITY, -INFINITY);
    math::Vector4D expected(true, true, false, false);

    // When compared with less than or equal
    const math::Vector4D<bool> result = vec.lessThanOrEqual(infVec);

    // Then, the resulting elements are FALSE for INFINITY and TRUE FOR -INFINITY
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DComparison, NanVector_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    // Given an arbitrary vector and a nan vector
    double nan = std::numeric_limits<double>::quiet_NaN();
    math::Vector4D vec(1.2, 4.5, 6.8, 9.5);
    math::Vector4D infVec(nan, nan, -5.9, nan);
    math::Vector4D expected(false, false, false, false);

    // When compared with less than or equal
    const math::Vector4D<bool> result = vec.lessThanOrEqual(infVec);

    // Then, the resulting elements are false for Nan
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DComparison, MixedType_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    math::Vector4D vecA(1.2, 4.5, 7.5, 9.5);
    math::Vector4D vecB(5, 6, 7, 8);
    math::Vector4D expected(true, true, false, false);

    // When compared with less than or equal
    const math::Vector4D<bool> result = vecA.lessThanOrEqual(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, result);
}
