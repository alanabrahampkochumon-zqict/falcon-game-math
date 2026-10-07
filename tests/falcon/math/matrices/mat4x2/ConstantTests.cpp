/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref fgm::Mat4x2 constants (@ref fgm::Mat4x2::one, @ref fgm::Mat4x2::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x2TestSetup.h"



/**
 * @addtogroup T_FGM_Mat4x2_Constant
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat4x2 Constants.
     */
    template <typename>
    class Mat4x2ConstantsTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat4x2ConstantsTests, SupportedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that Mat4::one() returns an one matrix at compile time.
        static_assert(fgm::Mat4x2<int>::one()(0, 0) == 1);
        static_assert(fgm::Mat4x2<int>::one()(0, 1) == 1);

        static_assert(fgm::Mat4x2<int>::one()(1, 0) == 1);
        static_assert(fgm::Mat4x2<int>::one()(1, 1) == 1);

        static_assert(fgm::Mat4x2<int>::one()(2, 0) == 1);
        static_assert(fgm::Mat4x2<int>::one()(2, 1) == 1);

        static_assert(fgm::Mat4x2<int>::one()(3, 0) == 1);
        static_assert(fgm::Mat4x2<int>::one()(3, 1) == 1);


        /// @test Verify that Mat4::zero() returns a zero matrix at compile time.
        static_assert(fgm::Mat4x2<int>::zero()(0, 0) == 0);
        static_assert(fgm::Mat4x2<int>::zero()(0, 1) == 0);

        static_assert(fgm::Mat4x2<int>::zero()(1, 0) == 0);
        static_assert(fgm::Mat4x2<int>::zero()(1, 1) == 0);

        static_assert(fgm::Mat4x2<int>::zero()(2, 0) == 0);
        static_assert(fgm::Mat4x2<int>::zero()(2, 1) == 0);

        static_assert(fgm::Mat4x2<int>::zero()(3, 0) == 0);
        static_assert(fgm::Mat4x2<int>::zero()(3, 1) == 0);
    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4x2ConstantsTests, One_ReturnsOneMatrix) { EXPECT_MAT_ONE(fgm::Mat4x2<TypeParam>::one()); }


TYPED_TEST(Mat4x2ConstantsTests, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::Mat4x2<TypeParam>::zero()); }

/** @} */
