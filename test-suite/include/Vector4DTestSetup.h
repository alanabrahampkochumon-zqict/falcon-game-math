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

#include "utils/VectorUtils.h"

#include <concepts>
#include <gtest/gtest.h>
#include <vector/Vector4D.h>


using namespace testutils;


using SupportedTypes =
    ::testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, bool, float, double>;
using SupportedArithmeticTypes =
    ::testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, float, double>;
using SupportedSignedArithmeticTypes = ::testing::Types<int8_t, int16_t, int32_t, int64_t, float, double>;
using SupportedIntegralTypes =
    ::testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t>;


template <typename T>
    requires std::floating_point<T>
struct Vector4DNaNParams
{
    fgm::Vector4D<T> nanVector, expectedVector;
};

/** @brief Test fixture for @fgm::Vector4D NaN tests */
class Vector4DNaNTests: public ::testing::TestWithParam<fgm::Vector4D<float>>
{};
class _Vector4DNaNTests: public ::testing::TestWithParam<Vector4DNaNParams<float>>
{}; // TODO: Remove