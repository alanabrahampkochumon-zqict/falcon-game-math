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



TEST(Matrix2D_Initialization, InitializedWithOutParametersProvidesIdentityMatrix)
{
    // Arrange & Act
    const fgm::Matrix2D<float> mat;

    // Assert
    EXPECT_MAT_IDENTITY(mat);
}
