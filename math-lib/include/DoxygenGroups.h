#pragma once
/**
 * @file DoxygenGroups.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 18, 2026
 *
 * @brief Definitions for doxygen groups used across fgm math library.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


// clang-format off
/**
 * @defgroup FGM_Math Math Library
 * @brief Complete math library.
 * @{
 */
    
    /**
     * @defgroup FGM_Core Core
     * @brief Fundamental mathematical structures and types.
     * @ingroup FGM_Math
     * @{
     */

        /**
         * @defgroup FGM_Vectors Vectors
         * @brief N-dimensional Euclidean vector implementations.
         * @ingroup FGM_Math
         * @{
         *   @defgroup FGM_Vec2 Vector2D
         *   @defgroup FGM_Vec3 Vector3D
         *   @defgroup FGM_Vec4 Vector4D
         * @}
         */

    /** @} */ // End of Core

    /**
     * @defgroup FGM_Concepts Concepts
     * @brief Fundamental mathematical constraints.
     * @ingroup FGM_Math
     * @{
     *   @defgroup FGM_Concepts Math Concepts
     * @}
     */

/** @} */ // End of FGM_Math

// clang-format on