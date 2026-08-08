/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref fgm::Mat4x3 division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x3TestSetup.h"


/**
 * @addtogroup T_FGM_Mat4x3_Division
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat4x3 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
template <typename T>
class Mat4x3DivisionTests: public testing::Test
{
protected:
    fgm::Mat4x3<T> _matrix;
    T _scalar;
    fgm::Mat4x3<T> _expectedMatrix;

    void SetUp() override
    {
        _matrix         = { fgm::Vec4{ T(7), T(3), T(0), T(21) }, fgm::Vec4{ T(1), T(6), T(6), T(12) },
                            fgm::Vec4{ T(3), T(12), T(18), T(21) } };
        _scalar         = T(3);
        _expectedMatrix = { fgm::Vec4{ T(2.333333333333333), T(1), T(0), T(7) },
                            fgm::Vec4{ T(0.3333333333333333), T(2), T(2), T(4) }, fgm::Vec4{ T(1), T(4), T(6), T(7) } };
    }
};
TYPED_TEST_SUITE(Mat4x3DivisionTests, SupportedArithmeticTypes);


    /**
         * @brief Test fixture for @ref fgm::Mat4 Division with NaN elements.
         */
class Mat4x3DivisionNaNTests: public testing::TestWithParam<fgm::Mat4x3<float>>
{};
INSTANTIATE_TEST_SUITE_P(
    Mat4InvalidDivision, Mat4x3DivisionNaNTests,
    ::testing::Values(
        fgm::Mat4x3<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
        fgm::Mat4x3<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
        fgm::Mat4x3<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
        fgm::Mat4x3<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
        fgm::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
        fgm::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
        fgm::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
        fgm::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
        fgm::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
        fgm::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f),
        fgm::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f),
        fgm::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN),
        fgm::Mat4x3<float>(fgm ::constants::NaN, fgm::constants::NaN, fgm ::constants::NaN, fgm ::constants::NaN,
                           fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                           fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN)));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
    constexpr fgm::Mat4x3 MAT(2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24);

        /// @test Verify that Mat4x3 division operator returns a valid matrix at compile time.
    constexpr fgm::Mat4x3 DIV_RESULT_1 = MAT / 2;
    static_assert(DIV_RESULT_1(0, 0) == 1);
    static_assert(DIV_RESULT_1(0, 1) == 2);
    static_assert(DIV_RESULT_1(0, 2) == 3);
    static_assert(DIV_RESULT_1(1, 0) == 4);
    static_assert(DIV_RESULT_1(1, 1) == 5);
    static_assert(DIV_RESULT_1(1, 2) == 6);
    static_assert(DIV_RESULT_1(2, 0) == 7);
    static_assert(DIV_RESULT_1(2, 1) == 8);
    static_assert(DIV_RESULT_1(2, 2) == 9);
    static_assert(DIV_RESULT_1(3, 0) == 10);
    static_assert(DIV_RESULT_1(3, 1) == 11);
    static_assert(DIV_RESULT_1(3, 2) == 12);

        /// @test Verify that Mat4x3 safeDiv returns a valid matrix at compile time.
    constexpr fgm::Mat4x3 DIV_RESULT_2 = MAT.safeDiv(2);
    static_assert(DIV_RESULT_2(0, 0) == 1);
    static_assert(DIV_RESULT_2(0, 1) == 2);
    static_assert(DIV_RESULT_2(0, 2) == 3);
    static_assert(DIV_RESULT_2(1, 0) == 4);
    static_assert(DIV_RESULT_2(1, 1) == 5);
    static_assert(DIV_RESULT_2(1, 2) == 6);
    static_assert(DIV_RESULT_2(2, 0) == 7);
    static_assert(DIV_RESULT_2(2, 1) == 8);
    static_assert(DIV_RESULT_2(2, 2) == 9);
    static_assert(DIV_RESULT_2(3, 0) == 10);
    static_assert(DIV_RESULT_2(3, 1) == 11);
    static_assert(DIV_RESULT_2(3, 2) == 12);

        /// @test Verify that Mat4x3 safeDiv (static wrapper) returns a valid matrix at compile time.
    constexpr fgm::Mat4x3 DIV_RESULT_3 = fgm::Mat4x3<int>::safeDiv(MAT, 2);
    static_assert(DIV_RESULT_3(0, 0) == 1);
    static_assert(DIV_RESULT_3(0, 1) == 2);
    static_assert(DIV_RESULT_3(0, 2) == 3);
    static_assert(DIV_RESULT_3(1, 0) == 4);
    static_assert(DIV_RESULT_3(1, 1) == 5);
    static_assert(DIV_RESULT_3(1, 2) == 6);
    static_assert(DIV_RESULT_3(2, 0) == 7);
    static_assert(DIV_RESULT_3(2, 1) == 8);
    static_assert(DIV_RESULT_3(2, 2) == 9);
    static_assert(DIV_RESULT_3(3, 0) == 10);
    static_assert(DIV_RESULT_3(3, 1) == 11);
    static_assert(DIV_RESULT_3(3, 2) == 12);

    // Matrix Try Division
    // NOT available at compile time due to [out] parameter (OperationStatus).

} // namespace
} // namespace



/**************************************
 *      DIVISION TESTS (RUNTIME)      *
 **************************************/

TYPED_TEST(Mat4x3DivisionTests, DivideOperator_ReturnsAValidMatrix)
{
    const fgm::Mat4x3 inverseScaledMat = this->_matrix / this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat4x3DivisionTests, DivideEqualsOperator_PerformsElementWiseDivisionInPlace)
{
    fgm::Mat4x3 matrix = this->_matrix;

    matrix /= this->_scalar;
    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}



/**************************************
 *         SAFE DIVISION TESTS        *
 **************************************/

TYPED_TEST(Mat4x3DivisionTests, SafeDiv_ReturnsAValidMatrix)
{
    const fgm::Mat4x3 inverseScaledMat = this->_matrix.safeDiv(this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat4x3DivisionTests, SafeDiv_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Mat4x3 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat4x3DivisionTests, SafeDiv_DivisionByZeroReturnsPassedInFallbackMatrix)
{
    const fgm::Mat4x3 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0), fgm::Mat4x3<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat4x3DivisionNaNTests, SafeDiv_ReturnsIdentityMatrixByDefault)
{
    const fgm::Mat4x3 inverseScaledMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat4x3DivisionNaNTests, SafeDiv_ReturnsPassedInFallbackMatrix)
{
    const fgm::Mat4x3 inverseScaledMat = GetParam().safeDiv(2.5, fgm::Mat4x3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat4x3DivisionTests, SafeDiv_StaticWrapper_ReturnsAValidMatrix)
{
    const fgm::Mat4x3 inverseScaledMat = fgm::Mat4x3<TypeParam>::safeDiv(this->_matrix, this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat4x3DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Mat4x3 inverseScaledMat = fgm::Mat4x3<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat4x3DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsPassedInFallbackMatrix)
{
    const fgm::Mat4x3 inverseScaledMat =
        fgm::Mat4x3<TypeParam>::safeDiv(this->_matrix, TypeParam(0), fgm::Mat4x3<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat4x3DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsIdentityMatrixByDefault)
{
    using T                            = ParamType::value_type;
    const fgm::Mat4x3 inverseScaledMat = fgm::Mat4x3<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat4x3DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsPassedInFallbackMatrix)
{
    using T                            = ParamType::value_type;
    const fgm::Mat4x3 inverseScaledMat = fgm::Mat4x3<T>::safeDiv(GetParam(), 2.5, fgm::Mat4x3<T>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @brief Verify that dividing a matrix using @ref fgm::Mat4x3::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4x3DivisionTests, TryDiv_ReturnsAValidMatrixAndSetsCorrectFlagAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat4x3 inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Mat4x3::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat4x3DivisionTests, TryDiv_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat4x3 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Mat4x3::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat4x3DivisionTests, TryDiv_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat4x3 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag, fgm::Mat4x3<TypeParam>::zero());

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Mat4x3::tryDiv returns zero matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4x3DivisionNaNTests, TryDiv_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat4x3 inverseScaledMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Mat4x3::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4x3DivisionNaNTests, TryDiv_ReturnsPassedInFallbackMatrix)
{
    fgm::OperationStatus flag;
    const fgm::Mat4x3 inverseScaledMat = GetParam().tryDiv(2.5, flag, fgm::Mat4x3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using @ref fgm::Mat4x3::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4x3DivisionNaNTests, TryDiv_NaNOperandTakesPrecedenceOverZeroDivisionAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Mat4x3 inverseScaledMat =
        GetParam().tryDiv(0, flag, fgm::Mat4x3<ParamType::value_type>::zero());
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Mat4x3::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4x3DivisionTests, StaticWrapper_TryDiv_ReturnsAValidMatrixAndSetsCorrectFlagAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat4x3 inverseScaledMat = fgm::Mat4x3<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat4x3::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat4x3DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat4x3 inverseScaledMat = fgm::Mat4x3<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat4x3::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat4x3DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat4x3 inverseScaledMat =
        fgm::Mat4x3<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, fgm::Mat4x3<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat4x3::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4x3DivisionNaNTests, StaticWrapper_TryDiv_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    using T                            = ParamType::value_type;
    const fgm::Mat4x3 inverseScaledMat = fgm::Mat4x3<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_ZERO(inverseScaledMat);

    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using the static variant of @ref fgm::Mat4x3::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4x3DivisionNaNTests, StaticWrapper_TryDiv_NaNOperandTakesPrecedenceOverZeroDivisionAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    using T                                             = ParamType::value_type;
    [[maybe_unused]] const fgm::Mat4x3 inverseScaledMat = fgm::Mat4x3<T>::tryDiv(GetParam(), T(0), flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat4x3::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4x3DivisionNaNTests, StaticWrapper_TryDiv_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    const fgm::Mat4x3 inverseScaledMat =
        fgm::Mat4x3<T>::tryDiv(GetParam(), 2.5, flag, fgm::Mat4x3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
