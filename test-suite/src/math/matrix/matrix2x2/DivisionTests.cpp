/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 13, 2026
 *
 * @brief Verify @ref fgm::Matrix2D division logic.
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
class Matrix2DDivision: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _matrix;
    T _scalar;
    fgm::Matrix2D<fgm::Magnitude<T>> _expectedMatrix;
    fgm::Matrix2D<T> _expectedTypedMatrix;

    void SetUp() override
    {
        _matrix = { fgm::Vector2D<T>{ 7, 3 }, fgm::Vector2D<T>{ 1, 6 } };
        _scalar = T(3);
        _expectedMatrix = { fgm::Vector2D{ fgm::Magnitude<T>(2.333333333333333), fgm::Magnitude<T>(1) },
                            fgm::Vector2D{ fgm::Magnitude<T>(0.3333333333333333), fgm::Magnitude<T>(2) } };
        _expectedTypedMatrix = { fgm::Vector2D{ T(2.333333333333333), T(1) },
                                 fgm::Vector2D{ T(0.3333333333333333), T(2) } };
    }
};
/** Test fixture for @ref fgm::Matrix2D division, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Matrix2DDivision, SupportedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Matrix2D division with NaN vectors. */
class NaNMatrix2DDivision: public ::testing::TestWithParam<fgm::Matrix2D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Matrix2DDivisionTestSuite, NaNMatrix2DDivision,
                         ::testing::Values(fgm::Matrix2D<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                                           fgm::Matrix2D<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                                           fgm::Matrix2D<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                                           fgm::Matrix2D<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                                           fgm::Matrix2D<float>(fgm ::constants::NaN, fgm::constants::NaN,
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
    constexpr fgm::Matrix2D MAT(2, 4, 6, 8);

    // Matrix scalar division
    // constexpr fgm::Matrix2D DIV_RESULT_1 = MAT / 2;
    // static_assert(DIV_RESULT_1(0, 0) == 1);
    // static_assert(DIV_RESULT_1(0, 1) == 2);
    // static_assert(DIV_RESULT_1(1, 0) == 3);
    // static_assert(DIV_RESULT_1(1, 1) == 4);
    // TODO: Add back static tests after implementing custom abs function
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
TYPED_TEST(Matrix2DDivision, ReturnsInverseScaledMatrix)
{
    const fgm::Matrix2D inverseScaledMat = this->_matrix / this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/** @brief Verify that the binary division operator always return a floating-point matrix. */
TYPED_TEST(Matrix2DDivision, AlwaysReturnFloatingPointMatrix)
{
    [[maybe_unused]] const fgm::Matrix2D inverseScaledMat = this->_matrix / this->_scalar;
    static_assert(std::is_floating_point_v<typename decltype(inverseScaledMat)::value_type>);
}


/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Matrix2DDivision, ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(this->_matrix / 0, "Matrix division by zero");
}


/**
 * @brief Verify that the compound division operator perform an element-wise divide
 *        and mutates the matrix in-place.
 */
TYPED_TEST(Matrix2DDivision, CompoundDivision_InverseScalesMatrixInPlace)
{
    fgm::Matrix2D matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedTypedMatrix, matrix);
}


/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Matrix2DDivision, CompoundDivision_ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(this->_matrix /= 0, "Matrix division by zero");
}


/**************************************
 *                                    *
 *         SAFE DIVISION TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a matrix using @ref fgm::Matrix2D::safeDiv perform an element-wise divide
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix2DDivision, SafeDivide_ReturnsInverseScaledMatrix)
{
    const fgm::Matrix2D inverseScaledMat = this->_matrix.safeDiv(this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix using @ref fgm::Matrix2D::safeDiv always
 *        return a floating-point matrix.
 */
TYPED_TEST(Matrix2DDivision, SafeDivide_AlwaysReturnFloatingPointMatrix)
{
    [[maybe_unused]] const fgm::Matrix2D inverseScaledMat = this->_matrix.safeDiv(this->_scalar);
    static_assert(std::is_floating_point_v<typename decltype(inverseScaledMat)::value_type>);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix2D::safeDiv
 *        returns identity matrix by default.
 */
TYPED_TEST(Matrix2DDivision, SafeDivide_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Matrix2D inverseScaledMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix2D::safeDiv
 *        returns passed-in fallback.
 */
TYPED_TEST(Matrix2DDivision, SafeDivide_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Matrix2D inverseScaledMat = this->_matrix.safeDiv(TypeParam(0), fgm::mat2d::zero<TypeParam>);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix2D::safeDiv
 *        returns identity matrix by default.
 */
TEST_P(NaNMatrix2DDivision, SafeDivide_ReturnsIdentityMatrixByDefault)
{
    const fgm::Matrix2D inverseScaledMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix2D::safeDiv
 *        returns passed-in fallback.
 */
TEST_P(NaNMatrix2DDivision, SafeDivide_ReturnsPassedInFallback)
{
    const fgm::Matrix2D inverseScaledMat = GetParam().safeDiv(2.5, fgm::mat2d::zero<ParamType::value_type>);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Matrix2D::safeDiv
 *        perform an element-wise divide and returns a new matrix instance.
 */
TYPED_TEST(Matrix2DDivision, SafeDivide_StaticWrapper_ReturnsInverseScaledMatrix)
{
    const fgm::Matrix2D inverseScaledMat = fgm::Matrix2D<TypeParam>::safeDiv(this->_matrix, this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Matrix2D::safeDiv always
 *        return a floating-point matrix.
 */
TYPED_TEST(Matrix2DDivision, SafeDivide_StaticWrapper_AlwaysReturnFloatingPointMatrix)
{
    [[maybe_unused]] const fgm::Matrix2D inverseScaledMat =
        fgm::Matrix2D<TypeParam>::safeDiv(this->_matrix, this->_scalar);
    static_assert(std::is_floating_point_v<typename decltype(inverseScaledMat)::value_type>);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix2D::safeDiv
 *        returns identity matrix by default.
 */
TYPED_TEST(Matrix2DDivision, SafeDivide_StaticWrapper_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Matrix2D inverseScaledMat = fgm::Matrix2D<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix2D::safeDiv
 *        returns passed-in fallback.
 */
TYPED_TEST(Matrix2DDivision, SafeDivide_StaticWrapper_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Matrix2D inverseScaledMat =
        fgm::Matrix2D<TypeParam>::safeDiv(this->_matrix, TypeParam(0), fgm::mat2d::zero<TypeParam>);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix2D::safeDiv
 *        returns identity matrix by default.
 */
TEST_P(NaNMatrix2DDivision, SafeDivide_StaticWrapper_ReturnsIdentityMatrixByDefault)
{
    using T = ParamType::value_type;
    const fgm::Matrix2D inverseScaledMat = fgm::Matrix2D<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix2D::safeDiv
 *        returns passed-in fallback.
 */
TEST_P(NaNMatrix2DDivision, SafeDivide_StaticWrapper_ReturnsPassedInFallback)
{
    using T = ParamType::value_type;
    const fgm::Matrix2D inverseScaledMat = fgm::Matrix2D<T>::safeDiv(GetParam(), 2.5, fgm::mat2d::zero<T>);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**************************************
 *                                    *
 *         TRY DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a matrix using @ref fgm::Matrix2D::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Matrix2DDivision, TryDivide_ReturnsInverseScaledMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2D inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix using @ref fgm::Matrix2D::tryDiv always
 *        return a floating-point matrix and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Matrix2DDivision, TryDivide_AlwaysReturnFloatingPointMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Matrix2D inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);
    static_assert(std::is_floating_point_v<typename decltype(inverseScaledMat)::value_type>);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix2D::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Matrix2DDivision, TryDivide_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2D inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix2D::tryDiv returns passed-in fallback 
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Matrix2DDivision, TryDivide_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2D inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag, fgm::mat2d::zero<TypeParam>);

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix2D::tryDiv returns identity matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2DDivision, TryDivide_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2D inverseScaledMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix2D::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2DDivision, TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2D inverseScaledMat = GetParam().tryDiv(2.5, flag, fgm::mat2d::zero<ParamType::value_type>);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using @ref fgm::Matrix2D::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2DDivision, TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Matrix2D inverseScaledMat =
        GetParam().tryDiv(0, flag, fgm::mat2d::zero<ParamType::value_type>);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Matrix2D::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Matrix2DDivision, StaticWrapper_TryDivide_ReturnsInverseScaledMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2D inverseScaledMat = fgm::Matrix2D<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Matrix2D::tryDiv always
 *        return a floating-point matrix and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Matrix2DDivision, StaticWrapper_TryDivide_AlwaysReturnFloatingPointMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Matrix2D inverseScaledMat =
        fgm::Matrix2D<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);
    static_assert(std::is_floating_point_v<typename decltype(inverseScaledMat)::value_type>);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix2D::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Matrix2DDivision, StaticWrapper_TryDivide_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2D inverseScaledMat = fgm::Matrix2D<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix2D::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Matrix2DDivision, StaticWrapper_TryDivide_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix2D inverseScaledMat =
        fgm::Matrix2D<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, fgm::mat2d::zero<TypeParam>);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix2D::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2DDivision, StaticWrapper_TryDivide_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    const fgm::Matrix2D inverseScaledMat = fgm::Matrix2D<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);

    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using the static variant of @ref fgm::Matrix2D::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2DDivision, StaticWrapper_TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    [[maybe_unused]] const fgm::Matrix2D inverseScaledMat = fgm::Matrix2D<T>::tryDiv(GetParam(), T(0), flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix2D::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2DDivision, StaticWrapper_TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    const fgm::Matrix2D inverseScaledMat =
        fgm::Matrix2D<T>::tryDiv(GetParam(), 2.5, flag, fgm::mat2d::zero<ParamType::value_type>);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
