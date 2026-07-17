/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 17, 2026
 *
 * @brief Verify @ref fgm::Matrix2x3 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Matrix2x3TestSetup.h"



template <typename T>
class Matrix2x3Initialization: public testing::Test
{
protected:
    std::vector<T> _elements;
    fgm::Vector2<T> _col0, _col1, _col2;

    void SetUp() override
    {
        _elements = { T(1), T(2), T(3), T(4), T(5), T(6) };
        _col0     = { T(1), T(4) };
        _col1     = { T(2), T(5) };
        _col2     = { T(3), T(6) };
    }
};
/** Test fixture for @ref fgm::Matrix2x3 initialization, parameterized by @ref SupportedTypes. */
TYPED_TEST_SUITE(Matrix2x3Initialization, SupportedTypes);



/**
 * @addtogroup T_FGM_Mat2x3_Init
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
    constexpr fgm::Matrix2x3 MAT1(1, 2, 3, 4, 5, 6);
    static_assert(MAT1(0, 0) == 1);
    static_assert(MAT1(0, 1) == 2);
    static_assert(MAT1(0, 2) == 3);
    static_assert(MAT1(1, 0) == 4);
    static_assert(MAT1(1, 1) == 5);
    static_assert(MAT1(1, 2) == 6);


    // Verify that the matrix can be initialized at compile time using column vectors.
    constexpr fgm::Matrix2x3 MAT2(fgm::Vector2(1, 4), fgm::Vector2(2, 5), fgm::Vector2(3, 6));
    static_assert(MAT2(0, 0) == 1);
    static_assert(MAT2(0, 1) == 2);
    static_assert(MAT2(0, 2) == 3);
    static_assert(MAT2(1, 0) == 4);
    static_assert(MAT2(1, 1) == 5);
    static_assert(MAT2(1, 2) == 6);



    // Verify that the matrix can be initialized at compile time using value initialization.
    constexpr fgm::Matrix2x3<int> MAT4{};
    static_assert(MAT4(0, 0) == 0);
    static_assert(MAT4(0, 1) == 0);
    static_assert(MAT4(0, 2) == 0);
    static_assert(MAT4(1, 0) == 0);
    static_assert(MAT4(1, 1) == 0);
    static_assert(MAT4(1, 2) == 0);

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that the default constructor initializes an identity matrix. */
TYPED_TEST(Matrix2x3Initialization, EmptyConstructorReturnsIdentityMatrix)
{
    constexpr fgm::Matrix2x3<TypeParam> matrix{};

    EXPECT_MAT_ZERO(matrix);
}


/** @brief Verify that the parameterized constructor can initialize matrix with elements. */
TYPED_TEST(Matrix2x3Initialization, ParameterizedConstructorInitializesMatrixWithElements)
{
    const fgm::Matrix2x3<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2],
                                           this->_elements[3], this->_elements[4], this->_elements[5]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


/** @brief Verify that the parameterized constructor can initialize matrix with vectors. */
TYPED_TEST(Matrix2x3Initialization, ParameterizedConstructorInitializesMatrixWithVectors)
{
    const fgm::Matrix2x3<TypeParam> matrix(this->_col0, this->_col1, this->_col2);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}



/** @brief Verify that a matrix can be initialized with implicit braced initialization. */
TYPED_TEST(Matrix2x3Initialization, CanBeConstructedWithBracedInitialization)
{
    const fgm::Matrix2x3<TypeParam> matrix = {
        { TypeParam(1), TypeParam(4) },
        { TypeParam(2), TypeParam(5) },
        { TypeParam(3), TypeParam(6) },
    };
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
