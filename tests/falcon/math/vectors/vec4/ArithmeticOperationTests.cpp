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



/**
 * @addtogroup T_FGM_Vec4_Arithmetic
 * @{
 */

namespace
{

    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec4 additions.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4AdditionTests: public testing::Test
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
    TYPED_TEST_SUITE(Vec4AdditionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec4 subtraction.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4SubtractionTests: public testing::Test
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
    TYPED_TEST_SUITE(Vec4SubtractionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec4 scalar multiplication.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4ScalarMultiplicationTests: public testing::Test
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
    TYPED_TEST_SUITE(Vec4ScalarMultiplicationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec4 scalar division.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4ScalarDivisionTests: public testing::Test
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
    TYPED_TEST_SUITE(Vec4ScalarDivisionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec4 negation.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4NegationTests: public testing::Test
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
    TYPED_TEST_SUITE(Vec4NegationTests, SupportedSignedArithmeticTypes);



    /// @brief Test fixture for @ref fgm::Vec4 division with NaN vectors.
    class Vec4DivisionNaNTests: public testing::TestWithParam<fgm::Vec4<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec4InvalidDivision, Vec4DivisionNaNTests,
                             ::testing::Values(fgm::Vec4<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                                               fgm::Vec4<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                                               fgm::Vec4<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                                               fgm::Vec4<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                                               fgm::Vec4<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN, fgm ::constants::NaN)));



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Vec4 VEC_A(1, 2, 3, 4);
        constexpr fgm::Vec4 VEC_B(3, 5, 6, 7);

        /// @test Verify that vector sum returns a valid vector at compile time.
        constexpr auto VEC_SUM = VEC_A + VEC_B;
        static_assert(VEC_SUM.x() == 4);
        static_assert(VEC_SUM.y() == 7);
        static_assert(VEC_SUM.z() == 9);
        static_assert(VEC_SUM.w() == 11);


        /// @test Verify that vector difference returns a valid vector at compile time.
        constexpr auto VEC_DIFF = VEC_B - VEC_A;
        static_assert(VEC_DIFF.x() == 2);
        static_assert(VEC_DIFF.y() == 3);
        static_assert(VEC_DIFF.z() == 3);
        static_assert(VEC_DIFF.w() == 3);


        /// @test Verify that vector scalar product(vector * scalar) returns a valid vector at compile time.
        constexpr auto VEC_MUL_SCALAR = VEC_A * 2;
        static_assert(VEC_MUL_SCALAR.x() == 2);
        static_assert(VEC_MUL_SCALAR.y() == 4);
        static_assert(VEC_MUL_SCALAR.z() == 6);
        static_assert(VEC_MUL_SCALAR.w() == 8);


        /// @test Verify that vector scalar product(scalar * vector) returns a valid vector at compile time.
        constexpr auto SCALAR_MUL_VEC = VEC_A * 2;
        static_assert(SCALAR_MUL_VEC.x() == 2);
        static_assert(SCALAR_MUL_VEC.y() == 4);
        static_assert(SCALAR_MUL_VEC.z() == 6);
        static_assert(SCALAR_MUL_VEC.w() == 8);


        /// @test Verify that vector scalar division(operator/) returns a valid vector at compile time.
        constexpr auto DIV_VEC = VEC_B / 2;
        static_assert(DIV_VEC.x() == 1);
        static_assert(DIV_VEC.y() == 2);
        static_assert(DIV_VEC.z() == 3);
        static_assert(DIV_VEC.w() == 3);


        /// @test Verify that vector scalar division(safeDiv) returns a valid vector at compile time.
        constexpr auto SAFE_DIV_VEC = VEC_B.safeDiv(2);
        static_assert(SAFE_DIV_VEC.x() == 1);
        static_assert(SAFE_DIV_VEC.y() == 2);
        static_assert(SAFE_DIV_VEC.z() == 3);
        static_assert(SAFE_DIV_VEC.w() == 3);


        /// @test Verify that vector scalar division(safeDiv-static wrapper) returns a valid vector at compile time.
        constexpr auto SAFE_DIV_VEC_STATIC = fgm::Vec4<int>::safeDiv(VEC_B, 2);
        static_assert(SAFE_DIV_VEC_STATIC.x() == 1);
        static_assert(SAFE_DIV_VEC_STATIC.y() == 2);
        static_assert(SAFE_DIV_VEC_STATIC.z() == 3);
        static_assert(SAFE_DIV_VEC_STATIC.w() == 3);


        /// @test Verify that vector inverse returns a valid vector at compile time.
        constexpr auto INV_VEC = -VEC_A;
        static_assert(INV_VEC.x() == -1);
        static_assert(INV_VEC.y() == -2);
        static_assert(INV_VEC.z() == -3);
        static_assert(INV_VEC.w() == -4);

    } // namespace static_tests
} // namespace



/**************************************
 *           ADDITION TESTS           *
 **************************************/

/**
 * @test Verify that the binary addition operator perform a component-wise addition and
 *       returns a new vector instance.
 */
TYPED_TEST(Vec4AdditionTests, PlusOperator_ReturnsVectorSum)
{
    const fgm::Vec4 result = this->_vecA + this->_vecB;
    EXPECT_VEC_EQ(this->_expectedSum, result);
}


/**
 * @test Verify that the compound addition assignment operator perform a component-wise addition and
 *       mutates the vector in-place.
 */
TYPED_TEST(Vec4AdditionTests, PlusEqualsOperator_ReturnsSameVectorWithSum)
{
    this->_vecA += this->_vecB;
    EXPECT_VEC_EQ(this->_expectedSum, this->_vecA);
}


/**
 * @test Verify that the binary addition operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Vec4Addition, PlusOperator_MixedType_PromotesType)
{
    const fgm::Vec4 vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const fgm::Vec4 vec2(9.0, -5.0, 10.0, 3.0);

    [[maybe_unused]] const fgm::Vec4 result = vec1 + vec2;
    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @test Verify that the compound addition assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Vec4Addition, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    fgm::Vec4 vec1(3.0f, 0.0f, -1.0f, 2.0f);
    [[maybe_unused]] const fgm::Vec4 vec2(9.0, -5.0, 10.0, 3.0);

    static_cast<void>(vec1 += vec2);
    static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
}



/**************************************
 *          SUBTRACTION TESTS         *
 **************************************/

/**
 * @test Verify that the binary subtraction operator perform a component-wise subtraction and
 *       returns a new vector instance.
 */
TYPED_TEST(Vec4SubtractionTests, MinusOperator_ReturnsMatrixDifference)
{
    const fgm::Vec4 result = this->_vecA - this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, result);
}


/**
 * @test Verify that the compound subtraction assignment operator perform a component-wise subtraction
 *       and mutates the vector in-place.
 */
TYPED_TEST(Vec4SubtractionTests, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_vecA -= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, this->_vecA);
}


/**
 * @test Verify that the binary subtraction operator perform automatic type promotion
 *       to the wider numeric type.
 */
TEST(Vec4Subtraction, MinusOperator_MixedType_PromotesType)
{
    const fgm::Vec4 vec1(3.0f, 0.0f, -1.0f, 2.0f);
    const fgm::Vec4 vec2(9.0, -5.0, 10.0, 3.0);

    [[maybe_unused]] const fgm::Vec4 result = vec1 - vec2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


/**
 * @test Verify that the compound subtraction assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Vec4Subtraction, MinusEqualsOperator_MixedType_DoesNotPromoteType)
{
    fgm::Vec4 vec1(3.0f, 0.0f, -1.0f, 2.0f);
    [[maybe_unused]] const fgm::Vec4 vec2(9.0, -5.0, 10.0, 3.0);

    static_cast<void>(vec1 -= vec2);

    static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
}



/**************************************
 *     SCALAR MULTIPLICATION TESTS    *
 **************************************/

/** @test Verify that scalar multiplication by zero returns a zero vector. */
TEST(Vec4ScalarMultiplication, MultiplicationByZeroReturnsZeroVector)
{
    const fgm::Vec4 vec(3.0f, 1.0f, 6.0f, 2.0f);

    const fgm::Vec4 result = vec * 0;

    EXPECT_VEC_ZERO(result);
}


/** @test Verify that scalar multiplication by one returns original vector. */
TEST(Vec4ScalarMultiplication, MultiplicationByOneReturnsOriginalVector)
{
    const fgm::Vec4 vec(3.0f, 1.0f, 6.0f, 2.0f);

    const fgm::Vec4 result = vec * 1;

    EXPECT_VEC_EQ(vec, result);
}


/**
 * @test Verify that the binary multiplication operator (vector * scalar) perform a component-wise (Hadamard) product
 *       and returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarMultiplicationTests, VectorTimesScalarReturnsScaledVector)
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
 * @test Verify that the binary multiplication operator (scalar * vector) perform a component-wise (Hadamard) product
 *       and returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarMultiplicationTests, ScalarTimesAVectorReturnsScaledVector)
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
 * @test Verify that the compound multiplication assignment operator performs a component-wise (Hadamard) product
 *       and mutates the vector in-place.
 */
TYPED_TEST(Vec4ScalarMultiplicationTests, VectorTimesEqualScalarReturnsTheSameVectorWithScaledComponents)
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
 * @test Verify that the binary multiplication operator perform automatic type promotion
 *       to the wider numeric type.
 */
TYPED_TEST(Vec4ScalarMultiplicationTests, MixedTypeScalarMultiplicationPromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Vec4 result = this->_vec * scalar;

    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
}


/**
 * @test Verify that the compound multiplication assignment operator maintains the destination type and
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
 * @test Verify that the compound multiplication operator for mixed types
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



/**************************************
 *        SCALAR DIVISION TESTS       *
 **************************************/

/** @test Verify that dividing a vector by one returns the original vector. */
TYPED_TEST(Vec4ScalarDivisionTests, DivisionByOneReturnsOriginalVector)
{
    const fgm::Vec4 result = this->_vec / 1;

    EXPECT_VEC_EQ(result, this->_vec);
}


/**
 * @test Verify that the binary division operator (vector / scalar) perform a component-wise divide and
 *       returns a vector instance.
 */
TYPED_TEST(Vec4ScalarDivisionTests, ScalarDivision_ReturnsVectorWithDividedComponents)
{
    const fgm::Vec4 result = this->_vec / this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @test Verify that the compound division assignment operator perform a component-wise divide and
 *       mutates the vector in-place.
 */
TYPED_TEST(Vec4ScalarDivisionTests, DivideEqualsOperator_ReturnsSameVectorWithDividedComponents)
{
    this->_vec /= this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, this->_vec);
}


/**
 * @test Verify that the binary division operator perform automatic type promotion
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
 * @test Verify that the compound division assignment operator maintains the destination type and
 *       perform an implicit cast.
 */
TEST(Vec4ScalarDivision, MixedType_ScalarDivisionAssignment_DoesNotPromoteType)
{
    fgm::Vec4 vec(15.0f, 0.0f, -5.0f, 10.0f);
    const double scalar = 5.0;

    vec /= scalar;

    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
}


/** @test Verify that the compound division operator for mixed types ensures minimal precision loss. */
TEST(Vec4ScalarDivision, TimesEqualsOperator_MixedType_EnsuresMinimalPrecisionLoss)
{
    fgm::Vec4 vec(10, 25, -30, 2);
    const double scalar = 2.5;
    const fgm::Vec4 expected(4, 10, -12, 0);

    vec /= scalar;

    EXPECT_VEC_EQ(expected, vec);
}

#ifndef ENABLE_DEBUG_TESTS

/**
 * @test Verify that dividing a float vector by zero returns an
 *       infinity vector of float type.
 */
TEST(Vec4ScalarDivision, FloatVectorDivisionByZeroReturnsInfinityVector)
{
    const fgm::Vec4 vec(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_VEC_INF(vec / 0);
}


/**
 * @test Verify that dividing a double vector by zero returns an
 *       infinity vector of double type.
 */
TEST(Vec4ScalarDivision, DoubleVectorDivisionByZeroReturnsInfinityVector)
{
    const fgm::Vec4 vec(1.0, 2.0, 3.0, 4.0);
    EXPECT_VEC_INF(vec / 0);
}

#endif



/**************************************
 *        SAFE DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a vector using @ref fgm::Vec4::safeDiv perform a component-wise divide and
 *       returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarDivisionTests, SafeDiv_ReturnsVectorWithDividedComponents)
{
    const auto result = this->_vec.safeDiv(this->_scalar);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @test Verify that dividing a vector by integral zero using @ref fgm::Vec4::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarDivisionTests, SafeDiv_ByIntegralZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0);
    EXPECT_VEC_ZERO(result);
}


/**
 * @test Verify that dividing a vector by floating point zero using @ref fgm::Vec4::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarDivisionTests, SafeDiv_ByFloatZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0.0f);
    EXPECT_VEC_ZERO(result);
}


/**
 * @test Verify that dividing a vector using static variant of @ref fgm::Vec4::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarDivisionTests, StaticWrapper_SafeDiv_ReturnsVectorWithDividedComponents)
{
    const auto result = fgm::Vec4<TypeParam>::safeDiv(this->_vec, this->_scalar);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @test Verify that dividing a vector by integral zero using static variant of @ref fgm::Vec4::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TEST(Vec4ScalarDivision, StaticWrapper_SafeDiv_ByIntergralZero_ReturnsZeroVector)
{
    const fgm::Vec4 vec(1, 2, 3, 4);
    EXPECT_VEC_ZERO(fgm::Vec4<int>::safeDiv(vec, 0));
}


/**
 * @test Verify that dividing a vector by floating point zero using static variant @ref fgm::Vec4::safeDiv
 *       perform a component-wise divide and returns a new vector instance.
 */
TYPED_TEST(Vec4ScalarDivisionTests, StaticWrapper_SafeDiv_ByFloatZero_ReturnsZeroVector)
{
    const auto result = fgm::Vec4<TypeParam>::safeDiv(this->_vec, 0.0f);
    EXPECT_VEC_ZERO(result);
}


/**
 * @test Verify that dividing a vector by NaN using @ref fgm::Vec4::safeDiv
 *       returns a zero vector.
 */
TYPED_TEST(Vec4ScalarDivisionTests, SafeDiv_ByNaN_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(fgm::constants::NaN);
    EXPECT_VEC_ZERO(result);
}


/**
 * @test Verify that dividing a vector by NaN using static variant of @ref fgm::Vec4::safeDiv
 *       returns a zero vector.
 */
TYPED_TEST(Vec4ScalarDivisionTests, StaticWrapper_SafeDiv_ByNaN_ReturnsZeroVector)
{
    const auto result = fgm::Vec4<TypeParam>::safeDiv(this->_vec, fgm::constants::INFINITY_F);
    EXPECT_VEC_ZERO(result);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a vector using @ref fgm::Vec4::tryDiv perform a component-wise divide and
 *       returns a new vector instance and sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec4ScalarDivisionTests, TryDivide_ReturnsVectorWithDividedComponentsAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(this->_scalar, flag);

    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @test Verify that dividing a vector by integral zero using @ref fgm::Vec4::tryDiv returns zero vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4ScalarDivisionTests, TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a vector by floating point zero using @ref fgm::Vec4::tryDiv returns zero vector and
 *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4ScalarDivisionTests, TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN vector by zero using @ref fgm::Vec4::tryDiv
 *       @ref fgm::OperationStatus::NANOPERAND takes precedence over @ref fgm::OperationStatus::NANOPERAND.
 */
TEST(Vec4ScalarDivision, TryDivideNaNVectorByZero_NaNOperandStatusTakesPrecedence)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const auto result = fgm::Vec4<double>::qnan().tryDiv(0, flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a vector by NaN using @ref fgm::Vec4::tryDiv returns a zero vector and
 *       sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TYPED_TEST(Vec4ScalarDivisionTests, TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = this->_vec.tryDiv(fgm::constants::NaN, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a vector using static variant of @ref fgm::Vec4::tryDiv
 *       perform a component-wise divide and returns a new vector instance and
 *       sets the flag to @ref fgm::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec4ScalarDivisionTests, StaticWrapper_TryDivide_ReturnsVectorWithDividedComponentsAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec4<TypeParam>::tryDiv(this->_vec, this->_scalar, flag);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a vector by integral zero using static variant of @ref fgm::Vec4::tryDiv
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4ScalarDivisionTests, StaticWrapper_TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec4<TypeParam>::tryDiv(this->_vec, 0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a vector by floating point zero using static variant of @ref fgm::Vec4::tryDiv
 *       returns zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4ScalarDivisionTests, StaticWrapper_TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec4<TypeParam>::tryDiv(this->_vec, 0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a vector by floating point zero using static variant of @ref fgm::Vec4::tryDiv
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
 * @test Verify that dividing a vector by NaN using static variant of @ref fgm::Vec4::tryDiv returns zero vector
 * and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
 */
TYPED_TEST(Vec4ScalarDivisionTests, StaticWrapper_TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto result = fgm::Vec4<TypeParam>::tryDiv(this->_vec, fgm::constants::NaN, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}



/**************************************
 *         NaN DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a nan vector by a scalar using @ref fgm::Vec4::safeDiv
 *       returns vector with NaN-components as zero.
 */
TEST_P(Vec4DivisionNaNTests, SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(vec.safeDiv(3));
}

/**
 * @test Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Vec4::safeDiv
 *       returns zero vector.
 */
TEST_P(Vec4DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(fgm::Vec4<float>::safeDiv(vec, 3));
}


/**
 * @test Verify that dividing a nan vector by a scalar using @ref fgm::Vec4::tryDiv
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
 * @test Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Vec4::tryDiv
 *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
 */
TEST_P(Vec4DivisionNaNTests, StaticWrapper_TryDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    fgm::OperationStatus flag;
    EXPECT_VEC_ZERO(fgm::Vec4<float>::tryDiv(vec, 3, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that  @ref fgm::Vec4 unary minus operator inverts each component and
 *       returns a new vector.
 */
TYPED_TEST(Vec4NegationTests, InvertsTheSignOfEachComponents)
{
    const fgm::Vec4 inverted = -this->_vec;
    EXPECT_VEC_EQ(this->_expectedInvertedVec, inverted);
}



/**************************************
 *              NEGATION              *
 **************************************/

/** @test Verify that @ref fgm::Vec4 unary minus operator inverts each component of an infinity vector. */
TEST(Vec4Negation, InvertsSignOfInfinity)
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


/** @test Verify that @ref fgm::Vec4 unary minus follows IEEE 754 rules for NaN. */
TEST(Vec4Negation, NoOpOnNaNVectors)
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
