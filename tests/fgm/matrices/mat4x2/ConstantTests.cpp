/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref fgm::Mat3x2 constants (@ref fgm::Mat3x2::EYE, @ref fgm::Mat3x2::ZERO).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x2TestSetup.h"



template <typename T>
class Mat3x2Constants: public testing::Test
{};
/** @brief Test fixture for @ref fgm::Mat3x2 constants, parameterized @ref SupportedArithmeticTypes.*/
TYPED_TEST_SUITE(Mat3x2Constants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat3x2x4_Constant
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Mat3x2 constants are available at compile time. */
namespace
{
    // Verify one matrix
    static_assert(fgm::Mat3x2<int>::one()(0, 0) == 1);
    static_assert(fgm::Mat3x2<int>::one()(0, 1) == 1);
    static_assert(fgm::Mat3x2<int>::one()(0, 1) == 1);
    static_assert(fgm::Mat3x2<int>::one()(1, 0) == 1);
    static_assert(fgm::Mat3x2<int>::one()(1, 1) == 1);
    static_assert(fgm::Mat3x2<int>::one()(1, 1) == 1);
    static_assert(fgm::Mat3x2<int>::one()(2, 0) == 1);
    static_assert(fgm::Mat3x2<int>::one()(2, 1) == 1);
    static_assert(fgm::Mat3x2<int>::one()(2, 1) == 1);


    // Verify zero matrix
    static_assert(fgm::Mat3x2<int>::zero()(0, 0) == 0);
    static_assert(fgm::Mat3x2<int>::zero()(0, 1) == 0);
    static_assert(fgm::Mat3x2<int>::zero()(0, 1) == 0);
    static_assert(fgm::Mat3x2<int>::zero()(1, 0) == 0);
    static_assert(fgm::Mat3x2<int>::zero()(1, 1) == 0);
    static_assert(fgm::Mat3x2<int>::zero()(1, 1) == 0);
    static_assert(fgm::Mat3x2<int>::zero()(2, 0) == 0);
    static_assert(fgm::Mat3x2<int>::zero()(2, 1) == 0);
    static_assert(fgm::Mat3x2<int>::zero()(2, 1) == 0);
} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that fgm::Mat3x2::one returns an identity matrix. */
TYPED_TEST(Mat3x2Constants, One_ReturnsIdentityMatrix) { EXPECT_MAT_ONE(fgm::Mat3x2<TypeParam>::one()); }


/** @brief Verify that fgm::Mat3x2::zero returns a zero matrix. */
TYPED_TEST(Mat3x2Constants, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::Mat3x2<TypeParam>::zero()); }

/** @} */
