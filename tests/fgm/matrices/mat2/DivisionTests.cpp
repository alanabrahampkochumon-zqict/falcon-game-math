/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 13, 2026
 *
 * @brief Verify @ref fgm::Mat2 division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"



/**
 * @addtogroup T_FGM_Mat2x2_Division
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat2 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2DivisionTests: public testing::Test
    {
    protected:
        fgm::Mat2<T> _matrix;
        T _scalar;
        fgm::Mat2<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { fgm::Vec2<T>{ 7, 3 }, fgm::Vec2<T>{ 1, 6 } };
            _scalar         = T(3);
            _expectedMatrix = { fgm::Vec2{ T(2.333333333333333), T(1) }, fgm::Vec2{ T(0.3333333333333333), T(2) } };
        }
    };
    TYPED_TEST_SUITE(Mat2DivisionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref fgm::Mat2 Division with NaN elements.
     */
    class Mat2DivisionNaNTests: public testing::TestWithParam<fgm::Mat2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2InvalidDivision, Mat2DivisionNaNTests,
                             ::testing::Values(fgm::Mat2<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                                               fgm::Mat2<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                                               fgm::Mat2<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                                               fgm::Mat2<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                                               fgm::Mat2<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN, fgm ::constants::NaN)));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat2 MAT(2, 4, 6, 8);

        /// @test Verify that Mat2 division operator returns a valid matrix at compile time.
        constexpr fgm::Mat2 DIV_OP_MAT = MAT / 2;
        static_assert(DIV_OP_MAT(0, 0) == 1);
        static_assert(DIV_OP_MAT(0, 1) == 2);
        static_assert(DIV_OP_MAT(1, 0) == 3);
        static_assert(DIV_OP_MAT(1, 1) == 4);


        /// @test Verify that Mat2 safeDiv returns a valid matrix at compile time.
        constexpr fgm::Mat2 SAFE_DIV_MAT = MAT.safeDiv(2);
        static_assert(SAFE_DIV_MAT(0, 0) == 1);
        static_assert(SAFE_DIV_MAT(0, 1) == 2);
        static_assert(SAFE_DIV_MAT(1, 0) == 3);
        static_assert(SAFE_DIV_MAT(1, 1) == 4);


        /// @test Verify that Mat2 safeDiv (static wrapper) returns a valid matrix at compile time.
        constexpr fgm::Mat2 SAFE_DIV_MAT_STATIC = fgm::Mat2<int>::safeDiv(MAT, 2);
        static_assert(SAFE_DIV_MAT_STATIC(0, 0) == 1);
        static_assert(SAFE_DIV_MAT_STATIC(0, 1) == 2);
        static_assert(SAFE_DIV_MAT_STATIC(1, 0) == 3);
        static_assert(SAFE_DIV_MAT_STATIC(1, 1) == 4);

        // Matrix Try Division
        // NOT available at compile time due to [out] parameter (OperationStatus).

    } // namespace static_tests

} // namespace




/**************************************
 *      DIVISION TESTS (RUNTIME)      *
 **************************************/

TYPED_TEST(Mat2DivisionTests, DivideOperator_ReturnsAValidMatrix)
{
    const fgm::Mat2 resultantMat = this->_matrix / this->_scalar;
    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
}


TYPED_TEST(Mat2DivisionTests, DivideEqualsOperator_PerformsElementWiseDivisionInPlace)
{
    fgm::Mat2 matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}



/**************************************
 *         SAFE DIVISION TESTS        *
 **************************************/

TYPED_TEST(Mat2DivisionTests, SafeDiv_ReturnsAValidMatrix)
{
    const fgm::Mat2 resultantMat = this->_matrix.safeDiv(this->_scalar);
    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
}


TYPED_TEST(Mat2DivisionTests, SafeDiv_DivisionByZero_ReturnsIdentityMatrixByDefault)
{
    const fgm::Mat2 resultantMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_IDENTITY(resultantMat);
}


TYPED_TEST(Mat2DivisionTests, SafeDivide_DivisionByZero_ReturnsPassedInFallbackMatrix)
{
    const fgm::Mat2 resultantMat = this->_matrix.safeDiv(TypeParam(0), fgm::Mat2<TypeParam>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}


TEST_P(Mat2DivisionNaNTests, SafeDivide_ReturnsIdentityMatrixByDefault)
{
    const fgm::Mat2 resultantMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_IDENTITY(resultantMat);
}


TEST_P(Mat2DivisionNaNTests, SafeDivide_ReturnsPassedInFallbackMatrix)
{
    const fgm::Mat2 resultantMat = GetParam().safeDiv(2.5, fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}


TYPED_TEST(Mat2DivisionTests, StaticWrapper_SafeDivide_ReturnsAValidMatrix)
{
    const fgm::Mat2 resultantMat = fgm::Mat2<TypeParam>::safeDiv(this->_matrix, this->_scalar);
    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
}


TYPED_TEST(Mat2DivisionTests, StaticWrapper_SafeDivide_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const fgm::Mat2 resultantMat = fgm::Mat2<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_IDENTITY(resultantMat);
}


TYPED_TEST(Mat2DivisionTests, StaticWrapper_SafeDivide_DivisionByZeroReturnsPassedInFallbackMatrix)
{
    const fgm::Mat2 resultantMat =
        fgm::Mat2<TypeParam>::safeDiv(this->_matrix, TypeParam(0), fgm::Mat2<TypeParam>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}


TEST_P(Mat2DivisionNaNTests, StaticWrapper_SafeDivide_ReturnsIdentityMatrixByDefault)
{
    using T                          = ParamType::value_type;
    const fgm::Mat2 resultantMat = fgm::Mat2<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_IDENTITY(resultantMat);
}


TEST_P(Mat2DivisionNaNTests, StaticWrapper_SafeDivide_ReturnsPassedInFallbackMatrix)
{
    using T                          = ParamType::value_type;
    const fgm::Mat2 resultantMat = fgm::Mat2<T>::safeDiv(GetParam(), 2.5, fgm::Mat2<T>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a matrix using @ref fgm::Mat2::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2DivisionTests, TryDivide_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2 resultantMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref fgm::Mat2::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2DivisionTests, TryDivide_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2 resultantMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_IDENTITY(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref fgm::Mat2::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2DivisionTests, TryDivide_DivisionByZeroReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2 resultantMat = this->_matrix.tryDiv(TypeParam(0), flag, fgm::Mat2<TypeParam>::zero());

    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref fgm::Mat2::tryDiv returns identity matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2DivisionNaNTests, TryDivide_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const fgm::Mat2 resultantMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_IDENTITY(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref fgm::Mat2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2DivisionNaNTests, TryDivide_ReturnsPassedInFallbackMatrix)
{
    fgm::OperationStatus flag;
    const fgm::Mat2 resultantMat = GetParam().tryDiv(2.5, flag, fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using @ref fgm::Mat2::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2DivisionNaNTests, TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    [[maybe_unused]] const fgm::Mat2 resultantMat =
        GetParam().tryDiv(0, flag, fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a matrix using the static variant of @ref fgm::Mat2::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2DivisionTests, StaticWrapper_TryDivide_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2 resultantMat = fgm::Mat2<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat2::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2DivisionTests, StaticWrapper_TryDivide_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2 resultantMat = fgm::Mat2<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_IDENTITY(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref fgm::Mat2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2DivisionTests, StaticWrapper_TryDivide_DivisionByZeroReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const fgm::Mat2 resultantMat =
        fgm::Mat2<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, fgm::Mat2<TypeParam>::zero());
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat2::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2DivisionNaNTests, StaticWrapper_TryDivide_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    using T                          = ParamType::value_type;
    const fgm::Mat2 resultantMat = fgm::Mat2<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_IDENTITY(resultantMat);

    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using the static variant of @ref fgm::Mat2::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2DivisionNaNTests, StaticWrapper_TryDivide_NaNOperandTakesPrecedenceOverZeroDivision)
{
    fgm::OperationStatus flag;
    using T                                           = ParamType::value_type;
    [[maybe_unused]] const fgm::Mat2 resultantMat = fgm::Mat2<T>::tryDiv(GetParam(), T(0), flag);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref fgm::Mat2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2DivisionNaNTests, StaticWrapper_TryDivide_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    using T = ParamType::value_type;
    const fgm::Mat2 resultantMat =
        fgm::Mat2<T>::tryDiv(GetParam(), 2.5, flag, fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
