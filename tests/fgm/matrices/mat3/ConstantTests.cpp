/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 23, 2026
 *
 * @brief Verify @ref fgm::Mat3 constants (@ref fgm::Mat3::identity, @ref fgm::Mat3::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"



template <typename T>
class Mat3Constants: public testing::Test
{};
/** @brief Test fixture for @ref fgm::Mat3 constants, parameterized @ref SupportedArithmeticTypes.*/
TYPED_TEST_SUITE(Mat3Constants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat3x3_Constant
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Mat3 constants are available at compile time. */
namespace
{
    // Verify identity matrix
    static_assert(fgm::Mat3<int>::identity()(0, 0) == 1);
    static_assert(fgm::Mat3<int>::identity()(0, 1) == 0);
    static_assert(fgm::Mat3<int>::identity()(0, 2) == 0);

    static_assert(fgm::Mat3<int>::identity()(1, 0) == 0);
    static_assert(fgm::Mat3<int>::identity()(1, 1) == 1);
    static_assert(fgm::Mat3<int>::identity()(1, 2) == 0);

    static_assert(fgm::Mat3<int>::identity()(2, 0) == 0);
    static_assert(fgm::Mat3<int>::identity()(2, 1) == 0);
    static_assert(fgm::Mat3<int>::identity()(2, 2) == 1);


    // Verify zero matrix
    static_assert(fgm::Mat3<int>::zero()(0, 0) == 0);
    static_assert(fgm::Mat3<int>::zero()(0, 1) == 0);
    static_assert(fgm::Mat3<int>::zero()(0, 2) == 0);

    static_assert(fgm::Mat3<int>::zero()(1, 0) == 0);
    static_assert(fgm::Mat3<int>::zero()(1, 1) == 0);
    static_assert(fgm::Mat3<int>::zero()(1, 2) == 0);

    static_assert(fgm::Mat3<int>::zero()(2, 0) == 0);
    static_assert(fgm::Mat3<int>::zero()(2, 1) == 0);
    static_assert(fgm::Mat3<int>::zero()(2, 2) == 0);
} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that fgm::Mat3::identity returns an identity matrix. */
TYPED_TEST(Mat3Constants, Identity_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::Mat3<TypeParam>::identity()); }


/** @brief Verify that fgm::Mat3::zero returns a zero matrix. */
TYPED_TEST(Mat3Constants, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::Mat3<TypeParam>::zero()); }

/** @} */
