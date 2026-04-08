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


#include <simd/SIMD.h>
#include <gtest/gtest.h>
#include <cstdint>


using SupportedSIMDTypes =
    ::testing::Types<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, double, float>;
using SupportedSIMDIntegralTypes = ::testing::Types<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>;
