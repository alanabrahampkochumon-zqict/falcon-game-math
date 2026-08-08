/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref fgm::Mat3x2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x2TestSetup.h"



/**
 * @addtogroup T_FGM_Mat3x2_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Mat3x2UtilityParams
    {
        fgm::Mat3x2<T> mat;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref fgm::Mat3x2 Infinity Checking.
     */
    class Mat3x2InfCheckerTests: public testing::TestWithParam<Mat3x2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat3x2UtilsInfMatrices, Mat3x2InfCheckerTests,
        ::testing::Values(
            Mat3x2UtilityParams{ fgm::Mat3x2(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat3x2UtilityParams{ fgm::Mat3x2(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat3x2UtilityParams{ fgm::Mat3x2(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
            Mat3x2UtilityParams{ fgm::Mat3x2(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
            Mat3x2UtilityParams{ fgm::Mat3x2(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
            Mat3x2UtilityParams{ fgm::Mat3x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F), true },
            Mat3x2UtilityParams{ fgm::Mat3x2(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                             fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                             fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                 true },
            Mat3x2UtilityParams{ fgm::Mat3x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), false }));



    /**
     * @brief Test fixture for @ref fgm::Mat3x2 NaN Checking.
     */
    class Mat3x2NaNCheckerTests: public testing::TestWithParam<Mat3x2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat3x2UtilsNaNMatrices, Mat3x2NaNCheckerTests,
        ::testing::Values(Mat3x2UtilityParams{ fgm::Mat3x2(fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
                          Mat3x2UtilityParams{ fgm::Mat3x2(1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f), true },
                          Mat3x2UtilityParams{ fgm::Mat3x2(1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f), true },
                          Mat3x2UtilityParams{ fgm::Mat3x2(1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
                          Mat3x2UtilityParams{ fgm::Mat3x2(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                          Mat3x2UtilityParams{ fgm::Mat3x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
                          Mat3x2UtilityParams{ fgm::Mat3x2(fgm::constants::NaN, fgm::constants::NaN,
                                                           fgm::constants::NaN, fgm::constants::NaN,
                                                           fgm::constants::NaN, fgm::constants::NaN),
                                               true },
                          Mat3x2UtilityParams{ fgm::Mat3x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref fgm::Mat3x2 utilities, verifying across various integral types.
     */
    template <typename>
    class Mat3x2UtilsIntTests: public testing::Test
    {};
    /** @brief Test fixture for @ref fgm::Mat3x2 utilities, parameterized by @ref SupportedIntegralTypes */
    TYPED_TEST_SUITE(Mat3x2UtilsIntTests, SupportedIntegralTypes);




    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat3x2 INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        constexpr fgm::Mat3x2 NAN_MAT(fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        constexpr fgm::Mat3x2 MAT(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);


        /** @brief Verify that the Mat3x2 hasNaN return correct boolean at compile time. */
        static_assert(MAT.hasNaN() == false);
        static_assert(NAN_MAT.hasNaN() == true);

        /** @brief Verify that the Mat3x2 hasNaN (static wrapper) return correct boolean at compile time. */
        static_assert(fgm::Mat3x2<float>::hasNaN(MAT) == false);
        static_assert(fgm::Mat3x2<float>::hasNaN(NAN_MAT) == true);


        /** @brief Verify that the Mat3x2 hasInf return correct boolean at compile time. */
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);


        /** @brief Verify that the Mat3x2 hasInf (static wrapper) return correct boolean at compile time. */
        static_assert(fgm::Mat3x2<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Mat3x2<float>::hasInf(MAT) == false);

    } // namespace static_tests

} // namespace



/**************************************
 *         INFINITY CHECKER           *
 **************************************/

TEST_P(Mat3x2InfCheckerTests, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}


TYPED_TEST(Mat3x2UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3x2(value, value, value, value, value, value).hasInf());
}


TEST_P(Mat3x2InfCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat3x2<float>::hasInf(mat));
}


TYPED_TEST(Mat3x2UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3x2<TypeParam>::hasInf(fgm::Mat3x2(value, value, value, value, value, value)));
}



/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

TEST_P(Mat3x2NaNCheckerTests, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}


TYPED_TEST(Mat3x2UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3x2(value, value, value, value, value, value).hasNaN());
}


TEST_P(Mat3x2NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat3x2<float>::hasNaN(mat));
}


TYPED_TEST(Mat3x2UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3x2<TypeParam>::hasNaN(fgm::Mat3x2(value, value, value, value, value, value)));
}

/** @} */
