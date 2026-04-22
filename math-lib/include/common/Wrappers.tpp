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


#include <bit>
#include <cmath>
#include <cstdlib>
#include <limits>


namespace fgm
{
    template <SignedStrictArithmetic T>
    constexpr T abs(T num) noexcept
    {
        if (std::is_constant_evaluated())
        {
            if constexpr (std::is_floating_point_v<T>)
            {
// In MSVC, taking abs with NaN returns wrong results, so an explicit check is required.
#ifdef _MSC_VER
                if constexpr (isnan(num))
                    return num;
#endif
                if constexpr (sizeof(T) == 4)
                {
                    auto bits = std::bit_cast<std::uint32_t>(num);
                    return std::bit_cast<T>(bits & 0x7FFFFFFFu);
                }
                else if (sizeof(T) == 8)
                {
                    auto bits = std::bit_cast<std::uint64_t>(num);
                    return std::bit_cast<T>(bits & 0x7FFFFFFFFFFFFFFFull);
                }
                else
                    return num < T(0) ? -num : num;
            }
            else
                return num < T(0) ? -num : num;
        }
        else
        {
            if constexpr (std::is_floating_point_v<T>)
                return std::fabs(num);
            else
                return std::abs(num);
        }
    }

    inline constexpr auto NAN_DOUBLE_WORD = 0x7FC00000;
    inline constexpr auto NAN_QUAD_WORD = 0x7FF8000000000000;
    template <Arithmetic T>
    constexpr bool isnan(T num) noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            if (std::is_constant_evaluated())
            {
                // noinspection CppEqualOperandsInBinaryExpression
                return num != num;
            }
            return std::isnan(num);
        }
        else
            return false;
    }


    template <Arithmetic T>
    constexpr bool isinf(T num) noexcept
    {
        if (std::is_constant_evaluated())
        {
            if (std::numeric_limits<T>::has_infinity)
                return std::numeric_limits<T>::infinity() == num || -std::numeric_limits<T>::infinity() == num;
            return false;
        }
        return std::isinf(num);
    }
} // namespace fgm
