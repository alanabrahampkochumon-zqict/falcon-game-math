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

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Matrix2D constants are available at compile time. */
namespace 
{
    // Verify identity matrix
    static_assert(fgm::mat2d::eye<int>(0, 0) == 1);
    static_assert(fgm::mat2d::eye<int>(0, 1) == 0);
    static_assert(fgm::mat2d::eye<int>(1, 0) == 0);
    static_assert(fgm::mat2d::eye<int>(1, 1) == 1);


    // Verify identity matrix static factory
    static_assert(fgm::Matrix2D<int>::eye()(0, 0) == 1);
    static_assert(fgm::Matrix2D<int>::eye()(0, 1) == 0);
    static_assert(fgm::Matrix2D<int>::eye()(1, 0) == 0);
    static_assert(fgm::Matrix2D<int>::eye()(1, 1) == 1);


    // Verify zero matrix
    static_assert(fgm::mat2d::zero<int>(0, 0) == 0);
    static_assert(fgm::mat2d::zero<int>(0, 1) == 0);
    static_assert(fgm::mat2d::zero<int>(1, 0) == 0);
    static_assert(fgm::mat2d::zero<int>(1, 1) == 0);


    // Verify zero matrix
    static_assert(fgm::Matrix2D<int>::zero()(0, 0) == 0);
    static_assert(fgm::Matrix2D<int>::zero()(0, 1) == 0);
    static_assert(fgm::Matrix2D<int>::zero()(1, 0) == 0);
    static_assert(fgm::Matrix2D<int>::zero()(1, 1) == 0);

}



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::mat2d::eye returns an identity matrix. */
TYPED_TEST(Matrix2DConstants, Eye_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::mat2d::eye<TypeParam>); }


/** @brief Verify that @ref fgm::Matrix2D::eye static factory returns an identity matrix. */
TYPED_TEST(Matrix2DConstants, StaticFactory_Eye_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::Matrix2D<TypeParam>::eye()); }


/** @brief Verify that @ref fgm::mat2d::zero returns a zero matrix. */
TYPED_TEST(Matrix2DConstants, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::mat2d::zero<TypeParam>); }


/** @brief Verify that @ref fgm::Matrix2D::zero static factory returns a zero matrix. */
TYPED_TEST(Matrix2DConstants, StaticFactory_Zero_ReturnsZeroMatrix)
{
    EXPECT_MAT_ZERO(fgm::Matrix2D<TypeParam>::zero());
}

/** @} */