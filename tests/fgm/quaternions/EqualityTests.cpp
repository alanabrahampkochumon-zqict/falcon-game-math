/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 05, 2026
 *
 * @brief Verify @ref fgm::Quaternion equality operator (==, !=) and their functional counterpart's (vecEq,  allEq,
 * anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"

#include <fgm/common/Constants.h>


/**
 * @addtogroup T_FGM_Quaternion_Equality
 * @{
 */

namespace
{

    /**************************************
     *             TEST SETUP             *
     **************************************/

    constexpr auto NAN_F = fgm::constants::NaN;
    constexpr auto INF   = fgm::constants::INFINITY_F;

    template <typename T>
    class QuaternionEqualityTests: public testing::Test
    {
    protected:
        fgm::Quaternion<T> _eqQuatA, _eqQuatB, _eqVecQuatA, _eqVecQuatB;
        fgm::Quaternion<T> _dissimilarQuat;
        fgm::Quaternion<bool> _equalityMask;
        fgm::Quaternion<bool> _inequalityMask;


        void SetUp() override
        {
            _eqQuatA = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
            _eqQuatB = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
            // Scalar part for *VecQuat* are different
            _eqVecQuatA     = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(56.213432412) };
            _eqVecQuatB     = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
            _dissimilarQuat = { T(7.1234568789), T(2.123458319), T(24.00), T(123.123489172589) };
            _equalityMask   = { false, true, false, true };
            _inequalityMask = { true, false, true, false };
        }
    };
    TYPED_TEST_SUITE(QuaternionEqualityTests, SupportedArithmeticTypes);




    namespace
    {
        // Quat C and D have same vector but different vector part
        constexpr fgm::Quaternion QUAT_A(1, 2, 4, 12);
        constexpr fgm::Quaternion QUAT_B(3, 2, 1, 7);
        constexpr fgm::Quaternion QUAT_C(1, 2, 4, 12);
        constexpr fgm::Quaternion QUAT_D(1, 2, 4, 18);

        /// @test Verify that Quaternion allEq returns the correct boolean at compile time,
        ///       given two quaternions with different components.
        static_assert(QUAT_A.allEq(QUAT_B) == false);

        /// @test Verify that Quaternion allEq returns the correct boolean at compile time,
        ///       given two quaternions with same components.
        static_assert(QUAT_A.allEq(QUAT_C) == true);


        /// @test Verify that Quaternion allEq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with different components.
        static_assert(fgm::Quaternion<int>::allEq(QUAT_A, QUAT_B) == false);

        /// @test Verify that Quaternion allEq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with same components.
        static_assert(fgm::Quaternion<int>::allEq(QUAT_A, QUAT_C) == true);


        /// @test Verify that Quaternion eq returns the correct boolean mask at compile time.
        constexpr auto EQ_QUAT_MASK = QUAT_A.eq(QUAT_B);
        static_assert(EQ_QUAT_MASK.x() == false);
        static_assert(EQ_QUAT_MASK.y() == true);
        static_assert(EQ_QUAT_MASK.z() == false);
        static_assert(EQ_QUAT_MASK.w() == false);

        /// @test Verify that Quaternion eq (static wrapper) returns the correct boolean mask at compile time.
        constexpr auto EQ_QUAT_MASK_STATIC = fgm::Quaternion<int>::eq(QUAT_A, QUAT_B);
        static_assert(EQ_QUAT_MASK_STATIC.x() == false);
        static_assert(EQ_QUAT_MASK_STATIC.y() == true);
        static_assert(EQ_QUAT_MASK_STATIC.z() == false);
        static_assert(EQ_QUAT_MASK_STATIC.w() == false);


        /// @test Verify that Quaternion vecEq returns the correct boolean at compile time,
        ///       given two quaternions with different vector parts.
        static_assert(QUAT_A.vecEq(QUAT_B) == false);

        /// @test Verify that Quaternion allEq returns the correct boolean at compile time,
        ///       given two quaternions with same vector parts.
        static_assert(QUAT_A.vecEq(QUAT_D) == true);


        /// @test Verify that Quaternion allEq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with different vector parts.
        static_assert(fgm::Quaternion<int>::vecEq(QUAT_A, QUAT_B) == false);

        /// @test Verify that Quaternion allEq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with same vector parts.
        static_assert(fgm::Quaternion<int>::vecEq(QUAT_A, QUAT_D) == true);

        // constexpr auto allEqQuat5 = QUAT_A == QUAT_B;
        // static_assert(allEqQuat5 == false);
        //
        // constexpr auto allEqQuat6 = QUAT_A == QUAT_C;
        // static_assert(allEqQuat6 == true);
        //
        // constexpr auto maskEqQuat = QUAT_A.eq(QUAT_B);
        // static_assert(maskEqQuat.x() == false);
        // static_assert(maskEqQuat.y() == true);
        // static_assert(maskEqQuat.z() == false);
        // static_assert(maskEqQuat.w() == false);
        //
        //
        // // Inequality tests
        // constexpr auto allNeqQuat1 = QUAT_A.anyNeq(QUAT_B);
        // static_assert(allNeqQuat1 == true);
        //
        // constexpr auto allNeqQuat2 = QUAT_A.anyNeq(QUAT_C);
        // static_assert(allNeqQuat2 == false);
        //
        // constexpr auto allNeqQuat3 = fgm::Quaternion<int>::anyNeq(QUAT_A, QUAT_B);
        // static_assert(allNeqQuat3 == true);
        //
        // constexpr auto allNeqQuaternion = fgm::Quaternion<int>::anyNeq(QUAT_A, QUAT_C);
        // static_assert(allNeqQuaternion == false);
        //
        // constexpr auto allNeqQuat5 = QUAT_A != QUAT_B;
        // static_assert(allNeqQuat5 == true);
        //
        // constexpr auto allNeqQuat6 = QUAT_A != QUAT_C;
        // static_assert(allNeqQuat6 == false);
        //
        // constexpr auto maskNeqQuat = QUAT_A.neq(QUAT_B);
        // static_assert(maskNeqQuat.x() == true);
        // static_assert(maskNeqQuat.y() == false);
        // static_assert(maskNeqQuat.z() == true);
        // static_assert(maskNeqQuat.w() == true);

    } // namespace

} // namespace



/**************************************
 *                                    *
 *           EQUALITY TESTS           *
 *                                    *
 **************************************/

/**************************************
 *             ALL EQ                 *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, AllEq_IdenticalQuaternionsReturnsTrue)
{ EXPECT_TRUE(this->_eqQuatA.allEq(this->_eqQuatB)); }


TYPED_TEST(QuaternionEqualityTests, AllEq_DifferentQuaternionsReturnsFalse)
{ EXPECT_FALSE(this->_eqQuatA.allEq(this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, AllEq_NanQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Quaternion<double> quatB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };

    EXPECT_FALSE(quatA.allEq(quatB));
}


TEST(QuaternionEqualityTests, AllEq_IdenticalInfiniteQuaternionsReturnsTrue)
{
    const fgm::Quaternion quatA = { INF, -INF, INF, -INF };
    const fgm::Quaternion quatB = { INF, -INF, INF, -INF };

    EXPECT_TRUE(quatA.allEq(quatB));
}


TEST(QuaternionEqualityTests, AllEq_DifferentInfiniteQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA = { INF, INF, INF, -INF };
    const fgm::Quaternion quatB = { INF, -INF, INF, INF };

    EXPECT_FALSE(quatA.allEq(quatB));
}


TYPED_TEST(QuaternionEqualityTests, AllEq_MixedType_IdenticalQuaternionsReturnsTrue)
{
    const fgm::Quaternion quatA(1, 2, 3, 4);
    const fgm::Quaternion quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(quatA.allEq(quatB));
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_AllEq_IdenticalQuaternionsReturnsTrue)
{ EXPECT_TRUE(fgm::Quaternion<TypeParam>::allEq(this->_eqQuatA, this->_eqQuatB)); }


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_AllEq_DifferentQuaternionsReturnsFalse)
{ EXPECT_FALSE(fgm::Quaternion<TypeParam>::allEq(this->_eqQuatA, this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, StaticWrapper_AllEq_NanQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Quaternion<double> quatB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };

    EXPECT_FALSE(fgm::Quaternion<float>::allEq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_AllEq_IdenticalInfiniteQuaternionsReturnsTrue)
{
    const fgm::Quaternion quatA = { INF, -INF, INF, -INF };
    const fgm::Quaternion quatB = { INF, -INF, INF, -INF };

    EXPECT_TRUE(fgm::Quaternion<float>::allEq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_AllEq_DifferentInfiniteQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA = { INF, INF, INF, -INF };
    const fgm::Quaternion quatB = { INF, -INF, INF, INF };

    EXPECT_FALSE(fgm::Quaternion<float>::allEq(quatA, quatB));
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_AllEq_MixedType_IdenticalQuaternionsReturnsTrue)
{
    const fgm::Quaternion quatA(1, 2, 3, 4);
    const fgm::Quaternion quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(fgm::Quaternion<int>::allEq(quatA, quatB));
}



/**************************************
 *          EQUALITY MASK             *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, Eq_ReturnsCorrectBooleanMask)
{
    const fgm::Quaternion<bool> mask = this->_eqQuatA.eq(this->_dissimilarQuat);
    EXPECT_QUAT_EQ(this->_equalityMask, mask);
}


TEST(QuaternionEqualityTests, Eq_MixedType_ReturnsCorrectBooleanMask)
{
    const fgm::Quaternion quatA        = { 1, 2, 3, 4 };
    const fgm::Quaternion quatB        = { 1.0, 4.0, 0.0, 4.0 };
    const fgm::Quaternion expectedMask = { true, false, false, true };

    const fgm::Quaternion<bool> mask = quatA.eq(quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, Eq_NaNQuaternionsReturnsFalseBooleanMask)
{
    const fgm::Quaternion quatA        = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Quaternion quatB        = { 1.0, -5.88874789, fgm::constants::INFINITY_D, fgm::constants::NaN_D };
    const fgm::Quaternion expectedMask = { false, false, false, false };

    const fgm::Quaternion mask = quatA.eq(quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, Eq_InfiniteQuaternionsReturnsCorrectBooleanMask)
{
    const fgm::Quaternion quatA         = { INF, -INF, INF, -INF };
    const fgm::Quaternion<double> quatB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11, 10e11 };
    const fgm::Quaternion expectedMask  = { true, false, false, false };

    const fgm::Quaternion mask = quatA.eq(quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_Eq_ReturnsCorrectBooleanMask)
{
    const fgm::Quaternion<bool> mask = fgm::Quaternion<TypeParam>::eq(this->_eqQuatA, this->_dissimilarQuat);
    EXPECT_QUAT_EQ(this->_equalityMask, mask);
}


TEST(QuaternionEqualityTests, StaticWrapper_Eq_MixedType_ReturnsCorrectBooleanMask)
{
    const fgm::Quaternion quatA        = { 1, 2, 3, 4 };
    const fgm::Quaternion quatB        = { 1.0, 4.0, 0.0, 4.0 };
    const fgm::Quaternion expectedMask = { true, false, false, true };

    const fgm::Quaternion<bool> mask = fgm::Quaternion<int>::eq(quatA, quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, StaticWrapper_Eq_NaNQuaternionsReturnsFalseBooleanMask)
{
    const fgm::Quaternion quatA        = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Quaternion quatB        = { 1.0, -5.88874789, fgm::constants::INFINITY_D, fgm::constants::NaN_D };
    const fgm::Quaternion expectedMask = { false, false, false, false };

    const fgm::Quaternion<bool> mask = fgm::Quaternion<float>::eq(quatA, quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, StaticWrapper_Eq_InfiniteQuaternionsReturnsCorrectBooleanMask)
{
    const fgm::Quaternion quatA         = { INF, -INF, INF, -INF };
    const fgm::Quaternion<double> quatB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11, 10e11 };
    const fgm::Quaternion expectedMask  = { true, false, false, false };

    const fgm::Quaternion<bool> mask = fgm::Quaternion<float>::eq(quatA, quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}



/**************************************
 *             VEC EQ                 *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, VeqEq_QuaternionsWithIdenticalVectorPartReturnsTrue)
{ EXPECT_TRUE(this->_eqVecQuatA.vecEq(this->_eqVecQuatB)); }


TYPED_TEST(QuaternionEqualityTests, VeqEq_QuaternionsWithDifferentVectorPartReturnsFalse)
{ EXPECT_FALSE(this->_eqVecQuatA.vecEq(this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, VeqEq_NanQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Quaternion<double> quatB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };

    EXPECT_FALSE(quatA.vecEq(quatB));
}


TEST(QuaternionEqualityTests, VeqEq_IdenticalInfiniteQuaternionsReturnsTrue)
{
    const fgm::Quaternion quatA = { INF, -INF, INF, 4.0f };
    const fgm::Quaternion quatB = { INF, -INF, INF, 8.0f };

    EXPECT_TRUE(quatA.vecEq(quatB));
}


TEST(QuaternionEqualityTests, VeqEq_DifferentInfiniteQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA = { INF, INF, INF, -INF };
    const fgm::Quaternion quatB = { INF, -INF, INF, -INF };

    EXPECT_FALSE(quatA.vecEq(quatB));
}


TYPED_TEST(QuaternionEqualityTests, VeqEq_MixedType_QuaternionsWithIdenticalVectorPartReturnsTrue)
{
    const fgm::Quaternion quatA(1, 2, 3, 4);
    const fgm::Quaternion quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(quatA.allEq(quatB));
}

TYPED_TEST(QuaternionEqualityTests, StaticWrapper_VeqEq_QuaternionsWithIdenticalVectorPartReturnsTrue)
{ EXPECT_TRUE(fgm::Quaternion<TypeParam>::vecEq(this->_eqVecQuatA, this->_eqVecQuatB)); }


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_VeqEq_QuaternionsWithDifferentVectorPartReturnsFalse)
{ EXPECT_FALSE(fgm::Quaternion<TypeParam>::vecEq(this->_eqVecQuatA, this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, StaticWrapper_VeqEq_NanQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Quaternion<double> quatB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };

    EXPECT_FALSE(fgm::Quaternion<float>::vecEq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_VeqEq_IdenticalInfiniteQuaternionsReturnsTrue)
{
    const fgm::Quaternion quatA = { INF, -INF, INF, 4.0f };
    const fgm::Quaternion quatB = { INF, -INF, INF, 8.0f };

    EXPECT_TRUE(fgm::Quaternion<float>::vecEq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_VeqEq_DifferentInfiniteQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA = { INF, INF, INF, -INF };
    const fgm::Quaternion quatB = { INF, -INF, INF, -INF };

    EXPECT_FALSE(fgm::Quaternion<float>::vecEq(quatA, quatB));
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_VeqEq_MixedType_QuaternionsWithIdenticalVectorPartReturnsTrue)
{
    const fgm::Quaternion quatA(1, 2, 3, 4);
    const fgm::Quaternion quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(fgm::Quaternion<int>::vecEq(quatA, quatB));
}

// /** @brief Verify that the equality operator returns true for identical vectors. */
// TYPED_TEST(QuaternionEqualityTests, EqualityOperator_IdenticalQuaternionsReturnsTrue)
// {
//     const bool equality = this->_eqQuatA == this->_eqQuatB;
//
//     EXPECT_TRUE(equality);
// }
//
//

//
//
// /** @brief Verify that @ref fgm::Quaternion::allEq works for different vector types with different components. */
// TYPED_TEST(QuaternionEqualityTests, MixedType_Equality_DifferentQuaternionsReturnsFalse)
// {
//     const fgm::Quaternion quatA(5, 6, 7, 8);
//     const fgm::Quaternion quatB(1.0, 2.0, 3.0, 4.0);
//
//     const bool equality = quatA.allEq(quatB);
//
//     EXPECT_FALSE(equality);
// }
//
//
// /** @brief Verify that the equality operator returns false if any component differ. */
// TYPED_TEST(QuaternionEqualityTests, EqualityOperator_DifferentQuaternionsReturnsFalse)
// {
//     const bool equality = this->_eqQuatA == this->_dissimilarQuat;
//
//     EXPECT_FALSE(equality);
// }
//
//
// /** @brief Verify that the equality operator works for bool vector with identical components. */
// TEST(QuaternionEqualityTests, EqualityOperator_IdenticalBooleanQuaternionsReturnsTrue)
// {
//     const fgm::Quaternion quatA(true, false, true, false);
//     const fgm::Quaternion quatB(true, false, true, false);
//
//     const bool equality = quatA == quatB;
//
//     EXPECT_TRUE(equality);
// }
//
//

// }
//
// /** @} */
//
//
//
// /**
//  * @addtogroup T_FGM_Quaternion_Inequality
//  * @{
//  */
//
// /**************************************
//  *                                    *
//  *          INEQUALITY TESTS          *
//  *                                    *
//  **************************************/
//
//
// /** @brief Verify that @ref fgm::Quaternion::anyNeq returns false for identical vectors. */
// TYPED_TEST(QuaternionEqualityTests, Inequality_IdenticalQuaternionsReturnsFalse)
// {
//     const bool equality = this->_eqQuatA.anyNeq(this->_eqQuatB);
//
//     EXPECT_FALSE(equality);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion::anyNeq returns true if any component differ. */
// TYPED_TEST(QuaternionEqualityTests, Inequality_DifferentQuaternionsReturnsTrue)
// {
//     const bool equality = this->_eqQuatA.anyNeq(this->_dissimilarQuat);
//
//     EXPECT_TRUE(equality);
// }
//
//
// /** @brief Verify that the static variant of @ref fgm::Quaternion::anyNeq for identical vectors. */
// TYPED_TEST(QuaternionEqualityTests, StaticWrapper_Inequality_IdenticalQuaternionsReturnsFalse)
// {
//     const bool equality = fgm::Quaternion<TypeParam>::anyNeq(this->_eqQuatA, this->_eqQuatB);
//
//     EXPECT_FALSE(equality);
// }
//
//
// /** @brief Verify that the static variant of @ref fgm::Quaternion::anyNeq for different vectors. */
// TYPED_TEST(QuaternionEqualityTests, StaticWrapper_Inequality_DifferentQuaternionsReturnsTrue)
// {
//     const bool equality = fgm::Quaternion<TypeParam>::anyNeq(this->_eqQuatA, this->_dissimilarQuat);
//
//     EXPECT_TRUE(equality);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion::anyNeq follows IEEE 754 for NaN comparisons. */
// TEST(QuaternionEqualityTests, NanInequalityReturnsTrue)
// {
//     const fgm::Quaternion quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
//     const fgm::Quaternion<double> quatB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };
//
//     const bool equality = quatA.anyNeq(quatB);
//
//     EXPECT_TRUE(equality);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion::anyNeq follows IEEE 754 for INFINITY comparisons. */
// TEST(QuaternionEqualityTests, InfinityInequality_IdenticalQuaternionsReturnsFalse)
// {
//     const fgm::Quaternion quatA = { INF, -INF, INF, -INF };
//     const fgm::Quaternion quatB = { INF, -INF, INF, -INF };
//
//     const bool equality = quatA.anyNeq(quatB);
//
//     EXPECT_FALSE(equality);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion::anyNeq follows IEEE 754 for INFINITY comparisons. */
// TEST(QuaternionEqualityTests, InfinityInequality_DifferentQuaternionsReturnsTrue)
// {
//     const fgm::Quaternion quatA = { INF, INF, INF, -INF };
//     const fgm::Quaternion quatB = { INF, -INF, INF, INF };
//
//     const bool equality = quatA.anyNeq(quatB);
//
//     EXPECT_TRUE(equality);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion::anyNeq works for different vector types with identical components. */
// TYPED_TEST(QuaternionEqualityTests, MixedType_Inequality_IdenticalQuaternionsReturnsFalse)
// {
//     const fgm::Quaternion quatA(1, 2, 3, 4);
//     const fgm::Quaternion quatB(1.0, 2.0, 3.0, 4.0);
//
//     const bool equality = quatA.anyNeq(quatB);
//
//     EXPECT_FALSE(equality);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion::anyNeq works for different vector types with different components. */
// TYPED_TEST(QuaternionEqualityTests, MixedType_Inequality_DifferentQuaternionsReturnsTrue)
// {
//     const fgm::Quaternion quatA(5, 6, 7, 8);
//     const fgm::Quaternion quatB(1.0, 2.0, 3.0, 4.0);
//
//     const bool equality = quatA.anyNeq(quatB);
//
//     EXPECT_TRUE(equality);
// }
//
//
// /** @brief Verify that the operator returns false for identical vectors. */
// TYPED_TEST(QuaternionEqualityTests, InEqualityOperator_IdenticalQuaternionsReturnsFalse)
// {
//     const bool equality = this->_eqQuatA != this->_eqQuatB;
//
//     EXPECT_FALSE(equality);
// }
//
//
// /** @brief Verify that the inequality operator returns true for different vectors. */
// TYPED_TEST(QuaternionEqualityTests, InEqualityOperator_DifferentQuaternionsReturnsTrue)
// {
//     const bool equality = this->_eqQuatA != this->_dissimilarQuat;
//
//     EXPECT_TRUE(equality);
// }
//
//
// /** @brief Verify that the inequality operator works for @ref fgm::Quaternion<bool> with identical components. */
// TEST(QuaternionEqualityTests, InequalityOperator_IdenticalBooleanQuaternionsReturnsFalse)
// {
//     const fgm::Quaternion quatA(true, false, true, false);
//     const fgm::Quaternion quatB(true, false, true, false);
//
//     const bool equality = quatA != quatB;
//
//     EXPECT_FALSE(equality);
// }
//
//
// /** @brief Verify that the inequality operator works for @ref fgm::Quaternion<bool> with different components. */
// TEST(QuaternionEqualityTests, InequalityOperator_DifferentBooleanQuaternionsReturnsTrue)
// {
//     const fgm::Quaternion quatA(true, false, true, false);
//     const fgm::Quaternion quatB(true, true, true, false);
//
//     const bool equality = quatA != quatB;
//
//     EXPECT_TRUE(equality);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion::neq returns @ref fgm::Quaternion<bool> mask for identical vectors. */
// TYPED_TEST(QuaternionEqualityTests, InequalityReturnsCorrectBooleanMask)
// {
//     const fgm::Quaternion<bool> mask = this->_eqQuatA.neq(this->_dissimilarQuat);
//
//     EXPECT_QUAT_EQ(this->_inequalityMask, mask);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion::neq returns @ref fgm::Quaternion<bool> mask for different vectors. */
// TEST(QuaternionEqualityTests, MixedType_InequalityReturnsCorrectBooleanMask)
// {
//     const fgm::Quaternion quatA         = { 1, 2, 3, 4 };
//     const fgm::Quaternion quatB         = { 1.0, 4.0, 0.0, 4.0 };
//     const fgm::Quaternion expectedMask = { false, true, true, false };
//
//     const fgm::Quaternion<bool> mask = quatA.neq(quatB);
//
//     EXPECT_QUAT_EQ(expectedMask, mask);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion::neq follows IEEE 754 for NaN comparisons. */
// TEST(QuaternionEqualityTests, NanInequalityReturnsTrueBooleanMask)
// {
//     const fgm::Quaternion quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
//     const fgm::Quaternion<double> quatB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };
//     const fgm::Quaternion expectedMask = { true, true, true, true };
//
//     const fgm::Quaternion mask = quatA.neq(quatB);
//
//     EXPECT_QUAT_EQ(expectedMask, mask);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion::neq follows IEEE 754 for INFINITY comparisons. */
// TEST(QuaternionEqualityTests, InfinityInequalityReturnsCorrectBooleanMask)
// {
//     const fgm::Quaternion quatA         = { INF, -INF, INF, -INF };
//     const fgm::Quaternion quatB         = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11, 10e11 };
//     const fgm::Quaternion expectedMask = { false, true, true, true };
//
//     const fgm::Quaternion mask = quatA.neq(quatB);
//
//     EXPECT_QUAT_EQ(expectedMask, mask);
// }
//
//
// /**
//  * @brief Verify that the static variant of @ref fgm::Quaternion::neq returns @ref fgm::Quaternion<bool> mask
//  *       for different vectors.
//  */
// TYPED_TEST(QuaternionEqualityTests, StaticWrapper_InequalityReturnsCorrectBooleanMask)
// {
//     const fgm::Quaternion<bool> mask = fgm::Quaternion<TypeParam>::neq(this->_eqQuatA, this->_dissimilarQuat);
//
//     EXPECT_QUAT_EQ(this->_inequalityMask, mask);
// }

/** @} */
