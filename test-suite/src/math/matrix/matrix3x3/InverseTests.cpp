/**
 * @file InverseTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 28, 2026
 *
 * @brief Verify @ref fgm::Matrix3D inverse logic.
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
class Matrix3DInverse: public ::testing::Test
{
protected:
    using Mag = fgm::Magnitude<T>;
    fgm::Matrix3D<T> _matrix;
    fgm::Matrix3D<Mag> _expectedInverse;

    void SetUp() override
    {
        _matrix = { { T(3), T(1), T(8) }, { T(3), T(9), T(3) }, { T(5), T(6), T(1) } };
        _expectedInverse = { { Mag(0.038961038961039), Mag(-0.203463203463203), Mag(0.298701298701299) },
                             { Mag(-0.051948051948052), Mag(0.16017316017316), Mag(-0.064935064935065) },
                             { Mag(0.116883116883117), Mag(0.056277056277056), Mag(-0.103896103896104) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix3D inverse, parameterized @ref SupportedSignedArithmeticTypes */
TYPED_TEST_SUITE(Matrix3DInverse, SupportedSignedArithmeticTypes);


/** @brief Test fixture for calculating @ref fgm::Matrix3D inverse with singular matrices */
 class SingularMatrix3DInverse: public ::testing::TestWithParam<fgm::Matrix3D<float>>
{};
 INSTANTIATE_TEST_SUITE_P(Matrix3DInverseTestSuite, SingularMatrix3DInverse,
    ::testing::Values(fgm::Matrix3D{ fgm::Vector3D{ 1.0f, 2.0f, 3.0f }, fgm::Vector3D{ 1.0f, 2.0f, 3.0f },
                                     fgm::Vector3D{ 7.0f, 8.0f, 9.0f } },
                      fgm::Matrix3D{ fgm::Vector3D{ 1.0f, 1.0f, 5.0f }, fgm::Vector3D{ 2.0f, 2.0f, 3.0f },
                                     fgm::Vector3D{ 3.0f, 3.0f, 9.0f } },
                      fgm::Matrix3D{ fgm::Vector3D{ 0.0f, 0.0f, 0.0f }, fgm::Vector3D{ 1.0f, 2.0f, 3.0f },
                                     fgm::Vector3D{ 1.0f, 8.0f, 9.0f } },
                      fgm::Matrix3D{ fgm::Vector3D{ 0.0f, 5.0f, 1.0f }, fgm::Vector3D{ 0.0f, 2.0f, 3.0f },
                                     fgm::Vector3D{ 0.0f, 8.0f, 9.0f } },
                      fgm::Matrix3D{ fgm::Vector3D{ 1.0f, 2.0f, 3.0f }, fgm::Vector3D{ 2.0f, 4.0f, 6.0f },
                                     fgm::Vector3D{ 7.0f, 8.0f, 9.0f } },
                      fgm::Matrix3D{ fgm::Vector3D{ 1.0f, 2.0f, 1.0f }, fgm::Vector3D{ 2.0f, 4.0f, 3.0f },
                                     fgm::Vector3D{ 3.0f, 6.0f, 9.0f } }));



///** @brief Test fixture for @ref fgm::Matrix3D inverse with NaN vectors. */
// class NaNMatrix3DInverse: public ::testing::TestWithParam<fgm::Matrix3D<float>>
//{};
// INSTANTIATE_TEST_SUITE_P(Matrix3DDivisionTestSuite, NaNMatrix3DInverse,
//                          ::testing::Values(fgm::Matrix3D<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
//                                            fgm::Matrix3D<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f),
//                                            fgm::Matrix3D<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f),
//                                            fgm::Matrix3D<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN),
//                                            fgm::Matrix3D<float>(fgm ::constants::NaN, fgm::constants::NaN,
//                                                                 fgm ::constants::NaN, fgm ::constants::NaN)));
//
//
//
///**
// * @addtogroup T_FGM_Mat2x2_Inverse
// * @{
// */
//
///**************************************
// *                                    *
// *           STATIC TESTS             *
// *                                    *
// **************************************/
//
///** @brief Verify that matrix inverse is available at compile time. */
//// namespace
////{
////     constexpr fgm::Matrix3D MAT(1, 2, 3, 4);
////    const fgm::Matrix3D mat(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);
////    const fgm::Matrix3D expectedInverse(-24.0f, 18.0f, 5.0f, 20.0f, -15.0f, -4.0f, -5.0f, 4.0f, 1.0f);
////     // Verify matrix transpose (member function)
////     constexpr fgm::Matrix3D TRANS_MAT = MAT.transpose();
////     static_assert(TRANS_MAT(0, 0) == 1);
////     static_assert(TRANS_MAT(0, 1) == 3);
////     static_assert(TRANS_MAT(1, 0) == 2);
////     static_assert(TRANS_MAT(1, 1) == 4);
////
////     // Verify matrix transpose (static function)
////     constexpr fgm::Matrix3D TRANS_MAT_S = fgm::Matrix3D<int>::transpose(MAT);
////     static_assert(TRANS_MAT_S(0, 0) == 1);
////     static_assert(TRANS_MAT_S(0, 1) == 3);
////     static_assert(TRANS_MAT_S(1, 0) == 2);
////     static_assert(TRANS_MAT_S(1, 1) == 4);
//// } // namespace



/**************************************
 *                                    *
 *       INVERSE TESTS (RUNTIME)      *
 *                                    *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Matrix3D::inverse exchanges row and
 *        column elements and returns a new matrix.
 */
 TYPED_TEST(Matrix3DInverse, ExchangesRowsAndColumnElements)
{
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.inverse());
}


/** @brief Verify that inverse of matrix times itself is an identity matrix. */
 TYPED_TEST(Matrix3DInverse, InverseTimesMatrixReturnsIdentityMatrix)
{
     const auto invMatrix = this->_matrix.inverse();
     EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
 }


/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Matrix3D::inverse exchanges row and
 *        column elements and returns a new matrix.
 */
 TYPED_TEST(Matrix3DInverse, StaticWrapper_ExchangesRowsAndColumnElements)
{
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Matrix3D<TypeParam>::inverse(this->_matrix));
}


/** @brief Verify that inverse of matrix (using the static variant) times itself is an identity matrix. */
 TYPED_TEST(Matrix3DInverse, StaticWrapper_InverseTimesMatrixReturnsIdentityMatrix)
{
     const auto invMatrix = fgm::Matrix3D<TypeParam>::inverse(this->_matrix);
     EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
 }


///**************************************
// *                                    *
// *          SAFE INVERSE TESTS        *
// *                                    *
// **************************************/
//
///**
// * @brief Verify that inverting a matrix using @ref fgm::Matrix3D::safeInverse exchanges row and
// *        column elements and returns a new matrix.
// */
// TYPED_TEST(Matrix3DInverse, SafeInverse_ExchangesRowsAndColumnElements)
//{
//    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.safeInverse());
//}
//
//
///** @brief Verify that inverse of matrix (using @ref fgm::Matrix3D::safeInverse) times itself is an identity matrix.
///*/
// TYPED_TEST(Matrix3DInverse, SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
//{
//     const auto invMatrix = this->_matrix.safeInverse();
//     EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
// }
//
//
///**
// * @brief Verify that inverting a singular matrix using @ref fgm::Matrix3D::safeInverse
// *        returns identity matrix by default.
// */
// TEST_P(SingularMatrix3DInverse, SafeInverse_ReturnsIdentityMatrixByDefault)
//{
//    const auto& matrix = GetParam();
//    EXPECT_MAT_IDENTITY(matrix.safeInverse());
//}
//
//
///**
// * @brief Verify that inverting a singular matrix using @ref fgm::Matrix3D::safeInverse
// *        returns passed-in fallback.
// */
// TEST_P(SingularMatrix3DInverse, SafeInverse_ReturnsPassedInFallback)
//{
//    const auto& inverseMatrix = GetParam().safeInverse(fgm::mat2d::zero<ParamType::value_type>);
//    EXPECT_MAT_ZERO(inverseMatrix);
//}
//
//
///**
// * @brief Verify that inverting a NaN matrix using @ref fgm::Matrix3D::safeInverse
// *        returns identity matrix by default.
// */
// TEST_P(NaNMatrix3DInverse, SafeInverse_ReturnsIdentityMatrixByDefault)
//{
//    const auto& matrix = GetParam();
//    EXPECT_MAT_IDENTITY(matrix.safeInverse());
//}
//
//
///**
// * @brief Verify that inverting a NaN matrix using @ref fgm::Matrix3D::safeInverse
// *        returns passed-in fallback.
// */
// TEST_P(NaNMatrix3DInverse, SafeInverse_ReturnsPassedInFallback)
//{
//    const auto& inverseMatrix = GetParam().safeInverse(fgm::mat2d::zero<ParamType::value_type>);
//    EXPECT_MAT_ZERO(inverseMatrix);
//}
//
//
///**
// * @brief Verify that inverting a matrix using static variant of @ref fgm::Matrix3D::safeInverse exchanges row and
// *        column elements and returns a new matrix.
// */
// TYPED_TEST(Matrix3DInverse, StaticWrapper_SafeInverse_ExchangesRowsAndColumnElements)
//{
//    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Matrix3D<TypeParam>::safeInverseOf(this->_matrix));
//}
//
//
///**
// * @brief Verify that inverse of matrix (using static variant of @ref fgm::Matrix3D::safeInverse) times itself is an
// *        identity matrix.
// */
// TYPED_TEST(Matrix3DInverse, StaticWrapper_SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
//{
//    const auto invMatrix = fgm::Matrix3D<TypeParam>::safeInverseOf(this->_matrix);
//    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
//}
//
//
///**
// * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix3D::safeInverseOf
// *         returns identity matrix by default.
// */
// TEST_P(SingularMatrix3DInverse, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
//{
//    const auto& matrix = GetParam();
//    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
//}
//
//
///**
// * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix3D::safeInverseOf
// *         returns passed-in fallback.
// */
// TEST_P(SingularMatrix3DInverse, StaticWrapper_SafeInverse_ReturnsPassedInFallback)
//{
//    const auto& matrix = GetParam();
//    EXPECT_MAT_ZERO(ParamType::safeInverseOf(matrix, fgm::mat2d::zero<ParamType::value_type>));
//}
//
//
///**
// * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Matrix3D::safeInverse
// *        returns identity matrix by default.
// */
// TEST_P(NaNMatrix3DInverse, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
//{
//    const auto& matrix = GetParam();
//    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
//}
//
//
///**
// * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Matrix3D::safeInverse
// *        returns passed-in fallback.
// */
// TEST_P(NaNMatrix3DInverse, StaticWrapper_SafeInverse_ReturnsPassedInFallback)
//{
//    const auto& inverseMatrix = ParamType::safeInverseOf(GetParam(), fgm::mat2d::zero<ParamType::value_type>);
//    EXPECT_MAT_ZERO(inverseMatrix);
//}
//
//
///**************************************
// *                                    *
// *          TRY INVERSE TESTS        *
// *                                    *
// **************************************/
//
///**
// * @brief Verify that inverting a matrix using @ref fgm::Matrix3D::tryInverse exchanges row and column elements and
// *        returns a new matrix and sets status flag to @ref OperationStatus::SUCCESS.
// */
// TYPED_TEST(Matrix3DInverse, TryInverse_ExchangesRowsAndColumnElements)
//{
//    fgm::OperationStatus flag;
//    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.tryInverse(flag));
//    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
//}
//
//
///**
// * @brief Verify that inverse of matrix (using @ref fgm::Matrix3D::tryInverse) times itself is an identity matrix and
// *        sets status flag to @ref OperationStatus::SUCCESS.
// */
// TYPED_TEST(Matrix3DInverse, TryInverse_InverseTimesMatrixReturnsIdentityMatrix)
//{
//    fgm::OperationStatus flag;
//    const auto invMatrix = this->_matrix.tryInverse(flag);
//    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
//    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
//}
//
//
///**
// * @brief Verify that inverting a singular matrix using @ref fgm::Matrix3D::tryInverse
// *        returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
// */
// TEST_P(SingularMatrix3DInverse, TryInverse_ReturnsIdentityMatrixByDefault)
//{
//    fgm::OperationStatus flag;
//    const auto& matrix = GetParam();
//    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
//    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
//}
//
//
///**
// * @brief Verify that inverting a singular matrix using @ref fgm::Matrix3D::tryInverse
// *        returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
// */
// TEST_P(SingularMatrix3DInverse, TryInverse_ReturnsPassedInFallback)
//{
//    fgm::OperationStatus flag;
//    const auto& inverseMatrix = GetParam().tryInverse(flag, fgm::mat2d::zero<ParamType::value_type>);
//    EXPECT_MAT_ZERO(inverseMatrix);
//    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
//}
//
//
///**
// * @brief Verify that inverting a NaN matrix using @ref fgm::Matrix3D::tryInverse
// *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
// */
// TEST_P(NaNMatrix3DInverse, TryInverse_ReturnsIdentityMatrixByDefault)
//{
//    fgm::OperationStatus flag;
//    const auto& matrix = GetParam();
//    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
//
///**
// * @brief Verify that inverting a NaN matrix using @ref fgm::Matrix3D::tryInverse returns passed-in fallback
// *        and sets status flag to @ref OperationStatus::NANOPERAND.
// */
// TEST_P(NaNMatrix3DInverse, TryInverse_ReturnsPassedInFallback)
//{
//    fgm::OperationStatus flag;
//    const auto& inverseMatrix = GetParam().tryInverse(flag, fgm::mat2d::zero<ParamType::value_type>);
//    EXPECT_MAT_ZERO(inverseMatrix);
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
//
///**
// * @brief Verify that inverting a matrix using static variant of @ref fgm::Matrix3D::tryInverse exchanges row and
// *        column elements and returns a new matrix and sets status flag to @ref OperationStatus::SUCCESS.
// */
// TYPED_TEST(Matrix3DInverse, StaticWrapper_TryInverse_ExchangesRowsAndColumnElements)
//{
//    fgm::OperationStatus flag;
//    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Matrix3D<TypeParam>::tryInverseOf(this->_matrix, flag));
//    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
//}
//
//
///**
// * @brief Verify that inverse of matrix (using static variant of @ref fgm::Matrix3D::tryInverse) times itself is an
// *        identity matrix and sets status flag to @ref OperationStatus::SUCCESS.
// */
// TYPED_TEST(Matrix3DInverse, StaticWrapper_TryInverse_InverseTimesMatrixReturnsIdentityMatrix)
//{
//    fgm::OperationStatus flag;
//    const auto invMatrix = fgm::Matrix3D<TypeParam>::tryInverseOf(this->_matrix, flag);
//    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
//    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
//}
//
//
///**
// * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix3D::tryInverseOf
// *         returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
// */
// TEST_P(SingularMatrix3DInverse, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefault)
//{
//    fgm::OperationStatus flag;
//    const auto& matrix = GetParam();
//    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
//    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
//}
//
//
///**
// * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix3D::tryInverseOf
// *         returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
// */
// TEST_P(SingularMatrix3DInverse, StaticWrapper_TryInverse_ReturnsPassedInFallback)
//{
//    fgm::OperationStatus flag;
//    const auto& matrix = GetParam();
//    EXPECT_MAT_ZERO(ParamType::tryInverseOf(matrix, flag, fgm::mat2d::zero<ParamType::value_type>));
//    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
//}
//
//
///**
// * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Matrix3D::tryInverse
// *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
// */
// TEST_P(NaNMatrix3DInverse, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefault)
//{
//    fgm::OperationStatus flag;
//    const auto& matrix = GetParam();
//    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
//
///**
// * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Matrix3D::tryInverse
// *        returns passed-in fallback and sets status flag to @ref OperationStatus::NANOPERAND.
// */
// TEST_P(NaNMatrix3DInverse, StaticWrapper_TryInverse_ReturnsPassedInFallback)
//{
//    fgm::OperationStatus flag;
//    const auto& inverseMatrix = ParamType::tryInverseOf(GetParam(), flag, fgm::mat2d::zero<ParamType::value_type>);
//    EXPECT_MAT_ZERO(inverseMatrix);
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
///** @} */