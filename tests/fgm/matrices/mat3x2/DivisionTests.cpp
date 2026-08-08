/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref fgm::Mat3x2 division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x2TestSetup.h"


/**
 * @addtogroup T_FGM_Mat3x2_Division
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat3x2 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3x2DivisionTests: public testing::Test
    {
    protected:
        fgm::Mat3x2<T> _matrix;
        T _scalar;
        fgm::Mat3x2<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { fgm::Vec3{ T(7), T(3), T(0) }, fgm::Vec3{ T(1), T(6), T(6) } };
            _scalar         = T(3);
            _expectedMatrix = { fgm::Vec3{ T(2.333333333333333), T(1), T(0) },
                                fgm::Vec3{ T(0.3333333333333333), T(2), T(2) } };
        }
    };
    /** Test fixture for @ref fgm::Mat3x2 division, parameterized by @ref SupportedArithmeticTypes */
    TYPED_TEST_SUITE(Mat3x2DivisionTests, SupportedArithmeticTypes);



    /** @brief Test fixture for @ref fgm::Mat3x2 division with NaN vectors. */
    class Mat3x2DivisionNaNTests: public testing::TestWithParam<fgm::Mat3x2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3x2InvalidDivision, Mat3x2DivisionNaNTests,
                             ::testing::Values(fgm::Mat3x2<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                                               fgm::Mat3x2<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
                                               fgm::Mat3x2<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                                               fgm::Mat3x2<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                                               fgm::Mat3x2<float>(3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                                               fgm::Mat3x2<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                                               fgm::Mat3x2<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                  fgm ::constants::NaN, fgm ::constants::NaN,
                                                                  fgm::constants::NaN, fgm::constants::NaN)));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat3x2 MAT(2, 4, 6, 8, 10, 12);

        /// @test Verify that Mat3x2 division operator returns a valid matrix at compile time.
        constexpr fgm::Mat3x2 DIV_RESULT_1 = MAT / 2;
        static_assert(DIV_RESULT_1(0, 0) == 1);
        static_assert(DIV_RESULT_1(0, 1) == 2);
        static_assert(DIV_RESULT_1(1, 0) == 3);
        static_assert(DIV_RESULT_1(1, 1) == 4);
        static_assert(DIV_RESULT_1(2, 0) == 5);
        static_assert(DIV_RESULT_1(2, 1) == 6);

        /// @test Verify that Mat3x2 safeDiv returns a valid matrix at compile time.
        constexpr fgm::Mat3x2 DIV_RESULT_2 = MAT.safeDiv(2);
        static_assert(DIV_RESULT_2(0, 0) == 1);
        static_assert(DIV_RESULT_2(0, 1) == 2);
        static_assert(DIV_RESULT_2(1, 0) == 3);
        static_assert(DIV_RESULT_2(1, 1) == 4);
        static_assert(DIV_RESULT_2(2, 0) == 5);
        static_assert(DIV_RESULT_2(2, 1) == 6);

        /// @test Verify that Mat3x2 safeDiv (static wrapper) returns a valid matrix at compile time.
        constexpr fgm::Mat3x2 DIV_RESULT_3 = fgm::Mat3x2<int>::safeDiv(MAT, 2);
        static_assert(DIV_RESULT_3(0, 0) == 1);
        static_assert(DIV_RESULT_3(0, 1) == 2);
        static_assert(DIV_RESULT_3(1, 0) == 3);
        static_assert(DIV_RESULT_3(1, 1) == 4);
        static_assert(DIV_RESULT_3(2, 0) == 5);
        static_assert(DIV_RESULT_3(2, 1) == 6);

        // Matrix Try Division
        // NOT available at compile time due to [out] parameter (OperationStatus).

    } // namespace static_tests
} // namespace



/**************************************
 *      DIVISION TESTS (RUNTIME)      *
 **************************************/

TYPED_TEST(Mat3x2DivisionTests, DivideOperator_ReturnsAValidMatrix)
{
    const fgm::Mat3x2 inverseScaledMat = this->_matrix / this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat3x2DivisionTests, DivideEqualsOperator_PerformsElementWiseDivisionInPlace)
{
    fgm::Mat3x2 matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}



/**************************************
 *         SAFE DIVISION TESTS        *
 **************************************/

TYPED_TEST(Mat3x2DivisionTests, SafeDiv_ReturnsAValidMatrix)
{
    const fgm::Mat3x2 inverseScaledMat = this->_matrix.safeDiv(this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat3x2DivisionTests, SafeDiv_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Mat3x2 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat3x2DivisionTests, SafeDiv_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Mat3x2 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0), fgm::Mat3x2<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat3x2DivisionNaNTests, SafeDiv_ReturnsIdentityMatrixByDefault)
{
    const fgm::Mat3x2 inverseScaledMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat3x2DivisionNaNTests, SafeDiv_ReturnsPassedInFallback)
{
    const fgm::Mat3x2 inverseScaledMat = GetParam().safeDiv(2.5, fgm::Mat3x2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat3x2DivisionTests, StaticWrapper_SafeDiv_ReturnsAValidMatrix)
{
    const fgm::Mat3x2 inverseScaledMat = fgm::Mat3x2<TypeParam>::safeDiv(this->_matrix, this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat3x2DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Mat3x2 inverseScaledMat = fgm::Mat3x2<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat3x2DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Mat3x2 inverseScaledMat =
        fgm::Mat3x2<TypeParam>::safeDiv(this->_matrix, TypeParam(0), fgm::Mat3x2<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat3x2DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsIdentityMatrixByDefault)
{
    using T                            = ParamType::value_type;
    const fgm::Mat3x2 inverseScaledMat = fgm::Mat3x2<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat3x2DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsPassedInFallback)
{
    using T                            = ParamType::value_type;
    const fgm::Mat3x2 inverseScaledMat = fgm::Mat3x2<T>::safeDiv(GetParam(), 2.5, fgm::Mat3x2<T>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @brief Verify that dividing a matrix using @ref fgm::Mat3x2::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat3x2DivisionTests, TryDiv_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat3x2 inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Mat3x2::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat3x2DivisionTests, TryDiv_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat3x2 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Mat3x2::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat3x2DivisionTests, TryDiv_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat3x2 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag, fgm::Mat3x2<TypeParam>::zero());

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Mat3x2::tryDiv returns zero matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat3x2DivisionNaNTests, TryDiv_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const fgm::Mat3x2 inverseScaledMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Mat3x2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat3x2DivisionNaNTests, TryDiv_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const fgm::Mat3x2 inverseScaledMat = GetParam().tryDiv(2.5, flag, fgm::Mat3x2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using @ref fgm::Mat3x2::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat3x2DivisionNaNTests, TryDiv_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Mat3x2 inverseScaledMat =
        GetParam().tryDiv(0, flag, fgm::Mat3x2<ParamType::value_type>::zero());
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Mat3x2::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat3x2DivisionTests, StaticWrapper_TryDiv_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat3x2 inverseScaledMat = fgm::Mat3x2<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat3x2::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat3x2DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat3x2 inverseScaledMat = fgm::Mat3x2<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat3x2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat3x2DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat3x2 inverseScaledMat =
        fgm::Mat3x2<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, fgm::Mat3x2<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat3x2::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat3x2DivisionNaNTests, StaticWrapper_TryDiv_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    using T                            = ParamType::value_type;
    const fgm::Mat3x2 inverseScaledMat = fgm::Mat3x2<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_ZERO(inverseScaledMat);

    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using the static variant of @ref fgm::Mat3x2::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat3x2DivisionNaNTests, StaticWrapper_TryDiv_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    using T                                             = ParamType::value_type;
    [[maybe_unused]] const fgm::Mat3x2 inverseScaledMat = fgm::Mat3x2<T>::tryDiv(GetParam(), T(0), flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat3x2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat3x2DivisionNaNTests, StaticWrapper_TryDiv_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    const fgm::Mat3x2 inverseScaledMat =
        fgm::Mat3x2<T>::tryDiv(GetParam(), 2.5, flag, fgm::Mat3x2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
