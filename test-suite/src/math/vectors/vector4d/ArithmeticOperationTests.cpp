/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref fgm::Vector4D arithmetic operator(+, -, *, /) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;


/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector4DAddition: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> _vecA;
    fgm::Vector4D<T> _vecB;
    fgm::Vector4D<T> _expectedSum;

    void SetUp() override
    {
        _vecA = { T(3), T(1), T(6), T(2) };
        _vecB = { T(-8), T(5), T(-2), T(5) };
        _expectedSum = { T(-5), T(6), T(4), T(7) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D addition, parameterized by SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector4DAddition, SupportedArithmeticTypes);


template <typename T>
class Vector4DSubtraction: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> _vecA;
    fgm::Vector4D<T> _vecB;
    fgm::Vector4D<T> _expectedDifference;

    void SetUp() override
    {
        _vecA = { T(95), T(11), T(-6), T(2) };
        _vecB = { T(-8), T(5), T(-2), T(-5) };
        _expectedDifference = { T(103), T(6), T(-4), T(7) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D subtraction, parameterized by SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector4DSubtraction, SupportedArithmeticTypes);


template <typename T>
class Vector4DScalarMultiplication: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> _vec;
    T _scalar;
    fgm::Vector4D<T> _expectedFloatingVec;
    fgm::Vector4D<T> _expectedIntegralVec;

    void SetUp() override
    {
        _vec = { T(7), T(13), T(29), T(41) };
        _scalar = T(2.123456789123456);
        _expectedFloatingVec = { T(14.864197523864192), T(27.604938258604928), T(61.580246884580224),
                                 T(87.061728354061696) };
        _expectedIntegralVec = { T(14), T(26), T(58), T(82) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D scalar multiplication, parameterized by SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector4DScalarMultiplication, SupportedArithmeticTypes);


template <typename T>
class Vector4DScalarDivision: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> _vec;
    T _scalar;
    fgm::Vector4D<T> _expectedScaledVec;

    void SetUp() override
    {
        _vec = { T(17), T(31), T(59), T(73) };
        _scalar = T(13);
        _expectedScaledVec = { T(1.30769230769230769231), T(2.38461538461538461538), T(4.53846153846153846154),
                               T(5.61538461538461538462) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D division, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector4DScalarDivision, SupportedArithmeticTypes);


template <typename T>
class Vector4DInversion: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> _vec;
    fgm::Vector4D<T> _expectedInvertedVec;

    void SetUp() override
    {
        _vec = { T(-8), T(0), T(-2), T(5) };
        _expectedInvertedVec = { T(8), T(0), T(2), T(-5) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D inversion, parameterized by @ref SupportedSignedArithmeticTypes */
TYPED_TEST_SUITE(Vector4DInversion, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Addition
 * @{
 */

/**************************************
 *                                    *
 *           ADDITION TESTS           *
 *                                    *
 **************************************/

/**
 * @test Verify that @ref fgm::Vector4D binary addition operator performs a component-wise sum and returns a new @ref
 * fgm::Vector4D instance.
 */
TYPED_TEST(Vector4DAddition, PlusOperator_ReturnsVectorSum)
{
    const fgm::Vector4D result = this->_vecA + this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, result);
}


/**
 * @test Verify that @ref fgm::Vector4D compound addition assignment operator performs a component-wise sum and mutates
 * the
 *       @ref fgm::Vector4D in-place.
 */
TYPED_TEST(Vector4DAddition, PlusEqualsOperator_ReturnsSameVectorWithSum)
{
    this->_vecA += this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, this->_vecA);
}


/** @test Verify that @ref fgm::Vector4D binary addition operator performs automatic type promotion to the wider numeric
 * type. */
TEST(Vector4DAddition, MixedTypeAdditionPromotesType)
{
    constexpr fgm::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    constexpr fgm::Vector4D vec2(9.0, -5.0, 10.0, 3.0);

    [[maybe_unused]] constexpr fgm::Vector4D result = vec1 + vec2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @test Verify that @ref fgm::Vector4D compound addition assignment operator maintains the destination type and
 * performs an implicit cast.
 */
TEST(Vector4DAddition, MixedTypeAdditionAssignmentDoesNotPromoteType)
{
    fgm::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    constexpr fgm::Vector4D vec2(9.0, -5.0, 10.0, 3.0);

    vec1 += vec2;

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
 * @test Verify that @ref fgm::Vector4D binary subtraction operator performs a component-wise difference and returns a
 * new
 *       @ref fgm::Vector4D instance.
 */
TYPED_TEST(Vector4DSubtraction, MinusOperator_ReturnsDifference)
{
    const fgm::Vector4D result = this->_vecA - this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, result);
}


/**
 * @test Verify that @ref fgm::Vector4D compound subtraction assignment operator performs a component-wise difference
 * and mutates the
 *       @ref fgm::Vector4D in-place.
 */
TYPED_TEST(Vector4DSubtraction, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_vecA -= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, this->_vecA);
}


/** @test Verify that @ref fgm::Vector4D binary subtraction operator performs automatic type promotion to the wider
 * numeric type. */
TEST(Vector4DSubtraction, MixedTypeSubtractionPromotesType)
{
    constexpr fgm::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    constexpr fgm::Vector4D vec2(9.0, -5.0, 10.0, 3.0);

    [[maybe_unused]] constexpr fgm::Vector4D result = vec1 - vec2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @test Verify that @ref fgm::Vector4D compound subtraction assignment operator maintains the destination type and
 * performs an implicit cast.
 */
TEST(Vector4DSubtraction, MixedTypeSubtractionAssignmentDoesNotPromoteType)
{
    fgm::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    constexpr fgm::Vector4D vec2(9.0, -5.0, 10.0, 3.0);

    vec1 -= vec2;

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

/** @test Verify that @ref fgm::Vector4D binary multiplication of a @ref fgm::Vector4D by zero scalar returns a
 * zero-vector. */
TEST(Vector4DScalarMultiplication, MultiplicationByZeroReturnsZeroVector)
{
    constexpr fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    constexpr fgm::Vector4D result = vec * 0;

    EXPECT_VEC_ZERO(result);
}


/** @test Verify that @ref fgm::Vector4D binary multiplication of a @ref fgm::Vector4D by one returns the original
 * vector. */
TEST(Vector4DScalarMultiplication, MultiplicationByOneReturnsOriginalVector)
{
    constexpr fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    constexpr fgm::Vector4D result = vec * 1;

    EXPECT_VEC_EQ(vec, result);
}


/**
 * @test Verify that @ref fgm::Vector4D binary multiplication operator (vector * scalar) performs a component-wise
 * (Hadamard) product and returns a new @ref fgm::Vector4D instance.
 */
TYPED_TEST(Vector4DScalarMultiplication, VectorTimesScalarReturnsScaledVector)
{
    const fgm::Vector4D result = this->_vec * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
    else
        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
}


/**
 * @test Verify that @ref fgm::Vector4D binary multiplication operator (scalar * vector) performs a component-wise
 * (Hadamard) product and returns a new @ref fgm::Vector4D instance.
 */
TYPED_TEST(Vector4DScalarMultiplication, ScalarTimesAVectorReturnsScaledVector)
{
    const fgm::Vector4D result = this->_scalar * this->_vec;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
    else
        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
}


/**
 * @test Verify that @ref fgm::Vector4D compound multiplication assignment operator performs a component-wise (Hadamard)
 * product and mutates the @ref fgm::Vector4D in-place.
 */
TYPED_TEST(Vector4DScalarMultiplication, VectorTimesEqualScalarIsTheSameVectorScaled)
{
    this->_vec *= this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_VEC_EQ(this->_expectedFloatingVec, this->_vec);
    else
        EXPECT_VEC_EQ(this->_expectedIntegralVec, this->_vec);
}


/** @test Verify that @ref fgm::Vector4D binary multiplication operator performs automatic type promotion to the wider
 * numeric type. */
TYPED_TEST(Vector4DScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    constexpr double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Vector4D result = this->_vec * scalar;

    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
}


/**
 * @test Verify that @ref fgm::Vector4D compound multiplication assignment operator maintains the destination type and
 * performs an implicit cast.
 */
TEST(Vector4DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Vector4D vec(3.0f, 0.0f, -1.0f, 2.0f);
    constexpr double scalar = 5.0;
    vec *= scalar;

    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
}


/** @test Verify that @ref fgm::Vector4D compound multiplication operator for mixed types ensures minimal precision
 * loss. */
TEST(Vector4DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    fgm::Vector4D vec(3, 0, -1, 8);
    constexpr double scalar = 2.5;
    constexpr fgm::Vector4D expected(7, 0, -2, 20);

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

/**
 * @test Verify that @ref fgm::Vector4D binary division of a @ref fgm::Vector4D by zero scalar returns an
 *       infinity-vector for float vector.
 */
TEST(Vector4DScalarDivision, FloatVectorDivisionByZeroReturnsInfinityVector)
{
    constexpr fgm::Vector4D vec(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_VEC_INF(vec / 0);
}


/**
 * @test Verify that @ref fgm::Vector4D binary division of a @ref fgm::Vector4D by zero scalar returns an
 *       infinity-vector for double vector.
 */
TEST(Vector4DScalarDivision, DoubleVectorDivisionByZeroReturnsInfinityVector)
{
    constexpr fgm::Vector4D vec(1.0, 2.0, 3.0, 4.0);
    EXPECT_VEC_INF(vec / 0);
}


/** @test Verify that @ref fgm::Vector4D binary division of a @ref fgm::Vector4D by one returns the original vector. */
TYPED_TEST(Vector4DScalarDivision, DivisionByOneReturnsOriginalVector)
{
    const fgm::Vector4D result = this->_vec / 1;

    EXPECT_VEC_EQ(result, this->_vec);
}


/**
 * @test Verify that @ref fgm::Vector4D binary division operator (vector / scalar) performs a component-wise divide
 *       and returns a new @ref fgm::Vector4D instance.
 */
TYPED_TEST(Vector4DScalarDivision, ScalarDivision_ReturnsInverseScaledVector)
{
    const fgm::Vector4D result = this->_vec / this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @test Verify that @ref fgm::Vector4D compound division assignment operator performs a component-wise divide
 *       and mutates the @ref fgm::Vector4D in-place.
 */
TYPED_TEST(Vector4DScalarDivision, ScalarDivisionAssignment_ReturnsSameVectorInverseScaled)
{
    this->_vec /= this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, this->_vec);
}


/**
 * @test Verify that @ref fgm::Vector4D binary division operator performs automatic type promotion to the wider numeric
 *       type.
 */
TEST(Vector4DScalarDivision, MixedType_ScalarDivision_PromotesType)
{
    constexpr fgm::Vector4D vec(15.0, 0.0, -5.0, 10.0);
    constexpr double scalar = 5.0;

    [[maybe_unused]] constexpr fgm::Vector4D result = vec / scalar;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @test Verify that @ref fgm::Vector4D compound division assignment operator maintains the destination type and
 *       performs an implicit cast.
 */
TEST(Vector4DScalarDivision, MixedType_ScalarDivisionAssignment_DoesNotPromoteType)
{
    fgm::Vector4D vec(15.0f, 0.0f, -5.0f, 10.0f);
    constexpr double scalar = 5.0;

    vec /= scalar;

    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
}


/** @test Verify that @ref fgm::Vector4D compound division operator for mixed types ensures minimal precision loss. */
TEST(Vector4DScalarDivision, MixedType_ScalarDivisionAssignment_ReturnsResultWithMinimalPrecisionLoss)
{
    fgm::Vector4D vec(10, 25, -30, 2);
    constexpr double scalar = 2.5;
    constexpr fgm::Vector4D expected(4, 10, -12, 0);

    vec /= scalar;

    EXPECT_VEC_EQ(expected, vec);
}


/**************************************
 *                                    *
 *        SAFE DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @test Verify that @ref fgm::Vector4D safeDiv performs a component-wise divide and returns a
 *       new @ref fgm::Vector4D instance.
 */
TYPED_TEST(Vector4DScalarDivision, SafeDivide_ReturnsAInverseScaledVector)
{
    const auto result = this->_vec.safeDiv(this->_scalar);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/** @test Verify that @ref fgm::Vector4D safeDiv return a zero vector. */
TYPED_TEST(Vector4DScalarDivision, SafeDivideByIntegralZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0);
    EXPECT_VEC_ZERO(result);
}


/** @test Verify that @ref fgm::Vector4D safeDiv by floating point zero returns zero vector. */
TYPED_TEST(Vector4DScalarDivision, SafeDivideByFloatZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0.0f);
    EXPECT_VEC_ZERO(result);
}


/**
 * @test Verify that the static safeDiv wrapper of @ref fgm::Vector4D performs a component-wise divide and returns a
 *       new @ref fgm::Vector4D instance.
 */
TYPED_TEST(Vector4DScalarDivision, StaticWrapper_SafeDivide_ReturnsAInverseScaledVector)
{
    const auto result = fgm::Vector4D<TypeParam>::safeDiv(this->_vec, this->_scalar);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/** @test Verify that the static safeDiv wrapper of @ref fgm::Vector4D returns a zero vector. */
TEST(Vector4DScalarDivision, StaticWrapper_SafeDivideByIntergralZero_ReturnsZeroVector)
{
    constexpr fgm::Vector4D vec(1, 2, 3, 4);
    EXPECT_VEC_ZERO(fgm::Vector4D<int>::safeDiv(vec, 0));
}


/** @test Verify that @ref fgm::Vector4D safeDiv by floating point zero returns zero vector. */
TYPED_TEST(Vector4DScalarDivision, StaticWrapper_SafeDivideByFloatZero_ReturnsZeroVector)
{
    const auto result = fgm::Vector4D<TypeParam>::safeDiv(this->_vec, 0.0f);
    EXPECT_VEC_ZERO(result);
}


/**************************************
 *                                    *
 *         TRY DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @test Verify that performing scalar division on a vector using @ref fgm::Vector4D::tryDiv
 *       returns a new instance and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector4DScalarDivision, TryDivide_ReturnsAInverseScaledVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(this->_scalar, flag);

    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @test Verify that performing scalar division on a vector using @ref fgm::Vector4D::tryDiv by an integral zero
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector4DScalarDivision, TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that performing scalar division on a vector using @ref fgm::Vector4D::tryDiv by floating point zero
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector4DScalarDivision, TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}

/**
 * @test Verify that performing scalar division on a nan vector using @ref fgm::Vector4D::tryDiv
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector4DScalarDivision, TryDivideNaNVector_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::vec4d::nan<double>.tryDiv(3, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN vector by zero using @ref fgm::Vector4D::tryDiv @ref
 * fgm::OperationStatus::NANOPERAND takes precedence over @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TEST(Vector4DScalarDivision, TryDivideNaNVectorByZero_NaNOperandStatusTakesPrecedence)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const auto result = fgm::vec4d::nan<double>.tryDiv(0, flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that performing scalar division on a vector using @ref fgm::Vector4D::tryDiv by nan
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TYPED_TEST(Vector4DScalarDivision, TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(fgm::constants::NaN, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that performing scalar division on a vector using static variant of @ref fgm::Vector4D::tryDiv
 *       returns a new instance and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vector4DScalarDivision, StaticWrapper_TryDivide_ReturnsAInverseScaledVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vector4D<TypeParam>::tryDiv(this->_vec, this->_scalar, flag);

    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @test Verify that performing scalar division on a vector using static variant of @ref fgm::Vector4D::tryDiv
 *       by an integral zero returns a zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector4DScalarDivision, StaticWrapper_TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vector4D<TypeParam>::tryDiv(this->_vec, 0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that performing scalar division on a vector using static variant of @ref fgm::Vector4D::tryDiv
 *       by a floating point zero returns a zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vector4DScalarDivision, StaticWrapper_TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vector4D<TypeParam>::tryDiv(this->_vec, 0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that performing scalar division on a nan vector using static variant of @ref fgm::Vector4D::tryDiv
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vector4DScalarDivision, StaticWrapper_TryDivideNaNVector_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vector4D<double>::tryDiv(fgm::vec4d::nan<double>, 3, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN vector by zero using the static variant of @ref fgm::Vector4D::tryDiv
 *       @ref fgm::OperationStatus::NANOPERAND takes precedence over @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TEST(Vector4DScalarDivision, StaticWrapper_TryDivideNaNVectorByZero_NaNOperandStatusTakesPrecedence)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const auto result = fgm::Vector4D<double>::tryDiv(fgm::vec4d::nan<double>, 0, flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that performing scalar division on a vector using static variant of @ref fgm::Vector4D::tryDiv by nan
 *       returns a zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TYPED_TEST(Vector4DScalarDivision, StaticWrapper_TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vector4D<double>::tryDiv(this->_vec, fgm::constants::NaN, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**************************************
 *                                    *
 *         NaN DIVISION TESTS         *
 *                                    *
 **************************************/

/** @test Verify that dividing a nan vector by a scalar using @ref fgm::Vector4D::safeDiv returns a zero vector. */
TEST_P(Vector4DNaNTests, SafeDiv_ReturnsZeroVector)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(vec.safeDiv(3));
}

/**
 * @test Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Vector4D::safeDiv
 *       returns a zero vector.
 */
TEST_P(Vector4DNaNTests, StaticWrapper_SafeDiv_ReturnsZeroVector)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(fgm::Vector4D<float>::safeDiv(vec, 3));
}


/** 
 * @test Verify that dividing a nan vector by a scalar using @ref fgm::Vector4D::try returns a zero vector 
 *       and sets correct flag. 
 */
TEST_P(Vector4DNaNTests, TryDiv_ReturnsZeroVector)
{
    const auto& vec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(vec.tryDiv(3, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Vector4D::tryDiv
 *       returns a zero vector and sets correct flag.
 */
TEST_P(Vector4DNaNTests, StaticWrapper_TryDiv_ReturnsZeroVector)
{
    const auto& vec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vector4D<float>::tryDiv(vec, 3, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/** @} */



/**
 * @addtogroup T_FGM_Vec4_Inversion
 * @{
 */

/** @test Verify that  @ref fgm::Vector4D unary minus operator inverts each component and returns a new @ref
 * fgm::Vector4D. */
TYPED_TEST(Vector4DInversion, InvertsTheSignOfEachComponents)
{
    const fgm::Vector4D inverted = -this->_vec;
    EXPECT_VEC_EQ(this->_expectedInvertedVec, inverted);
}


/** @test Verify that @ref fgm::Vector4D unary minus operator inverts each component of an infinity vector. */
TEST(Vector4DInversion, InvertsSignOfInfinity)
{
    constexpr fgm::Vector4D infVec = {
        fgm::constants::INFINITY_F,
        -fgm::constants::INFINITY_F,
        fgm::constants::INFINITY_F,
        -fgm::constants::INFINITY_F,
    };
    constexpr fgm::Vector4D expected = {
        -fgm::constants::INFINITY_F,
        fgm::constants::INFINITY_F,
        -fgm::constants::INFINITY_F,
        fgm::constants::INFINITY_F,
    };

    constexpr fgm::Vector4D<float> inverted = -infVec;

    EXPECT_VEC_EQ(expected, inverted);
}


/** @test Verify that @ref fgm::Vector4D unary minus follows IEEE 754 rules for NaN. */
TEST(Vector4DInversion, NoOpOnNaNVectors)
{
    constexpr fgm::Vector4D nanVec = {
        fgm::constants::NaN,
        fgm::constants::NaN,
        fgm::constants::NaN,
        fgm::constants::NaN,
    };

    constexpr fgm::Vector4D<float> inverted = -nanVec;

    EXPECT_TRUE(std::isnan(inverted.x));
    EXPECT_TRUE(std::isnan(inverted.y));
    EXPECT_TRUE(std::isnan(inverted.z));
    EXPECT_TRUE(std::isnan(inverted.w));
}

/** @} */
