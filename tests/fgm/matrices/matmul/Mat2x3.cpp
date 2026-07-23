/**
 * @file Mat2x3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref fgm::Mat2x3 vector and matrix multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"
#include "utils/VectorUtils.h"

#include <fgm/matrices/MatMul.h>
#include <gtest/gtest.h>

using namespace testutils;

template <typename T>
class Mat2x3Multiplication: public ::testing::Test
{
protected:
    fgm::Mat2<T> _expectedFPMat2, _expectedIntMat2;
    fgm::Mat2x3<T> _mat, _expectedFPMat2x3, _expectedIntMat2x3;
    fgm::Mat2x4<T> _expectedFPMat2x4, _expectedIntMat2x4;

    fgm::Mat3<T> _mat3x3;
    fgm::Mat3x2<T> _mat3x2;

    fgm::Mat3x4<T> _mat3x4;

    fgm::Vec2<T> _expectedFPVec2x1, _expectedIntVec2x1;
    fgm::Vec3<T> _vec3x1;

    void SetUp() override
    {
        _mat = { fgm::Vec2{ T(1.32194213899999991), T(4.32194213899999991) },
                 fgm::Vec2{ T(2.32194213899999991), T(5.32194213899999991) },
                 fgm::Vec2{ T(3.32194213899999991), T(6.32194213899999991) } };

        _mat3x3 = { fgm::Vec3{ T(5.12390421300000032), T(8.12390421299999943), T(11.12390421299999943) },
                    fgm::Vec3{ T(6.12390421300000032), T(9.12390421299999943), T(12.12390421299999943) },
                    fgm::Vec3{ T(7.12390421300000032), T(10.12390421299999943), T(13.12390421299999943) } };
        _mat3x4 = { fgm::Vec3{ T(5.12390421300000032), T(9.12390421299999943), T(13.12390421299999943) },
                    fgm::Vec3{ T(6.12390421300000032), T(10.12390421299999943), T(14.12390421299999943) },
                    fgm::Vec3{ T(7.12390421300000032), T(11.12390421299999943), T(15.12390421299999943) },
                    fgm::Vec3{ T(8.12390421299999943), T(12.12390421299999943), T(16.12390421299999943) } };

        _expectedFPMat2x4  = { fgm::Vec2{ T(71.55553299309299575), T(153.67067091009300839) },
                               fgm::Vec2{ T(78.52135941009299813), T(169.63649732709299656) },
                               fgm::Vec2{ T(85.48718582709298630), T(185.60232374409298473) },
                               fgm::Vec2{ T(92.45301224409298868), T(201.56815016109297289) } };
        _expectedIntMat2x4 = { fgm::Vec2{ T(62), T(143) }, fgm::Vec2{ T(68), T(158) }, fgm::Vec2{ T(74), T(173) },
                               fgm::Vec2{ T(80), T(188) } };

        _expectedFPMat2x3  = { fgm::Vec2{ T(62.58970657609299337), T(135.70484449309299180) },
                               fgm::Vec2{ T(69.55553299309298154), T(151.67067091009300839) },
                               fgm::Vec2{ T(76.52135941009299813), T(167.63649732709299656) } };
        _expectedIntMat2x3 = { fgm::Vec2{ T(54), T(126) }, fgm::Vec2{ T(60), T(141) }, fgm::Vec2{ T(66), T(156) } };

        _vec3x1 = fgm::Vec3{ T(5.12390421300000032), T(6.12390421300000032), T(7.12390421300000032) };

        _mat3x2 = { fgm::Vec3{ T(5.12390421300000032), T(7.12390421300000032), T(9.12390421299999943) },
                    fgm::Vec3{ T(6.12390421300000032), T(8.12390421299999943), T(10.12390421299999943) } };


        _expectedFPMat2  = { fgm::Vec2{ T(53.62388015909299099), T(117.73901807609298942) },
                             fgm::Vec2{ T(60.58970657609299337), T(133.70484449309299180) } };
        _expectedIntMat2 = { fgm::Vec2{ T(46), T(109) }, fgm::Vec2{ T(52), T(124) } };

        _expectedFPVec2x1  = fgm::Vec2{ T(44.65805374209299572), T(99.77319165909298704) };
        _expectedIntVec2x1 = fgm::Vec2{ T(38), T(92) };
    }
};
/** @brief Test fixture for @ref fgm::Mat2x3 multiplication, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Mat2x3Multiplication, SupportedArithmeticTypes);


/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that matrix multiplication operations are available at compile time. */
namespace
{
    constexpr fgm::Mat2x3 MAT2x3(1, 2, 3, 4, 5, 6);
    constexpr fgm::Vec3 VEC3(5, 6, 7);
    constexpr fgm::Mat3x2 MAT3x2(5, 6, 7, 8, 9, 10);
    constexpr fgm::Mat3 MAT3x3(5, 6, 7, 8, 9, 10, 11, 12, 13);
    constexpr fgm::Mat3x4 MAT3x4(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);


    // 2x3 * 3x1 => 2x1
    constexpr auto EXP_VEC2 = MAT2x3 * VEC3;
    static_assert(EXP_VEC2.x() == 38);
    static_assert(EXP_VEC2.y() == 92);

    // 2x3 * 3x2 => 2x2
    constexpr auto EXP_MAT2 = MAT2x3 * MAT3x2;
    static_assert(EXP_MAT2[0] == fgm::Vec2{ 46, 109 });
    static_assert(EXP_MAT2[1] == fgm::Vec2{ 52, 124 });


    // 2x3 * 3x3 => 2x3
    constexpr auto EXP_MAT2x3 = MAT2x3 * MAT3x3;
    static_assert(EXP_MAT2x3[0] == fgm::Vec2{ 54, 126 });
    static_assert(EXP_MAT2x3[1] == fgm::Vec2{ 60, 141 });
    static_assert(EXP_MAT2x3[2] == fgm::Vec2{ 66, 156 });

    constexpr auto EXP_MAT2x4 = MAT2x3 * MAT3x4;
    static_assert(EXP_MAT2x4[0] == fgm::Vec2{ 62, 143 });
    static_assert(EXP_MAT2x4[1] == fgm::Vec2{ 68, 158 });
    static_assert(EXP_MAT2x4[2] == fgm::Vec2{ 74, 173 });
    static_assert(EXP_MAT2x4[3] == fgm::Vec2{ 80, 188 });


    // Verify matrix * vector multiplication
    // constexpr fgm::Vec2 COL_VECTOR_PRODUCT = MAT1 * VEC;
    // static_assert(COL_VECTOR_PRODUCT[0] == 5);
    // static_assert(COL_VECTOR_PRODUCT[1] == 11);
    //
    // // Verify vector * matrix multiplication
    // constexpr fgm::Vec2 ROW_VEC_PRODUCT = VEC * MAT1;
    // static_assert(ROW_VEC_PRODUCT[0] == 7);
    // static_assert(ROW_VEC_PRODUCT[1] == 10);
    //
    // // Verify matrix * matrix multiplication
    // constexpr fgm::Mat2x3 MAT_PRODUCT = MAT1 * MAT2;
    // static_assert(MAT_PRODUCT(0, 0) == 19);
    // static_assert(MAT_PRODUCT(0, 1) == 22);
    // static_assert(MAT_PRODUCT(1, 0) == 43);
    // static_assert(MAT_PRODUCT(1, 1) == 50);
} // namespace


/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/


/**************************************
 *                                    *
 *    VECTOR MULTIPLICATION TESTS     *
 *                                    *
 **************************************/

/**
 * @brief Verify that the multiplication between a Mat2x3 and 3D column vector returns a 2D column vector.
 */
TYPED_TEST(Mat2x3Multiplication, Times3DVector_ReturnsA2DVector)
{
    const auto expectedVector = this->_mat * this->_vec3x1;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec2x1, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec2x1, expectedVector);
    }
}


/**
 * @brief Verify that the multiplication between a Mat2x3 and Mat3x2 returns a 2D Matrix.
 */
TYPED_TEST(Mat2x3Multiplication, TimesMat3x2_ReturnsA2DMatrix)
{
    const auto matrixProduct = this->_mat * this->_mat3x2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2, matrixProduct);
    }
}


/**
 * @brief Verify that the multiplication between a Mat2x3 and Mat3 returns a 2x3 Matrix.
 */
TYPED_TEST(Mat2x3Multiplication, TimesMat3x3_ReturnsA2x3Matrix)
{
    const auto matrixProduct = this->_mat * this->_mat3x3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2x3, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2x3, matrixProduct);
    }
}


/**
 * @brief Verify that the multiplication between a Mat2x3 and Mat3x4 returns a 2x4 Matrix.
 */
TYPED_TEST(Mat2x3Multiplication, TimesMat3x4_ReturnsA2x4Matrix)
{
    const auto matrixProduct = this->_mat * this->_mat3x4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2x4, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2x4, matrixProduct);
    }
}


// /**
//  * @brief Verify that the binary vector multiplication operation with fractional values perform linear transformation
//  *        and returns a new column vector.
//  */
// TYPED_TEST(Mat2x3VectorFractionalMultiplication, MatrixTimesVectorReturnsATransformedVectorWithPrecision)
// {
//     const auto transformedVector = this->_mat * this->_vec;
//     EXPECT_VEC_EQ(this->_expectedColVector, transformedVector);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation(mat * Vec) with identity matrix
//  *        and returns the original column vector.
//  */
// TEST(Mat2x3VectorMultiplication, IdentityMatrixTimesVectorReturnsOriginalVector)
// {
//     const fgm::Mat2x3<float> iMatrix = fgm::Mat2x3<float>::EYE();
//     const fgm::Vec2F vec(2.0f, 1.0f);
//
//     const fgm::Vec2F transformedVector = iMatrix * vec;
//
//     EXPECT_VEC_EQ(vec, transformedVector);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation perform automatic type promotion
//  *        to the wider numeric type.
//  */
// TEST(Mat2x3VectorMultiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
// {
//     const fgm::Mat2x3 mat(1.0, 2.0);
//     const fgm::Vec2I vec(2, 1);
//
//     [[maybe_unused]] const auto transformedVector = mat * vec;
//     static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation perform linear transformation
//  *        and returns a new row vector.
//  */
// TYPED_TEST(Mat2x3VectorMultiplication, VectorTimesMatrixReturnsATransformedVector)
// {
//     const auto transformedVector = this->_vec * this->_mat;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_VEC_EQ(this->_expectedFloatingRowVector, transformedVector);
//     }
//     else
//     {
//         EXPECT_VEC_EQ(this->_expectedIntegralRowVector, transformedVector);
//     }
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation with fractional values perform linear transformation
//  *        and returns a new row vector.
//  */
// TYPED_TEST(Mat2x3VectorFractionalMultiplication, VectorTimesMatrixReturnsATransformedVectorWithPrecision)
// {
//     const auto transformedVector = this->_vec * this->_mat;
//     EXPECT_VEC_EQ(this->_expectedRowVector, transformedVector);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation with identity matrix
//  *        and returns the original row vector.
//  */
// TEST(Mat2x3VectorMultiplication, VectorTimesIdentityMatrixReturnsOriginalVector)
// {
//     const fgm::Mat2x3<float> iMatrix = fgm::Mat2x3<float>::EYE();
//     const fgm::Vec2F vec(2.0f, 1.0f);
//
//     const fgm::Vec2F transformedVector = vec * iMatrix;
//
//     EXPECT_VEC_EQ(vec, transformedVector);
// }
//
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation perform automatic type promotion
//  *        to the wider numeric type.
//  */
// TEST(Mat2x3VectorMultiplication, VecTimesMat_MixedTypeScalarMultiplicationPromotesType)
// {
//     const fgm::Mat2x3 mat(1.0, 2.0);
//     const fgm::Vec2I vec(2, 1);
//
//     [[maybe_unused]] const auto transformedVector = vec * mat;
//     static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
// }
//
//
// /**
//  * @brief Verify that the compound vector multiplication operation perform linear transformation
//  *        and mutates the vector in-place.
//  */
// TYPED_TEST(Mat2x3VectorMultiplication, VectorTimesEqualMatrixReturnsATransformedVector)
// {
//     auto transformedVector = this->_vec;
//     transformedVector *= this->_mat;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_VEC_EQ(this->_expectedFloatingRowVector, transformedVector);
//     }
//     else
//     {
//         EXPECT_VEC_EQ(this->_expectedIntegralRowVector, transformedVector);
//     }
// }
//
//
// /**
//  * @brief Verify that the compound vector multiplication operation with identity matrix
//  *        does not mutate the row vector components.
//  */
// TEST(Mat2x3VectorMultiplication, VectorTimesEqualIdentityMatrixReturnsOriginalVector)
// {
//     const auto iMatrix = fgm::Mat2x3<float>::EYE();
//     fgm::Vec2F vec(2.0f, 1.0f);
//
//     vec *= iMatrix;
//
//     EXPECT_VEC_CONTAINS(vec, 2.0f, 1.0f);
// }
//
//
// /**
//  * @brief Verify that the compound vector multiplication operation maintains the destination type and
//  *        perform an implicit cast.
//  */
// TEST(Mat2x3VectorMultiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
// {
//     const fgm::Mat2x3<double> iMatrix = fgm::Mat2x3<double>::EYE();
//     [[maybe_unused]] fgm::Vec2I vec(2, 1);
//
//     (void) (vec *= iMatrix);
//     static_assert(std::is_same_v<decltype(vec)::value_type, int>);
// }
//
//
// /**
//  * @brief Verify that the compound multiplication operator (vector) for mixed type
//  *        ensure minimal precision loss.
//  */
// TEST(Mat2x3VectorMultiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
// {
//     const fgm::Mat2x3 mat(2.5, 3.5, 0.5, 1.5);
//     fgm::Vec2 vec(10, 20);
//     const fgm::Vec2 expected(35, 65);
//
//     vec *= mat;
//
//     EXPECT_VEC_EQ(expected, vec);
// }
//
//
//
// /**************************************
//  *                                    *
//  *    MATRIX MULTIPLICATION TESTS     *
//  *                                    *
//  **************************************/
//
// /** @brief Verify that the binary vector multiplication operation return matrix product. */
// TYPED_TEST(Mat2x3Multiplication, MatrixTimesMatrixReturnsAMatrixProduct)
// {
//     const auto transformedVector = this->_matA * this->_matB;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector);
//     }
//     else
//     {
//         EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
//     }
// }
//
//
// /** @brief Verify that the binary vector multiplication operation return matrix product for denormals. */
// TYPED_TEST(Mat2x3FractionalMultiplication, MatrixTimesMatrixReturnsMatrixWithPrecision)
// {
//     const auto transformedVector = this->_matA * this->_matB;
//     EXPECT_MAT_EQ(this->_expectedMat, transformedVector);
// }
//
//
// /**
//  * @brief Verify that binary matrix multiplication with identity matrix
//  *        returns original matrix.
//  */
// TEST(Mat2x3Multiplication, MultipliedByIdentityMatrixReturnsOriginalMatrix)
// {
//     const fgm::Mat2x3<float> iMatrix = fgm::Mat2x3<float>::EYE();
//     const fgm::Mat2x3 mat(1.0f, 2.0f, 3.0f, 4.0f);
//
//     const fgm::Mat2x3 matrixProduct = iMatrix * mat;
//
//     EXPECT_MAT_EQ(mat, matrixProduct);
// }
//
//
// /**
//  * @brief Verify that the binary matrix multiplication operation perform automatic type promotion
//  *        to the wider numeric type.
//  */
// TEST(Mat2x3Multiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
// {
//     const fgm::Mat2x3 matA(1.0, 2.0);
//     const fgm::Mat2x3 matB(2, 1);
//
//     [[maybe_unused]] const auto transformedVector = matA * matB;
//     static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
// }
//
//
// /** @brief Verify that the compound vector multiplication operation perform an in-place matrix multiplication. */
// TYPED_TEST(Mat2x3Multiplication, CompoundMultiplicationOperationPerformInPlaceMatrixMultiplication)
// {
//     auto transformedVector = this->_matA;
//     transformedVector *= this->_matB;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector);
//     }
//     else
//     {
//         EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
//     }
// }
//
//
// /**
//  * @brief Verify that components matrix multiplication with identity matrix
//  *        does not mutate the calling matrix.
//  */
// TEST(Mat2x3Multiplication, TimesEqualIdentityMatrixReturnsOriginalMatrix)
// {
//     const fgm::Mat2x3<float> iMatrix = fgm::Mat2x3<float>::EYE();
//     fgm::Mat2x3 mat(1.0f, 2.0f, 3.0f, 4.0f);
//
//     mat *= iMatrix;
//     EXPECT_MAT_CONTAINS(std::vector{ 1.0f, 2.0f, 3.0f, 4.0f }, mat);
// }
//
//
// /**
//  * @brief Verify that the compound matrix multiplication operation maintains the destination type and
//  *        perform an implicit cast.
//  */
// TEST(Mat2x3Multiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
// {
//     const fgm::Mat2x3<double> iMatrix = fgm::Mat2x3<double>::EYE();
//     fgm::Mat2x3 mat(1, 2, 3, 4);
//
//     mat *= iMatrix;
//     static_assert(std::is_same_v<decltype(mat)::value_type, int>);
// }
//
//
// /**
//  * @brief Verify that the compound multiplication operator (matrix) for mixed type
//  *        ensure minimal precision loss.
//  */
// TEST(Mat2x3Multiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
// {
//     const fgm::Mat2x3 matA(2.5, 3.5, 0.5, 1.5);
//     fgm::Mat2x3 matB(5, 10, 15, 20);
//     const fgm::Mat2x3 expectedMatrix(17, 32, 47, 82);
//
//     matB *= matA;
//
//     EXPECT_MAT_EQ(expectedMatrix, matB);
// }
