/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 15, 2026
 *
 * @brief Verify @ref fgm::Matrix2D constants (@ref fgm::Matrix2D::eye, @ref fgm::Matrix2D::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix2DConstants: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Matrix2D constants, parameterized @ref SupportedArithmeticTypes.*/
TYPED_TEST_SUITE(Matrix2DConstants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Constant
 * @{
 */

/** @brief Verify that @ref fgm::Matrix2D::eye returns an identity matrix. */
TYPED_TEST(Matrix2DConstants, Eye_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::mat2d::eye<TypeParam>); }


/** @brief Verify that @ref fgm::Matrix2D::zero returns a zero matrix. */
TYPED_TEST(Matrix2DConstants, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::mat2d::zero<TypeParam>); }

/** @} */