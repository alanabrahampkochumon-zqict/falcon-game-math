/**
 * @file MagnitudeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vec3 magnitude logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vec3Magnitude: public ::testing::Test
{
protected:
    fgm::Vec3<T> _vec;
    fgm::Magnitude<T> _expectedMagnitude;
    T _expectedMagnitudeSquare;

    void SetUp() override
    {
        _vec                     = { T(9), T(6), T(2) };
        _expectedMagnitude       = fgm::Magnitude<T>(11);
        _expectedMagnitudeSquare = T(121);
    }
};
/** @brief Test fixture for @ref fgm::Vec3 magnitude, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec3Magnitude, SupportedArithmeticTypes);


template <typename T>
class Vec3UncleanMagnitude: public ::testing::Test
{
protected:
    fgm::Vec3<T> _vec;
    fgm::Magnitude<T> _expectedMagnitude;

    void SetUp() override
    {
        _vec               = { T(1), T(2), T(3) };
        _expectedMagnitude = fgm::Magnitude<T>(3.7416573867739413);
    }
};
/**
 * @brief Test fixture for @ref fgm::Vec3 magnitude, parameterized by @ref SupportedArithmeticTypes,
 *        for testing high-precision magnitude.
 */
TYPED_TEST_SUITE(Vec3UncleanMagnitude, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Magnitude
 * @{
 */

/** @brief Verify that vector magnitude operation is available at compile time. */
namespace
{
    // TODO: Add static test after making sqrt constexpr
    // constexpr fgm::Vec3 Vec(1, 2, 3);
    // constexpr auto magA = Vec.mag();
    // constexpr auto magB = fgm::Vec2<int>::mag(Vec);
    // static_assert(magA - 3.7416573867739413 <= 1e-5);
    // static_assert(magB - 3.7416573867739413 <= 1e-5);

    constexpr fgm::Vec3 vecM(1, 2, 3);
    constexpr auto magSqA = vecM.magSq();
    constexpr auto magSqB = fgm::Vec3<int>::magSq(vecM);

    static_assert(magSqA == 14.0);
    static_assert(magSqB == 14.0);

} // namespace


/** @brief Verify that taking the magnitude of a zero vector returns exactly zero. */
TEST(Vec3Magnitude, ZeroVectorReturnsZero)
{
    const fgm::Vec3 vec(0.0f, 0.0f, 0.0f);

    EXPECT_FLOAT_EQ(0.0f, vec.mag());
}


/** @brief Verify that taking the magnitude of a one vector returns non-unit scalar. */
TEST(Vec3Magnitude, OneComponentVectorReturnsNonUnitScalar)
{
    const fgm::Vec3 vec(1.0f, 1.0f, 1.0f);

    EXPECT_NE(1.0f, vec.mag());
}


/** @brief Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vec3Magnitude, NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = this->_vec.mag();

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/** @brief Verify that taking the magnitude always returns a floating-point scalar. */
TYPED_TEST(Vec3Magnitude, MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = this->_vec.mag();
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}


/**
 * @brief Verify that taking the magnitude of a non-unit vector using static variant of @ref fgm::Vec3::mag
 *       returns non-unit scalar.
 */
TYPED_TEST(Vec3Magnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = fgm::Vec3<TypeParam>::mag(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/** @brief Verify that the magnitude calculations for non-unit vectors ensure minimal precision loss. */
TYPED_TEST(Vec3UncleanMagnitude, NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = this->_vec.mag();

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/**
 * @brief Verify that the magnitude calculations for non-unit vectors using static variant of @ref fgm::Vec3::mag
 *       ensure minimal precision loss.
 */
TYPED_TEST(Vec3UncleanMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = fgm::Vec3<TypeParam>::mag(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/**************************************
 *                                    *
 *       MAGNITUDE SQUARE TESTS       *
 *                                    *
 **************************************/

/** @brief Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vec3Magnitude, MagnitudeSquare_ReturnsSquaredMagnitude)
{
    const auto magnitude = this->_vec.magSq();

    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}


/**
 * @brief Verify that taking the magnitude square of a non-unit vector using static variant of
 *        @ref fgm::Vec3::mag returns non-unit scalar.
 */
TYPED_TEST(Vec3Magnitude, StaticWrapper_MagnitudeSquare_ReturnsSquaredMagnitude)
{
    const auto magnitude = fgm::Vec3<TypeParam>::magSq(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}

/** @} */
