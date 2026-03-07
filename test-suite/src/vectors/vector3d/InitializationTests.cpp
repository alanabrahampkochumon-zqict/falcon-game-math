#include "Vector3DTestSetup.h"

using namespace TestUtils;

template <typename T>
class Vector3DInitialization: public ::testing::Test
{
};
TYPED_TEST_SUITE(Vector3DInitialization, SupportedTypes);


TYPED_TEST(Vector3DInitialization, EmptyConstructorInitializesZeroVector)
{
    // Given a vector initialized without parameters
    const math::Vector3D<TypeParam> vec;

    // Then, it's elements form a zero vector
    EXPECT_VEC_ZERO(vec);
}

TYPED_TEST(Vector3DInitialization, ConstructorParametersInitializesVector)
{
    // Given 3 different values
    TypeParam a = static_cast<TypeParam>(3);
    TypeParam b = static_cast<TypeParam>(1);
    TypeParam c = static_cast<TypeParam>(6);

    // When, a vector is initialized with those values
    const math::Vector3D<TypeParam> vec(a, b, c);

    // Then, the values are stored as elements of the vector
    EXPECT_VEQ_CONTAINS(vec, a, b, c);
}

TYPED_TEST(Vector3DInitialization, One2DVectorAndScalarCanInitializeA3DVector)
{
    // Given one 2D Vector and a scalar
    TypeParam a = static_cast<TypeParam>(3);
    TypeParam b = static_cast<TypeParam>(1);
    const math::Vector2D<TypeParam> vec1(a, b);
    TypeParam scalar = static_cast<TypeParam>(6);

    // When a Vector3D is initialized with that vec2d and scalar
    const math::Vector3D<TypeParam> vec(vec1, scalar);

    // Then, the 2D vector elements + scalar form the 3D vector in the passed-in format
    EXPECT_VEQ_CONTAINS(vec, a, b, scalar);
}