/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 10, 2026
 *
 * @brief Verifies @ref fgm::Matrix2D multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix2DScalarMultiplication: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _mat;
    T _scalar;
    fgm::Matrix2D<T> _expectedFloatingMat;
    fgm::Matrix2D<T> _expectedIntegralMat;



    void SetUp() override
    {
        _mat = { fgm::Vector2D{ T(7), T(13) }, fgm::Vector2D{ T(5), T(4) } };
        _scalar = T(2.123456789123456);
        _expectedFloatingMat = { fgm::Vector2D{ T(14.864197523864192), T(27.604938258604928) },
                                 fgm::Vector2D{ T(10.61728394561728), T(8.493827156493824) } };
        _expectedIntegralMat = { fgm::Vector2D{ T(14), T(26) }, fgm::Vector2D{ T(10), T(8) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix2D scalar multiplication, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix2DScalarMultiplication, SupportedArithmeticTypes);


template <typename T>
class Matrix2DVectorMultiplication: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _mat;
    fgm::Vector2D<T> _vec;
    fgm::Vector2D<T> _expectedFloatingColVector, _expectedIntegralColVector, _expectedFloatingRowVector,
        _expectedIntegralRowVector;

    void SetUp() override
    {
        _mat = { fgm::Vector2D{ T(7.12345678912345), T(13.12345678912345) },
                 fgm::Vector2D{ T(5.12345678912345), T(4.12345678912345) } };
        _vec = { T(2.123456789123456), T(3.123456832912) };
        _expectedFloatingColVector = { T(31.129248797008778), T(40.74653269883751) };
        _expectedIntegralColVector = { T(29), T(38) };
        _expectedFloatingRowVector = { T(56.116903460304776), T(23.75887838584987) };
        _expectedIntegralRowVector = { T(53), T(22) };
    }
};
/** @brief Test fixture for @ref fgm::Matrix2D vector multiplication, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix2DVectorMultiplication, SupportedArithmeticTypes);


template <typename T>
class Matrix2DVectorFractionalMultiplication: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _mat;
    fgm::Vector2D<T> _vec, _expectedColVector, _expectedRowVector;

    void SetUp() override
    {
        _mat = { fgm::Vector2D{ T(0.1234568989329), T(0.1234214891234) },
                  fgm::Vector2D{ T(-0.123489823149), T(-0.123489757623) } };
        _vec = fgm::Vector2D{ T(0.8923764912287), T(0.78352829112384) };

        _expectedColVector = fgm::Vector2D{ T(0.013412264184596345), T(0.013380716644514457) };
        _expectedRowVector = fgm::Vector2D{ T(0.20687426274853477), T(-0.20695713384580372) };
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2D vector multiplication with denormals,
 *        parameterized by @ref SupportedFloatingPointTypes.
 */
TYPED_TEST_SUITE(Matrix2DVectorFractionalMultiplication, SupportedFloatingPointTypes);


template <typename T>
class Matrix2DMultiplication: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _matA, _matB, _expectedFloatingMat, _expectedIntegralMat;

    void SetUp() override
    {
        _matA = { fgm::Vector2D{ T(7.12345678912345), T(13.12345678912345) },
                  fgm::Vector2D{ T(5.12345678912345), T(4.12345678912345) } };
        _matB = { fgm::Vector2D{ T(3.12345678912345), T(10.12345678912345) },
                  fgm::Vector2D{ T(8.12345678912345), T(3.12345678912345) } };

        _expectedFloatingMat = { fgm::Vector2D{ T(74.11690288564759), T(82.73418683126485) },
                                 fgm::Vector2D{ T(73.8699893074007), T(119.48727325301795) } };
        _expectedIntegralMat = { fgm::Vector2D{ T(71), T(79) }, fgm::Vector2D{ T(71), T(116) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix2D matrix multiplication, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix2DMultiplication, SupportedArithmeticTypes);


template <typename T>
class Matrix2DFractionalMultiplication: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _matA, _matB, _expectedMat;

    void SetUp() override
    {
        _matA = { fgm::Vector2D{ T(0.1234568989329), T(0.1234214891234) },
                  fgm::Vector2D{ T(-0.123489823149), T(-0.123489757623) } };
        _matB = { fgm::Vector2D{ T(0.8923764912287), T(0.78352829112384) },
                  fgm::Vector2D{ T(0.0123412348958), T(-0.0231423489589) } };

        _expectedMat = { fgm::Vector2D{ T(0.013412264184596345), T(0.013380716644514457) },
                         fgm::Vector2D{ T(0.004381455169424965), T(0.004381016652222751) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix2D matrix multiplication with fractional values(<1), parameterized by @ref
 * SupportedFloatingPointTypes. */
TYPED_TEST_SUITE(Matrix2DFractionalMultiplication, SupportedFloatingPointTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Multiplication
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
    constexpr fgm::Matrix2D MAT1(1, 2, 3, 4);
    constexpr fgm::Matrix2D MAT2(5, 6, 7, 8);
    constexpr fgm::Vector2D VEC(1, 2);

    // Verify matrix * scalar multiplication
    constexpr fgm::Matrix2D BINARY_PRODUCT_1 = MAT1 * 2;
    static_assert(BINARY_PRODUCT_1(0, 0) == 2);
    static_assert(BINARY_PRODUCT_1(0, 1) == 4);
    static_assert(BINARY_PRODUCT_1(1, 0) == 6);
    static_assert(BINARY_PRODUCT_1(1, 1) == 8);


    // Verify scalar * matrix multiplication
    constexpr fgm::Matrix2D BINARY_PRODUCT_2 = 2 * MAT1;
    static_assert(BINARY_PRODUCT_2(0, 0) == 2);
    static_assert(BINARY_PRODUCT_2(0, 1) == 4);
    static_assert(BINARY_PRODUCT_2(1, 0) == 6);
    static_assert(BINARY_PRODUCT_2(1, 1) == 8);

    // Verify matrix * vector multiplication
    constexpr fgm::Vector2D COL_VECTOR_PRODUCT = MAT1 * VEC;
    static_assert(COL_VECTOR_PRODUCT[0] == 5);
    static_assert(COL_VECTOR_PRODUCT[1] == 11);

    // Verify vector * matrix multiplication
    constexpr fgm::Vector2D ROW_VEC_PRODUCT = VEC * MAT1;
    static_assert(ROW_VEC_PRODUCT[0] == 7);
    static_assert(ROW_VEC_PRODUCT[1] == 10);

    // Verify matrix * matrix multiplication
    constexpr fgm::Matrix2D MAT_PRODUCT = MAT1 * MAT2;
    static_assert(MAT_PRODUCT(0, 0) == 19);
    static_assert(MAT_PRODUCT(0, 1) == 22);
    static_assert(MAT_PRODUCT(1, 0) == 43);
    static_assert(MAT_PRODUCT(1, 1) == 50);
} // namespace



/**************************************
 *                                    *
 *     SCALAR MULTIPLICATION TESTS    *
 *                                    *
 **************************************/

/** @brief Verify that scalar multiplication by zero returns a zero matrix. */
TEST(Matrix2DScalarMultiplication, MultiplicationByZeroReturnsZeroMatrix)
{
    constexpr fgm::Matrix2D mat(3.0f, 4.0f, 5.0f, 6.0f);

    constexpr fgm::Matrix2D product = mat * 0;

    EXPECT_MAT_ZERO(product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Matrix2DScalarMultiplication, MultiplicationByOneReturnsOriginalMatrix)
{
    constexpr fgm::Matrix2D mat(3.0f, 4.0f, 5.0f, 6.0f);

    constexpr fgm::Matrix2D product = mat * 1;

    EXPECT_MAT_EQ(mat, product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Matrix2DScalarMultiplication, MultiplicationByNegativeScalarFlipsSigns)
{
    constexpr fgm::Matrix2D mat = { 1.0f, -2.0f, -4.0f, 5.0f };
    constexpr fgm::Matrix2D expected = { -2.0f, 4.0f, 8.0f, -10.0f };
    constexpr float scalar = -2.0f;

    constexpr fgm::Matrix2D<float> product = mat * scalar;

    EXPECT_MAT_EQ(expected, product);
}


/**
 * @brief Verify that the binary multiplication operator (matrix * scalar) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix2DScalarMultiplication, MatrixTimesScalarReturnsScaledMatrix)
{
    const fgm::Matrix2D product = this->_mat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
}


/**
 * @brief Verify that the binary multiplication operator (scalar * matrix) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix2DScalarMultiplication, ScalarTimesAMatrixReturnsScaledMatrix)
{
    const fgm::Matrix2D product = this->_scalar * this->_mat;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
}


/**
 * @brief Verify that the compound multiplication assignment operator (scalar) performs an element-wise product
 *        and mutates the matrix in-place.
 */
TYPED_TEST(Matrix2DScalarMultiplication, MatrixTimesEqualScalarIsTheSameMatrixScaled)
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
TYPED_TEST(Matrix2DScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    constexpr double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Matrix2D product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}


/**
 * @brief Verify that the compound multiplication assignment operator (scalar) maintains the destination type and
 *        perform an implicit cast.
 */
TEST(Matrix2DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Matrix2D mat(3.0f, -1.0f, -12.0f, 14.0f);
    constexpr double scalar = 5.0;
    mat *= scalar;

    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


/**
 * @brief Verify that the compound multiplication operator (scalar) for mixed type
 *        ensure minimal precision loss.
 */
TEST(Matrix2DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    fgm::Matrix2D mat(3, -1, 10, 5);
    constexpr double scalar = 2.5;
    constexpr fgm::Matrix2D expected(7, -2, 25, 12);

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
TYPED_TEST(Matrix2DVectorMultiplication, MatrixTimesVectorReturnsATransformedVector)
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
TYPED_TEST(Matrix2DVectorFractionalMultiplication, MatrixTimesVectorReturnsATransformedVectorWithPrecision)
{
    const auto transformedVector = this->_mat * this->_vec;
        EXPECT_VEC_EQ(this->_expectedColVector, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation(mat * vec) with identity matrix
 *        and returns the original column vector.
 */
TEST(Matrix2DVectorMultiplication, IdentityMatrixTimesVectorReturnsOriginalVector)
{
    constexpr fgm::Matrix2D<float> iMatrix;
    constexpr fgm::vec2 vec(2.0f, 1.0f);

    constexpr fgm::vec2 transformedVector = iMatrix * vec;

    EXPECT_VEC_EQ(vec, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation perform automatic type promotion
 *        to the wider numeric type.
 */
TEST(Matrix2DVectorMultiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
{
    constexpr fgm::Matrix2D mat(1.0, 2.0);
    constexpr fgm::iVec2 vec(2, 1);

    constexpr auto transformedVector = mat * vec;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


/**
 * @brief Verify that the binary vector multiplication operation perform linear transformation
 *        and returns a new row vector.
 */
TYPED_TEST(Matrix2DVectorMultiplication, VectorTimesMatrixReturnsATransformedVector)
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
TYPED_TEST(Matrix2DVectorFractionalMultiplication, VectorTimesMatrixReturnsATransformedVectorWithPrecision)
{
    const auto transformedVector = this->_vec * this->_mat;
    EXPECT_VEC_EQ(this->_expectedRowVector, transformedVector);
}


/**
 * @brief Verify that the binary vector multiplication operation with identity matrix
 *        and returns the original row vector.
 */
TEST(Matrix2DVectorMultiplication, VectorTimesIdentityMatrixReturnsOriginalVector)
{
    constexpr fgm::Matrix2D<float> iMatrix;
    constexpr fgm::vec2 vec(2.0f, 1.0f);

    constexpr fgm::vec2 transformedVector = vec * iMatrix;

    EXPECT_VEC_EQ(vec, transformedVector);
}



/**
 * @brief Verify that the binary vector multiplication operation perform automatic type promotion
 *        to the wider numeric type.
 */
TEST(Matrix2DVectorMultiplication, VecTimesMat_MixedTypeScalarMultiplicationPromotesType)
{
    constexpr fgm::Matrix2D mat(1.0, 2.0);
    constexpr fgm::iVec2 vec(2, 1);

    [[maybe_unused]] constexpr auto transformedVector = vec * mat;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


/**
 * @brief Verify that the compound vector multiplication operation perform linear transformation
 *        and mutates the vector in-place.
 */
TYPED_TEST(Matrix2DVectorMultiplication, VectorTimesEqualMatrixReturnsATransformedVector)
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
TEST(Matrix2DVectorMultiplication, VectorTimesEqualIdentityMatrixReturnsOriginalVector)
{
    constexpr fgm::Matrix2D<float> iMatrix;
    fgm::vec2 vec(2.0f, 1.0f);

    vec *= iMatrix;

    EXPECT_VEC_CONTAINS(vec, 2.0f, 1.0f);
}


/**
 * @brief Verify that the compound vector multiplication operation maintains the destination type and
 *        perform an implicit cast.
 */
TEST(Matrix2DVectorMultiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
{
    constexpr fgm::Matrix2D<double> iMatrix;
    [[maybe_unused]] fgm::iVec2 vec(2, 1);

    vec *= iMatrix;
    static_assert(std::is_same_v<decltype(vec)::value_type, int>);
}


/**
 * @brief Verify that the compound multiplication operator (vector) for mixed type
 *        ensure minimal precision loss.
 */
TEST(Matrix2DVectorMultiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    constexpr fgm::Matrix2D mat(2.5, 3.5, 0.5, 1.5);
    fgm::Vector2D vec(10, 20);
    constexpr fgm::Vector2D expected(35, 65);

    vec *= mat;

    EXPECT_VEC_EQ(expected, vec);
}



/**************************************
 *                                    *
 *    MATRIX MULTIPLICATION TESTS     *
 *                                    *
 **************************************/

/** @brief Verify that the binary vector multiplication operation return matrix product. */
TYPED_TEST(Matrix2DMultiplication, MatrixTimesMatrixReturnsAMatrixProduct)
{
    const auto transformedVector = this->_matA * this->_matB;
    if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
}


/** @brief Verify that the binary vector multiplication operation return matrix product for denormals. */
TYPED_TEST(Matrix2DFractionalMultiplication, MatrixTimesMatrixReturnsMatrixWithPrecision)
{
    const auto transformedVector = this->_matA * this->_matB;
    EXPECT_MAT_EQ(this->_expectedMat, transformedVector);
}


/**
 * @brief Verify that binary matrix multiplication with identity matrix
 *        returns original matrix.
 */
TEST(Matrix2DMultiplication, MultipliedByIdentityMatrixReturnsOriginalMatrix)
{
    constexpr fgm::Matrix2D<float> iMatrix;
    constexpr fgm::Matrix2D mat(1.0f, 2.0f, 3.0f, 4.0f);

    constexpr fgm::Matrix2D matrixProduct = iMatrix * mat;

    EXPECT_MAT_EQ(mat, matrixProduct);
}


/**
 * @brief Verify that the binary matrix multiplication operation perform automatic type promotion
 *        to the wider numeric type.
 */
TEST(Matrix2DMultiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
{
    constexpr fgm::Matrix2D matA(1.0, 2.0);
    constexpr fgm::Matrix2D matB(2, 1);

    [[maybe_unused]] constexpr auto transformedVector = matA * matB;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


/** @brief Verify that the compound vector multiplication operation perform an in-place matrix multiplication. */
TYPED_TEST(Matrix2DMultiplication, CompoundMultiplicationOperationPerformInPlaceMatrixMultiplication)
{
    auto transformedVector = this->_matA;
    transformedVector *= this->_matB;
    if constexpr (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
}


/**
 * @brief Verify that components matrix multiplication with identity matrix
 *        does not mutate the calling matrix.
 */
TEST(Matrix2DMultiplication, TimesEqualIdentityMatrixReturnsOriginalMatrix)
{
    constexpr fgm::Matrix2D<float> iMatrix;
    fgm::Matrix2D mat(1.0f, 2.0f, 3.0f, 4.0f);

    mat *= iMatrix;
    EXPECT_MAT_CONTAINS(std::vector{ 1.0f, 2.0f, 3.0f, 4.0f }, mat);
}


/**
 * @brief Verify that the compound matrix multiplication operation maintains the destination type and
 *        perform an implicit cast.
 */
TEST(Matrix2DMultiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
{
    constexpr fgm::Matrix2D<double> iMatrix;
    fgm::Matrix2D mat(1, 2, 3, 4);

    mat *= iMatrix;
    static_assert(std::is_same_v<decltype(mat)::value_type, int>);
}


/**
 * @brief Verify that the compound multiplication operator (matrix) for mixed type
 *        ensure minimal precision loss.
 */
TEST(Matrix2DMultiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    constexpr fgm::Matrix2D matA(2.5, 3.5, 0.5, 1.5);
    fgm::Matrix2D matB(5, 10, 15, 20);
    constexpr fgm::Matrix2D expectedMatrix(17, 32, 47, 82);

    matB *= matA;

    EXPECT_MAT_EQ(expectedMatrix, matB);
}


/** @} */