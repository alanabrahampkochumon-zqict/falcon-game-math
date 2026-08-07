/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref fgm::Mat2x3 constants (@ref fgm::Mat2x3::one, @ref fgm::Mat2x3::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x3TestSetup.h"



/**
 * @addtogroup T_FGM_Mat2x3x4_Constant
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat2 Constants.
     */
    template <typename>
    class Mat2x3ConstantsTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat2x3ConstantsTests, SupportedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    /** @brief Verify that @ref fgm::Mat2x3 constants are available at compile time. */
    namespace static_tests
    {
        /// @test Verify that Mat2x3::one returns a one matrix at compile time.
        static_assert(fgm::Mat2x3<int>::one()(0, 0) == 1);
        static_assert(fgm::Mat2x3<int>::one()(0, 1) == 1);
        static_assert(fgm::Mat2x3<int>::one()(0, 2) == 1);
        static_assert(fgm::Mat2x3<int>::one()(0, 1) == 1);
        static_assert(fgm::Mat2x3<int>::one()(1, 0) == 1);
        static_assert(fgm::Mat2x3<int>::one()(1, 1) == 1);
        static_assert(fgm::Mat2x3<int>::one()(1, 2) == 1);
        static_assert(fgm::Mat2x3<int>::one()(1, 1) == 1);


        /// @test Verify that Mat2x3::zero returns a zero matrix at compile time.
        static_assert(fgm::Mat2x3<int>::zero()(0, 0) == 0);
        static_assert(fgm::Mat2x3<int>::zero()(0, 1) == 0);
        static_assert(fgm::Mat2x3<int>::zero()(0, 2) == 0);
        static_assert(fgm::Mat2x3<int>::zero()(0, 1) == 0);
        static_assert(fgm::Mat2x3<int>::zero()(1, 0) == 0);
        static_assert(fgm::Mat2x3<int>::zero()(1, 1) == 0);
        static_assert(fgm::Mat2x3<int>::zero()(1, 2) == 0);
        static_assert(fgm::Mat2x3<int>::zero()(1, 1) == 0);
    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2x3ConstantsTests, One_ReturnsOneMatrix) { EXPECT_MAT_ONE(fgm::Mat2x3<TypeParam>::one()); }


TYPED_TEST(Mat2x3ConstantsTests, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::Mat2x3<TypeParam>::zero()); }

/** @} */
