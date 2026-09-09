#pragma once
/**
 * @file TypeTraits.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 09, 2026
 *
 * @brief Defines type traits and concepts for SIMD.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <type_traits>

namespace falcon
{


    /**
     * Concept for constraining mixed type usage without explict casting.
     *
     * @tparam From The incoming numeric type.
     * @tparam To   The expected numeric type.
     */
    template <typename From, typename To>
    concept SimdSafeConvertible = requires {
        requires std::is_convertible_v<From, To>;
        // Floating points cannot be converted to integrals due to precision loss.
        requires !(std::is_floating_point_v<From> && std::is_integral_v<To>);
        // The types must guarantee to fit.
        requires sizeof(From) <= sizeof(To);
    };

} // namespace falcon
