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



/**
 * @addtogroup T_FGM_Vec2_Normalize
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec2 normalization.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2NormalizationTests: public testing::Test
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
    TYPED_TEST_SUITE(Vec2NormalizationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec2 normalization with zero vectors.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2NormalizationZeroTests: public testing::Test
    {
    protected:
        fgm::Vec2<T> _vec;

        void SetUp() override { _vec = { T(0), T(0) }; }
    };
    TYPED_TEST_SUITE(Vec2NormalizationZeroTests, SupportedArithmeticTypes);




    /**
     * @brief Test fixture for @ref Vec2 normalization with NaN vectors.
     */
    class Vec2NormalizationNaNTests: public testing::TestWithParam<fgm::Vec2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec2NormalizationNaNVectors, Vec2NormalizationNaNTests,
                             ::testing::Values(fgm::Vec2<float>(fgm::constants::NaN, 1.0f),
                                               fgm::Vec2<float>(1.0f, fgm::constants::NaN),
                                               fgm::Vec2<float>(fgm ::constants::NaN, fgm::constants::NaN)));



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // TODO: Add static tests after making sqrt constexpr
        // constexpr fgm::Vec2 Vec(14, 27);
        // constexpr auto norm = Vec.normalize();
    }
} // namespace



/**************************************
 *        NORMALIZATION TESTS         *
 **************************************/

TYPED_TEST(Vec2NormalizationTests, Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vec2 normalized = this->_vec.normalize();
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


TYPED_TEST(Vec2NormalizationTests, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vec2 normalized = fgm::Vec2<TypeParam>::normalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


TYPED_TEST(Vec2NormalizationTests, NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.normalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}




/**************************************
 *                                    *
 *     SAFE NORMALIZATION TESTS       *
 *                                    *
 **************************************/

TYPED_TEST(Vec2NormalizationTests, SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vec2 normalized = this->_vec.safeNormalize();
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


TYPED_TEST(Vec2NormalizationTests, SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(fgm::Vec2<TypeParam>::zero().safeNormalize()); }


TEST(Vec2NormalizationTests, SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(fgm::Vec2<float>::qnan().safeNormalize()); }


TYPED_TEST(Vec2NormalizationTests, SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.safeNormalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


TYPED_TEST(Vec2NormalizationTests, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vec2 normalized = fgm::Vec2<TypeParam>::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


TYPED_TEST(Vec2NormalizationTests, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(fgm::Vec2<TypeParam>::safeNormalize(fgm::Vec2<TypeParam>::zero())); }


TEST(Vec2NormalizationTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(fgm::Vec2<float>::safeNormalize(fgm::Vec2<float>::qnan())); }


TYPED_TEST(Vec2NormalizationTests, StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = fgm::Vec2<TypeParam>::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}



/**************************************
 *      TRY NORMALIZATION TESTS       *
 **************************************/

/**
 * @test Verify that normalizing a vector using @ref fgm::Vec2::tryNormalize
 *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2NormalizationTests, TryNormalize_NonZeroVectorReturnsUnitVector)
{
    fgm::OperationStatus flag;
    const fgm::Vec2 normalized = this->_vec.tryNormalize(flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2NormalizationTests, TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec2<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using @ref fgm::Vec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec2NormalizationTests, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec2<float>::qnan().tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that normalizing a vector using @ref fgm::Vec2::tryNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(Vec2NormalizationTests, TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] fgm::OperationStatus flag;
    [[maybe_unused]] const auto normalized = this->_vec.tryNormalize(flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @test Verify that normalizing a 2D vector using static variant of @ref fgm::Vec2::tryNormalize
 *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2NormalizationTests, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Vec2 normalized = fgm::Vec2<TypeParam>::tryNormalize(this->_vec, flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref fgm::Vec2::tryNormalize returns a zero-vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2NormalizationTests, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec2<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec2NormalizationTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec2<float>::tryNormalize(fgm::Vec2<float>::qnan(), flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the normalizing a 2D vector using static variant of @ref fgm::Vec2::tryNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vec2NormalizationTests, StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
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
 * @test Verify that attempting to normalize a NaN vector of @ref fgm::Vec2::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vec2NormalizationNaNTests, SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.safeNormalize());
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vec2::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vec2NormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(fgm::Vec2<ParamType::value_type>::safeNormalize(vec));
}


/**
 * @test Verify that attempting to normalize a NaN vector of @ref fgm::Vec2::tryNormalize
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
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vec2::tryNormalize
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
