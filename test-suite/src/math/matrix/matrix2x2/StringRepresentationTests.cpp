/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref fgm::Matrix2D string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"

#include <sstream>



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

class Matrix2DStringRepresentationTests: public ::testing::Test
{
    /** @brief Switch to use full precision for testing. */
    void SetUp() override
    {
        fgm::Config::useFullPrecision = true;
    }

    /** @brief Switch back to normal log precision. */
    void TearDown() override
    {
        fgm::Config::useFullPrecision = false;
    }
};



/**
 * @addtogroup T_FGM_Mat2x2_String_Repr
 * @{
 */

/** @test Verify that the string representation matches the expected format for integral types. */
TEST_F(Matrix2DStringRepresentationTests, IntegralRepresentation)
{
    constexpr fgm::Matrix2D mat(1, 2, 3, 4);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1 2|\n|3 4|\n");
}


/**
 * @test Verify that the string representation matches the expected format for single-precision
 *       floating-point types.
 */
TEST_F(Matrix2DStringRepresentationTests, FloatRepresentation)
{
    constexpr fgm::Matrix2D mat(1.2345f, 2.0f, 4.53823f, 3.323f);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1.23450 2.00000|\n|4.53823 3.32300|\n");
}


/**
 * @test Verify that the string representation matches the expected format for double-precision
 *       floating-point types.
 */
TEST_F(Matrix2DStringRepresentationTests, DoubleRepresentation)
{
    constexpr fgm::Matrix2D mat(1.2345789777, 2.65831, 2.0, 4.0);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1.234578977700000 2.658310000000000|\n|2.000000000000000 4.000000000000000|\n");
}

/** @} */
