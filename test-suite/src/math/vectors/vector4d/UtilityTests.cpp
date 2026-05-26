/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 30, 2026
 *
 * @brief Verify @ref fgm::Vector4D utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Vector4DTestSetup.h>


/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Vector4DUtilityParams
{
    fgm::Vector4D<T> vec;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Vector4D infinity checker, parameterized by @ref VectorUtilityParams */
class Vector4DInfCheckerTests: public ::testing::TestWithParam<Vector4DUtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Vector4D NaN checker, parameterized by @ref VectorUtilityParams */
class Vector4DNaNCheckerTests: public ::testing::TestWithParam<Vector4DUtilityParams<float>>
{};


/** @brief Test fixture for @ref fgm::Vector4D utilities, parameterized by @ref SupportedIntegralTypes */
template <typename T>
class Vector4DIntegralUtilityTests: public ::testing::Test
{};
TYPED_TEST_SUITE(Vector4DIntegralUtilityTests, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Vec4_Utils
 * @{
 */

/** @brief Verify that vector utilities are available at compile time. */
namespace
{
    constexpr fgm::Vector4D normVec(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vector4D infVec(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                   fgm::constants::INFINITY_F);
    constexpr fgm::Vector4D nanVec(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN);

    static_assert(normVec.hasInf() == false);
    static_assert(infVec.hasInf() == true);
    static_assert(nanVec.hasInf() == false);

    static_assert(fgm::Vector4D<float>::hasInf(normVec) == false);
    static_assert(fgm::Vector4D<float>::hasInf(infVec) == true);
    static_assert(fgm::Vector4D<float>::hasInf(nanVec) == false);

    static_assert(normVec.hasNaN() == false);
    static_assert(infVec.hasNaN() == false);
    static_assert(nanVec.hasNaN() == true);

    static_assert(fgm::Vector4D<float>::hasNaN(normVec) == false);
    static_assert(fgm::Vector4D<float>::hasNaN(infVec) == false);
    static_assert(fgm::Vector4D<float>::hasNaN(nanVec) == true);

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Vector4D::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(Vector4DInfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Vector4DInfCheckerTestSuite, Vector4DInfCheckerTests,
    ::testing::Values(Vector4DUtilityParams{ fgm::Vector4D(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
                      Vector4DUtilityParams{ fgm::Vector4D(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                      Vector4DUtilityParams{ fgm::Vector4D(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Vector4DUtilityParams{ fgm::Vector4D(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Vector4DUtilityParams{ fgm::Vector4D(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                      Vector4DUtilityParams{ fgm::Vector4D(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                           fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                             true },
                      Vector4DUtilityParams{ fgm::Vector4D(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Vector4D::hasInf returns False for integral types. */
TYPED_TEST(Vector4DIntegralUtilityTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector4D(value, value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Vector4D::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(Vector4DInfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vector4D<float>::hasInf(vec));
}


/** @brief Verify that the static variant of @ref std::Vector4D::hasInf returns False for integral types. */
TYPED_TEST(Vector4DIntegralUtilityTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector4D<TypeParam>::hasInf(fgm::Vector4D(value, value, value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Vector4D::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Vector4DNaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Vector4DNaNCheckerTestSuite, Vector4DNaNCheckerTests,
    ::testing::Values(Vector4DUtilityParams{ fgm::Vector4D(fgm::constants::NaN, 1.0f, 1.0f, 1.0f), true },
                      Vector4DUtilityParams{ fgm::Vector4D(1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
                      Vector4DUtilityParams{ fgm::Vector4D(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                      Vector4DUtilityParams{ fgm::Vector4D(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                      Vector4DUtilityParams{ fgm::Vector4D(1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
                      Vector4DUtilityParams{ fgm::Vector4D(fgm::constants::NaN, fgm::constants::NaN,
                                                           fgm::constants::NaN, fgm::constants::NaN),
                                             true },
                      Vector4DUtilityParams{ fgm::Vector4D(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Vector4D::hasNaN returns False for integral types. */
TYPED_TEST(Vector4DIntegralUtilityTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector4D(value, value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Vector4D::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Vector4DNaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vector4D<float>::hasNaN(vec));
}


/** @brief Verify that the static variant of @ref std::Vector4D::hasNaN returns False for integral types. */
TYPED_TEST(Vector4DIntegralUtilityTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector4D<TypeParam>::hasNaN(fgm::Vector4D(value, value, value, value)));
}

/** @} */
