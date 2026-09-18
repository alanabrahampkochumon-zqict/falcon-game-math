#pragma once
/**
 * @file Simd128X86Math.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 18, 2026
 *
 * @brief Binary non-arithmetic math operations including min, max, etc.
 *
 * @note This header should not be directly included. Include SIMD128 will include the correct header file.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


namespace falcon
{
    template <typename DataType, size_t Lane>
    using _REG_128_SSE = Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>;

    /**
     * Get the minimum values from both the registers.
     *
     * @tparam DataType The data type of the Simd128 register.
     * @tparam Lane     The number of lanes of the Simd128 register.
     *
     * @param a The first register.
     * @param b The second register.
     *
     * @return A Simd128 register with minimum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr _REG_128_SSE<DataType, Lane> min(_REG_128_SSE<DataType, Lane> a,
                                                                      _REG_128_SSE<DataType, Lane> b) noexcept;
} // namespace falcon

#include "Simd128X86Math.inl"
