/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::CVec2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"


/**
 * @addtogroup T_FGM_CVec2_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct CVec2UtilityParams
    {
        fgm::CVec2<T> vec;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref fgm::CVec2 Infinity Checking.
     */
    class CVec2InfCheckerTests: public testing::TestWithParam<CVec2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        CVec2UtilsInfVectors, CVec2InfCheckerTests,
        ::testing::Values(CVec2UtilityParams{ fgm::CVec2(fgm::constants::INFINITY_F, 1.0f), true },
                          CVec2UtilityParams{ fgm::CVec2(1.0f, fgm::constants::INFINITY_F), true },
                          CVec2UtilityParams{ fgm::CVec2(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F), true },
                          CVec2UtilityParams{ fgm::CVec2(1.0f, 1.0f), false }));



    /**
     * @brief Test fixture for @ref fgm::CVec2 NaN Checking.
     */
    class CVec2NaNCheckerTests: public testing::TestWithParam<CVec2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(CVec2UtilsNaNVectors, CVec2NaNCheckerTests,
                             ::testing::Values(CVec2UtilityParams{ fgm::CVec2(fgm::constants::NaN, 1.0f), true },
                                               CVec2UtilityParams{ fgm::CVec2(1.0f, fgm::constants::NaN), true },
                                               CVec2UtilityParams{ fgm::CVec2(fgm::constants::NaN, fgm::constants::NaN),
                                                                  true },
                                               CVec2UtilityParams{ fgm::CVec2(1.0f, 1.0f), false }));



    /**
     * @brief Test fixture for @ref fgm::CVec2 utilities, verifying across various integral types.
     */
    template <typename>
    class CVec2UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(CVec2UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::CVec2 NORM_VEC(1.0f, 2.0f);
        constexpr fgm::CVec2 INF_VEC(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);
        constexpr fgm::CVec2 NAN_VEC(fgm::constants::NaN, fgm::constants::NaN);

        /// @test Verify that CVec2::hasInf returns a valid boolean at compile time.
        static_assert(NORM_VEC.hasInf() == false);
        static_assert(INF_VEC.hasInf() == true);
        static_assert(NAN_VEC.hasInf() == false);

        /// @test Verify that CVec2::hasInf(static wrapper) returns a valid boolean at compile time.
        static_assert(fgm::CVec2<float>::hasInf(NORM_VEC) == false);
        static_assert(fgm::CVec2<float>::hasInf(INF_VEC) == true);
        static_assert(fgm::CVec2<float>::hasInf(NAN_VEC) == false);

        /// @test Verify that CVec2::hasNaN returns a valid boolean at compile time.
        static_assert(NORM_VEC.hasNaN() == false);
        static_assert(INF_VEC.hasNaN() == false);
        static_assert(NAN_VEC.hasNaN() == true);

        /// @test Verify that CVec2::hasNaN(static wrapper) returns a valid boolean at compile time.
        static_assert(fgm::CVec2<float>::hasNaN(NORM_VEC) == false);
        static_assert(fgm::CVec2<float>::hasNaN(INF_VEC) == false);
        static_assert(fgm::CVec2<float>::hasNaN(NAN_VEC) == true);

    } // namespace
} // namespace


/**************************************
 *      INFINITY CHECKER TESTS        *
 **************************************/

/**
 * @test Verify that @ref std::CVec2::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(CVec2InfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}



/** @test Verify that @ref std::CVec2::hasInf returns False for integral types. */
TYPED_TEST(CVec2UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::CVec2(value, value).hasInf());
}


/**
 * @test Verify that the static variant of @ref std::CVec2::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(CVec2InfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::CVec2<float>::hasInf(vec));
}


/** @test Verify that the static variant of @ref std::CVec2::hasInf returns False for integral types. */
TYPED_TEST(CVec2UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::CVec2<TypeParam>::hasInf(fgm::CVec2(value, value)));
}


/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

/**
 * @test Verify that @ref std::CVec2::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(CVec2NaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}


/** @test Verify that @ref std::CVec2::hasNaN returns False for integral types. */
TYPED_TEST(CVec2UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::CVec2(value, value).hasNaN());
}


/**
 * @test Verify that the static variant of @ref std::CVec2::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(CVec2NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::CVec2<float>::hasNaN(vec));
}


/** @test Verify that the static variant of @ref std::CVec2::hasNaN returns False for integral types. */
TYPED_TEST(CVec2UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::CVec2<TypeParam>::hasNaN(fgm::CVec2(value, value)));
}

/** @} */
