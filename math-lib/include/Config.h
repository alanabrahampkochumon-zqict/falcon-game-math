#pragma once
/**
 * @file Config.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 16, 2026
 *
 * @brief Global configuration for FGM library.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


namespace fgm
{
    struct Config
    {
        /** @brief Standard precision for logging and debugging. */
        static constexpr unsigned int LOG_PRECISION = 4;

        /** @brief Defines the maximum reliable decimal precision for 32-bit floating point types. */
        static constexpr unsigned int FLOAT_PRECISION = 5;

        /** @brief Defines the maximum reliable decimal precision for 64-bit floating point types. */
        static constexpr unsigned int DOUBLE_PRECISION = 15;

        /** 
         * @brief Toggles between standard logging precision and type-specific maximum precision.
         */
        static inline bool useFullPrecision = false;
    };
}

