/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify @ref fgm::Mat4 constants (@ref fgm::Mat4::EYE, @ref fgm::Mat4::ZERO).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"



template <typename T>
class Mat4Constants: public testing::Test
{};
/** @brief Test fixture for @ref fgm::Mat4 constants, parameterized @ref SupportedArithmeticTypes.*/
TYPED_TEST_SUITE(Mat4Constants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat4x4_Constant
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Mat4 constants are available at compile time. */
namespace
{
    // Verify identity matrix
    static_assert(fgm::Mat4<int>::identity()(0, 0) == 1);
    static_assert(fgm::Mat4<int>::identity()(0, 1) == 0);
    static_assert(fgm::Mat4<int>::identity()(0, 2) == 0);
    static_assert(fgm::Mat4<int>::identity()(0, 3) == 0);

    static_assert(fgm::Mat4<int>::identity()(1, 0) == 0);
    static_assert(fgm::Mat4<int>::identity()(1, 1) == 1);
    static_assert(fgm::Mat4<int>::identity()(1, 2) == 0);
    static_assert(fgm::Mat4<int>::identity()(1, 3) == 0);

    static_assert(fgm::Mat4<int>::identity()(2, 0) == 0);
    static_assert(fgm::Mat4<int>::identity()(2, 1) == 0);
    static_assert(fgm::Mat4<int>::identity()(2, 2) == 1);
    static_assert(fgm::Mat4<int>::identity()(2, 3) == 0);

    static_assert(fgm::Mat4<int>::identity()(3, 0) == 0);
    static_assert(fgm::Mat4<int>::identity()(3, 1) == 0);
    static_assert(fgm::Mat4<int>::identity()(3, 2) == 0);
    static_assert(fgm::Mat4<int>::identity()(3, 3) == 1);


    // Verify zero matrix
    static_assert(fgm::Mat4<int>::zero()(0, 0) == 0);
    static_assert(fgm::Mat4<int>::zero()(0, 1) == 0);
    static_assert(fgm::Mat4<int>::zero()(0, 2) == 0);
    static_assert(fgm::Mat4<int>::zero()(0, 3) == 0);

    static_assert(fgm::Mat4<int>::zero()(1, 0) == 0);
    static_assert(fgm::Mat4<int>::zero()(1, 1) == 0);
    static_assert(fgm::Mat4<int>::zero()(1, 2) == 0);
    static_assert(fgm::Mat4<int>::zero()(1, 3) == 0);

    static_assert(fgm::Mat4<int>::zero()(2, 0) == 0);
    static_assert(fgm::Mat4<int>::zero()(2, 1) == 0);
    static_assert(fgm::Mat4<int>::zero()(2, 2) == 0);
    static_assert(fgm::Mat4<int>::zero()(2, 3) == 0);

    static_assert(fgm::Mat4<int>::zero()(3, 0) == 0);
    static_assert(fgm::Mat4<int>::zero()(3, 1) == 0);
    static_assert(fgm::Mat4<int>::zero()(3, 2) == 0);
    static_assert(fgm::Mat4<int>::zero()(3, 3) == 0);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Mat4::EYE returns an identity matrix. */
TYPED_TEST(Mat4Constants, Eye_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::Mat4<TypeParam>::identity()); }


/** @brief Verify that @ref fgm::Mat4::ZERO returns a zero matrix. */
TYPED_TEST(Mat4Constants, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::Mat4<TypeParam>::zero()); }

/** @} */
