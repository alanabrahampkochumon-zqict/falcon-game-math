/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref Vector4D<bool> projection and rejection logic.
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
    fgm::Vector4D<T> vec;
    fgm::Vector4D<T> perpendicularVec;
    fgm::Vector4D<T> onto;
    fgm::Vector4D<T> expectedProjection;

    void SetUp() override
    {
        vec = { T(5), T(6), T(7), T(8) };
        perpendicularVec = { T(10), T(0), T(14), T(16) };
        onto = { T(0), T(2), T(0), T(0) };
        expectedProjection = { T(0), T(6), T(0), T(0) };
    }
};
/** @brief Test fixture for @ref Vector4D projection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DProjection, SupportedArithmeticTypes);


template <typename T>
class Vector4DRejection: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> vec;
    fgm::Vector4D<T> parallelVec;
    fgm::Vector4D<T> onto;
    fgm::Vector4D<T> expectedRejection;

    void SetUp() override
    {
        vec = { T(5), T(6), T(7), T(8) };
        parallelVec = { T(10), T(12), T(14), T(16) };
        onto = { T(0), T(2), T(0), T(0) };
        expectedRejection = { T(5), T(0), T(7), T(8) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D rejection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DRejection, SupportedArithmeticTypes);




/**
 * @addtogroup FGM_Vec4_Proj
 * @{
 */

/**************************************
 *                                    *
 *          PROJECTION TESTS          *
 *                                    *
 **************************************/

/** @test Verify that projecting orthogonal @ref fgm::Vector4D instances returns a zero vector. */
TYPED_TEST(Vector4DProjection, OrthogonalVectorsReturnsZeroVector)
{
    const fgm::Vector4D actualProjection = this->perpendicularVec.project(this->onto);

    EXPECT_VEC_ZERO(actualProjection);
}

/**
 * @test Verify that projecting a @ref fgm::Vector4D onto another @ref fgm::Vector4D containing only an x-component
 *       returns a vector containing only an x-component.
 */
TEST(Vector4DProjection, ProjectionOntoXAxisReturnsVectorWithOnlyXComponent)
{
    // Given an arbitrary vector
    const fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const fgm::Vector4D xAxis(1.0f, 0.0f, 0.0f, 0.0f);
    const fgm::Vector4D expectedProjection(10.0f, 0.0f, 0.0f, 0.0f);

    // When projected onto x-axis
    const fgm::Vector4D actualProjection = a.project(xAxis);

    // Then, the resultant vector only has x-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

/**
 * @test Verify that projecting a @ref fgm::Vector4D onto another @ref fgm::Vector4D containing only a y-component
 *       returns a vector containing only a y-component.
 */
TEST(Vector4DProjection, ProjectionOntoYAxisReturnsVectorWithOnlyYComponent)
{
    // Given an arbitrary vector
    const fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const fgm::Vector4D yAxis(0.0f, 1.0f, 0.0f, 0.0f);
    const fgm::Vector4D expectedProjection(0.0f, 20.0f, 0.0f, 0.0f);

    // When projected onto y-axis
    const fgm::Vector4D actualProjection = a.project(yAxis);

    // Then, the resultant vector only has y-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

/**
 * @test Verify that projecting a @ref fgm::Vector4D onto another @ref fgm::Vector4D containing only a z-component
 *       returns a vector containing only a z-component.
 */
TEST(Vector4DProjection, ProjectionOntoZAxisReturnsVectorWithOnlyZComponent)
{
    // Given an arbitrary vector
    const fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const fgm::Vector4D zAxis(0.0f, 0.0f, 1.0f, 0.0f);
    const fgm::Vector4D expectedProjection(0.0f, 0.0f, 30.0f, 0.0f);

    // When projected onto z-axis
    const fgm::Vector4D actualProjection = a.project(zAxis);

    // Then, the resultant vector only has z-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

/**
 * @test Verify that projecting a @ref fgm::Vector4D onto another @ref fgm::Vector4D containing only a w-component
 *       returns a vector containing only a w-component.
 */
TEST(Vector4DProjection, ProjectionOntoWAxisReturnsVectorWithOnlyWComponent)
{
    // Given an arbitrary vector
    const fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const fgm::Vector4D wAxis(0.0f, 0.0f, 0.0f, 1.0f);
    const fgm::Vector4D expectedProjection(0.0f, 0.0f, 0.0f, 40.0f);

    // When projected onto w-axis
    const fgm::Vector4D actualProjection = a.project(wAxis);

    // Then, the resultant vector only has w-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

/**
 * @test Verify that projecting a @ref fgm::Vector4D onto a non-orthogonal @ref fgm::Vector4D returns a non-zero
 *       vector.
 */
TYPED_TEST(Vector4DProjection, NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualProjection = this->vec.project(this->onto);

    EXPECT_VEC_EQ(this->expectedProjection, actualProjection);
}

/** 
 * @test Verify that the @ref fgm::Vector4D static projection wrapper returns a non-zero vector when projecting
 *        non-orthogonal instances.
 */
TYPED_TEST(Vector4DProjection, StaticWrapper_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualProjection = fgm::Vector4D<TypeParam>::project(this->vec, this->onto);

    EXPECT_VEC_EQ(this->expectedProjection, actualProjection);
}

/**
 * @test Verify that projecting onto a non-orthogonal unit vector with the @p ontoNormalized flag enabled returns a
 *        non-zero vector.
 */
TEST(Vector4DProjection, ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const fgm::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector4D actualProjection = a.project(b, true);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

/**
 * @test Verify that projecting a @ref fgm::Vector4D onto a non-orthogonal @ref fgm::Vector4D pointing in the opposite
 *        direction returns a non-zero vector. 
 */
TEST(Vector4DProjection, ProjectionOntoVectorInOppositeDirectionReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    const fgm::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    const fgm::Vector4D expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);

    // When projected
    const fgm::Vector4D<float> actualProjection = a.project(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

/** @test Verify that projecting a @ref fgm::Vector4D onto a non-orthogonal @ref fgm::Vector4D of a different numeric
 *        type returns a type-promoted vector. */
TEST(Vector4DProjection, MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector4D vec(7, 13, 29, 41);
    const fgm::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    const fgm::Vector4D expectedProjection(13.2, 26.4, 26.4, 13.2);

    // When projected onto another
    const fgm::Vector4D actualProjection = vec.project(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

/** @} */





/**
 * @addtogroup FGM_Vec4_Rej
 * @{
 */

/**************************************
 *                                    *
 *          REJECTION TESTS           *
 *                                    *
 **************************************/

/** @test Verify that rejecting parallel @ref fgm::Vector4D instances returns a zero vector. */
TYPED_TEST(Vector4DRejection, ParallelVectorsReturnsZeroVector)
{
    const fgm::Vector4D actualRejection = this->vec.reject(this->parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}

/**
 * @test Verify that rejecting a @ref fgm::Vector4D from a target @ref fgm::Vector4D containing only an x-component
 *       returns a vector with a zero x-component.
 */
TEST(Vector4DRejection, RejectionFromXAxisReturnsVectorWithZeroXComponent)
{
    // Given an arbitrary vector
    const fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const fgm::Vector4D xAxis(1.0f, 0.0f, 0.0f, 0.0f);
    const fgm::Vector4D expectedRejection(0.0f, 20.0f, 30.0f, 40.f);

    // When rejected from x-axis
    const fgm::Vector4D actualRejection = a.reject(xAxis);

    // Then, the resultant vector has zero x-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

/**
 * @test Verify that rejecting a @ref fgm::Vector4D from a target @ref fgm::Vector4D containing only a y-component
 *       returns a vector with a zero y-component.
 */
TEST(Vector4DRejection, RejectionFromYAxisReturnsVectorWithZeroYComponent)
{
    // Given an arbitrary vector
    const fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const fgm::Vector4D yAxis(0.0f, 1.0f, 0.0f, 0.0f);
    const fgm::Vector4D expectedRejection(10.0f, 0.0f, 30.0f, 40.0f);

    // When rejected from y-axis
    const fgm::Vector4D actualRejection = a.reject(yAxis);

    // Then, the resultant vector has zero y-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

/**
 *@test Verify that rejecting a @ref fgm::Vector4D from a target @ref fgm::Vector4D containing only a z-component
 *        returns a vector with a zero z-component.
 */
TEST(Vector4DRejection, RejectionFromZAxisReturnsVectorWithZeroZComponent)
{
    // Given an arbitrary vector
    const fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const fgm::Vector4D zAxis(0.0f, 0.0f, 1.0f, 0.0f);
    const fgm::Vector4D expectedRejection(10.0f, 20.0f, 0.0f, 40.0f);

    // When rejected from z-axis
    const fgm::Vector4D actualRejection = a.reject(zAxis);

    // Then, the resultant vector has zero z-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

/**
 * @test Verify that rejecting a @ref fgm::Vector4D from a target @ref fgm::Vector4D containing only a w-component
 *        returns a vector with a zero w-component.
 */
TEST(Vector4DRejection, RejectionFromWAxisReturnsVectorWithZeroWComponent)
{
    // Given an arbitrary vector
    const fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    const fgm::Vector4D wAxis(0.0f, 0.0f, 0.0f, 1.0f);
    const fgm::Vector4D expectedRejection(10.0f, 20.0f, 30.0f, 0.0f);

    // When rejected from w-axis
    const fgm::Vector4D actualRejection = a.reject(wAxis);

    // Then, the resultant vector has zero w-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

/** 
 * @test Verify that rejecting a @ref fgm::Vector4D from a target @ref fgm::Vector4D that is orthogonal returns the
 *       original vector.
 */
TEST(Vector4DRejection, OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 0.0f);
    const fgm::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);

    // When rejected on to an orthogonal vector
    const fgm::Vector4D actualRejection = a.reject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}

/** 
 * @test Verify that rejecting a @ref fgm::Vector4D from a non-orthogonal @ref fgm::Vector4D returns a non-zero
 *       vector with perpendicular component.
 */
TYPED_TEST(Vector4DRejection, NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualRejection = this->vec.reject(this->onto);

    EXPECT_VEC_EQ(this->expectedRejection, actualRejection);
}

/**
 * @test Verify that the @ref fgm::Vector4D static rejection wrapper returns a non-zero vector when rejecting from
 *        orthogonal instances.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualRejection = fgm::Vector4D<TypeParam>::reject(this->vec, this->onto);

    EXPECT_VEC_EQ(this->expectedRejection, actualRejection);
}

/**
 * @test Verify that rejecting from an orthogonal unit vector with the @p ontoNormalized flag enabled returns a non-zero
 *       vector with perpendicular component.
 */
TEST(Vector4DRejection, RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const fgm::Vector4D expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected from another
    const fgm::Vector4D actualRejection = a.reject(b, true);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

/**
 * @test Verify that rejecting a @ref fgm::Vector4D from an orthogonal @ref fgm::Vector4D pointing in the opposite
 *        direction returns a non-zero vector with perpendicular components.
 */
TEST(Vector4DRejection, RejectionFromVectorInOppositeDirectionReturnsVectorWithPerpendicularComponents)
{
    // Given an arbitrary vector
    const fgm::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    const fgm::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    const fgm::Vector4D expectedRejection(4.0f, 4.0f, 0.0f, 4.0f);

    // When rejection onto a vector in opposite direction
    const fgm::Vector4D actualRejection = a.reject(negativeZAxis);

    // Then, the resultant vector has components perpendicular to the `from` vector in the same direction.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

/**
 * @test Verify that rejecting a @ref fgm::Vector4D from another @ref fgm::Vector4D of a different numeric
 *       type returns a type-promoted vector.
 */
TEST(Vector4DRejection, MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector4D vec(7, 13, 29, 41);
    const fgm::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    const fgm::Vector4D expectedRejection(-6.2, -13.4, 2.6, 27.8);

    // When projected onto another
    const fgm::Vector4D actualRejection = vec.reject(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

/** @} */