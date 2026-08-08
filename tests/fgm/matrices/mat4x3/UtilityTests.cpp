/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref fgm::Mat4x3 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x3TestSetup.h"



/**
 * @addtogroup T_FGM_Mat4x3_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Mat4x3UtilityParams
    {
        fgm::Mat4x3<T> mat;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref fgm::Mat4x3 Infinity Checking.
     */
    class Mat4x3InfCheckerTests: public testing::TestWithParam<Mat4x3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4x3UtilsInfMatrices, Mat4x3InfCheckerTests,
        ::testing::Values(
            Mat4x3UtilityParams{ fgm::Mat4x3(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             fgm::constants::INFINITY_F, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             fgm::constants::INFINITY_F, 1.0f),
                                 true },
            Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             fgm::constants::INFINITY_F),
                                 true },
            Mat4x3UtilityParams{
                fgm::Mat4x3(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                            fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                            fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                            fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                true },
            Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                 false }));


    /**
     * @brief Test fixture for @ref fgm::Mat4x3 NaN Checking.
     */
    class Mat4x3NaNCheckerTests: public testing::TestWithParam<Mat4x3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4x3UtilsNaNMatrices, Mat4x3NaNCheckerTests,
        ::testing::Values(Mat4x3UtilityParams{ fgm::Mat4x3(fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           fgm::constants::NaN, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           fgm::constants::NaN, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           fgm::constants::NaN, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           1.0f, fgm::constants::NaN),
                                               true },
                          Mat4x3UtilityParams{
                              fgm::Mat4x3(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                          fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                          fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                          fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN),
                              true },
                          Mat4x3UtilityParams{
                              fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                              false }));


    /**
     * @brief Test fixture for @ref fgm::Mat4x3 utilities, verifying across various integral types.
     */
    template <typename>
    class Mat4x3UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat4x3UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat4x3 INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                      1.0f, 1.0f);
        constexpr fgm::Mat4x3 NAN_MAT(fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                      1.0f);
        constexpr fgm::Mat4x3 MAT(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

        /** @brief Verify that the Mat4x3 hasNaN return correct boolean at compile time. */
        static_assert(MAT.hasNaN() == false);
        static_assert(NAN_MAT.hasNaN() == true);

        /** @brief Verify that the Mat4x3 hasNaN (static wrapper) return correct boolean at compile time. */
        static_assert(fgm::Mat4x3<float>::hasNaN(MAT) == false);
        static_assert(fgm::Mat4x3<float>::hasNaN(NAN_MAT) == true);


        /** @brief Verify that the Mat4x3 hasInf return correct boolean at compile time. */
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        /** @brief Verify that the Mat4x3 hasInf (static wrapper) return correct boolean at compile time. */
        static_assert(fgm::Mat4x3<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Mat4x3<float>::hasInf(MAT) == false);

    } // namespace static_tests

} // namespace



/**************************************
 *         INFINITY CHECKER           *
 **************************************/

TEST_P(Mat4x3InfCheckerTests, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}


TYPED_TEST(Mat4x3UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(
        fgm::Mat4x3(value, value, value, value, value, value, value, value, value, value, value, value).hasInf());
}


TEST_P(Mat4x3InfCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat4x3<float>::hasInf(mat));
}


TYPED_TEST(Mat4x3UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat4x3<TypeParam>::hasInf(
        fgm::Mat4x3(value, value, value, value, value, value, value, value, value, value, value, value)));
}



/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

TEST_P(Mat4x3NaNCheckerTests, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}


TYPED_TEST(Mat4x3UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(
        fgm::Mat4x3(value, value, value, value, value, value, value, value, value, value, value, value).hasNaN());
}


TEST_P(Mat4x3NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat4x3<float>::hasNaN(mat));
}


TYPED_TEST(Mat4x3UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat4x3<TypeParam>::hasNaN(
        fgm::Mat4x3(value, value, value, value, value, value, value, value, value, value, value, value)));
}

/** @} */
