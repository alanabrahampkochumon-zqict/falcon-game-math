/**
 * @file MagnitudeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref Vector4D<bool> magnitude and normalization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"

using namespace testutils;


/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector4DMagnitude: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> vec;
    fgm::Magnitude<T> magnitude;

    void SetUp() override
    {
        vec = { T(1), T(2), T(2), T(4) };
        magnitude = fgm::Magnitude<T>(5);
    }
};
/** @brief Test fixture for @ref fgm::Vector4D magnitude, parameterized by SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DMagnitude, SupportedArithmeticTypes);


template <typename T>
class Vector4DUncleanMagnitude: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> vec;
    fgm::Magnitude<T> magnitude;

    void SetUp() override
    {
        vec = { T(1), T(2), T(3), T(4) };
        magnitude = fgm::Magnitude<T>(5.477225575051661);
    }
};
/** @brief Test fixture for @ref fgm::Vector4D magnitude, parameterized by SupportedArithmeticTypes, for testing
 * high-precision magnitude. */
TYPED_TEST_SUITE(Vector4DUncleanMagnitude, SupportedArithmeticTypes);


template <typename T>
class Vector4DNormalization: public ::testing::Test
{
    using R = fgm::Magnitude<T>;

    protected:
    fgm::Vector4D<T> vec;
    fgm::Vector4D<R> expectedVector;

    void SetUp() override
    {
        vec = { T(14), T(27), T(83), T(52) };
        expectedVector = { static_cast<R>(0.13650905255670645), static_cast<R>(0.2632674585022196),
                           static_cast<R>(0.8093036687290455), static_cast<R>(0.5070336237820525) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D normalization, parameterized by SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DNormalization, SupportedArithmeticTypes);


template <typename T>
class Vector4DZeroNormalization: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> vec;

    void SetUp() override
    {
        vec = { T(0), T(0), T(0), T(0) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D zero-vector normalization, parameterized by SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DZeroNormalization, SupportedArithmeticTypes);




/**
 * @addtogroup T_FGM_Vec4_Magnitude
 * @{
 */

/**************************************
 *                                    *
 *           MAGNITUDE TESTS          *
 *                                    *
 **************************************/

/** @test Verify that the magnitude of a zero @ref fgm::Vector4D returns exactly zero. */
TEST(Vector4DMagnitude, ZeroVectorReturnsZero)
{
    constexpr fgm::Vector4D vec(0.0f, 0.0f, 0.0f, 0.0f);

    EXPECT_FLOAT_EQ(0.0f, vec.mag());
}

/** @test Verify that the magnitude of a @ref fgm::Vector4D with multiple unit-component returns non-unit magnitude. */
TEST(Vector4DMagnitude, OneComponentVectorReturnsNonUnitScalar)
{
    constexpr fgm::Vector4D vec(1.0f, 1.0f, 1.0f, 1.0f);

    EXPECT_NE(1.0f, vec.mag());
}

/** @test Verify that the magnitude of a non-unit @ref fgm::Vector4D returns a non-unit magnitude. */
TYPED_TEST(Vector4DMagnitude, NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = this->vec.mag();

    static_assert(std::is_floating_point_v<decltype(magnitude)>);
    EXPECT_MAG_EQ(this->magnitude, magnitude);
}

/**
 * @test Verify that the @ref fgm::Vector4D magnitude calculation results in a floating-point type, regardless of the
 *       component type.
 */
TYPED_TEST(Vector4DMagnitude, MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = this->vec.mag();
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}

/** @test Verify that the static magnitude wrapper of @ref fgm::Vector4D returns a non-unit magnitude. */
TYPED_TEST(Vector4DMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = fgm::Vector4D<TypeParam>::mag(this->vec);

    EXPECT_MAG_EQ(this->magnitude, magnitude);
}

/**
 * @test Verify the numerical accuracy of @ref fgm::Vector4D magnitude calculations for non-unit vectors to ensure
 *        minimal precision loss.
 */
TYPED_TEST(Vector4DUncleanMagnitude, NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = this->vec.mag();

    EXPECT_MAG_EQ(this->magnitude, magnitude);
}

/**
 * @test Verify the numerical accuracy of @ref fgm::Vector4D static magnitude wrapper for non-unit vectors ensure
 *        minimal precision loss.
 */
TYPED_TEST(Vector4DUncleanMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = fgm::Vector4D<TypeParam>::mag(this->vec);

    EXPECT_MAG_EQ(this->magnitude, magnitude);
}

/** @} */




/**
 * @addtogroup T_FGM_Vec4_Normalize
 * @{
 */

/**************************************
 *                                    *
 *        NORMALIZATION TESTS         *
 *                                    *
 **************************************/

/** @test Verify that attempting to normalize a zero-magnitude @ref fgm::Vector4D results in program termination. */
TEST(Vector4DNormalization, ZeroVectorWhenNormalizationCausesDeath)
{
    constexpr fgm::Vector4D vec(0.0, 0.0, 0.0, 0.0);

    EXPECT_DEATH({ vec.normalize(); }, "Vector4D Normalization : Division by 0");
}


/** @test Verify that normalizing a @ref fgm::Vector4D returns a unit vector. */
TYPED_TEST(Vector4DNormalization, NonZeroVectorNormalizationReturnsUnitVector)
{
    const fgm::Vector4D normalized = this->vec.normalize();

    EXPECT_VEC_EQ(this->expectedVector, normalized);
}


/** @test Verify that @ref fgm::Vector4D static wrapper normalization returns a unit vector. */
TYPED_TEST(Vector4DNormalization, StaticWrapper_NonZeroVectorNormalizationReturnsUnitVector)
{

    const fgm::Vector4D normalized = fgm::Vector4D<TypeParam>::normalize(this->vec);

    EXPECT_VEC_EQ(this->expectedVector, normalized);
}


/**
 * @test Verify that the @ref fgm::Vector4D normalization results in a floating-point type, regardless of the
 *       component type.
 */
TYPED_TEST(Vector4DNormalization, NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->vec.normalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}

/** @} */