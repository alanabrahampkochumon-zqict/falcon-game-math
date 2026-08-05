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


        /// @test Verify that Quaternion operator== returns the correct boolean at compile time,
        ///       given two quaternions with different components.
        static_assert((QUAT_A == QUAT_B) == false);

        /// @test Verify that Quaternion operator== returns the correct boolean at compile time,
        ///       given two quaternions with same components.
        static_assert((QUAT_A == QUAT_C) == true);



        /// @test Verify that Quaternion anyNeq returns the correct boolean at compile time,
        ///       given two quaternions with different components.
        static_assert(QUAT_A.anyNeq(QUAT_B) == true);

        /// @test Verify that Quaternion anyNeq returns the correct boolean at compile time,
        ///       given two quaternions with same components.
        static_assert(QUAT_A.anyNeq(QUAT_C) == false);


        /// @test Verify that Quaternion anyNeq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with different components.
        static_assert(fgm::Quaternion<int>::anyNeq(QUAT_A, QUAT_B) == true);

        /// @test Verify that Quaternion anyNeq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with same components.
        static_assert(fgm::Quaternion<int>::anyNeq(QUAT_A, QUAT_C) == false);


        /// @test Verify that Quaternion neq returns the correct boolean mask at compile time.
        constexpr auto NEQ_QUAT_MASK = QUAT_A.neq(QUAT_B);
        static_assert(NEQ_QUAT_MASK.x() == true);
        static_assert(NEQ_QUAT_MASK.y() == false);
        static_assert(NEQ_QUAT_MASK.z() == true);
        static_assert(NEQ_QUAT_MASK.w() == true);

        /// @test Verify that Quaternion neq (static wrapper) returns the correct boolean mask at compile time.
        constexpr auto NEQ_QUAT_MASK_STATIC = fgm::Quaternion<int>::neq(QUAT_A, QUAT_B);
        static_assert(NEQ_QUAT_MASK_STATIC.x() == true);
        static_assert(NEQ_QUAT_MASK_STATIC.y() == false);
        static_assert(NEQ_QUAT_MASK_STATIC.z() == true);
        static_assert(NEQ_QUAT_MASK_STATIC.w() == true);


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



/**************************************
 *         EQUALITY OPERATOR          *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, EqualityOperator_IdenticalQuaternionsReturnsTrue)
{ EXPECT_TRUE(this->_eqQuatA == this->_eqQuatB); }


TYPED_TEST(QuaternionEqualityTests, EqualityOperator_DifferentQuaternionsReturnsFalse)
{ EXPECT_FALSE(this->_eqQuatA == this->_dissimilarQuat); }


TEST(QuaternionEqualityTests, EqualityOperator_NanQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Quaternion<double> quatB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };

    EXPECT_FALSE(quatA == quatB);
}


TEST(QuaternionEqualityTests, EqualityOperator_IdenticalInfiniteQuaternionsReturnsTrue)
{
    const fgm::Quaternion quatA = { INF, -INF, INF, -INF };
    const fgm::Quaternion quatB = { INF, -INF, INF, -INF };

    EXPECT_TRUE(quatA == quatB);
}


TEST(QuaternionEqualityTests, EqualityOperator_DifferentInfiniteQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA = { INF, INF, INF, -INF };
    const fgm::Quaternion quatB = { INF, -INF, INF, INF };

    EXPECT_FALSE(quatA == quatB);
}


TYPED_TEST(QuaternionEqualityTests, EqualityOperator_MixedType_IdenticalQuaternionsReturnsTrue)
{
    const fgm::Quaternion quatA(1, 2, 3, 4);
    const fgm::Quaternion quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(quatA == quatB);
}




/**************************************
 *                                    *
 *          INEQUALITY TESTS          *
 *                                    *
 **************************************/

/**************************************
 *             ANY NEQ                *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, AnyNeq_IdenticalQuaternionsReturnsFalse)
{ EXPECT_FALSE(this->_eqQuatA.anyNeq(this->_eqQuatB)); }


TYPED_TEST(QuaternionEqualityTests, AnyNeq__DifferentQuaternionsReturnsTrue)
{ EXPECT_TRUE(this->_eqQuatA.anyNeq(this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, AnyNeq_NanQuaternionsReturnsTrue)
{
    const fgm::Quaternion quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Quaternion<double> quatB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };

    EXPECT_TRUE(quatA.anyNeq(quatB));
}


TEST(QuaternionEqualityTests, AnyNeq_IdenticalInfiniteQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA = { INF, -INF, INF, -INF };
    const fgm::Quaternion quatB = { INF, -INF, INF, -INF };

    EXPECT_FALSE(quatA.anyNeq(quatB));
}


TEST(QuaternionEqualityTests, AnyNeq_DifferentInfiniteQuaternionsReturnsTrue)
{
    const fgm::Quaternion quatA = { INF, INF, INF, -INF };
    const fgm::Quaternion quatB = { INF, -INF, INF, INF };

    EXPECT_TRUE(quatA.anyNeq(quatB));
}


TYPED_TEST(QuaternionEqualityTests, AnyNeq_MixedType_IdenticalQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA(1, 2, 3, 4);
    const fgm::Quaternion quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_FALSE(quatA.anyNeq(quatB));
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_AnyNeq_IdenticalQuaternionsReturnsFalse)
{ EXPECT_FALSE(fgm::Quaternion<TypeParam>::anyNeq(this->_eqQuatA, this->_eqQuatB)); }


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_AnyNeq_DifferentQuaternionsReturnsTrue)
{ EXPECT_TRUE(fgm::Quaternion<TypeParam>::anyNeq(this->_eqQuatA, this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, StaticWrapper_AnyNeq_NanQuaternionsReturnsTrue)
{
    const fgm::Quaternion quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Quaternion<double> quatB = { 1.0, -5.88874789, fgm::constants::INFINITY_D, NAN_F };

    EXPECT_TRUE(fgm::Quaternion<float>::anyNeq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_AnyNeq_IdenticalInfiniteQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA = { INF, -INF, INF, -INF };
    const fgm::Quaternion quatB = { INF, -INF, INF, -INF };

    EXPECT_FALSE(fgm::Quaternion<float>::anyNeq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_AnyNeq_DifferentInfiniteQuaternionsReturnsTrue)
{
    const fgm::Quaternion quatA = { INF, INF, INF, -INF };
    const fgm::Quaternion quatB = { INF, -INF, INF, INF };

    EXPECT_TRUE(fgm::Quaternion<float>::anyNeq(quatA, quatB));
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_AnyNeq_MixedType_IdenticalQuaternionsReturnsFalse)
{
    const fgm::Quaternion quatA(1, 2, 3, 4);
    const fgm::Quaternion quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_FALSE(fgm::Quaternion<int>::anyNeq(quatA, quatB));
}


/**************************************
 *         INEQUALITY MASK            *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, Neq_ReturnsCorrectBooleanMask)
{
    const fgm::Quaternion<bool> mask = this->_eqQuatA.neq(this->_dissimilarQuat);
    EXPECT_QUAT_EQ(this->_inequalityMask, mask);
}


TEST(QuaternionEqualityTests, Neq_MixedType_ReturnsCorrectBooleanMask)
{
    const fgm::Quaternion quatA        = { 1, 2, 3, 4 };
    const fgm::Quaternion quatB        = { 1.0, 4.0, 0.0, 4.0 };
    const fgm::Quaternion expectedMask = { false, true, true, false };

    const fgm::Quaternion<bool> mask = quatA.neq(quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, Neq_NaNQuaternionsReturnsFalseBooleanMask)
{
    const fgm::Quaternion quatA        = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Quaternion quatB        = { 1.0, -5.88874789, fgm::constants::INFINITY_D, fgm::constants::NaN_D };
    const fgm::Quaternion expectedMask = { true, true, true, true };

    const fgm::Quaternion mask = quatA.neq(quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, Neq_InfiniteQuaternionsReturnsCorrectBooleanMask)
{
    const fgm::Quaternion quatA         = { INF, -INF, INF, -INF };
    const fgm::Quaternion<double> quatB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11, 10e11 };
    const fgm::Quaternion expectedMask  = { false, true, true, true };

    const fgm::Quaternion mask = quatA.neq(quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_Neq_ReturnsCorrectBooleanMask)
{
    const fgm::Quaternion<bool> mask = fgm::Quaternion<TypeParam>::neq(this->_eqQuatA, this->_dissimilarQuat);
    EXPECT_QUAT_EQ(this->_inequalityMask, mask);
}


TEST(QuaternionEqualityTests, StaticWrapper_Neq_MixedType_ReturnsCorrectBooleanMask)
{
    const fgm::Quaternion quatA        = { 1, 2, 3, 4 };
    const fgm::Quaternion quatB        = { 1.0, 4.0, 0.0, 4.0 };
    const fgm::Quaternion expectedMask = { false, true, true, false };

    const fgm::Quaternion<bool> mask = fgm::Quaternion<int>::neq(quatA, quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, StaticWrapper_Neq_NaNQuaternionsReturnsFalseBooleanMask)
{
    const fgm::Quaternion quatA        = { NAN_F, NAN_F, NAN_F, NAN_F };
    const fgm::Quaternion quatB        = { 1.0, -5.88874789, fgm::constants::INFINITY_D, fgm::constants::NaN_D };
    const fgm::Quaternion expectedMask = { true, true, true, true };

    const fgm::Quaternion<bool> mask = fgm::Quaternion<float>::neq(quatA, quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, StaticWrapper_Neq_InfiniteQuaternionsReturnsCorrectBooleanMask)
{
    const fgm::Quaternion quatA         = { INF, -INF, INF, -INF };
    const fgm::Quaternion<double> quatB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D, 10e11, 10e11 };
    const fgm::Quaternion expectedMask  = { false, true, true, true };

    const fgm::Quaternion<bool> mask = fgm::Quaternion<float>::neq(quatA, quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


/** @} */
