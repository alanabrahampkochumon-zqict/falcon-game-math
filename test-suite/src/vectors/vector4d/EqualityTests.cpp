/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref Vector4D<bool> equality operator (==, !=) and their functional counterpart's (eq, neq, allEq, allNeq) logic.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;


template <typename T>
class Vector4DEquality: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> eqVecA;
    fgm::Vector4D<T> eqVecB;
    fgm::Vector4D<T> dissimilarVec;
    fgm::Vector4D<bool> equalityMask;
    fgm::Vector4D<bool> inequalityMask;


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
    bool equality = fgm::Vector4D<TypeParam>::allEq(this->eqVecA, this->dissimilarVec);

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
    const fgm::Vector4D vecA(1, 2, 3, 4);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    // When they are compared for equality
    bool equality = vecA == vecB;

    // Then, the result is true
    EXPECT_TRUE(equality);
}

TYPED_TEST(Vector4DEquality, MixedTypeEquality_DissimilarVectorsReturnsFalse)
{
    // Given two dissimilar vectors of different types
    const fgm::Vector4D vecA(5, 6, 7, 8);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    // When they are compared for inequality
    bool equality = vecA == vecB;

    // Then, the result is false
    EXPECT_FALSE(equality);
}

TEST(Vector4DEquality, EqualityOperator_SimilarBooleanVectorsReturnsTrue)
{
    // Given two similar boolean vectors
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, false, true, false);

    // When they are compared for equality
    bool equality = vecA == vecB;

    // Then, the result is true
    EXPECT_TRUE(equality);
}

TEST(Vector4DEquality, EqualityOperator_DissimilarBooleanVectorsReturnsFalse)
{
    // Given two dissimilar boolean vectors
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, true, true, false);

    // When they are compared for inequality
    bool equality = vecA == vecB;

    // Then, the result is false
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vector4DEquality, EqualityMaskReturnsCorrectBooleanMask)
{
    // When two vectors are compared for component-wise equality
    fgm::Vector4D<bool> mask = this->eqVecA.eq(this->dissimilarVec);

    // Then, correct boolean mask is returned
    EXPECT_VEC_EQ(this->equalityMask, mask);
}

TEST(Vector4DEquality, MixedType_EqualityMaskReturnsCorrectBooleanMask)
{
    // When two different type vectors are compared for component-wise equality
    fgm::Vector4D vecA = {1, 2, 3, 4};
    fgm::Vector4D vecB = {1.0, 4.0, 0.0, 4.0};
    fgm::Vector4D expectedMask = {true, false, false, true};

    fgm::Vector4D<bool> mask = vecA.eq(vecB);

    // Then, correct boolean mask is returned
    EXPECT_VEC_EQ(expectedMask, mask);
}

TEST(Vector4DEquality, NanEqualityReturnsFalseBooleanMask)
{
    // When a vector with only nan is compared with another vector
    double nan = std::numeric_limits<double>::quiet_NaN();
    fgm::Vector4D vecA = { nan, nan,nan, nan };
    fgm::Vector4D<double> vecB = { 1.0, -5.88874789, INFINITY, nan };
    fgm::Vector4D expectedMask = { false, false, false, false };

    fgm::Vector4D mask = vecA.eq(vecB);

    // Then, boolean masks contains only false values
    EXPECT_VEC_EQ(expectedMask, mask);
}

TEST(Vector4DEquality, InfinityEqualityReturnsCorrectBooleanMask)
{
    // When an infinity vector is compared with another
    fgm::Vector4D vecA = { INFINITY, -INFINITY, INFINITY, -INFINITY };
    fgm::Vector4D<double> vecB = { INFINITY, INFINITY, 10e11, 10e11 };
    fgm::Vector4D expectedMask = { true, false, false, false };

    fgm::Vector4D mask = vecA.eq(vecB);

    // Then, boolean masks contains correct values
    EXPECT_VEC_EQ(expectedMask, mask);
}

// TODO: Fix nan test

TYPED_TEST(Vector4DEquality, StaticWrapper_EqualityMaskReturnsCorrectBooleanMask)
{
    // When two vectors are compared for component-wise equality
    fgm::Vector4D<bool> mask = fgm::Vector4D<TypeParam>::eq(this->eqVecA, this->dissimilarVec);

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
    const fgm::Vector4D vecA(1, 2, 3, 4);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    // When they are compared for equality
    bool equality = vecA != vecB;

    // Then, the result is false
    EXPECT_FALSE(equality);
}

TYPED_TEST(Vector4DEquality, MixedTypeInequality_DissimilarVectorsReturnsTrue)
{
    // Given two dissimilar vectors of different types
    const fgm::Vector4D vecA(5, 6, 7, 8);
    const fgm::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

    // When they are compared for inequality
    bool equality = vecA != vecB;

    // Then, the result is true
    EXPECT_TRUE(equality);
}

TEST(Vector4DEquality, InequalityOperator_SimilarBooleanVectorsReturnsFalse)
{
    // Given two similar boolean vectors
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, false, true, false);

    // When they are compared for equality
    bool equality = vecA != vecB;

    // Then, the result is false
    EXPECT_FALSE(equality);
}

TEST(Vector4DEquality, InequalityOperator_DissimilarBooleanVectorsReturnsFalse)
{
    // Given two dissimilar boolean vectors
    const fgm::Vector4D vecA(true, false, true, false);
    const fgm::Vector4D vecB(true, true, true, false);

    // When they are compared for inequality
    bool equality = vecA != vecB;

    // Then, the result is true
    EXPECT_TRUE(equality);
}
