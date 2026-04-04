/**
 * @file NormalizationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verifies @ref fgm::Vector2D normalization logic.
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
class Vector2DNormalization: public ::testing::Test
{
    using R = fgm::Magnitude<T>;

protected:
    fgm::Vector2D<T> _vec;
    fgm::Vector2D<R> _expectedUnitVec;

    void SetUp() override
    {
        _vec = { T(14), T(27) };
        _expectedUnitVec = { static_cast<R>(0.46031716445500037), static_cast<R>(0.8877545314489294) };
    }
};
/** @brief Test fixture for @ref fgm::Vector2D normalization, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector2DNormalization, SupportedArithmeticTypes);


template <typename T>
class Vector2DZeroNormalization: public ::testing::Test
{
protected:
    fgm::Vector2D<T> _vec;

    void SetUp() override
    {
        _vec = { T(0), T(0) };
    }
};
/**
 * @brief Test fixture for @ref fgm::Vector2D zero-vector normalization, parameterized by
 *        @ref SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Vector2DZeroNormalization, SupportedArithmeticTypes);


/** @brief Test fixture for @fgm::Vector2D normalization with NaN vectors. */
class Vector2DNormalizationNaNTests: public ::testing::TestWithParam<fgm::Vector2D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vector2DNormalizationNaNTestSuite, Vector2DNormalizationNaNTests,
                         ::testing::Values(fgm::Vector2D<float>(fgm::constants::NaN, 1.0f),
                                           fgm::Vector2D<float>(1.0f, fgm::constants::NaN), 
                                           fgm::Vector2D<float>(fgm ::constants::NaN, fgm::constants::NaN)));



/**
 * @addtogroup T_FGM_Vec2_Normalize
 * @{
 */

/**************************************
 *                                    *
 *        NORMALIZATION TESTS         *
 *                                    *
 **************************************/

/** @test Verify that normalizing a vector using @ref fgm::Vector2D::normalize returns a unit vector. */
TYPED_TEST(Vector2DNormalization, Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector2D normalized = this->_vec.normalize();

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a vector using static variant of @ref fgm::Vector2D::normalize
 *       returns a unit vector.
 */
TYPED_TEST(Vector2DNormalization, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector2D normalized = fgm::Vector2D<TypeParam>::normalize(this->_vec);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a vector using @ref fgm::Vector2D::normalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vector2DNormalization, NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.normalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *     SAFE NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/** @test Verify that normalizing a vector using @ref fgm::Vector2D::safeNormalize returns a unit vector. */
TYPED_TEST(Vector2DNormalization, SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector2D normalized = this->_vec.safeNormalize();
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vector2D::safeNormalize
 *       returns a zero-vector.
 */
TYPED_TEST(Vector2DNormalization, SafeNormalize_ZeroVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::vec2d::zero<TypeParam>.safeNormalize());
}


/**
 * @test Verify that attempting to normalize a NaN vector using @ref fgm::Vector2D::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vector2DNormalization, SafeNormalize_NaNVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::vec2d::nan<float>.safeNormalize());
}


/**
 * @test Verify that normalizing a vector using @ref fgm::Vector2D::safeNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(Vector2DNormalization, SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.safeNormalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @test Verify that normalizing a 2D vector using static variant of @ref fgm::Vector2D::safeNormalize
 *       returns a unit vector.
 */
TYPED_TEST(Vector2DNormalization, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector2D normalized = fgm::Vector2D<TypeParam>::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref fgm::Vector2D::safeNormalize returns a zero-vector.
 */
TYPED_TEST(Vector2DNormalization, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::Vector2D<double>::safeNormalize(fgm::vec2d::zero<TypeParam>));
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector2D::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vector2DNormalization, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::Vector2D<float>::safeNormalize(fgm::vec2d::nan<float>));
}


/**
 * @test Verify that the normalizing a 2D vector using static variant of @ref fgm::Vector2D::safeNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vector2DNormalization, StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = fgm::Vector2D<TypeParam>::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *      TRY NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/**
 * @test Verify that normalizing a vector using @ref fgm::Vector2D::tryNormalize
 *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector2DNormalization, TryNormalize_NonZeroVectorReturnsUnitVector)
{
    fgm::OperationStatus flag;
    const fgm::Vector2D normalized = this->_vec.tryNormalize(flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vector2D::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector2DNormalization, TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::vec2d::zero<TypeParam>.tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using @ref fgm::Vector2D::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector2DNormalization, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::vec2d::nan<float>.tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that normalizing a vector using @ref fgm::Vector2D::tryNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(Vector2DNormalization, TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const auto normalized = this->_vec.tryNormalize(flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @test Verify that normalizing a 2D vector using static variant of @ref fgm::Vector2D::tryNormalize
 *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector2DNormalization, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector2D normalized = fgm::Vector2D<TypeParam>::tryNormalize(this->_vec, flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref fgm::Vector2D::tryNormalize returns a zero-vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector2DNormalization, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::vec2d::zero<TypeParam>.tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector2D::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector2DNormalization, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vector2D<float>::tryNormalize(fgm::vec2d::nan<float>, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the normalizing a 2D vector using static variant of @ref fgm::Vector2D::tryNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vector2DNormalization, StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const auto normalized = fgm::Vector2D<TypeParam>::tryNormalize(this->_vec, flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *      NAN NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/**
 * @test Verify that attempting to normalize a NaN vector of @ref fgm::Vector2D::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vector2DNormalizationNaNTests, SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.safeNormalize());
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector2D::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vector2DNormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector2D<ParamType::value_type>::safeNormalize(vec));
}


/**
 * @test Verify that attempting to normalize a NaN vector of @ref fgm::Vector2D::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector2DNormalizationNaNTests, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector2D::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector2DNormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector2D<ParamType::value_type>::tryNormalize(vec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */