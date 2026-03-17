/**
 * @file BooleanBitOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref Vector4D<bool> bitwise operator(&, |, !) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;


/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

/** @brief Test fixture for @ref Vector4D<bool> bitwise operations */
class BooleanVectorBitOperations: public ::testing::Test
{
    protected:
    fgm::Vector4D<bool> vecA;
    fgm::Vector4D<bool> vecB;
    fgm::Vector4D<bool> expectedAndVector;
    fgm::Vector4D<bool> expectedOrVector;
    fgm::Vector4D<bool> expectedNotAVector;

    void SetUp() override
    {
        vecA = { true, false, true, false };
        vecB = { true, true, false, false };
        expectedAndVector = { true, false, false, false };
        expectedOrVector = { true, true, true, false };
        expectedNotAVector = { false, true, false, true };
    }
};


/**************************************
 *                                    *
 *                TESTS               *
 *                                    *
 **************************************/

/**
 * @test Verify that the @ref fgm::Vector4D<bool> bitwise AND operator performs a component-wise logical conjunction
 *        and returns the correct boolean mask.
 */
TEST_F(BooleanVectorBitOperations, BitwiseAndReturnsComponentwiseAnd)
{
    auto mask = this->vecA & this->vecB;

    EXPECT_VEC_EQ(this->expectedAndVector, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D<bool> bitwise OR operator performs a component-wise logical disjunction
 *        and returns the correct boolean mask.
 */
TEST_F(BooleanVectorBitOperations, BitwiseOrReturnsComponentwiseOr)
{
    auto mask = this->vecA | this->vecB;

    EXPECT_VEC_EQ(this->expectedOrVector, mask);
}


/**
 * @test Verify that the @ref fgm::Vector4D<bool> bitwise NOT operator performs a component-wise logical inversion
 *        and returns the correct boolean mask.
 */
TEST_F(BooleanVectorBitOperations, BitwiseNotReturnsInvertedVector)
{
    auto mask = !this->vecA;

    EXPECT_VEC_EQ(this->expectedNotAVector, mask);
}