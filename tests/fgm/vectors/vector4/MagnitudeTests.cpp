/**
 * @file MagnitudeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref fgm::Vector4 magnitude logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector4Magnitude: public ::testing::Test
{
protected:
    fgm::Vector4<T> _vec;
    fgm::Magnitude<T> _expectedMagnitude;
    T _expectedMagnitudeSquare;

    void SetUp() override
    {
        _vec                     = { T(1), T(2), T(2), T(4) };
        _expectedMagnitude       = fgm::Magnitude<T>(5);
        _expectedMagnitudeSquare = T(25);
    }
};
/** @brief Test fixture for @ref fgm::Vector4 magnitude, parameterized by SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4Magnitude, SupportedArithmeticTypes);


template <typename T>
class Vector4UncleanMagnitude: public ::testing::Test
{
protected:
    fgm::Vector4<T> _vec;
    fgm::Magnitude<T> _expectedMagnitude;

    void SetUp() override
    {
        _vec               = { T(1), T(2), T(3), T(4) };
        _expectedMagnitude = fgm::Magnitude<T>(5.477225575051661);
    }
};
/**
 * @brief Test fixture for @ref fgm::Vector4 magnitude, parameterized by @ref SupportedArithmeticTypes,
 *        for testing high-precision magnitude.
 */
TYPED_TEST_SUITE(Vector4UncleanMagnitude, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Magnitude
 * @{
 */

/** @brief Verify that vector magnitude operation is available at compile time. */
namespace
{
    // TODO: Add static test after making sqrt constexpr
    // constexpr fgm::Vector4 Vec(1, 2, 3, 4);
    // constexpr auto magA = Vec.mag();
    // constexpr auto magB = fgm::Vector2<int>::mag(Vec);

    // static_assert(magA - 5.477225575051661 <= 1e-5);
    // static_assert(magB - 5.477225575051661 <= 1e-5);

    constexpr fgm::Vector4 vecM(1, 2, 3, 4);
    constexpr auto magSqA = vecM.magSq();
    constexpr auto magSqB = fgm::Vector4<int>::magSq(vecM);

    static_assert(magSqA == 30);
    static_assert(magSqB == 30);
} // namespace


/** @brief Verify that taking the magnitude of a zero vector returns exactly zero. */
TEST(Vector4Magnitude, ZeroVectorReturnsZero)
{
    const fgm::Vector4 vec(0.0f, 0.0f, 0.0f, 0.0f);

    EXPECT_FLOAT_EQ(0.0f, vec.mag());
}


/** @brief Verify that taking the magnitude of a one vector returns non-unit scalar. */
TEST(Vector4Magnitude, OneComponentVectorReturnsNonUnitScalar)
{
    const fgm::Vector4 vec(1.0f, 1.0f, 1.0f, 1.0f);

    EXPECT_NE(1.0f, vec.mag());
}


/** @brief Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vector4Magnitude, NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = this->_vec.mag();

    static_assert(std::is_floating_point_v<decltype(magnitude)>);
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/** @brief Verify that taking the magnitude always returns a floating-point scalar. */
TYPED_TEST(Vector4Magnitude, MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = this->_vec.mag();
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}


/**
 * @brief Verify that taking the magnitude of a non-unit vector using static variant of @ref fgm::Vector4::mag
 *       returns non-unit scalar.
 */
TYPED_TEST(Vector4Magnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = fgm::Vector4<TypeParam>::mag(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/** @brief Verify that the magnitude calculations for non-unit vectors ensure minimal precision loss. */
TYPED_TEST(Vector4UncleanMagnitude, NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = this->_vec.mag();

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/**
 * @brief Verify that the magnitude calculations for non-unit vectors using static variant of @ref fgm::Vector4::mag
 *       ensure minimal precision loss.
 */
TYPED_TEST(Vector4UncleanMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = fgm::Vector4<TypeParam>::mag(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/**************************************
 *                                    *
 *       MAGNITUDE SQUARE TESTS       *
 *                                    *
 **************************************/

/** @brief Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vector4Magnitude, MagnitudeSquare_ReturnsSquaredMagnitude)
{
    const auto magnitude = this->_vec.magSq();

    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}


/**
 * @brief Verify that taking the magnitude square of a non-unit vector using static variant of
 *        @ref fgm::Vector4::mag returns non-unit scalar.
 */
TYPED_TEST(Vector4Magnitude, StaticWrapper_MagnitudeSquare_ReturnsSquaredMagnitude)
{
    const auto magnitude = fgm::Vector4<TypeParam>::magSq(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}

/** @} */
