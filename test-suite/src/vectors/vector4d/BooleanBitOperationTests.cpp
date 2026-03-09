/**
 * @file BooleanBitOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Boolean `Vector4D` bitwise operation (!, &, |) tests.
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

class BooleanVectorBitOperations: public ::testing::Test
{
    protected:
    math::Vector4D<bool> vecA;
    math::Vector4D<bool> vecB;
    math::Vector4D<bool> expectedAndVector;
    math::Vector4D<bool> expectedOrVector;
    math::Vector4D<bool> expectedNotAVector;

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

TEST_F(BooleanVectorBitOperations, BitwiseAndReturnsComponentwiseAnd)
{
    // Given two bool vectors

    // When they are `AND` together
    auto result = this->vecA & this->vecB;

    // Then, we get another vector with componentwise AND applied
    EXPECT_VEC_EQ(this->expectedAndVector, result);
}

TEST_F(BooleanVectorBitOperations, BitwiseOrReturnsComponentwiseOr)
{
    // Given two bool vectors

    // When they are `OR` together
    auto result = this->vecA | this->vecB;

    // Then, we get another vector with componentwise OR applied
    EXPECT_VEC_EQ(this->expectedOrVector, result);
}

TEST_F(BooleanVectorBitOperations, BitwiseNotReturnsInvertedVector)
{
    // Given a bool vector

    // When they are `OR` together
    auto result = !this->vecA;

    // Then, we get another vector with componentwise NOT applied
    EXPECT_VEC_EQ(this->expectedNotAVector, result);
}