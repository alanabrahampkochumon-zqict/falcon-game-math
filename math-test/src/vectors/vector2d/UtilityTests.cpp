/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vector2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Vector2TestSetup.h>


/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Vector2UtilityParams
{
    fgm::Vector2<T> vec;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Vector2 infinity checker, parameterized by @ref VectorUtilityParams */
class Vector2InfChecker: public ::testing::TestWithParam<Vector2UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Vector2 NaN checker, parameterized by @ref VectorUtilityParams */
class Vector2NaNChecker: public ::testing::TestWithParam<Vector2UtilityParams<float>>
{};


/** @brief Test fixture for @ref fgm::Vector2 utilities, parameterized by @ref SupportedIntegralTypes */
template <typename T>
class Vector2IntegralUtility: public ::testing::Test
{};
TYPED_TEST_SUITE(Vector2IntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Vec2_Utils
 * @{
 */

/** @brief Verify that vector utilities are available at compile time. */
namespace
{
    constexpr fgm::Vector2 normVec(1.0f, 2.0f);
    constexpr fgm::Vector2 infVec(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);
    constexpr fgm::Vector2 nanVec(fgm::constants::NaN, fgm::constants::NaN);

    static_assert(normVec.hasInf() == false);
    static_assert(infVec.hasInf() == true);
    static_assert(nanVec.hasInf() == false);

    static_assert(fgm::Vector2<float>::hasInf(normVec) == false);
    static_assert(fgm::Vector2<float>::hasInf(infVec) == true);
    static_assert(fgm::Vector2<float>::hasInf(nanVec) == false);

    static_assert(normVec.hasNaN() == false);
    static_assert(infVec.hasNaN() == false);
    static_assert(nanVec.hasNaN() == true);

    static_assert(fgm::Vector2<float>::hasNaN(normVec) == false);
    static_assert(fgm::Vector2<float>::hasNaN(infVec) == false);
    static_assert(fgm::Vector2<float>::hasNaN(nanVec) == true);

} // namespace

/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Vector2::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(Vector2InfChecker, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Vector2InfCheckerTestSuite, Vector2InfChecker,
    ::testing::Values(Vector2UtilityParams{ fgm::Vector2(fgm::constants::INFINITY_F, 1.0f), true },
                      Vector2UtilityParams{ fgm::Vector2(1.0f, fgm::constants::INFINITY_F), true },
                      Vector2UtilityParams{ fgm::Vector2(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                             true },
                      Vector2UtilityParams{ fgm::Vector2(1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Vector2::hasInf returns False for integral types. */
TYPED_TEST(Vector2IntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector2(value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Vector2::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(Vector2InfChecker, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vector2<float>::hasInf(vec));
}


/** @brief Verify that the static variant of @ref std::Vector2::hasInf returns False for integral types. */
TYPED_TEST(Vector2IntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector2<TypeParam>::hasInf(fgm::Vector2(value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Vector2::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Vector2NaNChecker, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(Vector2NaNCheckerTestSuite, Vector2NaNChecker,
                         ::testing::Values(Vector2UtilityParams{ fgm::Vector2(fgm::constants::NaN, 1.0f), true },
                                           Vector2UtilityParams{ fgm::Vector2(1.0f, fgm::constants::NaN), true },
                                           Vector2UtilityParams{
                                               fgm::Vector2(fgm::constants::NaN, fgm::constants::NaN), true },
                                           Vector2UtilityParams{ fgm::Vector2(1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Vector2::hasNaN returns False for integral types. */
TYPED_TEST(Vector2IntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector2(value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Vector2::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Vector2NaNChecker, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vector2<float>::hasNaN(vec));
}


/** @brief Verify that the static variant of @ref std::Vector2::hasNaN returns False for integral types. */
TYPED_TEST(Vector2IntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vector2<TypeParam>::hasNaN(fgm::Vector2(value, value)));
}

/** @} */
