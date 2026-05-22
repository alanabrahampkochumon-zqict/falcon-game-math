/**
 * @file PNormTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 22, 2026
 *
 * @brief Verify the @ref fgm::Vector2D p-Norm length logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vector2DTestSetup.h"



template <typename T>
class Vector2DManhattanNorm: public testing::Test
{
protected:
    fgm::Vector2D<T> _vec;
    T _norm;

    void SetUp() override
    {
        _vec = {1, 2};
        _norm = 3;
    }
};
/** @brief Test fixture for @ref fgm::Vector2D manhattan norm, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector2DManhattanNorm, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Vec2_Norm
 * @{
 */

/** @brief Verify that pNorm (Manhattan and Chebyshev) operations are available at compile time. */
namespace
{
    constexpr fgm::Vector2D vector(1, 2);

    // L1 Norm (Manhattan Norm)
    static_assert(vector.manhattanNorm() == 3);
    static_assert(fgm::Vector2D<int>::manhattanNorm(vector) == 3);

} // namespace


/**************************************
 *                                    *
 *           MANHATTAN NORM           *
 *                                    *
 **************************************/

/** @brief Verify that taking the manhattan norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vector2DManhattanNorm, MagnitudeSquare_ReturnsSquaredMagnitude)
{
    const auto magnitude = this->_vec.manhattanNorm();

    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @brief Verify that taking the manhattan norm of a non-unit vector using static variant of
 *        @ref fgm::Vector2D::manhattanNorm returns non-unit scalar.
 */
TYPED_TEST(Vector2DManhattanNorm, StaticWrapper_MagnitudeSquare_ReturnsSquaredMagnitude)
{
    const auto magnitude = fgm::Vector2D<TypeParam>::manhattanNorm(this->_vec);

    EXPECT_MAG_EQ(this->_norm, magnitude);
}

/** @} */
