#pragma once
/**
 * @file Constants.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 21, 2026
 *
 * @brief Constant definitions of FGM.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <limits>




/**
 * @addtogroup FGM_Math_Constants
 * @{
 */

namespace fgm
{
    inline struct Constants
    {
        /** @brief Positive infinity for single-precision floats. */
        static constexpr float INFINITY_F = std::numeric_limits<float>::infinity();

        /** @brief Positive infinity for double-precision floats. */
        static constexpr double INFINITY_D = std::numeric_limits<double>::infinity();

        /** @brief Quiet Not-a-Number for single-precision floats. */
        static constexpr float NaN = std::numeric_limits<float>::quiet_NaN();

        /** @brief Quiet Not-a-Number for double-precision floats. */
        static constexpr double NaN_D = std::numeric_limits<double>::quiet_NaN();
    } Constants;
}

/**
 * @}
 */