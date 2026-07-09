/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 03, 2026
 *
 * @brief Verify @ref fgm::Vector4 constants (@ref fgm::Vector4::ONE(), @ref fgm::Vector4::ZERO(), etc).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4TestSetup.h"



template <typename T>
class Vector4Constants: public testing::Test
{
protected:
    T _one  = T(1);
    T _zero = T(0);
};
/** @brief Test fixture for @ref fgm::Vector4 constants, parameterized by @ref SupportedSignedArithmeticTypes. */
// Unsigned types not tested since only zero and one are constraint to include unsigned types.
TYPED_TEST_SUITE(Vector4Constants, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Const
 * @{
 */

/** @brief Verify that @ref fgm::Vector4 constants are available at compile time. */
namespace
{
    static_assert(fgm::Vector4<int>::ONE().x() == 1);
    static_assert(fgm::Vector4<int>::ONE().y() == 1);
    static_assert(fgm::Vector4<int>::ONE().z() == 1);
    static_assert(fgm::Vector4<int>::ONE().w() == 1);

    static_assert(fgm::Vector4<int>::ZERO().x() == 0);
    static_assert(fgm::Vector4<int>::ZERO().y() == 0);
    static_assert(fgm::Vector4<int>::ZERO().z() == 0);
    static_assert(fgm::Vector4<int>::ZERO().w() == 0);

    static_assert(fgm::isinf(fgm::Vector4<float>::INF().x()));
    static_assert(fgm::isinf(fgm::Vector4<float>::INF().y()));
    static_assert(fgm::isinf(fgm::Vector4<float>::INF().z()));
    static_assert(fgm::isinf(fgm::Vector4<float>::INF().w()));

    static_assert(fgm::isinf(fgm::Vector4<float>::INF_NEG().x()));
    static_assert(fgm::isinf(fgm::Vector4<float>::INF_NEG().y()));
    static_assert(fgm::isinf(fgm::Vector4<float>::INF_NEG().z()));
    static_assert(fgm::isinf(fgm::Vector4<float>::INF_NEG().w()));

    static_assert(fgm::isnan(fgm::Vector4<float>::QNAN().x()));
    static_assert(fgm::isnan(fgm::Vector4<float>::QNAN().y()));
    static_assert(fgm::isnan(fgm::Vector4<float>::QNAN().z()));
    static_assert(fgm::isnan(fgm::Vector4<float>::QNAN().w()));

    static_assert(fgm::Vector4<int>::LEFT().x() == -1);
    static_assert(fgm::Vector4<int>::LEFT().y() == 0);
    static_assert(fgm::Vector4<int>::LEFT().z() == 0);
    static_assert(fgm::Vector4<int>::LEFT().w() == 0);

    static_assert(fgm::Vector4<int>::RIGHT().x() == 1);
    static_assert(fgm::Vector4<int>::RIGHT().y() == 0);
    static_assert(fgm::Vector4<int>::RIGHT().z() == 0);
    static_assert(fgm::Vector4<int>::RIGHT().w() == 0);

    static_assert(fgm::Vector4<int>::UP().x() == 0);
    static_assert(fgm::Vector4<int>::UP().y() == 1);
    static_assert(fgm::Vector4<int>::UP().z() == 0);
    static_assert(fgm::Vector4<int>::UP().w() == 0);

    static_assert(fgm::Vector4<int>::DOWN().x() == 0);
    static_assert(fgm::Vector4<int>::DOWN().y() == -1);
    static_assert(fgm::Vector4<int>::DOWN().z() == 0);
    static_assert(fgm::Vector4<int>::DOWN().w() == 0);


#ifdef FGM_LEFT_HANDED
    static_assert(fgm::Vector4<int>::FORWARD().x() == 0);
    static_assert(fgm::Vector4<int>::FORWARD().y() == 0);
    static_assert(fgm::Vector4<int>::FORWARD().z() == 1);
    static_assert(fgm::Vector4<int>::FORWARD().w() == 0);


    static_assert(fgm::Vector4<int>::BACKWARD().x() == 0);
    static_assert(fgm::Vector4<int>::BACKWARD().y() == 0);
    static_assert(fgm::Vector4<int>::BACKWARD().z() == -1);
    static_assert(fgm::Vector4<int>::BACKWARD().w() == 0);
#else

    static_assert(fgm::Vector4<int>::FORWARD().x() == 0);
    static_assert(fgm::Vector4<int>::FORWARD().y() == 0);
    static_assert(fgm::Vector4<int>::FORWARD().z() == -1);
    static_assert(fgm::Vector4<int>::FORWARD().w() == 0);


    static_assert(fgm::Vector4<int>::BACKWARD().x() == 0);
    static_assert(fgm::Vector4<int>::BACKWARD().y() == 0);
    static_assert(fgm::Vector4<int>::BACKWARD().z() == 1);
    static_assert(fgm::Vector4<int>::BACKWARD().w() == 0);
#endif

    constexpr auto P1 = fgm::Vector4<int>::POINT();
    static_assert(P1.x() == 0);
    static_assert(P1.y() == 0);
    static_assert(P1.z() == 0);
    static_assert(P1.w() == 1);

    constexpr auto P2 = fgm::Vector4<int>::POINT(4, 5, 6);
    static_assert(P2.x() == 4);
    static_assert(P2.y() == 5);
    static_assert(P2.z() == 6);
    static_assert(P2.w() == 1);

} // namespace


/** @brief Verify that @ref fgm::Vector4::ONE() returns a 4D vector with unit components. */
TYPED_TEST(Vector4Constants, ONE_ReturnsVectorWithUnitComponents)
{
    const auto one = TypeParam(1);
    EXPECT_VEC_CONTAINS(fgm::Vector4<TypeParam>::ONE(), one, one, one, one);
}


/** @brief Verify that @ref fgm::Vector4::ZERO returns a 4D vector with zero components. */
TYPED_TEST(Vector4Constants, ZERO_ReturnsVectorWithZeroComponents) { EXPECT_VEC_ZERO(fgm::Vector4<TypeParam>::ZERO()); }


/** @brief Verify that @ref fgm::Vector4<float>::INF returns a 4D vector with infinity components. */
TEST(Vector4Constants, Float_INF_ReturnsFloatVectorWithInfinityComponents)
{
    const auto inf = fgm::Vector4<float>::INF();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC4_POS_INF(inf)
}


/** @brief Verify that @ref fgm::Vector4<double>::INF returns a 4D vector with infinity components. */
TEST(Vector4Constants, Double_INF_ReturnsDoubleVectorWithInfinityComponents)
{
    const auto inf = fgm::Vector4<double>::INF();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC4_POS_INF(inf)
}


/** @brief Verify that @ref fgm::Vector4<float>::INF_NEG returns a 4D vector with negative infinity components. */
TEST(Vector4Constants, Float_INF_NEG_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::Vector4<float>::INF_NEG();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC4_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::Vector4<double>::INF_NEG returns a 4D vector with negative infinity components. */
TEST(Vector4Constants, Double_INF_NEG_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::Vector4<double>::INF_NEG();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC4_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::Vector4<float>::QNAN returns a 4D vector with NaN components. */
TEST(Vector4Constants, Float_QNAN_ReturnsFloatVectorWithNaNComponents)
{
    const auto nan = fgm::Vector4<float>::QNAN();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @brief Verify that @ref fgm::Vector4<double>::QNAN returns a 4D vector with NaN components. */
TEST(Vector4Constants, Double_QNAN_ReturnsDoubleVectorWithNaNComponents)
{
    const auto nan = fgm::Vector4<double>::QNAN();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @brief Verify that @ref fgm::Vector4::RIGHT returns a unit vector aligned with positive x-axis. */
TYPED_TEST(Vector4Constants, RIGHT_ReturnsUnitVectorWithOnlyPositiveXComponent)
{
    const auto vec = fgm::Vector4<TypeParam>::RIGHT();
    EXPECT_VEC_CONTAINS(vec, this->_one, this->_zero, this->_zero, this->_zero);
}


/** @brief Verify that @ref fgm::Vector4::LEFT returns a unit vector aligned with negative x-axis. */
TYPED_TEST(Vector4Constants, LEFT_ReturnsUnitVectorWithOnlyNegativeXComponent)
{
    const auto vec = fgm::Vector4<TypeParam>::LEFT();
    EXPECT_VEC_CONTAINS(vec, TypeParam(-this->_one), this->_zero, this->_zero, this->_zero);
}


/** @brief Verify that @ref fgm::Vector4::UP returns a unit vector aligned with positive y-axis. */
TYPED_TEST(Vector4Constants, UP_ReturnsUnitVectorWithOnlyPositiveYComponent)
{
    const auto vec = fgm::Vector4<TypeParam>::UP();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_one, this->_zero, this->_zero);
}


/** @brief Verify that @ref fgm::Vector4::DOWN returns a unit vector aligned with negative y-axis. */
TYPED_TEST(Vector4Constants, DOWN_ReturnsUnitVectorWithOnlyNegativeYComponent)
{
    const auto vec = fgm::Vector4<TypeParam>::DOWN();
    EXPECT_VEC_CONTAINS(vec, this->_zero, TypeParam(-this->_one), this->_zero, this->_zero);
}


#ifdef FGM_LEFT_HANDED

/** @brief Verify that @ref fgm::Vector4::FORWARD returns a unit vector aligned with positive z-axis. */
TYPED_TEST(Vector4Constants, FORWARD_ReturnsUnitVectorWithOnlyPositiveZComponent)
{
    const auto vec = fgm::Vector4<TypeParam>::FORWARD();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one, this->_zero);
}


/** @brief Verify that @ref fgm::Vector4::BACKWARD returns a unit vector aligned with negative z-axis. */
TYPED_TEST(Vector4Constants, BACKWARD_ReturnsUnitVectorWithOnlyNegativeZComponent)
{
    const auto vec = fgm::Vector4<TypeParam>::BACKWARD();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, TypeParam(-this->_one), this->_zero);
}

#else

/** @brief Verify that @ref fgm::Vector4::FORWARD returns a unit vector aligned with negative z-axis. */
TYPED_TEST(Vector4Constants, FORWARD_ReturnsUnitVectorWithOnlyPositiveZComponent)
{
    const auto vec = fgm::Vector4<TypeParam>::FORWARD();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, TypeParam(-this->_one), this->_zero);
}


/** @brief Verify that @ref fgm::Vector4::BACKWARD returns a unit vector aligned with positive z-axis. */
TYPED_TEST(Vector4Constants, BACKWARD_ReturnsUnitVectorWithOnlyNegativeZComponent)
{
    const auto vec = fgm::Vector4<TypeParam>::BACKWARD();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one, this->_zero);
}

#endif

/**
 * @brief Verify that @ref fgm::Vector4::POINT returns a vector with a unit z-component
 *        and zero <x,y,z> component by default.
 */
TYPED_TEST(Vector4Constants, POINT_ReturnsVectorWithUnitZComponent)
{
    const auto vec = fgm::Vector4<TypeParam>::POINT();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_zero, this->_one);
}

/**
 * @brief Verify that @ref fgm::Vector4::POINT returns a vector with a unit z-component
 *        and passed-in <x,y,z> component.
 */
TYPED_TEST(Vector4Constants, POINT_ReturnsVectorWithUnitZComponentAndPassedInXYZComponent)
{
    const auto x   = TypeParam(5);
    const auto y   = TypeParam(8);
    const auto z   = TypeParam(12);
    const auto vec = fgm::Vector4<TypeParam>::POINT(x, y, z);
    EXPECT_VEC_CONTAINS(vec, x, y, z, this->_one);
}

/** @} */
