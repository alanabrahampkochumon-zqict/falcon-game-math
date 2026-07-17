/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify fgm::Matrix2x3 equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Matrix2x3TestSetup.h"

#include <fgm/common/Constants.h>



constexpr auto NAN_F = fgm::constants::NaN;
constexpr auto INF   = fgm::constants::INFINITY_F;


template <typename T>
class Matrix2x3Equality: public ::testing::Test
{
protected:
    fgm::Mat2x3<T> _eqMatA;
    fgm::Mat2x3<T> _eqMatB;
    fgm::Mat2x3<T> _dissimilarMat;


    void SetUp() override
    {
        _eqMatA        = { { T(1.1234568789), T(2.123458319) },
                           { T(3.1234568789), T(4.123458319) },
                           { T(1.23942), T(5.2192381) } };
        _eqMatB        = { { T(1.1234568789), T(2.123458319) },
                           { T(3.1234568789), T(4.123458319) },
                           { T(1.23942), T(5.2192381) } };
        _dissimilarMat = { { T(1.1234568789), T(4.5238852912) },
                           { T(3.1234568789), T(6.123458319) },
                           { T(5.2389421), T(22.123904213) } };
    }
};
/**
 * @brief Test fixture for fgm::Matrix2x3 equality and inequality checks, parameterized by
 *        SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Matrix2x3Equality, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x3_Equality
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{

    constexpr fgm::Mat2x3 MAT1(1, 2, 3, 4, 5, 6);
    constexpr fgm::Mat2x3 MAT2(1, 2, 3, 4, 5, 6);
    constexpr fgm::Mat2x3 MAT3(4, 2, 2, 4, 5, 6);
    constexpr fgm::Mat2x3 INF_MAT1(-fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                      -fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                      fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);
    constexpr fgm::Mat2x3 INF_MAT2(-fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                      -fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                      fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);


    /** @brief Verify that matrix equality check is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(MAT1.allEq(MAT2) == true);
        static_assert(MAT1.allEq(MAT3) == false);
        static_assert(INF_MAT1.allEq(INF_MAT2) == true);


        // Static functions
        static_assert(fgm::Mat2x3<int>::allEq(MAT1, MAT2) == true);
        static_assert(fgm::Mat2x3<int>::allEq(MAT1, MAT3) == false);
        static_assert(fgm::Mat2x3<float>::allEq(INF_MAT1, INF_MAT2) == true);

    } // namespace

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that fgm::Matrix2x3::allEq returns true for identical matrices. */
TYPED_TEST(Matrix2x3Equality, Equality_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA.allEq(this->_eqMatB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that fgm::Matrix2x3::allEq returns false if any component differ. */
TYPED_TEST(Matrix2x3Equality, Equality_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA.allEq(this->_dissimilarMat);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the static variant of fgm::Matrix2x3::allEq for identical matrices. */
TYPED_TEST(Matrix2x3Equality, StaticWrapper_Equality_IdenticalMatricesReturnTrue)
{
    const bool equality = fgm::Mat2x3<TypeParam>::allEq(this->_eqMatA, this->_eqMatB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the static variant of fgm::Matrix2x3::allEq for different matrices. */
TYPED_TEST(Matrix2x3Equality, StaticWrapper_Equality_DifferentMatricesReturnFalse)
{
    const bool equality = fgm::Mat2x3<TypeParam>::allEq(this->_eqMatA, this->_dissimilarMat);

    EXPECT_FALSE(equality);
}


/** @brief Verify that fgm::Matrix2x3::allEq follows IEEE 754 for NaN comparisons. */
TEST(Matrix2x3Equality, NanEqualityReturnsFalse)
{
    const fgm::Mat2x3 matA(NAN_F, NAN_F, NAN_F, NAN_F, NAN_F, 1.0f);
    const fgm::Mat2x3 matB(1.0f, -5.88874789f, 2.0f, 0.888749f, 0.5329f, 5.23193f);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that fgm::Matrix2x3::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Matrix2x3Equality, InfinityEquality_IdenticalMatricesReturnTrue)
{
    const fgm::Mat2x3 matA(INF, -INF, INF, -INF, -INF, INF);
    const fgm::Mat2x3 matB(INF, -INF, INF, -INF, -INF, INF);

    const bool equality = matA.allEq(matB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that fgm::Matrix2x3::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Matrix2x3Equality, InfinityEquality_DifferentMatricesReturnFalse)
{
    const fgm::Mat2x3 matA(INF, -INF, INF, -INF, INF, INF);
    const fgm::Mat2x3 matB(-INF, -INF, INF, INF, INF, INF);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}

/** @brief Verify that fgm::Matrix2x3::allEq works for different vector types with identical components. */
TYPED_TEST(Matrix2x3Equality, MixedType_Equality_IdenticalMatricesReturnTrue)
{
    const fgm::Mat2x3 matA(1, 2, 3, 4, 5, 6);
    const fgm::Mat2x3 matB(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    const bool equality = matA.allEq(matB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that fgm::Matrix2x3::allEq works for different vector types with different components. */
TYPED_TEST(Matrix2x3Equality, MixedType_Equality_DifferentMatricesReturnFalse)
{
    const fgm::Mat2x3 matA(5, 6, 7, 8, 9, 10);
    const fgm::Mat2x3 matB(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}



/** @brief Verify that the equality operator returns true for identical matrices. */
TYPED_TEST(Matrix2x3Equality, EqualityOperator_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA == this->_eqMatB;

    EXPECT_TRUE(equality);
}



/** @brief Verify that the equality operator returns false if any component differ. */
TYPED_TEST(Matrix2x3Equality, EqualityOperator_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA == this->_dissimilarMat;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator works for bool matrix with identical components. */
TEST(Matrix2x3Equality, EqualityOperator_IdenticalBooleanMatricesReturnTrue)
{
    const fgm::Mat2x3 matA(true, false, true, false, false, true);
    const fgm::Mat2x3 matB(true, false, true, false, false, true);

    const bool equality = matA == matB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that the equality operator works for bool matrix with different components. */
TEST(Matrix2x3Equality, EqualityOperator_DifferentBooleanMatricesReturnFalse)
{
    const fgm::Mat2x3 matA(true, false, false, true, false, false);
    const fgm::Mat2x3 matB(true, true, false, true, true, false);

    const bool equality = matA == matB;

    EXPECT_FALSE(equality);
}

/** @} */



/**
 * @addtogroup T_FGM_Mat2x3_Inequality
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that matrix inequality check is available at compile time. */
namespace
{
    // Member functions
    static_assert(MAT1.anyNeq(MAT2) == false);
    static_assert(MAT1.anyNeq(MAT3) == true);
    static_assert(INF_MAT1.anyNeq(INF_MAT2) == false);


    // Static functions
    static_assert(fgm::Mat2x3<int>::anyNeq(MAT1, MAT2) == false);
    static_assert(fgm::Mat2x3<int>::anyNeq(MAT1, MAT3) == true);
    static_assert(fgm::Mat2x3<float>::anyNeq(INF_MAT1, INF_MAT2) == false);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that fgm::Matrix2x3::anyNeq returns false for identical matrices. */
TYPED_TEST(Matrix2x3Equality, Inequality_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_eqMatB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that fgm::Matrix2x3::anyNeq returns true if any component differ. */
TYPED_TEST(Matrix2x3Equality, Inequality_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_dissimilarMat);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that the static variant of fgm::Matrix2x3::anyNeq for identical matrices. */
TYPED_TEST(Matrix2x3Equality, StaticWrapper_Inequality_IdenticalMatricesReturnFalse)
{
    const bool inequality = fgm::Mat2x3<TypeParam>::anyNeq(this->_eqMatA, this->_eqMatB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that the static variant of fgm::Matrix2x3::anyNeq for different matrices. */
TYPED_TEST(Matrix2x3Equality, StaticWrapper_Inequality_DifferentMatricesReturnTrue)
{
    const bool inequality = fgm::Mat2x3<TypeParam>::anyNeq(this->_eqMatA, this->_dissimilarMat);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that fgm::Matrix2x3::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Matrix2x3Equality, NanInequalityReturnsTrue)
{
    const fgm::Mat2x3 matA(NAN_F, NAN_F, NAN_F, NAN_F, NAN_F, NAN_F);
    const fgm::Mat2x3 matB(1.0f, -5.88874789f, INF, -INF, INF, NAN_F);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that fgm::Matrix2x3::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Matrix2x3Equality, InfinityInequality_IdenticalMatricesReturnFalse)
{
    const fgm::Mat2x3 matA(INF, -INF, INF, -INF, INF, INF);
    const fgm::Mat2x3 matB(INF, -INF, INF, -INF, INF, INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that fgm::Matrix2x3::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Matrix2x3Equality, InfinityInequality_DifferentMatricesReturnTrue)
{
    const fgm::Mat2x3 matA(-INF, INF, INF, -INF, INF, -INF);
    const fgm::Mat2x3 matB(INF, INF, -INF, -INF, INF, INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that fgm::Matrix2x3::anyNeq works for different vector types with identical components. */
TYPED_TEST(Matrix2x3Equality, MixedType_Inequality_IdenticalMatricesReturnFalse)
{
    const fgm::Mat2x3 matA(1, 2, 3, 4, 5, 6);
    const fgm::Mat2x3 matB(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that fgm::Matrix2x3::anyNeq works for different vector types with different components. */
TYPED_TEST(Matrix2x3Equality, MixedType_Inequality_DifferentMatricesReturnTrue)
{
    const fgm::Mat2x3 matA(5, 6, 7, 8, 10, 11);
    const fgm::Mat2x3 matB(1.0, 2.0, 7.0, 8.0, 9.0, 10.0);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that the operator returns false for identical matrices. */
TYPED_TEST(Matrix2x3Equality, InEqualityOperator_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA != this->_eqMatB;

    EXPECT_FALSE(inequality);
}


/** @brief Verify that the inequality operator returns true for different matrices. */
TYPED_TEST(Matrix2x3Equality, InEqualityOperator_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA != this->_dissimilarMat;

    EXPECT_TRUE(inequality);
}


/** @brief Verify that the inequality operator works for fgm::Matrix2x3<bool> with identical components. */
TEST(Matrix2x3Equality, InequalityOperator_IdenticalBooleanMatricesReturnFalse)
{
    const fgm::Mat2x3 matA(true, false, false, true, false, false);
    const fgm::Mat2x3 matB(true, false, false, true, false, false);

    const bool inequality = matA != matB;

    EXPECT_FALSE(inequality);
}


/** @brief Verify that the inequality operator works for fgm::Matrix2x3<bool> with different components. */
TEST(Matrix2x3Equality, InequalityOperator_DifferentBooleanMatricesReturnTrue)
{
    const fgm::Mat2x3 matA(true, false, true, false, false, true);
    const fgm::Mat2x3 matB(true, true, false, true, false, true);

    const bool inequality = matA != matB;

    EXPECT_TRUE(inequality);
}

/** @} */
