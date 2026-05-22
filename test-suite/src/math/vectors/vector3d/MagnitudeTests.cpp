/**
 * @file MagnitudeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vector3D magnitude logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3DTestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector3DMagnitude: public ::testing::Test
{
protected:
    fgm::Vector3D<T> _vec;
    fgm::Magnitude<T> _expectedMagnitude;
    T _expectedMagnitudeSquare;

    void SetUp() override
    {
        _vec               = { T(3), T(4), T(12) };
        _expectedMagnitude = fgm::Magnitude<T>(13);
        _expectedMagnitudeSquare = T(169);
    }
};
/** @brief Test fixture for @ref fgm::Vector3D magnitude, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector3DMagnitude, SupportedArithmeticTypes);


template <typename T>
class Vector3DUncleanMagnitude: public ::testing::Test
{
protected:
    fgm::Vector3D<T> _vec;
    fgm::Magnitude<T> _expectedMagnitude;

    void SetUp() override
    {
        _vec               = { T(1), T(2), T(3) };
        _expectedMagnitude = fgm::Magnitude<T>(3.7416573867739413);
    }
};
/**
 * @brief Test fixture for @ref fgm::Vector3D magnitude, parameterized by @ref SupportedArithmeticTypes,
 *        for testing high-precision magnitude.
 */
TYPED_TEST_SUITE(Vector3DUncleanMagnitude, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Magnitude
 * @{
 */

/** @brief Verify that vector magnitude operation is available at compile time. */
namespace
{
    // TODO: Add static test after making sqrt constexpr
    // constexpr fgm::Vector3D vec(1, 2, 3);
    // constexpr auto magA = vec.mag();
    // constexpr auto magB = fgm::Vector2D<int>::mag(vec);
    // static_assert(magA - 3.7416573867739413 <= 1e-5);
    // static_assert(magB - 3.7416573867739413 <= 1e-5);

    constexpr fgm::Vector3D vecM(1, 2, 3);
    constexpr auto magSqA = vecM.magSq();
    constexpr auto magSqB = fgm::Vector3D<int>::magSq(vecM);

    static_assert(magSqA - 14.0 <= 1e-5);
    static_assert(magSqB - 14.0 <= 1e-5);

} // namespace


/** @brief Verify that taking the magnitude of a zero vector returns exactly zero. */
TEST(Vector3DMagnitude, ZeroVectorReturnsZero)
{
    const fgm::Vector3D vec(0.0f, 0.0f, 0.0f);

    EXPECT_FLOAT_EQ(0.0f, vec.mag());
}


/** @brief Verify that taking the magnitude of a one vector returns non-unit scalar. */
TEST(Vector3DMagnitude, OneComponentVectorReturnsNonUnitScalar)
{
    const fgm::Vector3D vec(1.0f, 1.0f, 1.0f);

    EXPECT_NE(1.0f, vec.mag());
}


/** @brief Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vector3DMagnitude, NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = this->_vec.mag();

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/** @brief Verify that taking the magnitude always returns a floating-point scalar. */
TYPED_TEST(Vector3DMagnitude, MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = this->_vec.mag();
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}


/**
 * @brief Verify that taking the magnitude of a non-unit vector using static variant of @ref fgm::Vector3D::mag
 *       returns non-unit scalar.
 */
TYPED_TEST(Vector3DMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = fgm::Vector3D<TypeParam>::mag(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/** @brief Verify that the magnitude calculations for non-unit vectors ensure minimal precision loss. */
TYPED_TEST(Vector3DUncleanMagnitude, NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = this->_vec.mag();

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/**
 * @brief Verify that the magnitude calculations for non-unit vectors using static variant of @ref fgm::Vector3D::mag
 *       ensure minimal precision loss.
 */
TYPED_TEST(Vector3DUncleanMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = fgm::Vector3D<TypeParam>::mag(this->_vec);

    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/**************************************
 *                                    *
 *       MAGNITUDE SQUARE TESTS       *
 *                                    *
 **************************************/

/** @brief Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vector3DMagnitude, MagnitudeSquare_ReturnsSquaredMagnitude)
{
    const auto magnitude = this->_vec.magSq();
    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}


/** @brief Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vector3DMagnitude, StaticWrapper_MagnitudeSquare_ReturnsSquaredMagnitude)
{
    const auto magnitude = fgm::Vector3D<TypeParam>::magSq(this->_vec);
    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}

/** @} */
