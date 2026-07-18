/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref fgm::Mat3x2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Mat3x2TestSetup.h>



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Mat3x2UtilityParams
{
    fgm::Mat3x2<T> mat;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Mat3x2 infinity checker, parameterized by @ref VectorUtilityParams */
class Mat3x2InfChecker: public ::testing::TestWithParam<Mat3x2UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Mat3x2 NaN checker, parameterized by @ref VectorUtilityParams */
class Mat3x2NaNChecker: public ::testing::TestWithParam<Mat3x2UtilityParams<float>>
{};


template <typename T>
class Mat3x2IntegralUtility: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Mat3x2 utilities, parameterized by @ref SupportedIntegralTypes */
TYPED_TEST_SUITE(Mat3x2IntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Mat3x2_Utils
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{
    constexpr fgm::Mat3x2 INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    constexpr fgm::Mat3x2 MAT(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);


    /** @brief Verify that the matrix hasNaN utility is available at compile time. */
    namespace
    {
        /// Member functions
        static_assert(MAT.hasNaN() == false);

        // Static functions
        static_assert(fgm::Mat3x2<float>::hasNaN(MAT) == false);
    } // namespace


    /** @brief Verify that the matrix hasInf utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        // Static functions
        static_assert(fgm::Mat3x2<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Mat3x2<float>::hasInf(MAT) == false);
    } // namespace

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std:: Mat3x2::hasInf returns  `true` if any of elements are IEE754 infinity
 *        and `false` otherwise.
 */
TEST_P(Mat3x2InfChecker, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Mat3x2InfCheckerTestSuite, Mat3x2InfChecker,
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


/** @brief Verify that @ref std:: Mat3x2::hasInf returns `false` for integral types. */
TYPED_TEST(Mat3x2IntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3x2(value, value, value, value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std:: Mat3x2::hasInf returns  `true` if any of elements are IEE754
 *        infinity and `false` otherwise.
 */
TEST_P(Mat3x2InfChecker, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat3x2<float>::hasInf(mat));
}


/** @brief Verify that the static variant of @ref std:: Mat3x2::hasInf returns `false` for integral types. */
TYPED_TEST(Mat3x2IntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3x2<TypeParam>::hasInf(fgm::Mat3x2(value, value, value, value, value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std:: Mat3x2::hasNaN returns  `true` if any of elements are IEE754 NaN(Not-a-Number)
 *       and `false` otherwise.
 */
TEST_P(Mat3x2NaNChecker, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Mat3x2NaNCheckerTestSuite, Mat3x2NaNChecker,
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


/** @brief Verify that @ref std:: Mat3x2::hasNaN returns `false` for integral types. */
TYPED_TEST(Mat3x2IntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3x2(value, value, value, value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std:: Mat3x2::hasNaN returns  `true` if any of elements are IEE754
 *        NaN(Not-a-Number) and `false` otherwise.
 */
TEST_P(Mat3x2NaNChecker, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat3x2<float>::hasNaN(mat));
}


/** @brief Verify that the static variant of @ref std:: Mat3x2::hasNaN returns `false` for integral types. */
TYPED_TEST(Mat3x2IntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat3x2<TypeParam>::hasNaN(fgm::Mat3x2(value, value, value, value, value, value)));
}

/** @} */
