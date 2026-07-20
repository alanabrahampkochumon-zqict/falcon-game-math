/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref fgm::Mat3x2 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x2TestSetup.h"



template <typename T>
class Mat3x2Initialization: public testing::Test
{
protected:
    std::vector<T> _elements;
    fgm::Vec3<T> _col0, _col1;

    void SetUp() override
    {
        _elements = { T(1), T(2), T(3), T(4), T(5), T(6) };
        _col0     = { T(1), T(3), T(5) };
        _col1     = { T(2), T(4), T(6) };
    }
};
/** Test fixture for @ref fgm::Mat3x2 initialization, parameterized by @ref SupportedTypes. */
TYPED_TEST_SUITE(Mat3x2Initialization, SupportedTypes);



/**
 * @addtogroup T_FGM_Mat3x2_Init
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
    constexpr fgm::Mat3x2 MAT1(1, 2, 3, 4, 5, 6);
    static_assert(MAT1(0, 0) == 1);
    static_assert(MAT1(0, 1) == 2);
    static_assert(MAT1(1, 0) == 3);
    static_assert(MAT1(1, 1) == 4);
    static_assert(MAT1(2, 0) == 5);
    static_assert(MAT1(2, 1) == 6);


    // Verify that the matrix can be initialized at compile time using column vectors.
    constexpr fgm::Mat3x2 MAT2(fgm::Vec3(1, 3, 5), fgm::Vec3(2, 4, 6));
    static_assert(MAT2(0, 0) == 1);
    static_assert(MAT2(0, 1) == 2);
    static_assert(MAT2(1, 0) == 3);
    static_assert(MAT2(1, 1) == 4);
    static_assert(MAT2(2, 0) == 5);
    static_assert(MAT2(2, 1) == 6);



    // Verify that the matrix can be initialized at compile time using value initialization.
    constexpr fgm::Mat3x2<int> MAT4{};
    static_assert(MAT4(0, 0) == 0);
    static_assert(MAT4(0, 1) == 0);
    static_assert(MAT4(1, 0) == 0);
    static_assert(MAT4(1, 1) == 0);
    static_assert(MAT4(2, 0) == 0);
    static_assert(MAT4(2, 1) == 0);

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that the default constructor initializes an identity matrix. */
TYPED_TEST(Mat3x2Initialization, EmptyConstructorReturnsIdentityMatrix)
{
    constexpr fgm::Mat3x2<TypeParam> matrix{};

    EXPECT_MAT_ZERO(matrix);
}


/** @brief Verify that the parameterized constructor can initialize matrix with elements. */
TYPED_TEST(Mat3x2Initialization, ParameterizedConstructorInitializesMatrixWithElements)
{
    const fgm::Mat3x2<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2], this->_elements[3],
                                        this->_elements[4], this->_elements[5]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


/** @brief Verify that the parameterized constructor can initialize matrix with vectors. */
TYPED_TEST(Mat3x2Initialization, ParameterizedConstructorInitializesMatrixWithVectors)
{
    const fgm::Mat3x2<TypeParam> matrix(this->_col0, this->_col1);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}



/** @brief Verify that a matrix can be initialized with implicit braced initialization. */
TYPED_TEST(Mat3x2Initialization, CanBeConstructedWithBracedInitialization)
{
    const fgm::Mat3x2<TypeParam> matrix = {
        { TypeParam(1), TypeParam(3), TypeParam(5) },
        { TypeParam(2), TypeParam(4), TypeParam(6) },
    };
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
