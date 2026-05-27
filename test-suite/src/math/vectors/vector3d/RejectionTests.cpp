/**
 * @file RejectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vector3D rejection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3DTestSetup.h"



template <typename T>
class Vector3DRejection: public ::testing::Test
{
protected:
    fgm::Vector3D<T> _vec;
    fgm::Vector3D<T> _parallelVec;
    fgm::Vector3D<T> _fromVec;
    fgm::Vector3D<T> _expectedRejection;

    void SetUp() override
    {
        _vec               = { T(1), T(2), T(3) };
        _parallelVec       = { T(2), T(4), T(6) };
        _fromVec           = { T(0), T(2), T(0) };
        _expectedRejection = { T(1), T(0), T(3) };
    }
};
/** @brief Test fixture for @ref fgm::Vector3D rejection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector3DRejection, SupportedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Vector3D rejection with NaN vectors. */
class Vector3DRejectionNaNTests: public ::testing::TestWithParam<fgm::Vector3D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vector3DRejectionTestSuite, Vector3DRejectionNaNTests,
                         ::testing::Values(fgm::Vector3D<float>(fgm::constants::NaN, 1.0f, 1.0f),
                                           fgm::Vector3D<float>(1.0f, fgm::constants::NaN, 1.0f),
                                           fgm::Vector3D<float>(1.0f, 1.0f, fgm::constants::NaN),
                                           fgm::Vector3D<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN)));



/**
 * @addtogroup T_FGM_Vec3_Rej
 * @{
 */

/** @brief Verify that vector rejection is available at compile time. */
namespace
{
    constexpr fgm::Vector3D vecA(1, 2, 3);
    constexpr fgm::Vector3D vecB(1, 0, 0);
    constexpr auto rej1 = vecA.reject(vecB);
    static_assert(rej1.x() == 0);
    static_assert(rej1.y() == 2);
    static_assert(rej1.z() == 3);

    constexpr auto rej2 = vecA.rejectNorm(vecB);
    static_assert(rej2.x() == 0);
    static_assert(rej2.y() == 2);
    static_assert(rej2.z() == 3);

    constexpr auto rej3 = fgm::Vector3D<int>::reject(vecA, vecB);
    static_assert(rej3.x() == 0);
    static_assert(rej3.y() == 2);
    static_assert(rej3.z() == 3);

    constexpr auto rej4 = fgm::Vector3D<int>::rejectNorm(vecA, vecB);
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

    constexpr auto rej7 = fgm::Vector3D<int>::safeReject(vecA, vecB);
    static_assert(rej7.x() == 0);
    static_assert(rej7.y() == 2);
    static_assert(rej7.z() == 3);

    constexpr auto rej8 = fgm::Vector3D<int>::safeRejectNorm(vecA, vecB);
    static_assert(rej8.x() == 0);
    static_assert(rej8.y() == 2);
    static_assert(rej8.z() == 3);

} // namespace


/**************************************
 *                                    *
 *          REJECTION TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that rejecting from a parallel vector using @ref fgm::Vector3D::reject returns a zero vector. */
TYPED_TEST(Vector3DRejection, ParallelVectorsReturnsZeroVector)
{
    const fgm::Vector3D actualRejection = this->_vec.reject(this->_parallelVec);
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @brief Verify that rejecting from a vector parallel to x-axis using @ref fgm::Vector3D::reject
 *       returns a vector with a zero x-component.
 */
TEST(Vector3DRejection, RejectionFromXAxisReturnsVectorWithZeroXComponent)
{
    // Given an arbitrary vector
    const fgm::Vector3D a(10.0f, 20.0f, 30.0f);
    const fgm::Vector3D xAxis(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedRejection(0.0f, 20.0f, 30.0f);

    // When rejected from x-axis
    const fgm::Vector3D actualRejection = a.reject(xAxis);

    // Then, the resultant vector has zero x-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting from a vector parallel to y-axis using @ref fgm::Vector3D::reject
 *       returns a vector with a zero y-component.
 */
TEST(Vector3DRejection, RejectionFromYAxisReturnsVectorWithZeroYComponent)
{
    // Given an arbitrary vector
    const fgm::Vector3D a(10.0f, 20.0f, 30.0f);
    const fgm::Vector3D yAxis(0.0f, 1.0f, 0.0f);
    const fgm::Vector3D expectedRejection(10.0f, 0.0f, 30.0f);

    // When rejected from y-axis
    const fgm::Vector3D actualRejection = a.reject(yAxis);

    // Then, the resultant vector has zero y-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting from a vector parallel to z-axis using @ref fgm::Vector3D::reject
 *       returns a vector with a zero z-component.
 */
TEST(Vector3DRejection, RejectionFromZAxisReturnsVectorWithZeroZComponent)
{
    // Given an arbitrary vector
    const fgm::Vector3D a(10.0f, 20.0f, 30.0f);
    const fgm::Vector3D zAxis(0.0f, 0.0f, 1.0f);
    const fgm::Vector3D expectedRejection(10.0f, 20.0f, 0.0f);

    // When rejected from z-axis
    const fgm::Vector3D actualRejection = a.reject(zAxis);

    // Then, the resultant vector has zero z-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @brief Verify that rejecting an orthogonal using @ref fgm::Vector3D::reject returns the original vector. */
TEST(Vector3DRejection, OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const fgm::Vector3D a(1.0f, 2.0f, 0.0f);
    const fgm::Vector3D b(0.0f, 0.0f, 1.0f);

    // When rejected on to an orthogonal vector
    const fgm::Vector3D actualRejection = a.reject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @brief Verify that rejecting from a non-orthogonal vector using @ref fgm::Vector3D::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector3DRejection, NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector3D actualRejection = this->_vec.reject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting from a non-orthogonal vector using static variant of @ref fgm::Vector3D::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector3DRejection, StaticWrapper_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector3D actualRejection = fgm::Vector3D<TypeParam>::reject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting from an orthogonal unit vector using @ref fgm::Vector3D::rejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vector3DRejection, RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedRejection(0.0f, 2.0f, 3.0f);

    // When rejected from another
    const fgm::Vector3D actualRejection = a.rejectNorm(b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting from an orthogonal vector pointing in the opposite direction
 *       using @ref fgm::Vector3D::reject returns a non-zero vector with perpendicular components.
 */
TEST(Vector3DRejection, RejectionFromVectorInOppositeDirectionReturnsVectorWithPerpendicularComponents)
{
    // Given an arbitrary vector
    const fgm::Vector3D a(4.0f, 4.0f, 4.0f);
    const fgm::Vector3D negativeZAxis(0.0f, 0.0f, -1.0f);
    const fgm::Vector3D expectedRejection(4.0f, 4.0f, 0.0f);

    // When rejected from a vector in opposite direction
    const fgm::Vector3D actualRejection = a.reject(negativeZAxis);

    // Then, the resultant vector has components perpendicular to the `from` vector in the same direction.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting a vector from another vector of different numeric type using @ref fgm::Vector3D::reject
 *       returns a type-promoted vector.
 */
TEST(Vector3DRejection, MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3D vec(7, 13, 29);
    const fgm::Vector3D from(2.0, 4.0, 4.0);
    const fgm::Vector3D expectedRejection(-3.11111111111111, -7.22222222222222, 8.77777777777777);

    // When reject from another
    const fgm::Vector3D actualRejection = vec.reject(from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that rejecting from an orthogonal unit vector using static variant of @ref fgm::Vector3D::rejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vector3DRejection, StaticWrapper_RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedRejection(0.0f, 2.0f, 3.0f);

    // When rejected from another
    const fgm::Vector3D actualRejection = fgm::Vector3D<float>::rejectNorm(a, b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @brief Verify that rejection using @ref fgm::Vector3D::reject always return floating-point vector. */
TYPED_TEST(Vector3DRejection, Reject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector3D rejection = this->_vec.reject(this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @brief Verify that rejection using static variant of @ref fgm::Vector3D::reject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector3DRejection, StaticWrapper_Reject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector3D rejection = fgm::Vector3D<TypeParam>::reject(this->_vec, this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


#ifdef ENABLE_DEBUG_TESTS

/**
 * @brief Verify that rejecting a vector from a zero vector triggers assert in debug mode.
 */
TYPED_TEST(Vector3DRejection, FromZeroVectorTriggersAssertionInCallback)
{
    const fgm::Vector3D<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.reject(zeroVec)), "");
}


/**
 * @brief Verify that rejecting a vector from a zero vector using static variant of @ref fgm::Vector3D::reject
 *        triggers assert in debug mode.
 */
TYPED_TEST(Vector3DRejection, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
{
    const fgm::Vector3D<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Vector3D<TypeParam>::reject(this->_vec, zeroVec)), "");
}

#endif



/**************************************
 *                                    *
 *       SAFE REJECTION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that safely rejecting from a parallel vector using @ref fgm::Vector3D::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(Vector3DRejection, SafeReject_ParallelVectorsReturnsZeroVector)
{
    const fgm::Vector3D actualRejection = this->_vec.safeReject(this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @brief Verify that safely rejecting from orthogonal using @ref fgm::Vector3D::safeReject
 *       returns the original vector.
 */
TEST(Vector3DRejection, SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const fgm::Vector3D a(1.0f, 2.0f, 0.0f);
    const fgm::Vector3D b(0.0f, 0.0f, 1.0f);

    // When rejected from an orthogonal vector
    const fgm::Vector3D actualRejection = a.safeReject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @brief Verify that safely rejecting from a non-orthogonal vector using @ref fgm::Vector3D::safeReject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector3DRejection, SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector3D actualRejection = this->_vec.safeReject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @brief Verify that safely rejecting from an orthogonal unit vector using @ref fgm::Vector3D::safeRejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vector3DRejection, SafeReject_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedRejection(0.0f, 2.0f, 3.0f);

    // When rejected from another
    const fgm::Vector3D actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that safely rejecting a NaN vector from a non-orthogonal unit vector using
 *       @ref fgm::Vector3D::safeRejectNorm returns a zero vector.
 */
TEST(Vector3DRejection, SafeRejectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const fgm::Vector3D a(1.0f, fgm::constants::NaN, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);

    // When the vector is rejected onto the normalized vector
    const fgm::Vector3D actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @brief Verify that safely rejecting from a NaN vector using @ref fgm::Vector3D::safeRejectNorm returns a zero vector.
 */
TEST(Vector3DRejection, SafeRejectNorm_FromNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, fgm::constants::NaN, 0.0f);

    // When the vector is rejected from a NaN vector
    const fgm::Vector3D actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}



/**
 * @brief Verify that safely rejecting a vector from another vector of different numeric
 *       type using @ref fgm::Vector3D::safeReject returns a type-promoted vector.
 */
TEST(Vector3DRejection, SafeReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3D vec(7, 13, 29);
    const fgm::Vector3D from(2.0, 4.0, 4.0);
    const fgm::Vector3D expectedRejection(-3.11111111111111, -7.22222222222222, 8.77777777777777);

    // When rejected from another
    const fgm::Vector3D actualRejection = vec.safeReject(from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that safely rejecting from a zero vector using @ref fgm::Vector3D::safeReject
 *       returns the same vector.
 */
TYPED_TEST(Vector3DRejection, SafeReject_FromZeroVectorReturnsSameVector)
{
    const fgm::Vector3D zeroVec = fgm::vec3d::zero<TypeParam>;

    const fgm::Vector3D actualRejection = this->_vec.safeReject(zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/**
 * @brief Verify that safely rejecting from a parallel vector using static variant of @ref fgm::Vector3D::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(Vector3DRejection, StaticWrapper_SafeReject_ParallelVectorsReturnsZeroVector)
{
    const fgm::Vector3D actualRejection = fgm::Vector3D<TypeParam>::safeReject(this->_vec, this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @brief Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref fgm::Vector3D::safeReject returns the original vector.
 */
TEST(Vector3DRejection, StaticWrapper_SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    const fgm::Vector3D a(1.0f, 2.0f, 0.0f);
    const fgm::Vector3D b(0.0f, 0.0f, 1.0f);

    const fgm::Vector3D actualRejection = fgm::Vector3D<float>::safeReject(a, b);

    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @brief Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref fgm::Vector3D::safeReject returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vector3DRejection, StaticWrapper_SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const fgm::Vector3D actualRejection = fgm::Vector3D<TypeParam>::safeReject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @brief Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref fgm::Vector3D::safeRejectNorm returns a non-zero vector with perpendicular component.
 */
TEST(Vector3DRejection, StaticWrapper_SafeRejectNorm_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedRejection(0.0f, 2.0f, 3.0f);

    // When rejected from another
    const fgm::Vector3D actualRejection = fgm::Vector3D<float>::safeRejectNorm(a, b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that safely rejecting a NaN vector from a non-orthogonal unit vector using static variant of
 *       @ref fgm::Vector3D::safeRejectNorm returns a zero vector.
 */
TEST(Vector3DRejection, StaticWrapper_SafeRejectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const fgm::Vector3D a(1.0f, fgm::constants::NaN, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);

    // When the vector is rejected onto the normalized vector
    const fgm::Vector3D actualRejection = fgm::Vector3D<float>::safeRejectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @brief Verify that safely rejecting from a NaN vector using static variant of
 *       @ref fgm::Vector3D::safeRejectNorm returns a zero vector.
 */
TEST(Vector3DRejection, StaticWrapper_SafeRejectNorm_FromNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, fgm::constants::NaN, 0.0f);

    // When the vector is rejected from a NaN vector
    const fgm::Vector3D actualRejection = fgm::Vector3D<float>::safeRejectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @brief Verify that safely rejecting a vector from another vector of different numeric type
 *       using static variant of @ref fgm::Vector3D::safeReject returns a type-promoted vector.
 */
TEST(Vector3DRejection, StaticWrapper_SafeReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3D vec(7, 13, 29);
    const fgm::Vector3D from(2.0, 4.0, 4.0);
    const fgm::Vector3D expectedRejection(-3.11111111111111, -7.22222222222222, 8.77777777777777);

    // When rejected from another
    const fgm::Vector3D actualRejection = fgm::Vector3D<int>::safeReject(vec, from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @brief Verify that safely rejecting from a zero length vector using static variant of @ref fgm::Vector3D::safeReject
 *       returns the same vector.
 */
TYPED_TEST(Vector3DRejection, StaticWrapper_SafeReject_FromZeroVectorReturnsSameVector)
{
    const fgm::Vector3D zeroVec = fgm::vec3d::zero<TypeParam>;

    const fgm::Vector3D actualRejection = fgm::Vector3D<TypeParam>::safeReject(this->_vec, zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/** @brief Verify that rejection using @ref fgm::Vector3D::safeReject always return floating-point vector. */
TYPED_TEST(Vector3DRejection, SafeReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector3D rejection = this->_vec.safeReject(this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @brief Verify that rejection using static variant of @ref fgm::Vector3D::safeReject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector3DRejection, StaticWrapper_SafeReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const fgm::Vector3D rejection = fgm::Vector3D<TypeParam>::safeReject(this->_vec, this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @brief Verify that the rejection of NaN vector using @ref fgm::Vector3D::safeReject
 *       returns zero vector.
 */
TEST_P(Vector3DRejectionNaNTests, SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec3d::one<float>;

    EXPECT_VEC_ZERO(nanVec.safeReject(ontoVec));
}


/**
 * @brief Verify that rejecting onto NaN vector using @ref fgm::Vector3D::safeReject
 *       returns zero vector.
 */
TEST_P(Vector3DRejectionNaNTests, SafeReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec3d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeReject(ontoNaNVec));
}


/**
 * @brief Verify that the rejection of NaN vector using static variant of @ref fgm::Vector3D::safeReject
 *       returns zero vector.
 */
TEST_P(Vector3DRejectionNaNTests, StaticWrapper_SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec3d::one<float>;

    EXPECT_VEC_ZERO(fgm::Vector3D<float>::safeReject(nanVec, ontoVec));
}


/**
 * @brief Verify that rejecting onto a NaN vector using static variant of @ref fgm::Vector3D::safeReject
 *       returns zero vector.
 */
TEST_P(Vector3DRejectionNaNTests, StaticWrapper_SafeReject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = fgm::vec3d::one<float>;
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector3D<float>::safeReject(oneVec, ontoNaNVec));
}


/**************************************
 *                                    *
 *        TRY REJECTION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that safely rejecting from a parallel vector using @ref fgm::Vector3D::tryReject
 *       returns a zero vector  and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector3DRejection, TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector3D actualRejection = this->_vec.tryReject(this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from orthogonal using @ref fgm::Vector3D::tryReject
 *       returns the original vector and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3DRejection, TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector
    const fgm::Vector3D a(1.0f, 2.0f, 0.0f);
    const fgm::Vector3D b(0.0f, 0.0f, 1.0f);
    fgm::OperationStatus flag;

    // When rejected from an orthogonal vector
    const fgm::Vector3D actualRejection = a.tryReject(b, flag);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from a non-orthogonal vector using @ref fgm::Vector3D::tryReject
 *       returns a non-zero vector with perpendicular component sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector3DRejection, TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector3D actualRejection = this->_vec.tryReject(this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from an orthogonal unit vector using @ref fgm::Vector3D::tryRejectNorm
 *       returns a non-zero vector and with perpendicular component sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3DRejection, TryRejectNorm_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedRejection(0.0f, 2.0f, 3.0f);
    fgm::OperationStatus flag;


    // When rejected from another
    const fgm::Vector3D actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting NaN vector from an orthogonal unit vector using @ref fgm::Vector3D::tryRejectNorm
 *       returns a zero vector and sets flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3DRejection, TryRejectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, fgm::constants::NaN, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;


    // When rejected from another
    const fgm::Vector3D actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that safely rejecting from an NaN vector using @ref fgm::Vector3D::tryRejectNorm
 *       returns a zero vector and sets flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3DRejection, TryRejectNorm_FromNaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, fgm::constants::NaN, 0.0f);
    fgm::OperationStatus flag;


    // When rejected from another
    const fgm::Vector3D actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that safely rejecting a vector from another vector of different numeric
 *       type using @ref fgm::Vector3D::tryReject returns a type-promoted vector
 *       sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3DRejection, TryReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3D vec(7, 13, 29);
    const fgm::Vector3D from(2.0, 4.0, 4.0);
    const fgm::Vector3D expectedRejection(-3.11111111111111, -7.22222222222222, 8.77777777777777);
    fgm::OperationStatus flag;

    // When rejected from another
    const fgm::Vector3D actualRejection = vec.tryReject(from, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from a zero vector using @ref fgm::Vector3D::tryReject
 *       returns the same vector and sets flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector3DRejection, TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    const fgm::Vector3D zeroVec = fgm::vec3d::zero<TypeParam>;
    fgm::OperationStatus flag;

    const fgm::Vector3D actualRejection = this->_vec.tryReject(zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that safely rejecting from a parallel vector using static variant of @ref fgm::Vector3D::tryReject
 *       returns a zero vector and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector3DRejection, StaticWrapper_TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;

    const fgm::Vector3D actualRejection = fgm::Vector3D<TypeParam>::tryReject(this->_vec, this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref fgm::Vector3D::tryReject returns the original vector
 *       and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3DRejection, StaticWrapper_TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    const fgm::Vector3D a(1.0f, 2.0f, 0.0f);
    const fgm::Vector3D b(0.0f, 0.0f, 1.0f);
    fgm::OperationStatus flag;

    const fgm::Vector3D actualRejection = fgm::Vector3D<float>::tryReject(a, b, flag);

    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref fgm::Vector3D::tryReject returns a non-zero vector with perpendicular component
 *       and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector3DRejection,
           StaticWrapper_TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    fgm::OperationStatus flag;

    const fgm::Vector3D actualRejection = fgm::Vector3D<TypeParam>::tryReject(this->_vec, this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref fgm::Vector2D::tryRejectNorm returns a non-zero vector and with perpendicular component sets flag to
 *       @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3DRejection, StaticWrapper_TryRejectNorm_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    const fgm::Vector3D expectedRejection(0.0f, 2.0f, 3.0f);
    fgm::OperationStatus flag;

    // When rejected from another
    const fgm::Vector3D actualRejection = fgm::Vector3D<float>::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    // Flag is set to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting NaN vector from an orthogonal unit vector using static variant of
 *       @ref fgm::Vector3D::tryRejectNorm returns a zero vector and sets flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3DRejection, StaticWrapper_TryRejectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, fgm::constants::NaN, 3.0f);
    const fgm::Vector3D b(1.0f, 0.0f, 0.0f);
    fgm::OperationStatus flag;


    // When rejected from another
    const fgm::Vector3D actualRejection = fgm::Vector3D<float>::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/**
 * @brief Verify that safely rejecting from an NaN vector using static variant of @ref fgm::Vector3D::tryRejectNorm
 *       returns a zero vector and sets flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3DRejection, StaticWrapper_TryRejectNorm_FromNaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const fgm::Vector3D a(1.0f, 2.0f, 3.0f);
    const fgm::Vector3D b(1.0f, fgm::constants::NaN, 0.0f);
    fgm::OperationStatus flag;


    // When rejected from another
    const fgm::Vector3D actualRejection = fgm::Vector3D<float>::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that safely rejecting a vector from another vector of different numeric type
 *       using static variant of @ref fgm::Vector3D::tryReject returns a type-promoted vector
 *       and sets flag to @ref fgm::OperationStatus::SUCCESS.
 */
TEST(Vector3DRejection, StaticWrapper_TryReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const fgm::Vector3D vec(7, 13, 29);
    const fgm::Vector3D from(2.0, 4.0, 4.0);
    const fgm::Vector3D expectedRejection(-3.11111111111111, -7.22222222222222, 8.77777777777777);
    fgm::OperationStatus flag;

    // When rejected from another
    const fgm::Vector3D actualRejection = fgm::Vector3D<int>::tryReject(vec, from, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    // Flag is set to SUCCESS
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that safely rejecting from a zero length vector using static variant of @ref fgm::Vector3D::tryReject
 *       returns the same vector and sets flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector3DRejection, StaticWrapper_TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    const fgm::Vector3D zeroVec = fgm::vec3d::zero<TypeParam>;
    fgm::OperationStatus flag;

    const fgm::Vector3D actualRejection = fgm::Vector3D<TypeParam>::tryReject(this->_vec, zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/** @brief Verify that rejection using @ref fgm::Vector3D::tryReject always return floating-point vector. */
TYPED_TEST(Vector3DRejection, TryRejectAlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus status;
    [[maybe_unused]] const fgm::Vector3D rejection = this->_vec.tryReject(this->_fromVec, status);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @brief Verify that rejection using static variant of @ref fgm::Vector3D::tryReject
 *       always return floating-point vector.
 */
TYPED_TEST(Vector3DRejection, StaticWrapper_TryReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] fgm::OperationStatus status;
    [[maybe_unused]] const fgm::Vector3D rejection =
        fgm::Vector3D<TypeParam>::tryReject(this->_vec, this->_fromVec, status);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}



/**
 * @brief Verify that the rejection of NaN vector using @ref fgm::Vector3D::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3DRejectionNaNTests, TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec3d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryReject(ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that the rejection onto NaN vector using @ref fgm::Vector3D::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3DRejectionNaNTests, TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec3d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryReject(ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that the rejection of NaN vector using static variant of @ref fgm::Vector3D::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3DRejectionNaNTests, StaticWrapper_TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = fgm::vec3d::one<float>;
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vector3D<float>::tryReject(nanVec, ontoVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that the rejection onto NaN vector using static variant of @ref fgm::Vector3D::tryReject
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3DRejectionNaNTests, StaticWrapper_TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = fgm::vec3d::one<float>;
    const auto& ontoNaNVec = GetParam();
    fgm::OperationStatus flag;

    EXPECT_VEC_ZERO(fgm::Vector3D<float>::tryReject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
