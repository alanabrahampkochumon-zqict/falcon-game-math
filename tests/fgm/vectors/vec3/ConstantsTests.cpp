/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 03, 2026
 *
 * @brief Verify @ref fgm::Vec3 constants (@ref fgm::Vec3::ONE(), @ref fgm::Vec3::ZERO(), etc).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"



template <typename T>
class Vec3Constants: public testing::Test
{
protected:
    T _one  = T(1);
    T _zero = T(0);
};
/** @brief Test fixture for @ref fgm::Vec3 constants, parameterized by @ref SupportedSignedArithmeticTypes. */
// Unsigned types not tested since only zero and one are constraint to include unsigned types.
TYPED_TEST_SUITE(Vec3Constants, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Const
 * @{
 */

/** @brief Verify that @ref fgm::Vec3 constants are available at compile time. */
namespace
{
    static_assert(fgm::Vec3<int>::one().x() == 1);
    static_assert(fgm::Vec3<int>::one().y() == 1);
    static_assert(fgm::Vec3<int>::one().z() == 1);

    static_assert(fgm::Vec3<int>::zero().x() == 0);
    static_assert(fgm::Vec3<int>::zero().y() == 0);
    static_assert(fgm::Vec3<int>::zero().z() == 0);

    static_assert(fgm::isinf(fgm::Vec3<float>::inf().x()));
    static_assert(fgm::isinf(fgm::Vec3<float>::inf().y()));
    static_assert(fgm::isinf(fgm::Vec3<float>::inf().z()));

    static_assert(fgm::isinf(fgm::Vec3<float>::infNeg().x()));
    static_assert(fgm::isinf(fgm::Vec3<float>::infNeg().y()));
    static_assert(fgm::isinf(fgm::Vec3<float>::infNeg().z()));

    static_assert(fgm::isnan(fgm::Vec3<float>::qnan().x()));
    static_assert(fgm::isnan(fgm::Vec3<float>::qnan().y()));
    static_assert(fgm::isnan(fgm::Vec3<float>::qnan().z()));

    static_assert(fgm::Vec3<int>::left().x() == -1);
    static_assert(fgm::Vec3<int>::left().y() == 0);
    static_assert(fgm::Vec3<int>::left().z() == 0);

    static_assert(fgm::Vec3<int>::right().x() == 1);
    static_assert(fgm::Vec3<int>::right().y() == 0);
    static_assert(fgm::Vec3<int>::right().z() == 0);

    static_assert(fgm::Vec3<int>::up().x() == 0);
    static_assert(fgm::Vec3<int>::up().y() == 1);
    static_assert(fgm::Vec3<int>::up().z() == 0);

    static_assert(fgm::Vec3<int>::down().x() == 0);
    static_assert(fgm::Vec3<int>::down().y() == -1);
    static_assert(fgm::Vec3<int>::down().z() == 0);


#ifdef FGM_LEFT_HANDED
    static_assert(fgm::Vec3<int>::forward().x() == 0);
    static_assert(fgm::Vec3<int>::forward().y() == 0);
    static_assert(fgm::Vec3<int>::forward().z() == 1);


    static_assert(fgm::Vec3<int>::backward().x() == 0);
    static_assert(fgm::Vec3<int>::backward().y() == 0);
    static_assert(fgm::Vec3<int>::backward().z() == -1);
#else

    static_assert(fgm::Vec3<int>::forward().x() == 0);
    static_assert(fgm::Vec3<int>::forward().y() == 0);
    static_assert(fgm::Vec3<int>::forward().z() == -1);


    static_assert(fgm::Vec3<int>::backward().x() == 0);
    static_assert(fgm::Vec3<int>::backward().y() == 0);
    static_assert(fgm::Vec3<int>::backward().z() == 1);
#endif

    constexpr auto P1 = fgm::Vec3<int>::point();
    static_assert(P1.x() == 0);
    static_assert(P1.y() == 0);
    static_assert(P1.z() == 1);

    constexpr auto P2 = fgm::Vec3<int>::point(4, 5);
    static_assert(P2.x() == 4);
    static_assert(P2.y() == 5);
    static_assert(P2.z() == 1);

} // namespace


/** @brief Verify that @ref fgm::Vec3::ONE() returns a 3D vector with unit components. */
TYPED_TEST(Vec3Constants, ONE_ReturnsVectorWithUnitComponents)
{
    const auto one = TypeParam(1);
    EXPECT_VEC_CONTAINS(fgm::Vec3<TypeParam>::one(), one, one, one);
}


/** @brief Verify that @ref fgm::Vec3::ZERO returns a 3D vector with zero components. */
TYPED_TEST(Vec3Constants, ZERO_ReturnsVectorWithZeroComponents) { EXPECT_VEC_ZERO(fgm::Vec3<TypeParam>::zero()); }


/** @brief Verify that @ref fgm::Vec3<float>::INF returns a 3D vector with infinity components. */
TEST(Vec3Constants, Float_INF_ReturnsFloatVectorWithInfinityComponents)
{
    const auto inf = fgm::Vec3<float>::inf();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC3_POS_INF(inf)
}


/** @brief Verify that @ref fgm::Vec3<double>::INF returns a 3D vector with infinity components. */
TEST(Vec3Constants, Double_INF_ReturnsDoubleVectorWithInfinityComponents)
{
    const auto inf = fgm::Vec3<double>::inf();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC3_POS_INF(inf)
}


/** @brief Verify that @ref fgm::Vec3<float>::INF_NEG returns a 3D vector with negative infinity components. */
TEST(Vec3Constants, Float_INF_NEG_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::Vec3<float>::infNeg();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC3_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::Vec3<double>::INF_NEG returns a 3D vector with negative infinity components. */
TEST(Vec3Constants, Double_INF_NEG_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::Vec3<double>::infNeg();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC3_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::Vec3<float>::QNAN returns a 3D vector with NaN components. */
TEST(Vec3Constants, Float_QNAN_ReturnsFloatVectorWithNaNComponents)
{
    const auto nan = fgm::Vec3<float>::qnan();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @brief Verify that @ref fgm::Vec3<double>::QNAN returns a 3D vector with NaN components. */
TEST(Vec3Constants, Double_QNAN_ReturnsDoubleVectorWithNaNComponents)
{
    const auto nan = fgm::Vec3<double>::qnan();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @brief Verify that @ref fgm::Vec3::RIGHT returns a unit vector aligned with positive x-axis. */
TYPED_TEST(Vec3Constants, RIGHT_ReturnsUnitVectorWithOnlyPositiveXComponent)
{
    const auto vec = fgm::Vec3<TypeParam>::right();
    EXPECT_VEC_CONTAINS(vec, this->_one, this->_zero, this->_zero);
}


/** @brief Verify that @ref fgm::Vec3::LEFT returns a unit vector aligned with negative x-axis. */
TYPED_TEST(Vec3Constants, LEFT_ReturnsUnitVectorWithOnlyNegativeXComponent)
{
    const auto vec = fgm::Vec3<TypeParam>::left();
    EXPECT_VEC_CONTAINS(vec, TypeParam(-this->_one), this->_zero, this->_zero);
}


/** @brief Verify that @ref fgm::Vec3::UP returns a unit vector aligned with positive y-axis. */
TYPED_TEST(Vec3Constants, UP_ReturnsUnitVectorWithOnlyPositiveYComponent)
{
    const auto vec = fgm::Vec3<TypeParam>::up();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_one, this->_zero);
}


/** @brief Verify that @ref fgm::Vec3::DOWN returns a unit vector aligned with negative y-axis. */
TYPED_TEST(Vec3Constants, DOWN_ReturnsUnitVectorWithOnlyNegativeYComponent)
{
    const auto vec = fgm::Vec3<TypeParam>::down();
    EXPECT_VEC_CONTAINS(vec, this->_zero, TypeParam(-this->_one), this->_zero);
}


#ifdef FGM_LEFT_HANDED

/** @brief Verify that @ref fgm::Vec3::FORWARD returns a unit vector aligned with positive z-axis. */
TYPED_TEST(Vec3Constants, FORWARD_ReturnsUnitVectorWithOnlyPositiveZComponent)
{
    const auto vec = fgm::Vec3<TypeParam>::forward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one);
}


/** @brief Verify that @ref fgm::Vec3::BACKWARD returns a unit vector aligned with negative z-axis. */
TYPED_TEST(Vec3Constants, BACKWARD_ReturnsUnitVectorWithOnlyNegativeZComponent)
{
    const auto vec = fgm::Vec3<TypeParam>::backward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, TypeParam(-this->_one));
}

#else

/** @brief Verify that @ref fgm::Vec3::FORWARD returns a unit vector aligned with negative z-axis. */
TYPED_TEST(Vec3Constants, FORWARD_ReturnsUnitVectorWithOnlyPositiveZComponent)
{
    const auto vec = fgm::Vec3<TypeParam>::forward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, TypeParam(-this->_one));
}


/** @brief Verify that @ref fgm::Vec3::BACKWARD returns a unit vector aligned with positive z-axis. */
TYPED_TEST(Vec3Constants, BACKWARD_ReturnsUnitVectorWithOnlyNegativeZComponent)
{
    const auto vec = fgm::Vec3<TypeParam>::backward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one);
}

#endif

/**
 * @brief Verify that @ref fgm::Vec3::POINT returns a vector with a unit z-component
 *        and zero <x,y> component by default.
 */
TYPED_TEST(Vec3Constants, POINT_ReturnsVectorWithUnitZComponent)
{
    const auto vec = fgm::Vec3<TypeParam>::point();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one);
}

/**
 * @brief Verify that @ref fgm::Vec3::POINT returns a vector with a unit z-component
 *        and passed-in <x,y> component.
 */
TYPED_TEST(Vec3Constants, POINT_ReturnsVectorWithUnitZComponentAndPassedInXYComponent)
{
    const auto x   = TypeParam(5);
    const auto y   = TypeParam(8);
    const auto vec = fgm::Vec3<TypeParam>::point(x, y);
    EXPECT_VEC_CONTAINS(vec, x, y, this->_one);
}

/** @} */
