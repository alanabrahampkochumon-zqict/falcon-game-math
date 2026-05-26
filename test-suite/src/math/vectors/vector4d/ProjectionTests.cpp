/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref fgm::Vector4D projection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"



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
        _vec                = { T(5), T(6), T(7), T(8) };
        _perpendicularVec   = { T(10), T(0), T(14), T(16) };
        _ontoVec            = { T(0), T(2), T(0), T(0) };
        _expectedProjection = { T(0), T(6), T(0), T(0) };
    }
};
/** @brief Test fixture for @ref Vector4D projection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DProjection, SupportedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Vector4D projection with NaN vectors. */
class Vector4DProjectionNaNTests: public ::testing::TestWithParam<fgm::Vector4D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vector4DProjectionTestSuite, Vector4DProjectionNaNTests,
                         ::testing::Values(fgm::Vector4D<float>(fgm::constants::NaN, 1.0f, 1.0f, 1.0f),
                                           fgm::Vector4D<float>(1.0f, fgm::constants::NaN, 1.0f, 1.0f),
                                           fgm::Vector4D<float>(1.0f, 1.0f, fgm::constants::NaN, 1.0f),
                                           fgm::Vector4D<float>(1.0f, 1.0f, 1.0f, fgm::constants::NaN),
                                           fgm::Vector4D<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN, fgm ::constants::NaN)));



/**
 * @addtogroup T_FGM_Vec4_Proj
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
    constexpr fgm::Vector4D vecA(1, 2, 3, 4);
    constexpr fgm::Vector4D vecB(1, 0, 0, 0);
    constexpr auto proj1 = vecA.project(vecB);
    static_assert(proj1.x() == 1);
    static_assert(proj1.y() == 0);
    static_assert(proj1.z() == 0);
    static_assert(proj1.w() == 0);

    constexpr auto proj2 = vecA.projectNorm(vecB);
    static_assert(proj2.x() == 1);
    static_assert(proj2.y() == 0);
    static_assert(proj2.z() == 0);
    static_assert(proj2.w() == 0);

    constexpr auto proj3 = fgm::Vector4D<int>::project(vecA, vecB);
    static_assert(proj3.x() == 1);
    static_assert(proj3.y() == 0);
    static_assert(proj3.z() == 0);
    static_assert(proj3.w() == 0);

    constexpr auto proj4 = fgm::Vector4D<int>::projectNorm(vecA, vecB);
    static_assert(proj4.x() == 1);
    static_assert(proj4.y() == 0);
    static_assert(proj4.z() == 0);
    static_assert(proj4.w() == 0);

    constexpr auto proj5 = vecA.safeProject(vecB);
    static_assert(proj5.x() == 1);
    static_assert(proj5.y() == 0);
    static_assert(proj5.z() == 0);
    static_assert(proj5.w() == 0);

    constexpr auto proj6 = vecA.safeProjectNorm(vecB);
    static_assert(proj6.x() == 1);
    static_assert(proj6.y() == 0);
    static_assert(proj6.z() == 0);
    static_assert(proj6.w() == 0);

    constexpr auto proj7 = fgm::Vector4D<int>::safeProject(vecA, vecB);
    static_assert(proj7.x() == 1);
    static_assert(proj7.y() == 0);
    static_assert(proj7.z() == 0);
    static_assert(proj7.w() == 0);

    constexpr auto proj8 = fgm::Vector4D<int>::safeProjectNorm(vecA, vecB);
    static_assert(proj8.x() == 1);
    static_assert(proj8.y() == 0);
    static_assert(proj8.z() == 0);
    static_assert(proj8.w() == 0);

} // namespace


/** @brief Verify that projecting onto an orthogonal vector using @ref fgm::Vector4D::project returns a zero vector. */
TYPED_TEST(Vector4DProjection, OrthogonalVectorsReturnsZeroVector)
{
    const fgm::Vector4D actualProjection = this->_perpendicularVec.project(this->_ontoVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @brief Verify that projecting onto a vector parallel to x-axis using @ref fgm::Vector4D::project
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
 * @brief Verify that projecting onto a vector parallel to y-axis using @ref fgm::Vector4D::project
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
 * @brief Verify that projecting onto a vector parallel to z-axis using @ref fgm::Vector4D::project
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
 * @brief Verify that projecting onto a vector parallel to w-axis using @ref fgm::Vector4D::project
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
 * @brief Verify that projecting onto a non-orthogonal vector using @ref fgm::Vector4D::project
 *       returns a non-zero vector.
 */
TYPED_TEST(Vector4DProjection, NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualProjection = this->_vec.project(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vector4D::project
 *       returns a non-zero vector.
 */
TYPED_TEST(Vector4DProjection, StaticWrapper_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualProjection = fgm::Vector4D<TypeParam>::project(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vector4D::projectNorm
 *       returns a non-zero vector.
 */
TEST(Vector4DProjection, ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const fgm::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector4D actualProjection = a.projectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector4D::project returns a non-zero vector.
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


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vector4D::project returns a type-promoted vector.
 */
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


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector4D::projectNorm returns a non-zero vector.
 */
TEST(Vector4DProjection, StaticWrapper_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const fgm::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector4D actualProjection = fgm::Vector4D<float>::projectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}



/** @brief Verify that projection using @ref fgm::Vector4D::project always return floating-point vector. */
TYPED_TEST(Vector4DProjection, Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector4D projection = this->_vec.project(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection using static variant of @ref fgm::Vector4D::project
 *       always return floating-point vector.
 */
TYPED_TEST(Vector4DProjection, StaticWrapper_Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector4D projection = fgm::Vector4D<TypeParam>::project(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**************************************
 *                                    *
 *        SAFE PROJECTION TESTS       *
 *                                    *
 **************************************/

/**
 * @brief Verify that projecting onto an orthogonal vector using @ref fgm::Vector4D::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(Vector4DProjection, SafeProject_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualProjection = this->_vec.safeProject(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vector4D::safeProjectNorm
 *       returns a non-zero vector.
 */
TEST(Vector4DProjection, SafeProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const fgm::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector4D actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 * fgm::Vector4D::safeProjectNorm returns a zero vector.
 */
TEST(Vector4DProjection, SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const fgm::Vector4D a(1.0f, fgm::constants::NaN, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector4D actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}

/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 * fgm::Vector4D::safeProjectNorm returns a zero vector.
 */
TEST(Vector4DProjection, SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, fgm::constants::NaN, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector4D actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector4D::safeProject returns a non-zero vector.
 */
TEST(Vector4DProjection, SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    const fgm::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    const fgm::Vector4D expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);

    // When projected
    const fgm::Vector4D<float> actualProjection = a.safeProject(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vector4D::safeProject returns a type-promoted vector.
 */
TEST(Vector4DProjection, SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector4D vec(7, 13, 29, 41);
    const fgm::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    const fgm::Vector4D expectedProjection(13.2, 26.4, 26.4, 13.2);

    // When projected onto another
    const fgm::Vector4D actualProjection = vec.safeProject(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a zero length vector using @ref fgm::Vector4D::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(Vector4DProjection, SafeProject_OntoZeroReturnsZeroVector)
{
    const fgm::Vector4D zeroVec = fgm::vec4d::zero<TypeParam>;

    const fgm::Vector4D actualProjection = this->_vec.safeProject(zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}

/**
 * @brief Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vector4D::safeProject
 *       returns a non-zero vector.
 */
TYPED_TEST(Vector4DProjection, StaticWrapper_SafeProject_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualProjection = fgm::Vector4D<TypeParam>::safeProject(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector4D::safeProjectNorm returns a non-zero vector.
 */
TEST(Vector4DProjection, StaticWrapper_SafeProject_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const fgm::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector4D actualProjection = fgm::Vector4D<float>::safeProjectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector4D::safeProjectNorm returns a zero vector.
 */
TEST(Vector4DProjection, StaticWrapper_SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const fgm::Vector4D a(1.0f, fgm::constants::NaN, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector4D actualProjection = fgm::Vector4D<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @brief Verify that projecting onto a NaN vector using static variant of
 *       @ref fgm::Vector4D::safeProjectNorm returns a zero vector.
 */
TEST(Vector4DProjection, StaticWrapper_SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, fgm::constants::NaN, 0.0f, 0.0f);

    // When the vector is from a NaN vector
    const fgm::Vector4D actualProjection = fgm::Vector4D<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref fgm::Vector4D::safeProject returns a non-zero vector.
 */
TEST(Vector4DProjection, StaticWrapper_SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    const fgm::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    const fgm::Vector4D expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);

    // When projected
    const fgm::Vector4D<float> actualProjection = fgm::Vector4D<float>::safeProject(a, negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref fgm::Vector4D::safeProject returns a type-promoted vector.
 */
TEST(Vector4DProjection, StaticWrapper_SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector4D vec(7, 13, 29, 41);
    const fgm::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    const fgm::Vector4D expectedProjection(13.2, 26.4, 26.4, 13.2);

    // When projected onto another
    const fgm::Vector4D actualProjection = fgm::Vector4D<int>::safeProject(vec, onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a zero length vector using static variant of @ref fgm::Vector4D::safeProject
 *       returns a type-promoted vector.
 */
TYPED_TEST(Vector4DProjection, StaticWrapper_SafeProject_OntoZeroVectorReturnsZeroVector)
{
    const fgm::Vector4D zeroVec = fgm::vec4d::zero<TypeParam>;

    const fgm::Vector4D actualProjection = fgm::Vector4D<TypeParam>::safeProject(this->_vec, zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/** @brief Verify that projection using @ref fgm::Vector4D::safeProject always return floating-point vector. */
TYPED_TEST(Vector4DProjection, SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector4D projection = this->_vec.safeProject(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection using static variant of @ref fgm::Vector4D::safeProject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector4DProjection, StaticWrapper_SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector4D projection = fgm::Vector4D<TypeParam>::safeProject(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection of NaN vector using @ref fgm::Vector4D::safeProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector4DProjectionNaNTests, SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec4d::one<float>;

    EXPECT_VEC_ZERO(nanVec.safeProject(ontoVec));
}


/**
 * @brief Verify that projection onto NaN vector using @ref fgm::Vector4D::safeProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector4DProjectionNaNTests, SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec4d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeProject(ontoNaNVec));
}


/**
 * @brief Verify that projection of NaN vector using static variant of @ref fgm::Vector4D::safeProject
 *       returns zero vector.
 */
TEST_P(Vector4DProjectionNaNTests, StaticWrapper_SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec4d::one<float>;

    EXPECT_VEC_ZERO(fgm::Vector4D<float>::safeProject(nanVec, ontoVec));
}


/**
 * @brief Verify that projection onto NaN vector using static variant of @ref fgm::Vector4D::safeProject
 *       returns zero vector.
 */
TEST_P(Vector4DProjectionNaNTests, StaticWrapper_SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec4d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector4D<float>::safeProject(oneVec, ontoNaNVec));
}


/**************************************
 *                                    *
 *         TRY PROJECTION TESTS       *
 *                                    *
 **************************************/

/**
 * @brief Verify that projecting onto an orthogonal vector using @ref fgm::Vector4D::tryProject
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector4DProjection, TryProject_NonOrthogonalProjectionReturnsNonZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector4D actualProjection = this->_vec.tryProject(this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref fgm::Vector4D::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector4DProjection, TryProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const fgm::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector4D actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref fgm::Vector4D::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector4DProjection, TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector4D a(fgm::constants::NaN, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector4D actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projecting a vector onto a NaN vector using @ref fgm::Vector4D::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector4DProjection, TryProjectNorm_VectorProjectedOntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, fgm::constants::NaN, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector4D actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector4D::tryProject returns a non-zero vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector4DProjection, TryProjectNorm_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    const fgm::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    const fgm::Vector4D expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);
    fgm::OperationStatus flag;

    // When projected
    const fgm::Vector4D<float> actualProjection = a.tryProject(negativeZAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vector4D::tryProject returns a type-promoted vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector4DProjection, TryProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector4D vec(7, 13, 29, 41);
    const fgm::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    const fgm::Vector4D expectedProjection(13.2, 26.4, 26.4, 13.2);
    fgm::OperationStatus flag;

    // When projected onto another
    const fgm::Vector4D actualProjection = vec.tryProject(onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a zero length vector using @ref fgm::Vector4D::tryProject
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector4DProjection, TryProject_OntoZeroReturnsZeroVectorAndSetsCorrectFlag)
{
    const fgm::Vector4D zeroVec = fgm::vec4d::zero<TypeParam>;
    fgm::OperationStatus flag;


    const fgm::Vector4D actualProjection = this->_vec.tryProject(zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vector4D::tryProject
 *       returns a non-zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector4DProjection, StaticWrapper_TryProject_NonOrthogonalProjectionReturnsNonZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector4D actualProjection = fgm::Vector4D<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector4D::tryProject with the @p ontoNormalized flag enabled returns a non-zero vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector4DProjection,
     StaticWrapper_TryProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    const fgm::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector4D actualProjection = fgm::Vector4D<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector4D::tryProjectNorm returns a zero vector and sets the flag to
 *       @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector4DProjection, StaticWrapper_TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const fgm::Vector4D a(fgm::constants::NaN, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const fgm::Vector4D actualProjection = fgm::Vector4D<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/**
 * @brief Verify that projecting a vector onto a NaN vector using static variant of @ref fgm::Vector4D::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector4DProjection, StaticWrapper_TryProjectNorm_VectorProjectedOntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    const fgm::Vector4D b(1.0f, fgm::constants::NaN, 0.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const fgm::Vector4D actualProjection = fgm::Vector4D<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}



/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref fgm::Vector4D::tryProject returns a non-zero vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector4DProjection,
     StaticWrapper_TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    const fgm::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    const fgm::Vector4D expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);
    fgm::OperationStatus flag;

    // When projected
    const fgm::Vector4D<float> actualProjection = fgm::Vector4D<float>::tryProject(a, negativeZAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref fgm::Vector4D::tryProject returns a type-promoted vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector4DProjection, StaticWrapper_TryProject_MixedTypeProjectionPromotesTypeAndSetsCorrectFlag)
{
    // Given two arbitrary vectors
    const fgm::Vector4D vec(7, 13, 29, 41);
    const fgm::Vector4D onto(2.0, 4.0, 4.0, 2.0);
    const fgm::Vector4D expectedProjection(13.2, 26.4, 26.4, 13.2);
    fgm::OperationStatus flag;

    // When projected onto another
    const fgm::Vector4D actualProjection = fgm::Vector4D<int>::tryProject(vec, onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a zero length vector using static variant of @ref fgm::Vector4D::tryProject
 *       returns a type-promoted vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector4DProjection, StaticWrapper_TryProject_OntoZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const fgm::Vector4D zeroVec = fgm::vec4d::zero<TypeParam>;
    fgm::OperationStatus flag;

    const fgm::Vector4D actualProjection = fgm::Vector4D<TypeParam>::tryProject(this->_vec, zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/** @brief Verify that projection using @ref fgm::Vector4D::tryProject always return floating-point vector. */
TYPED_TEST(Vector4DProjection, TryProject_AlwaysReturnFloatingPointVectorAndSetsCorrectFlag)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Vector4D projection = this->_vec.tryProject(this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection using static variant of @ref fgm::Vector4D::tryProject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector4DProjection, StaticWrapper_TryProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Vector4D projection =
        fgm::Vector4D<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection of NaN vector using @ref fgm::Vector4D::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector4DProjectionNaNTests, TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec4d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryProject(ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projection onto NaN vector using @ref fgm::Vector4D::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector4DProjectionNaNTests, TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec4d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryProject(ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projection of NaN vector using static variant of @ref fgm::Vector4D::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector4DProjectionNaNTests, StaticWrapper_TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec4d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vector4D<float>::tryProject(nanVec, ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projection onto NaN vector using static variant of @ref fgm::Vector4D::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector4DProjectionNaNTests, StaticWrapper_TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec4d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vector4D<float>::tryProject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
