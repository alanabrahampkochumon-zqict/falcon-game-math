#pragma once
/**
 * @file Utils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: May 28, 2026
 *
 * @brief Implementation for helper and utility functions defined in Utils.h.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cmath>


namespace fgm::utils
{

    template <Arithmetic T, Arithmetic U>
    constexpr PromotedValue_t<T, U> diffAbs(T lhs, U rhs) noexcept
    {
        // Only one side of the expression is evaluated to a non-zero number.
        // So, if either side of + underflows, it will be canceled out by the boolean expression.
        return PromotedValue_t<T, U>((lhs - rhs) * (lhs >= rhs) + (rhs - lhs) * (lhs < rhs));
    }


    //template <Arithmetic T>
    //constexpr Magnitude<T> sqrt(T num, double epsilon) noexcept
    //{
    //    if (std::is_constant_evaluated())
    //    {
    //        // Compile time evaluation
    //        using R = Magnitude<T>;

    //        const R fpNum = static_cast<R>(num);
    //        R guess    = fpNum / 2; // Initial guess num / 2.

    //        while (guess * guess - fpNum > epsilon)
    //        {
    //            guess = guess - ((guess * guess - num) / (2 * guess));
    //        }
    //        return guess;
    //    }
    //    else
    //    {
    //        return static_cast<Magnitude<T>>(std::sqrt(num));
    //    }
    //}

} // namespace fgm::utils
