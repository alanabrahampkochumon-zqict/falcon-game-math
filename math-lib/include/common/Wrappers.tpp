#pragma once
/**
 * @file Wrappers.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 20, 2026
 *
 * @brief Implementation of wrapper functions defined in Wrapper.h.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstdlib>



namespace fgm
{
    template <SignedStrictArithmetic T>
    constexpr T abs(T num) noexcept
    {
        if (std::is_constant_evaluated())
            return num < T(0) ? -num : num;
        if constexpr (std::is_floating_point_v<T>)
            return std::fabs(num);
        else
            return std::abs(num);
    }


    template <std::floating_point T>
    constexpr bool isnan(T num) noexcept {}
}
