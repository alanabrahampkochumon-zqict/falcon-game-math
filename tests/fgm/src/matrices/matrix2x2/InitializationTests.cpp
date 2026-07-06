/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Matrix2 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix2Initialization: public ::testing::Test
{
protected:
    std::vector<T> _elements;
    std::vector<T> _diagonalElements;
    fgm::Vector2<T> _col0, _col1;
    T _diagonal0, _diagonal1;

    void SetUp() override
    {
        _elements         = { T(1), T(2), T(3), T(4) };
        _diagonalElements = { T(2), T(0), T(0), T(3) };
        _col0             = { T(1), T(3) };
        _col1             = { T(2), T(4) };
        _diagonal0        = T(2);
        _diagonal1        = T(3);
    }
};
/** Test fixture for @ref fgm::Matrix2 initialization, parameterized by @ref SupportedTypes. */
TYPED_TEST_SUITE(Matrix2Initialization, SupportedTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Init
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the matrix can be initialized at compile time. */
namespace
{
    // Verify that the matrix can be initialized at compile time using scalar values.
    constexpr fgm::Matrix2 MAT1(1, 2, 3, 4);
    static_assert(MAT1(0, 0) == 1);
    static_assert(MAT1(0, 1) == 2);
    static_assert(MAT1(1, 0) == 3);
    static_assert(MAT1(1, 1) == 4);


    // Verify that the matrix can be initialized at compile time using column vectors.
    constexpr fgm::Matrix2 MAT2(fgm::Vector2(1, 3), fgm::Vector2(2, 4));
    static_assert(MAT2(0, 0) == 1);
    static_assert(MAT2(0, 1) == 2);
    static_assert(MAT2(1, 0) == 3);
    static_assert(MAT2(1, 1) == 4);


    // Verify that the matrix can be initialized at compile time using diagonals.
    constexpr fgm::Matrix2 MAT3(3, 4);
    static_assert(MAT3(0, 0) == 3);
    static_assert(MAT3(0, 1) == 0);
    static_assert(MAT3(1, 0) == 0);
    static_assert(MAT3(1, 1) == 4);

    // Verify that the matrix can be initialized at compile time using value initialization.
    constexpr fgm::Matrix2<int> MAT4{};
    static_assert(MAT4(0, 0) == 0);
    static_assert(MAT4(0, 1) == 0);
    static_assert(MAT4(1, 0) == 0);
    static_assert(MAT4(1, 1) == 0);

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that the default constructor initializes an identity matrix. */
TYPED_TEST(Matrix2Initialization, EmptyConstructorReturnsIdentityMatrix)
{
    const fgm::Matrix2<TypeParam> matrix{};

    EXPECT_MAT_ZERO(matrix);
}


/** @brief Verify that the parameterized constructor can initialize matrix with elements. */
TYPED_TEST(Matrix2Initialization, ParameterizedConstructorInitializesMatrixWithElements)
{
    const fgm::Matrix2<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2],
                                          this->_elements[3]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


/** @brief Verify that the parameterized constructor can initialize matrix with vectors. */
TYPED_TEST(Matrix2Initialization, ParameterizedConstructorInitializesMatrixWithVectors)
{
    const fgm::Matrix2<TypeParam> matrix(this->_col0, this->_col1);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


/** @brief Verify that the parameterized constructor can initialize a diagonal matrix. */
TYPED_TEST(Matrix2Initialization, ParameterizedConstructorInitializesDiagonalMatrix)
{
    const fgm::Matrix2<TypeParam> matrix(this->_diagonal0, this->_diagonal1);
    EXPECT_MAT_CONTAINS(this->_diagonalElements, matrix);
}


/** @brief Verify that a matrix can be initialized with implicit braced initialization. */
TYPED_TEST(Matrix2Initialization, CanBeConstructedWithBracedInitialization)
{
    const fgm::Matrix2<TypeParam> matrix = { { TypeParam(1), TypeParam(3) }, { TypeParam(2), TypeParam(4) } };
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
