/**
 * @file NormalizationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 28, 2026
 *
 * @brief Verify @ref fgm::Vector4D normalization logic.
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
class Vector4DNormalization: public ::testing::Test
{
    using R = fgm::Magnitude<T>;

protected:
    fgm::Vector4D<T> _vec;
    fgm::Vector4D<R> _expectedUnitVec;

    void SetUp() override
    {
        _vec = { T(14), T(27), T(83), T(52) };
        _expectedUnitVec = { static_cast<R>(0.13650905255670645), static_cast<R>(0.2632674585022196),
                             static_cast<R>(0.8093036687290455), static_cast<R>(0.5070336237820525) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D normalization, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DNormalization, SupportedArithmeticTypes);


template <typename T>
class Vector4DZeroNormalization: public ::testing::Test
{
protected:
    fgm::Vector4D<T> _vec;

    void SetUp() override
    {
        _vec = { T(0), T(0), T(0), T(0) };
    }
};
/** 
 * @brief Test fixture for @ref fgm::Vector4D zero-vector normalization, parameterized by 
 * @ref SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Vector4DZeroNormalization, SupportedArithmeticTypes);


/** @brief Test fixture for @fgm::Vector4D normalization with NaN vectors. */
class Vector4DNormalizationNaNTests: public ::testing::TestWithParam<fgm::Vector4D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vector4DNormalizationNaNTestSuite, Vector4DNormalizationNaNTests,
                         ::testing::Values(fgm::Vector4D<float>(fgm::constants::NaN, 1.0f, 1.0f, 1.0f),
                                           fgm::Vector4D<float>(1.0f, fgm::constants::NaN, 1.0f, 1.0f),
                                           fgm::Vector4D<float>(1.0f, 1.0f, fgm::constants::NaN, 1.0f),
                                           fgm::Vector4D<float>(1.0f, 1.0f, 1.0f, fgm::constants::NaN),
                                           fgm::Vector4D<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN, fgm ::constants::NaN)));



/**
 * @addtogroup T_FGM_Vec4_Normalize
 * @{
 */

/**************************************
 *                                    *
 *        NORMALIZATION TESTS         *
 *                                    *
 **************************************/

/** @test Verify that normalizing a vector using @ref fgm::Vector4D::normalize returns a unit vector. */
TYPED_TEST(Vector4DNormalization, Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector4D normalized = this->_vec.normalize();

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a vector using static variant of @ref fgm::Vector4D::normalize
 *       returns a unit vector.
 */
TYPED_TEST(Vector4DNormalization, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector4D normalized = fgm::Vector4D<TypeParam>::normalize(this->_vec);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a vector using @ref fgm::Vector4D::normalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vector4DNormalization, NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.normalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *     SAFE NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/** @test Verify that normalizing a vector using @ref fgm::Vector4D::safeNormalize returns a unit vector. */
TYPED_TEST(Vector4DNormalization, SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector4D normalized = this->_vec.safeNormalize();
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vector4D::safeNormalize
 *       returns a zero-vector.
 */
TYPED_TEST(Vector4DNormalization, SafeNormalize_ZeroVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::vec4d::zero<TypeParam>.safeNormalize());
}


/**
 * @test Verify that attempting to normalize a NaN vector using @ref fgm::Vector4D::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vector4DNormalization, SafeNormalize_NaNVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::vec4d::nan<float>.safeNormalize());
}


/**
 * @test Verify that normalizing a vector using @ref fgm::Vector4D::safeNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(Vector4DNormalization, SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.safeNormalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @test Verify that normalizing a 4D vector using static variant of @ref fgm::Vector4D::safeNormalize
 *       returns a unit vector.
 */
TYPED_TEST(Vector4DNormalization, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector4D normalized = fgm::Vector4D<TypeParam>::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref fgm::Vector4D::safeNormalize returns a zero-vector.
 */
TYPED_TEST(Vector4DNormalization, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::Vector4D<double>::safeNormalize(fgm::vec4d::zero<TypeParam>));
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector4D::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vector4DNormalization, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    EXPECT_VEC_ZERO(fgm::Vector4D<float>::safeNormalize(fgm::vec4d::nan<float>));
}


/**
 * @test Verify that the normalizing a 4D vector using static variant of @ref fgm::Vector4D::safeNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vector4DNormalization, StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = fgm::Vector4D<TypeParam>::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *      TRY NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/**
 * @test Verify that normalizing a vector using @ref fgm::Vector4D::tryNormalize
 *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector4DNormalization, TryNormalize_NonZeroVectorReturnsUnitVector)
{
    fgm::OperationStatus flag;
    const fgm::Vector4D normalized = this->_vec.tryNormalize(flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vector4D::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector4DNormalization, TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::vec4d::zero<TypeParam>.tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using @ref fgm::Vector4D::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector4DNormalization, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::vec4d::nan<float>.tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that normalizing a vector using @ref fgm::Vector4D::tryNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(Vector4DNormalization, TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const auto normalized = this->_vec.tryNormalize(flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @test Verify that normalizing a 4D vector using static variant of @ref fgm::Vector4D::tryNormalize
 *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector4DNormalization, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vector4D normalized = fgm::Vector4D<TypeParam>::tryNormalize(this->_vec, flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref fgm::Vector4D::tryNormalize returns a zero-vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector4DNormalization, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::vec4d::zero<TypeParam>.tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector4D::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector4DNormalization, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vector4D<float>::tryNormalize(fgm::vec4d::nan<float>, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the normalizing a 4D vector using static variant of @ref fgm::Vector4D::tryNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vector4DNormalization, StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const auto normalized = fgm::Vector4D<TypeParam>::tryNormalize(this->_vec, flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *      NAN NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/**
 * @test Verify that attempting to normalize a NaN vector of @ref fgm::Vector4D::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vector4DNormalizationNaNTests, SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.safeNormalize());
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector4D::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vector4DNormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector4D<ParamType::value_type>::safeNormalize(vec));
}


/**
 * @test Verify that attempting to normalize a NaN vector of @ref fgm::Vector4D::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector4DNormalizationNaNTests, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector4D::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vector4DNormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vector4D<ParamType::value_type>::tryNormalize(vec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */