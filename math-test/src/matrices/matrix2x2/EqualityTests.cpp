/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Matrix2 equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"

#include <fgm/common/Constants.h>



constexpr auto NAN_F = fgm::constants::NaN;
constexpr auto INF   = fgm::constants::INFINITY_F;


template <typename T>
class Matrix2Equality: public ::testing::Test
{
protected:
    fgm::Matrix2<T> _eqMatA;
    fgm::Matrix2<T> _eqMatB;
    fgm::Matrix2<T> _dissimilarMat;


    void SetUp() override
    {
        _eqMatA        = { { T(1.1234568789), T(2.123458319) }, { T(3.1234568789), T(4.123458319) } };
        _eqMatB        = { { T(1.1234568789), T(2.123458319) }, { T(3.1234568789), T(4.123458319) } };
        _dissimilarMat = { { T(1.1234568789), T(4.5238852912) }, { T(3.1234568789), T(6.123458319) } };
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2 equality and inequality checks, parameterized by
 *        @ref SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Matrix2Equality, SupportedArithmeticTypes);



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

    constexpr fgm::Matrix2 MAT1(1, 2, 3, 4);
    constexpr fgm::Matrix2 MAT2(1, 2, 3, 4);
    constexpr fgm::Matrix2 MAT3(4, 2, 2, 4);
    constexpr fgm::Matrix2 INF_MAT1(-fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                     -fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);
    constexpr fgm::Matrix2 INF_MAT2(-fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                     -fgm::constants::INFINITY_F, fgm::constants::INFINITY_F);


    /** @brief Verify that matrix equality check is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(MAT1.allEq(MAT2) == true);
        static_assert(MAT1.allEq(MAT3) == false);
        static_assert(INF_MAT1.allEq(INF_MAT2) == true);


        // Static functions
        static_assert(fgm::Matrix2<int>::allEq(MAT1, MAT2) == true);
        static_assert(fgm::Matrix2<int>::allEq(MAT1, MAT3) == false);
        static_assert(fgm::Matrix2<float>::allEq(INF_MAT1, INF_MAT2) == true);

    } // namespace

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Matrix2::allEq returns true for identical matrices. */
TYPED_TEST(Matrix2Equality, Equality_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA.allEq(this->_eqMatB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Matrix2::allEq returns false if any component differ. */
TYPED_TEST(Matrix2Equality, Equality_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA.allEq(this->_dissimilarMat);

    EXPECT_FALSE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Matrix2::allEq for identical matrices. */
TYPED_TEST(Matrix2Equality, StaticWrapper_Equality_IdenticalMatricesReturnTrue)
{
    const bool equality = fgm::Matrix2<TypeParam>::allEq(this->_eqMatA, this->_eqMatB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that the static variant of @ref fgm::Matrix2::allEq for different matrices. */
TYPED_TEST(Matrix2Equality, StaticWrapper_Equality_DifferentMatricesReturnFalse)
{
    const bool equality = fgm::Matrix2<TypeParam>::allEq(this->_eqMatA, this->_dissimilarMat);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Matrix2::allEq follows IEEE 754 for NaN comparisons. */
TEST(Matrix2Equality, NanEqualityReturnsFalse)
{
    const fgm::Matrix2 matA(NAN_F, NAN_F, NAN_F, NAN_F);
    const fgm::Matrix2 matB(1.0f, -5.88874789f, 2.0f, 0.888749f);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}


/** @brief Verify that @ref fgm::Matrix2::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Matrix2Equality, InfinityEquality_IdenticalMatricesReturnTrue)
{
    const fgm::Matrix2 matA(INF, -INF, INF, -INF);
    const fgm::Matrix2 matB(INF, -INF, INF, -INF);

    const bool equality = matA.allEq(matB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Matrix2::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Matrix2Equality, InfinityEquality_DifferentMatricesReturnFalse)
{
    const fgm::Matrix2 matA(INF, -INF, INF, -INF);
    const fgm::Matrix2 matB(-INF, -INF, INF, INF);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}

/** @brief Verify that @ref fgm::Matrix2::allEq works for different vector types with identical components. */
TYPED_TEST(Matrix2Equality, MixedType_Equality_IdenticalMatricesReturnTrue)
{
    const fgm::Matrix2 matA(1, 2);
    const fgm::Matrix2 matB(1.0, 2.0);

    const bool equality = matA.allEq(matB);

    EXPECT_TRUE(equality);
}


/** @brief Verify that @ref fgm::Matrix2::allEq works for different vector types with different components. */
TYPED_TEST(Matrix2Equality, MixedType_Equality_DifferentMatricesReturnFalse)
{
    const fgm::Matrix2 matA(5, 6);
    const fgm::Matrix2 matB(1.0, 2.0);

    const bool equality = matA.allEq(matB);

    EXPECT_FALSE(equality);
}



/** @brief Verify that the equality operator returns true for identical matrices. */
TYPED_TEST(Matrix2Equality, EqualityOperator_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA == this->_eqMatB;

    EXPECT_TRUE(equality);
}



/** @brief Verify that the equality operator returns false if any component differ. */
TYPED_TEST(Matrix2Equality, EqualityOperator_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA == this->_dissimilarMat;

    EXPECT_FALSE(equality);
}


/** @brief Verify that the equality operator works for bool matrix with identical components. */
TEST(Matrix2Equality, EqualityOperator_IdenticalBooleanMatricesReturnTrue)
{
    const fgm::Matrix2 matA(true, false, true, false);
    const fgm::Matrix2 matB(true, false, true, false);

    const bool equality = matA == matB;

    EXPECT_TRUE(equality);
}


/** @brief Verify that the equality operator works for bool matrix with different components. */
TEST(Matrix2Equality, EqualityOperator_DifferentBooleanMatricesReturnFalse)
{
    const fgm::Matrix2 matA(true, false, false, true);
    const fgm::Matrix2 matB(true, true, false, true);

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
    static_assert(fgm::Matrix2<int>::anyNeq(MAT1, MAT2) == false);
    static_assert(fgm::Matrix2<int>::anyNeq(MAT1, MAT3) == true);
    static_assert(fgm::Matrix2<float>::anyNeq(INF_MAT1, INF_MAT2) == false);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that @ref fgm::Matrix2::anyNeq returns false for identical matrices. */
TYPED_TEST(Matrix2Equality, Inequality_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_eqMatB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that @ref fgm::Matrix2::anyNeq returns true if any component differ. */
TYPED_TEST(Matrix2Equality, Inequality_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_dissimilarMat);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that the static variant of @ref fgm::Matrix2::anyNeq for identical matrices. */
TYPED_TEST(Matrix2Equality, StaticWrapper_Inequality_IdenticalMatricesReturnFalse)
{
    const bool inequality = fgm::Matrix2<TypeParam>::anyNeq(this->_eqMatA, this->_eqMatB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that the static variant of @ref fgm::Matrix2::anyNeq for different matrices. */
TYPED_TEST(Matrix2Equality, StaticWrapper_Inequality_DifferentMatricesReturnTrue)
{
    const bool inequality = fgm::Matrix2<TypeParam>::anyNeq(this->_eqMatA, this->_dissimilarMat);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that @ref fgm::Matrix2::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Matrix2Equality, NanInequalityReturnsTrue)
{
    const fgm::Matrix2 matA(NAN_F, NAN_F, NAN_F, NAN_F);
    const fgm::Matrix2 matB(1.0f, -5.88874789f, INF, -INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that @ref fgm::Matrix2::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Matrix2Equality, InfinityInequality_IdenticalMatricesReturnFalse)
{
    const fgm::Matrix2 matA(INF, -INF, INF, -INF);
    const fgm::Matrix2 matB(INF, -INF, INF, -INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that @ref fgm::Matrix2::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Matrix2Equality, InfinityInequality_DifferentMatricesReturnTrue)
{
    const fgm::Matrix2 matA(-INF, INF, INF, -INF);
    const fgm::Matrix2 matB(INF, INF, -INF, -INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that @ref fgm::Matrix2::anyNeq works for different vector types with identical components. */
TYPED_TEST(Matrix2Equality, MixedType_Inequality_IdenticalMatricesReturnFalse)
{
    const fgm::Matrix2 matA(1, 2, 3, 4);
    const fgm::Matrix2 matB(1.0, 2.0, 3.0, 4.0);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_FALSE(inequality);
}


/** @brief Verify that @ref fgm::Matrix2::anyNeq works for different vector types with different components. */
TYPED_TEST(Matrix2Equality, MixedType_Inequality_DifferentMatricesReturnTrue)
{
    const fgm::Matrix2 matA(5, 6, 7, 8);
    const fgm::Matrix2 matB(1.0, 2.0, 7.0, 8.0);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


/** @brief Verify that the operator returns false for identical matrices. */
TYPED_TEST(Matrix2Equality, InEqualityOperator_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA != this->_eqMatB;

    EXPECT_FALSE(inequality);
}


/** @brief Verify that the inequality operator returns true for different matrices. */
TYPED_TEST(Matrix2Equality, InEqualityOperator_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA != this->_dissimilarMat;

    EXPECT_TRUE(inequality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Matrix2<bool> with identical components. */
TEST(Matrix2Equality, InequalityOperator_IdenticalBooleanMatricesReturnFalse)
{
    const fgm::Matrix2 matA(true, false);
    const fgm::Matrix2 matB(true, false);

    const bool inequality = matA != matB;

    EXPECT_FALSE(inequality);
}


/** @brief Verify that the inequality operator works for @ref fgm::Matrix2<bool> with different components. */
TEST(Matrix2Equality, InequalityOperator_DifferentBooleanMatricesReturnTrue)
{
    const fgm::Matrix2 matA(true, false, true, false);
    const fgm::Matrix2 matB(true, true, false, true);

    const bool inequality = matA != matB;

    EXPECT_TRUE(inequality);
}

/** @} */
