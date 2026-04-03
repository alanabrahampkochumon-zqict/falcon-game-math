///**
// * @file ArithmeticOperationTests.cpp
// * @author Alan Abraham P Kochumon
// * @date Created on: April 02, 2026
// *
// * @brief Verifies @ref fgm::Vector3D arithmetic operator(+, -, *, /) logic.
// *
// * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
// */
//
//
//#include "Vector3DTestSetup.h"
//
//
//
///**************************************
// *                                    *
// *               SETUP                *
// *                                    *
// **************************************/
//
//template <typename T>
//class Vector3DAddition: public ::testing::Test
//{
//protected:
//    fgm::Vector3D<T> _vecA;
//    fgm::Vector3D<T> _vecB;
//    fgm::Vector3D<T> _expectedSum;
//
//    void SetUp() override
//    {
//        _vecA = { T(3), T(1), T(6) };
//        _vecB = { T(-8), T(5), T(-2) };
//        _expectedSum = { T(-5), T(6), T(4) };
//    }
//};
///** @brief Test fixture for @ref fgm::Vector3D addition, parameterized by SupportedArithmeticTypes. */
//TYPED_TEST_SUITE(Vector3DAddition, SupportedArithmeticTypes);
//
//
//template <typename T>
//class Vector3DSubtraction: public ::testing::Test
//{
//protected:
//    fgm::Vector3D<T> _vecA;
//    fgm::Vector3D<T> _vecB;
//    fgm::Vector3D<T> _expectedDifference;
//
//    void SetUp() override
//    {
//        _vecA = { T(95), T(11), T(-6) };
//        _vecB = { T(-8), T(5), T(-2) };
//        _expectedDifference = { T(103), T(6), T(-4) };
//    }
//};
///** @brief Test fixture for @ref fgm::Vector3D subtraction, parameterized by SupportedArithmeticTypes. */
//TYPED_TEST_SUITE(Vector3DSubtraction, SupportedArithmeticTypes);
//
//
//template <typename T>
//class Vector3DScalarMultiplication: public ::testing::Test
//{
//protected:
//    fgm::Vector3D<T> _vec;
//    T _scalar;
//    fgm::Vector3D<T> _expectedFloatingVec;
//    fgm::Vector3D<T> _expectedIntegralVec;
//
//    void SetUp() override
//    {
//        _vec = { T(7), T(13), T(29) };
//        _scalar = T(2.123456789123456);
//        _expectedFloatingVec = { T(14.864197523864192), T(27.604938258604928), T(61.580246884580224) };
//        _expectedIntegralVec = { T(14), T(26), T(58) };
//    }
//};
///** @brief Test fixture for @ref fgm::Vector3D scalar multiplication, parameterized by SupportedArithmeticTypes. */
//TYPED_TEST_SUITE(Vector3DScalarMultiplication, SupportedArithmeticTypes);
//
//
//template <typename T>
//class Vector3DScalarDivision: public ::testing::Test
//{
//protected:
//    fgm::Vector3D<T> _vec;
//    T _scalar;
//    fgm::Vector3D<T> _expectedScaledVec;
//
//    void SetUp() override
//    {
//        _vec = { T(17), T(31), T(59) };
//        _scalar = T(13);
//        _expectedScaledVec = { T(1.30769230769230769231), T(2.38461538461538461538), T(4.53846153846153846154) };
//    }
//};
///** @brief Test fixture for @ref fgm::Vector3D division, parameterized by @ref SupportedArithmeticTypes. */
//TYPED_TEST_SUITE(Vector3DScalarDivision, SupportedArithmeticTypes);
//
//
//template <typename T>
//class Vector3DInversion: public ::testing::Test
//{
//protected:
//    fgm::Vector3D<T> _vec;
//    fgm::Vector3D<T> _expectedInvertedVec;
//
//    void SetUp() override
//    {
//        _vec = { T(-8), T(0), T(-2) };
//        _expectedInvertedVec = { T(8), T(0), T(2) };
//    }
//};
///** @brief Test fixture for @ref fgm::Vector3D inversion, parameterized by @ref SupportedSignedArithmeticTypes. */
//TYPED_TEST_SUITE(Vector3DInversion, SupportedSignedArithmeticTypes);
//
//
///** @brief Test fixture for @fgm::Vector3D division with NaN vectors. */
//class Vector3DDivisionNaNTests: public ::testing::TestWithParam<fgm::Vector3D<float>>
//{};
//INSTANTIATE_TEST_SUITE_P(Vector3DDivisionTestSuite, Vector3DDivisionNaNTests,
//                         ::testing::Values(fgm::Vector3D<float>(fgm::constants::NaN, 3.0f, 3.0f),
//                                           fgm::Vector3D<float>(3.0f, fgm::constants::NaN, 3.0f),
//                                           fgm::Vector3D<float>(3.0f, 3.0f, fgm::constants::NaN),
//                                           fgm::Vector3D<float>(fgm ::constants::NaN, fgm::constants::NaN,
//                                                                fgm ::constants::NaN)));
//
//
//
///**
// * @addtogroup T_FGM_Vec3_Addition
// * @{
// */
//
///**************************************
// *                                    *
// *           ADDITION TESTS           *
// *                                    *
// **************************************/
//
///**
// * @test Verify that the binary addition operator perform a component-wise addition and
// *       returns a new vector instance.
// */
//TYPED_TEST(Vector3DAddition, PlusOperator_ReturnsVectorSum)
//{
//    const fgm::Vector3D result = this->_vecA + this->_vecB;
//
//    EXPECT_VEC_EQ(this->_expectedSum, result);
//}
//
//
///**
// * @test Verify that the compound addition assignment operator perform a component-wise addition and
// *       mutates the vector in-place.
// */
//TYPED_TEST(Vector3DAddition, PlusEqualsOperator_ReturnsSameVectorWithSum)
//{
//    this->_vecA += this->_vecB;
//
//    EXPECT_VEC_EQ(this->_expectedSum, this->_vecA);
//}
//
//
///**
// * @test Verify that the binary addition operator perform automatic type promotion
// *       to the wider numeric type.
// */
//TEST(Vector3DAddition, MixedTypeAdditionPromotesType)
//{
//    constexpr fgm::Vector3D vec1(3.0f, 0.0f, -1.0f);
//    constexpr fgm::Vector3D vec2(9.0, -5.0, 10.0);
//
//    [[maybe_unused]] constexpr fgm::Vector3D result = vec1 + vec2;
//
//    static_assert(std::is_same_v<decltype(result)::value_type, double>);
//}
//
//
///**
// * @test Verify that the compound addition assignment operator maintains the destination type and
// *       perform an implicit cast.
// */
//TEST(Vector3DAddition, MixedTypeAdditionAssignmentDoesNotPromoteType)
//{
//    fgm::Vector3D vec1(3.0f, 0.0f, -1.0f);
//    constexpr fgm::Vector3D vec2(9.0, -5.0, 10.0);
//
//    vec1 += vec2;
//
//    static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
//}
//
///** @} */
//
//
//
///**
// * @addtogroup T_FGM_Vec3_Subtraction
// * @{
// */
//
///**************************************
// *                                    *
// *          SUBTRACTION TESTS         *
// *                                    *
// **************************************/
//
///**
// * @test Verify that the binary subtraction operator perform a component-wise subtraction and
// *       returns a new vector instance.
// */
//TYPED_TEST(Vector3DSubtraction, MinusOperator_ReturnsDifference)
//{
//    const fgm::Vector3D result = this->_vecA - this->_vecB;
//
//    EXPECT_VEC_EQ(this->_expectedDifference, result);
//}
//
//
///**
// * @test Verify that the compound subtraction assignment operator perform a component-wise subtraction
// *       and mutates the vector in-place.
// */
//TYPED_TEST(Vector3DSubtraction, MinusEqualsOperator_ReturnsSameVectorWithDifference)
//{
//    this->_vecA -= this->_vecB;
//
//    EXPECT_VEC_EQ(this->_expectedDifference, this->_vecA);
//}
//
//
///**
// * @test Verify that the binary subtraction operator perform automatic type promotion
// *       to the wider numeric type.
// */
//TEST(Vector3DSubtraction, MixedTypeSubtractionPromotesType)
//{
//    constexpr fgm::Vector3D vec1(3.0f, 0.0f, -1.0f);
//    constexpr fgm::Vector3D vec2(9.0, -5.0, 10.0);
//
//    [[maybe_unused]] constexpr fgm::Vector3D result = vec1 - vec2;
//
//    static_assert(std::is_same_v<decltype(result)::value_type, double>);
//}
//
//
///**
// * @test Verify that the compound subtraction assignment operator maintains the destination type and
// *       perform an implicit cast.
// */
//TEST(Vector3DSubtraction, MixedTypeSubtractionAssignmentDoesNotPromoteType)
//{
//    fgm::Vector3D vec1(3.0f, 0.0f, -1.0f);
//    constexpr fgm::Vector3D vec2(9.0, -5.0, 10.0);
//
//    vec1 -= vec2;
//
//    static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
//}
//
///** @} */
//
//
//
///**
// * @addtogroup T_FGM_Vec3_Multiplication
// * @{
// */
//
///**************************************
// *                                    *
// *     SCALAR MULTIPLICATION TESTS    *
// *                                    *
// **************************************/
//
///** @test Verify that scalar multiplication by zero returns a zero vector. */
//TEST(Vector3DScalarMultiplication, MultiplicationByZeroReturnsZeroVector)
//{
//    constexpr fgm::Vector3D vec(3.0f, 1.0f, 6.0f);
//
//    constexpr fgm::Vector3D result = vec * 0;
//
//    EXPECT_VEC_ZERO(result);
//}
//
//
///** @test Verify that scalar multiplication by one returns original vector. */
//TEST(Vector3DScalarMultiplication, MultiplicationByOneReturnsOriginalVector)
//{
//    constexpr fgm::Vector3D vec(3.0f, 1.0f, 6.0f);
//
//    constexpr fgm::Vector3D result = vec * 1;
//
//    EXPECT_VEC_EQ(vec, result);
//}
//
//
///**
// * @test Verify that the binary multiplication operator (vector * scalar) perform a component-wise (Hadamard) product
// *       and returns a new vector instance.
// */
//TYPED_TEST(Vector3DScalarMultiplication, VectorTimesScalarReturnsScaledVector)
//{
//    const fgm::Vector3D result = this->_vec * this->_scalar;
//
//    if (std::is_floating_point_v<TypeParam>)
//        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
//    else
//        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
//}
//
//
///**
// * @test Verify that the binary multiplication operator (scalar * vector) perform a component-wise (Hadamard) product
// *       and returns a new vector instance.
// */
//TYPED_TEST(Vector3DScalarMultiplication, ScalarTimesAVectorReturnsScaledVector)
//{
//    const fgm::Vector3D result = this->_scalar * this->_vec;
//
//    if (std::is_floating_point_v<TypeParam>)
//        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
//    else
//        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
//}
//
//
///**
// * @test Verify that the compound multiplication assignment operator performs a component-wise (Hadamard) product
// *       and mutates the vector in-place.
// */
//TYPED_TEST(Vector3DScalarMultiplication, VectorTimesEqualScalarIsTheSameVectorScaled)
//{
//    this->_vec *= this->_scalar;
//
//    if (std::is_floating_point_v<TypeParam>)
//        EXPECT_VEC_EQ(this->_expectedFloatingVec, this->_vec);
//    else
//        EXPECT_VEC_EQ(this->_expectedIntegralVec, this->_vec);
//}
//
//
///**
// * @test Verify that the binary multiplication operator perform automatic type promotion
// *       to the wider numeric type.
// */
//TYPED_TEST(Vector3DScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
//{
//    constexpr double scalar = 2.123456789123456;
//
//    [[maybe_unused]] const fgm::Vector3D result = this->_vec * scalar;
//
//    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
//}
//
//
///**
// * @test Verify that the compound multiplication assignment operator maintains the destination type and
// *       perform an implicit cast.
// */
//TEST(Vector3DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
//{
//    fgm::Vector3D vec(3.0f, 0.0f, -1.0f);
//    constexpr double scalar = 5.0;
//    vec *= scalar;
//
//    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
//}
//
//
///**
// * @test Verify that the compound multiplication operator for mixed types
// *       ensure minimal precision loss.
// */
//TEST(Vector3DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
//{
//    fgm::Vector3D vec(3, 0, -1);
//    constexpr double scalar = 2.5;
//    constexpr fgm::Vector3D expected(7, 0, -2);
//
//    vec *= scalar;
//
//    EXPECT_VEC_EQ(expected, vec);
//}
//
///** @} */
//
//
//
///**
// * @addtogroup T_FGM_Vec3_Division
// * @{
// */
//
///**************************************
// *                                    *
// *        SCALAR DIVISION TESTS       *
// *                                    *
// **************************************/
//
///**
// * @test Verify that dividing a float vector by zero returns an
// *       infinity vector of float type.
// */
//TEST(Vector3DScalarDivision, FloatVectorDivisionByZeroReturnsInfinityVector)
//{
//    constexpr fgm::Vector3D vec(1.0f, 2.0f, 3.0f);
//    EXPECT_VEC_INF(vec / 0);
//}
//
//
///**
// * @test Verify that dividing a double vector by zero returns an
// *       infinity vector of double type.
// */
//TEST(Vector3DScalarDivision, DoubleVectorDivisionByZeroReturnsInfinityVector)
//{
//    constexpr fgm::Vector3D vec(1.0, 2.0, 3.0);
//    EXPECT_VEC_INF(vec / 0);
//}
//
//
///** @test Verify that dividing a vector by one returns the original vector. */
//TYPED_TEST(Vector3DScalarDivision, DivisionByOneReturnsOriginalVector)
//{
//    const fgm::Vector3D result = this->_vec / 1;
//
//    EXPECT_VEC_EQ(result, this->_vec);
//}
//
//
///**
// * @test Verify that the binary division operator (vector / scalar) perform a component-wise divide and
// *       returns a vector instance.
// */
//TYPED_TEST(Vector3DScalarDivision, ScalarDivision_ReturnsInverseScaledVector)
//{
//    const fgm::Vector3D result = this->_vec / this->_scalar;
//
//    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
//}
//
//
///**
// * @test Verify that the compound division assignment operator perform a component-wise divide and
// *       mutates the vector in-place.
// */
//TYPED_TEST(Vector3DScalarDivision, ScalarDivisionAssignment_ReturnsSameVectorInverseScaled)
//{
//    this->_vec /= this->_scalar;
//
//    EXPECT_VEC_EQ(this->_expectedScaledVec, this->_vec);
//}
//
//
///**
// * @test Verify that the binary division operator perform automatic type promotion
// *       to the wider numeric type.
// */
//TEST(Vector3DScalarDivision, MixedType_ScalarDivision_PromotesType)
//{
//    constexpr fgm::Vector3D vec(15.0, 0.0, -5.0);
//    constexpr double scalar = 5.0;
//
//    [[maybe_unused]] constexpr fgm::Vector3D result = vec / scalar;
//
//    static_assert(std::is_same_v<decltype(result)::value_type, double>);
//}
//
//
///**
// * @test Verify that the compound division assignment operator maintains the destination type and
// *       perform an implicit cast.
// */
//TEST(Vector3DScalarDivision, MixedType_ScalarDivisionAssignment_DoesNotPromoteType)
//{
//    fgm::Vector3D vec(15.0f, 0.0f, -5.0f);
//    constexpr double scalar = 5.0;
//
//    vec /= scalar;
//
//    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
//}
//
//
///** @test Verify that the compound division operator for mixed types ensures minimal precision loss. */
//TEST(Vector3DScalarDivision, MixedType_ScalarDivisionAssignment_ReturnsResultWithMinimalPrecisionLoss)
//{
//    fgm::Vector3D vec(10, 25, -30);
//    constexpr double scalar = 2.5;
//    constexpr fgm::Vector3D expected(4, 10, -12);
//
//    vec /= scalar;
//
//    EXPECT_VEC_EQ(expected, vec);
//}
//
//
///**************************************
// *                                    *
// *        SAFE DIVISION TESTS         *
// *                                    *
// **************************************/
//
///**
// * @test Verify that dividing a vector using @ref fgm::Vector3D::safeDiv perform a component-wise divide and
// *       returns a new vector instance.
// */
//TYPED_TEST(Vector3DScalarDivision, SafeDivide_ReturnsAInverseScaledVector)
//{
//    const auto result = this->_vec.safeDiv(this->_scalar);
//
//    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
//}
//
//
///**
// * @test Verify that dividing a vector by integral zero using @ref fgm::Vector3D::safeDiv
// *       perform a component-wise divide and returns a new vector instance.
// */
//TYPED_TEST(Vector3DScalarDivision, SafeDivideByIntegralZero_ReturnsZeroVector)
//{
//    const auto result = this->_vec.safeDiv(0);
//    EXPECT_VEC_ZERO(result);
//}
//
//
///**
// * @test Verify that dividing a vector by floating point zero using @ref fgm::Vector3D::safeDiv
// *       perform a component-wise divide and returns a new vector instance.
// */
//TYPED_TEST(Vector3DScalarDivision, SafeDivideByFloatZero_ReturnsZeroVector)
//{
//    const auto result = this->_vec.safeDiv(0.0f);
//    EXPECT_VEC_ZERO(result);
//}
//
//
///**
// * @test Verify that dividing a vector using static variant of @ref fgm::Vector3D::safeDiv
// *       perform a component-wise divide and returns a new vector instance.
// */
//TYPED_TEST(Vector3DScalarDivision, StaticWrapper_SafeDivide_ReturnsAInverseScaledVector)
//{
//    const auto result = fgm::Vector3D<TypeParam>::safeDiv(this->_vec, this->_scalar);
//    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
//}
//
//
///**
// * @test Verify that dividing a vector by integral zero using static variant of @ref fgm::Vector3D::safeDiv
// *       perform a component-wise divide and returns a new vector instance.
// */
//TEST(Vector3DScalarDivision, StaticWrapper_SafeDivideByIntergralZero_ReturnsZeroVector)
//{
//    constexpr fgm::Vector3D vec(1, 2, 3);
//    EXPECT_VEC_ZERO(fgm::Vector3D<int>::safeDiv(vec, 0));
//}
//
//
///**
// * @test Verify that dividing a vector by floating point zero using static variant @ref fgm::Vector3D::safeDiv
// *       perform a component-wise divide and returns a new vector instance.
// */
//TYPED_TEST(Vector3DScalarDivision, StaticWrapper_SafeDivideByFloatZero_ReturnsZeroVector)
//{
//    const auto result = fgm::Vector3D<TypeParam>::safeDiv(this->_vec, 0.0f);
//    EXPECT_VEC_ZERO(result);
//}
//
//
///**
// * @test Verify that dividing a vector by NaN using @ref fgm::Vector3D::safeDiv
// *       returns a zero vector.
// */
//TYPED_TEST(Vector3DScalarDivision, SafeDivideByNaN_ReturnsZeroVector)
//{
//    const auto result = this->_vec.safeDiv(fgm::constants::NaN);
//
//    EXPECT_VEC_ZERO(result);
//}
//
//
///**
// * @test Verify that dividing a vector by NaN using static variant of @ref fgm::Vector3D::safeDiv
// *       returns a zero vector.
// */
//TYPED_TEST(Vector3DScalarDivision, StaticWrapper_SafeDivideByNaN_ReturnsZeroVector)
//{
//    const auto result = fgm::Vector3D<TypeParam>::safeDiv(this->_vec, fgm::constants::INFINITY_F);
//
//    EXPECT_VEC_ZERO(result);
//}
//
//
///**************************************
// *                                    *
// *         TRY DIVISION TESTS         *
// *                                    *
// **************************************/
//
///**
// * @test Verify that dividing a vector using @ref fgm::Vector3D::tryDiv perform a component-wise divide and
// *       returns a new vector instance and sets the flag to @ref fgm::OperationStatus::SUCCESS.
// */
//TYPED_TEST(Vector3DScalarDivision, TryDivide_ReturnsAInverseScaledVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    const auto result = this->_vec.tryDiv(this->_scalar, flag);
//
//    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
//    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
//}
//
//
///**
// * @test Verify that dividing a vector by integral zero using @ref fgm::Vector3D::tryDiv returns zero vector and
// *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
// */
//TYPED_TEST(Vector3DScalarDivision, TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    const auto result = this->_vec.tryDiv(0, flag);
//
//    EXPECT_VEC_ZERO(result);
//    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
//}
//
//
///**
// * @test Verify that dividing a vector by floating point zero using @ref fgm::Vector3D::tryDiv returns zero vector and
// *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
// */
//TYPED_TEST(Vector3DScalarDivision, TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    const auto result = this->_vec.tryDiv(0.0, flag);
//
//    EXPECT_VEC_ZERO(result);
//    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
//}
//
//
///**
// * @test Verify that dividing a NaN vector by zero using @ref fgm::Vector3D::tryDiv
// *       @ref fgm::OperationStatus::NANOPERAND takes precedence over @ref fgm::OperationStatus::NANOPERAND.
// */
//TEST(Vector3DScalarDivision, TryDivideNaNVectorByZero_NaNOperandStatusTakesPrecedence)
//{
//    fgm::OperationStatus flag;
//    [[maybe_unused]] const auto result = fgm::vec3d::nan<double>.tryDiv(0, flag);
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
//
///**
// * @test Verify that dividing a vector by NaN using @ref fgm::Vector3D::tryDiv returns a zero vector and
// *       sets the flag to @ref fgm::OperationStatus::NANOPERAND.
// */
//TYPED_TEST(Vector3DScalarDivision, TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    const auto result = this->_vec.tryDiv(fgm::constants::NaN, flag);
//
//    EXPECT_VEC_ZERO(result);
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
//
///**
// * @test Verify that dividing a vector using static variant of @ref fgm::Vector3D::tryDiv
// *       perform a component-wise divide and returns a new vector instance and
// *       sets the flag to @ref fgm::OperationStatus::SUCCESS.
// */
//TYPED_TEST(Vector3DScalarDivision, StaticWrapper_TryDivide_ReturnsAInverseScaledVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    const auto result = fgm::Vector3D<TypeParam>::tryDiv(this->_vec, this->_scalar, flag);
//
//    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
//    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
//}
//
//
///**
// * @test Verify that dividing a vector by integral zero using static variant of @ref fgm::Vector3D::tryDiv
// *       returns zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
// */
//TYPED_TEST(Vector3DScalarDivision, StaticWrapper_TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    const auto result = fgm::Vector3D<TypeParam>::tryDiv(this->_vec, 0, flag);
//
//    EXPECT_VEC_ZERO(result);
//    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
//}
//
//
///**
// * @test Verify that dividing a vector by floating point zero using static variant of @ref fgm::Vector3D::tryDiv
// *       returns zero vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
// */
//TYPED_TEST(Vector3DScalarDivision, StaticWrapper_TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    const auto result = fgm::Vector3D<TypeParam>::tryDiv(this->_vec, 0.0, flag);
//
//    EXPECT_VEC_ZERO(result);
//    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
//}
//
//
///**
// * @test Verify that dividing a vector by floating point zero using static variant of @ref fgm::Vector3D::tryDiv
// *       returns zero vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
// */
//TEST(Vector3DScalarDivision, StaticWrapper_TryDivideNaNVector_ReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    const auto result = fgm::Vector3D<double>::tryDiv(fgm::vec3d::nan<double>, 3, flag);
//
//    EXPECT_VEC_ZERO(result);
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
//
///**
// * @test Verify that dividing a vector by NaN using static variant of @ref fgm::Vector3D::tryDiv returns zero vector and
// *       sets the flag to @ref fgm::OperationStatus::NANOPERAND.
// */
//TYPED_TEST(Vector3DScalarDivision, StaticWrapper_TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    const auto result = fgm::Vector3D<double>::tryDiv(this->_vec, fgm::constants::NaN, flag);
//
//    EXPECT_VEC_ZERO(result);
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
//
///**************************************
// *                                    *
// *         NaN DIVISION TESTS         *
// *                                    *
// **************************************/
//
///**
// * @test Verify that dividing a nan vector by a scalar using @ref fgm::Vector3D::safeDiv
// *       returns vector with NaN-components as zero.
// */
//TEST_P(Vector3DDivisionNaNTests, SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
//{
//    const auto& vec = GetParam();
//    EXPECT_VEC_ZERO(vec.safeDiv(3));
//}
//
///**
// * @test Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Vector3D::safeDiv
// *       returns zero vector.
// */
//TEST_P(Vector3DDivisionNaNTests, StaticWrapper_SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
//{
//    const auto& vec = GetParam();
//    EXPECT_VEC_ZERO(fgm::Vector3D<float>::safeDiv(vec, 3));
//}
//
//
///**
// * @test Verify that dividing a nan vector by a scalar using @ref fgm::Vector3D::tryDiv
// *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
// */
//TEST_P(Vector3DDivisionNaNTests, TryDiv_ReturnsVectorWithNaNComponentsAsZero)
//{
//    const auto& vec = GetParam();
//    fgm::OperationStatus flag;
//    EXPECT_VEC_ZERO(vec.tryDiv(3, flag));
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
//
///**
// * @test Verify that dividing a nan vector by a scalar using static variant of @ref fgm::Vector3D::tryDiv
// *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
// */
//TEST_P(Vector3DDivisionNaNTests, StaticWrapper_TryDiv_ReturnsVectorWithNaNComponentsAsZero)
//{
//    const auto& vec = GetParam();
//    fgm::OperationStatus flag;
//    EXPECT_VEC_ZERO(fgm::Vector3D<float>::tryDiv(vec, 3, flag));
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
///** @} */
//
//
//
///**
// * @addtogroup T_FGM_Vec3_Inversion
// * @{
// */
//
///**
// * @test Verify that  @ref fgm::Vector3D unary minus operator inverts each component and
// * returns a new vector.
// */
//TYPED_TEST(Vector3DInversion, InvertsTheSignOfEachComponents)
//{
//    const fgm::Vector3D inverted = -this->_vec;
//    EXPECT_VEC_EQ(this->_expectedInvertedVec, inverted);
//}
//
//
///** @test Verify that @ref fgm::Vector3D unary minus operator inverts each component of an infinity vector. */
//TEST(Vector3DInversion, InvertsSignOfInfinity)
//{
//    constexpr fgm::Vector3D infVec = {
//        fgm::constants::INFINITY_F,
//        -fgm::constants::INFINITY_F,
//        fgm::constants::INFINITY_F,
//    };
//    constexpr fgm::Vector3D expected = {
//        -fgm::constants::INFINITY_F,
//        fgm::constants::INFINITY_F,
//        -fgm::constants::INFINITY_F,
//    };
//
//    constexpr fgm::Vector3D<float> inverted = -infVec;
//
//    EXPECT_VEC_EQ(expected, inverted);
//}
//
//
///** @test Verify that @ref fgm::Vector3D unary minus follows IEEE 754 rules for NaN. */
//TEST(Vector3DInversion, NoOpOnNaNVectors)
//{
//    constexpr fgm::Vector3D nanVec = {
//        fgm::constants::NaN,
//        fgm::constants::NaN,
//        fgm::constants::NaN,
//    };
//
//    constexpr fgm::Vector3D<float> inverted = -nanVec;
//
//    EXPECT_TRUE(std::isnan(inverted.x));
//    EXPECT_TRUE(std::isnan(inverted.y));
//    EXPECT_TRUE(std::isnan(inverted.z));
//}
//
///** @} */
