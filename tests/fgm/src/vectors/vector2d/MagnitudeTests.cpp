/**
 * @file MagnitudeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vector2 magnitude logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector2Magnitude: public ::testing::Test
{
protected:
    fgm::Vector2<T> _vec;
    fgm::Magnitude<T> _expectedMagnitude;
    T _expectedMagnitudeSquare;

    void SetUp() override
    {
        _vec                     = { T(3), T(4) };
        _expectedMagnitude       = fgm::Magnitude<T>(5);
        _expectedMagnitudeSquare = T(25);
    }
};
/** @brief Test fixture for @ref fgm::Vector2 magnitude, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector2Magnitude, SupportedArithmeticTypes);


template <typename T>
class Vector2UncleanMagnitude: public ::testing::Test
{
protected:
    fgm::Vector2<T> _vec;
    fgm::Magnitude<T> _expectedMagnitude;

    void SetUp() override
    {
        _vec               = { T(1), T(2) };
        _expectedMagnitude = fgm::Magnitude<T>(2.2360679774997898);
    }
};
/**
 * @brief Test fixture for @ref fgm::Vector2 magnitude, parameterized by @ref SupportedArithmeticTypes,
 *        for testing high-precision magnitude.
 */
TYPED_TEST_SUITE(Vector2UncleanMagnitude, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec2_Magnitude
 * @{
 */

/** @brief Verify that vector magnitude operation is available at compile time. */
namespace
{
    // TODO: Add static test after making sqrt constexpr
    // constexpr auto magA = Vec.mag();
    // constexpr auto magB = fgm::Vector2<int>::mag(Vec);

    constexpr fgm::Vector2 vecM(1, 2);
    constexpr auto magSqA = vecM.magSq();
    constexpr auto magSqB = fgm::Vector2<int>::magSq(vecM);

    static_assert(magSqA == 5.0);
    static_assert(magSqB == 5.0);
} // namespace


/**************************************
 *                                    *
 *           MAGNITUDE TESTS          *
 *                                    *
 **************************************/


/** @brief Verify that taking the magnitude of a zero vector returns exactly zero. */
TEST(Vector2Magnitude, ZeroVectorReturnsZero)
{
    const fgm::Vector2 vec(0.0f, 0.0f);

    EXPECT_FLOAT_EQ(0.0f, vec.mag());
}


/** @brief Verify that taking the magnitude of a one vector returns non-unit scalar. */
TEST(Vector2Magnitude, OneComponentVectorReturnsNonUnitScalar)
{
    const fgm::Vector2 vec(1.0f, 1.0f);

    EXPECT_NE(1.0f, vec.mag());
}


/** @brief Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vector2Magnitude, NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = this->_vec.mag();

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/** @brief Verify that taking the magnitude always returns a floating-point scalar. */
TYPED_TEST(Vector2Magnitude, MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = this->_vec.mag();
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}


/**
 * @brief Verify that taking the magnitude of a non-unit vector using static variant of @ref fgm::Vector2::mag
 *        returns non-unit scalar.
 */
TYPED_TEST(Vector2Magnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = fgm::Vector2<TypeParam>::mag(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/** @brief Verify that the magnitude calculations for non-unit vectors ensure minimal precision loss. */
TYPED_TEST(Vector2UncleanMagnitude, NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = this->_vec.mag();

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/**
 * @brief Verify that the magnitude calculations for non-unit vectors using static variant of @ref fgm::Vector2::mag
 *       ensure minimal precision loss.
 */
TYPED_TEST(Vector2UncleanMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = fgm::Vector2<TypeParam>::mag(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/**************************************
 *                                    *
 *       MAGNITUDE SQUARE TESTS       *
 *                                    *
 **************************************/

/** @brief Verify that taking the magnitude square of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vector2Magnitude, MagnitudeSquare_ReturnsSquaredMagnitude)
{
    const auto magnitude = this->_vec.magSq();

    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}


/**
 * @brief Verify that taking the magnitude square of a non-unit vector using static variant of
 *        @ref fgm::Vector2::mag returns non-unit scalar.
 */
TYPED_TEST(Vector2Magnitude, StaticWrapper_MagnitudeSquare_ReturnsSquaredMagnitude)
{
    const auto magnitude = fgm::Vector2<TypeParam>::magSq(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}


/** @} */
