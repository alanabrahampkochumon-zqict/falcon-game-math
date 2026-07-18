/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref fgm::Mat2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <MatrixTestSetup.h>



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Mat2UtilityParams
{
    fgm::Mat2<T> mat;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Mat2 infinity checker, parameterized by @ref VectorUtilityParams */
class Mat2InfChecker: public ::testing::TestWithParam<Mat2UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Mat2 NaN checker, parameterized by @ref VectorUtilityParams */
class Mat2NaNChecker: public ::testing::TestWithParam<Mat2UtilityParams<float>>
{};


template <typename T>
class Mat2IntegralUtility: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Mat2 utilities, parameterized by @ref SupportedIntegralTypes */
TYPED_TEST_SUITE(Mat2IntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Utils
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{
    constexpr fgm::Mat2 INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f);
    constexpr fgm::Mat2 MAT(1.0f, 1.0f, 1.0f, 1.0f);


    /** @brief Verify that the matrix hasNaN utility is available at compile time. */
    namespace
    {
        /// Member functions
        static_assert(MAT.hasNaN() == false);

        // Static functions
        static_assert(fgm::Mat2<float>::hasNaN(MAT) == false);
    } // namespace


    /** @brief Verify that the matrix hasInf utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        // Static functions
        static_assert(fgm::Mat2<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Mat2<float>::hasInf(MAT) == false);
    } // namespace

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Mat2::hasInf returns  `true` if any of elements are IEE754 infinity
 *        and `false` otherwise.
 */
TEST_P(Mat2InfChecker, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Mat2InfCheckerTestSuite, Mat2InfChecker,
    ::testing::Values(Mat2UtilityParams{ fgm::Mat2(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
                      Mat2UtilityParams{ fgm::Mat2(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                      Mat2UtilityParams{ fgm::Mat2(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Mat2UtilityParams{ fgm::Mat2(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                      Mat2UtilityParams{ fgm::Mat2(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                         fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                            true },
                      Mat2UtilityParams{ fgm::Mat2(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Mat2::hasInf returns `false` for integral types. */
TYPED_TEST(Mat2IntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat2(value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Mat2::hasInf returns  `true` if any of elements are IEE754
 *        infinity and `false` otherwise.
 */
TEST_P(Mat2InfChecker, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat2<float>::hasInf(mat));
}


/** @brief Verify that the static variant of @ref std::Mat2::hasInf returns `false` for integral types. */
TYPED_TEST(Mat2IntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat2<TypeParam>::hasInf(fgm::Mat2(value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Mat2::hasNaN returns  `true` if any of elements are IEE754 NaN(Not-a-Number)
 *       and `false` otherwise.
 */
TEST_P(Mat2NaNChecker, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Mat2NaNCheckerTestSuite, Mat2NaNChecker,
    ::testing::Values(Mat2UtilityParams{ fgm::Mat2(fgm::constants::NaN, 1.0f), true },
                      Mat2UtilityParams{ fgm::Mat2(1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
                      Mat2UtilityParams{ fgm::Mat2(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                      Mat2UtilityParams{ fgm::Mat2(1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
                      Mat2UtilityParams{ fgm::Mat2(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                                         fgm::constants::NaN),
                                            true },
                      Mat2UtilityParams{ fgm::Mat2(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Mat2::hasNaN returns `false` for integral types. */
TYPED_TEST(Mat2IntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat2(value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Mat2::hasNaN returns  `true` if any of elements are IEE754
 *        NaN(Not-a-Number) and `false` otherwise.
 */
TEST_P(Mat2NaNChecker, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat2<float>::hasNaN(mat));
}


/** @brief Verify that the static variant of @ref std::Mat2::hasNaN returns `false` for integral types. */
TYPED_TEST(Mat2IntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat2<TypeParam>::hasNaN(fgm::Mat2(value, value)));
}

/** @} */
