/**
 * @file PNormTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 22, 2026
 *
 * @brief Verify the @ref fgm::Vec3 p-Norm length logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vec3TestSetup.h"



template <typename T>
class Vec3ManhattanNorm: public testing::Test
{
protected:
    fgm::Vec3<T> _vec;
    T _norm;

    void SetUp() override
    {
        _vec  = { T(1), T(2), T(4) };
        _norm = T(7);
    }
};
/** @brief Test fixture for @ref fgm::Vec3 manhattan norm, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec3ManhattanNorm, SupportedArithmeticTypes);


template <typename T>
class Vec3ChebyshevNorm: public testing::Test
{
protected:
    fgm::Vec3<T> _vec;
    T _norm;

    void SetUp() override
    {
        _vec  = { T(1), T(2), T(4) };
        _norm = T(4);
    }
};
/** @brief Test fixture for @ref fgm::Vec3 chebyshev norm, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec3ChebyshevNorm, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Norm
 * @{
 */

/** @brief Verify that pNorm (Manhattan and Chebyshev length) operations are available at compile time. */
namespace
{
    constexpr fgm::Vec3 vector(1, -2, 4);

    // L1 Norm (Manhattan Norm)
    static_assert(vector.manhattanNorm() == 7);
    static_assert(fgm::Vec3<int>::manhattanNorm(vector) == 7);

    // L∞ Norm (Chebyshev Norm)
    static_assert(vector.chebyshevNorm() == 4);
    static_assert(fgm::Vec3<int>::chebyshevNorm(vector) == 4);

} // namespace


/**************************************
 *                                    *
 *           MANHATTAN NORM           *
 *                                    *
 **************************************/

/** @brief Verify that taking the manhattan norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vec3ManhattanNorm, ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = this->_vec.manhattanNorm();

    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @brief Verify that taking the manhattan norm of a non-unit vector using static variant of
 *        @ref fgm::Vec3::manhattanNorm returns non-unit scalar.
 */
TYPED_TEST(Vec3ManhattanNorm, StaticWrapper_ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = fgm::Vec3<TypeParam>::manhattanNorm(this->_vec);

    EXPECT_MAG_EQ(this->_norm, magnitude);
}



/**************************************
 *                                    *
 *           CHEBYSHEV NORM           *
 *                                    *
 **************************************/

/** @brief Verify that taking the chebyshev norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vec3ChebyshevNorm, ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = this->_vec.chebyshevNorm();

    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @brief Verify that taking the chebyshev norm of a non-unit vector using static variant of
 *        @ref fgm::Vec3::chebyshevNorm returns non-unit scalar.
 */
TYPED_TEST(Vec3ChebyshevNorm, StaticWrapper_ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = fgm::Vec3<TypeParam>::chebyshevNorm(this->_vec);

    EXPECT_MAG_EQ(this->_norm, magnitude);
}

/** @} */
