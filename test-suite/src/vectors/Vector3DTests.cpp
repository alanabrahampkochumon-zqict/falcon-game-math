#include <gtest/gtest.h>

#include <vector/Vector3D.h>
#include <vector/Vector2D.h>

#include "../utils/VectorUtils.h"


using namespace TestUtils;


/***********************************************
 *                                             *
 *  INITIALIZATION, ACCESS AND MUTATION TESTS  *
 *                                             *
 ***********************************************/

TEST(Vector3D_Initialization, EmptyConstructorInitializesZeroVector)
{
	// Arrange & Act
	const math::Vector3D<float> vec;

	// Assert
	EXPECT_VEC_ZERO(vec);
}

TEST(Vector3D_Initialization, ConstructorParametersInitializesVector)
{
	// Arrange & Act
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.x);
	EXPECT_FLOAT_EQ(1.0f, vec.y);
	EXPECT_FLOAT_EQ(6.0f, vec.z);
}

TEST(Vector3D_Initialization, One2DVectorAndFloatCanInitializeA3DVector)
{
	// Arrange
	math::Vector2D vec1(3.0f, 1.0f);

	// Act
	math::Vector3D vec(vec1, 6.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.x);
	EXPECT_FLOAT_EQ(1.0f, vec.y);
	EXPECT_FLOAT_EQ(6.0f, vec.z);
}

TEST(Vector3D_ConversionConstructor, ConversionConstructorCreatesNewVectorWithPromotedType)
{
	// Arrange
	math::Vector3D vec1(3.0f, 1.0f, 6.0f);

	// Act
	math::Vector3D<double> vec2(vec1);
	vec2.x = 5;

	// Assert
	ASSERT_FLOAT_EQ(3.0f, vec1.x);
	ASSERT_FLOAT_EQ(1.0f, vec1.y);
	ASSERT_FLOAT_EQ(6.0f, vec1.z);

	static_assert(std::is_same_v<typename decltype(vec2)::value_type, double>);

	ASSERT_DOUBLE_EQ(5.0, vec2.x);
	ASSERT_DOUBLE_EQ(1.0, vec2.y);
	ASSERT_DOUBLE_EQ(6.0, vec2.z);

}

TEST(Vector3D_ConversionConstructor, ConversionConstructorCreatesNewVectorWithDemotedType)
{
	// Arrange
	math::Vector3D vec1(3.0, 1.0, 6.0);

	// Act
	math::Vector3D<float> vec2 = vec1;
	vec2.x = 5;

	// Assert
	ASSERT_DOUBLE_EQ(3.0, vec1.x);
	ASSERT_DOUBLE_EQ(1.0, vec1.y);
	ASSERT_DOUBLE_EQ(6.0, vec1.z);

	static_assert(std::is_same_v<typename decltype(vec2)::value_type, float>);

	ASSERT_FLOAT_EQ(5.0f, vec2.x);
	ASSERT_FLOAT_EQ(1.0f, vec2.y);
	ASSERT_FLOAT_EQ(6.0f, vec2.z);

}

TEST(Vector3D_Access, AccessibleAsXYZ)
{
	// Arrange & Act
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.x);
	EXPECT_FLOAT_EQ(1.0f, vec.y);
	EXPECT_FLOAT_EQ(6.0f, vec.z);
}

TEST(Vector3D_Access, AccessibleAsSTP)
{
	// Arrange & Act
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.s);
	EXPECT_FLOAT_EQ(1.0f, vec.t);
	EXPECT_FLOAT_EQ(6.0f, vec.p);
}

TEST(Vector3D_Access, AccessibleAsRGB)
{
	// Arrange & Act
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.r);
	EXPECT_FLOAT_EQ(1.0f, vec.g);
	EXPECT_FLOAT_EQ(6.0f, vec.b);
}

TEST(Vector3D_Access, AccessibleAsArray)
{
	// Arrange & Act
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
	EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
	EXPECT_FLOAT_EQ(6.0f, vec.elements[2]);
}

TEST(Vector3D_Access, IndexBasedAssignmentAndRetrivalSupport)
{
	// Arrange
	math::Vector3D<float> vec;

	// Act
	vec[0] = 3.0f;
	vec[1] = 1.0f;
	vec[2] = 6.0f;

	// Assert
	EXPECT_FLOAT_EQ(3.0f, vec[0]);
	EXPECT_FLOAT_EQ(1.0f, vec[1]);
	EXPECT_FLOAT_EQ(6.0f, vec[2]);

}

TEST(Vector3D_Helper, vec3Return3DFloatVector)
{
	// Arrange & Act
	constexpr bool isCorrectType = std::is_same_v<math::vec3, math::Vector3D<float>>;

	// Assert
	EXPECT_TRUE(isCorrectType);
}

TEST(Vector3D_Helper, dvec3Return3DDoubleVector)
{
	// Arrange & Act
	constexpr bool isCorrectType = std::is_same_v<math::dvec3, math::Vector3D<double>>;

	// Assert
	EXPECT_TRUE(isCorrectType);
}


/*********************************
 *                               *
 *  SIMPLE MATH OPERATION TESTS  *
 *                               *
 *********************************/

TEST(Vector3D_Addition, VectorPlusVectorReturnsNewVectorWithEachComponentsSummedUp)
{
	// Arrange
	const math::Vector3D vec1(3.0f, 0.0f, -1.0f);
	const math::Vector3D vec2(9.0f, -5.0f, 10.0f);
	const math::Vector3D expected(12.0f, -5.0f, 9.0f);

	// Act
	const math::Vector3D actual = vec1 + vec2;

	// Assert
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Addition, VectorPlusEqualsAnotherVectorReturnsFirstVectorWithCorrectValues)
{
	// Arrange
	math::Vector3D vec1(3.0f, 0.0f, -1.0f);
	const math::Vector3D vec2(9.0f, -5.0f, 10.0f);
	const math::Vector3D expected(12.0f, -5.0f, 9.0f);

	// Act
	vec1 += vec2;

	// Assert
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector3D_Addition, VectorPlusVectorOfDifferentTypeReturnsNewVectorWithPromotedType)
{
	// Arrange
	const math::Vector3D vec1(3.0f, 0.0f, -1.0f);
	const math::Vector3D vec2(9.0, -5.0, 10.0);
	const math::Vector3D expected(12.0, -5.0, 9.0);

	// Act
	const math::Vector3D actual = vec1 + vec2;

	// Assert
	static_assert(std::is_same_v<typename decltype(actual)::value_type, double>);
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Addition, VectorPlusEqualsVectorOfDifferentTypeReturnsNewVectorWithoutPromotedType)
{
	// Arrange
	math::Vector3D vec1(3.0f, 0.0f, -1.0f);
	const math::Vector3D vec2(9.0, -5.0, 10.0);
	const math::Vector3D expected(12.0, -5.0, 9.0);

	// Act
	vec1 += vec2;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec1)::value_type, float>);
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector3D_Subraction, VectorSubtraction)
{
	// Arrange
	const math::Vector3D vec1(3.0f, 0.0f, -1.0f);
	const math::Vector3D vec2(9.0f, -5.0f, 10.0f);
	const math::Vector3D expected(-6.0f, 5.0f, -11.0f);

	// Act
	const math::Vector3D actual = vec1 - vec2;

	// Assert
	EXPECT_VEC_EQ(expected, actual);

}

TEST(Vector3D_Subraction, VectorMinusEqualsAnotherVectorReturnsFirstVectorWithCorrectValues)
{
	// Arrange
	math::Vector3D vec1(3.0f, 0.0f, -1.0f);
	const math::Vector3D vec2(9.0f, -5.0f, 10.0f);
	const math::Vector3D expected(-6.0f, 5.0f, -11.0f);

	// Act
	vec1 -= vec2;

	// Assert
	EXPECT_VEC_EQ(expected, vec1);

}

TEST(Vector3D_Subraction, VectorMinusVectorOfDifferentTypeReturnsNewVectorWithPromotedType)
{
	// Arrange
	const math::Vector3D vec1(3.0f, 0.0f, -1.0f);
	const math::Vector3D vec2(9.0, -5.0, 10.0);
	const math::Vector3D expected(-6.0, 5.0, -11.0);

	// Act
	const math::Vector3D actual = vec1 - vec2;

	// Assert
	static_assert(std::is_same_v<typename decltype(actual)::value_type, double>);
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Subraction, VectorMinusEqualsVectorOfDifferentTypeReturnsNewVectorWithoutPromotedType)
{
	// Arrange
	math::Vector3D vec1(3.0f, 0.0f, -1.0f);
	const math::Vector3D vec2(9.0, -5.0, 10.0);
	const math::Vector3D expected(-6.0, 5.0, -11.0);

	// Act
	vec1 -= vec2;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec1)::value_type, float>);
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector3D_Product, VectorTimesZeroIsZero)
{
	// Arrange
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);

	// Act
	const math::Vector3D result = vec * 0;

	// Assert
	EXPECT_VEC_ZERO(result);
}

TEST(Vector3D_Product, VectorTimesOneIsItself)
{
	// Arrange
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);

	// Act
	const math::Vector3D result = vec * 1;

	// Assert
	EXPECT_VEC_EQ(vec, result);
}

TEST(Vector3D_Product, VectorTimesAnIntegerIsANewVector)
{
	// Arrange
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(6.0f, 2.0f, 12.0f);
	constexpr int scalar = 2;

	// Act
	const math::Vector3D actual = vec * scalar;

	// Assert
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Product, VectorTimesAFloatIsANewVector)
{
	// Arrange
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(6.0f, 2.0f, 12.0f);
	constexpr float scalar = 2.0f;

	// Act
	const math::Vector3D actual = vec * scalar;

	// Assert
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Product, IntegerTimesAVectorIsANewVector)
{
	// Arrange
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(6.0f, 2.0f, 12.0f);
	constexpr int scalar = 2;

	// Act
	const math::Vector3D actual = scalar * vec;

	// Assert
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Product, VectorTimesEqualAScalarIsSameVectorWithNewValues)
{
	// Arrange
	math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(6.0f, 2.0f, 12.0f);
	constexpr int scalar = 2;

	// Act
	vec *= scalar;

	// Assert
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector3D_Product, VectorTimesEqualAScalarFloatIsSameVectorWithNewValues)
{
	// Arrange
	math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(6.0f, 2.0f, 12.0f);
	constexpr float scalar = 2.0f;

	// Act
	vec *= scalar;

	// Assert
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector3D_Product, VectorTimesAScalarDoubleIsReturnsVectorWithoutPromotedType)
{
	// Arrange
	math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(6.0f, 2.0f, 12.0f);
	constexpr double scalar = 2.0;

	// Act
	vec *= scalar;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec)::value_type, float>);
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector3D_Product, VectorTimesEqualAScalarDoubleIsSameVectorWithPromotedType)
{
	// Arrange
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(6.0f, 2.0f, 12.0f);
	constexpr double scalar = 2.0;

	// Act
	const auto actual = scalar * vec;

	// Assert
	static_assert(std::is_same_v<typename decltype(actual)::value_type, double>);
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Product, IntegerVectorTimesEqualAScalarFloatReturnsInMinimalPrecisionLoss)
{
	// Arrange
	const math::Vector3D vec(2, 4, 8);
	const math::Vector3D expected(5.0f, 10.0f, 20.0f);
	constexpr double scalar = 2.5;

	// Act
	const auto actual = scalar * vec;

	// Assert
	static_assert(std::is_same_v<typename decltype(actual)::value_type, double>);
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Division, VectorDividedByZeroIsInfinity)
{
	// Arrange
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);

	// Act
	const math::Vector3D result = vec / 0;

	// Assert
	EXPECT_VEC_INF(result);
}

TEST(Vector3D_Division, VectorDividedByOneIsItself)
{
	// Arrange
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);

	// Act
	const math::Vector3D result = vec / 1;

	// Assert
	EXPECT_VEC_EQ(vec, result);
}

TEST(Vector3D_Division, VectorDividedByANumberIsANewVector)
{
	// Arrange
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(1.5f, 0.5f, 3.0f);
	constexpr int scalar = 2;
	// Act
	const math::Vector3D actual = vec / scalar;

	// Assert
	EXPECT_VEC_EQ(expected, actual);

}

TEST(Vector3D_Division, VectorDividedByAFloatIsANewVector)
{
	// Arrange
	const math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(1.5f, 0.5f, 3.0f);
	constexpr float scalar = 2.0f;
	// Act
	const math::Vector3D actual = vec / scalar;

	// Assert
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Division, VectorDivideEqualAScalarIsSameVectorWithNewValues)
{
	// Arrange
	math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(1.5f, 0.5f, 3.0f);
	constexpr int scalar = 2;

	// Act
	vec /= scalar;

	// Assert
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector3D_Division, VectorDivideEqualAFloatIsSameVectorWithNewValues)
{
	// Arrange
	math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(1.5f, 0.5f, 3.0f);
	constexpr float scalar = 2.0f;

	// Act
	vec /= scalar;

	// Assert
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector3D_Division, VectorDivideEqualADoubleScalarIsSameVectorWithoutPromotedType)
{
	// Arrange
	math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(1.5f, 0.5f, 3.0f);
	constexpr double scalar = 2.0;

	// Act
	vec /= scalar;

	// Assert
	static_assert(std::is_same_v<typename decltype(vec)::value_type, float>);
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector3D_Division, VectorDividedByADoubleScalarIsAVectorWithPromotedType)
{
	// Arrange
	math::Vector3D vec(3.0f, 1.0f, 6.0f);
	const math::Vector3D expected(1.5f, 0.5f, 3.0f);
	constexpr double scalar = 2.0;

	// Act
	const auto actual = vec / scalar;

	// Assert
	static_assert(std::is_same_v<typename decltype(actual)::value_type, double>);
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Division, IntegerVectorDividedByAScalarFloatResultsInMinimalPrecisionLoss)
{
	// Arrange
	const math::Vector3D vec(2, 4, 8);
	const math::Vector3D expected(4.0, 8.0, 16.0);
	constexpr double scalar = 0.5;

	// Act
	const auto actual = vec / scalar;

	// Assert
	static_assert(std::is_same_v<typename decltype(actual)::value_type, double>);
	EXPECT_VEC_EQ(expected, actual);
}


/***************************************
 *                                     *
 *  MAGNITUDE AND NORMALIZATION TESTS  *
 *                                     *
 ***************************************/

TEST(Vector3D_Magnitude, ZeroVectorReturnsMagnitudeZero)
{
	// Arrange
	const math::Vector3D vec(0.0f, 0.0f, 0.0f);

	// Act
	const float magnitude = vec.mag();

	// Assert
	EXPECT_FLOAT_EQ(0.0f, magnitude);
}

TEST(Vector3D_Magnitude, OneVectorReturnsMagnitudeNotEqualToOne)
{
	// Arrange
	const math::Vector3D vec(1.0f, 1.0f, 1.0f);

	// Act
	const float magnitude = vec.mag();

	// Assert
	EXPECT_NE(1.0f, magnitude);
}

TEST(Vector3D_Magnitude, NonUnitVectorReturnsCorrectMagnitude)
{
	// Arrange
	const math::Vector3D vec(2.0f, 3.0f, 6.0f);

	// Act
	const float magnitude = vec.mag();

	// Assert
	EXPECT_FLOAT_EQ(7.0f, magnitude);
}

TEST(Vector3D_Normalization, VectorWhenNormalizedReturnsANormalVector)
{
	// Arrange
	const math::Vector3D vec(0.0f, 3.0f, 4.0f);
	const math::Vector3D expected(0.0f, 0.6f, 0.8f);

	// Act
	const math::Vector3D normalized = vec.normalize();

	// Assert
	EXPECT_VEC_EQ(expected, normalized);
}


/*********************************
 *                               *
 *  DOT AND CROSS PRODUCT TESTS  *
 *                               *
 *********************************/

TEST(Vector3D_Dot, VectorWhenDotWithItselfReturnsOne)
{
	// Arrange
	const math::Vector3D vec(1.0f, 0.0f, 0.0f);

	// Act
	const float res = vec.dot(vec);

	// Assert
	EXPECT_FLOAT_EQ(1.0f, res);
}

TEST(Vector3D_Dot, VectorWhenDotWithOrthogonalVectorReturnZero)
{
	// Arrange
	const math::Vector3D vec1(1.0f, 0.0f, 0.0f);
	const math::Vector3D vec2(0.0f, 1.0f, 0.0f);

	// Act
	const float res = vec1.dot(vec2);

	// Assert
	EXPECT_FLOAT_EQ(0.0f, res);
}

TEST(Vector3D_Dot, VectorWhenDotWithOppositeParallelVectorReturnsNegativeOne)
{
	// Arrange
	const math::Vector3D vec1(1.0f, 0.0f, 0.0f);
	const math::Vector3D vec2(-1.0f, 0.0f, 0.0f);

	// Act
	const float res = vec1.dot(vec2);

	// Assert
	EXPECT_FLOAT_EQ(-1.0f, res);
}

TEST(Vector3D_Dot, VectorWhenDotWithAnotherNonOrthogonalVectorReturnsNonZeroNumber)
{
	// Arrange
	const math::Vector3D<float> vec1(1.0f, 2.0f, 3.0f);
	const math::Vector3D<float> vec2(4.0f, -5.0f, 6.0f);

	// Act
	const float res = vec1.dot(vec2);

	// Assert
	EXPECT_FLOAT_EQ(12.0, res);
}

TEST(Vector3D_Dot, VectorWhenStaticWrapperDotWithAnotherNonOrthogonalVectorReturnsNonZeroNumber)
{
	// Arrange
	const math::Vector3D vec1(1.0f, 2.0f, 3.0f);
	const math::Vector3D vec2(4.0f, -5.0f, 6.0f);

	// Act
	const float res = math::Vector3D<float>::dot(vec1, vec2);

	// Assert
	EXPECT_FLOAT_EQ(12.0, res);
}

TEST(Vector3D_Dot, VectorWhenDotWithAnotherNonOrthogonalVectorOfDifferentTypeReturnsNonZeroNumberWithPromotedType)
{
	// Arrange
	const math::Vector3D vec1(1.0f, 2.0f, 3.0f);
	const math::Vector3D vec2(4.0, -5.0, 6.0);

	// Act
	const auto res = vec1.dot(vec2);

	// Assert
	static_assert(std::is_same_v<decltype(res), const double>);
	EXPECT_DOUBLE_EQ(12.0, res);
}

TEST(Vector3D_Cross, UnitXVectorWhenCrossWithUnitYVectorReturnsUnitZVector)
{
	// Arrange
	const math::Vector3D vec1(1.0f, 0.0f, 0.0f);
	const math::Vector3D vec2(0.0f, 1.0f, 0.0f);
	const math::Vector3D expected(0.0f, 0.0f, 1.0f);

	// Act
	const math::Vector3D actual = vec1.cross(vec2);

	// Assert
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Cross, UnitYVectorWhenCrossWithUnitXVectorReturnsUnitNegativeZVector)
{
	// Arrange
	const math::Vector3D vec1(0.0f, 1.0f, 0.0f);
	const math::Vector3D vec2(1.0f, 0.0f, 0.0f);
	const math::Vector3D expected(0.0f, 0.0f, -1.0f);

	// Act
	const  math::Vector3D actual = vec1.cross(vec2);

	// Assert
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Cross, UnitZVectorWhenCrossWithUnitYVectorReturnsUnitNegativeVector)
{
	// Arrange
	const math::Vector3D vec1(0.0f, 0.0f, 1.0f);
	const math::Vector3D vec2(0.0f, 1.0f, 0.0f);
	const math::Vector3D expected(-1.0f, 0.0f, 0.0f);

	// Act
	const math::Vector3D actual = vec1.cross(vec2);

	// Assert
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Cross, UnitVectorCrossWithItselfReturnZeroVector)
{
	// Arrange
	const math::Vector3D vec(0.0f, 0.0f, 1.0f);

	const math::Vector3D expected(0.0f, 0.0f, 0.0f);

	// Act
	const math::Vector3D actual = vec.cross(vec);

	// Assert
	EXPECT_VEC_EQ(expected, actual);
}

TEST(Vector3D_Cross, VectorCrossWithAnotherNonParallelVectorReturnsNewPerpendicularVector)
{
	// Arrange
	const math::Vector3D vec1(2.0f, 3.0f, 4.0f);
	const math::Vector3D vec2(5.0f, 6.0f, 7.0f);

	const math::Vector3D expected(-3.0f, 6.0f, -3.0f);

	// Act
	const math::Vector3D actual = vec1.cross(vec2);

	// Assert
	EXPECT_VEC_EQ(expected, actual);

	// Orientation Check: Dot must be zero
	const float dotProduct1 = vec1.dot(actual);
	const float dotProduct2 = vec2.dot(actual);

	EXPECT_FLOAT_EQ(0.0, dotProduct1);
	EXPECT_FLOAT_EQ(0.0, dotProduct2);
}

TEST(Vector3D_Cross, VectorCrossStaticWrapperWithAnotherNonParallelVectorReturnsNewPerpendicularVector)
{
	// Arrange
	const math::Vector3D vec1(2.0f, 3.0f, 4.0f);
	const math::Vector3D vec2(5.0f, 6.0f, 7.0f);

	math::Vector3D expected(-3.0f, 6.0f, -3.0f);

	// Act
	math::Vector3D actual = math::Vector3D<float>::cross(vec1, vec2);

	// Assert
	EXPECT_VEC_EQ(expected, actual);

	// Orientation Check: Dot must be zero
	const float dotProduct1 = math::Vector3D<float>::dot(vec1, actual);
	const float dotProduct2 = math::Vector3D<float>::dot(vec2, actual);

	EXPECT_FLOAT_EQ(0.0f, dotProduct1);
	EXPECT_FLOAT_EQ(0.0f, dotProduct2);
}

TEST(Vector3D_Cross, VectorCrossProductsAreAntiCommutative)
{
	// vec1 x(cross) vec2 = - (vec2 x vec1)
	// Arrange
	const math::Vector3D vec1(2.0f, 3.0f, 4.0f);
	const math::Vector3D vec2(3.0f, 5.0f, 9.0f);

	// Act
	math::Vector3D result1 = math::Vector3D<float>::cross(vec1, vec2);
	math::Vector3D result2 = -1.0f * (math::Vector3D<float>::cross(vec2, vec1));

	// Assert
	EXPECT_VEC_EQ(result1, result2);
}

TEST(Vector3D_Cross, VectorCrossProductsOfScalarMultiplesAreCommutative)
{
	// vec1 x(cross) vec2 = vec2 x vec1, given vec2 = a * vec1
	// Arrange
	const math::Vector3D vec1(2.0f, 3.0f, 4.0f);
	const math::Vector3D vec2 = vec1 * 2.0f;

	// Act
	math::Vector3D result1 = math::Vector3D<float>::cross(vec1, vec2);
	math::Vector3D result2 = math::Vector3D<float>::cross(vec2, vec1);

	// Assert
	EXPECT_VEC_EQ(result1, result2);
}

TEST(Vector3D_Cross, VectorCrossWithAnotherNonParallelVectorOfDifferentTypeReturnsNewPerpendicularVectorWithPromotedType)
{
	// Arrange
	const math::Vector3D vec1(2.0f, 3.0f, 4.0f);
	const math::Vector3D vec2(5.0, 6.0, 7.0);

	const math::Vector3D expected(-3.0, 6.0, -3.0);

	// Act
	const math::Vector3D actual = vec1.cross(vec2);

	// Assert
	static_assert(std::is_same_v<typename decltype(actual)::value_type, double>);
	EXPECT_VEC_EQ(expected, actual);

	// Orientation Check: Dot must be zero
	const auto dotProduct1 = vec1.dot(actual);
	const auto dotProduct2 = vec2.dot(actual);

	EXPECT_DOUBLE_EQ(0.0, dotProduct1);
	EXPECT_DOUBLE_EQ(0.0, dotProduct2);
}


/************************************
 *                                  *
 *  PROJECTION AND REJECTION TESTS  *
 *                                  *
 ************************************/

TEST(Vector3D_Projection, ParallelVectorsWhenProjectedReturnsNonZeroVector)
{
	// Arrange
	const math::Vector3D a(1.0f, 2.0f, 3.0f);
	const math::Vector3D b(2.0f, 4.0f, 6.0f);
	const math::Vector3D expectedProjection(1.0f, 2.0f, 3.0f);

	// Act
	const math::Vector3D<float> actualProjection = a.project(b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector3D_Projection, PerpendicularVectorsWhenProjectedReturnsZeroVector)
{
	// Arrange
	const math::Vector3D a(1.0f, 0.0f, 0.0f);
	const math::Vector3D b(0.0f, 1.0f, 0.0f);
	const math::Vector3D expectedProjection(0.0f, 0.0f, 0.0f);

	// Act
	const math::Vector3D<float> actualProjection = a.project(b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector3D_Projection, VectorsWhenProjectedReturnsNonZeroVector)
{
	// Arrange
	const math::Vector3D a(2.0f, 1.0f, -1.0f);
	const math::Vector3D b(1.0f, 0.0f, 1.0f);
	const math::Vector3D expectedProjection(0.5f, 0.0f, 0.5f);

	// Act
	const math::Vector3D<float> actualProjection = a.project(b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector3D_Projection, VectorsWhenProjectedOntoNormalizedVectorReturnsNonZeroVector)
{
	// Arrange
	const math::Vector3D a(10.0f, 5.0f, 2.0f);
	const math::Vector3D b(0.8f, 0.6f, 0.0f);
	const math::Vector3D expectedProjection(8.8f, 6.6f, 0.0f);

	// Act
	const math::Vector3D<float> actualProjection = a.project(b, true);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector3D_Projection, VectorsWhenProjectedOntoNegativeVectorReturnsNonZeroVectorInSameDirection)
{
	// Arrange
	const math::Vector3D a(4.0f, 4.0f, 4.0f);
	const math::Vector3D b(0.0f, 0.0f, -1.0f);
	const math::Vector3D expectedProjection(0.0f, 0.0f, 4.0f);

	// Act
	const math::Vector3D<float> actualProjection = a.project(b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector3D_Projection, VectorsWhenProjectedUsingStaticWrapperReturnsNonZeroVector)
{
	// Arrange
	const math::Vector3D a(2.0f, 1.0f, -1.0f);
	const math::Vector3D b(1.0f, 0.0f, 1.0f);
	const math::Vector3D expectedProjection(0.5f, 0.0f, 0.5f);

	// Act
	const math::Vector3D<float> actualProjection = math::Vector3D<float>::project(a, b);

	// Assert
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector3D_Projection, VectorsWhenProjectedOntoVectorOfDifferentTypeReturnsVectorWithPromotedType)
{
	// Arrange
	const math::Vector3D a(2.0f, 1.0f, -1.0f);
	const math::Vector3D b(1.0, 0.0, 1.0);
	const math::Vector3D expectedProjection(0.5, 0.0, 0.5);

	// Act
	const auto actualProjection = a.project(b);

	// Assert
	static_assert(std::is_same_v<typename decltype(actualProjection)::value_type, double>);
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TEST(Vector3D_Rejection, ParallelVectorsWhenRejectedReturnsZeroVector)
{
	// Arrange
	const math::Vector3D a(1.0f, 2.0f, 3.0f);
	const math::Vector3D b(2.0f, 4.0f, 6.0f);
	const math::Vector3D expectedRejection(0.0f, 0.0f, 0.0f);

	// Act
	const math::Vector3D<float> actualRejection = a.reject(b);

	// Assert
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector3D_Rejection, PerpendicularVectorsWhenRejectedReturnsNonZeroVector)
{
	// Arrange
	const math::Vector3D a(1.0f, 0.0f, 0.0f);
	const math::Vector3D b(0.0f, 1.0f, 0.0f);
	const math::Vector3D expectedRejection(1.0f, 0.0f, 0.0f);

	// Act
	const math::Vector3D<float> actualRejection = a.reject(b);

	// Assert
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector3D_Rejection, VectorsWhenRejectedReturnNonZeroVector)
{
	// Arrange
	const math::Vector3D a(2.0f, 1.0f, -1.0f);
	const math::Vector3D b(1.0f, 0.0f, 1.0f);
	const math::Vector3D expectedRejection(1.5f, 1.0f, -1.5f);

	// Act
	const math::Vector3D<float> actualRejection = a.reject(b);

	// Assert
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector3D_Rejection, VectorsWhenRejectedOntoNormalizedVectorReturnNonZeroVector)
{
	// Arrange
	const math::Vector3D a(10.0f, 5.0f, 2.0f);
	const math::Vector3D b(0.8f, 0.6f, 0.0f);
	const math::Vector3D expectedRejection(1.2f, -1.6f, 2.0f);

	// Act
	const math::Vector3D<float> actualRejection = a.reject(b, true);

	// Assert
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector3D_Rejection, PositiveVectorsWhenRejectedOntoNegativeVectorReturnsNonZeroPositiveVector)
{
	// Arrange
	const math::Vector3D a(4.0f, 4.0f, 4.0f);
	const math::Vector3D b(0.0f, 0.0f, -1.0f);
	const math::Vector3D expectedRejection(4.0f, 4.0f, 0.0f);

	// Act
	const math::Vector3D<float> actualRejection = a.reject(b);

	// Assert
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector3D_Rejection, VectorsWhenRejectedUsingStaticWrapperReturnNonZeroVector)
{
	// Arrange
	const math::Vector3D a(2.0f, 1.0f, -1.0f);
	const math::Vector3D b(1.0f, 0.0f, 1.0f);
	const math::Vector3D expectedRejection(1.5f, 1.0f, -1.5f);

	// Act
	const math::Vector3D<float> actualRejection = math::Vector3D<float>::reject(a, b);

	// Assert
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector3D_Rejection, VectorsWhenRejectedOntoVectorOfDifferentTypeReturnsVectorWithPromotedType)
{
	// Arrange
	const math::Vector3D a(4.0f, 4.0f, 4.0f);
	const math::Vector3D b(0.0, 0.0, -1.0);
	const math::Vector3D expectedRejection(4.0, 4.0, 0.0);

	// Act
	const math::Vector3D actualRejection = a.reject(b);

	// Assert
	static_assert(std::is_same_v<typename decltype(actualRejection)::value_type, double>);
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}