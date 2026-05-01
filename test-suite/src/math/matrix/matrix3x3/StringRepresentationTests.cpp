/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref fgm::Matrix3D string representation.
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

class Matrix3DStringRepresentationTests: public ::testing::Test
{
    /** @brief Switch to use full precision for testing. */
    void SetUp() override { fgm::Config::useFullPrecision = true; }

    /** @brief Switch back to normal log precision. */
    void TearDown() override { fgm::Config::useFullPrecision = false; }
};



/**
 * @addtogroup T_FGM_Mat3x3_String_Repr
 * @{
 */

/** @test Verify that the string representation matches the expected format for integral types. */
TEST_F(Matrix3DStringRepresentationTests, IntegralRepresentation)
{
    constexpr fgm::Matrix3D mat(1, 2, 3, 4, 5, 6, 7, 8, 9);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1 2 3|\n|4 5 6|\n|7 8 9|\n");
}


/**
 * @test Verify that the string representation matches the expected format for single-precision
 *       floating-point types.
 */
TEST_F(Matrix3DStringRepresentationTests, FloatRepresentation)
{
    constexpr fgm::Matrix3D mat(1.2345f, 2.0f, 4.53823f, 3.323f, 3.5832f, 5.8392f, 9.9238f, -12.0532f, 3.2312f);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1.23450 2.00000 4.53823|\n|3.32300 3.58320 5.83920|\n|9.92380 -12.05320 3.23120|\n");
}


/**
 * @test Verify that the string representation matches the expected format for double-precision
 *       floating-point types.
 */
TEST_F(Matrix3DStringRepresentationTests, DoubleRepresentation)
{
    constexpr fgm::Matrix3D mat(1.2345789777, 2.65831, 2.0, 4.0, 3.2345789777, 1.2345789777, 12.0, -6.2345789777,
                                0.2345789777);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(),
              "|1.234578977700000 2.658310000000000 2.000000000000000|\n|4.000000000000000 3.234578977700000 "
              "1.234578977700000|\n|12.000000000000000 -6.234578977700000 0.234578977700000|\n");
}

/** @} */
