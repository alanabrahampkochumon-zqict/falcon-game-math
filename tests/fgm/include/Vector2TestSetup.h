#pragma once
/**
 * @file Vector3TestSetup.h
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Define test setups common to all @ref Vector3 tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#define FORCE_SCALAR
#define ENABLE_FGM_SHADER_OPERATORS

#include "CommonSetup.h"
#include "utils/VectorUtils.h"

#include <fgm/common/MathTraits.h>
#include <fgm/vectors/Vector3.h>
#include <gtest/gtest.h>



using namespace testutils;
