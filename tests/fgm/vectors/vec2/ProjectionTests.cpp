/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vec2 projection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**
 * @addtogroup T_FGM_Vec2_Proj
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Vec2 projection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec2ProjectionTests: public testing::Test
    {
    protected:
        fgm::Vec2<T> _vec;
        fgm::Vec2<T> _perpendicularVec;
        fgm::Vec2<T> _ontoVec;
        fgm::Vec2<T> _expectedProjection;

        void SetUp() override
        {
            _vec                = { T(4), T(0) };
            _perpendicularVec   = { T(0), T(11) };
            _ontoVec            = { T(2), T(0) };
            _expectedProjection = { T(4), T(0) };
        }
    };
    TYPED_TEST_SUITE(Vec2ProjectionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref fgm::Vec2 projection with NaN vectors.
     */
    class Vec2ProjectionNaNTests: public testing::TestWithParam<fgm::Vec2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec2ProjectionNanVectors, Vec2ProjectionNaNTests,
                             ::testing::Values(fgm::Vec2<float>(fgm::constants::NaN, 1.0f),
                                               fgm::Vec2<float>(1.0f, fgm::constants::NaN),
                                               fgm::Vec2<float>(fgm::constants::NaN, fgm::constants::NaN)));



    /**************************************
     *           STATIC TESTS             *
     **************************************/
    namespace static_tests
    {
        constexpr fgm::Vec2 VEC_A(1, 2);
        constexpr fgm::Vec2 VEC_B(1, 0);

        /// @test Verify that vector projection(project) returns a valid vector at compile time.
        constexpr auto PROJ_VEC = VEC_A.project(VEC_B);
        static_assert(PROJ_VEC.x() == 1);
        static_assert(PROJ_VEC.y() == 0);


        /// @test Verify that vector projection(project-static wrapper) returns a valid vector at compile time.
        constexpr auto PROJ_VEC_STATIC = fgm::Vec2<int>::project(VEC_A, VEC_B);
        static_assert(PROJ_VEC_STATIC.x() == 1);
        static_assert(PROJ_VEC_STATIC.y() == 0);


        /// @test Verify that vector projection(project normalized) returns a valid vector at compile time.
        constexpr auto PROJ_NORM_VEC = VEC_A.projectNorm(VEC_B);
        static_assert(PROJ_NORM_VEC.x() == 1);
        static_assert(PROJ_NORM_VEC.y() == 0);


        /// @test Verify that vector projection(project normalized-static wrapper) returns a valid vector at compile
        /// time.
        constexpr auto PROJ_NORM_VEC_STATIC = fgm::Vec2<int>::projectNorm(VEC_A, VEC_B);
        static_assert(PROJ_NORM_VEC_STATIC.x() == 1);
        static_assert(PROJ_NORM_VEC_STATIC.y() == 0);


        /// @test Verify that vector projection(safe project) returns a valid vector at compile time.
        constexpr auto SAFE_PROJ_VEC = VEC_A.safeProject(VEC_B);
        static_assert(SAFE_PROJ_VEC.x() == 1);
        static_assert(SAFE_PROJ_VEC.y() == 0);


        /// @test Verify that vector projection(safe project-static wrapper) returns a valid vector at compile time.
        constexpr auto SAFE_PROJ_VEC_STATIC = fgm::Vec2<int>::safeProject(VEC_A, VEC_B);
        static_assert(SAFE_PROJ_VEC_STATIC.x() == 1);
        static_assert(SAFE_PROJ_VEC_STATIC.y() == 0);


        /// @test Verify that vector projection(safe project normalized) returns a valid vector at compile time.
        constexpr auto SAFE_PROJ_NORM_VEC = VEC_A.safeProjectNorm(VEC_B);
        static_assert(SAFE_PROJ_NORM_VEC.x() == 1);
        static_assert(SAFE_PROJ_NORM_VEC.y() == 0);


        /// @test Verify that vector projection(safe project normalized-static wrapper) returns a valid vector at
        /// compile time.
        constexpr auto SAFE_PROJ_NORM_VEC_STATIC = fgm::Vec2<int>::safeProjectNorm(VEC_A, VEC_B);
        static_assert(SAFE_PROJ_NORM_VEC_STATIC.x() == 1);
        static_assert(SAFE_PROJ_NORM_VEC_STATIC.y() == 0);
    } // namespace static_tests

} // namespace



/**************************************
 *          PROJECTION TESTS          *
 **************************************/

TYPED_TEST(Vec2ProjectionTests, Project_OrthogonalVectorsReturnsZeroVector)
{
    const fgm::Vec2 actualProjection = this->_perpendicularVec.project(this->_ontoVec);
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(Vec2ProjectionTests, Project_XAxis_ReturnVectorWithNonZeroXComponent)
{
    // Given an arbitrary vector
    const fgm::Vec2 a(10.0f, 20.0f);
    const fgm::Vec2 xAxis(1.0f, 0.0f);
    const fgm::Vec2 expectedProjection(10.0f, 0.0f);

    // When projected onto x-axis
    const fgm::Vec2 actualProjection = a.project(xAxis);

    // Then, the resultant vector only has x-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TEST(Vec2ProjectionTests, Project_YAxis_ReturnVectorWithNonZeroYComponent)
{
    // Given an arbitrary vector
    const fgm::Vec2 a(10.0f, 20.0f);
    const fgm::Vec2 yAxis(0.0f, 1.0f);
    const fgm::Vec2 expectedProjection(0.0f, 20.0f);

    // When projected onto y-axis
    const fgm::Vec2 actualProjection = a.project(yAxis);

    // Then, the resultant vector only has y-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TYPED_TEST(Vec2ProjectionTests, Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const fgm::Vec2 actualProjection = this->_vec.project(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


TYPED_TEST(Vec2ProjectionTests, StaticWrapper_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const fgm::Vec2 actualProjection = fgm::Vec2<TypeParam>::project(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


TEST(Vec2ProjectionTests, ProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec2 a(1.0f, 2.0f);
    const fgm::Vec2 b(1.0f, 0.0f);
    const fgm::Vec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vec2 actualProjection = a.projectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vec2::project returns a non-zero vector.
 */
TEST(Vec2ProjectionTests, ProjectionOntoVectorInOppositeDirectionReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vec2 a(4.0f, 4.0f);
    const fgm::Vec2 negativeYAxis(0.0f, -1.0f);
    const fgm::Vec2 expectedProjection(0.0f, 4.0f);

    // When projected
    const fgm::Vec2<float> actualProjection = a.project(negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vec2::project returns a type-promoted vector.
 */
TEST(Vec2ProjectionTests, MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vec2 vec(7, 13);
    const fgm::Vec2 onto(2.0, 4.0);
    const fgm::Vec2 expectedProjection(6.6, 13.2);

    // When projected onto another
    const fgm::Vec2 actualProjection = vec.project(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vec2::projectNorm returns a non-zero vector.
 */
TEST(Vec2ProjectionTests, StaticWrapper_ProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec2 a(1.0f, 2.0f);
    const fgm::Vec2 b(1.0f, 0.0f);
    const fgm::Vec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vec2 actualProjection = fgm::Vec2<float>::projectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/** @brief Verify that projection using @ref fgm::Vec2::project always return floating-point vector. */
TYPED_TEST(Vec2ProjectionTests, Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vec2 projection = this->_vec.project(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection using static variant of @ref fgm::Vec2::project
 *       always return floating-point vector.
 */
TYPED_TEST(Vec2ProjectionTests, StaticWrapper_Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vec2 projection = fgm::Vec2<TypeParam>::project(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}





/**************************************
 *        SAFE PROJECTION TESTS       *
 **************************************/

TYPED_TEST(Vec2ProjectionTests, SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const fgm::Vec2 actualProjection = this->_vec.safeProject(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}



TEST(Vec2ProjectionTests, SafeProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec2 a(1.0f, 2.0f);
    const fgm::Vec2 b(1.0f, 0.0f);
    const fgm::Vec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vec2 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TEST(Vec2ProjectionTests, SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const fgm::Vec2 a(1.0f, fgm::constants::NaN);
    const fgm::Vec2 b(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vec2 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(Vec2ProjectionTests, SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec2 a(1.0f, 2.0f);
    const fgm::Vec2 b(1.0f, fgm::constants::NaN);

    // When the vector is projected onto the normalized vector
    const fgm::Vec2 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(Vec2ProjectionTests, SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vec2 a(4.0f, 4.0f);
    const fgm::Vec2 negativeYAxis(0.0f, -1.0f);
    const fgm::Vec2 expectedProjection(0.0f, 4.0f);

    // When projected
    const fgm::Vec2<float> actualProjection = a.safeProject(negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}



TEST(Vec2ProjectionTests, SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vec2 vec(7, 13);
    const fgm::Vec2 onto(2.0, 4.0);
    const fgm::Vec2 expectedProjection(6.6, 13.2);

    // When projected onto another
    const fgm::Vec2 actualProjection = vec.safeProject(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}



TYPED_TEST(Vec2ProjectionTests, SafeProject_OntoZeroReturnsZeroVector)
{
    const fgm::Vec2 zeroVec = fgm::Vec2<TypeParam>::zero();

    const fgm::Vec2 actualProjection = this->_vec.safeProject(zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}


TYPED_TEST(Vec2ProjectionTests, StaticWrapper_SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const fgm::Vec2 actualProjection = fgm::Vec2<TypeParam>::safeProject(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


TEST(Vec2ProjectionTests, StaticWrapper_SafeProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec2 a(1.0f, 2.0f);
    const fgm::Vec2 b(1.0f, 0.0f);
    const fgm::Vec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vec2 actualProjection = fgm::Vec2<float>::safeProjectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TEST(Vec2ProjectionTests, StaticWrapper_SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const fgm::Vec2 a(1.0f, fgm::constants::NaN);
    const fgm::Vec2 b(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const fgm::Vec2 actualProjection = fgm::Vec2<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(Vec2ProjectionTests, StaticWrapper_SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const fgm::Vec2 a(1.0f, 2.0f);
    const fgm::Vec2 b(1.0f, fgm::constants::NaN);

    // When the vector is from a NaN vector
    const fgm::Vec2 actualProjection = fgm::Vec2<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(Vec2ProjectionTests, StaticWrapper_SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vec2 a(4.0f, 4.0f);
    const fgm::Vec2 negativeYAxis(0.0f, -1.0f);
    const fgm::Vec2 expectedProjection(0.0f, 4.0f);

    // When projected
    const fgm::Vec2<float> actualProjection = fgm::Vec2<float>::safeProject(a, negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}



TEST(Vec2ProjectionTests, StaticWrapper_SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vec2 vec(7, 13);
    const fgm::Vec2 onto(2.0, 4.0);
    const fgm::Vec2 expectedProjection(6.6, 13.2);

    // When projected onto another
    const fgm::Vec2 actualProjection = fgm::Vec2<int>::safeProject(vec, onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TYPED_TEST(Vec2ProjectionTests, StaticWrapper_SafeProject_OntoZeroVectorReturnsZeroVector)
{
    const fgm::Vec2 zeroVec = fgm::Vec2<TypeParam>::zero();
    const fgm::Vec2 actualProjection = fgm::Vec2<TypeParam>::safeProject(this->_vec, zeroVec);
    EXPECT_VEC_ZERO(actualProjection);
}


TYPED_TEST(Vec2ProjectionTests, SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vec2 projection = this->_vec.safeProject(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


TYPED_TEST(Vec2ProjectionTests, StaticWrapper_SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vec2 projection = fgm::Vec2<TypeParam>::safeProject(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


TEST_P(Vec2ProjectionNaNTests, SafeProject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::Vec2<float>::one();

    EXPECT_VEC_ZERO(nanVec.safeProject(ontoVec));
}


TEST_P(Vec2ProjectionNaNTests, SafeProject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = fgm::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeProject(ontoNaNVec));
}


TEST_P(Vec2ProjectionNaNTests, StaticWrapper_SafeProject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::Vec2<float>::one();

    EXPECT_VEC_ZERO(fgm::Vec2<float>::safeProject(nanVec, ontoVec));
}


TEST_P(Vec2ProjectionNaNTests, StaticWrapper_SafeProject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = fgm::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vec2<float>::safeProject(oneVec, ontoNaNVec));
}



/**************************************
 *         TRY PROJECTION TESTS       *
 **************************************/

/**
 * @brief Verify that projecting onto an orthogonal vector using @ref fgm::Vec2::tryProject
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2ProjectionTests, TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vec2 actualProjection = this->_vec.tryProject(this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using @ref fgm::Vec2::tryProjectNorm
 *       returns a non-zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vec2ProjectionTests, TryProject_NormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec2 a(1.0f, 2.0f);
    const fgm::Vec2 b(1.0f, 0.0f);
    const fgm::Vec2 expectedProjection(1.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vec2 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref fgm::Vec2::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec2ProjectionTests, TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec2 a(fgm::constants::NaN, 2.0f);
    const fgm::Vec2 b(1.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vec2 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projecting a vector onto a NaN vector using @ref fgm::Vec2::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec2ProjectionTests, TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec2 a(1.0f, 2.0f);
    const fgm::Vec2 b(1.0f, fgm::constants::NaN);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vec2 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vec2::tryProject returns a non-zero vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vec2ProjectionTests, TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vec2 a(4.0f, 4.0f);
    const fgm::Vec2 negativeYAxis(0.0f, -1.0f);
    const fgm::Vec2 expectedProjection(0.0f, 4.0f);
    fgm::OperationStatus flag;

    // When projected
    const fgm::Vec2<float> actualProjection = a.tryProject(negativeYAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref fgm::Vec2::tryProject returns a type-promoted vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vec2ProjectionTests, TryProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vec2 vec(7, 13);
    const fgm::Vec2 onto(2.0, 4.0);
    const fgm::Vec2 expectedProjection(6.6, 13.2);
    fgm::OperationStatus flag;

    // When projected onto another
    const fgm::Vec2 actualProjection = vec.tryProject(onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a zero length vector using @ref fgm::Vec2::tryProject
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2ProjectionTests, TryProject_OntoZeroReturnsZeroVectorAndSetsCorrectFlag)
{
    const fgm::Vec2 zeroVec = fgm::Vec2<TypeParam>::zero();
    fgm::OperationStatus flag;


    const fgm::Vec2 actualProjection = this->_vec.tryProject(zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector using static variant of @ref fgm::Vec2::tryProject
 *       returns a non-zero vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2ProjectionTests, StaticWrapper_TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vec2 actualProjection = fgm::Vec2<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vec2::tryProjectNorm returns a non-zero vector and sets the flag to
 *       @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vec2ProjectionTests, StaticWrapper_TryProjectNorm_NormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec2 a(1.0f, 2.0f);
    const fgm::Vec2 b(1.0f, 0.0f);
    const fgm::Vec2 expectedProjection(1.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const fgm::Vec2 actualProjection = fgm::Vec2<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of @ref
 * fgm::Vec2::tryProjectNorm returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec2ProjectionTests, StaticWrapper_TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const fgm::Vec2 a(fgm::constants::NaN, 2.0f);
    const fgm::Vec2 b(1.0f, 0.0f);
    fgm::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const fgm::Vec2 actualProjection = fgm::Vec2<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/**
 * @brief Verify that projecting a vector onto a NaN vector using static variant of @ref fgm::Vec2::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec2ProjectionTests, StaticWrapper_TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const fgm::Vec2 a(1.0f, 2.0f);
    const fgm::Vec2 b(1.0f, fgm::constants::NaN);
    fgm::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const fgm::Vec2 actualProjection = fgm::Vec2<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref fgm::Vec2::tryProject returns a non-zero vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vec2ProjectionTests,
     StaticWrapper_TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const fgm::Vec2 a(4.0f, 4.0f);
    const fgm::Vec2 negativeYAxis(0.0f, -1.0f);
    const fgm::Vec2 expectedProjection(0.0f, 4.0f);
    fgm::OperationStatus flag;

    // When projected
    const fgm::Vec2<float> actualProjection = fgm::Vec2<float>::tryProject(a, negativeYAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref fgm::Vec2::tryProject returns a type-promoted vector
 *       and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vec2ProjectionTests, StaticWrapper_TryProject_MixedTypeProjectionPromotesTypeAndSetsCorrectFlag)
{
    // Given two arbitrary vectors
    const fgm::Vec2 vec(7, 13);
    const fgm::Vec2 onto(2.0, 4.0);
    const fgm::Vec2 expectedProjection(6.6, 13.2);
    fgm::OperationStatus flag;

    // When projected onto another
    const fgm::Vec2 actualProjection = fgm::Vec2<int>::tryProject(vec, onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that projecting onto a zero length vector using static variant of @ref fgm::Vec2::tryProject
 *       returns a type-promoted vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2ProjectionTests, StaticWrapper_TryProject_OntoZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const fgm::Vec2 zeroVec = fgm::Vec2<TypeParam>::zero();
    fgm::OperationStatus flag;

    const fgm::Vec2 actualProjection = fgm::Vec2<TypeParam>::tryProject(this->_vec, zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/** @brief Verify that projection using @ref fgm::Vec2::tryProject always return floating-point vector. */
TYPED_TEST(Vec2ProjectionTests, TryProject_AlwaysReturnFloatingPointVectorAndSetsCorrectFlag)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Vec2 projection = this->_vec.tryProject(this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection using static variant of @ref fgm::Vec2::tryProject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec2ProjectionTests, StaticWrapper_TryProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Vec2 projection = fgm::Vec2<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @brief Verify that projection of NaN vector using @ref fgm::Vec2::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2ProjectionNaNTests, TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::Vec2<float>::one();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryProject(ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projection onto NaN vector using @ref fgm::Vec2::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2ProjectionNaNTests, TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryProject(ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projection of NaN vector using static variant of @ref fgm::Vec2::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2ProjectionNaNTests, StaticWrapper_TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::Vec2<float>::one();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vec2<float>::tryProject(nanVec, ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that projection onto NaN vector using static variant of @ref fgm::Vec2::tryProject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2ProjectionNaNTests, StaticWrapper_TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec2<float>::tryProject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
