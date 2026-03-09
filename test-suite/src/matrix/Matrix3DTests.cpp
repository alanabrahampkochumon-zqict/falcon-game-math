#include "utils/FloatEquals.h"
#include "utils/MatrixUtils.h"
#include "utils/VectorUtils.h"

#include <cstddef>
#include <gtest/gtest.h>
#include <matrix/Matrix3D.h>
#include <vector/Vector3D.h>

using namespace testutils::Matrix3D;
// TODO: Add test for integer precision on multiplication -> [[2]] * 2.5 = [[5]] not 4


/***********************************************
 *                                             *
 *  INITIALIZATION, ACCESS AND MUTATION TESTS  *
 *                                             *
 ***********************************************/

constexpr int size = 9;
constexpr int rowSize = 3;

TEST(Matrix3D_Initialization, InitializedWithOutParametersProvidesIdentityMatrix)
{
    // Given a matrix initialized without parameters
    const math::Matrix3D<float> mat;

    // Then it's elements form an identity matrix
    EXPECT_MAT_IDENTITY(mat);
}

TEST(Matrix3D_Initialization, InitializationSupportedForIntegers)
{
    // Given an integer matrix initialized without parameters
    const math::Matrix3D<int> mat;

    // Then it's value_type is int, and elements form an identity matrix
    static_assert(std::is_same_v<typename decltype(mat)::value_type, int>);
    EXPECT_MAT_IDENTITY(mat);
}

TEST(Matrix3D_Initialization, InitializedWithParametersProvidesCorrectMatrix)
{
    // Given a matrix with arbitrary values passed in
    const math::Matrix3D mat(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);

    // Then it's elements reflect the correct values
    for (size_t i = 0; i < size; ++i)
        EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i / rowSize, i % rowSize));
}

TEST(Matrix3D_Initialization, InitializedWithThree3DVectorsProvidesCorrectMatrix)
{
    // Arrange & Act
    const math::Vector3D col0(0.0f, 3.0f, 6.0f);
    const math::Vector3D col1(1.0f, 4.0f, 7.0f);
    const math::Vector3D col2(2.0f, 5.0f, 8.0f);

    const math::Matrix3D mat(col0, col1, col2);


    // Assert
    for (std::size_t i = 0; i < size; ++i)
        EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i / rowSize, i % rowSize));
}

TEST(Matrix3D_Initialization, CanMutateVectorAtIndex)
{
    // Arrange
    math::Matrix3D<float> mat;
    math::Vector3D vec(3.0f, 1.0f, 6.0f);

    // Act
    mat[2] = vec;

    // Assert
    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(0.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 2));

    EXPECT_FLOAT_EQ(0.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(1.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(1.0f, mat(1, 2));

    EXPECT_FLOAT_EQ(0.0f, mat(2, 0));
    EXPECT_FLOAT_EQ(0.0f, mat(2, 1));
    EXPECT_FLOAT_EQ(6.0f, mat(2, 2));
}

TEST(Matrix3D_Initialization, CanMutateValueAtRowColumn)
{
    // Arrange
    math::Matrix3D<float> mat;

    // Act
    for (std::size_t i = 0; i < size; ++i)
        mat(i / rowSize, i % rowSize) = static_cast<float>(i);

    // Assert
    for (std::size_t i = 0; i < size; ++i)
        EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i / rowSize, i % rowSize));
}

TEST(Matrix3D_Initialization, ConversionConstructorHandlesTypeDemotion)
{
    // Arrange
    math::Matrix3D<double> mat;


    // Act
    math::Matrix3D<float> copy(mat);
    copy(0, 0) = 5.0f;

    // Assert
    static_assert(std::is_same_v<typename decltype(copy)::value_type, float>);
    EXPECT_MAT_IDENTITY(mat);

    EXPECT_FLOAT_EQ(5.0f, copy(0, 0));
    for (std::size_t i = 1; i < size; ++i)
        EXPECT_FLOAT_EQ(i % rowSize == i / rowSize, copy(i / rowSize, i % rowSize));
}

TEST(Matrix3D_Initialization, ConversionConstructorHandlesTypePromotion)
{
    // Arrange
    math::Matrix3D<float> mat;

    // Act
    math::Matrix3D<double> copy(mat);
    copy(0, 0) = 5.0;

    // Assert
    static_assert(std::is_same_v<typename decltype(copy)::value_type, double>);
    EXPECT_MAT_IDENTITY(mat);

    EXPECT_DOUBLE_EQ(5.0f, copy(0, 0));
    for (std::size_t i = 1; i < size; ++i)
        EXPECT_DOUBLE_EQ(i % rowSize == i / rowSize,
                         copy(i / rowSize, i % rowSize)); // i % rowSize == i / rowSize => Gives diagonal entries as 1
}

TEST(Matrix3D_Access, CanBeAccessedAsAVectorAtIndex)
{
    // Arrange
    math::Matrix3D<float> mat;

    // Act
    math::Vector3D vec = mat[1];

    // Assert
    EXPECT_FLOAT_EQ(0.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(0.0f, vec.z);
}

TEST(Matrix3D_Access, CanBeAccessedAsAValueAtRowColumn)
{
    // Arrange & Act
    const math::Matrix3D mat(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);


    // Assert
    for (size_t i = 0; i < size; ++i)
        EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i / rowSize, i % rowSize));
}


/*********************************
 *                               *
 *  SIMPLE MATH OPERATION TESTS  *
 *                               *
 *********************************/

TEST(Matrix3D_Sum, SumOfTwoMatricesReturnsAnotherMatrixWithCorrectValues)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D b = { 3.0f, 2.0f, 255.0f, -8.0f, 24.0f, 6.0f, 7.0f, 16.0f, -98.0f };
    const math::Matrix3D c = { 4.0f, 4.0f, 258.0f, -4.0f, 29.0f, 12.0f, 14.0f, 8.0f, -89.0f };

    // Act
    const math::Matrix3D<float> res = a + b;

    // Assert
    EXPECT_MAT_EQ(c, res);
}

TEST(Matrix3D_Sum, PlusEqualsMatrixWithAnotherMatrixReturnsSameMatrixWithCorrectValues)
{
    // Arrange
    math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D b = { 3.0f, 2.0f, 255.0f, -8.0f, 24.0f, 6.0f, 7.0f, 16.0f, -98.0f };
    const math::Matrix3D c = { 4.0f, 4.0f, 258.0f, -4.0f, 29.0f, 12.0f, 14.0f, 8.0f, -89.0f };

    // Act
    a += b;

    // Assert
    EXPECT_MAT_EQ(c, a);
}

TEST(Matrix3D_Sum, SumOfTwoMatricesOfDifferentTypeReturnsAnotherMatrixPromotedType)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D b = { 3.0, 2.0, 255.0, -8.0, 24.0, 6.0, 7.0, 16.0, -98.0 };
    const math::Matrix3D c = { 4.0, 4.0, 258.0, -4.0, 29.0, 12.0, 14.0, 8.0, -89.0 };

    // Act
    const auto res = a + b;

    // Assert
    static_assert(std::is_same_v<typename decltype(res)::value_type, double>,
                  "Assertion Failed (Matrix3D): Float + Double = Double");
    EXPECT_MAT_EQ(c, res);
}

TEST(Matrix3D_Difference, DifferenceOfTwoMatricesReturnsAnotherMatrixWithCorrectValues)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D b = { 3.0f, 2.0f, 255.0f, -8.0f, 24.0f, 6.0f, 2.0f, 16.0f, -98.0f };
    const math::Matrix3D c = { -2.0f, 0.0f, -252.0f, 12.0f, -19.0f, 0.0f, 5.0f, -24.0f, 107.0f };

    // Act
    const math::Matrix3D<float> res = a - b;

    // Assert
    EXPECT_MAT_EQ(c, res);
}

TEST(Matrix3D_Difference, DifferenceOfTwoMatricesOfDifferentTypeReturnsAnotherMatrixPromotedType)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D b = { 3.0, 2.0, 255.0, -8.0, 24.0, 6.0, 2.0, 16.0, -98.0 };
    const math::Matrix3D c = { -2.0, 0.0, -252.0, 12.0, -19.0, 0.0, 5.0, -24.0, 107.0 };

    // Act
    const auto res = a - b;

    // Assert
    static_assert(std::is_same_v<typename decltype(res)::value_type, double>,
                  "Assertion Failed (Matrix3D): Float - Double = Double");
    EXPECT_MAT_EQ(c, res);
}

TEST(Matrix3D_Sum, PlusEqualsMatrixWithMatrixOfAnotherTypeReturnsSameMatrixWithoutTypePromotion)
{
    // Arrange
    math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D b = { 3.0, 2.0, 255.0, -8.0, 24.0, 6.0, 7.0, 16.0, -98.0 };
    const math::Matrix3D c = { 4.0f, 4.0f, 258.0f, -4.0f, 29.0f, 12.0f, 14.0f, 8.0f, -89.0f };

    // Act
    a += b;

    // Assert
    static_assert(std::is_same_v<typename decltype(a)::value_type, float>,
                  "Assertion Failed (Matrix3D): Float += Double = Float");
    EXPECT_MAT_EQ(c, a);
}

TEST(Matrix3D_Difference, MinusEqualsMatrixWithAnotherMatrixOfDifferentTypeReturnsSameMatrixWithoutTypePromotion)
{
    // Arrange
    math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D b = { 3.0, 2.0, 255.0, -8.0, 24.0, 6.0, 2.0, 16.0, -98.0 };
    const math::Matrix3D c = { -2.0f, 0.0f, -252.0f, 12.0f, -19.0f, 0.0f, 5.0f, -24.0f, 107.0f };

    // Act
    a -= b;

    // Assert
    static_assert(std::is_same_v<typename decltype(a)::value_type, float>,
                  "Assertion Failed (Matrix3D): Float -= Double = Float");
    EXPECT_MAT_EQ(c, a);
}

TEST(Matrix3D_Product, MatrixTimesAIntegerScalarReturnsCorrectMatrix)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D expected = { 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, -16.0f, 18.0f };
    constexpr int scalar = 2;

    // Act
    const math::Matrix3D actual = a * scalar;

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix3D_Product, IntegerScalarTimesAMatrixReturnsCorrectMatrix)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D expected = { 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, -16.0f, 18.0f };
    constexpr int scalar = 2;

    // Act
    const math::Matrix3D<float> actual = scalar * a;

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix3D_Product, MatrixTimesEqualIntegerScalarIsTheSameMatrixWithCorrectValues)
{
    // Arrange
    math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D b = { 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, -16.0f, 18.0f };
    constexpr int scalar = 2;

    // Act
    a *= scalar;

    // Assert
    EXPECT_MAT_EQ(a, b);
}

TEST(Matrix3D_Product, MatrixTimesOneReturnANewMatrixWithOriginalMatrixValues)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };

    // Act
    const math::Matrix3D<float> b = a * 1;

    // Assert
    EXPECT_MAT_EQ(a, b);
}

TEST(Matrix3D_Product, MatrixTimesZeroScalarReturnsZeroMatrix)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };

    // Act
    const math::Matrix3D<float> b = a * 0;

    // Assert
    EXPECT_MAT_ZERO(b);
}

TEST(Matrix3D_Product, MatrixTimesAFloatScalarReturnsCorrectMatrix)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    constexpr float scalar = 2.5f;

    const math::Matrix3D expected = { 2.5f, 5.0f, 7.5f, 10.0f, 12.5f, 15.0f, 17.5f, -20.0f, 22.5f };

    // Act
    const math::Matrix3D<float> b = a * scalar;

    // Assert
    EXPECT_MAT_EQ(expected, b);
}

TEST(Matrix3D_Product, IntegerMatrixTimesEqualAFloatScalarReturnsCorrectMatrixWithMinimalPrecisionLoss)
{
    // Arrange
    math::Matrix3D a = { 1, 2, 3, 4, 5, 6, 7, -8, 9 };
    constexpr float scalar = 2.5f;

    const math::Matrix3D expected = { 2, 5, 7, 10, 12, 15, 17, -20, 22 };

    // Act
    a *= scalar;

    // Assert
    EXPECT_MAT_EQ(expected, a);
}

TEST(Matrix3D_Product, MatrixTimesNegativeFloatScalarFlipsSigns)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, -2.0f, 0.0f, -4.0f, 5.0f, -6.0f, 0.0f, 8.0f, 9.0f };
    const math::Matrix3D expected = { -2.0f, 4.0f, 0.0f, 8.0f, -10.0f, 12.0f, 0.0f, -16.0f, -18.0f };
    constexpr float scalar = -2.0f;

    // Act
    const math::Matrix3D<float> b = a * scalar;

    // Assert
    EXPECT_MAT_EQ(expected, b);
}

TEST(Matrix3D_Product, MatrixTimesVectorReturnsANewMatrixWithCorrectValues)
{
    // Arrange
    const math::Matrix3D mat = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    const math::vec3 vec(2.0f, 1.0f, 3.0f);
    const math::vec3 expected(13.0f, 31.0f, 49.0f);

    // Act
    const math::vec3 actual = mat * vec;

    // Assert
    testutils::EXPECT_VEC_EQ(expected, actual);
}

TEST(Matrix3D_Product, IdentityMatrixTimesAVectorReturnsTheSameMatrix)
{
    // Arrange
    const math::Matrix3D<float> mat;
    const math::vec3 vec(2.0f, 1.0f, 3.0f);

    // Act
    const math::vec3 actual = mat * vec;

    // Assert
    testutils::EXPECT_VEC_EQ(vec, actual);
}

TEST(Matrix3D_Product, VectorTimesAMatrixReturnsANewVectorWithCorrectValues)
{
    // Arrange
    const math::Matrix3D mat = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    math::Vector3D vec(2.0f, 1.0f, 3.0f);
    const math::Vector3D expected(27.0f, 33.0f, 39.0f);

    // Act
    const auto actual = vec * mat;

    // Assert
    testutils::EXPECT_VEC_EQ(expected, actual);
}


TEST(Matrix3D_Product, VectorTimesIdentityMatrixReturnsTheSameMatrix)
{
    // Arrange
    const math::Matrix3D<float> mat;
    math::vec3 vec(2.0f, 1.0f, 3.0f);

    // Act
    const math::vec3 actual = vec * mat;

    // Assert
    testutils::EXPECT_VEC_EQ(vec, actual);
}

TEST(Matrix3D_Product, VectorTimesEqualMatrixReturnTheSameVectorWithNewValues)
{
    // Arrange
    const math::Matrix3D mat = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    math::vec3 vec(2.0f, 1.0f, 3.0f);
    const math::vec3 expected(27.0f, 33.0f, 39.0f);

    // Act
    vec *= mat;

    // Assert
    testutils::EXPECT_VEC_EQ(expected, vec);
}

TEST(Matrix3D_Product, MatrixTimesMatrixGivesAnotherMatrixWithCorrectValues)
{
    // Arrange
    const math::Matrix3D mat1 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    const math::Matrix3D mat2 = { 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0 };
    const math::Matrix3D expected = { 60.0f, 72.0f, 84.0f, 132.0f, 162.0f, 192.0f, 204.0f, 252.0f, 300.0f };

    // Act
    const math::Matrix3D actual = mat1 * mat2;

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix3D_Product, MatrixTimesIdentityMatrixReturnsSameMatrix)
{
    // Arrange
    const math::Matrix3D mat = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    const math::Matrix3D<float> eye;

    // Act
    const math::Matrix3D actual = mat * eye;

    // Assert
    EXPECT_MAT_EQ(mat, actual);
}

TEST(Matrix3D_Product, MatrixTimesEqualAnotherMatrixReturnsSameMatrixWithCorrectValues)
{
    // Arrange
    math::Matrix3D mat1 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    const math::Matrix3D mat2 = { 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f };
    const math::Matrix3D expected = { 60.0f, 72.0f, 84.0f, 132.0f, 162.0f, 192.0f, 204.0f, 252.0f, 300.0f };

    // Act
    mat1 *= mat2;

    // Assert
    EXPECT_MAT_EQ(expected, mat1);
}


TEST(Matrix3D_Product, Matrix3DProductIsAntiCommutative)
{
    // Arrange
    const math::Matrix3D mat1 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    const math::Matrix3D mat2 = { 3.0f, 6.0f, 3.0f, 12.0f, 0.0f, 2.0f, 15.0f, 11.0f, 6.0f };

    // Act
    const math::Matrix3D result1 = mat1 * mat2;
    const math::Matrix3D result2 = mat2 * mat1;

    // Assert
    bool commutative = true;
    for (std::size_t i = 0; i < size; i++)
    {
        commutative &= floatEquals(result1(i / rowSize, i % rowSize), result2(i / rowSize, i % rowSize));
    }
    EXPECT_FALSE(commutative);
}

TEST(Matrix3D_Product, Matrix3DProductWithScalarMultiplesAreCommutative)
{
    // Arrange
    const math::Matrix3D mat1 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    const math::Matrix3D mat2 = mat1 * 5.0f;

    // Act
    const math::Matrix3D result1 = mat1 * mat2;
    const math::Matrix3D result2 = mat2 * mat1;

    // Assert
    bool commutative = true;
    for (std::size_t i = 0; i < size; i++)
    {
        commutative &= floatEquals(result1(i / rowSize, i % rowSize), result2(i / rowSize, i % rowSize));
    }
    EXPECT_TRUE(commutative);
}

TEST(Matrix3D_Product, MatrixTimesADoubleScalarReturnsMatrixWithPromotedType)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    constexpr double scalar = 2.5;

    const math::Matrix3D expected = { 2.5, 5.0, 7.5, 10.0, 12.5, 15.0, 17.5, -20.0, 22.5 };

    // Act
    const auto b = a * scalar;

    // Assert
    static_assert(std::is_same_v<typename decltype(b)::value_type, double>,
                  "Assertion Failed (Matrix3D): Float * Double(Scalar) = Double");
    EXPECT_MAT_EQ(expected, b);
}

TEST(Matrix3D_Product, MatrixTimesEqualDoubleScalarReturnsMatrixWithoutTypePromotion)
{
    // Arrange
    math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    constexpr double scalar = 2.5;

    const math::Matrix3D expected = { 2.5, 5.0, 7.5, 10.0, 12.5, 15.0, 17.5, -20.0, 22.5 };

    // Act
    a *= scalar;

    // Assert
    static_assert(std::is_same_v<typename decltype(a)::value_type, float>,
                  "Assertion Failed (Matrix3D): Float * Double(Scalar) = Double");
    EXPECT_MAT_EQ(expected, a);
}

TEST(Matrix3D_Product, DoubleVectorTimesAMatrixReturnsANewVectorWithPromotedType)
{
    // Arrange
    const math::Matrix3D mat = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };

    math::dvec3 vec(2.0, 1.0, 3.0);
    const math::dvec3 expected(27.0, 33.0, 39.0);

    // Act
    const math::dvec3 actual = vec * mat;

    // Assert
    static_assert(std::is_same_v<typename decltype(actual)::value_type, double>,
                  "Assertion Failed (Matrix3D): Float * Double(vec) = Double");
    testutils::EXPECT_VEC_EQ(expected, actual);
}

TEST(Matrix3D_Product, DoubleVectorTimesEqualAMatrixReturnsANewVectorWithPromotedType)
{
    // Arrange
    const math::Matrix3D mat = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };

    math::vec3 vec(2.0f, 1.0f, 3.0f);
    const math::dvec3 expected(27.0, 33.0, 39.0);

    // Act
    vec *= mat;

    // Assert
    static_assert(std::is_same_v<typename decltype(vec)::value_type, float>,
                  "Assertion Failed (Matrix3D): Float(vec) * Double = Float");
    testutils::EXPECT_VEC_EQ(expected, vec);
}

TEST(Matrix3D_Product, MatrixTimesMatrixGivesAnotherMatrixWithTypePromotion)
{
    // Arrange
    const math::Matrix3D mat1 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    const math::Matrix3D mat2 = { 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0 };
    const math::Matrix3D expected = { 60.0, 72.0, 84.0, 132.0, 162.0, 192.0, 204.0, 252.0, 300.0 };

    // Act
    const math::Matrix3D actual = mat1 * mat2;

    // Assert
    static_assert(std::is_same_v<typename decltype(actual)::value_type, double>,
                  "Assertion Failed (Matrix3D): Float * Double = Double");
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix3D_Product, MatrixTimesEqualAnotherMatrixReturnsSameMatrixWithoutTypePromotion)
{
    // Arrange
    math::Matrix3D mat1 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    const math::Matrix3D mat2 = { 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0 };
    const math::Matrix3D expected = { 60.0, 72.0, 84.0, 132.0, 162.0, 192.0, 204.0, 252.0, 300.0 };

    // Act
    mat1 *= mat2;

    // Assert
    static_assert(std::is_same_v<typename decltype(mat1)::value_type, float>,
                  "Assertion Failed (Matrix3D): Float *= Double = Float");
    EXPECT_MAT_EQ(expected, mat1);
}


TEST(Matrix3D_Division, MatrixDividedByAIntegerScalarReturnsCorrectMatrix)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D expected = { 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, -4.0f, 4.5f };
    constexpr int scalar = 2;

    // Act
    const math::Matrix3D<float> actual = a / scalar;

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix3D_Division, MatrixDividesEqualIntegerScalarIsTheSameMatrixWithCorrectValues)
{
    // Arrange
    math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D b = { 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, -4.0f, 4.5f };
    constexpr int scalar = 2;

    // Act
    a /= scalar;

    // Assert
    EXPECT_MAT_EQ(b, a);
}

TEST(Matrix3D_Division, MatrixDividedByOneReturnANewMatrixWithOriginalMatrixValues)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };

    // Act
    const math::Matrix3D<float> b = a / 1;

    // Assert
    EXPECT_MAT_EQ(a, b);
}

TEST(Matrix3D_Division, MatrixDividedByZeroScalarReturnsInfinityMatrix)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };

    // Act
    const math::Matrix3D<float> b = a / 0;

    // Assert
    EXPECT_MAT_INF(b);
}

TEST(Matrix3D_Division, MatrixDividedByAFloatScalarReturnsCorrectMatrix)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };

    const math::Matrix3D expected = { 0.4f, 0.8f, 1.2f, 1.6f, 2.0f, 2.4f, 2.8f, -3.2f, 3.6f };

    constexpr float scalar = 2.5f;

    // Act
    const math::Matrix3D<float> actual = a / scalar;

    // Assert
    EXPECT_MAT_NEAR(expected, actual);
}

TEST(Matrix3D_Division, MatrixDividedNegativeFloatScalarFlipsSigns)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, -2.0f, 22.0f, -4.0f, 5.0f, -6.0f, 4.0f, 8.0f, 9.0f };
    const math::Matrix3D expected = { -0.5f, 1.0f, -11.0f, 2.0f, -2.5f, 3.0f, -2.0f, -4.0f, -4.5f };
    constexpr float scalar = -2.0f;

    // Act
    const math::Matrix3D<float> actual = a / scalar;

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix3D_Division, MatrixDividedByDoubleScalarReturnsMatrixWithTypePromotion)
{
    // Arrange
    const math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D expected = { 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, -4.0, 4.5 };
    constexpr double scalar = 2.0;

    // Act
    const auto actual = a / scalar;

    // Assert
    static_assert(std::is_same_v<typename decltype(actual)::value_type, double>,
                  "Assertion Failed (Matrix3D): Float / Double = Double");
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix3D_Division, MatrixDividesEqualDoubleScalarIsTheSameMatrixWithoutTypePromotion)
{
    // Arrange
    math::Matrix3D a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, -8.0f, 9.0f };
    const math::Matrix3D b = { 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, -4.0f, 4.5f };
    constexpr double scalar = 2.0;

    // Act
    a /= scalar;

    // Assert
    static_assert(std::is_same_v<typename decltype(a)::value_type, float>,
                  "Assertion Failed (Matrix3D): Float /= Double = Float");
    EXPECT_MAT_EQ(b, a);
}

TEST(Matrix3D_Division, IntegerMatrixDivideEqualFloatScalarIsTheSameMatrixWithMinimalPrecisionLoss)
{
    // Arrange
    math::Matrix3D a = { 1, 2, 3, 4, 5, 6, 7, -8, 9 };
    const math::Matrix3D b = { 4, 8, 12, 16, 20, 24, 28, -32, 36 };
    constexpr float scalar = 0.25f;

    // Act
    a /= scalar;

    // Assert
    EXPECT_MAT_EQ(b, a);
}


/***********************
 *                     *
 *  DETERMINANT TESTS  *
 *                     *
 ***********************/

TEST(Matrix3D_Determinant, IdentityMatrixReturnsDeterminantOfOne)
{
    // Arrange
    const math::Matrix3D<float> mat;
    constexpr float expectedDeterminant = 1.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D_Determinant, DiagonalMatrixReturnsProductOfDiagonalEntriesAsDeterminant)
{
    // Arrange
    const math::Matrix3D mat(2.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 4.0f);
    constexpr float expectedDeterminant = 24.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D_Determinant, MatrixWithScalarMultipleColumnsReturnsDeterminantOfZero)
{
    const math::Matrix3D mat(2.0f, 1.0f, 3.0f, 4.0f, 2.0f, 6.0f, 1.0f, 5.0f, 4.0f);

    constexpr float expectedDeterminant = 0.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D_Determinant, MatrixWithScalarMultipleRowsReturnsDeterminantOfZero)
{
    const math::Matrix3D mat(2.0f, 4.0f, 3.0f, 4.0f, 8.0f, 6.0f, 1.0f, 2.0f, 4.0f);

    constexpr float expectedDeterminant = 0.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D_Determinant, IdentityMatrixWithSwappedRowsReturnsDeterminantOfNegativeOne)
{
    const math::Matrix3D mat(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

    constexpr float expectedDeterminant = -1.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D_Determinant, IdentityMatrixWithSwappedColumnsReturnsDeterminantOfNegativeOne)
{
    const math::Matrix3D mat(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

    constexpr float expectedDeterminant = -1.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D_Determinant, IdentityMatrixWithShearAppliedsReturnsDeterminantOfOne)
{
    const math::Matrix3D mat(1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    constexpr float expectedDeterminant = 1.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D_Determinant, MatrixDeterminantReturnsCorrectValue)
{
    const math::Matrix3D mat(1.0f, 2.0f, 3.0f, 0.0f, 4.0f, 1.0f, 5.0f, 6.0f, 0.0f);

    constexpr float expectedDeterminant = -56.0f;

    // Act
    const float actualDeterminant = mat.determinant();

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D_Determinant, MatrixDeterminantWithStaticWrapperReturnsCorrectValue)
{
    const math::Matrix3D mat(1.0f, 2.0f, 3.0f, 0.0f, 4.0f, 1.0f, 5.0f, 6.0f, 0.0f);

    constexpr float expectedDeterminant = -56.0f;

    // Act
    const float actualDeterminant = math::Matrix3D<float>::determinant(mat);

    // Assert
    EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
}

TEST(Matrix3D_Determinant, DeterminantofTransposedMatrixIsEqualToDeterminantOfTheMatrix)
{
    const math::Matrix3D a(1.0f, 2.0f, 3.0f, 0.0f, 4.0f, 1.0f, 5.0f, 6.0f, 0.0f);

    // Act
    const float detA = a.determinant();
    const float detAT = a.transpose().determinant();

    // Assert
    EXPECT_FLOAT_EQ(detA, detAT);
}

TEST(Matrix3D_Determinant, DeterminantOfProductOfMatricesIsSameAsProductOfDeterminantOfMatrix)
{
    // det(A*B) = det(A) * det(B)
    const math::Matrix3D a(1.0f, 2.0f, 3.0f, 0.0f, 4.0f, 1.0f, 5.0f, 6.0f, 0.0f);
    const math::Matrix3D b(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

    // Act
    const float determinantOfProduct = math::Matrix3D<float>::determinant(a * b);
    const float productOfDeterminant = a.determinant() * b.determinant();

    // Assert
    EXPECT_FLOAT_EQ(determinantOfProduct, productOfDeterminant);
}

TEST(Matrix3D_Determinant, DeterminantOfAMatrixMultipledByScalarIsScalarPowNTimesTheDeterminantOfOriginalMatrix)
{
    // det(t*A) = (t^n)det(A)
    const math::Matrix3D a(1.0f, 2.0f, 3.0f, 0.0f, 4.0f, 1.0f, 5.0f, 6.0f, 0.0f);
    constexpr float scalar = 5.0f;

    // Act
    const float determinantOfProduct = math::Matrix3D<float>::determinant(scalar * a);
    const float productOfDeterminant = (scalar * scalar * scalar) * a.determinant(); // n = 3 for 3x3 matrix

    // Assert
    EXPECT_FLOAT_EQ(determinantOfProduct, productOfDeterminant);
}


/*********************
 *                   *
 *  TRANSPOSE TESTS  *
 *                   *
 *********************/

TEST(Matrix3D_Transpose, TransposeOfIdentityMatrixIsItself)
{
    // Arrange
    const math::Matrix3D<float> mat;

    // Act
    const math::Matrix3D<float> actual = mat.transpose();

    // Assert
    EXPECT_MAT_EQ(mat, actual);
}

TEST(Matrix3D_Transpose, TransposeOfAMatrixReturnsMatrixWithRowsAndColumnsSwapped)
{
    // Arrange
    const math::Matrix3D mat(1.0f, 2.0f, 3.0f, 0.0f, 4.0f, 1.0f, 5.0f, 6.0f, 0.0f);
    const math::Matrix3D expected(1.0f, 0.0f, 5.0f, 2.0f, 4.0f, 6.0f, 3.0f, 1.0f, 0.0f);

    // Act
    const math::Matrix3D<float> actual = mat.transpose();

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}

TEST(Matrix3D_Transpose, TransposeOfAMatrixUsingStaticWrapperReturnsMatrixWithRowsAndColumnsSwapped)
{
    // Arrange
    const math::Matrix3D mat(1.0f, 2.0f, 3.0f, 0.0f, 4.0f, 1.0f, 5.0f, 6.0f, 0.0f);
    const math::Matrix3D expected(1.0f, 0.0f, 5.0f, 2.0f, 4.0f, 6.0f, 3.0f, 1.0f, 0.0f);

    // Act
    const math::Matrix3D<float> actual = math::Matrix3D<float>::transpose(mat);

    // Assert
    EXPECT_MAT_EQ(expected, actual);
}


/*******************
 *                 *
 *  INVERSE TESTS  *
 *                 *
 *******************/

TEST(Matrix3D_Inverse, InverseReturnsAnotherMatrixWithCorrectValues)
{
    // Given
    const math::Matrix3D mat(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);
    const math::Matrix3D expectedInverse(-24.0f, 18.0f, 5.0f, 20.0f, -15.0f, -4.0f, -5.0f, 4.0f, 1.0f);

    // Act
    const math::Matrix3D actualInverse = mat.inverse();

    // Assert
    EXPECT_MAT_EQ(expectedInverse, actualInverse);
}

TEST(Matrix3D_Inverse, StaticWrapperForInverseReturnsAnotherMatrixWithCorrectValues)
{
    const math::Matrix3D mat(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);
    const math::Matrix3D expectedInverse(-24.0f, 18.0f, 5.0f, 20.0f, -15.0f, -4.0f, -5.0f, 4.0f, 1.0f);

    // Act
    const math::Matrix3D<float> actualInverse = math::Matrix3D<float>::inverse(mat);

    // Assert
    EXPECT_MAT_EQ(expectedInverse, actualInverse);
}

TEST(Matrix3D_Inverse, IdentityMatrixInverseReturnsAnotherIdentityMatrix)
{
    // Given
    const math::Matrix3D<float> identity;

    // Act
    const math::Matrix3D<float> actualInverse = identity.inverse();

    // Assert
    EXPECT_MAT_IDENTITY(actualInverse);
}

TEST(Matrix3D_Inverse, MatrixTimeInverseReturnsIdentityMatrix)
{
    const math::Matrix3D mat(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);

    // Act
    const math::Matrix3D<float> inverse = math::Matrix3D<float>::inverse(mat);
    const math::Matrix3D<float> product = mat * inverse;

    // Assert
    EXPECT_MAT_IDENTITY(product);
}

TEST(Matrix3D_Inverse, InverseTimesMatrixReturnsIdentityMatrix)
{
    const math::Matrix3D mat(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);

    // Act
    const math::Matrix3D<float> inverse = math::Matrix3D<float>::inverse(mat);
    const math::Matrix3D<float> product = inverse * mat;

    // Assert
    EXPECT_MAT_IDENTITY(product);
}

TEST(Matrix3D_Inverse, SingularMatrixProducesIdentityMatrix)
{
    const math::Matrix3D singularMatrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    // Act
    const math::Matrix3D<float> actualInverse = math::Matrix3D<float>::inverse(singularMatrix);

    // Assert
    EXPECT_MAT_IDENTITY(actualInverse);
}

TEST(Matrix3D_Inverse, NearSingularMatrixProducesNonIdentityMatrix)
{
    const math::Matrix3D nearSingularMatrix(1.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f, 0.0f, 0.1f);

    const math::Matrix3D expectedInverse(1.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 10.0f);

    // Act
    const math::Matrix3D<float> actualInverse = math::Matrix3D<float>::inverse(nearSingularMatrix);

    // Assert
    EXPECT_MAT_NEAR(expectedInverse, actualInverse);
}

TEST(Matrix3D_Inverse, InversionOfRotationOnlyMatrixReturnsTranspose)
{
    const math::Matrix3D mat(0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    const math::Matrix3D transpose(0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    // Act
    const math::Matrix3D<float> actualInverse = math::Matrix3D<float>::inverse(mat);

    // Assert
    EXPECT_MAT_EQ(transpose, actualInverse);
}