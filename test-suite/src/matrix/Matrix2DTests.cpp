#include "utils/FloatEquals.h"
#include "utils/MatrixUtils.h"
#include "utils/VectorUtils.h"

#include <cstddef>
#include <gtest/gtest.h>
#include <matrix/Matrix2D.h>
#include <vector/Vector2D.h>

using namespace testutils::Matrix2D;


static constexpr std::size_t size = 4;
static constexpr std::size_t rowSize = 2;


/***********************************************
 *                                             *
 *  INITIALIZATION, ACCESS AND MUTATION TESTS  *
 *                                             *
 ***********************************************/

TEST(Matrix2D_Initialization, InitializedWithOutParametersProvidesIdentityMatrix)
{
    // Arrange & Act
    const math::Matrix2D<float> mat;

    // Assert
    EXPECT_MAT_IDENTITY(mat);
}

TEST(Matrix2D_Initialization, InitializationSupportedForIntegers)
{
    // Arrange and Act
    const math::Matrix2D<int> mat;

    // Assert
    static_assert(std::is_same_v<typename decltype(mat)::value_type, int>);
    EXPECT_MAT_IDENTITY(mat);
}

TEST(Matrix2D_Initialization, InitializedWithParametersProvidesCorrectMatrix)
{
    // Arrange & Act
    const math::Matrix2D mat(0.0f, 1.0f, 2.0f, 3.0f);

    // Assert
    for (std::size_t i = 0; i < size; ++i)
        EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i / rowSize, i % rowSize));
}

TEST(Matrix2D_Initialization, InitializedWithTwo2DVectorsProvidesCorrectMatrix)
{
    // Arrange & Act
    const math::Vector2D col1(0.0f, 2.0f);
    const math::Vector2D col2(1.0f, 3.0f);

    const math::Matrix2D mat(col1, col2);

    // Assert
    for (size_t i = 0; i < size; ++i)
        EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i / rowSize, i % rowSize));
}

TEST(Matrix2D_Initialization, CanMutateVectorAtIndex)
{
    // Arrange
    math::Matrix2D<float> mat;
    math::Vector2D vec(3.0f, 1.0f);

    // Act
    mat[1] = vec;

    // Assert
    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 1));

    EXPECT_FLOAT_EQ(0.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(1.0f, mat(1, 1));
}

TEST(Matrix2D_Initialization, CanMutateValueAtRowColumn)
{
    // Arrange
    math::Matrix2D<float> mat;

    // Act
    for (size_t i = 0; i < size; ++i)
        mat(i / rowSize, i % rowSize) = static_cast<float>(i);

    // Assert
    for (size_t i = 0; i < size; ++i)
        EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i / rowSize, i % rowSize));
}

TEST(Matrix2D_Access, CanBeAccessedAsAVectorAtIndex)
{
    // Arrange
    math::Matrix2D<float> mat;

    // Act
    math::Vector2D vec = mat[1];

    // Assert
    EXPECT_FLOAT_EQ(0.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
}

TEST(Matrix2D_Access, CanBeAccessedAsAValueAtRowColumn)
{
    // Arrange & Act
    const math::Matrix2D mat(0.0f, 1.0f, 2.0f, 3.0f);

    // Assert
    for (size_t i = 0; i < size; ++i)
        EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i / rowSize, i % rowSize));
}


/*********************************
 *                               *
 *  SIMPLE MATH OPERATION TESTS  *
 *                               *
 *********************************/

TEST(Matrix2D_Sum, SumOfTwoMatricesReturnsAnotherMatrixWithCorrectValues)
{
    // Arrange
    math::Matrix2D a = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::Matrix2D b = { 3.0f, 2.0f, -8.0f, 24.0f };
    const math::Matrix2D c = { 4.0f, 4.0f, -4.0f, 29.0f };

    // Act
    const math::Matrix2D<float> res = a + b;

    // Assert
    EXPECT_MAT_EQ(c, res);
}

TEST(Matrix2D_Sum, PlusEqualsMatrixWithAnotherMatrixReturnsSameMatrixWithCorrectValues)
{
    // Arrange
    math::Matrix2D a = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::Matrix2D b = { 3.0f, 2.0f, -8.0f, 24.0f };
    const math::Matrix2D c = { 4.0f, 4.0f, -4.0f, 29.0f };

    // Act
    a += b;

    // Assert
    EXPECT_MAT_EQ(c, a);
}

TEST(Matrix2D_Difference, DifferenceOfTwoMatricesReturnsAnotherMatrixWithCorrectValues)
{
    // Arrange
    math::Matrix2D a = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::Matrix2D b = { 3.0f, 2.0f, -8.0f, 24.0f };
    const math::Matrix2D c = { -2.0f, 0.0f, 12.0f, -19.0f };

    // Act
    const math::Matrix2D<float> res = a - b;

    // Assert
    EXPECT_MAT_EQ(c, res);
}

TEST(Matrix2D_Difference, MinusEqualsMatrixWithAnotherMatrixReturnsSameMatrixWithCorrectValues)
{
    // Arrange
    math::Matrix2D a = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::Matrix2D b = { 3.0f, 2.0f, -8.0f, 24.0f };
    const math::Matrix2D c = { -2.0f, 0.0f, 12.0f, -19.0f };

    // Act
    a -= b;

    // Assert
    EXPECT_MAT_EQ(c, a);
}

TEST(Matrix2D_Product, MatrixTimesAIntegerScalarReturnsCorrectMatrix)
{
    // Arrange
    const math::Matrix2D a = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::Matrix2D expected = { 2.0f, 4.0f, 8.0f, 10.0f };
    constexpr int scalar = 2;

    // Act
    const math::Matrix2D actual = a * scalar;

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix2D_Product, IntegerScalarTimesAMatrixReturnsCorrectMatrix)
{
    // Arrange
    const math::Matrix2D a = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::Matrix2D expected = { 2.0f, 4.0f, 8.0f, 10.0f };
    constexpr int scalar = 2;

    // Act
    const math::Matrix2D<float> actual = scalar * a;

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix2D_Product, MatrixTimesEqualIntegerScalarIsTheSameMatrixWithCorrectValues)
{
    // Arrange
    math::Matrix2D a = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::Matrix2D b = { 2.0f, 4.0f, 8.0f, 10.0f };
    constexpr int scalar = 2;

    // Act
    a *= scalar;

    // Assert
    EXPECT_MAT_EQ(a, b);
}

TEST(Matrix2D_Product, MatrixTimesOneReturnANewMatrixWithOriginalMatrixValues)
{
    // Arrange
    const math::Matrix2D a = { 1.0f, 2.0f, 4.0f, 5.0f };

    // Act
    const math::Matrix2D<float> b = a * 1;

    // Assert
    EXPECT_MAT_EQ(a, b);
}

TEST(Matrix2D_Product, MatrixTimesZeroScalarReturnsZeroMatrix)
{
    // Arrange
    const math::Matrix2D a = { 1.0f, 2.0f, 4.0f, 5.0f };

    // Act
    const math::Matrix2D<float> b = a * 0;

    // Assert
    EXPECT_MAT_ZERO(b);
}

TEST(Matrix2D_Product, MatrixTimesAFloatScalarReturnsCorrectMatrix)
{
    // Arrange
    const math::Matrix2D a = { 1.0f, 2.0f, 4.0f, 5.0f };
    constexpr float scalar = 2.5f;

    const math::Matrix2D expected = { 2.5f, 5.0f, 10.0f, 12.5f };

    // Act
    const math::Matrix2D<float> b = a * scalar;

    // Assert
    EXPECT_MAT_EQ(expected, b);
}

TEST(Matrix2D_Product, MatrixTimesNegativeFloatScalarFlipsSigns)
{
    // Arrange
    const math::Matrix2D a = { 1.0f, -2.0f, -4.0f, 5.0f };
    const math::Matrix2D expected = { -2.0f, 4.0f, 8.0f, -10.0f };
    constexpr float scalar = -2.0f;

    // Act
    const math::Matrix2D<float> b = a * scalar;

    // Assert
    EXPECT_MAT_EQ(expected, b);
}

TEST(Matrix2D_Product, MatrixTimesVectorReturnsANewMatrixWithCorrectValues)
{
    // Arrange
    const math::Matrix2D mat = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::vec2 vec(2.0f, 1.0f);
    const math::vec2 expected(4.0f, 13.0f);

    // Act
    const math::vec2 actual = mat * vec;

    // Assert
    testutils::EXPECT_VEC_EQ(expected, actual);
}

TEST(Matrix2D_Product, IdentityMatrixTimesAVectorReturnsTheSameMatrix)
{
    // Arrange
    const math::Matrix2D<float> mat;
    const math::vec2 vec(2.0f, 1.0f);

    // Act
    const math::vec2 actual = mat * vec;

    // Assert
    testutils::EXPECT_VEC_EQ(vec, actual);
}

TEST(Matrix2D_Product, VectorTimesAMatrixReturnsANewVectorWithCorrectValues)
{
    // Arrange
    const math::Matrix2D mat = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::vec2 vec(2.0f, 1.0f);
    const math::vec2 expected(6.0f, 9.0f);

    // Act
    const math::vec2 actual = vec * mat;

    // Assert
    testutils::EXPECT_VEC_EQ(expected, actual);
}

TEST(Matrix2D_Product, VectorTimesIdentityMatrixReturnsTheSameMatrix)
{
    // Arrange
    const math::Matrix2D<float> mat;
    math::vec2 vec(2.0f, 1.0f);

    // Act
    const math::vec2 actual = vec * mat;

    // Assert
    testutils::EXPECT_VEC_EQ(vec, actual);
}

TEST(Matrix2D_Product, VectorTimesEqualMatrixReturnTheSameVectorWithNewValues)
{
    // Arrange
    math::vec2 vec(2.0f, 1.0f);
    const math::Matrix2D mat = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::vec2 expected(6.0f, 9.0f);

    // Act
    vec *= mat;

    // Assert
    testutils::EXPECT_VEC_EQ(expected, vec);
}

TEST(Matrix2D_Product, MatrixTimesMatrixGivesAnotherMatrixWithCorrectValues)
{
    // Arrange
    const math::Matrix2D mat1 = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::Matrix2D mat2 = { 2.0f, 4.0f, 8.0f, 10.0f };
    const math::Matrix2D expected = { 18.0f, 24.0f, 48.0f, 66.0f };

    // Act
    const math::Matrix2D actual = mat1 * mat2;

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix2D_Product, MatrixTimesIdentityMatrixReturnsSameMatrix)
{
    // Arrange
    const math::Matrix2D mat = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::Matrix2D<float> eye;

    // Act
    const math::Matrix2D actual = mat * eye;

    // Assert
    EXPECT_MAT_EQ(mat, actual);
}

TEST(Matrix2D_Product, MatrixTimesEqualAnotherMatrixReturnsSameMatrixWithCorrectValues)
{
    // Arrange
    math::Matrix2D mat1 = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::Matrix2D mat2 = { 2.0f, 4.0f, 8.0f, 10.0f };
    const math::Matrix2D expected = { 18.0f, 24.0f, 48.0f, 66.0f };

    // Act
    mat1 *= mat2;

    // Assert
    EXPECT_MAT_EQ(expected, mat1);
}

TEST(Matrix2D_Product, Matrix2DProductIsAntiCommutative)
{
    // Arrange
    const math::Matrix2D mat1 = { 1.0f, 5.0f, 4.0f, 12.0f };
    const math::Matrix2D mat2 = { 2.0f, 4.0f, 3.0f, 7.0f };


    // Act
    const math::Matrix2D result1 = mat1 * mat2;
    const math::Matrix2D result2 = mat2 * mat1;

    // Assert
    bool commutative = true;
    for (std::size_t i = 0; i < size; i++)
    {
        commutative &= floatEquals(result1(i / rowSize, i % rowSize), result2(i / rowSize, i % rowSize));
    }
    EXPECT_FALSE(commutative);
}

TEST(Matrix2D_Product, Matrix2DProductWithScalarMultiplesAreCommutative)
{
    // Arrange
    const math::Matrix2D mat1 = { 1.0f, 2.0f, 4.0f, 5.0f };
    const math::Matrix2D mat2 = mat1 * 5.0f;

    // Act
    const math::Matrix2D result1 = mat1 * mat2;
    const math::Matrix2D result2 = mat2 * mat1;

    // Assert
    bool commutative = true;
    for (std::size_t i = 0; i < size; i++)
    {
        commutative &= floatEquals(result1(i / rowSize, i % rowSize), result2(i / rowSize, i % rowSize));
    }
    EXPECT_TRUE(commutative);
}

TEST(Matrix2D_Division, MatrixDividedByAIntegerScalarReturnsCorrectMatrix)
{
    // Arrange
    const math::Matrix2D a = { 1.0f, 2.0f, -4.0f, 5.0f };
    const math::Matrix2D expected = { 0.5f, 1.0f, -2.0f, 2.5f };
    constexpr int scalar = 2;

    // Act
    const math::Matrix2D<float> actual = a / scalar;

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix2D_Division, MatrixDividesEqualIntegerScalarIsTheSameMatrixWithCorrectValues)
{
    // Arrange
    math::Matrix2D a = { 1.0f, 2.0f, -4.0f, 5.0f };
    const math::Matrix2D b = { 0.5f, 1.0f, -2.0f, 2.5f };
    constexpr int scalar = 2;

    // Act
    a /= scalar;

    // Assert
    EXPECT_MAT_EQ(b, a);
}

TEST(Matrix2D_Division, MatrixDividedByOneReturnANewMatrixWithOriginalMatrixValues)
{
    // Arrange
    const math::Matrix2D a = { 1.0f, 2.0f, -4.0f, 5.0f };


    // Act
    const math::Matrix2D<float> b = a / 1;

    // Assert
    EXPECT_MAT_EQ(a, b);
}

TEST(Matrix2D_Division, MatrixDividedByZeroScalarReturnsInfinityMatrix)
{
    // Arrange
    const math::Matrix2D a = { 1.0f, 2.0f, -4.0f, 5.0f };

    // Act
    const math::Matrix2D<float> b = a / 0;

    // Assert
    EXPECT_MAT_INF(b);
}

TEST(Matrix2D_Division, MatrixDividedByAFloatScalarReturnsCorrectMatrix)
{
    // Arrange
    const math::Matrix2D a = { 1.0f, 2.0f, 4.0f, 5.0f };

    const math::Matrix2D expected = { 0.4f, 0.8f, 1.6f, 2.0f };

    constexpr float scalar = 2.5;

    // Act
    const math::Matrix2D<float> actual = a / scalar;

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix2D_Division, MatrixDividedNegativeFloatScalarFlipsSigns)
{
    // Arrange
    const math::Matrix2D a = { 1.0f, 2.0f, -4.0f, 5.0f };
    const math::Matrix2D expected = { -0.5f, -1.0f, 2.0f, -2.5f };
    constexpr float scalar = -2.0f;

    // Act
    const math::Matrix2D<float> actual = a / scalar;

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}


/***********************
 *                     *
 *  DETERMINANT TESTS  *
 *                     *
 ***********************/

TEST(Matrix2D_Determinant, IdentityMatrixReturnsDeterminantOfOne)
{
    // Arrange
    const math::Matrix2D<float> mat;
    constexpr float expectedDeterminant = 1.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix2D_Determinant, DiagonalMatrixReturnsProductOfDiagonalEntriesAsDeterminant)
{
    // Arrange
    const math::Matrix2D mat(2.0f, 0.0f, 0.0f, 3.0f);
    constexpr float expectedDeterminant = 6.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix2D_Determinant, MatrixWithScalarMultipleColumnsReturnsDeterminantOfZero)
{
    const math::Matrix2D mat(2.0f, 1.0f, 4.0f, 2.0f);

    constexpr float expectedDeterminant = 0.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix2D_Determinant, MatrixWithScalarMultipleRowsReturnsDeterminantOfZero)
{
    const math::Matrix2D mat(2.0f, 4.0f, 4.0f, 8.0f);

    constexpr float expectedDeterminant = 0.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix2D_Determinant, IdentityMatrixWithSwappedRowsReturnsDeterminantOfNegativeOne)
{
    const math::Matrix2D mat(0.0f, 1.0f, 1.0f, 0.0f);

    constexpr float expectedDeterminant = -1.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix2D_Determinant, IdentityMatrixWithSwappedColumnsReturnsDeterminantOfNegativeOne)
{
    const math::Matrix2D mat(0.0f, 1.0f, 1.0f, 0.0f);

    constexpr float expectedDeterminant = -1.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix2D_Determinant, IdentityMatrixWithShearAppliedsReturnsDeterminantOfOne)
{
    const math::Matrix2D mat(1.0f, 1.0f, 0.0f, 1.0f);

    constexpr float expectedDeterminant = 1.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix2D_Determinant, MatrixDeterminantReturnsCorrectValue)
{
    const math::Matrix2D mat(1.0f, 2.0f, -5.0f, 4.0f);

    constexpr float expectedDeterminant = 14.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix2D_Determinant, MatrixDeterminantWithStaticWrapperReturnsCorrectValue)
{
    const math::Matrix2D mat(1.0f, 2.0f, -5.0f, 4.0f);

    constexpr float expectedDeterminant = 14.0f;

    // Act
    const float actualDeterminant = math::Matrix2D<float>::determinant(mat);

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix2D_Determinant, DeterminantofTransposedMatrixIsEqualToDeterminantOfTheMatrix)
{
    const math::Matrix2D a(1.0f, 2.0f, 0.0f, 4.0f);

    // Act
    const float detA = a.determinant();
    const float detAT = a.transpose().determinant();

    // Assert
    EXPECT_FLOAT_EQ(detA, detAT);
}

TEST(Matrix2D_Determinant, DeterminantOfProductOfMatricesIsSameAsProductOfDeterminantOfMatrix)
{
    // det(A*B) = det(A) * det(B)
    const math::Matrix2D a(1.0f, 2.0f, 0.0f, 4.0f);
    const math::Matrix2D b(1.0f, 2.0f, 4.0f, 5.0f);

    // Act
    const float determinantOfProduct = math::Matrix2D<float>::determinant(a * b);
    const float productOfDeterminant = a.determinant() * b.determinant();

    // Assert
    EXPECT_FLOAT_EQ(determinantOfProduct, productOfDeterminant);
}

TEST(Matrix2D_Determinant, DeterminantOfAMatrixMultipledByScalarIsScalarPowNTimesTheDeterminantOfOriginalMatrix)
{
    // det(t*A) = (t^n)det(A)
    const math::Matrix2D a(1.0f, 2.0f, 0.0f, 4.0f);
    const float scalar = 5.0f;

    // Act
    const float determinantOfProduct = math::Matrix2D<float>::determinant(scalar * a);
    const float productOfDeterminant = (scalar * scalar) * a.determinant(); // n = 2 for 2x2 matrix

    // Assert
    EXPECT_FLOAT_EQ(determinantOfProduct, productOfDeterminant);
}

/*********************
 *                   *
 *  TRANSPOSE TESTS  *
 *                   *
 *********************/

TEST(Matrix2D_Transpose, TransposeOfIdentityMatrixIsItself)
{
    // Arrange
    const math::Matrix2D<float> mat;

    // Act
    const math::Matrix2D<float> actual = mat.transpose();

    // Assert
    EXPECT_MAT_EQ(mat, actual);
}

TEST(Matrix2D_Transpose, TransposeOfAMatrixReturnsMatrixWithRowsAndColumnsSwapped)
{
    // Arrange
    const math::Matrix2D mat(1.0f, 2.0f, 0.0f, 4.0f);
    const math::Matrix2D expected(1.0f, 0.0f, 2.0f, 4.0f);

    // Act
    const math::Matrix2D<float> actual = mat.transpose();


    // Assert
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix2D_Transpose, TransposeOfAMatrixUsingStaticWrapperReturnsMatrixWithRowsAndColumnsSwapped)
{
    // Arrange
    const math::Matrix2D mat(1.0f, 2.0f, 0.0f, 4.0f);
    const math::Matrix2D expected(1.0f, 0.0f, 2.0f, 4.0f);

    // Act
    const math::Matrix2D<float> actual = math::Matrix2D<float>::transpose(mat);

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}


/*******************
 *                 *
 *  INVERSE TESTS  *
 *                 *
 *******************/

TEST(Matrix2D_Inverse, InverseReturnsAnotherMatrixWithCorrectValues)
{
    // Given
    const math::Matrix2D mat(2.0f, 1.0f, 5.0f, 3.0f);
    const math::Matrix2D expectedInverse(3.0f, -1.0f, -5.0f, 2.0f);

    // Act
    const math::Matrix2D actualInverse = mat.inverse();

    // Assert
    EXPECT_MAT_EQ(expectedInverse, actualInverse);
}

TEST(Matrix2D_Inverse, StaticWrapperForInverseReturnsAnotherMatrixWithCorrectValues)
{
    const math::Matrix2D mat(2.0f, 1.0f, 5.0f, 3.0f);
    const math::Matrix2D expectedInverse(3.0f, -1.0f, -5.0f, 2.0f);

    // Act
    const math::Matrix2D<float> actualInverse = math::Matrix2D<float>::inverse(mat);

    // Assert
    EXPECT_MAT_EQ(expectedInverse, actualInverse);
}

TEST(Matrix2D_Inverse, IdentityMatrixInverseReturnsAnotherIdentityMatrix)
{
    // Given
    const math::Matrix2D<float> identity;

    // Act
    const math::Matrix2D<float> actualInverse = identity.inverse();

    // Assert
    EXPECT_MAT_IDENTITY(actualInverse);
}

TEST(Matrix2D_Inverse, MatrixTimeInverseReturnsIdentityMatrix)
{
    const math::Matrix2D mat(1.0f, 2.0f, 3.0f, 1.0f);

    // Act
    const math::Matrix2D<float> inverse = math::Matrix2D<float>::inverse(mat);
    const math::Matrix2D<float> product = mat * inverse;

    // Assert
    EXPECT_MAT_IDENTITY(product);
}

TEST(Matrix2D_Inverse, InverseTimesMatrixReturnsIdentityMatrix)
{
    const math::Matrix2D mat(1.0f, 2.0f, 3.0f, 1.0f);

    // Act
    const math::Matrix2D<float> inverse = math::Matrix2D<float>::inverse(mat);
    const math::Matrix2D<float> product = inverse * mat;

    // Assert
    EXPECT_MAT_IDENTITY(product);
}

TEST(Matrix2D_Inverse, SingularMatrixProducesIdentityMatrix)
{
    const math::Matrix2D singularMatrix(1.0f, 2.0f, 2.0f, 4.0f);

    // Act
    const math::Matrix2D<float> actualInverse = math::Matrix2D<float>::inverse(singularMatrix);

    // Assert
    EXPECT_MAT_IDENTITY(actualInverse);
}

TEST(Matrix2D_Inverse, InversionOfRotationOnlyMatrixReturnsTranspose)
{
    const math::Matrix2D mat(0.0f, -1.0f, 1.0f, 0.0f);
    const math::Matrix2D transpose(0.0f, 1.0f, -1.0f, 0.0f);

    // Act
    const math::Matrix2D<float> actualInverse = math::Matrix2D<float>::inverse(mat);

    // Assert
    EXPECT_MAT_EQ(transpose, actualInverse);
}
