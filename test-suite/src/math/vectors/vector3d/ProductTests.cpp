/**
 * @file ProductTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verifies @ref fgm::Vector3D dot product logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3DTestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector3DDotProduct: public ::testing::Test
{
protected:
    fgm::Vector3D<T> _vecA;
    fgm::Vector3D<T> _vecB;

    fgm::Vector3D<T> _vecAOrthogonal;
    fgm::Vector3D<T> _vecBOrthogonal;

    T _expectedDotProduct;

    T _expectedADotA;

    void SetUp() override
    {
        _vecA = { T(2), T(3), T(4) };
        _vecB = { T(6), T(7), T(8) };
        // TODO: Add orthogonal
        _vecAOrthogonal = { T(3), T(0), T(4) };
        _vecBOrthogonal = { T(0), T(5), T(0) };
        _expectedDotProduct = static_cast<T>(65);

        _expectedADotA = static_cast<T>(29);
    }
};
/** @brief Test fixture for @ref fgm::Vector3D dot project, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector3DDotProduct, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Dot
 * @{
 */

/** @test Verify that the dot product of a vector with itself returns its squared magnitude. */
TYPED_TEST(Vector3DDotProduct, SelfDotProductReturnsSquareMagnitude)
{

    const TypeParam result = this->_vecA.dot(this->_vecA);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->_expectedADotA, result);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->_expectedADotA, result);
    else
        EXPECT_EQ(this->_expectedADotA, result);
}


/** @test Verify that the dot product of a vector with an orthogonal vector returns zero. */
TYPED_TEST(Vector3DDotProduct, OrthogonalDotProductReturnZero)
{
    const TypeParam result = this->_vecAOrthogonal.dot(this->_vecBOrthogonal);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(0.0, result);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(0.0f, result);
    else
        EXPECT_EQ(0, result);
}


/** @test Verify that the dot product of a vector with a non-orthogonal vector returns a non-zero scalar. */
TYPED_TEST(Vector3DDotProduct, NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam result = this->_vecA.dot(this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, result);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, result);
    else
        EXPECT_EQ(this->_expectedDotProduct, result);
}


/** @test Verify that the static variant of @ref fgm::Vector3D::dot returns a non-zero scalar. */
TYPED_TEST(Vector3DDotProduct, StaticWrapper_NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam result = fgm::Vector3D<TypeParam>::dot(this->_vecA, this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, result);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, result);
    else
        EXPECT_EQ(this->_expectedDotProduct, result);
}


/**
 * @test Verify that the dot product of a vector with another vector in opposite direction
 *        returns a negative scalar.
 */
TEST(Vector3DDotProduct, AntiParallelDotProductReturnsNegativeScalar)
{
    // Given two opposite vectors
    constexpr fgm::Vector3D vecA(-1.0, 0.0, 0.0);
    constexpr fgm::Vector3D vecB(1.0, 0.0, 0.0);

    // When dot with each other
    const double result = vecA.dot(vecB);

    // Then, the dot product is -1
    EXPECT_DOUBLE_EQ(-1.0, result);
}


/** 
 * @test Verify that the dot product of a vector with another vector of different type
 *        returns a type promoted vector.
 */
TEST(Vector3DDotProduct, MixedTypeDotProductPromotesType)
{
    // Given two vectors of different type
    constexpr fgm::Vector3D vecA(7, 13, 29);
    constexpr fgm::Vector3D vecB(1.123456789, 2.123456789, 3.123456789);

    // When dot with each other
    const auto result = vecA.dot(vecB);

    // Then, the dot product is type promoted
    static_assert(std::is_same_v<decltype(result), const double>);

    // Then, the dot product is non-zero
    EXPECT_DOUBLE_EQ(126.049382661, result);
}

/** @} */
