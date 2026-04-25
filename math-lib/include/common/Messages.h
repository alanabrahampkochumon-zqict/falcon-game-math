#pragma once
/**
 * @file Messages.h
 * @author Alan Abraham P Kochumon
 * @date Created on: April 25, 2026
 *
 * @brief Central repository for all library string resources like assertion messages.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <string>



/**
 * @addtogroup FGM_Messages
 * @{
 */

namespace fgm::messages::assertion
{
    /** @brief Assertion message thrown when a matrix division by zero occurs. */
    inline constexpr std::string MAT_DIV_BY_ZERO = "Matrix division by zero";
} // namespace fgm::messages::assertion

/** @} */
