/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref fgm::Vec4 arithmetic operator(+, -, *, /) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vec4Addition: public testing::Test
{
protected:
    fgm::Vec4<T> _vecA;
    fgm::Vec4<T> _vecB;
    fgm::Vec4<T> _expectedSum;

    void SetUp() override
    {
        _vecA        = { T(3), T(1), T(6), T(2) };
        _vecB        = { T(-8), T(5), T(-2), T(5) };
        _expectedSum = { T(-5), T(6), T(4), T(7) };
    }
};
/** @brief Test fixture for @ref fgm::Vec4 addition, parameterized by SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec4Addition, SupportedArithmeticTypes);


template <typename T>
class Vec4Subtraction: public testing::Test
{
protected:
    fgm::Vec4<T> _vecA;
    fgm::Vec4<T> _vecB;
    fgm::Vec4<T> _expectedDifference;

    void SetUp() override
    {
        _vecA               = { T(95), T(11), T(-6), T(2) };
        _vecB               = { T(-8), T(5), T(-2), T(-5) };
        _expectedDifference = { T(103), T(6), T(-4), T(7) };
    }
};
/** @brief Test fixture for @ref fgm::Vec4 subtraction, parameterized by SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec4Subtraction, SupportedArithmeticTypes);


template <typename T>
class Vec4ScalarMultiplication: public testing::Test
{
protected:
    fgm::Vec4<T> _vec;
    T _scalar;
    fgm::Vec4<T> _expectedFloatingVec;
    fgm::Vec4<T> _expectedIntegralVec;

    void SetUp() override
    {
        _vec                 = { T(7), T(13), T(29), T(41) };
        _scalar              = T(2.123456789123456);
        _expectedFloatingVec = { T(14.864197523864192), T(27.604938258604928), T(61.580246884580224),
                                 T(87.061728354061696) };
        _expectedIntegralVec = { T(14), T(26), T(58), T(82) };
    }
};
/** @brief Test fixture for @ref fgm::Vec4 scalar multiplication, parameterized by SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec4ScalarMultiplication, SupportedArithmeticTypes);


template <typename T>
class Vec4ScalarDivision: public testing::Test
{
protected:
    fgm::Vec4<T> _vec;
    T _scalar;
    fgm::Vec4<T> _expectedScaledVec;

    void SetUp() override
    {
        _vec               = { T(17), T(31), T(59), T(73) };
        _scalar            = T(13);
        _expectedScaledVec = { T(1.30769230769230769231), T(2.38461538461538461538), T(4.53846153846153846154),
                               T(5.61538461538461538462) };
    }
};
/** @brief Test fixture for @ref fgm::Vec4 division, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec4ScalarDivision, SupportedArithmeticTypes);


template <typename T>
class Vec4Inversion: public testing::Test
{
protected:
    fgm::Vec4<T> _vec;
    fgm::Vec4<T> _expectedInvertedVec;

    void SetUp() override
    {
        _vec                 = { T(-8), T(0), T(-2), T(5) };
        _expectedInvertedVec = { T(8), T(0), T(2), T(-5) };
    }
};
/** @brief Test fixture for @ref fgm::Vec4 inversion, parameterized by @ref SupportedSignedArithmeticTypes. */
TYPED_TEST_SUITE(Vec4Inversion, SupportedSignedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Vec4 division with NaN vectors. */
class Vec4DivisionNaNTests: public testing::TestWithParam<fgm::Vec4<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vec4DivisionTestSuite, Vec4DivisionNaNTests,
                         ::testing::Values(fgm::Vec4<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                                           fgm::Vec4<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                                           fgm::Vec4<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                                           fgm::Vec4<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                                           fgm::Vec4<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                               fgm ::constants::NaN, fgm ::constants::NaN)));



/**
 * @addtogroup T_FGM_Vec4_Addition
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that vector arithmetic operations are available at compile time. */
namespace
{
    constexpr fgm::Vec4 vecA(1, 2, 3, 4);
    constexpr fgm::Vec4 vecB(5, 12, 5, 3);
    constexpr auto sumVec    = vecA + vecB;
    constexpr auto diffVec   = vecB - vecA;
    constexpr auto scaledVec = vecA * 2;
    constexpr auto divVec1   = vecB / 2;
    constexpr auto divVec2   = vecB.safeDiv(2);
    constexpr auto divVec3   = fgm::Vec4<int>::safeDiv(vecB, 2);
    constexpr auto invVec    = -vecA;

    static_assert(sumVec.x() == 6);
    static_assert(sumVec.y() == 14);
    static_assert(sumVec.z() == 8);
    static_assert(sumVec.w() == 7);

    static_assert(diffVec.x() == 4);
    static_assert(diffVec.y() == 10);
    static_assert(diffVec.z() == 2);
    static_assert(diffVec.w() == -1);

    static_assert(scaledVec.x() == 2);
    static_assert(scaledVec.y() == 4);
    static_assert(scaledVec.z() == 6);
    static_assert(scaledVec.w() == 8);

    static_assert(divVec1.x() == 2);
    static_assert(divVec1.y() == 6);
    static_assert(divVec1.z() == 2);
    static_assert(divVec1.w() == 1);

    static_assert(divVec2.x() == 2);
    static_assert(divVec2.y() == 6);
    static_assert(divVec2.z() == 2);
    static_assert(divVec2.w() == 1);

    static_assert(divVec3.x() == 2);
    static_assert(divVec3.y() == 6);
    static_assert(divVec3.z() == 2);
    static_assert(divVec3.w() == 1);

    static_assert(invVec.x() == -1);
    static_assert(invVec.y() == -2);
    static_assert(invVec.z() == -3);
    static_assert(invVec.w() == -4);
} // namespace


/**************************************
 *                                    *
 *           ADDITION TESTS           *
 *                                    *
 **************************************/

/**
 * @brief Verify that the binary addition operator perform a component-wise addition and
 *       returns a new vector instance.
 */
TYPED_TEST(Vec4Addition, PlusOperator_ReturnsVectorSum)
{
    const fgm::Vec4 result = this->_vecA + this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, result);
}


/**
 * @brief Verify that the compound addition assignment operator perform a component-wise addition and
 *       mutates the vector in-place.
 */
TYPED_TEST(Vec4Addition, PlusEqualsOperator_ReturnsSameVectorWithSum)
{
    this->_vecA += this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, this->_vecA);
}


/**
 * @brief Verify that the binary addition operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Vec4Addition, PlusOperator_MixedTypePromotesType)
{
    const fgm::Vec4 vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const fgm::Vec4 vec2(9.0, -5.0, 10.0, 3.0);

    [[maybe_unused]] const fgm::Vec4 result = vec1 + vec2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @brief Verify that the compound addition assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Vec4Addition, PlusEqualsOperator_MixedTypeDoesNotPromoteType)
{
    fgm::Vec4 vec1(3.0f, 0.0f, -1.0f, 2.0f);
    [[maybe_unused]] const fgm::Vec4 vec2(9.0, -5.0, 10.0, 3.0);

    static_cast<void>(vec1 += vec2);

    static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec4_Subtraction
 * @{
 */

/**************************************
 *                                    *
 *          SUBTRACTION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that the binary subtraction operator perform a component-wise subtraction and
 *       returns a new vector instance.
 */
TYPED_TEST(Vec4Subtraction, MinusOperator_ReturnsDifference)
{
    const fgm::Vec4 result = this->_vecA - this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, result);
}


/**
 * @brief Verify that the compound subtraction assignment operator perform a component-wise subtraction
 *       and mutates the vector in-place.
 */
TYPED_TEST(Vec4Subtraction, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_vecA -= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, this->_vecA);
}


/**
 * @brief Verify that the binary subtraction operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Vec4Subtraction, MinusOperator_MixedTypePromotesType)
{
    const fgm::Vec4 vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const fgm::Vec4 vec2(9.0, -5.0, 10.0, 3.0);

    [[maybe_unused]] const fgm::Vec4 result = vec1 - vec2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @brief Verify that the compound subtraction assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Vec4Subtraction, MinusEqualsOperator_MixedTypeDoesNotPromoteType)
{
    fgm::Vec4 vec1(3.0f, 0.0f, -1.0f, 2.0f);
    [[maybe_unused]] const fgm::Vec4 vec2(9.0, -5.0, 10.0, 3.0);

    static_cast<void>(vec1 -= vec2);

    static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec4_Multiplication
 * @{
 */

/**************************************
 *                                    *
 *     SCALAR MULTIPLICATION TESTS    *
 *                                    *
 **************************************/

/** @brief Verify that scalar multiplication by zero returns a zero vector. */
TEST(Vec4ScalarMultiplication, MultiplicationByZeroReturnsZeroVector)
{
    const fgm::Vec4 vec(3.0f, 1.0f, 6.0f, 2.0f);

    const fgm::Vec4 result = vec * 0;

    EXPECT_VEC_ZERO(result);
}


/** @brief Verify that scalar multiplication by one returns original vector. */
TEST(Vec4ScalarMultiplication, MultiplicationByOneReturnsOriginalVector)
{
    const fgm::Vec4 vec(3.0f, 1.0f, 6.0f, 2.0f);

    const fgm::Vec4 result = vec * 1;

    EXPECT_VEC_EQ(vec, result);
}


/**
 * @brief Verify that the binary multiplication operator (vector * scalar) perform a component-wise (Hadamard) product
 *       and returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarMultiplication, VectorTimesScalarReturnsScaledVector)
{
    const fgm::Vec4 result = this->_vec * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
    }
}


/**
 * @brief Verify that the binary multiplication operator (scalar * vector) perform a component-wise (Hadamard) product
 *       and returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarMultiplication, ScalarTimesAVectorReturnsScaledVector)
{
    const fgm::Vec4 result = this->_scalar * this->_vec;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
    }
}


/**
 * @brief Verify that the compound multiplication assignment operator performs a component-wise (Hadamard) product
 *       and mutates the vector in-place.
 */
TYPED_TEST(Vec4ScalarMultiplication, VectorTimesEqualScalarIsTheSameVectorScaled)
{
    this->_vec *= this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingVec, this->_vec);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralVec, this->_vec);
    }
}


/**
 * @brief Verify that the binary multiplication operator perform automatic type promotion
 *       to the wider numeric type.
 */
TYPED_TEST(Vec4ScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Vec4 result = this->_vec * scalar;

    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
}


/**
 * @brief Verify that the compound multiplication assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Vec4ScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Vec4 vec(3.0f, 0.0f, -1.0f, 2.0f);
    const double scalar = 5.0;
    vec *= scalar;

    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
}


/**
 * @brief Verify that the compound multiplication operator for mixed types
 *       ensure minimal precision loss.
 */
TEST(Vec4ScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    fgm::Vec4 vec(3, 0, -1, 8);
    const double scalar = 2.5;
    const fgm::Vec4 expected(7, 0, -2, 20);

    vec *= scalar;

    EXPECT_VEC_EQ(expected, vec);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec4_Division
 * @{
 */

/**************************************
 *                                    *
 *        SCALAR DIVISION TESTS       *
 *                                    *
 **************************************/

#ifndef ENABLE_DEBUG_TESTS

/**
 * @brief Verify that dividing a float vector by zero returns an
 *       infinity vector of float type.
 */
TEST(Vec4ScalarDivision, FloatVectorDivisionByZeroReturnsInfinityVector)
{
    const fgm::Vec4 vec(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_VEC_INF(vec / 0);
}


/**
 * @brief Verify that dividing a double vector by zero returns an
 *       infinity vector of double type.
 */
TEST(Vec4ScalarDivision, DoubleVectorDivisionByZeroReturnsInfinityVector)
{
    const fgm::Vec4 vec(1.0, 2.0, 3.0, 4.0);
    EXPECT_VEC_INF(vec / 0);
}

#endif


/** @brief Verify that dividing a vector by one returns the original vector. */
TYPED_TEST(Vec4ScalarDivision, DivisionByOneReturnsOriginalVector)
{
    const fgm::Vec4 result = this->_vec / 1;

    EXPECT_VEC_EQ(result, this->_vec);
}


/**
 * @brief Verify that the binary division operator (vector / scalar) perform a component-wise divide and
 *       returns a vector instance.
 */
TYPED_TEST(Vec4ScalarDivision, ScalarDivision_ReturnsInverseScaledVector)
{
    const fgm::Vec4 result = this->_vec / this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @brief Verify that the compound division assignment operator perform a component-wise divide and
 *       mutates the vector in-place.
 */
TYPED_TEST(Vec4ScalarDivision, ScalarDivisionAssignment_ReturnsSameVectorInverseScaled)
{
    this->_vec /= this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, this->_vec);
}


/**
 * @brief Verify that the binary division operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Vec4ScalarDivision, MixedType_ScalarDivision_PromotesType)
{
    const fgm::Vec4 vec(15.0, 0.0, -5.0, 10.0);
    const double scalar = 5.0;

    [[maybe_unused]] const fgm::Vec4 result = vec / scalar;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @brief Verify that the compound division assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Vec4ScalarDivision, MixedType_ScalarDivisionAssignment_DoesNotPromoteType)
{
    fgm::Vec4 vec(15.0f, 0.0f, -5.0f, 10.0f);
    const double scalar = 5.0;

    vec /= scalar;

    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
}


/** @brief Verify that the compound division operator for mixed types ensures minimal precision loss. */
TEST(Vec4ScalarDivision, MixedType_ScalarDivisionAssignment_ReturnsResultWithMinimalPrecisionLoss)
{
    fgm::Vec4 vec(10, 25, -30, 2);
    const double scalar = 2.5;
    const fgm::Vec4 expected(4, 10, -12, 0);

    vec /= scalar;

    EXPECT_VEC_EQ(expected, vec);
}


#ifdef ENABLE_DEBUG_TESTS

/**
 * @brief Verify that the binary division assignment operator when dividing a vector by zero,
 *        triggers assert in debug mode.
 */
TYPED_TEST(Vec4ScalarDivision, DivideOperator_ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec / 0), "");
}


/**
 * @brief Verify that the compound division assignment operator when dividing a vector by zero,
 *        triggers assert in debug mode.
 */
TYPED_TEST(Vec4ScalarDivision, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Vec4 newVec = this->_vec;
    EXPECT_DEBUG_DEATH(static_cast<void>(newVec /= 0), "");
}
#endif



/**************************************
 *                                    *
 *        SAFE DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a vector using @ref fgm::Vec4::safeDiv perform a component-wise divide and
 *       returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarDivision, SafeDivide_ReturnsAInverseScaledVector)
{
    const auto result = this->_vec.safeDiv(this->_scalar);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @brief Verify that dividing a vector by integral zero using @ref fgm::Vec4::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarDivision, SafeDivideByIntegralZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0);
    EXPECT_VEC_ZERO(result);
}


/**
 * @brief Verify that dividing a vector by floating point zero using @ref fgm::Vec4::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarDivision, SafeDivideByFloatZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0.0f);
    EXPECT_VEC_ZERO(result);
}


/**
 * @brief Verify that dividing a vector using static variant of @ref fgm::Vec4::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarDivision, StaticWrapper_SafeDivide_ReturnsAInverseScaledVector)
{
    const auto result = fgm::Vec4<TypeParam>::safeDiv(this->_vec, this->_scalar);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @brief Verify that dividing a vector by integral zero using static variant of @ref fgm::Vec4::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TEST(Vec4ScalarDivision, StaticWrapper_SafeDivideByIntergralZero_ReturnsZeroVector)
{
    const fgm::Vec4 vec(1, 2, 3, 4);
    EXPECT_VEC_ZERO(fgm::Vec4<int>::safeDiv(vec, 0));
}


/**
 * @brief Verify that dividing a vector by floating point zero using static variant @ref fgm::Vec4::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarDivision, StaticWrapper_SafeDivideByFloatZero_ReturnsZeroVector)
{
    const auto result = fgm::Vec4<TypeParam>::safeDiv(this->_vec, 0.0f);
    EXPECT_VEC_ZERO(result);
}


/**
 * @brief Verify that dividing a vector by NaN using @ref fgm::Vec4::safeDiv
 *       returns a zero vector.
 */
TYPED_TEST(Vec4ScalarDivision, SafeDivideByNaN_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(fgm::constants::NaN);

    EXPECT_VEC_ZERO(result);
}


/**
 * @brief Verify that dividing a vector by NaN using static variant of @ref fgm::Vec4::safeDiv
 *       returns a zero vector.
 */
TYPED_TEST(Vec4ScalarDivision, StaticWrapper_SafeDivideByNaN_ReturnsZeroVector)
{
    const auto result = fgm::Vec4<TypeParam>::safeDiv(this->_vec, fgm::constants::INFINITY_F);

    EXPECT_VEC_ZERO(result);
}


/**************************************
 *                                    *
 *         TRY DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a vector using @ref fgm::Vec4::tryDiv perform a component-wise divide and
 *       returns a new vector instance and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec4ScalarDivision, TryDivide_ReturnsAInverseScaledVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(this->_scalar, flag);

    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @brief Verify that dividing a vector by integral zero using @ref fgm::Vec4::tryDiv returns zero vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4ScalarDivision, TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a vector by floating point zero using @ref fgm::Vec4::tryDiv returns zero vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4ScalarDivision, TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN vector by zero using @ref fgm::Vec4::tryDiv
 *       @ref fgm::OperationStatus::NANOPERAND takes precedence over @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec4ScalarDivision, TryDivideNaNVectorByZero_NaNOperandStatusTakesPrecedence)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const auto result = fgm::Vec4<double>::qnan().tryDiv(0, flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a vector by NaN using @ref fgm::Vec4::tryDiv returns a zero vector and
 *       sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TYPED_TEST(Vec4ScalarDivision, TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(fgm::constants::NaN, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a vector using static variant of @ref fgm::Vec4::tryDiv
 *       perform a component-wise divide and returns a new vector instance and
 *       sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec4ScalarDivision, StaticWrapper_TryDivide_ReturnsAInverseScaledVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec4<TypeParam>::tryDiv(this->_vec, this->_scalar, flag);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a vector by integral zero using static variant of @ref fgm::Vec4::tryDiv
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4ScalarDivision, StaticWrapper_TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec4<TypeParam>::tryDiv(this->_vec, 0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a vector by floating point zero using static variant of @ref fgm::Vec4::tryDiv
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4ScalarDivision, StaticWrapper_TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec4<TypeParam>::tryDiv(this->_vec, 0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a vector by floating point zero using static variant of @ref fgm::Vec4::tryDiv
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec4ScalarDivision, StaticWrapper_TryDivideNaNVector_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec4<double>::tryDiv(fgm::Vec4<double>::qnan(), 3, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a vector by NaN using static variant of @ref fgm::Vec4::tryDiv returns zero vector
 * and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TYPED_TEST(Vec4ScalarDivision, StaticWrapper_TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec4<TypeParam>::tryDiv(this->_vec, fgm::constants::NaN, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**************************************
 *                                    *
 *         NaN DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a nan vector by a scalar using @ref fgm::Vec4::safeDiv
 *       returns vector with NaN-components as zero.
 */
TEST_P(Vec4DivisionNaNTests, SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(vec.safeDiv(3));
}

/**
 * @brief Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Vec4::safeDiv
 *       returns zero vector.
 */
TEST_P(Vec4DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(fgm::Vec4<float>::safeDiv(vec, 3));
}


/**
 * @brief Verify that dividing a nan vector by a scalar using @ref fgm::Vec4::tryDiv
 *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
 */
TEST_P(Vec4DivisionNaNTests, TryDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(vec.tryDiv(3, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Vec4::tryDiv
 *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
 */
TEST_P(Vec4DivisionNaNTests, StaticWrapper_TryDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec4<float>::tryDiv(vec, 3, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec4_Inversion
 * @{
 */

/**
 * @brief Verify that  @ref fgm::Vec4 unary minus operator inverts each component and
 *       returns a new vector.
 */
TYPED_TEST(Vec4Inversion, InvertsTheSignOfEachComponents)
{
    const fgm::Vec4 inverted = -this->_vec;
    EXPECT_VEC_EQ(this->_expectedInvertedVec, inverted);
}


/** @brief Verify that @ref fgm::Vec4 unary minus operator inverts each component of an infinity vector. */
TEST(Vec4Inversion, InvertsSignOfInfinity)
{
    const fgm::Vec4 infVec = {
        fgm::constants::INFINITY_F,
        -fgm::constants::INFINITY_F,
        fgm::constants::INFINITY_F,
        -fgm::constants::INFINITY_F,
    };
    const fgm::Vec4 expected = {
        -fgm::constants::INFINITY_F,
        fgm::constants::INFINITY_F,
        -fgm::constants::INFINITY_F,
        fgm::constants::INFINITY_F,
    };

    const fgm::Vec4<float> inverted = -infVec;

    EXPECT_VEC_EQ(expected, inverted);
}


/** @brief Verify that @ref fgm::Vec4 unary minus follows IEEE 754 rules for NaN. */
TEST(Vec4Inversion, NoOpOnNaNVectors)
{
    const fgm::Vec4 nanVec = {
        fgm::constants::NaN,
        fgm::constants::NaN,
        fgm::constants::NaN,
        fgm::constants::NaN,
    };

    const fgm::Vec4<float> inverted = -nanVec;

    EXPECT_TRUE(std::isnan(inverted.x()));
    EXPECT_TRUE(std::isnan(inverted.y()));
    EXPECT_TRUE(std::isnan(inverted.z()));
    EXPECT_TRUE(std::isnan(inverted.w()));
}

/** @} */
