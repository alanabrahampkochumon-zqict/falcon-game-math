/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref fgm::Mat2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"


/**
 * @addtogroup T_FGM_Mat2x2_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Mat2UtilityParams
    {
        fgm::Mat2<T> mat;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref fgm::Mat2 Infinity Checking.
     */
    class Mat2InfCheckerTests: public testing::TestWithParam<Mat2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat2UtilsInfMatrices, Mat2InfCheckerTests,
        ::testing::Values(Mat2UtilityParams{ fgm::Mat2(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
                          Mat2UtilityParams{ fgm::Mat2(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                          Mat2UtilityParams{ fgm::Mat2(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                          Mat2UtilityParams{ fgm::Mat2(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                          Mat2UtilityParams{ fgm::Mat2(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                       fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                             true },
                          Mat2UtilityParams{ fgm::Mat2(1.0f, 1.0f, 1.0f, 1.0f), false }));

    /**
     * @brief Test fixture for @ref fgm::Mat2 NaN Checking.
     */
    class Mat2NaNCheckerTests: public testing::TestWithParam<Mat2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat2UtilsNaNMatrices, Mat2NaNCheckerTests,
        ::testing::Values(Mat2UtilityParams{ fgm::Mat2(fgm::constants::NaN, 1.0f), true },
                          Mat2UtilityParams{ fgm::Mat2(1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
                          Mat2UtilityParams{ fgm::Mat2(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                          Mat2UtilityParams{ fgm::Mat2(1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
                          Mat2UtilityParams{ fgm::Mat2(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                                       fgm::constants::NaN),
                                             true },
                          Mat2UtilityParams{ fgm::Mat2(1.0f, 1.0f, 1.0f, 1.0f), false }));



    /**
     * @brief Test fixture for @ref fgm::Mat2 utilities, verifying across various integral types.
     */
    template <typename>
    class Mat2UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat2UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat2 INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f);
        constexpr fgm::Mat2 NAN_MAT(fgm::constants::NaN, 1.0f, 1.0f, 1.0f);
        constexpr fgm::Mat2 MAT(1.0f, 1.0f, 1.0f, 1.0f);


        /** s@test Verify that the Mat2 hasNaN return correct boolean at compile time. */
        static_assert(MAT.hasNaN() == false);
        static_assert(NAN_MAT.hasNaN() == true);

        /** @test Verify that the Mat2 hasNaN (static wrapper) return correct boolean at compile time. */
        static_assert(fgm::Mat2<float>::hasNaN(MAT) == false);
        static_assert(fgm::Mat2<float>::hasNaN(NAN_MAT) == true);


        /** @test Verify that the Mat2 hasInf return correct boolean at compile time. */
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);


        /** @test Verify that the Mat2 hasInf (static wrapper) return correct boolean at compile time. */
        static_assert(fgm::Mat2<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Mat2<float>::hasInf(MAT) == false);

    } // namespace static_tests

} // namespace



/**************************************
 *         INFINITY CHECKER           *
 **************************************/

TEST_P(Mat2InfCheckerTests, HasInf_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}


TYPED_TEST(Mat2UtilsIntTests, HasInf_ReturnsFalseForIntegralMatrix)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat2(value, value).hasInf());
}


TEST_P(Mat2InfCheckerTests, StaticWrapper_HasInf_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat2<float>::hasInf(mat));
}


TYPED_TEST(Mat2UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegralMatrix)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat2<TypeParam>::hasInf(fgm::Mat2(value, value)));
}



/**************************************
 *             NAN CHECKER            *
 **************************************/

TEST_P(Mat2NaNCheckerTests, HasNaN_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}


TYPED_TEST(Mat2UtilsIntTests, HasNaN_ReturnsFalseForIntegralMatrix)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat2(value, value).hasNaN());
}


TEST_P(Mat2NaNCheckerTests, StaticWrapper_HasNaN_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat2<float>::hasNaN(mat));
}


TYPED_TEST(Mat2UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegralMatrix)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat2<TypeParam>::hasNaN(fgm::Mat2(value, value)));
}

/** @} */
