/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref fgm::Vec3 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "Vec3TestSetup.h"



/**
 * @addtogroup T_FGM_Vec3_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Vec3UtilityParams
    {
        fgm::Vec3<T> vec;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref fgm::Vec3 Infinity Checking.
     */
    class Vec3InfCheckerTests: public testing::TestWithParam<Vec3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec3UtilsInfVectors, Vec3InfCheckerTests,
                         ::testing::Values(Vec3UtilityParams{ fgm::Vec3(fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                                           Vec3UtilityParams{ fgm::Vec3(1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                                           Vec3UtilityParams{ fgm::Vec3(1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                                           Vec3UtilityParams{ fgm::Vec3(fgm::constants::INFINITY_F,
                                                                        fgm::constants::INFINITY_F,
                                                                        fgm::constants::INFINITY_F),
                                                              true },
                                           Vec3UtilityParams{ fgm::Vec3(1.0f, 1.0f, 1.0f), false }));


    /**
         * @brief Test fixture for @ref fgm::Vec3 NaN Checking.
         */
    class Vec3NaNCheckerTests: public testing::TestWithParam<Vec3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec3UtilsNaNVectors, Vec3NaNCheckerTests,
                             ::testing::Values(Vec3UtilityParams{ fgm::Vec3(fgm::constants::NaN, 1.0f, 1.0f), true },
                                               Vec3UtilityParams{ fgm::Vec3(1.0f, fgm::constants::NaN, 1.0f), true },
                                               Vec3UtilityParams{ fgm::Vec3(1.0f, 1.0f, fgm::constants::NaN), true },
                                               Vec3UtilityParams{
                                                   fgm::Vec3(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN),
                                                   true },
                                               Vec3UtilityParams{ fgm::Vec3(1.0f, 1.0f, 1.0f), false }));



    /**
         * @brief Test fixture for @ref fgm::Vec3 utilities, verifying across various integral types.
         */
    template <typename>
    class Vec3UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Vec3UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Vec3 NORM_VEC(1.0f, 2.0f, 3.0f);
        constexpr fgm::Vec3 INF_VEC(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);
        constexpr fgm::Vec3 NAN_VEC(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN);

        /// @test Verify that Vec3::hasInf returns a valid boolean at compile time.
        static_assert(NORM_VEC.hasInf() == false);
        static_assert(INF_VEC.hasInf() == true);
        static_assert(NAN_VEC.hasInf() == false);

        /// @test Verify that Vec3::hasInf(static wrapper) returns a valid boolean at compile time.
        static_assert(fgm::Vec3<float>::hasInf(NORM_VEC) == false);
        static_assert(fgm::Vec3<float>::hasInf(INF_VEC) == true);
        static_assert(fgm::Vec3<float>::hasInf(NAN_VEC) == false);

        /// @test Verify that Vec3::hasNaN returns a valid boolean at compile time.
        static_assert(NORM_VEC.hasNaN() == false);
        static_assert(INF_VEC.hasNaN() == false);
        static_assert(NAN_VEC.hasNaN() == true);

        /// @test Verify that Vec3::hasNaN(static wrapper) returns a valid boolean at compile time.
        static_assert(fgm::Vec3<float>::hasNaN(NORM_VEC) == false);
        static_assert(fgm::Vec3<float>::hasNaN(INF_VEC) == false);
        static_assert(fgm::Vec3<float>::hasNaN(NAN_VEC) == true);

    } // namespace
} // namespace



/**************************************
 *      INFINITY CHECKER TESTS        *
 **************************************/

/**
 * @brief Verify that @ref std::Vec3::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(Vec3InfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}



/** @brief Verify that @ref std::Vec3::hasInf returns False for integral types. */
TYPED_TEST(Vec3UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec3(value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Vec3::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(Vec3InfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vec3<float>::hasInf(vec));
}


/** @brief Verify that the static variant of @ref std::Vec3::hasInf returns False for integral types. */
TYPED_TEST(Vec3UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec3<TypeParam>::hasInf(fgm::Vec3(value, value, value)));
}


/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

/**
 * @brief Verify that @ref std::Vec3::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Vec3NaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}



/** @brief Verify that @ref std::Vec3::hasNaN returns False for integral types. */
TYPED_TEST(Vec3UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec3(value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Vec3::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Vec3NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vec3<float>::hasNaN(vec));
}


/** @brief Verify that the static variant of @ref std::Vec3::hasNaN returns False for integral types. */
TYPED_TEST(Vec3UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec3<TypeParam>::hasNaN(fgm::Vec3(value, value, value)));
}

/** @} */
