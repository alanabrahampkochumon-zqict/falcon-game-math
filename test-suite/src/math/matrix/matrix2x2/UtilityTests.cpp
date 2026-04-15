/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref fgm::Matrix2D utility functions.
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
struct Matrix2DUtilityParams
{
    fgm::Matrix2D<T> mat;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Matrix2D infinity checker, parameterized by @ref VectorUtilityParams */
class Matrix2DInfChecker: public ::testing::TestWithParam<Matrix2DUtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Matrix2D NaN checker, parameterized by @ref VectorUtilityParams */
class Matrix2DNaNChecker: public ::testing::TestWithParam<Matrix2DUtilityParams<float>>
{};


/** @brief Test fixture for @ref fgm::Matrix2D utilities, parameterized by @ref SupportedIntegralTypes */
template <typename T>
class Matrix2DIntegralUtility: public ::testing::Test
{};
TYPED_TEST_SUITE(Matrix2DIntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Utils
 * @{
 */

/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Matrix2D::hasInf returns True if any of elements are IEE754 infinity
 *        and False otherwise.
 */
TEST_P(Matrix2DInfChecker, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix2DInfCheckerTestSuite, Matrix2DInfChecker,
    ::testing::Values(Matrix2DUtilityParams{ fgm::Matrix2D(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
                      Matrix2DUtilityParams{ fgm::Matrix2D(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                      Matrix2DUtilityParams{ fgm::Matrix2D(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Matrix2DUtilityParams{ fgm::Matrix2D(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                      Matrix2DUtilityParams{ fgm::Matrix2D(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                           fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                             true },
                      Matrix2DUtilityParams{ fgm::Matrix2D(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Matrix2D::hasInf returns False for integral types. */
TYPED_TEST(Matrix2DIntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix2D(value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Matrix2D::hasInf returns True if any of elements are IEE754
 *        infinity and False otherwise.
 */
TEST_P(Matrix2DInfChecker, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix2D<float>::hasInf(mat));
}


/** @brief Verify that the static variant of @ref std::Matrix2D::hasInf returns False for integral types. */
TYPED_TEST(Matrix2DIntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix2D<TypeParam>::hasInf(fgm::Matrix2D(value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Matrix2D::hasNaN returns True if any of elements are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Matrix2DNaNChecker, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix2DNaNCheckerTestSuite, Matrix2DNaNChecker,
    ::testing::Values(Matrix2DUtilityParams{ fgm::Matrix2D(fgm::constants::NaN, 1.0f), true },
                      Matrix2DUtilityParams{ fgm::Matrix2D(1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
                      Matrix2DUtilityParams{ fgm::Matrix2D(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                      Matrix2DUtilityParams{ fgm::Matrix2D(1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
                      Matrix2DUtilityParams{ fgm::Matrix2D(fgm::constants::NaN, fgm::constants::NaN,
                                                           fgm::constants::NaN, fgm::constants::NaN),
                                             true },
                      Matrix2DUtilityParams{ fgm::Matrix2D(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Matrix2D::hasNaN returns False for integral types. */
TYPED_TEST(Matrix2DIntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix2D(value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Matrix2D::hasNaN returns True if any of elements are IEE754
 *        NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Matrix2DNaNChecker, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix2D<float>::hasNaN(mat));
}


/** @brief Verify that the static variant of @ref std::Matrix2D::hasNaN returns False for integral types. */
TYPED_TEST(Matrix2DIntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix2D<TypeParam>::hasNaN(fgm::Matrix2D(value, value)));
}

/** @} */
