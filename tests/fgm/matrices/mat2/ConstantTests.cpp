/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 15, 2026
 *
 * @brief Verify @ref fgm::Mat2 constants (@ref fgm::Mat2::identity, @ref fgm::Mat2::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"

/**
 * @addtogroup T_FGM_Mat2x2_Constant
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
    class Mat2ConstantsTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat2ConstantsTests, SupportedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that Mat2::identity() returns an identity matrix at compile time.
        static_assert(fgm::Mat2<int>::identity()(0, 0) == 1);
        static_assert(fgm::Mat2<int>::identity()(0, 1) == 0);
        static_assert(fgm::Mat2<int>::identity()(1, 0) == 0);
        static_assert(fgm::Mat2<int>::identity()(1, 1) == 1);

        /// @test Verify that Mat2::zero() returns a zero matrix at compile time.
        static_assert(fgm::Mat2<int>::zero()(0, 0) == 0);
        static_assert(fgm::Mat2<int>::zero()(0, 1) == 0);
        static_assert(fgm::Mat2<int>::zero()(1, 0) == 0);
        static_assert(fgm::Mat2<int>::zero()(1, 1) == 0);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2ConstantsTests, Identity_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::Mat2<TypeParam>::identity()); }


TYPED_TEST(Mat2ConstantsTests, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::Mat2<TypeParam>::zero()); }

/** @} */
