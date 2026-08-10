/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vec2 equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"

#include <fgm/common/Constants.h>




/**
 * @addtogroup T_FGM_Vec2_Equality
 * @{
 */

namespace
{

    constexpr auto NAN_F = fgm::constants::NaN;
    constexpr auto INF   = fgm::constants::INFINITY_F;


    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec2 equality.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */

    template <typename T>
    class Vec2EqualityTests: public testing::Test
    {
    protected:
        fgm::Vec2<T> _eqVecA;
        fgm::Vec2<T> _eqVecB;
        fgm::Vec2<T> _dissimilarVec;
        fgm::Vec2<bool> _equalityMask;
        fgm::Vec2<bool> _inequalityMask;


        void SetUp() override
        {
            _eqVecA         = { T(1.1234568789), T(2.123458319) };
            _eqVecB         = { T(1.1234568789), T(2.123458319) };
            _dissimilarVec  = { T(7.1234568789), T(2.123458319) };
            _equalityMask   = { false, true };
            _inequalityMask = { true, false };
        }
    };
    TYPED_TEST_SUITE(Vec2EqualityTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Vec2 vec1(1, 2);
        constexpr fgm::Vec2 vec2(3, 2);
        constexpr fgm::Vec2 vec3(1, 2);


        /// @test Verify that @ref Vec2 allEq returns correct boolean for equal vectors.
        constexpr auto ALLEQ_EQ_VECS = vec1.allEq(vec2);
        static_assert(ALLEQ_EQ_VECS == false);

        /// @test Verify that @ref Vec2 allEq returns correct boolean for unequal vectors.
        constexpr auto ALL_EQ_UNEQUAL_VECS = vec1.allEq(vec3);
        static_assert(ALL_EQ_UNEQUAL_VECS == true);

        /// @test Verify that @ref Vec2 allEq (static wrapper) returns correct boolean for equal vectors.
        constexpr auto ALLEQ_EQ_VECS_STATIC = fgm::Vec2<int>::allEq(vec1, vec2);
        static_assert(ALLEQ_EQ_VECS_STATIC == false);

        /// @test Verify that @ref Vec2 allEq (static wrapper) returns correct boolean for unequal vectors.
        constexpr auto ALLEQ_UNEQUAL_VECS_STATIC = fgm::Vec2<int>::allEq(vec1, vec3);
        static_assert(ALLEQ_UNEQUAL_VECS_STATIC == true);

        /// @test Verify that @ref Vec2 equals operator returns correct boolean for equal vectors.
        constexpr auto DBLEQ_OP_EQUAL_VECS = vec1 == vec2;
        static_assert(DBLEQ_OP_EQUAL_VECS == false);

        /// @test Verify that @ref Vec2 equals operator returns correct boolean for unequal vectors.
        constexpr auto DBLEQ_OP_UNEQUAL_VECS = vec1 == vec3;
        static_assert(DBLEQ_OP_UNEQUAL_VECS == true);


        /// @test Verify that @ref Vec2 equality mask returns valid boolean mask
        constexpr auto EQ_VEC_MASK = vec1.eq(vec2);
        static_assert(EQ_VEC_MASK.x() == false);
        static_assert(EQ_VEC_MASK.y() == true);


        /// @test Verify that @ref Vec2 anyNeq returns correct boolean for equal vectors.
        constexpr auto ANYNEQ_EQ_VECS = vec1.anyNeq(vec2);
        static_assert(ANYNEQ_EQ_VECS == true);

        /// @test Verify that @ref Vec2 anyNeq returns correct boolean for unequal vectors.
        constexpr auto ANYNEQ_UNEQUAL_VECS = vec1.anyNeq(vec3);
        static_assert(ANYNEQ_UNEQUAL_VECS == false);

        /// @test Verify that @ref Vec2 anyNeq(static wrapper) returns correct boolean for equal vectors.
        constexpr auto ANYNEQ_EQ_VECS_STATIC = fgm::Vec2<int>::anyNeq(vec1, vec2);
        static_assert(ANYNEQ_EQ_VECS_STATIC == true);

        /// @test Verify that @ref Vec2 anyNeq(static wrapper) returns correct boolean for unequal vectors.
        constexpr auto ANYNEQ_UNEQUAL_VECS_STATIC = fgm::Vec2<int>::anyNeq(vec1, vec3);
        static_assert(ANYNEQ_UNEQUAL_VECS_STATIC == false);

        /// @test Verify that @ref Vec2 not equals operator returns correct boolean for equal vectors.
        constexpr auto ANYNEQ_OP_EQUAL_VECS = vec1 != vec2;
        static_assert(ANYNEQ_OP_EQUAL_VECS == true);

        /// @test Verify that @ref Vec2 not equals operator returns correct boolean for unequal vectors.
        constexpr auto NOT_EQ_OP = vec1 != vec3;
        static_assert(NOT_EQ_OP == false);

        /// @test Verify that @ref Vec2 inequality mask returns valid boolean mask.
        constexpr auto NEQ_MASK_VEC = vec1.neq(vec2);
        static_assert(NEQ_MASK_VEC.x() == true);
        static_assert(NEQ_MASK_VEC.y() == false);

    } // namespace static_tests
} // namespace



/**************************************
 *           EQUALITY TESTS           *
 **************************************/

TYPED_TEST(Vec2EqualityTests, AllEq_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.allEq(this->_eqVecB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Vec2EqualityTests, AllEq_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.allEq(this->_dissimilarVec);
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vec2EqualityTests, StaticWrapper_AllEq_IdenticalVectorsReturnsTrue)
{
    const bool equality = fgm::Vec2<TypeParam>::allEq(this->_eqVecA, this->_eqVecB);

    EXPECT_TRUE(equality);
}


TYPED_TEST(Vec2EqualityTests, StaticWrapper_AllEq_DifferentVectorsReturnsFalse)
{
    const bool equality = fgm::Vec2<TypeParam>::allEq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


TEST(Vec2EqualityTests, AllEq_NanVectorsReturnsFalse)
{
    const fgm::Vec2 vecA = { NAN_F, NAN_F };
    const fgm::Vec2 vecB = { 1.0, -5.88874789 };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality) << "NaN vector shouldn't equal anything!";
}


TEST(Vec2EqualityTests, AllEq_IdenticalInfinitVectors_VectorsReturnsTrue)
{
    const fgm::Vec2 vecA = { INF, -INF };
    const fgm::Vec2 vecB = { INF, -INF };

    const bool equality = vecA.allEq(vecB);
    EXPECT_TRUE(equality);
}


TEST(Vec2EqualityTests, AllEq_DifferentInfinitVectors_VectorsReturnsFalse)
{
    const fgm::Vec2 vecA = { INF, INF };
    const fgm::Vec2 vecB = { INF, -INF };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vec2EqualityTests, DoubleEqualsOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA == this->_eqVecB;

    EXPECT_TRUE(equality);
}


TYPED_TEST(Vec2EqualityTests, MixedType_AllEq_IdenticalVectorsReturnsTrue)
{
    const fgm::Vec2 vecA(1, 2);
    const fgm::Vec2 vecB(1.0, 2.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


TYPED_TEST(Vec2EqualityTests, MixedType_AllEq_DifferentVectorsReturnsFalse)
{
    const fgm::Vec2 vecA(5, 6);
    const fgm::Vec2 vecB(1.0, 2.0);

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vec2EqualityTests, DoubleEqualsOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA == this->_dissimilarVec;
    EXPECT_FALSE(equality);
}


TEST(Vec2EqualityTests, DoubleEqualsOperator_IdenticalBooleanVectorsReturnsTrue)
{
    const fgm::Vec2 vecA(true, false);
    const fgm::Vec2 vecB(true, false);

    const bool equality = vecA == vecB;
    EXPECT_TRUE(equality);
}


TEST(Vec2EqualityTests, DoubleEqualsOperator_DifferentBooleanVectorsReturnsFalse)
{
    const fgm::Vec2 vecA(true, false);
    const fgm::Vec2 vecB(true, true);

    const bool equality = vecA == vecB;
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vec2EqualityTests, Eq_ReturnsCorrectBooleanMask)
{
    const fgm::Vec2<bool> mask = this->_eqVecA.eq(this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_equalityMask, mask);
}


TEST(Vec2EqualityTests, Eq_MixedType_ReturnsCorrectBooleanMask)
{
    const fgm::Vec2 vecA         = { 1, 2 };
    const fgm::Vec2 vecB         = { 1.0, 4.0 };
    const fgm::Vec2 expectedMask = { true, false };

    const fgm::Vec2<bool> mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


TEST(Vec2EqualityTests, Eq_NanVectorsReturnsFalseBooleanMask)
{
    const fgm::Vec2 vecA         = { NAN_F, NAN_F };
    const fgm::Vec2 vecB         = { 1.0, -5.88874789 };
    const fgm::Vec2 expectedMask = { false, false };

    const fgm::Vec2 mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


TEST(Vec2EqualityTests, Eq_InfiniteVectorsReturnsCorrectBooleanMask)
{
    const fgm::Vec2 vecA         = { INF, -INF };
    const fgm::Vec2<double> vecB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D };
    const fgm::Vec2 expectedMask = { true, false };

    const fgm::Vec2 mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


TYPED_TEST(Vec2EqualityTests, StaticWrapper_Eq_ReturnsCorrectBooleanMask)
{
    const fgm::Vec2<bool> mask = fgm::Vec2<TypeParam>::eq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_equalityMask, mask);
}



/**************************************
 *          INEQUALITY TESTS          *
 **************************************/

TYPED_TEST(Vec2EqualityTests, AnyNeq_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.anyNeq(this->_eqVecB);
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vec2EqualityTests, AnyNeq_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.anyNeq(this->_dissimilarVec);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Vec2EqualityTests, StaticWrapper_AnyNeq_IdenticalVectorsReturnsFalse)
{
    const bool equality = fgm::Vec2<TypeParam>::anyNeq(this->_eqVecA, this->_eqVecB);
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vec2EqualityTests, StaticWrapper_AnyNeq_DifferentVectorsReturnsTrue)
{
    const bool equality = fgm::Vec2<TypeParam>::anyNeq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_TRUE(equality);
}


TEST(Vec2EqualityTests, AnyNeq_NaNVectorsReturnsTrue)
{
    const fgm::Vec2 vecA = { NAN_F, NAN_F };
    const fgm::Vec2 vecB = { 1.0, -5.88874789 };

    const bool equality = vecA.anyNeq(vecB);
    EXPECT_TRUE(equality);
}


TEST(Vec2EqualityTests, AnyNeq_IdenticalInfinitVectors_ReturnsFalse)
{
    const fgm::Vec2 vecA = { INF, -INF };
    const fgm::Vec2 vecB = { INF, -INF };

    const bool equality = vecA.anyNeq(vecB);
    EXPECT_FALSE(equality);
}


TEST(Vec2EqualityTests, AnyNeq_DifferentInfinitVectors_ReturnsTrue)
{
    const fgm::Vec2 vecA = { INF, INF };
    const fgm::Vec2 vecB = { INF, -INF };

    const bool equality = vecA.anyNeq(vecB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Vec2EqualityTests, AnyNeq_MixedType_IdenticalVectorsReturnsFalse)
{
    const fgm::Vec2 vecA(1, 2);
    const fgm::Vec2 vecB(1.0, 2.0);

    const bool equality = vecA.anyNeq(vecB);
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vec2EqualityTests, AnyNeq_MixedType_DifferentVectorsReturnsTrue)
{
    const fgm::Vec2 vecA(5, 6);
    const fgm::Vec2 vecB(1.0, 2.0);

    const bool equality = vecA.anyNeq(vecB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Vec2EqualityTests, NotEqualsOperator_IdenticalVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA != this->_eqVecB;
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vec2EqualityTests, NotEqualsOperator_DifferentVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA != this->_dissimilarVec;
    EXPECT_TRUE(equality);
}


TEST(Vec2EqualityTests, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    const fgm::Vec2 vecA(true, false);
    const fgm::Vec2 vecB(true, false);

    const bool equality = vecA != vecB;
    EXPECT_FALSE(equality);
}


TEST(Vec2EqualityTests, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    const fgm::Vec2 vecA(true, false);
    const fgm::Vec2 vecB(true, true);

    const bool equality = vecA != vecB;
    EXPECT_TRUE(equality);
}


TYPED_TEST(Vec2EqualityTests, Neq_ReturnsCorrectBooleanMask)
{
    const fgm::Vec2<bool> mask = this->_eqVecA.neq(this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}


TEST(Vec2EqualityTests, Neq_MixedType_ReturnsCorrectBooleanMask)
{
    const fgm::Vec2 vecA         = { 1, 2 };
    const fgm::Vec2 vecB         = { 1.0, 4.0 };
    const fgm::Vec2 expectedMask = { false, true };

    const fgm::Vec2<bool> mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


TEST(Vec2EqualityTests, Neq_NaNVectorsReturnsTrueBooleanMask)
{
    const fgm::Vec2 vecA         = { NAN_F, NAN_F };
    const fgm::Vec2 vecB         = { 1.0, -5.88874789 };
    const fgm::Vec2 expectedMask = { true, true };

    const fgm::Vec2 mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


TEST(Vec2EqualityTests, Neq_InfinityVectorsReturnsCorrectBooleanMask)
{
    const fgm::Vec2 vecA         = { INF, -INF };
    const fgm::Vec2 vecB         = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D };
    const fgm::Vec2 expectedMask = { false, true };

    const fgm::Vec2 mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}



TYPED_TEST(Vec2EqualityTests, StaticWrapper_Neq_ReturnsCorrectBooleanMask)
{
    const fgm::Vec2<bool> mask = fgm::Vec2<TypeParam>::neq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}

/** @} */
