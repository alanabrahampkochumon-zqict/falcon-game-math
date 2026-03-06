#include "Vector4DTestSetup.h"

using namespace TestUtils;

template<typename T>
class VectorInitialization : public ::testing::Test {};
TYPED_TEST_SUITE(VectorInitialization, SupportedTypes);


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
