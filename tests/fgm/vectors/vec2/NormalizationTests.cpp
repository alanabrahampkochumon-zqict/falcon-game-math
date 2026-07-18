/**
 * @file NormalizationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vec2 normalization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vec2Normalization: public ::testing::Test
{
    using R = fgm::Magnitude<T>;

protected:
    fgm::Vec2<T> _vec;
    fgm::Vec2<R> _expectedUnitVec;

    void SetUp() override
    {
        _vec             = { T(14), T(27) };
        _expectedUnitVec = { static_cast<R>(0.46031716445500037), static_cast<R>(0.8877545314489294) };
    }
};
/** @brief Test fixture for @ref fgm::Vec2 normalization, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec2Normalization, SupportedArithmeticTypes);


template <typename T>
class Vec2ZeroNormalization: public ::testing::Test
{
protected:
    fgm::Vec2<T> _vec;

    void SetUp() override { _vec = { T(0), T(0) }; }
};
/**
 * @brief Test fixture for @ref fgm::Vec2 zero-vector normalization, parameterized by
 *        @ref SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Vec2ZeroNormalization, SupportedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Vec2 normalization with NaN vectors. */
class Vec2NormalizationNaNTests: public ::testing::TestWithParam<fgm::Vec2<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vec2NormalizationNaNTestSuite, Vec2NormalizationNaNTests,
                         ::testing::Values(fgm::Vec2<float>(fgm::constants::NaN, 1.0f),
                                           fgm::Vec2<float>(1.0f, fgm::constants::NaN),
                                           fgm::Vec2<float>(fgm ::constants::NaN, fgm::constants::NaN)));



/**
 * @addtogroup T_FGM_Vec2_Normalize
 * @{
 */

/** @brief Verify that vector normalization operations are available at compile time. */
namespace
{
    // TODO: Add static tests after making sqrt constexpr
    // constexpr fgm::Vec2 Vec(14, 27);
    // constexpr auto norm = Vec.normalize();
}


/**************************************
 *                                    *
 *        NORMALIZATION TESTS         *
 *                                    *
 **************************************/

/** @brief Verify that normalizing a vector using @ref fgm::Vec2::normalize returns a unit vector. */
TYPED_TEST(Vec2Normalization, Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vec2 normalized = this->_vec.normalize();

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @brief Verify that normalizing a vector using static variant of @ref fgm::Vec2::normalize
 *       returns a unit vector.
 */
TYPED_TEST(Vec2Normalization, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vec2 normalized = fgm::Vec2<TypeParam>::normalize(this->_vec);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @brief Verify that normalizing a vector using @ref fgm::Vec2::normalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vec2Normalization, NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.normalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


#ifdef ENABLE_DEBUG_TESTS
/**
 * @brief Verify that normalizing a vector with zero magnitude triggers assert in debug mode.
 */
TYPED_TEST(Vec2Normalization, ZeroMagnitudeTriggersAssertInDebugMode)
{
    const fgm::Vec2<TypeParam> zVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(zVec.normalize()), "");
}


/**
 * @brief Verify that normalizing a vector with zero magnitude using static variant of fgm::Vec2::normalize triggers
 *        assert in debug mode.
 */
TYPED_TEST(Vec2Normalization, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const fgm::Vec2<TypeParam> zVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Vec2<TypeParam>::normalize(zVec)), "");
}

#endif


/**************************************
 *                                    *
 *     SAFE NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/** @brief Verify that normalizing a vector using @ref fgm::Vec2::safeNormalize returns a unit vector. */
TYPED_TEST(Vec2Normalization, SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vec2 normalized = this->_vec.safeNormalize();
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @brief Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vec2::safeNormalize
 *       returns a zero-vector.
 */
TYPED_TEST(Vec2Normalization, SafeNormalize_ZeroVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::Vec2<TypeParam>::zero().safeNormalize());
}


/**
 * @brief Verify that attempting to normalize a NaN vector using @ref fgm::Vec2::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vec2Normalization, SafeNormalize_NaNVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::Vec2<float>::qnan().safeNormalize());
}


/**
 * @brief Verify that normalizing a vector using @ref fgm::Vec2::safeNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(Vec2Normalization, SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.safeNormalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @brief Verify that normalizing a 2D vector using static variant of @ref fgm::Vec2::safeNormalize
 *       returns a unit vector.
 */
TYPED_TEST(Vec2Normalization, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vec2 normalized = fgm::Vec2<TypeParam>::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @brief Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref fgm::Vec2::safeNormalize returns a zero-vector.
 */
TYPED_TEST(Vec2Normalization, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::Vec2<TypeParam>::safeNormalize(fgm::Vec2<TypeParam>::zero()));
}


/**
 * @brief Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vec2::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vec2Normalization, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::Vec2<float>::safeNormalize(fgm::Vec2<float>::qnan()));
}


/**
 * @brief Verify that the normalizing a 2D vector using static variant of @ref fgm::Vec2::safeNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vec2Normalization, StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = fgm::Vec2<TypeParam>::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *      TRY NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/**
 * @brief Verify that normalizing a vector using @ref fgm::Vec2::tryNormalize
 *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2Normalization, TryNormalize_NonZeroVectorReturnsUnitVector)
{
    fgm::OperationStatus flag;
    const fgm::Vec2 normalized = this->_vec.tryNormalize(flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2Normalization, TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec2<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that attempting to normalize a NaN vector using @ref fgm::Vec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec2Normalization, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec2<float>::qnan().tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that normalizing a vector using @ref fgm::Vec2::tryNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(Vec2Normalization, TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const auto normalized = this->_vec.tryNormalize(flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @brief Verify that normalizing a 2D vector using static variant of @ref fgm::Vec2::tryNormalize
 *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2Normalization, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vec2 normalized = fgm::Vec2<TypeParam>::tryNormalize(this->_vec, flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref fgm::Vec2::tryNormalize returns a zero-vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2Normalization, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec2<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec2Normalization, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec2<float>::tryNormalize(fgm::Vec2<float>::qnan(), flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that the normalizing a 2D vector using static variant of @ref fgm::Vec2::tryNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vec2Normalization, StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const auto normalized = fgm::Vec2<TypeParam>::tryNormalize(this->_vec, flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *      NAN NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/**
 * @brief Verify that attempting to normalize a NaN vector of @ref fgm::Vec2::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vec2NormalizationNaNTests, SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.safeNormalize());
}


/**
 * @brief Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vec2::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vec2NormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vec2<ParamType::value_type>::safeNormalize(vec));
}


/**
 * @brief Verify that attempting to normalize a NaN vector of @ref fgm::Vec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2NormalizationNaNTests, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2NormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vec2<ParamType::value_type>::tryNormalize(vec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
