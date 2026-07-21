/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 22, 2026
 *
 * @brief Verify @ref fgm::Mat3 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"



template <typename T>
class Mat3Initialization: public ::testing::Test
{
protected:
    std::vector<T> _elements;
    std::vector<T> _diagonalElements;
    fgm::Vec3<T> _col0, _col1, _col2;
    T _diagonal0, _diagonal1, _diagonal2;

    void SetUp() override
    {
        _elements         = { T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(9) };
        _diagonalElements = { T(2), T(0), T(0), T(0), T(3), T(0), T(0), T(0), T(5) };
        _col0             = { T(1), T(4), T(7) };
        _col1             = { T(2), T(5), T(8) };
        _col2             = { T(3), T(6), T(9) };
        _diagonal0        = T(2);
        _diagonal1        = T(3);
        _diagonal2        = T(5);
    }
};
/** Test fixture for @ref fgm::Mat3 initialization, parameterized by @ref SupportedTypes. */
TYPED_TEST_SUITE(Mat3Initialization, SupportedTypes);



/**
 * @addtogroup T_FGM_Mat3x3_Init
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
    constexpr fgm::Mat3 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    static_assert(MAT1(0, 0) == 1);
    static_assert(MAT1(0, 1) == 2);
    static_assert(MAT1(0, 2) == 3);
    static_assert(MAT1(1, 0) == 4);
    static_assert(MAT1(1, 1) == 5);
    static_assert(MAT1(1, 2) == 6);
    static_assert(MAT1(2, 0) == 7);
    static_assert(MAT1(2, 1) == 8);
    static_assert(MAT1(2, 2) == 9);


    // Verify that the matrix can be initialized at compile time using column vectors.
    constexpr fgm::Mat3 MAT2(fgm::Vec3(1, 4, 7), fgm::Vec3(2, 5, 8), fgm::Vec3(3, 6, 9));
    static_assert(MAT2(0, 0) == 1);
    static_assert(MAT2(0, 1) == 2);
    static_assert(MAT2(0, 2) == 3);
    static_assert(MAT2(1, 0) == 4);
    static_assert(MAT2(1, 1) == 5);
    static_assert(MAT2(1, 2) == 6);
    static_assert(MAT2(2, 0) == 7);
    static_assert(MAT2(2, 1) == 8);
    static_assert(MAT2(2, 2) == 9);


    // Verify that the matrix can be initialized at compile time using diagonals.
    constexpr fgm::Mat3 MAT3(3, 4, 5);
    static_assert(MAT3(0, 0) == 3);
    static_assert(MAT3(0, 1) == 0);
    static_assert(MAT3(0, 2) == 0);
    static_assert(MAT3(1, 0) == 0);
    static_assert(MAT3(1, 1) == 4);
    static_assert(MAT3(1, 2) == 0);
    static_assert(MAT3(2, 0) == 0);
    static_assert(MAT3(2, 1) == 0);
    static_assert(MAT3(2, 2) == 5);

    // Verify that the matrix can be initialized at compile time using value initialization.
    constexpr fgm::Mat3<int> MAT4{};
    static_assert(MAT4(0, 0) == 0);
    static_assert(MAT4(0, 1) == 0);
    static_assert(MAT4(0, 2) == 0);
    static_assert(MAT4(1, 0) == 0);
    static_assert(MAT4(1, 1) == 0);
    static_assert(MAT4(1, 2) == 0);
    static_assert(MAT4(2, 0) == 0);
    static_assert(MAT4(2, 1) == 0);
    static_assert(MAT4(2, 2) == 0);

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that the default constructor initializes an identity matrix. */
TYPED_TEST(Mat3Initialization, EmptyConstructorReturnsIdentityMatrix)
{
    const fgm::Mat3<TypeParam> matrix{};

    EXPECT_MAT_ZERO(matrix);
}


/** @brief Verify that the parameterized constructor can initialize matrix with elements. */
TYPED_TEST(Mat3Initialization, ParameterizedConstructorInitializesMatrixWithElements)
{
    const fgm::Mat3<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2], this->_elements[3],
                                      this->_elements[4], this->_elements[5], this->_elements[6], this->_elements[7],
                                      this->_elements[8]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


/** @brief Verify that the parameterized constructor can initialize matrix with vectors. */
TYPED_TEST(Mat3Initialization, ParameterizedConstructorInitializesMatrixWithVectors)
{
    const fgm::Mat3<TypeParam> matrix(this->_col0, this->_col1, this->_col2);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


/** @brief Verify that the parameterized constructor can initialize a diagonal matrix. */
TYPED_TEST(Mat3Initialization, ParameterizedConstructorInitializesDiagonalMatrix)
{
    const fgm::Mat3<TypeParam> matrix(this->_diagonal0, this->_diagonal1, this->_diagonal2);
    EXPECT_MAT_CONTAINS(this->_diagonalElements, matrix);
}


/** @brief Verify that a matrix can be initialized with implicit braced initialization. */
TYPED_TEST(Mat3Initialization, CanBeConstructedWithBracedInitialization)
{
    const fgm::Mat3<TypeParam> matrix = { { TypeParam(1), TypeParam(4), TypeParam(7) },
                                          { TypeParam(2), TypeParam(5), TypeParam(8) },
                                          { TypeParam(3), TypeParam(6), TypeParam(9) } };
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
