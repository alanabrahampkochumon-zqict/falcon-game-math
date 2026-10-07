/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref fgm::Mat3x4 constants (@ref fgm::Mat3x4::one, @ref fgm::Mat3x4::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x4TestSetup.h"


/**
 * @addtogroup T_FGM_Mat3x4_Constant
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat3x4 Constants.
     */
    template <typename>
    class Mat3x4ConstantsTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat3x4ConstantsTests, SupportedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that Mat3x4::one() returns an one matrix at compile time.
        static_assert(fgm::Mat3x4<int>::one()(0, 0) == 1);
        static_assert(fgm::Mat3x4<int>::one()(0, 1) == 1);
        static_assert(fgm::Mat3x4<int>::one()(0, 2) == 1);
        static_assert(fgm::Mat3x4<int>::one()(0, 1) == 1);
        static_assert(fgm::Mat3x4<int>::one()(1, 0) == 1);
        static_assert(fgm::Mat3x4<int>::one()(1, 1) == 1);
        static_assert(fgm::Mat3x4<int>::one()(1, 2) == 1);
        static_assert(fgm::Mat3x4<int>::one()(1, 1) == 1);
        static_assert(fgm::Mat3x4<int>::one()(2, 0) == 1);
        static_assert(fgm::Mat3x4<int>::one()(2, 1) == 1);
        static_assert(fgm::Mat3x4<int>::one()(2, 2) == 1);
        static_assert(fgm::Mat3x4<int>::one()(2, 1) == 1);


        /// @test Verify that Mat3x4::zero() returns a zero matrix at compile time.
        static_assert(fgm::Mat3x4<int>::zero()(0, 0) == 0);
        static_assert(fgm::Mat3x4<int>::zero()(0, 1) == 0);
        static_assert(fgm::Mat3x4<int>::zero()(0, 2) == 0);
        static_assert(fgm::Mat3x4<int>::zero()(0, 1) == 0);
        static_assert(fgm::Mat3x4<int>::zero()(1, 0) == 0);
        static_assert(fgm::Mat3x4<int>::zero()(1, 1) == 0);
        static_assert(fgm::Mat3x4<int>::zero()(1, 2) == 0);
        static_assert(fgm::Mat3x4<int>::zero()(1, 1) == 0);
        static_assert(fgm::Mat3x4<int>::zero()(2, 0) == 0);
        static_assert(fgm::Mat3x4<int>::zero()(2, 1) == 0);
        static_assert(fgm::Mat3x4<int>::zero()(2, 2) == 0);
        static_assert(fgm::Mat3x4<int>::zero()(2, 1) == 0);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3x4ConstantsTests, One_ReturnsOneMatrix) { EXPECT_MAT_ONE(fgm::Mat3x4<TypeParam>::one()); }


TYPED_TEST(Mat3x4ConstantsTests, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::Mat3x4<TypeParam>::zero()); }

/** @} */
