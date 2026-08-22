#pragma once
/**
 * @file DoxygenGroups.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 18, 2026
 *
 * @brief Doxygen groups for organizing FGM SIMD test harness.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


// clang-format off
/**
 * @defgroup SIMD_Test_Suite Falcon SIMD Test Suite
 * @brief Falcon SIMD Library Test Suite.
 * @{
 */

    /**
     * @defgroup T_SIMD_Reg SIMD Register Types
     * @brief Verifies the wrapper for x86/ARM(Not supported yet) registers.
     * @ingroup T_SIMD_Reg.
     */

    /**
     * @defgroup T_SIMD_Utils Utility Tests
     * @brief Validates logic of all SIMD utility functions.
     * @ingroup T_SIMD_Reg.
     */

    /**
     * @defgroup T_SIMD128 Simd 128 Tests
     * @brief Verifies functions provided by Simd128
     * @ingroup T_SIMD_Reg.
*
         * @{
         *   @defgroup T_SIMD128_Arithmetic Arithmetic Tests
         *   @defgroup T_SIMD128_ConvCtor Conversion Constructors Tests
         *   @defgroup T_SIMD128_Get_Set Getters/Setters Tests
         *   @defgroup T_SIMD128_Load_Store Load/Store Tests
         * @}
        */

    /** @} */ // End of T_SIMD128


/** @} */ // End of SIMD_Test_Suite

// clang-format on
