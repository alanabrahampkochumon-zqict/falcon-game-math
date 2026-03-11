/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief `Vector4D` equality (==, != and their functional counterparts) tests.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;


template <typename T>
class Vector4DEquality: public ::testing::Test
{
    protected:
    math::Vector4D<T> eqVecA;
    math::Vector4D<T> eqVecB;
    math::Vector4D<T> dissimilarVec;
    math::Vector4D<bool> equalityMask;
    math::Vector4D<bool> inequalityMask;


    void SetUp() override
    {
        eqVecA = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
        eqVecB = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
        dissimilarVec = { T(7.1234568789), T(2.123458319), T(24.00), T(123.123489172589) };
        equalityMask = {false, true, false, true};
        inequalityMask = {true, false, true, false};
    }
};
TYPED_TEST_SUITE(Vector4DEquality, SupportedArithmeticTypes);


/**************************************
 *                                    *
 *           EQUALITY TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Vector4DEquality, SimilarVectorsAreEqual)
{
    // When two equal vectors are compared for equality
    bool equality = this->eqVecA.allEq(this->eqVecB);

    // Then, they are equal
    EXPECT_TRUE(equality);
}

TYPED_TEST(Vector4DEquality, DissimilarVectorsAreNotEqual)
{
    // When two equal vectors are compared for equality
    bool equality = this->eqVecA.allEq(this->dissimilarVec);

    // Then, they are not equal
    EXPECT_FALSE(equality);
}

TYPED_TEST(Vector4DEquality, StaticWrapper_SimilarVectorsAreEqual)
{
    // When two equal vectors are compared for equality
    bool equality = this->eqVecA.allEq(this->eqVecB);

    // Then, they are equal
    EXPECT_TRUE(equality);
}

TYPED_TEST(Vector4DEquality, StaticWrapper_DissimilarVectorsAreNotEqual)
{
    // When two equal vectors are compared for equality
    bool equality = math::Vector4D<TypeParam>::allEq(this->eqVecA, this->dissimilarVec);

    // Then, they are not equal
    EXPECT_FALSE(equality);
}

TYPED_TEST(Vector4DEquality, EqualityOperator_SimilarVectorsReturnsTrue)
{
    // When two equal vectors are compared for equality
    bool equality = this->eqVecA == this->eqVecB;

    // Then, result is true
    EXPECT_TRUE(equality);
}

TYPED_TEST(Vector4DEquality, EqualityOperator_DissimilarVectorsReturnsFalse)
{
    // When two equal vectors are compared for equality
    bool equality = this->eqVecA == this->dissimilarVec;

    // Then, result is false
    EXPECT_FALSE(equality);
}

TYPED_TEST(Vector4DEquality, MixedTypeEquality_SimilarVectorsReturnsTrue)
{
    // Given two similar vectors of different types
    const math::Vector4D vecA(1, 2, 3, 4);
    const math::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    // When they are compared for equality
    bool equality = vecA == vecB;

    // Then, the result is true
    EXPECT_TRUE(equality);
}

TYPED_TEST(Vector4DEquality, MixedTypeEquality_DissimilarVectorsReturnsFalse)
{
    // Given two dissimilar vectors of different types
    const math::Vector4D vecA(5, 6, 7, 8);
    const math::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    // When they are compared for inequality
    bool equality = vecA == vecB;

    // Then, the result is false
    EXPECT_FALSE(equality);
}

TEST(Vector4DEquality, EqualityOperator_SimilarBooleanVectorsReturnsTrue)
{
    // Given two similar boolean vectors
    const math::Vector4D vecA(true, false, true, false);
    const math::Vector4D vecB(true, false, true, false);

    // When they are compared for equality
    bool equality = vecA == vecB;

    // Then, the result is true
    EXPECT_TRUE(equality);
}

TEST(Vector4DEquality, EqualityOperator_DissimilarBooleanVectorsReturnsFalse)
{
    // Given two dissimilar boolean vectors
    const math::Vector4D vecA(true, false, true, false);
    const math::Vector4D vecB(true, true, true, false);

    // When they are compared for inequality
    bool equality = vecA == vecB;

    // Then, the result is false
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vector4DEquality, eqReturnsCorrectBooleanMask)
{
    // When two equal vectors are compared for component-wise equality
    math::Vector4D<bool> mask = this->eqVecA.eq(this->dissimilarVec);

    // Then, correct boolean mask is returned
    EXPECT_VEC_EQ(this->equalityMask, mask);
}

TYPED_TEST(Vector4DEquality, StaticWrapper_eqReturnsCorrectBooleanMask)
{
    // When two equal vectors are compared for component-wise equality
    math::Vector4D<bool> mask = math::Vector4D<TypeParam>::eq(this->eqVecA, this->dissimilarVec);

    // Then, correct boolean mask is returned
    EXPECT_VEC_EQ(this->equalityMask, mask);
}


/**************************************
 *                                    *
 *          INEQUALITY TESTS          *
 *                                    *
 **************************************/

TYPED_TEST(Vector4DEquality, InEqualityOperator_SimilarVectorsReturnsFalse)
{
    // When two equal vectors are compared for equality
    bool equality = this->eqVecA != this->eqVecB;

    // Then, result is false
    EXPECT_FALSE(equality);
}

TYPED_TEST(Vector4DEquality, InEqualityOperator_DissimilarVectorsReturnsTrue)
{
    // When two equal vectors are compared for equality
    bool equality = this->eqVecA != this->dissimilarVec;

    // Then, result is true
    EXPECT_TRUE(equality);
}

TYPED_TEST(Vector4DEquality, MixedTypeInequality_SimilarVectorsReturnsFalse)
{
    // Given two similar vectors of different types
    const math::Vector4D vecA(1, 2, 3, 4);
    const math::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    // When they are compared for equality
    bool equality = vecA != vecB;

    // Then, the result is false
    EXPECT_FALSE(equality);
}

TYPED_TEST(Vector4DEquality, MixedTypeInequality_DissimilarVectorsReturnsTrue)
{
    // Given two dissimilar vectors of different types
    const math::Vector4D vecA(5, 6, 7, 8);
    const math::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    // When they are compared for inequality
    bool equality = vecA != vecB;

    // Then, the result is true
    EXPECT_TRUE(equality);
}

TEST(Vector4DEquality, InequalityOperator_SimilarBooleanVectorsReturnsFalse)
{
    // Given two similar boolean vectors
    const math::Vector4D vecA(true, false, true, false);
    const math::Vector4D vecB(true, false, true, false);

    // When they are compared for equality
    bool equality = vecA != vecB;

    // Then, the result is false
    EXPECT_FALSE(equality);
}

TEST(Vector4DEquality, InequalityOperator_DissimilarBooleanVectorsReturnsFalse)
{
    // Given two dissimilar boolean vectors
    const math::Vector4D vecA(true, false, true, false);
    const math::Vector4D vecB(true, true, true, false);

    // When they are compared for inequality
    bool equality = vecA != vecB;

    // Then, the result is true
    EXPECT_TRUE(equality);
}
