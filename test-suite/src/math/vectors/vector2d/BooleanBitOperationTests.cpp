/**
 * @file BooleanBitOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vector2D bitwise operator(&, |, !) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

/** @brief Test fixture for @ref Vector2D<bool> bitwise operations */
class BooleanVector2DBitOperations: public ::testing::Test
{
protected:
    fgm::Vector2D<bool> _vecA;
    fgm::Vector2D<bool> _vecB;
    fgm::Vector2D<bool> _expectedConjunctionVector;
    fgm::Vector2D<bool> _expectedDisjunctionVec;
    fgm::Vector2D<bool> _expectedInvertedVec;

    void SetUp() override
    {
        _vecA                      = { true, false };
        _vecB                      = { true, true };
        _expectedConjunctionVector = { true, false };
        _expectedDisjunctionVec    = { true, true };
        _expectedInvertedVec       = { false, true };
    }
};



/**
 * @addtogroup T_FGM_Vec2_Bool_Bit
 * @{
 */

/** @brief Verify that vector boolean bitwise operations are available at compile time. */
namespace
{
    constexpr fgm::Vector2D vec1(true, false);
    constexpr fgm::Vector2D vec2(false, false);
    constexpr auto andVec = vec1 & vec2;
    constexpr auto orVec = vec1 | vec2;
    constexpr auto notVec = !vec1;

    static_assert(andVec.x() == false);
    static_assert(andVec.y() == false);

    static_assert(orVec.x() == true);
    static_assert(orVec.y() == false);

    static_assert(notVec.x() == false);
    static_assert(notVec.y() == true);

}


/**
 * @brief Verify that the bitwise AND operator perform a component-wise logical conjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVector2DBitOperations, BitwiseAND_PerformComponentwiseConjunction)
{
    const auto mask = this->_vecA & this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, mask);
}

/**
 * @brief Verify that the compound bitwise AND operator performs a component-wise logical conjunction in-place
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVector2DBitOperations, CompoundBitwiseAND_PerformInPlaceConjunction)
{
    this->_vecA &= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @brief Verify that the bitwise OR operator performs a component-wise logical disjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVector2DBitOperations, BitwiseOR_PerformComponentwiseDisjunction)
{
    const auto mask = this->_vecA | this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDisjunctionVec, mask);
}


/**
 * @brief Verify that the compound bitwise OR operator performs a component-wise logical disjunction in-place
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVector2DBitOperations, CompoundBitwiseOR_PerformInPlaceDisjunction)
{
    this->_vecA |= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @brief Verify that the bitwise NOT operator performs a component-wise logical inversion and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVector2DBitOperations, BitwiseNOT_PerformComponentwiseInversion)
{
    const auto mask = !this->_vecA;

    EXPECT_VEC_EQ(this->_expectedInvertedVec, mask);
}

/** @} */
