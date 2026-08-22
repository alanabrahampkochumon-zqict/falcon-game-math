#pragma once
/**
 * @file SIMDTestSetup.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 10, 2026
 *
 * @brief Test setups common to all @ref falcon::simd tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <bit>
#include <cstdint>
#include <falcon_simd/FalconSimd.h>
#include <gtest/gtest.h>
#include <limits>

using SupportedSIMDTypes =
    testing::Types<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, double, float>;
using SupportedSIMDIntegralTypes =
    testing::Types<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>;


template <typename T, size_t V>
struct SimdRegisterTypeMatrix
{
    using Type                    = T;
    static constexpr size_t VALUE = V;
};


using Simd128RegisterTypeHints = testing::Types<
    SimdRegisterTypeMatrix<uint8_t, 2>, SimdRegisterTypeMatrix<uint8_t, 4>, SimdRegisterTypeMatrix<uint8_t, 4>,
    SimdRegisterTypeMatrix<uint8_t, 8>, SimdRegisterTypeMatrix<uint8_t, 16>, SimdRegisterTypeMatrix<uint16_t, 2>,
    SimdRegisterTypeMatrix<uint16_t, 4>, SimdRegisterTypeMatrix<uint16_t, 8>, SimdRegisterTypeMatrix<uint32_t, 2>,
    SimdRegisterTypeMatrix<uint32_t, 4>, SimdRegisterTypeMatrix<uint64_t, 2>, SimdRegisterTypeMatrix<int8_t, 2>,
    SimdRegisterTypeMatrix<int8_t, 4>, SimdRegisterTypeMatrix<int8_t, 4>, SimdRegisterTypeMatrix<int8_t, 8>,
    SimdRegisterTypeMatrix<int8_t, 16>, SimdRegisterTypeMatrix<int16_t, 2>, SimdRegisterTypeMatrix<int16_t, 4>,
    SimdRegisterTypeMatrix<int16_t, 8>, SimdRegisterTypeMatrix<int32_t, 2>, SimdRegisterTypeMatrix<int32_t, 4>,
    SimdRegisterTypeMatrix<int64_t, 2>, SimdRegisterTypeMatrix<float, 2>, SimdRegisterTypeMatrix<float, 4>,
    SimdRegisterTypeMatrix<double, 2>>;


/// TODO: Add the below helpers to main library.

/// Helper that returns all 1s bitwise(1111..1111) for the given type.
template <typename T>
constexpr T getAllOnes()
{
    if constexpr (std::is_integral_v<T>)
    {
        return static_cast<T>(-1);
    }
    else if constexpr (sizeof(T) == 4)
    {
        return std::bit_cast<T>(std::numeric_limits<uint32_t>::max());
    }
    else if constexpr (sizeof(T) == 8)
    {
        return std::bit_cast<T>(std::numeric_limits<uint64_t>::max());
    }
    return 1; // Shouldn't hit this path.
}


/// @brief Test whether a and b are equal bitwise.
template <typename T>
constexpr bool isEqualBitwise(T a, T b)
{
    if constexpr (std::is_same_v<T, double>)
    {
        return std::bit_cast<uint64_t>(a) == std::bit_cast<uint64_t>(b);
    }
    else if constexpr (std::is_same_v<T, float>)
    {
        return std::bit_cast<uint32_t>(a) == std::bit_cast<uint32_t>(b);
    }
    else
    {
        return a == b;
    }
}
