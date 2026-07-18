/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vec2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Vec2TestSetup.h>


/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Vec2UtilityParams
{
    fgm::Vec2<T> vec;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Vec2 infinity checker, parameterized by @ref VectorUtilityParams */
class Vec2InfChecker: public ::testing::TestWithParam<Vec2UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Vec2 NaN checker, parameterized by @ref VectorUtilityParams */
class Vec2NaNChecker: public ::testing::TestWithParam<Vec2UtilityParams<float>>
{};


/** @brief Test fixture for @ref fgm::Vec2 utilities, parameterized by @ref SupportedIntegralTypes */
template <typename T>
class Vec2IntegralUtility: public ::testing::Test
{};
TYPED_TEST_SUITE(Vec2IntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Vec2_Utils
 * @{
 */

/** @brief Verify that vector utilities are available at compile time. */
namespace
{
    constexpr fgm::Vec2 normVec(1.0f, 2.0f);
    constexpr fgm::Vec2 infVec(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);
    constexpr fgm::Vec2 nanVec(fgm::constants::NaN, fgm::constants::NaN);

    static_assert(normVec.hasInf() == false);
    static_assert(infVec.hasInf() == true);
    static_assert(nanVec.hasInf() == false);

    static_assert(fgm::Vec2<float>::hasInf(normVec) == false);
    static_assert(fgm::Vec2<float>::hasInf(infVec) == true);
    static_assert(fgm::Vec2<float>::hasInf(nanVec) == false);

    static_assert(normVec.hasNaN() == false);
    static_assert(infVec.hasNaN() == false);
    static_assert(nanVec.hasNaN() == true);

    static_assert(fgm::Vec2<float>::hasNaN(normVec) == false);
    static_assert(fgm::Vec2<float>::hasNaN(infVec) == false);
    static_assert(fgm::Vec2<float>::hasNaN(nanVec) == true);

} // namespace

/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Vec2::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(Vec2InfChecker, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}
INSTANTIATE_TEST_SUITE_P(Vec2InfCheckerTestSuite, Vec2InfChecker,
                         ::testing::Values(Vec2UtilityParams{ fgm::Vec2(fgm::constants::INFINITY_F, 1.0f), true },
                                           Vec2UtilityParams{ fgm::Vec2(1.0f, fgm::constants::INFINITY_F), true },
                                           Vec2UtilityParams{
                                               fgm::Vec2(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                               true },
                                           Vec2UtilityParams{ fgm::Vec2(1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Vec2::hasInf returns False for integral types. */
TYPED_TEST(Vec2IntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec2(value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Vec2::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(Vec2InfChecker, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vec2<float>::hasInf(vec));
}


/** @brief Verify that the static variant of @ref std::Vec2::hasInf returns False for integral types. */
TYPED_TEST(Vec2IntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec2<TypeParam>::hasInf(fgm::Vec2(value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Vec2::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Vec2NaNChecker, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(Vec2NaNCheckerTestSuite, Vec2NaNChecker,
                         ::testing::Values(Vec2UtilityParams{ fgm::Vec2(fgm::constants::NaN, 1.0f), true },
                                           Vec2UtilityParams{ fgm::Vec2(1.0f, fgm::constants::NaN), true },
                                           Vec2UtilityParams{ fgm::Vec2(fgm::constants::NaN, fgm::constants::NaN),
                                                                 true },
                                           Vec2UtilityParams{ fgm::Vec2(1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Vec2::hasNaN returns False for integral types. */
TYPED_TEST(Vec2IntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec2(value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Vec2::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Vec2NaNChecker, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vec2<float>::hasNaN(vec));
}


/** @brief Verify that the static variant of @ref std::Vec2::hasNaN returns False for integral types. */
TYPED_TEST(Vec2IntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec2<TypeParam>::hasNaN(fgm::Vec2(value, value)));
}

/** @} */
