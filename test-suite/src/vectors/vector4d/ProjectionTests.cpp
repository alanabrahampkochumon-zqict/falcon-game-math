/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref fgm::Vector4D<bool> projection and rejection logic.
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
    fgm::Vector4D<T> _vec;
    fgm::Vector4D<T> _perpendicularVec;
    fgm::Vector4D<T> _ontoVec;
    fgm::Vector4D<T> _expectedProjection;

    void SetUp() override
    {
        _vec = { T(5), T(6), T(7), T(8) };
        _perpendicularVec = { T(10), T(0), T(14), T(16) };
        _ontoVec = { T(0), T(2), T(0), T(0) };
        _expectedProjection = { T(0), T(6), T(0), T(0) };
    }
};
/** @brief Test fixture for @ref Vector4D projection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DProjection, SupportedArithmeticTypes);


template <typename T>
class Vector4DRejection: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> _vec;
    fgm::Vector4D<T> _parallelVec;
    fgm::Vector4D<T> _ontoVec;
    fgm::Vector4D<T> _expectedRejection;

    void SetUp() override
    {
        _vec = { T(5), T(6), T(7), T(8) };
        _parallelVec = { T(10), T(12), T(14), T(16) };
        _ontoVec = { T(0), T(2), T(0), T(0) };
        _expectedRejection = { T(5), T(0), T(7), T(8) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D rejection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DRejection, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Vec4_Proj
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
    const fgm::Vector4D actualProjection = this->_perpendicularVec.project(this->_ontoVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projecting a @ref fgm::Vector4D onto another @ref fgm::Vector4D containing only an x-component
 *       returns a vector containing only an x-component.
 */
TEST(Vector4DProjection, ProjectionOntoXAxisReturnsVectorWithOnlyXComponent)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    constexpr fgm::Vector4D xAxis(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedProjection(10.0f, 0.0f, 0.0f, 0.0f);

    // When projected onto x-axis
    constexpr fgm::Vector4D actualProjection = a.project(xAxis);

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
    constexpr fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    constexpr fgm::Vector4D yAxis(0.0f, 1.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedProjection(0.0f, 20.0f, 0.0f, 0.0f);

    // When projected onto y-axis
    constexpr fgm::Vector4D actualProjection = a.project(yAxis);

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
    constexpr fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    constexpr fgm::Vector4D zAxis(0.0f, 0.0f, 1.0f, 0.0f);
    constexpr fgm::Vector4D expectedProjection(0.0f, 0.0f, 30.0f, 0.0f);

    // When projected onto z-axis
    constexpr fgm::Vector4D actualProjection = a.project(zAxis);

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
    constexpr fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    constexpr fgm::Vector4D wAxis(0.0f, 0.0f, 0.0f, 1.0f);
    constexpr fgm::Vector4D expectedProjection(0.0f, 0.0f, 0.0f, 40.0f);

    // When projected onto w-axis
    constexpr fgm::Vector4D actualProjection = a.project(wAxis);

    // Then, the resultant vector only has w-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting a @ref fgm::Vector4D onto a non-orthogonal @ref fgm::Vector4D returns a non-zero
 *       vector.
 */
TYPED_TEST(Vector4DProjection, NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualProjection = this->_vec.project(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that the @ref fgm::Vector4D static projection wrapper returns a non-zero vector when projecting
 *        non-orthogonal instances.
 */
TYPED_TEST(Vector4DProjection, StaticWrapper_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualProjection = fgm::Vector4D<TypeParam>::project(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector with the @p ontoNormalized flag enabled returns a
 *        non-zero vector.
 */
TEST(Vector4DProjection, ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    constexpr fgm::Vector4D actualProjection = a.project(b, true);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}


/**
 * @test Verify that projecting a @ref fgm::Vector4D onto a non-orthogonal @ref fgm::Vector4D pointing in the opposite
 *       direction returns a non-zero vector.
 */
TEST(Vector4DProjection, ProjectionOntoVectorInOppositeDirectionReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    constexpr fgm::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    constexpr fgm::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    constexpr fgm::Vector4D expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);

    // When projected
    constexpr fgm::Vector4D<float> actualProjection = a.project(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/** @test Verify that projecting a @ref fgm::Vector4D onto a non-orthogonal @ref fgm::Vector4D of a different numeric
 *        type returns a type-promoted vector. */
TEST(Vector4DProjection, MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector4D vec(7, 13, 29, 41);
    constexpr fgm::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    constexpr fgm::Vector4D expectedProjection(13.2, 26.4, 26.4, 13.2);

    // When projected onto another
    constexpr fgm::Vector4D actualProjection = vec.project(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**************************************
 *                                    *
 *        SAFE PROJECTION TESTS       *
 *                                    *
 **************************************/

/**
 * @test Verify that projecting a @ref fgm::Vector4D onto a non-orthogonal @ref fgm::Vector4D using
 *       @ref fgm::Vector4D::safeProject returns a non-zero vector.
 */
TYPED_TEST(Vector4DProjection, SafeProject_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualProjection = this->_vec.safeProject(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vector4D::safeProject with the
 *       @p ontoNormalized flag enabled returns a non-zero vector.
 */
TEST(Vector4DProjection, SafeProject_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    constexpr fgm::Vector4D actualProjection = a.safeProject(b, true);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}


/**
 * @test Verify that projecting a @ref fgm::Vector4D onto a non-orthogonal @ref fgm::Vector4D pointing in the opposite
 *       direction using @ref fgm::Vector4D::safeProject returns a non-zero vector.
 */
TEST(Vector4DProjection, SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    constexpr fgm::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    constexpr fgm::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    constexpr fgm::Vector4D expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);

    // When projected
    constexpr fgm::Vector4D<float> actualProjection = a.safeProject(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/** @test Verify that projecting a @ref fgm::Vector4D onto a non-orthogonal @ref fgm::Vector4D of a different numeric
 *        type using @ref fgm::Vector4D::safeProject returns a type-promoted vector. */
TEST(Vector4DProjection, SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector4D vec(7, 13, 29, 41);
    constexpr fgm::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    constexpr fgm::Vector4D expectedProjection(13.2, 26.4, 26.4, 13.2);

    // When projected onto another
    constexpr fgm::Vector4D actualProjection = vec.safeProject(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting a @ref fgm::Vector4D onto a zero length vector using @ref fgm::Vector4D::safeProject
 *       returns a type-promoted vector.
 */
TYPED_TEST(Vector4DProjection, SafeProject_OntoZeroReturnsZeroVector)
{
    constexpr TypeParam zero = TypeParam(0);
    constexpr fgm::Vector4D zeroVec(zero, zero, zero, zero);

    const fgm::Vector4D actualProjection = this->_vec.safeProject(zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}



/**
 * @test Verify that projecting a @ref fgm::Vector4D onto a non-orthogonal @ref fgm::Vector4D using
 *       static variant of @ref fgm::Vector4D::safeProject returns a non-zero vector.
 */
TYPED_TEST(Vector4DProjection, Static_Wrapper_SafeProject_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualProjection = fgm::Vector4D<TypeParam>::safeProject(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector4D::safeProject with the @p ontoNormalized flag enabled returns a non-zero vector.
 */
TEST(Vector4DProjection, Static_Wrapper_SafeProject_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    constexpr fgm::Vector4D actualProjection = fgm::Vector4D<float>::safeProject(a, b, true);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
    EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}


/**
 * @test Verify that projecting a @ref fgm::Vector4D onto a non-orthogonal @ref fgm::Vector4D pointing in the opposite
 *       direction using static variant of @ref fgm::Vector4D::safeProject returns a non-zero vector.
 */
TEST(Vector4DProjection, Static_Wrapper_SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    constexpr fgm::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    constexpr fgm::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    constexpr fgm::Vector4D expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);

    // When projected
    constexpr fgm::Vector4D<float> actualProjection = fgm::Vector4D<float>::safeProject(a, negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting a @ref fgm::Vector4D onto a non-orthogonal @ref fgm::Vector4D of a different numeric
 *       type using static variant of @ref fgm::Vector4D::safeProject returns a type-promoted vector.
 */
TEST(Vector4DProjection, Static_Wrapper_SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector4D vec(7, 13, 29, 41);
    constexpr fgm::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    constexpr fgm::Vector4D expectedProjection(13.2, 26.4, 26.4, 13.2);

    // When projected onto another
    constexpr fgm::Vector4D actualProjection = fgm::Vector4D<float>::safeProject(vec, onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting a @ref fgm::Vector4D onto a zero length vector using static variant of
 *       @ref fgm::Vector4D::safeProject returns a type-promoted vector.
 */
TYPED_TEST(Vector4DProjection, Static_Wrapper_SafeProject_OntoZeroVectorReturnsZeroVector)
{
    constexpr TypeParam zero = TypeParam(0);
    constexpr fgm::Vector4D zeroVec(zero, zero, zero, zero);

    const fgm::Vector4D actualProjection = fgm::Vector4D<float>::safeProject(this->_vec, zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec4_Rej
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
    const fgm::Vector4D actualRejection = this->_vec.reject(this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that rejecting a @ref fgm::Vector4D from a target @ref fgm::Vector4D containing only an x-component
 *       returns a vector with a zero x-component.
 */
TEST(Vector4DRejection, RejectionFromXAxisReturnsVectorWithZeroXComponent)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    constexpr fgm::Vector4D xAxis(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(0.0f, 20.0f, 30.0f, 40.f);

    // When rejected from x-axis
    constexpr fgm::Vector4D actualRejection = a.reject(xAxis);

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
    constexpr fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    constexpr fgm::Vector4D yAxis(0.0f, 1.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(10.0f, 0.0f, 30.0f, 40.0f);

    // When rejected from y-axis
    constexpr fgm::Vector4D actualRejection = a.reject(yAxis);

    // Then, the resultant vector has zero y-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 *@test Verify that rejecting a @ref fgm::Vector4D from a target @ref fgm::Vector4D containing only a z-component
 *      returns a vector with a zero z-component.
 */
TEST(Vector4DRejection, RejectionFromZAxisReturnsVectorWithZeroZComponent)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    constexpr fgm::Vector4D zAxis(0.0f, 0.0f, 1.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(10.0f, 20.0f, 0.0f, 40.0f);

    // When rejected from z-axis
    constexpr fgm::Vector4D actualRejection = a.reject(zAxis);

    // Then, the resultant vector has zero z-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting a @ref fgm::Vector4D from a target @ref fgm::Vector4D containing only a w-component
 *       returns a vector with a zero w-component.
 */
TEST(Vector4DRejection, RejectionFromWAxisReturnsVectorWithZeroWComponent)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    constexpr fgm::Vector4D wAxis(0.0f, 0.0f, 0.0f, 1.0f);
    constexpr fgm::Vector4D expectedRejection(10.0f, 20.0f, 30.0f, 0.0f);

    // When rejected from w-axis
    constexpr fgm::Vector4D actualRejection = a.reject(wAxis);

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
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 0.0f);
    constexpr fgm::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);

    // When rejected on to an orthogonal vector
    constexpr fgm::Vector4D actualRejection = a.reject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that rejecting a @ref fgm::Vector4D from a non-orthogonal @ref fgm::Vector4D returns a non-zero
 *       vector with perpendicular component.
 */
TYPED_TEST(Vector4DRejection, NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualRejection = this->_vec.reject(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that the @ref fgm::Vector4D static rejection wrapper returns a non-zero vector when rejecting from
 *        orthogonal instances.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualRejection = fgm::Vector4D<TypeParam>::reject(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal unit vector with the @p ontoNormalized flag enabled returns a non-zero
 *       vector with perpendicular component.
 */
TEST(Vector4DRejection, RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected from another
    constexpr fgm::Vector4D actualRejection = a.reject(b, true);

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
    constexpr fgm::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    constexpr fgm::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(4.0f, 4.0f, 0.0f, 4.0f);

    // When rejection onto a vector in opposite direction
    constexpr fgm::Vector4D actualRejection = a.reject(negativeZAxis);

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
    constexpr fgm::Vector4D vec(7, 13, 29, 41);
    constexpr fgm::Vector4D from(2.0, 4.0, 4.0, 2.0);
    constexpr fgm::Vector4D expectedRejection(-6.2, -13.4, 2.6, 27.8);

    // When reject from another
    constexpr fgm::Vector4D actualRejection = vec.reject(from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**************************************
 *                                    *
 *       SAFE REJECTION TESTS         *
 *                                    *
 **************************************/

/**
 * @test Verify that safely rejecting parallel @ref fgm::Vector4D instances using @ref fgm::Vector4D::safeReject returns
 *       a zero vector.
 */
TYPED_TEST(Vector4DRejection, SafeReject_ParallelVectorsReturnsZeroVector)
{
    const fgm::Vector4D actualRejection = this->_vec.safeReject(this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting a @ref fgm::Vector4D from a target @ref fgm::Vector4D that is orthogonal using
 *       @ref fgm::Vector4D::safeReject returns the original vector.
 */
TEST(Vector4DRejection, SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 0.0f);
    constexpr fgm::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);

    // When rejected from an orthogonal vector
    constexpr fgm::Vector4D actualRejection = a.safeReject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting a @ref fgm::Vector4D from a non-orthogonal @ref fgm::Vector4D using
 *       @ref fgm::Vector4D::safeReject returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector4DRejection, SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualRejection = this->_vec.safeReject(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref fgm::Vector4D::safeReject with the
 *       @p ontoNormalized flag enabled returns a non-zero vector with perpendicular component.
 */
TEST(Vector4DRejection, SafeReject_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected from another
    constexpr fgm::Vector4D actualRejection = a.safeReject(b, true);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting a @ref fgm::Vector4D from another @ref fgm::Vector4D of a different numeric
 *       type using @ref fgm::Vector4D::safeReject returns a type-promoted vector.
 */
TEST(Vector4DRejection, SafeReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector4D vec(7, 13, 29, 41);
    constexpr fgm::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    constexpr fgm::Vector4D expectedRejection(-6.2, -13.4, 2.6, 27.8);

    // When rejected from another
    constexpr fgm::Vector4D actualRejection = vec.safeReject(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from a zero vector using @ref fgm::Vector4D::safeReject
 *       returns the same vector.
 */
TYPED_TEST(Vector4DRejection, SafeReject_FromZeroVectorReturnsSameVector)
{
    constexpr TypeParam zero = TypeParam(0);
    constexpr fgm::Vector4D zeroVec(zero, zero, zero, zero);

    const fgm::Vector4D actualRejection = this->_vec.safeReject(zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/**
 * @test Verify that safely rejecting parallel vector using static variant of @ref fgm::Vector4D::safeReject returns
 *       a zero vector.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_SafeReject_ParallelVectorsReturnsZeroVector)
{
    const fgm::Vector4D actualRejection = fgm::Vector4D<TypeParam>::safeReject(this->_vec, this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref fgm::Vector4D::safeReject returns the original vector.
 */
TEST(Vector4DRejection, StaticWrapper_SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 0.0f);
    constexpr fgm::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);

    constexpr fgm::Vector4D actualRejection = fgm::Vector4D<float>::safeReject(a, b);

    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from a non-orthogonal vector using static variant of
 *       @ref fgm::Vector4D::safeReject returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualRejection = fgm::Vector4D<TypeParam>::safeReject(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref fgm::Vector4D::safeReject with the @p ontoNormalized flag enabled returns a non-zero vector with
 *       perpendicular component.
 */
TEST(Vector4DRejection, StaticWrapper_SafeReject_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected from another
    constexpr fgm::Vector4D actualRejection = fgm::Vector4D<float>::safeReject(a, b, true);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from another vector of different numeric type
 *       using static variant of @ref fgm::Vector4D::safeReject returns a type-promoted vector.
 */
TEST(Vector4DRejection, StaticWrapper_SafeReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector4D vec(7, 13, 29, 41);
    constexpr fgm::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    constexpr fgm::Vector4D expectedRejection(-6.2, -13.4, 2.6, 27.8);

    // When rejected from another
    constexpr fgm::Vector4D actualRejection = fgm::Vector4D<float>::safeReject(vec, onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from a zero vector using static variant of @ref fgm::Vector4D::safeReject returns
 *       the same vector.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_SafeReject_FromZeroVectorReturnsSameVector)
{
    constexpr TypeParam zero = TypeParam(0);
    constexpr fgm::Vector4D zeroVec(zero, zero, zero, zero);

    const fgm::Vector4D actualRejection = fgm::Vector4D<TypeParam>::safeReject(this->_vec, zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}

/** @} */