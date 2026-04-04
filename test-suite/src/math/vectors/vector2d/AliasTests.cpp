/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify alias for @ref fgm::Vector2D returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"



/**
 * @addtogroup T_FGM_Vec2_Alias
 * @{
 */

/** @test Verify @ref fgm::bVec2 has `bool` value_type. */
TEST(Vector2DAlias, bVec2IsA2DBoolVector)
{
    static_assert(std::is_same_v<fgm::bVec2::value_type, bool> && "bVec2 must contain boolean elements");
    static_assert(std::is_same_v<fgm::bVec2, fgm::Vector2D<bool>> && "bVec2 must be an alias of Vector2D<bool>");
}


/** @test Verify @ref fgm::iVec2 has `int` value_type. */
TEST(Vector2DAlias, iVec2IsA2DIntVector)
{
    static_assert(std::is_same_v<fgm::iVec2::value_type, int> && "iVec2 must contain int elements");
    static_assert(std::is_same_v<fgm::iVec2, fgm::Vector2D<int>> && "iVec2 must be an alias of Vector2D<int>");
}


/** @test Verify @ref fgm::uVec2 has `unsigned int` value_type. */
TEST(Vector2DAlias, uVec2IsA2DUnsignedIntVector)
{
    static_assert(std::is_same_v<fgm::uVec2::value_type, unsigned int> && "uVec2 must contain unsigned int elements");
    static_assert(std::is_same_v<fgm::uVec2, fgm::Vector2D<unsigned int>> &&
                  "uVec2 must be an alias of Vector2D<unsigned int>");
}


/** @test Verify @ref fgm::vec2 has `float` value_type. */
TEST(Vector2DAlias, vec2IsA2DFloatVector)
{
    static_assert(std::is_same_v<fgm::vec2::value_type, float> && "vec2 must contain float elements");
    static_assert(std::is_same_v<fgm::vec2, fgm::Vector2D<float>> && "vec2 must be an alias of Vector2D<float>");
}


/** @test Verify @ref fgm::lVec2 has `long long` value_type. */
TEST(Vector2DAlias, lVec2IsA2DLongLongVector)
{
    static_assert(std::is_same_v<fgm::lVec2::value_type, long long> && "lVec2 must contain long long elements");
    static_assert(std::is_same_v<fgm::lVec2, fgm::Vector2D<long long>> &&
                  "lVec2 must be an alias of Vector2D<long long>");
}


/** @test Verify @ref fgm::dVec2 has `double` value_type. */
TEST(Vector2DAlias, dVec2IsA2DDoubleVector)
{
    static_assert(std::is_same_v<fgm::dVec2::value_type, double> && "dVec2 must contain double elements");
    static_assert(std::is_same_v<fgm::dVec2, fgm::Vector2D<double>> && "dVec2 must be an alias of Vector2D<double>");
}


/** @test Verify @ref fgm::ulVec2 has `unsigned long long` value_type. */
TEST(Vector2DAlias, ulVec2IsA2DUnsignedLongLongVector)
{
    static_assert(std::is_same_v<fgm::ulVec2::value_type, unsigned long long> &&
                  "ulVec2 must contain unsigned long long elements");
    static_assert(std::is_same_v<fgm::ulVec2, fgm::Vector2D<unsigned long long>> &&
                  "ulVec2 must be an alias of Vector2D<unsigned long long>");
}

/** @} */