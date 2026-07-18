/**
 * @file PNormTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 22, 2026
 *
 * @brief Verify the @ref fgm::Vec2 p-Norm length logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vec2TestSetup.h"



template <typename T>
class Vec2ManhattanNorm: public testing::Test
{
protected:
    fgm::Vec2<T> _vec;
    T _norm;

    void SetUp() override
    {
        _vec  = { T(1), T(2) };
        _norm = T(3);
    }
};
/** @brief Test fixture for @ref fgm::Vec2 manhattan norm, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec2ManhattanNorm, SupportedArithmeticTypes);


template <typename T>
class Vec2ChebyshevNorm: public testing::Test
{
protected:
    fgm::Vec2<T> _vec;
    T _norm;

    void SetUp() override
    {
        _vec  = { T(1), T(2) };
        _norm = T(2);
    }
};
/** @brief Test fixture for @ref fgm::Vec2 chebyshev norm, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec2ChebyshevNorm, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Vec2_Norm
 * @{
 */

/** @brief Verify that pNorm (Manhattan and Chebyshev length) operations are available at compile time. */
namespace
{
    constexpr fgm::Vec2 vector(1, -2);

    // L1 Norm (Manhattan Norm)
    static_assert(vector.manhattanNorm() == 3);
    static_assert(fgm::Vec2<int>::manhattanNorm(vector) == 3);

    // L∞ Norm (Chebyshev Norm)
    static_assert(vector.chebyshevNorm() == 2);
    static_assert(fgm::Vec2<int>::chebyshevNorm(vector) == 2);

} // namespace


/**************************************
 *                                    *
 *           MANHATTAN NORM           *
 *                                    *
 **************************************/

/** @brief Verify that taking the manhattan norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vec2ManhattanNorm, ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = this->_vec.manhattanNorm();

    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @brief Verify that taking the manhattan norm of a non-unit vector using static variant of
 *        @ref fgm::Vec2::manhattanNorm returns non-unit scalar.
 */
TYPED_TEST(Vec2ManhattanNorm, StaticWrapper_ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = fgm::Vec2<TypeParam>::manhattanNorm(this->_vec);

    EXPECT_MAG_EQ(this->_norm, magnitude);
}



/**************************************
 *                                    *
 *           CHEBYSHEV NORM           *
 *                                    *
 **************************************/

/** @brief Verify that taking the chebyshev norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vec2ChebyshevNorm, ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = this->_vec.chebyshevNorm();

    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @brief Verify that taking the chebyshev norm of a non-unit vector using static variant of
 *        @ref fgm::Vec2::chebyshevNorm returns non-unit scalar.
 */
TYPED_TEST(Vec2ChebyshevNorm, StaticWrapper_ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = fgm::Vec2<TypeParam>::chebyshevNorm(this->_vec);

    EXPECT_MAG_EQ(this->_norm, magnitude);
}

/** @} */
