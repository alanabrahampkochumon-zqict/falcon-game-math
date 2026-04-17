#pragma once
/**
 * @file MatrixTestSetup.h
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Define test setups common to all Matrix tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#define FORCE_SCALAR

#include "utils/MatrixUtils.h"
#include "utils/VectorUtils.h"

#include <common/MathTraits.h>
#include <gtest/gtest.h>
#include <limits>
#include <matrix/Matrix2D.h>
#include <utility>
#include <vector>



using namespace testutils;


using SupportedTypes =
    ::testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, bool, float, double>;
using SupportedArithmeticTypes =
    ::testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, float, double>;
using SupportedSignedArithmeticTypes = ::testing::Types<int8_t, int16_t, int32_t, int64_t, float, double>;
using SupportedIntegralTypes =
    ::testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t>;
using SupportedFloatingPointTypes = ::testing::Types<float, double>;
using SupportedArithmeticFloatingTypePair = ::testing::Types<
    std::pair<float, int8_t>, std::pair<float, int16_t>, std::pair<float, int32_t>, std::pair<float, int64_t>,
    std::pair<float, uint8_t>, std::pair<float, uint16_t>, std::pair<float, uint32_t>, std::pair<float, uint64_t>,
    std::pair<float, double>, std::pair<float, float>, std::pair<double, int8_t>, std::pair<double, int16_t>,
    std::pair<double, int32_t>, std::pair<double, int64_t>, std::pair<double, uint8_t>, std::pair<double, uint16_t>,
    std::pair<double, uint32_t>, std::pair<double, uint64_t>, std::pair<double, double>, std::pair<double, float>>;
using SupportedSignedArithmeticFloatingTypePair =
    ::testing::Types<std::pair<float, int8_t>, std::pair<float, int16_t>, std::pair<float, int32_t>,
                     std::pair<float, int64_t>, std::pair<float, float>, std::pair<double, int8_t>,
                     std::pair<double, int16_t>, std::pair<double, int32_t>, std::pair<double, int64_t>,
                     std::pair<double, double>, std::pair<double, float>>;