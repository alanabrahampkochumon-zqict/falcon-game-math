/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 23, 2026
 *
 * @brief Verify @ref fgm::Matrix3 constants (@ref fgm::Matrix3::eye, @ref fgm::Matrix3::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix3Constants: public ::testing::Test
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
    static_assert(fgm::mat3d::eye<int>(0, 0) == 1);
    static_assert(fgm::mat3d::eye<int>(0, 1) == 0);
    static_assert(fgm::mat3d::eye<int>(0, 2) == 0);
    static_assert(fgm::mat3d::eye<int>(1, 0) == 0);
    static_assert(fgm::mat3d::eye<int>(1, 1) == 1);
    static_assert(fgm::mat3d::eye<int>(1, 2) == 0);
    static_assert(fgm::mat3d::eye<int>(2, 0) == 0);
    static_assert(fgm::mat3d::eye<int>(2, 1) == 0);
    static_assert(fgm::mat3d::eye<int>(2, 2) == 1);


    // Verify identity (functional variant)
    static_assert(fgm::Matrix3<int>::eye()(0, 0) == 1);
    static_assert(fgm::Matrix3<int>::eye()(0, 1) == 0);
    static_assert(fgm::Matrix3<int>::eye()(0, 2) == 0);
    static_assert(fgm::Matrix3<int>::eye()(1, 0) == 0);
    static_assert(fgm::Matrix3<int>::eye()(1, 1) == 1);
    static_assert(fgm::Matrix3<int>::eye()(1, 2) == 0);
    static_assert(fgm::Matrix3<int>::eye()(2, 0) == 0);
    static_assert(fgm::Matrix3<int>::eye()(2, 1) == 0);
    static_assert(fgm::Matrix3<int>::eye()(2, 2) == 1);


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


    // Verify zero matrix (functional variant)
    static_assert(fgm::Matrix3<int>::zero()(0, 0) == 0);
    static_assert(fgm::Matrix3<int>::zero()(0, 1) == 0);
    static_assert(fgm::Matrix3<int>::zero()(0, 2) == 0);
    static_assert(fgm::Matrix3<int>::zero()(1, 0) == 0);
    static_assert(fgm::Matrix3<int>::zero()(1, 1) == 0);
    static_assert(fgm::Matrix3<int>::zero()(1, 2) == 0);
    static_assert(fgm::Matrix3<int>::zero()(2, 0) == 0);
    static_assert(fgm::Matrix3<int>::zero()(2, 1) == 0);
    static_assert(fgm::Matrix3<int>::zero()(2, 2) == 0);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::mat3d::eye returns an identity matrix. */
TYPED_TEST(Matrix3Constants, Eye_ReturnsIdentityMatrix) { EXPECT_MAT_IDENTITY(fgm::mat3d::eye<TypeParam>); }


/** @brief Verify that @ref fgm::Matrix3::eye static factory returns an identity matrix. */
TYPED_TEST(Matrix3Constants, StaticWrapper_Eye_ReturnsIdentityMatrix)
{ EXPECT_MAT_IDENTITY(fgm::Matrix3<TypeParam>::eye()); }


/** @brief Verify that @ref fgm::mat3d::zero returns a zero matrix. */
TYPED_TEST(Matrix3Constants, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(fgm::mat3d::zero<TypeParam>); }


/** @brief Verify that @ref fgm::Matrix3::zero static factory returns a zero matrix. */
TYPED_TEST(Matrix3Constants, StaticWrapper_Zero_ReturnsZeroMatrix)
{ EXPECT_MAT_ZERO(fgm::Matrix3<TypeParam>::zero()); }

/** @} */
