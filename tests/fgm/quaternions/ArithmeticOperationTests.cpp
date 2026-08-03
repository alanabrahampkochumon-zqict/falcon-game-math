/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 03, 2026
 *
 * @brief Verify @ref fgm::Quaternion arithmetic operator(+, -, *, /) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"


/**
 * @addtogroup T_FGM_Quaternion_Arithmetic
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for verifying quaternion addition across different scalar types.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionAddition: public testing::Test
    {
    protected:
        fgm::Quaternion<T> _quatA;
        fgm::Quaternion<T> _quatB;
        fgm::Quaternion<T> _expectedSum;

        void SetUp() override
        {
            _quatA       = { T(3), T(1), T(6), T(2) };
            _quatB       = { T(5), T(3), T(1), T(6) };
            _expectedSum = { T(8), T(4), T(7), T(8) };
        }
    };
    TYPED_TEST_SUITE(QuaternionAddition, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for verifying quaternion subtraction across different scalar types.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionSubtraction: public testing::Test
    {
    protected:
        fgm::Quaternion<T> _quatA;
        fgm::Quaternion<T> _quatB;
        fgm::Quaternion<T> _expectedDifference;

        void SetUp() override
        {
            _quatA              = { T(95), T(12), T(5), T(7) };
            _quatB              = { T(88), T(5), T(2), T(5) };
            _expectedDifference = { T(7), T(7), T(3), T(2) };
        }
    };
    TYPED_TEST_SUITE(QuaternionSubtraction, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for verifying quaternion multiplication with scalar across different scalar types.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionScalarMultiplication: public testing::Test
    {
    protected:
        fgm::Quaternion<T> _quat;
        T _scalar;
        fgm::Quaternion<T> _expectedFloatingVec;
        fgm::Quaternion<T> _expectedIntegralVec;

        void SetUp() override
        {
            _quat                = { T(7), T(13), T(29), T(41) };
            _scalar              = T(2.123456789123456);
            _expectedFloatingVec = { T(14.864197523864192), T(27.604938258604928), T(61.580246884580224),
                                     T(87.061728354061696) };
            _expectedIntegralVec = { T(14), T(26), T(58), T(82) };
        }
    };
    TYPED_TEST_SUITE(QuaternionScalarMultiplication, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for verifying quaternion division by a scalar across different scalar types.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionScalarDivision: public testing::Test
    {
    protected:
        fgm::Quaternion<T> _quat;
        T _scalar;
        fgm::Quaternion<T> _expectedScaledVec;

        void SetUp() override
        {
            _quat              = { T(17), T(31), T(59), T(73) };
            _scalar            = T(13);
            _expectedScaledVec = { T(1.30769230769230769231), T(2.38461538461538461538), T(4.53846153846153846154),
                                   T(5.61538461538461538462) };
        }
    };
    TYPED_TEST_SUITE(QuaternionScalarDivision, SupportedArithmeticTypes);


    // /**
    //  * @brief Test fixture for verifying quaternion negation across different scalar types.
    //  *
    //  * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
    //  */
    // template <typename T>
    // class QuaternionNegation: public testing::Test
    // {
    // protected:
    //     fgm::Quaternion<T> _quat;
    //     fgm::Quaternion<T> _expectedInvertedVec;
    //
    //     void SetUp() override
    //     {
    //         _quat                 = { T(-8), T(0), T(-2), T(5) };
    //         _expectedInvertedVec = { T(8), T(0), T(2), T(-5) };
    //     }
    // };
    // TYPED_TEST_SUITE(QuaternionNegation, SupportedSignedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    /** @brief Verify that quaternion arithmetic operations are available at compile time. */
    namespace static_tests
    {
        constexpr fgm::Quaternion QUAT_A(-1, 12, 3, 4);
        constexpr fgm::Quaternion QUAT_B(5, 12, -5, 3);

        /// @test Verify that quaterion addition returns a valid quaternion at compile-time.
        constexpr auto QUAT_SUM = QUAT_A + QUAT_B;
        static_assert(QUAT_SUM.i() == 4);
        static_assert(QUAT_SUM.j() == 24);
        static_assert(QUAT_SUM.k() == -2);
        static_assert(QUAT_SUM.s() == 7);


        /// @test Verify that quaterion subtraction returns a valid quaternion at compile-time.
        constexpr auto QUAT_DIFF = QUAT_A - QUAT_B;
        static_assert(QUAT_DIFF.i() == -6);
        static_assert(QUAT_DIFF.j() == 0);
        static_assert(QUAT_DIFF.k() == 8);
        static_assert(QUAT_DIFF.s() == 1);

        /// @test Verify that quaternion multiplied with a scalar returns a valid quaternion at compile-time.
        constexpr auto QUAT_PROD_SCALAR = QUAT_A * 2;
        static_assert(QUAT_PROD_SCALAR.i() == -2);
        static_assert(QUAT_PROD_SCALAR.j() == 24);
        static_assert(QUAT_PROD_SCALAR.k() == 6);
        static_assert(QUAT_PROD_SCALAR.s() == 8);

        /// @test Verify that scalar multiplied with a quaternion returns a valid quaternion at compile-time.
        constexpr auto QUAT_SCALAR_PROD_QUAT = 2 * QUAT_A;
        static_assert(QUAT_SCALAR_PROD_QUAT.i() == -2);
        static_assert(QUAT_SCALAR_PROD_QUAT.j() == 24);
        static_assert(QUAT_SCALAR_PROD_QUAT.k() == 6);
        static_assert(QUAT_SCALAR_PROD_QUAT.s() == 8);

    } // namespace static_tests


} // namespace



/**************************************
 *           ADDITION TESTS           *
 **************************************/

TYPED_TEST(QuaternionAddition, PlusOperator_ReturnsQuaternionSum)
{
    const fgm::Quaternion result = this->_quatA + this->_quatB;

    EXPECT_QUAT_EQ(this->_expectedSum, result);
}


TYPED_TEST(QuaternionAddition, PlusEqualsOperator_ReturnsSameQuaternionWithSum)
{
    this->_quatA += this->_quatB;

    EXPECT_QUAT_EQ(this->_expectedSum, this->_quatA);
}


TEST(QuaternionAddition, PlusOperator_MixedTypePromotesType)
{
    const fgm::Quaternion quat1(3.0f, 0.0f, -1.0f, 2.0f);
    const fgm::Quaternion quat2(9.0, -5.0, 10.0, 3.0);

    [[maybe_unused]] const fgm::Quaternion result = quat1 + quat2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}



TEST(QuaternionAddition, PlusEqualsOperator_MixedTypeDoesNotPromoteType)
{
    fgm::Quaternion quat1(3.0f, 0.0f, -1.0f, 2.0f);
    [[maybe_unused]] const fgm::Quaternion quat2(9.0, -5.0, 10.0, 3.0);

    static_cast<void>(quat1 += quat2);

    static_assert(std::is_same_v<decltype(quat1)::value_type, float>);
}


TYPED_TEST(QuaternionSubtraction, MinusOperator_ReturnsQuaternionDifference)
{
    const fgm::Quaternion result = this->_quatA - this->_quatB;

    EXPECT_QUAT_EQ(this->_expectedDifference, result);
}


TYPED_TEST(QuaternionSubtraction, MinusEqualsOperator_ReturnsSameQuaternionWithDifference)
{
    this->_quatA -= this->_quatB;

    EXPECT_QUAT_EQ(this->_expectedDifference, this->_quatA);
}


TEST(QuaternionSubtraction, MinusOperator_MixedTypePromotesType)
{
    const fgm::Quaternion quat1(3.0f, 0.0f, -1.0f, 2.0f);
    const fgm::Quaternion quat2(9.0, -5.0, 10.0, 3.0);

    [[maybe_unused]] const fgm::Quaternion result = quat1 - quat2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


TEST(QuaternionSubtraction, MinusEqualsOperator_MixedTypeDoesNotPromoteType)
{
    fgm::Quaternion quat1(3.0f, 0.0f, -1.0f, 2.0f);
    [[maybe_unused]] const fgm::Quaternion quat2(9.0, -5.0, 10.0, 3.0);

    static_cast<void>(quat1 -= quat2);

    static_assert(std::is_same_v<decltype(quat1)::value_type, float>);
}


TEST(QuaternionScalarMultiplication, QuaternionTimesZeroReturnsZeroQuaternion)
{
    const fgm::Quaternion quat(3.0f, 1.0f, 6.0f, 2.0f);

    const fgm::Quaternion result = quat * 0;

    EXPECT_QUAT_CONTAINS(result, 0.0f, 0.0f, 0.0f, 0.0f);
}


TEST(QuaternionScalarMultiplication, QuaternionTimesOneReturnsOriginalQuaternion)
{
    const fgm::Quaternion quat(3.0f, 1.0f, 6.0f, 2.0f);

    const fgm::Quaternion result = quat * 1;

    EXPECT_QUAT_CONTAINS(result, 3.0f, 1.0f, 6.0f, 2.0f);
}


TYPED_TEST(QuaternionScalarMultiplication, QuaternionTimesScalarReturnsScaledQuaternion)
{
    const fgm::Quaternion result = this->_quat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_QUAT_EQ(this->_expectedFloatingVec, result);
    }
    else
    {
        EXPECT_QUAT_EQ(this->_expectedIntegralVec, result);
    }
}


TYPED_TEST(QuaternionScalarMultiplication, ScalarTimesAQuaternionReturnsScaledQuaternion)
{
    const fgm::Quaternion result = this->_scalar * this->_quat;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_QUAT_EQ(this->_expectedFloatingVec, result);
    }
    else
    {
        EXPECT_QUAT_EQ(this->_expectedIntegralVec, result);
    }
}


TYPED_TEST(QuaternionScalarMultiplication, QuaternionTimesEqualScalarIsTheSameQuaternionScaled)
{
    this->_quat *= this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_QUAT_EQ(this->_expectedFloatingVec, this->_quat);
    }
    else
    {
        EXPECT_QUAT_EQ(this->_expectedIntegralVec, this->_quat);
    }
}



TEST(QuaternionScalarMultiplication, MixedTypeScalarMultiplication_PromotesType)
{
    const double scalar = 2.123456789123456;

    fgm::Quaternion quat(3.0f, 0.0f, -1.0f, 2.0f);
    [[maybe_unused]] const auto result = quat * scalar;

    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
}


TEST(QuaternionScalarMultiplication, MixedTypeScalarMultiplicationAssignment_DoesNotPromoteType)
{
    fgm::Quaternion quat(3.0f, 0.0f, -1.0f, 2.0f);
    const double scalar = 5.0;
    quat *= scalar;

    static_assert(std::is_same_v<decltype(quat)::value_type, float>);
}


TEST(QuaternionScalarMultiplication, MixedTypeScalarMultiplicationAssignment_EnsuresMinimalPrecisionLoss)
{
    fgm::Quaternion quat(3, 0, -1, 8);
    const double scalar = 2.5;
    const fgm::Quaternion expected(7, 0, -2, 20);

    quat *= scalar;

    EXPECT_QUAT_EQ(expected, quat);
}


// TODO: Move to death tests separate binary
#ifndef ENABLE_DEBUG_TESTS
// Release mode behaviour

TEST(QuaternionScalarDivision, FloatQuaternionDivisionByZero_ReturnsInfinityQuaternion_InReleaseMode)
{
    const fgm::Quaternion quat(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_QUAT_INF(quat / 0);
}


TEST(QuaternionScalarDivision, DoubleQuaternionDivisionByZero_ReturnsInfinityQuaternion_InReleaseMode)
{
    const fgm::Quaternion quat(1.0, 2.0, 3.0, 4.0);
    EXPECT_QUAT_INF(quat / 0);
}

#else
// Debug Mode behaviour

TYPED_TEST(QuaternionScalarDivision, DivideOperator_ByZeroTriggersAssertionInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_quat / TypeParam(0)), ""); }


TYPED_TEST(QuaternionScalarDivision, DivideEqualsOperator_ByZeroTriggersAssertionInDebugMode)
{
    [[maybe_unused]] fgm::Quaternion newVec = this->_quat;
    EXPECT_DEBUG_DEATH(static_cast<void>(newVec /= TypeParam(0)), "");
}

#endif



TYPED_TEST(QuaternionScalarDivision, ByOneReturnsOriginalQuaternion)
{
    const fgm::Quaternion result = this->_quat / TypeParam(1);

    EXPECT_QUAT_EQ(result, this->_quat);
}


TYPED_TEST(QuaternionScalarDivision, DivideOperator_ReturnsAValidQuaternion)
{
    const fgm::Quaternion result = this->_quat / this->_scalar;

    EXPECT_QUAT_EQ(this->_expectedScaledVec, result);
}


TYPED_TEST(QuaternionScalarDivision, DivideEqualsOperator_ReturnsSameQuaternionInverseScaled)
{
    this->_quat /= this->_scalar;

    EXPECT_QUAT_EQ(this->_expectedScaledVec, this->_quat);
}


TEST(QuaternionScalarDivision, DivideOperator_MixedType_PromotesType)
{
    const fgm::Quaternion quat(15.0, 0.0, -5.0, 10.0);
    const double scalar = 5.0;

    [[maybe_unused]] const auto result = quat / scalar;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


TEST(QuaternionScalarDivision, DivideEqualsOperator_MixedType_DoesNotPromoteType)
{
    fgm::Quaternion quat(15.0f, 0.0f, -5.0f, 10.0f);
    const double scalar = 5.0;

    quat /= scalar;

    static_assert(std::is_same_v<decltype(quat)::value_type, float>);
}


TEST(QuaternionScalarDivision, DivideEqualsOperator_MixedType_ReturnsResultWithMinimalPrecisionLoss)
{
    fgm::Quaternion quat(10, 25, -30, 2);
    const double scalar = 2.5;
    const fgm::Quaternion expected(4, 10, -12, 0);

    quat /= scalar;

    EXPECT_QUAT_EQ(expected, quat);
}






// /**************************************
//  *                                    *
//  *        SAFE DIVISION TESTS         *
//  *                                    *
//  **************************************/
//
// /**
//  * @brief Verify that dividing a quaternion using @ref fgm::Quaternion::safeDiv perform a component-wise divide and
//  *       returns a new quaternion instance.
//  */
// TYPED_TEST(QuaternionScalarDivision, SafeDivide_ReturnsAInverseScaledQuaternion)
// {
//     const auto result = this->_quat.safeDiv(this->_scalar);
//
//     EXPECT_QUAT_EQ(this->_expectedScaledVec, result);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by integral zero using @ref fgm::Quaternion::safeDiv
//  *       perform a component-wise divide and returns a new quaternion instance.
//  */
// TYPED_TEST(QuaternionScalarDivision, SafeDivideByIntegralZero_ReturnsZeroQuaternion)
// {
//     const auto result = this->_quat.safeDiv(0);
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by floating point zero using @ref fgm::Quaternion::safeDiv
//  *       perform a component-wise divide and returns a new quaternion instance.
//  */
// TYPED_TEST(QuaternionScalarDivision, SafeDivideByFloatZero_ReturnsZeroQuaternion)
// {
//     const auto result = this->_quat.safeDiv(0.0f);
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion using static variant of @ref fgm::Quaternion::safeDiv
//  *       perform a component-wise divide and returns a new quaternion instance.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_SafeDivide_ReturnsAInverseScaledQuaternion)
// {
//     const auto result = fgm::Quaternion<TypeParam>::safeDiv(this->_quat, this->_scalar);
//     EXPECT_QUAT_EQ(this->_expectedScaledVec, result);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by integral zero using static variant of @ref fgm::Quaternion::safeDiv
//  *       perform a component-wise divide and returns a new quaternion instance.
//  */
// TEST(QuaternionScalarDivision, StaticWrapper_SafeDivideByIntergralZero_ReturnsZeroQuaternion)
// {
//     const fgm::Quaternion quat(1, 2, 3, 4);
//     EXPECT_VEC_ZERO(fgm::Quaternion<int>::safeDiv(quat, 0));
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by floating point zero using static variant @ref fgm::Quaternion::safeDiv
//  *       perform a component-wise divide and returns a new quaternion instance.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_SafeDivideByFloatZero_ReturnsZeroQuaternion)
// {
//     const auto result = fgm::Quaternion<TypeParam>::safeDiv(this->_quat, 0.0f);
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by NaN using @ref fgm::Quaternion::safeDiv
//  *       returns a zero quaternion.
//  */
// TYPED_TEST(QuaternionScalarDivision, SafeDivideByNaN_ReturnsZeroQuaternion)
// {
//     const auto result = this->_quat.safeDiv(fgm::constants::NaN);
//
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by NaN using static variant of @ref fgm::Quaternion::safeDiv
//  *       returns a zero quaternion.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_SafeDivideByNaN_ReturnsZeroQuaternion)
// {
//     const auto result = fgm::Quaternion<TypeParam>::safeDiv(this->_quat, fgm::constants::INFINITY_F);
//
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**************************************
//  *                                    *
//  *         TRY DIVISION TESTS         *
//  *                                    *
//  **************************************/
//
// /**
//  * @brief Verify that dividing a quaternion using @ref fgm::Quaternion::tryDiv perform a component-wise divide and
//  *       returns a new quaternion instance and sets the flag to @ref fgm::OperationStatus::SUCCESS.
//  */
// TYPED_TEST(QuaternionScalarDivision, TryDivide_ReturnsAInverseScaledQuaternionAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = this->_quat.tryDiv(this->_scalar, flag);
//
//     EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
//     EXPECT_QUAT_EQ(this->_expectedScaledVec, result);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by integral zero using @ref fgm::Quaternion::tryDiv returns zero
//  quaternion and
//  *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
//  */
// TYPED_TEST(QuaternionScalarDivision, TryDivideByIntegralZero_ReturnsZeroQuaternionAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = this->_quat.tryDiv(0, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by floating point zero using @ref fgm::Quaternion::tryDiv returns zero
//  quaternion
//  * and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
//  */
// TYPED_TEST(QuaternionScalarDivision, TryDivideByFloatZero_ReturnsZeroQuaternionAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = this->_quat.tryDiv(0.0, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a NaN quaternion by zero using @ref fgm::Quaternion::tryDiv
//  *       @ref fgm::OperationStatus::NANOPERAND takes precedence over @ref fgm::OperationStatus::NANOPERAND.
//  */
// TEST(QuaternionScalarDivision, TryDivideNaNQuaternionByZero_NaNOperandStatusTakesPrecedence)
// {
//     fgm::OperationStatus flag;
//     [[maybe_unused]] const auto result = fgm::Quaternion<double>::qnan().tryDiv(0, flag);
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by NaN using @ref fgm::Quaternion::tryDiv returns a zero quaternion and
//  *       sets the flag to @ref fgm::OperationStatus::NANOPERAND.
//  */
// TYPED_TEST(QuaternionScalarDivision, TryDivideByNaN_ReturnsZeroQuaternionAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = this->_quat.tryDiv(fgm::constants::NaN, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion using static variant of @ref fgm::Quaternion::tryDiv
//  *       perform a component-wise divide and returns a new quaternion instance and
//  *       sets the flag to @ref fgm::OperationStatus::SUCCESS.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_TryDivide_ReturnsAInverseScaledQuaternionAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = fgm::Quaternion<TypeParam>::tryDiv(this->_quat, this->_scalar, flag);
//
//     EXPECT_QUAT_EQ(this->_expectedScaledVec, result);
//     EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by integral zero using static variant of @ref fgm::Quaternion::tryDiv
//  *       returns zero quaternion and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_TryDivideByIntegralZero_ReturnsZeroQuaternionAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = fgm::Quaternion<TypeParam>::tryDiv(this->_quat, 0, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by floating point zero using static variant of @ref
//  fgm::Quaternion::tryDiv
//  *       returns zero quaternion and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_TryDivideByFloatZero_ReturnsZeroQuaternionAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = fgm::Quaternion<TypeParam>::tryDiv(this->_quat, 0.0, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by floating point zero using static variant of @ref
//  fgm::Quaternion::tryDiv
//  *       returns zero quaternion and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
//  */
// TEST(QuaternionScalarDivision, StaticWrapper_TryDivideNaNQuaternion_ReturnsZeroQuaternionAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = fgm::Quaternion<double>::tryDiv(fgm::Quaternion<double>::qnan(), 3, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a quaternion by NaN using static variant of @ref fgm::Quaternion::tryDiv returns zero
//  quaternion
//  * and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_TryDivideByNaN_ReturnsZeroQuaternionAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = fgm::Quaternion<TypeParam>::tryDiv(this->_quat, fgm::constants::NaN, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**************************************
//  *                                    *
//  *         NaN DIVISION TESTS         *
//  *                                    *
//  **************************************/
//
// /**
//  * @brief Verify that dividing a nan quaternion by a scalar using @ref fgm::Quaternion::safeDiv
//  *       returns quaternion with NaN-components as zero.
//  */
// TEST_P(QuaternionDivisionNaNTests, SafeDiv_ReturnsQuaternionWithNaNComponentsAsZero)
// {
//     const auto& quat = GetParam();
//     EXPECT_VEC_ZERO(quat.safeDiv(3));
// }
//
// /**
//  * @brief Verify that dividing a nan quaternion by a scalar using static variant of @ref fgm::Quaternion::safeDiv
//  *       returns zero quaternion.
//  */
// TEST_P(QuaternionDivisionNaNTests, StaticWrapper_SafeDiv_ReturnsQuaternionWithNaNComponentsAsZero)
// {
//     const auto& quat = GetParam();
//     EXPECT_VEC_ZERO(fgm::Quaternion<float>::safeDiv(quat, 3));
// }
//
//
// /**
//  * @brief Verify that dividing a nan quaternion by a scalar using @ref fgm::Quaternion::tryDiv
//  *       returns zero quaternion and sets flag to OperationStatus::NANOPERAND.
//  */
// TEST_P(QuaternionDivisionNaNTests, TryDiv_ReturnsQuaternionWithNaNComponentsAsZero)
// {
//     const auto& quat = GetParam();
//     fgm::OperationStatus flag;
//     EXPECT_VEC_ZERO(quat.tryDiv(3, flag));
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a nan quaternion by a scalar using static variant of @ref fgm::Quaternion::tryDiv
//  *       returns zero quaternion and sets flag to OperationStatus::NANOPERAND.
//  */
// TEST_P(QuaternionDivisionNaNTests, StaticWrapper_TryDiv_ReturnsQuaternionWithNaNComponentsAsZero)
// {
//     const auto& quat = GetParam();
//     fgm::OperationStatus flag;
//     EXPECT_VEC_ZERO(fgm::Quaternion<float>::tryDiv(quat, 3, flag));
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }
//
// /** @} */
//
//
//
// /**
//  * @addtogroup T_FGM_Quaternion_Negation
//  * @{
//  */
//
// /**
//  * @brief Verify that  @ref fgm::Quaternion unary minus operator inverts each component and
//  *       returns a new quaternion.
//  */
// TYPED_TEST(QuaternionNegation, InvertsTheSignOfEachComponents)
// {
//     const fgm::Quaternion inverted = -this->_quat;
//     EXPECT_QUAT_EQ(this->_expectedInvertedVec, inverted);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion unary minus operator inverts each component of an infinity quaternion. */
// TEST(QuaternionNegation, InvertsSignOfInfinity)
// {
//     const fgm::Quaternion infVec = {
//         fgm::constants::INFINITY_F,
//         -fgm::constants::INFINITY_F,
//         fgm::constants::INFINITY_F,
//         -fgm::constants::INFINITY_F,
//     };
//     const fgm::Quaternion expected = {
//         -fgm::constants::INFINITY_F,
//         fgm::constants::INFINITY_F,
//         -fgm::constants::INFINITY_F,
//         fgm::constants::INFINITY_F,
//     };
//
//     const fgm::Quaternion<float> inverted = -infVec;
//
//     EXPECT_QUAT_EQ(expected, inverted);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion unary minus follows IEEE 754 rules for NaN. */
// TEST(QuaternionNegation, NoOpOnNaNQuaternions)
// {
//     const fgm::Quaternion nanVec = {
//         fgm::constants::NaN,
//         fgm::constants::NaN,
//         fgm::constants::NaN,
//         fgm::constants::NaN,
//     };
//
//     const fgm::Quaternion<float> inverted = -nanVec;
//
//     EXPECT_TRUE(std::isnan(inverted.x()));
//     EXPECT_TRUE(std::isnan(inverted.y()));
//     EXPECT_TRUE(std::isnan(inverted.z()));
//     EXPECT_TRUE(std::isnan(inverted.w()));
// }

/** @} */
