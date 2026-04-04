/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verifies @ref fgm::Vector2D projection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector2DProjection: public ::testing::Test
{
protected:
    fgm::Vector2D<T> _vec;
    fgm::Vector2D<T> _perpendicularVec;
    fgm::Vector2D<T> _ontoVec;
    fgm::Vector2D<T> _expectedProjection;

    void SetUp() override
    {
        _vec = { T(4), T(0) };
        _perpendicularVec = { T(0), T(11) };
        _ontoVec = { T(2), T(0) };
        _expectedProjection = { T(4), T(0) };
    }
};
/** @brief Test fixture for @ref Vector2D projection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector2DProjection, SupportedArithmeticTypes);


/** @brief Test fixture for @fgm::Vector2D projection with NaN vectors. */
class Vector2DProjectionNaNTests: public ::testing::TestWithParam<fgm::Vector2D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vector2DProjectionTestSuite, Vector2DProjectionNaNTests,
                         ::testing::Values(fgm::Vector2D<float>(fgm::constants::NaN, 1.0f),
                                           fgm::Vector2D<float>(1.0f, fgm::constants::NaN),
                                           fgm::Vector2D<float>(fgm::constants::NaN, fgm::constants::NaN)));



/**
 * @addtogroup T_FGM_Vec2_Proj
 * @{
 */

/**************************************
 *                                    *
 *          PROJECTION TESTS          *
 *                                    *
 **************************************/

/** @test Verify that projecting onto an orthogonal vector using @ref fgm::Vector2D::project returns a zero vector. */
TYPED_TEST(Vector2DProjection, OrthogonalVectorsReturnsZeroVector)
{
    const fgm::Vector2D actualProjection = this->_perpendicularVec.project(this->_ontoVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projecting onto a vector parallel to x-axis using @ref fgm::Vector2D::project
 *       returns a vector containing only an x-component.
 */
TEST(Vector2DProjection, ProjectionOntoXAxisReturnsVectorWithOnlyXComponent)
{
    // Given an arbitrary vector
    constexpr fgm::Vector2D a(10.0f, 20.0f);
    constexpr fgm::Vector2D xAxis(1.0f, 0.0f);
    constexpr fgm::Vector2D expectedProjection(10.0f, 0.0f);

    // When projected onto x-axis
    const fgm::Vector2D actualProjection = a.project(xAxis);

    // Then, the resultant vector only has x-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a vector parallel to y-axis using @ref fgm::Vector2D::project
 *       returns a vector containing only a y-component.
 */
TEST(Vector2DProjection, ProjectionOntoYAxisReturnsVectorWithOnlyYComponent)
{
    // Given an arbitrary vector
    constexpr fgm::Vector2D a(10.0f, 20.0f);
    constexpr fgm::Vector2D yAxis(0.0f, 1.0f);
    constexpr fgm::Vector2D expectedProjection(0.0f, 20.0f);

    // When projected onto y-axis
    const fgm::Vector2D actualProjection = a.project(yAxis);

    // Then, the resultant vector only has y-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector using @ref fgm::Vector2D::project
 *       returns a non-zero vector.
 */
TYPED_TEST(Vector2DProjection, NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector2D actualProjection = this->_vec.project(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vector2D::project
 *       returns a non-zero vector.
 */
TYPED_TEST(Vector2DProjection, StaticWrapper_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector2D actualProjection = fgm::Vector2D<TypeParam>::project(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vector2D::project with the
 *       @p ontoNormalized flag enabled returns a non-zero vector.
 */
TEST(Vector2DProjection, ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector2D a(1.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);
    constexpr fgm::Vector2D expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector2D actualProjection = a.project(b, true);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector2D::project returns a non-zero vector.
 */
TEST(Vector2DProjection, ProjectionOntoVectorInOppositeDirectionReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    constexpr fgm::Vector2D a(4.0f, 4.0f);
    constexpr fgm::Vector2D negativeYAxis(0.0f, -1.0f);
    constexpr fgm::Vector2D expectedProjection(0.0f, 4.0f);

    // When projected
    const fgm::Vector2D<float> actualProjection = a.project(negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vector2D::project returns a type-promoted vector.
 */
TEST(Vector2DProjection, MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector2D vec(7, 13);
    constexpr fgm::Vector2D onto(2.0, 4.0);
    constexpr fgm::Vector2D expectedProjection(6.6, 13.2);

    // When projected onto another
    const fgm::Vector2D actualProjection = vec.project(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/** @test Verify that projection using @ref fgm::Vector2D::project always return floating-point vector. */
TYPED_TEST(Vector2DProjection, Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector2D projection = this->_vec.project(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection using static variant of @ref fgm::Vector2D::project
 *       always return floating-point vector.
 */
TYPED_TEST(Vector2DProjection, StaticWrapper_Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector2D projection = fgm::Vector2D<float>::project(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**************************************
 *                                    *
 *        SAFE PROJECTION TESTS       *
 *                                    *
 **************************************/

/**
 * @test Verify that projecting onto an orthogonal vector using @ref fgm::Vector2D::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(Vector2DProjection, SafeProject_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector2D actualProjection = this->_vec.safeProject(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vector2D::safeProject with the
 *       @p ontoNormalized flag enabled returns a non-zero vector.
 */
TEST(Vector2DProjection, SafeProject_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector2D a(1.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);
    constexpr fgm::Vector2D expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector2D actualProjection = a.safeProject(b, true);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector2D::safeProject returns a non-zero vector.
 */
TEST(Vector2DProjection, SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    constexpr fgm::Vector2D a(4.0f, 4.0f);
    constexpr fgm::Vector2D negativeYAxis(0.0f, -1.0f);
    constexpr fgm::Vector2D expectedProjection(0.0f, 4.0f);

    // When projected
    const fgm::Vector2D<float> actualProjection = a.safeProject(negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vector2D::safeProject returns a type-promoted vector.
 */
TEST(Vector2DProjection, SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector2D vec(7, 13);
    constexpr fgm::Vector2D onto(2.0, 4.0);
    constexpr fgm::Vector2D expectedProjection(6.6, 13.2);

    // When projected onto another
    const fgm::Vector2D actualProjection = vec.safeProject(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a zero length vector using @ref fgm::Vector2D::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(Vector2DProjection, SafeProject_OntoZeroReturnsZeroVector)
{
    constexpr TypeParam zero = TypeParam(0);
    constexpr fgm::Vector2D zeroVec(zero, zero);

    const fgm::Vector2D actualProjection = this->_vec.safeProject(zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}

/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vector2D::safeProject
 *       returns a non-zero vector.
 */
TYPED_TEST(Vector2DProjection, StaticWrapper_SafeProject_NonOrthogonalProjectionReturnsNonZeroVector)
{
    const fgm::Vector2D actualProjection = fgm::Vector2D<TypeParam>::safeProject(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector2D::safeProject with the @p ontoNormalized flag enabled returns a non-zero vector.
 */
TEST(Vector2DProjection, StaticWrapper_SafeProject_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector2D a(1.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);
    constexpr fgm::Vector2D expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vector2D actualProjection = fgm::Vector2D<float>::safeProject(a, b, true);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref fgm::Vector2D::safeProject returns a non-zero vector.
 */
TEST(Vector2DProjection, StaticWrapper_SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    constexpr fgm::Vector2D a(4.0f, 4.0f);
    constexpr fgm::Vector2D negativeYAxis(0.0f, -1.0f);
    constexpr fgm::Vector2D expectedProjection(0.0f, 4.0f);

    // When projected
    const fgm::Vector2D<float> actualProjection = fgm::Vector2D<float>::safeProject(a, negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref fgm::Vector2D::safeProject returns a type-promoted vector.
 */
TEST(Vector2DProjection, StaticWrapper_SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector2D vec(7, 13);
    constexpr fgm::Vector2D onto(2.0, 4.0);
    constexpr fgm::Vector2D expectedProjection(6.6, 13.2);

    // When projected onto another
    const fgm::Vector2D actualProjection = fgm::Vector2D<float>::safeProject(vec, onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a zero length vector using static variant of @ref fgm::Vector2D::safeProject
 *       returns a type-promoted vector.
 */
TYPED_TEST(Vector2DProjection, StaticWrapper_SafeProject_OntoZeroVectorReturnsZeroVector)
{
    constexpr TypeParam zero = TypeParam(0);
    constexpr fgm::Vector2D zeroVec(zero, zero);

    const fgm::Vector2D actualProjection = fgm::Vector2D<float>::safeProject(this->_vec, zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/** @test Verify that projection using @ref fgm::Vector2D::safeProject always return floating-point vector. */
TYPED_TEST(Vector2DProjection, SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector2D projection = this->_vec.safeProject(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection using static variant of @ref fgm::Vector2D::safeProject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector2DProjection, StaticWrapper_SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector2D projection = fgm::Vector2D<float>::safeProject(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection of NaN vector using @ref fgm::Vector2D::safeProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector2DProjectionNaNTests, SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec = GetParam();
    const auto& ontoVec = fgm::vec2d::one<float>;

    EXPECT_VEC_ZERO(nanVec.safeProject(ontoVec));
}


/**
 * @test Verify that projection onto NaN vector using @ref fgm::Vector2D::safeProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector2DProjectionNaNTests, SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec = fgm::vec2d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeProject(ontoNaNVec));
}


/**
 * @test Verify that projection of NaN vector using static variant of @ref fgm::Vector2D::safeProject
 *       returns zero vector.
 */
TEST_P(Vector2DProjectionNaNTests, StaticWrapper_SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec = GetParam();
    const auto& ontoVec = fgm::vec2d::one<float>;

    EXPECT_VEC_ZERO(fgm::Vector2D<float>::safeProject(nanVec, ontoVec));
}


/**
 * @test Verify that projection onto NaN vector using static variant of @ref fgm::Vector2D::safeProject
 *       returns zero vector.
 */
TEST_P(Vector2DProjectionNaNTests, StaticWrapper_SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec = fgm::vec2d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector2D<float>::safeProject(oneVec, ontoNaNVec));
}


/**************************************
 *                                    *
 *         TRY PROJECTION TESTS       *
 *                                    *
 **************************************/

/**
 * @test Verify that projecting onto an orthogonal vector using @ref fgm::Vector2D::tryProject
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector2DProjection, TryProject_NonOrthogonalProjectionReturnsNonZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector2D actualProjection = this->_vec.tryProject(this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}
/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vector2D::tryProject with the
 *       @p ontoNormalized flag enabled returns a non-zero vector and
 *       sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector2DProjection, TryProject_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector2D a(1.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);
    constexpr fgm::Vector2D expectedProjection(1.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector2D actualProjection = a.tryProject(b, flag, true);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector2D::tryProject returns a non-zero vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector2DProjection, TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    constexpr fgm::Vector2D a(4.0f, 4.0f);
    constexpr fgm::Vector2D negativeYAxis(0.0f, -1.0f);
    constexpr fgm::Vector2D expectedProjection(0.0f, 4.0f);
    fgm::OperationStatus flag;

    // When projected
    const fgm::Vector2D<float> actualProjection = a.tryProject(negativeYAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vector2D::tryProject returns a type-promoted vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector2DProjection, TryProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector2D vec(7, 13);
    constexpr fgm::Vector2D onto(2.0, 4.0);
    constexpr fgm::Vector2D expectedProjection(6.6, 13.2);
    fgm::OperationStatus flag;

    // When projected onto another
    const fgm::Vector2D actualProjection = vec.tryProject(onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using @ref fgm::Vector2D::tryProject
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector2DProjection, TryProject_OntoZeroReturnsZeroVectorAndSetsCorrectFlag)
{
    constexpr TypeParam zero = TypeParam(0);
    constexpr fgm::Vector2D zeroVec(zero, zero);
    fgm::OperationStatus flag;


    const fgm::Vector2D actualProjection = this->_vec.tryProject(zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vector2D::tryProject
 *       returns a non-zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector2DProjection, StaticWrapper_TryProject_NonOrthogonalProjectionReturnsNonZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector2D actualProjection = fgm::Vector2D<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector2D::tryProject with the @p ontoNormalized flag enabled returns a non-zero vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector2DProjection, StaticWrapper_TryProject_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector2D a(1.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);
    constexpr fgm::Vector2D expectedProjection(1.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vector2D actualProjection = fgm::Vector2D<float>::tryProject(a, b, flag, true);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
    EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref fgm::Vector2D::tryProject returns a non-zero vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector2DProjection,
     StaticWrapper_TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    constexpr fgm::Vector2D a(4.0f, 4.0f);
    constexpr fgm::Vector2D negativeYAxis(0.0f, -1.0f);
    constexpr fgm::Vector2D expectedProjection(0.0f, 4.0f);
    fgm::OperationStatus flag;

    // When projected
    const fgm::Vector2D<float> actualProjection = fgm::Vector2D<float>::tryProject(a, negativeYAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref fgm::Vector2D::tryProject returns a type-promoted vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector2DProjection, StaticWrapper_TryProject_MixedTypeProjectionPromotesTypeAndSetsCorrectFlag)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector2D vec(7, 13);
    constexpr fgm::Vector2D onto(2.0, 4.0);
    constexpr fgm::Vector2D expectedProjection(6.6, 13.2);
    fgm::OperationStatus flag;

    // When projected onto another
    const fgm::Vector2D actualProjection = fgm::Vector2D<float>::tryProject(vec, onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using static variant of @ref fgm::Vector2D::tryProject
 *       returns a type-promoted vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector2DProjection, StaticWrapper_TryProject_OntoZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    constexpr TypeParam zero = TypeParam(0);
    constexpr fgm::Vector2D zeroVec(zero, zero);
    fgm::OperationStatus flag;

    const fgm::Vector2D actualProjection = fgm::Vector2D<float>::tryProject(this->_vec, zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/** @test Verify that projection using @ref fgm::Vector2D::tryProject always return floating-point vector. */
TYPED_TEST(Vector2DProjection, TryProject_AlwaysReturnFloatingPointVectorAndSetsCorrectFlag)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Vector2D projection = this->_vec.tryProject(this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection using static variant of @ref fgm::Vector2D::tryProject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector2DProjection, StaticWrapper_TryProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Vector2D projection =
        fgm::Vector2D<float>::tryProject(this->_vec, this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection of NaN vector using @ref fgm::Vector2D::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector2DProjectionNaNTests, TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec = GetParam();
    const auto& ontoVec = fgm::vec2d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryProject(ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using @ref fgm::Vector2D::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector2DProjectionNaNTests, TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec = fgm::vec2d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryProject(ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection of NaN vector using static variant of @ref fgm::Vector2D::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector2DProjectionNaNTests, StaticWrapper_TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec = GetParam();
    const auto& ontoVec = fgm::vec2d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vector2D<float>::tryProject(nanVec, ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using static variant of @ref fgm::Vector2D::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector2DProjectionNaNTests, StaticWrapper_TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec = fgm::vec2d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vector2D<float>::tryProject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
