/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref fgm::Mat3x4 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x4TestSetup.h"



template <typename T>
class Mat3x4Initialization: public testing::Test
{
protected:
    std::vector<T> _elements;
    fgm::Vec3<T> _col0, _col1, _col2, _col3;

    void SetUp() override
    {
        _elements = { T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(9), T(10), T(11), T(12) };
        _col0     = { T(1), T(5), T(9) };
        _col1     = { T(2), T(6), T(10) };
        _col2     = { T(3), T(7), T(11) };
        _col3     = { T(4), T(8), T(12) };
    }
};
/** Test fixture for @ref fgm::Mat3x4 initialization, parameterized by @ref SupportedTypes. */
TYPED_TEST_SUITE(Mat3x4Initialization, SupportedTypes);



/**
 * @addtogroup T_FGM_Mat3x4_Init
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
    constexpr fgm::Mat3x4 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    static_assert(MAT1(0, 0) == 1);
    static_assert(MAT1(0, 1) == 2);
    static_assert(MAT1(0, 2) == 3);
    static_assert(MAT1(0, 3) == 4);

    static_assert(MAT1(1, 0) == 5);
    static_assert(MAT1(1, 1) == 6);
    static_assert(MAT1(1, 2) == 7);
    static_assert(MAT1(1, 3) == 8);

    static_assert(MAT1(2, 0) == 9);
    static_assert(MAT1(2, 1) == 10);
    static_assert(MAT1(2, 2) == 11);
    static_assert(MAT1(2, 3) == 12);


    // Verify that the matrix can be initialized at compile time using column vectors.
    constexpr fgm::Mat3x4 MAT2(fgm::Vec3(1, 5, 9), fgm::Vec3(2, 6, 10), fgm::Vec3(3, 7, 11), fgm::Vec3(4, 8, 12));
    static_assert(MAT2(0, 0) == 1);
    static_assert(MAT2(0, 1) == 2);
    static_assert(MAT2(0, 2) == 3);
    static_assert(MAT2(0, 3) == 4);

    static_assert(MAT2(1, 0) == 5);
    static_assert(MAT2(1, 1) == 6);
    static_assert(MAT2(1, 2) == 7);
    static_assert(MAT2(1, 3) == 8);

    static_assert(MAT2(2, 0) == 9);
    static_assert(MAT2(2, 1) == 10);
    static_assert(MAT2(2, 2) == 11);
    static_assert(MAT2(2, 3) == 12);



    // Verify that the matrix can be initialized at compile time using value initialization.
    constexpr fgm::Mat3x4<int> MAT4{};
    static_assert(MAT4(0, 0) == 0);
    static_assert(MAT4(0, 1) == 0);
    static_assert(MAT4(0, 2) == 0);
    static_assert(MAT4(0, 3) == 0);

    static_assert(MAT4(1, 0) == 0);
    static_assert(MAT4(1, 1) == 0);
    static_assert(MAT4(1, 2) == 0);
    static_assert(MAT4(1, 3) == 0);

    static_assert(MAT4(2, 0) == 0);
    static_assert(MAT4(2, 1) == 0);
    static_assert(MAT4(2, 2) == 0);
    static_assert(MAT4(2, 3) == 0);

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that the default constructor initializes an identity matrix. */
TYPED_TEST(Mat3x4Initialization, EmptyConstructorReturnsIdentityMatrix)
{
    constexpr fgm::Mat3x4<TypeParam> matrix{};

    EXPECT_MAT_ZERO(matrix);
}


/** @brief Verify that the parameterized constructor can initialize matrix with elements. */
TYPED_TEST(Mat3x4Initialization, ParameterizedConstructorInitializesMatrixWithElements)
{
    const fgm::Mat3x4<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2], this->_elements[3],
                                        this->_elements[4], this->_elements[5], this->_elements[6], this->_elements[7],
                                        this->_elements[8], this->_elements[9], this->_elements[10],
                                        this->_elements[11]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


/** @brief Verify that the parameterized constructor can initialize matrix with vectors. */
TYPED_TEST(Mat3x4Initialization, ParameterizedConstructorInitializesMatrixWithVectors)
{
    const fgm::Mat3x4<TypeParam> matrix(this->_col0, this->_col1, this->_col2, this->_col3);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}



/** @brief Verify that a matrix can be initialized with implicit braced initialization. */
TYPED_TEST(Mat3x4Initialization, CanBeConstructedWithBracedInitialization)
{
    const fgm::Mat3x4<TypeParam> matrix = {
        { TypeParam(1), TypeParam(5), TypeParam(9) },
        { TypeParam(2), TypeParam(6), TypeParam(10) },
        { TypeParam(3), TypeParam(7), TypeParam(11) },
        { TypeParam(4), TypeParam(8), TypeParam(12) },
    };
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
