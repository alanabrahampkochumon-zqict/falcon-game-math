/**
 * @file BooleanBitOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref fgm::Vector4D<bool> bitwise operator(&, |, !) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

/** @brief Test fixture for @ref Vector4D<bool> bitwise operations */
class BooleanVectorBitOperations: public ::testing::Test
{
protected:
    fgm::Vector4D<bool> _vecA;
    fgm::Vector4D<bool> _vecB;
    fgm::Vector4D<bool> _expectedConjunctionVector;
    fgm::Vector4D<bool> _expectedDisjunctionVec;
    fgm::Vector4D<bool> _expectedInvertedVec;

    void SetUp() override
    {
        _vecA = { true, false, true, false };
        _vecB = { true, true, false, false };
        _expectedConjunctionVector = { true, false, false, false };
        _expectedDisjunctionVec = { true, true, true, false };
        _expectedInvertedVec = { false, true, false, true };
    }
};



/**
 * @addtogroup T_FGM_Vec4_Bool_Bit
 * @{
 */

/**
 * @test Verify that the bitwise AND operator perform a component-wise logical conjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVectorBitOperations, BitwiseAND_PerformComponentwiseConjunction)
{
    const auto mask = this->_vecA & this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, mask);
}

/**
 * @test Verify that the compound bitwise AND operator performs a component-wise logical conjunction in-place
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVectorBitOperations, CompoundBitwiseAND_PerformInPlaceConjunction)
{
    this->_vecA &= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @test Verify that the bitwise OR operator performs a component-wise logical disjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVectorBitOperations, BitwiseOR_PerformComponentwiseDisjunction)
{
    const auto mask = this->_vecA | this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDisjunctionVec, mask);
}


/**
 * @test Verify that the compound bitwise OR operator performs a component-wise logical disjunction in-place 
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVectorBitOperations, CompoundBitwiseOR_PerformInPlaceDisjunction)
{
    this->_vecA |= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @test Verify that the bitwise NOT operator performs a component-wise logical inversion and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVectorBitOperations, BitwiseNOT_PerformComponentwiseInversion)
{
    const auto mask = !this->_vecA;

    EXPECT_VEC_EQ(this->_expectedInvertedVec, mask);
}

/** @} */