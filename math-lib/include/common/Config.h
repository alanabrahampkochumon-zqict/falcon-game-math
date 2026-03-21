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


#include <limits>

namespace fgm
{

    /**
     * @addtogroup FGM_Math_Config
     * @{
     */

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



        /***********************************!***
         *                                    *
         *            CUSTOM EPSILON          *
         *                                    *
         **************************************/

        /** @brief The smallest positive value such that 1.0 + EPSILON != 1.0 for 32-bit floats. */
        static constexpr double FLOAT_EPSILON = 1e-5;

        /** @brief The smallest positive value such that 1.0 + EPSILON != 1.0 for 64-bit floats. */
        static constexpr double DOUBLE_EPSILON = 1e-12;

        /** @brief Positive infinity for single-precision floats. */
        static constexpr float INFINITY_F = std::numeric_limits<float>::infinity();

        /** @brief Positive infinity for double-precision floats. */
        static constexpr double INFINITY_D = std::numeric_limits<double>::infinity();

        /** @brief Quiet Not-a-Number for single-precision floats. */
        static constexpr float NaN = std::numeric_limits<float>::quiet_NaN();

        /** @brief Quiet Not-a-Number for double-precision floats. */
        static constexpr double NaN_D = std::numeric_limits<double>::quiet_NaN();
    };

    /** @} */

} // namespace fgm
