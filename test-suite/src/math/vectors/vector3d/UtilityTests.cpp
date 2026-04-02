/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verifies @ref fgm::Vector3D utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Vector3DTestSetup.h>


/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/
template <typename T>
    requires std::floating_point<T>
struct Vector3DUtilityParams
{
    fgm::Vector3D<T> vec;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Vector3D infinity checker, parameterized by @ref VectorUtilityParams */
class Vector3DInfCheckerTests: public ::testing::TestWithParam<Vector3DUtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Vector3D NaN checker, parameterized by @ref VectorUtilityParams */
class Vector3DNaNCheckerTests: public ::testing::TestWithParam<Vector3DUtilityParams<float>>
{};


/** @brief Test fixture for @ref fgm::Vector3D utilities, parameterized by @ref SupportedIntegralTypes */
template <typename T>
class Vector3DIntegralUtilityTests: public ::testing::Test
{};
TYPED_TEST_SUITE(Vector3DIntegralUtilityTests, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Vec3_Utils
 * @{
 */

/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @test Verify that @ref std::Vector3D::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(Vector3DInfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Vector3DNaNCheckerTestSuite, Vector3DInfCheckerTests,
    ::testing::Values(Vector3DUtilityParams{ fgm::Vector3D(fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                      Vector3DUtilityParams{ fgm::Vector3D(1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Vector3DUtilityParams{ fgm::Vector3D(1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                      Vector3DUtilityParams{ fgm::Vector3D(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                         fgm::constants::INFINITY_F),
                                           true },
                      Vector3DUtilityParams{ fgm::Vector3D(1.0f, 1.0f, 1.0f), false }));


/** @test Verify that @ref std::Vector3D::hasInf returns False for integral types. */
TYPED_TEST(Vector3DIntegralUtilityTests, HasInf_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector3D(value, value, value).hasInf());
}


/**
 * @test Verify that the static variant of @ref std::Vector3D::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(Vector3DInfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vector3D<float>::hasInf(vec));
}


/** @test Verify that the static variant of @ref std::Vector3D::hasInf returns False for integral types. */
TYPED_TEST(Vector3DIntegralUtilityTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector3D<TypeParam>::hasInf(fgm::Vector3D(value, value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @test Verify that @ref std::Vector3D::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Vector3DNaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Vector3DNaNCheckerTestSuite, Vector3DNaNCheckerTests,
    ::testing::Values(Vector3DUtilityParams{ fgm::Vector3D(fgm::constants::NaN, 1.0f, 1.0f), true },
                      Vector3DUtilityParams{ fgm::Vector3D(1.0f, fgm::constants::NaN, 1.0f), true },
                      Vector3DUtilityParams{ fgm::Vector3D(1.0f, 1.0f, fgm::constants::NaN), true },
                      Vector3DUtilityParams{ fgm::Vector3D(fgm::constants::NaN, fgm::constants::INFINITY_F,
                                                         fgm::constants::NaN),
                                           true },
                      Vector3DUtilityParams{ fgm::Vector3D(1.0f, 1.0f, 1.0f), false }));


/** @test Verify that @ref std::Vector3D::hasNaN returns False for integral types. */
TYPED_TEST(Vector3DIntegralUtilityTests, HasNaN_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector3D(value, value, value).hasNaN());
}


/**
 * @test Verify that the static variant of @ref std::Vector3D::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Vector3DNaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vector3D<float>::hasNaN(vec));
}


/** @test Verify that the static variant of @ref std::Vector3D::hasNaN returns False for integral types. */
TYPED_TEST(Vector3DIntegralUtilityTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector3D<TypeParam>::hasNaN(fgm::Vector3D(value, value, value)));
}

/** @} */
