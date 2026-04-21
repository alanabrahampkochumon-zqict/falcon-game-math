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
    } // namespace


    /** Verify that @ref fgm::isnan is available at compile time. */
    namespace
    {
        static_assert(fgm::isnan(-3.53) == false);
        static_assert(fgm::isnan(fgm::constants::NaN) == true);
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
 *             NAN TESTS              *
 *                                    *
 **************************************/

/** @brief Verify that check for NaN using @ref fgm::isnan returns true for a standard quiet NaN. */
TEST(NaNTests, NaNReturnsTrue) { EXPECT_TRUE(fgm::isnan(fgm::constants::NaN)); }


/** @brief Verify that check for NaN using @ref fgm::isnan returns false for a non-NaN. */
TEST(NaNTests, NumberReturnsFalse) { EXPECT_FALSE(fgm::isnan(3.16f)); }

/** @} */
