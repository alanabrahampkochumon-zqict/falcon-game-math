/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vector2 constants (@ref fgm::Vector2::ONE, @ref fgm::Vector2::ZERO, etc).
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
/** @brief Test fixture for @ref fgm::Vector2 constants, parameterized by @ref SupportedSignedArithmeticTypes. */
// Unsigned types not tested since only zero and one are constraint to include unsigned types.
TYPED_TEST_SUITE(Vector2Constants, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec2_Const
 * @{
 */

/** @brief Verify that @ref fgm::Vector2 constants are available at compile time. */
namespace
{
    static_assert(fgm::Vector2<int>::ONE().x() == 1);
    static_assert(fgm::Vector2<int>::ONE().y() == 1);

    static_assert(fgm::Vector2<int>::ZERO().x() == 0);
    static_assert(fgm::Vector2<int>::ZERO().y() == 0);

    static_assert(fgm::isinf(fgm::Vector2<float>::INF().x()));
    static_assert(fgm::isinf(fgm::Vector2<float>::INF().y()));

    static_assert(fgm::isinf(fgm::Vector2<float>::INF_NEG().x()));
    static_assert(fgm::isinf(fgm::Vector2<float>::INF_NEG().y()));


    static_assert(fgm::isnan(fgm::Vector2<float>::QNAN().x()));
    static_assert(fgm::isnan(fgm::Vector2<float>::QNAN().y()));

    static_assert(fgm::Vector2<int>::LEFT().x() == -1);
    static_assert(fgm::Vector2<int>::LEFT().y() == 0);

    static_assert(fgm::Vector2<int>::RIGHT().x() == 1);
    static_assert(fgm::Vector2<int>::RIGHT().y() == 0);

    static_assert(fgm::Vector2<int>::UP().x() == 0);
    static_assert(fgm::Vector2<int>::UP().y() == 1);

    static_assert(fgm::Vector2<int>::DOWN().x() == 0);
    static_assert(fgm::Vector2<int>::DOWN().y() == -1);

} // namespace


/** @brief Verify that @ref fgm::Vector2::ONE() returns a 2D vector with unit components. */
TYPED_TEST(Vector2Constants, ONE_ReturnsVectorWithUnitComponents)
{
    const auto one = TypeParam(1);
    EXPECT_VEC_CONTAINS(fgm::Vector2<TypeParam>::ONE(), one, one);
}


/** @brief Verify that @ref fgm::Vector2::ZERO returns a 2D vector with zero components. */
TYPED_TEST(Vector2Constants, ZERO_ReturnsVectorWithZeroComponents) { EXPECT_VEC_ZERO(fgm::Vector2<TypeParam>::ZERO()); }


/** @brief Verify that @ref fgm::Vector2<float>::INF returns a 2D vector with infinity components. */
TEST(Vector2Constants, Float_INF_ReturnsFloatVectorWithInfinityComponents)
{
    const auto inf = fgm::Vector2<float>::INF();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC2_POS_INF(inf)
}


/** @brief Verify that @ref fgm::Vector2<double>::INF returns a 2D vector with infinity components. */
TEST(Vector2Constants, Double_INF_ReturnsDoubleVectorWithInfinityComponents)
{
    const auto inf = fgm::Vector2<double>::INF();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC2_POS_INF(inf)
}


/** @brief Verify that @ref fgm::Vector2<float>::INF_NEG returns a 2D vector with negative infinity components. */
TEST(Vector2Constants, Float_INF_NEG_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::Vector2<float>::INF_NEG();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC2_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::Vector2<double>::INF_NEG returns a 2D vector with negative infinity components. */
TEST(Vector2Constants, Double_INF_NEG_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    const auto inf = fgm::Vector2<double>::INF_NEG();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC2_NEG_INF(inf)
}


/** @brief Verify that @ref fgm::Vector2<float>::QNAN returns a 2D vector with NaN components. */
TEST(Vector2Constants, Float_QNAN_ReturnsFloatVectorWithNaNComponents)
{
    const auto nan = fgm::Vector2<float>::QNAN();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @brief Verify that @ref fgm::Vector2<double>::QNAN returns a 2D vector with NaN components. */
TEST(Vector2Constants, Double_QNAN_ReturnsDoubleVectorWithNaNComponents)
{
    const auto nan = fgm::Vector2<double>::QNAN();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @brief Verify that @ref fgm::Vector2::RIGHT returns a unit vector aligned with positive x-axis. */
TYPED_TEST(Vector2Constants, RIGHT_ReturnsUnitVectorWithOnlyPositiveXComponent)
{
    const auto x = fgm::Vector2<TypeParam>::RIGHT();
    EXPECT_VEC_CONTAINS(x, this->_one, this->_zero);
}


/** @brief Verify that @ref fgm::Vector2::LEFT returns a unit vector aligned with negative x-axis. */
TYPED_TEST(Vector2Constants, LEFT_ReturnsUnitVectorWithOnlyNegativeXComponent)
{
    const auto x = fgm::Vector2<TypeParam>::LEFT();
    EXPECT_VEC_CONTAINS(x, TypeParam(-this->_one), this->_zero);
}


/** @brief Verify that @ref fgm::Vector2::UP returns a unit vector aligned with positive y-axis. */
TYPED_TEST(Vector2Constants, UP_ReturnsUnitVectorWithOnlyPositiveYComponent)
{
    const auto x = fgm::Vector2<TypeParam>::UP();
    EXPECT_VEC_CONTAINS(x, this->_zero, this->_one);
}


/** @brief Verify that @ref fgm::Vector2::DOWN returns a unit vector aligned with negative y-axis. */
TYPED_TEST(Vector2Constants, DOWN_ReturnsUnitVectorWithOnlyNegativeYComponent)
{
    const auto x = fgm::Vector2<TypeParam>::DOWN();
    EXPECT_VEC_CONTAINS(x, this->_zero, TypeParam(-this->_one));
}

/** @} */
