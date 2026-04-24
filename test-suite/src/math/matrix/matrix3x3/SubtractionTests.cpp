/**
 * @file SubtractionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 24, 2026
 *
 * @brief Verify @ref fgm::Matrix3D subtraction logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Matrix3DSubtraction: public ::testing::Test
{
protected:
    fgm::Matrix3D<T> _matA;
    fgm::Matrix3D<T> _matB;
    fgm::Matrix3D<T> _expectedDifference;

    void SetUp() override
    {
        _matA = { fgm::Vector3D<T>{ 5, 6, 9 }, fgm::Vector3D<T>{ 13, 8, 5 }, fgm::Vector3D<T>{ 5, 4, 10 } };
        _matB = { fgm::Vector3D<T>{ 3, 1, 6 }, fgm::Vector3D<T>{ 8, 1, 5 }, fgm::Vector3D<T>{ 2, 3, 1 } };
        _expectedDifference = { fgm::Vector3D<T>{ 2, 5, 3 }, fgm::Vector3D<T>{ 5, 7, 0 }, fgm::Vector3D<T>{ 3, 1, 9 } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix3D subtraction, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix3DSubtraction, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Mat2x2_Subtraction
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that matrix subtraction operations are available at compile time. */
namespace
{
    constexpr fgm::Matrix3D MAT1{ 8, 2, 12, 4, 15, -11, 23, -55, 12 };
    constexpr fgm::Matrix3D MAT2{ 80, -5, 15, 3, 1, -13, 0, 55, 38 };
    constexpr fgm::Matrix3D BINARY_DIFF = MAT1 - MAT2;

    static_assert(BINARY_DIFF(0, 0) == -72);
    static_assert(BINARY_DIFF(0, 1) == 7);
    static_assert(BINARY_DIFF(0, 2) == -3);
    static_assert(BINARY_DIFF(1, 0) == 1);
    static_assert(BINARY_DIFF(1, 1) == 14);
    static_assert(BINARY_DIFF(1, 2) == 2);
    static_assert(BINARY_DIFF(2, 0) == 23);
    static_assert(BINARY_DIFF(2, 1) == -110);
    static_assert(BINARY_DIFF(2, 2) == -26);

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @test Verify that the binary subtraction operator perform an element-wise subtraction and
 *       returns a new matrix instance.
 */
TYPED_TEST(Matrix3DSubtraction, MinusOperator_ReturnsDifference)
{
    const fgm::Matrix3D difference = this->_matA - this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, difference);
}


/**
 * @test Verify that the binary subtraction operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Matrix3DSubtraction, MixedTypeSubtractionPromotesType)
{
    constexpr fgm::Matrix3D mat1(3.0f, -1.0f, 4.0f, -23.0f, 4.0f, 5.0f, 3.0f, 3.0f, 12.0f);
    constexpr fgm::Matrix3D mat2(9.0, 10.0, 3.0, 4.0, -1.0, 0.0, 5.0, 12.0, -22.0);

    [[maybe_unused]] constexpr fgm::Matrix3D difference = mat1 - mat2;

    static_assert(std::is_same_v<decltype(difference)::value_type, double>);
}


/**
 * @test Verify that the compound subtraction assignment operator perform an element-wise subtraction
 *       and mutates the matrix in-place.
 */
TYPED_TEST(Matrix3DSubtraction, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_matA -= this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, this->_matA);
}


/**
 * @test Verify that the compound subtraction assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Matrix3DSubtraction, MixedTypeSubtractionAssignmentDoesNotPromoteType)
{
    fgm::Matrix3D mat1(3.0f, -1.0f, 4.0f, -23.0f, 4.0f, 5.0f, 3.0f, 3.0f, 12.0f);
    constexpr fgm::Matrix3D mat2(9.0, 10.0, 3.0, 4.0, -1.0, 0.0, 5.0, 12.0, -22.0);

    mat1 -= mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */