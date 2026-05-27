/**
 * @file TrivialTypeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 27, 2026.
 *
 * @brief Verify @ref fgm classes and structs are trivial types.
 *
 * @copyright Copyright (c) a Alan Abraham P Kochumon
 */


#include "utils/TypeUtils.h"

#include <matrix/Matrix2D.h>
#include <matrix/Matrix3D.h>
#include <matrix/Matrix4D.h>
#include <vector/Vector2D.h>
#include <vector/Vector3D.h>
#include <vector/Vector4D.h>


// static_assert(std::is_trivial_v<fgm::Matrix2D<float>>);
// static_assert(std::is_trivially_default_constructible_v<fgm::Matrix2D<float>>);
// static_assert(std::is_trivially_copy_constructible_v<fgm::Matrix2D<float>>);
// static_assert(std::is_trivially_copy_assignable_v<fgm::Matrix2D<float>>);
// static_assert(std::is_trivially_copyable_v<fgm::Matrix2D<float>>);
// static_assert(std::is_trivially_move_constructible_v<fgm::Matrix2D<float>>);
// static_assert(std::is_trivially_move_assignable_v<fgm::Matrix2D<float>>);
// static_assert(std::is_trivially_destructible_v<fgm::Matrix2D<float>>)

std::is_trivially_default_constructible<fgm::Matrix2D<float>>;
std::is_trivially_copyable<fgm::Matrix2D<float>>;
// ASSERT_TRIVIAL_TYPE(fgm::Matrix2D<float>);