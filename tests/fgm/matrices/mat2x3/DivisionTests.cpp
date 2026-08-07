/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref fgm::Mat2x3x3 division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x3TestSetup.h"



/**
 * @addtogroup T_FGM_Mat2x3_Division
 * @{
 */

namespace
{

    /**************************************
     *               SETUP                *
     **************************************/
    /**
     * @brief Test fixture for @ref fgm::Mat2x3x3 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2x3DivisionTests: public testing::Test
    {
    protected:
        fgm::Mat2x3<T> _matrix;
        T _scalar;
        fgm::Mat2x3<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { fgm::Vec2{ T(7), T(3) }, fgm::Vec2{ T(1), T(6) }, fgm::Vec2{ T(3), T(9) } };
            _scalar         = T(3);
            _expectedMatrix = { fgm::Vec2{ T(2.333333333333333), T(1) }, fgm::Vec2{ T(0.3333333333333333), T(2) },
                                fgm::Vec2{ T(1), T(3) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x3DivisionTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref fgm::Mat2x3x3 Division with NaN elements.
     */
    class Mat2x3DivisionNaNTests: public ::testing::TestWithParam<fgm::Mat2x3<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2InvalidDivision, Mat2x3DivisionNaNTests,
                             ::testing::Values(fgm::Mat2x3<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                                               fgm::Mat2x3<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
                                               fgm::Mat2x3<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                                               fgm::Mat2x3<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                                               fgm::Mat2x3<float>(3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                                               fgm::Mat2x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                                               fgm::Mat2x3<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                  fgm ::constants::NaN, fgm ::constants::NaN,
                                                                  fgm::constants::NaN, fgm::constants::NaN)));

    

    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat2x3 MAT(2, 4, 6, 8, 10, 12);


        /// @test Verify that Mat2x3 division operator returns a valid matrix at compile time.
        constexpr fgm::Mat2x3 DIV_OP_MAT = MAT / 2;
        static_assert(DIV_OP_MAT(0, 0) == 1);
        static_assert(DIV_OP_MAT(0, 1) == 2);
        static_assert(DIV_OP_MAT(0, 2) == 3);
        static_assert(DIV_OP_MAT(1, 0) == 4);
        static_assert(DIV_OP_MAT(1, 1) == 5);
        static_assert(DIV_OP_MAT(1, 2) == 6);


        /// @test Verify that Mat2x3 safeDiv returns a valid matrix at compile time.
        constexpr fgm::Mat2x3 SAFE_DIV_MAT = MAT.safeDiv(2);
        static_assert(SAFE_DIV_MAT(0, 0) == 1);
        static_assert(SAFE_DIV_MAT(0, 1) == 2);
        static_assert(SAFE_DIV_MAT(0, 2) == 3);
        static_assert(SAFE_DIV_MAT(1, 0) == 4);
        static_assert(SAFE_DIV_MAT(1, 1) == 5);
        static_assert(SAFE_DIV_MAT(1, 2) == 6);


        /// @test Verify that Mat2x3 safeDiv (static wrapper) returns a valid matrix at compile time.
        constexpr fgm::Mat2x3 SAFE_DIV_MAT_STATIC = fgm::Mat2x3<int>::safeDiv(MAT, 2);
        static_assert(SAFE_DIV_MAT_STATIC(0, 0) == 1);
        static_assert(SAFE_DIV_MAT_STATIC(0, 1) == 2);
        static_assert(SAFE_DIV_MAT_STATIC(0, 2) == 3);
        static_assert(SAFE_DIV_MAT_STATIC(1, 0) == 4);
        static_assert(SAFE_DIV_MAT_STATIC(1, 1) == 5);
        static_assert(SAFE_DIV_MAT_STATIC(1, 2) == 6);

        // Matrix Try Division
        // NOT available at compile time due to [out] parameter (OperationStatus).

    } // namespace static_tests

} // namespace




/**************************************
 *      DIVISION TESTS (RUNTIME)      *
 **************************************/

TYPED_TEST(Mat2x3DivisionTests, DivideOperator_ReturnsAValidMatrix)
{
    const fgm::Mat2x3 resultantMat = this->_matrix / this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
}


TYPED_TEST(Mat2x3DivisionTests, DivideEqualsOperator_PerformsElementWiseDivisionInPlace)
{
    fgm::Mat2x3 matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}



/**************************************
 *         SAFE DIVISION TESTS        *
 **************************************/

TYPED_TEST(Mat2x3DivisionTests, SafeDiv_ReturnsAValidMatrix)
{
    const fgm::Mat2x3 resultantMat = this->_matrix.safeDiv(this->_scalar);
    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
}


TYPED_TEST(Mat2x3DivisionTests, SafeDiv_DivisionByZero_ReturnsZeroMatrixByDefault)
{
    const fgm::Mat2x3 resultantMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_ZERO(resultantMat);
}


TYPED_TEST(Mat2x3DivisionTests, SafeDivide_DivisionByZero_ReturnsPassedInFallbackMatrix)
{
    const fgm::Mat2x3 resultantMat = this->_matrix.safeDiv(TypeParam(0), fgm::Mat2x3<TypeParam>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}


TEST_P(Mat2x3DivisionNaNTests, SafeDivide_ReturnsZeroMatrixByDefault)
{
    const fgm::Mat2x3 resultantMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_ZERO(resultantMat);
}


TEST_P(Mat2x3DivisionNaNTests, SafeDivide_ReturnsPassedInFallbackMatrix)
{
    const fgm::Mat2x3 resultantMat = GetParam().safeDiv(2.5, fgm::Mat2x3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}


TYPED_TEST(Mat2x3DivisionTests, StaticWrapper_SafeDivide_ReturnsAValidMatrix)
{
    const fgm::Mat2x3 resultantMat = fgm::Mat2x3<TypeParam>::safeDiv(this->_matrix, this->_scalar);
    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
}


TYPED_TEST(Mat2x3DivisionTests, StaticWrapper_SafeDivide_DivisionByZeroReturnsZeroMatrixByDefault)
{
    const fgm::Mat2x3 resultantMat = fgm::Mat2x3<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_ZERO(resultantMat);
}


TYPED_TEST(Mat2x3DivisionTests, StaticWrapper_SafeDivide_DivisionByZeroReturnsPassedInFallbackMatrix)
{
    const fgm::Mat2x3 resultantMat =
        fgm::Mat2x3<TypeParam>::safeDiv(this->_matrix, TypeParam(0), fgm::Mat2x3<TypeParam>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}


TEST_P(Mat2x3DivisionNaNTests, StaticWrapper_SafeDivide_ReturnsZeroMatrixByDefault)
{
    using T                          = ParamType::value_type;
    const fgm::Mat2x3 resultantMat = fgm::Mat2x3<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_ZERO(resultantMat);
}


TEST_P(Mat2x3DivisionNaNTests, StaticWrapper_SafeDivide_ReturnsPassedInFallbackMatrix)
{
    using T                          = ParamType::value_type;
    const fgm::Mat2x3 resultantMat = fgm::Mat2x3<T>::safeDiv(GetParam(), 2.5, fgm::Mat2x3<T>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a matrix using @ref fgm::Mat2x3::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2x3DivisionTests, TryDivide_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x3 resultantMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref fgm::Mat2x3::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x3DivisionTests, TryDivide_DivisionByZeroReturnsZeroMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x3 resultantMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref fgm::Mat2x3::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x3DivisionTests, TryDivide_DivisionByZeroReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x3 resultantMat = this->_matrix.tryDiv(TypeParam(0), flag, fgm::Mat2x3<TypeParam>::zero());

    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref fgm::Mat2x3::tryDiv returns identity matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2x3DivisionNaNTests, TryDivide_ReturnsZeroMatrixByDefault)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x3 resultantMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref fgm::Mat2x3::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2x3DivisionNaNTests, TryDivide_ReturnsPassedInFallbackMatrix)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x3 resultantMat = GetParam().tryDiv(2.5, flag, fgm::Mat2x3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using @ref fgm::Mat2x3::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2x3DivisionNaNTests, TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Mat2x3 resultantMat =
        GetParam().tryDiv(0, flag, fgm::Mat2x3<ParamType::value_type>::zero());
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a matrix using the static variant of @ref fgm::Mat2x3::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2x3DivisionTests, StaticWrapper_TryDivide_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x3 resultantMat = fgm::Mat2x3<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat2x3::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x3DivisionTests, StaticWrapper_TryDivide_DivisionByZeroReturnsZeroMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x3 resultantMat = fgm::Mat2x3<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat2x3::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x3DivisionTests, StaticWrapper_TryDivide_DivisionByZeroReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2x3 resultantMat =
        fgm::Mat2x3<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, fgm::Mat2x3<TypeParam>::zero());
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat2x3::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2x3DivisionNaNTests, StaticWrapper_TryDivide_ReturnsZeroMatrixByDefault)
{
    fgm::OperationStatus flag;
    using T                          = ParamType::value_type;
    const fgm::Mat2x3 resultantMat = fgm::Mat2x3<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_ZERO(resultantMat);

    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using the static variant of @ref fgm::Mat2x3::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2x3DivisionNaNTests, StaticWrapper_TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    using T                                           = ParamType::value_type;
    [[maybe_unused]] const fgm::Mat2x3 resultantMat = fgm::Mat2x3<T>::tryDiv(GetParam(), T(0), flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat2x3::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2x3DivisionNaNTests, StaticWrapper_TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    const fgm::Mat2x3 resultantMat =
        fgm::Mat2x3<T>::tryDiv(GetParam(), 2.5, flag, fgm::Mat2x3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}
/** @} */
