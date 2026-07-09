/**
 * @file UtilsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 28, 2026
 *
 * @brief Verify @ref fgm::utils function's logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CommonSetup.h"
#include "utils/VectorUtils.h"

#include <fgm/common/Utils.h>


template <typename T>
class FGMDiffAbs: public testing::Test
{};
/** @brief Test fixture for @ref fgm::utils::diffAbs, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(FGMDiffAbs, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Utils
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/
namespace
{
    /** @brief Verify that @ref fgm::utils::diffAbs is available at compile time. */
    namespace
    {
        static_assert(fgm::utils::diffAbs(1000, 100) == 900);
        static_assert(fgm::utils::diffAbs(100, 1000) == 900);
    } // namespace


    // namespace
    //{
    //     static_assert(fgm::utils::sqrt(4) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    //     static_assert(fgm::utils::sqrt(2.0) - 1.41421356237 <= fgm::Config::DOUBLE_EPSILON);
    //     static_assert(fgm::utils::sqrt(4) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    //     static_assert(fgm::utils::sqrt(4) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    //     static_assert(fgm::utils::sqrt(4) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    //     static_assert(fgm::utils::sqrt(4) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    //     static_assert(fgm::utils::sqrt(4) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    // }
} // namespace


/**
 * @brief Verify that @ref fgm::utils::diffAbs returns absolute difference without overflow when
 *        first operand is greater than second operand.
 */
TYPED_TEST(FGMDiffAbs, ReturnsAbsoluteValueWithUnderflow_WhenAGreaterThanB)
{
    const auto a      = TypeParam(12);
    const auto b      = TypeParam(7);
    const auto result = TypeParam(5);
    testutils::EXPECT_MAG_EQ(result, fgm::utils::diffAbs(a, b));
}


/**
 * @brief Verify that @ref fgm::utils::diffAbs returns absolute difference without overflow when
 *        second operand is greater than first operand.
 */
TYPED_TEST(FGMDiffAbs, ReturnsAbsoluteValueWithUnderflow_WhenBGreaterThanA)
{
    const auto a      = TypeParam(7);
    const auto b      = TypeParam(12);
    const auto result = TypeParam(5);
    testutils::EXPECT_MAG_EQ(result, fgm::utils::diffAbs(a, b));
}


/**
 * @brief Verify that @ref fgm::utils::diffAbs returns zero when
 *        first operand is equal to second operand.
 */
TYPED_TEST(FGMDiffAbs, ReturnsAbsoluteValueWithUnderflow_WhenAEqualsB)
{
    const auto a      = TypeParam(12);
    const auto b      = TypeParam(12);
    const auto result = TypeParam(0);
    testutils::EXPECT_MAG_EQ(result, fgm::utils::diffAbs(a, b));
}

/** @} */
