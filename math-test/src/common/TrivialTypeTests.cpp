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

#include <fgm/matrices/Matrix2.h>
#include <fgm/matrices/Matrix3.h>
#include <fgm/matrices/Matrix4.h>
#include <fgm/vectors/Vector2.h>
#include <fgm/vectors/Vector3.h>
#include <fgm/vectors/Vector4.h>


/**
 * @addtogroup T_FGM_Trivial
 * @{
 */

/** @brief Verify that @ref fgm Vectors are trivial types. */
ASSERT_TRIVIAL_TYPE(fgm::Vector2<float>);
ASSERT_TRIVIAL_TYPE(fgm::Vector3<float>);
ASSERT_TRIVIAL_TYPE(fgm::Vector4<float>);


/** @brief Verify that @ref fgm Matrices are trivial types. */
ASSERT_TRIVIAL_TYPE(fgm::Matrix2<float>);
ASSERT_TRIVIAL_TYPE(fgm::Matrix3<float>);
ASSERT_TRIVIAL_TYPE(fgm::Matrix4<float>);

/** @} */
