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



/**
 * @addtogroup T_FGM_Vec2_Arithmetic
 * @{
 */

namespace
{

    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec2 additions.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2AdditionTests: public testing::Test
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
    TYPED_TEST_SUITE(Vec2AdditionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec2 subtraction.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2SubtractionTests: public testing::Test
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
    TYPED_TEST_SUITE(Vec2SubtractionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec2 scalar multiplication.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2ScalarMultiplicationTests: public testing::Test
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
    TYPED_TEST_SUITE(Vec2ScalarMultiplicationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec2 scalar division.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2ScalarDivisionTests: public testing::Test
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
    TYPED_TEST_SUITE(Vec2ScalarDivisionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec2 negation.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2NegationTests: public testing::Test
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
    TYPED_TEST_SUITE(Vec2NegationTests, SupportedSignedArithmeticTypes);


    /// @brief Test fixture for @ref fgm::Vec2 division with NaN vectors.
    class Vec2DivisionNaNTests: public testing::TestWithParam<fgm::Vec2<float>>
    {};

    INSTANTIATE_TEST_SUITE_P(Vec2InvalidDivision, Vec2DivisionNaNTests,
                             ::testing::Values(fgm::Vec2<float>(fgm::constants::NaN, 3.0f),
                                               fgm::Vec2<float>(3.0f, fgm::constants::NaN),
                                               fgm::Vec2<float>(fgm ::constants::NaN, fgm::constants::NaN)));
} // namespace



/**************************************
 *           ADDITION TESTS           *
 **************************************/

TYPED_TEST(Vec2AdditionTests, PlusOperator_ReturnsVectorSum)
{
    const fgm::Vec2 result = this->_vecA + this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, result);
}



TYPED_TEST(Vec2AdditionTests, PlusEqualsOperator_ReturnsSameVectorWithSum)
{
    this->_vecA += this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, this->_vecA);
}




/**************************************
 *          SUBTRACTION TESTS         *
 **************************************/

TYPED_TEST(Vec2SubtractionTests, MinusOperator_ReturnsVectorDifference)
{
    const fgm::Vec2 result = this->_vecA - this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, result);
}


TYPED_TEST(Vec2SubtractionTests, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_vecA -= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, this->_vecA);
}




/**************************************
 *     SCALAR MULTIPLICATION TESTS    *
 **************************************/

TEST(Vec2ScalarMultiplicationTests, TimesOperator_ByZeroReturnsZeroVector)
{
    const fgm::Vec2 vec(3.0f, 6.0f);

    const fgm::Vec2 result = vec * 0;

    EXPECT_VEC_ZERO(result);
}


TEST(Vec2ScalarMultiplicationTests, TimesOperator_ByOneReturnsOriginalVector)
{
    const fgm::Vec2 vec(3.0f, 6.0f);

    const fgm::Vec2 result = vec * 1;

    EXPECT_VEC_EQ(vec, result);
}


TYPED_TEST(Vec2ScalarMultiplicationTests, TimesOperator_ByScalarReturnsScaledVector)
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


TYPED_TEST(Vec2ScalarMultiplicationTests, TimesOperator_ScalarByVectorReturnsScaledVector)
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



TYPED_TEST(Vec2ScalarMultiplicationTests, TimesEqualsOperator_ByScalarReturnsTheSameVectorWithScaledComponents)
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


/**************************************
 *           DIVIDE OPERATOR          *
 **************************************/

TYPED_TEST(Vec2ScalarDivisionTests, DivideOperator_ByOneReturnsOriginalVector)
{
    const fgm::Vec2 result = this->_vec / 1;

    EXPECT_VEC_EQ(result, this->_vec);
}


TYPED_TEST(Vec2ScalarDivisionTests, DivideOperator_ReturnsVectorWithDividedComponents)
{
    const fgm::Vec2 result = this->_vec / this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


TYPED_TEST(Vec2ScalarDivisionTests, DivideEqualsOperator_ReturnsSameVectorWithDividedComponents)
{
    this->_vec /= this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, this->_vec);
}




TEST(Vec2ScalarDivisionTests, TimesEqualsOperator_MixedType_EnsuresMinimalPrecisionLoss)
{
    fgm::Vec2 vec(10, -30);
    const double scalar = 2.5;
    const fgm::Vec2 expected(4, -12);

    vec /= scalar;

    EXPECT_VEC_EQ(expected, vec);
}


#ifndef ENABLE_DEBUG_TESTS
/**
 * @test Verify that dividing a float vector by zero returns an
 *        infinity vector of float type.
 */
TEST(Vec2ScalarDivisionTests, FloatVectorDivisionByZeroReturnsInfinityVector)
{
    const fgm::Vec2 vec(1.0f, 3.0f);
    EXPECT_VEC_INF(vec / 0);
}


/**
 * @test Verify that dividing a double vector by zero returns an
 *        infinity vector of double type.
 */
TEST(Vec2ScalarDivisionTests, DoubleVectorDivisionByZeroReturnsInfinityVector)
{
    const fgm::Vec2 vec(1.0, 3.0);
    EXPECT_VEC_INF(vec / 0);
}
#endif



/**************************************
 *        SAFE DIVISION TESTS         *
 **************************************/

TYPED_TEST(Vec2ScalarDivisionTests, SafeDiv_ReturnsVectorWithDividedComponents)
{
    const auto result = this->_vec.safeDiv(this->_scalar);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


TYPED_TEST(Vec2ScalarDivisionTests, SafeDiv_ByIntegralZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0);
    EXPECT_VEC_ZERO(result);
}


TYPED_TEST(Vec2ScalarDivisionTests, SafeDiv_ByFloatZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0.0f);
    EXPECT_VEC_ZERO(result);
}


TYPED_TEST(Vec2ScalarDivisionTests, StaticWrapper_SafeDiv_ReturnsVectorWithDividedComponents)
{
    const auto result = fgm::Vec2<TypeParam>::safeDiv(this->_vec, this->_scalar);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


TEST(Vec2ScalarDivision, StaticWrapper_SafeDiv_ByIntergralZero_ReturnsZeroVector)
{
    const fgm::Vec2 vec(1, 3);
    EXPECT_VEC_ZERO(fgm::Vec2<int>::safeDiv(vec, 0));
}


TYPED_TEST(Vec2ScalarDivisionTests, StaticWrapper_SafeDiv_ByFloatZero_ReturnsZeroVector)
{
    const auto result = fgm::Vec2<TypeParam>::safeDiv(this->_vec, 0.0f);
    EXPECT_VEC_ZERO(result);
}


TYPED_TEST(Vec2ScalarDivisionTests, SafeDiv_ByNaN_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(fgm::constants::NaN);

    EXPECT_VEC_ZERO(result);
}



TYPED_TEST(Vec2ScalarDivisionTests, StaticWrapper_SafeDiv_ByNaN_ReturnsZeroVector)
{
    const auto result = fgm::Vec2<TypeParam>::safeDiv(this->_vec, fgm::constants::INFINITY_F);

    EXPECT_VEC_ZERO(result);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a vector using @ref fgm::Vec2::tryDiv perform a component-wise divide and
 *       returns a new vector instance and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2ScalarDivisionTests, TryDivide_ReturnsVectorWithDividedComponentsAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(this->_scalar, flag);

    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @test Verify that dividing a vector by integral zero using @ref fgm::Vec2::tryDiv returns zero vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2ScalarDivisionTests, TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a vector by floating point zero using @ref fgm::Vec2::tryDiv returns zero vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2ScalarDivisionTests, TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN vector by zero using @ref fgm::Vec2::tryDiv
 *       @ref fgm::OperationStatus::NANOPERAND takes precedence over @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec2ScalarDivision, TryDivideNaNVectorByZero_NaNOperandStatusTakesPrecedence)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const auto result = fgm::Vec2<double>::qnan().tryDiv(0, flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a vector by NaN using @ref fgm::Vec2::tryDiv returns a zero vector and
 *       sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TYPED_TEST(Vec2ScalarDivisionTests, TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(fgm::constants::NaN, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a vector using static variant of @ref fgm::Vec2::tryDiv
 *       perform a component-wise divide and returns a new vector instance and
 *       sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2ScalarDivisionTests, StaticWrapper_TryDivide_ReturnsVectorWithDividedComponentsAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec2<TypeParam>::tryDiv(this->_vec, this->_scalar, flag);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a vector by integral zero using static variant of @ref fgm::Vec2::tryDiv
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2ScalarDivisionTests, StaticWrapper_TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec2<TypeParam>::tryDiv(this->_vec, 0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a vector by floating point zero using static variant of @ref fgm::Vec2::tryDiv
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2ScalarDivisionTests, StaticWrapper_TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec2<TypeParam>::tryDiv(this->_vec, 0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a vector by floating point zero using static variant of @ref fgm::Vec2::tryDiv
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
 * @test Verify that dividing a vector by NaN using static variant of @ref fgm::Vec2::tryDiv returns zero vector
 * and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TYPED_TEST(Vec2ScalarDivisionTests, StaticWrapper_TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec2<TypeParam>::tryDiv(this->_vec, fgm::constants::NaN, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}



/**************************************
 *         NaN DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a nan vector by a scalar using @ref fgm::Vec2::safeDiv
 *       returns vector with NaN-components as zero.
 */
TEST_P(Vec2DivisionNaNTests, SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(vec.safeDiv(3));
}

/**
 * @test Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Vec2::safeDiv
 *       returns zero vector.
 */
TEST_P(Vec2DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(fgm::Vec2<float>::safeDiv(vec, 3));
}


/**
 * @test Verify that dividing a nan vector by a scalar using @ref fgm::Vec2::tryDiv
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
 * @test Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Vec2::tryDiv
 *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
 */
TEST_P(Vec2DivisionNaNTests, StaticWrapper_TryDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec2<float>::tryDiv(vec, 3, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}



/**************************************
 *              NEGATION              *
 **************************************/

TYPED_TEST(Vec2NegationTests, InvertsTheSignOfEachComponents)
{
    const fgm::Vec2 inverted = -this->_vec;
    EXPECT_VEC_EQ(this->_expectedInvertedVec, inverted);
}


/** @test Verify that @ref fgm::Vec2 unary minus operator inverts each component of an infinity vector. */
TEST(Vec2NegationTests, InvertsSignOfInfinity)
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


/** @test Verify that @ref fgm::Vec2 unary minus follows IEEE 754 rules for NaN. */
TEST(Vec2NegationTests, NoOpOnNaNVectors)
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
