/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref Vector4D arithmetic operator(+, -, *, /) logic.
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
/** @brief Test fixture for @ref fgm::Vector4D division, parameterized by SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector4DScalarDivision, SupportedArithmeticTypes);



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
 * @test Verify that the binary addition operator performs a component-wise sum and returns a new @ref fgm::Vector4D
 *       instance.
 */
TYPED_TEST(Vector4DAddition, PlusOperator_ReturnsVectorSum)
{
    const fgm::Vector4D result = this->_vecA + this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, result);
}


/**
 * @test Verify that the compound addition assignment operator performs a component-wise sum and mutates the @ref
 *       fgm::Vector4D in-place.
 */
TYPED_TEST(Vector4DAddition, PlusEqualsOperator_ReturnsSameVectorWithSum)
{
    this->_vecA += this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, this->_vecA);
}


/** @test Verify that the binary addition operator performs automatic type promotion to the wider numeric type. */
TEST(Vector4DAddition, MixedTypeAdditionPromotesType)
{
    constexpr fgm::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    constexpr fgm::Vector4D vec2(9.0, -5.0, 10.0, 3.0);

    [[maybe_unused]] constexpr fgm::Vector4D result = vec1 + vec2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @test Verify that the compound addition assignment operator maintains the destination type and performs an implicit
 *       cast.
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
 * @test Verify that the binary subtraction operator performs a component-wise difference and returns a new @ref
 * fgm::Vector4D instance.
 */
TYPED_TEST(Vector4DSubtraction, MinusOperator_ReturnsDifference)
{
    const fgm::Vector4D result = this->_vecA - this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, result);
}


/**
 * @test Verify that the compound subtraction assignment operator performs a component-wise difference and mutates the
 * @ref fgm::Vector4D in-place.
 */
TYPED_TEST(Vector4DSubtraction, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_vecA -= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, this->_vecA);
}


/** @test Verify that the binary subtraction operator performs automatic type promotion to the wider numeric type. */
TEST(Vector4DSubtraction, MixedTypeSubtractionPromotesType)
{
    constexpr fgm::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
    constexpr fgm::Vector4D vec2(9.0, -5.0, 10.0, 3.0);

    [[maybe_unused]] constexpr fgm::Vector4D result = vec1 - vec2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @test Verify that the compound subtraction assignment operator maintains the destination type and performs an
 * implicit cast.
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

/** @test Verify that the binary multiplication of a @ref fgm::Vector4D by a zero scalar returns a zero-vector. */
TEST(Vector4DScalarMultiplication, MultiplicationByZeroReturnsZeroVector)
{
    constexpr fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    constexpr fgm::Vector4D result = vec * 0;

    EXPECT_VEC_ZERO(result);
}


/** @test Verify that the binary multiplication of a @ref fgm::Vector4D by one returns the original vector. */
TEST(Vector4DScalarMultiplication, MultiplicationByOneReturnsOriginalVector)
{
    constexpr fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    constexpr fgm::Vector4D result = vec * 1;

    EXPECT_VEC_EQ(vec, result);
}


/**
 * @test Verify that the binary multiplication operator (vector * scalar) performs a component-wise (Hadamard) product
 * and returns a new @ref fgm::Vector4D instance.
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
 * @test Verify that the binary multiplication operator (scalar * vector) performs a component-wise (Hadamard) product
 * and returns a new
 *        @ref fgm::Vector4D instance.
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
 * @test Verify that the compound multiplication assignment operator performs a component-wise (Hadamard) product
 *       and mutates the @ref fgm::Vector4D in-place.
 */
TYPED_TEST(Vector4DScalarMultiplication, VectorTimesEqualScalarIsTheSameVectorScaled)
{
    this->_vec *= this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_VEC_EQ(this->_expectedFloatingVec, this->_vec);
    else
        EXPECT_VEC_EQ(this->_expectedIntegralVec, this->_vec);
}


/** @test Verify that the binary multiplication operator performs automatic type promotion to the wider numeric type. */
TYPED_TEST(Vector4DScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    constexpr double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Vector4D result = this->_vec * scalar;

    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
}


/**
 * @test Verify that the compound multiplication assignment operator maintains the destination type and performs an
 *       implicit cast.
 */
TEST(Vector4DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Vector4D vec(3.0f, 0.0f, -1.0f, 2.0f);
    constexpr double scalar = 5.0;
    vec *= scalar;

    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
}


/** @test Verify that the compound multiplication operator for mixed types ensures minimal precision loss. */
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
 * @test Verify that the binary division of a @ref fgm::Vector4D by a zero scalar returns an infinity-vector for
 *       floating-point types and triggers program termination for integral types.
 */
TYPED_TEST(Vector4DScalarDivision, DivisionByZeroReturnsInfinityVector)
{
    if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_VEC_INF(this->_vec / 0);
    else
        EXPECT_DEATH({ this->_vec / 0; }, "Integral division by zero");
}


/** @test Verify that the binary division of a @ref fgm::Vector4D by one returns the original vector. */
TYPED_TEST(Vector4DScalarDivision, DivisionByOneReturnsOriginalVector)
{
    const fgm::Vector4D result = this->_vec / 1;

    EXPECT_VEC_EQ(result, this->_vec);
}


/**
 * @test Verify that the binary division operator (vector / scalar) performs a component-wise divide
 *       and returns a new @ref fgm::Vector4D instance.
 */
TYPED_TEST(Vector4DScalarDivision, VectorDividedByANumberReturnsAScaledVector)
{
    const fgm::Vector4D result = this->_vec / this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @test Verify that the compound division assignment operator performs a component-wise divide
 *       and mutates the @ref fgm::Vector4D in-place.
 */
TYPED_TEST(Vector4DScalarDivision, VectorDivideEqualsANumberIsTheSameVectorScaled)
{
    this->_vec /= this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, this->_vec);
}


/** @test Verify that the binary division operator performs automatic type promotion to the wider numeric type. */
TEST(Vector4DScalarDivision, MixedTypeScalarDivisionPromotesType)
{
    constexpr fgm::Vector4D vec(15.0, 0.0, -5.0, 10.0);
    constexpr double scalar = 5.0;

    [[maybe_unused]] constexpr fgm::Vector4D result = vec / scalar;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @test Verify that the compound division assignment operator maintains the destination type and performs an
 *       implicit cast.
 */
TEST(Vector4DScalarDivision, MixedTypeScalarDivisionAssignmentDoesNotPromoteType)
{
    fgm::Vector4D vec(15.0f, 0.0f, -5.0f, 10.0f);
    constexpr double scalar = 5.0;

    vec /= scalar;

    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
}


/** @test Verify that the compound division operator for mixed types ensures minimal precision loss. */
TEST(Vector4DScalarDivision, MixedTypeScalarDivisionAssignmentGivesResultWithMinimalPrecisionLoss)
{
    fgm::Vector4D vec(10, 25, -30, 2);
    constexpr double scalar = 2.5;
    constexpr fgm::Vector4D expected(4, 10, -12, 0);

    vec /= scalar;

    EXPECT_VEC_EQ(expected, vec);
}

/** @} */