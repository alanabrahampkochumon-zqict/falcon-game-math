#pragma once
/**
 * @file Simd256X86Math.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 29, 2026
 *
 * @brief Implementation of function declared in Simd256X86Math.h.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Simd128X86Math.h"

namespace flcn
{
    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_256_SSE<DataType, Lane> min(_REG_256_SSE<DataType, Lane> a,
                                                             _REG_256_SSE<DataType, Lane> b) noexcept
    {
        return _REG_256_SSE<DataType, Lane>(min(a._lower, b._lower), min(a._upper, b._upper));
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_256_SSE<DataType, Lane> max(_REG_256_SSE<DataType, Lane> a,
                                                             _REG_256_SSE<DataType, Lane> b) noexcept
    {
        return _REG_256_SSE<DataType, Lane>(max(a._lower, b._lower), max(a._upper, b._upper));
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_256_SSE<DataType, Lane> abs(_REG_256_SSE<DataType, Lane> reg) noexcept
    { return reg.abs(); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_256_SSE<DataType, Lane> sqrt(_REG_256_SSE<DataType, Lane> reg) noexcept
    { return reg.sqrt(); }
} // namespace flcn
