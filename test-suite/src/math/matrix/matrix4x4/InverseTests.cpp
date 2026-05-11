/**
 * @file InverseTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 09, 2026
 *
 * @brief Verify @ref fgm::Matrix4D inverse logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**************************************
 *                                    *
 *              SETUP                 *
 *                                    *
 **************************************/

template <typename T>
class Matrix4DInverse: public ::testing::Test
{
protected:
    using Mag = fgm::Magnitude<T>;
    fgm::Matrix4D<T> _matrix;
    fgm::Matrix4D<Mag> _expectedInverse;

    void SetUp() override
    {
        _matrix          = { { T(3), T(1), T(8), T(4) },
                             { T(3), T(7), T(4), T(2) },
                             { T(6), T(1), T(2), T(1) },
                             { T(3), T(1), T(6), T(2) } };
        _expectedInverse = { { Mag(-0.037878787878788), Mag(-0.022727272727273), Mag(0.196969696969697), Mag(0.0) },
                             { Mag(-0.068181818181818), Mag(0.159090909090909), Mag(-0.045454545454545), Mag(0.0) },
                             { Mag(-0.204545454545455), Mag(-0.022727272727273), Mag(-0.136363636363636), Mag(0.5) },
                             { Mag(0.704545454545455), Mag(0.022727272727273), Mag(0.136363636363636), Mag(-1.0) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix4D inverse, parameterized @ref SupportedSignedArithmeticTypes */
TYPED_TEST_SUITE(Matrix4DInverse, SupportedSignedArithmeticTypes);


/** @brief Test fixture for calculating @ref fgm::Matrix4D inverse with singular matrices */
class SingularMatrix4DInverse: public ::testing::TestWithParam<fgm::Matrix4D<float>>
{};
INSTANTIATE_TEST_SUITE_P(
    Matrix4DInverseTestSuite, SingularMatrix4DInverse,
    ::testing::Values(
        fgm::Matrix4D{ fgm::Vector4D{ 1.0f, 2.0f, 3.0f, 4.0f }, fgm::Vector4D{ 1.0f, 2.0f, 3.0f, 4.0f },
                       fgm::Vector4D{ 7.0f, 8.0f, 9.0f, 12.0f }, fgm::Vector4D{ 1.0f, 85.0f, 19.0f, 12.0f } },
        fgm::Matrix4D{ fgm::Vector4D{ 1.0f, 1.0f, 3.0f, 4.0f }, fgm::Vector4D{ 2.0f, 2.0f, 3.0f, 4.0f },
                       fgm::Vector4D{ 3.0f, 3.0f, 9.0f, 12.0f }, fgm::Vector4D{ 4.0f, 4.0f, 31.6f, 2.0f } },
        fgm::Matrix4D{ fgm::Vector4D{ 0.0f, 0.0f, 0.0f, 0.0f }, fgm::Vector4D{ 2.0f, 2.0f, 3.0f, 4.0f },
                       fgm::Vector4D{ 3.0f, 3.0f, 9.0f, 12.0f }, fgm::Vector4D{ 4.0f, 4.0f, 31.6f, 2.0f } },
        fgm::Matrix4D{ fgm::Vector4D{ 0.0f, 1.0f, 3.0f, 4.0f }, fgm::Vector4D{ 0.0f, 2.0f, 3.0f, 4.0f },
                       fgm::Vector4D{ 0.0f, 3.0f, 9.0f, 12.0f }, fgm::Vector4D{ 0.0f, 4.0f, 31.6f, 2.0f } },
        fgm::Matrix4D{ fgm::Vector4D{ 1.0f, 2.0f, 3.0f, 4.0f }, fgm::Vector4D{ 2.0f, 4.0f, 6.0f, 8.0f },
                       fgm::Vector4D{ 3.0f, 3.0f, 9.0f, 12.0f }, fgm::Vector4D{ 4.0f, 4.0f, 31.6f, 2.0f } },
        fgm::Matrix4D{ fgm::Vector4D{ 1.0f, 2.0f, 3.0f, 4.0f }, fgm::Vector4D{ 2.0f, 4.0f, 5.0f, 10.0f },
                       fgm::Vector4D{ 3.0f, 6.0f, 9.0f, 12.0f }, fgm::Vector4D{ 4.0f, 8.0f, 31.6f, 2.0f } }));


/** @brief Test fixture for @ref fgm::Matrix4D inverse with NaN vectors. */
class NaNMatrix4DInverse: public ::testing::TestWithParam<fgm::Matrix4D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Matrix4DInverseTestSuite, NaNMatrix4DInverse,
                         ::testing::Values(fgm::Matrix4D<float>{ fgm::constants::NaN, 3.0f, 3.0f, 3.0f },
                                           fgm::Matrix4D<float>{ 3.0f, fgm::constants::NaN, 3.0f, 3.0f },
                                           fgm::Matrix4D<float>{ 3.0f, 3.0f, fgm::constants::NaN, 3.0f },
                                           fgm::Matrix4D<float>{ 3.0f, 3.0f, 3.0f, fgm::constants::NaN },
                                           fgm::Matrix4D<float>{ fgm ::constants::NaN, fgm::constants::NaN,
                                                                 fgm ::constants::NaN, fgm ::constants::NaN }));


/**
 * @addtogroup T_FGM_Mat4x4_Inverse
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that matrix inverse functions are available at compile time. */
namespace
{
    // constexpr fgm::Matrix4D MAT(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);
    // //TODO: Add back
    // // Verify matrix inverse (member function)
    // constexpr fgm::Matrix4D INV_MAT = MAT.inverse();
    // static_assert(INV_MAT(0, 0) - -24.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT(0, 1) - 18.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT(0, 2) - 5.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT(1, 0) - 20.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT(1, 1) - -15.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT(1, 2) - -4.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT(2, 0) - -5.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT(2, 1) - 4.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT(2, 2) - 1.0f <= fgm::Config::FLOAT_EPSILON);
    //
    // // Verify matrix inverse (static function)
    // constexpr fgm::Matrix4D INV_MAT_S = fgm::Matrix4D<float>::inverse(MAT);
    // static_assert(INV_MAT_S(0, 0) - -24.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT_S(0, 1) - 18.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT_S(0, 2) - 5.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT_S(1, 0) - 20.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT_S(1, 1) - -15.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT_S(1, 2) - -4.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT_S(2, 0) - -5.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT_S(2, 1) - 4.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(INV_MAT_S(2, 2) - 1.0f <= fgm::Config::FLOAT_EPSILON);

    //
    // // Verify matrix safeInverse (member function)
    // constexpr fgm::Matrix4D SAFE_INV_MAT = MAT.safeInverse();
    // static_assert(SAFE_INV_MAT(0, 0) - -24.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT(0, 1) - 18.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT(0, 2) - 5.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT(1, 0) - 20.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT(1, 1) - -15.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT(1, 2) - -4.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT(2, 0) - -5.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT(2, 1) - 4.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT(2, 2) - 1.0f <= fgm::Config::FLOAT_EPSILON);
    //
    // // Verify matrix safeInverse (static function)
    // constexpr fgm::Matrix4D SAFE_INV_MAT_S = fgm::Matrix4D<float>::safeInverseOf(MAT);
    // static_assert(SAFE_INV_MAT_S(0, 0) - -24.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT_S(0, 1) - 18.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT_S(0, 2) - 5.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT_S(1, 0) - 20.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT_S(1, 1) - -15.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT_S(1, 2) - -4.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT_S(2, 0) - -5.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT_S(2, 1) - 4.0f <= fgm::Config::FLOAT_EPSILON);
    // static_assert(SAFE_INV_MAT_S(2, 2) - 1.0f <= fgm::Config::FLOAT_EPSILON);
} // namespace



/**************************************
 *                                    *
 *       INVERSE TESTS (RUNTIME)      *
 *                                    *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Matrix4D::inverse returns a new matrix that when multiplied
 *        with the original matrix returns an identity matrix.
 */
TYPED_TEST(Matrix4DInverse, ExchangesRowsAndColumnElements)
{ EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.inverse()); }


/** @brief Verify that inverse of matrix times itself is an identity matrix. */
TYPED_TEST(Matrix4DInverse, InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.inverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}

/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Matrix4D::inverse returns a new matrix that
 *        when multiplied with the original matrix returns an identity matrix.
 */
TYPED_TEST(Matrix4DInverse, StaticWrapper_ExchangesRowsAndColumnElements)
{ EXPECT_MAT_EQ(this->_expectedInverse, fgm::Matrix4D<TypeParam>::inverse(this->_matrix)); }


/** @brief Verify that inverse of matrix (using the static variant) times itself is an identity matrix. */
TYPED_TEST(Matrix4DInverse, StaticWrapper_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = fgm::Matrix4D<TypeParam>::inverse(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}

/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Matrix4D::inverse
 *        fails assertion in debug mode.
 */
TEST_P(SingularMatrix4DInverse, Inverse_FailsAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}



/**************************************
 *                                    *
 *          SAFE INVERSE TESTS        *
 *                                    *
 **************************************/

// /**
//  * @brief Verify that inverting a matrix using @ref fgm::Matrix4D::safeInverse exchanges row and
//  *        column elements and returns a new matrix.
//  */
// TYPED_TEST(Matrix4DInverse, SafeInverse_ExchangesRowsAndColumnElements)
// {
//     EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.safeInverse());
// }
//
//
// /**
//  * @brief Verify that inverse of matrix (using @ref fgm::Matrix4D::safeInverse) times itself
//  *        is an identity matrix.
// /*/
// TYPED_TEST(Matrix4DInverse, SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
// {
//     const auto invMatrix = this->_matrix.safeInverse();
//     EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
// }
//
//
// /**
//  * @brief Verify that inverting a singular matrix using @ref fgm::Matrix4D::safeInverse
//  *        returns identity matrix by default.
//  */
// TEST_P(SingularMatrix4DInverse, SafeInverse_ReturnsIdentityMatrixByDefault)
// {
//     const auto& matrix = GetParam();
//     EXPECT_MAT_IDENTITY(matrix.safeInverse());
// }
//
//
// /**
//  * @brief Verify that inverting a singular matrix using @ref fgm::Matrix4D::safeInverse
//  *        returns passed-in fallback.
//  */
// TEST_P(SingularMatrix4DInverse, SafeInverse_ReturnsPassedInFallback)
// {
//     const auto& inverseMatrix = GetParam().safeInverse(fgm::mat3d::zero<ParamType::value_type>);
//     EXPECT_MAT_ZERO(inverseMatrix);
// }
//
//
// /**
//  * @brief Verify that inverting a NaN matrix using @ref fgm::Matrix4D::safeInverse
//  *        returns identity matrix by default.
//  */
// TEST_P(NaNMatrix4DInverse, SafeInverse_ReturnsIdentityMatrixByDefault)
// {
//     const auto& matrix = GetParam();
//     EXPECT_MAT_IDENTITY(matrix.safeInverse());
// }
//
//
// /**
//  * @brief Verify that inverting a NaN matrix using @ref fgm::Matrix4D::safeInverse
//  *        returns passed-in fallback.
//  */
// TEST_P(NaNMatrix4DInverse, SafeInverse_ReturnsPassedInFallback)
// {
//     const auto& inverseMatrix = GetParam().safeInverse(fgm::mat3d::zero<ParamType::value_type>);
//     EXPECT_MAT_ZERO(inverseMatrix);
// }
//
//
// /**
//  * @brief Verify that inverting a matrix using static variant of @ref fgm::Matrix4D::safeInverse exchanges row and
//  *        column elements and returns a new matrix.
//  */
//  TYPED_TEST(Matrix4DInverse, StaticWrapper_SafeInverse_ExchangesRowsAndColumnElements)
// {
//     EXPECT_MAT_EQ(this->_expectedInverse, fgm::Matrix4D<TypeParam>::safeInverseOf(this->_matrix));
// }
//
//
// /**
//  * @brief Verify that inverse of matrix (using static variant of @ref fgm::Matrix4D::safeInverse) times itself is an
//  *        identity matrix.
//  */
//  TYPED_TEST(Matrix4DInverse, StaticWrapper_SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
// {
//     const auto invMatrix = fgm::Matrix4D<TypeParam>::safeInverseOf(this->_matrix);
//     EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
// }
//
//
// /**
//  * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix4D::safeInverseOf
//  *         returns identity matrix by default.
//  */
//  TEST_P(SingularMatrix4DInverse, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
// {
//     const auto& matrix = GetParam();
//     EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
// }
//
//
// /**
//  * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix4D::safeInverseOf
//  *         returns passed-in fallback.
//  */
//  TEST_P(SingularMatrix4DInverse, StaticWrapper_SafeInverse_ReturnsPassedInFallback)
// {
//     const auto& matrix = GetParam();
//     EXPECT_MAT_ZERO(ParamType::safeInverseOf(matrix, fgm::mat3d::zero<ParamType::value_type>));
// }
//
//
// /**
//  * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Matrix4D::safeInverse
//  *        returns identity matrix by default.
//  */
//  TEST_P(NaNMatrix4DInverse, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
// {
//     const auto& matrix = GetParam();
//     EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
// }
//
//
// /**
//  * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Matrix4D::safeInverse
//  *        returns passed-in fallback.
//  */
//  TEST_P(NaNMatrix4DInverse, StaticWrapper_SafeInverse_ReturnsPassedInFallback)
// {
//     const auto& inverseMatrix = ParamType::safeInverseOf(GetParam(), fgm::mat3d::zero<ParamType::value_type>);
//     EXPECT_MAT_ZERO(inverseMatrix);
// }
//
//
// /**************************************
//  *                                    *
//  *          TRY INVERSE TESTS        *
//  *                                    *
//  **************************************/
//
// /**
//  * @brief Verify that inverting a matrix using @ref fgm::Matrix4D::tryInverse exchanges row and column elements and
//  *        returns a new matrix and sets status flag to @ref OperationStatus::SUCCESS.
//  */
//  TYPED_TEST(Matrix4DInverse, TryInverse_ExchangesRowsAndColumnElements)
// {
//     fgm::OperationStatus flag;
//     EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.tryInverse(flag));
//     EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
// }
//
//
// /**
//  * @brief Verify that inverse of matrix (using @ref fgm::Matrix4D::tryInverse) times itself is an identity matrix and
//  *        sets status flag to @ref OperationStatus::SUCCESS.
//  */
//  TYPED_TEST(Matrix4DInverse, TryInverse_InverseTimesMatrixReturnsIdentityMatrix)
// {
//     fgm::OperationStatus flag;
//     const auto invMatrix = this->_matrix.tryInverse(flag);
//     EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
//     EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
// }
//
//
// /**
//  * @brief Verify that inverting a singular matrix using @ref fgm::Matrix4D::tryInverse
//  *        returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
//  */
//  TEST_P(SingularMatrix4DInverse, TryInverse_ReturnsIdentityMatrixByDefault)
// {
//     fgm::OperationStatus flag;
//     const auto& matrix = GetParam();
//     EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
//     EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @brief Verify that inverting a singular matrix using @ref fgm::Matrix4D::tryInverse
//  *        returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
//  */
//  TEST_P(SingularMatrix4DInverse, TryInverse_ReturnsPassedInFallback)
// {
//     fgm::OperationStatus flag;
//     const auto& inverseMatrix = GetParam().tryInverse(flag, fgm::mat3d::zero<ParamType::value_type>);
//     EXPECT_MAT_ZERO(inverseMatrix);
//     EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @brief Verify that inverting a NaN matrix using @ref fgm::Matrix4D::tryInverse
//  *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
//  */
//  TEST_P(NaNMatrix4DInverse, TryInverse_ReturnsIdentityMatrixByDefault)
// {
//     fgm::OperationStatus flag;
//     const auto& matrix = GetParam();
//     EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @brief Verify that inverting a NaN matrix using @ref fgm::Matrix4D::tryInverse returns passed-in fallback
//  *        and sets status flag to @ref OperationStatus::NANOPERAND.
//  */
//  TEST_P(NaNMatrix4DInverse, TryInverse_ReturnsPassedInFallback)
// {
//     fgm::OperationStatus flag;
//     const auto& inverseMatrix = GetParam().tryInverse(flag, fgm::mat3d::zero<ParamType::value_type>);
//     EXPECT_MAT_ZERO(inverseMatrix);
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @brief Verify that inverting a matrix using static variant of @ref fgm::Matrix4D::tryInverse exchanges row and
//  *        column elements and returns a new matrix and sets status flag to @ref OperationStatus::SUCCESS.
//  */
//  TYPED_TEST(Matrix4DInverse, StaticWrapper_TryInverse_ExchangesRowsAndColumnElements)
// {
//     fgm::OperationStatus flag;
//     EXPECT_MAT_EQ(this->_expectedInverse, fgm::Matrix4D<TypeParam>::tryInverseOf(this->_matrix, flag));
//     EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
// }
//
//
// /**
//  * @brief Verify that inverse of matrix (using static variant of @ref fgm::Matrix4D::tryInverse) times itself is an
//  *        identity matrix and sets status flag to @ref OperationStatus::SUCCESS.
//  */
//  TYPED_TEST(Matrix4DInverse, StaticWrapper_TryInverse_InverseTimesMatrixReturnsIdentityMatrix)
// {
//     fgm::OperationStatus flag;
//     const auto invMatrix = fgm::Matrix4D<TypeParam>::tryInverseOf(this->_matrix, flag);
//     EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
//     EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
// }
//
//
// /**
//  * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix4D::tryInverseOf
//  *         returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
//  */
//  TEST_P(SingularMatrix4DInverse, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefault)
// {
//     fgm::OperationStatus flag;
//     const auto& matrix = GetParam();
//     EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
//     EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix4D::tryInverseOf
//  *         returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
//  */
//  TEST_P(SingularMatrix4DInverse, StaticWrapper_TryInverse_ReturnsPassedInFallback)
// {
//     fgm::OperationStatus flag;
//     const auto& matrix = GetParam();
//     EXPECT_MAT_ZERO(ParamType::tryInverseOf(matrix, flag, fgm::mat3d::zero<ParamType::value_type>));
//     EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Matrix4D::tryInverse
//  *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
//  */
//  TEST_P(NaNMatrix4DInverse, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefault)
// {
//     fgm::OperationStatus flag;
//     const auto& matrix = GetParam();
//     EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Matrix4D::tryInverse
//  *        returns passed-in fallback and sets status flag to @ref OperationStatus::NANOPERAND.
//  */
//  TEST_P(NaNMatrix4DInverse, StaticWrapper_TryInverse_ReturnsPassedInFallback)
// {
//     fgm::OperationStatus flag;
//     const auto& inverseMatrix = ParamType::tryInverseOf(GetParam(), flag, fgm::mat3d::zero<ParamType::value_type>);
//     EXPECT_MAT_ZERO(inverseMatrix);
//     EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
// }

/** @} */