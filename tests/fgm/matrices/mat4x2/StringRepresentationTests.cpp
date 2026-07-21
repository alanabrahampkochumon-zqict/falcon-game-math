/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref fgm::Mat3x2 string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x2TestSetup.h"

#include <sstream>



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

class Mat3x2StringRepresentationTests: public ::testing::Test
{
    /** @brief Switch to use full precision for testing. */
    void SetUp() override { fgm::Config::useFullPrecision = true; }

    /** @brief Switch back to normal log precision. */
    void TearDown() override { fgm::Config::useFullPrecision = false; }
};



/**
 * @addtogroup T_FGM_Mat2x2_String_Repr
 * @{
 */

/** @brief Verify that the string representation matches the expected format for integral types. */
TEST_F(Mat3x2StringRepresentationTests, IntegralRepresentation)
{
    const fgm::Mat3x2 mat(1, 2, 3, 4, 5, 6);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1 2|\n|3 4|\n|5 6|\n");
}


/**
 * @brief Verify that the string representation matches the expected format for single-precision
 *       floating-point types.
 */
TEST_F(Mat3x2StringRepresentationTests, FloatRepresentation)
{
    const fgm::Mat3x2 mat(1.2345f, 2.0f, 3.0f, 4.53823f, 3.323f, 12.003f);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1.23450 2.00000|\n|3.00000 4.53823|\n|3.32300 12.00300|\n");
}


/**
 * @brief Verify that the string representation matches the expected format for double-precision
 *       floating-point types.
 */
TEST_F(Mat3x2StringRepresentationTests, DoubleRepresentation)
{
    const fgm::Mat3x2 mat(1.2345789777, 2.65831, 5.39281, 2.0, 4.0, 2.0);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(),
              "|1.234578977700000 2.658310000000000|\n"
              "|5.392810000000000 2.000000000000000|\n"
              "|4.000000000000000 2.000000000000000|\n");
}

/** @} */
