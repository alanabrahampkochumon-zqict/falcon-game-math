/**
 * @file WrapperTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 20, 2026
 *
 * @brief Verify @ref fgm wrapper functions logic and static evaluation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/VectorUtils.h"

#include <common/Wrappers.h>


template <typename T>
class AbsTest: public ::testing::Test
{
protected:
    T _value, _expectedAbsValue;

    void SetUp() override
    {
        _value = T(-5.2891283123432);
        _expectedAbsValue = T(5.2891283123432);
    }
};
/** @brief Test fixture for @ref fgm::abs, parameterized by @ref SupportSignedTypes. */
TYPED_TEST_SUITE(AbsTest, SupportedSignedArithmeticTypes);


/**
 * @addtogroup T_Wrappers
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS           *
 *                                    *
 **************************************/
namespace
{
    /** Verify that @ref fgm::abs is available at compile time. */
    namespace
    {
        static_assert(fgm::abs(-3.53) == 3.53);
        static_assert(fgm::abs(static_cast<char>(-3.5312893)) == 3);
        static_assert(fgm::abs(-0.0000000000053) == 0.0000000000053);
        static_assert(fgm::abs(-3) == 3);
        static_assert(fgm::abs(fgm::constants::NaN_D) != fgm::constants::NaN_D);
    } // namespace


    /** Verify that @ref fgm::isnan is available at compile time. */
    namespace
    {
        static_assert(fgm::isnan(-3.53) == false);
        static_assert(fgm::isnan(fgm::constants::NaN) == true);
        static_assert(fgm::isnan(fgm::constants::NaN_D) == true);
    } // namespace


    /** Verify that @ref fgm::isinf is available at compile time. */
    namespace
    {
        static_assert(fgm::isinf(-3.53) == false);
        static_assert(fgm::isinf(3.53) == false);
        static_assert(fgm::isinf(fgm::constants::INFINITY_F) == true);
        static_assert(fgm::isinf(-fgm::constants::INFINITY_F) == true);
    } // namespace

} // namespace



/**************************************
 *                                    *
 *              ABS TEST              *
 *                                    *
 **************************************/

/** @brief Verify that taking absolute value using @ref fgm::abs returns the absolute value. */
TYPED_TEST(AbsTest, ReturnsAbsoluteValue) { testutils::EXPECT_MAG_EQ(this->_expectedAbsValue, fgm::abs(this->_value)); }



/**************************************
 *                                    *
 *            ISNAN TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that check for IEEE 754 NaN using @ref fgm::isnan returns true for a standard quiet NaN. */
TEST(IsNaNTests, NaNReturnsTrue) { EXPECT_TRUE(fgm::isnan(fgm::constants::NaN)); }


/** @brief Verify that check for IEEE 754 NaN using @ref fgm::isnan returns false for a non-NaN. */
TEST(IsNaNTests, NumberReturnsFalse) { EXPECT_FALSE(fgm::isnan(3.16f)); }



/**************************************
 *                                    *
 *            ISINF TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that check for IEEE 754 infinity using @ref fgm::isinf returns true for a positive infinity. */
TEST(IsInfTests, PositiveInfinityReturnsTrue) { EXPECT_TRUE(fgm::isinf(fgm::constants::INFINITY_F)); }


/** @brief Verify that check for IEEE 754 infinity using @ref fgm::isinf returns true for a negative infinity. */
TEST(IsInfTests, NegativeInfinityReturnsTrue) { EXPECT_TRUE(fgm::isinf(-fgm::constants::INFINITY_F)); }


/** @brief Verify that check for IEEE 754 infinity using @ref fgm::isinf returns true for a non-infinity value. */
TEST(IsInfTests, NonInfiniteNumberReturnsFalse) { EXPECT_FALSE(fgm::isinf(3.16f)); }

/** @} */
