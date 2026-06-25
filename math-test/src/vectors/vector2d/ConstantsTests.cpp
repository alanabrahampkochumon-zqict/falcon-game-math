/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vector2 constants (@ref fgm::Vector2::one, @ref fgm::Vector2::zero, etc).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2TestSetup.h"



template <typename T>
class Vector2Constants: public testing::Test
{
protected:
    T _one  = T(1);
    T _zero = T(0);
};
/** @brief Test fixture for @ref fgm::Vector2 constants, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector2Constants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec2_Const
 * @{
 */

/** @brief Verify that @ref fgm::Vector2 constants are available at compile time. */
namespace
{
    static_assert(fgm::vec2d::one<int>.x() == 1);
    static_assert(fgm::vec2d::one<int>.y() == 1);

    static_assert(fgm::vec2d::zero<int>.x() == 0);
    static_assert(fgm::vec2d::zero<int>.y() == 0);

    static_assert(fgm::isinf(fgm::vec2d::inf<float>.x()));
    static_assert(fgm::isinf(fgm::vec2d::inf<float>.y()));


    static_assert(fgm::isnan(fgm::vec2d::nan<float>.x()));
    static_assert(fgm::isnan(fgm::vec2d::nan<float>.y()));

} // namespace


/** @brief Verify that @ref fgm::vec2d::one returns a 2D vector with unit components. */
TYPED_TEST(Vector2Constants, One_ReturnsVectorWithUnitComponents)
{
    const TypeParam one = TypeParam(1);
    EXPECT_VEC_CONTAINS(fgm::vec2d::one<TypeParam>, one, one);
}


/** @brief Verify that @ref fgm::vec2d::zero returns a 2D vector with zero components. */
TYPED_TEST(Vector2Constants, Zero_ReturnsVectorWithZeroComponents) { EXPECT_VEC_ZERO(fgm::vec2d::zero<TypeParam>); }


/** @brief Verify that @ref fgm::vec2d::inf<float> returns a 2D vector with infinity components. */
TEST(Vector2Constants, FloatInf_ReturnsFloatVectorWithInfinityComponents)
{
    const auto inf = fgm::vec2d::inf<float>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC2_POS_INF(inf)
}


/** @brief Verify that @ref fgm::vec2d::inf<double> returns a 2D vector with infinity components. */
TEST(Vector2Constants, DoubleInf_ReturnsDoubleVectorWithInfinityComponents)
{
    const auto inf = fgm::vec2d::inf<double>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC2_POS_INF(inf)
}


/** @brief Verify that @ref fgm::vec2d::infN<float> returns a 2D vector with negative infinity components. */
TEST(Vector2Constants, NegativeFloatInf_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::vec2d::infN<float>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC2_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::vec2d::infN<double> returns a 2D vector with negative infinity components. */
TEST(Vector2Constants, NegativeDoubleInf_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::vec2d::infN<double>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC2_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::vec2d::infN<float> returns a 2D vector with NaN components. */
TEST(Vector2Constants, NaNFloatInf_ReturnsFloatVectorWithNaNComponents)
{
    const auto nan = fgm::vec2d::nan<float>;
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @brief Verify that @ref fgm::vec2d::infN<double> returns a 2D vector with NaN components. */
TEST(Vector2Constants, NaNDoubleInf_ReturnsDoubleVectorWithNaNComponents)
{
    const auto nan = fgm::vec2d::nan<double>;
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @brief Verify that @ref fgm::vec2d::x returns a unit vector aligned with x-axis. */
TYPED_TEST(Vector2Constants, X_ReturnsUnitVectorWithOnlyXComponent)
{
    const auto x = fgm::vec2d::x<TypeParam>;
    EXPECT_VEC_CONTAINS(x, this->_one, this->_zero);
}


/** @brief Verify that @ref fgm::vec2d::y returns a unit vector aligned with y-axis. */
TYPED_TEST(Vector2Constants, Y_ReturnsUnitVectorWithOnlyYComponent)
{
    const auto y = fgm::vec2d::y<TypeParam>;
    EXPECT_VEC_CONTAINS(y, this->_zero, this->_one);
}

/** @} */
