/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verifies @ref fgm::Vector2D constants (@ref fgm::Vector2D::one, @ref fgm::Vector2D::zero, etc).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"



template <typename T>
class Vector2DConstants: public ::testing::Test
{
protected:
    T _one = T(1);
    T _zero = T(0);
};
/** @brief Test fixture for @ref fgm::Vector2D constants, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector2DConstants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec2_Const
 * @{
 */

/** @test Verifies that @ref fgm::vec2d::one returns a 2D vector with unit components. */
TYPED_TEST(Vector2DConstants, One_ReturnsVectorWithUnitComponents)
{
    constexpr TypeParam one = TypeParam(1);
    EXPECT_VEC_CONTAINS(fgm::vec2d::one<TypeParam>, one, one);
}


/** @test Verifies that @ref fgm::vec2d::zero returns a 2D vector with zero components. */
TYPED_TEST(Vector2DConstants, Zero_ReturnsVectorWithZeroComponents)
{
    EXPECT_VEC_ZERO(fgm::vec2d::zero<TypeParam>);
}


/** @test Verifies that @ref fgm::vec2d::inf<float> returns a 2D vector with infinity components. */
TEST(Vector2DConstants, FloatInf_ReturnsFloatVectorWithInfinityComponents)
{
    constexpr auto inf = fgm::vec2d::inf<float>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC2_POS_INF(inf)
}


/** @test Verifies that @ref fgm::vec2d::inf<double> returns a 2D vector with infinity components. */
TEST(Vector2DConstants, DoubleInf_ReturnsDoubleVectorWithInfinityComponents)
{
    constexpr auto inf = fgm::vec2d::inf<double>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC2_POS_INF(inf)
}


/** @test Verifies that @ref fgm::vec2d::infN<float> returns a 2D vector with negative infinity components. */
TEST(Vector2DConstants, NegativeFloatInf_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    constexpr auto inf = fgm::vec2d::infN<float>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC2_NEG_INF(inf)
}


/** @test Verifies that @ref fgm::vec2d::infN<double> returns a 2D vector with negative infinity components. */
TEST(Vector2DConstants, NegativeDoubleInf_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    constexpr auto inf = fgm::vec2d::infN<double>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC2_NEG_INF(inf)
}


/** @test Verifies that @ref fgm::vec2d::infN<float> returns a 2D vector with NaN components. */
TEST(Vector2DConstants, NaNFloatInf_ReturnsFloatVectorWithNaNComponents)
{
    constexpr auto nan = fgm::vec2d::nan<float>;
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @test Verifies that @ref fgm::vec2d::infN<double> returns a 2D vector with NaN components. */
TEST(Vector2DConstants, NaNDoubleInf_ReturnsDoubleVectorWithNaNComponents)
{
    constexpr auto nan = fgm::vec2d::nan<double>;
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @test Verifies that @ref fgm::vec2d::x returns a unit vector aligned with x-axis. */
TYPED_TEST(Vector2DConstants, X_ReturnsUnitVectorWithOnlyXComponent)
{
    constexpr auto x = fgm::vec2d::x<TypeParam>;
    EXPECT_VEC_CONTAINS(x, this->_one, this->_zero);
}


/** @test Verifies that @ref fgm::vec2d::y returns a unit vector aligned with y-axis. */
TYPED_TEST(Vector2DConstants, Y_ReturnsUnitVectorWithOnlyYComponent)
{
    constexpr auto y = fgm::vec2d::y<TypeParam>;
    EXPECT_VEC_CONTAINS(y, this->_zero, this->_one);
}

/** @} */