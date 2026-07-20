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



template <typename T>
class Mat2Constants: public testing::Test
{};
/** @brief Test fixture for @ref fgm::Mat2 constants, parameterized @ref SupportedArithmeticTypes.*/
TYPED_TEST_SUITE(Mat2Constants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Constant
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Mat2 constants are available at compile time. */
namespace
{
    // Verify identity matrix
    static_assert(fgm::Mat2<int>::identity()(0, 0) == 1);
    static_assert(fgm::Mat2<int>::identity()(0, 1) == 0);
    static_assert(fgm::Mat2<int>::identity()(1, 0) == 0);
    static_assert(fgm::Mat2<int>::identity()(1, 1) == 1);

    // Verify zero matrix
    static_assert(fgm::Mat2<int>::zero()(0, 0) == 0);
    static_assert(fgm::Mat2<int>::zero()(0, 1) == 0);
    static_assert(fgm::Mat2<int>::zero()(1, 0) == 0);
    static_assert(fgm::Mat2<int>::zero()(1, 1) == 0);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that fgm::Mat2::eye returns an identity matrix. */
TYPED_TEST(Mat2Constants, Identity_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::Mat2<TypeParam>::identity()); }


/** @brief Verify that fgm::Mat2::zero returns a zero matrix. */
TYPED_TEST(Mat2Constants, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::Mat2<TypeParam>::zero()); }

/** @} */
