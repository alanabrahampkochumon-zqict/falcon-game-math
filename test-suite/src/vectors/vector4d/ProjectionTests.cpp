/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief `Vector4D` projection and rejection tests.
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
class Vector4DProjection: public ::testing::Test
{
    protected:
    math::Vector4D<T> vec;
    math::Vector4D<T> perpendicularVec;
    math::Vector4D<T> onto;
    math::Vector4D<T> expectedProjection;

    void SetUp() override
    {
        vec = { T(5), T(6), T(7), T(8) };
        perpendicularVec = { T(10), T(0), T(14), T(16) };
        onto = { T(0), T(2), T(0), T(0) };
        expectedProjection = { T(0), T(6), T(0), T(0) };
    }
};
TYPED_TEST_SUITE(Vector4DProjection, SupportedArithmeticTypes);

template <typename T>
class Vector4DRejection: public ::testing::Test
{
    protected:
    math::Vector4D<T> vec;
    math::Vector4D<T> parallelVec;
    math::Vector4D<T> onto;
    math::Vector4D<T> expectedRejection;

    void SetUp() override
    {
        vec = { T(5), T(6), T(7), T(8) };
        parallelVec = { T(10), T(12), T(14), T(16) };
        onto = { T(0), T(2), T(0), T(0) };
        expectedRejection = { T(5), T(0), T(7), T(8) };
    }
};
TYPED_TEST_SUITE(Vector4DRejection, SupportedArithmeticTypes);


/**************************************
 *                                    *
 *          PROJECTION TESTS          *
 *                                    *
 **************************************/

TYPED_TEST(Vector4DProjection, OrthogonalVectorsWhenProjectedReturnsZeroVector)
{
    // Given two orthogonal vectors

    // When projected onto another
    const math::Vector4D actualProjection = this->perpendicularVec.project(this->onto);

    // Then, the resultant is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}

TEST(Vector4DProjection, VectorProjectedOntoXAxisProducesVectorWithOnlyXComponent)
{
    // Given an arbitrary vector
    const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const math::Vector4D xAxis(1.0f, 0.0f, 0.0f, 0.0f);
    const math::Vector4D expectedProjection(10.0f, 0.0f, 0.0f, 0.0f);

    // When projected onto x-axis
    const math::Vector4D actualProjection = a.project(xAxis);

    // Then, the resultant vector only has x-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector4DProjection, VectorProjectedOntoYAxisProducesVectorWithOnlyYComponent)
{
    // Given an arbitrary vector
    const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const math::Vector4D yAxis(0.0f, 1.0f, 0.0f, 0.0f);
    const math::Vector4D expectedProjection(0.0f, 20.0f, 0.0f, 0.0f);

    // When projected onto y-axis
    const math::Vector4D actualProjection = a.project(yAxis);

    // Then, the resultant vector only has y-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector4DProjection, VectorProjectedOntoZAxisProducesVectorWithOnlyZComponent)
{
    // Given an arbitrary vector
    const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const math::Vector4D zAxis(0.0f, 0.0f, 1.0f, 0.0f);
    const math::Vector4D expectedProjection(0.0f, 0.0f, 30.0f, 0.0f);

    // When projected onto z-axis
    const math::Vector4D actualProjection = a.project(zAxis);

    // Then, the resultant vector only has z-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector4DProjection, VectorProjectedOntoWAxisProducesVectorWithOnlyWComponent)
{
    // Given an arbitrary vector
    const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const math::Vector4D wAxis(0.0f, 0.0f, 0.0f, 1.0f);
    const math::Vector4D expectedProjection(0.0f, 0.0f, 0.0f, 40.0f);

    // When projected onto w-axis
    const math::Vector4D actualProjection = a.project(wAxis);

    // Then, the resultant vector only has w-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TYPED_TEST(Vector4DProjection, VectorsWhenProjectedReturnsNonZeroVector)
{
    // Given an arbitrary vector

    // When projected onto another vector
    const math::Vector4D actualProjection = this->vec.project(this->onto);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(this->expectedProjection, actualProjection);
}

TYPED_TEST(Vector4DProjection, StaticWrapper_VectorsWhenProjectedReturnsNonZeroVector)
{
    // Given an arbitrary vector

    // When projected onto another vector
    const math::Vector4D actualProjection = math::Vector4D<TypeParam>::project(this->vec, this->onto);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(this->expectedProjection, actualProjection);
}

TEST(Vector4DProjection, VectorProjectedOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const math::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const math::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const math::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const math::Vector4D actualProjection = a.project(b, true);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4DProjection, VectorProjectedOntoNegativeVectorReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const math::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    const math::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    const math::Vector4D expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);

    // When projected
    const math::Vector4D<float> actualProjection = a.project(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector4DProjection, MixedTypeVectorProjectionPromotesType)
{
    // Given two arbitrary vectors
    const math::Vector4D vec(7, 13, 29, 41);
    const math::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    const math::Vector4D expectedProjection(13.2, 26.4, 26.4, 13.2);

    // When projected onto another
    const math::Vector4D actualProjection = vec.project(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**************************************
 *                                    *
 *          REJECTION TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Vector4DRejection, ParallelVectorsWhenRejectedReturnsZeroVector)
{
    // Given two parallel vectors

    // When rejected onto another
    const math::Vector4D actualRejection = this->vec.reject(this->parallelVec);

    // Then, the resultant vector is zero
    EXPECT_VEC_ZERO(actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoXAxisReturnsVectorWithoutXComponent)
{
    // Given an arbitrary vector
    const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const math::Vector4D xAxis(1.0f, 0.0f, 0.0f, 0.0f);
    const math::Vector4D expectedRejection(0.0f, 20.0f, 30.0f, 40.f);

    // When rejected onto x-axis
    const math::Vector4D actualRejection = a.reject(xAxis);

    // Then, the resultant vector has no x-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoYAxisReturnsVectorWithoutYComponent)
{
    // Given an arbitrary vector
    const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const math::Vector4D yAxis(0.0f, 1.0f, 0.0f, 0.0f);
    const math::Vector4D expectedRejection(10.0f, 0.0f, 30.0f, 40.0f);

    // When rejected onto y-axis
    const math::Vector4D actualRejection = a.reject(yAxis);

    // Then, the resultant vector has no y-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoZAxisReturnsVectorWithoutZComponent)
{
    // Given an arbitrary vector
    const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const math::Vector4D zAxis(0.0f, 0.0f, 1.0f, 0.0f);
    const math::Vector4D expectedRejection(10.0f, 20.0f, 0.0f, 40.0f);

    // When rejected onto z-axis
    const math::Vector4D actualRejection = a.reject(zAxis);

    // Then, the resultant vector has no z-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoWAxisReturnsVectorWithoutWComponent)
{
    // Given an arbitrary vector
    const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const math::Vector4D wAxis(0.0f, 0.0f, 0.0f, 1.0f);
    const math::Vector4D expectedRejection(10.0f, 20.0f, 30.0f, 0.0f);

    // When rejected onto w-axis
    const math::Vector4D actualRejection = a.reject(wAxis);

    // Then, the resultant vector has no w-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoNonExistentComponentReturnsSameVector)
{
    // Given an arbitrary vector
    const math::Vector4D a(1.0f, 2.0f, 3.0f, 0.0f);
    const math::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);

    // When rejected on to non-existent component vector
    const math::Vector4D actualRejection = a.reject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}

TYPED_TEST(Vector4DRejection, VectorWhenRejectedReturnNonZeroVector)
{
    // Given an arbitrary vector

    // When rejected onto another
    const math::Vector4D actualRejection = this->vec.reject(this->onto);

    // Then, the resultant vector has components non-parallel to onto vector.
    EXPECT_VEC_EQ(this->expectedRejection, actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoNormalizedVectorReturnNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const math::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const math::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const math::Vector4D expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected onto another
    const math::Vector4D actualRejection = a.reject(b, true);

    // Then, the resultant vector has components non-parallel to onto vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoNegativeVectorReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector
    const math::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    const math::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    const math::Vector4D expectedRejection(4.0f, 4.0f, 0.0f, 4.0f);

    // When rejection onto a vector in opposite direction
    const math::Vector4D actualRejection = a.reject(negativeZAxis);

    // Then, the resultant vector has components non-parallel to onto vector in the same direction.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TYPED_TEST(Vector4DRejection, StaticWrapper_VectorWhenRejectedReturnNonZeroVector)
{
    // Given an arbitrary vector

    // When rejected onto another
    const math::Vector4D actualRejection = math::Vector4D<TypeParam>::reject(this->vec, this->onto);

    // Then, the resultant vector has components non-parallel to onto vector.
    EXPECT_VEC_EQ(this->expectedRejection, actualRejection);
}

TEST(Vector4DRejection, MixedTypeVectorRejectionPromotesType)
{
    // Given two arbitrary vectors
    const math::Vector4D vec(7, 13, 29, 41);
    const math::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    const math::Vector4D expectedRejection(-6.2, -13.4, 2.6, 27.8);

    // When projected onto another
    const math::Vector4D actualRejection = vec.reject(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}