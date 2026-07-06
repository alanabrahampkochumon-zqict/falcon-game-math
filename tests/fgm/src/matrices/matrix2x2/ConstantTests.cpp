/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 15, 2026
 *
 * @brief Verify @ref fgm::Matrix2 constants (@ref fgm::Matrix2::EYE, @ref fgm::Matrix2::ZERO).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix2Constants: public testing::Test
{};
/** @brief Test fixture for @ref fgm::Matrix2 constants, parameterized @ref SupportedArithmeticTypes.*/
TYPED_TEST_SUITE(Matrix2Constants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Constant
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Matrix2 constants are available at compile time. */
namespace
{
    // Verify identity matrix
    static_assert(fgm::Matrix2<int>::EYE()(0, 0) == 1);
    static_assert(fgm::Matrix2<int>::EYE()(0, 1) == 0);
    static_assert(fgm::Matrix2<int>::EYE()(1, 0) == 0);
    static_assert(fgm::Matrix2<int>::EYE()(1, 1) == 1);

    // Verify zero matrix
    static_assert(fgm::Matrix2<int>::ZERO()(0, 0) == 0);
    static_assert(fgm::Matrix2<int>::ZERO()(0, 1) == 0);
    static_assert(fgm::Matrix2<int>::ZERO()(1, 0) == 0);
    static_assert(fgm::Matrix2<int>::ZERO()(1, 1) == 0);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Matrix2::EYE returns an identity matrix. */
TYPED_TEST(Matrix2Constants, Eye_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::Matrix2<TypeParam>::EYE()); }


/** @brief Verify that @ref fgm::Matrix2::ZERO returns a zero matrix. */
TYPED_TEST(Matrix2Constants, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::Matrix2<TypeParam>::ZERO()); }

/** @} */
