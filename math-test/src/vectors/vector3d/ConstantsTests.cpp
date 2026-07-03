/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 03, 2026
 *
 * @brief Verify @ref fgm::Vector3 constants (@ref fgm::Vector3::ONE(), @ref fgm::Vector3::ZERO(), etc).
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
/** @brief Test fixture for @ref fgm::Vector3 constants, parameterized by @ref SupportedSignedArithmeticTypes. */
// Unsigned types not tested since only zero and one are constraint to include unsigned types.
TYPED_TEST_SUITE(Vector3Constants, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Const
 * @{
 */

/** @brief Verify that @ref fgm::Vector3 constants are available at compile time. */
namespace
{
    static_assert(fgm::Vector3<int>::ONE().x() == 1);
    static_assert(fgm::Vector3<int>::ONE().y() == 1);

    static_assert(fgm::Vector3<int>::ZERO().x() == 0);
    static_assert(fgm::Vector3<int>::ZERO().y() == 0);

    static_assert(fgm::isinf(fgm::Vector3<float>::INF().x()));
    static_assert(fgm::isinf(fgm::Vector3<float>::INF().y()));

    static_assert(fgm::isinf(fgm::Vector3<float>::INF_NEG().x()));
    static_assert(fgm::isinf(fgm::Vector3<float>::INF_NEG().y()));


    static_assert(fgm::isnan(fgm::Vector3<float>::QNAN().x()));
    static_assert(fgm::isnan(fgm::Vector3<float>::QNAN().y()));

} // namespace


/** @brief Verify that @ref fgm::Vector3::ONE() returns a 3D vector with unit components. */
TYPED_TEST(Vector3Constants, ONE_ReturnsVectorWithUnitComponents)
{
    const auto one = TypeParam(1);
    EXPECT_VEC_CONTAINS(fgm::Vector3<TypeParam>::ONE(), one, one, one);
}


/** @brief Verify that @ref fgm::Vector3::ZERO returns a 3D vector with zero components. */
TYPED_TEST(Vector3Constants, ZERO_ReturnsVectorWithZeroComponents) { EXPECT_VEC_ZERO(fgm::Vector3<TypeParam>::ZERO()); }


/** @brief Verify that @ref fgm::Vector3<float>::INF returns a 3D vector with infinity components. */
TEST(Vector3Constants, Float_INF_ReturnsFloatVectorWithInfinityComponents)
{
    const auto inf = fgm::Vector3<float>::INF();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC3_POS_INF(inf)
}


/** @brief Verify that @ref fgm::Vector3<double>::INF returns a 3D vector with infinity components. */
TEST(Vector3Constants, Double_INF_ReturnsDoubleVectorWithInfinityComponents)
{
    const auto inf = fgm::Vector3<double>::INF();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC3_POS_INF(inf)
}


/** @brief Verify that @ref fgm::Vector3<float>::INF_NEG returns a 3D vector with negative infinity components. */
TEST(Vector3Constants, Float_INF_NEG_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::Vector3<float>::INF_NEG();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC3_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::Vector3<double>::INF_NEG returns a 3D vector with negative infinity components. */
TEST(Vector3Constants, Double_INF_NEG_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::Vector3<double>::INF_NEG();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC3_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::Vector3<float>::QNAN returns a 3D vector with NaN components. */
TEST(Vector3Constants, Float_QNAN_ReturnsFloatVectorWithNaNComponents)
{
    const auto nan = fgm::Vector3<float>::QNAN();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @brief Verify that @ref fgm::Vector3<double>::QNAN returns a 3D vector with NaN components. */
TEST(Vector3Constants, Double_QNAN_ReturnsDoubleVectorWithNaNComponents)
{
    const auto nan = fgm::Vector3<double>::QNAN();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @brief Verify that @ref fgm::Vector3::RIGHT returns a unit vector aligned with positive x-axis. */
TYPED_TEST(Vector3Constants, RIGHT_ReturnsUnitVectorWithOnlyPositiveXComponent)
{
    const auto vec = fgm::Vector3<TypeParam>::RIGHT();
    EXPECT_VEC_CONTAINS(vec, this->_one, this->_zero, this->_zero);
}


/** @brief Verify that @ref fgm::Vector3::LEFT returns a unit vector aligned with negative x-axis. */
TYPED_TEST(Vector3Constants, LEFT_ReturnsUnitVectorWithOnlyNegativeXComponent)
{
    const auto vec = fgm::Vector3<TypeParam>::LEFT();
    EXPECT_VEC_CONTAINS(vec, TypeParam(-this->_one), this->_zero, this->_zero);
}


/** @brief Verify that @ref fgm::Vector3::UP returns a unit vector aligned with positive y-axis. */
TYPED_TEST(Vector3Constants, UP_ReturnsUnitVectorWithOnlyPositiveYComponent)
{
    const auto vec = fgm::Vector3<TypeParam>::UP();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_one, this->_zero);
}


/** @brief Verify that @ref fgm::Vector3::DOWN returns a unit vector aligned with negative y-axis. */
TYPED_TEST(Vector3Constants, DOWN_ReturnsUnitVectorWithOnlyNegativeYComponent)
{
    const auto vec = fgm::Vector3<TypeParam>::DOWN();
    EXPECT_VEC_CONTAINS(vec, this->_zero, TypeParam(-this->_one), this->_zero);
}


#ifdef FGM_LEFT_HANDED

/** @brief Verify that @ref fgm::Vector3::FORWARD returns a unit vector aligned with positive z-axis. */
TYPED_TEST(Vector3Constants, FORWARD_ReturnsUnitVectorWithOnlyPositiveZComponent)
{
    const auto vec = fgm::Vector3<TypeParam>::FORWARD();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one);
}


/** @brief Verify that @ref fgm::Vector3::BACKWARD returns a unit vector aligned with negative z-axis. */
TYPED_TEST(Vector3Constants, BACKWARD_ReturnsUnitVectorWithOnlyNegativeZComponent)
{
    const auto vec = fgm::Vector3<TypeParam>::BACKWARD();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, TypeParam(-this->_one));
}

#else

/** @brief Verify that @ref fgm::Vector3::FORWARD returns a unit vector aligned with negative z-axis. */
TYPED_TEST(Vector3Constants, FORWARD_ReturnsUnitVectorWithOnlyPositiveZComponent)
{
    const auto vec = fgm::Vector3<TypeParam>::FORWARD();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, TypeParam(-this->_one));
}


/** @brief Verify that @ref fgm::Vector3::BACKWARD returns a unit vector aligned with positive z-axis. */
TYPED_TEST(Vector3Constants, BACKWARD_ReturnsUnitVectorWithOnlyNegativeZComponent)
{
    const auto vec = fgm::Vector3<TypeParam>::BACKWARD();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one);
}

#endif

/**
 * @brief Verify that @ref fgm::Vector3::POINT returns a vector with a unit z-component
 *        and zero <x,y> component by default.
 */
TYPED_TEST(Vector3Constants, POINT_ReturnsVectorWithUnitZComponent)
{
    const auto vec = fgm::Vector3<TypeParam>::POINT();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one);
}

/**
 * @brief Verify that @ref fgm::Vector3::POINT returns a vector with a unit z-component
 *        and passed-in <x,y> component.
 */
TYPED_TEST(Vector3Constants, POINT_ReturnsVectorWithUnitZComponentAndPassedInXYComponent)
{
    const auto x   = TypeParam(5);
    const auto y   = TypeParam(8);
    const auto vec = fgm::Vector3<TypeParam>::POINT(x, y);
    EXPECT_VEC_CONTAINS(vec, x, y, this->_one);
}

/** @} */
