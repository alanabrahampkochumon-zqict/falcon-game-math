#pragma once
/**
 * @file DoxygenGroups.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 18, 2026
 *
 * @brief Definitions for doxygen groups used across fgm.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


// clang-format off
/**
 * @defgroup FGMTestSuite Falcon Game Math Library Test Suite
 * @brief Master test suite for Falcon Game Math Library.
 * @{
 */
    
    /**
     * @defgroup MathTests Mathematics
     * @brief Test suite for mathematical components.
     * @ingroup FGMTestSuite
     * @{
     */

        /**
         * @defgroup VectorTests Vectors
         * @brief Test suite for vectors.
         * @ingroup MathTests
         * @{
         */

            /**
             * @defgroup FGMVector4D Vector4D Test Suite
             * @brief Verification of 4D Euclidean vector operations.
             * @ingroup VectorTests
             * @{
             *   @defgroup FGM_Vec4_Access Component Access
             *   @defgroup FGM_Vec4_Mutation Component Mutation
             *   @defgroup FGM_Vec4_Alias Spatial Aliasing
             *   @defgroup FGM_Vec4_Addition Addition
             *   @defgroup FGM_Vec4_Subtraction Subtraction
             *   @defgroup FGM_Vec4_Multiplication Scalar Multiplication
             *   @defgroup FGM_Vec4_Division Scalar Division
             *   @defgroup FGM_Vec4_GT_Comp Greater Than Comparison
             *   @defgroup FGM_Vec4_GTE_Comp Greater Than or Equal Comparison
             *   @defgroup FGM_Vec4_LT_Comp Less Than Comparison
             *   @defgroup FGM_Vec4_LTE_Comp Less Than or Equal Comparison
             *   @defgroup FGM_Vec4_Equality Component-wise and Masked Equality
             *   @defgroup FGM_Vec4_Inequality Component-wise and Masked Inequality
             *   @defgroup FGM_Vec4_Magnitude Scalar Length(Magnitude)
             *   @defgroup FGM_Vec4_Normalize Vector Normalization
             *   @defgroup FGM_Vec4_Dot Dot Product
             *   @defgroup FGM_Vec4_Proj Vector Projection
             *   @defgroup FGM_Vec4_Rej Vector Rejection
             *   @defgroup FGM_Vec4_String_Repr Formatted String Representation
             *   @defgroup FGM_Vec4_Type_Conv Conversion Constructor
             * @}
             */

        /** @} */ // End of VectorTests

    /** @} */ // End of MathTests

/** @} */ // End of FGMTestSuite

// clang-format on