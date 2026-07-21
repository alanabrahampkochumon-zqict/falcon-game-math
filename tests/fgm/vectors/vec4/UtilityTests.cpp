/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 30, 2026
 *
 * @brief Verify @ref fgm::Vec4 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Vec4TestSetup.h>


/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Vec4UtilityParams
{
    fgm::Vec4<T> vec;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Vec4 infinity checker, parameterized by @ref VectorUtilityParams */
class Vec4InfCheckerTests: public ::testing::TestWithParam<Vec4UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Vec4 NaN checker, parameterized by @ref VectorUtilityParams */
class Vec4NaNCheckerTests: public ::testing::TestWithParam<Vec4UtilityParams<float>>
{};


/** @brief Test fixture for @ref fgm::Vec4 utilities, parameterized by @ref SupportedIntegralTypes */
template <typename T>
class Vec4IntegralUtilityTests: public ::testing::Test
{};
TYPED_TEST_SUITE(Vec4IntegralUtilityTests, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Vec4_Utils
 * @{
 */

/** @brief Verify that vector utilities are available at compile time. */
namespace
{
    constexpr fgm::Vec4 normVec(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr fgm::Vec4 infVec(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                               fgm::constants::INFINITY_F);
    constexpr fgm::Vec4 nanVec(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN);

    static_assert(normVec.hasInf() == false);
    static_assert(infVec.hasInf() == true);
    static_assert(nanVec.hasInf() == false);

    static_assert(fgm::Vec4<float>::hasInf(normVec) == false);
    static_assert(fgm::Vec4<float>::hasInf(infVec) == true);
    static_assert(fgm::Vec4<float>::hasInf(nanVec) == false);

    static_assert(normVec.hasNaN() == false);
    static_assert(infVec.hasNaN() == false);
    static_assert(nanVec.hasNaN() == true);

    static_assert(fgm::Vec4<float>::hasNaN(normVec) == false);
    static_assert(fgm::Vec4<float>::hasNaN(infVec) == false);
    static_assert(fgm::Vec4<float>::hasNaN(nanVec) == true);

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Vec4::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(Vec4InfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Vec4InfCheckerTestSuite, Vec4InfCheckerTests,
    ::testing::Values(Vec4UtilityParams{ fgm::Vec4(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
                      Vec4UtilityParams{ fgm::Vec4(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                      Vec4UtilityParams{ fgm::Vec4(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Vec4UtilityParams{ fgm::Vec4(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Vec4UtilityParams{ fgm::Vec4(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                      Vec4UtilityParams{ fgm::Vec4(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                   fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                         true },
                      Vec4UtilityParams{ fgm::Vec4(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Vec4::hasInf returns False for integral types. */
TYPED_TEST(Vec4IntegralUtilityTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec4(value, value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Vec4::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(Vec4InfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vec4<float>::hasInf(vec));
}


/** @brief Verify that the static variant of @ref std::Vec4::hasInf returns False for integral types. */
TYPED_TEST(Vec4IntegralUtilityTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec4<TypeParam>::hasInf(fgm::Vec4(value, value, value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Vec4::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Vec4NaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(Vec4NaNCheckerTestSuite, Vec4NaNCheckerTests,
                         ::testing::Values(Vec4UtilityParams{ fgm::Vec4(fgm::constants::NaN, 1.0f, 1.0f, 1.0f), true },
                                           Vec4UtilityParams{ fgm::Vec4(1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
                                           Vec4UtilityParams{ fgm::Vec4(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                                           Vec4UtilityParams{ fgm::Vec4(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                                           Vec4UtilityParams{ fgm::Vec4(1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
                                           Vec4UtilityParams{ fgm::Vec4(fgm::constants::NaN, fgm::constants::NaN,
                                                                        fgm::constants::NaN, fgm::constants::NaN),
                                                              true },
                                           Vec4UtilityParams{ fgm::Vec4(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Vec4::hasNaN returns False for integral types. */
TYPED_TEST(Vec4IntegralUtilityTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec4(value, value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Vec4::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Vec4NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Vec4<float>::hasNaN(vec));
}


/** @brief Verify that the static variant of @ref std::Vec4::hasNaN returns False for integral types. */
TYPED_TEST(Vec4IntegralUtilityTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Vec4<TypeParam>::hasNaN(fgm::Vec4(value, value, value, value)));
}

/** @} */
