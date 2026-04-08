#pragma once
/**
 * @file SIMDTestSetup.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 10, 2026
 *
 * @brief Test setups common to all @ref SIMD tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <SIMD.h>
#include <gtest/gtest.h>



using SupportedSIMDTypes =
    ::testing::Types<unsigned char, bool, int, unsigned int, float, double, std::size_t, long long>;
using SupportedSIMDIntegralTypes = ::testing::Types<unsigned char, bool, int, unsigned int, std::size_t, long long>;
