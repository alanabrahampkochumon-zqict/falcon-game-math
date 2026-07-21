/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 13, 2026
 *
 * @brief Verify @ref fgm::Mat3 division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat3Division: public ::testing::Test
{
protected:
    fgm::Mat3<T> _matrix;
    T _scalar;
    fgm::Mat3<T> _expectedMatrix;

    void SetUp() override
    {
        _matrix         = { fgm::Vec3<T>{ 17, 13, 15 }, fgm::Vec3<T>{ 11, 16, 35 }, fgm::Vec3<T>{ 27, 44, 56 } };
        _scalar         = T(7);
        _expectedMatrix = { { T(2.428571428571428), T(1.857142857142857), T(2.142857142857143) },
                            { T(1.571428571428571), T(2.285714285714286), T(5.0) },
                            { T(3.857142857142857), T(6.285714285714286), T(8.0) } };
    }
};
/** Test fixture for @ref fgm::Mat3 division, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Mat3Division, SupportedArithmeticTypes);


/** @brief Test fixture for @ref fgm::Mat3 division with NaN vectors. */
class NaNMat3Division: public ::testing::TestWithParam<fgm::Mat3<float>>
{};
INSTANTIATE_TEST_SUITE_P(Mat3DivisionTestSuite, NaNMat3Division,
                         ::testing::Values(fgm::Mat3<float>(fgm::constants::NaN, 3.0f, 3.0f),
                                           fgm::Mat3<float>(3.0f, fgm::constants::NaN, 3.0f),
                                           fgm::Mat3<float>(3.0f, 3.0f, fgm::constants::NaN),
                                           fgm::Mat3<float>(fgm ::constants::NaN, fgm::constants::NaN,
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
    constexpr fgm::Mat3 MAT(2, 4, 6, 8, 10, 12, 14, 16, 18);

    // Matrix scalar division
    constexpr fgm::Mat3 DIV_RESULT_1 = MAT / 2;
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
    constexpr fgm::Mat3 DIV_RESULT_2 = MAT.safeDiv(2);
    static_assert(DIV_RESULT_2(0, 0) == 1);
    static_assert(DIV_RESULT_2(0, 1) == 2);
    static_assert(DIV_RESULT_2(0, 2) == 3);
    static_assert(DIV_RESULT_2(1, 0) == 4);
    static_assert(DIV_RESULT_2(1, 1) == 5);
    static_assert(DIV_RESULT_2(1, 2) == 6);
    static_assert(DIV_RESULT_2(2, 0) == 7);
    static_assert(DIV_RESULT_2(2, 1) == 8);
    static_assert(DIV_RESULT_2(2, 2) == 9);

    constexpr fgm::Mat3 DIV_RESULT_3 = fgm::Mat3<int>::safeDiv(MAT, 2);
    static_assert(DIV_RESULT_3(0, 0) == 1);
    static_assert(DIV_RESULT_3(0, 1) == 2);
    static_assert(DIV_RESULT_3(0, 2) == 3);
    static_assert(DIV_RESULT_3(1, 0) == 4);
    static_assert(DIV_RESULT_3(1, 1) == 5);
    static_assert(DIV_RESULT_3(1, 2) == 6);
    static_assert(DIV_RESULT_3(2, 0) == 7);
    static_assert(DIV_RESULT_3(2, 1) == 8);
    static_assert(DIV_RESULT_3(2, 2) == 9);


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
TYPED_TEST(Mat3Division, DivideOperator_ReturnsInverseScaledMatrix)
{
    const fgm::Mat3 inverseScaledMat = this->_matrix / this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Mat3Division, DivideOperator_ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), "");
}

#endif


/**
 * @brief Verify that the compound division operator perform an element-wise divide
 *        and mutates the matrix in-place.
 */
TYPED_TEST(Mat3Division, DivideEqualsOperator_InverseScalesMatrixInPlace)
{
    fgm::Mat3 matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Mat3Division, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
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
 * @brief Verify that dividing a matrix using @ref fgm::Mat3::safeDiv perform an element-wise divide
 *        and returns a new matrix instance.
 */
TYPED_TEST(Mat3Division, SafeDivide_ReturnsInverseScaledMatrix)
{
    const fgm::Mat3 inverseScaledMat = this->_matrix.safeDiv(this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Mat3::safeDiv
 *        returns identity matrix by default.
 */
TYPED_TEST(Mat3Division, SafeDivide_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Mat3 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Mat3::safeDiv
 *        returns passed-in fallback.
 */
TYPED_TEST(Mat3Division, SafeDivide_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Mat3 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0), fgm::Mat3<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Mat3::safeDiv
 *        returns identity matrix by default.
 */
TEST_P(NaNMat3Division, SafeDivide_ReturnsIdentityMatrixByDefault)
{
    const fgm::Mat3 inverseScaledMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Mat3::safeDiv
 *        returns passed-in fallback.
 */
TEST_P(NaNMat3Division, SafeDivide_ReturnsPassedInFallback)
{
    const fgm::Mat3 inverseScaledMat = GetParam().safeDiv(2.5, fgm::Mat3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Mat3::safeDiv
 *        perform an element-wise divide and returns a new matrix instance.
 */
TYPED_TEST(Mat3Division, StaticWrapper_SafeDivide_ReturnsInverseScaledMatrix)
{
    const fgm::Mat3 inverseScaledMat = fgm::Mat3<TypeParam>::safeDiv(this->_matrix, this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat3::safeDiv
 *        returns identity matrix by default.
 */
TYPED_TEST(Mat3Division, StaticWrapper_SafeDivide_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Mat3 inverseScaledMat = fgm::Mat3<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat3::safeDiv
 *        returns passed-in fallback.
 */
TYPED_TEST(Mat3Division, StaticWrapper_SafeDivide_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Mat3 inverseScaledMat =
        fgm::Mat3<TypeParam>::safeDiv(this->_matrix, TypeParam(0), fgm::Mat3<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat3::safeDiv
 *        returns identity matrix by default.
 */
TEST_P(NaNMat3Division, StaticWrapper_SafeDivide_ReturnsIdentityMatrixByDefault)
{
    using T                          = ParamType::value_type;
    const fgm::Mat3 inverseScaledMat = fgm::Mat3<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat3::safeDiv
 *        returns passed-in fallback.
 */
TEST_P(NaNMat3Division, StaticWrapper_SafeDivide_ReturnsPassedInFallback)
{
    using T                          = ParamType::value_type;
    const fgm::Mat3 inverseScaledMat = fgm::Mat3<T>::safeDiv(GetParam(), 2.5, fgm::Mat3<T>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


/**************************************
 *                                    *
 *         TRY DIVISION TESTS         *
 *                                    *
 **************************************/

/**
 * @brief Verify that dividing a matrix using @ref fgm::Mat3::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat3Division, TryDivide_ReturnsInverseScaledMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat3 inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Mat3::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat3Division, TryDivide_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat3 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Mat3::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat3Division, TryDivide_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat3 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag, fgm::Mat3<TypeParam>::zero());

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Mat3::tryDiv returns identity matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat3Division, TryDivide_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const fgm::Mat3 inverseScaledMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Mat3::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat3Division, TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const fgm::Mat3 inverseScaledMat = GetParam().tryDiv(2.5, flag, fgm::Mat3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using @ref fgm::Mat3::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat3Division, TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Mat3 inverseScaledMat =
        GetParam().tryDiv(0, flag, fgm::Mat3<ParamType::value_type>::zero());
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Mat3::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat3Division, StaticWrapper_TryDivide_ReturnsInverseScaledMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat3 inverseScaledMat = fgm::Mat3<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}



/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat3::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat3Division, StaticWrapper_TryDivide_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat3 inverseScaledMat = fgm::Mat3<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat3::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat3Division, StaticWrapper_TryDivide_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat3 inverseScaledMat =
        fgm::Mat3<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, fgm::Mat3<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat3::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat3Division, StaticWrapper_TryDivide_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    using T                          = ParamType::value_type;
    const fgm::Mat3 inverseScaledMat = fgm::Mat3<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);

    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using the static variant of @ref fgm::Mat3::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat3Division, StaticWrapper_TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    using T                                           = ParamType::value_type;
    [[maybe_unused]] const fgm::Mat3 inverseScaledMat = fgm::Mat3<T>::tryDiv(GetParam(), static_cast<T>(0), flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat3::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat3Division, StaticWrapper_TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    const fgm::Mat3 inverseScaledMat =
        fgm::Mat3<T>::tryDiv(GetParam(), 2.5, flag, fgm::Mat3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
