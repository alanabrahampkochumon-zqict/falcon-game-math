/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vec2 arithmetic operator(+, -, *, /) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"


/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vec2Addition: public testing::Test
{
protected:
    fgm::Vec2<T> _vecA;
    fgm::Vec2<T> _vecB;
    fgm::Vec2<T> _expectedSum;

    void SetUp() override
    {
        _vecA        = { T(3), T(1) };
        _vecB        = { T(-8), T(5) };
        _expectedSum = { T(-5), T(6) };
    }
};

/** @brief Test fixture for @ref fgm::Vec2 addition, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec2Addition, SupportedArithmeticTypes);


template <typename T>
class Vec2Subtraction: public testing::Test
{
protected:
    fgm::Vec2<T> _vecA;
    fgm::Vec2<T> _vecB;
    fgm::Vec2<T> _expectedDifference;

    void SetUp() override
    {
        _vecA               = { T(95), T(11) };
        _vecB               = { T(-8), T(5) };
        _expectedDifference = { T(103), T(6) };
    }
};

/** @brief Test fixture for @ref fgm::Vec2 subtraction, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec2Subtraction, SupportedArithmeticTypes);


template <typename T>
class Vec2ScalarMultiplication: public testing::Test
{
protected:
    fgm::Vec2<T> _vec;
    T _scalar;
    fgm::Vec2<T> _expectedFloatingVec;
    fgm::Vec2<T> _expectedIntegralVec;

    void SetUp() override
    {
        _vec                 = { T(7), T(13) };
        _scalar              = T(2.123456789123456);
        _expectedFloatingVec = { T(14.864197523864192), T(27.604938258604928) };
        _expectedIntegralVec = { T(14), T(26) };
    }
};

/** @brief Test fixture for @ref fgm::Vec2 scalar multiplication, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec2ScalarMultiplication, SupportedArithmeticTypes);


template <typename T>
class Vec2ScalarDivision: public testing::Test
{
protected:
    fgm::Vec2<T> _vec;
    T _scalar;
    fgm::Vec2<T> _expectedScaledVec;

    void SetUp() override
    {
        _vec               = { T(17), T(31) };
        _scalar            = T(13);
        _expectedScaledVec = { T(1.30769230769230769231), T(2.38461538461538461538) };
    }
};

/** @brief Test fixture for @ref fgm::Vec2 division, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec2ScalarDivision, SupportedArithmeticTypes);


template <typename T>
class Vec2Inversion: public testing::Test
{
protected:
    fgm::Vec2<T> _vec;
    fgm::Vec2<T> _expectedInvertedVec;

    void SetUp() override
    {
        _vec                 = { T(-8), T(0) };
        _expectedInvertedVec = { T(8), T(0) };
    }
};

/** @brief Test fixture for @ref fgm::Vec2 inversion, parameterized by @ref SupportedSignedArithmeticTypes. */
TYPED_TEST_SUITE(Vec2Inversion, SupportedSignedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Vec2 division with NaN vectors. */
class Vec2DivisionNaNTests: public testing::TestWithParam<fgm::Vec2<float>>
{};

INSTANTIATE_TEST_SUITE_P(Vec2DivisionTestSuite, Vec2DivisionNaNTests,
                         ::testing::Values(fgm::Vec2<float>(fgm::constants::NaN, 3.0f),
                                           fgm::Vec2<float>(3.0f, fgm::constants::NaN),
                                           fgm::Vec2<float>(fgm ::constants::NaN, fgm::constants::NaN)));


/**
 * @addtogroup T_FGM_Vec2_Addition
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
    constexpr fgm::Vec2 vecA(1, 2);
    constexpr fgm::Vec2 vecB(3, 5);
    constexpr auto sumVec    = vecA + vecB;
    constexpr auto diffVec   = vecB - vecA;
    constexpr auto scaledVec = vecA * 2;
    constexpr auto divVec1   = vecB / 2;
    constexpr auto divVec2   = vecB.safeDiv(2);
    constexpr auto divVec3   = fgm::Vec2<int>::safeDiv(vecB, 2);
    constexpr auto invVec    = -vecA;

    static_assert(sumVec.x() == 4);
    static_assert(sumVec.y() == 7);

    static_assert(diffVec.x() == 2);
    static_assert(diffVec.y() == 3);

    static_assert(scaledVec.x() == 2);
    static_assert(scaledVec.y() == 4);

    static_assert(divVec1.x() == 1);
    static_assert(divVec1.y() == 2);

    static_assert(divVec2.x() == 1);
    static_assert(divVec2.y() == 2);

    static_assert(divVec3.x() == 1);
    static_assert(divVec3.y() == 2);

    static_assert(invVec.x() == -1);
    static_assert(invVec.y() == -2);
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
TYPED_TEST(Vec2Addition, PlusOperator_ReturnsVectorSum)
{
    const fgm::Vec2 result = this->_vecA + this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, result);
}


/**
 * @brief Verify that the compound addition assignment operator perform a component-wise addition and
 *       mutates the vector in-place.
 */
TYPED_TEST(Vec2Addition, PlusEqualsOperator_ReturnsSameVectorWithSum)
{
    this->_vecA += this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, this->_vecA);
}


/**
 * @brief Verify that the binary addition operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Vec2Addition, PlusOperator_MixedTypePromotesType)
{
    const fgm::Vec2 vec1(3.0f, -1.0f);
    const fgm::Vec2 vec2(9.0, 10.0);

    [[maybe_unused]] const fgm::Vec2 result = vec1 + vec2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @brief Verify that the compound addition assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Vec2Addition, PlusEqualsOperator_MixedTypeDoesNotPromoteType)
{
    fgm::Vec2 vec1(3.0f, -1.0f);
    [[maybe_unused]] const fgm::Vec2 vec2(9.0, 10.0);

    static_cast<void>(vec1 += vec2);

    static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
}

/** @} */


/**
 * @addtogroup T_FGM_Vec2_Subtraction
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
TYPED_TEST(Vec2Subtraction, MinusOperator_ReturnsDifference)
{
    const fgm::Vec2 result = this->_vecA - this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, result);
}


/**
 * @brief Verify that the compound subtraction assignment operator perform a component-wise subtraction
 *       and mutates the vector in-place.
 */
TYPED_TEST(Vec2Subtraction, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_vecA -= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, this->_vecA);
}


/**
 * @brief Verify that the binary subtraction operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Vec2Subtraction, MinusOperator_MixedTypePromotesType)
{
    const fgm::Vec2 vec1(3.0f, -1.0f);
    const fgm::Vec2 vec2(9.0, 10.0);

    [[maybe_unused]] const fgm::Vec2 result = vec1 - vec2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @brief Verify that the compound subtraction assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Vec2Subtraction, MinusEqualsOperator_MixedTypeDoesNotPromoteType)
{
    fgm::Vec2 vec1(3.0f, -1.0f);
    [[maybe_unused]] const fgm::Vec2 vec2(9.0, 10.0);

    static_cast<void>(vec1 -= vec2);

    static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
}

/** @} */


/**
 * @addtogroup T_FGM_Vec2_Multiplication
 * @{
 */

/**************************************
 *                                    *
 *     SCALAR MULTIPLICATION TESTS    *
 *                                    *
 **************************************/

/** @brief Verify that scalar multiplication by zero returns a zero vector. */
TEST(Vec2ScalarMultiplication, MultiplicationByZeroReturnsZeroVector)
{
    const fgm::Vec2 vec(3.0f, 6.0f);

    const fgm::Vec2 result = vec * 0;

    EXPECT_VEC_ZERO(result);
}


/** @brief Verify that scalar multiplication by one returns original vector. */
TEST(Vec2ScalarMultiplication, MultiplicationByOneReturnsOriginalVector)
{
    const fgm::Vec2 vec(3.0f, 6.0f);

    const fgm::Vec2 result = vec * 1;

    EXPECT_VEC_EQ(vec, result);
}


/**
 * @brief Verify that the binary multiplication operator (vector * scalar) perform a component-wise (Hadamard) product
 *       and returns a new vector instance.
 */
TYPED_TEST(Vec2ScalarMultiplication, VectorTimesScalarReturnsScaledVector)
{
    const fgm::Vec2 result = this->_vec * this->_scalar;

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
TYPED_TEST(Vec2ScalarMultiplication, ScalarTimesAVectorReturnsScaledVector)
{
    const fgm::Vec2 result = this->_scalar * this->_vec;

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
TYPED_TEST(Vec2ScalarMultiplication, VectorTimesEqualScalarIsTheSameVectorScaled)
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
TYPED_TEST(Vec2ScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Vec2 result = this->_vec * scalar;

    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
}


/**
 * @brief Verify that the compound multiplication assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Vec2ScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Vec2 vec(3.0f, -1.0f);
    const double scalar = 5.0;
    vec *= scalar;

    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
}


/**
 * @brief Verify that the compound multiplication operator for mixed types
 *       ensure minimal precision loss.
 */
TEST(Vec2ScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    fgm::Vec2 vec(3, -1);
    const double scalar = 2.5;
    const fgm::Vec2 expected(7, -2);

    vec *= scalar;

    EXPECT_VEC_EQ(expected, vec);
}

/** @} */


/**
 * @addtogroup T_FGM_Vec2_Division
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
TEST(Vec2ScalarDivision, FloatVectorDivisionByZeroReturnsInfinityVector)
{
    const fgm::Vec2 vec(1.0f, 3.0f);
    EXPECT_VEC_INF(vec / 0);
}


/**
 * @brief Verify that dividing a double vector by zero returns an
 *       infinity vector of double type.
 */
TEST(Vec2ScalarDivision, DoubleVectorDivisionByZeroReturnsInfinityVector)
{
    const fgm::Vec2 vec(1.0, 3.0);
    EXPECT_VEC_INF(vec / 0);
}
#endif


/** @brief Verify that dividing a vector by one returns the original vector. */
TYPED_TEST(Vec2ScalarDivision, DivisionByOneReturnsOriginalVector)
{
    const fgm::Vec2 result = this->_vec / 1;

    EXPECT_VEC_EQ(result, this->_vec);
}


/**
 * @brief Verify that the binary division operator (vector / scalar) perform a component-wise divide and
 *       returns a vector instance.
 */
TYPED_TEST(Vec2ScalarDivision, ScalarDivision_ReturnsInverseScaledVector)
{
    const fgm::Vec2 result = this->_vec / this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @brief Verify that the compound division assignment operator perform a component-wise divide and
 *       mutates the vector in-place.
 */
TYPED_TEST(Vec2ScalarDivision, ScalarDivisionAssignment_ReturnsSameVectorInverseScaled)
{
    this->_vec /= this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, this->_vec);
}


/**
 * @brief Verify that the binary division operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Vec2ScalarDivision, MixedType_ScalarDivision_PromotesType)
{
    const fgm::Vec2 vec(15.0, -5.0);
    const double scalar = 5.0;

    [[maybe_unused]] const fgm::Vec2 result = vec / scalar;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @brief Verify that the compound division assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Vec2ScalarDivision, MixedType_ScalarDivisionAssignment_DoesNotPromoteType)
{
    fgm::Vec2 vec(15.0f, -5.0f);
    const double scalar = 5.0;

    vec /= scalar;

    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
}


/** @brief Verify that the compound division operator for mixed types ensures minimal precision loss. */
TEST(Vec2ScalarDivision, MixedType_ScalarDivisionAssignment_ReturnsResultWithMinimalPrecisionLoss)
{
    fgm::Vec2 vec(10, -30);
    const double scalar = 2.5;
    const fgm::Vec2 expected(4, -12);

    vec /= scalar;

    EXPECT_VEC_EQ(expected, vec);
}


#ifdef ENABLE_DEBUG_TESTS

/**
 * @brief Verify that the binary division assignment operator when dividing a vector by zero,
 *        triggers assert in debug mode.
 */
TYPED_TEST(Vec2ScalarDivision, DivideOperator_ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec / 0), "");
}


/**
 * @brief Verify that the compound division assignment operator when dividing a vector by zero,
 *        triggers assert in debug mode.
 */
TYPED_TEST(Vec2ScalarDivision, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Vec2 newVec = this->_vec;
    EXPECT_DEBUG_DEATH(static_cast<void>(newVec /= 0), "");
}
#endif



/**************************************
 *                                    *
 *        SAFE DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a vector using @ref fgm::Vec2::safeDiv perform a component-wise divide and
 *       returns a new vector instance.
 */
TYPED_TEST(Vec2ScalarDivision, SafeDivide_ReturnsAInverseScaledVector)
{
    const auto result = this->_vec.safeDiv(this->_scalar);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @brief Verify that dividing a vector by integral zero using @ref fgm::Vec2::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TYPED_TEST(Vec2ScalarDivision, SafeDivideByIntegralZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0);
    EXPECT_VEC_ZERO(result);
}


/**
 * @brief Verify that dividing a vector by floating point zero using @ref fgm::Vec2::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TYPED_TEST(Vec2ScalarDivision, SafeDivideByFloatZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0.0f);
    EXPECT_VEC_ZERO(result);
}


/**
 * @brief Verify that dividing a vector using static variant of @ref fgm::Vec2::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TYPED_TEST(Vec2ScalarDivision, StaticWrapper_SafeDivide_ReturnsAInverseScaledVector)
{
    const auto result = fgm::Vec2<TypeParam>::safeDiv(this->_vec, this->_scalar);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @brief Verify that dividing a vector by integral zero using static variant of @ref fgm::Vec2::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TEST(Vec2ScalarDivision, StaticWrapper_SafeDivideByIntergralZero_ReturnsZeroVector)
{
    const fgm::Vec2 vec(1, 3);
    EXPECT_VEC_ZERO(fgm::Vec2<int>::safeDiv(vec, 0));
}


/**
 * @brief Verify that dividing a vector by floating point zero using static variant @ref fgm::Vec2::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TYPED_TEST(Vec2ScalarDivision, StaticWrapper_SafeDivideByFloatZero_ReturnsZeroVector)
{
    const auto result = fgm::Vec2<TypeParam>::safeDiv(this->_vec, 0.0f);
    EXPECT_VEC_ZERO(result);
}


/**
 * @brief Verify that dividing a vector by NaN using @ref fgm::Vec2::safeDiv
 *       returns a zero vector.
 */
TYPED_TEST(Vec2ScalarDivision, SafeDivideByNaN_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(fgm::constants::NaN);

    EXPECT_VEC_ZERO(result);
}


/**
 * @brief Verify that dividing a vector by NaN using static variant of @ref fgm::Vec2::safeDiv
 *       returns a zero vector.
 */
TYPED_TEST(Vec2ScalarDivision, StaticWrapper_SafeDivideByNaN_ReturnsZeroVector)
{
    const auto result = fgm::Vec2<TypeParam>::safeDiv(this->_vec, fgm::constants::INFINITY_F);

    EXPECT_VEC_ZERO(result);
}


/**************************************
 *                                    *
 *         TRY DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a vector using @ref fgm::Vec2::tryDiv perform a component-wise divide and
 *       returns a new vector instance and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2ScalarDivision, TryDivide_ReturnsAInverseScaledVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(this->_scalar, flag);

    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @brief Verify that dividing a vector by integral zero using @ref fgm::Vec2::tryDiv returns zero vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2ScalarDivision, TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a vector by floating point zero using @ref fgm::Vec2::tryDiv returns zero vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2ScalarDivision, TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN vector by zero using @ref fgm::Vec2::tryDiv
 *       @ref fgm::OperationStatus::NANOPERAND takes precedence over @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec2ScalarDivision, TryDivideNaNVectorByZero_NaNOperandStatusTakesPrecedence)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const auto result = fgm::Vec2<double>::qnan().tryDiv(0, flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a vector by NaN using @ref fgm::Vec2::tryDiv returns a zero vector and
 *       sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TYPED_TEST(Vec2ScalarDivision, TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(fgm::constants::NaN, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a vector using static variant of @ref fgm::Vec2::tryDiv
 *       perform a component-wise divide and returns a new vector instance and
 *       sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2ScalarDivision, StaticWrapper_TryDivide_ReturnsAInverseScaledVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec2<TypeParam>::tryDiv(this->_vec, this->_scalar, flag);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a vector by integral zero using static variant of @ref fgm::Vec2::tryDiv
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2ScalarDivision, StaticWrapper_TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec2<TypeParam>::tryDiv(this->_vec, 0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a vector by floating point zero using static variant of @ref fgm::Vec2::tryDiv
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2ScalarDivision, StaticWrapper_TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec2<TypeParam>::tryDiv(this->_vec, 0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a vector by floating point zero using static variant of @ref fgm::Vec2::tryDiv
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec2ScalarDivision, StaticWrapper_TryDivideNaNVector_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec2<double>::tryDiv(fgm::Vec2<double>::qnan(), 3, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a vector by NaN using static variant of @ref fgm::Vec2::tryDiv returns zero vector
 * and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TYPED_TEST(Vec2ScalarDivision, StaticWrapper_TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec2<TypeParam>::tryDiv(this->_vec, fgm::constants::NaN, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**************************************
 *                                    *
 *         NaN DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a nan vector by a scalar using @ref fgm::Vec2::safeDiv
 *       returns vector with NaN-components as zero.
 */
TEST_P(Vec2DivisionNaNTests, SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(vec.safeDiv(3));
}

/**
 * @brief Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Vec2::safeDiv
 *       returns zero vector.
 */
TEST_P(Vec2DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(fgm::Vec2<float>::safeDiv(vec, 3));
}


/**
 * @brief Verify that dividing a nan vector by a scalar using @ref fgm::Vec2::tryDiv
 *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
 */
TEST_P(Vec2DivisionNaNTests, TryDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(vec.tryDiv(3, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Vec2::tryDiv
 *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
 */
TEST_P(Vec2DivisionNaNTests, StaticWrapper_TryDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec2<float>::tryDiv(vec, 3, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */


/**
 * @addtogroup T_FGM_Vec2_Inversion
 * @{
 */

/**
 * @brief Verify that  @ref fgm::Vec2 unary minus operator inverts each component and
 * returns a new vector.
 */
TYPED_TEST(Vec2Inversion, InvertsTheSignOfEachComponents)
{
    const fgm::Vec2 inverted = -this->_vec;
    EXPECT_VEC_EQ(this->_expectedInvertedVec, inverted);
}


/** @brief Verify that @ref fgm::Vec2 unary minus operator inverts each component of an infinity vector. */
TEST(Vec2Inversion, InvertsSignOfInfinity)
{
    const fgm::Vec2 infVec = {
        fgm::constants::INFINITY_F,
        -fgm::constants::INFINITY_F,
    };
    const fgm::Vec2 expected = {
        -fgm::constants::INFINITY_F,
        fgm::constants::INFINITY_F,
    };

    const fgm::Vec2<float> inverted = -infVec;

    EXPECT_VEC_EQ(expected, inverted);
}


/** @brief Verify that @ref fgm::Vec2 unary minus follows IEEE 754 rules for NaN. */
TEST(Vec2Inversion, NoOpOnNaNVectors)
{
    const fgm::Vec2 nanVec = {
        fgm::constants::NaN,
        fgm::constants::NaN,
    };

    const fgm::Vec2<float> inverted = -nanVec;

    EXPECT_TRUE(std::isnan(inverted.x()));
    EXPECT_TRUE(std::isnan(inverted.y()));
}

/** @} */
