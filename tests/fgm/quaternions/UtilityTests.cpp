/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 04, 2026
 *
 * @brief Verify @ref fgm::Quaternion utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"


/**
 * @addtogroup T_FGM_Quaternion_Utils
 * @{
 */

namespace
{


    /**************************************
     *                                    *
     *            TEST SETUP              *
     *                                    *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct QuaternionUtilityParams
    {
        fgm::Quaternion<T> vec;
        bool expected;
    };


    /** @brief Parameterized test fixture for @ref fgm::Quaternion infinity checker. */
    class QuaternionInfCheckerTests: public testing::TestWithParam<QuaternionUtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        QuaternionInfCheckerTestSuite, QuaternionInfCheckerTests,
        ::testing::Values(
            QuaternionUtilityParams{ fgm::Quaternion(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
            QuaternionUtilityParams{ fgm::Quaternion(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
            QuaternionUtilityParams{ fgm::Quaternion(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
            QuaternionUtilityParams{ fgm::Quaternion(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
            QuaternionUtilityParams{ fgm::Quaternion(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F), true },
            QuaternionUtilityParams{ fgm::Quaternion(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                     fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                     true },
            QuaternionUtilityParams{ fgm::Quaternion(1.0f, 1.0f, 1.0f, 1.0f), false }));


    /** @brief Parameterized test fixture for @ref fgm::Quaternion NaN checker. */
    class QuaternionNaNCheckerTests: public ::testing::TestWithParam<QuaternionUtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        QuaternionNaNCheckerTestSuite, QuaternionNaNCheckerTests,
        ::testing::Values(QuaternionUtilityParams{ fgm::Quaternion(fgm::constants::NaN, 1.0f, 1.0f, 1.0f), true },
                          QuaternionUtilityParams{ fgm::Quaternion(1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
                          QuaternionUtilityParams{ fgm::Quaternion(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                          QuaternionUtilityParams{ fgm::Quaternion(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                          QuaternionUtilityParams{ fgm::Quaternion(1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
                          QuaternionUtilityParams{ fgm::Quaternion(fgm::constants::NaN, fgm::constants::NaN,
                                                                   fgm::constants::NaN, fgm::constants::NaN),
                                                   true },
                          QuaternionUtilityParams{ fgm::Quaternion(1.0f, 1.0f, 1.0f, 1.0f), false }));


    /** @brief Test fixture for @ref fgm::Quaternion utilities, for testing against integral types. */
    template <typename T>
    class QuaternionIntegralUtilityTests: public testing::Test
    {};
    TYPED_TEST_SUITE(QuaternionIntegralUtilityTests, SupportedIntegralTypes);


    /**************************************
     *                                    *
     *           STATIC TESTS             *
     *                                    *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Quaternion NORMAL_QUATERNION(1.0f, 2.0f, 3.0f, 4.0f);
        constexpr fgm::Quaternion INF_QUATERNION(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                 fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);
        constexpr fgm::Quaternion NAN_QUATERNION(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                                 fgm::constants::NaN);

        /// @test Verify that quaternion hasInf return correct boolean at compile time.
        static_assert(NORMAL_QUATERNION.hasInf() == false);
        static_assert(INF_QUATERNION.hasInf() == true);
        static_assert(NAN_QUATERNION.hasInf() == false);
        //
        // static_assert(fgm::Quaternion<float>::hasInf(normVec) == false);
        // static_assert(fgm::Quaternion<float>::hasInf(infVec) == true);
        // static_assert(fgm::Quaternion<float>::hasInf(nanVec) == false);
        //
        // static_assert(normVec.hasNaN() == false);
        // static_assert(infVec.hasNaN() == false);
        // static_assert(nanVec.hasNaN() == true);
        //
        // static_assert(fgm::Quaternion<float>::hasNaN(normVec) == false);
        // static_assert(fgm::Quaternion<float>::hasNaN(infVec) == false);
        // static_assert(fgm::Quaternion<float>::hasNaN(nanVec) == true);

    } // namespace static_tests

} // namespace



/**************************************
 *      INFINITY CHECKER TESTS        *
 **************************************/

TEST_P(QuaternionInfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}



/** @brief Verify that @ref std::Quaternion::hasInf returns False for integral types. */
TYPED_TEST(QuaternionIntegralUtilityTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Quaternion(value, value, value, value).hasInf());
}


TEST_P(QuaternionInfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Quaternion<float>::hasInf(vec));
}


TYPED_TEST(QuaternionIntegralUtilityTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Quaternion<TypeParam>::hasInf(fgm::Quaternion(value, value, value, value)));
}

//
// /**************************************
//  *         NAN CHECKER TESTS          *
//  **************************************/
//
// /**
//  * @brief Verify that @ref std::Quaternion::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
//  *       and False otherwise.
//  */
// TEST_P(QuaternionNaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
// {
//     const auto& [vec, expected] = GetParam();
//     EXPECT_EQ(expected, vec.hasNaN());
// }
//
//
//
// /** @brief Verify that @ref std::Quaternion::hasNaN returns False for integral types. */
// TYPED_TEST(QuaternionIntegralUtilityTests, HasNaN_ReturnsFalseForIntegrals)
// {
//     const auto value = TypeParam(1);
//     EXPECT_FALSE(fgm::Quaternion(value, value, value, value).hasNaN());
// }
//
//
// /**
//  * @brief Verify that the static variant of @ref std::Quaternion::hasNaN returns True if any of components are IEE754
//  *       NaN(Not-a-Number) and False otherwise.
//  */
// TEST_P(QuaternionNaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
// {
//     const auto& [vec, expected] = GetParam();
//     EXPECT_EQ(expected, fgm::Quaternion<float>::hasNaN(vec));
// }
//
//
// /** @brief Verify that the static variant of @ref std::Quaternion::hasNaN returns False for integral types. */
// TYPED_TEST(QuaternionIntegralUtilityTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
// {
//     const auto value = TypeParam(1);
//     EXPECT_FALSE(fgm::Quaternion<TypeParam>::hasNaN(fgm::Quaternion(value, value, value, value)));
// }

/** @} */
