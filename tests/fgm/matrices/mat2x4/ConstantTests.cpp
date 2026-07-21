/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref fgm::Mat2x4 constants (@ref fgm::Mat2x4::one, @ref fgm::Mat2x4::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x4TestSetup.h"



template <typename T>
class Mat2x4Constants: public testing::Test
{};
/** @brief Test fixture for @ref fgm::Mat2x4 constants, parameterized @ref SupportedArithmeticTypes.*/
TYPED_TEST_SUITE(Mat2x4Constants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x4x4_Constant
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Mat2x4 constants are available at compile time. */
namespace
{
    // Verify one matrix
    static_assert(fgm::Mat2x4<int>::one()(0, 0) == 1);
    static_assert(fgm::Mat2x4<int>::one()(0, 1) == 1);
    static_assert(fgm::Mat2x4<int>::one()(0, 2) == 1);
    static_assert(fgm::Mat2x4<int>::one()(0, 1) == 1);
    static_assert(fgm::Mat2x4<int>::one()(1, 0) == 1);
    static_assert(fgm::Mat2x4<int>::one()(1, 1) == 1);
    static_assert(fgm::Mat2x4<int>::one()(1, 2) == 1);
    static_assert(fgm::Mat2x4<int>::one()(1, 1) == 1);


    // Verify zero matrix
    static_assert(fgm::Mat2x4<int>::zero()(0, 0) == 0);
    static_assert(fgm::Mat2x4<int>::zero()(0, 1) == 0);
    static_assert(fgm::Mat2x4<int>::zero()(0, 2) == 0);
    static_assert(fgm::Mat2x4<int>::zero()(0, 1) == 0);
    static_assert(fgm::Mat2x4<int>::zero()(1, 0) == 0);
    static_assert(fgm::Mat2x4<int>::zero()(1, 1) == 0);
    static_assert(fgm::Mat2x4<int>::zero()(1, 2) == 0);
    static_assert(fgm::Mat2x4<int>::zero()(1, 1) == 0);
} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that fgm::Mat2x4::one returns an identity matrix. */
TYPED_TEST(Mat2x4Constants, One_ReturnsIdentityMatrix) { EXPECT_MAT_ONE(fgm::Mat2x4<TypeParam>::one()); }


/** @brief Verify that fgm::Mat2x4::zero returns a zero matrix. */
TYPED_TEST(Mat2x4Constants, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::Mat2x4<TypeParam>::zero()); }

/** @} */
