/**
 * @file NormalizationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vec3 normalization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"



/**
 * @addtogroup T_FGM_Vec3_Normalize
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec3 normalization.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3NormalizationTests: public testing::Test
    {
        using R = fgm::Magnitude<T>;

    protected:
        fgm::Vec3<T> _vec;
        fgm::Vec3<R> _expectedUnitVec;

        void SetUp() override
        {
            _vec             = { T(14), T(27), T(83) };
            _expectedUnitVec = { static_cast<R>(0.1583767155508236), static_cast<R>(0.30544080856230266),
                                 static_cast<R>(0.9389476707655972) };
        }
    };
    TYPED_TEST_SUITE(Vec3NormalizationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec3 normalization with zero vectors.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3ZeroNormalizationTests: public testing::Test
    {
    protected:
        fgm::Vec3<T> _vec;

        void SetUp() override { _vec = { T(0), T(0), T(0) }; }
    };
    TYPED_TEST_SUITE(Vec3ZeroNormalization, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec3 normalization with NaN vectors.
     */
    class Vec3NormalizationNaNTests: public testing::TestWithParam<fgm::Vec3<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec3NormalizationNaNVectors, Vec3NormalizationNaNTests,
                             ::testing::Values(fgm::Vec3<float>(fgm::constants::NaN, 1.0f, 1.0f),
                                               fgm::Vec3<float>(1.0f, fgm::constants::NaN, 1.0f),
                                               fgm::Vec3<float>(1.0f, 1.0f, fgm::constants::NaN),
                                               fgm::Vec3<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN)));



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // TODO: Add static tests after making sqrt constexpr
        // constexpr fgm::Vec3 Vec(14, 27, 83);
        // constexpr auto norm = Vec.normalize();
    } // namespace static_tests
} // namespace



/**************************************
 *        NORMALIZATION TESTS         *
 **************************************/

/** @test Verify that normalizing a vector using @ref fgm::Vec3::normalize returns a unit vector. */
TYPED_TEST(Vec3NormalizationTests, Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vec3 normalized = this->_vec.normalize();

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a vector using static variant of @ref fgm::Vec3::normalize
 *       returns a unit vector.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vec3 normalized = fgm::Vec3<TypeParam>::normalize(this->_vec);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a vector using @ref fgm::Vec3::normalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vec3NormalizationTests, NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.normalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}



/**************************************
 *     SAFE NORMALIZATION TESTS       *
 **************************************/

/** @test Verify that normalizing a vector using @ref fgm::Vec3::safeNormalize returns a unit vector. */
TYPED_TEST(Vec3NormalizationTests, SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vec3 normalized = this->_vec.safeNormalize();
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TYPED_TEST(Vec3NormalizationTests, SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(fgm::Vec3<TypeParam>::zero().safeNormalize()); }


/**
 * @test Verify that attempting to normalize a NaN vector using @ref fgm::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vec3Normalization, SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(fgm::Vec3<float>::qnan().safeNormalize()); }


/**
 * @test Verify that normalizing a vector using @ref fgm::Vec3::safeNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(Vec3NormalizationTests, SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.safeNormalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @test Verify that normalizing a 3D vector using static variant of @ref fgm::Vec3::safeNormalize
 *       returns a unit vector.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vec3 normalized = fgm::Vec3<TypeParam>::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref fgm::Vec3::safeNormalize returns a zero-vector.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(fgm::Vec3<TypeParam>::safeNormalize(fgm::Vec3<TypeParam>::zero())); }


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vec3Normalization, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(fgm::Vec3<float>::safeNormalize(fgm::Vec3<float>::qnan())); }


/**
 * @test Verify that the normalizing a 3D vector using static variant of @ref fgm::Vec3::safeNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = fgm::Vec3<TypeParam>::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *      TRY NORMALIZATION TESTS       *
 **************************************/

/**
 * @test Verify that normalizing a vector using @ref fgm::Vec3::tryNormalize
 *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec3NormalizationTests, TryNormalize_NonZeroVectorReturnsUnitVector)
{
    fgm::OperationStatus flag;
    const fgm::Vec3 normalized = this->_vec.tryNormalize(flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec3NormalizationTests, TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec3<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using @ref fgm::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec3Normalization, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec3<float>::qnan().tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that normalizing a vector using @ref fgm::Vec3::tryNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(Vec3NormalizationTests, TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const auto normalized = this->_vec.tryNormalize(flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @test Verify that normalizing a 3D vector using static variant of @ref fgm::Vec3::tryNormalize
 *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vec3 normalized = fgm::Vec3<TypeParam>::tryNormalize(this->_vec, flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref fgm::Vec3::tryNormalize returns a zero-vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec3<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec3Normalization, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec3<float>::tryNormalize(fgm::Vec3<float>::qnan(), flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the normalizing a 3D vector using static variant of @ref fgm::Vec3::tryNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const auto normalized = fgm::Vec3<TypeParam>::tryNormalize(this->_vec, flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *      NAN NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/**
 * @test Verify that attempting to normalize a NaN vector of @ref fgm::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vec3NormalizationNaNTests, SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.safeNormalize());
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vec3NormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vec3<ParamType::value_type>::safeNormalize(vec));
}


/**
 * @test Verify that attempting to normalize a NaN vector of @ref fgm::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3NormalizationNaNTests, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3NormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vec3<ParamType::value_type>::tryNormalize(vec, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
