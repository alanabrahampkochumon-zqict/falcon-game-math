/**
 * @file ProductTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref fgm::Vector4D<bool> dot product logic.
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
    fgm::Vector4D<T> _vecA;
    fgm::Vector4D<T> _vecB;

    fgm::Vector4D<T> _vecAOrthogonal;
    fgm::Vector4D<T> _vecBOrthogonal;

    T _expectedDotProduct;

    T _expectedADotA;

    void SetUp() override
    {
        _vecA = { T(2), T(3), T(4), T(5) };
        _vecB = { T(6), T(7), T(8), T(9) };
        _vecAOrthogonal = { T(3), T(0), T(4), T(0) };
        _vecBOrthogonal = { T(0), T(5), T(0), T(6) };
        _expectedDotProduct = static_cast<T>(110);

        _expectedADotA = static_cast<T>(54);
    }
};
/** @brief Test fixture for @ref fgm::Vector4D dot project, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector4DDotProduct, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Dot
 * @{
 */

/** @test Verify that the dot product of a @ref fgm::Vector4D with itself returns its squared magnitude. */
TYPED_TEST(Vector4DDotProduct, SelfDotProductReturnsSquareMagnitude)
{

    const TypeParam result = this->_vecA.dot(this->_vecA);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->_expectedADotA, result);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->_expectedADotA, result);
    else
        EXPECT_EQ(this->_expectedADotA, result);
}


/** @test Verify that the dot product of a @ref fgm::Vector4D with an orthogonal vector returns zero. */
TYPED_TEST(Vector4DDotProduct, OrthogonalDotProductReturnZero)
{
    const TypeParam result = this->_vecAOrthogonal.dot(this->_vecBOrthogonal);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(0.0, result);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(0.0f, result);
    else
        EXPECT_EQ(0, result);
}


/** @test Verify that the dot product of a @ref fgm::Vector4D with a non-orthogonal vector returns a non-zero scalar. */
TYPED_TEST(Vector4DDotProduct, NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam result = this->_vecA.dot(this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, result);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, result);
    else
        EXPECT_EQ(this->_expectedDotProduct, result);
}


/** @test Verify that the static dot product wrapper of @ref fgm::Vector4D returns a non-zero scalar. */
TYPED_TEST(Vector4DDotProduct, StaticWrapper_NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam result = fgm::Vector4D<TypeParam>::dot(this->_vecA, this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, result);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, result);
    else
        EXPECT_EQ(this->_expectedDotProduct, result);
}


/** @test Verify that the dot product of a @ref fgm::Vector4D with another @ref fgm::Vector4D in opposite direction
 *        returns a negative scalar. */
TEST(Vector4DDotProduct, AntiParallelDotProductReturnsNegativeScalar)
{
    // Given two opposite vectors
    constexpr fgm::Vector4D vecA(-1.0, 0.0, 0.0, 0.0);
    constexpr fgm::Vector4D vecB(1.0, 0.0, 0.0, 0.0);

    // When dot with each other
    constexpr double result = vecA.dot(vecB);

    // Then, the dot product is -1
    EXPECT_DOUBLE_EQ(-1.0, result);
}


/** @test Verify that the dot product of a @ref fgm::Vector4D with another @ref fgm::Vector4D of different type
 *        returns a type promoted vector. */
TEST(Vector4DDotProduct, MixedTypeDotProductPromotesType)
{
    // Given two vectors of different type
    constexpr fgm::Vector4D vecA(7, 13, 29, 41);
    constexpr fgm::Vector4D vecB(1.123456789, 2.123456789, 3.123456789, 4.123456789);

    // When dot with each other
    constexpr auto result = vecA.dot(vecB);

    // Then, the dot product is type promoted
    static_assert(std::is_same_v<decltype(result), const double>);

    // Then, the dot product is non-zero
    EXPECT_DOUBLE_EQ(295.11111101, result);
}

/** @} */
