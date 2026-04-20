#pragma once
/**
 * @file Wrappers.h
 * @author Alan Abraham P Kochumon
 * @date Created on: April 20, 2026
 *
 * @brief Wrapper for C++ `std` functions, to enable constexpr evaluation in pre-C++23.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MathTraits.h"



namespace fgm
{

    /**
     * @addtogroup FGM_Wrappers
     * @{
     */

    /**
     * @brief Compute the absolute value of an integral or floating-point value.
     *        Wrapper around the `std::abs`/`std::fabs` function, to enable constexpr evaluation in pre-C++23.
     *
     * @tparam T The numeric type of the value.
     *
     * @param num The number to take the absolute value of.
     *
     * @return Return the absolute value of @p value.
     */
    template <SignedStrictArithmetic T>
    constexpr T abs(T num) noexcept;

    /** @} */

}


#include "Wrappers.tpp"