/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Mat3 equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"

#include <fgm/common/Constants.h>



/**
 * @addtogroup T_FGM_Mat3x3_Equality
 * @{
 */

namespace
{

    constexpr auto NAN_F = fgm::constants::NaN;
    constexpr auto INF   = fgm::constants::INFINITY_F;


    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat3 Equality.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3EqualityTests: public testing::Test
    {
    protected:
        fgm::Mat3<T> _eqMatA;
        fgm::Mat3<T> _eqMatB;
        fgm::Mat3<T> _unEqualMat;


        void SetUp() override
        {
            _eqMatA     = { { T(1.1234568789), T(2.123458319), T(3.323458319) },
                            { T(3.1234568789), T(4.123458319), T(7.123458319) },
                            { T(11.1234568789), T(3.123458319), T(5.123458319) } };
            _eqMatB     = { { T(1.1234568789), T(2.123458319), T(3.323458319) },
                            { T(3.1234568789), T(4.123458319), T(7.123458319) },
                            { T(11.1234568789), T(3.123458319), T(5.123458319) } };
            _unEqualMat = { { T(1.1234568789), T(4.5238852912), T(3.123458319) },
                            { T(3.1234568789), T(6.123458319), T(4.123458319) },
                            { T(3.1234568789), T(4.123458319), T(7.123458319) } };
        }
    };
    TYPED_TEST_SUITE(Mat3EqualityTests, SupportedArithmeticTypes);


    struct Mat3ElementParam
    {
        fgm::Mat3<int> first, second;
        bool expected;
    };

    /// @brief Test fixture for @ref fgm::Mat3 Equality on a per-element basis.
    class Mat3PerElementEqualityTests: public testing::TestWithParam<Mat3ElementParam>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat3Tests, Mat3PerElementEqualityTests,
        ::testing::Values(
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .expected = true },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 2, 2, 3, 4, 5, 6, 7, 8, 9 }, .expected = false },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 1, 3, 4, 5, 6, 7, 8, 9 }, .expected = false },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 1, 4, 5, 6, 7, 8, 9 }, .expected = false },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 1, 5, 6, 7, 8, 9 }, .expected = false },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 1, 6, 7, 8, 9 }, .expected = false },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 1, 7, 8, 9 }, .expected = false },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 1, 8, 9 }, .expected = false },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 7, 1, 9 }, .expected = false },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 1 }, .expected = false }));




    /// @brief Test fixture for @ref fgm::Mat3 Inequality on a per-element basis.
    class Mat3PerElementInequalityTests: public ::testing::TestWithParam<Mat3ElementParam>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat3Tests, Mat3PerElementInequalityTests,
        ::testing::Values(
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .expected = false },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 2, 2, 3, 4, 5, 6, 7, 8, 9 }, .expected = true },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 1, 3, 4, 5, 6, 7, 8, 9 }, .expected = true },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 1, 4, 5, 6, 7, 8, 9 }, .expected = true },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 1, 5, 6, 7, 8, 9 }, .expected = true },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 1, 6, 7, 8, 9 }, .expected = true },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 1, 7, 8, 9 }, .expected = true },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 1, 8, 9 }, .expected = true },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 7, 1, 9 }, .expected = true },
            Mat3ElementParam{
                .first = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, .second = { 1, 2, 3, 4, 5, 6, 7, 8, 1 }, .expected = true }));



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat3 MAT1(1, 2, 3);
        constexpr fgm::Mat3 MAT2(1, 2, 3);
        constexpr fgm::Mat3 MAT3(4, 2, 2);
        constexpr fgm::Mat3 INF_MAT1(-fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                     -fgm::constants::INFINITY_F);
        constexpr fgm::Mat3 INF_MAT2(-fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                     -fgm::constants::INFINITY_F);


        /** @test Verify that Mat3 allEq returns true for equal matrices at compile time. */
        static_assert(MAT1.allEq(MAT2) == true);

        /** @test Verify that Mat3 allEq returns false for unequal matrices at compile time. */
        static_assert(MAT1.allEq(MAT3) == false);

        /** @test Verify that Mat3 allEq returns true for equal infinite matrices at compile time. */
        static_assert(INF_MAT1.allEq(INF_MAT2) == true);



        /** @test Verify that Mat3 allEq (static wrapper) returns true for equal matrices at compile time. */
        static_assert(fgm::Mat3<int>::allEq(MAT1, MAT2) == true);

        /** @test Verify that Mat3 allEq (static wrapper) returns false for unequal matrices at compile time. */
        static_assert(fgm::Mat3<int>::allEq(MAT1, MAT3) == false);

        /** @test Verify that Mat3 allEq (static wrapper) returns true for equal infinite matrices at compile time. */
        static_assert(fgm::Mat3<float>::allEq(INF_MAT1, INF_MAT2) == true);



        /** @test Verify that Mat3 anyNeq returns false for equal matrices at compile time. */
        static_assert(MAT1.anyNeq(MAT2) == false);

        /** @test Verify that Mat3 anyNeq returns true for unequal matrices at compile time. */
        static_assert(MAT1.anyNeq(MAT3) == true);

        /** @test Verify that Mat3 anyNeq returns false for equal infinite matrices at compile time. */
        static_assert(INF_MAT1.anyNeq(INF_MAT2) == false);



        /** @test Verify that Mat3 anyNeq (static wrapper) returns false for equal matrices at compile time. */
        static_assert(fgm::Mat3<int>::anyNeq(MAT1, MAT2) == false);

        /** @test Verify that Mat3 anyNeq (static wrapper) returns true for unequal matrices at compile time. */
        static_assert(fgm::Mat3<int>::anyNeq(MAT1, MAT3) == true);

        /** @test Verify that Mat3 anyNeq (static wrapper) returns false for equal infinite matrices at compile time. */
        static_assert(fgm::Mat3<float>::anyNeq(INF_MAT1, INF_MAT2) == false);

    } // namespace static_tests

} // namespace




/**************************************
 *             ALL EQ                 *
 **************************************/

TYPED_TEST(Mat3EqualityTests, AllEq_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA.allEq(this->_eqMatB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat3EqualityTests, AllEq_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA.allEq(this->_unEqualMat);
    EXPECT_FALSE(equality);
}


TEST(Mat3EqualityTests, AllEq_NanMatrixReturnsFalse)
{
    const fgm::Mat3 matA(NAN_F, NAN_F, NAN_F);
    const fgm::Mat3 matB(1.0f, -5.88874789f, 0.888749f);

    const bool equality = matA.allEq(matB);
    EXPECT_FALSE(equality);
}


TEST(Mat3EqualityTests, AllEq_IdenticalInfiniteMatricesReturnTrue)
{
    const fgm::Mat3 matA(INF, -INF, INF);
    const fgm::Mat3 matB(INF, -INF, INF);

    const bool equality = matA.allEq(matB);
    EXPECT_TRUE(equality);
}


TEST(Mat3EqualityTests, AllEq_DifferentInfiniteMatricesReturnFalse)
{
    const fgm::Mat3 matA(INF, -INF, INF);
    const fgm::Mat3 matB(-INF, -INF, INF);

    const bool equality = matA.allEq(matB);
    EXPECT_FALSE(equality);
}


TYPED_TEST(Mat3EqualityTests, AllEq_MixedType_IdenticalMatricesReturnTrue)
{
    const fgm::Mat3 matA(1, 2, 3);
    const fgm::Mat3 matB(1.0, 2.0, 3.0);

    const bool equality = matA.allEq(matB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat3EqualityTests, AllEq_MixedType_DifferentMatricesReturnFalse)
{
    const fgm::Mat3 matA(5, 6, 7);
    const fgm::Mat3 matB(1.0, 2.0, 3.0);

    const bool equality = matA.allEq(matB);
    EXPECT_FALSE(equality);
}

TEST_P(Mat3PerElementEqualityTests, AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat.allEq(secondMat));
}


TYPED_TEST(Mat3EqualityTests, StaticWrapper_AllEq_IdenticalMatricesReturnTrue)
{
    const bool equality = fgm::Mat3<TypeParam>::allEq(this->_eqMatA, this->_eqMatB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat3EqualityTests, StaticWrapper_AllEq_DifferentMatricesReturnFalse)
{
    const bool equality = fgm::Mat3<TypeParam>::allEq(this->_eqMatA, this->_unEqualMat);
    EXPECT_FALSE(equality);
}


TEST_P(Mat3PerElementEqualityTests, StaticWrapper_AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat3<int>::allEq(firstMat, secondMat));
}



/**************************************
 *       DOUBLE-EQUALS OPERATOR       *
 **************************************/

TYPED_TEST(Mat3EqualityTests, DoubleEqualsOperator_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA == this->_eqMatB;
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat3EqualityTests, DoubleEqualsOperator_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA == this->_unEqualMat;
    EXPECT_FALSE(equality);
}


TEST_P(Mat3PerElementEqualityTests, DoubleEqualsOperator_AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat == secondMat);
}


TEST(Mat3EqualityTests, DoubleEqualsOperator_IdenticalBooleanMatricesReturnTrue)
{
    const fgm::Mat3 matA(true, false, true);
    const fgm::Mat3 matB(true, false, true);

    const bool equality = matA == matB;
    EXPECT_TRUE(equality);
}


TEST(Mat3EqualityTests, DoubleEqualsOperator_DifferentBooleanMatricesReturnFalse)
{
    const fgm::Mat3 matA(true, false, false);
    const fgm::Mat3 matB(true, true, false);

    const bool equality = matA == matB;
    EXPECT_FALSE(equality);
}


TEST_P(Mat3PerElementEqualityTests, DoubleEqualsOperator_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat == secondMat);
}



/**************************************
 *             ANY NEQ                *
 **************************************/

TYPED_TEST(Mat3EqualityTests, AnyNeq_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_eqMatB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat3EqualityTests, AnyNeq_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_unEqualMat);
    EXPECT_TRUE(inequality);
}


TEST(Mat3EqualityTests, AnyNeq_NanMatrixReturnsTrue)
{
    const fgm::Mat3 matA(NAN_F, NAN_F, NAN_F);
    const fgm::Mat3 matB(1.0f, INF, -INF);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_TRUE(inequality);
}


TEST(Mat3EqualityTests, AnyNeq_IdenticalInfiniteMatricesReturnFalse)
{
    const fgm::Mat3 matA(INF, -INF, INF);
    const fgm::Mat3 matB(INF, -INF, INF);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_FALSE(inequality);
}


TEST(Mat3EqualityTests, AnyNeq_DifferentInfiniteMatricesReturnTrue)
{
    const fgm::Mat3 matA(-INF, INF, INF);
    const fgm::Mat3 matB(INF, INF, -INF);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_TRUE(inequality);
}


TYPED_TEST(Mat3EqualityTests, AnyNeq_MixedType_IdenticalMatricesReturnFalse)
{
    const fgm::Mat3 matA(1, 2, 3);
    const fgm::Mat3 matB(1.0, 2.0, 3.0);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat3EqualityTests, AnyNeq_MixedType_DifferentMatricesReturnTrue)
{
    const fgm::Mat3 matA(5, 6, 7);
    const fgm::Mat3 matB(1.0, 2.0, 7.0);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_TRUE(inequality);
}


TEST_P(Mat3PerElementInequalityTests, AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat.anyNeq(secondMat));
}


TYPED_TEST(Mat3EqualityTests, StaticWrapper_AnyNeq_IdenticalMatricesReturnFalse)
{
    const bool inequality = fgm::Mat3<TypeParam>::anyNeq(this->_eqMatA, this->_eqMatB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat3EqualityTests, StaticWrapper_AnyNeq_DifferentMatricesReturnTrue)
{
    const bool inequality = fgm::Mat3<TypeParam>::anyNeq(this->_eqMatA, this->_unEqualMat);
    EXPECT_TRUE(inequality);
}


TEST_P(Mat3PerElementInequalityTests, StaticWrapper_AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Mat3<int>::anyNeq(firstMat, secondMat));
}



/**************************************
 *            NOT EQUALS              *
 **************************************/

TYPED_TEST(Mat3EqualityTests, NotEqualsOperator_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA != this->_eqMatB;
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat3EqualityTests, NotEqualsOperator_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA != this->_unEqualMat;
    EXPECT_TRUE(inequality);
}


TEST(Mat3EqualityTests, NotEqualsOperator_IdenticalBooleanMatricesReturnFalse)
{
    const fgm::Mat3 matA(true, false, true);
    const fgm::Mat3 matB(true, false, true);

    const bool inequality = matA != matB;
    EXPECT_FALSE(inequality);
}


TEST(Mat3EqualityTests, NotEqualsOperator_DifferentBooleanMatricesReturnTrue)
{
    const fgm::Mat3 matA(true, false, true);
    const fgm::Mat3 matB(true, true, false);

    const bool inequality = matA != matB;
    EXPECT_TRUE(inequality);
}


TEST_P(Mat3PerElementInequalityTests, NotEqualsOperator_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat != secondMat);
}


/** @} */
