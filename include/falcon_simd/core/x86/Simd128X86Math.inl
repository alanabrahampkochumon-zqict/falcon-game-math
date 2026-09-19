#pragma once
/**
 * @file Simd128X86Math.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 18, 2026
 *
 * @brief Implementation of function declared in Simd128X86Math.h.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


namespace falcon
{
    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_128_SSE<DataType, Lane> min(_REG_128_SSE<DataType, Lane> a,
                                                             _REG_128_SSE<DataType, Lane> b) noexcept
    {
        // min function is not available for all data types and for some,
        // it was introduced with SSE4.1
        // As a workaround we use a > b ? b : a
        // with blend to get the correct min values.
        using Reg = _REG_128_SSE<DataType, Lane>;
        if constexpr (types::IsFP64<DataType>)
        {
            return Reg(_mm_min_pd(*a, *b));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Reg(_mm_min_ps(*a, *b));
        }
        // Types natively supported by SSE or SSE2(EPI16 and EPU8)
        // This allows us to remove redundant if CURRENT_SIMD_BACKEND conditionals in majority of the code.
        else if constexpr (types::IsWord<DataType>)
        {
            return Reg(_mm_min_epi16(*a, *b));
        }
        else if constexpr (types::IsUByte<DataType>)
        {
            return Reg(_mm_min_epu8(*a, *b));
        }
        else if constexpr (types::IsQWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            return Reg(_mm_min_epi64(*a, *b)); // AVX512F + VL
        }
        else if constexpr (types::IsUQWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            return Reg(_mm_min_epu64(*a, *b)); // AVX512F + VL
        }
        else if constexpr (types::IsDWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_min_epi32(*a, *b));
        }
        else if constexpr (types::IsByte<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_min_epi8(*a, *b));
        } // Unsigned types
        else if constexpr (types::IsUDWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_min_epu32(*a, *b));
        }
        else if constexpr (types::IsUWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_min_epu16(*a, *b));
        }
        else // if constexpr(CURRENT_SIMD_BACKEND <= SimdBackend::ARCH_SSE2)
        {
            auto mask = a > b;
            return a.blend(b, mask);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_128_SSE<DataType, Lane> max(_REG_128_SSE<DataType, Lane> a,
                                                             _REG_128_SSE<DataType, Lane> b) noexcept
    {
        // min function is not available for all data types and for some,
        // it was introduced with SSE4.1
        // As a workaround we use a > b ? a : b
        // with blend to get the correct min values.
        using Reg = _REG_128_SSE<DataType, Lane>;
        if constexpr (types::IsFP64<DataType>)
        {
            return Reg(_mm_max_pd(*a, *b));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Reg(_mm_max_ps(*a, *b));
        }
        // Types natively supported by SSE or SSE2(EPI16 and EPU8)
        // This allows us to remove redundant if CURRENT_SIMD_BACKEND conditionals in majority of the code.
        else if constexpr (types::IsWord<DataType>)
        {
            return Reg(_mm_max_epi16(*a, *b));
        }
        else if constexpr (types::IsUByte<DataType>)
        {
            return Reg(_mm_max_epu8(*a, *b));
        }
        else if constexpr (types::IsQWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            return Reg(_mm_max_epi64(*a, *b)); // AVX512F + VL
        }
        else if constexpr (types::IsUQWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            return Reg(_mm_max_epu64(*a, *b)); // AVX512F + VL
        }
        else if constexpr (types::IsDWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_max_epi32(*a, *b));
        }
        else if constexpr (types::IsByte<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_max_epi8(*a, *b));
        } // Unsigned types
        else if constexpr (types::IsUDWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_max_epu32(*a, *b));
        }
        else if constexpr (types::IsUWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_max_epu16(*a, *b));
        }
        else // if constexpr(CURRENT_SIMD_BACKEND <= SimdBackend::ARCH_SSE2)
        {
            // a > b ? a : b
            auto mask = a > b;
            return b.blend(a, mask);
        }
    }


    template <typename DataType, size_t Lane>
    constexpr _REG_128_SSE<DataType, Lane> abs(_REG_128_SSE<DataType, Lane> reg) noexcept
    {
        // There is no intrinsic for floating point abs so we have to use a sign flag mask and use AND
        // 1 101 1010
        // 0 111 1111 &
        // 0 101 1010

        // For integral we can use the trick mention in Hackers Delight[2-4]
        // y = x a>> (sizeof(DataType) * 8 - 1) (for int32 its y = x >> 31)
        // (x xor y) - y
        // -7  1001
        // t = 1111 xor
        //   = 0110
        //   = 1111 -
        //   = 0111 (7)
        using Reg = _REG_128_SSE<DataType, Lane>;
        if constexpr (std::is_unsigned_v<DataType>)
        {
            return Reg(*reg);
        }
        else if constexpr (types::IsFP64<DataType>)
        {
            // We can take the abs of a register by using a flag mask and ANDing it with our register.
            const auto flagMask    = _mm_set1_epi64x(0x7FFFFFFFFFFFFFFF); // 0b0111..1111
            const auto integralReg = _mm_castpd_si128(*reg);
            const auto absReg      = _mm_and_si128(integralReg, flagMask);
            return Reg(_mm_castsi128_pd(absReg));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            // We can take the abs of a register by using a flag mask and ANDing it with our register.
            const auto flagMask    = _mm_set1_epi32(0x7FFFFFFF); // 0b0111..1111
            const auto integralReg = _mm_castps_si128(*reg);
            const auto absReg      = _mm_and_si128(integralReg, flagMask);
            return Reg(_mm_castsi128_ps(absReg));
        }
        else if constexpr (types::IsQWord<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
            {
                return Simd128(_mm_abs_epi64(*reg));
            }
            else
            {
                // t = x a>> 63; abs = (x xor t) - t;
                const auto t      = *reg.template shiftRightArithmetic<63>();
                const auto xorReg = _mm_xor_si128(*reg, t);
                return Reg(_mm_sub_epi64(xorReg, t));
            }
        }
        else if constexpr (types::IsDWord<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                return Reg(_mm_abs_epi32(*reg));
            }
            else
            {
                // t = x a>> 31; abs = (x xor t) - t;
                const auto t      = *reg.template shiftRightArithmetic<31>();
                const auto xorReg = _mm_xor_si128(*reg, t);
                return Reg(_mm_sub_epi32(xorReg, t));
            }
        }
        else if constexpr (types::IsWord<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                return Reg(_mm_abs_epi16(*reg));
            }
            else
            {
                // t = x a>> 15; abs = (x xor t) - t;
                const auto t      = *reg.template shiftRightArithmetic<15>();
                const auto xorReg = _mm_xor_si128(*reg, t);
                return Reg(_mm_sub_epi16(xorReg, t));
            }
        }
        else // if constexpr (types::IsByte<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                return Reg(_mm_abs_epi8(*reg));
            }
            else
            {
                // t = x a>> 7; abs = (x xor t) - t;
                const auto t      = *reg.template shiftRightArithmetic<7>();
                const auto xorReg = _mm_xor_si128(*reg, t);
                return Reg(_mm_sub_epi8(xorReg, t));
            }
        }
    }
} // namespace falcon
