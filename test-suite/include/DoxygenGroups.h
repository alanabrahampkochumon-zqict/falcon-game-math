#pragma once
/**
 * @file DoxygenGroups.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 18, 2026
 *
 * @brief Definitions for doxygen groups used across fgm test harness.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


// clang-format off
/**
 * @defgroup FGMTestSuite Test Suite
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
             * @defgroup FGM_Vector4D_Tests Vector4D Test Suite
             * @brief Verification of 4D Euclidean vector operations.
             * @ingroup VectorTests
             * @{
             *   @defgroup T_FGM_Vec4_Access Component Access
             *   @defgroup T_FGM_Vec4_Mutation Component Mutation
             *   @defgroup T_FGM_Vec4_Alias Spatial Aliasing
             *   @defgroup T_FGM_Vec4_Const Vector Constants
             *   @defgroup T_FGM_Vec4_Addition Addition
             *   @defgroup T_FGM_Vec4_Subtraction Subtraction
             *   @defgroup T_FGM_Vec4_Multiplication Scalar Multiplication
             *   @defgroup T_FGM_Vec4_Division Scalar Division
             *   @defgroup T_FGM_Vec4_Bool_Bit Boolean Bitwise Operation
             *   @defgroup T_FGM_Vec4_GT_Comp Greater Than Comparison
             *   @defgroup T_FGM_Vec4_GTE_Comp Greater Than or Equal Comparison
             *   @defgroup T_FGM_Vec4_LT_Comp Less Than Comparison
             *   @defgroup T_FGM_Vec4_LTE_Comp Less Than or Equal Comparison
             *   @defgroup T_FGM_Vec4_Equality Component-wise and Masked Equality
             *   @defgroup T_FGM_Vec4_Inequality Component-wise and Masked Inequality
             *   @defgroup T_FGM_Vec4_Init Initialization
             *   @defgroup T_FGM_Vec4_Magnitude Scalar Length(Magnitude)
             *   @defgroup T_FGM_Vec4_Normalize Vector Normalization
             *   @defgroup T_FGM_Vec4_Dot Dot Product
             *   @defgroup T_FGM_Vec4_Proj Vector Projection
             *   @defgroup T_FGM_Vec4_Rej Vector Rejection
             *   @defgroup T_FGM_Vec4_String_Repr Formatted String Representation
             *   @defgroup T_FGM_Vec4_Type_Conv Conversion Constructor
             *   @defgroup T_FGM_Vec4_Inversion Unary Inversion(-)
             * @}
             */

        /** @} */ // End of Vectors
        //TODO: Update Description
        /**
         * @defgroup FGM_Common_Tests Common 
         * @brief Test suite for functions common used in FGM math library.
         * @ingroup MathTests
         * @{
         *   @defgroup T_Op_Status Operation Status
         * @}
         */

    /** @} */ // End of VectorTests

    /**
     * @defgroup T_Utils Test Utilities
     * @brief Diagnostic and validation utilities for testing.
     * @ingroup FGMTestSuite
     * @{
     *   @defgroup Vector_Utils Vector Validation Utilities
     *   @defgroup Matrix_Utils Matrix Validation Utilities
     * @}
     */

/** @} */ // End of FGMTestSuite
// clang-format on