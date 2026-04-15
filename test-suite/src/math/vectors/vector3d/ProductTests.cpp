/**
 * @file ProductTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref fgm::Vector3D dot and cross product logic.
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
        _vecAOrthogonal = { T(3), T(0), T(4) };
        _vecBOrthogonal = { T(0), T(5), T(0) };
        _expectedDotProduct = static_cast<T>(65);

        _expectedADotA = static_cast<T>(29);
    }
};
/** @brief Test fixture for @ref fgm::Vector3D dot product, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector3DDotProduct, SupportedArithmeticTypes);


template <typename T>
class Vector3DCrossProduct: public ::testing::Test
{
protected:
    fgm::Vector3D<T> _vecA;
    fgm::Vector3D<T> _vecB;
    fgm::Vector3D<T> _expectedCrossProduct;

    void SetUp() override
    {
        _vecA = { T(2), T(3), T(4) };
        _vecB = { T(5), T(6), T(7) };
        _expectedCrossProduct = { T(-3), T(6), T(-3) };
    }
};
/** @brief Test fixture for @ref fgm::Vector3D cross product, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector3DCrossProduct, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Product
 * @{
 */

/**************************************
 *                                    *
 *         DOT PRODUCT TESTS          *
 *                                    *
 **************************************/

/** @test Verify that the dot product of a vector with itself returns its squared magnitude. */
TYPED_TEST(Vector3DDotProduct, SelfDotProductReturnsSquareMagnitude)
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
TYPED_TEST(Vector3DDotProduct, OrthogonalDotProductReturnZero)
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
TYPED_TEST(Vector3DDotProduct, NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam dotProduct = this->_vecA.dot(this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, dotProduct);
    else if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, dotProduct);
    else
        EXPECT_EQ(this->_expectedDotProduct, dotProduct);
}


/** @test Verify that the static variant of @ref fgm::Vector3D::dot returns a non-zero scalar. */
TYPED_TEST(Vector3DDotProduct, StaticWrapper_NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam dotProduct = fgm::Vector3D<TypeParam>::dot(this->_vecA, this->_vecB);

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
TEST(Vector3DDotProduct, AntiParallelDotProductReturnsNegativeScalar)
{
    // Given two opposite vectors
    constexpr fgm::Vector3D vecA(-1.0, 0.0, 0.0);
    constexpr fgm::Vector3D vecB(1.0, 0.0, 0.0);

    // When dot with each other
    const double dotProduct = vecA.dot(vecB);

    // Then, the dot product is -1
    EXPECT_DOUBLE_EQ(-1.0, dotProduct);
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
TEST(Vector3DCrossProduct, BetweenAxisAlignedXAndYVectorsReturnsZ)
{
    constexpr fgm::Vector3D xAxis(1.0f, 0.0f, 0.0f);
    constexpr fgm::Vector3D yAxis(0.0f, 1.0f, 0.0f);
    constexpr fgm::Vector3D expectedCrossProduct(0.0f, 0.0f, 1.0f);

    constexpr fgm::Vector3D crossProduct = xAxis.cross(yAxis);

    EXPECT_VEC_EQ(expectedCrossProduct, crossProduct);
}


/**
 * @brief Verify that the cross product of vector aligned with y-axis and a vector aligned with x-axis
 *        returns a vector aligned with the negative z-axis.
 */
TEST(Vector3DCrossProduct, BetweenAxisAlignedYAndZVectorsReturnsNegativeZ)
{
    constexpr fgm::Vector3D yAxis(0.0f, 1.0f, 0.0f);
    constexpr fgm::Vector3D xAxis(1.0f, 0.0f, 0.0f);
    constexpr fgm::Vector3D expectedCrossProduct(0.0f, 0.0f, -1.0f);

    constexpr fgm::Vector3D crossProduct = yAxis.cross(xAxis);

    EXPECT_VEC_EQ(expectedCrossProduct, crossProduct);
}


/**
 * @brief Verify that the cross product of vector aligned with z-axis and a vector aligned with y-axis
 *        returns a vector aligned with the negative x-axis.
 */
TEST(Vector3DCrossProduct, BetweenAxisAlignedZAndYVectorsReturnsNegativeX)
{
    // Arrange
    constexpr fgm::Vector3D zAxis(0.0f, 0.0f, 1.0f);
    constexpr fgm::Vector3D yAxis(0.0f, 1.0f, 0.0f);
    constexpr fgm::Vector3D expectedCrossProduct(-1.0f, 0.0f, 0.0f);

    // Act
    constexpr fgm::Vector3D crossProduct = zAxis.cross(yAxis);

    // Assert
    EXPECT_VEC_EQ(expectedCrossProduct, crossProduct);
}


/** @brief Verify that the cross product of vector with self is a zero-vector. */
TEST(Vector3DCrossProduct, VectorCrossItselfReturnsZeroVector)
{
    constexpr fgm::Vector3D vec(0.0f, 0.0f, 1.0f);

    constexpr fgm::Vector3D crossProduct = vec.cross(vec);

    EXPECT_VEC_ZERO(crossProduct);
}


/** @brief Verify that the cross product of vector with a non-parallel vector returns a new vector. */
TYPED_TEST(Vector3DCrossProduct, BetweenTwoNonParallelVectorsReturnsNewProduct)
{
    const fgm::Vector3D crossProduct = this->_vecA.cross(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedCrossProduct, crossProduct);
}


/**
 * @brief Verify that the cross product of vector with a non-parallel vector
 *        returns a new vector perpendicular to both.
 */
TYPED_TEST(Vector3DCrossProduct, BetweenTwoNonParallelVectorsReturnAVectorPerpendicularToBoth)
{
    const fgm::Vector3D crossProduct = this->_vecA.cross(this->_vecB);

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
 *        @ref fgm::Vector3D::cross returns a new vector.
 */
TYPED_TEST(Vector3DCrossProduct, StaticWrapper_BetweenTwoNonParallelVectorsReturnsNewProduct)
{
    const fgm::Vector3D crossProduct = fgm::Vector3D<TypeParam>::cross(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedCrossProduct, crossProduct);
}


/**
 * @brief Verify that the cross product of vector with a non-parallel vector using static variant of
 *        @ref fgm::Vector3D::cross returns a new vector perpendicular to both.
 */
TYPED_TEST(Vector3DCrossProduct, StaticWrapper_BetweenTwoNonParallelVectorsReturnAVectorPerpendicularToBoth)
{
    const fgm::Vector3D crossProduct = fgm::Vector3D<TypeParam>::cross(this->_vecA, this->_vecB);

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
TYPED_TEST(Vector3DCrossProduct, IsAntiCommutative)
{
    fgm::Vector3D crossProduct1 = fgm::Vector3D<float>::cross(this->_vecA, this->_vecB);
    fgm::Vector3D crossProduct2 = fgm::Vector3D<float>::cross(this->_vecB, this->_vecA);

    EXPECT_VEC_EQ(crossProduct1, -1.0f * crossProduct2);
}


/**
 * @brief Verify that the cross product between parallel vectors is commutative.
 *        Commutativity: \f$ \mathbf{a}\times\mathbf{b} = \mathbf{b}\times\mathbf{a} \f$,
 *        **given a and b are scalar multiples of each other**.
 */
TYPED_TEST(Vector3DCrossProduct, BetweenParallelVectorIsCommutatives)
{
    const fgm::Vector3D vecB = TypeParam(2) * this->_vecA;
    fgm::Vector3D crossProduct1 = fgm::Vector3D<float>::cross(this->_vecA, vecB);
    fgm::Vector3D crossProduct2 = fgm::Vector3D<float>::cross(vecB, this->_vecA);

    EXPECT_VEC_EQ(crossProduct1, crossProduct2);
}


/** @brief Verify that the cross product between two differently typed vectors promote type. */
TEST(Vector3DCrossProduct, BetweenDifferentlyTypedVectorsPromotesType)
{
    constexpr fgm::Vector3D vecA(2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector3D vecB(5.0, 6.0, 7.0);

    [[maybe_unused]] constexpr fgm::Vector3D crossProduct = vecA.cross(vecB);

    static_assert(std::is_same_v<typename decltype(crossProduct)::value_type, double>);
}

/** @} */
