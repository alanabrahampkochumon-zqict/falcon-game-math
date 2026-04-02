/**
 * @file RejectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 28, 2026
 *
 * @brief Verifies @ref fgm::Vector4D rejection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"



template <typename T>
class Vector4DRejection: public ::testing::Test
{
protected:
    fgm::Vector4D<T> _vec;
    fgm::Vector4D<T> _parallelVec;
    fgm::Vector4D<T> _fromVec;
    fgm::Vector4D<T> _expectedRejection;

    void SetUp() override
    {
        _vec = { T(1), T(2), T(3), T(4) };
        _parallelVec = { T(2), T(4), T(6), T(8) };
        _fromVec = { T(0), T(2), T(0), T(0) };
        _expectedRejection = { T(1), T(0), T(3), T(4) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D rejection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DRejection, SupportedArithmeticTypes);


/** @brief Test fixture for @fgm::Vector4D rejection with NaN vectors. */
class Vector4DRejectionNaNTests: public ::testing::TestWithParam<fgm::Vector4D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vector4RejectionTestSuite, Vector4DRejectionNaNTests,
                         ::testing::Values(fgm::Vector4D<float>(fgm::constants::NaN, 1.0f, 1.0f, 1.0f),
                                           fgm::Vector4D<float>(1.0f, fgm::constants::NaN, 1.0f, 1.0f),
                                           fgm::Vector4D<float>(1.0f, 1.0f, fgm::constants::NaN, 1.0f),
                                           fgm::Vector4D<float>(1.0f, 1.0f, 1.0f, fgm::constants::NaN),
                                           fgm::Vector4D<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN, fgm ::constants::NaN)));

// TODO: SafeRejection tests for NaN
// TODO: Update rejection tests

/**
 * @addtogroup T_FGM_Vec4_Rej
 * @{
 */

/**************************************
 *                                    *
 *          REJECTION TESTS           *
 *                                    *
 **************************************/

/** @test Verify that rejecting from a parallel vector using @ref fgm::Vector4D::reject returns a zero vector. */
TYPED_TEST(Vector4DRejection, ParallelVectorsReturnsZeroVector)
{
    const fgm::Vector4D actualRejection = this->_vec.reject(this->_parallelVec);
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to x-axis using @ref fgm::Vector4D::reject
 *       returns a vector with a zero x-component.
 */
TEST(Vector4DRejection, RejectionFromXAxisReturnsVectorWithZeroXComponent)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    constexpr fgm::Vector4D xAxis(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(0.0f, 20.0f, 30.0f, 40.f);

    // When rejected from x-axis
    const fgm::Vector4D actualRejection = a.reject(xAxis);

    // Then, the resultant vector has zero x-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to y-axis using @ref fgm::Vector4D::reject
 *       returns a vector with a zero y-component.
 */
TEST(Vector4DRejection, RejectionFromYAxisReturnsVectorWithZeroYComponent)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    constexpr fgm::Vector4D yAxis(0.0f, 1.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(10.0f, 0.0f, 30.0f, 40.0f);

    // When rejected from y-axis
    const fgm::Vector4D actualRejection = a.reject(yAxis);

    // Then, the resultant vector has zero y-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to z-axis using @ref fgm::Vector4D::reject
 *       returns a vector with a zero z-component.
 */
TEST(Vector4DRejection, RejectionFromZAxisReturnsVectorWithZeroZComponent)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    constexpr fgm::Vector4D zAxis(0.0f, 0.0f, 1.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(10.0f, 20.0f, 0.0f, 40.0f);

    // When rejected from z-axis
    const fgm::Vector4D actualRejection = a.reject(zAxis);

    // Then, the resultant vector has zero z-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to w-axis using @ref fgm::Vector4D::reject
 *       returns a vector with a zero w-component.
 */
TEST(Vector4DRejection, RejectionFromWAxisReturnsVectorWithZeroWComponent)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
    constexpr fgm::Vector4D wAxis(0.0f, 0.0f, 0.0f, 1.0f);
    constexpr fgm::Vector4D expectedRejection(10.0f, 20.0f, 30.0f, 0.0f);

    // When rejected from w-axis
    const fgm::Vector4D actualRejection = a.reject(wAxis);

    // Then, the resultant vector has zero w-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @test Verify that rejecting an orthogonal using @ref fgm::Vector4D::reject returns the original vector. */
TEST(Vector4DRejection, OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 0.0f);
    constexpr fgm::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);

    // When rejected on to an orthogonal vector
    const fgm::Vector4D actualRejection = a.reject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that rejecting from a non-orthogonal vector using @ref fgm::Vector4D::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector4DRejection, NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualRejection = this->_vec.reject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a non-orthogonal vector using static variant of @ref fgm::Vector4D::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualRejection = fgm::Vector4D<TypeParam>::reject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal unit vector using @ref fgm::Vector4D::reject with the
 *       @p fromNormalized flag enabled returns a non-zero vector with perpendicular component.
 */
TEST(Vector4DRejection, RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected from another
    const fgm::Vector4D actualRejection = a.reject(b, true);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector4D::reject returns a non-zero vector with perpendicular components.
 */
TEST(Vector4DRejection, RejectionFromVectorInOppositeDirectionReturnsVectorWithPerpendicularComponents)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
    constexpr fgm::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(4.0f, 4.0f, 0.0f, 4.0f);

    // When rejected from a vector in opposite direction
    const fgm::Vector4D actualRejection = a.reject(negativeZAxis);

    // Then, the resultant vector has components perpendicular to the `from` vector in the same direction.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting a vector from another vector of different numeric type using @ref fgm::Vector4D::reject
 *       returns a type-promoted vector.
 */
TEST(Vector4DRejection, MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector4D vec(7, 13, 29, 41);
    constexpr fgm::Vector4D from(2.0, 4.0, 4.0, 2.0);
    constexpr fgm::Vector4D expectedRejection(-6.2, -13.4, 2.6, 27.8);

    // When reject from another
    const fgm::Vector4D actualRejection = vec.reject(from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @test Verify that rejection using @ref fgm::Vector4D::reject always return floating-point vector. */
TYPED_TEST(Vector4DRejection, Reject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector4D rejection = this->_vec.reject(this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @test Verify that rejection using static variant of @ref fgm::Vector4D::reject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_Reject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector4D rejection = fgm::Vector4D<float>::reject(this->_vec, this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**************************************
 *                                    *
 *       SAFE REJECTION TESTS         *
 *                                    *
 **************************************/

/**
 * @test Verify that safely rejecting from a parallel vector using @ref fgm::Vector4D::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(Vector4DRejection, SafeReject_ParallelVectorsReturnsZeroVector)
{
    const fgm::Vector4D actualRejection = this->_vec.safeReject(this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from orthogonal using @ref fgm::Vector4D::safeReject
 *       returns the original vector.
 */
TEST(Vector4DRejection, SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 0.0f);
    constexpr fgm::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);

    // When rejected from an orthogonal vector
    const fgm::Vector4D actualRejection = a.safeReject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using @ref fgm::Vector4D::safeReject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector4DRejection, SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualRejection = this->_vec.safeReject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref fgm::Vector4D::safeReject with the
 *       @p fromNormalized flag enabled returns a non-zero vector with perpendicular component.
 */
TEST(Vector4DRejection, SafeReject_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected from another
    const fgm::Vector4D actualRejection = a.safeReject(b, true);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from another vector of different numeric
 *       type using @ref fgm::Vector4D::safeReject returns a type-promoted vector.
 */
TEST(Vector4DRejection, SafeReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector4D vec(7, 13, 29, 41);
    constexpr fgm::Vector4D from(2.0, 4.0, 4.0, 2.0);
    constexpr fgm::Vector4D expectedRejection(-6.2, -13.4, 2.6, 27.8);

    // When rejected from another
    const fgm::Vector4D actualRejection = vec.safeReject(from);

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
 * @test Verify that safely rejecting from a parallel vector using static variant of @ref fgm::Vector4D::safeReject
 *       returns a zero vector.
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

    const fgm::Vector4D actualRejection = fgm::Vector4D<float>::safeReject(a, b);

    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref fgm::Vector4D::safeReject returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector4D actualRejection = fgm::Vector4D<TypeParam>::safeReject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref fgm::Vector4D::safeReject with the @p fromNormalized flag enabled returns a non-zero vector with
 *       perpendicular component.
 */
TEST(Vector4DRejection, StaticWrapper_SafeReject_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected from another
    const fgm::Vector4D actualRejection = fgm::Vector4D<float>::safeReject(a, b, true);

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
    constexpr fgm::Vector4D from(2.0, 4.0, 4.0, 2.0);
    constexpr fgm::Vector4D expectedRejection(-6.2, -13.4, 2.6, 27.8);

    // When rejected from another
    const fgm::Vector4D actualRejection = fgm::Vector4D<float>::safeReject(vec, from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from a zero length vector using static variant of @ref fgm::Vector4D::safeReject
 *       returns the same vector.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_SafeReject_FromZeroVectorReturnsSameVector)
{
    constexpr TypeParam zero = TypeParam(0);
    constexpr fgm::Vector4D zeroVec(zero, zero, zero, zero);

    const fgm::Vector4D actualRejection = fgm::Vector4D<TypeParam>::safeReject(this->_vec, zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/** @test Verify that rejection using @ref fgm::Vector4D::safeReject always return floating-point vector. */
TYPED_TEST(Vector4DRejection, SafeReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector4D rejection = this->_vec.safeReject(this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @test Verify that rejection using static variant of @ref fgm::Vector4D::safeReject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_SafeReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector4D rejection = fgm::Vector4D<float>::safeReject(this->_vec, this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @test Verify that the rejection of NaN vector using @ref fgm::Vector4D::safeReject
 *       returns zero vector.
 */
TEST_P(Vector4DRejectionNaNTests, SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec = GetParam();
    const auto& ontoVec = fgm::vec4d::one<float>;

    EXPECT_VEC_ZERO(nanVec.safeReject(ontoVec));
}


/**
 * @test Verify that rejecting onto NaN vector using @ref fgm::Vector4D::safeReject
 *       returns zero vector.
 */
TEST_P(Vector4DRejectionNaNTests, SafeReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec = fgm::vec4d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeReject(ontoNaNVec));
}


/**
 * @test Verify that the rejection of NaN vector using static variant of @ref fgm::Vector4D::safeReject
 *       returns zero vector.
 */
TEST_P(Vector4DRejectionNaNTests, StaticWrapper_SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec = GetParam();
    const auto& ontoVec = fgm::vec4d::one<float>;

    EXPECT_VEC_ZERO(fgm::Vector4D<float>::safeReject(nanVec, ontoVec));
}


/**
 * @test Verify that rejecting onto a NaN vector using static variant of @ref fgm::Vector4D::safeReject
 *       returns zero vector.
 */
TEST_P(Vector4DRejectionNaNTests, StaticWrapper_SafeReject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec = fgm::vec4d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector4D<float>::safeReject(oneVec, ontoNaNVec));
}


/**************************************
 *                                    *
 *        TRY REJECTION TESTS         *
 *                                    *
 **************************************/

/**
 * @test Verify that safely rejecting from a parallel vector using @ref fgm::Vector4D::tryReject
 *       returns a zero vector  and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector4DRejection, TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector4D actualRejection = this->_vec.tryReject(this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from orthogonal using @ref fgm::Vector4D::tryReject
 *       returns the original vector and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector4DRejection, TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 0.0f);
    constexpr fgm::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);
    fgm::OperationStatus flag;

    // When rejected from an orthogonal vector
    const fgm::Vector4D actualRejection = a.tryReject(b, flag);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using @ref fgm::Vector4D::tryReject
 *       returns a non-zero vector with perpendicular component sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector4DRejection, TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector4D actualRejection = this->_vec.tryReject(this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref fgm::Vector4D::tryReject with the
 *       @p fromNormalized flag enabled returns a non-zero vector with perpendicular component
 *       sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector4DRejection, TryReject_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);
    fgm::OperationStatus flag;


    // When rejected from another
    const fgm::Vector4D actualRejection = a.tryReject(b, flag, true);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting a vector from another vector of different numeric
 *       type using @ref fgm::Vector4D::tryReject returns a type-promoted vector
 *       sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector4DRejection, TryReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector4D vec(7, 13, 29, 41);
    constexpr fgm::Vector4D from(2.0, 4.0, 4.0, 2.0);
    constexpr fgm::Vector4D expectedRejection(-6.2, -13.4, 2.6, 27.8);
    fgm::OperationStatus flag;

    // When rejected from another
    const fgm::Vector4D actualRejection = vec.tryReject(from, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a zero vector using @ref fgm::Vector4D::tryReject
 *       returns the same vector and sets flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector4DRejection, TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    constexpr TypeParam zero = TypeParam(0);
    constexpr fgm::Vector4D zeroVec(zero, zero, zero, zero);
    fgm::OperationStatus flag;

    const fgm::Vector4D actualRejection = this->_vec.tryReject(zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that safely rejecting from a parallel vector using static variant of @ref fgm::Vector4D::tryReject
 *       returns a zero vector and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;

    const fgm::Vector4D actualRejection = fgm::Vector4D<TypeParam>::tryReject(this->_vec, this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref fgm::Vector4D::tryReject returns the original vector
 *       and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector4DRejection, StaticWrapper_TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 0.0f);
    constexpr fgm::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);
    fgm::OperationStatus flag;

    const fgm::Vector4D actualRejection = fgm::Vector4D<float>::tryReject(a, b, flag);

    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref fgm::Vector4D::tryReject returns a non-zero vector with perpendicular component
 *       and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector4DRejection,
           StaticWrapper_TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;

    const fgm::Vector4D actualRejection = fgm::Vector4D<TypeParam>::tryReject(this->_vec, this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref fgm::Vector4D::tryReject with the @p fromNormalized flag enabled returns a non-zero vector with
 *       perpendicular component and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector4DRejection, StaticWrapper_TryReject_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    constexpr fgm::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
    constexpr fgm::Vector4D expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);
    fgm::OperationStatus flag;

    // When rejected from another
    const fgm::Vector4D actualRejection = fgm::Vector4D<float>::tryReject(a, b, flag, true);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    // Flag is set to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting a vector from another vector of different numeric type
 *       using static variant of @ref fgm::Vector4D::tryReject returns a type-promoted vector
 *       and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector4DRejection, StaticWrapper_TryReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    constexpr fgm::Vector4D vec(7, 13, 29, 41);
    constexpr fgm::Vector4D from(2.0, 4.0, 4.0, 2.0);
    constexpr fgm::Vector4D expectedRejection(-6.2, -13.4, 2.6, 27.8);
    fgm::OperationStatus flag;

    // When rejected from another
    const fgm::Vector4D actualRejection = fgm::Vector4D<float>::tryReject(vec, from, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    // Flag is set to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a zero length vector using static variant of @ref fgm::Vector4D::tryReject
 *       returns the same vector and sets flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    constexpr TypeParam zero = TypeParam(0);
    constexpr fgm::Vector4D zeroVec(zero, zero, zero, zero);
    fgm::OperationStatus flag;

    const fgm::Vector4D actualRejection = fgm::Vector4D<TypeParam>::tryReject(this->_vec, zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/** @test Verify that rejection using @ref fgm::Vector4D::tryReject always return floating-point vector. */
TYPED_TEST(Vector4DRejection, TryRejectAlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus status;
    [[maybe_unused]] const fgm::Vector4D rejection = this->_vec.tryReject(this->_fromVec, status);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @test Verify that rejection using static variant of @ref fgm::Vector4D::tryReject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector4DRejection, StaticWrapper_TryReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus status;
    [[maybe_unused]] const fgm::Vector4D rejection =
        fgm::Vector4D<float>::tryReject(this->_vec, this->_fromVec, status);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}



/**
 * @test Verify that the rejection of NaN vector using @ref fgm::Vector4D::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector4DRejectionNaNTests, TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec = GetParam();
    const auto& ontoVec = fgm::vec4d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryReject(ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection onto NaN vector using @ref fgm::Vector4D::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector4DRejectionNaNTests, TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec = fgm::vec4d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryReject(ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection of NaN vector using static variant of @ref fgm::Vector4D::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector4DRejectionNaNTests, StaticWrapper_TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec = GetParam();
    const auto& ontoVec = fgm::vec4d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vector4D<float>::tryReject(nanVec, ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection onto NaN vector using static variant of @ref fgm::Vector4D::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector4DRejectionNaNTests, StaticWrapper_TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec = fgm::vec4d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vector4D<float>::tryReject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */