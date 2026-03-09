/**
 * @file ProductTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief `Vector4D` dot product tests.
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
class Vector4DDotProduct: public ::testing::Test
{
    protected:
    math::Vector4D<T> vecA;
    math::Vector4D<T> vecB;

    math::Vector4D<T> vecAOrtho;
    math::Vector4D<T> vecBOrtho;

    T expected;

    T aDotA;

    void SetUp() override
    {
        vecA = { T(2), T(3), T(4), T(5) };
        vecB = { T(6), T(7), T(8), T(9) };
        vecAOrtho = { T(3), T(0), T(4), T(0) };
        vecBOrtho = { T(0), T(5), T(0), T(6) };
        expected = static_cast<T>(110);

        aDotA = static_cast<T>(54);
    }
};
TYPED_TEST_SUITE(Vector4DDotProduct, SupportedArithmeticTypes);


/**************************************
 *                                    *
 *               TESTS                *
 *                                    *
 **************************************/

TYPED_TEST(Vector4DDotProduct, VectorWhenDotWithItselfReturnsSquareMagnitude)
{
    // Given an arbitrary vector

    // When dot with itself
    const TypeParam result = this->vecA.dot(this->vecA);

    // Then, the dot product is 1
    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->aDotA, result);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->aDotA, result);
    else
        EXPECT_EQ(this->aDotA, result);
}

TYPED_TEST(Vector4DDotProduct, VectorWhenDotWithOrthogonalVectorReturnZero)
{
    // Given two orthogonal vectors

    // When dot with each other
    const TypeParam result = this->vecAOrtho.dot(this->vecBOrtho);

    // Then, the dot product is 0
    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(0.0, result);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(0.0f, result);
    else
        EXPECT_EQ(0, result);
}

TYPED_TEST(Vector4DDotProduct, VectorDotWithNonOrthogonalVectorIsNonZeroNumber)
{
    // Given two non-orthogonal vectors

    // When dot with each other
    const TypeParam result = this->vecA.dot(this->vecB);

    // Then, the dot product is non-zero
    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->expected, result);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->expected, result);
    else
        EXPECT_EQ(this->expected, result);
}

TYPED_TEST(Vector4DDotProduct, StaticWrapper_VectorDotWithNonParallelVectorIsNonZeroNumber)
{
    // Given two non-orthogonal vectors

    // When dot with each other with static wrapper
    const TypeParam result = math::Vector4D<TypeParam>::dot(this->vecA, this->vecB);

    // Then, the dot product is non-zero
    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->expected, result);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->expected, result);
    else
        EXPECT_EQ(this->expected, result);
}

TEST(Vector4DDotProduct, VectorDotWithOppositeVectorIsNegative)
{
    // Given two opposite vectors
    const math::Vector4D vecA(-1.0, 0.0, 0.0, 0.0);
    const math::Vector4D vecB(1.0, 0.0, 0.0, 0.0);

    // When dot with each other
    const double result = vecA.dot(vecB);

    // Then, the dot product is -1
    EXPECT_DOUBLE_EQ(-1.0, result);
}

TEST(Vector4DDotProduct, MixedTypeDotProductPromotesType)
{
    // Given two vectors of different type
    const math::Vector4D vecA(7, 13, 29, 41);
    const math::Vector4D vecB(1.123456789, 2.123456789, 3.123456789, 4.123456789);

    // When dot with each other
    const auto result = vecA.dot(vecB);

    // Then, the dot product is type promoted
    static_assert(std::is_same_v<decltype(result), const double>);

    // Then, the dot product is non-zero
    EXPECT_DOUBLE_EQ(295.11111101, result);
}
