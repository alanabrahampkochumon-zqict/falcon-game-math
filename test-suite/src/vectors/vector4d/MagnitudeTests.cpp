/**
 * @file MagnitudeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref fgm::Vector4D<bool> magnitude and normalization logic.
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
    fgm::Vector4D<T> _vec;
    fgm::Magnitude<T> _expectedMagnitude;

    void SetUp() override
    {
        _vec = { T(1), T(2), T(2), T(4) };
        _expectedMagnitude = fgm::Magnitude<T>(5);
    }
};
/** @brief Test fixture for @ref fgm::Vector4D magnitude, parameterized by SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DMagnitude, SupportedArithmeticTypes);


template <typename T>
class Vector4DUncleanMagnitude: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> _vec;
    fgm::Magnitude<T> _expectedMagnitude;

    void SetUp() override
    {
        _vec = { T(1), T(2), T(3), T(4) };
        _expectedMagnitude = fgm::Magnitude<T>(5.477225575051661);
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
    fgm::Vector4D<T> _vec;
    fgm::Vector4D<R> _expectedUnitVec;

    void SetUp() override
    {
        _vec = { T(14), T(27), T(83), T(52) };
        _expectedUnitVec = { static_cast<R>(0.13650905255670645), static_cast<R>(0.2632674585022196),
                             static_cast<R>(0.8093036687290455), static_cast<R>(0.5070336237820525) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D normalization, parameterized by SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DNormalization, SupportedArithmeticTypes);


template <typename T>
class Vector4DZeroNormalization: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> _vec;

    void SetUp() override
    {
        _vec = { T(0), T(0), T(0), T(0) };
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
    const auto magnitude = this->_vec.mag();

    static_assert(std::is_floating_point_v<decltype(magnitude)>);
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}

/**
 * @test Verify that the @ref fgm::Vector4D magnitude calculation results in a floating-point type, regardless of the
 *       component type.
 */
TYPED_TEST(Vector4DMagnitude, MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = this->_vec.mag();
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}

/** @test Verify that the static magnitude wrapper of @ref fgm::Vector4D returns a non-unit magnitude. */
TYPED_TEST(Vector4DMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = fgm::Vector4D<TypeParam>::mag(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}

/**
 * @test Verify the numerical accuracy of @ref fgm::Vector4D magnitude calculations for non-unit vectors to ensure
 *        minimal precision loss.
 */
TYPED_TEST(Vector4DUncleanMagnitude, NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = this->_vec.mag();

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}

/**
 * @test Verify the numerical accuracy of @ref fgm::Vector4D static magnitude wrapper for non-unit vectors ensure
 *        minimal precision loss.
 */
TYPED_TEST(Vector4DUncleanMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = fgm::Vector4D<TypeParam>::mag(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
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

/** @test Verify that normalizing a @ref fgm::Vector4D returns a unit vector. */
TYPED_TEST(Vector4DNormalization, Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector4D normalized = this->_vec.normalize();

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/** @test Verify that @ref fgm::Vector4D static wrapper normalization returns a unit vector. */
TYPED_TEST(Vector4DNormalization, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector4D normalized = fgm::Vector4D<TypeParam>::normalize(this->_vec);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that the @ref fgm::Vector4D normalization results in a floating-point type, regardless of the
 *       component type.
 */
TYPED_TEST(Vector4DNormalization, NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.normalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/** @test Verify that normalizing a 4D vector using @ref fgm::Vector4D::safeNormalize returns a unit vector. */
TYPED_TEST(Vector4DNormalization, SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector4D normalized = this->_vec.normalize();
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vector4D::safeNormalize returns a
 *       zero-vector.
 */
TEST(Vector4DNormalization, Normalize_ZeroVectorCausesDeath)
{
    constexpr fgm::Vector4D vec(0.0, 0.0, 0.0, 0.0);
    EXPECT_VEC_ZERO(vec.safeNormalize());
}


/**
 * @test Verify that the normalizing a 4D vector using @ref fgm::Vector4D::safeNormalize results in a floating-point
 *       type, regardless of the component type.
 */
TYPED_TEST(Vector4DNormalization, SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.safeNormalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}

/** @} */