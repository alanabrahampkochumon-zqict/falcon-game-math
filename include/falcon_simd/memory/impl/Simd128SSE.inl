#pragma once
#include "Simd128SSE.h"
/**
 * @file Simd128SSE.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 03, 2026
 *
 * @brief Implementation of templated functions declared in Simd128SSE.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace falcon
{

    /**************************************
     *         SETTERS/GETTERS            *
     **************************************/

    template <typename DataType, size_t Lane>
    constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::setZero() noexcept

    {
        if constexpr (types::IsFP64<DataType>)
        {
            _register = _mm_setzero_pd();
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            _register = _mm_setzero_ps();
        }
        else
        {
            _register = _mm_setzero_si128();
        }
    }


    template <typename DataType, size_t Lane>
    constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::setOne() noexcept
    {
        // Since we can't direction negate zero for floating point numbers we need to negate an appropriately sized
        // 0 and bit cast them to respective floating point types.
        if constexpr (types::IsFP64<DataType>)
        {
            constexpr auto ONE = std::bit_cast<double>(~static_cast<uint64_t>(0));
            _register          = _mm_set1_pd(ONE);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            constexpr auto ONE = std::bit_cast<float>(~static_cast<uint32_t>(0));
            _register          = _mm_set1_ps(ONE);
        }
        else
        {
            constexpr auto ONE = ~static_cast<int32_t>(0);
            _register          = _mm_set1_epi32(ONE);
        }
    }


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                      Lane>::operator~() const noexcept
    {
        // There is no direct invert instruction so we have to use and_not = ~a ^ b and set b = 1(~0)
        Simd128 oneReg{};
        oneReg.setOne();
        if constexpr (std::is_same_v<DataType, double>)
        {
            return Simd128(_mm_andnot_pd(_register, oneReg.naive()));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return Simd128(_mm_andnot_ps(_register, oneReg.naive()));
        }
        else
        {
            return Simd128(_mm_andnot_ps(_register, oneReg.naive()));
        }
    }
} // namespace falcon
