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

#include <fgm/common/Wrappers.h>


/**
 * @addtogroup T_Wrappers
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::abs(signed numbers).
     *
     * @tparam T The scalar type(int, float, double...) of the values.
     */
    template <typename T>
    class AbsTestUnsigned: public testing::Test
    {
    protected:
        T _value, _expectedAbsValue;

        void SetUp() override
        {
            _value            = T(-5.2891283123432);
            _expectedAbsValue = T(5.2891283123432);
        }
    };
    TYPED_TEST_SUITE(AbsTestUnsigned, SupportedSignedArithmeticTypes);


    /**
     * @brief Test fixture for @ref fgm::abs(unsigned numbers).
     *
     * @tparam T The scalar type(int, float, double...) of the values.
     */
    template <typename T>
    class AbsTest: public testing::Test
    {
    protected:
        T _value, _expectedAbsValue;

        void SetUp() override
        {
            _value            = T(5.2891283123432);
            _expectedAbsValue = T(5.2891283123432);
        }
    };
    TYPED_TEST_SUITE(AbsTest, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /** @test Verify that @ref fgm::abs return absolute value at compile time. */
        static_assert(fgm::abs(-3.53) == 3.53);
        static_assert(fgm::abs(static_cast<unsigned int>(12)) == 12);
        static_assert(fgm::abs(static_cast<char>(-3.5312893)) == 3);
        static_assert(fgm::abs(-0.0000000000053) == 0.0000000000053);
        static_assert(fgm::abs(-3) == 3);
        static_assert(fgm::abs(fgm::constants::NaN_D) != fgm::constants::NaN_D);


        /** @test Verify that @ref fgm::isnan is correct boolean at compile time. */
        static_assert(fgm::isnan(-3.53) == false);
        static_assert(fgm::isnan(fgm::constants::NaN) == true);
        static_assert(fgm::isnan(fgm::constants::NaN_D) == true);


        /** @test Verify that @ref fgm::isinf returns correct boolean at compile time. */
        static_assert(fgm::isinf(-3.53) == false);
        static_assert(fgm::isinf(3.53) == false);
        static_assert(fgm::isinf(fgm::constants::INFINITY_F) == true);
        static_assert(fgm::isinf(-fgm::constants::INFINITY_F) == true);

    } // namespace static_tests

} // namespace



/**************************************
 *              ABS TEST              *
 **************************************/

TYPED_TEST(AbsTestUnsigned, UnsignedNumbers_ReturnsAbsoluteValue)
{ testutils::EXPECT_MAG_EQ(this->_expectedAbsValue, fgm::abs(this->_value)); }


TYPED_TEST(AbsTest, SignedNumbers_ReturnsAbsoluteValue) { testutils::EXPECT_MAG_EQ(this->_expectedAbsValue, fgm::abs(this->_value)); }



/**************************************
 *            ISNAN TESTS             *
 **************************************/

/** @test Verify thatcheck for IEEE 754 NaN using @ref fgm::isnan returns true for a standard quiet NaN. */
TEST(IsNaNTests, NaNReturnsTrue) { EXPECT_TRUE(fgm::isnan(fgm::constants::NaN)); }


/** @test Verify thatcheck for IEEE 754 NaN using @ref fgm::isnan returns false for a non-NaN. */
TEST(IsNaNTests, NumberReturnsFalse) { EXPECT_FALSE(fgm::isnan(3.16f)); }



/**************************************
 *            IS INF TESTS            *
 **************************************/

/** @test Verify thatcheck for IEEE 754 infinity using @ref fgm::isinf returns true for a positive infinity. */
TEST(IsInfTests, PositiveInfinityReturnsTrue) { EXPECT_TRUE(fgm::isinf(fgm::constants::INFINITY_F)); }


/** @test Verify thatcheck for IEEE 754 infinity using @ref fgm::isinf returns true for a negative infinity. */
TEST(IsInfTests, NegativeInfinityReturnsTrue) { EXPECT_TRUE(fgm::isinf(-fgm::constants::INFINITY_F)); }


/** @test Verify thatcheck for IEEE 754 infinity using @ref fgm::isinf returns true for a non-infinity value. */
TEST(IsInfTests, NonInfiniteNumberReturnsFalse) { EXPECT_FALSE(fgm::isinf(3.16f)); }

/** @} */
