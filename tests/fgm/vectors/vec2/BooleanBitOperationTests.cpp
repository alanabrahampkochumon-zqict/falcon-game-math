/**
 * @file BooleanBitOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vec2 bitwise operator(&, |, !) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"


/**
 * @addtogroup T_FGM_Vec2_Bool_Bit
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Vec2 boolean bitwise operations.
     */
    class BooleanVec2BitOperationsTests: public testing::Test
    {
    protected:
        fgm::Vec2<bool> _vecA;
        fgm::Vec2<bool> _vecB;
        fgm::Vec2<bool> _expectedConjunctionVector;
        fgm::Vec2<bool> _expectedDisjunctionVec;
        fgm::Vec2<bool> _expectedInvertedVec;

        void SetUp() override
        {
            _vecA                      = { true, false };
            _vecB                      = { true, true };
            _expectedConjunctionVector = { true, false };
            _expectedDisjunctionVec    = { true, true };
            _expectedInvertedVec       = { false, true };
        }
    };



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Vec2 VEC_A(true, false);
        constexpr fgm::Vec2 VEC_B(false, false);


        /// @test Verify that vector AND returns a valid vector at compile time.
        constexpr auto AND_VEC = VEC_A & VEC_B;
        static_assert(AND_VEC.x() == false);
        static_assert(AND_VEC.y() == false);


        /// @test Verify that vector OR returns a valid vector at compile time.
        constexpr auto OR_VEC = VEC_A | VEC_B;
        static_assert(OR_VEC.x() == true);
        static_assert(OR_VEC.y() == false);


        /// @test Verify that vector NOT returns a valid vector at compile time.
        constexpr auto NOT_VEC = !VEC_A;
        static_assert(NOT_VEC.x() == false);
        static_assert(NOT_VEC.y() == true);

    } // namespace static_tests

} // namespace



/**
 * @brief Verify that the bitwise AND operator perform a component-wise logical conjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVec2BitOperationsTests, BitwiseAND_PerformComponentwiseConjunction)
{
    const auto mask = this->_vecA & this->_vecB;
    EXPECT_VEC_EQ(this->_expectedConjunctionVector, mask);
}

/**
 * @brief Verify that the compound bitwise AND operator performs a component-wise logical conjunction in-place
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVec2BitOperationsTests, CompoundBitwiseAND_PerformInPlaceConjunction)
{
    this->_vecA &= this->_vecB;
    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @brief Verify that the bitwise OR operator performs a component-wise logical disjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVec2BitOperationsTests, BitwiseOR_PerformComponentwiseDisjunction)
{
    const auto mask = this->_vecA | this->_vecB;
    EXPECT_VEC_EQ(this->_expectedDisjunctionVec, mask);
}


/**
 * @brief Verify that the compound bitwise OR operator performs a component-wise logical disjunction in-place
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVec2BitOperationsTests, CompoundBitwiseOR_PerformInPlaceDisjunction)
{
    this->_vecA |= this->_vecB;
    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @brief Verify that the bitwise NOT operator performs a component-wise logical inversion and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVec2BitOperationsTests, BitwiseNOT_PerformComponentwiseInversion)
{
    const auto mask = !this->_vecA;
    EXPECT_VEC_EQ(this->_expectedInvertedVec, mask);
}

/** @} */
