/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 25, 2026
 *
 * @brief Verify @ref fgm::Matrix3D multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix3DScalarMultiplication: public ::testing::Test
{
protected:
    fgm::Matrix3D<T> _mat;
    T _scalar;
    fgm::Matrix3D<T> _expectedFloatingMat;
    fgm::Matrix3D<T> _expectedIntegralMat;



    void SetUp() override
    {
        _mat = { fgm::Vector3D{ T(7), T(13), T(3) }, fgm::Vector3D{ T(5), T(4), T(7) },
                 fgm::Vector3D{ T(5.5), T(11.25), T(25.3) } };
        _scalar = T(2.123456789123456);
        _expectedFloatingMat = { fgm::Vector3D{ T(14.864197523864192), T(27.604938258604928), T(6.370370367370368) },
                                 fgm::Vector3D{ T(10.61728394561728), T(8.493827156493824), T(14.864197523864192) },
                                 fgm::Vector3D{ T(11.679012340179007), T(23.88888887763888), T(53.72345676482344) } };
        _expectedIntegralMat = { fgm::Vector3D{ T(14), T(26), T(6) }, fgm::Vector3D{ T(10), T(8), T(14) },
                                 fgm::Vector3D{ T(10), T(22), T(50) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix3D scalar multiplication, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix3DScalarMultiplication, SupportedArithmeticTypes);


template <typename T>
class Matrix3DVectorMultiplication: public ::testing::Test
{
protected:
    fgm::Matrix3D<T> _mat;
    fgm::Vector3D<T> _vec;
    fgm::Vector3D<T> _expectedFloatingColVector, _expectedIntegralColVector, _expectedFloatingRowVector,
        _expectedIntegralRowVector;

    void SetUp() override
    {
        _mat = { fgm::Vector3D{ T(7.12345678912345), T(13.12345678912345), T(1.32893912338) },
                 fgm::Vector3D{ T(5.12345678912345), T(4.12345678912345), T(3.3129381239321) },
                 fgm::Vector3D{ T(2.238929123125), T(11.238924194839), T(9.2389291239898) } };
        _vec = { T(2.123456789123456), T(3.123456832912), T(1.2318492394128) };
        _expectedFloatingColVector = { T(33.88727193442948), T(54.59119292006805), T(24.550731838459015) };
        _expectedIntegralColVector = { T(31), T(49), T(20) };
        _expectedFloatingRowVector = { T(57.753956108666344), T(27.839918694037294), T(51.239531632191486) };
        _expectedIntegralRowVector = { T(54), T(25), T(46) };
    }
};
/** @brief Test fixture for @ref fgm::Matrix3D vector multiplication, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix3DVectorMultiplication, SupportedArithmeticTypes);


template <typename T>
class Matrix3DVectorFractionalMultiplication: public ::testing::Test
{
protected:
    fgm::Matrix3D<T> _mat;
    fgm::Vector3D<T> _vec, _expectedColVector, _expectedRowVector;

    void SetUp() override
    {
        _mat = {
            fgm::Vector3D{ T(0.1234568989329), T(0.1234214891234), T(0.12348923829) },
            fgm::Vector3D{ T(-0.123489823149), T(-0.123489757623), T(0.89281239432) },
            fgm::Vector3D{ T(-0.38291023892), T(0.29381938232), T(-0.0038291382) },
        };
        _vec = fgm::Vector3D{ T(0.8923764912287), T(0.78352829112384), T(0.234891238341) };

        _expectedColVector = fgm::Vector3D{ T(-0.07652999600877063), T(0.08239631520624698), T(0.8088432317718919) };
        _expectedRowVector = fgm::Vector3D{ T(0.2358808028522597), T(0.0027566750622143033), T(-0.11238372794829783) };
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix3D vector multiplication with small fractions,
 *        parameterized by @ref SupportedFloatingPointTypes.
 */
TYPED_TEST_SUITE(Matrix3DVectorFractionalMultiplication, SupportedFloatingPointTypes);


// template <typename T>
// class Matrix3DMultiplication: public ::testing::Test
//{
// protected:
//     fgm::Matrix3D<T> _matA, _matB, _expectedFloatingMat, _expectedIntegralMat;
//
//     void SetUp() override
//     {
//         _matA = { fgm::Vector3D{ T(7.12345678912345), T(13.12345678912345) },
//                   fgm::Vector3D{ T(5.12345678912345), T(4.12345678912345) } };
//         _matB = { fgm::Vector3D{ T(3.12345678912345), T(10.12345678912345) },
//                   fgm::Vector3D{ T(8.12345678912345), T(3.12345678912345) } };
//
//         _expectedFloatingMat = { fgm::Vector3D{ T(74.11690288564759), T(82.73418683126485) },
//                                  fgm::Vector3D{ T(73.8699893074007), T(119.48727325301795) } };
//         _expectedIntegralMat = { fgm::Vector3D{ T(71), T(79) }, fgm::Vector3D{ T(71), T(116) } };
//     }
// };
///** @brief Test fixture for @ref fgm::Matrix3D matrix multiplication, parameterized by @ref SupportedArithmeticTypes.
///*/
// TYPED_TEST_SUITE(Matrix3DMultiplication, SupportedArithmeticTypes);


// template <typename T>
// class Matrix3DFractionalMultiplication: public ::testing::Test
//{
// protected:
//     fgm::Matrix3D<T> _matA, _matB, _expectedMat;
//
//     void SetUp() override
//     {
//         _matA = { fgm::Vector3D{ T(0.1234568989329), T(0.1234214891234) },
//                   fgm::Vector3D{ T(-0.123489823149), T(-0.123489757623) } };
//         _matB = { fgm::Vector3D{ T(0.8923764912287), T(0.78352829112384) },
//                   fgm::Vector3D{ T(0.0123412348958), T(-0.0231423489589) } };
//
//         _expectedMat = { fgm::Vector3D{ T(0.013412264184596345), T(0.013380716644514457) },
//                          fgm::Vector3D{ T(0.004381455169424965), T(0.004381016652222751) } };
//     }
// };
///** @brief Test fixture for @ref fgm::Matrix3D matrix multiplication with fractional values(<1), parameterized by @ref
// * SupportedFloatingPointTypes. */
// TYPED_TEST_SUITE(Matrix3DFractionalMultiplication, SupportedFloatingPointTypes);
//


/**
 * @addtogroup T_FGM_Mat3x3_Multiplication
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that matrix multiplication operations are available at compile time. */
namespace
{
    constexpr fgm::Matrix3D MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    constexpr fgm::Matrix3D MAT2(5, 6, 7, 8, 10, 11, 12, 13, 14);
    constexpr fgm::Vector3D VEC(1, 2, 3);

    // Verify matrix * scalar multiplication
    constexpr fgm::Matrix3D BINARY_PRODUCT_1 = MAT1 * 2;
    static_assert(BINARY_PRODUCT_1(0, 0) == 2);
    static_assert(BINARY_PRODUCT_1(0, 1) == 4);
    static_assert(BINARY_PRODUCT_1(0, 2) == 6);
    static_assert(BINARY_PRODUCT_1(1, 0) == 8);
    static_assert(BINARY_PRODUCT_1(1, 1) == 10);
    static_assert(BINARY_PRODUCT_1(1, 2) == 12);
    static_assert(BINARY_PRODUCT_1(2, 0) == 14);
    static_assert(BINARY_PRODUCT_1(2, 1) == 16);
    static_assert(BINARY_PRODUCT_1(2, 2) == 18);


    // Verify scalar * matrix multiplication
    constexpr fgm::Matrix3D BINARY_PRODUCT_2 = 2 * MAT1;
    static_assert(BINARY_PRODUCT_2(0, 0) == 2);
    static_assert(BINARY_PRODUCT_2(0, 1) == 4);
    static_assert(BINARY_PRODUCT_2(0, 2) == 6);
    static_assert(BINARY_PRODUCT_2(1, 0) == 8);
    static_assert(BINARY_PRODUCT_2(1, 1) == 10);
    static_assert(BINARY_PRODUCT_2(1, 2) == 12);
    static_assert(BINARY_PRODUCT_2(2, 0) == 14);
    static_assert(BINARY_PRODUCT_2(2, 1) == 16);
    static_assert(BINARY_PRODUCT_2(2, 2) == 18);

    // Verify matrix * vector multiplication
    constexpr fgm::Vector3D COL_VECTOR_PRODUCT = MAT1 * VEC;
    static_assert(COL_VECTOR_PRODUCT[0] == 14);
    static_assert(COL_VECTOR_PRODUCT[1] == 32);
    static_assert(COL_VECTOR_PRODUCT[2] == 50);

    // Verify vector * matrix multiplication
    constexpr fgm::Vector3D ROW_VEC_PRODUCT = VEC * MAT1;
    static_assert(ROW_VEC_PRODUCT[0] == 30);
    static_assert(ROW_VEC_PRODUCT[1] == 36);
    static_assert(ROW_VEC_PRODUCT[2] == 42);

    //// Verify matrix * matrix multiplication
    // constexpr fgm::Matrix3D MAT_PRODUCT = MAT1 * MAT2;
    // static_assert(MAT_PRODUCT(0, 0) == 2);
    // static_assert(MAT_PRODUCT(0, 1) == 4);
    // static_assert(MAT_PRODUCT(0, 2) == 6);
    // static_assert(MAT_PRODUCT(1, 0) == 8);
    // static_assert(MAT_PRODUCT(1, 1) == 10);
    // static_assert(MAT_PRODUCT(1, 2) == 12);
    // static_assert(MAT_PRODUCT(2, 0) == 14);
    // static_assert(MAT_PRODUCT(2, 1) == 16);
    // static_assert(MAT_PRODUCT(2, 2) == 18);
} // namespace



/**************************************
 *                                    *
 *     SCALAR MULTIPLICATION TESTS    *
 *                                    *
 **************************************/

/** @brief Verify that scalar multiplication by zero returns a zero matrix. */
TEST(Matrix3DScalarMultiplication, MultiplicationByZeroReturnsZeroMatrix)
{
    constexpr fgm::Matrix3D mat{ 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f };

    constexpr fgm::Matrix3D product = mat * 0;

    EXPECT_MAT_ZERO(product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Matrix3DScalarMultiplication, MultiplicationByOneReturnsOriginalMatrix)
{
    constexpr fgm::Matrix3D mat{ 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f };

    constexpr fgm::Matrix3D product = mat * 1;

    EXPECT_MAT_EQ(mat, product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Matrix3DScalarMultiplication, MultiplicationByNegativeScalarFlipsSigns)
{
    constexpr fgm::Matrix3D mat = { 1.0f, -2.0f, 3.0f, -4.0f, 5.0f, 6.0f, 7.0f, 8.0f, -9.0f };
    constexpr fgm::Matrix3D expected = { -2.0f, 4.0f, -6.0f, 8.0f, -10.0f, -12.0f, -14.0f, -16.0f, 18.0f };
    constexpr float scalar = -2.0f;

    constexpr fgm::Matrix3D product = mat * scalar;

    EXPECT_MAT_EQ(expected, product);
}


/**
 * @brief Verify that the binary multiplication operator (matrix * scalar) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix3DScalarMultiplication, MatrixTimesScalarReturnsScaledMatrix)
{
    const fgm::Matrix3D product = this->_mat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
}


/**
 * @brief Verify that the binary multiplication operator (scalar * matrix) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix3DScalarMultiplication, ScalarTimesAMatrixReturnsScaledMatrix)
{
    const fgm::Matrix3D product = this->_scalar * this->_mat;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
}


/**
 * @brief Verify that the compound multiplication assignment operator (scalar) performs an element-wise product
 *        and mutates the matrix in-place.
 */
TYPED_TEST(Matrix3DScalarMultiplication, MatrixTimesEqualScalarIsTheSameMatrixScaled)
{
    this->_mat *= this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, this->_mat);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, this->_mat);
}


/**
 * @brief Verify that the binary multiplication operator (scalar) perform automatic type promotion
 *        to the wider numeric type.
 */
TYPED_TEST(Matrix3DScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    constexpr double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Matrix3D product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}


/**
 * @brief Verify that the compound multiplication assignment operator (scalar) maintains the destination type and
 *        perform an implicit cast.
 */
TEST(Matrix3DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Matrix3D mat = { 1.0f, -2.0f, 3.0f, -4.0f, 5.0f, 6.0f, 7.0f, 8.0f, -9.0f };
    constexpr double scalar = 5.0;
    mat *= scalar;

    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


/**
 * @brief Verify that the compound multiplication operator (scalar) for mixed type
 *        ensure minimal precision loss.
 */
TEST(Matrix3DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    fgm::Matrix3D mat = { 1, -2, 3, -4, 5, 6, 7, 8, -9 };
    constexpr double scalar = 2.5;
    constexpr fgm::Matrix3D expected{ 2, -5, 7, -10, 12, 15, 17, 20, -22 };

    mat *= scalar;

    EXPECT_MAT_EQ(expected, mat);
}



/**************************************
 *                                    *
 *    VECTOR MULTIPLICATION TESTS     *
 *                                    *
 **************************************/

/**
 * @brief Verify that the binary vector multiplication operation perform linear transformation
 *        and returns a new column vector.
 */
TYPED_TEST(Matrix3DVectorMultiplication, MatrixTimesVectorReturnsATransformedVector)
{
    const auto transformedVector = this->_mat * this->_vec;
    if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_VEC_EQ(this->_expectedFloatingColVector, transformedVector);
    else
        EXPECT_VEC_EQ(this->_expectedIntegralColVector, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation with fractional values perform linear transformation
 *        and returns a new column vector.
 */
TYPED_TEST(Matrix3DVectorFractionalMultiplication, MatrixTimesVectorReturnsATransformedVectorWithPrecision)
{
    const auto transformedVector = this->_mat * this->_vec;
    EXPECT_VEC_EQ(this->_expectedColVector, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation(mat * vec) with identity matrix
 *        and returns the original column vector.
 */
TEST(Matrix3DVectorMultiplication, IdentityMatrixTimesVectorReturnsOriginalVector)
{
    constexpr fgm::Matrix3D<float> iMatrix;
    constexpr fgm::vec3 vec{ 2.0f, 1.0f, 2.5 };

    constexpr fgm::vec3 transformedVector = iMatrix * vec;

    EXPECT_VEC_EQ(vec, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation perform automatic type promotion
 *        to the wider numeric type.
 */
TEST(Matrix3DVectorMultiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
{
    constexpr fgm::Matrix3D mat{ 1.0, 2.0, 3.0 };
    constexpr fgm::iVec3 vec{ 2, 1, 3 };

    [[maybe_unused]] constexpr auto transformedVector = mat * vec;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


/**
 * @brief Verify that the binary vector multiplication operation perform linear transformation
 *        and returns a new row vector.
 */
TYPED_TEST(Matrix3DVectorMultiplication, VectorTimesMatrixReturnsATransformedVector)
{
    const auto transformedVector = this->_vec * this->_mat;
    if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_VEC_EQ(this->_expectedFloatingRowVector, transformedVector);
    else
        EXPECT_VEC_EQ(this->_expectedIntegralRowVector, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation with fractional values perform linear transformation
 *        and returns a new row vector.
 */
TYPED_TEST(Matrix3DVectorFractionalMultiplication, VectorTimesMatrixReturnsATransformedVectorWithPrecision)
{
    const auto transformedVector = this->_vec * this->_mat;
    EXPECT_VEC_EQ(this->_expectedRowVector, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation with identity matrix
 *        and returns the original row vector.
 */
TEST(Matrix3DVectorMultiplication, VectorTimesIdentityMatrixReturnsOriginalVector)
{
    constexpr fgm::Matrix3D<float> iMatrix;
    constexpr fgm::vec3 vec{ 2.0f, 1.0f, 3.0f };

    constexpr fgm::vec3 transformedVector = vec * iMatrix;

    EXPECT_VEC_EQ(vec, transformedVector);
}



/**
 * @brief Verify that the binary vector multiplication operation perform automatic type promotion
 *        to the wider numeric type.
 */
TEST(Matrix3DVectorMultiplication, VecTimesMat_MixedTypeScalarMultiplicationPromotesType)
{
    constexpr fgm::Matrix3D mat{ 1.0, 2.0, 3.0 };
    constexpr fgm::iVec3 vec{ 2, 1, 3 };

    [[maybe_unused]] constexpr auto transformedVector = vec * mat;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


/**
 * @brief Verify that the compound vector multiplication operation perform linear transformation
 *        and mutates the vector in-place.
 */
TYPED_TEST(Matrix3DVectorMultiplication, VectorTimesEqualMatrixReturnsATransformedVector)
{
    auto transformedVector = this->_vec;
    transformedVector *= this->_mat;
    if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_VEC_EQ(this->_expectedFloatingRowVector, transformedVector);
    else
        EXPECT_VEC_EQ(this->_expectedIntegralRowVector, transformedVector);
}


/**
 * @brief Verify that the compound vector multiplication operation with identity matrix
 *        does not mutate the row vector components.
 */
TEST(Matrix3DVectorMultiplication, VectorTimesEqualIdentityMatrixReturnsOriginalVector)
{
    constexpr fgm::Matrix3D<float> iMatrix;
    fgm::vec3 vec{ 2.0f, 1.0f, 3.0f };

    vec *= iMatrix;

    EXPECT_VEC_CONTAINS(vec, 2.0f, 1.0f, 3.0f);
}


/**
 * @brief Verify that the compound vector multiplication operation maintains the destination type and
 *        perform an implicit cast.
 */
TEST(Matrix3DVectorMultiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
{
    constexpr fgm::Matrix3D<double> iMatrix;
    [[maybe_unused]] fgm::iVec3 vec{ 2, 1, 5 };

    (void) (vec *= iMatrix);
    static_assert(std::is_same_v<decltype(vec)::value_type, int>);
}


/**
 * @brief Verify that the compound multiplication operator (vector) for mixed type
 *        ensure minimal precision loss.
 */
TEST(Matrix3DVectorMultiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    constexpr fgm::Matrix3D mat{ 2.5, 3.5, 0.5, 1.5, 12.0, 3.25, 5.0, 11.5, 5.0 };
    fgm::Vector3D vec{ 10, 20, 30 };
    constexpr fgm::Vector3D expected{ 205, 620, 220 };

    vec *= mat;

    EXPECT_VEC_EQ(expected, vec);
}



/**************************************
 *                                    *
 *    MATRIX MULTIPLICATION TESTS     *
 *                                    *
 **************************************/
//
///** @brief Verify that the binary vector multiplication operation return matrix product. */
// TYPED_TEST(Matrix3DMultiplication, MatrixTimesMatrixReturnsAMatrixProduct)
//{
//     const auto transformedVector = this->_matA * this->_matB;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//         EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector);
//     else
//         EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
// }
//
//
///** @brief Verify that the binary vector multiplication operation return matrix product for denormals. */
// TYPED_TEST(Matrix3DFractionalMultiplication, MatrixTimesMatrixReturnsMatrixWithPrecision)
//{
//     const auto transformedVector = this->_matA * this->_matB;
//     EXPECT_MAT_EQ(this->_expectedMat, transformedVector);
// }
//
//
///**
// * @brief Verify that binary matrix multiplication with identity matrix
// *        returns original matrix.
// */
// TEST(Matrix3DMultiplication, MultipliedByIdentityMatrixReturnsOriginalMatrix)
//{
//    constexpr fgm::Matrix3D<float> iMatrix;
//    constexpr fgm::Matrix3D mat(1.0f, 2.0f, 3.0f, 4.0f);
//
//    constexpr fgm::Matrix3D matrixProduct = iMatrix * mat;
//
//    EXPECT_MAT_EQ(mat, matrixProduct);
//}
//
//
///**
// * @brief Verify that the binary matrix multiplication operation perform automatic type promotion
// *        to the wider numeric type.
// */
// TEST(Matrix3DMultiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
//{
//    constexpr fgm::Matrix3D matA(1.0, 2.0);
//    constexpr fgm::Matrix3D matB(2, 1);
//
//    [[maybe_unused]] constexpr auto transformedVector = matA * matB;
//    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
//}
//
//
///** @brief Verify that the compound vector multiplication operation perform an in-place matrix multiplication. */
// TYPED_TEST(Matrix3DMultiplication, CompoundMultiplicationOperationPerformInPlaceMatrixMultiplication)
//{
//     auto transformedVector = this->_matA;
//     transformedVector *= this->_matB;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//         EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector);
//     else
//         EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
// }
//
//
///**
// * @brief Verify that components matrix multiplication with identity matrix
// *        does not mutate the calling matrix.
// */
// TEST(Matrix3DMultiplication, TimesEqualIdentityMatrixReturnsOriginalMatrix)
//{
//    constexpr fgm::Matrix3D<float> iMatrix;
//    fgm::Matrix3D mat(1.0f, 2.0f, 3.0f, 4.0f);
//
//    mat *= iMatrix;
//    EXPECT_MAT_CONTAINS(std::vector{ 1.0f, 2.0f, 3.0f, 4.0f }, mat);
//}
//
//
///**
// * @brief Verify that the compound matrix multiplication operation maintains the destination type and
// *        perform an implicit cast.
// */
// TEST(Matrix3DMultiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
//{
//    constexpr fgm::Matrix3D<double> iMatrix;
//    fgm::Matrix3D mat(1, 2, 3, 4);
//
//    mat *= iMatrix;
//    static_assert(std::is_same_v<decltype(mat)::value_type, int>);
//}
//
//
///**
// * @brief Verify that the compound multiplication operator (matrix) for mixed type
// *        ensure minimal precision loss.
// */
// TEST(Matrix3DMultiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
//{
//    constexpr fgm::Matrix3D matA(2.5, 3.5, 0.5, 1.5);
//    fgm::Matrix3D matB(5, 10, 15, 20);
//    constexpr fgm::Matrix3D expectedMatrix(17, 32, 47, 82);
//
//    matB *= matA;
//
//    EXPECT_MAT_EQ(expectedMatrix, matB);
//}


/** @} */