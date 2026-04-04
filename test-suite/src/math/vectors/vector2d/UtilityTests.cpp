/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verifies @ref fgm::Vector2D utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Vector2DTestSetup.h>


/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Vector2DUtilityParams
{
    fgm::Vector2D<T> vec;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Vector2D infinity checker, parameterized by @ref VectorUtilityParams */
class Vector2DInfChecker: public ::testing::TestWithParam<Vector2DUtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Vector2D NaN checker, parameterized by @ref VectorUtilityParams */
class Vector2DNaNChecker: public ::testing::TestWithParam<Vector2DUtilityParams<float>>
{};


/** @brief Test fixture for @ref fgm::Vector2D utilities, parameterized by @ref SupportedIntegralTypes */
template <typename T>
class Vector2DIntegralUtility: public ::testing::Test
{};
TYPED_TEST_SUITE(Vector2DIntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Vec2_Utils
 * @{
 */

/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @test Verify that @ref std::Vector2D::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(Vector2DInfChecker, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Vector2DNaNCheckerTestSuite, Vector2DInfChecker,
    ::testing::Values(Vector2DUtilityParams{ fgm::Vector2D(fgm::constants::INFINITY_F, 1.0f), true },
                      Vector2DUtilityParams{ fgm::Vector2D(1.0f, fgm::constants::INFINITY_F), true },
                      Vector2DUtilityParams{ fgm::Vector2D(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                             true },
                      Vector2DUtilityParams{ fgm::Vector2D(1.0f, 1.0f), false }));


/** @test Verify that @ref std::Vector2D::hasInf returns False for integral types. */
TYPED_TEST(Vector2DIntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector2D(value, value).hasInf());
}


/**
 * @test Verify that the static variant of @ref std::Vector2D::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(Vector2DInfChecker, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vector2D<float>::hasInf(vec));
}


/** @test Verify that the static variant of @ref std::Vector2D::hasInf returns False for integral types. */
TYPED_TEST(Vector2DIntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector2D<TypeParam>::hasInf(fgm::Vector2D(value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @test Verify that @ref std::Vector2D::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Vector2DNaNChecker, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Vector2DNaNCheckerTestSuite, Vector2DNaNChecker,
    ::testing::Values(Vector2DUtilityParams{ fgm::Vector2D(fgm::constants::NaN, 1.0f), true },
                      Vector2DUtilityParams{ fgm::Vector2D(1.0f, fgm::constants::NaN), true },
                      Vector2DUtilityParams{
                          fgm::Vector2D(fgm::constants::NaN, fgm::constants::NaN), true },
                      Vector2DUtilityParams{ fgm::Vector2D(1.0f, 1.0f), false }));


/** @test Verify that @ref std::Vector2D::hasNaN returns False for integral types. */
TYPED_TEST(Vector2DIntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector2D(value, value).hasNaN());
}


/**
 * @test Verify that the static variant of @ref std::Vector2D::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Vector2DNaNChecker, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vector2D<float>::hasNaN(vec));
}


/** @test Verify that the static variant of @ref std::Vector2D::hasNaN returns False for integral types. */
TYPED_TEST(Vector2DIntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector2D<TypeParam>::hasNaN(fgm::Vector2D(value, value)));
}

/** @} */
