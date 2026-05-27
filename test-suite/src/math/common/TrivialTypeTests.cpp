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
#include <vectors/Vector2D.h>
#include <vectors/Vector3D.h>
#include <vectors/Vector4D.h>


/**
 * @addtogroup T_FGM_Trivial
 * @{
 */

/** @brief Verify that @ref fgm Vectors are trivial types. */
ASSERT_TRIVIAL_TYPE(fgm::Vector2D<float>);
ASSERT_TRIVIAL_TYPE(fgm::Vector3D<float>);
ASSERT_TRIVIAL_TYPE(fgm::Vector4D<float>);


/** @brief Verify that @ref fgm Matrices are trivial types. */
ASSERT_TRIVIAL_TYPE(fgm::Matrix2D<float>);
ASSERT_TRIVIAL_TYPE(fgm::Matrix3D<float>);
ASSERT_TRIVIAL_TYPE(fgm::Matrix4D<float>);

/** @} */