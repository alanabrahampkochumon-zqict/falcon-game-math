/**
 * @file Vector3DTestSetup.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Test setups common to all `Vector3D` tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#pragma once

#define FORCE_SCALAR
#define ENABLE_FGM_SHADER_OPERATORS

#include "utils/VectorUtils.h"

#include <MathTraits.h>
#include <gtest/gtest.h>
#include <limits>
#include <vector/Vector3D.h>


using SupportedTypes = ::testing::Types<unsigned char, bool, int, unsigned int, float, double, std::size_t, long long>;
using SupportedArithmeticTypes =
    ::testing::Types<unsigned char, int, unsigned int, float, double, std::size_t, long long>;
