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
#include <string_view>



/**
 * @addtogroup FGM_Messages
 * @{
 */

namespace fgm::messages::assertion
{} // namespace fgm::messages::assertion


namespace fgm::messages
{
    namespace assertion
    {              
        /** @brief Assertion message thrown when a matrix division by zero occurs. */
        inline constexpr std::string_view MAT_DIV_BY_ZERO = "Matrix division by zero";

    } // namespace assertion


    /** @brief Message mapping for @ref OperationStatus status code. */
    namespace opstatus
    {
        inline constexpr std::string_view OPERATION_SUCCESS = "Operation success!";
        inline constexpr std::string_view OPERATION_DIV_BY_ZERO = "Failure: Division by Zero";
        inline constexpr std::string_view OPERATION_NAN_OPERAND = "Failure: NaN operand encountered";
        inline constexpr std::string_view OPERATION_UNKNOWN_FAILURE = "Failure: Unknown error";

    } // namespace opstatus

} // namespace fgm::messages

/** @} */
