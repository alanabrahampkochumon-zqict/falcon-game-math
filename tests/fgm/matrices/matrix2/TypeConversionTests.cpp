/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Mat2 conversion constructor logic.
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
    constexpr fgm::Mat2 MAT(1.0f, 2.0f, 3.0f, 4.0f);

    // Verify that the matrix can be type promoted at compile time.
    constexpr fgm::Mat2<double> MAT_D(MAT);
    static_assert(std::is_same_v<decltype(MAT_D)::value_type, double>);

    // Verify that the matrix can be type demoted at compile time.
    constexpr fgm::Mat2<int> MATI(MAT);
    static_assert(std::is_same_v<decltype(MATI)::value_type, int>);
} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @brief Verify that the conversion constructor correctly promotes components from float to double.
 */
TEST(Mat2ConversionConstructor, PromotesType)
{
    const fgm::Mat2 mat1(1.0f, 2.0f, 3.0f, 4.0f);

    [[maybe_unused]] const fgm::Mat2<double> mat2(mat1);

    static_assert(std::is_same_v<decltype(mat2)::value_type, double>);
}


/** @brief Verify that the conversion constructor ensures deep-copy value semantics. */
TEST(Mat2ConversionConstructor, ReturnsNewInstance)
{
    // Given a float matrix
    const fgm::Mat2 mat1(1.0f, 2.0f, 3.0f, 4.0f);

    // When converted to a double matrix
    fgm::Mat2<double> mat2(mat1);
    // And one of its value mutated
    mat2(0, 0) = 5;

    // Then, the float matrix remains unchanged
    EXPECT_MAT_CONTAINS(std::vector{ 1.0f, 2.0f, 3.0f, 4.0f }, mat1);

    // And, the new matrix is of type double with the mutated value
    EXPECT_MAT_CONTAINS(std::vector{ 5.0, 2.0, 3.0, 4.0 }, mat2);
}


/**
 * @brief Verify that the conversion constructor correctly demotes components from double to float.
 */
TEST(Mat2ConversionConstructor, DemotesType)
{
    const fgm::Mat2 mat1(1.0, 2.0, 3.0, 4.0);

    [[maybe_unused]] const fgm::Mat2<float> mat2(mat1);

    static_assert(std::is_same_v<decltype(mat2)::value_type, float>);
}

/** @} */
