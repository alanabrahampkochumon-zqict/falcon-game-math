/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref fgm::Mat4x3 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Mat4x3TestSetup.h>



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Mat4x3UtilityParams
{
    fgm::Mat4x3<T> mat;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Mat4x3 infinity checker, parameterized by @ref VectorUtilityParams */
class Mat4x3InfChecker: public ::testing::TestWithParam<Mat4x3UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Mat4x3 NaN checker, parameterized by @ref VectorUtilityParams */
class Mat4x3NaNChecker: public ::testing::TestWithParam<Mat4x3UtilityParams<float>>
{};


template <typename T>
class Mat4x3IntegralUtility: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Mat4x3 utilities, parameterized by @ref SupportedIntegralTypes */
TYPED_TEST_SUITE(Mat4x3IntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Mat4x3_Utils
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{
    constexpr fgm::Mat4x3 INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                  1.0f, 1.0f);
    constexpr fgm::Mat4x3 MAT(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);


    /** @brief Verify that the matrix hasNaN utility is available at compile time. */
    namespace
    {
        /// Member functions
        static_assert(MAT.hasNaN() == false);

        // Static functions
        static_assert(fgm::Mat4x3<float>::hasNaN(MAT) == false);
    } // namespace


    /** @brief Verify that the matrix hasInf utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        // Static functions
        static_assert(fgm::Mat4x3<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Mat4x3<float>::hasInf(MAT) == false);
    } // namespace

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std:: Mat4x3::hasInf returns  `true` if any of elements are IEE754 infinity
 *        and `false` otherwise.
 */
TEST_P(Mat4x3InfChecker, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Mat4x3InfCheckerTestSuite, Mat4x3InfChecker,
    ::testing::Values(
        Mat4x3UtilityParams{
            fgm::Mat4x3(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f),
            true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f),
            true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f),
            true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f),
            true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F),
            true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                        fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                        fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                        fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
            true },
        Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                             false }));


/** @brief Verify that @ref std:: Mat4x3::hasInf returns `false` for integral types. */
TYPED_TEST(Mat4x3IntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(
        fgm::Mat4x3(value, value, value, value, value, value, value, value, value, value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std:: Mat4x3::hasInf returns  `true` if any of elements are IEE754
 *        infinity and `false` otherwise.
 */
TEST_P(Mat4x3InfChecker, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat4x3<float>::hasInf(mat));
}


/** @brief Verify that the static variant of @ref std:: Mat4x3::hasInf returns `false` for integral types. */
TYPED_TEST(Mat4x3IntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat4x3<TypeParam>::hasInf(
        fgm::Mat4x3(value, value, value, value, value, value, value, value, value, value, value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std:: Mat4x3::hasNaN returns  `true` if any of elements are IEE754 NaN(Not-a-Number)
 *       and `false` otherwise.
 */
TEST_P(Mat4x3NaNChecker, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Mat4x3NaNCheckerTestSuite, Mat4x3NaNChecker,
    ::testing::Values(
        Mat4x3UtilityParams{
            fgm::Mat4x3(fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f), true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
        Mat4x3UtilityParams{
            fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
        Mat4x3UtilityParams{ fgm::Mat4x3(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                         fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                         fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                         fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN),
                             true },
        Mat4x3UtilityParams{ fgm::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                             false }));


/** @brief Verify that @ref std:: Mat4x3::hasNaN returns `false` for integral types. */
TYPED_TEST(Mat4x3IntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(
        fgm::Mat4x3(value, value, value, value, value, value, value, value, value, value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std:: Mat4x3::hasNaN returns  `true` if any of elements are IEE754
 *        NaN(Not-a-Number) and `false` otherwise.
 */
TEST_P(Mat4x3NaNChecker, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat4x3<float>::hasNaN(mat));
}


/** @brief Verify that the static variant of @ref std:: Mat4x3::hasNaN returns `false` for integral types. */
TYPED_TEST(Mat4x3IntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat4x3<TypeParam>::hasNaN(
        fgm::Mat4x3(value, value, value, value, value, value, value, value, value, value, value, value)));
}

/** @} */
