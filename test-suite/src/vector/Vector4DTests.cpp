#include <gtest/gtest.h>

#include <MathTraits.h>
#include <vector/Vector4D.h>

#include "../utils/VectorUtils.h"
#include "matrix/Matrix4D.h"


using namespace TestUtils;

/****************
 *              *
 *  TEST SETUP  *
 *              *
 ****************/

 // Turn off SIMD
#define FORCE_NO_SIMD // TODO: Update

using SupportedTypes = ::testing::Types<unsigned char, bool, int, unsigned int, float, double, std::size_t, long long>;
using SupportedArithmeticTypes = ::testing::Types<unsigned char, int, unsigned int, float, double, std::size_t, long long>;


/**************************
 *                        *
 *  INITIALIZATION SETUP  *
 *                        *
 **************************/

template<typename T>
class VectorInitialization : public ::testing::Test { };
TYPED_TEST_SUITE(VectorInitialization, SupportedTypes);

/************************
 *                      *
 *  VECTOR COMPARISONS  *
 *                      *
 ************************/
template <typename T>
class VectorEquality: public ::testing::Test
{
protected:
	math::Vector4D<T> eqVecA;
	math::Vector4D<T> eqVecB;
	math::Vector4D<T> uneqVec;

	void SetUp() override
	{
		eqVecA = {T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589)};
		eqVecB = {T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589)};
		uneqVec = {T(7.1234568789), T(2.123458319), T(24.00), T(123.123489172589)};
	}
};
TYPED_TEST_SUITE(VectorEquality, SupportedArithmeticTypes);

template <typename T>
class VectorComparison: public ::testing::Test
{
protected:
	math::Vector4D<T> vecA;
	math::Vector4D<T> vecB;
	math::bVec4 expectedGT, expectedGTE, expectedLT, expectedLTE; // GT-> Greater Than, GTE-> Greater Than or Equal, LT -> Less than, LTE -> Less than or equal

	void SetUp() override
	{
		vecA = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
		vecB = { T(5.1234568789), T(1.123458319), T(8.123412593891), T(123.123489172589) };
		expectedGT = {false, true, false, false};
		expectedGTE = {false, true, false, true};
		expectedLT = {true, false, true, false};
		expectedLTE = {true, false, true, true};
	}
};
TYPED_TEST_SUITE(VectorComparison, SupportedArithmeticTypes);

/*********************************
 *                               *
 *  ARITHMETIC OPERATIONS SETUP  *
 *                               *
 *********************************/

template <typename T>
class Vector4DAddition : public ::testing::Test
{
protected:
	math::Vector4D<T> vecA;
	math::Vector4D<T> vecB;
	math::Vector4D<T> expected;

	void SetUp() override
	{
		vecA = { T(3), T(1), T(6), T(2) };
		vecB = { T(-8) , T(5), T(-2), T(5) };
		expected = { T(-5) , T(6), T(4), T(7) };
	}
};
TYPED_TEST_SUITE(Vector4DAddition, SupportedArithmeticTypes);


template <typename T>
class Vector4DSubtraction : public ::testing::Test
{
protected:
	math::Vector4D<T> vecA;
	math::Vector4D<T> vecB;
	math::Vector4D<T> expected;

	void SetUp() override
	{
		vecA = { T(95), T(11), T(-6), T(2) };
		vecB = { T(-8) , T(5), T(-2), T(-5) };
		expected = { T(103) , T(6), T(-4), T(7) };
	}
};
TYPED_TEST_SUITE(Vector4DSubtraction, SupportedArithmeticTypes);


template <typename T>
class Vector4DScalarMultiplication : public ::testing::Test
{
protected:
	math::Vector4D<T> vec;
	T scalar;
	math::Vector4D<T> expectedFloating;
	math::Vector4D<T> expectedIntegral;

	void SetUp() override
	{
		vec = { T(7), T(13), T(29), T(41) };
		scalar = T(2.123456789123456);
		expectedFloating = { T(14.864197523864192), T(27.604938258604928), T(61.580246884580224), T(87.061728354061696) };
		expectedIntegral = { T(14), T(26), T(58), T(82) };
	}
};
TYPED_TEST_SUITE(Vector4DScalarMultiplication, SupportedArithmeticTypes);


template<typename T>
class Vector4DScalarDivision : public ::testing::Test
{
protected:
	math::Vector4D<T> vec;
	T scalar;
	math::Vector4D<T> expected;

	void SetUp() override
	{
		vec = { T(17), T(31), T(59), T(73) };
		scalar = T(13);
		expected = { T(1.30769230769230769231), T(2.38461538461538461538), T(4.53846153846153846154), T(5.61538461538461538462) };
	}

};
TYPED_TEST_SUITE(Vector4DScalarDivision, SupportedArithmeticTypes);


/***********************
 *                     *
 *  DOT PRODUCT SETUP  *
 *                     *
 ***********************/
template <typename T>
class Vector4DDotProduct : public ::testing::Test
{
protected:
	math::Vector4D<T> vecA;
	math::Vector4D<T> vecB;

	math::Vector4D<T> vecAOrtho;
	math::Vector4D<T> vecBOrtho;

	T expected;

	T aDotA;

	void SetUp() override
	{
		vecA = { T(2), T(3), T(4), T(5) };
		vecB = { T(6), T(7), T(8), T(9) };
		vecAOrtho = { T(3), T(0), T(4), T(0) };
		vecBOrtho = { T(0), T(5), T(0), T(6) };
		expected = static_cast<T>(110);

		aDotA = static_cast<T>(54);
	}
};
TYPED_TEST_SUITE(Vector4DDotProduct, SupportedArithmeticTypes);


/***************************************
 *                                     *
 *  MAGNITUDE AND NORMALIZATION SETUP  *
 *                                     *
 ***************************************/

template <typename T>
class Vector4DMagnitude : public ::testing::Test
{
protected:
	math::Vector4D<T> vec;
	math::Magnitude<T> magnitude;

	void SetUp() override
	{
		vec = { T(1), T(2), T(2), T(4) };
		magnitude = math::Magnitude<T>(5);
	}
};
TYPED_TEST_SUITE(Vector4DMagnitude, SupportedArithmeticTypes);


template <typename T>
class Vector4DUncleanMagnitude : public ::testing::Test
{
protected:
	math::Vector4D<T> vec;
	math::Magnitude<T> magnitude;

	void SetUp() override
	{
		vec = { T(1), T(2), T(3), T(4) };
		magnitude = math::Magnitude<T>(5.477225575051661);
	}
};
TYPED_TEST_SUITE(Vector4DUncleanMagnitude, SupportedArithmeticTypes);


template <typename T>
class Vector4DNormalization : public ::testing::Test
{
	using R = math::Magnitude<T>;
protected:
	math::Vector4D<T> vec;
	math::Vector4D<R> expectedVector;

	void SetUp() override
	{
		vec = { T(14), T(27), T(83), T(52) };
		expectedVector = { static_cast<R>(0.13650905255670645), static_cast<R>(0.2632674585022196), static_cast<R>(0.8093036687290455), static_cast<R>(0.5070336237820525) };
	}
};
TYPED_TEST_SUITE(Vector4DNormalization, SupportedArithmeticTypes);


template <typename T>
class Vector4DZeroNormalization : public ::testing::Test
{
protected:
	math::Vector4D<T> vec;

	void SetUp() override
	{
		vec = { T(0), T(0), T(0), T(0) };
	}
};
TYPED_TEST_SUITE(Vector4DZeroNormalization, SupportedArithmeticTypes);


/*************************************
 *                                   *
 *  PROJECTIONS AND REJECTION SETUP  *
 *                                   *
 *************************************/
template <typename T>
class Vector4DProjection : public ::testing::Test
{
protected:
	math::Vector4D<T> vec;
	math::Vector4D<T> perpendicularVec;
	math::Vector4D<T> onto;
	math::Vector4D<T> expectedProjection;

	void SetUp() override
	{
		vec = { T(5), T(6), T(7), T(8) };
		perpendicularVec = { T(10), T(0), T(14), T(16) };
		onto = { T(0), T(2), T(0), T(0) };
		expectedProjection = { T(0), T(6), T(0), T(0) };
	}
};
TYPED_TEST_SUITE(Vector4DProjection, SupportedArithmeticTypes);

template <typename T>
class Vector4DRejection : public ::testing::Test
{
protected:
	math::Vector4D<T> vec;
	math::Vector4D<T> parallelVec;
	math::Vector4D<T> onto;
	math::Vector4D<T> expectedRejection;

	void SetUp() override
	{
		vec = { T(5), T(6), T(7), T(8) };
		parallelVec = { T(10), T(12), T(14), T(16) };
		onto = { T(0), T(2), T(0), T(0) };
		expectedRejection = { T(5), T(0), T(7), T(8) };
	}
};
TYPED_TEST_SUITE(Vector4DRejection, SupportedArithmeticTypes);



/***********************************************
 *                                             *
 *  INITIALIZATION, ACCESS AND MUTATION TESTS  *
 *                                             *
 ***********************************************/

TEST(VectorInitialization, EmptyConstructorInitializesZeroVector)
{
	// Given a vector initialized without parameters
	const math::Vector4D<float> vec;

	// Then, it's elements form a zero vector
	EXPECT_VEC_ZERO(vec);
}

TYPED_TEST(VectorInitialization, ConstructorInitializesVectorsWithCorrectValue)
{
	// Given 4 different values
	TypeParam a = static_cast<TypeParam>(3);
	TypeParam b = static_cast<TypeParam>(1);
	TypeParam c = static_cast<TypeParam>(6);
	TypeParam d = static_cast<TypeParam>(4);

	// When, a vector is initialized with those values
	const math::Vector4D<TypeParam> vec(a, b, c, d);

	// Then, the values are stored as elements of the vector
	EXPECT_VEQ_CONTAINS(vec, a, b, c, d);
}

TYPED_TEST(VectorInitialization, Two2DVectorsCanInitializeA4DVector)
{
	// Given two 2D Vectors
	TypeParam a = static_cast<TypeParam>(3);
	TypeParam b = static_cast<TypeParam>(1);
	TypeParam c = static_cast<TypeParam>(6);
	TypeParam d = static_cast<TypeParam>(4);
	const math::Vector2D<TypeParam> vec1(a, b);
	const math::Vector2D<TypeParam> vec2(c, d);

	// When a Vector4D is initialized with those vectors
	const math::Vector4D<TypeParam> vec(vec1, vec2);

	// Then, the 2D vector elements form the 4D vector
	EXPECT_VEQ_CONTAINS(vec, a, b, c, d);
}

TYPED_TEST(VectorInitialization, One3DVectorAndScalarCanInitializeA4DVector)
{
	// Given a 3D Vector and a scalar
	TypeParam a = static_cast<TypeParam>(3);
	TypeParam b = static_cast<TypeParam>(1);
	TypeParam c = static_cast<TypeParam>(6);
	const math::Vector3D vec1(a, b, c);
	TypeParam scalar = static_cast<TypeParam>(4);

	// When a Vector4D is initialized with those vectors
	const math::Vector4D vec(vec1, scalar);

	// Then, the 3D vector elements + scalar form the 4D vector in the passed-in format
	EXPECT_VEQ_CONTAINS(vec, a, b, c, scalar);
}

TEST(Vector4DConversionConstructor, ConversionConstructorCreatesNewVectorWithPromotedType)
{
	// Given a float vector
	math::Vector4D vec1(3.0f, 1.0f, 6.0f, 2.0f);

	// When it is converted to a double vector
	math::Vector4D<double> vec2(vec1);
	// And some values of new vector is mutated
	vec2.x = 5;

	// Then, the float vector remains unchanged
	ASSERT_FLOAT_EQ(3.0f, vec1.x);
	ASSERT_FLOAT_EQ(1.0f, vec1.y);
	ASSERT_FLOAT_EQ(6.0f, vec1.z);
	ASSERT_FLOAT_EQ(2.0f, vec1.w);

	// And, the new vector is of type double with the mutated value
	static_assert(std::is_same_v<typename decltype(vec2)::value_type, double>);
	ASSERT_DOUBLE_EQ(5.0, vec2.x);
	ASSERT_DOUBLE_EQ(1.0, vec2.y);
	ASSERT_DOUBLE_EQ(6.0, vec2.z);
	ASSERT_DOUBLE_EQ(2.0, vec2.w);
}

TEST(Vector4DConversionConstructor, ConversionConstructorCreatesNewVectorWithDemotedType)
{
	// Given a double vector
	math::Vector4D vec1(3.0, 1.0, 6.0, 2.0);

	// When it is converted to a float vector
	math::Vector4D<float> vec2(vec1);
	// And some values of new vector is mutated
	vec2.x = 5;

	// Then, the float vector remains unchanged
	ASSERT_DOUBLE_EQ(3.0, vec1.x);
	ASSERT_DOUBLE_EQ(1.0, vec1.y);
	ASSERT_DOUBLE_EQ(6.0, vec1.z);
	ASSERT_DOUBLE_EQ(2.0, vec1.w);

	// And, the new vector is of type float with the mutated value
	static_assert(std::is_same_v<typename decltype(vec2)::value_type, float>);
	ASSERT_FLOAT_EQ(5.0f, vec2.x);
	ASSERT_FLOAT_EQ(1.0f, vec2.y);
	ASSERT_FLOAT_EQ(6.0f, vec2.z);
	ASSERT_FLOAT_EQ(2.0f, vec2.w);

}

TEST(Vector4DMutation, ElementsCanBeMutatedAtGivenIndex)
{
	// Given a vector initialization without parameters
	math::Vector4D<float> vec;

	// When it's elements are mutated at a particular index
	vec[0] = 3.0f;
	vec[1] = 1.0f;
	vec[2] = 6.0f;
	vec[3] = 2.0f;

	// Then, it's element reflect the change
	EXPECT_FLOAT_EQ(3.0f, vec[0]);
	EXPECT_FLOAT_EQ(1.0f, vec[1]);
	EXPECT_FLOAT_EQ(6.0f, vec[2]);
	EXPECT_FLOAT_EQ(2.0f, vec[3]);
}

TEST(Vector4DAccess, AccessibleAsXYZ)
{
	// Given a vector with arbitrary values passed in
	const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

	// Then, it's elements are accessible as x, y, z, w
	EXPECT_FLOAT_EQ(3.0f, vec.x);
	EXPECT_FLOAT_EQ(1.0f, vec.y);
	EXPECT_FLOAT_EQ(6.0f, vec.z);
	EXPECT_FLOAT_EQ(2.0f, vec.w);
}

TEST(Vector4DAccess, AccessibleAsSTP)
{
	// Given a vector with arbitrary values passed in
	const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

	// Then, it's elements are accessible as s, t, p, q
	EXPECT_FLOAT_EQ(3.0f, vec.s);
	EXPECT_FLOAT_EQ(1.0f, vec.t);
	EXPECT_FLOAT_EQ(6.0f, vec.p);
	EXPECT_FLOAT_EQ(2.0f, vec.q);
}

TEST(Vector4DAccess, AccessibleAsRGB)
{
	// Given a vector with arbitrary values passed in
	const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

	// Then, it's elements are accessible as r, g, b, a
	EXPECT_FLOAT_EQ(3.0f, vec.r);
	EXPECT_FLOAT_EQ(1.0f, vec.g);
	EXPECT_FLOAT_EQ(6.0f, vec.b);
	EXPECT_FLOAT_EQ(2.0f, vec.a);
}

TEST(Vector4DAccess, AccessibleAsArray)
{
	// Given a vector with arbitrary values passed in
	const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

	// Then, it's elements are accessible as array elements
	EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
	EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
	EXPECT_FLOAT_EQ(6.0f, vec.elements[2]);
	EXPECT_FLOAT_EQ(2.0f, vec.elements[3]);
}

TEST(Vector4DHelper, bVec4Return4DBoolVector)
{
	// Given a vector is accessed as bVec4
	constexpr bool isCorrectType = std::is_same_v<math::bVec4::value_type, bool>;

	// Then, it's value_type is bool
	EXPECT_TRUE(isCorrectType);
}

TEST(Vector4DHelper, iVec4Return4DIntVector)
{
	// Given a vector is accessed as iVec4
	constexpr bool isCorrectType = std::is_same_v<math::iVec4::value_type, int>;

	// Then, it's value_type is int
	EXPECT_TRUE(isCorrectType);
}

TEST(Vector4DHelper, uVec4Return4DUnsignedIntVector)
{
	// Given a vector is accessed as uVec4
	constexpr bool isCorrectType = std::is_same_v<math::uVec4::value_type, unsigned int>;

	// Then, it's value_type is unsigned int
	EXPECT_TRUE(isCorrectType);
}

TEST(Vector4DHelper, vec4Return4DFloatVector)
{
	// Given a vector is accessed as vec4
	constexpr bool isCorrectType = std::is_same_v<math::vec4::value_type, float>;

	// Then, it's value_type is float
	EXPECT_TRUE(isCorrectType);
}

TEST(Vector4DHelper, lVec4Return4DLongLongVector)
{
	// Given a vector is accessed as lVec4
	constexpr bool isCorrectType = std::is_same_v<math::lVec4::value_type, long long>;

	// Then, it's value_type is long long
	EXPECT_TRUE(isCorrectType);
}

TEST(Vector4DHelper, dVec4Return4DUnsignedLongLongVector)
{
	// Given a vector is accessed as dVec4
	constexpr bool isCorrectType = std::is_same_v<math::dVec4::value_type, double>;

	// Then, it's value_type is double
	EXPECT_TRUE(isCorrectType);
}

TEST(Vector4DHelper, ulVec4Return4DFloatVector)
{
	// Given a vector is accessed as ulVec4
	constexpr bool isCorrectType = std::is_same_v<math::ulVec4::value_type, unsigned long long>;

	// Then, it's value_type is unsigned long long
	EXPECT_TRUE(isCorrectType);
}


/**********************
 *                    *
 *  COMPARISON TESTS  *
 *                    *
 **********************/

TYPED_TEST(VectorEquality, SimilarVectorsAreEqual)
{
	// When two equal vectors are compared for equality
	bool equality = this->eqVecA.equals(this->eqVecB);

	// Then, they are equal
	EXPECT_TRUE(equality);
}

TYPED_TEST(VectorEquality, DissimilarVectorsAreNotEqual)
{
	// When two equal vectors are compared for equality
	bool equality = this->eqVecA.equals(this->uneqVec);

	// Then, they are not equal
	EXPECT_FALSE(equality);
}

TYPED_TEST(VectorEquality, StaticWrapper_SimilarVectorsAreEqual)
{
	// When two equal vectors are compared for equality
	bool equality = this->eqVecA.equals(this->eqVecB);

	// Then, they are equal
	EXPECT_TRUE(equality);
}

TYPED_TEST(VectorEquality, StaticWrapper_DissimilarVectorsAreNotEqual)
{
	// When two equal vectors are compared for equality
	bool equality = math::Vector4D<TypeParam>::equals(this->eqVecA, this->uneqVec);

	// Then, they are not equal
	EXPECT_FALSE(equality);
}

TYPED_TEST(VectorEquality, EqualityOperator_SimilarVectorsReturnsTrue)
{
	// When two equal vectors are compared for equality
	bool equality = this->eqVecA == this->eqVecB;

	// Then, result is true
	EXPECT_TRUE(equality);
}

TYPED_TEST(VectorEquality, EqualityOperator_DissimilarVectorsReturnsFalse)
{
	// When two equal vectors are compared for equality
	bool equality = this->eqVecA == this->uneqVec;

	// Then, result is false
	EXPECT_FALSE(equality);
}

TYPED_TEST(VectorEquality, InEqualityOperator_SimilarVectorsReturnsFalse)
{
	// When two equal vectors are compared for equality
	bool equality = this->eqVecA != this->eqVecB;

	// Then, result is false
	EXPECT_FALSE(equality);
}

TYPED_TEST(VectorEquality, InEqualityOperator_DissimilarVectorsReturnsTrue)
{
	// When two equal vectors are compared for equality
	bool equality = this->eqVecA != this->uneqVec;

	// Then, result is true
	EXPECT_TRUE(equality);
}

TYPED_TEST(VectorEquality, MixedTypeEquality_SimilarVectorsReturnsTrue)
{
	// Given two similar vectors of different types
	const math::Vector4D vecA(1, 2, 3, 4);
	const math::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

	// When they are compared for equality
	bool equality = vecA == vecB;

	// Then, the result is true
	EXPECT_TRUE(equality);
}

TYPED_TEST(VectorEquality, MixedTypeEquality_DissimilarVectorsReturnsFalse)
{
	// Given two dissimilar vectors of different types
	const math::Vector4D vecA(5, 6, 7, 8);
	const math::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

	// When they are compared for inequality
	bool equality = vecA == vecB;

	// Then, the result is false
	EXPECT_FALSE(equality);
}

TYPED_TEST(VectorEquality, MixedTypeInequality_SimilarVectorsReturnsFalse)
{
	// Given two similar vectors of different types
	const math::Vector4D vecA(1, 2, 3, 4);
	const math::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

	// When they are compared for equality
	bool equality = vecA != vecB;

	// Then, the result is false
	EXPECT_FALSE(equality);
}

TYPED_TEST(VectorEquality, MixedTypeInequality_DissimilarVectorsReturnsTrue)
{
	// Given two dissimilar vectors of different types
	const math::Vector4D vecA(5, 6, 7, 8);
	const math::Vector4D vecB(1.0, 2.0, 3.0, 4.0);

	// When they are compared for inequality
	bool equality = vecA != vecB;

	// Then, the result is true
	EXPECT_TRUE(equality);
}

TEST(VectorEquality, EqualityOperator_SimilarBooleanVectorsReturnsTrue)
{
	// Given two similar boolean vectors
	const math::Vector4D vecA(true, false, true, false);
	const math::Vector4D vecB(true, false, true, false);

	// When they are compared for equality
	bool equality = vecA == vecB;

	// Then, the result is true
	EXPECT_TRUE(equality);
}

TEST(VectorEquality, EqualityOperator_DissimilarSimilarVectorsReturnsFalse)
{
	// Given two dissimilar boolean vectors
	const math::Vector4D vecA(true, false, true, false);
	const math::Vector4D vecB(true, true, true, false);

	// When they are compared for inequality
	bool equality = vecA == vecB;

	// Then, the result is false
	EXPECT_FALSE(equality);
}

TEST(VectorEquality, InequalityOperator_SimilarBooleanVectorsReturnsFalse)
{
	// Given two similar boolean vectors
	const math::Vector4D vecA(true, false, true, false);
	const math::Vector4D vecB(true, false, true, false);

	// When they are compared for equality
	bool equality = vecA != vecB;

	// Then, the result is false
	EXPECT_FALSE(equality);
}

TEST(VectorEquality, InequalityOperator_DissimilarBooleanVectorsReturnsFalse)
{
	// Given two dissimilar boolean vectors
	const math::Vector4D vecA(true, false, true, false);
	const math::Vector4D vecB(true, true, true, false);

	// When they are compared for inequality
	bool equality = vecA != vecB;

	// Then, the result is true
	EXPECT_TRUE(equality);
}


//TODO: Add test for bool vector == and !=

/*********************************
 *                               *
 *  SIMPLE MATH OPERATION TESTS  *
 *                               *
 *********************************/

TYPED_TEST(Vector4DAddition, VectorPlusVectorReturnsNewVectorWithSum)
{
	// Given two vectors
	// When they are added together
	const math::Vector4D result = this->vecA + this->vecB;

	// Then the output vector contains sum of elements
	EXPECT_VEC_EQ(this->expected, result);
}

TYPED_TEST(Vector4DAddition, VectorPlusEqualsReturnsSameVectorWithSum)
{
	//Given two vectors
	// When one vector is added to the other(+=)
	this->vecA += this->vecB;

	// Then, the original vector contains the sum of the elements added together
	EXPECT_VEC_EQ(this->expected, this->vecA);
}

TEST(Vector4DAddition, MixedTypeAdditionPromotesType)
{
	// Given vectors with arbitrary values
	const math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
	const math::Vector4D vec2(9.0, -5.0, 10.0, 3.0);
	const math::Vector4D expected(12.0, -5.0, 9.0, 5.0);

	// When they are added together
	const math::Vector4D result = vec1 + vec2;

	// Then the new vector is type promoted
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	// And contains sum of elements
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DAddition, MixedTypeAdditionAssignmentDoesNotPromoteType)
{
	// Given vectors with arbitrary values
	math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
	const math::Vector4D vec2(9.0, -5.0, 10.0, 3.0);
	const math::Vector4D expected(12.0f, -5.0f, 9.0f, 5.0f);

	// When one vector is added to the other(+=)
	vec1 += vec2;

	// Then, the original vector's type is preserved
	static_assert(std::is_same_v<typename decltype(vec1)::value_type, float>);
	// and contains sum of elements
	EXPECT_VEC_EQ(expected, vec1);
}

TYPED_TEST(Vector4DSubtraction, VectorMinusVectorReturnsNewVectorWithDifference)
{
	// Given two vectors
	// When they are added together
	const math::Vector4D result = this->vecA - this->vecB;

	// Then the output vector contains the difference between elements
	EXPECT_VEC_EQ(this->expected, result);
}

TYPED_TEST(Vector4DSubtraction, VectorMinusEqualsVectorReturnsSameVectorWithDifference)
{
	//Given two vectors
	// When one vector is added to the other(+=)
	this->vecA -= this->vecB;

	// Then, the original vector contains the difference between elements
	EXPECT_VEC_EQ(this->expected, this->vecA);
}

TEST(Vector4DSubtraction, MixedTypeSubtractionPromotesType)
{
	// Given vectors with arbitrary values
	const math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
	const math::Vector4D vec2(9.0, -5.0, 10.0, 3.0);
	const math::Vector4D expected(-6.0, 5.0, -11.0, -1.0);

	// When they are subtracted
	const math::Vector4D result = vec1 - vec2;

	// Then the new vector is type promoted
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	// And contains difference between the elements
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DSubtraction, MixedTypeSubtractionAssignmentDoesNotPromoteType)
{
	// Given vectors with arbitrary values
	math::Vector4D vec1(3.0f, 0.0f, -1.0f, 2.0f);
	const math::Vector4D vec2(9.0, -5.0, 10.0, 3.0);
	const math::Vector4D expected(-6.0, 5.0, -11.0, -1.0);

	// When one vector is subtracted from the other(-=)
	vec1 -= vec2;

	// Then, the original vector's type is preserved
	static_assert(std::is_same_v<typename decltype(vec1)::value_type, float>);
	// And contains difference between the elements
	EXPECT_VEC_EQ(expected, vec1);
}

TEST(Vector4DScalarMultiplication, VectorTimesZeroReturnsZeroVector)
{
	// Given an arbitrary vector
	const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

	// When multiplied with 0
	const math::Vector4D result = vec * 0;

	// Then, we get a zero vector
	EXPECT_VEC_ZERO(result);
}

TEST(Vector4DScalarMultiplication, VectorTimesOneReturnsVectorWithSameValues)
{
	// Given an arbitrary vector
	const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

	// When multiplied with 1
	const math::Vector4D result = vec * 1;

	// Then, we get the same vector
	EXPECT_VEC_EQ(vec, result);
}

TYPED_TEST(Vector4DScalarMultiplication, VectorTimesANumberReturnsAScaledVector)
{
	// Given an arbitrary vector and a scalar

	// When multiplied (vec * scalar)
	const math::Vector4D result = this->vec * this->scalar;

	// Then, new vector contains elements multiplied(scaled) with the scalar
	if (std::is_floating_point_v<TypeParam>)
		EXPECT_VEC_EQ(this->expectedFloating, result);
	else
		EXPECT_VEC_EQ(this->expectedIntegral, result);
}

TYPED_TEST(Vector4DScalarMultiplication, NumberTimesAVectorReturnsAScaledVector)
{
	// Given an arbitrary vector and a scalar

	// When multiplied (vec * scalar)
	const math::Vector4D result = this->scalar * this->vec;

	// Then, new vector contains elements multiplied(scaled) with the scalar
	if (std::is_floating_point_v<TypeParam>)
		EXPECT_VEC_EQ(this->expectedFloating, result);
	else
		EXPECT_VEC_EQ(this->expectedIntegral, result);
}

TYPED_TEST(Vector4DScalarMultiplication, VectorTimesEqualAScalarIsTheSameVectorScaled)
{
	// Given an arbitrary vector and a scalar

	// When multiplied (vec * scalar)
	this->vec *= this->scalar;

	// Then, the original vector is scaled by the scalar
	if (std::is_floating_point_v<TypeParam>)
		EXPECT_VEC_EQ(this->expectedFloating, this->vec);
	else
		EXPECT_VEC_EQ(this->expectedIntegral, this->vec);
}

TYPED_TEST(Vector4DScalarMultiplication, MixedTypeScalarMulitplicationPromotesType)
{
	// Given a vector and scalar with arbitrary values
	constexpr double scalar = 2.123456789123456;
	const math::Vector4D expected(14.864197523864192, 27.604938258604928, 61.580246884580224, 87.061728354061696);

	// When they are multiplied
	const math::Vector4D result = this->vec * scalar;

	// Then the new vector is type promoted
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);

	// And the vector is scaled by `scalar`
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DScalarMultiplication, MixedTypeScalarMulitplicationAssignmentDoesNotPromoteType)
{
	// Given a vector and scalar with arbitrary values
	math::Vector4D vec(3.0f, 0.0f, -1.0f, 2.0f);
	constexpr double scalar = 5.0;
	const math::Vector4D expected(15.0f, 0.0f, -5.0f, 10.0f);

	// When vector is multiplied by the scalar and assigned (*=)
	vec *= scalar;

	// Then the vector type is preserved
	static_assert(std::is_same_v<typename decltype(vec)::value_type, float>);
	// And the vector is scaled by `scalar`
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector4DScalarMultiplication, MixedTypeScalarMulitplicationAssignmentGivesResultWithMinimalPrecisionLoss)
{
	// Given a vector and scalar with arbitrary values
	math::Vector4D vec(3, 0, -1, 8);
	constexpr double scalar = 2.5;
	const math::Vector4D expected(7, 0, -2, 20);

	// When vector is multiplied by the scalar and assigned (*=)
	vec *= scalar;

	// And the vector is scaled by `scalar` with minimal precision loss
	EXPECT_VEC_EQ(expected, vec);
}

TYPED_TEST(Vector4DScalarDivision, VectorDividedByZeroReturnsInfinityVector)
{
	// Given an arbitrary vector

	// Floating point
	if constexpr (std::is_floating_point_v<TypeParam>)
	{
		// When divided by zero
		const math::Vector4D result = this->vec / 0;

		// Then, the resultant vector is an infinity vector
		EXPECT_VEC_INF(result);
	} // Integrals
	else
	{
		EXPECT_DEATH({ this->vec / 0; }, "Integral division by zero");
	}
}

TYPED_TEST(Vector4DScalarDivision, VectorDividedByOneReturnsAVectorWithSameValues)
{
	// Given an arbitrary vector

	// When divided by one
	const math::Vector4D result = this->vec / 1;

	// Then, the resultant vector is an infinity vector
	EXPECT_VEC_EQ(result, this->vec);
}

TYPED_TEST(Vector4DScalarDivision, VectorDividedByANumberReturnsAScaledVector)
{
	// Given an arbitrary vector

	// When divided by a scalar
	const math::Vector4D result = this->vec / this->scalar;

	// Then, the resultant vector is a new vector with elements divided by the scalar
	EXPECT_VEC_EQ(this->expected, result);
}

TYPED_TEST(Vector4DScalarDivision, VectorDivideEqualsANumberIsTheSameVectorScaled)
{
	// Given an arbitrary vector

	// When divide equals by a scalar
	this->vec /= this->scalar;

	// Then, the resultant vector is the same vector with elements divided by the scalar
	EXPECT_VEC_EQ(this->expected, this->vec);
}

TEST(Vector4DScalarDivision, MixedTypeScalarDivisionPromotesType)
{
	// Given an arbitrary vector
	const math::Vector4D vec(15.0, 0.0, -5.0, 10.0);
	constexpr double scalar = 5.0;
	const math::Vector4D expected(3.0f, 0.0f, -1.0f, 2.0f);

	// When divided by a scalar
	const math::Vector4D result = vec / scalar;

	// Then the new vector is type promoted
	static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
	// And the vector is scaled by `scalar`
	EXPECT_VEC_EQ(expected, result);
}

TEST(Vector4DScalarDivision, MixedTypeScalarDivisonAssignmentDoesNotPromoteType)
{
	// Given an arbitrary vector
	math::Vector4D vec(15.0f, 0.0f, -5.0f, 10.0f);
	constexpr double scalar = 5.0;

	const math::Vector4D expected(3.0f, 0.0f, -1.0f, 2.0f);

	// When divide equals by a scalar
	vec /= scalar;

	// Then the vector type is preserved
	static_assert(std::is_same_v<typename decltype(vec)::value_type, float>);
	// And the vector is scaled by `scalar`
	EXPECT_VEC_EQ(expected, vec);
}

TEST(Vector4DScalarDivision, MixedTypeScalarDivisionAssignmentGivesResultWithMinimalPrecisionLoss)
{
	// Given an arbitrary vector
	math::Vector4D vec(10, 25, -30, 2);
	constexpr double scalar = 2.5;
	const math::Vector4D expected(4, 10, -12, 0);

	// When vector divides equal by a scalar
	vec /= scalar;

	// And the vector is scaled by `scalar` with minimal precision loss
	EXPECT_VEC_EQ(expected, vec);
}


/***********************
 *                     *
 *  DOT PRODUCT TESTS  *
 *                     *
 ***********************/

TYPED_TEST(Vector4DDotProduct, VectorWhenDotWithItselfSquareMagnitude)
{
	// Given an arbitrary vector

	// When dot with itself
	const TypeParam result = this->vecA.dot(this->vecA);

	// Then, the dot product is 1
	if constexpr (std::is_same_v<TypeParam, double>)
		EXPECT_DOUBLE_EQ(this->aDotA, result);
	else if constexpr (std::is_floating_point_v<TypeParam>)
		EXPECT_FLOAT_EQ(this->aDotA, result);
	else
		EXPECT_EQ(this->aDotA, result);
}

TYPED_TEST(Vector4DDotProduct, VectorWhenDotWithOrthogonalVectorReturnZero)
{
	// Given two orthogonal vectors

	// When dot with each other
	const TypeParam result = this->vecAOrtho.dot(this->vecBOrtho);

	// Then, the dot product is 0
	if constexpr (std::is_same_v<TypeParam, double>)
		EXPECT_DOUBLE_EQ(0.0, result);
	else if constexpr (std::is_floating_point_v<TypeParam>)
		EXPECT_FLOAT_EQ(0.0f, result);
	else
		EXPECT_EQ(0, result);
}

TYPED_TEST(Vector4DDotProduct, VectorDotWithNonOrthogonalVectorIsNonZeroNumber)
{
	// Given two non-orthogonal vectors

	// When dot with each other
	const TypeParam result = this->vecA.dot(this->vecB);

	// Then, the dot product is non-zero
	if constexpr (std::is_same_v<TypeParam, double>)
		EXPECT_DOUBLE_EQ(this->expected, result);
	else if constexpr (std::is_floating_point_v<TypeParam>)
		EXPECT_FLOAT_EQ(this->expected, result);
	else
		EXPECT_EQ(this->expected, result);
}

TYPED_TEST(Vector4DDotProduct, StaticWrapper_VectorDotWithNonParallelVectorIsNonZeroNumber)
{
	// Given two non-orthogonal vectors

	// When dot with each other with static wrapper
	const TypeParam result = math::Vector4D<TypeParam>::dot(this->vecA, this->vecB);

	// Then, the dot product is non-zero
	if constexpr (std::is_same_v<TypeParam, double>)
		EXPECT_DOUBLE_EQ(this->expected, result);
	else if constexpr (std::is_floating_point_v<TypeParam>)
		EXPECT_FLOAT_EQ(this->expected, result);
	else
		EXPECT_EQ(this->expected, result);
}

TEST(Vector4DDotProduct, VectorDotWithOppositeVectorIsNegative)
{
	// Given two opposite vectors
	const math::Vector4D vecA(-1.0, 0.0, 0.0, 0.0);
	const math::Vector4D vecB(1.0, 0.0, 0.0, 0.0);

	// When dot with each other
	const double result = vecA.dot(vecB);

	// Then, the dot product is -1
	EXPECT_DOUBLE_EQ(-1.0, result);
}

TEST(Vector4DDotProduct, MixedTypeDotProductPromotesType)
{
	// Given two vectors of different type
	const math::Vector4D vecA(7, 13, 29, 41);
	const math::Vector4D vecB(1.123456789, 2.123456789, 3.123456789, 4.123456789);

	// When dot with each other
	const auto result = vecA.dot(vecB);

	// Then, the dot product is type promoted
	static_assert(std::is_same_v<decltype(result), const double>);

	// Then, the dot product is non-zero
	EXPECT_DOUBLE_EQ(295.11111101, result);
}


/***************************************
 *                                     *
 *  MAGNITUDE AND NORMALIZATION TESTS  *
 *                                     *
 ***************************************/

TEST(Vector4DMagnitude, ZeroVectorReturnsZero)
{
	// Given a zero vector
	const math::Vector4D vec(0.0f, 0.0f, 0.0f, 0.0f);

	// When its magnitude is taken
	const float magnitude = vec.mag();

	// Then, zero is returned
	EXPECT_FLOAT_EQ(0.0f, magnitude);
}

TEST(Vector4DMagnitude, VectorWithOneComponentsReturnsNonUnitScalar)
{
	// Given a unit vector
	const math::Vector4D vec(1.0f, 1.0f, 1.0f, 1.0f);

	// When its magnitude is taken
	const float magnitude = vec.mag();

	// Then, non-unit number is returned
	EXPECT_NE(1.0f, magnitude);
}

TYPED_TEST(Vector4DMagnitude, NonUnitVectorReturnsCorrectMagnitude)
{
	// Given an arbitrary vector

	// When its magnitude is taken
	const auto result = this->vec.mag();

	// Then, a non-unit number is returned which is a floating_v
	static_assert(std::is_floating_point_v<decltype(result)>);
	EXPECT_MAG_EQ(this->magnitude, result);

}

TYPED_TEST(Vector4DMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
	// Given an arbitrary vector

	// When its magnitude is taken
	const auto result = math::Vector4D<TypeParam>::mag(this->vec);

	// Then, a non-unit number is returned which is a floating_v
	static_assert(std::is_floating_point_v<decltype(result)>);
	EXPECT_MAG_EQ(this->magnitude, result);
}

TYPED_TEST(Vector4DUncleanMagnitude, NonUnitVectorReturnsCorrectMagnitudeWithPrecision)
{
	// Given an arbitrary vector

	// When its magnitude is taken
	const auto result = this->vec.mag();

	// Then, a non-unit number is returned which is a floating_v
	static_assert(std::is_floating_point_v<decltype(result)>);
	EXPECT_MAG_EQ(this->magnitude, result);
}

TYPED_TEST(Vector4DUncleanMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitudeWithPrecision)
{
	// Given an arbitrary vector

	// When its magnitude is taken
	const auto result = math::Vector4D<TypeParam>::mag(this->vec);

	// Then, a non-unit number is returned which is a floating_v
	static_assert(std::is_floating_point_v<decltype(result)>);
	EXPECT_MAG_EQ(this->magnitude, result);
}

TEST(Vector4DNormalization, ZeroVectorWhenNormalizedCausesDeath)
{
	// Given a zero vector
	const math::Vector4D vec(0.0, 0.0, 0.0, 0.0);

	// When its magnitude is taken
	// Assertion is thrown
	EXPECT_DEATH({ vec.normalize(); }, "Vector4D Normalization : Division by 0");
}

TYPED_TEST(Vector4DNormalization, VectorWhenNormalizedReturnsANormalVector)
{
	// Given a non-normalized vector

	// When it is normalized
	const math::Vector4D normalized = this->vec.normalize();

	// Then, the resultant vector is normalized
	EXPECT_VEC_EQ(this->expectedVector, normalized);
}

TYPED_TEST(Vector4DNormalization, StaticWrapper_VectorWhenNormalizedReturnsANormalVector)
{
	// Given a non-normalized vector

	// When it is normalized
	const math::Vector4D normalized = math::Vector4D<TypeParam>::normalize(this->vec);

	// Then, the resultant vector is normalized
	EXPECT_VEC_EQ(this->expectedVector, normalized);
}


/************************************
 *                                  *
 *  PROJECTION AND REJECTION TESTS  *
 *                                  *
 ************************************/

TYPED_TEST(Vector4DProjection, OrthogonalVectorsWhenProjectedReturnsNonZeroVector)
{
	// Given two orthogonal vectors

	// When projected onto another
	const math::Vector4D actualProjection = this->perpendicularVec.project(this->onto);

	// Then, the resultant is a zero vector
	EXPECT_VEC_ZERO(actualProjection);
}

TEST(Vector4DProjection, VectorProjectedOntoXAxisProducesVectorWithOnlyXComponent)
{
	// Given an arbitrary vector
	const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
	const math::Vector4D xAxis(1.0f, 0.0f, 0.0f, 0.0f);
	const math::Vector4D expectedProjection(10.0f, 0.0f, 0.0f, 0.0f);

	// When projected onto x-axis
	const math::Vector4D actualProjection = a.project(xAxis);

	// Then, the resultant vector only has x-component as non-zero
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector4DProjection, VectorProjectedOntoYAxisProducesVectorWithOnlyYComponent)
{
	// Given an arbitrary vector
	const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
	const math::Vector4D yAxis(0.0f, 1.0f, 0.0f, 0.0f);
	const math::Vector4D expectedProjection(0.0f, 20.0f, 0.0f, 0.0f);

	// When projected onto y-axis
	const math::Vector4D actualProjection = a.project(yAxis);

	// Then, the resultant vector only has y-component as non-zero
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector4DProjection, VectorProjectedOntoZAxisProducesVectorWithOnlyZComponent)
{
	// Given an arbitrary vector
	const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
	const math::Vector4D zAxis(0.0f, 0.0f, 1.0f, 0.0f);
	const math::Vector4D expectedProjection(0.0f, 0.0f, 30.0f, 0.0f);

	// When projected onto z-axis
	const math::Vector4D actualProjection = a.project(zAxis);

	// Then, the resultant vector only has z-component as non-zero
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector4DProjection, VectorProjectedOntoWAxisProducesVectorWithOnlyWComponent)
{
	// Given an arbitrary vector
	const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
	const math::Vector4D wAxis(0.0f, 0.0f, 0.0f, 1.0f);
	const math::Vector4D expectedProjection(0.0f, 0.0f, 0.0f, 40.0f);

	// When projected onto w-axis
	const math::Vector4D actualProjection = a.project(wAxis);

	// Then, the resultant vector only has w-component as non-zero
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TYPED_TEST(Vector4DProjection, VectorsWhenProjectedReturnsNonZeroVector)
{
	// Given an arbitrary vector

	// When projected onto another vector
	const math::Vector4D actualProjection = this->vec.project(this->onto);

	// Then, the resultant vector has components that is parallel to the projected vector
	EXPECT_VEC_EQ(this->expectedProjection, actualProjection);
}

TYPED_TEST(Vector4DProjection, StaticWrapper_VectorsWhenProjectedReturnsNonZeroVector)
{
	// Given an arbitrary vector

	// When projected onto another vector
	const math::Vector4D actualProjection = math::Vector4D<TypeParam>::project(this->vec, this->onto);

	// Then, the resultant vector has components that is parallel to the projected vector
	EXPECT_VEC_EQ(this->expectedProjection, actualProjection);
}

TEST(Vector4DProjection, VectorProjectedOntoNormalizedVectorReturnsNonZeroVector)
{
	// Given an arbitrary vector and a normalized vector
	const math::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
	const math::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
	const math::Vector4D expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

	// When the vector is projected onto the normalized vector
	const math::Vector4D actualProjection = a.project(b, true);

	// Then, the resultant vector has components that is parallel to the projected vector
	EXPECT_FLOAT_EQ(expectedProjection.x, actualProjection.x);
	EXPECT_FLOAT_EQ(expectedProjection.y, actualProjection.y);
	EXPECT_FLOAT_EQ(expectedProjection.z, actualProjection.z);
	EXPECT_FLOAT_EQ(expectedProjection.w, actualProjection.w);
}

TEST(Vector4DProjection, VectorProjectedOntoNegativeVectorReturnsNonZeroVectorInSameDirection)
{
	// Given an arbitrary vector and a vector in the opposite Direction
	const math::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
	const math::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
	const math::Vector4D expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);

	// When projected
	const math::Vector4D<float> actualProjection = a.project(negativeZAxis);

	// Then, the resultant vector is non-zero and in the same direction
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

TEST(Vector4DProjection, MixedTypeVectorProjectionPromotesType)
{
	// Given two arbitrary vectors
	const math::Vector4D vec(7, 13, 29, 41);
	const math::Vector4D onto(2.0, 4.0, 4.0, 2.0);
	const math::Vector4D expectedProjection(13.2, 26.4, 26.4, 13.2);

	// When projected onto another
	const math::Vector4D actualProjection = vec.project(onto);

	// Then, the resultant vector is type promoted
	static_assert(std::is_same_v<typename decltype(actualProjection)::value_type, double>);
	// and is the projection
	EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TYPED_TEST(Vector4DRejection, ParallelVectorsWhenRejectedReturnsZeroVector)
{
	// Given two parallel vectors

	// When rejected onto another
	const math::Vector4D actualRejection = this->vec.reject(this->parallelVec);

	// Then, the resultant vector is zero
	EXPECT_VEC_ZERO(actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoXAxisReturnsVectorWithoutXComponent)
{
	// Given an arbitrary vector
	const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
	const math::Vector4D xAxis(1.0f, 0.0f, 0.0f, 0.0f);
	const math::Vector4D expectedRejection(0.0f, 20.0f, 30.0f, 40.f);

	// When rejected onto x-axis
	const math::Vector4D actualRejection = a.reject(xAxis);

	// Then, the resultant vector has no x-component
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoYAxisReturnsVectorWithoutYComponent)
{
	// Given an arbitrary vector
	const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
	const math::Vector4D yAxis(0.0f, 1.0f, 0.0f, 0.0f);
	const math::Vector4D expectedRejection(10.0f, 0.0f, 30.0f, 40.0f);

	// When rejected onto y-axis
	const math::Vector4D actualRejection = a.reject(yAxis);

	// Then, the resultant vector has no y-component
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoZAxisReturnsVectorWithoutZComponent)
{
	// Given an arbitrary vector
	const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
	const math::Vector4D zAxis(0.0f, 0.0f, 1.0f, 0.0f);
	const math::Vector4D expectedRejection(10.0f, 20.0f, 0.0f, 40.0f);

	// When rejected onto z-axis
	const math::Vector4D actualRejection = a.reject(zAxis);

	// Then, the resultant vector has no z-component
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoWAxisReturnsVectorWithoutWComponent)
{
	// Given an arbitrary vector
	const math::Vector4D a(10.0f, 20.0f, 30.0f, 40.0f);
	const math::Vector4D wAxis(0.0f, 0.0f, 0.0f, 1.0f);
	const math::Vector4D expectedRejection(10.0f, 20.0f, 30.0f, 0.0f);

	// When rejected onto w-axis
	const math::Vector4D actualRejection = a.reject(wAxis);

	// Then, the resultant vector has no w-component
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoNonExistantComponentReturnsSameVector)
{
	// Given an arbitrary vector
	const math::Vector4D a(1.0f, 2.0f, 3.0f, 0.0f);
	const math::Vector4D b(0.0f, 0.0f, 0.0f, 1.0f);

	// When rejected on to non-existent component vector
	const math::Vector4D actualRejection = a.reject(b);

	// Then, the resultant is same the original vector
	EXPECT_VEC_EQ(a, actualRejection);
}

TYPED_TEST(Vector4DRejection, VectorWhenRejectedReturnNonZeroVector)
{
	// Given an arbitrary vector

	// When rejected onto another
	const math::Vector4D actualRejection = this->vec.reject(this->onto);

	// Then, the resultant vector has components non-parallel to onto vector.
	EXPECT_VEC_EQ(this->expectedRejection, actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoNormalizedVectorReturnNonZeroVector)
{
	// Given an arbitrary vector and a normalized vector
	const math::Vector4D a(1.0f, 2.0f, 3.0f, 4.0f);
	const math::Vector4D b(1.0f, 0.0f, 0.0f, 0.0f);
	const math::Vector4D expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

	// When rejected onto another
	const math::Vector4D actualRejection = a.reject(b, true);

	// Then, the resultant vector has components non-parallel to onto vector.
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TEST(Vector4DRejection, VectorRejectedOntoNegativeVectorReturnsNonZeroVectorInSameDirection)
{
	// Given an arbitrary vector
	const math::Vector4D a(4.0f, 4.0f, 4.0f, 4.0f);
	const math::Vector4D negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
	const math::Vector4D expectedRejection(4.0f, 4.0f, 0.0f, 4.0f);

	// When rejection onto a vector in opposite direction
	const math::Vector4D actualRejection = a.reject(negativeZAxis);

	// Then, the resultant vector has components non-parallel to onto vector in the same direction.
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

TYPED_TEST(Vector4DRejection, StaticWrapper_VectorWhenRejectedReturnNonZeroVector)
{
	// Given an arbitrary vector

	// When rejected onto another
	const math::Vector4D actualRejection = math::Vector4D<TypeParam>::reject(this->vec, this->onto);

	// Then, the resultant vector has components non-parallel to onto vector.
	EXPECT_VEC_EQ(this->expectedRejection, actualRejection);
}

TEST(Vector4DRejection, MixedTypeVectorRejectionPromotesType)
{
	// Given two arbitrary vectors
	const math::Vector4D vec(7, 13, 29, 41);
	const math::Vector4D onto(2.0, 4.0, 4.0, 2.0);
	const math::Vector4D expectedRejection(-6.2, -13.4, 2.6, 27.8);

	// When projected onto another
	const math::Vector4D actualRejection = vec.reject(onto);

	// Then, the resultant vector is type promoted
	static_assert(std::is_same_v<typename decltype(actualRejection)::value_type, double>);
	// and is the rejection
	EXPECT_VEC_EQ(expectedRejection, actualRejection);
}