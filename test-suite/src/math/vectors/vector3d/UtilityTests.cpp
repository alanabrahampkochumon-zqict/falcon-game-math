/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref fgm::Vector3D utility functions.
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
class Vector3DInfChecker: public ::testing::TestWithParam<Vector3DUtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Vector3D NaN checker, parameterized by @ref VectorUtilityParams */
class Vector3DNaNChecker: public ::testing::TestWithParam<Vector3DUtilityParams<float>>
{};


/** @brief Test fixture for @ref fgm::Vector3D utilities, parameterized by @ref SupportedIntegralTypes */
template <typename T>
class Vector3DIntegralUtility: public ::testing::Test
{};
TYPED_TEST_SUITE(Vector3DIntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Vec3_Utils
 * @{
 */

/** @brief Verify that vector utilities are available at compile time. */
namespace
{
    constexpr fgm::Vector3D normVec(1, 2, 3);
    constexpr fgm::Vector3D infVec(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);
    constexpr fgm::Vector3D nanVec(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN);

    static_assert(normVec.hasInf() == false);
    static_assert(infVec.hasInf() == true);
    static_assert(nanVec.hasInf() == false);

    static_assert(fgm::Vector3D<float>::hasInf(normVec) == false);
    static_assert(fgm::Vector3D<float>::hasInf(infVec) == true);
    static_assert(fgm::Vector3D<float>::hasInf(nanVec) == false);

    static_assert(normVec.hasNaN() == false);
    static_assert(infVec.hasNaN() == false);
    static_assert(nanVec.hasNaN() == true);

    static_assert(fgm::Vector3D<float>::hasNaN(normVec) == false);
    static_assert(fgm::Vector3D<float>::hasNaN(infVec) == false);
    static_assert(fgm::Vector3D<float>::hasNaN(nanVec) == true);

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Vector3D::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(Vector3DInfChecker, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Vector3DInfCheckerTestSuite, Vector3DInfChecker,
    ::testing::Values(Vector3DUtilityParams{ fgm::Vector3D(fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                      Vector3DUtilityParams{ fgm::Vector3D(1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Vector3DUtilityParams{ fgm::Vector3D(1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                      Vector3DUtilityParams{ fgm::Vector3D(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                           fgm::constants::INFINITY_F),
                                             true },
                      Vector3DUtilityParams{ fgm::Vector3D(1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Vector3D::hasInf returns False for integral types. */
TYPED_TEST(Vector3DIntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector3D(value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Vector3D::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(Vector3DInfChecker, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vector3D<float>::hasInf(vec));
}


/** @brief Verify that the static variant of @ref std::Vector3D::hasInf returns False for integral types. */
TYPED_TEST(Vector3DIntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector3D<TypeParam>::hasInf(fgm::Vector3D(value, value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Vector3D::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Vector3DNaNChecker, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Vector3DNaNCheckerTestSuite, Vector3DNaNChecker,
    ::testing::Values(Vector3DUtilityParams{ fgm::Vector3D(fgm::constants::NaN, 1.0f, 1.0f), true },
                      Vector3DUtilityParams{ fgm::Vector3D(1.0f, fgm::constants::NaN, 1.0f), true },
                      Vector3DUtilityParams{ fgm::Vector3D(1.0f, 1.0f, fgm::constants::NaN), true },
                      Vector3DUtilityParams{
                          fgm::Vector3D(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN), true },
                      Vector3DUtilityParams{ fgm::Vector3D(1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Vector3D::hasNaN returns False for integral types. */
TYPED_TEST(Vector3DIntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector3D(value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Vector3D::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Vector3DNaNChecker, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vector3D<float>::hasNaN(vec));
}


/** @brief Verify that the static variant of @ref std::Vector3D::hasNaN returns False for integral types. */
TYPED_TEST(Vector3DIntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector3D<TypeParam>::hasNaN(fgm::Vector3D(value, value, value)));
}

/** @} */
