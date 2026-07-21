/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref fgm::Vec3 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Vec3TestSetup.h>


/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Vec3UtilityParams
{
    fgm::Vec3<T> vec;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Vec3 infinity checker, parameterized by @ref VectorUtilityParams */
class Vec3InfChecker: public ::testing::TestWithParam<Vec3UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Vec3 NaN checker, parameterized by @ref VectorUtilityParams */
class Vec3NaNChecker: public ::testing::TestWithParam<Vec3UtilityParams<float>>
{};


/** @brief Test fixture for @ref fgm::Vec3 utilities, parameterized by @ref SupportedIntegralTypes */
template <typename T>
class Vec3IntegralUtility: public ::testing::Test
{};
TYPED_TEST_SUITE(Vec3IntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Vec3_Utils
 * @{
 */

/** @brief Verify that vector utilities are available at compile time. */
namespace
{
    constexpr fgm::Vec3 normVec(1.0f, 2.0f, 3.0f);
    constexpr fgm::Vec3 infVec(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);
    constexpr fgm::Vec3 nanVec(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN);

    static_assert(normVec.hasInf() == false);
    static_assert(infVec.hasInf() == true);
    static_assert(nanVec.hasInf() == false);

    static_assert(fgm::Vec3<float>::hasInf(normVec) == false);
    static_assert(fgm::Vec3<float>::hasInf(infVec) == true);
    static_assert(fgm::Vec3<float>::hasInf(nanVec) == false);

    static_assert(normVec.hasNaN() == false);
    static_assert(infVec.hasNaN() == false);
    static_assert(nanVec.hasNaN() == true);

    static_assert(fgm::Vec3<float>::hasNaN(normVec) == false);
    static_assert(fgm::Vec3<float>::hasNaN(infVec) == false);
    static_assert(fgm::Vec3<float>::hasNaN(nanVec) == true);

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Vec3::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(Vec3InfChecker, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}
INSTANTIATE_TEST_SUITE_P(Vec3InfCheckerTestSuite, Vec3InfChecker,
                         ::testing::Values(Vec3UtilityParams{ fgm::Vec3(fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                                           Vec3UtilityParams{ fgm::Vec3(1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                                           Vec3UtilityParams{ fgm::Vec3(1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                                           Vec3UtilityParams{ fgm::Vec3(fgm::constants::INFINITY_F,
                                                                        fgm::constants::INFINITY_F,
                                                                        fgm::constants::INFINITY_F),
                                                              true },
                                           Vec3UtilityParams{ fgm::Vec3(1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Vec3::hasInf returns False for integral types. */
TYPED_TEST(Vec3IntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec3(value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Vec3::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(Vec3InfChecker, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vec3<float>::hasInf(vec));
}


/** @brief Verify that the static variant of @ref std::Vec3::hasInf returns False for integral types. */
TYPED_TEST(Vec3IntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec3<TypeParam>::hasInf(fgm::Vec3(value, value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Vec3::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Vec3NaNChecker, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(Vec3NaNCheckerTestSuite, Vec3NaNChecker,
                         ::testing::Values(Vec3UtilityParams{ fgm::Vec3(fgm::constants::NaN, 1.0f, 1.0f), true },
                                           Vec3UtilityParams{ fgm::Vec3(1.0f, fgm::constants::NaN, 1.0f), true },
                                           Vec3UtilityParams{ fgm::Vec3(1.0f, 1.0f, fgm::constants::NaN), true },
                                           Vec3UtilityParams{
                                               fgm::Vec3(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN),
                                               true },
                                           Vec3UtilityParams{ fgm::Vec3(1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Vec3::hasNaN returns False for integral types. */
TYPED_TEST(Vec3IntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec3(value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Vec3::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Vec3NaNChecker, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vec3<float>::hasNaN(vec));
}


/** @brief Verify that the static variant of @ref std::Vec3::hasNaN returns False for integral types. */
TYPED_TEST(Vec3IntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec3<TypeParam>::hasNaN(fgm::Vec3(value, value, value)));
}

/** @} */
