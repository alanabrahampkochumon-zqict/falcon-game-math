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


/**
 * @addtogroup T_FGM_Trivial
 * @{
 */


/** @brief Verify that @ref fgm Vectors are trivial types. */
ASSERT_TRIVIAL_TYPE(fgm::Vector2D<float>);
ASSERT_TRIVIAL_TYPE(fgm::Vector3D<float>);
ASSERT_TRIVIAL_TYPE(fgm::Vector4D<float>);

/** @} */