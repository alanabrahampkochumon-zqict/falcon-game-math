/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verifies @ref fgm::Matrix2D equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, allNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"

#include <common/Constants.h>


constexpr auto NAN_F = fgm::constants::NaN;
constexpr auto INF = fgm::constants::INFINITY_F;



template <typename T>
class Matrix2DEquality: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _eqMatA;
    fgm::Matrix2D<T> _eqMatB;
    fgm::Matrix2D<T> _dissimilarMat;


    void SetUp() override
    {
        _eqMatA = { { T(1.1234568789), T(2.123458319) }, { T(3.1234568789), T(4.123458319) } };
        _eqMatB = { { T(1.1234568789), T(2.123458319) }, { T(3.1234568789), T(4.123458319) } };
        _dissimilarMat = { { T(1.1234568789), T(4.5238852912) }, { T(3.1234568789), T(6.123458319) } };
    }
};

/** @brief Test fixture for @ref fgm::Matrix2D equality and inequality checks, parameterized by @ref
 * SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix2DEquality, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Equality
 * @{
 */

/**************************************
 *                                    *
 *           EQUALITY TESTS           *
 *                                    *
 **************************************/

/** @test Verify that @ref fgm::Matrix2D::allEq returns true for identical vectors. */
TYPED_TEST(Matrix2DEquality, Equality_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA.allEq(this->_eqMatB);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Matrix2D::allEq returns false if any component differ. */
TYPED_TEST(Matrix2DEquality, Equality_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA.allEq(this->_dissimilarMat);

    EXPECT_FALSE(equality);
}


/** @test Verify that the static variant of @ref fgm::Matrix2D::allEq for identical vectors. */
TYPED_TEST(Matrix2DEquality, StaticWrapper_Equality_IdenticalMatricesReturnTrue)
{
    const bool equality = fgm::Matrix2D<TypeParam>::allEq(this->_eqMatA, this->_eqMatB);

    EXPECT_TRUE(equality);
}


/** @test Verify that the static variant of @ref fgm::Matrix2D::allEq for different vectors. */
TYPED_TEST(Matrix2DEquality, StaticWrapper_Equality_DifferentMatricesReturnFalse)
{
    const bool equality = fgm::Matrix2D<TypeParam>::allEq(this->_eqMatA, this->_dissimilarMat);

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Matrix2D::allEq follows IEEE 754 for NaN comparisons. */
TEST(Matrix2DEquality, NanEqualityReturnsFalse)
{
    constexpr fgm::Matrix2D matA(NAN_F, NAN_F, NAN_F, NAN_F);
    constexpr fgm::Matrix2D matB(1.0f, -5.88874789f, 2.0f, 0.888749f);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}


/** @test Verify that @ref fgm::Matrix2D::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Matrix2DEquality, InfinityEquality_IdenticalMatricesReturnTrue)
{
    constexpr fgm::Matrix2D matA(INF, -INF, INF, -INF);
    constexpr fgm::Matrix2D matB(INF, -INF, INF, -INF);

    const bool equality = matA.allEq(matB);

    EXPECT_TRUE(equality);
}


/** @test Verify that @ref fgm::Matrix2D::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Matrix2DEquality, InfinityEquality_DifferentMatricesReturnFalse)
{
    constexpr fgm::Matrix2D matA(INF, -INF, INF, -INF);
    constexpr fgm::Matrix2D matB(-INF, -INF, INF, INF);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}

/** @test Verify that @ref fgm::Matrix2D::allEq works for different vector types with identical components. */
 TYPED_TEST(Matrix2DEquality, MixedType_Equality_IdenticalMatricesReturnTrue)
{
     constexpr fgm::Matrix2D matA(1, 2);
     constexpr fgm::Matrix2D matB(1.0, 2.0);

     constexpr bool equality = matA.allEq(matB);

     EXPECT_TRUE(equality);
 }


/** @test Verify that @ref fgm::Matrix2D::allEq works for different vector types with different components. */
 TYPED_TEST(Matrix2DEquality, MixedType_Equality_DifferentMatricesReturnFalse)
 {
     constexpr fgm::Matrix2D matA(5, 6);
     constexpr fgm::Matrix2D matB(1.0, 2.0);

     const bool equality = matA.allEq(matB);

     EXPECT_FALSE(equality);
 }



///** @test Verify that the equality operator returns true for identical vectors. */
// TYPED_TEST(Matrix2DEquality, EqualityOperator_IdenticalVectorsReturnsTrue)
//{
//     const bool equality = this->_eqMatA == this->_eqMatB;
//
//     EXPECT_TRUE(equality);
// }
//
//

///** @test Verify that the equality operator returns false if any component differ. */
// TYPED_TEST(Matrix2DEquality, EqualityOperator_DifferentVectorsReturnsFalse)
//{
//     const bool equality = this->_eqMatA == this->_dissimilarMat;
//
//     EXPECT_FALSE(equality);
// }
//
//
///** @test Verify that the equality operator works for bool vector with identical components. */
// TEST(Matrix2DEquality, EqualityOperator_IdenticalBooleanVectorsReturnsTrue)
//{
//     constexpr fgm::Matrix2D matA(true, false);
//     constexpr fgm::Matrix2D matB(true, false);
//
//     constexpr bool equality = matA == matB;
//
//     EXPECT_TRUE(equality);
// }
//
//
///** @test Verify that the equality operator works for bool vector with different components. */
// TEST(Matrix2DEquality, EqualityOperator_DifferentBooleanVectorsReturnsFalse)
//{
//     constexpr fgm::Matrix2D matA(true, false);
//     constexpr fgm::Matrix2D matB(true, true);
//
//     constexpr bool equality = matA == matB;
//
//     EXPECT_FALSE(equality);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::eq returns @ref fgm::Matrix2D<bool> mask for identical vectors. */
// TYPED_TEST(Matrix2DEquality, EqualityReturnsCorrectBooleanMask)
//{
//     const fgm::Matrix2D<bool> mask = this->_eqMatA.eq(this->_dissimilarMat);
//
//     EXPECT_VEC_EQ(this->_equalityMask, mask);
// }
//
///** @test Verify that @ref fgm::Matrix2D::eq returns @ref fgm::Matrix2D<bool> mask for different vectors. */
// TEST(Matrix2DEquality, MixedType_EqualityReturnsCorrectBooleanMask)
//{
//     constexpr fgm::Matrix2D matA = { 1, 2 };
//     constexpr fgm::Matrix2D matB = { 1.0, 4.0 };
//     constexpr fgm::Matrix2D expectedMask = { true, false };
//
//     const fgm::Matrix2D<bool> mask = matA.eq(matB);
//
//     EXPECT_VEC_EQ(expectedMask, mask);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::eq follows IEEE 754 for NaN comparisons. */
// TEST(Matrix2DEquality, NanEqualityReturnsFalseBooleanMask)
//{
//     constexpr fgm::Matrix2D matA = { NAN_F, NAN_F };
//     constexpr fgm::Matrix2D matB = { 1.0, -5.88874789 };
//     constexpr fgm::Matrix2D expectedMask = { false, false };
//
//     const fgm::Matrix2D mask = matA.eq(matB);
//
//     EXPECT_VEC_EQ(expectedMask, mask);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::eq follows IEEE 754 for INFINITY comparisons. */
// TEST(Matrix2DEquality, InfinityEqualityReturnsCorrectBooleanMask)
//{
//     constexpr fgm::Matrix2D matA = { INF, -INF };
//     constexpr fgm::Matrix2D<double> matB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D };
//     constexpr fgm::Matrix2D expectedMask = { true, false };
//
//     const fgm::Matrix2D mask = matA.eq(matB);
//
//     EXPECT_VEC_EQ(expectedMask, mask);
// }
//
//
///**
// * @test Verify that the static variant of @ref fgm::Matrix2D::eq returns @ref fgm::Matrix2D<bool> mask
// *       for different vectors.
// */
// TYPED_TEST(Matrix2DEquality, StaticWrapper_EqualityReturnsCorrectBooleanMask)
//{
//    const fgm::Matrix2D<bool> mask = fgm::Matrix2D<TypeParam>::eq(this->_eqMatA, this->_dissimilarMat);
//
//    EXPECT_VEC_EQ(this->_equalityMask, mask);
//}
//
///** @} */
//
//
//
///**
// * @addtogroup T_FGM_Mat2x2_Inequality
// * @{
// */
//
///**************************************
// *                                    *
// *          INEQUALITY TESTS          *
// *                                    *
// **************************************/
//
//
///** @test Verify that @ref fgm::Matrix2D::allNeq returns false for identical vectors. */
// TYPED_TEST(Matrix2DEquality, Inequality_IdenticalVectorsReturnsFalse)
//{
//     const bool equality = this->_eqMatA.allNeq(this->_eqMatB);
//
//     EXPECT_FALSE(equality);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::allNeq returns true if any component differ. */
// TYPED_TEST(Matrix2DEquality, Inequality_DifferentVectorsReturnsTrue)
//{
//     const bool equality = this->_eqMatA.allNeq(this->_dissimilarMat);
//
//     EXPECT_TRUE(equality);
// }
//
//
///** @test Verify that the static variant of @ref fgm::Matrix2D::allNeq for identical vectors. */
// TYPED_TEST(Matrix2DEquality, StaticWrapper_Inequality_IdenticalVectorsReturnsFalse)
//{
//     const bool equality = fgm::Matrix2D<TypeParam>::allNeq(this->_eqMatA, this->_eqMatB);
//
//     EXPECT_FALSE(equality);
// }
//
//
///** @test Verify that the static variant of @ref fgm::Matrix2D::allNeq for different vectors. */
// TYPED_TEST(Matrix2DEquality, StaticWrapper_Inequality_DifferentVectorsReturnsTrue)
//{
//     const bool equality = fgm::Matrix2D<TypeParam>::allNeq(this->_eqMatA, this->_dissimilarMat);
//
//     EXPECT_TRUE(equality);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::allNeq follows IEEE 754 for NaN comparisons. */
// TEST(Matrix2DEquality, NanInequalityReturnsTrue)
//{
//     constexpr fgm::Matrix2D matA = { NAN_F, NAN_F };
//     constexpr fgm::Matrix2D matB = { 1.0, -5.88874789 };
//
//     const bool equality = matA.allNeq(matB);
//
//     EXPECT_TRUE(equality);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::allNeq follows IEEE 754 for INFINITY comparisons. */
// TEST(Matrix2DEquality, InfinityInequality_IdenticalVectorsReturnsFalse)
//{
//     constexpr fgm::Matrix2D matA = { INF, -INF };
//     constexpr fgm::Matrix2D matB = { INF, -INF };
//
//     constexpr bool equality = matA.allNeq(matB);
//
//     EXPECT_FALSE(equality);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::allNeq follows IEEE 754 for INFINITY comparisons. */
// TEST(Matrix2DEquality, InfinityInequality_DifferentVectorsReturnsTrue)
//{
//     constexpr fgm::Matrix2D matA = { INF, INF };
//     constexpr fgm::Matrix2D matB = { INF, -INF };
//
//     const bool equality = matA.allNeq(matB);
//
//     EXPECT_TRUE(equality);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::allNeq works for different vector types with identical components. */
// TYPED_TEST(Matrix2DEquality, MixedType_Inequality_IdenticalVectorsReturnsFalse)
//{
//     constexpr fgm::Matrix2D matA(1, 2);
//     constexpr fgm::Matrix2D matB(1.0, 2.0);
//
//     constexpr bool equality = matA.allNeq(matB);
//
//     EXPECT_FALSE(equality);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::allNeq works for different vector types with different components. */
// TYPED_TEST(Matrix2DEquality, MixedType_Inequality_DifferentVectorsReturnsTrue)
//{
//     constexpr fgm::Matrix2D matA(5, 6);
//     constexpr fgm::Matrix2D matB(1.0, 2.0);
//
//     const bool equality = matA.allNeq(matB);
//
//     EXPECT_TRUE(equality);
// }
//
//
///** @test Verify that the operator returns false for identical vectors. */
// TYPED_TEST(Matrix2DEquality, InEqualityOperator_IdenticalVectorsReturnsFalse)
//{
//     const bool equality = this->_eqMatA != this->_eqMatB;
//
//     EXPECT_FALSE(equality);
// }
//
//
///** @test Verify that the inequality operator returns true for different vectors. */
// TYPED_TEST(Matrix2DEquality, InEqualityOperator_DifferentVectorsReturnsTrue)
//{
//     const bool equality = this->_eqMatA != this->_dissimilarMat;
//
//     EXPECT_TRUE(equality);
// }
//
//
///** @test Verify that the inequality operator works for @ref fgm::Matrix2D<bool> with identical components. */
// TEST(Matrix2DEquality, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
//{
//     constexpr fgm::Matrix2D matA(true, false);
//     constexpr fgm::Matrix2D matB(true, false);
//
//     constexpr bool equality = matA != matB;
//
//     EXPECT_FALSE(equality);
// }
//
//
///** @test Verify that the inequality operator works for @ref fgm::Matrix2D<bool> with different components. */
// TEST(Matrix2DEquality, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
//{
//     constexpr fgm::Matrix2D matA(true, false);
//     constexpr fgm::Matrix2D matB(true, true);
//
//     constexpr bool equality = matA != matB;
//
//     EXPECT_TRUE(equality);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::neq returns @ref fgm::Matrix2D<bool> mask for identical vectors. */
// TYPED_TEST(Matrix2DEquality, InequalityReturnsCorrectBooleanMask)
//{
//     const fgm::Matrix2D<bool> mask = this->_eqMatA.neq(this->_dissimilarMat);
//
//     EXPECT_VEC_EQ(this->_inequalityMask, mask);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::neq returns @ref fgm::Matrix2D<bool> mask for different vectors. */
// TEST(Matrix2DEquality, MixedType_InequalityReturnsCorrectBooleanMask)
//{
//     constexpr fgm::Matrix2D matA = { 1, 2 };
//     constexpr fgm::Matrix2D matB = { 1.0, 4.0};
//     constexpr fgm::Matrix2D expectedMask = { false, true };
//
//     const fgm::Matrix2D<bool> mask = matA.neq(matB);
//
//     EXPECT_VEC_EQ(expectedMask, mask);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::neq follows IEEE 754 for NaN comparisons. */
// TEST(Matrix2DEquality, NanInequalityReturnsTrueBooleanMask)
//{
//     constexpr fgm::Matrix2D matA = { NAN_F, NAN_F };
//     constexpr fgm::Matrix2D<double> matB = { 1.0, -5.88874789 };
//     constexpr fgm::Matrix2D expectedMask = { true, true };
//
//     const fgm::Matrix2D mask = matA.neq(matB);
//
//     EXPECT_VEC_EQ(expectedMask, mask);
// }
//
//
///** @test Verify that @ref fgm::Matrix2D::neq follows IEEE 754 for INFINITY comparisons. */
// TEST(Matrix2DEquality, InfinityInequalityReturnsCorrectBooleanMask)
//{
//     constexpr fgm::Matrix2D matA = { INF, -INF };
//     constexpr fgm::Matrix2D matB = { fgm::constants::INFINITY_D, fgm::constants::INFINITY_D };
//     constexpr fgm::Matrix2D expectedMask = { false, true };
//
//     const fgm::Matrix2D mask = matA.neq(matB);
//
//     EXPECT_VEC_EQ(expectedMask, mask);
// }
//
//
///**
// * @test Verify that the static variant of @ref fgm::Matrix2D::neq returns @ref fgm::Matrix2D<bool> mask
// *       for different vectors.
// */
// TYPED_TEST(Matrix2DEquality, StaticWrapper_InequalityReturnsCorrectBooleanMask)
//{
//    const fgm::Matrix2D<bool> mask = fgm::Matrix2D<TypeParam>::neq(this->_eqMatA, this->_dissimilarMat);
//
//    EXPECT_VEC_EQ(this->_inequalityMask, mask);
//}

/** @} */