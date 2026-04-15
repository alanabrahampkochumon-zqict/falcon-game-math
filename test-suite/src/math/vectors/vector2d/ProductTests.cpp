/**
 * @file ProductTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vector2D dot and cross product logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector2DDotProduct: public ::testing::Test
{
protected:
    fgm::Vector2D<T> _vecA;
    fgm::Vector2D<T> _vecB;

    fgm::Vector2D<T> _vecAOrthogonal;
    fgm::Vector2D<T> _vecBOrthogonal;

    T _expectedDotProduct;

    T _expectedADotA;

    void SetUp() override
    {
        _vecA = { T(13), T(2)};
        _vecB = { T(5), T(5)};
        _vecAOrthogonal = { T(13), T(0) };
        _vecBOrthogonal = { T(0), T(13) };
        _expectedDotProduct = static_cast<T>(75);

        _expectedADotA = static_cast<T>(173);
    }
};
/** @brief Test fixture for @ref fgm::Vector2D dot product, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector2DDotProduct, SupportedArithmeticTypes);


template <typename T>
class Vector2DCrossProduct: public ::testing::Test
{
protected:
    fgm::Vector2D<T> _vecA;
    fgm::Vector2D<T> _vecB;
    T _expectedCrossProduct;

    void SetUp() override
    {
        _vecA = { T(3), T(0) };
        _vecB = { T(0), T(4) };
        _expectedCrossProduct = T(12);
    }
};
/** @brief Test fixture for @ref fgm::Vector2D cross product, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector2DCrossProduct, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec2_Product
 * @{
 */

/**************************************
 *                                    *
 *         DOT PRODUCT TESTS          *
 *                                    *
 **************************************/

/** @test Verify that the dot product of a vector with itself returns its squared magnitude. */
TYPED_TEST(Vector2DDotProduct, SelfDotProductReturnsSquareMagnitude)
{

    const TypeParam dotProduct = this->_vecA.dot(this->_vecA);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->_expectedADotA, dotProduct);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->_expectedADotA, dotProduct);
    else
        EXPECT_EQ(this->_expectedADotA, dotProduct);
}


/** @test Verify that the dot product of a vector with an orthogonal vector returns zero. */
TYPED_TEST(Vector2DDotProduct, OrthogonalDotProductReturnZero)
{
    const TypeParam dotProduct = this->_vecAOrthogonal.dot(this->_vecBOrthogonal);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(0.0, dotProduct);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(0.0f, dotProduct);
    else
        EXPECT_EQ(0, dotProduct);
}


/** @test Verify that the dot product of a vector with a non-orthogonal vector returns a non-zero scalar. */
TYPED_TEST(Vector2DDotProduct, NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam dotProduct = this->_vecA.dot(this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, dotProduct);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, dotProduct);
    else
        EXPECT_EQ(this->_expectedDotProduct, dotProduct);
}


/** @test Verify that the static variant of @ref fgm::Vector2D::dot returns a non-zero scalar. */
TYPED_TEST(Vector2DDotProduct, StaticWrapper_NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam dotProduct = fgm::Vector2D<TypeParam>::dot(this->_vecA, this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, dotProduct);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, dotProduct);
    else
        EXPECT_EQ(this->_expectedDotProduct, dotProduct);
}


/**
 * @test Verify that the dot product of a vector with another vector in opposite direction
 *        returns a negative scalar.
 */
TEST(Vector2DDotProduct, AntiParallelDotProductReturnsNegativeScalar)
{
    // Given two opposite vectors
    constexpr fgm::Vector2D vecA(-1.0, 0.0);
    constexpr fgm::Vector2D vecB(1.0, 0.0);

    // When dot with each other
    const double dotProduct = vecA.dot(vecB);

    // Then, the dot product is -1
    EXPECT_DOUBLE_EQ(-1.0, dotProduct);
}


/**
 * @test Verify that the dot product of a vector with another vector of different type
 *        returns a type promoted vector.
 */
TEST(Vector2DDotProduct, MixedTypeDotProductPromotesType)
{
    // Given two vectors of different type
    constexpr fgm::Vector2D vecA(7, 13);
    constexpr fgm::Vector2D vecB(1.123456789, 2.123456789);

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
TEST(Vector2DCrossProduct, VectorCrossItselfReturnsZeroVector)
{
    constexpr fgm::Vector2D vec(2.0f, 1.0f);

    constexpr float crossProduct = vec.cross(vec);

    EXPECT_FLOAT_EQ(0.0f, crossProduct);
}


/** @brief Verify that the cross product of vector with a non-parallel vector returns a new vector. */
TYPED_TEST(Vector2DCrossProduct, BetweenTwoNonParallelVectorsReturnsNewProduct)
{
    const TypeParam crossProduct = this->_vecA.cross(this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->_expectedCrossProduct, crossProduct);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->_expectedCrossProduct, crossProduct);
    else
        EXPECT_EQ(this->_expectedCrossProduct, crossProduct);
}


/**
 * @brief Verify that the cross product of vector with a non-parallel vector using static variant of 
 *        @ref fgm::Vector2D::cross returns a new vector.
 */
TYPED_TEST(Vector2DCrossProduct, StaticWrapper_BetweenTwoNonParallelVectorsReturnsNewProduct)
{
    const TypeParam crossProduct = fgm::Vector2D<TypeParam>::cross(this->_vecA, this->_vecB);
    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->_expectedCrossProduct, crossProduct);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->_expectedCrossProduct, crossProduct);
    else
        EXPECT_EQ(this->_expectedCrossProduct, crossProduct);
}


/** @brief Verify that the cross product between two differently typed vectors promote type. */
TEST(Vector2DCrossProduct, BetweenDifferentlyTypedVectorsPromotesType)
{
    constexpr fgm::Vector2D vecA(2.0f, 3.0f);
    constexpr fgm::Vector2D vecB(5.0, 6.0);

    [[maybe_unused]] constexpr auto crossProduct = vecA.cross(vecB);
    static_assert(std::is_same_v<decltype(crossProduct), const double>);
}

/** @} */
