/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify alias for @ref fgm::Vector4D returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


/**
 * @addtogroup T_FGM_Vec4_Alias
 * @{
 */

/** @test Verify @ref fgm::bVec4 has bool value_type. */
TEST(Vector4DAlias, bVec4IsA4DBoolVector)
{
    static_assert(std::is_same_v<fgm::bVec4::value_type, bool> && "bVec4 must contain boolean elements");
    static_assert(std::is_same_v<fgm::bVec4, fgm::Vector4D<bool>> && "bVec4 must be an alias of Vector4D<bool>");
}


/** @test Verify @ref fgm::iVec4 has int value_type. */
TEST(Vector4DAlias, iVec4IsA4DIntVector)
{
    static_assert(std::is_same_v<fgm::iVec4::value_type, int> && "iVec4 must contain int elements");
    static_assert(std::is_same_v<fgm::iVec4, fgm::Vector4D<int>> && "iVec4 must be an alias of Vector4D<int>");
}


/** @test Verify @ref fgm::uVec4 has unsigned int value_type. */
TEST(Vector4DAlias, uVec4IsA4DUnsignedIntVector)
{
    static_assert(std::is_same_v<fgm::uVec4::value_type, unsigned int> && "uVec4 must contain unsigned int elements");
    static_assert(std::is_same_v<fgm::uVec4, fgm::Vector4D<unsigned int>> &&
                  "uVec4 must be an alias of Vector4D<unsigned int>");
}


/** @test Verify @ref fgm::vec4 has float value_type. */
TEST(Vector4DAlias, vec4IsA4DFloatVector)
{
    static_assert(std::is_same_v<fgm::vec4::value_type, float> && "vec4 must contain float elements");
    static_assert(std::is_same_v<fgm::vec4, fgm::Vector4D<float>> && "vec4 must be an alias of Vector4D<float>");
}


/** @test Verify @ref fgm::lVec4 has long long value_type. */
TEST(Vector4DAlias, lVec4IsA4DLongLongVector)
{
    static_assert(std::is_same_v<fgm::lVec4::value_type, long long> && "lVec4 must contain long long elements");
    static_assert(std::is_same_v<fgm::lVec4, fgm::Vector4D<long long>> &&
                  "lVec4 must be an alias of Vector4D<long long>");
}


/** @test Verify @ref fgm::dVec4 has double value_type. */
TEST(Vector4DAlias, dVec4IsA4DDoubleVector)
{
    static_assert(std::is_same_v<fgm::dVec4::value_type, double> && "dVec4 must contain double elements");
    static_assert(std::is_same_v<fgm::dVec4, fgm::Vector4D<double>> && "dVec4 must be an alias of Vector4D<double>");
}


/** @test Verify @ref fgm::ulVec4 has unsigned long long value_type. */
TEST(Vector4DAlias, ulVec4IsA4DUnsignedLongLongVector)
{
    static_assert(std::is_same_v<fgm::ulVec4::value_type, unsigned long long> &&
                  "ulVec4 must contain unsigned long long elements");
    static_assert(std::is_same_v<fgm::ulVec4, fgm::Vector4D<unsigned long long>> &&
                  "ulVec4 must be an alias of Vector4D<unsigned long long>");
}

/** @} */