/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vector3D projection logic.
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
class Vector3DProjection: public ::testing::Test
{
protected:
    fgm::Vector3D<T> _vec;
    fgm::Vector3D<T> _perpendicularVec;
    fgm::Vector3D<T> _ontoVec;
    fgm::Vector3D<T> _expectedProjection;

    void SetUp() override
    {
        _vec                = { T(4), T(9), T(0) };
        _perpendicularVec   = { T(0), T(0), T(11) };
        _ontoVec            = { T(0), T(2), T(0) };
        _expectedProjection = { T(0), T(9), T(0) };
    }
};
/** @brief Test fixture for @ref Vector3D projection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector3DProjection, SupportedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Vector3D projection with NaN vectors. */
class Vector3DProjectionNaNTests: public ::testing::TestWithParam<fgm::Vector3D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vector3DProjectionTestSuite, Vector3DProjectionNaNTests,
                         ::testing::Values(fgm::Vector3D<float>(fgm::constants::NaN, 1.0f, 1.0f),
                                           fgm::Vector3D<float>(1.0f, fgm::constants::NaN, 1.0f),
                                           fgm::Vector3D<float>(1.0f, 1.0f, fgm::constants::NaN),
                                           fgm::Vector3D<float>(fgm ::constants::NaN, fgm::constants::NaN,
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
    constexpr fgm::Vector3D vecA(1, 2, 3);
    constexpr fgm::Vector3D vecB(1, 0, 0);
    constexpr auto proj1 = vecA.project(vecB);
    static_assert(proj1.x() == 1);
    static_assert(proj1.y() == 0);
    static_assert(proj1.z() == 0);

    constexpr auto proj2 = vecA.projectNorm(vecB);
    static_assert(proj2.x() == 1);
    static_assert(proj2.y() == 0);
    static_assert(proj2.z() == 0);

    constexpr auto proj3 = fgm::Vector3D<int>::project(vecA, vecB);
    static_assert(proj3.x() == 1);
    static_assert(proj3.y() == 0);
    static_assert(proj3.z() == 0);

    constexpr auto proj4 = fgm::Vector3D<int>::projectNorm(vecA, vecB);
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

    constexpr auto proj7 = fgm::Vector3D<int>::safeProject(vecA, vecB);
    static_assert(proj7.x() == 1);
    static_assert(proj7.y() == 0);
    static_assert(proj7.z() == 0);

    constexpr auto proj8 = fgm::Vector3D<int>::safeProjectNorm(vecA, vecB);
    static_assert(proj8.x() == 1);
    static_assert(proj8.y() == 0);
    static_assert(proj8.z() == 0);

} // namespace



/** @brief Verify that projecting onto an orthogonal vector using @ref fgm::Vector3D::project returns a zero vector. */
TYPED_TEST(Vector3DProjection, OrthogonalVectorsReturnsZeroVector)
{
    const fgm::Vector3D actualProjection = this->_perpendicularVec.project(this->_ontoVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @brief Verify that projecting onto a vector parallel to x-axis using @ref fgm::Vector3D::project
 *       returns a vector containing only an x-component.
 */
TEST(Vector3DProjection, ProjectionOntoXAxisReturnsVectorWithOnlyXComponent)
{
    // Given an arbitrary vector
    const fgm::Vector3D a(10.0f, 20.0f, 30.0f);
    const fgm::Vector3D xAxis(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedProjection(10.0f, 0.0f, 0.0f);

    // When projected onto x-axis
    const fgm::Vector3D actualProjection = a.project(xAxis);

    // Then, the resultant vector only has x-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a vector parallel to y-axis using @ref fgm::Vector3D::project
 *       returns a vector containing only a y-component.
 */
TEST(Vector3DProjection, ProjectionOntoYAxisReturnsVectorWithOnlyYComponent)
{
    // Given an arbitrary vector
    const fgm::Vector3D a(10.0f, 20.0f, 30.0f);
    const fgm::Vector3D yAxis(0.0f, 1.0f, 0.0f);
    const fgm::Vector3D expectedProjection(0.0f, 20.0f, 0.0f);

    // When projected onto y-axis
    const fgm::Vector3D actualProjection = a.project(yAxis);

    // Then, the resultant vector only has y-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a vector parallel to z-axis using @ref fgm::Vector3D::project
 *       returns a vector containing only a z-component.
 */
TEST(Vector3DProjection, ProjectionOntoZAxisReturnsVectorWithOnlyZComponent)
{
    // Given an arbitrary vector
    const fgm::Vector3D a(10.0f, 20.0f, 30.0f);
    const fgm::Vector3D zAxis(0.0f, 0.0f, 1.0f);
    const fgm::Vector3D expectedProjection(0.0f, 0.0f, 30.0f);

    // When projected onto z-axis
    const fgm::Vector3D actualProjection = a.project(zAxis);

    // Then, the resultant vector only has z-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector using @ref fgm::Vector3D::project
 *       returns a non-zero vector.
 */
TYPED_TEST(Vector3DProjection, NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector3D actualProjection = this->_vec.project(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vector3D::project
 *       returns a non-zero vector.
 */
TYPED_TEST(Vector3DProjection, StaticWrapper_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector3D actualProjection = fgm::Vector3D<TypeParam>::project(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vector3D::projectNorm
 *       returns a non-zero vector.
 */
TEST(Vector3DProjection, ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3D actualProjection = a.projectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector3D::project returns a non-zero vector.
 */
TEST(Vector3DProjection, ProjectionOntoVectorInOppositeDirectionReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector3D a(4.0f, 4.0f, 4.0f);
    const fgm::Vector3D negativeZAxis(0.0f, 0.0f, -1.0f);
    const fgm::Vector3D expectedProjection(0.0f, 0.0f, 4.0f);

    // When projected
    const fgm::Vector3D<float> actualProjection = a.project(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vector3D::project returns a type-promoted vector.
 */
TEST(Vector3DProjection, MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3D vec(7, 13, 29);
    const fgm::Vector3D onto(2.0, 4.0, 4.0);
    const fgm::Vector3D expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);

    // When projected onto another
    const fgm::Vector3D actualProjection = vec.project(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector3D::projectNorm returns a non-zero vector.
 */
TEST(Vector3DProjection, StaticWrapper_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3D actualProjection = fgm::Vector3D<float>::projectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/** @brief Verify that projection using @ref fgm::Vector3D::project always return floating-point vector. */
TYPED_TEST(Vector3DProjection, Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector3D projection = this->_vec.project(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection using static variant of @ref fgm::Vector3D::project
 *       always return floating-point vector.
 */
TYPED_TEST(Vector3DProjection, StaticWrapper_Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector3D projection = fgm::Vector3D<TypeParam>::project(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**************************************
 *                                    *
 *        SAFE PROJECTION TESTS       *
 *                                    *
 **************************************/

/**
 * @brief Verify that projecting onto an orthogonal vector using @ref fgm::Vector3D::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(Vector3DProjection, SafeProject_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector3D actualProjection = this->_vec.safeProject(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vector3D::safeProjectNorm
 *       returns a non-zero vector.
 */
TEST(Vector3DProjection, SafeProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3D actualProjection = a.safeProject(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 * fgm::Vector3D::safeProjectNorm returns a zero vector.
 */
TEST(Vector3DProjection, SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, fgm::constants::NaN);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3D actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 * fgm::Vector3D::safeProjectNorm returns a zero vector.
 */
TEST(Vector3DProjection, SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 1.0f, fgm::constants::NaN);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3D actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector3D::safeProject returns a non-zero vector.
 */
TEST(Vector3DProjection, SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector3D a(4.0f, 4.0f, 4.0f);
    const fgm::Vector3D negativeZAxis(0.0f, 0.0f, -1.0f);
    const fgm::Vector3D expectedProjection(0.0f, 0.0f, 4.0f);

    // When projected
    const fgm::Vector3D<float> actualProjection = a.safeProject(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vector3D::safeProject returns a type-promoted vector.
 */
TEST(Vector3DProjection, SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3D vec(7, 13, 29);
    const fgm::Vector3D onto(2.0, 4.0, 4.0);
    const fgm::Vector3D expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);

    // When projected onto another
    const fgm::Vector3D actualProjection = vec.safeProject(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a zero length vector using @ref fgm::Vector3D::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(Vector3DProjection, SafeProject_OntoZeroReturnsZeroVector)
{
    const fgm::Vector3D zeroVec = fgm::vec3d::zero<TypeParam>;

    const fgm::Vector3D actualProjection = this->_vec.safeProject(zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}

/**
 * @brief Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vector3D::safeProject
 *       returns a non-zero vector.
 */
TYPED_TEST(Vector3DProjection, StaticWrapper_SafeProject_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector3D actualProjection = fgm::Vector3D<TypeParam>::safeProject(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector3D::safeProjectNorm returns a non-zero vector.
 */
TEST(Vector3DProjection, StaticWrapper_SafeProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3D actualProjection = fgm::Vector3D<float>::safeProjectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}



/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector3D::safeProjectNorm returns a zero vector.
 */
TEST(Vector3DProjection, StaticWrapper_SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, fgm::constants::NaN);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3D actualProjection = fgm::Vector3D<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector3D::safeProjectNorm returns a zero vector.
 */
TEST(Vector3DProjection, StaticWrapper_SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 1.0f, fgm::constants::NaN);

    // When the vector is projected onto the normalized vector
    const fgm::Vector3D actualProjection = fgm::Vector3D<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}

/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref fgm::Vector3D::safeProject returns a non-zero vector.
 */
TEST(Vector3DProjection, StaticWrapper_SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector3D a(4.0f, 4.0f, 4.0f);
    const fgm::Vector3D negativeZAxis(0.0f, 0.0f, -1.0f);
    const fgm::Vector3D expectedProjection(0.0f, 0.0f, 4.0f);

    // When projected
    const fgm::Vector3D<float> actualProjection = fgm::Vector3D<float>::safeProject(a, negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref fgm::Vector3D::safeProject returns a type-promoted vector.
 */
TEST(Vector3DProjection, StaticWrapper_SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3D vec(7, 13, 29);
    const fgm::Vector3D onto(2.0, 4.0, 4.0);
    const fgm::Vector3D expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);

    // When projected onto another
    const fgm::Vector3D actualProjection = fgm::Vector3D<int>::safeProject(vec, onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a zero length vector using static variant of @ref fgm::Vector3D::safeProject
 *       returns a type-promoted vector.
 */
TYPED_TEST(Vector3DProjection, StaticWrapper_SafeProject_OntoZeroVectorReturnsZeroVector)
{
    const fgm::Vector3D zeroVec = fgm::vec3d::zero<TypeParam>;

    const fgm::Vector3D actualProjection = fgm::Vector3D<TypeParam>::safeProject(this->_vec, zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/** @brief Verify that projection using @ref fgm::Vector3D::safeProject always return floating-point vector. */
TYPED_TEST(Vector3DProjection, SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector3D projection = this->_vec.safeProject(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection using static variant of @ref fgm::Vector3D::safeProject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector3DProjection, StaticWrapper_SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector3D projection = fgm::Vector3D<TypeParam>::safeProject(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection of NaN vector using @ref fgm::Vector3D::safeProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3DProjectionNaNTests, SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec3d::one<float>;

    EXPECT_VEC_ZERO(nanVec.safeProject(ontoVec));
}


/**
 * @brief Verify that projection onto NaN vector using @ref fgm::Vector3D::safeProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3DProjectionNaNTests, SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec3d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeProject(ontoNaNVec));
}


/**
 * @brief Verify that projection of NaN vector using static variant of @ref fgm::Vector3D::safeProject
 *       returns zero vector.
 */
TEST_P(Vector3DProjectionNaNTests, StaticWrapper_SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec3d::one<float>;

    EXPECT_VEC_ZERO(fgm::Vector3D<float>::safeProject(nanVec, ontoVec));
}


/**
 * @brief Verify that projection onto NaN vector using static variant of @ref fgm::Vector3D::safeProject
 *       returns zero vector.
 */
TEST_P(Vector3DProjectionNaNTests, StaticWrapper_SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec3d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector3D<float>::safeProject(oneVec, ontoNaNVec));
}


/**************************************
 *                                    *
 *         TRY PROJECTION TESTS       *
 *                                    *
 **************************************/

/**
 * @brief Verify that projecting onto an orthogonal vector using @ref fgm::Vector3D::tryProject
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector3DProjection, TryProject_NonOrthogonalProjectionReturnsNonZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector3D actualProjection = this->_vec.tryProject(this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}
/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vector3D::tryProject
 *       returns a non-zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3DProjection, TryProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedProjection(1.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector3D actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref fgm::Vector3D::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3DProjection, TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(fgm::constants::NaN, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector3D actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/**
 * @brief Verify that projecting a vector onto a NaN vector using @ref fgm::Vector3D::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3DProjection, TryProjectNorm_VectorProjectedOntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, fgm::constants::NaN, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector3D actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector3D::tryProject returns a non-zero vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3DProjection, TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector3D a(4.0f, 4.0f, 4.0f);
    const fgm::Vector3D negativeZAxis(0.0f, 0.0f, -1.0f);
    const fgm::Vector3D expectedProjection(0.0f, 0.0f, 4.0f);
    fgm::OperationStatus flag;

    // When projected
    const fgm::Vector3D<float> actualProjection = a.tryProject(negativeZAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vector3D::tryProject returns a type-promoted vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3DProjection, TryProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3D vec(7, 13, 29);
    const fgm::Vector3D onto(2.0, 4.0, 4.0);
    const fgm::Vector3D expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);
    fgm::OperationStatus flag;

    // When projected onto another
    const fgm::Vector3D actualProjection = vec.tryProject(onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a zero length vector using @ref fgm::Vector3D::tryProject
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector3DProjection, TryProject_OntoZeroReturnsZeroVectorAndSetsCorrectFlag)
{
    const fgm::Vector3D zeroVec = fgm::vec3d::zero<TypeParam>;
    fgm::OperationStatus flag;


    const fgm::Vector3D actualProjection = this->_vec.tryProject(zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vector3D::tryProject
 *       returns a non-zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector3DProjection, StaticWrapper_TryProject_NonOrthogonalProjectionReturnsNonZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector3D actualProjection = fgm::Vector3D<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector3D::tryProject returns a non-zero vector and sets the flag to
 *       @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3DProjection, StaticWrapper_TryProject_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedProjection(1.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector3D actualProjection = fgm::Vector3D<float>::tryProject(a, b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}



/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of @ref
 * fgm::Vector3D::tryProjectNorm returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3DProjection, StaticWrapper_TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const fgm::Vector3D a(fgm::constants::NaN, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const fgm::Vector3D actualProjection = fgm::Vector3D<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/**
 * @brief Verify that projecting a vector onto a NaN vector using static variant of @ref fgm::Vector3D::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3DProjection, StaticWrapper_TryProjectNorm_VectorProjectedOntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, fgm::constants::NaN, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const fgm::Vector3D actualProjection = fgm::Vector3D<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}



/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref fgm::Vector3D::tryProject returns a non-zero vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3DProjection,
     StaticWrapper_TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector3D a(4.0f, 4.0f, 4.0f);
    const fgm::Vector3D negativeZAxis(0.0f, 0.0f, -1.0f);
    const fgm::Vector3D expectedProjection(0.0f, 0.0f, 4.0f);
    fgm::OperationStatus flag;

    // When projected
    const fgm::Vector3D<float> actualProjection = fgm::Vector3D<float>::tryProject(a, negativeZAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref fgm::Vector3D::tryProject returns a type-promoted vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3DProjection, StaticWrapper_TryProject_MixedTypeProjectionPromotesTypeAndSetsCorrectFlag)
{
    // Given two arbitrary vectors
    const fgm::Vector3D vec(7, 13, 29);
    const fgm::Vector3D onto(2.0, 4.0, 4.0);
    const fgm::Vector3D expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);
    fgm::OperationStatus flag;

    // When projected onto another
    const fgm::Vector3D actualProjection = fgm::Vector3D<int>::tryProject(vec, onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a zero length vector using static variant of @ref fgm::Vector3D::tryProject
 *       returns a type-promoted vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector3DProjection, StaticWrapper_TryProject_OntoZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const fgm::Vector3D zeroVec = fgm::vec3d::zero<TypeParam>;
    fgm::OperationStatus flag;

    const fgm::Vector3D actualProjection = fgm::Vector3D<TypeParam>::tryProject(this->_vec, zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/** @brief Verify that projection using @ref fgm::Vector3D::tryProject always return floating-point vector. */
TYPED_TEST(Vector3DProjection, TryProject_AlwaysReturnFloatingPointVectorAndSetsCorrectFlag)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Vector3D projection = this->_vec.tryProject(this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection using static variant of @ref fgm::Vector3D::tryProject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector3DProjection, StaticWrapper_TryProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Vector3D projection =
        fgm::Vector3D<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection of NaN vector using @ref fgm::Vector3D::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3DProjectionNaNTests, TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec3d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryProject(ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projection onto NaN vector using @ref fgm::Vector3D::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3DProjectionNaNTests, TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec3d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryProject(ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projection of NaN vector using static variant of @ref fgm::Vector3D::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3DProjectionNaNTests, StaticWrapper_TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec3d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vector3D<float>::tryProject(nanVec, ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projection onto NaN vector using static variant of @ref fgm::Vector3D::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3DProjectionNaNTests, StaticWrapper_TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec3d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vector3D<float>::tryProject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
