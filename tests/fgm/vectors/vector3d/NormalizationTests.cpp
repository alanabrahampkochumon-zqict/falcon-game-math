/**
 * @file NormalizationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vector3 normalization logic.
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
class Vector3Normalization: public ::testing::Test
{
    using R = fgm::Magnitude<T>;

protected:
    fgm::Vector3<T> _vec;
    fgm::Vector3<R> _expectedUnitVec;

    void SetUp() override
    {
        _vec             = { T(14), T(27), T(83) };
        _expectedUnitVec = { static_cast<R>(0.1583767155508236), static_cast<R>(0.30544080856230266),
                             static_cast<R>(0.9389476707655972) };
    }
};
/** @brief Test fixture for @ref fgm::Vector3 normalization, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector3Normalization, SupportedArithmeticTypes);


template <typename T>
class Vector3ZeroNormalization: public ::testing::Test
{
protected:
    fgm::Vector3<T> _vec;

    void SetUp() override { _vec = { T(0), T(0), T(0) }; }
};
/**
 * @brief Test fixture for @ref fgm::Vector3 zero-vector normalization, parameterized by
 *        @ref SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Vector3ZeroNormalization, SupportedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Vector3 normalization with NaN vectors. */
class Vector3NormalizationNaNTests: public ::testing::TestWithParam<fgm::Vector3<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vector3NormalizationNaNTestSuite, Vector3NormalizationNaNTests,
                         ::testing::Values(fgm::Vector3<float>(fgm::constants::NaN, 1.0f, 1.0f),
                                           fgm::Vector3<float>(1.0f, fgm::constants::NaN, 1.0f),
                                           fgm::Vector3<float>(1.0f, 1.0f, fgm::constants::NaN),
                                           fgm::Vector3<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                               fgm ::constants::NaN)));



/**
 * @addtogroup T_FGM_Vec3_Normalize
 * @{
 */

/** @brief Verify that vector normalization operations are available at compile time. */
namespace
{
    // TODO: Add static tests after making sqrt constexpr
    // constexpr fgm::Vector3 Vec(14, 27, 83);
    // constexpr auto norm = Vec.normalize();
} // namespace


/**************************************
 *                                    *
 *        NORMALIZATION TESTS         *
 *                                    *
 **************************************/

/** @brief Verify that normalizing a vector using @ref fgm::Vector3::normalize returns a unit vector. */
TYPED_TEST(Vector3Normalization, Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector3 normalized = this->_vec.normalize();

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @brief Verify that normalizing a vector using static variant of @ref fgm::Vector3::normalize
 *       returns a unit vector.
 */
TYPED_TEST(Vector3Normalization, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector3 normalized = fgm::Vector3<TypeParam>::normalize(this->_vec);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @brief Verify that normalizing a vector using @ref fgm::Vector3::normalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vector3Normalization, NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.normalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


#ifdef ENABLE_DEBUG_TESTS
/**
 * @brief Verify that normalizing a vector with zero magnitude triggers assert in debug mode.
 */
TYPED_TEST(Vector3Normalization, ZeroMagnitudeTriggersAssertInDebugMode)
{
    const fgm::Vector3<TypeParam> zVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(zVec.normalize()), "");
}


/**
 * @brief Verify that normalizing a vector with zero magnitude using static variant of fgm::Vector4::normalize triggers
 *        assert in debug mode.
 */
TYPED_TEST(Vector3Normalization, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const fgm::Vector3<TypeParam> zVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Vector3<TypeParam>::normalize(zVec)), "");
}

#endif



/**************************************
 *                                    *
 *     SAFE NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/** @brief Verify that normalizing a vector using @ref fgm::Vector3::safeNormalize returns a unit vector. */
TYPED_TEST(Vector3Normalization, SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector3 normalized = this->_vec.safeNormalize();
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @brief Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vector3::safeNormalize
 *       returns a zero-vector.
 */
TYPED_TEST(Vector3Normalization, SafeNormalize_ZeroVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::Vector3<TypeParam>::ZERO().safeNormalize());
}


/**
 * @brief Verify that attempting to normalize a NaN vector using @ref fgm::Vector3::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vector3Normalization, SafeNormalize_NaNVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::Vector3<float>::QNAN().safeNormalize());
}


/**
 * @brief Verify that normalizing a vector using @ref fgm::Vector3::safeNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(Vector3Normalization, SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.safeNormalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @brief Verify that normalizing a 3D vector using static variant of @ref fgm::Vector3::safeNormalize
 *       returns a unit vector.
 */
TYPED_TEST(Vector3Normalization, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector3 normalized = fgm::Vector3<TypeParam>::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @brief Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref fgm::Vector3::safeNormalize returns a zero-vector.
 */
TYPED_TEST(Vector3Normalization, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::Vector3<TypeParam>::safeNormalize(fgm::Vector3<TypeParam>::ZERO()));
}


/**
 * @brief Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector3::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vector3Normalization, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::Vector3<float>::safeNormalize(fgm::Vector3<float>::QNAN()));
}


/**
 * @brief Verify that the normalizing a 3D vector using static variant of @ref fgm::Vector3::safeNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vector3Normalization, StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = fgm::Vector3<TypeParam>::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *      TRY NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/**
 * @brief Verify that normalizing a vector using @ref fgm::Vector3::tryNormalize
 *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector3Normalization, TryNormalize_NonZeroVectorReturnsUnitVector)
{
    fgm::OperationStatus flag;
    const fgm::Vector3 normalized = this->_vec.tryNormalize(flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vector3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector3Normalization, TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vector3<TypeParam>::ZERO().tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that attempting to normalize a NaN vector using @ref fgm::Vector3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3Normalization, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vector3<float>::QNAN().tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that normalizing a vector using @ref fgm::Vector3::tryNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(Vector3Normalization, TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const auto normalized = this->_vec.tryNormalize(flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @brief Verify that normalizing a 3D vector using static variant of @ref fgm::Vector3::tryNormalize
 *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector3Normalization, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector3 normalized = fgm::Vector3<TypeParam>::tryNormalize(this->_vec, flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref fgm::Vector3::tryNormalize returns a zero-vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector3Normalization, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vector3<TypeParam>::ZERO().tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector3Normalization, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vector3<float>::tryNormalize(fgm::Vector3<float>::QNAN(), flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that the normalizing a 3D vector using static variant of @ref fgm::Vector3::tryNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vector3Normalization, StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const auto normalized = fgm::Vector3<TypeParam>::tryNormalize(this->_vec, flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *      NAN NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/**
 * @brief Verify that attempting to normalize a NaN vector of @ref fgm::Vector3::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vector3NormalizationNaNTests, SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.safeNormalize());
}


/**
 * @brief Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector3::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vector3NormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector3<ParamType::value_type>::safeNormalize(vec));
}


/**
 * @brief Verify that attempting to normalize a NaN vector of @ref fgm::Vector3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3NormalizationNaNTests, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector3NormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector3<ParamType::value_type>::tryNormalize(vec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
