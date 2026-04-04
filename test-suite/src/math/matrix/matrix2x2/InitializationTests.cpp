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
    std::vector<T> _diagonalElements;
    fgm::Vector2D<T> _col0, _col1;
    T _diagonal0, _diagonal1;

    void SetUp() override
    {
        _elements = { T(1), T(2), T(3), T(4) };
        _diagonalElements = { T(2), T(0), T(0), T(3) };
        _col0 = { T(1), T(3) };
        _col1 = { T(2), T(4) };
        _diagonal0 = T(2);
        _diagonal1 = T(3);
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


/** @brief Verify that the parameterized constructor can initialize matrix with vectors. */
TYPED_TEST(Matrix2DInitialization, ParameterizedConstructorInitializesMatrixWithVectors)
{
    const fgm::Matrix2D<TypeParam> matrix(this->_col0, this->_col1);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


/** @brief Verify that the parameterized constructor can initialize a diagonal matrix. */
TYPED_TEST(Matrix2DInitialization, ParameterizedConstructorInitializesDiagonalMatrix)
{
    const fgm::Matrix2D<TypeParam> matrix(this->_diagonal0, this->_diagonal1);
    EXPECT_MAT_CONTAINS(this->_diagonalElements, matrix);
}

/** @} */
