/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief `Vector4D` alias (`vec4`, `bVec4`, ...) tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


TEST(Vector4DAlias, bVec4IsA4DBoolVector)
{
    static_assert(std::is_same_v<math::bVec4::value_type, bool> && "bVec4 must contain boolean elements");
    static_assert(std::is_same_v<math::bVec4, math::Vector4D<bool>> && "bVec4 must be an alias of Vector4D<bool>");
}

TEST(Vector4DAlias, iVec4IsA4DIntVector)
{
    static_assert(std::is_same_v<math::iVec4::value_type, int> && "iVec4 must contain int elements");
    static_assert(std::is_same_v<math::iVec4, math::Vector4D<int>> && "iVec4 must be an alias of Vector4D<int>");
}

TEST(Vector4DAlias, uVec4IsA4DUnsignedIntVector)
{
    static_assert(std::is_same_v<math::uVec4::value_type, unsigned int> && "uVec4 must contain unsigned int elements");
    static_assert(std::is_same_v<math::uVec4, math::Vector4D<unsigned int>> &&
                  "uVec4 must be an alias of Vector4D<unsigned int>");
}

TEST(Vector4DAlias, vec4IsA4DFloatVector)
{
    static_assert(std::is_same_v<math::vec4::value_type, float> && "vec4 must contain float elements");
    static_assert(std::is_same_v<math::vec4, math::Vector4D<float>> && "vec4 must be an alias of Vector4D<float>");
}

TEST(Vector4DAlias, lVec4IsA4DLongLongVector)
{
    static_assert(std::is_same_v<math::lVec4::value_type, long long> && "lVec4 must contain long long elements");
    static_assert(std::is_same_v<math::lVec4, math::Vector4D<long long>> &&
                  "lVec4 must be an alias of Vector4D<long long>");
}

TEST(Vector4DAlias, dVec4IsA4DDoubleVector)
{
    static_assert(std::is_same_v<math::dVec4::value_type, double> && "dVec4 must contain double elements");
    static_assert(std::is_same_v<math::dVec4, math::Vector4D<double>> && "dVec4 must be an alias of Vector4D<double>");
}

TEST(Vector4DAlias, ulVec4IsA4DUnsignedLongLongVector)
{
    static_assert(std::is_same_v<math::ulVec4::value_type, unsigned long long> &&
                  "ulVec4 must contain unsigned long long elements");
    static_assert(std::is_same_v<math::ulVec4, math::Vector4D<unsigned long long>> &&
                  "ulVec4 must be an alias of Vector4D<unsigned long long>");
}