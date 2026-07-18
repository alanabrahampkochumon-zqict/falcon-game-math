/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 25, 2026
 *
 * @brief Verify @ref fgm::Mat3 multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"


template <typename T>
class Mat3ScalarMultiplication: public ::testing::Test
{
protected:
    fgm::Mat3<T> _mat;
    T _scalar;
    fgm::Mat3<T> _expectedFloatingMat;
    fgm::Mat3<T> _expectedIntegralMat;


    void SetUp() override
    {
        _mat                 = { fgm::Vec3{ T(7), T(13), T(3) }, fgm::Vec3{ T(5), T(4), T(7) },
                                 fgm::Vec3{ T(5.5), T(11.25), T(25.3) } };
        _scalar              = T(2.123456789123456);
        _expectedFloatingMat = { fgm::Vec3{ T(14.864197523864192), T(27.604938258604928), T(6.370370367370368) },
                                 fgm::Vec3{ T(10.61728394561728), T(8.493827156493824), T(14.864197523864192) },
                                 fgm::Vec3{ T(11.679012340179007), T(23.88888887763888), T(53.72345676482344) } };
        _expectedIntegralMat = { fgm::Vec3{ T(14), T(26), T(6) }, fgm::Vec3{ T(10), T(8), T(14) },
                                 fgm::Vec3{ T(10), T(22), T(50) } };
    }
};

/** @brief Test fixture for @ref fgm::Mat3 scalar multiplication, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Mat3ScalarMultiplication, SupportedArithmeticTypes);


template <typename T>
class Mat3VectorMultiplication: public ::testing::Test
{
protected:
    fgm::Mat3<T> _mat;
    fgm::Vec3<T> _vec;
    fgm::Vec3<T> _expectedFloatingColVector, _expectedIntegralColVector, _expectedFloatingRowVector,
        _expectedIntegralRowVector;

    void SetUp() override
    {
        _mat                       = { fgm::Vec3{ T(7.12345678912345), T(13.12345678912345), T(1.32893912338) },
                                       fgm::Vec3{ T(5.12345678912345), T(4.12345678912345), T(3.3129381239321) },
                                       fgm::Vec3{ T(2.238929123125), T(11.238924194839), T(9.2389291239898) } };
        _vec                       = { T(2.123456789123456), T(3.123456832912), T(1.2318492394128) };
        _expectedFloatingColVector = { T(33.88727193442948), T(54.59119292006805), T(24.550731838459015) };
        _expectedIntegralColVector = { T(31), T(49), T(20) };
        _expectedFloatingRowVector = { T(57.753956108666344), T(27.839918694037294), T(51.239531632191486) };
        _expectedIntegralRowVector = { T(54), T(25), T(46) };
    }
};

/** @brief Test fixture for @ref fgm::Mat3 vector multiplication, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Mat3VectorMultiplication, SupportedArithmeticTypes);


template <typename T>
class Mat3VectorFractionalMultiplication: public ::testing::Test
{
protected:
    fgm::Mat3<T> _mat;
    fgm::Vec3<T> _vec, _expectedColVector, _expectedRowVector;

    void SetUp() override
    {
        _mat = {
            fgm::Vec3{ T(0.1234568989329), T(0.1234214891234), T(0.12348923829) },
            fgm::Vec3{ T(-0.123489823149), T(-0.123489757623), T(0.89281239432) },
            fgm::Vec3{ T(-0.38291023892), T(0.29381938232), T(-0.0038291382) },
        };
        _vec = fgm::Vec3{ T(0.8923764912287), T(0.78352829112384), T(0.234891238341) };

        _expectedColVector = fgm::Vec3{ T(-0.07652999600877063), T(0.08239631520624698), T(0.8088432317718919) };
        _expectedRowVector = fgm::Vec3{ T(0.2358808028522597), T(0.0027566750622143033), T(-0.11238372794829783) };
    }
};

/**
 * @brief Test fixture for @ref fgm::Mat3 vector multiplication with small fractions,
 *        parameterized by @ref SupportedFloatingPointTypes.
 */
TYPED_TEST_SUITE(Mat3VectorFractionalMultiplication, SupportedFloatingPointTypes);


template <typename T>
class Mat3Multiplication: public ::testing::Test
{
protected:
    fgm::Mat3<T> _matA, _matB, _expectedFloatingMat, _expectedIntegralMat;

    void SetUp() override
    {
        _matA = { fgm::Vec3{ T(7.12345678912345), T(6.12345678912345), T(1.2389123488213) },
                  fgm::Vec3{ T(5.12345678912345), T(4.12345678912345), T(2.53283924821338) },
                  fgm::Vec3{ T(9.32189342348), T(8.238192312343), T(5.12398423821223) } };
        _matB = { fgm::Vec3{ T(3.12345678912345), T(5.12345678912345), T(1.213849123421) },
                  fgm::Vec3{ T(8.12345678912345), T(3.12345678912345), T(2.3218934118233) },
                  fgm::Vec3{ T(7.23912389492341), T(4.291238423419123), T(4.18234983241234) } };

        _expectedFloatingMat = { fgm::Vec3{ T(59.81499110074553), T(50.25262787869462), T(23.066325405048886) },
                                 fgm::Vec3{ T(95.51443223309786), T(81.75128018451636), T(29.872810121743093) },
                                 fgm::Vec3{ T(112.54098028826937), T(96.47820080937791), T(41.267951710315614) } };

        _expectedIntegralMat = { fgm::Vec3{ T(55), T(46), T(18) }, fgm::Vec3{ T(89), T(76), T(24) },
                                 fgm::Vec3{ T(105), T(90), T(35) } };
    }
};

/** @brief Test fixture for @ref fgm::Mat3 matrix multiplication, parameterized by @ref SupportedArithmeticTypes.
/*/
TYPED_TEST_SUITE(Mat3Multiplication, SupportedArithmeticTypes);


template <typename T>
class Mat3FractionalMultiplication: public ::testing::Test
{
protected:
    fgm::Mat3<T> _matA, _matB, _expectedMat;

    void SetUp() override
    {
        _matA = { fgm::Vec3{ T(0.1234568989329), T(0.1234214891234), T(0.382348912394) },
                  fgm::Vec3{ T(-0.123489823149), T(-0.123489757623), T(0.093218349323) },
                  fgm::Vec3{ T(0.0123489823149), T(0.53489757623), T(-0.93218349323) } };
        _matB = { fgm::Vec3{ T(0.8923764912287), T(0.78352829112384), T(0.0523812349234) },
                  fgm::Vec3{ T(0.0123412348958), T(-0.0231423489589), T(0.3829123948324) },
                  fgm::Vec3{ T(-0.539282348958), T(0.00033423489589), T(-0.8239123948324) } };

        _expectedMat = { fgm::Vec3{ T(0.014059119128298), T(0.041399312244975), T(0.365409472263106) },
                         fgm::Vec3{ T(0.009110033561366), T(0.209199928556498), T(-0.354383247645329) },
                         fgm::Vec3{ T(-0.076793880652601), T(-0.50730904817435), T(0.56187467155827) } };
    }
};

/**
 * @brief Test fixture for @ref fgm::Mat3 matrix multiplication with fractional values(<1),
 *        parameterized by @ref SupportedFloatingPointTypes.
 */
TYPED_TEST_SUITE(Mat3FractionalMultiplication, SupportedFloatingPointTypes);


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
    constexpr fgm::Mat3 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    constexpr fgm::Mat3 MAT2(5, 6, 7, 8, 10, 11, 12, 13, 14);
    constexpr fgm::Vec3 VEC(1, 2, 3);

    // Verify matrix * scalar multiplication
    constexpr fgm::Mat3 BINARY_PRODUCT_1 = MAT1 * 2;
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
    constexpr fgm::Mat3 BINARY_PRODUCT_2 = 2 * MAT1;
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
    constexpr fgm::Vec3 COL_VECTOR_PRODUCT = MAT1 * VEC;
    static_assert(COL_VECTOR_PRODUCT[0] == 14);
    static_assert(COL_VECTOR_PRODUCT[1] == 32);
    static_assert(COL_VECTOR_PRODUCT[2] == 50);

    // Verify vector * matrix multiplication
    constexpr fgm::Vec3 ROW_VEC_PRODUCT = VEC * MAT1;
    static_assert(ROW_VEC_PRODUCT[0] == 30);
    static_assert(ROW_VEC_PRODUCT[1] == 36);
    static_assert(ROW_VEC_PRODUCT[2] == 42);

    // Verify matrix * matrix multiplication
    constexpr fgm::Mat3 MAT_PRODUCT = MAT1 * MAT2;
    static_assert(MAT_PRODUCT(0, 0) == 57);
    static_assert(MAT_PRODUCT(0, 1) == 65);
    static_assert(MAT_PRODUCT(0, 2) == 71);
    static_assert(MAT_PRODUCT(1, 0) == 132);
    static_assert(MAT_PRODUCT(1, 1) == 152);
    static_assert(MAT_PRODUCT(1, 2) == 167);
    static_assert(MAT_PRODUCT(2, 0) == 207);
    static_assert(MAT_PRODUCT(2, 1) == 239);
    static_assert(MAT_PRODUCT(2, 2) == 263);
} // namespace


/**************************************
 *                                    *
 *     SCALAR MULTIPLICATION TESTS    *
 *                                    *
 **************************************/

/** @brief Verify that scalar multiplication by zero returns a zero matrix. */
TEST(Mat3ScalarMultiplication, MultiplicationByZeroReturnsZeroMatrix)
{
    const fgm::Mat3 mat{ 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f };

    const fgm::Mat3 product = mat * 0;

    EXPECT_MAT_ZERO(product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Mat3ScalarMultiplication, MultiplicationByOneReturnsOriginalMatrix)
{
    const fgm::Mat3 mat{ 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f };

    const fgm::Mat3 product = mat * 1;

    EXPECT_MAT_EQ(mat, product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Mat3ScalarMultiplication, MultiplicationByNegativeScalarFlipsSigns)
{
    const fgm::Mat3 mat      = { 1.0f, -2.0f, 3.0f, -4.0f, 5.0f, 6.0f, 7.0f, 8.0f, -9.0f };
    const fgm::Mat3 expected = { -2.0f, 4.0f, -6.0f, 8.0f, -10.0f, -12.0f, -14.0f, -16.0f, 18.0f };
    const float scalar          = -2.0f;

    const fgm::Mat3 product = mat * scalar;

    EXPECT_MAT_EQ(expected, product);
}


/**
 * @brief Verify that the binary multiplication operator (matrix * scalar) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Mat3ScalarMultiplication, MatrixTimesScalarReturnsScaledMatrix)
{
    const fgm::Mat3 product = this->_mat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


/**
 * @brief Verify that the binary multiplication operator (scalar * matrix) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Mat3ScalarMultiplication, ScalarTimesAMatrixReturnsScaledMatrix)
{
    const fgm::Mat3 product = this->_scalar * this->_mat;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


/**
 * @brief Verify that the compound multiplication assignment operator (scalar) performs an element-wise product
 *        and mutates the matrix in-place.
 */
TYPED_TEST(Mat3ScalarMultiplication, MatrixTimesEqualScalarIsTheSameMatrixScaled)
{
    this->_mat *= this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, this->_mat);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, this->_mat);
    }
}


/**
 * @brief Verify that the binary multiplication operator (scalar) perform automatic type promotion
 *        to the wider numeric type.
 */
TYPED_TEST(Mat3ScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Mat3 product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}


/**
 * @brief Verify that the compound multiplication assignment operator (scalar) maintains the destination type and
 *        perform an implicit cast.
 */
TEST(Mat3ScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Mat3 mat    = { 1.0f, -2.0f, 3.0f, -4.0f, 5.0f, 6.0f, 7.0f, 8.0f, -9.0f };
    const double scalar = 5.0;
    mat *= scalar;

    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


/**
 * @brief Verify that the compound multiplication operator (scalar) for mixed type
 *        ensure minimal precision loss.
 */
TEST(Mat3ScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    fgm::Mat3 mat    = { 1, -2, 3, -4, 5, 6, 7, 8, -9 };
    const double scalar = 2.5;
    const fgm::Mat3 expected{ 2, -5, 7, -10, 12, 15, 17, 20, -22 };

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
TYPED_TEST(Mat3VectorMultiplication, MatrixTimesVectorReturnsATransformedVector)
{
    const auto transformedVector = this->_mat * this->_vec;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingColVector, transformedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralColVector, transformedVector);
    }
}


/**
 * @brief Verify that the binary vector multiplication operation with fractional values perform linear transformation
 *        and returns a new column vector.
 */
TYPED_TEST(Mat3VectorFractionalMultiplication, MatrixTimesVectorReturnsATransformedVectorWithPrecision)
{
    const auto transformedVector = this->_mat * this->_vec;
    EXPECT_VEC_EQ(this->_expectedColVector, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation(mat * Vec) with identity matrix
 *        and returns the original column vector.
 */
TEST(Mat3VectorMultiplication, IdentityMatrixTimesVectorReturnsOriginalVector)
{
    const fgm::Mat3<float> iMatrix = fgm::Mat3<float>::identity();
    const fgm::Vec3F vec{ 2.0f, 1.0f, 2.5 };

    const fgm::Vec3F transformedVector = iMatrix * vec;

    EXPECT_VEC_EQ(vec, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation perform automatic type promotion
 *        to the wider numeric type.
 */
TEST(Mat3VectorMultiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
{
    const fgm::Mat3 mat{ 1.0, 2.0, 3.0 };
    const fgm::Vec3I vec{ 2, 1, 3 };

    [[maybe_unused]] const auto transformedVector = mat * vec;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


/**
 * @brief Verify that the binary vector multiplication operation perform linear transformation
 *        and returns a new row vector.
 */
TYPED_TEST(Mat3VectorMultiplication, VectorTimesMatrixReturnsATransformedVector)
{
    const auto transformedVector = this->_vec * this->_mat;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingRowVector, transformedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralRowVector, transformedVector);
    }
}


/**
 * @brief Verify that the binary vector multiplication operation with fractional values perform linear transformation
 *        and returns a new row vector.
 */
TYPED_TEST(Mat3VectorFractionalMultiplication, VectorTimesMatrixReturnsATransformedVectorWithPrecision)
{
    const auto transformedVector = this->_vec * this->_mat;
    EXPECT_VEC_EQ(this->_expectedRowVector, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation with identity matrix
 *        and returns the original row vector.
 */
TEST(Mat3VectorMultiplication, VectorTimesIdentityMatrixReturnsOriginalVector)
{
    const fgm::Mat3<float> iMatrix = fgm::Mat3<float>::identity();
    const fgm::Vec3F vec{ 2.0f, 1.0f, 3.0f };

    const fgm::Vec3F transformedVector = vec * iMatrix;

    EXPECT_VEC_EQ(vec, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation perform automatic type promotion
 *        to the wider numeric type.
 */
TEST(Mat3VectorMultiplication, VecTimesMat_MixedTypeScalarMultiplicationPromotesType)
{
    const fgm::Mat3 mat{ 1.0, 2.0, 3.0 };
    const fgm::Vec3I vec{ 2, 1, 3 };

    [[maybe_unused]] const auto transformedVector = vec * mat;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


/**
 * @brief Verify that the compound vector multiplication operation perform linear transformation
 *        and mutates the vector in-place.
 */
TYPED_TEST(Mat3VectorMultiplication, VectorTimesEqualMatrixReturnsATransformedVector)
{
    auto transformedVector = this->_vec;
    transformedVector *= this->_mat;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingRowVector, transformedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralRowVector, transformedVector);
    }
}


/**
 * @brief Verify that the compound vector multiplication operation with identity matrix
 *        does not mutate the row vector components.
 */
TEST(Mat3VectorMultiplication, VectorTimesEqualIdentityMatrixReturnsOriginalVector)
{
    const fgm::Mat3<float> iMatrix = fgm::Mat3<float>::identity();
    fgm::Vec3F vec{ 2.0f, 1.0f, 3.0f };

    vec *= iMatrix;

    EXPECT_VEC_CONTAINS(vec, 2.0f, 1.0f, 3.0f);
}


/**
 * @brief Verify that the compound vector multiplication operation maintains the destination type and
 *        perform an implicit cast.
 */
TEST(Mat3VectorMultiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
{
    const fgm::Mat3<double> iMatrix = fgm::Mat3<double>::identity();
    [[maybe_unused]] fgm::Vec3I vec{ 2, 1, 5 };

    (void) (vec *= iMatrix);
    static_assert(std::is_same_v<decltype(vec)::value_type, int>);
}


/**
 * @brief Verify that the compound multiplication operator (vector) for mixed type
 *        ensure minimal precision loss.
 */
TEST(Mat3VectorMultiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    const fgm::Mat3 mat{ 2.5, 3.5, 0.5, 1.5, 12.0, 3.25, 5.0, 11.5, 5.0 };
    fgm::Vec3 vec{ 10, 20, 30 };
    const fgm::Vec3 expected{ 205, 620, 220 };

    vec *= mat;

    EXPECT_VEC_EQ(expected, vec);
}


/**************************************
 *                                    *
 *    MATRIX MULTIPLICATION TESTS     *
 *                                    *
 **************************************/

/** @brief Verify that the binary vector multiplication operation return matrix product. */
TYPED_TEST(Mat3Multiplication, MatrixTimesMatrixReturnsAMatrixProduct)
{
    const auto transformedVector = this->_matA * this->_matB;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
    }
}


/** @brief Verify that the binary vector multiplication operation return matrix product for denormals. */
TYPED_TEST(Mat3FractionalMultiplication, MatrixTimesMatrixReturnsMatrixWithPrecision)
{
    const auto transformedVector = this->_matA * this->_matB;
    EXPECT_MAT_EQ(this->_expectedMat, transformedVector);
}


/**
 * @brief Verify that binary matrix multiplication with identity matrix
 *        returns original matrix.
 */
TEST(Mat3Multiplication, MultipliedByIdentityMatrixReturnsOriginalMatrix)
{
    const fgm::Mat3<float> iMatrix = fgm::Mat3<float>::identity();
    const fgm::Mat3 mat{ 1.0f, 2.0f, 3.0f };

    const fgm::Mat3 matrixProduct = iMatrix * mat;

    EXPECT_MAT_EQ(mat, matrixProduct);
}


/**
 * @brief Verify that the binary matrix multiplication operation perform automatic type promotion
 *        to the wider numeric type.
 */
TEST(Mat3Multiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
{
    const fgm::Mat3 matA{ 1.0, 2.0, 3.0 };
    const fgm::Mat3 matB{ 2, 1, 3 };

    [[maybe_unused]] const auto transformedVector = matA * matB;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


/** @brief Verify that the compound vector multiplication operation perform an in-place matrix multiplication. */
TYPED_TEST(Mat3Multiplication, CompoundMultiplicationOperationPerformInPlaceMatrixMultiplication)
{
    auto transformedVector = this->_matA;
    transformedVector *= this->_matB;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
    }
}


/**
 * @brief Verify that components matrix multiplication with identity matrix
 *        does not mutate the calling matrix.
 */
TEST(Mat3Multiplication, TimesEqualIdentityMatrixReturnsOriginalMatrix)
{
    const fgm::Mat3<float> iMatrix = fgm::Mat3<float>::identity();
    fgm::Mat3 mat{ 1.0f, 2.0f, 3.0f };

    mat *= iMatrix;
    EXPECT_MAT_CONTAINS(std::vector{ 1.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 3.0f }, mat);
}


/**
 * @brief Verify that the compound matrix multiplication operation maintains the destination type and
 *        perform an implicit cast.
 */
TEST(Mat3Multiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
{
    const fgm::Mat3<double> iMatrix = fgm::Mat3<double>::identity();
    fgm::Mat3 mat{ 1, 2, 3 };

    mat *= iMatrix;
    static_assert(std::is_same_v<decltype(mat)::value_type, int>);
}


/**
 * @brief Verify that the compound multiplication operator (matrix) for mixed type
 *        ensure minimal precision loss.
 */
TEST(Mat3Multiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    const fgm::Mat3 matA{ 2.5, 3.5, 0.5, 1.5, 2.5, -12.5, 5.45, 23.25, 85.5 };
    fgm::Mat3 matB{ 5, 10, 15, 20, 25, 30, 35, 40, 45 };
    const fgm::Mat3 expectedMatrix{ 109, 391, 1160, 251, 830, 2262, 392, 1268, 3365 };

    matB *= matA;

    EXPECT_MAT_EQ(expectedMatrix, matB);
}


/** @} */
