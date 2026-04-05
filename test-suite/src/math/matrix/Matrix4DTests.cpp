#include "utils/FloatEquals.h"
#include "utils/MatrixUtils.h"
#include "utils/VectorUtils.h"

#include <cstddef>
#include <gtest/gtest.h>
#include <matrix/Matrix4D.h>
#include <vector/Vector3D.h>

using namespace testutils;
// TODO: Add test for integer precision on multiplication -> [[2]] * 2.5 = [[5]] not 4


/***********************************************
 *                                             *
 *  INITIALIZATION, ACCESS AND MUTATION TESTS  *
 *                                             *
 ***********************************************/

static constexpr std::size_t rows = fgm::Matrix4D<float>::rows;
static constexpr std::size_t cols = fgm::Matrix4D<float>::columns;

TEST(Matrix4D_Initialization, InitializedWithOutParametersProvidesIdentityMatrix)
{
    // Given a matrix initialized without parameters
    const fgm::Matrix4D<float> mat;

    // Then, it's elements form an identity matrix
    EXPECT_MAT_IDENTITY(mat);
}

TEST(Matrix4D_Initialization, InitializationSupportedForIntegers)
{
    // Given an integer matrix initialized without parameters
    const fgm::Matrix4D<int> mat;

    // Then, it's value_type is int, and elements form an identity matrix
    static_assert(std::is_same_v<typename decltype(mat)::value_type, int>);
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            EXPECT_EQ(i == j, mat.elements[i][j]); // TODO: Replace with accessor
}

TEST(Matrix4D_Initialization, InitializedWithParametersProvidesCorrectMatrix)
{
    // Given a matrix with arbitrary values passed in
    const fgm::Matrix4D mat(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f,
                            14.0f, 15.0f);

    // Then, it's elements reflect the correct values
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            EXPECT_FLOAT_EQ(static_cast<float>((i * rows) + j), mat(i, j)); // TODO: Replace with accessor
}

TEST(Matrix4D_Initialization, InitializedWithFour4DVectorsProvidesCorrectMatrix)
{
    // Given four 4D vectors
    const fgm::Vector4D col0(0.0f, 4.0f, 8.0f, 12.0f);
    const fgm::Vector4D col1(1.0f, 5.0f, 9.0f, 13.0f);
    const fgm::Vector4D col2(2.0f, 6.0f, 10.0f, 14.0f);
    const fgm::Vector4D col3(3.0f, 7.0f, 11.0f, 15.0f);

    // When a matrix is initialized with those vectors
    const fgm::Matrix4D mat(col0, col1, col2, col3);


    // Then, it's elements reflect the vectors put in column major order
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            EXPECT_FLOAT_EQ(static_cast<float>((i * rows) + j), mat(i, j));
}

TEST(Matrix4D_Initialization, CanMutateVectorAtIndex)
{
    // Given an identity matrix and a vector
    fgm::Matrix4D<float> mat;
    fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // When the vector is put into the matrices column
    mat[2] = vec;

    // Then, it's value reflect that change
    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(0.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 2));
    EXPECT_FLOAT_EQ(0.0f, mat(0, 3));

    EXPECT_FLOAT_EQ(0.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(1.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(1.0f, mat(1, 2));
    EXPECT_FLOAT_EQ(0.0f, mat(1, 3));

    EXPECT_FLOAT_EQ(0.0f, mat(2, 0));
    EXPECT_FLOAT_EQ(0.0f, mat(2, 1));
    EXPECT_FLOAT_EQ(6.0f, mat(2, 2));
    EXPECT_FLOAT_EQ(0.0f, mat(2, 3));

    EXPECT_FLOAT_EQ(0.0f, mat(3, 0));
    EXPECT_FLOAT_EQ(0.0f, mat(3, 1));
    EXPECT_FLOAT_EQ(2.0f, mat(3, 2));
    EXPECT_FLOAT_EQ(1.0f, mat(3, 3));
}

TEST(Matrix4D_Initialization, CanMutateValueAtRowColumn)
{
    // Given an identity matrix
    fgm::Matrix4D<float> mat;

    // When populated with elements using loop indices at (row, col)
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            mat(i, j) = static_cast<float>(i);

    // Then, matrix is populated with correct value
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            EXPECT_FLOAT_EQ(static_cast<float>(i), mat(i, j));
}

TEST(Matrix4D_Initialization, ConversionConstructorHandlesTypePromotion)
{
    // Given a float matrix
    fgm::Matrix4D<float> mat;

    // When copied to a double matrix
    fgm::Matrix4D<double> copy(mat);
    // And some value of the new matrix mutated
    copy(0, 0) = 5.0;
    copy(0, 1) = 4.0;
    copy(0, 2) = 3.0;
    copy(0, 3) = 2.0;

    // Then, the double matrix remains unchanged
    EXPECT_MAT_IDENTITY(mat);

    // And, the new matrix is of type float with the mutated value
    static_assert(std::is_same_v<typename decltype(copy)::value_type, double>);

    EXPECT_DOUBLE_EQ(5.0, copy(0, 0));
    EXPECT_DOUBLE_EQ(4.0, copy(0, 1));
    EXPECT_DOUBLE_EQ(3.0, copy(0, 2));
    EXPECT_DOUBLE_EQ(2.0, copy(0, 3));

    for (std::size_t i = 1; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            EXPECT_DOUBLE_EQ(i == j, copy(i, j));
}

TEST(Matrix4D_Initialization, ConversionConstructorHandlesTypeDemotion)
{
    // Given a double matrix
    fgm::Matrix4D<double> mat;

    // When copied to a float matrix
    fgm::Matrix4D<float> copy(mat);
    // And some value of the new matrix mutated
    copy(0, 0) = 5.0f;
    copy(0, 1) = 4.0f;
    copy(0, 2) = 3.0f;
    copy(0, 3) = 2.0f;

    // Then, the double matrix remains unchanged
    EXPECT_MAT_IDENTITY(mat);

    // And, the new matrix is of type float with the mutated value
    static_assert(std::is_same_v<typename decltype(copy)::value_type, float>);

    EXPECT_FLOAT_EQ(5.0f, copy(0, 0));
    EXPECT_FLOAT_EQ(4.0f, copy(0, 1));
    EXPECT_FLOAT_EQ(3.0f, copy(0, 2));
    EXPECT_FLOAT_EQ(2.0f, copy(0, 3));

    for (std::size_t i = 1; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            EXPECT_FLOAT_EQ(i == j, copy(i, j));
}

TEST(Matrix4D_Access, CanBeAccessedAsAVectorAtIndex)
{
    // Given an identity matrix
    fgm::Matrix4D<float> mat;

    // When accessed by index[] operator
    fgm::Vector4D vec = mat[1];

    // Returns a vector with the correct value
    EXPECT_FLOAT_EQ(0.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
    EXPECT_FLOAT_EQ(0.0f, vec.z());
    EXPECT_FLOAT_EQ(0.0f, vec.w());
}

TEST(Matrix4D_Access, CanBeAccessedAsAValueAtRowColumn)
{
    // Given a matrix initialized with arbitrary values
    const fgm::Matrix4D mat(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f,
                            14.0f, 15.0f);

    // Then, its elements can be accessed using (row, col)
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            EXPECT_FLOAT_EQ(static_cast<float>(i * rows + j), mat(i, j));
}


/*********************************
 *                               *
 *  SIMPLE MATH OPERATION TESTS  *
 *                               *
 *********************************/

TEST(Matrix4D_Addition, SumOfTwoMatricesReturnsAnotherMatrixWithCorrectValues)
{
    // Given two matrices with arbitrary values
    const fgm::Matrix4D a = { 1.0f, 2.0f,  3.0f, 5.0f, 4.0f,  5.0f,  6.0f,  2.0f,
                              7.0f, -8.0f, 9.0f, 8.0f, 12.0f, -3.0f, -20.f, 2.0f };
    const fgm::Matrix4D b = { 3.0f, 2.0f,  255.0f, 55.0f, -8.0f, 24.0f, 6.0f,  -23.0f,
                              7.0f, 16.0f, -98.0f, 11.0f, 1.0f,  55.0f, 11.0f, -316.0f };

    const fgm::Matrix4D expected = { 4.0f,  4.0f, 258.0f, 60.0f, -4.0f, 29.0f, 12.0f, -21.0f,
                                     14.0f, 8.0f, -89.0f, 19.0f, 13.0f, 52.0f, -9.0f, -314.0f };

    // When they are added together
    const fgm::Matrix4D result = a + b;

    // Then, the result is the sum of individual elements
    EXPECT_MAT_EQ(expected, result);
}

TEST(Matrix4D_Addition, PlusEqualsMatrixWithAnotherMatrixReturnsSameMatrixWithCorrectValues)
{

    // Given two matrices with arbitrary values
    fgm::Matrix4D a = { 1.0f, 2.0f,  3.0f, 5.0f, 4.0f,  5.0f,  6.0f,  2.0f,
                        7.0f, -8.0f, 9.0f, 8.0f, 12.0f, -3.0f, -20.f, 2.0f };

    const fgm::Matrix4D b = { 3.0f, 2.0f,  255.0f, 55.0f, -8.0f, 24.0f, 6.0f,  -23.0f,
                              7.0f, 16.0f, -98.0f, 11.0f, 1.0f,  55.0f, 11.0f, -316.0f };

    const fgm::Matrix4D expected = { 4.0f,  4.0f, 258.0f, 60.0f, -4.0f, 29.0f, 12.0f, -21.0f,
                                     14.0f, 8.0f, -89.0f, 19.0f, 13.0f, 52.0f, -9.0f, -314.0f };

    // When one matrix is added to the other(+=)
    a += b;

    // Then, the original matrix contains the sum of the elements added together
    EXPECT_MAT_EQ(expected, a);
}

TEST(Matrix4D_Addition, SumOfTwoMatricesOfDifferentTypeReturnsAnotherMatrixWithTypePromotion)
{
    // Given two matrices with arbitrary values and different types
    const fgm::Matrix4D a = { 1.0f, 2.0f,  3.0f, 5.0f, 4.0f,  5.0f,  6.0f,  2.0f,
                              7.0f, -8.0f, 9.0f, 8.0f, 12.0f, -3.0f, -20.f, 2.0f };

    const fgm::Matrix4D b = { 3.0, 2.0,  255.0, 55.0, -8.0, 24.0, 6.0,  -23.0,
                              7.0, 16.0, -98.0, 11.0, 1.0,  55.0, 11.0, -316.0 };

    const fgm::Matrix4D expected = { 4.0,  4.0, 258.0, 60.0, -4.0, 29.0, 12.0, -21.0,
                                     14.0, 8.0, -89.0, 19.0, 13.0, 52.0, -9.0, -314.0 };

    // When they are added together
    const auto result = a + b;

    // Then, the type of the resultant matrix is of the larger of the two type
    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
    // And, the result is the sum of individual elements
    EXPECT_MAT_EQ(expected, result);
}

TEST(Matrix4D_Addition, PlusEqualsMatrixWithAnotherMatrixOfDifferentTypeReturnsSameMatrixWithoutTypePromotion)
{
    // Given two matrices with arbitrary values with different types
    fgm::Matrix4D a = { 1.0f, 2.0f,  3.0f, 5.0f, 4.0f,  5.0f,  6.0f,  2.0f,
                        7.0f, -8.0f, 9.0f, 8.0f, 12.0f, -3.0f, -20.f, 2.0f };

    const fgm::Matrix4D b = { 3.0, 2.0,  255.0, 55.0, -8.0, 24.0, 6.0,  -23.0,
                              7.0, 16.0, -98.0, 11.0, 1.0,  55.0, 11.0, -316.0 };

    const fgm::Matrix4D expected = { 4.0f,  4.0f, 258.0f, 60.0f, -4.0f, 29.0f, 12.0f, -21.0f,
                                     14.0f, 8.0f, -89.0f, 19.0f, 13.0f, 52.0f, -9.0f, -314.0f };

    // When one matrix is added to the other(+=)
    a += b;

    // Then, the type of the original matrix is preserved
    static_assert(std::is_same_v<typename decltype(a)::value_type, float>);
    // And, the original matrix contains the sum of the elements added together
    EXPECT_MAT_EQ(expected, a);
}

// TEST(Matrix4D_Difference, DifferenceOfTwoMatricesReturnsAnotherMatrixWithCorrectValues)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	const fgm::Matrix4D b = {
//		3.0f, 2.0f, 255.0f,
//		-8.0f, 24.0f, 6.0f,
//		2.0f, 16.0f, -98.0f };
//	const fgm::Matrix4D c = {
//		-2.0f, 0.0f, -252.0f,
//		12.0f, -19.0f, 0.0f,
//		5.0f, -24.0f, 107.0f };
//
//	// Act
//	const fgm::Matrix4D<float> res = a - b;
//
//	// Assert
//	EXPECT_MAT_EQ(c, res);
// }

// TEST(Matrix4D_Difference, DifferenceOfTwoMatricesOfDifferentTypeReturnsAnotherMatrixPromotedType)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	const fgm::Matrix4D b = {
//		3.0, 2.0, 255.0,
//		-8.0, 24.0, 6.0,
//		2.0, 16.0, -98.0 };
//	const fgm::Matrix4D c = {
//		-2.0, 0.0, -252.0,
//		12.0, -19.0, 0.0,
//		5.0, -24.0, 107.0 };
//
//	// Act
//	const auto res = a - b;
//
//	// Assert
//	static_assert(std::is_same_v<typename decltype(res)::value_type, double>, "Assertion Failed (Matrix4D): Float -
// Double = Double"); 	EXPECT_MAT_EQ(c, res);
// }
//
// TEST(Matrix4D_Addition, PlusEqualsMatrixWithMatrixOfAnotherTypeReturnsSameMatrixWithoutTypePromotion)
//{
//	// Arrange
//	fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	const fgm::Matrix4D b = {
//		3.0, 2.0, 255.0,
//		-8.0, 24.0, 6.0,
//		7.0, 16.0, -98.0 };
//	const fgm::Matrix4D c = {
//		4.0f, 4.0f, 258.0f,
//		-4.0f, 29.0f, 12.0f,
//		14.0f, 8.0f, -89.0f };
//
//	// Act
//	a += b;
//
//	// Assert
//	static_assert(std::is_same_v<typename decltype(a)::value_type, float>, "Assertion Failed (Matrix4D): Float += Double
//= Float"); 	EXPECT_MAT_EQ(c, a);
// }
//
// TEST(Matrix4D_Difference, MinusEqualsMatrixWithAnotherMatrixOfDifferentTypeReturnsSameMatrixWithoutTypePromotion)
//{
//	// Arrange
//	fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	const fgm::Matrix4D b = {
//		3.0, 2.0, 255.0,
//		-8.0, 24.0, 6.0,
//		2.0, 16.0, -98.0 };
//	const fgm::Matrix4D c = {
//		-2.0f, 0.0f, -252.0f,
//		12.0f, -19.0f, 0.0f,
//		5.0f, -24.0f, 107.0f };
//
//	// Act
//	a -= b;
//
//	// Assert
//	static_assert(std::is_same_v<typename decltype(a)::value_type, float>, "Assertion Failed (Matrix4D): Float -= Double
//= Float"); 	EXPECT_MAT_EQ(c, a);
// }
//
// TEST(Matrix4D_Product, MatrixTimesAIntegerScalarReturnsCorrectMatrix)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	const fgm::Matrix4D expected = {
//		2.0f, 4.0f, 6.0f,
//		8.0f, 10.0f, 12.0f,
//		14.0f, -16.0f, 18.0f };
//	constexpr int scalar = 2;
//
//	// Act
//	const fgm::Matrix4D actual = a * scalar;
//
//	// Assert
//	EXPECT_MAT_EQ(expected, actual);
// }
//
// TEST(Matrix4D_Product, IntegerScalarTimesAMatrixReturnsCorrectMatrix)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	const fgm::Matrix4D expected = {
//		2.0f, 4.0f, 6.0f,
//		8.0f, 10.0f, 12.0f,
//		14.0f, -16.0f, 18.0f };
//	constexpr int scalar = 2;
//
//	// Act
//	const fgm::Matrix4D<float> actual = scalar * a;
//
//	// Assert
//	EXPECT_MAT_EQ(expected, actual);
// }
//
// TEST(Matrix4D_Product, MatrixTimesEqualIntegerScalarIsTheSameMatrixWithCorrectValues)
//{
//	// Arrange
//	fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	const fgm::Matrix4D b = {
//		2.0f, 4.0f, 6.0f,
//		8.0f, 10.0f, 12.0f,
//		14.0f, -16.0f, 18.0f };
//	constexpr int scalar = 2;
//
//	// Act
//	a *= scalar;
//
//	// Assert
//	EXPECT_MAT_EQ(a, b);
// }
//
// TEST(Matrix4D_Product, MatrixTimesOneReturnANewMatrixWithOriginalMatrixValues)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//
//	// Act
//	const fgm::Matrix4D<float> b = a * 1;
//
//	// Assert
//	EXPECT_MAT_EQ(a, b);
// }
//
// TEST(Matrix4D_Product, MatrixTimesZeroScalarReturnsZeroMatrix)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//
//	// Act
//	const fgm::Matrix4D<float> b = a * 0;
//
//	// Assert
//	EXPECT_MAT_ZERO(b);
// }
//
// TEST(Matrix4D_Product, MatrixTimesAFloatScalarReturnsCorrectMatrix)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	constexpr float scalar = 2.5f;
//
//	const fgm::Matrix4D expected = {
//		2.5f, 5.0f, 7.5f,
//		10.0f, 12.5f, 15.0f,
//		17.5f, -20.0f, 22.5f };
//
//	// Act
//	const fgm::Matrix4D<float> b = a * scalar;
//
//	// Assert
//	EXPECT_MAT_EQ(expected, b);
// }
//
// TEST(Matrix4D_Product, IntegerMatrixTimesEqualAFloatScalarReturnsCorrectMatrixWithMinimalPrecisionLoss)
//{
//	// Arrange
//	fgm::Matrix4D a = {
//		1, 2, 3,
//		4, 5, 6,
//		7, -8, 9 };
//	constexpr float scalar = 2.5f;
//
//	const fgm::Matrix4D expected = {
//		2, 5, 7,
//		10, 12, 15,
//		17, -20, 22 };
//
//	// Act
//	a *= scalar;
//
//	// Assert
//	EXPECT_MAT_EQ(expected, a);
// }
//
// TEST(Matrix4D_Product, MatrixTimesNegativeFloatScalarFlipsSigns)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, -2.0f, 0.0f,
//		-4.0f, 5.0f, -6.0f,
//		0.0f, 8.0f, 9.0f };
//	const fgm::Matrix4D expected = {
//		-2.0f, 4.0f, 0.0f,
//		8.0f, -10.0f, 12.0f,
//		0.0f, -16.0f, -18.0f };
//	constexpr float scalar = -2.0f;
//
//	// Act
//	const fgm::Matrix4D<float> b = a * scalar;
//
//	// Assert
//	EXPECT_MAT_EQ(expected, b);
// }
//
// TEST(Matrix4D_Product, MatrixTimesVectorReturnsANewMatrixWithCorrectValues)
//{
//	// Arrange
//	const fgm::Matrix4D mat = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f };
//	const fgm::vec3 vec(2.0f, 1.0f, 3.0f);
//	const fgm::vec3 expected(13.0f, 31.0f, 49.0f);
//
//	// Act
//	const fgm::vec3 actual = mat * vec;
//
//	// Assert
//	testutils::EXPECT_VEC_EQ(expected, actual);
// }
//
// TEST(Matrix4D_Product, IdentityMatrixTimesAVectorReturnsTheSameMatrix)
//{
//	// Arrange
//	const fgm::Matrix4D<float> mat;
//	const fgm::vec3 vec(2.0f, 1.0f, 3.0f);
//
//	// Act
//	const fgm::vec3 actual = mat * vec;
//
//	// Assert
//	testutils::EXPECT_VEC_EQ(vec, actual);
// }
//
// TEST(Matrix4D_Product, VectorTimesAMatrixReturnsANewVectorWithCorrectValues)
//{
//	// Arrange
//	const fgm::Matrix4D mat = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f };
//	fgm::Vector3D vec(2.0f, 1.0f, 3.0f);
//	const fgm::Vector3D expected(27.0f, 33.0f, 39.0f);
//
//	// Act
//	const auto actual = vec * mat;
//
//	// Assert
//	testutils::EXPECT_VEC_EQ(expected, actual);
// }
//
//
// TEST(Matrix4D_Product, VectorTimesIdentityMatrixReturnsTheSameMatrix)
//{
//	// Arrange
//	const fgm::Matrix4D<float> mat;
//	fgm::vec3 vec(2.0f, 1.0f, 3.0f);
//
//	// Act
//	const fgm::vec3 actual = vec * mat;
//
//	// Assert
//	testutils::EXPECT_VEC_EQ(vec, actual);
// }
//
// TEST(Matrix4D_Product, VectorTimesEqualMatrixReturnTheSameVectorWithNewValues)
//{
//	// Arrange
//	const fgm::Matrix4D mat = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f };
//	fgm::vec3 vec(2.0f, 1.0f, 3.0f);
//	const fgm::vec3 expected(27.0f, 33.0f, 39.0f);
//
//	// Act
//	vec *= mat;
//
//	// Assert
//	testutils::EXPECT_VEC_EQ(expected, vec);
// }
//
// TEST(Matrix4D_Product, MatrixTimesMatrixGivesAnotherMatrixWithCorrectValues)
//{
//	// Arrange
//	const fgm::Matrix4D mat1 = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f };
//	const fgm::Matrix4D mat2 = {
//		2.0, 4.0, 6.0,
//		8.0, 10.0, 12.0,
//		14.0, 16.0, 18.0 };
//	const fgm::Matrix4D expected = {
//		60.0f, 72.0f, 84.0f,
//		132.0f, 162.0f, 192.0f,
//		204.0f, 252.0f, 300.0f };
//
//	// Act
//	const fgm::Matrix4D actual = mat1 * mat2;
//
//	// Assert
//	EXPECT_MAT_EQ(expected, actual);
// }
//
// TEST(Matrix4D_Product, MatrixTimesIdentityMatrixReturnsSameMatrix)
//{
//	// Arrange
//	const fgm::Matrix4D mat = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f };
//	const fgm::Matrix4D<float> eye;
//
//	// Act
//	const fgm::Matrix4D actual = mat * eye;
//
//	// Assert
//	EXPECT_MAT_EQ(mat, actual);
// }
//
// TEST(Matrix4D_Product, MatrixTimesEqualAnotherMatrixReturnsSameMatrixWithCorrectValues)
//{
//	// Arrange
//	fgm::Matrix4D mat1 = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f };
//	const fgm::Matrix4D mat2 = {
//		2.0f, 4.0f, 6.0f,
//		8.0f, 10.0f, 12.0f,
//		14.0f, 16.0f, 18.0f };
//	const fgm::Matrix4D expected = {
//		60.0f, 72.0f, 84.0f,
//		132.0f, 162.0f, 192.0f,
//		204.0f, 252.0f, 300.0f };
//
//	// Act
//	mat1 *= mat2;
//
//	// Assert
//	EXPECT_MAT_EQ(expected, mat1);
// }
//
//
// TEST(Matrix4D_Product, Matrix4DProductIsAntiCommutative)
//{
//	// Arrange
//	const fgm::Matrix4D mat1 = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f };
//	const fgm::Matrix4D mat2 = {
//		3.0f, 6.0f, 3.0f,
//		12.0f, 0.0f, 2.0f,
//		15.0f, 11.0f, 6.0f };
//
//	// Act
//	const fgm::Matrix4D result1 = mat1 * mat2;
//	const fgm::Matrix4D result2 = mat2 * mat1;
//
//	// Assert
//	bool commutative = true;
//	for (std::size_t i = 0; i < size; i++)
//	{
//		commutative &= floatEquals(result1(i / rowSize, i % rowSize), result2(i / rowSize, i % rowSize));
//	}
//	EXPECT_FALSE(commutative);
// }
//
// TEST(Matrix4D_Product, Matrix4DProductWithScalarMultiplesAreCommutative)
//{
//	// Arrange
//	const fgm::Matrix4D mat1 = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f };
//	const fgm::Matrix4D mat2 = mat1 * 5.0f;
//
//	// Act
//	const fgm::Matrix4D result1 = mat1 * mat2;
//	const fgm::Matrix4D result2 = mat2 * mat1;
//
//	// Assert
//	bool commutative = true;
//	for (std::size_t i = 0; i < size; i++)
//	{
//		commutative &= floatEquals(result1(i / rowSize, i % rowSize), result2(i / rowSize, i % rowSize));
//	}
//	EXPECT_TRUE(commutative);
// }
//
// TEST(Matrix4D_Product, MatrixTimesADoubleScalarReturnsMatrixWithPromotedType)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	constexpr double scalar = 2.5;
//
//	const fgm::Matrix4D expected = {
//		2.5, 5.0, 7.5,
//		10.0, 12.5, 15.0,
//		17.5, -20.0, 22.5 };
//
//	// Act
//	const auto b = a * scalar;
//
//	// Assert
//	static_assert(std::is_same_v<typename decltype(b)::value_type, double>, "Assertion Failed (Matrix4D): Float *
// Double(Scalar) = Double"); 	EXPECT_MAT_EQ(expected, b);
// }
//
// TEST(Matrix4D_Product, MatrixTimesEqualDoubleScalarReturnsMatrixWithoutTypePromotion)
//{
//	// Arrange
//	fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	constexpr double scalar = 2.5;
//
//	const fgm::Matrix4D expected = {
//		2.5, 5.0, 7.5,
//		10.0, 12.5, 15.0,
//		17.5, -20.0, 22.5 };
//
//	// Act
//	a *= scalar;
//
//	// Assert
//	static_assert(std::is_same_v<typename decltype(a)::value_type, float>, "Assertion Failed (Matrix4D): Float *
// Double(Scalar) = Double"); 	EXPECT_MAT_EQ(expected, a);
// }
//
// TEST(Matrix4D_Product, DoubleVectorTimesAMatrixReturnsANewVectorWithPromotedType)
//{
//	// Arrange
//	const fgm::Matrix4D mat = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f };
//
//	fgm::dvec3 vec(2.0, 1.0, 3.0);
//	const fgm::dvec3 expected(27.0, 33.0, 39.0);
//
//	// Act
//	const fgm::dvec3 actual = vec * mat;
//
//	// Assert
//	static_assert(std::is_same_v<typename decltype(actual)::value_type, double>, "Assertion Failed (Matrix4D): Float *
// Double(vec) = Double"); 	testutils::EXPECT_VEC_EQ(expected, actual);
// }
//
// TEST(Matrix4D_Product, DoubleVectorTimesEqualAMatrixReturnsANewVectorWithPromotedType)
//{
//	// Arrange
//	const fgm::Matrix4D mat = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f };
//
//	fgm::vec3 vec(2.0f, 1.0f, 3.0f);
//	const fgm::dvec3 expected(27.0, 33.0, 39.0);
//
//	// Act
//	vec *= mat;
//
//	// Assert
//	static_assert(std::is_same_v<typename decltype(vec)::value_type, float>, "Assertion Failed (Matrix4D): Float(vec) *
// Double = Float"); 	testutils::EXPECT_VEC_EQ(expected, vec);
// }
//
// TEST(Matrix4D_Product, MatrixTimesMatrixGivesAnotherMatrixWithTypePromotion)
//{
//	// Arrange
//	const fgm::Matrix4D mat1 = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f };
//	const fgm::Matrix4D mat2 = {
//		2.0, 4.0, 6.0,
//		8.0, 10.0, 12.0,
//		14.0, 16.0, 18.0 };
//	const fgm::Matrix4D expected = {
//		60.0, 72.0, 84.0,
//		132.0, 162.0, 192.0,
//		204.0, 252.0, 300.0 };
//
//	// Act
//	const fgm::Matrix4D actual = mat1 * mat2;
//
//	// Assert
//	static_assert(std::is_same_v<typename decltype(actual)::value_type, double>, "Assertion Failed (Matrix4D): Float *
// Double = Double"); 	EXPECT_MAT_EQ(expected, actual);
// }
//
// TEST(Matrix4D_Product, MatrixTimesEqualAnotherMatrixReturnsSameMatrixWithoutTypePromotion)
//{
//	// Arrange
//	fgm::Matrix4D mat1 = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f };
//	const fgm::Matrix4D mat2 = {
//		2.0, 4.0, 6.0,
//		8.0, 10.0, 12.0,
//		14.0, 16.0, 18.0 };
//	const fgm::Matrix4D expected = {
//		60.0, 72.0, 84.0,
//		132.0, 162.0, 192.0,
//		204.0, 252.0, 300.0 };
//
//	// Act
//	mat1 *= mat2;
//
//	// Assert
//	static_assert(std::is_same_v<typename decltype(mat1)::value_type, float>, "Assertion Failed (Matrix4D): Float *=
// Double = Float"); 	EXPECT_MAT_EQ(expected, mat1);
// }
//
//
// TEST(Matrix4D_Division, MatrixDividedByAIntegerScalarReturnsCorrectMatrix)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	const fgm::Matrix4D expected = {
//		0.5f, 1.0f, 1.5f,
//		2.0f, 2.5f, 3.0f,
//		3.5f, -4.0f, 4.5f };
//	constexpr int scalar = 2;
//
//	// Act
//	const fgm::Matrix4D<float> actual = a / scalar;
//
//	// Assert
//	EXPECT_MAT_EQ(expected, actual);
// }
//
// TEST(Matrix4D_Division, MatrixDividesEqualIntegerScalarIsTheSameMatrixWithCorrectValues)
//{
//	// Arrange
//	fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	const fgm::Matrix4D b = {
//		0.5f, 1.0f, 1.5f,
//		2.0f, 2.5f, 3.0f,
//		3.5f, -4.0f, 4.5f };
//	constexpr int scalar = 2;
//
//	// Act
//	a /= scalar;
//
//	// Assert
//	EXPECT_MAT_EQ(b, a);
// }
//
// TEST(Matrix4D_Division, MatrixDividedByOneReturnANewMatrixWithOriginalMatrixValues)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//
//	// Act
//	const fgm::Matrix4D<float> b = a / 1;
//
//	// Assert
//	EXPECT_MAT_EQ(a, b);
// }
//
// TEST(Matrix4D_Division, MatrixDividedByZeroScalarReturnsInfinityMatrix)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//
//	// Act
//	const fgm::Matrix4D<float> b = a / 0;
//
//	// Assert
//	EXPECT_MAT_INF(b);
// }
//
// TEST(Matrix4D_Division, MatrixDividedByAFloatScalarReturnsCorrectMatrix)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//
//	const fgm::Matrix4D expected = {
//		0.4f, 0.8f, 1.2f,
//		1.6f, 2.0f, 2.4f,
//		2.8f, -3.2f, 3.6f };
//
//	constexpr float scalar = 2.5f;
//
//	// Act
//	const fgm::Matrix4D<float> actual = a / scalar;
//
//	// Assert
//	EXPECT_MAT_NEAR(expected, actual);
// }
//
// TEST(Matrix4D_Division, MatrixDividedNegativeFloatScalarFlipsSigns)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, -2.0f, 22.0f,
//		-4.0f, 5.0f, -6.0f,
//		4.0f, 8.0f, 9.0f };
//	const fgm::Matrix4D expected = {
//		-0.5f, 1.0f, -11.0f,
//		2.0f, -2.5f, 3.0f,
//		-2.0f, -4.0f, -4.5f };
//	constexpr float scalar = -2.0f;
//
//	// Act
//	const fgm::Matrix4D<float> actual = a / scalar;
//
//	// Assert
//	EXPECT_MAT_EQ(expected, actual);
// }
//
// TEST(Matrix4D_Division, MatrixDividedByDoubleScalarReturnsMatrixWithTypePromotion)
//{
//	// Arrange
//	const fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	const fgm::Matrix4D expected = {
//		0.5, 1.0, 1.5,
//		2.0, 2.5, 3.0,
//		3.5, -4.0, 4.5 };
//	constexpr double scalar = 2.0;
//
//	// Act
//	const auto actual = a / scalar;
//
//	// Assert
//	static_assert(std::is_same_v<typename decltype(actual)::value_type, double>, "Assertion Failed (Matrix4D): Float /
// Double = Double"); 	EXPECT_MAT_EQ(expected, actual);
// }
//
// TEST(Matrix4D_Division, MatrixDividesEqualDoubleScalarIsTheSameMatrixWithoutTypePromotion)
//{
//	// Arrange
//	fgm::Matrix4D a = {
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, -8.0f, 9.0f };
//	const fgm::Matrix4D b = {
//		0.5f, 1.0f, 1.5f,
//		2.0f, 2.5f, 3.0f,
//		3.5f, -4.0f, 4.5f };
//	constexpr double scalar = 2.0;
//
//	// Act
//	a /= scalar;
//
//	// Assert
//	static_assert(std::is_same_v<typename decltype(a)::value_type, float>, "Assertion Failed (Matrix4D): Float /= Double
//= Float"); 	EXPECT_MAT_EQ(b, a);
// }
//
// TEST(Matrix4D_Division, IntegerMatrixDivideEqualFloatScalarIsTheSameMatrixWithMinimalPrecisionLoss)
//{
//	// Arrange
//	fgm::Matrix4D a = {
//		1, 2, 3,
//		4, 5, 6,
//		7, -8, 9 };
//	const fgm::Matrix4D b = {
//		4, 8, 12,
//		16, 20, 24,
//		28, -32, 36 };
//	constexpr float scalar = 0.25f;
//
//	// Act
//	a /= scalar;
//
//	// Assert
//	EXPECT_MAT_EQ(b, a);
// }
//
//
///***********************
// *                     *
// *  DETERMINANT TESTS  *
// *                     *
// ***********************/
//
// TEST(Matrix4D_Determinant, IdentityMatrixReturnsDeterminantOfOne)
//{
//	// Arrange
//	const fgm::Matrix4D<float> mat;
//	constexpr float expectedDeterminant = 1.0f;
//
//	// Act
//	const float actualDeterminant = mat.determinant();
//
//	// Assert
//	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
//}
//
// TEST(Matrix4D_Determinant, DiagonalMatrixReturnsProductOfDiagonalEntriesAsDeterminant)
//{
//	// Arrange
//	const fgm::Matrix4D mat(
//		2.0f, 0.0f, 0.0f,
//		0.0f, 3.0f, 0.0f,
//		0.0f, 0.0f, 4.0f);
//	constexpr float expectedDeterminant = 24.0f;
//
//	// Act
//	const float actualDeterminant = mat.determinant();
//
//	// Assert
//	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
//}
//
// TEST(Matrix4D_Determinant, MatrixWithScalarMultipleColumnsReturnsDeterminantOfZero)
//{
//	const fgm::Matrix4D mat(
//		2.0f, 1.0f, 3.0f,
//		4.0f, 2.0f, 6.0f,
//		1.0f, 5.0f, 4.0f);
//
//	constexpr float expectedDeterminant = 0.0f;
//
//	// Act
//	const float actualDeterminant = mat.determinant();
//
//	// Assert
//	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
//}
//
// TEST(Matrix4D_Determinant, MatrixWithScalarMultipleRowsReturnsDeterminantOfZero)
//{
//	const fgm::Matrix4D mat(
//		2.0f, 4.0f, 3.0f,
//		4.0f, 8.0f, 6.0f,
//		1.0f, 2.0f, 4.0f);
//
//	constexpr float expectedDeterminant = 0.0f;
//
//	// Act
//	const float actualDeterminant = mat.determinant();
//
//	// Assert
//	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
//}
//
// TEST(Matrix4D_Determinant, IdentityMatrixWithSwappedRowsReturnsDeterminantOfNegativeOne)
//{
//	const fgm::Matrix4D mat(
//		1.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 1.0f,
//		0.0f, 1.0f, 0.0f);
//
//	constexpr float expectedDeterminant = -1.0f;
//
//	// Act
//	const float actualDeterminant = mat.determinant();
//
//	// Assert
//	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
//}
//
// TEST(Matrix4D_Determinant, IdentityMatrixWithSwappedColumnsReturnsDeterminantOfNegativeOne)
//{
//	const fgm::Matrix4D mat(
//		1.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 1.0f,
//		0.0f, 1.0f, 0.0f);
//
//	constexpr float expectedDeterminant = -1.0f;
//
//	// Act
//	const float actualDeterminant = mat.determinant();
//
//	// Assert
//	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
//}
//
// TEST(Matrix4D_Determinant, IdentityMatrixWithShearAppliedsReturnsDeterminantOfOne)
//{
//	const fgm::Matrix4D mat(
//		1.0f, 1.0f, 0.0f,
//		0.0f, 1.0f, 0.0f,
//		0.0f, 0.0f, 1.0f);
//
//	constexpr float expectedDeterminant = 1.0f;
//
//	// Act
//	const float actualDeterminant = mat.determinant();
//
//	// Assert
//	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
//}
//
// TEST(Matrix4D_Determinant, MatrixDeterminantReturnsCorrectValue)
//{
//	const fgm::Matrix4D mat(
//		1.0f, 2.0f, 3.0f,
//		0.0f, 4.0f, 1.0f,
//		5.0f, 6.0f, 0.0f);
//
//	constexpr float expectedDeterminant = -56.0f;
//
//	// Act
//	const float actualDeterminant = mat.determinant();
//
//	// Assert
//	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
//}
//
// TEST(Matrix4D_Determinant, MatrixDeterminantWithStaticWrapperReturnsCorrectValue)
//{
//	const fgm::Matrix4D mat(
//		1.0f, 2.0f, 3.0f,
//		0.0f, 4.0f, 1.0f,
//		5.0f, 6.0f, 0.0f);
//
//	constexpr float expectedDeterminant = -56.0f;
//
//	// Act
//	const float actualDeterminant = fgm::Matrix4D<float>::determinant(mat);
//
//	// Assert
//	EXPECT_FLOAT_EQ(expectedDeterminant, actualDeterminant);
//}
//
// TEST(Matrix4D_Determinant, DeterminantOfTransposedMatrixIsEqualToDeterminantOfTheMatrix)
//{
//	const fgm::Matrix4D a(
//		1.0f, 2.0f, 3.0f,
//		0.0f, 4.0f, 1.0f,
//		5.0f, 6.0f, 0.0f);
//
//	// Act
//	const float detA = a.determinant();
//	const float detAT = a.transpose().determinant();
//
//	// Assert
//	EXPECT_FLOAT_EQ(detA, detAT);
//}
//
// TEST(Matrix4D_Determinant, DeterminantOfProductOfMatricesIsSameAsProductOfDeterminantOfMatrix)
//{
//	// det(A*B) = det(A) * det(B)
//	const fgm::Matrix4D a(
//		1.0f, 2.0f, 3.0f,
//		0.0f, 4.0f, 1.0f,
//		5.0f, 6.0f, 0.0f);
//	const fgm::Matrix4D b(
//		1.0f, 2.0f, 3.0f,
//		4.0f, 5.0f, 6.0f,
//		7.0f, 8.0f, 9.0f);
//
//	// Act
//	const float determinantOfProduct = fgm::Matrix4D<float>::determinant(a * b);
//	const float productOfDeterminant = a.determinant() * b.determinant();
//
//	// Assert
//	EXPECT_FLOAT_EQ(determinantOfProduct, productOfDeterminant);
//}
//
// TEST(Matrix4D_Determinant, DeterminantOfAMatrixMultipliedByScalarIsScalarPowNTimesTheDeterminantOfOriginalMatrix)
//{
//	// det(t*A) = (t^n)det(A)
//	const fgm::Matrix4D a(
//		1.0f, 2.0f, 3.0f,
//		0.0f, 4.0f, 1.0f,
//		5.0f, 6.0f, 0.0f);
//	constexpr float scalar = 5.0f;
//
//	// Act
//	const float determinantOfProduct = fgm::Matrix4D<float>::determinant(scalar * a);
//	const float productOfDeterminant = (scalar * scalar * scalar) * a.determinant(); // n = 3 for 3x3 matrix
//
//	// Assert
//	EXPECT_FLOAT_EQ(determinantOfProduct, productOfDeterminant);
//}


///*********************
// *                   *
// *  TRANSPOSE TESTS  *
// *                   *
// *********************/

// TEST(Matrix4D_Transpose, TransposeOfIdentityMatrixIsItself)
//{
//	// Arrange
//	const fgm::Matrix4D<float> mat;
//
//	// Act
//	const fgm::Matrix4D<float> actual = mat.transpose();
//
//	// Assert
//	EXPECT_MAT_EQ(mat, actual);
// }
//
// TEST(Matrix4D_Transpose, TransposeOfAMatrixReturnsMatrixWithRowsAndColumnsSwapped)
//{
//	// Arrange
//	const fgm::Matrix4D mat(
//		1.0f, 2.0f, 3.0f,
//		0.0f, 4.0f, 1.0f,
//		5.0f, 6.0f, 0.0f);
//	const fgm::Matrix4D expected(
//		1.0f, 0.0f, 5.0f,
//		2.0f, 4.0f, 6.0f,
//		3.0f, 1.0f, 0.0f);
//
//	// Act
//	const fgm::Matrix4D<float> actual = mat.transpose();
//
//	// Assert
//	EXPECT_MAT_EQ(expected, actual);
// }
//
// TEST(Matrix4D_Transpose, TransposeOfAMatrixUsingStaticWrapperReturnsMatrixWithRowsAndColumnsSwapped)
//{
//	// Arrange
//	const fgm::Matrix4D mat(
//		1.0f, 2.0f, 3.0f,
//		0.0f, 4.0f, 1.0f,
//		5.0f, 6.0f, 0.0f);
//	const fgm::Matrix4D expected(
//		1.0f, 0.0f, 5.0f,
//		2.0f, 4.0f, 6.0f,
//		3.0f, 1.0f, 0.0f);
//
//	// Act
//	const fgm::Matrix4D<float> actual = fgm::Matrix4D<float>::transpose(mat);
//
//	// Assert
//	EXPECT_MAT_EQ(expected, actual);
// }


///*******************
// *                 *
// *  INVERSE TESTS  *
// *                 *
// *******************/

// TEST(Matrix4D_Inverse, InverseReturnsAnotherMatrixWithCorrectValues)
//{
//	// Given
//	const fgm::Matrix4D mat(
//		1.0f, 2.0f, 3.0f,
//		0.0f, 1.0f, 4.0f,
//		5.0f, 6.0f, 0.0f);
//	const fgm::Matrix4D expectedInverse(
//		-24.0f, 18.0f, 5.0f,
//		20.0f, -15.0f, -4.0f,
//		-5.0f, 4.0f, 1.0f);
//
//	// Act
//	const fgm::Matrix4D actualInverse = mat.inverse();
//
//	// Assert
//	EXPECT_MAT_EQ(expectedInverse, actualInverse);
// }
//
// TEST(Matrix4D_Inverse, StaticWrapperForInverseReturnsAnotherMatrixWithCorrectValues)
//{
//	const fgm::Matrix4D mat(
//		1.0f, 2.0f, 3.0f,
//		0.0f, 1.0f, 4.0f,
//		5.0f, 6.0f, 0.0f);
//	const fgm::Matrix4D expectedInverse(
//		-24.0f, 18.0f, 5.0f,
//		20.0f, -15.0f, -4.0f,
//		-5.0f, 4.0f, 1.0f);
//
//	// Act
//	const fgm::Matrix4D<float> actualInverse = fgm::Matrix4D<float>::inverse(mat);
//
//	// Assert
//	EXPECT_MAT_EQ(expectedInverse, actualInverse);
// }
//
// TEST(Matrix4D_Inverse, IdentityMatrixInverseReturnsAnotherIdentityMatrix)
//{
//	// Given
//	const fgm::Matrix4D<float> identity;
//
//	// Act
//	const fgm::Matrix4D<float> actualInverse = identity.inverse();
//
//	// Assert
//	EXPECT_MAT_IDENTITY(actualInverse);
// }
//
// TEST(Matrix4D_Inverse, MatrixTimeInverseReturnsIdentityMatrix)
//{
//	const fgm::Matrix4D mat(
//		1.0f, 2.0f, 3.0f,
//		0.0f, 1.0f, 4.0f,
//		5.0f, 6.0f, 0.0f);
//
//	// Act
//	const fgm::Matrix4D<float> inverse = fgm::Matrix4D<float>::inverse(mat);
//	const fgm::Matrix4D<float> product = mat * inverse;
//
//	// Assert
//	EXPECT_MAT_IDENTITY(product);
// }
//
// TEST(Matrix4D_Inverse, InverseTimesMatrixReturnsIdentityMatrix)
//{
//	const fgm::Matrix4D mat(
//		1.0f, 2.0f, 3.0f,
//		0.0f, 1.0f, 4.0f,
//		5.0f, 6.0f, 0.0f);
//
//	// Act
//	const fgm::Matrix4D<float> inverse = fgm::Matrix4D<float>::inverse(mat);
//	const fgm::Matrix4D<float> product = inverse * mat;
//
//	// Assert
//	EXPECT_MAT_IDENTITY(product);
// }
//
// TEST(Matrix4D_Inverse, SingularMatrixProducesIdentityMatrix)
//{
//	const fgm::Matrix4D singularMatrix(
//		0.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.0f);
//
//	// Act
//	const fgm::Matrix4D<float> actualInverse = fgm::Matrix4D<float>::inverse(singularMatrix);
//
//	// Assert
//	EXPECT_MAT_IDENTITY(actualInverse);
// }
//
// TEST(Matrix4D_Inverse, NearSingularMatrixProducesNonIdentityMatrix)
//{
//	const fgm::Matrix4D nearSingularMatrix(
//		1.0f, 0.0f, 0.0f,
//		0.0f, 0.1f, 0.0f,
//		0.0f, 0.0f, 0.1f
//	);
//
//	const fgm::Matrix4D expectedInverse(
//		1.0f, 0.0f, 0.0f,
//		0.0f, 10.0f, 0.0f,
//		0.0f, 0.0f, 10.0f
//	);
//
//	// Act
//	const fgm::Matrix4D<float> actualInverse = fgm::Matrix4D<float>::inverse(nearSingularMatrix);
//
//	// Assert
//	EXPECT_MAT_NEAR(expectedInverse, actualInverse);
// }
//
// TEST(Matrix4D_Inverse, InversionOfRotationOnlyMatrixReturnsTranspose)
//{
//	const fgm::Matrix4D mat(
//		0.0f, -1.0f, 0.0f,
//		1.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 1.0f);
//	const fgm::Matrix4D transpose(
//		0.0f, 1.0f, 0.0f,
//		-1.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 1.0f);
//
//	// Act
//	const fgm::Matrix4D<float> actualInverse = fgm::Matrix4D<float>::inverse(mat);
//
//	// Assert
//	EXPECT_MAT_EQ(transpose, actualInverse);
// }