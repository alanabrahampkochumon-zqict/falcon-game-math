/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 23, 2026
 *
 * @brief Verify @ref fgm::Matrix3D constants (@ref fgm::Matrix3D::eye, @ref fgm::Matrix3D::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix3DConstants: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Matrix3D constants, parameterized @ref SupportedArithmeticTypes.*/
TYPED_TEST_SUITE(Matrix3DConstants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat3x3_Constant
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Matrix3D constants are available at compile time. */
namespace 
{
    // Verify identity matrix
    static_assert(fgm::mat3d::eye<int>(0, 0) == 1);
    static_assert(fgm::mat3d::eye<int>(0, 1) == 0);
    static_assert(fgm::mat3d::eye<int>(0, 2) == 0);
    static_assert(fgm::mat3d::eye<int>(1, 0) == 0);
    static_assert(fgm::mat3d::eye<int>(1, 1) == 1);
    static_assert(fgm::mat3d::eye<int>(1, 2) == 0);
    static_assert(fgm::mat3d::eye<int>(2, 0) == 0);
    static_assert(fgm::mat3d::eye<int>(2, 1) == 0);
    static_assert(fgm::mat3d::eye<int>(2, 2) == 1);


    // Verify identity matrix static factory
    static_assert(fgm::Matrix3D<int>::eye()(0, 0) == 1);
    static_assert(fgm::Matrix3D<int>::eye()(0, 1) == 0);
    static_assert(fgm::Matrix3D<int>::eye()(0, 2) == 0);
    static_assert(fgm::Matrix3D<int>::eye()(1, 0) == 0);
    static_assert(fgm::Matrix3D<int>::eye()(1, 1) == 1);
    static_assert(fgm::Matrix3D<int>::eye()(1, 2) == 0);
    static_assert(fgm::Matrix3D<int>::eye()(2, 0) == 0);
    static_assert(fgm::Matrix3D<int>::eye()(2, 1) == 0);
    static_assert(fgm::Matrix3D<int>::eye()(2, 2) == 1);


    // Verify zero matrix
    static_assert(fgm::mat3d::zero<int>(0, 0) == 0);
    static_assert(fgm::mat3d::zero<int>(0, 1) == 0);
    static_assert(fgm::mat3d::zero<int>(0, 2) == 0);
    static_assert(fgm::mat3d::zero<int>(1, 0) == 0);
    static_assert(fgm::mat3d::zero<int>(1, 1) == 0);
    static_assert(fgm::mat3d::zero<int>(1, 2) == 0);
    static_assert(fgm::mat3d::zero<int>(2, 0) == 0);
    static_assert(fgm::mat3d::zero<int>(2, 1) == 0);
    static_assert(fgm::mat3d::zero<int>(2, 2) == 0);


    // Verify zero matrix
    static_assert(fgm::Matrix3D<int>::zero()(0, 0) == 0);
    static_assert(fgm::Matrix3D<int>::zero()(0, 1) == 0);
    static_assert(fgm::Matrix3D<int>::zero()(0, 2) == 0);
    static_assert(fgm::Matrix3D<int>::zero()(1, 0) == 0);
    static_assert(fgm::Matrix3D<int>::zero()(1, 1) == 0);
    static_assert(fgm::Matrix3D<int>::zero()(1, 2) == 0);
    static_assert(fgm::Matrix3D<int>::zero()(2, 0) == 0);
    static_assert(fgm::Matrix3D<int>::zero()(2, 1) == 0);
    static_assert(fgm::Matrix3D<int>::zero()(2, 2) == 0);

}



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::mat3d::eye returns an identity matrix. */
TYPED_TEST(Matrix3DConstants, Eye_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::mat3d::eye<TypeParam>); }


/** @brief Verify that @ref fgm::Matrix3D::eye static factory returns an identity matrix. */
TYPED_TEST(Matrix3DConstants, StaticFactory_Eye_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::Matrix3D<TypeParam>::eye()); }


/** @brief Verify that @ref fgm::mat3d::zero returns a zero matrix. */
TYPED_TEST(Matrix3DConstants, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::mat3d::zero<TypeParam>); }


/** @brief Verify that @ref fgm::Matrix3D::zero static factory returns a zero matrix. */
TYPED_TEST(Matrix3DConstants, StaticFactory_Zero_ReturnsZeroMatrix)
{
    EXPECT_MAT_ZERO(fgm::Matrix3D<TypeParam>::zero());
}

/** @} */