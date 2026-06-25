/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref fgm::Vector3 constants (@ref fgm::Vector3::one, @ref fgm::Vector3::zero, etc).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3TestSetup.h"



template <typename T>
class Vector3Constants: public testing::Test
{
protected:
    T _one  = T(1);
    T _zero = T(0);
};
/** @brief Test fixture for @ref fgm::Vector3 constants, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector3Constants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Const
 * @{
 */

/** @brief Verify that @ref fgm::Vector3 constants are available at compile time. */
namespace
{
    static_assert(fgm::vec3d::one<int>.x() == 1);
    static_assert(fgm::vec3d::one<int>.y() == 1);
    static_assert(fgm::vec3d::one<int>.z() == 1);

    static_assert(fgm::vec3d::zero<int>.x() == 0);
    static_assert(fgm::vec3d::zero<int>.y() == 0);
    static_assert(fgm::vec3d::zero<int>.z() == 0);

    static_assert(fgm::isinf(fgm::vec3d::inf<float>.x()));
    static_assert(fgm::isinf(fgm::vec3d::inf<float>.y()));
    static_assert(fgm::isinf(fgm::vec3d::inf<float>.z()));


    static_assert(fgm::isnan(fgm::vec3d::nan<float>.x()));
    static_assert(fgm::isnan(fgm::vec3d::nan<float>.y()));
    static_assert(fgm::isnan(fgm::vec3d::nan<float>.z()));

} // namespace


/** @brief Verify that @ref fgm::vec3d::one returns a 3D vector with unit components. */
TYPED_TEST(Vector3Constants, One_ReturnsVectorWithUnitComponents)
{
    const TypeParam one = TypeParam(1);
    EXPECT_VEC_CONTAINS(fgm::vec3d::one<TypeParam>, one, one, one);
}


/** @brief Verify that @ref fgm::vec3d::zero returns a 3D vector with zero components. */
TYPED_TEST(Vector3Constants, Zero_ReturnsVectorWithZeroComponents) { EXPECT_VEC_ZERO(fgm::vec3d::zero<TypeParam>); }


/** @brief Verify that @ref fgm::vec3d::inf<float> returns a 3D vector with infinity components. */
TEST(Vector3Constants, FloatInf_ReturnsFloatVectorWithInfinityComponents)
{
    const auto inf = fgm::vec3d::inf<float>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC3_POS_INF(inf)
}


/** @brief Verify that @ref fgm::vec3d::inf<double> returns a 3D vector with infinity components. */
TEST(Vector3Constants, DoubleInf_ReturnsDoubleVectorWithInfinityComponents)
{
    const auto inf = fgm::vec3d::inf<double>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC3_POS_INF(inf)
}


/** @brief Verify that @ref fgm::vec3d::infN<float> returns a 3D vector with negative infinity components. */
TEST(Vector3Constants, NegativeFloatInf_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::vec3d::infN<float>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC3_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::vec3d::infN<double> returns a 3D vector with negative infinity components. */
TEST(Vector3Constants, NegativeDoubleInf_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::vec3d::infN<double>;
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC3_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::vec3d::infN<float> returns a 3D vector with NaN components. */
TEST(Vector3Constants, NaNFloatInf_ReturnsFloatVectorWithNaNComponents)
{
    const auto nan = fgm::vec3d::nan<float>;
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
    EXPECT_TRUE(std::isnan(nan.z()));
}


/** @brief Verify that @ref fgm::vec3d::infN<double> returns a 3D vector with NaN components. */
TEST(Vector3Constants, NaNDoubleInf_ReturnsDoubleVectorWithNaNComponents)
{
    const auto nan = fgm::vec3d::nan<double>;
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
    EXPECT_TRUE(std::isnan(nan.z()));
}


/** @brief Verify that @ref fgm::vec3d::x returns a unit vector aligned with x-axis. */
TYPED_TEST(Vector3Constants, X_ReturnsUnitVectorWithOnlyXComponent)
{
    const auto x = fgm::vec3d::x<TypeParam>;
    EXPECT_VEC_CONTAINS(x, this->_one, this->_zero, this->_zero);
}


/** @brief Verify that @ref fgm::vec3d::y returns a unit vector aligned with y-axis. */
TYPED_TEST(Vector3Constants, Y_ReturnsUnitVectorWithOnlyYComponent)
{
    const auto y = fgm::vec3d::y<TypeParam>;
    EXPECT_VEC_CONTAINS(y, this->_zero, this->_one, this->_zero);
}


/** @brief Verify that @ref fgm::vec3d::z returns a unit vector aligned with z-axis. */
TYPED_TEST(Vector3Constants, Z_ReturnsUnitVectorWithOnlyZComponent)
{
    const auto z = fgm::vec3d::z<TypeParam>;
    EXPECT_VEC_CONTAINS(z, this->_zero, this->_zero, this->_one);
}

/** @} */
