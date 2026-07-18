/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 03, 2026
 *
 * @brief Verify @ref fgm::Vec4 constants (@ref fgm::Vec4::ONE(), @ref fgm::Vec4::ZERO(), etc).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"



template <typename T>
class Vec4Constants: public testing::Test
{
protected:
    T _one  = T(1);
    T _zero = T(0);
};
/** @brief Test fixture for @ref fgm::Vec4 constants, parameterized by @ref SupportedSignedArithmeticTypes. */
// Unsigned types not tested since only zero and one are constraint to include unsigned types.
TYPED_TEST_SUITE(Vec4Constants, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Const
 * @{
 */

/** @brief Verify that @ref fgm::Vec4 constants are available at compile time. */
namespace
{
    static_assert(fgm::Vec4<int>::one().x() == 1);
    static_assert(fgm::Vec4<int>::one().y() == 1);
    static_assert(fgm::Vec4<int>::one().z() == 1);
    static_assert(fgm::Vec4<int>::one().w() == 1);

    static_assert(fgm::Vec4<int>::zero().x() == 0);
    static_assert(fgm::Vec4<int>::zero().y() == 0);
    static_assert(fgm::Vec4<int>::zero().z() == 0);
    static_assert(fgm::Vec4<int>::zero().w() == 0);

    static_assert(fgm::isinf(fgm::Vec4<float>::inf().x()));
    static_assert(fgm::isinf(fgm::Vec4<float>::inf().y()));
    static_assert(fgm::isinf(fgm::Vec4<float>::inf().z()));
    static_assert(fgm::isinf(fgm::Vec4<float>::inf().w()));

    static_assert(fgm::isinf(fgm::Vec4<float>::infNeg().x()));
    static_assert(fgm::isinf(fgm::Vec4<float>::infNeg().y()));
    static_assert(fgm::isinf(fgm::Vec4<float>::infNeg().z()));
    static_assert(fgm::isinf(fgm::Vec4<float>::infNeg().w()));

    static_assert(fgm::isnan(fgm::Vec4<float>::qnan().x()));
    static_assert(fgm::isnan(fgm::Vec4<float>::qnan().y()));
    static_assert(fgm::isnan(fgm::Vec4<float>::qnan().z()));
    static_assert(fgm::isnan(fgm::Vec4<float>::qnan().w()));

    static_assert(fgm::Vec4<int>::left().x() == -1);
    static_assert(fgm::Vec4<int>::left().y() == 0);
    static_assert(fgm::Vec4<int>::left().z() == 0);
    static_assert(fgm::Vec4<int>::left().w() == 0);

    static_assert(fgm::Vec4<int>::right().x() == 1);
    static_assert(fgm::Vec4<int>::right().y() == 0);
    static_assert(fgm::Vec4<int>::right().z() == 0);
    static_assert(fgm::Vec4<int>::right().w() == 0);

    static_assert(fgm::Vec4<int>::up().x() == 0);
    static_assert(fgm::Vec4<int>::up().y() == 1);
    static_assert(fgm::Vec4<int>::up().z() == 0);
    static_assert(fgm::Vec4<int>::up().w() == 0);

    static_assert(fgm::Vec4<int>::down().x() == 0);
    static_assert(fgm::Vec4<int>::down().y() == -1);
    static_assert(fgm::Vec4<int>::down().z() == 0);
    static_assert(fgm::Vec4<int>::down().w() == 0);


#ifdef FGM_LEFT_HANDED
    static_assert(fgm::Vec4<int>::forward().x() == 0);
    static_assert(fgm::Vec4<int>::forward().y() == 0);
    static_assert(fgm::Vec4<int>::forward().z() == 1);
    static_assert(fgm::Vec4<int>::forward().w() == 0);


    static_assert(fgm::Vec4<int>::backward().x() == 0);
    static_assert(fgm::Vec4<int>::backward().y() == 0);
    static_assert(fgm::Vec4<int>::backward().z() == -1);
    static_assert(fgm::Vec4<int>::backward().w() == 0);
#else

    static_assert(fgm::Vec4<int>::forward().x() == 0);
    static_assert(fgm::Vec4<int>::forward().y() == 0);
    static_assert(fgm::Vec4<int>::forward().z() == -1);
    static_assert(fgm::Vec4<int>::forward().w() == 0);


    static_assert(fgm::Vec4<int>::backward().x() == 0);
    static_assert(fgm::Vec4<int>::backward().y() == 0);
    static_assert(fgm::Vec4<int>::backward().z() == 1);
    static_assert(fgm::Vec4<int>::backward().w() == 0);
#endif

    constexpr auto P1 = fgm::Vec4<int>::point();
    static_assert(P1.x() == 0);
    static_assert(P1.y() == 0);
    static_assert(P1.z() == 0);
    static_assert(P1.w() == 1);

    constexpr auto P2 = fgm::Vec4<int>::point(4, 5, 6);
    static_assert(P2.x() == 4);
    static_assert(P2.y() == 5);
    static_assert(P2.z() == 6);
    static_assert(P2.w() == 1);

} // namespace


/** @brief Verify that @ref fgm::Vec4::ONE() returns a 4D vector with unit components. */
TYPED_TEST(Vec4Constants, ONE_ReturnsVectorWithUnitComponents)
{
    const auto one = TypeParam(1);
    EXPECT_VEC_CONTAINS(fgm::Vec4<TypeParam>::one(), one, one, one, one);
}


/** @brief Verify that @ref fgm::Vec4::ZERO returns a 4D vector with zero components. */
TYPED_TEST(Vec4Constants, ZERO_ReturnsVectorWithZeroComponents) { EXPECT_VEC_ZERO(fgm::Vec4<TypeParam>::zero()); }


/** @brief Verify that @ref fgm::Vec4<float>::INF returns a 4D vector with infinity components. */
TEST(Vec4Constants, Float_INF_ReturnsFloatVectorWithInfinityComponents)
{
    const auto inf = fgm::Vec4<float>::inf();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC4_POS_INF(inf)
}


/** @brief Verify that @ref fgm::Vec4<double>::INF returns a 4D vector with infinity components. */
TEST(Vec4Constants, Double_INF_ReturnsDoubleVectorWithInfinityComponents)
{
    const auto inf = fgm::Vec4<double>::inf();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC4_POS_INF(inf)
}


/** @brief Verify that @ref fgm::Vec4<float>::INF_NEG returns a 4D vector with negative infinity components. */
TEST(Vec4Constants, Float_INF_NEG_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::Vec4<float>::infNeg();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC4_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::Vec4<double>::INF_NEG returns a 4D vector with negative infinity components. */
TEST(Vec4Constants, Double_INF_NEG_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::Vec4<double>::infNeg();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC4_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::Vec4<float>::QNAN returns a 4D vector with NaN components. */
TEST(Vec4Constants, Float_QNAN_ReturnsFloatVectorWithNaNComponents)
{
    const auto nan = fgm::Vec4<float>::qnan();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @brief Verify that @ref fgm::Vec4<double>::QNAN returns a 4D vector with NaN components. */
TEST(Vec4Constants, Double_QNAN_ReturnsDoubleVectorWithNaNComponents)
{
    const auto nan = fgm::Vec4<double>::qnan();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @brief Verify that @ref fgm::Vec4::RIGHT returns a unit vector aligned with positive x-axis. */
TYPED_TEST(Vec4Constants, RIGHT_ReturnsUnitVectorWithOnlyPositiveXComponent)
{
    const auto vec = fgm::Vec4<TypeParam>::right();
    EXPECT_VEC_CONTAINS(vec, this->_one, this->_zero, this->_zero, this->_zero);
}


/** @brief Verify that @ref fgm::Vec4::LEFT returns a unit vector aligned with negative x-axis. */
TYPED_TEST(Vec4Constants, LEFT_ReturnsUnitVectorWithOnlyNegativeXComponent)
{
    const auto vec = fgm::Vec4<TypeParam>::left();
    EXPECT_VEC_CONTAINS(vec, TypeParam(-this->_one), this->_zero, this->_zero, this->_zero);
}


/** @brief Verify that @ref fgm::Vec4::UP returns a unit vector aligned with positive y-axis. */
TYPED_TEST(Vec4Constants, UP_ReturnsUnitVectorWithOnlyPositiveYComponent)
{
    const auto vec = fgm::Vec4<TypeParam>::up();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_one, this->_zero, this->_zero);
}


/** @brief Verify that @ref fgm::Vec4::DOWN returns a unit vector aligned with negative y-axis. */
TYPED_TEST(Vec4Constants, DOWN_ReturnsUnitVectorWithOnlyNegativeYComponent)
{
    const auto vec = fgm::Vec4<TypeParam>::down();
    EXPECT_VEC_CONTAINS(vec, this->_zero, TypeParam(-this->_one), this->_zero, this->_zero);
}


#ifdef FGM_LEFT_HANDED

/** @brief Verify that @ref fgm::Vec4::FORWARD returns a unit vector aligned with positive z-axis. */
TYPED_TEST(Vec4Constants, FORWARD_ReturnsUnitVectorWithOnlyPositiveZComponent)
{
    const auto vec = fgm::Vec4<TypeParam>::forward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one, this->_zero);
}


/** @brief Verify that @ref fgm::Vec4::BACKWARD returns a unit vector aligned with negative z-axis. */
TYPED_TEST(Vec4Constants, BACKWARD_ReturnsUnitVectorWithOnlyNegativeZComponent)
{
    const auto vec = fgm::Vec4<TypeParam>::backward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, TypeParam(-this->_one), this->_zero);
}

#else

/** @brief Verify that @ref fgm::Vec4::FORWARD returns a unit vector aligned with negative z-axis. */
TYPED_TEST(Vec4Constants, FORWARD_ReturnsUnitVectorWithOnlyPositiveZComponent)
{
    const auto vec = fgm::Vec4<TypeParam>::forward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, TypeParam(-this->_one), this->_zero);
}


/** @brief Verify that @ref fgm::Vec4::BACKWARD returns a unit vector aligned with positive z-axis. */
TYPED_TEST(Vec4Constants, BACKWARD_ReturnsUnitVectorWithOnlyNegativeZComponent)
{
    const auto vec = fgm::Vec4<TypeParam>::backward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one, this->_zero);
}

#endif

/**
 * @brief Verify that @ref fgm::Vec4::POINT returns a vector with a unit z-component
 *        and zero <x,y,z> component by default.
 */
TYPED_TEST(Vec4Constants, POINT_ReturnsVectorWithUnitZComponent)
{
    const auto vec = fgm::Vec4<TypeParam>::point();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_zero, this->_one);
}

/**
 * @brief Verify that @ref fgm::Vec4::POINT returns a vector with a unit z-component
 *        and passed-in <x,y,z> component.
 */
TYPED_TEST(Vec4Constants, POINT_ReturnsVectorWithUnitZComponentAndPassedInXYZComponent)
{
    const auto x   = TypeParam(5);
    const auto y   = TypeParam(8);
    const auto z   = TypeParam(12);
    const auto vec = fgm::Vec4<TypeParam>::point(x, y, z);
    EXPECT_VEC_CONTAINS(vec, x, y, z, this->_one);
}

/** @} */
