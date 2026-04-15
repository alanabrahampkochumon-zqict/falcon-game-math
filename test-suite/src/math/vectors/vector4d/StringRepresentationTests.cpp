/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 16, 2026
 *
 * @brief Verify @ref fgm::Vector4D string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"

#include <sstream>



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

class Vector4DStringRepresentationTests: public ::testing::Test
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
 * @addtogroup T_FGM_Vec4_String_Repr
 * @{
 */

/** @test Verify that the string representation matches the expected format for integral types. */
TEST_F(Vector4DStringRepresentationTests, IntegralRepresentation)
{
    constexpr fgm::Vector4D vec(1, 2, 3, 4);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1, 2, 3, 4>\n");
}


/**
 * @test Verify that the string representation matches the expected format for single-precision
 *       floating-point types.
 */
TEST_F(Vector4DStringRepresentationTests, FloatRepresentation)
{
    constexpr fgm::Vector4D vec(1.2345f, 2.0f, 3.56789f, 4.2f);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1.23450, 2.00000, 3.56789, 4.20000>\n");
}


/**
 * @test Verify that the string representation matches the expected format for double-precision
 *       floating-point types.
 */
TEST_F(Vector4DStringRepresentationTests, DoubleRepresentation)
{
    constexpr fgm::Vector4D vec(1.2345789777, 2.65831, 3.161285, 4.0);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1.234578977700000, 2.658310000000000, 3.161285000000000, 4.000000000000000>\n");
}

/** @} */
