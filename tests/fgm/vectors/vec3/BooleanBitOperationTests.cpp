/**
 * @file BooleanBitOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref fgm::Vec3 bitwise operator(&, |, !) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

/** @brief Test fixture for @ref Vec3<bool> bitwise operations */
class BooleanVec3BitOperations: public ::testing::Test
{
protected:
    fgm::Vec3<bool> _vecA;
    fgm::Vec3<bool> _vecB;
    fgm::Vec3<bool> _expectedConjunctionVector;
    fgm::Vec3<bool> _expectedDisjunctionVec;
    fgm::Vec3<bool> _expectedInvertedVec;

    void SetUp() override
    {
        _vecA                      = { true, false, true };
        _vecB                      = { true, true, false };
        _expectedConjunctionVector = { true, false, false };
        _expectedDisjunctionVec    = { true, true, true };
        _expectedInvertedVec       = { false, true, false };
    }
};



/**
 * @addtogroup T_FGM_Vec3_Bool_Bit
 * @{
 */

/** @brief Verify that vector boolean bitwise operations are available at compile time. */
namespace
{
    constexpr fgm::Vec3 vec1(true, false, true);
    constexpr fgm::Vec3 vec2(false, false, true);
    constexpr auto andVec = vec1 & vec2;
    constexpr auto orVec  = vec1 | vec2;
    constexpr auto notVec = !vec1;

    static_assert(andVec.x() == false);
    static_assert(andVec.y() == false);
    static_assert(andVec.z() == true);

    static_assert(orVec.x() == true);
    static_assert(orVec.y() == false);
    static_assert(orVec.z() == true);

    static_assert(notVec.x() == false);
    static_assert(notVec.y() == true);
    static_assert(notVec.z() == false);

} // namespace


/**
 * @brief Verify that the bitwise AND operator perform a component-wise logical conjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVec3BitOperations, BitwiseAND_PerformComponentwiseConjunction)
{
    const auto mask = this->_vecA & this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, mask);
}

/**
 * @brief Verify that the compound bitwise AND operator performs a component-wise logical conjunction in-place
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVec3BitOperations, CompoundBitwiseAND_PerformInPlaceConjunction)
{
    this->_vecA &= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @brief Verify that the bitwise OR operator performs a component-wise logical disjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVec3BitOperations, BitwiseOR_PerformComponentwiseDisjunction)
{
    const auto mask = this->_vecA | this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDisjunctionVec, mask);
}


/**
 * @brief Verify that the compound bitwise OR operator performs a component-wise logical disjunction in-place
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVec3BitOperations, CompoundBitwiseOR_PerformInPlaceDisjunction)
{
    this->_vecA |= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @brief Verify that the bitwise NOT operator performs a component-wise logical inversion and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVec3BitOperations, BitwiseNOT_PerformComponentwiseInversion)
{
    const auto mask = !this->_vecA;

    EXPECT_VEC_EQ(this->_expectedInvertedVec, mask);
}

/** @} */
