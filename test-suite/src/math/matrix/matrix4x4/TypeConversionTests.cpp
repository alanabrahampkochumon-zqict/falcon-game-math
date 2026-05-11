/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify @ref fgm::Matrix4D conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**
 * @addtogroup T_FGM_Mat4x4_Type_Conv
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
    constexpr fgm::Matrix4D MAT(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f,
                                15.0f, 16.0f);

    // Verify that the matrix can be type promoted at compile time.
    constexpr fgm::Matrix4D<double> MAT_D(MAT);
    static_assert(std::is_same_v<decltype(MAT_D)::value_type, double>);

    // Verify that the matrix can be type demoted at compile time.
    constexpr fgm::Matrix4D<int> MATI(MAT);
    static_assert(std::is_same_v<decltype(MATI)::value_type, int>);
}



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @test Verify that the conversion constructor correctly promotes components from float to double.
 */
TEST(Matrix4DConversionConstructor, PromotesType)
{
    constexpr fgm::Matrix4D mat1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f,
                                15.0f, 16.0f);

    [[maybe_unused]] constexpr fgm::Matrix4D<double> mat2(mat1);

    static_assert(std::is_same_v<decltype(mat2)::value_type, double>);
}


/** @test Verify that the conversion constructor ensures deep-copy value semantics. */
TEST(Matrix4DConversionConstructor, ReturnsNewInstance)
{
    // Given a float matrix
    constexpr fgm::Matrix4D mat1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f,
                                 14.0f, 15.0f, 16.0f);

    // When converted to a double matrix
    fgm::Matrix4D<double> mat2(mat1);
    // And one of its value mutated
    mat2(0, 0) = 5;

    // Then, the float matrix remains unchanged
    EXPECT_MAT_CONTAINS(std::vector{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f,
                                     14.0f, 15.0f, 16.0f },
                        mat1);

    // And, the new matrix is of type double with the mutated value
    EXPECT_MAT_CONTAINS(std::vector{ 5.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 }, mat2);
}


/**
 * @test Verify that the conversion constructor correctly demotes components from double to float.
 */
TEST(Matrix4DConversionConstructor, DemotesType)
{
    constexpr fgm::Matrix4D mat1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0,
                                 14.0, 15.0, 16.0);

    [[maybe_unused]] constexpr fgm::Matrix4D<float> mat2(mat1);

    static_assert(std::is_same_v<decltype(mat2)::value_type, float>);
}

/** @} */