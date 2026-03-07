#include "Vector4DTestSetup.h"

using namespace TestUtils;


/***********
 *         *
 *  SETUP  *
 *         *
 ***********/

template <typename T>
class Vector4DMagnitude: public ::testing::Test
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
class Vector4DUncleanMagnitude: public ::testing::Test
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
class Vector4DNormalization: public ::testing::Test
{
    using R = math::Magnitude<T>;

    protected:
    math::Vector4D<T> vec;
    math::Vector4D<R> expectedVector;

    void SetUp() override
    {
        vec = { T(14), T(27), T(83), T(52) };
        expectedVector = { static_cast<R>(0.13650905255670645), static_cast<R>(0.2632674585022196),
                           static_cast<R>(0.8093036687290455), static_cast<R>(0.5070336237820525) };
    }
};
TYPED_TEST_SUITE(Vector4DNormalization, SupportedArithmeticTypes);


template <typename T>
class Vector4DZeroNormalization: public ::testing::Test
{
    protected:
    math::Vector4D<T> vec;

    void SetUp() override { vec = { T(0), T(0), T(0), T(0) }; }
};
TYPED_TEST_SUITE(Vector4DZeroNormalization, SupportedArithmeticTypes);


/*********************
 *                   *
 *  MAGNITUDE TESTS  *
 *                   *
 *********************/

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


/*************************
 *                       *
 *  NORMALIZATION TESTS  *
 *                       *
 *************************/

TEST(Vector4DNormalization, ZeroVectorWhenNormalizedCausesDeath)
{
    // Given a zero vector
    const math::Vector4D vec(0.0, 0.0, 0.0, 0.0);

    // When its magnitude is taken
    // Assertion is thrown
    EXPECT_DEATH({ vec.normalize(); }, "Vector4D Normalization : Division by 0");
}

TYPED_TEST(Vector4DNormalization, VectorWhenNormalizedReturnsAUnitVector)
{
    // Given a non-normalized vector

    // When it is normalized
    const math::Vector4D normalized = this->vec.normalize();

    // Then, the resultant vector is normalized
    EXPECT_VEC_EQ(this->expectedVector, normalized);
}

TYPED_TEST(Vector4DNormalization,
           StaticWrapper_VectorWhenNormalizedReturnsAUnitVectorWhenDotWithItselfSquareMagnitudeVector)
{
    // Given a non-normalized vector

    // When it is normalized
    const math::Vector4D normalized = math::Vector4D<TypeParam>::normalize(this->vec);

    // Then, the resultant vector is normalized
    EXPECT_VEC_EQ(this->expectedVector, normalized);
}
