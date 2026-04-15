/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vector2D string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"

#include <sstream>



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

class Vector2DStringRepresentationTests: public ::testing::Test
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
 * @addtogroup T_FGM_Vec2_String_Repr
 * @{
 */

/** @test Verify that the string representation matches the expected format for integral types. */
TEST_F(Vector2DStringRepresentationTests, IntegralRepresentation)
{
    constexpr fgm::Vector2D vec(1, 2);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1, 2>\n");
}


/**
 * @test Verify that the string representation matches the expected format for single-precision
 *       floating-point types.
 */
TEST_F(Vector2DStringRepresentationTests, FloatRepresentation)
{
    constexpr fgm::Vector2D vec(1.2345f, 2.0f);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1.23450, 2.00000>\n");
}


/**
 * @test Verify that the string representation matches the expected format for double-precision
 *       floating-point types.
 */
TEST_F(Vector2DStringRepresentationTests, DoubleRepresentation)
{
    constexpr fgm::Vector2D vec(1.2345789777, 2.65831);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1.234578977700000, 2.658310000000000>\n");
}

/** @} */
