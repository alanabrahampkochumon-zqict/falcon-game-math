/**
 * @file RejectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vector2D rejection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"



template <typename T>
class Vector2DRejection: public ::testing::Test
{
protected:
    fgm::Vector2D<T> _vec;
    fgm::Vector2D<T> _parallelVec;
    fgm::Vector2D<T> _fromVec;
    fgm::Vector2D<T> _expectedRejection;

    void SetUp() override
    {
        _vec = { T(4), T(0) };
        _parallelVec = { T(6), T(0) };
        _fromVec = { T(0), T(2) };
        _expectedRejection = { T(4), T(0) };
    }
};
/** @brief Test fixture for @ref fgm::Vector2D rejection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector2DRejection, SupportedArithmeticTypes);


/** @brief Test fixture for @fgm::Vector2D rejection with NaN vectors. */
class Vector2DRejectionNaNTests: public ::testing::TestWithParam<fgm::Vector2D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vector2DRejectionTestSuite, Vector2DRejectionNaNTests,
                         ::testing::Values(fgm::Vector2D<float>(fgm::constants::NaN, 1.0f),
                                           fgm::Vector2D<float>(1.0f, fgm::constants::NaN),
                                           fgm::Vector2D<float>(fgm ::constants::NaN, fgm::constants::NaN)));



/**
 * @addtogroup T_FGM_Vec2_Rej
 * @{
 */

/**************************************
 *                                    *
 *          REJECTION TESTS           *
 *                                    *
 **************************************/

/** @test Verify that rejecting from a parallel vector using @ref fgm::Vector2D::reject returns a zero vector. */
TYPED_TEST(Vector2DRejection, ParallelVectorsReturnsZeroVector)
{
    const fgm::Vector2D actualRejection = this->_vec.reject(this->_parallelVec);
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to x-axis using @ref fgm::Vector2D::reject
 *       returns a vector with a zero x-component.
 */
TEST(Vector2DRejection, RejectionFromXAxisReturnsVectorWithZeroXComponent)
{
    // Given an arbitrary vector
    constexpr fgm::Vector2D a(10.0f, 20.0f);
    constexpr fgm::Vector2D xAxis(1.0f, 0.0f);
    constexpr fgm::Vector2D expectedRejection(0.0f, 20.0f);

    // When rejected from x-axis
    const fgm::Vector2D actualRejection = a.reject(xAxis);

    // Then, the resultant vector has zero x-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to y-axis using @ref fgm::Vector2D::reject
 *       returns a vector with a zero y-component.
 */
TEST(Vector2DRejection, RejectionFromYAxisReturnsVectorWithZeroYComponent)
{
    // Given an arbitrary vector
    constexpr fgm::Vector2D a(10.0f, 20.0f);
    constexpr fgm::Vector2D yAxis(0.0f, 1.0f);
    constexpr fgm::Vector2D expectedRejection(10.0f, 0.0f);

    // When rejected from y-axis
    const fgm::Vector2D actualRejection = a.reject(yAxis);

    // Then, the resultant vector has zero y-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @test Verify that rejecting an orthogonal using @ref fgm::Vector2D::reject returns the original vector. */
TEST(Vector2DRejection, OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    constexpr fgm::Vector2D a(0.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);

    // When rejected on to an orthogonal vector
    const fgm::Vector2D actualRejection = a.reject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that rejecting from a non-orthogonal vector using @ref fgm::Vector2D::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector2DRejection, NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector2D actualRejection = this->_vec.reject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a non-orthogonal vector using static variant of @ref fgm::Vector2D::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector2DRejection, StaticWrapper_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector2D actualRejection = fgm::Vector2D<TypeParam>::reject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal unit vector using @ref fgm::Vector2D::reject with the
 *       @p fromNormalized flag enabled returns a non-zero vector with perpendicular component.
 */
TEST(Vector2DRejection, RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector2D a(1.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);
    constexpr fgm::Vector2D expectedRejection(0.0f, 2.0f);

    // When rejected from another
    const fgm::Vector2D actualRejection = a.reject(b, true);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector2D::reject returns a non-zero vector with perpendicular components.
 */
TEST(Vector2DRejection, RejectionFromVectorInOppositeDirectionReturnsVectorWithPerpendicularComponents)
{
    // Given an arbitrary vector
    constexpr fgm::Vector2D a(4.0f, 4.0f);
    constexpr fgm::Vector2D negativeYAxis(0.0f, -1.0f);
    constexpr fgm::Vector2D expectedRejection(4.0f, 0.0f);

    // When rejected from a vector in opposite direction
    const fgm::Vector2D actualRejection = a.reject(negativeYAxis);

    // Then, the resultant vector has components perpendicular to the `from` vector in the same direction.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting a vector from another vector of different numeric type using @ref fgm::Vector2D::reject
 *       returns a type-promoted vector.
 */
TEST(Vector2DRejection, MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector2D vec(7, 13);
    constexpr fgm::Vector2D from(2.0, 4.0);
    constexpr fgm::Vector2D expectedRejection(0.4, -0.2);

    // When reject from another
    const fgm::Vector2D actualRejection = vec.reject(from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @test Verify that rejection using @ref fgm::Vector2D::reject always return floating-point vector. */
TYPED_TEST(Vector2DRejection, Reject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector2D rejection = this->_vec.reject(this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @test Verify that rejection using static variant of @ref fgm::Vector2D::reject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector2DRejection, StaticWrapper_Reject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector2D rejection = fgm::Vector2D<float>::reject(this->_vec, this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**************************************
 *                                    *
 *       SAFE REJECTION TESTS         *
 *                                    *
 **************************************/

/**
 * @test Verify that safely rejecting from a parallel vector using @ref fgm::Vector2D::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(Vector2DRejection, SafeReject_ParallelVectorsReturnsZeroVector)
{
    const fgm::Vector2D actualRejection = this->_vec.safeReject(this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from orthogonal using @ref fgm::Vector2D::safeReject
 *       returns the original vector.
 */
TEST(Vector2DRejection, SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    constexpr fgm::Vector2D a(0.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);

    // When rejected from an orthogonal vector
    const fgm::Vector2D actualRejection = a.safeReject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using @ref fgm::Vector2D::safeReject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector2DRejection, SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector2D actualRejection = this->_vec.safeReject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref fgm::Vector2D::safeReject with the
 *       @p fromNormalized flag enabled returns a non-zero vector with perpendicular component.
 */
TEST(Vector2DRejection, SafeReject_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector2D a(1.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);
    constexpr fgm::Vector2D expectedRejection(0.0f, 2.0f);

    // When rejected from another
    const fgm::Vector2D actualRejection = a.safeReject(b, true);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from another vector of different numeric
 *       type using @ref fgm::Vector2D::safeReject returns a type-promoted vector.
 */
TEST(Vector2DRejection, SafeReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector2D vec(7, 13);
    constexpr fgm::Vector2D from(2.0, 4.0);
    constexpr fgm::Vector2D expectedRejection(0.4, -0.2);

    // When rejected from another
    const fgm::Vector2D actualRejection = vec.safeReject(from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from a zero vector using @ref fgm::Vector2D::safeReject
 *       returns the same vector.
 */
TYPED_TEST(Vector2DRejection, SafeReject_FromZeroVectorReturnsSameVector)
{
    constexpr fgm::Vector2D zeroVec = fgm::vec2d::zero<TypeParam>;

    const fgm::Vector2D actualRejection = this->_vec.safeReject(zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/**
 * @test Verify that safely rejecting from a parallel vector using static variant of @ref fgm::Vector2D::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(Vector2DRejection, StaticWrapper_SafeReject_ParallelVectorsReturnsZeroVector)
{
    const fgm::Vector2D actualRejection = fgm::Vector2D<TypeParam>::safeReject(this->_vec, this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref fgm::Vector2D::safeReject returns the original vector.
 */
TEST(Vector2DRejection, StaticWrapper_SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    constexpr fgm::Vector2D a(0.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);

    const fgm::Vector2D actualRejection = fgm::Vector2D<float>::safeReject(a, b);

    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref fgm::Vector2D::safeReject returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector2DRejection, StaticWrapper_SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector2D actualRejection = fgm::Vector2D<TypeParam>::safeReject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref fgm::Vector2D::safeReject with the @p fromNormalized flag enabled returns a non-zero vector with
 *       perpendicular component.
 */
TEST(Vector2DRejection, StaticWrapper_SafeReject_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector2D a(1.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);
    constexpr fgm::Vector2D expectedRejection(0.0f, 2.0f);

    // When rejected from another
    const fgm::Vector2D actualRejection = fgm::Vector2D<float>::safeReject(a, b, true);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from another vector of different numeric type
 *       using static variant of @ref fgm::Vector2D::safeReject returns a type-promoted vector.
 */
TEST(Vector2DRejection, StaticWrapper_SafeReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector2D vec(7, 13);
    constexpr fgm::Vector2D from(2.0, 4.0);
    constexpr fgm::Vector2D expectedRejection(0.4, -0.2);

    // When rejected from another
    const fgm::Vector2D actualRejection = fgm::Vector2D<float>::safeReject(vec, from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from a zero length vector using static variant of @ref fgm::Vector2D::safeReject
 *       returns the same vector.
 */
TYPED_TEST(Vector2DRejection, StaticWrapper_SafeReject_FromZeroVectorReturnsSameVector)
{
    constexpr fgm::Vector2D zeroVec = fgm::vec2d::zero<TypeParam>;

    const fgm::Vector2D actualRejection = fgm::Vector2D<TypeParam>::safeReject(this->_vec, zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/** @test Verify that rejection using @ref fgm::Vector2D::safeReject always return floating-point vector. */
TYPED_TEST(Vector2DRejection, SafeReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector2D rejection = this->_vec.safeReject(this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @test Verify that rejection using static variant of @ref fgm::Vector2D::safeReject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector2DRejection, StaticWrapper_SafeReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector2D rejection = fgm::Vector2D<float>::safeReject(this->_vec, this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @test Verify that the rejection of NaN vector using @ref fgm::Vector2D::safeReject
 *       returns zero vector.
 */
TEST_P(Vector2DRejectionNaNTests, SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec = GetParam();
    const auto& ontoVec = fgm::vec2d::one<float>;

    EXPECT_VEC_ZERO(nanVec.safeReject(ontoVec));
}


/**
 * @test Verify that rejecting onto NaN vector using @ref fgm::Vector2D::safeReject
 *       returns zero vector.
 */
TEST_P(Vector2DRejectionNaNTests, SafeReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec = fgm::vec2d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeReject(ontoNaNVec));
}


/**
 * @test Verify that the rejection of NaN vector using static variant of @ref fgm::Vector2D::safeReject
 *       returns zero vector.
 */
TEST_P(Vector2DRejectionNaNTests, StaticWrapper_SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec = GetParam();
    const auto& ontoVec = fgm::vec2d::one<float>;

    EXPECT_VEC_ZERO(fgm::Vector2D<float>::safeReject(nanVec, ontoVec));
}


/**
 * @test Verify that rejecting onto a NaN vector using static variant of @ref fgm::Vector2D::safeReject
 *       returns zero vector.
 */
TEST_P(Vector2DRejectionNaNTests, StaticWrapper_SafeReject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec = fgm::vec2d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector2D<float>::safeReject(oneVec, ontoNaNVec));
}


/**************************************
 *                                    *
 *        TRY REJECTION TESTS         *
 *                                    *
 **************************************/

/**
 * @test Verify that safely rejecting from a parallel vector using @ref fgm::Vector2D::tryReject
 *       returns a zero vector  and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector2DRejection, TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector2D actualRejection = this->_vec.tryReject(this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from orthogonal using @ref fgm::Vector2D::tryReject
 *       returns the original vector and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector2DRejection, TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector
    constexpr fgm::Vector2D a(0.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);
    fgm::OperationStatus flag;

    // When rejected from an orthogonal vector
    const fgm::Vector2D actualRejection = a.tryReject(b, flag);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using @ref fgm::Vector2D::tryReject
 *       returns a non-zero vector with perpendicular component sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector2DRejection, TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector2D actualRejection = this->_vec.tryReject(this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref fgm::Vector2D::tryReject with the
 *       @p fromNormalized flag enabled returns a non-zero vector with perpendicular component
 *       sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector2DRejection, TryReject_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector2D a(1.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);
    constexpr fgm::Vector2D expectedRejection(0.0f, 2.0f);
    fgm::OperationStatus flag;


    // When rejected from another
    const fgm::Vector2D actualRejection = a.tryReject(b, flag, true);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting a vector from another vector of different numeric
 *       type using @ref fgm::Vector2D::tryReject returns a type-promoted vector
 *       sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector2DRejection, TryReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector2D vec(7, 13);
    constexpr fgm::Vector2D from(2.0, 4.0);
    constexpr fgm::Vector2D expectedRejection(0.4, -0.2);
    fgm::OperationStatus flag;

    // When rejected from another
    const fgm::Vector2D actualRejection = vec.tryReject(from, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a zero vector using @ref fgm::Vector2D::tryReject
 *       returns the same vector and sets flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector2DRejection, TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    constexpr fgm::Vector2D zeroVec = fgm::vec2d::zero<TypeParam>;
    fgm::OperationStatus flag;

    const fgm::Vector2D actualRejection = this->_vec.tryReject(zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that safely rejecting from a parallel vector using static variant of @ref fgm::Vector2D::tryReject
 *       returns a zero vector and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector2DRejection, StaticWrapper_TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;

    const fgm::Vector2D actualRejection = fgm::Vector2D<TypeParam>::tryReject(this->_vec, this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref fgm::Vector2D::tryReject returns the original vector
 *       and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector2DRejection, StaticWrapper_TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    constexpr fgm::Vector2D a(0.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);
    fgm::OperationStatus flag;

    const fgm::Vector2D actualRejection = fgm::Vector2D<float>::tryReject(a, b, flag);

    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref fgm::Vector2D::tryReject returns a non-zero vector with perpendicular component
 *       and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector2DRejection,
           StaticWrapper_TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;

    const fgm::Vector2D actualRejection = fgm::Vector2D<TypeParam>::tryReject(this->_vec, this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref fgm::Vector2D::tryReject with the @p fromNormalized flag enabled returns a non-zero vector with
 *       perpendicular component and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector2DRejection, StaticWrapper_TryReject_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector2D a(1.0f, 2.0f);
    constexpr fgm::Vector2D b(1.0f, 0.0f);
    constexpr fgm::Vector2D expectedRejection(0.0f, 2.0f);
    fgm::OperationStatus flag;

    // When rejected from another
    const fgm::Vector2D actualRejection = fgm::Vector2D<float>::tryReject(a, b, flag, true);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    // Flag is set to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting a vector from another vector of different numeric type
 *       using static variant of @ref fgm::Vector2D::tryReject returns a type-promoted vector
 *       and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector2DRejection, StaticWrapper_TryReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector2D vec(7, 13);
    constexpr fgm::Vector2D from(2.0, 4.0);
    constexpr fgm::Vector2D expectedRejection(0.4, -0.2);
    fgm::OperationStatus flag;

    // When rejected from another
    const fgm::Vector2D actualRejection = fgm::Vector2D<float>::tryReject(vec, from, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    // Flag is set to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a zero length vector using static variant of @ref fgm::Vector2D::tryReject
 *       returns the same vector and sets flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector2DRejection, StaticWrapper_TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    constexpr fgm::Vector2D zeroVec = fgm::vec2d::zero<TypeParam>;
    fgm::OperationStatus flag;

    const fgm::Vector2D actualRejection = fgm::Vector2D<TypeParam>::tryReject(this->_vec, zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/** @test Verify that rejection using @ref fgm::Vector2D::tryReject always return floating-point vector. */
TYPED_TEST(Vector2DRejection, TryRejectAlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus status;
    [[maybe_unused]] const fgm::Vector2D rejection = this->_vec.tryReject(this->_fromVec, status);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @test Verify that rejection using static variant of @ref fgm::Vector2D::tryReject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector2DRejection, StaticWrapper_TryReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus status;
    [[maybe_unused]] const fgm::Vector2D rejection =
        fgm::Vector2D<float>::tryReject(this->_vec, this->_fromVec, status);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}



/**
 * @test Verify that the rejection of NaN vector using @ref fgm::Vector2D::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector2DRejectionNaNTests, TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec = GetParam();
    const auto& ontoVec = fgm::vec2d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryReject(ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection onto NaN vector using @ref fgm::Vector2D::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector2DRejectionNaNTests, TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec = fgm::vec2d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryReject(ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection of NaN vector using static variant of @ref fgm::Vector2D::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector2DRejectionNaNTests, StaticWrapper_TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec = GetParam();
    const auto& ontoVec = fgm::vec2d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vector2D<float>::tryReject(nanVec, ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection onto NaN vector using static variant of @ref fgm::Vector2D::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector2DRejectionNaNTests, StaticWrapper_TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec = fgm::vec2d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vector2D<float>::tryReject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */