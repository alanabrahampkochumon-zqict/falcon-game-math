/**
 * @file Matrix2x3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref fgm::Matrix2x3 vector and matrix multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



//
// template <typename T>
// class Matrix2x3VectorMultiplication: public ::testing::Test
// {
// protected:
//     fgm::Matrix2x3<T> _mat;
//     fgm::Vec2<T> _vec;
//     fgm::Vec2<T> _expectedFloatingColVector, _expectedIntegralColVector, _expectedFloatingRowVector,
//         _expectedIntegralRowVector;
//
//     void SetUp() override
//     {
//         _mat                       = { fgm::Vec2{ T(7.12345678912345), T(13.12345678912345) },
//                                        fgm::Vec2{ T(5.12345678912345), T(4.12345678912345) } };
//         _vec                       = { T(2.123456789123456), T(3.123456832912) };
//         _expectedFloatingColVector = { T(31.129248797008778), T(40.74653269883751) };
//         _expectedIntegralColVector = { T(29), T(38) };
//         _expectedFloatingRowVector = { T(56.116903460304776), T(23.75887838584987) };
//         _expectedIntegralRowVector = { T(53), T(22) };
//     }
// };
// /** @brief Test fixture for @ref fgm::Matrix2x3 vector multiplication, parameterized by @ref
// SupportedArithmeticTypes.
//  */
// TYPED_TEST_SUITE(Matrix2x3VectorMultiplication, SupportedArithmeticTypes);
//
//
// template <typename T>
// class Matrix2x3VectorFractionalMultiplication: public ::testing::Test
// {
// protected:
//     fgm::Matrix2x3<T> _mat;
//     fgm::Vec2<T> _vec, _expectedColVector, _expectedRowVector;
//
//     void SetUp() override
//     {
//         _mat = { fgm::Vec2{ T(0.1234568989329), T(0.1234214891234) },
//                  fgm::Vec2{ T(-0.123489823149), T(-0.123489757623) } };
//         _vec = fgm::Vec2{ T(0.8923764912287), T(0.78352829112384) };
//
//         _expectedColVector = fgm::Vec2{ T(0.013412264184596345), T(0.013380716644514457) };
//         _expectedRowVector = fgm::Vec2{ T(0.20687426274853477), T(-0.20695713384580372) };
//     }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix2x3 vector multiplication with small fractions,
//  *        parameterized by @ref SupportedFloatingPointTypes.
//  */
// TYPED_TEST_SUITE(Matrix2x3VectorFractionalMultiplication, SupportedFloatingPointTypes);
//
//
// template <typename T>
// class Matrix2x3Multiplication: public ::testing::Test
// {
// protected:
//     fgm::Matrix2x3<T> _matA, _matB, _expectedFloatingMat, _expectedIntegralMat;
//
//     void SetUp() override
//     {
//         _matA = { fgm::Vec2{ T(7.12345678912345), T(13.12345678912345) },
//                   fgm::Vec2{ T(5.12345678912345), T(4.12345678912345) } };
//         _matB = { fgm::Vec2{ T(3.12345678912345), T(10.12345678912345) },
//                   fgm::Vec2{ T(8.12345678912345), T(3.12345678912345) } };
//
//         _expectedFloatingMat = { fgm::Vec2{ T(74.11690288564759), T(82.73418683126485) },
//                                  fgm::Vec2{ T(73.8699893074007), T(119.48727325301795) } };
//         _expectedIntegralMat = { fgm::Vec2{ T(71), T(79) }, fgm::Vec2{ T(71), T(116) } };
//     }
// };
// /** @brief Test fixture for @ref fgm::Matrix2x3 matrix multiplication, parameterized by @ref
// SupportedArithmeticTypes.
//  */
// TYPED_TEST_SUITE(Matrix2x3Multiplication, SupportedArithmeticTypes);
//
//
// template <typename T>
// class Matrix2x3FractionalMultiplication: public ::testing::Test
// {
// protected:
//     fgm::Matrix2x3<T> _matA, _matB, _expectedMat;
//
//     void SetUp() override
//     {
//         _matA = { fgm::Vec2{ T(0.1234568989329), T(0.1234214891234) },
//                   fgm::Vec2{ T(-0.123489823149), T(-0.123489757623) } };
//         _matB = { fgm::Vec2{ T(0.8923764912287), T(0.78352829112384) },
//                   fgm::Vec2{ T(0.0123412348958), T(-0.0231423489589) } };
//
//         _expectedMat = { fgm::Vec2{ T(0.013412264184596345), T(0.013380716644514457) },
//                          fgm::Vec2{ T(0.004381455169424965), T(0.004381016652222751) } };
//     }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix2x3 matrix multiplication with fractional values(<1),
//  *        parameterized by @ref SupportedFloatingPointTypes.
//  */
// TYPED_TEST_SUITE(Matrix2x3FractionalMultiplication, SupportedFloatingPointTypes);


/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that matrix multiplication operations are available at compile time. */
namespace
{
    // constexpr fgm::Matrix2x3 MAT1(1, 2, 3, 4, 5, 6);
    // constexpr fgm::Matrix2x3 MAT2(5, 6, 7, 8, 9, 10);
    // constexpr fgm::Vec2 VEC(1, 2);


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
    // constexpr fgm::Matrix2x3 MAT_PRODUCT = MAT1 * MAT2;
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
 * @brief Verify that the binary vector multiplication operation perform linear transformation
 *        and returns a new column vector.
 */
// TYPED_TEST(Matrix2x3VectorMultiplication, MatrixTimesVectorReturnsATransformedVector)
// {
//     const auto transformedVector = this->_mat * this->_vec;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_VEC_EQ(this->_expectedFloatingColVector, transformedVector);
//     }
//     else
//     {
//         EXPECT_VEC_EQ(this->_expectedIntegralColVector, transformedVector);
//     }
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation with fractional values perform linear transformation
//  *        and returns a new column vector.
//  */
// TYPED_TEST(Matrix2x3VectorFractionalMultiplication, MatrixTimesVectorReturnsATransformedVectorWithPrecision)
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
// TEST(Matrix2x3VectorMultiplication, IdentityMatrixTimesVectorReturnsOriginalVector)
// {
//     const fgm::Matrix2x3<float> iMatrix = fgm::Matrix2x3<float>::EYE();
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
// TEST(Matrix2x3VectorMultiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
// {
//     const fgm::Matrix2x3 mat(1.0, 2.0);
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
// TYPED_TEST(Matrix2x3VectorMultiplication, VectorTimesMatrixReturnsATransformedVector)
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
// TYPED_TEST(Matrix2x3VectorFractionalMultiplication, VectorTimesMatrixReturnsATransformedVectorWithPrecision)
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
// TEST(Matrix2x3VectorMultiplication, VectorTimesIdentityMatrixReturnsOriginalVector)
// {
//     const fgm::Matrix2x3<float> iMatrix = fgm::Matrix2x3<float>::EYE();
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
// TEST(Matrix2x3VectorMultiplication, VecTimesMat_MixedTypeScalarMultiplicationPromotesType)
// {
//     const fgm::Matrix2x3 mat(1.0, 2.0);
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
// TYPED_TEST(Matrix2x3VectorMultiplication, VectorTimesEqualMatrixReturnsATransformedVector)
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
// TEST(Matrix2x3VectorMultiplication, VectorTimesEqualIdentityMatrixReturnsOriginalVector)
// {
//     const auto iMatrix = fgm::Matrix2x3<float>::EYE();
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
// TEST(Matrix2x3VectorMultiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
// {
//     const fgm::Matrix2x3<double> iMatrix = fgm::Matrix2x3<double>::EYE();
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
// TEST(Matrix2x3VectorMultiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
// {
//     const fgm::Matrix2x3 mat(2.5, 3.5, 0.5, 1.5);
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
// TYPED_TEST(Matrix2x3Multiplication, MatrixTimesMatrixReturnsAMatrixProduct)
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
// TYPED_TEST(Matrix2x3FractionalMultiplication, MatrixTimesMatrixReturnsMatrixWithPrecision)
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
// TEST(Matrix2x3Multiplication, MultipliedByIdentityMatrixReturnsOriginalMatrix)
// {
//     const fgm::Matrix2x3<float> iMatrix = fgm::Matrix2x3<float>::EYE();
//     const fgm::Matrix2x3 mat(1.0f, 2.0f, 3.0f, 4.0f);
//
//     const fgm::Matrix2x3 matrixProduct = iMatrix * mat;
//
//     EXPECT_MAT_EQ(mat, matrixProduct);
// }
//
//
// /**
//  * @brief Verify that the binary matrix multiplication operation perform automatic type promotion
//  *        to the wider numeric type.
//  */
// TEST(Matrix2x3Multiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
// {
//     const fgm::Matrix2x3 matA(1.0, 2.0);
//     const fgm::Matrix2x3 matB(2, 1);
//
//     [[maybe_unused]] const auto transformedVector = matA * matB;
//     static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
// }
//
//
// /** @brief Verify that the compound vector multiplication operation perform an in-place matrix multiplication. */
// TYPED_TEST(Matrix2x3Multiplication, CompoundMultiplicationOperationPerformInPlaceMatrixMultiplication)
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
// TEST(Matrix2x3Multiplication, TimesEqualIdentityMatrixReturnsOriginalMatrix)
// {
//     const fgm::Matrix2x3<float> iMatrix = fgm::Matrix2x3<float>::EYE();
//     fgm::Matrix2x3 mat(1.0f, 2.0f, 3.0f, 4.0f);
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
// TEST(Matrix2x3Multiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
// {
//     const fgm::Matrix2x3<double> iMatrix = fgm::Matrix2x3<double>::EYE();
//     fgm::Matrix2x3 mat(1, 2, 3, 4);
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
// TEST(Matrix2x3Multiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
// {
//     const fgm::Matrix2x3 matA(2.5, 3.5, 0.5, 1.5);
//     fgm::Matrix2x3 matB(5, 10, 15, 20);
//     const fgm::Matrix2x3 expectedMatrix(17, 32, 47, 82);
//
//     matB *= matA;
//
//     EXPECT_MAT_EQ(expectedMatrix, matB);
// }


