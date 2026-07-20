/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref fgm::Mat3x4 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Mat3x4TestSetup.h>



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Mat3x4UtilityParams
{
    fgm::Mat3x4<T> mat;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Mat3x4 infinity checker, parameterized by @ref VectorUtilityParams */
class Mat3x4InfChecker: public ::testing::TestWithParam<Mat3x4UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Mat3x4 NaN checker, parameterized by @ref VectorUtilityParams */
class Mat3x4NaNChecker: public ::testing::TestWithParam<Mat3x4UtilityParams<float>>
{};


template <typename T>
class Mat3x4IntegralUtility: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Mat3x4 utilities, parameterized by @ref SupportedIntegralTypes */
TYPED_TEST_SUITE(Mat3x4IntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Mat3x4_Utils
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{
    constexpr fgm::Mat3x4 INF_MAT(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -fgm::constants::INFINITY_F,
                                  -fgm::constants::INFINITY_F);
    constexpr fgm::Mat3x4 MAT(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);


    /** @brief Verify that the matrix hasNaN utility is available at compile time. */
    namespace
    {
        /// Member functions
        static_assert(MAT.hasNaN() == false);

        // Static functions
        static_assert(fgm::Mat3x4<float>::hasNaN(MAT) == false);
    } // namespace


    /** @brief Verify that the matrix hasInf utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        // Static functions
        static_assert(fgm::Mat3x4<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Mat3x4<float>::hasInf(MAT) == false);
    } // namespace

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std:: Mat3x4::hasInf returns  `true` if any of elements are IEE754 infinity
 *        and `false` otherwise.
 */
TEST_P(Mat3x4InfChecker, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Mat3x4InfCheckerTestSuite, Mat3x4InfChecker,
    ::testing::Values(
        Mat3x4UtilityParams{
            fgm::Mat3x4(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f),
            true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f),
            true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f),
            true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F),
            true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                        fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                        fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                        fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
            true },
        Mat3x4UtilityParams{ fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                             false }));


/** @brief Verify that @ref std:: Mat3x4::hasInf returns `false` for integral types. */
TYPED_TEST(Mat3x4IntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(
        fgm::Mat3x4(value, value, value, value, value, value, value, value, value, value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std:: Mat3x4::hasInf returns  `true` if any of elements are IEE754
 *        infinity and `false` otherwise.
 */
TEST_P(Mat3x4InfChecker, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat3x4<float>::hasInf(mat));
}


/** @brief Verify that the static variant of @ref std:: Mat3x4::hasInf returns `false` for integral types. */
TYPED_TEST(Mat3x4IntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3x4<TypeParam>::hasInf(
        fgm::Mat3x4(value, value, value, value, value, value, value, value, value, value, value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std:: Mat3x4::hasNaN returns  `true` if any of elements are IEE754 NaN(Not-a-Number)
 *       and `false` otherwise.
 */
TEST_P(Mat3x4NaNChecker, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Mat3x4NaNCheckerTestSuite, Mat3x4NaNChecker,
    ::testing::Values(
        Mat3x4UtilityParams{
            fgm::Mat3x4(fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
        Mat3x4UtilityParams{
            fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
        Mat3x4UtilityParams{ fgm::Mat3x4(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                         fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                         fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                         fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN),
                             true },
        Mat3x4UtilityParams{ fgm::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                             false }));


/** @brief Verify that @ref std:: Mat3x4::hasNaN returns `false` for integral types. */
TYPED_TEST(Mat3x4IntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(
        fgm::Mat3x4(value, value, value, value, value, value, value, value, value, value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std:: Mat3x4::hasNaN returns  `true` if any of elements are IEE754
 *        NaN(Not-a-Number) and `false` otherwise.
 */
TEST_P(Mat3x4NaNChecker, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat3x4<float>::hasNaN(mat));
}


/** @brief Verify that the static variant of @ref std:: Mat3x4::hasNaN returns `false` for integral types. */
TYPED_TEST(Mat3x4IntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3x4<TypeParam>::hasNaN(
        fgm::Mat3x4(value, value, value, value, value, value, value, value, value, value, value, value)));
}

/** @} */
