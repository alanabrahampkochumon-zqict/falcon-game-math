/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify @ref fgm::Mat4 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Mat4UtilityParams
{
    fgm::Mat4<T> mat;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Mat4 infinity checker, parameterized by @ref VectorUtilityParams */
class Mat4InfChecker: public ::testing::TestWithParam<Mat4UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Mat4 NaN checker, parameterized by @ref VectorUtilityParams */
class Mat4NaNChecker: public ::testing::TestWithParam<Mat4UtilityParams<float>>
{};


template <typename T>
class Mat4IntegralUtility: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Mat4 utilities, parameterized by @ref SupportedIntegralTypes */
TYPED_TEST_SUITE(Mat4IntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Mat4x4_Utils
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{
    constexpr fgm::Mat4 INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f);
    constexpr fgm::Mat4 MAT(1.0f, 1.0f, 1.0f, 1.0f);


    /** @brief Verify that the matrix hasNaN utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(MAT.hasNaN() == false);

        // Static functions
        static_assert(fgm::Mat4<float>::hasNaN(MAT) == false);
    } // namespace


    /** @brief Verify that the matrix hasInf utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        // Static functions
        static_assert(fgm::Mat4<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Mat4<float>::hasInf(MAT) == false);
    } // namespace

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Mat4::hasInf returns `true` if any of elements are IEE754 infinity
 *        and False otherwise.
 */
TEST_P(Mat4InfChecker, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Mat4InfCheckerTestSuite, Mat4InfChecker,
    ::testing::Values(Mat4UtilityParams{ fgm::Mat4(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
                      Mat4UtilityParams{ fgm::Mat4(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                      Mat4UtilityParams{ fgm::Mat4(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Mat4UtilityParams{ fgm::Mat4(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                      Mat4UtilityParams{ fgm::Mat4(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                         fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                            true },
                      Mat4UtilityParams{ fgm::Mat4(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Mat4::hasInf returns `false` for integral types. */
TYPED_TEST(Mat4IntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat4(value, value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Mat4::hasInf returns `true` if any of elements are IEE754
 *        infinity and False otherwise.
 */
TEST_P(Mat4InfChecker, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat4<float>::hasInf(mat));
}


/** @brief Verify that the static variant of @ref std::Mat4::hasInf returns `false` for integral types. */
TYPED_TEST(Mat4IntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat4<TypeParam>::hasInf(fgm::Mat4(value, value, value, value)));
}



/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Mat4::hasNaN returns `true` if any of elements are IEE754 NaN(Not-a-Number)
 *       and `false` otherwise.
 */
TEST_P(Mat4NaNChecker, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Mat4NaNCheckerTestSuite, Mat4NaNChecker,
    ::testing::Values(Mat4UtilityParams{ fgm::Mat4(fgm::constants::NaN, 1.0f, 1.0f, 1.0f), true },
                      Mat4UtilityParams{ fgm::Mat4(1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
                      Mat4UtilityParams{ fgm::Mat4(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                      Mat4UtilityParams{ fgm::Mat4(1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
                      Mat4UtilityParams{ fgm::Mat4(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                                         fgm::constants::NaN),
                                            true },
                      Mat4UtilityParams{ fgm::Mat4(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Mat4::hasNaN returns `false` for integral types. */
TYPED_TEST(Mat4IntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat4(value, value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Mat4::hasNaN returns `true` if any of elements are IEE754
 *        NaN(Not-a-Number) and `false` otherwise.
 */
TEST_P(Mat4NaNChecker, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat4<float>::hasNaN(mat));
}


/** @brief Verify that the static variant of @ref std::Mat4::hasNaN returns `false` for integral types. */
TYPED_TEST(Mat4IntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Mat4<TypeParam>::hasNaN(fgm::Mat4(value, value, value, value)));
}

/** @} */
