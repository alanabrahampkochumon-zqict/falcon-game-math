/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 23, 2026
 *
 * @brief Verify @ref fgm::Mat3 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"



/**
 * @addtogroup T_FGM_Mat3x3_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Mat3UtilityParams
    {
        fgm::Mat3<T> mat;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref fgm::Mat3 Infinity Checking.
     */
    class Mat3InfCheckerTests: public testing::TestWithParam<Mat3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat3UtilsInfMatrices, Mat3InfCheckerTests,
        ::testing::Values(
            Mat3UtilityParams{ fgm::Mat3(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f),
                               true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f),
                               true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f),
                               true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F),
                               true },
            Mat3UtilityParams{
                fgm::Mat3(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F), true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref fgm::Mat3 NaN Checking.
     */
    class Mat3NaNCheckerTests: public testing::TestWithParam<Mat3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat3UtilsNaNMatrices, Mat3NaNCheckerTests,
        ::testing::Values(
            Mat3UtilityParams{ fgm::Mat3(fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f), true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
            Mat3UtilityParams{ fgm::Mat3(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN), true },
            Mat3UtilityParams{ fgm::Mat3(1.0f, 1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref fgm::Mat3 utilities, verifying across various integral types.
     */
    template <typename>
    class Mat3UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat3UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat3 INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f);
        constexpr fgm::Mat3 NAN_MAT(fgm::constants::NaN, 1.0f, 1.0f);
        constexpr fgm::Mat3 MAT(1.0f, 1.0f, 1.0f);


        /** @brief Verify that the Mat3 hasNaN return correct boolean at compile time. */
        static_assert(MAT.hasNaN() == false);
        static_assert(NAN_MAT.hasNaN() == true);

        /** @brief Verify that the Mat3 hasNaN (static wrapper) return correct boolean at compile time. */
        static_assert(fgm::Mat3<float>::hasNaN(MAT) == false);
        static_assert(fgm::Mat3<float>::hasNaN(NAN_MAT) == true);


        /** @brief Verify that the Mat3 hasInf return correct boolean at compile time. */
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);


        /** @brief Verify that the Mat3 hasInf (static wrapper) return correct boolean at compile time. */
        static_assert(fgm::Mat3<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Mat3<float>::hasInf(MAT) == false);

    } // namespace static_tests

} // namespace



/**************************************
 *         INFINITY CHECKER           *
 **************************************/

TEST_P(Mat3InfCheckerTests, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}


/** @brief Verify that @ref std::Mat3::hasInf returns `false` for integral types. */
TYPED_TEST(Mat3UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3(value, value, value).hasInf());
}


TEST_P(Mat3InfCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat3<float>::hasInf(mat));
}


TYPED_TEST(Mat3UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3<TypeParam>::hasInf(fgm::Mat3(value, value, value)));
}



/**************************************
 *             NAN CHECKER            *
 **************************************/

TEST_P(Mat3NaNCheckerTests, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}


TYPED_TEST(Mat3UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3(value, value, value).hasNaN());
}


TEST_P(Mat3NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat3<float>::hasNaN(mat));
}


TYPED_TEST(Mat3UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3<TypeParam>::hasNaN(fgm::Mat3(value, value, value)));
}

/** @} */
