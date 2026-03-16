/**
 * @file StringStreamTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 16, 2026
 *
 * @brief Verifies @ref Vector4D string representation.
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
    void SetUp() override { fgm::Config::useFullPrecision = true; }

    /** @brief Switch back to normal log precision. */
    void TearDown() override { fgm::Config::useFullPrecision = false; }
};




/**************************************
 *                                    *
 *               TESTS                *
 *                                    *
 **************************************/

/** test Verify @ref Vector4D string representation of integral types */
TEST_F(Vector4DStringRepresentationTests, IntegralRepresentation)
{
    fgm::Vector4D vec(1, 2, 3, 4);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1, 2, 3, 4>");
}


/** test Verify @ref Vector4D string representation of single precision floating type. */
TEST_F(Vector4DStringRepresentationTests, FloatRepresentation)
{
    fgm::Vector4D vec(1.2345f, 2.0f, 3.56789f, 4.2f);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1.2345, 2.0, 3.56789, 4.2>");
}

/** test Verify @ref Vector4D string representation of double precision floating type. */
TEST_F(Vector4DStringRepresentationTests, DoubleRepresentation)
{
    fgm::Vector4D vec(1.2345789777, 2.65831, 3.161285, 4.0);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1.2345789777, 2.2.65831, 3.161285, 4.0>");
}