/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify @ref fgm::Matrix4 division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Matrix4Division: public ::testing::Test
{
protected:
    fgm::Matrix4<T> _matrix;
    T _scalar;
    fgm::Matrix4<T> _expectedMatrix;


    void SetUp() override
    {
        _matrix         = { { T(17), T(13), T(15), T(12) },
                            { T(11), T(16), T(35), T(101) },
                            { T(27), T(44), T(56), T(23) },
                            { T(5), T(6), T(11), T(31) } };
        _scalar         = T(7);
        _expectedMatrix = {
            { T(2.428571428571428), T(1.857142857142857), T(2.142857142857143), T(1.714285714285714) },
            { T(1.571428571428571), T(2.285714285714286), T(5.0), T(14.428571428571429) },
            { T(3.857142857142857), T(6.285714285714286), T(8.0), T(3.285714285714286) },
            { T(0.714285714285714), T(0.857142857142857), T(1.571428571428571), T(4.428571428571429) },
        };
    }
};
/** Test fixture for @ref fgm::Matrix4 division, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Matrix4Division, SupportedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Matrix4 division with NaN vectors. */
class NaNMatrix4Division: public ::testing::TestWithParam<fgm::Matrix4<float>>
{};
INSTANTIATE_TEST_SUITE_P(Matrix4DivisionTestSuite, NaNMatrix4Division,
                         ::testing::Values(fgm::Matrix4<float>{ fgm::constants::NaN, 3.0f, 3.0f, 3.0f },
                                           fgm::Matrix4<float>{ 3.0f, fgm::constants::NaN, 3.0f, 3.0f },
                                           fgm::Matrix4<float>{ 3.0f, 3.0f, fgm::constants::NaN, 3.0f },
                                           fgm::Matrix4<float>{ 3.0f, 3.0f, 3.0f, fgm::constants::NaN },
                                           fgm::Matrix4<float>{ fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN, fgm ::constants::NaN }));

/**
 * @addtogroup T_FGM_Mat4x4_Division
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that matrix division operations are available at compile time. */
namespace
{
    constexpr fgm::Matrix4 MAT(2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32);

    // Matrix scalar division
    constexpr fgm::Matrix4 DIV_RESULT_1 = MAT / 2;
    static_assert(DIV_RESULT_1(0, 0) == 1);
    static_assert(DIV_RESULT_1(0, 1) == 2);
    static_assert(DIV_RESULT_1(0, 2) == 3);
    static_assert(DIV_RESULT_1(0, 3) == 4);
    static_assert(DIV_RESULT_1(1, 0) == 5);
    static_assert(DIV_RESULT_1(1, 1) == 6);
    static_assert(DIV_RESULT_1(1, 2) == 7);
    static_assert(DIV_RESULT_1(1, 3) == 8);
    static_assert(DIV_RESULT_1(2, 0) == 9);
    static_assert(DIV_RESULT_1(2, 1) == 10);
    static_assert(DIV_RESULT_1(2, 2) == 11);
    static_assert(DIV_RESULT_1(2, 3) == 12);
    static_assert(DIV_RESULT_1(3, 0) == 13);
    static_assert(DIV_RESULT_1(3, 1) == 14);
    static_assert(DIV_RESULT_1(3, 2) == 15);
    static_assert(DIV_RESULT_1(3, 3) == 16);


    // Matrix Safe Division
    constexpr fgm::Matrix4 DIV_RESULT_2 = MAT.safeDiv(2);
    static_assert(DIV_RESULT_2(0, 0) == 1);
    static_assert(DIV_RESULT_2(0, 1) == 2);
    static_assert(DIV_RESULT_2(0, 2) == 3);
    static_assert(DIV_RESULT_2(0, 3) == 4);
    static_assert(DIV_RESULT_2(1, 0) == 5);
    static_assert(DIV_RESULT_2(1, 1) == 6);
    static_assert(DIV_RESULT_2(1, 2) == 7);
    static_assert(DIV_RESULT_2(1, 3) == 8);
    static_assert(DIV_RESULT_2(2, 0) == 9);
    static_assert(DIV_RESULT_2(2, 1) == 10);
    static_assert(DIV_RESULT_2(2, 2) == 11);
    static_assert(DIV_RESULT_2(2, 3) == 12);
    static_assert(DIV_RESULT_2(3, 0) == 13);
    static_assert(DIV_RESULT_2(3, 1) == 14);
    static_assert(DIV_RESULT_2(3, 2) == 15);
    static_assert(DIV_RESULT_2(3, 3) == 16);

    constexpr fgm::Matrix4 DIV_RESULT_3 = fgm::Matrix4<int>::safeDiv(MAT, 2);
    static_assert(DIV_RESULT_3(0, 0) == 1);
    static_assert(DIV_RESULT_3(0, 1) == 2);
    static_assert(DIV_RESULT_3(0, 2) == 3);
    static_assert(DIV_RESULT_3(0, 3) == 4);
    static_assert(DIV_RESULT_3(1, 0) == 5);
    static_assert(DIV_RESULT_3(1, 1) == 6);
    static_assert(DIV_RESULT_3(1, 2) == 7);
    static_assert(DIV_RESULT_3(1, 3) == 8);
    static_assert(DIV_RESULT_3(2, 0) == 9);
    static_assert(DIV_RESULT_3(2, 1) == 10);
    static_assert(DIV_RESULT_3(2, 2) == 11);
    static_assert(DIV_RESULT_3(2, 3) == 12);
    static_assert(DIV_RESULT_3(3, 0) == 13);
    static_assert(DIV_RESULT_3(3, 1) == 14);
    static_assert(DIV_RESULT_3(3, 2) == 15);
    static_assert(DIV_RESULT_3(3, 3) == 16);


    // Matrix Try Division
    // NOT available at compile time due to [out] parameter (OperationStatus).
} // namespace



/**************************************
 *                                    *
 *      DIVISION TESTS (RUNTIME)      *
 *                                    *
 **************************************/

/**
 * @brief Verify that the binary division operator perform an element-wise divide
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix4Division, DivideOperator_ReturnsInverseScaledMatrix)
{
    const fgm::Matrix4 inverseScaledMat = this->_matrix / this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


#ifdef ENABLE_DEBUG_TESTS
/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Matrix4Division, DivideOperator_ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), "");
}
#endif


/**
 * @brief Verify that the compound division operator perform an element-wise divide
 *        and mutates the matrix in-place.
 */
TYPED_TEST(Matrix4Division, DivideEqualsOperator_InverseScalesMatrixInPlace)
{
    fgm::Matrix4 matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Matrix4Division, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix /= 0), "");
}

#endif


/**************************************
 *                                    *
 *         SAFE DIVISION TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a matrix using @ref fgm::Matrix4::safeDiv perform an element-wise divide
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix4Division, SafeDivide_ReturnsInverseScaledMatrix)
{
    const fgm::Matrix4 inverseScaledMat = this->_matrix.safeDiv(this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix4::safeDiv
 *        returns identity matrix by default.
 */
TYPED_TEST(Matrix4Division, SafeDivide_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Matrix4 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix4::safeDiv
 *        returns passed-in fallback.
 */
TYPED_TEST(Matrix4Division, SafeDivide_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Matrix4 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0), fgm::Matrix4<TypeParam>::ZERO());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix4::safeDiv
 *        returns identity matrix by default.
 */
TEST_P(NaNMatrix4Division, SafeDivide_ReturnsIdentityMatrixByDefault)
{
    const fgm::Matrix4 inverseScaledMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix4::safeDiv
 *        returns passed-in fallback.
 */
TEST_P(NaNMatrix4Division, SafeDivide_ReturnsPassedInFallback)
{
    const fgm::Matrix4 inverseScaledMat = GetParam().safeDiv(2.5, fgm::Matrix4<ParamType::value_type>::ZERO());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Matrix4::safeDiv
 *        perform an element-wise divide and returns a new matrix instance.
 */
TYPED_TEST(Matrix4Division, StaticWrapper_SafeDivide_ReturnsInverseScaledMatrix)
{
    const fgm::Matrix4 inverseScaledMat = fgm::Matrix4<TypeParam>::safeDiv(this->_matrix, this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix4::safeDiv
 *        returns identity matrix by default.
 */
TYPED_TEST(Matrix4Division, StaticWrapper_SafeDivide_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Matrix4 inverseScaledMat = fgm::Matrix4<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix4::safeDiv
 *        returns passed-in fallback.
 */
TYPED_TEST(Matrix4Division, StaticWrapper_SafeDivide_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Matrix4 inverseScaledMat =
        fgm::Matrix4<TypeParam>::safeDiv(this->_matrix, TypeParam(0), fgm::Matrix4<TypeParam>::ZERO());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix4::safeDiv
 *        returns identity matrix by default.
 */
TEST_P(NaNMatrix4Division, StaticWrapper_SafeDivide_ReturnsIdentityMatrixByDefault)
{
    using T                             = ParamType::value_type;
    const fgm::Matrix4 inverseScaledMat = fgm::Matrix4<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix4::safeDiv
 *        returns passed-in fallback.
 */
TEST_P(NaNMatrix4Division, StaticWrapper_SafeDivide_ReturnsPassedInFallback)
{
    using T                             = ParamType::value_type;
    const fgm::Matrix4 inverseScaledMat = fgm::Matrix4<T>::safeDiv(GetParam(), 2.5, fgm::Matrix4<T>::ZERO());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**************************************
 *                                    *
 *         TRY DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a matrix using @ref fgm::Matrix4::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Matrix4Division, TryDivide_ReturnsInverseScaledMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix4 inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix4::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Matrix4Division, TryDivide_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix4 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix4::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Matrix4Division, TryDivide_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix4 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag, fgm::Matrix4<TypeParam>::ZERO());

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix4::tryDiv returns identity matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix4Division, TryDivide_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const fgm::Matrix4 inverseScaledMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix4::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix4Division, TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const fgm::Matrix4 inverseScaledMat = GetParam().tryDiv(2.5, flag, fgm::Matrix4<ParamType::value_type>::ZERO());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using @ref fgm::Matrix4::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix4Division, TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Matrix4 inverseScaledMat =
        GetParam().tryDiv(0, flag, fgm::Matrix4<ParamType::value_type>::ZERO());
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Matrix4::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Matrix4Division, StaticWrapper_TryDivide_ReturnsInverseScaledMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix4 inverseScaledMat = fgm::Matrix4<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix4::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Matrix4Division, StaticWrapper_TryDivide_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix4 inverseScaledMat = fgm::Matrix4<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix4::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Matrix4Division, StaticWrapper_TryDivide_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix4 inverseScaledMat =
        fgm::Matrix4<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, fgm::Matrix4<TypeParam>::ZERO());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix4::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix4Division, StaticWrapper_TryDivide_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    using T                             = ParamType::value_type;
    const fgm::Matrix4 inverseScaledMat = fgm::Matrix4<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);

    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using the static variant of @ref fgm::Matrix4::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix4Division, StaticWrapper_TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    using T                                              = ParamType::value_type;
    [[maybe_unused]] const fgm::Matrix4 inverseScaledMat = fgm::Matrix4<T>::tryDiv(GetParam(), static_cast<T>(0), flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix4::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix4Division, StaticWrapper_TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    const fgm::Matrix4 inverseScaledMat =
        fgm::Matrix4<T>::tryDiv(GetParam(), 2.5, flag, fgm::Matrix4<ParamType::value_type>::ZERO());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
