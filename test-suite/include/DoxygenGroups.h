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
             * @defgroup FGM_Vector2D_Tests Vector4D Test Suite
             * @brief Verification of 2D Euclidean vector operations.
             * @ingroup VectorTests
             * @{
             *   @defgroup T_FGM_Vec2_Access Component Access
             *   @defgroup T_FGM_Vec2_Mutation Component Mutation
             *   @defgroup T_FGM_Vec2_Alias Spatial Aliasing
             *   @defgroup T_FGM_Vec2_Const Vector Constants
             *   @defgroup T_FGM_Vec2_Addition Addition
             *   @defgroup T_FGM_Vec2_Subtraction Subtraction
             *   @defgroup T_FGM_Vec2_Multiplication Scalar Multiplication
             *   @defgroup T_FGM_Vec2_Division Scalar Division
             *   @defgroup T_FGM_Vec2_Bool_Bit Boolean Bitwise Operation
             *   @defgroup T_FGM_Vec2_GT_Comp Greater Than Comparison
             *   @defgroup T_FGM_Vec2_GTE_Comp Greater Than or Equal Comparison
             *   @defgroup T_FGM_Vec2_LT_Comp Less Than Comparison
             *   @defgroup T_FGM_Vec2_LTE_Comp Less Than or Equal Comparison
             *   @defgroup T_FGM_Vec2_Equality Component-wise and Masked Equality
             *   @defgroup T_FGM_Vec2_Inequality Component-wise and Masked Inequality
             *   @defgroup T_FGM_Vec2_Init Initialization
             *   @defgroup T_FGM_Vec2_Magnitude Scalar Length(Magnitude)
             *   @defgroup T_FGM_Vec2_Normalize Vector Normalization
             *   @defgroup T_FGM_Vec2_Product Dot and Cross Product
             *   @defgroup T_FGM_Vec2_Proj Vector Projection
             *   @defgroup T_FGM_Vec2_Rej Vector Rejection
             *   @defgroup T_FGM_Vec2_String_Repr Formatted String Representation
             *   @defgroup T_FGM_Vec2_Type_Conv Conversion Constructor
             *   @defgroup T_FGM_Vec2_Inversion Unary Inversion(-)
             *   @defgroup T_FGM_Vec2_Utils Vector Utilities
             *   @defgroup T_FGM_Vec2_Swizzle Vector Swizzling
             * @}
             */


            /**
             * @defgroup FGM_Vector3D_Tests Vector4D Test Suite
             * @brief Verification of 3D Euclidean vector operations.
             * @ingroup VectorTests
             * @{
             *   @defgroup T_FGM_Vec3_Access Component Access
             *   @defgroup T_FGM_Vec3_Mutation Component Mutation
             *   @defgroup T_FGM_Vec3_Alias Spatial Aliasing
             *   @defgroup T_FGM_Vec3_Const Vector Constants
             *   @defgroup T_FGM_Vec3_Addition Addition
             *   @defgroup T_FGM_Vec3_Subtraction Subtraction
             *   @defgroup T_FGM_Vec3_Multiplication Scalar Multiplication
             *   @defgroup T_FGM_Vec3_Division Scalar Division
             *   @defgroup T_FGM_Vec3_Bool_Bit Boolean Bitwise Operation
             *   @defgroup T_FGM_Vec3_GT_Comp Greater Than Comparison
             *   @defgroup T_FGM_Vec3_GTE_Comp Greater Than or Equal Comparison
             *   @defgroup T_FGM_Vec3_LT_Comp Less Than Comparison
             *   @defgroup T_FGM_Vec3_LTE_Comp Less Than or Equal Comparison
             *   @defgroup T_FGM_Vec3_Equality Component-wise and Masked Equality
             *   @defgroup T_FGM_Vec3_Inequality Component-wise and Masked Inequality
             *   @defgroup T_FGM_Vec3_Init Initialization
             *   @defgroup T_FGM_Vec3_Magnitude Scalar Length(Magnitude)
             *   @defgroup T_FGM_Vec3_Normalize Vector Normalization
             *   @defgroup T_FGM_Vec3_Product Dot and Cross Product
             *   @defgroup T_FGM_Vec3_Proj Vector Projection
             *   @defgroup T_FGM_Vec3_Rej Vector Rejection
             *   @defgroup T_FGM_Vec3_String_Repr Formatted String Representation
             *   @defgroup T_FGM_Vec3_Type_Conv Conversion Constructor
             *   @defgroup T_FGM_Vec3_Inversion Unary Inversion(-)
             *   @defgroup T_FGM_Vec3_Utils Vector Utilities
             *   @defgroup T_FGM_Vec3_Swizzle Vector Swizzling
             * @}
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
             *   @defgroup T_FGM_Vec4_Product Dot Product
             *   @defgroup T_FGM_Vec4_Proj Vector Projection
             *   @defgroup T_FGM_Vec4_Rej Vector Rejection
             *   @defgroup T_FGM_Vec4_String_Repr Formatted String Representation
             *   @defgroup T_FGM_Vec4_Type_Conv Conversion Constructor
             *   @defgroup T_FGM_Vec4_Inversion Unary Inversion(-)
             *   @defgroup T_FGM_Vec4_Utils Vector Utilities
             *   @defgroup T_FGM_Vec4_Swizzle Vector Swizzling
             * @}
             */

        /** @} */ // End of VectorTests

    
        /**
         * @defgroup MatrixTests Matrices
         * @brief Test suite for vectors.
         * @ingroup MathTests
         * @{
         */
        
            /**
             * @defgroup FGM_Mat2x2_Tests 2x2 Matrix Test Suite
             * @brief Verification of 2x2 square matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FGM_Mat2x2_Access Component Access
             *   @defgroup T_FGM_Mat2x2_Mutation Component Mutation
             *   @defgroup T_FGM_Mat2x2_Alias Spatial Aliasing
             *   @defgroup T_FGM_Mat2x2_Const Matrix Constants
             *   @defgroup T_FGM_Mat2x2_Addition Addition
             *   @defgroup T_FGM_Mat2x2_Subtraction Subtraction
             *   @defgroup T_FGM_Mat2x2_Multiplication Scalar Multiplication
             *   @defgroup T_FGM_Mat2x2_Division Scalar Division
             *   @defgroup T_FGM_Mat2x2_Transpose Matrix Transpose
             *   @defgroup T_FGM_Mat2x2_Inverse Matrix Inverse
             *   @defgroup T_FGM_Mat2x2_Constant Matrix Constants
             *   @defgroup T_FGM_Mat2x2_Equality Equality
             *   @defgroup T_FGM_Mat2x2_Inequality  Inequality
             *   @defgroup T_FGM_Mat2x2_Init Initialization
             *   @defgroup T_FGM_Mat2x2_String_Repr Formatted String Representation
             *   @defgroup T_FGM_Mat2x2_Type_Conv Conversion Constructor
             *   @defgroup T_FGM_Mat2x2_Inversion Unary Inversion(-)
             *   @defgroup T_FGM_Mat2x2_Det Determinants
             *   @defgroup T_FGM_Mat2x2_Trace Trace
             *   @defgroup T_FGM_Mat2x2_Transforms Transformation Factories
             *   @defgroup T_FGM_Mat2x2_Utils Matrix Utilities
             * @}
             */

            /**
             * @defgroup FGM_Mat3x3_Tests 3x3 Matrix Test Suite
             * @brief Verification of 3x3 square matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FGM_Mat3x3_Access Component Access
             *   @defgroup T_FGM_Mat3x3_Mutation Component Mutation
             *   @defgroup T_FGM_Mat3x3_Alias Spatial Aliasing
             *   @defgroup T_FGM_Mat3x3_Const Matrix Constants
             *   @defgroup T_FGM_Mat3x3_Addition Addition
             *   @defgroup T_FGM_Mat3x3_Subtraction Subtraction
             *   @defgroup T_FGM_Mat3x3_Multiplication Scalar Multiplication
             *   @defgroup T_FGM_Mat3x3_Division Scalar Division
             *   @defgroup T_FGM_Mat3x3_Transpose Matrix Transpose
             *   @defgroup T_FGM_Mat3x3_Inverse Matrix Inverse
             *   @defgroup T_FGM_Mat3x3_Constant Matrix Constants
             *   @defgroup T_FGM_Mat3x3_Equality Equality
             *   @defgroup T_FGM_Mat3x3_Inequality  Inequality
             *   @defgroup T_FGM_Mat3x3_Init Initialization
             *   @defgroup T_FGM_Mat3x3_String_Repr Formatted String Representation
             *   @defgroup T_FGM_Mat3x3_Type_Conv Conversion Constructor
             *   @defgroup T_FGM_Mat3x3_Inversion Unary Inversion(-)
             *   @defgroup T_FGM_Mat3x3_Det Determinants
             *   @defgroup T_FGM_Mat3x3_Trace Trace
             *   @defgroup T_FGM_Mat3x3_Transforms Transformation Factories
             *   @defgroup T_FGM_Mat3x3_Utils Matrix Utilities
             * @}
             */


            /**
             * @defgroup FGM_Mat4x4_Tests 4x4 Matrix Test Suite
             * @brief Verification of 4x4 square matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FGM_Mat4x4_Access Component Access
             *   @defgroup T_FGM_Mat4x4_Mutation Component Mutation
             *   @defgroup T_FGM_Mat4x4_Alias Spatial Aliasing
             *   @defgroup T_FGM_Mat4x4_Const Matrix Constants
             *   @defgroup T_FGM_Mat4x4_Addition Addition
             *   @defgroup T_FGM_Mat4x4_Subtraction Subtraction
             *   @defgroup T_FGM_Mat4x4_Multiplication Scalar Multiplication
             *   @defgroup T_FGM_Mat4x4_Division Scalar Division
             *   @defgroup T_FGM_Mat4x4_Transpose Matrix Transpose
             *   @defgroup T_FGM_Mat4x4_Inverse Matrix Inverse
             *   @defgroup T_FGM_Mat4x4_Constant Matrix Constants
             *   @defgroup T_FGM_Mat4x4_Equality Equality
             *   @defgroup T_FGM_Mat4x4_Inequality  Inequality
             *   @defgroup T_FGM_Mat4x4_Init Initialization
             *   @defgroup T_FGM_Mat4x4_String_Repr Formatted String Representation
             *   @defgroup T_FGM_Mat4x4_Type_Conv Conversion Constructor
             *   @defgroup T_FGM_Mat4x4_Inversion Unary Inversion(-)
             *   @defgroup T_FGM_Mat4x4_Det Determinants
             *   @defgroup T_FGM_Mat4x4_Trace Trace
             *   @defgroup T_FGM_Mat4x4_Transforms Transformation Factories
             *   @defgroup T_FGM_Mat4x4_Utils Matrix Utilities
             * @}
             */
        /** @} */ // End of MatrixTests

        /**
         * @defgroup FGM_Common_Tests Common 
         * @brief Verify general function operations exposed by FGM library.
         * @ingroup MathTests
         * @{
         *   @defgroup T_Op_Status Operation Status
         *   @defgroup T_Wrappers Wrapper Utilities
         * @}
         */

    /** @} */ // End of MathTests

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