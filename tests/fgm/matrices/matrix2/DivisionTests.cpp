/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 13, 2026
 *
 * @brief Verify @ref fgm::Matrix2 division logic.
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
class Matrix2Division: public ::testing::Test
{
protected:
    fgm::Matrix2<T> _matrix;
    T _scalar;
    fgm::Matrix2<T> _expectedMatrix;

    void SetUp() override
    {
        _matrix         = { fgm::Vec2<T>{ 7, 3 }, fgm::Vec2<T>{ 1, 6 } };
        _scalar         = T(3);
        _expectedMatrix = { fgm::Vec2{ T(2.333333333333333), T(1) }, fgm::Vec2{ T(0.3333333333333333), T(2) } };
    }
};
/** Test fixture for @ref fgm::Matrix2 division, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Matrix2Division, SupportedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Matrix2 division with NaN vectors. */
class NaNMatrix2Division: public ::testing::TestWithParam<fgm::Matrix2<float>>
{};
INSTANTIATE_TEST_SUITE_P(Matrix2DivisionTestSuite, NaNMatrix2Division,
                         ::testing::Values(fgm::Matrix2<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                                           fgm::Matrix2<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                                           fgm::Matrix2<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                                           fgm::Matrix2<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                                           fgm::Matrix2<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                               fgm ::constants::NaN, fgm ::constants::NaN)));



/**
 * @addtogroup T_FGM_Mat2x2_Division
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
    constexpr fgm::Matrix2 MAT(2, 4, 6, 8);

    // Matrix scalar division
    constexpr fgm::Matrix2 DIV_RESULT_1 = MAT / 2;
    static_assert(DIV_RESULT_1(0, 0) == 1);
    static_assert(DIV_RESULT_1(0, 1) == 2);
    static_assert(DIV_RESULT_1(1, 0) == 3);
    static_assert(DIV_RESULT_1(1, 1) == 4);

    // Matrix safe division
    constexpr fgm::Matrix2 DIV_RESULT_2 = MAT.safeDiv(2);
    static_assert(DIV_RESULT_2(0, 0) == 1);
    static_assert(DIV_RESULT_2(0, 1) == 2);
    static_assert(DIV_RESULT_2(1, 0) == 3);
    static_assert(DIV_RESULT_2(1, 1) == 4);

    constexpr fgm::Matrix2 DIV_RESULT_3 = fgm::Matrix2<int>::safeDiv(MAT, 2);
    static_assert(DIV_RESULT_3(0, 0) == 1);
    static_assert(DIV_RESULT_3(0, 1) == 2);
    static_assert(DIV_RESULT_3(1, 0) == 3);
    static_assert(DIV_RESULT_3(1, 1) == 4);

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
TYPED_TEST(Matrix2Division, DivideOperator_ReturnsInverseScaledMatrix)
{
    const fgm::Matrix2 inverseScaledMat = this->_matrix / this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Matrix2Division, DivideOperator_ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), "");
}

#endif


/**
 * @brief Verify that the compound division operator perform an element-wise divide
 *        and mutates the matrix in-place.
 */
TYPED_TEST(Matrix2Division, DivideEqualsOperator_InverseScalesMatrixInPlace)
{
    fgm::Matrix2 matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Matrix2Division, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(this->_matrix /= 0, "");
}

#endif


/**************************************
 *                                    *
 *         SAFE DIVISION TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a matrix using @ref fgm::Matrix2::safeDiv perform an element-wise divide
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix2Division, SafeDivide_ReturnsInverseScaledMatrix)
{
    const fgm::Matrix2 inverseScaledMat = this->_matrix.safeDiv(this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix2::safeDiv
 *        returns identity matrix by default.
 */
TYPED_TEST(Matrix2Division, SafeDivide_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Matrix2 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix2::safeDiv
 *        returns passed-in fallback.
 */
TYPED_TEST(Matrix2Division, SafeDivide_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Matrix2 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0), fgm::Matrix2<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix2::safeDiv
 *        returns identity matrix by default.
 */
TEST_P(NaNMatrix2Division, SafeDivide_ReturnsIdentityMatrixByDefault)
{
    const fgm::Matrix2 inverseScaledMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix2::safeDiv
 *        returns passed-in fallback.
 */
TEST_P(NaNMatrix2Division, SafeDivide_ReturnsPassedInFallback)
{
    const fgm::Matrix2 inverseScaledMat = GetParam().safeDiv(2.5, fgm::Matrix2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Matrix2::safeDiv
 *        perform an element-wise divide and returns a new matrix instance.
 */
TYPED_TEST(Matrix2Division, SafeDivide_StaticWrapper_ReturnsInverseScaledMatrix)
{
    const fgm::Matrix2 inverseScaledMat = fgm::Matrix2<TypeParam>::safeDiv(this->_matrix, this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix2::safeDiv
 *        returns identity matrix by default.
 */
TYPED_TEST(Matrix2Division, StaticWrapper_SafeDivide_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Matrix2 inverseScaledMat = fgm::Matrix2<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix2::safeDiv
 *        returns passed-in fallback.
 */
TYPED_TEST(Matrix2Division, StaticWrapper_SafeDivide_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Matrix2 inverseScaledMat =
        fgm::Matrix2<TypeParam>::safeDiv(this->_matrix, TypeParam(0), fgm::Matrix2<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix2::safeDiv
 *        returns identity matrix by default.
 */
TEST_P(NaNMatrix2Division, StaticWrapper_SafeDivide_ReturnsIdentityMatrixByDefault)
{
    using T                             = ParamType::value_type;
    const fgm::Matrix2 inverseScaledMat = fgm::Matrix2<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix2::safeDiv
 *        returns passed-in fallback.
 */
TEST_P(NaNMatrix2Division, StaticWrapper_SafeDivide_ReturnsPassedInFallback)
{
    using T                             = ParamType::value_type;
    const fgm::Matrix2 inverseScaledMat = fgm::Matrix2<T>::safeDiv(GetParam(), 2.5, fgm::Matrix2<T>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**************************************
 *                                    *
 *         TRY DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a matrix using @ref fgm::Matrix2::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Matrix2Division, TryDivide_ReturnsInverseScaledMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2 inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix2::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Matrix2Division, TryDivide_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix2::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Matrix2Division, TryDivide_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag, fgm::Matrix2<TypeParam>::zero());

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix2::tryDiv returns identity matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2Division, TryDivide_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2 inverseScaledMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2Division, TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2 inverseScaledMat = GetParam().tryDiv(2.5, flag, fgm::Matrix2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using @ref fgm::Matrix2::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2Division, TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Matrix2 inverseScaledMat =
        GetParam().tryDiv(0, flag, fgm::Matrix2<ParamType::value_type>::zero());
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Matrix2::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Matrix2Division, StaticWrapper_TryDivide_ReturnsInverseScaledMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2 inverseScaledMat = fgm::Matrix2<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix2::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Matrix2Division, StaticWrapper_TryDivide_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2 inverseScaledMat = fgm::Matrix2<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Matrix2Division, StaticWrapper_TryDivide_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2 inverseScaledMat =
        fgm::Matrix2<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, fgm::Matrix2<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix2::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2Division, StaticWrapper_TryDivide_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    using T                             = ParamType::value_type;
    const fgm::Matrix2 inverseScaledMat = fgm::Matrix2<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);

    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using the static variant of @ref fgm::Matrix2::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2Division, StaticWrapper_TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    using T                                              = ParamType::value_type;
    [[maybe_unused]] const fgm::Matrix2 inverseScaledMat = fgm::Matrix2<T>::tryDiv(GetParam(), T(0), flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2Division, StaticWrapper_TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    const fgm::Matrix2 inverseScaledMat =
        fgm::Matrix2<T>::tryDiv(GetParam(), 2.5, flag, fgm::Matrix2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
