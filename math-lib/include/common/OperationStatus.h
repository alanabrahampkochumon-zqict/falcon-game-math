#pragma once
/**
 * @file OperationStatus.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 28, 2026
 *
 * @brief Operation status flags in use by "try..." variants of math functions that can trigger a hardware exception.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstdint>



namespace fgm
{

    /**
     * @addtogroup FGM_Math_Common
     * @{
     */

    /** @brief Operation status flags used for flagging exceptions and unexpected behavior. */
    enum class OperationStatus : uint8_t
    {
        SUCCESS = 0,    //< Flag indicating operation success.
        DIVISIONBYZERO, //< Flag indicating that division by zero has occured.
        NANOPERAND      //< Flag indicating that one or more operands are NaN.
    };


    /**
     * @brief Translates @ref OperationStatus into a verbose message.
     *
     * @param[in] status The status to convert.
     *
     * @return The status message.
     */
    constexpr const char* getStatusMessage(const OperationStatus status) noexcept
    {
        switch (status)
        {
            case OperationStatus::SUCCESS:
                return "Operation success!";
            case OperationStatus::DIVISIONBYZERO:
                return "Failure: Division by Zero";
            case OperationStatus::NANOPERAND:
                return "Failure: NaN operand encountered";
            default:
                return "Failure: Unknown error";
        }
    }

    /** @} */

} // namespace fgm