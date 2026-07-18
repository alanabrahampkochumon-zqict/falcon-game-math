/**
 * @file ProductTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref fgm::Vec3 dot and cross product logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vec3DotProduct: public ::testing::Test
{
protected:
    fgm::Vec3<T> _vecA;
    fgm::Vec3<T> _vecB;

    fgm::Vec3<T> _vecAOrthogonal;
    fgm::Vec3<T> _vecBOrthogonal;

    T _expectedDotProduct;

    T _expectedADotA;

    void SetUp() override
    {
        _vecA               = { T(2), T(3), T(4) };
        _vecB               = { T(6), T(7), T(8) };
        _vecAOrthogonal     = { T(3), T(0), T(4) };
        _vecBOrthogonal     = { T(0), T(5), T(0) };
        _expectedDotProduct = static_cast<T>(65);

        _expectedADotA = static_cast<T>(29);
    }
};
/** @brief Test fixture for @ref fgm::Vec3 dot product, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec3DotProduct, SupportedArithmeticTypes);


template <typename T>
class Vec3CrossProduct: public ::testing::Test
{
protected:
    fgm::Vec3<T> _vecA;
    fgm::Vec3<T> _vecB;
    fgm::Vec3<T> _expectedCrossProduct;

    void SetUp() override
    {
        _vecA                 = { T(2), T(3), T(4) };
        _vecB                 = { T(5), T(6), T(7) };
        _expectedCrossProduct = { T(-3), T(6), T(-3) };
    }
};
/** @brief Test fixture for @ref fgm::Vec3 cross product, parameterized by @ref SupportedSignedArithmeticTypes. */
TYPED_TEST_SUITE(Vec3CrossProduct, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Product
 * @{
 */

/** @brief Verify that vector geometric product operations are available at compile time. */
namespace
{
    constexpr fgm::Vec3 vec1(1, 2, 3);
    constexpr fgm::Vec3 vec2(4, 5, 6);
    constexpr auto dotProductA = vec1.dot(vec2);
    constexpr auto dotProductB = fgm::Vec3<int>::dot(vec1, vec2);
    static_assert(dotProductA == 32);
    static_assert(dotProductB == 32);

    constexpr auto crossProductA = vec1.cross(vec2);
    constexpr auto crossProductB = fgm::Vec3<int>::cross(vec1, vec2);
    static_assert(crossProductA.x() == -3);
    static_assert(crossProductA.y() == 6);
    static_assert(crossProductA.z() == -3);

    static_assert(crossProductB.x() == -3);
    static_assert(crossProductB.y() == 6);
    static_assert(crossProductB.z() == -3);

} // namespace


/**************************************
 *                                    *
 *         DOT PRODUCT TESTS          *
 *                                    *
 **************************************/

/** @brief Verify that the dot product of a vector with itself returns its squared magnitude. */
TYPED_TEST(Vec3DotProduct, SelfDotProductReturnsSquareMagnitude)
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
TYPED_TEST(Vec3DotProduct, OrthogonalDotProductReturnZero)
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
TYPED_TEST(Vec3DotProduct, NonOrthogonalDotProductReturnsNonZeroScalar)
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


/** @brief Verify that the static variant of @ref fgm::Vec3::dot returns a non-zero scalar. */
TYPED_TEST(Vec3DotProduct, StaticWrapper_NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam dotProduct = fgm::Vec3<TypeParam>::dot(this->_vecA, this->_vecB);

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
TEST(Vec3DotProduct, AntiParallelDotProductReturnsNegativeScalar)
{
    // Given two opposite vectors
    const fgm::Vec3 vecA(-1.0, 0.0, 0.0);
    const fgm::Vec3 vecB(1.0, 0.0, 0.0);

    // When dot with each other
    const double dotProduct = vecA.dot(vecB);

    // Then, the dot product is -1
    EXPECT_DOUBLE_EQ(-1.0, dotProduct);
}


/**
 * @brief Verify that the dot product of a vector with another vector of different type
 *        returns a type promoted vector.
 */
TEST(Vec3DotProduct, MixedTypeDotProductPromotesType)
{
    // Given two vectors of different type
    const fgm::Vec3 vecA(7, 13, 29);
    const fgm::Vec3 vecB(1.123456789, 2.123456789, 3.123456789);

    // When dot with each other
    const auto dotProduct = vecA.dot(vecB);

    // Then, the dot product is type promoted
    static_assert(std::is_same_v<decltype(dotProduct), const double>);

    // Then, the dot product is non-zero
    EXPECT_DOUBLE_EQ(126.049382661, dotProduct);
}


/**************************************
 *                                    *
 *        CROSS PRODUCT TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that the cross product of vector aligned with x-axis and a vector aligned with y-axis
 *        returns a vector aligned with the z-axis.
 */
TEST(Vec3CrossProduct, BetweenAxisAlignedXAndYVectorsReturnsZ)
{
    const fgm::Vec3 xAxis(1.0f, 0.0f, 0.0f);
    const fgm::Vec3 yAxis(0.0f, 1.0f, 0.0f);
    const fgm::Vec3 expectedCrossProduct(0.0f, 0.0f, 1.0f);

    const fgm::Vec3 crossProduct = xAxis.cross(yAxis);

    EXPECT_VEC_EQ(expectedCrossProduct, crossProduct);
}


/**
 * @brief Verify that the cross product of vector aligned with y-axis and a vector aligned with x-axis
 *        returns a vector aligned with the negative z-axis.
 */
TEST(Vec3CrossProduct, BetweenAxisAlignedYAndZVectorsReturnsNegativeZ)
{
    const fgm::Vec3 yAxis(0.0f, 1.0f, 0.0f);
    const fgm::Vec3 xAxis(1.0f, 0.0f, 0.0f);
    const fgm::Vec3 expectedCrossProduct(0.0f, 0.0f, -1.0f);

    const fgm::Vec3 crossProduct = yAxis.cross(xAxis);

    EXPECT_VEC_EQ(expectedCrossProduct, crossProduct);
}


/**
 * @brief Verify that the cross product of vector aligned with z-axis and a vector aligned with y-axis
 *        returns a vector aligned with the negative x-axis.
 */
TEST(Vec3CrossProduct, BetweenAxisAlignedZAndYVectorsReturnsNegativeX)
{
    // Arrange
    const fgm::Vec3 zAxis(0.0f, 0.0f, 1.0f);
    const fgm::Vec3 yAxis(0.0f, 1.0f, 0.0f);
    const fgm::Vec3 expectedCrossProduct(-1.0f, 0.0f, 0.0f);

    // Act
    const fgm::Vec3 crossProduct = zAxis.cross(yAxis);

    // Assert
    EXPECT_VEC_EQ(expectedCrossProduct, crossProduct);
}


/** @brief Verify that the cross product of vector with self is a zero-vector. */
TEST(Vec3CrossProduct, VectorCrossItselfReturnsZeroVector)
{
    const fgm::Vec3 vec(0.0f, 0.0f, 1.0f);

    const fgm::Vec3 crossProduct = vec.cross(vec);

    EXPECT_VEC_ZERO(crossProduct);
}


/** @brief Verify that the cross product of vector with a non-parallel vector returns a new vector. */
TYPED_TEST(Vec3CrossProduct, BetweenTwoNonParallelVectorsReturnsNewProduct)
{
    const fgm::Vec3 crossProduct = this->_vecA.cross(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedCrossProduct, crossProduct);
}


/**
 * @brief Verify that the cross product of vector with a non-parallel vector
 *        returns a new vector perpendicular to both.
 */
TYPED_TEST(Vec3CrossProduct, BetweenTwoNonParallelVectorsReturnAVectorPerpendicularToBoth)
{
    const fgm::Vec3 crossProduct = this->_vecA.cross(this->_vecB);

    // Orientation Check: Dot must be zero
    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(0.0, this->_vecA.dot(crossProduct));
        EXPECT_DOUBLE_EQ(0.0, this->_vecB.dot(crossProduct));
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(0.0f, this->_vecA.dot(crossProduct));
        EXPECT_FLOAT_EQ(0.0f, this->_vecB.dot(crossProduct));
    }
    else
    {
        EXPECT_EQ(0, this->_vecA.dot(crossProduct));
        EXPECT_EQ(0, this->_vecB.dot(crossProduct));
    }
}


/**
 * @brief Verify that the cross product of vector with a non-parallel vector using static variant of
 *        @ref fgm::Vec3::cross returns a new vector.
 */
TYPED_TEST(Vec3CrossProduct, StaticWrapper_BetweenTwoNonParallelVectorsReturnsNewProduct)
{
    const fgm::Vec3 crossProduct = fgm::Vec3<TypeParam>::cross(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedCrossProduct, crossProduct);
}


/**
 * @brief Verify that the cross product of vector with a non-parallel vector using static variant of
 *        @ref fgm::Vec3::cross returns a new vector perpendicular to both.
 */
TYPED_TEST(Vec3CrossProduct, StaticWrapper_BetweenTwoNonParallelVectorsReturnAVectorPerpendicularToBoth)
{
    const fgm::Vec3 crossProduct = fgm::Vec3<TypeParam>::cross(this->_vecA, this->_vecB);

    // Orientation Check: Dot must be zero
    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(0.0, this->_vecA.dot(crossProduct));
        EXPECT_DOUBLE_EQ(0.0, this->_vecB.dot(crossProduct));
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(0.0f, this->_vecA.dot(crossProduct));
        EXPECT_FLOAT_EQ(0.0f, this->_vecB.dot(crossProduct));
    }
    else
    {
        EXPECT_EQ(0, this->_vecA.dot(crossProduct));
        EXPECT_EQ(0, this->_vecB.dot(crossProduct));
    }
}


/**
 * @brief Verify that the cross product between non-parallel vectors is anti-commutative.
 *        Anti-Commutativity: \f$ \mathbf{a}\times\mathbf{b} = -(\mathbf{b}\times\mathbf{a}) \f$
 */
TYPED_TEST(Vec3CrossProduct, IsAntiCommutative)
{
    fgm::Vec3 crossProduct1 = fgm::Vec3<TypeParam>::cross(this->_vecA, this->_vecB);
    fgm::Vec3 crossProduct2 = fgm::Vec3<TypeParam>::cross(this->_vecB, this->_vecA);

    EXPECT_VEC_EQ(crossProduct1, -1.0f * crossProduct2);
}


/**
 * @brief Verify that the cross product between parallel vectors is commutative.
 *        Commutativity: \f$ \mathbf{a}\times\mathbf{b} = \mathbf{b}\times\mathbf{a} \f$,
 *        **given a and b are scalar multiples of each other**.
 */
TYPED_TEST(Vec3CrossProduct, BetweenParallelVectorIsCommutatives)
{
    const fgm::Vec3 vecB    = TypeParam(2) * this->_vecA;
    fgm::Vec3 crossProduct1 = fgm::Vec3<TypeParam>::cross(this->_vecA, vecB);
    fgm::Vec3 crossProduct2 = fgm::Vec3<TypeParam>::cross(vecB, this->_vecA);

    EXPECT_VEC_EQ(crossProduct1, crossProduct2);
}


/** @brief Verify that the cross product between two differently typed vectors promote type. */
TEST(Vec3CrossProduct, BetweenDifferentlyTypedVectorsPromotesType)
{
    const fgm::Vec3 vecA(2.0f, 3.0f, 4.0f);
    const fgm::Vec3 vecB(5.0, 6.0, 7.0);

    [[maybe_unused]] const fgm::Vec3 crossProduct = vecA.cross(vecB);

    static_assert(std::is_same_v<typename decltype(crossProduct)::value_type, double>);
}

/** @} */
