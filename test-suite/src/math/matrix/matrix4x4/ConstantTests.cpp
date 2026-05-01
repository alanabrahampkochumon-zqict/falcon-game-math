/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01S, 2026
 *
 * @brief Verify @ref fgm::Matrix4D constants (@ref fgm::Matrix4D::eye, @ref fgm::Matrix4D::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix4DConstants: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Matrix4D constants, parameterized @ref SupportedArithmeticTypes.*/
TYPED_TEST_SUITE(Matrix4DConstants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat4x4_Constant
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Matrix4D constants are available at compile time. */
namespace 
{
    // Verify identity matrix
    static_assert(fgm::mat4d::eye<int>(0, 0) == 1);
    static_assert(fgm::mat4d::eye<int>(0, 1) == 0);
    static_assert(fgm::mat4d::eye<int>(0, 2) == 0);
    static_assert(fgm::mat4d::eye<int>(0, 3) == 0);
    static_assert(fgm::mat4d::eye<int>(1, 0) == 0);
    static_assert(fgm::mat4d::eye<int>(1, 1) == 1);
    static_assert(fgm::mat4d::eye<int>(1, 2) == 0);
    static_assert(fgm::mat4d::eye<int>(1, 3) == 0);
    static_assert(fgm::mat4d::eye<int>(2, 0) == 0);
    static_assert(fgm::mat4d::eye<int>(2, 1) == 0);
    static_assert(fgm::mat4d::eye<int>(2, 2) == 1);
    static_assert(fgm::mat4d::eye<int>(2, 3) == 0);
    static_assert(fgm::mat4d::eye<int>(3, 0) == 0);
    static_assert(fgm::mat4d::eye<int>(3, 1) == 0);
    static_assert(fgm::mat4d::eye<int>(3, 2) == 0);
    static_assert(fgm::mat4d::eye<int>(3, 3) == 1);


    // Verify identity matrix static factory
    static_assert(fgm::Matrix4D<int>::eye()(0, 0) == 1);
    static_assert(fgm::Matrix4D<int>::eye()(0, 1) == 0);
    static_assert(fgm::Matrix4D<int>::eye()(0, 2) == 0);
    static_assert(fgm::Matrix4D<int>::eye()(0, 3) == 0);
    static_assert(fgm::Matrix4D<int>::eye()(1, 0) == 0);
    static_assert(fgm::Matrix4D<int>::eye()(1, 1) == 1);
    static_assert(fgm::Matrix4D<int>::eye()(1, 2) == 0);
    static_assert(fgm::Matrix4D<int>::eye()(1, 3) == 0);
    static_assert(fgm::Matrix4D<int>::eye()(2, 0) == 0);
    static_assert(fgm::Matrix4D<int>::eye()(2, 1) == 0);
    static_assert(fgm::Matrix4D<int>::eye()(2, 2) == 1);
    static_assert(fgm::Matrix4D<int>::eye()(2, 3) == 0);
    static_assert(fgm::Matrix4D<int>::eye()(3, 0) == 0);
    static_assert(fgm::Matrix4D<int>::eye()(3, 1) == 0);
    static_assert(fgm::Matrix4D<int>::eye()(3, 2) == 0);
    static_assert(fgm::Matrix4D<int>::eye()(3, 3) == 1);

    // Verify zero matrix
    static_assert(fgm::mat4d::zero<int>(0, 0) == 0);
    static_assert(fgm::mat4d::zero<int>(0, 1) == 0);
    static_assert(fgm::mat4d::zero<int>(0, 2) == 0);
    static_assert(fgm::mat4d::zero<int>(0, 3) == 0);
    static_assert(fgm::mat4d::zero<int>(1, 0) == 0);
    static_assert(fgm::mat4d::zero<int>(1, 1) == 0);
    static_assert(fgm::mat4d::zero<int>(1, 2) == 0);
    static_assert(fgm::mat4d::zero<int>(1, 3) == 0);
    static_assert(fgm::mat4d::zero<int>(2, 0) == 0);
    static_assert(fgm::mat4d::zero<int>(2, 1) == 0);
    static_assert(fgm::mat4d::zero<int>(2, 2) == 0);
    static_assert(fgm::mat4d::zero<int>(2, 3) == 0);
    static_assert(fgm::mat4d::zero<int>(3, 0) == 0);
    static_assert(fgm::mat4d::zero<int>(3, 1) == 0);
    static_assert(fgm::mat4d::zero<int>(3, 2) == 0);
    static_assert(fgm::mat4d::zero<int>(3, 3) == 0);


    // Verify zero matrix
    static_assert(fgm::Matrix4D<int>::zero()(0, 0) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(0, 1) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(0, 2) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(0, 3) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(1, 0) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(1, 1) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(1, 2) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(1, 3) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(2, 0) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(2, 1) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(2, 2) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(2, 3) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(3, 0) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(3, 1) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(3, 2) == 0);
    static_assert(fgm::Matrix4D<int>::zero()(3, 3) == 0);

}



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::mat4d::eye returns an identity matrix. */
TYPED_TEST(Matrix4DConstants, Eye_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::mat4d::eye<TypeParam>); }


/** @brief Verify that @ref fgm::Matrix4D::eye static factory returns an identity matrix. */
TYPED_TEST(Matrix4DConstants, StaticFactory_Eye_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::Matrix4D<TypeParam>::eye()); }


/** @brief Verify that @ref fgm::mat4d::zero returns a zero matrix. */
TYPED_TEST(Matrix4DConstants, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::mat4d::zero<TypeParam>); }


/** @brief Verify that @ref fgm::Matrix4D::zero static factory returns a zero matrix. */
TYPED_TEST(Matrix4DConstants, StaticFactory_Zero_ReturnsZeroMatrix)
{
    EXPECT_MAT_ZERO(fgm::Matrix4D<TypeParam>::zero());
}

/** @} */