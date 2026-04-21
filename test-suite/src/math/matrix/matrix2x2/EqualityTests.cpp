/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Matrix2D equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
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
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace 
{

    constexpr fgm::Matrix2D MAT1(1, 2, 3, 4);
    constexpr fgm::Matrix2D MAT2(1, 2, 3, 4);
    constexpr fgm::Matrix2D MAT3(4, 2, 2, 4);
    constexpr fgm::Matrix2D NAN_MAT(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN);
    constexpr fgm::Matrix2D INF_MAT1(-fgm::constants::INFINITY_F, fgm::constants::INFINITY_F, -fgm::constants::INFINITY_F,
                                    fgm::constants::INFINITY_F);
    constexpr fgm::Matrix2D INF_MAT2(-fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                    -fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);

    /** @brief Verify that matrix equality check is available at compile time. */
    namespace 
    {
        // Member functions
        static_assert(MAT1.allEq(MAT2) == true);
        static_assert(MAT1.allEq(MAT3) == false);
        static_assert(NAN_MAT.allEq(MAT1) == false);
        static_assert(INF_MAT1.allEq(INF_MAT2) == true);


        // Static functions
        static_assert(fgm::Matrix2D<int>::allEq(MAT1, MAT2) == true);
        static_assert(fgm::Matrix2D<int>::allEq(MAT1, MAT3) == false);
        static_assert(fgm::Matrix2D<int>::allEq(MAT1, NAN_MAT) == false);
        static_assert(fgm::Matrix2D<float>::allEq(INF_MAT1, INF_MAT2) == true);

    }


    /** @brief Verify that matrix inequality check is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(MAT1.anyNeq(MAT2) == false);
        static_assert(MAT1.anyNeq(MAT3) == true);
        static_assert(NAN_MAT.anyNeq(MAT1) == true);
        static_assert(INF_MAT1.anyNeq(INF_MAT2) == false);


        // Static functions
        static_assert(fgm::Matrix2D<int>::anyNeq(MAT1, MAT2) == false);
        static_assert(fgm::Matrix2D<int>::anyNeq(MAT1, MAT3) == true);
        static_assert(fgm::Matrix2D<int>::anyNeq(MAT1, NAN_MAT) == true);
        static_assert(fgm::Matrix2D<float>::anyNeq(INF_MAT1, INF_MAT2) == false);

    } // namespace
}


/**************************************
 *                                    *
 *           EQUALITY TESTS           *
 *                                    *
 **************************************/

/** @test Verify that @ref fgm::Matrix2D::allEq returns true for identical matrices. */
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


/** @test Verify that the static variant of @ref fgm::Matrix2D::allEq for identical matrices. */
TYPED_TEST(Matrix2DEquality, StaticWrapper_Equality_IdenticalMatricesReturnTrue)
{
    const bool equality = fgm::Matrix2D<TypeParam>::allEq(this->_eqMatA, this->_eqMatB);

    EXPECT_TRUE(equality);
}


/** @test Verify that the static variant of @ref fgm::Matrix2D::allEq for different matrices. */
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

    constexpr bool equality = matA.allEq(matB);

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



/** @test Verify that the equality operator returns true for identical matrices. */
 TYPED_TEST(Matrix2DEquality, EqualityOperator_IdenticalMatricesReturnTrue)
{
     const bool equality = this->_eqMatA == this->_eqMatB;

     EXPECT_TRUE(equality);
 }



/** @test Verify that the equality operator returns false if any component differ. */
 TYPED_TEST(Matrix2DEquality, EqualityOperator_DifferentMatricesReturnFalse)
{
     const bool equality = this->_eqMatA == this->_dissimilarMat;

     EXPECT_FALSE(equality);
 }


/** @test Verify that the equality operator works for bool matrix with identical components. */
 TEST(Matrix2DEquality, EqualityOperator_IdenticalBooleanMatricesReturnTrue)
{
     constexpr fgm::Matrix2D matA(true, false, true, false);
     constexpr fgm::Matrix2D matB(true, false, true, false);

     const bool equality = matA == matB;

     EXPECT_TRUE(equality);
 }


/** @test Verify that the equality operator works for bool matrix with different components. */
 TEST(Matrix2DEquality, EqualityOperator_DifferentBooleanMatricesReturnFalse)
{
     constexpr fgm::Matrix2D matA(true, false, false, true);
     constexpr fgm::Matrix2D matB(true, true, false, true);

     const bool equality = matA == matB;

     EXPECT_FALSE(equality);
 }

/** @} */



/**
 * @addtogroup T_FGM_Mat2x2_Inequality
 * @{
 */

/**************************************
 *                                    *
 *          INEQUALITY TESTS          *
 *                                    *
 **************************************/


/** @test Verify that @ref fgm::Matrix2D::anyNeq returns false for identical matrices. */
TYPED_TEST(Matrix2DEquality, Inequality_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_eqMatB);
        
    EXPECT_FALSE(inequality);
}


/** @test Verify that @ref fgm::Matrix2D::anyNeq returns true if any component differ. */
TYPED_TEST(Matrix2DEquality, Inequality_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_dissimilarMat);

    EXPECT_TRUE(inequality);
}


/** @test Verify that the static variant of @ref fgm::Matrix2D::anyNeq for identical matrices. */
TYPED_TEST(Matrix2DEquality, StaticWrapper_Inequality_IdenticalMatricesReturnFalse)
{
    const bool inequality = fgm::Matrix2D<TypeParam>::anyNeq(this->_eqMatA, this->_eqMatB);

    EXPECT_FALSE(inequality);
}


/** @test Verify that the static variant of @ref fgm::Matrix2D::anyNeq for different matrices. */
TYPED_TEST(Matrix2DEquality, StaticWrapper_Inequality_DifferentMatricesReturnTrue)
{
    const bool inequality = fgm::Matrix2D<TypeParam>::anyNeq(this->_eqMatA, this->_dissimilarMat);

    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref fgm::Matrix2D::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Matrix2DEquality, NanInequalityReturnsTrue)
{
    constexpr fgm::Matrix2D matA( NAN_F, NAN_F, NAN_F, NAN_F );
    constexpr fgm::Matrix2D matB(1.0f, -5.88874789f, INF, -INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref fgm::Matrix2D::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Matrix2DEquality, InfinityInequality_IdenticalMatricesReturnFalse)
{
    constexpr fgm::Matrix2D matA(INF, -INF, INF, -INF);
    constexpr fgm::Matrix2D matB(INF, -INF, INF, -INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_FALSE(inequality);
}


/** @test Verify that @ref fgm::Matrix2D::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Matrix2DEquality, InfinityInequality_DifferentMatricesReturnTrue)
{
    constexpr fgm::Matrix2D matA(-INF, INF, INF, -INF);
    constexpr fgm::Matrix2D matB(INF, INF, -INF, -INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref fgm::Matrix2D::anyNeq works for different vector types with identical components. */
TYPED_TEST(Matrix2DEquality, MixedType_Inequality_IdenticalMatricesReturnFalse)
{
    constexpr fgm::Matrix2D matA(1, 2, 3, 4);
    constexpr fgm::Matrix2D matB(1.0, 2.0, 3.0, 4.0);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_FALSE(inequality);
}


/** @test Verify that @ref fgm::Matrix2D::anyNeq works for different vector types with different components. */
TYPED_TEST(Matrix2DEquality, MixedType_Inequality_DifferentMatricesReturnTrue)
{
    constexpr fgm::Matrix2D matA(5, 6, 7, 8);
    constexpr fgm::Matrix2D matB(1.0, 2.0, 7.0, 8.0);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @test Verify that the operator returns false for identical matrices. */
 TYPED_TEST(Matrix2DEquality, InEqualityOperator_IdenticalMatricesReturnFalse)
{
     const bool inequality = this->_eqMatA != this->_eqMatB;

     EXPECT_FALSE(inequality);
 }


/** @test Verify that the inequality operator returns true for different matrices. */
 TYPED_TEST(Matrix2DEquality, InEqualityOperator_DifferentMatricesReturnTrue)
{
     const bool inequality = this->_eqMatA != this->_dissimilarMat;

     EXPECT_TRUE(inequality);
 }


/** @test Verify that the inequality operator works for @ref fgm::Matrix2D<bool> with identical components. */
 TEST(Matrix2DEquality, InequalityOperator_IdenticalBooleanMatricesReturnFalse)
{
     constexpr fgm::Matrix2D matA(true, false);
     constexpr fgm::Matrix2D matB(true, false);

     constexpr bool inequality = matA != matB;

     EXPECT_FALSE(inequality);
 }


/** @test Verify that the inequality operator works for @ref fgm::Matrix2D<bool> with different components. */
 TEST(Matrix2DEquality, InequalityOperator_DifferentBooleanMatricesReturnTrue)
{
     constexpr fgm::Matrix2D matA(true, false, true, false);
     constexpr fgm::Matrix2D matB(true, true, false, true);

     constexpr bool inequality = matA != matB;

     EXPECT_TRUE(inequality);
 }

/** @} */