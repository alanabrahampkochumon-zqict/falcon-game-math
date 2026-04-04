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
protected:
    std::vector<T> _elements;

    void SetUp() override
    {
        _elements = { T(1), T(2), T(3), T(4) };
    }
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

/** @brief Verify that the parameterized constructor can initialize matrix with elements. */
TYPED_TEST(Matrix2DInitialization, ParameterizedConstructorInitializesMatrixWithElements)
{
    const fgm::Matrix2D<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2], this->_elements[3]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
