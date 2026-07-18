/**
 * @file ProductTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vec2 dot and cross product logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vec2DotProduct: public ::testing::Test
{
protected:
    fgm::Vec2<T> _vecA;
    fgm::Vec2<T> _vecB;

    fgm::Vec2<T> _vecAOrthogonal;
    fgm::Vec2<T> _vecBOrthogonal;

    T _expectedDotProduct;

    T _expectedADotA;

    void SetUp() override
    {
        _vecA               = { T(13), T(2) };
        _vecB               = { T(5), T(5) };
        _vecAOrthogonal     = { T(13), T(0) };
        _vecBOrthogonal     = { T(0), T(13) };
        _expectedDotProduct = static_cast<T>(75);

        _expectedADotA = static_cast<T>(173);
    }
};
/** @brief Test fixture for @ref fgm::Vec2 dot product, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vec2DotProduct, SupportedArithmeticTypes);


template <typename T>
class Vec2CrossProduct: public ::testing::Test
{
protected:
    fgm::Vec2<T> _vecA;
    fgm::Vec2<T> _vecB;
    T _expectedCrossProduct;

    void SetUp() override
    {
        _vecA                 = { T(3), T(0) };
        _vecB                 = { T(0), T(4) };
        _expectedCrossProduct = T(12);
    }
};
/** @brief Test fixture for @ref fgm::Vec2 cross product, parameterized by @ref SupportedSignedArithmeticTypes */
TYPED_TEST_SUITE(Vec2CrossProduct, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec2_Product
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that vector geometric product operations are available at compile time. */
namespace
{
    constexpr fgm::Vec2 vec1(1, 2);
    constexpr fgm::Vec2 vec2(3, 4);
    constexpr auto dotProductA = vec1.dot(vec2);
    constexpr auto dotProductB = fgm::Vec2<int>::dot(vec1, vec2);
    static_assert(dotProductA == 11);
    static_assert(dotProductB == 11);

    constexpr auto crossProductA = vec1.cross(vec2);
    constexpr auto crossProductB = fgm::Vec2<int>::cross(vec1, vec2);
    static_assert(crossProductA == -2);
    static_assert(crossProductB == -2);

} // namespace


/**************************************
 *                                    *
 *         DOT PRODUCT TESTS          *
 *                                    *
 **************************************/

/** @brief Verify that the dot product of a vector with itself returns its squared magnitude. */
TYPED_TEST(Vec2DotProduct, SelfDotProductReturnsSquareMagnitude)
{

    const TypeParam dotProduct = this->_vecA.dot(this->_vecA);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedADotA, dotProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedADotA, dotProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedADotA, dotProduct);
    }
}


/** @brief Verify that the dot product of a vector with an orthogonal vector returns zero. */
TYPED_TEST(Vec2DotProduct, OrthogonalDotProductReturnZero)
{
    const TypeParam dotProduct = this->_vecAOrthogonal.dot(this->_vecBOrthogonal);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(0.0, dotProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(0.0f, dotProduct);
    }
    else
    {
        EXPECT_EQ(0, dotProduct);
    }
}


/** @brief Verify that the dot product of a vector with a non-orthogonal vector returns a non-zero scalar. */
TYPED_TEST(Vec2DotProduct, NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam dotProduct = this->_vecA.dot(this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, dotProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, dotProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedDotProduct, dotProduct);
    }
}


/** @brief Verify that the static variant of @ref fgm::Vec2::dot returns a non-zero scalar. */
TYPED_TEST(Vec2DotProduct, StaticWrapper_NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam dotProduct = fgm::Vec2<TypeParam>::dot(this->_vecA, this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, dotProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, dotProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedDotProduct, dotProduct);
    }
}


/**
 * @brief Verify that the dot product of a vector with another vector in opposite direction
 *        returns a negative scalar.
 */
TEST(Vec2DotProduct, AntiParallelDotProductReturnsNegativeScalar)
{
    // Given two opposite vectors
    const fgm::Vec2 vecA(-1.0, 0.0);
    const fgm::Vec2 vecB(1.0, 0.0);

    // When dot with each other
    const double dotProduct = vecA.dot(vecB);

    // Then, the dot product is -1
    EXPECT_DOUBLE_EQ(-1.0, dotProduct);
}


/**
 * @brief Verify that the dot product of a vector with another vector of different type
 *        returns a type promoted vector.
 */
TEST(Vec2DotProduct, MixedTypeDotProductPromotesType)
{
    // Given two vectors of different type
    const fgm::Vec2 vecA(7, 13);
    const fgm::Vec2 vecB(1.123456789, 2.123456789);

    // When dot with each other
    const auto dotProduct = vecA.dot(vecB);

    // Then, the dot product is type promoted
    static_assert(std::is_same_v<decltype(dotProduct), const double>);

    // Then, the dot product is non-zero
    EXPECT_DOUBLE_EQ(35.46913578, dotProduct);
}


/**************************************
 *                                    *
 *        CROSS PRODUCT TESTS         *
 *                                    *
 **************************************/

/** @brief Verify that the cross product of vector with self is a zero-vector. */
TEST(Vec2CrossProduct, VectorCrossItselfReturnsZeroVector)
{
    const fgm::Vec2 vec(2.0f, 1.0f);

    const float crossProduct = vec.cross(vec);

    EXPECT_FLOAT_EQ(0.0f, crossProduct);
}


/** @brief Verify that the cross product of vector with a non-parallel vector returns a new vector. */
TYPED_TEST(Vec2CrossProduct, BetweenTwoNonParallelVectorsReturnsNewProduct)
{
    const TypeParam crossProduct = this->_vecA.cross(this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedCrossProduct, crossProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedCrossProduct, crossProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedCrossProduct, crossProduct);
    }
}


/**
 * @brief Verify that the cross product of vector with a non-parallel vector using static variant of
 *        @ref fgm::Vec2::cross returns a new vector.
 */
TYPED_TEST(Vec2CrossProduct, StaticWrapper_BetweenTwoNonParallelVectorsReturnsNewProduct)
{
    const TypeParam crossProduct = fgm::Vec2<TypeParam>::cross(this->_vecA, this->_vecB);
    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedCrossProduct, crossProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedCrossProduct, crossProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedCrossProduct, crossProduct);
    }
}


/** @brief Verify that the cross product between two differently typed vectors promote type. */
TEST(Vec2CrossProduct, BetweenDifferentlyTypedVectorsPromotesType)
{
    const fgm::Vec2 vecA(2.0f, 3.0f);
    const fgm::Vec2 vecB(5.0, 6.0);

    [[maybe_unused]] const auto crossProduct = vecA.cross(vecB);
    static_assert(std::is_same_v<decltype(crossProduct), const double>);
}

/** @} */
