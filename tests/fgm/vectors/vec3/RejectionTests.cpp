/**
 * @file RejectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vec3 rejection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"



template <typename T>
class Vec3Rejection: public ::testing::Test
{
protected:
    fgm::Vec3<T> _vec;
    fgm::Vec3<T> _parallelVec;
    fgm::Vec3<T> _fromVec;
    fgm::Vec3<T> _expectedRejection;

    void SetUp() override
    {
        _vec               = { T(1), T(2), T(3) };
        _parallelVec       = { T(2), T(4), T(6) };
        _fromVec           = { T(0), T(2), T(0) };
        _expectedRejection = { T(1), T(0), T(3) };
    }
};
/** @brief Test fixture for @ref fgm::Vec3 rejection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec3Rejection, SupportedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Vec3 rejection with NaN vectors. */
class Vec3RejectionNaNTests: public ::testing::TestWithParam<fgm::Vec3<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vec3RejectionTestSuite, Vec3RejectionNaNTests,
                         ::testing::Values(fgm::Vec3<float>(fgm::constants::NaN, 1.0f, 1.0f),
                                           fgm::Vec3<float>(1.0f, fgm::constants::NaN, 1.0f),
                                           fgm::Vec3<float>(1.0f, 1.0f, fgm::constants::NaN),
                                           fgm::Vec3<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                               fgm ::constants::NaN)));



/**
 * @addtogroup T_FGM_Vec3_Rej
 * @{
 */

/** @brief Verify that vector rejection is available at compile time. */
namespace
{
    constexpr fgm::Vec3 vecA(1, 2, 3);
    constexpr fgm::Vec3 vecB(1, 0, 0);
    constexpr auto rej1 = vecA.reject(vecB);
    static_assert(rej1.x() == 0);
    static_assert(rej1.y() == 2);
    static_assert(rej1.z() == 3);

    constexpr auto rej2 = vecA.rejectNorm(vecB);
    static_assert(rej2.x() == 0);
    static_assert(rej2.y() == 2);
    static_assert(rej2.z() == 3);

    constexpr auto rej3 = fgm::Vec3<int>::reject(vecA, vecB);
    static_assert(rej3.x() == 0);
    static_assert(rej3.y() == 2);
    static_assert(rej3.z() == 3);

    constexpr auto rej4 = fgm::Vec3<int>::rejectNorm(vecA, vecB);
    static_assert(rej4.x() == 0);
    static_assert(rej4.y() == 2);
    static_assert(rej4.z() == 3);

    constexpr auto rej5 = vecA.safeReject(vecB);
    static_assert(rej5.x() == 0);
    static_assert(rej5.y() == 2);
    static_assert(rej5.z() == 3);

    constexpr auto rej6 = vecA.safeRejectNorm(vecB);
    static_assert(rej6.x() == 0);
    static_assert(rej6.y() == 2);
    static_assert(rej6.z() == 3);

    constexpr auto rej7 = fgm::Vec3<int>::safeReject(vecA, vecB);
    static_assert(rej7.x() == 0);
    static_assert(rej7.y() == 2);
    static_assert(rej7.z() == 3);

    constexpr auto rej8 = fgm::Vec3<int>::safeRejectNorm(vecA, vecB);
    static_assert(rej8.x() == 0);
    static_assert(rej8.y() == 2);
    static_assert(rej8.z() == 3);

} // namespace


/**************************************
 *                                    *
 *          REJECTION TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that rejecting from a parallel vector using @ref fgm::Vec3::reject returns a zero vector. */
TYPED_TEST(Vec3Rejection, ParallelVectorsReturnsZeroVector)
{
    const fgm::Vec3 actualRejection = this->_vec.reject(this->_parallelVec);
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @brief Verify that rejecting from a vector parallel to x-axis using @ref fgm::Vec3::reject
 *       returns a vector with a zero x-component.
 */
TEST(Vec3Rejection, RejectionFromXAxisReturnsVectorWithZeroXComponent)
{
    // Given an arbitrary vector
    const fgm::Vec3 a(10.0f, 20.0f, 30.0f);
    const fgm::Vec3 xAxis(1.0f, 0.0f, 0.0f);
    const fgm::Vec3 expectedRejection(0.0f, 20.0f, 30.0f);

    // When rejected from x-axis
    const fgm::Vec3 actualRejection = a.reject(xAxis);

    // Then, the resultant vector has zero x-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting from a vector parallel to y-axis using @ref fgm::Vec3::reject
 *       returns a vector with a zero y-component.
 */
TEST(Vec3Rejection, RejectionFromYAxisReturnsVectorWithZeroYComponent)
{
    // Given an arbitrary vector
    const fgm::Vec3 a(10.0f, 20.0f, 30.0f);
    const fgm::Vec3 yAxis(0.0f, 1.0f, 0.0f);
    const fgm::Vec3 expectedRejection(10.0f, 0.0f, 30.0f);

    // When rejected from y-axis
    const fgm::Vec3 actualRejection = a.reject(yAxis);

    // Then, the resultant vector has zero y-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting from a vector parallel to z-axis using @ref fgm::Vec3::reject
 *       returns a vector with a zero z-component.
 */
TEST(Vec3Rejection, RejectionFromZAxisReturnsVectorWithZeroZComponent)
{
    // Given an arbitrary vector
    const fgm::Vec3 a(10.0f, 20.0f, 30.0f);
    const fgm::Vec3 zAxis(0.0f, 0.0f, 1.0f);
    const fgm::Vec3 expectedRejection(10.0f, 20.0f, 0.0f);

    // When rejected from z-axis
    const fgm::Vec3 actualRejection = a.reject(zAxis);

    // Then, the resultant vector has zero z-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @brief Verify that rejecting an orthogonal using @ref fgm::Vec3::reject returns the original vector. */
TEST(Vec3Rejection, OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const fgm::Vec3 a(1.0f, 2.0f, 0.0f);
    const fgm::Vec3 b(0.0f, 0.0f, 1.0f);

    // When rejected on to an orthogonal vector
    const fgm::Vec3 actualRejection = a.reject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @brief Verify that rejecting from a non-orthogonal vector using @ref fgm::Vec3::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec3Rejection, NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vec3 actualRejection = this->_vec.reject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting from a non-orthogonal vector using static variant of @ref fgm::Vec3::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec3Rejection, StaticWrapper_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vec3 actualRejection = fgm::Vec3<TypeParam>::reject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting from an orthogonal unit vector using @ref fgm::Vec3::rejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vec3Rejection, RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vec3 b(1.0f, 0.0f, 0.0f);
    const fgm::Vec3 expectedRejection(0.0f, 2.0f, 3.0f);

    // When rejected from another
    const fgm::Vec3 actualRejection = a.rejectNorm(b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting from an orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vec3::reject returns a non-zero vector with perpendicular components.
 */
TEST(Vec3Rejection, RejectionFromVectorInOppositeDirectionReturnsVectorWithPerpendicularComponents)
{
    // Given an arbitrary vector
    const fgm::Vec3 a(4.0f, 4.0f, 4.0f);
    const fgm::Vec3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const fgm::Vec3 expectedRejection(4.0f, 4.0f, 0.0f);

    // When rejected from a vector in opposite direction
    const fgm::Vec3 actualRejection = a.reject(negativeZAxis);

    // Then, the resultant vector has components perpendicular to the `from` vector in the same direction.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting a vector from another vector of different numeric type using @ref fgm::Vec3::reject
 *       returns a type-promoted vector.
 */
TEST(Vec3Rejection, MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vec3 vec(7, 13, 29);
    const fgm::Vec3 from(2.0, 4.0, 4.0);
    const fgm::Vec3 expectedRejection(-3.11111111111111, -7.22222222222222, 8.77777777777777);

    // When reject from another
    const fgm::Vec3 actualRejection = vec.reject(from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting from an orthogonal unit vector using static variant of @ref fgm::Vec3::rejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vec3Rejection, StaticWrapper_RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vec3 b(1.0f, 0.0f, 0.0f);
    const fgm::Vec3 expectedRejection(0.0f, 2.0f, 3.0f);

    // When rejected from another
    const fgm::Vec3 actualRejection = fgm::Vec3<float>::rejectNorm(a, b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @brief Verify that rejection using @ref fgm::Vec3::reject always return floating-point vector. */
TYPED_TEST(Vec3Rejection, Reject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vec3 rejection = this->_vec.reject(this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @brief Verify that rejection using static variant of @ref fgm::Vec3::reject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec3Rejection, StaticWrapper_Reject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vec3 rejection = fgm::Vec3<TypeParam>::reject(this->_vec, this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


#ifdef ENABLE_DEBUG_TESTS

/**
 * @brief Verify that rejecting a vector from a zero vector triggers assert in debug mode.
 */
TYPED_TEST(Vec3Rejection, FromZeroVectorTriggersAssertionInCallback)
{
    const fgm::Vec3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.reject(zeroVec)), "");
}


/**
 * @brief Verify that rejecting a vector from a zero vector using static variant of @ref fgm::Vec3::reject
 *        triggers assert in debug mode.
 */
TYPED_TEST(Vec3Rejection, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
{
    const fgm::Vec3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Vec3<TypeParam>::reject(this->_vec, zeroVec)), "");
}

#endif



/**************************************
 *                                    *
 *       SAFE REJECTION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that safely rejecting from a parallel vector using @ref fgm::Vec3::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(Vec3Rejection, SafeReject_ParallelVectorsReturnsZeroVector)
{
    const fgm::Vec3 actualRejection = this->_vec.safeReject(this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @brief Verify that safely rejecting from orthogonal using @ref fgm::Vec3::safeReject
 *       returns the original vector.
 */
TEST(Vec3Rejection, SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const fgm::Vec3 a(1.0f, 2.0f, 0.0f);
    const fgm::Vec3 b(0.0f, 0.0f, 1.0f);

    // When rejected from an orthogonal vector
    const fgm::Vec3 actualRejection = a.safeReject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @brief Verify that safely rejecting from a non-orthogonal vector using @ref fgm::Vec3::safeReject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec3Rejection, SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vec3 actualRejection = this->_vec.safeReject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @brief Verify that safely rejecting from an orthogonal unit vector using @ref fgm::Vec3::safeRejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vec3Rejection, SafeReject_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vec3 b(1.0f, 0.0f, 0.0f);
    const fgm::Vec3 expectedRejection(0.0f, 2.0f, 3.0f);

    // When rejected from another
    const fgm::Vec3 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that safely rejecting a NaN vector from a non-orthogonal unit vector using
 *       @ref fgm::Vec3::safeRejectNorm returns a zero vector.
 */
TEST(Vec3Rejection, SafeRejectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const fgm::Vec3 a(1.0f, fgm::constants::NaN, 3.0f);
    const fgm::Vec3 b(1.0f, 0.0f, 0.0f);

    // When the vector is rejected onto the normalized vector
    const fgm::Vec3 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @brief Verify that safely rejecting from a NaN vector using @ref fgm::Vec3::safeRejectNorm returns a zero vector.
 */
TEST(Vec3Rejection, SafeRejectNorm_FromNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const fgm::Vec3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vec3 b(1.0f, fgm::constants::NaN, 0.0f);

    // When the vector is rejected from a NaN vector
    const fgm::Vec3 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}



/**
 * @brief Verify that safely rejecting a vector from another vector of different numeric
 *       type using @ref fgm::Vec3::safeReject returns a type-promoted vector.
 */
TEST(Vec3Rejection, SafeReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vec3 vec(7, 13, 29);
    const fgm::Vec3 from(2.0, 4.0, 4.0);
    const fgm::Vec3 expectedRejection(-3.11111111111111, -7.22222222222222, 8.77777777777777);

    // When rejected from another
    const fgm::Vec3 actualRejection = vec.safeReject(from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that safely rejecting from a zero vector using @ref fgm::Vec3::safeReject
 *       returns the same vector.
 */
TYPED_TEST(Vec3Rejection, SafeReject_FromZeroVectorReturnsSameVector)
{
    const fgm::Vec3 zeroVec = fgm::Vec3<TypeParam>::zero();

    const fgm::Vec3 actualRejection = this->_vec.safeReject(zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/**
 * @brief Verify that safely rejecting from a parallel vector using static variant of @ref fgm::Vec3::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(Vec3Rejection, StaticWrapper_SafeReject_ParallelVectorsReturnsZeroVector)
{
    const fgm::Vec3 actualRejection = fgm::Vec3<TypeParam>::safeReject(this->_vec, this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @brief Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref fgm::Vec3::safeReject returns the original vector.
 */
TEST(Vec3Rejection, StaticWrapper_SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    const fgm::Vec3 a(1.0f, 2.0f, 0.0f);
    const fgm::Vec3 b(0.0f, 0.0f, 1.0f);

    const fgm::Vec3 actualRejection = fgm::Vec3<float>::safeReject(a, b);

    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @brief Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref fgm::Vec3::safeReject returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec3Rejection, StaticWrapper_SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vec3 actualRejection = fgm::Vec3<TypeParam>::safeReject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @brief Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref fgm::Vec3::safeRejectNorm returns a non-zero vector with perpendicular component.
 */
TEST(Vec3Rejection, StaticWrapper_SafeRejectNorm_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vec3 b(1.0f, 0.0f, 0.0f);
    const fgm::Vec3 expectedRejection(0.0f, 2.0f, 3.0f);

    // When rejected from another
    const fgm::Vec3 actualRejection = fgm::Vec3<float>::safeRejectNorm(a, b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that safely rejecting a NaN vector from a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vec3::safeRejectNorm returns a zero vector.
 */
TEST(Vec3Rejection, StaticWrapper_SafeRejectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const fgm::Vec3 a(1.0f, fgm::constants::NaN, 3.0f);
    const fgm::Vec3 b(1.0f, 0.0f, 0.0f);

    // When the vector is rejected onto the normalized vector
    const fgm::Vec3 actualRejection = fgm::Vec3<float>::safeRejectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @brief Verify that safely rejecting from a NaN vector using static variant of
 *       @ref fgm::Vec3::safeRejectNorm returns a zero vector.
 */
TEST(Vec3Rejection, StaticWrapper_SafeRejectNorm_FromNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const fgm::Vec3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vec3 b(1.0f, fgm::constants::NaN, 0.0f);

    // When the vector is rejected from a NaN vector
    const fgm::Vec3 actualRejection = fgm::Vec3<float>::safeRejectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @brief Verify that safely rejecting a vector from another vector of different numeric type
 *       using static variant of @ref fgm::Vec3::safeReject returns a type-promoted vector.
 */
TEST(Vec3Rejection, StaticWrapper_SafeReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vec3 vec(7, 13, 29);
    const fgm::Vec3 from(2.0, 4.0, 4.0);
    const fgm::Vec3 expectedRejection(-3.11111111111111, -7.22222222222222, 8.77777777777777);

    // When rejected from another
    const fgm::Vec3 actualRejection = fgm::Vec3<int>::safeReject(vec, from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that safely rejecting from a zero length vector using static variant of @ref fgm::Vec3::safeReject
 *       returns the same vector.
 */
TYPED_TEST(Vec3Rejection, StaticWrapper_SafeReject_FromZeroVectorReturnsSameVector)
{
    const fgm::Vec3 zeroVec = fgm::Vec3<TypeParam>::zero();

    const fgm::Vec3 actualRejection = fgm::Vec3<TypeParam>::safeReject(this->_vec, zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/** @brief Verify that rejection using @ref fgm::Vec3::safeReject always return floating-point vector. */
TYPED_TEST(Vec3Rejection, SafeReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vec3 rejection = this->_vec.safeReject(this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @brief Verify that rejection using static variant of @ref fgm::Vec3::safeReject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec3Rejection, StaticWrapper_SafeReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vec3 rejection = fgm::Vec3<TypeParam>::safeReject(this->_vec, this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @brief Verify that the rejection of NaN vector using @ref fgm::Vec3::safeReject
 *       returns zero vector.
 */
TEST_P(Vec3RejectionNaNTests, SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::Vec3<float>::one();

    EXPECT_VEC_ZERO(nanVec.safeReject(ontoVec));
}


/**
 * @brief Verify that rejecting onto NaN vector using @ref fgm::Vec3::safeReject
 *       returns zero vector.
 */
TEST_P(Vec3RejectionNaNTests, SafeReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeReject(ontoNaNVec));
}


/**
 * @brief Verify that the rejection of NaN vector using static variant of @ref fgm::Vec3::safeReject
 *       returns zero vector.
 */
TEST_P(Vec3RejectionNaNTests, StaticWrapper_SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::Vec3<float>::one();

    EXPECT_VEC_ZERO(fgm::Vec3<float>::safeReject(nanVec, ontoVec));
}


/**
 * @brief Verify that rejecting onto a NaN vector using static variant of @ref fgm::Vec3::safeReject
 *       returns zero vector.
 */
TEST_P(Vec3RejectionNaNTests, StaticWrapper_SafeReject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = fgm::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vec3<float>::safeReject(oneVec, ontoNaNVec));
}


/**************************************
 *                                    *
 *        TRY REJECTION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that safely rejecting from a parallel vector using @ref fgm::Vec3::tryReject
 *       returns a zero vector  and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec3Rejection, TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vec3 actualRejection = this->_vec.tryReject(this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from orthogonal using @ref fgm::Vec3::tryReject
 *       returns the original vector and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vec3Rejection, TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector
    const fgm::Vec3 a(1.0f, 2.0f, 0.0f);
    const fgm::Vec3 b(0.0f, 0.0f, 1.0f);
    fgm::OperationStatus flag;

    // When rejected from an orthogonal vector
    const fgm::Vec3 actualRejection = a.tryReject(b, flag);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from a non-orthogonal vector using @ref fgm::Vec3::tryReject
 *       returns a non-zero vector with perpendicular component sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec3Rejection, TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vec3 actualRejection = this->_vec.tryReject(this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from an orthogonal unit vector using @ref fgm::Vec3::tryRejectNorm
 *       returns a non-zero vector and with perpendicular component sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vec3Rejection, TryRejectNorm_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vec3 b(1.0f, 0.0f, 0.0f);
    const fgm::Vec3 expectedRejection(0.0f, 2.0f, 3.0f);
    fgm::OperationStatus flag;


    // When rejected from another
    const fgm::Vec3 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting NaN vector from an orthogonal unit vector using @ref fgm::Vec3::tryRejectNorm
 *       returns a zero vector and sets flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec3Rejection, TryRejectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec3 a(1.0f, fgm::constants::NaN, 3.0f);
    const fgm::Vec3 b(1.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;


    // When rejected from another
    const fgm::Vec3 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that safely rejecting from an NaN vector using @ref fgm::Vec3::tryRejectNorm
 *       returns a zero vector and sets flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec3Rejection, TryRejectNorm_FromNaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vec3 b(1.0f, fgm::constants::NaN, 0.0f);
    fgm::OperationStatus flag;


    // When rejected from another
    const fgm::Vec3 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that safely rejecting a vector from another vector of different numeric
 *       type using @ref fgm::Vec3::tryReject returns a type-promoted vector
 *       sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vec3Rejection, TryReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vec3 vec(7, 13, 29);
    const fgm::Vec3 from(2.0, 4.0, 4.0);
    const fgm::Vec3 expectedRejection(-3.11111111111111, -7.22222222222222, 8.77777777777777);
    fgm::OperationStatus flag;

    // When rejected from another
    const fgm::Vec3 actualRejection = vec.tryReject(from, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from a zero vector using @ref fgm::Vec3::tryReject
 *       returns the same vector and sets flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec3Rejection, TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    const fgm::Vec3 zeroVec = fgm::Vec3<TypeParam>::zero();
    fgm::OperationStatus flag;

    const fgm::Vec3 actualRejection = this->_vec.tryReject(zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that safely rejecting from a parallel vector using static variant of @ref fgm::Vec3::tryReject
 *       returns a zero vector and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec3Rejection, StaticWrapper_TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;

    const fgm::Vec3 actualRejection = fgm::Vec3<TypeParam>::tryReject(this->_vec, this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref fgm::Vec3::tryReject returns the original vector
 *       and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vec3Rejection, StaticWrapper_TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    const fgm::Vec3 a(1.0f, 2.0f, 0.0f);
    const fgm::Vec3 b(0.0f, 0.0f, 1.0f);
    fgm::OperationStatus flag;

    const fgm::Vec3 actualRejection = fgm::Vec3<float>::tryReject(a, b, flag);

    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref fgm::Vec3::tryReject returns a non-zero vector with perpendicular component
 *       and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec3Rejection, StaticWrapper_TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;

    const fgm::Vec3 actualRejection = fgm::Vec3<TypeParam>::tryReject(this->_vec, this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref fgm::Vec2::tryRejectNorm returns a non-zero vector and with perpendicular component sets flag to
 *       @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vec3Rejection, StaticWrapper_TryRejectNorm_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vec3 b(1.0f, 0.0f, 0.0f);
    const fgm::Vec3 expectedRejection(0.0f, 2.0f, 3.0f);
    fgm::OperationStatus flag;

    // When rejected from another
    const fgm::Vec3 actualRejection = fgm::Vec3<float>::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    // Flag is set to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting NaN vector from an orthogonal unit vector using static variant of
 *       @ref fgm::Vec3::tryRejectNorm returns a zero vector and sets flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec3Rejection, StaticWrapper_TryRejectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec3 a(1.0f, fgm::constants::NaN, 3.0f);
    const fgm::Vec3 b(1.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;


    // When rejected from another
    const fgm::Vec3 actualRejection = fgm::Vec3<float>::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/**
 * @brief Verify that safely rejecting from an NaN vector using static variant of @ref fgm::Vec3::tryRejectNorm
 *       returns a zero vector and sets flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec3Rejection, StaticWrapper_TryRejectNorm_FromNaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vec3 a(1.0f, 2.0f, 3.0f);
    const fgm::Vec3 b(1.0f, fgm::constants::NaN, 0.0f);
    fgm::OperationStatus flag;


    // When rejected from another
    const fgm::Vec3 actualRejection = fgm::Vec3<float>::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that safely rejecting a vector from another vector of different numeric type
 *       using static variant of @ref fgm::Vec3::tryReject returns a type-promoted vector
 *       and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vec3Rejection, StaticWrapper_TryReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vec3 vec(7, 13, 29);
    const fgm::Vec3 from(2.0, 4.0, 4.0);
    const fgm::Vec3 expectedRejection(-3.11111111111111, -7.22222222222222, 8.77777777777777);
    fgm::OperationStatus flag;

    // When rejected from another
    const fgm::Vec3 actualRejection = fgm::Vec3<int>::tryReject(vec, from, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    // Flag is set to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from a zero length vector using static variant of @ref fgm::Vec3::tryReject
 *       returns the same vector and sets flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec3Rejection, StaticWrapper_TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    const fgm::Vec3 zeroVec = fgm::Vec3<TypeParam>::zero();
    fgm::OperationStatus flag;

    const fgm::Vec3 actualRejection = fgm::Vec3<TypeParam>::tryReject(this->_vec, zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/** @brief Verify that rejection using @ref fgm::Vec3::tryReject always return floating-point vector. */
TYPED_TEST(Vec3Rejection, TryRejectAlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus status;
    [[maybe_unused]] const fgm::Vec3 rejection = this->_vec.tryReject(this->_fromVec, status);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @brief Verify that rejection using static variant of @ref fgm::Vec3::tryReject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec3Rejection, StaticWrapper_TryReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus status;
    [[maybe_unused]] const fgm::Vec3 rejection =
        fgm::Vec3<TypeParam>::tryReject(this->_vec, this->_fromVec, status);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}



/**
 * @brief Verify that the rejection of NaN vector using @ref fgm::Vec3::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3RejectionNaNTests, TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::Vec3<float>::one();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryReject(ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that the rejection onto NaN vector using @ref fgm::Vec3::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3RejectionNaNTests, TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryReject(ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that the rejection of NaN vector using static variant of @ref fgm::Vec3::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3RejectionNaNTests, StaticWrapper_TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::Vec3<float>::one();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vec3<float>::tryReject(nanVec, ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that the rejection onto NaN vector using static variant of @ref fgm::Vec3::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3RejectionNaNTests, StaticWrapper_TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vec3<float>::tryReject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
