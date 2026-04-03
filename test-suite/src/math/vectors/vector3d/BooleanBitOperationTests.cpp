/**
 * @file BooleanBitOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verifies @ref fgm::Vector3D bitwise operator(&, |, !) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3DTestSetup.h"



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

/** @brief Test fixture for @ref Vector3D<bool> bitwise operations */
class BooleanVector3DBitOperations: public ::testing::Test
{
protected:
    fgm::Vector3D<bool> _vecA;
    fgm::Vector3D<bool> _vecB;
    fgm::Vector3D<bool> _expectedConjunctionVector;
    fgm::Vector3D<bool> _expectedDisjunctionVec;
    fgm::Vector3D<bool> _expectedInvertedVec;

    void SetUp() override
    {
        _vecA = { true, false, true };
        _vecB = { true, true, false };
        _expectedConjunctionVector = { true, false, false };
        _expectedDisjunctionVec = { true, true, true };
        _expectedInvertedVec = { false, true, false };
    }
};



/**
 * @addtogroup T_FGM_Vec3_Bool_Bit
 * @{
 */

/**
 * @test Verify that the bitwise AND operator perform a component-wise logical conjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVector3DBitOperations, BitwiseAND_PerformComponentwiseConjunction)
{
    const auto mask = this->_vecA & this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, mask);
}

/**
 * @test Verify that the compound bitwise AND operator performs a component-wise logical conjunction in-place
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVector3DBitOperations, CompoundBitwiseAND_PerformInPlaceConjunction)
{
    this->_vecA &= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @test Verify that the bitwise OR operator performs a component-wise logical disjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVector3DBitOperations, BitwiseOR_PerformComponentwiseDisjunction)
{
    const auto mask = this->_vecA | this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDisjunctionVec, mask);
}


/**
 * @test Verify that the compound bitwise OR operator performs a component-wise logical disjunction in-place 
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVector3DBitOperations, CompoundBitwiseOR_PerformInPlaceDisjunction)
{
    this->_vecA |= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @test Verify that the bitwise NOT operator performs a component-wise logical inversion and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVector3DBitOperations, BitwiseNOT_PerformComponentwiseInversion)
{
    const auto mask = !this->_vecA;

    EXPECT_VEC_EQ(this->_expectedInvertedVec, mask);
}

/** @} */