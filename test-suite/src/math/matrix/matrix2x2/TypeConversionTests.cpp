/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verifies @ref fgm::Matrix2D conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**
 * @addtogroup T_FGM_Mat2x2_Type_Conv
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that the matrix can be type promoted and demoted at compile time. */
namespace 
{
    constexpr fgm::Matrix2D s_Mat(1.0f, 2.0f, 3.0f, 4.0f);

    // Verify that the matrix can be type promoted at compile time.
    constexpr fgm::Matrix2D<double> s_MatD(s_Mat);
    static_assert(std::is_same_v<decltype(s_MatD)::value_type, double>);

    // Verify that the matrix can be type demoted at compile time.
    constexpr fgm::Matrix2D<int> s_MatI(s_Mat);
    static_assert(std::is_same_v<decltype(s_MatI)::value_type, int>);
}



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @test Verify that the conversion constructor correctly promotes components from float to double.
 */
TEST(Matrix2DConversionConstructor, PromotesType)
{
    constexpr fgm::Matrix2D mat1(1.0f, 2.0f, 3.0f, 4.0f);

    [[maybe_unused]] constexpr fgm::Matrix2D<double> mat2(mat1);

    static_assert(std::is_same_v<decltype(mat2)::value_type, double>);
}


/** @test Verify that the conversion constructor ensures deep-copy value semantics. */
TEST(Matrix2DConversionConstructor, ReturnsNewInstance)
{
    // Given a float matrix
    constexpr fgm::Matrix2D mat1(1.0f, 2.0f, 3.0f, 4.0f);

    // When converted to a double matrix
    fgm::Matrix2D<double> mat2(mat1);
    // And one of its value mutated
    mat2(0, 0) = 5;

    // Then, the float matrix remains unchanged
    EXPECT_MAT_CONTAINS(std::vector{ 1.0f, 2.0f, 3.0f, 4.0f }, mat1);

    // And, the new matrix is of type double with the mutated value
    EXPECT_MAT_CONTAINS(std::vector{ 5.0, 2.0, 3.0, 4.0 }, mat2);
}


/**
 * @test Verify that the conversion constructor correctly demotes components from double to float.
 */
TEST(Matrix2DConversionConstructor, DemotesType)
{
    constexpr fgm::Matrix2D mat1(1.0, 2.0, 3.0, 4.0);

    [[maybe_unused]] constexpr fgm::Matrix2D<float> mat2(mat1);

    static_assert(std::is_same_v<decltype(mat2)::value_type, float>);
}

/** @} */