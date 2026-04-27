/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 13, 2026
 *
 * @brief Verify @ref fgm::Matrix3D division logic.
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
class Matrix3DDivision: public ::testing::Test
{
protected:
    fgm::Matrix3D<T> _matrix;
    T _scalar;
    fgm::Matrix3D<fgm::Magnitude<T>> _expectedMatrix;
    fgm::Matrix3D<T> _expectedTypedMatrix;

    void SetUp() override
    {
        _matrix = { fgm::Vector3D<T>{ 17, 13, 15 }, fgm::Vector3D<T>{ 11, 16, 35 }, fgm::Vector3D<T>{ 27, 44, 56 } };
        _scalar = T(7);
        // Used by / tests
        _expectedMatrix = {
            { fgm::Magnitude<T>(2.428571428571428), fgm::Magnitude<T>(1.857142857142857),
              fgm::Magnitude<T>(2.142857142857143) },
            { fgm::Magnitude<T>(1.571428571428571), fgm::Magnitude<T>(2.285714285714286), fgm::Magnitude<T>(5.0) },
            { fgm::Magnitude<T>(3.857142857142857), fgm::Magnitude<T>(6.285714285714286), fgm::Magnitude<T>(8.0) }
        };
        // Used by /= tests
        _expectedTypedMatrix = { { T(2.428571428571428), T(1.857142857142857), T(2.142857142857143) },
                                 { T(1.571428571428571), T(2.285714285714286), T(5.0) },
                                 { T(3.857142857142857), T(6.285714285714286), T(8.0) } };
    };
};
/** Test fixture for @ref fgm::Matrix3D division, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Matrix3DDivision, SupportedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Matrix3D division with NaN vectors. */
class NaNMatrix3DDivision: public ::testing::TestWithParam<fgm::Matrix3D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Matrix3DDivisionTestSuite, NaNMatrix3DDivision,
                         ::testing::Values(fgm::Matrix3D<float>(fgm::constants::NaN, 3.0f, 3.0f),
                                           fgm::Matrix3D<float>(3.0f, fgm::constants::NaN, 3.0f),
                                           fgm::Matrix3D<float>(3.0f, 3.0f, fgm::constants::NaN),
                                           fgm::Matrix3D<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN)));



/**
 * @addtogroup T_FGM_Mat3x3_Division
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
    constexpr fgm::Matrix3D MAT(2, 4, 6, 8, 10, 12, 14, 16, 18);

    // Matrix scalar division
    constexpr fgm::Matrix3D DIV_RESULT_1 = MAT / 2;
    static_assert(DIV_RESULT_1(0, 0) == 1);
    static_assert(DIV_RESULT_1(0, 1) == 2);
    static_assert(DIV_RESULT_1(0, 2) == 3);
    static_assert(DIV_RESULT_1(1, 0) == 4);
    static_assert(DIV_RESULT_1(1, 1) == 5);
    static_assert(DIV_RESULT_1(1, 2) == 6);
    static_assert(DIV_RESULT_1(2, 0) == 7);
    static_assert(DIV_RESULT_1(2, 1) == 8);
    static_assert(DIV_RESULT_1(2, 2) == 9);

    // Matrix Safe Division
    //constexpr fgm::Matrix3D DIV_RESULT_2 = MAT.safeDiv(2);
    //static_assert(DIV_RESULT_1(0, 0) == 1);
    //static_assert(DIV_RESULT_1(0, 1) == 2);
    //static_assert(DIV_RESULT_1(0, 2) == 3);
    //static_assert(DIV_RESULT_1(1, 0) == 4);
    //static_assert(DIV_RESULT_1(1, 1) == 5);
    //static_assert(DIV_RESULT_1(1, 2) == 6);
    //static_assert(DIV_RESULT_1(2, 0) == 7);
    //static_assert(DIV_RESULT_1(2, 1) == 8);
    //static_assert(DIV_RESULT_1(2, 2) == 9);
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
TYPED_TEST(Matrix3DDivision, ReturnsInverseScaledMatrix)
{
    const fgm::Matrix3D inverseScaledMat = this->_matrix / this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/** @brief Verify that the binary division operator always return a floating-point matrix. */
TYPED_TEST(Matrix3DDivision, AlwaysReturnFloatingPointMatrix)
{
    [[maybe_unused]] const fgm::Matrix3D inverseScaledMat = this->_matrix / this->_scalar;
    static_assert(std::is_floating_point_v<typename decltype(inverseScaledMat)::value_type>);
}


/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Matrix3DDivision, ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(this->_matrix / 0, "Matrix division by zero");
}


/**
 * @brief Verify that the compound division operator perform an element-wise divide
 *        and mutates the matrix in-place.
 */
TYPED_TEST(Matrix3DDivision, CompoundDivision_InverseScalesMatrixInPlace)
{
    fgm::Matrix3D matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedTypedMatrix, matrix);
}


/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Matrix3DDivision, CompoundDivision_ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(this->_matrix /= 0, "Matrix division by zero");
}


/**************************************
 *                                    *
 *         SAFE DIVISION TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a matrix using @ref fgm::Matrix3D::safeDiv perform an element-wise divide
 *        and returns a new matrix instance.
 */
 TYPED_TEST(Matrix3DDivision, SafeDivide_ReturnsInverseScaledMatrix)
{
    const fgm::Matrix3D inverseScaledMat = this->_matrix.safeDiv(this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix using @ref fgm::Matrix3D::safeDiv always
 *        return a floating-point matrix.
 */
 TYPED_TEST(Matrix3DDivision, SafeDivide_AlwaysReturnFloatingPointMatrix)
{
    [[maybe_unused]] const fgm::Matrix3D inverseScaledMat = this->_matrix.safeDiv(this->_scalar);
    static_assert(std::is_floating_point_v<typename decltype(inverseScaledMat)::value_type>);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix3D::safeDiv
 *        returns identity matrix by default.
 */
 TYPED_TEST(Matrix3DDivision, SafeDivide_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Matrix3D inverseScaledMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix3D::safeDiv
 *        returns passed-in fallback.
 */
 TYPED_TEST(Matrix3DDivision, SafeDivide_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Matrix3D inverseScaledMat = this->_matrix.safeDiv(TypeParam(0), fgm::mat3d::zero<TypeParam>);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix3D::safeDiv
 *        returns identity matrix by default.
 */
 TEST_P(NaNMatrix3DDivision, SafeDivide_ReturnsIdentityMatrixByDefault)
{
    const fgm::Matrix3D inverseScaledMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix3D::safeDiv
 *        returns passed-in fallback.
 */
 TEST_P(NaNMatrix3DDivision, SafeDivide_ReturnsPassedInFallback)
{
    const fgm::Matrix3D inverseScaledMat = GetParam().safeDiv(2.5, fgm::mat3d::zero<ParamType::value_type>);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Matrix3D::safeDiv
 *        perform an element-wise divide and returns a new matrix instance.
 */
 TYPED_TEST(Matrix3DDivision, SafeDivide_StaticWrapper_ReturnsInverseScaledMatrix)
{
    const fgm::Matrix3D inverseScaledMat = fgm::Matrix3D<TypeParam>::safeDiv(this->_matrix, this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Matrix3D::safeDiv always
 *        return a floating-point matrix.
 */
 TYPED_TEST(Matrix3DDivision, SafeDivide_StaticWrapper_AlwaysReturnFloatingPointMatrix)
{
    [[maybe_unused]] const fgm::Matrix3D inverseScaledMat =
        fgm::Matrix3D<TypeParam>::safeDiv(this->_matrix, this->_scalar);
    static_assert(std::is_floating_point_v<typename decltype(inverseScaledMat)::value_type>);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix3D::safeDiv
 *        returns identity matrix by default.
 */
 TYPED_TEST(Matrix3DDivision, SafeDivide_StaticWrapper_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Matrix3D inverseScaledMat = fgm::Matrix3D<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix3D::safeDiv
 *        returns passed-in fallback.
 */
 TYPED_TEST(Matrix3DDivision, SafeDivide_StaticWrapper_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Matrix3D inverseScaledMat =
        fgm::Matrix3D<TypeParam>::safeDiv(this->_matrix, TypeParam(0), fgm::mat3d::zero<TypeParam>);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix3D::safeDiv
 *        returns identity matrix by default.
 */
 TEST_P(NaNMatrix3DDivision, SafeDivide_StaticWrapper_ReturnsIdentityMatrixByDefault)
{
    using T = ParamType::value_type;
    const fgm::Matrix3D inverseScaledMat = fgm::Matrix3D<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix3D::safeDiv
 *        returns passed-in fallback.
 */
 TEST_P(NaNMatrix3DDivision, SafeDivide_StaticWrapper_ReturnsPassedInFallback)
{
    using T = ParamType::value_type;
    const fgm::Matrix3D inverseScaledMat = fgm::Matrix3D<T>::safeDiv(GetParam(), 2.5, fgm::mat3d::zero<T>);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**************************************
 *                                    *
 *         TRY DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a matrix using @ref fgm::Matrix3D::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
 TYPED_TEST(Matrix3DDivision, TryDivide_ReturnsInverseScaledMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix3D inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix using @ref fgm::Matrix3D::tryDiv always
 *        return a floating-point matrix and set flag to @ref OperationStatus::SUCCESS.
 */
 TYPED_TEST(Matrix3DDivision, TryDivide_AlwaysReturnFloatingPointMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Matrix3D inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);
    static_assert(std::is_floating_point_v<typename decltype(inverseScaledMat)::value_type>);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix3D::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
 TYPED_TEST(Matrix3DDivision, TryDivide_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix3D inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Matrix3D::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
 TYPED_TEST(Matrix3DDivision, TryDivide_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix3D inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag, fgm::mat3d::zero<TypeParam>);

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix3D::tryDiv returns identity matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
 TEST_P(NaNMatrix3DDivision, TryDivide_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const fgm::Matrix3D inverseScaledMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Matrix3D::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
 TEST_P(NaNMatrix3DDivision, TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const fgm::Matrix3D inverseScaledMat = GetParam().tryDiv(2.5, flag, fgm::mat3d::zero<ParamType::value_type>);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using @ref fgm::Matrix3D::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
 TEST_P(NaNMatrix3DDivision, TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Matrix3D inverseScaledMat =
        GetParam().tryDiv(0, flag, fgm::mat3d::zero<ParamType::value_type>);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Matrix3D::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
 TYPED_TEST(Matrix3DDivision, StaticWrapper_TryDivide_ReturnsInverseScaledMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix3D inverseScaledMat = fgm::Matrix3D<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Matrix3D::tryDiv always
 *        return a floating-point matrix and set flag to @ref OperationStatus::SUCCESS.
 */
 TYPED_TEST(Matrix3DDivision, StaticWrapper_TryDivide_AlwaysReturnFloatingPointMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Matrix3D inverseScaledMat =
        fgm::Matrix3D<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);
    static_assert(std::is_floating_point_v<typename decltype(inverseScaledMat)::value_type>);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix3D::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
 TYPED_TEST(Matrix3DDivision, StaticWrapper_TryDivide_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix3D inverseScaledMat = fgm::Matrix3D<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Matrix3D::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
 TYPED_TEST(Matrix3DDivision, StaticWrapper_TryDivide_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Matrix3D inverseScaledMat =
        fgm::Matrix3D<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, fgm::mat3d::zero<TypeParam>);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix3D::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
 TEST_P(NaNMatrix3DDivision, StaticWrapper_TryDivide_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    const fgm::Matrix3D inverseScaledMat = fgm::Matrix3D<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);

    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using the static variant of @ref fgm::Matrix3D::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
 TEST_P(NaNMatrix3DDivision, StaticWrapper_TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    [[maybe_unused]] const fgm::Matrix3D inverseScaledMat = fgm::Matrix3D<T>::tryDiv(GetParam(), static_cast<T>(0), flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Matrix3D::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
 TEST_P(NaNMatrix3DDivision, StaticWrapper_TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    const fgm::Matrix3D inverseScaledMat =
        fgm::Matrix3D<T>::tryDiv(GetParam(), 2.5, flag, fgm::mat3d::zero<ParamType::value_type>);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
