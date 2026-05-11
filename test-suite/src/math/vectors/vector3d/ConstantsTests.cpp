/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref fgm::Vector3D constants (@ref fgm::Vector3D::one, @ref fgm::Vector3D::zero, etc).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3DTestSetup.h"



template <typename T>
class Vector3DConstants: public ::testing::Test
{
protected:
    T _one = T(1);
    T _zero = T(0);
};
/** @brief Test fixture for @ref fgm::Vector3D constants, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector3DConstants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Const
 * @{
 */

/** @test Verify that @ref fgm::vec3d::one returns a 3D vector with unit components. */
TYPED_TEST(Vector3DConstants, One_ReturnsVectorWithUnitComponents)
{
    constexpr TypeParam one = TypeParam(1);
    EXPECT_VEC_CONTAINS(fgm::vec3d::one<TypeParam>, one, one, one);
}


/** @test Verify that @ref fgm::vec3d::zero returns a 3D vector with zero components. */
TYPED_TEST(Vector3DConstants, Zero_ReturnsVectorWithZeroComponents)
{
    EXPECT_VEC_ZERO(fgm::vec3d::zero<TypeParam>);
}


/** @test Verify that @ref fgm::vec3d::inf<float> returns a 3D vector with infinity components. */
TEST(Vector3DConstants, FloatInf_ReturnsFloatVectorWithInfinityComponents)
{
    constexpr auto inf = fgm::vec3d::inf<float>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC3_POS_INF(inf)
}


/** @test Verify that @ref fgm::vec3d::inf<double> returns a 3D vector with infinity components. */
TEST(Vector3DConstants, DoubleInf_ReturnsDoubleVectorWithInfinityComponents)
{
    constexpr auto inf = fgm::vec3d::inf<double>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC3_POS_INF(inf)
}


/** @test Verify that @ref fgm::vec3d::infN<float> returns a 3D vector with negative infinity components. */
TEST(Vector3DConstants, NegativeFloatInf_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    constexpr auto inf = fgm::vec3d::infN<float>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC3_NEG_INF(inf)
}


/** @test Verify that @ref fgm::vec3d::infN<double> returns a 3D vector with negative infinity components. */
TEST(Vector3DConstants, NegativeDoubleInf_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    constexpr auto inf = fgm::vec3d::infN<double>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC3_NEG_INF(inf)
}


/** @test Verify that @ref fgm::vec3d::infN<float> returns a 3D vector with NaN components. */
TEST(Vector3DConstants, NaNFloatInf_ReturnsFloatVectorWithNaNComponents)
{
    constexpr auto nan = fgm::vec3d::nan<float>;
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
    EXPECT_TRUE(std::isnan(nan.z()));
}


/** @test Verify that @ref fgm::vec3d::infN<double> returns a 3D vector with NaN components. */
TEST(Vector3DConstants, NaNDoubleInf_ReturnsDoubleVectorWithNaNComponents)
{
    constexpr auto nan = fgm::vec3d::nan<double>;
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
    EXPECT_TRUE(std::isnan(nan.z()));
}


/** @test Verify that @ref fgm::vec3d::x returns a unit vector aligned with x-axis. */
TYPED_TEST(Vector3DConstants, X_ReturnsUnitVectorWithOnlyXComponent)
{
    constexpr auto x = fgm::vec3d::x<TypeParam>;
    EXPECT_VEC_CONTAINS(x, this->_one, this->_zero, this->_zero);
}


/** @test Verify that @ref fgm::vec3d::y returns a unit vector aligned with y-axis. */
TYPED_TEST(Vector3DConstants, Y_ReturnsUnitVectorWithOnlyYComponent)
{
    constexpr auto y = fgm::vec3d::y<TypeParam>;
    EXPECT_VEC_CONTAINS(y, this->_zero, this->_one, this->_zero);
}


/** @test Verify that @ref fgm::vec3d::z returns a unit vector aligned with z-axis. */
TYPED_TEST(Vector3DConstants, Z_ReturnsUnitVectorWithOnlyZComponent)
{
    constexpr auto z = fgm::vec3d::z<TypeParam>;
    EXPECT_VEC_CONTAINS(z, this->_zero, this->_zero, this->_one);
}

/** @} */