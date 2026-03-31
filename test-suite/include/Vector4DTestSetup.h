#pragma once
/**
 * @file Vector4DTestSetup.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Define test setups common to all @ref Vector4D tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#define FORCE_SCALAR
#define ENABLE_FGM_SHADER_OPERATORS

#include "./utils/VectorUtils.h"

#include <common/MathTraits.h>
#include <gtest/gtest.h>
#include <limits>
#include <vector/Vector4D.h>


using SupportedTypes = ::testing::Types<unsigned char, bool, int, unsigned int, float, double, std::size_t, long long>;
using SupportedArithmeticTypes =
    ::testing::Types<unsigned char, int, unsigned int, float, double, std::size_t, long long>;
using SupportedSignedArithmeticTypes = ::testing::Types<short, int, float, double, long long>;
using SupportedIntegralTypes =
    ::testing::Types<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>;


/** @brief Test fixture for @fgm::Vector4D NaN tests */
class Vector4DNaNTests: public ::testing::TestWithParam<fgm::Vector4D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vector4DNaNTestSuite, Vector4DNaNTests,
                         ::testing::Values(fgm::Vector4D<float>(fgm::constants::NaN, 1.0f, 1.0f, 1.0f),
                                           fgm::Vector4D<float>(1.0f, fgm::constants::NaN, 1.0f, 1.0f),
                                           fgm::Vector4D<float>(1.0f, 1.0f, fgm::constants::NaN, 1.0f),
                                           fgm::Vector4D<float>(1.0f, 1.0f, 1.0f, fgm ::constants::NaN),
                                           fgm::Vector4D<float>(fgm ::constants::NaN, fgm ::constants::NaN,
                                                                fgm ::constants::NaN, fgm ::constants::NaN)));