/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verifies @ref fgm::Matrix2D initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/** Test fixture for @ref fgm::Matrix2D, parameterized by @ref SupportedTypes. */
template <typename T>
class Matrix2DInitialization: public ::testing::Test
{
    T _v00;
    T _v01;
    T _v10;
    T _v11;
};
TYPED_TEST_SUITE(Matrix2DInitialization, SupportedTypes);


/**
 * @addtogroup T_FGM_Mat2x2_Init
 * @{
 */

/** @brief Verify that the default constructor initializes an identity matrix. */
TYPED_TEST(Matrix2DInitialization, EmptyConstructorReturnsIdentityMatrix)
{
    constexpr fgm::Matrix2D<TypeParam> matrix;

    EXPECT_MAT_IDENTITY(matrix);
}

/** @brief Verify that the parameterized constructor initializes matrix with element-wise entries. */
TYPED_TEST(Matrix2DInitialization, ParameterizedConstructorInitializesMatrixWithElements) {}

/** @} */
