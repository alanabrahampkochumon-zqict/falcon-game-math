/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 23, 2026
 *
 * @brief Verify @ref fgm::Matrix3 constants (@ref fgm::Matrix3::EYE, @ref fgm::Matrix3::ZERO).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix3Constants: public testing::Test
{};
/** @brief Test fixture for @ref fgm::Matrix3 constants, parameterized @ref SupportedArithmeticTypes.*/
TYPED_TEST_SUITE(Matrix3Constants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat3x3_Constant
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Matrix3 constants are available at compile time. */
namespace
{
    // Verify identity matrix
    static_assert(fgm::Matrix4<int>::EYE()(0, 0) == 1);
    static_assert(fgm::Matrix3<int>::EYE()(0, 1) == 0);
    static_assert(fgm::Matrix3<int>::EYE()(0, 2) == 0);

    static_assert(fgm::Matrix3<int>::EYE()(1, 0) == 0);
    static_assert(fgm::Matrix3<int>::EYE()(1, 1) == 1);
    static_assert(fgm::Matrix3<int>::EYE()(1, 2) == 0);

    static_assert(fgm::Matrix3<int>::EYE()(2, 0) == 0);
    static_assert(fgm::Matrix3<int>::EYE()(2, 1) == 0);
    static_assert(fgm::Matrix3<int>::EYE()(2, 2) == 1);


    // Verify zero matrix
    static_assert(fgm::Matrix3<int>::ZERO()(0, 0) == 0);
    static_assert(fgm::Matrix3<int>::ZERO()(0, 1) == 0);
    static_assert(fgm::Matrix3<int>::ZERO()(0, 2) == 0);

    static_assert(fgm::Matrix3<int>::ZERO()(1, 0) == 0);
    static_assert(fgm::Matrix3<int>::ZERO()(1, 1) == 0);
    static_assert(fgm::Matrix3<int>::ZERO()(1, 2) == 0);

    static_assert(fgm::Matrix3<int>::ZERO()(2, 0) == 0);
    static_assert(fgm::Matrix3<int>::ZERO()(2, 1) == 0);
    static_assert(fgm::Matrix3<int>::ZERO()(2, 2) == 0);
} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Matrix3::EYE returns an identity matrix. */
TYPED_TEST(Matrix3Constants, Eye_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::Matrix3<TypeParam>::EYE()); }


/** @brief Verify that @ref fgm::Matrix3::ZERO returns a zero matrix. */
TYPED_TEST(Matrix3Constants, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::Matrix3<TypeParam>::ZERO()); }

/** @} */
