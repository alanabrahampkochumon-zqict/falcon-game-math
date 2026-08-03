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


    // /**
    //  * @brief Test fixture for verifying quaternion multiplication with scalar across different scalar types.
    //  *
    //  * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
    //  */
    // template <typename T>
    // class QuaternionScalarMultiplication: public testing::Test
    // {
    // protected:
    //     fgm::Quaternion<T> _vec;
    //     T _scalar;
    //     fgm::Quaternion<T> _expectedFloatingVec;
    //     fgm::Quaternion<T> _expectedIntegralVec;
    //
    //     void SetUp() override
    //     {
    //         _vec                 = { T(7), T(13), T(29), T(41) };
    //         _scalar              = T(2.123456789123456);
    //         _expectedFloatingVec = { T(14.864197523864192), T(27.604938258604928), T(61.580246884580224),
    //                                  T(87.061728354061696) };
    //         _expectedIntegralVec = { T(14), T(26), T(58), T(82) };
    //     }
    // };
    // TYPED_TEST_SUITE(QuaternionScalarMultiplication, SupportedArithmeticTypes);
    //
    //
    // /**
    //  * @brief Test fixture for verifying quaternion division by a scalar across different scalar types.
    //  *
    //  * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
    //  */
    // template <typename T>
    // class QuaternionScalarDivision: public testing::Test
    // {
    // protected:
    //     fgm::Quaternion<T> _vec;
    //     T _scalar;
    //     fgm::Quaternion<T> _expectedScaledVec;
    //
    //     void SetUp() override
    //     {
    //         _vec               = { T(17), T(31), T(59), T(73) };
    //         _scalar            = T(13);
    //         _expectedScaledVec = { T(1.30769230769230769231), T(2.38461538461538461538), T(4.53846153846153846154),
    //                                T(5.61538461538461538462) };
    //     }
    // };
    // TYPED_TEST_SUITE(QuaternionScalarDivision, SupportedArithmeticTypes);
    //
    //
    // /**
    //  * @brief Test fixture for verifying quaternion negation across different scalar types.
    //  *
    //  * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
    //  */
    // template <typename T>
    // class QuaternionNegation: public testing::Test
    // {
    // protected:
    //     fgm::Quaternion<T> _vec;
    //     fgm::Quaternion<T> _expectedInvertedVec;
    //
    //     void SetUp() override
    //     {
    //         _vec                 = { T(-8), T(0), T(-2), T(5) };
    //         _expectedInvertedVec = { T(8), T(0), T(2), T(-5) };
    //     }
    // };
    // TYPED_TEST_SUITE(QuaternionNegation, SupportedSignedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    /** @brief Verify that vector arithmetic operations are available at compile time. */
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




// /**
//  * @addtogroup T_FGM_Quaternion_Multiplication
//  * @{
//  */
//
// /**************************************
//  *                                    *
//  *     SCALAR MULTIPLICATION TESTS    *
//  *                                    *
//  **************************************/
//
// /** @brief Verify that scalar multiplication by zero returns a zero vector. */
// TEST(QuaternionScalarMultiplication, MultiplicationByZeroReturnsZeroVector)
// {
//     const fgm::Quaternion vec(3.0f, 1.0f, 6.0f, 2.0f);
//
//     const fgm::Quaternion result = vec * 0;
//
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /** @brief Verify that scalar multiplication by one returns original vector. */
// TEST(QuaternionScalarMultiplication, MultiplicationByOneReturnsOriginalVector)
// {
//     const fgm::Quaternion vec(3.0f, 1.0f, 6.0f, 2.0f);
//
//     const fgm::Quaternion result = vec * 1;
//
//     EXPECT_VEC_EQ(vec, result);
// }
//
//
// /**
//  * @brief Verify that the binary multiplication operator (vector * scalar) perform a component-wise (Hadamard)
//  product
//  *       and returns a new vector instance.
//  */
// TYPED_TEST(QuaternionScalarMultiplication, VectorTimesScalarReturnsScaledVector)
// {
//     const fgm::Quaternion result = this->_vec * this->_scalar;
//
//     if (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
//     }
//     else
//     {
//         EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
//     }
// }
//
//
// /**
//  * @brief Verify that the binary multiplication operator (scalar * vector) perform a component-wise (Hadamard)
//  product
//  *       and returns a new vector instance.
//  */
// TYPED_TEST(QuaternionScalarMultiplication, ScalarTimesAVectorReturnsScaledVector)
// {
//     const fgm::Quaternion result = this->_scalar * this->_vec;
//
//     if (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
//     }
//     else
//     {
//         EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
//     }
// }
//
//
// /**
//  * @brief Verify that the compound multiplication assignment operator performs a component-wise (Hadamard) product
//  *       and mutates the vector in-place.
//  */
// TYPED_TEST(QuaternionScalarMultiplication, VectorTimesEqualScalarIsTheSameVectorScaled)
// {
//     this->_vec *= this->_scalar;
//
//     if (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_VEC_EQ(this->_expectedFloatingVec, this->_vec);
//     }
//     else
//     {
//         EXPECT_VEC_EQ(this->_expectedIntegralVec, this->_vec);
//     }
// }
//
//
// /**
//  * @brief Verify that the binary multiplication operator perform automatic type promotion
//  *       to the wider numeric type.
//  */
// TYPED_TEST(QuaternionScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
// {
//     const double scalar = 2.123456789123456;
//
//     [[maybe_unused]] const fgm::Quaternion result = this->_vec * scalar;
//
//     static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
// }
//
//
// /**
//  * @brief Verify that the compound multiplication assignment operator maintains the destination type and
//  *       perform an implicit cast.
//  */
// TEST(QuaternionScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
// {
//     fgm::Quaternion vec(3.0f, 0.0f, -1.0f, 2.0f);
//     const double scalar = 5.0;
//     vec *= scalar;
//
//     static_assert(std::is_same_v<decltype(vec)::value_type, float>);
// }
//
//
// /**
//  * @brief Verify that the compound multiplication operator for mixed types
//  *       ensure minimal precision loss.
//  */
// TEST(QuaternionScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
// {
//     fgm::Quaternion vec(3, 0, -1, 8);
//     const double scalar = 2.5;
//     const fgm::Quaternion expected(7, 0, -2, 20);
//
//     vec *= scalar;
//
//     EXPECT_VEC_EQ(expected, vec);
// }
//
// /** @} */
//
//
//
// /**
//  * @addtogroup T_FGM_Quaternion_Division
//  * @{
//  */
//
// /**************************************
//  *                                    *
//  *        SCALAR DIVISION TESTS       *
//  *                                    *
//  **************************************/
//
// #ifndef ENABLE_DEBUG_TESTS
//
// /**
//  * @brief Verify that dividing a float vector by zero returns an
//  *       infinity vector of float type.
//  */
// TEST(QuaternionScalarDivision, FloatVectorDivisionByZeroReturnsInfinityVector)
// {
//     const fgm::Quaternion vec(1.0f, 2.0f, 3.0f, 4.0f);
//     EXPECT_VEC_INF(vec / 0);
// }
//
//
// /**
//  * @brief Verify that dividing a double vector by zero returns an
//  *       infinity vector of double type.
//  */
// TEST(QuaternionScalarDivision, DoubleVectorDivisionByZeroReturnsInfinityVector)
// {
//     const fgm::Quaternion vec(1.0, 2.0, 3.0, 4.0);
//     EXPECT_VEC_INF(vec / 0);
// }
//
// #endif
//
//
// /** @brief Verify that dividing a vector by one returns the original vector. */
// TYPED_TEST(QuaternionScalarDivision, DivisionByOneReturnsOriginalVector)
// {
//     const fgm::Quaternion result = this->_vec / 1;
//
//     EXPECT_VEC_EQ(result, this->_vec);
// }
//
//
// /**
//  * @brief Verify that the binary division operator (vector / scalar) perform a component-wise divide and
//  *       returns a vector instance.
//  */
// TYPED_TEST(QuaternionScalarDivision, ScalarDivision_ReturnsInverseScaledVector)
// {
//     const fgm::Quaternion result = this->_vec / this->_scalar;
//
//     EXPECT_VEC_EQ(this->_expectedScaledVec, result);
// }
//
//
// /**
//  * @brief Verify that the compound division assignment operator perform a component-wise divide and
//  *       mutates the vector in-place.
//  */
// TYPED_TEST(QuaternionScalarDivision, ScalarDivisionAssignment_ReturnsSameVectorInverseScaled)
// {
//     this->_vec /= this->_scalar;
//
//     EXPECT_VEC_EQ(this->_expectedScaledVec, this->_vec);
// }
//
//
// /**
//  * @brief Verify that the binary division operator perform automatic type promotion
//  *       to the wider numeric type.
//  */
// TEST(QuaternionScalarDivision, MixedType_ScalarDivision_PromotesType)
// {
//     const fgm::Quaternion vec(15.0, 0.0, -5.0, 10.0);
//     const double scalar = 5.0;
//
//     [[maybe_unused]] const fgm::Quaternion result = vec / scalar;
//
//     static_assert(std::is_same_v<decltype(result)::value_type, double>);
// }
//
//
// /**
//  * @brief Verify that the compound division assignment operator maintains the destination type and
//  *       perform an implicit cast.
//  */
// TEST(QuaternionScalarDivision, MixedType_ScalarDivisionAssignment_DoesNotPromoteType)
// {
//     fgm::Quaternion vec(15.0f, 0.0f, -5.0f, 10.0f);
//     const double scalar = 5.0;
//
//     vec /= scalar;
//
//     static_assert(std::is_same_v<decltype(vec)::value_type, float>);
// }
//
//
// /** @brief Verify that the compound division operator for mixed types ensures minimal precision loss. */
// TEST(QuaternionScalarDivision, MixedType_ScalarDivisionAssignment_ReturnsResultWithMinimalPrecisionLoss)
// {
//     fgm::Quaternion vec(10, 25, -30, 2);
//     const double scalar = 2.5;
//     const fgm::Quaternion expected(4, 10, -12, 0);
//
//     vec /= scalar;
//
//     EXPECT_VEC_EQ(expected, vec);
// }
//
//
// #ifdef ENABLE_DEBUG_TESTS
//
// /**
//  * @brief Verify that the binary division assignment operator when dividing a vector by zero,
//  *        triggers assert in debug mode.
//  */
// TYPED_TEST(QuaternionScalarDivision, DivideOperator_ByZeroTriggersAssertInDebugMode)
// { EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec / 0), ""); }
//
//
// /**
//  * @brief Verify that the compound division assignment operator when dividing a vector by zero,
//  *        triggers assert in debug mode.
//  */
// TYPED_TEST(QuaternionScalarDivision, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
// {
//     [[maybe_unused]] fgm::Quaternion newVec = this->_vec;
//     EXPECT_DEBUG_DEATH(static_cast<void>(newVec /= 0), "");
// }
// #endif
//
//
//
// /**************************************
//  *                                    *
//  *        SAFE DIVISION TESTS         *
//  *                                    *
//  **************************************/
//
// /**
//  * @brief Verify that dividing a vector using @ref fgm::Quaternion::safeDiv perform a component-wise divide and
//  *       returns a new vector instance.
//  */
// TYPED_TEST(QuaternionScalarDivision, SafeDivide_ReturnsAInverseScaledVector)
// {
//     const auto result = this->_vec.safeDiv(this->_scalar);
//
//     EXPECT_VEC_EQ(this->_expectedScaledVec, result);
// }
//
//
// /**
//  * @brief Verify that dividing a vector by integral zero using @ref fgm::Quaternion::safeDiv
//  *       perform a component-wise divide and returns a new vector instance.
//  */
// TYPED_TEST(QuaternionScalarDivision, SafeDivideByIntegralZero_ReturnsZeroVector)
// {
//     const auto result = this->_vec.safeDiv(0);
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**
//  * @brief Verify that dividing a vector by floating point zero using @ref fgm::Quaternion::safeDiv
//  *       perform a component-wise divide and returns a new vector instance.
//  */
// TYPED_TEST(QuaternionScalarDivision, SafeDivideByFloatZero_ReturnsZeroVector)
// {
//     const auto result = this->_vec.safeDiv(0.0f);
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**
//  * @brief Verify that dividing a vector using static variant of @ref fgm::Quaternion::safeDiv
//  *       perform a component-wise divide and returns a new vector instance.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_SafeDivide_ReturnsAInverseScaledVector)
// {
//     const auto result = fgm::Quaternion<TypeParam>::safeDiv(this->_vec, this->_scalar);
//     EXPECT_VEC_EQ(this->_expectedScaledVec, result);
// }
//
//
// /**
//  * @brief Verify that dividing a vector by integral zero using static variant of @ref fgm::Quaternion::safeDiv
//  *       perform a component-wise divide and returns a new vector instance.
//  */
// TEST(QuaternionScalarDivision, StaticWrapper_SafeDivideByIntergralZero_ReturnsZeroVector)
// {
//     const fgm::Quaternion vec(1, 2, 3, 4);
//     EXPECT_VEC_ZERO(fgm::Quaternion<int>::safeDiv(vec, 0));
// }
//
//
// /**
//  * @brief Verify that dividing a vector by floating point zero using static variant @ref fgm::Quaternion::safeDiv
//  *       perform a component-wise divide and returns a new vector instance.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_SafeDivideByFloatZero_ReturnsZeroVector)
// {
//     const auto result = fgm::Quaternion<TypeParam>::safeDiv(this->_vec, 0.0f);
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**
//  * @brief Verify that dividing a vector by NaN using @ref fgm::Quaternion::safeDiv
//  *       returns a zero vector.
//  */
// TYPED_TEST(QuaternionScalarDivision, SafeDivideByNaN_ReturnsZeroVector)
// {
//     const auto result = this->_vec.safeDiv(fgm::constants::NaN);
//
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**
//  * @brief Verify that dividing a vector by NaN using static variant of @ref fgm::Quaternion::safeDiv
//  *       returns a zero vector.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_SafeDivideByNaN_ReturnsZeroVector)
// {
//     const auto result = fgm::Quaternion<TypeParam>::safeDiv(this->_vec, fgm::constants::INFINITY_F);
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
//  * @brief Verify that dividing a vector using @ref fgm::Quaternion::tryDiv perform a component-wise divide and
//  *       returns a new vector instance and sets the flag to @ref fgm::OperationStatus::SUCCESS.
//  */
// TYPED_TEST(QuaternionScalarDivision, TryDivide_ReturnsAInverseScaledVectorAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = this->_vec.tryDiv(this->_scalar, flag);
//
//     EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
//     EXPECT_VEC_EQ(this->_expectedScaledVec, result);
// }
//
//
// /**
//  * @brief Verify that dividing a vector by integral zero using @ref fgm::Quaternion::tryDiv returns zero vector and
//  *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
//  */
// TYPED_TEST(QuaternionScalarDivision, TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = this->_vec.tryDiv(0, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a vector by floating point zero using @ref fgm::Quaternion::tryDiv returns zero vector
//  * and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
//  */
// TYPED_TEST(QuaternionScalarDivision, TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = this->_vec.tryDiv(0.0, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a NaN vector by zero using @ref fgm::Quaternion::tryDiv
//  *       @ref fgm::OperationStatus::NANOPERAND takes precedence over @ref fgm::OperationStatus::NANOPERAND.
//  */
// TEST(QuaternionScalarDivision, TryDivideNaNVectorByZero_NaNOperandStatusTakesPrecedence)
// {
//     fgm::OperationStatus flag;
//     [[maybe_unused]] const auto result = fgm::Quaternion<double>::qnan().tryDiv(0, flag);
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a vector by NaN using @ref fgm::Quaternion::tryDiv returns a zero vector and
//  *       sets the flag to @ref fgm::OperationStatus::NANOPERAND.
//  */
// TYPED_TEST(QuaternionScalarDivision, TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = this->_vec.tryDiv(fgm::constants::NaN, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a vector using static variant of @ref fgm::Quaternion::tryDiv
//  *       perform a component-wise divide and returns a new vector instance and
//  *       sets the flag to @ref fgm::OperationStatus::SUCCESS.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_TryDivide_ReturnsAInverseScaledVectorAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = fgm::Quaternion<TypeParam>::tryDiv(this->_vec, this->_scalar, flag);
//
//     EXPECT_VEC_EQ(this->_expectedScaledVec, result);
//     EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a vector by integral zero using static variant of @ref fgm::Quaternion::tryDiv
//  *       returns zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = fgm::Quaternion<TypeParam>::tryDiv(this->_vec, 0, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a vector by floating point zero using static variant of @ref fgm::Quaternion::tryDiv
//  *       returns zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = fgm::Quaternion<TypeParam>::tryDiv(this->_vec, 0.0, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a vector by floating point zero using static variant of @ref fgm::Quaternion::tryDiv
//  *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
//  */
// TEST(QuaternionScalarDivision, StaticWrapper_TryDivideNaNVector_ReturnsZeroVectorAndSetsCorrectFlag)
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
//  * @brief Verify that dividing a vector by NaN using static variant of @ref fgm::Quaternion::tryDiv returns zero
//  vector
//  * and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
//  */
// TYPED_TEST(QuaternionScalarDivision, StaticWrapper_TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     fgm::OperationStatus flag;
//     const auto result = fgm::Quaternion<TypeParam>::tryDiv(this->_vec, fgm::constants::NaN, flag);
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
//  * @brief Verify that dividing a nan vector by a scalar using @ref fgm::Quaternion::safeDiv
//  *       returns vector with NaN-components as zero.
//  */
// TEST_P(QuaternionDivisionNaNTests, SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
// {
//     const auto& vec = GetParam();
//     EXPECT_VEC_ZERO(vec.safeDiv(3));
// }
//
// /**
//  * @brief Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Quaternion::safeDiv
//  *       returns zero vector.
//  */
// TEST_P(QuaternionDivisionNaNTests, StaticWrapper_SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
// {
//     const auto& vec = GetParam();
//     EXPECT_VEC_ZERO(fgm::Quaternion<float>::safeDiv(vec, 3));
// }
//
//
// /**
//  * @brief Verify that dividing a nan vector by a scalar using @ref fgm::Quaternion::tryDiv
//  *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
//  */
// TEST_P(QuaternionDivisionNaNTests, TryDiv_ReturnsVectorWithNaNComponentsAsZero)
// {
//     const auto& vec = GetParam();
//     fgm::OperationStatus flag;
//     EXPECT_VEC_ZERO(vec.tryDiv(3, flag));
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @brief Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Quaternion::tryDiv
//  *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
//  */
// TEST_P(QuaternionDivisionNaNTests, StaticWrapper_TryDiv_ReturnsVectorWithNaNComponentsAsZero)
// {
//     const auto& vec = GetParam();
//     fgm::OperationStatus flag;
//     EXPECT_VEC_ZERO(fgm::Quaternion<float>::tryDiv(vec, 3, flag));
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
//  *       returns a new vector.
//  */
// TYPED_TEST(QuaternionNegation, InvertsTheSignOfEachComponents)
// {
//     const fgm::Quaternion inverted = -this->_vec;
//     EXPECT_VEC_EQ(this->_expectedInvertedVec, inverted);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion unary minus operator inverts each component of an infinity vector. */
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
//     EXPECT_VEC_EQ(expected, inverted);
// }
//
//
// /** @brief Verify that @ref fgm::Quaternion unary minus follows IEEE 754 rules for NaN. */
// TEST(QuaternionNegation, NoOpOnNaNVectors)
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
