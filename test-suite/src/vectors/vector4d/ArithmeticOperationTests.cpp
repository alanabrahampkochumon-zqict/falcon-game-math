/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief `Vector4D` arithmetic operation (+, -, /, *) tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;


/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector4DAddition: public ::testing::Test
{
    protected:
    math::Vector4D<T> vecA;
    math::Vector4D<T> vecB;
    math::Vector4D<T> expected;

    void SetUp() override
    {
        vecA = { T(3), T(1), T(6), T(2) };
        vecB = { T(-8), T(5), T(-2), T(5) };
        expected = { T(-5), T(6), T(4), T(7) };
    }
};
TYPED_TEST_SUITE(Vector4DAddition, SupportedArithmeticTypes);


template <typename T>
class Vector4DSubtraction: public ::testing::Test
{
    protected:
    math::Vector4D<T> vecA;
    math::Vector4D<T> vecB;
    math::Vector4D<T> expected;

    void SetUp() override
    {
        vecA = { T(95), T(11), T(-6), T(2) };
        vecB = { T(-8), T(5), T(-2), T(-5) };
        expected = { T(103), T(6), T(-4), T(7) };
    }
};
TYPED_TEST_SUITE(Vector4DSubtraction, SupportedArithmeticTypes);


template <typename T>
class Vector4DScalarMultiplication: public ::testing::Test
{
    protected:
    math::Vector4D<T> vec;
    T scalar;
    math::Vector4D<T> expectedFloating;
    math::Vector4D<T> expectedIntegral;

    void SetUp() override
    {
        vec = { T(7), T(13), T(29), T(41) };
        scalar = T(2.123456789123456);
        expectedFloating = { T(14.864197523864192), T(27.604938258604928), T(61.580246884580224),
                             T(87.061728354061696) };
        expectedIntegral = { T(14), T(26), T(58), T(82) };
    }
};
TYPED_TEST_SUITE(Vector4DScalarMultiplication, SupportedArithmeticTypes);


template <typename T>
class Vector4DScalarDivision: public ::testing::Test
{
    protected:
    math::Vector4D<T> vec;
    T scalar;
    math::Vector4D<T> expected;

    void SetUp() override
    {
        vec = { T(17), T(31), T(59), T(73) };
        scalar = T(13);
        expected = { T(1.30769230769230769231), T(2.38461538461538461538), T(4.53846153846153846154),
                     T(5.61538461538461538462) };
    }
};
TYPED_TEST_SUITE(Vector4DScalarDivision, SupportedArithmeticTypes);


/**************************************
 *                                    *
 *           ADDITION TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Vector4DAddition, VectorPlusVectorReturnsNewVectorWithSum)
{
    // Given two vectors
    // When they are added together
    const math::Vector4D result = this->vecA + this->vecB;

    // Then the output vector contains sum of elements
    EXPECT_VEC_EQ(this->expected, result);
}

TYPED_TEST(Vector4DAddition, VectorPlusEqualsReturnsSameVectorWithSum)
{
    // Given two vectors
    //  When one vector is added to the other(+=)
    this->vecA += this->vecB;

    // Then, the original vector contains the sum of the elements added together
    EXPECT_VEC_EQ(this->expected, this->vecA);
}

TEST(Vector4DAddition, MixedTypeAdditionPromotesType)
{
    // Given vectors with arbitrary values
    const math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const math::Vector4D vec2(9.0, -5.0, 10.0, 3.0);
    const math::Vector4D expected(12.0, -5.0, 9.0, 5.0);

    // When they are added together
    const math::Vector4D result = vec1 + vec2;

    // Then the new vector is type promoted
    static_assert(std::is_same_v<decltype(result)::value_type, double>);
    // And contains sum of elements
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DAddition, MixedTypeAdditionAssignmentDoesNotPromoteType)
{
    // Given vectors with arbitrary values
    math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const math::Vector4D vec2(9.0, -5.0, 10.0, 3.0);
    const math::Vector4D expected(12.0f, -5.0f, 9.0f, 5.0f);

    // When one vector is added to the other(+=)
    vec1 += vec2;

    // Then, the original vector's type is preserved
    static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
    // and contains sum of elements
    EXPECT_VEC_EQ(expected, vec1);
}


/**************************************
 *                                    *
 *          SUBTRACTION TESTS         *
 *                                    *
 **************************************/

TYPED_TEST(Vector4DSubtraction, VectorMinusVectorReturnsNewVectorWithDifference)
{
    // Given two vectors
    // When they are added together
    const math::Vector4D result = this->vecA - this->vecB;

    // Then the output vector contains the difference between elements
    EXPECT_VEC_EQ(this->expected, result);
}

TYPED_TEST(Vector4DSubtraction, VectorMinusEqualsVectorReturnsSameVectorWithDifference)
{
    // Given two vectors
    //  When one vector is added to the other(+=)
    this->vecA -= this->vecB;

    // Then, the original vector contains the difference between elements
    EXPECT_VEC_EQ(this->expected, this->vecA);
}

TEST(Vector4DSubtraction, MixedTypeSubtractionPromotesType)
{
    // Given vectors with arbitrary values
    const math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const math::Vector4D vec2(9.0, -5.0, 10.0, 3.0);
    const math::Vector4D expected(-6.0, 5.0, -11.0, -1.0);

    // When they are subtracted
    const math::Vector4D result = vec1 - vec2;

    // Then the new vector is type promoted
    static_assert(std::is_same_v<decltype(result)::value_type, double>);
    // And contains difference between the elements
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DSubtraction, MixedTypeSubtractionAssignmentDoesNotPromoteType)
{
    // Given vectors with arbitrary values
    math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const math::Vector4D vec2(9.0, -5.0, 10.0, 3.0);
    const math::Vector4D expected(-6.0, 5.0, -11.0, -1.0);

    // When one vector is subtracted from the other(-=)
    vec1 -= vec2;

    // Then, the original vector's type is preserved
    static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
    // And contains difference between the elements
    EXPECT_VEC_EQ(expected, vec1);
}



/**************************************
 *                                    *
 *     SCALAR MULTIPLICATION TESTS    *
 *                                    *
 **************************************/

TEST(Vector4DScalarMultiplication, VectorTimesZeroReturnsZeroVector)
{
    // Given an arbitrary vector
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // When multiplied with 0
    const math::Vector4D result = vec * 0;

    // Then, we get a zero vector
    EXPECT_VEC_ZERO(result);
}

TEST(Vector4DScalarMultiplication, VectorTimesOneReturnsVectorWithSameValues)
{
    // Given an arbitrary vector
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // When multiplied with 1
    const math::Vector4D result = vec * 1;

    // Then, we get the same vector
    EXPECT_VEC_EQ(vec, result);
}

TYPED_TEST(Vector4DScalarMultiplication, VectorTimesANumberReturnsAScaledVector)
{
    // Given an arbitrary vector and a scalar

    // When multiplied (vec * scalar)
    const math::Vector4D result = this->vec * this->scalar;

    // Then, new vector contains elements multiplied(scaled) with the scalar
    if (std::is_floating_point_v<TypeParam>)
        EXPECT_VEC_EQ(this->expectedFloating, result);
    else
        EXPECT_VEC_EQ(this->expectedIntegral, result);
}

TYPED_TEST(Vector4DScalarMultiplication, NumberTimesAVectorReturnsAScaledVector)
{
    // Given an arbitrary vector and a scalar

    // When multiplied (vec * scalar)
    const math::Vector4D result = this->scalar * this->vec;

    // Then, new vector contains elements multiplied(scaled) with the scalar
    if (std::is_floating_point_v<TypeParam>)
        EXPECT_VEC_EQ(this->expectedFloating, result);
    else
        EXPECT_VEC_EQ(this->expectedIntegral, result);
}

TYPED_TEST(Vector4DScalarMultiplication, VectorTimesEqualAScalarIsTheSameVectorScaled)
{
    // Given an arbitrary vector and a scalar

    // When multiplied (vec * scalar)
    this->vec *= this->scalar;

    // Then, the original vector is scaled by the scalar
    if (std::is_floating_point_v<TypeParam>)
        EXPECT_VEC_EQ(this->expectedFloating, this->vec);
    else
        EXPECT_VEC_EQ(this->expectedIntegral, this->vec);
}

TYPED_TEST(Vector4DScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    // Given a vector and scalar with arbitrary values
    constexpr double scalar = 2.123456789123456;
    const math::Vector4D expected(14.864197523864192, 27.604938258604928, 61.580246884580224, 87.061728354061696);

    // When they are multiplied
    const math::Vector4D result = this->vec * scalar;

    // Then the new vector is type promoted
    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);

    // And the vector is scaled by `scalar`
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    // Given a vector and scalar with arbitrary values
    math::Vector4D vec(3.0f, 0.0f, -1.0f, 2.0f);
    constexpr double scalar = 5.0;
    const math::Vector4D expected(15.0f, 0.0f, -5.0f, 10.0f);

    // When vector is multiplied by the scalar and assigned (*=)
    vec *= scalar;

    // Then the vector type is preserved
    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
    // And the vector is scaled by `scalar`
    EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector4DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentGivesResultWithMinimalPrecisionLoss)
{
    // Given a vector and scalar with arbitrary values
    math::Vector4D vec(3, 0, -1, 8);
    constexpr double scalar = 2.5;
    const math::Vector4D expected(7, 0, -2, 20);

    // When vector is multiplied by the scalar and assigned (*=)
    vec *= scalar;

    // And the vector is scaled by `scalar` with minimal precision loss
    EXPECT_VEC_EQ(expected, vec);
}


/**************************************
 *                                    *
 *        SCALAR DIVISION TESTS       *
 *                                    *
 **************************************/

TYPED_TEST(Vector4DScalarDivision, VectorDividedByZeroReturnsInfinityVector)
{
    // Given an arbitrary vector

    // Floating point
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        // When divided by zero
        const math::Vector4D result = this->vec / 0;

        // Then, the resultant vector is an infinity vector
        EXPECT_VEC_INF(result);
    } // Integrals
    else
    {
        EXPECT_DEATH({ this->vec / 0; }, "Integral division by zero");
    }
}

TYPED_TEST(Vector4DScalarDivision, VectorDividedByOneReturnsAVectorWithSameValues)
{
    // Given an arbitrary vector

    // When divided by one
    const math::Vector4D result = this->vec / 1;

    // Then, the resultant vector is an infinity vector
    EXPECT_VEC_EQ(result, this->vec);
}

TYPED_TEST(Vector4DScalarDivision, VectorDividedByANumberReturnsAScaledVector)
{
    // Given an arbitrary vector

    // When divided by a scalar
    const math::Vector4D result = this->vec / this->scalar;

    // Then, the resultant vector is a new vector with elements divided by the scalar
    EXPECT_VEC_EQ(this->expected, result);
}

TYPED_TEST(Vector4DScalarDivision, VectorDivideEqualsANumberIsTheSameVectorScaled)
{
    // Given an arbitrary vector

    // When divide equals by a scalar
    this->vec /= this->scalar;

    // Then, the resultant vector is the same vector with elements divided by the scalar
    EXPECT_VEC_EQ(this->expected, this->vec);
}

TEST(Vector4DScalarDivision, MixedTypeScalarDivisionPromotesType)
{
    // Given an arbitrary vector
    const math::Vector4D vec(15.0, 0.0, -5.0, 10.0);
    constexpr double scalar = 5.0;
    const math::Vector4D expected(3.0f, 0.0f, -1.0f, 2.0f);

    // When divided by a scalar
    const math::Vector4D result = vec / scalar;

    // Then the new vector is type promoted
    static_assert(std::is_same_v<decltype(result)::value_type, double>);
    // And the vector is scaled by `scalar`
    EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DScalarDivision, MixedTypeScalarDivisionAssignmentDoesNotPromoteType)
{
    // Given an arbitrary vector
    math::Vector4D vec(15.0f, 0.0f, -5.0f, 10.0f);
    constexpr double scalar = 5.0;

    const math::Vector4D expected(3.0f, 0.0f, -1.0f, 2.0f);

    // When divide equals by a scalar
    vec /= scalar;

    // Then the vector type is preserved
    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
    // And the vector is scaled by `scalar`
    EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector4DScalarDivision, MixedTypeScalarDivisionAssignmentGivesResultWithMinimalPrecisionLoss)
{
    // Given an arbitrary vector
    math::Vector4D vec(10, 25, -30, 2);
    constexpr double scalar = 2.5;
    const math::Vector4D expected(4, 10, -12, 0);

    // When vector divides equal by a scalar
    vec /= scalar;

    // And the vector is scaled by `scalar` with minimal precision loss
    EXPECT_VEC_EQ(expected, vec);
}