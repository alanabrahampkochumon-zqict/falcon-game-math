#include <gtest/gtest.h>

#include <vector/Vector2D.h>
#include <type_traits>

#include "../utils/MatrixUtils.h"
#include "../utils/VectorUtils.h"

using namespace TestUtils;


/***********************************************
 *                                             *
 *  INITIALIZATION, ACCESS AND MUTATION TESTS  *
 *                                             *
 ***********************************************/

TEST(Vector2D_Initialization, EmptyConstructorInitializesZeroVector)
{
	// Arrange & Act
	const math::Vector2D<float> vec;

	// Assert
	EXPECT_VEC_ZERO(vec);
}

TEST(Vector2D_Initialization, IntializationWithIntegersSupported)
{
	// Arrange & Act
	const math::Vector2D vec(3, 1);

	// Assert
	static_assert(std::is_same_v<typename decltype(vec)::value_type, int>);
	EXPECT_EQ(3, vec.x);
	EXPECT_EQ(1, vec.y);
}

TEST(Vector2D_Initialization, ConstructorParametersInitializesVector)
{
	// Arrange & Act
	const math::Vector2D vec(3.0f, 1.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.x);
	EXPECT_FLOAT_EQ(1.0f, vec.y);
}

TEST(Vector2D_ConversionContructor, ConversionConstructorCreatesNewVectorWithPromotedType)
{
	// Arrange
	math::Vector2D vec1(3.0f, 1.0f);

	// Act
	math::Vector2D<double> vec2(vec1);
	vec2.x = 5;

	// Assert
	ASSERT_FLOAT_EQ(3.0f, vec1.x);
	ASSERT_FLOAT_EQ(1.0f, vec1.y);

	static_assert(std::is_same_v<typename decltype(vec2)::value_type, double>);

	ASSERT_DOUBLE_EQ(5.0, vec2.x);
	ASSERT_DOUBLE_EQ(1.0, vec2.y);

}

TEST(Vector2D_ConversionContructor, ConversionConstructorCreatesNewVectorWithDemotedType)
{
	// Arrange
	math::Vector2D vec1(3.0, 1.0);

	// Act
	math::Vector2D<float> vec2 = vec1;
	vec2.x = 5;

	// Assert
	ASSERT_DOUBLE_EQ(3.0, vec1.x);
	ASSERT_DOUBLE_EQ(1.0, vec1.y);

	static_assert(std::is_same_v<typename decltype(vec2)::value_type, float>);

	ASSERT_FLOAT_EQ(5.0f, vec2.x);
	ASSERT_FLOAT_EQ(1.0f, vec2.y);
}


TEST(Vector2D_Access, AccessibleAsXYZ)
{
	// Arrange & Act
	const math::Vector2D vec(3.0f, 1.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.x);
	EXPECT_FLOAT_EQ(1.0f, vec.y);
}

TEST(Vector2D_Access, AccessibleAsSTP)
{
	// Arrange & Act
	const math::Vector2D vec(3.0f, 1.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.s);
	EXPECT_FLOAT_EQ(1.0f, vec.t);
}

TEST(Vector2D_Access, AccessibleAsRGB)
{
	// Arrange & Act
	const math::Vector2D vec(3.0f, 1.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.r);
	EXPECT_FLOAT_EQ(1.0f, vec.g);
}

TEST(Vector2D_Access, AccessibleAsArray)
{
	// Arrange & Act
	const math::Vector2D vec(3.0f, 1.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
	EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
}

TEST(Vector2D_Access, IndexBasedAssignmentAndRetrivalSupport)
{
	// Arrange
	math::Vector2D<float> vec;

	// Act
	vec[0] = 3.0f;
	vec[1] = 1.0f;

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec[0]);
	EXPECT_FLOAT_EQ(1.0f, vec[1]);

}

TEST(Vector2D_Access, vec2Return2DFloatVector)
{
	// Arrange & Act
	constexpr bool isCorrectType = std::is_same_v<math::vec2, math::Vector2D<float>>;

	// Assert
	EXPECT_TRUE(isCorrectType);
}

TEST(Vector2D_Access, dvec2Return2DDoubleVector)
{
	// Arrange & Act
	constexpr bool isCorrectType = std::is_same_v<math::dvec2, math::Vector2D<double>>;

	// Assert
	EXPECT_TRUE(isCorrectType);
}


/*********************************
 *                               *
 *  SIMPLE MATH OPERATION TESTS  *
 *                               *
 *********************************/

TEST(Vector2D_Addition, VectorPlusVectorReturnsCorrectVector)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0f, -5.0f);
	const math::Vector2D expected(12.0f, -5.0f);

	// Act
	const math::Vector2D result = vec1 + vec2;

	// Assert
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Addition, VectorPlusEqualsAnotherVectorReturnsFirstVectorWithCorrectValues)
{
	// Arrange
	math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0f, -5.0f);
	const math::Vector2D expected(12.0f, -5.0f);

	// Act
	vec1 += vec2;

	// Assert
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector2D_Addition, VectorPlusVectorOfDifferentTypesReturnsVectorWithTypePromotion)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0, -5.0);
	const math::Vector2D expected(12.0, -5.0);

	// Act
	const math::Vector2D result = vec1 + vec2;

	// Assert
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Addition, VectorPlusEqualsVectorOfDifferentTypesReturnsVectorWithTypePromotion)
{
	// Arrange
	math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0, -5.0);
	const math::Vector2D expected(12.0f, -5.0f);

	// Act
	vec1 += vec2;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec1)::value_type, float>);
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector2D_Subraction, VectorMinusVectorReturnsCorrectVector)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0f, -5.0f);
	const math::Vector2D expected(-6.0f, 5.0f);

	// Act
	const math::Vector2D result = vec1 - vec2;

	// Assert
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Subraction, VectorMinusEqualsAnotherVectorReturnsFirstVectorWithCorrectValues)
{
	// Arrange
	math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0f, -5.0f);
	const math::Vector2D expected(-6.0f, 5.0f);

	// Act
	vec1 -= vec2;

	// Assert
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector2D_Subraction, VectorMinusVectorOfDifferentTypeReturnsVectorWithTypePromotion)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0, -5.0);
	const math::Vector2D expected(-6.0, 5.0);

	// Act
	const math::Vector2D result = vec1 - vec2;

	// Assert
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Subraction, VectorMinusEqualsAnotherVectorWithDifferentTypeReturnsFirstVectorWithoutTypePromotion)
{
	// Arrange
	math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(9.0, -5.0);
	const math::Vector2D expected(-6.0f, 5.0f);

	// Act
	vec1 -= vec2;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec1)::value_type, float>);
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector2D_Mutliplication, VectorTimesZeroIsZero)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);

	// Act
	const math::Vector2D result = vec * 0;

	// Assert
	EXPECT_VEC_ZERO(result);
}

TEST(Vector2D_Mutliplication, VectorTimesOneIsItself)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);

	// Act
	const math::Vector2D result = vec * 1;

	// Assert
	EXPECT_VEC_EQ(vec, result);
}

TEST(Vector2D_Mutliplication, VectorTimesANumberIsANewVector)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	const math::Vector2D result = vec * 2;

	// Assert
	EXPECT_VEC_EQ(expected, result);

}

TEST(Vector2D_Mutliplication, VectorTimesAFloatIsANewVector)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	const math::Vector2D result = vec * 2.0f;

	// Assert
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Mutliplication, NumberTimesAVectorIsANewVector)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	const math::Vector2D result = 2 * vec;

	// Assert
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Mutliplication, VectorTimesEqualAScalarIsSameVectorWithNewValues)
{
	// Arrange
	math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	vec *= 2;

	// Assert
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Mutliplication, VectorTimesEqualAScalarFloatIsSameVectorWithNewValues)
{
	// Arrange
	math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	vec *= 2.0;

	// Assert
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Mutliplication, VectorTimesEqualADoubleScalarIsSameVectorWithoutTypePromotion)
{
	// Arrange
	math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	vec *= 2.0;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec)::value_type, float>);
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Mutliplication, FloatVectorTimesADoubleScalarReturnsVectorWithTypePromotion)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(6.0f, 2.0f);

	// Act
	const math::Vector2D result = vec * 2.0;

	// Assert
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Mutliplication, IntegerVectorTimesEqualADoubleScalarReturnsVectorWithMinimalPrecisionLoss)
{
	// Arrange
	math::Vector2D vec(3, 1);
	const math::Vector2D expected(7, 2);

	// Act
	vec *= 2.5;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec)::value_type, int>);
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Division, VectorDividedByZeroIsInfinityVector)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);

	// Act
	const math::Vector2D result = vec / 0;

	// Assert
	EXPECT_VEC_INF(result);
}

TEST(Vector2D_Division, VectorDividedReturnsVectorWithSameValues)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);

	// Act
	const math::Vector2D result = vec / 1;

	// Assert
	EXPECT_VEC_EQ(vec, result);
}

TEST(Vector2D_Division, VectorDividedByANumberReturnsANewVectorWithCorrectValues)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(1.5f, 0.5f);

	// Act
	const math::Vector2D result = vec / 2;

	// Assert
	EXPECT_VEC_EQ(expected, result);

}

TEST(Vector2D_Division, VectorDividedByAFloatReturnsANewVectorWithCorrectValues)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(1.5f, 0.5f);

	// Act
	const math::Vector2D result = vec / 2.0f;

	// Assert
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Division, VectorDividesEqualAScalarIsSameVectorWithNewValues)
{
	// Arrange
	math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(1.5f, 0.5f);

	// Act
	vec /= 2;

	// Assert
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Division, VectorDividesEqualAFloatIsSameVectorWithNewValues)
{
	// Arrange
	math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(1.5f, 0.5f);

	// Act
	vec /= 2.0;

	// Assert
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Division, VectorDividesEqualADoubleIsSameVectorWithoutTypePromotion)
{
	// Arrange
	math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(1.5f, 0.5f);

	// Act
	vec /= 2.0;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec)::value_type, float>);
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector2D_Division, VectorDividedByADoubleReturnsVectorWithTypePromotion)
{
	// Arrange
	const math::Vector2D vec(3.0f, 1.0f);
	const math::Vector2D expected(1.5f, 0.5f);

	// Act
	const math::Vector2D result = vec / 2.0;

	// Assert
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector2D_Division, IntegerVectorDivideEqualsAFloatReturnsVectorWithMinimalPrecisionLoss)
{
	// Arrange
	math::Vector2D vec(3, 1);
	const math::Vector2D expected(12, 4);

	// Act
	vec /= 0.25f;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec)::value_type, int>);
	EXPECT_VEC_EQ(expected, vec);
}


/***************************************
 *                                     *
 *  MAGNITUDE AND NORMALIZATION TESTS  *
 *                                     *
 ***************************************/

TEST(Vector2D_Magnitude, ZeroVectorReturnsMagnitudeZero)
{
	// Arrange
	const math::Vector2D vec(0.0f, 0.0f);

	// Act
	const float magnitude = vec.mag();

	// Assert
	EXPECT_FLOAT_EQ(0.0f, magnitude);
}

TEST(Vector2D_Magnitude, OneVectorReturnsMagnitudeNotEqualToOne)
{
	// Arrange
	const math::Vector2D vec(1.0f, 1.0f);

	// Act
	const float magnitude = vec.mag();

	// Assert
	EXPECT_NE(1.0f, magnitude);
}

TEST(Vector2D_Magnitude, NonUnitVectorReturnsCorrectMagnitude)
{
	// Arrange
	const math::Vector2D vec(4.0f, 3.0f);

	// Act
	const float magnitude = vec.mag();

	// Assert
	EXPECT_FLOAT_EQ(5.0f, magnitude);
}


TEST(Vector2D_Normalize, VectorWhenNormalizedReturnsANormalVector)
{
	// Arrange
	math::Vector2D vec(4.0f, 3.0f);
	const math::Vector2D expected(0.8f, 0.6f);

	// Act
	math::Vector2D normalized = vec.normalize();

	// Assert
	EXPECT_VEC_EQ(expected, normalized);
	EXPECT_FLOAT_EQ(1.0f, normalized.mag());
}


/*********************************
 *                               *
 *  DOT AND CROSS PRODUCT TESTS  *
 *                               *
 *********************************/

TEST(Vector2D_Dot, VectorWhenDotWithItselfReturnsOne)
{
	// Arrange
	const math::Vector2D vec(1.0f, 0.0f);

	// Act
	const float result = vec.dot(vec);

	// Assert
	EXPECT_FLOAT_EQ(1.0, result);
}

TEST(Vector2D_Dot, VectorWhenDotWithOrthogonalVectorReturnZero)
{
	// Arrange
	const math::Vector2D vec1(1.0f, 0.0f);
	const math::Vector2D vec2(0.0f, 1.0f);

	// Act
	const float result = vec1.dot(vec2);

	// Assert
	EXPECT_FLOAT_EQ(0.0, result);
}

TEST(Vector2D_Dot, VectorWhenDotWithOppositeParallelVectorReturnsNegativeOne)
{
	// Arrange
	const math::Vector2D vec1(1.0f, 0.0f);
	const math::Vector2D vec2(-1.0f, 0.0f);

	// Act
	const float result = vec1.dot(vec2);

	// Assert
	EXPECT_FLOAT_EQ(-1.0, result);
}

TEST(Vector2D_Dot, VectorWhenDotWithAnotherNonOrthogonalVectorReturnsNonZeroNumber)
{
	// Arrange
	const math::Vector2D vec1(1.0f, 2.0f);
	const math::Vector2D vec2(4.0f, -5.0f);

	// Act
	const float result = vec1.dot(vec2);

	// Assert
	EXPECT_FLOAT_EQ(-6.0, result);
}

TEST(Vector2D_Dot, VectorWhenStaticWrapperDotWithAnotherNonOrthogonalVectorReturnsNonZeroNumber)
{
	// Arrange
	const math::Vector2D vec1(1.0f, 2.0f);
	const math::Vector2D vec2(4.0f, -5.0f);

	// Act
	const float result = math::Vector2D<float>::dot(vec1, vec2);

	// Assert
	EXPECT_FLOAT_EQ(-6.0f, result);
}

TEST(Vector2D_Dot, VectorWhenDotWithNonOrthogonalVectorOfDifferentTypeReturnsNumberWithTypePromotion)
{
	// Arrange
	const math::Vector2D vec1(1.0f, 2.0f);
	const math::Vector2D vec2(4.0, -5.0);

	// Act
	const auto result = vec1.dot(vec2);

	// Assert
	static_assert(std::is_same_v<decltype(result), const double>);
	EXPECT_DOUBLE_EQ(-6.0, result);
}

TEST(Vector2D_Cross, UnitXVectorWhenCrossWithUnitYVectorReturnsOne)
{
	// Arrange
	math::Vector2D vec1(1.0f, 0.0f);
	math::Vector2D vec2(0.0f, 1.0f);

	// Act
	const float res = vec1.cross(vec2);

	// Assert
	EXPECT_FLOAT_EQ(1.0f, res);
}

TEST(Vector2D_Cross, UnitYVectorWhenCrossWithUnitXVectorReturnsUnitNegativeOne)
{
	// Arrange
	const math::Vector2D vec1(0.0f, 1.0f);
	const math::Vector2D vec2(1.0f, 0.0f);

	// Act
	float res = vec1.cross(vec2);

	// Assert
	EXPECT_FLOAT_EQ(-1.0f, res);
}

TEST(Vector2D_Cross, UnitVectorCrossWithItselfReturnZero)
{
	// Arrange
	const math::Vector2D vec(0.0f, 1.0f);


	// Act
	const float res = vec.cross(vec);

	// Assert
	EXPECT_FLOAT_EQ(0.0f, res);
}

TEST(Vector2D_Cross, VectorCrossWithAnotherNonParallelVectorReturnsPseudoCrossProduct)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(0.0f, 4.0f);

	// Act
	const float res = vec1.cross(vec2);

	// Assert
	EXPECT_FLOAT_EQ(12.0f, res);
}

TEST(Vector2D_Cross, VectorCrossStaticWrapperWithAnotherNonParallelVectorReturnsPseudoCrossProduct)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(0.0f, 4.0f);

	// Act
	const float res = math::Vector2D<float>::cross(vec1, vec2);

	// Assert
	EXPECT_FLOAT_EQ(12.0f, res);
}

TEST(Vector2D_Cross, VectorCrossWithVectorOfDifferentTypeReturnsScalarWithTypePromotion)
{
	// Arrange
	const math::Vector2D vec1(3.0f, 0.0f);
	const math::Vector2D vec2(0.0, 4.0);

	// Act
	const auto result = vec1.cross(vec2);

	// Assert
	static_assert(std::is_same_v<decltype(result), const double>);
	EXPECT_DOUBLE_EQ(12.0, result);
}


/************************************
 *                                  *
 *  PROJECTION AND REJECTION TESTS  *
 *                                  *
 ************************************/

TEST(Vector2D_Projection, ParallelVectorsWhenProjectedReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(3.0f, 0.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(3.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.project(b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector2D_Projection, PerpendicularVectorsWhenProjectedReturnsZeroVector)
{
	// Arrange
	const math::Vector2D a(3.0f, 0.0f);
	const math::Vector2D b(0.0f, 1.0f);
	const math::Vector2D expectedProjection(0.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.project(b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector2D_Projection, VectorsWhenProjectedReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(2.0f, 2.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(2.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.project(b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector2D_Projection, VectorsWhenProjectedOntoNormalizedVectorReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(3.0f, 4.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(3.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.project(b, true);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector2D_Projection, VectorsWhenProjectedUsingStaticWrapperReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(2.0f, 2.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(2.0f, 0.0f);

	// Act
	const math::Vector2D actualProjection = math::Vector2D<float>::project(a, b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector2D_Projection, VectorsWhenProjectedOntoVectorOfDifferentTypeReturnsVectorWithTypePromotion)
{
	// Arrange
	const math::Vector2D a(2.0f, 2.0f);
	const math::Vector2D b(1.0, 0.0);
	const math::Vector2D expectedProjection(2.0, 0.0);

	// Act
	const math::Vector2D actualProjection = a.project(b);

	// Assert
	static_assert(std::is_same_v<typename decltype(actualProjection)::value_type, double>);
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector2D_Rejection, ParallelVectorsWhenRejectedReturnsZeroVector)
{
	// Arrange
	const math::Vector2D a(3.0f, 0.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(0.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.reject(b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector2D_Rejection, PerpendicularVectorsWhenRejectedReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(3.0f, 0.0f);
	const math::Vector2D b(0.0f, 1.0f);
	const math::Vector2D expectedProjection(3.0f, 0.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.reject(b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector2D_Rejection, VectorsWhenRejectedReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(2.0f, 2.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(0.0f, 2.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.reject(b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector2D_Rejection, VectorsWhenRejectedOntoNormalizedVectorReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(3.0f, 4.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(0.0f, 4.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.reject(b, true);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector2D_Rejection, VectorsWhenProjectedUsingStaticWrapperReturnsNonZeroVector)
{
	// Arrange
	const math::Vector2D a(2.0f, 2.0f);
	const math::Vector2D b(1.0f, 0.0f);
	const math::Vector2D expectedProjection(0.0f, 2.0f);

	// Act
	const math::Vector2D<float> actualProjection = a.reject(b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector2D_Rejection, VectorsWhenRejectedOntoVectorOfDifferentTypeReturnsVectorWithTypePromotion)
{
	// Arrange
	const math::Vector2D a(2.0f, 2.0f);
	const math::Vector2D b(1.0, 0.0);
	const math::Vector2D expectedProjection(0.0, 2.0);

	// Act
	const math::Vector2D actualProjection = a.reject(b);

	// Assert
	static_assert(std::is_same_v<typename decltype(actualProjection)::value_type, double>);
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}