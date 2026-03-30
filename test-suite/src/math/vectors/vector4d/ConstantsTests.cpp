/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 24, 2026
 *
 * @brief Verifies @ref fgm::Vector4D constants (@ref fgm::Vector4D::one, @ref fgm::Vector4D::zero, etc).
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;



template <typename T>
class Vector4DConstants: public ::testing::Test
{
protected:
    T _one = T(1);
    T _zero = T(0);
};
/** @brief Test fixture for @ref fgm::Vector4D constants, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DConstants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Const
 * @{
 */

/** @test Verifies that @ref fgm::Vector4D::one returns a 4D vector with unit components. */
TYPED_TEST(Vector4DConstants, One_ReturnsVectorWithUnitComponents)
{
    constexpr TypeParam one = TypeParam(1);
    EXPECT_VEC_CONTAINS(fgm::vec4d::one<TypeParam>, one, one, one, one);
}


/** @test Verifies that @ref fgm::Vector4D::zero returns a 4D vector with zero components. */
TYPED_TEST(Vector4DConstants, Zero_ReturnsVectorWithZeroComponents)
{
    EXPECT_VEC_ZERO(fgm::vec4d::zero<TypeParam>);
}


/** @test Verifies that @ref fgm::Vector4D::inf<float> returns a 4D vector with infinity components. */
TEST(Vector4DConstants, FloatInf_ReturnsFloatVectorWithInfinityComponents)
{
    constexpr auto inf = fgm::vec4d::inf<float>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC4_POS_INF(inf);
}


/** @test Verifies that @ref fgm::Vector4D::inf<double> returns a 4D vector with infinity components. */
TEST(Vector4DConstants, DoubleInf_ReturnsDoubleVectorWithInfinityComponents)
{
    constexpr auto inf = fgm::vec4d::inf<double>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC4_POS_INF(inf);
}


/** @test Verifies that @ref fgm::Vector4D::infN<float> returns a 4D vector with negative infinity components. */
TEST(Vector4DConstants, NegativeFloatInf_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    constexpr auto inf = fgm::vec4d::infN<float>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC4_NEG_INF(inf);
}


/** @test Verifies that @ref fgm::Vector4D::infN<double> returns a 4D vector with negative infinity components. */
TEST(Vector4DConstants, NegativeDoubleInf_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    constexpr auto inf = fgm::vec4d::infN<double>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC4_NEG_INF(inf);
}


/** @test Verifies that @ref fgm::Vector4D::infN<float> returns a 4D vector with NaN components. */
TEST(Vector4DConstants, NaNFloatInf_ReturnsFloatVectorWithNaNComponents)
{
    constexpr auto nan = fgm::vec4d::nan<float>;
    EXPECT_TRUE(std::isnan(nan.x));
    EXPECT_TRUE(std::isnan(nan.y));
    EXPECT_TRUE(std::isnan(nan.z));
    EXPECT_TRUE(std::isnan(nan.w));
}


/** @test Verifies that @ref fgm::Vector4D::infN<double> returns a 4D vector with NaN components. */
TEST(Vector4DConstants, NaNDoubleInf_ReturnsDoubleVectorWithNaNComponents)
{
    constexpr auto nan = fgm::vec4d::nan<double>;
    EXPECT_TRUE(std::isnan(nan.x));
    EXPECT_TRUE(std::isnan(nan.y));
    EXPECT_TRUE(std::isnan(nan.z));
    EXPECT_TRUE(std::isnan(nan.w));
}


/** @test Verifies that @ref fgm::Vector4D::x returns a unit vector aligned with x-axis. */
TYPED_TEST(Vector4DConstants, X_ReturnsUnitVectorWithOnlyXComponent)
{
    constexpr auto x = fgm::vec4d::x<TypeParam>;
    EXPECT_VEC_CONTAINS(x, this->_one, this->_zero, this->_zero, this->_zero);
}


/** @test Verifies that @ref fgm::Vector4D::x returns a unit vector aligned with y-axis. */
TYPED_TEST(Vector4DConstants, Y_ReturnsUnitVectorWithOnlyYComponent)
{
    constexpr auto y = fgm::vec4d::y<TypeParam>;
    EXPECT_VEC_CONTAINS(y, this->_zero, this->_one, this->_zero, this->_zero);
}


/** @test Verifies that @ref fgm::Vector4D::x returns a unit vector aligned with z-axis. */
TYPED_TEST(Vector4DConstants, Z_ReturnsUnitVectorWithOnlyZComponent)
{
    constexpr auto z = fgm::vec4d::z<TypeParam>;
    EXPECT_VEC_CONTAINS(z, this->_zero, this->_zero, this->_one, this->_zero);
}


/** @test Verifies that @ref fgm::Vector4D::x returns a unit vector aligned with w-axis. */
TYPED_TEST(Vector4DConstants, W_ReturnsUnitVectorWithOnlyWComponent)
{
    constexpr auto w = fgm::vec4d::w<TypeParam>;
    EXPECT_VEC_CONTAINS(w, this->_zero, this->_zero, this->_zero, this->_one);
}

/** @} */