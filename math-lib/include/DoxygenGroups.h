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
         */

            /**
             * @defgroup FGM_Vec2 2D Vectors
             * @brief 2-dimensional Euclidean vectors.
             * @ingroup FGM_Vectors
             * @{
             *   @defgroup FGM_Vec2_Members Class Members
             *   @defgroup FGM_Vec2_Init Constructors
             *   @defgroup FGM_Vec2_Access Accessors
             *   @defgroup FGM_Vec2_Arithmetic Arithmetic Operations
             *   @defgroup FGM_Vec2_Bitwise Boolean Bitwise Operations
             *   @defgroup FGM_Vec2_Equality Equality
             *   @defgroup FGM_Vec2_Comparison Comparisons
             *   @defgroup FGM_Vec2_Product Geometric Products
             *   @defgroup FGM_Vec2_Mag Scalar Magnitude and Normalization
             *   @defgroup FGM_Vec2_Proj Vector Projection and Rejection
             *   @defgroup FGM_Vec2_Alias Spatial Alias
             *   @defgroup FGM_Vec2_Log String Representation
             *   @defgroup FGM_Vec2_Const Vector Constants
             *   @defgroup FGM_Vec2_Utils Vector Utilities
             *   @defgroup FGM_Vec2_Swizzle Vector Swizzling
             * @}
             */

            /**
             * @defgroup FGM_Vec3 3D Vectors
             * @brief 3-dimensional Euclidean vectors.
             * @ingroup FGM_Vectors
             * @{
             *   @defgroup FGM_Vec3_Members Class Members
             *   @defgroup FGM_Vec3_Init Constructors
             *   @defgroup FGM_Vec3_Access Accessors
             *   @defgroup FGM_Vec3_Arithmetic Arithmetic Operations
             *   @defgroup FGM_Vec3_Bitwise Boolean Bitwise Operations
             *   @defgroup FGM_Vec3_Equality Equality
             *   @defgroup FGM_Vec3_Comparison Comparisons
             *   @defgroup FGM_Vec3_Product Geometric Products
             *   @defgroup FGM_Vec3_Mag Scalar Magnitude and Normalization
             *   @defgroup FGM_Vec3_Proj Vector Projection and Rejection
             *   @defgroup FGM_Vec3_Alias Spatial Alias
             *   @defgroup FGM_Vec3_Log String Representation
             *   @defgroup FGM_Vec3_Const Vector Constants
             *   @defgroup FGM_Vec3_Utils Vector Utilities
             *   @defgroup FGM_Vec3_Swizzle Vector Swizzling
             * @}
             */

            /**
             * @defgroup FGM_Vec4 4D Vectors
             * @brief 4-dimensional Euclidean vectors.
             * @ingroup FGM_Vectors
             * @{
             *   @defgroup FGM_Vec4_Members Class Members
             *   @defgroup FGM_Vec4_Init Constructors
             *   @defgroup FGM_Vec4_Access Accessors
             *   @defgroup FGM_Vec4_Arithmetic Arithmetic Operations
             *   @defgroup FGM_Vec4_Bitwise Boolean Bitwise Operations
             *   @defgroup FGM_Vec4_Equality Equality
             *   @defgroup FGM_Vec4_Comparison Comparisons
             *   @defgroup FGM_Vec4_Product Geometric Products
             *   @defgroup FGM_Vec4_Mag Scalar Magnitude and Normalization
             *   @defgroup FGM_Vec4_Proj Vector Projection and Rejection
             *   @defgroup FGM_Vec4_Alias Spatial Alias
             *   @defgroup FGM_Vec4_Log String Representation
             *   @defgroup FGM_Vec4_Const Vector Constants
             *   @defgroup FGM_Vec4_Utils Vector Utilities
             *   @defgroup FGM_Vec4_Swizzle Vector Swizzling
             * @}
             */

        /** @} */ // FGM_Vectors
        
        /**
         * @defgroup FGM_Matrices Matrices
         * @brief MxN-dimensional Matrix implementations.
         * @ingroup FGM_Math
         * @{
         */
            
            /**
             * @defgroup FGM_Mat2x2 2x2 Square Matrix
             * @brief 2x2 Square Matrix.
             * @ingroup FGM_Matrices
             * @{
             *   @defgroup FGM_Mat2x2_Members Class Members
             *   @defgroup FGM_Mat2x2_Init Constructors
             *   @defgroup FGM_Mat2x2_Access Accessors
             *   @defgroup FGM_Mat2x2_Arithmetic Arithmetic Operations
             *   @defgroup FGM_Mat2x2_Algebra Matrix Algebra
             *   @defgroup FGM_Mat2x2_Equality Equality
             *   @defgroup FGM_Mat2x2_Product Geometric Products
             *   @defgroup FGM_Mat2x2_Log String Representation
             *   @defgroup FGM_Mat2x2_Const Matrix Constants
             *   @defgroup FGM_Mat2x2_Utils Matrix Utilities
             *   @defgroup FGM_Mat2x2_Transforms Matrix Transformation Factories
             * @}
             */

            
            /**
             * @defgroup FGM_Mat3x3 3x3 Square Matrix
             * @brief 3x3 Square Matrix.
             * @ingroup FGM_Matrices
             * @{
             *   @defgroup FGM_Mat3x3_Members Class Members
             *   @defgroup FGM_Mat3x3_Init Constructors
             *   @defgroup FGM_Mat3x3_Access Accessors
             *   @defgroup FGM_Mat3x3_Arithmetic Arithmetic Operations
             *   @defgroup FGM_Mat3x3_Algebra Matrix Algebra
             *   @defgroup FGM_Mat3x3_Equality Equality
             *   @defgroup FGM_Mat3x3_Product Geometric Products
             *   @defgroup FGM_Mat3x3_Log String Representation
             *   @defgroup FGM_Mat3x3_Const Matrix Constants
             *   @defgroup FGM_Mat3x3_Utils Matrix Utilities
             *   @defgroup FGM_Mat3x3_Transforms Matrix Transformation Factories
             * @}
             */
        
        /** @} */ // FGM_Matrices

    /** @} */ // End of FGM_Core

    /**
     * @defgroup FGM_Concepts Concepts
     * @brief Fundamental mathematical constraints.
     * @ingroup FGM_Math
     */
    
    /**
     * @defgroup FGM_Math_Config Library Configuration
     * @brief Configurations that dictate certain library behaviors.
     * @ingroup FGM_Math
     */

    /**
     * @defgroup FGM_Math_Constants Library Constants
     * @brief Constants defined in FGM.
     * @ingroup FGM_Math
     */

    /**
     * @defgroup FGM_Math_Common Library Utilities
     * @brief Common utilities used by FGM.
     * @ingroup FGM_Math
     */

    /**
     * @defgroup FGM_Wrappers Wrapper Functions
     * @brief Wrapper for `std` functions to enable compile time evaluation in pre-C++23/26.
     * @ingroup FGM_Math
     */

    /**
     * @defgroup FGM_Macro Preprocessor Macros
     * @brief Preprocessor macro for assertions and compiler intrinsic debug breaks.
     * @ingroup FGM_Math
     */

/** @} */ // End of FGM_Math

// clang-format on