/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vector3 projection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector3Projection: public ::testing::Test
{
protected:
    fgm::Vector3<T> _vec;
    fgm::Vector3<T> _perpendicularVec;
    fgm::Vector3<T> _ontoVec;
    fgm::Vector3<T> _expectedProjection;

    void SetUp() override
    {
        _vec                = { T(4), T(9), T(0) };
        _perpendicularVec   = { T(0), T(0), T(11) };
        _ontoVec            = { T(0), T(2), T(0) };
        _expectedProjection = { T(0), T(9), T(0) };
    }
};
/** @brief Test fixture for @ref Vector3 projection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector3Projection, SupportedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Vector3 projection with NaN vectors. */
class Vector3ProjectionNaNTests: public ::testing::TestWithParam<fgm::Vector3<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vector3ProjectionTestSuite, Vector3ProjectionNaNTests,
                         ::testing::Values(fgm::Vector3<float>(fgm::constants::NaN, 1.0f, 1.0f),
                                           fgm::Vector3<float>(1.0f, fgm::constants::NaN, 1.0f),
                                           fgm::Vector3<float>(1.0f, 1.0f, fgm::constants::NaN),
                                           fgm::Vector3<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN)));



/**
 * @addtogroup T_FGM_Vec3_Proj
 * @{
 */

/**************************************
 *                                    *
 *          PROJECTION TESTS          *
 *                                    *
 **************************************/

/** @brief Verify that vector projection is available at compile time. */
namespace
{
    constexpr fgm::Vector3 vecA(1, 2, 3);
    constexpr fgm::Vector3 vecB(1, 0, 0);
    constexpr auto proj1 = vecA.project(vecB);
    static_assert(proj1.x() == 1);
    static_assert(proj1.y() == 0);
    static_assert(proj1.z() == 0);

    constexpr auto proj2 = vecA.projectNorm(vecB);
    static_assert(proj2.x() == 1);
    static_assert(proj2.y() == 0);
    static_assert(proj2.z() == 0);

    constexpr auto proj3 = fgm::Vector3<int>::project(vecA, vecB);
    static_assert(proj3.x() == 1);
    static_assert(proj3.y() == 0);
    static_assert(proj3.z() == 0);

    constexpr auto proj4 = fgm::Vector3<int>::projectNorm(vecA, vecB);
    static_assert(proj4.x() == 1);
    static_assert(proj4.y() == 0);
    static_assert(proj4.z() == 0);

    constexpr auto proj5 = vecA.safeProject(vecB);
    static_assert(proj5.x() == 1);
    static_assert(proj5.y() == 0);
    static_assert(proj5.z() == 0);

    constexpr auto proj6 = vecA.safeProjectNorm(vecB);
    static_assert(proj6.x() == 1);
    static_assert(proj6.y() == 0);
    static_assert(proj6.z() == 0);

    constexpr auto proj7 = fgm::Vector3<int>::safeProject(vecA, vecB);
    static_assert(proj7.x() == 1);
    static_assert(proj7.y() == 0);
    static_assert(proj7.z() == 0);

    constexpr auto proj8 = fgm::Vector3<int>::safeProjectNorm(vecA, vecB);
    static_assert(proj8.x() == 1);
    static_assert(proj8.y() == 0);
    static_assert(proj8.z() == 0);

} // namespace



/** @brief Verify that projecting onto an orthogonal vector using @ref fgm::Vector3::project returns a zero vector. */
TYPED_TEST(Vector3Projection, OrthogonalVectorsReturnsZeroVector)
{
    const fgm::Vector3 actualProjection = this->_perpendicularVec.project(this->_ontoVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @brief Verify that projecting onto a vector parallel to x-axis using @ref fgm::Vector3::project
 *       returns a vector containing only an x-component.
 */
TEST(Vector3Projection, ProjectionOntoXAxisReturnsVectorWithOnlyXComponent)
{
    // Given an arbitrary vector
    const fgm::Vector3 a(10.0f, 20.0f, 30.0f);
    const fgm::Vector3 xAxis(1.0f, 0.0f, 0.0f);
    const fgm::Vector3 expectedProjection(10.0f, 0.0f, 0.0f);

    // When projected onto x-axis
    const fgm::Vector3 actualProjection = a.project(xAxis);

    // Then, the resultant vector only has x-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a vector parallel to y-axis using @ref fgm::Vector3::project
 *       returns a vector containing only a y-component.
 */
TEST(Vector3Projection, ProjectionOntoYAxisReturnsVectorWithOnlyYComponent)
{
    // Given an arbitrary vector
    const fgm::Vector3 a(10.0f, 20.0f, 30.0f);
    const fgm::Vector3 yAxis(0.0f, 1.0f, 0.0f);
    const fgm::Vector3 expectedProjection(0.0f, 20.0f, 0.0f);

    // When projected onto y-axis
    const fgm::Vector3 actualProjection = a.project(yAxis);

    // Then, the resultant vector only has y-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a vector parallel to z-axis using @ref fgm::Vector3::project
 *       returns a vector containing only a z-component.
 */
TEST(Vector3Projection, ProjectionOntoZAxisReturnsVectorWithOnlyZComponent)
{
    // Given an arbitrary vector
    const fgm::Vector3 a(10.0f, 20.0f, 30.0f);
    const fgm::Vector3 zAxis(0.0f, 0.0f, 1.0f);
    const fgm::Vector3 expectedProjection(0.0f, 0.0f, 30.0f);

    // When projected onto z-axis
    const fgm::Vector3 actualProjection = a.project(zAxis);

    // Then, the resultant vector only has z-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector using @ref fgm::Vector3::project
 *       returns a non-zero vector.
 */
TYPED_TEST(Vector3Projection, NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector3 actualProjection = this->_vec.project(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vector3::project
 *       returns a non-zero vector.
 */
TYPED_TEST(Vector3Projection, StaticWrapper_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector3 actualProjection = fgm::Vector3<TypeParam>::project(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vector3::projectNorm
 *       returns a non-zero vector.
 */
TEST(Vector3Projection, ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3 b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3 expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3 actualProjection = a.projectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector3::project returns a non-zero vector.
 */
TEST(Vector3Projection, ProjectionOntoVectorInOppositeDirectionReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector3 a(4.0f, 4.0f, 4.0f);
    const fgm::Vector3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const fgm::Vector3 expectedProjection(0.0f, 0.0f, 4.0f);

    // When projected
    const fgm::Vector3<float> actualProjection = a.project(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vector3::project returns a type-promoted vector.
 */
TEST(Vector3Projection, MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3 vec(7, 13, 29);
    const fgm::Vector3 onto(2.0, 4.0, 4.0);
    const fgm::Vector3 expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);

    // When projected onto another
    const fgm::Vector3 actualProjection = vec.project(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector3::projectNorm returns a non-zero vector.
 */
TEST(Vector3Projection, StaticWrapper_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3 b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3 expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3 actualProjection = fgm::Vector3<float>::projectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/** @brief Verify that projection using @ref fgm::Vector3::project always return floating-point vector. */
TYPED_TEST(Vector3Projection, Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector3 projection = this->_vec.project(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection using static variant of @ref fgm::Vector3::project
 *       always return floating-point vector.
 */
TYPED_TEST(Vector3Projection, StaticWrapper_Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector3 projection = fgm::Vector3<TypeParam>::project(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


#ifdef ENABLE_DEBUG_TESTS
/**
 * @brief Verify that projecting a vector onto zero vector triggers assert in debug mode.
 */
TYPED_TEST(Vector3Projection, ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const fgm::Vector3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.project(zeroVec)), "");
}


/**
 * @brief Verify that projecting a vector onto zero vector using static variant of @ref fgm::Vector3::project
 *        triggers assert in debug mode.
 */
TYPED_TEST(Vector3Projection, StaticWrapper_ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const fgm::Vector3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Vector3<TypeParam>::project(this->_vec, zeroVec)), "");
}

#endif



/**************************************
 *                                    *
 *        SAFE PROJECTION TESTS       *
 *                                    *
 **************************************/

/**
 * @brief Verify that projecting onto an orthogonal vector using @ref fgm::Vector3::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(Vector3Projection, SafeProject_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector3 actualProjection = this->_vec.safeProject(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vector3::safeProjectNorm
 *       returns a non-zero vector.
 */
TEST(Vector3Projection, SafeProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3 b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3 expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3 actualProjection = a.safeProject(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 * fgm::Vector3::safeProjectNorm returns a zero vector.
 */
TEST(Vector3Projection, SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const fgm::Vector3 a(1.0f, 2.0f, fgm::constants::NaN);
    const fgm::Vector3 b(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 * fgm::Vector3::safeProjectNorm returns a zero vector.
 */
TEST(Vector3Projection, SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3 b(1.0f, 1.0f, fgm::constants::NaN);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector3::safeProject returns a non-zero vector.
 */
TEST(Vector3Projection, SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector3 a(4.0f, 4.0f, 4.0f);
    const fgm::Vector3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const fgm::Vector3 expectedProjection(0.0f, 0.0f, 4.0f);

    // When projected
    const fgm::Vector3<float> actualProjection = a.safeProject(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vector3::safeProject returns a type-promoted vector.
 */
TEST(Vector3Projection, SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3 vec(7, 13, 29);
    const fgm::Vector3 onto(2.0, 4.0, 4.0);
    const fgm::Vector3 expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);

    // When projected onto another
    const fgm::Vector3 actualProjection = vec.safeProject(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a zero length vector using @ref fgm::Vector3::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(Vector3Projection, SafeProject_OntoZeroReturnsZeroVector)
{
    const fgm::Vector3 zeroVec = fgm::vec3d::zero<TypeParam>;

    const fgm::Vector3 actualProjection = this->_vec.safeProject(zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}

/**
 * @brief Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vector3::safeProject
 *       returns a non-zero vector.
 */
TYPED_TEST(Vector3Projection, StaticWrapper_SafeProject_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector3 actualProjection = fgm::Vector3<TypeParam>::safeProject(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector3::safeProjectNorm returns a non-zero vector.
 */
TEST(Vector3Projection, StaticWrapper_SafeProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3 b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3 expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3 actualProjection = fgm::Vector3<float>::safeProjectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}



/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector3::safeProjectNorm returns a zero vector.
 */
TEST(Vector3Projection, StaticWrapper_SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const fgm::Vector3 a(1.0f, 2.0f, fgm::constants::NaN);
    const fgm::Vector3 b(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3 actualProjection = fgm::Vector3<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector3::safeProjectNorm returns a zero vector.
 */
TEST(Vector3Projection, StaticWrapper_SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3 b(1.0f, 1.0f, fgm::constants::NaN);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3 actualProjection = fgm::Vector3<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}

/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref fgm::Vector3::safeProject returns a non-zero vector.
 */
TEST(Vector3Projection, StaticWrapper_SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector3 a(4.0f, 4.0f, 4.0f);
    const fgm::Vector3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const fgm::Vector3 expectedProjection(0.0f, 0.0f, 4.0f);

    // When projected
    const fgm::Vector3<float> actualProjection = fgm::Vector3<float>::safeProject(a, negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref fgm::Vector3::safeProject returns a type-promoted vector.
 */
TEST(Vector3Projection, StaticWrapper_SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3 vec(7, 13, 29);
    const fgm::Vector3 onto(2.0, 4.0, 4.0);
    const fgm::Vector3 expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);

    // When projected onto another
    const fgm::Vector3 actualProjection = fgm::Vector3<int>::safeProject(vec, onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a zero length vector using static variant of @ref fgm::Vector3::safeProject
 *       returns a type-promoted vector.
 */
TYPED_TEST(Vector3Projection, StaticWrapper_SafeProject_OntoZeroVectorReturnsZeroVector)
{
    const fgm::Vector3 zeroVec = fgm::vec3d::zero<TypeParam>;

    const fgm::Vector3 actualProjection = fgm::Vector3<TypeParam>::safeProject(this->_vec, zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/** @brief Verify that projection using @ref fgm::Vector3::safeProject always return floating-point vector. */
TYPED_TEST(Vector3Projection, SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector3 projection = this->_vec.safeProject(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection using static variant of @ref fgm::Vector3::safeProject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector3Projection, StaticWrapper_SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector3 projection = fgm::Vector3<TypeParam>::safeProject(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection of NaN vector using @ref fgm::Vector3::safeProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3ProjectionNaNTests, SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec3d::one<float>;

    EXPECT_VEC_ZERO(nanVec.safeProject(ontoVec));
}


/**
 * @brief Verify that projection onto NaN vector using @ref fgm::Vector3::safeProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3ProjectionNaNTests, SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec3d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeProject(ontoNaNVec));
}


/**
 * @brief Verify that projection of NaN vector using static variant of @ref fgm::Vector3::safeProject
 *       returns zero vector.
 */
TEST_P(Vector3ProjectionNaNTests, StaticWrapper_SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec3d::one<float>;

    EXPECT_VEC_ZERO(fgm::Vector3<float>::safeProject(nanVec, ontoVec));
}


/**
 * @brief Verify that projection onto NaN vector using static variant of @ref fgm::Vector3::safeProject
 *       returns zero vector.
 */
TEST_P(Vector3ProjectionNaNTests, StaticWrapper_SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec3d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector3<float>::safeProject(oneVec, ontoNaNVec));
}


/**************************************
 *                                    *
 *         TRY PROJECTION TESTS       *
 *                                    *
 **************************************/

/**
 * @brief Verify that projecting onto an orthogonal vector using @ref fgm::Vector3::tryProject
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector3Projection, TryProject_NonOrthogonalProjectionReturnsNonZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector3 actualProjection = this->_vec.tryProject(this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}
/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vector3::tryProject
 *       returns a non-zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3Projection, TryProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3 b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3 expectedProjection(1.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector3 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref fgm::Vector3::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3Projection, TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3 a(fgm::constants::NaN, 2.0f, 3.0f);
    const fgm::Vector3 b(1.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector3 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/**
 * @brief Verify that projecting a vector onto a NaN vector using @ref fgm::Vector3::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3Projection, TryProjectNorm_VectorProjectedOntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3 b(1.0f, fgm::constants::NaN, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector3 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector3::tryProject returns a non-zero vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3Projection, TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector3 a(4.0f, 4.0f, 4.0f);
    const fgm::Vector3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const fgm::Vector3 expectedProjection(0.0f, 0.0f, 4.0f);
    fgm::OperationStatus flag;

    // When projected
    const fgm::Vector3<float> actualProjection = a.tryProject(negativeZAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vector3::tryProject returns a type-promoted vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3Projection, TryProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3 vec(7, 13, 29);
    const fgm::Vector3 onto(2.0, 4.0, 4.0);
    const fgm::Vector3 expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);
    fgm::OperationStatus flag;

    // When projected onto another
    const fgm::Vector3 actualProjection = vec.tryProject(onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a zero length vector using @ref fgm::Vector3::tryProject
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector3Projection, TryProject_OntoZeroReturnsZeroVectorAndSetsCorrectFlag)
{
    const fgm::Vector3 zeroVec = fgm::vec3d::zero<TypeParam>;
    fgm::OperationStatus flag;


    const fgm::Vector3 actualProjection = this->_vec.tryProject(zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vector3::tryProject
 *       returns a non-zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector3Projection, StaticWrapper_TryProject_NonOrthogonalProjectionReturnsNonZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector3 actualProjection = fgm::Vector3<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector3::tryProject returns a non-zero vector and sets the flag to
 *       @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3Projection, StaticWrapper_TryProject_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3 b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3 expectedProjection(1.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector3 actualProjection = fgm::Vector3<float>::tryProject(a, b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}



/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of @ref
 * fgm::Vector3::tryProjectNorm returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3Projection, StaticWrapper_TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const fgm::Vector3 a(fgm::constants::NaN, 2.0f, 3.0f);
    const fgm::Vector3 b(1.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const fgm::Vector3 actualProjection = fgm::Vector3<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/**
 * @brief Verify that projecting a vector onto a NaN vector using static variant of @ref fgm::Vector3::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3Projection, StaticWrapper_TryProjectNorm_VectorProjectedOntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const fgm::Vector3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3 b(1.0f, fgm::constants::NaN, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const fgm::Vector3 actualProjection = fgm::Vector3<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}



/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref fgm::Vector3::tryProject returns a non-zero vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3Projection,
     StaticWrapper_TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector3 a(4.0f, 4.0f, 4.0f);
    const fgm::Vector3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const fgm::Vector3 expectedProjection(0.0f, 0.0f, 4.0f);
    fgm::OperationStatus flag;

    // When projected
    const fgm::Vector3<float> actualProjection = fgm::Vector3<float>::tryProject(a, negativeZAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref fgm::Vector3::tryProject returns a type-promoted vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3Projection, StaticWrapper_TryProject_MixedTypeProjectionPromotesTypeAndSetsCorrectFlag)
{
    // Given two arbitrary vectors
    const fgm::Vector3 vec(7, 13, 29);
    const fgm::Vector3 onto(2.0, 4.0, 4.0);
    const fgm::Vector3 expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);
    fgm::OperationStatus flag;

    // When projected onto another
    const fgm::Vector3 actualProjection = fgm::Vector3<int>::tryProject(vec, onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a zero length vector using static variant of @ref fgm::Vector3::tryProject
 *       returns a type-promoted vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector3Projection, StaticWrapper_TryProject_OntoZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const fgm::Vector3 zeroVec = fgm::vec3d::zero<TypeParam>;
    fgm::OperationStatus flag;

    const fgm::Vector3 actualProjection = fgm::Vector3<TypeParam>::tryProject(this->_vec, zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/** @brief Verify that projection using @ref fgm::Vector3::tryProject always return floating-point vector. */
TYPED_TEST(Vector3Projection, TryProject_AlwaysReturnFloatingPointVectorAndSetsCorrectFlag)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Vector3 projection = this->_vec.tryProject(this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection using static variant of @ref fgm::Vector3::tryProject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector3Projection, StaticWrapper_TryProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Vector3 projection =
        fgm::Vector3<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection of NaN vector using @ref fgm::Vector3::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3ProjectionNaNTests, TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec3d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryProject(ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projection onto NaN vector using @ref fgm::Vector3::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3ProjectionNaNTests, TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec3d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryProject(ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projection of NaN vector using static variant of @ref fgm::Vector3::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3ProjectionNaNTests, StaticWrapper_TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec3d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vector3<float>::tryProject(nanVec, ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projection onto NaN vector using static variant of @ref fgm::Vector3::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3ProjectionNaNTests, StaticWrapper_TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec3d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vector3<float>::tryProject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
