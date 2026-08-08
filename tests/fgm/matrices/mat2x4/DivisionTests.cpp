/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref fgm::Mat2x4 division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x4TestSetup.h"


/**
 * @addtogroup T_FGM_Mat2x4_Division
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat2x4 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */

    template <typename T>
    class Mat2x4DivisionTests: public ::testing::Test
    {
    protected:
        fgm::Mat2x4<T> _matrix;
        T _scalar;
        fgm::Mat2x4<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { fgm::Vec2{ T(7), T(3) }, fgm::Vec2{ T(1), T(6) }, fgm::Vec2{ T(3), T(9) },
                                fgm::Vec2{ T(0), T(24) } };
            _scalar         = T(3);
            _expectedMatrix = { fgm::Vec2{ T(2.333333333333333), T(1) }, fgm::Vec2{ T(0.3333333333333333), T(2) },
                                fgm::Vec2{ T(1), T(3) }, fgm::Vec2{ T(0), T(8) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x4DivisionTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref fgm::Mat2x4 Division with NaN elements.
     */
    class NaNMat2x4DivisionTests: public ::testing::TestWithParam<fgm::Mat2x4<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat2x4DivisionTestSuite, NaNMat2x4DivisionTests,
        ::testing::Values(fgm::Mat2x4<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                          fgm::Mat2x4<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                          fgm::Mat2x4<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                          fgm::Mat2x4<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
                          fgm::Mat2x4<float>(3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                          fgm::Mat2x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                          fgm::Mat2x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                          fgm::Mat2x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                          fgm::Mat2x4<float>(fgm ::constants::NaN, fgm::constants::NaN, fgm ::constants::NaN,
                                             fgm ::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                             fgm::constants::NaN, fgm::constants::NaN)));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat2x4 MAT(2, 4, 6, 8, 10, 12, 14, 16);

        /// @test Verify that Mat2x4 division operator returns a valid matrix at compile time.
        constexpr fgm::Mat2x4 DIV_RESULT_1 = MAT / 2;
        static_assert(DIV_RESULT_1(0, 0) == 1);
        static_assert(DIV_RESULT_1(0, 1) == 2);
        static_assert(DIV_RESULT_1(0, 2) == 3);
        static_assert(DIV_RESULT_1(0, 3) == 4);
        static_assert(DIV_RESULT_1(1, 0) == 5);
        static_assert(DIV_RESULT_1(1, 1) == 6);
        static_assert(DIV_RESULT_1(1, 2) == 7);
        static_assert(DIV_RESULT_1(1, 3) == 8);


        /// @test Verify that Mat2x4 safeDiv returns a valid matrix at compile time.
        constexpr fgm::Mat2x4 DIV_RESULT_2 = MAT.safeDiv(2);
        static_assert(DIV_RESULT_2(0, 0) == 1);
        static_assert(DIV_RESULT_2(0, 1) == 2);
        static_assert(DIV_RESULT_2(0, 2) == 3);
        static_assert(DIV_RESULT_2(0, 3) == 4);
        static_assert(DIV_RESULT_2(1, 0) == 5);
        static_assert(DIV_RESULT_2(1, 1) == 6);
        static_assert(DIV_RESULT_2(1, 2) == 7);
        static_assert(DIV_RESULT_2(1, 3) == 8);

        /// @test Verify that Mat2x4 safeDiv (static wrapper) returns a valid matrix at compile time.
        constexpr fgm::Mat2x4 DIV_RESULT_3 = fgm::Mat2x4<int>::safeDiv(MAT, 2);
        static_assert(DIV_RESULT_3(0, 0) == 1);
        static_assert(DIV_RESULT_3(0, 1) == 2);
        static_assert(DIV_RESULT_3(0, 2) == 3);
        static_assert(DIV_RESULT_3(0, 3) == 4);
        static_assert(DIV_RESULT_3(1, 0) == 5);
        static_assert(DIV_RESULT_3(1, 1) == 6);
        static_assert(DIV_RESULT_3(1, 2) == 7);
        static_assert(DIV_RESULT_3(1, 3) == 8);

        // Matrix Try Division
        // NOT available at compile time due to [out] parameter (OperationStatus).

    } // namespace static_tests
} // namespace



/**************************************
 *      DIVISION TESTS (RUNTIME)      *
 **************************************/

TYPED_TEST(Mat2x4DivisionTests, DivideOperator_ReturnsAValidMatrix)
{
    const fgm::Mat2x4 inverseScaledMat = this->_matrix / this->_scalar;
    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}



TYPED_TEST(Mat2x4DivisionTests, DivideEqualsOperator_PerformsElementWiseDivisionInPlace)
{
    fgm::Mat2x4 matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}



/**************************************
 *         SAFE DIVISION TESTS        *
 **************************************/

TYPED_TEST(Mat2x4DivisionTests, SafeDiv_ReturnsAValidMatrix)
{
    const fgm::Mat2x4 inverseScaledMat = this->_matrix.safeDiv(this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat2x4DivisionTests, SafeDiv_DivisionByZero_ReturnsZeroMatrixByDefault)
{
    const fgm::Mat2x4 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat2x4DivisionTests, SafeDiv_DivisionByZero_ReturnsPassedInFallback)
{
    const fgm::Mat2x4 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0), fgm::Mat2x4<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(NaNMat2x4DivisionTests, SafeDiv_ReturnsZeroMatrixByDefault)
{
    const fgm::Mat2x4 inverseScaledMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(NaNMat2x4DivisionTests, SafeDiv_ReturnsPassedInFallback)
{
    const fgm::Mat2x4 inverseScaledMat = GetParam().safeDiv(2.5, fgm::Mat2x4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat2x4DivisionTests, StaticWrapper_SafeDiv_ReturnsAValidMatrix)
{
    const fgm::Mat2x4 inverseScaledMat = fgm::Mat2x4<TypeParam>::safeDiv(this->_matrix, this->_scalar);
    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat2x4DivisionTests, StaticWrapper_SafeDiv_DivisionByZero_ReturnsZeroMatrixByDefault)
{
    const fgm::Mat2x4 inverseScaledMat = fgm::Mat2x4<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat2x4DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsPassedInFallback)
{
    const fgm::Mat2x4 inverseScaledMat =
        fgm::Mat2x4<TypeParam>::safeDiv(this->_matrix, TypeParam(0), fgm::Mat2x4<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(NaNMat2x4DivisionTests, StaticWrapper_SafeDiv_ReturnsZeroMatrixByDefault)
{
    using T                            = ParamType::value_type;
    const fgm::Mat2x4 inverseScaledMat = fgm::Mat2x4<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(NaNMat2x4DivisionTests, StaticWrapper_SafeDiv_ReturnsPassedInFallback)
{
    using T                            = ParamType::value_type;
    const fgm::Mat2x4 inverseScaledMat = fgm::Mat2x4<T>::safeDiv(GetParam(), 2.5, fgm::Mat2x4<T>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @brief Verify that dividing a matrix using @ref fgm::Mat2x4::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2x4DivisionTests, TryDivide_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x4 inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Mat2x4::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x4DivisionTests, TryDivide_DivisionByZero_ReturnsZeroMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x4 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using @ref fgm::Mat2x4::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x4DivisionTests, TryDivide_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x4 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag, fgm::Mat2x4<TypeParam>::zero());

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Mat2x4::tryDiv returns identity matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat2x4DivisionTests, TryDivide_ReturnsZeroMatrixByDefault)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x4 inverseScaledMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using @ref fgm::Mat2x4::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat2x4DivisionTests, TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x4 inverseScaledMat = GetParam().tryDiv(2.5, flag, fgm::Mat2x4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using @ref fgm::Mat2x4::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat2x4DivisionTests, TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Mat2x4 inverseScaledMat =
        GetParam().tryDiv(0, flag, fgm::Mat2x4<ParamType::value_type>::zero());
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a matrix using the static variant of @ref fgm::Mat2x4::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2x4DivisionTests, StaticWrapper_TryDivide_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x4 inverseScaledMat = fgm::Mat2x4<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat2x4::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x4DivisionTests, StaticWrapper_TryDivide_DivisionByZero_ReturnsZeroMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x4 inverseScaledMat = fgm::Mat2x4<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat2x4::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x4DivisionTests, StaticWrapper_TryDivide_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x4 inverseScaledMat =
        fgm::Mat2x4<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, fgm::Mat2x4<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat2x4::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat2x4DivisionTests, StaticWrapper_TryDivide_ReturnsZeroMatrixByDefault)
{
    fgm::OperationStatus flag;
    using T                            = ParamType::value_type;
    const fgm::Mat2x4 inverseScaledMat = fgm::Mat2x4<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_ZERO(inverseScaledMat);

    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix by zero using the static variant of @ref fgm::Mat2x4::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat2x4DivisionTests, StaticWrapper_TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    using T                                             = ParamType::value_type;
    [[maybe_unused]] const fgm::Mat2x4 inverseScaledMat = fgm::Mat2x4<T>::tryDiv(GetParam(), T(0), flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat2x4::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat2x4DivisionTests, StaticWrapper_TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    const fgm::Mat2x4 inverseScaledMat =
        fgm::Mat2x4<T>::tryDiv(GetParam(), 2.5, flag, fgm::Mat2x4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
