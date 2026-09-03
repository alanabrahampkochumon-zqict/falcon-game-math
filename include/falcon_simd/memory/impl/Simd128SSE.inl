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
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::setZero() noexcept

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
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::setOne() noexcept
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


    /**************************************
     *        BITWISE OPERATIONS          *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
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


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator&(const Simd128 other) const noexcept
    {
        if constexpr (std::is_same_v<DataType, double>)
        {
            return Simd128(_mm_and_pd(_register, other.naive()));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return Simd128(_mm_and_ps(_register, other.naive()));
        }
        else
        {
            return Simd128(_mm_and_si128(_register, other.naive()));
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator|(const Simd128 other) const noexcept
    {
        if constexpr (std::is_same_v<DataType, double>)
        {
            return Simd128(_mm_or_pd(_register, other.naive()));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return Simd128(_mm_or_ps(_register, other.naive()));
        }
        else
        {
            return Simd128(_mm_or_si128(_register, other.naive()));
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator^(const Simd128 other) const noexcept
    {
        if constexpr (std::is_same_v<DataType, double>)
        {
            return Simd128(_mm_xor_pd(_register, other.naive()));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return Simd128(_mm_xor_ps(_register, other.naive()));
        }
        else
        {
            return Simd128(_mm_xor_si128(_register, other.naive()));
        }
    }



    /**************************************
     *       EQUALITY OPERATIONS          *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator==(const Simd128 other) const noexcept
    {
        if constexpr (std::is_same_v<DataType, double>)
        {
            return Simd128(_mm_cmpeq_pd(_register, other.naive()));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return Simd128(_mm_cmpeq_ps(_register, other.naive()));
        }
        else
        {
            if constexpr (sizeof(DataType) == 8)
            {

                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
                {
                    // Equality operator for epi64 was introduced in SSE4.2
                    return Simd128(_mm_cmpeq_epi64(_register, other.naive()));
                }
                else
                {
                    // Compare high and low in one go
                    const auto eqHiLo = _mm_cmpeq_epi32(_register, other.naive());
                    // Shuffle the high bits into the lower portion
                    const auto eqHi =
                        _mm_shuffle_epi32(eqHiLo, _MM_SHUFFLE(3, 3, 1, 1)); // (A_Hi1, A_Hi1, A_Hi0, A_Hi0)
                    // And(&&) the result and extend it into lower higher lanes
                    const auto result = _mm_and_si128(eqHiLo, eqHi);
                    return Simd128(_mm_shuffle_epi32(result, _MM_SHUFFLE(2, 2, 0, 0)));
                }
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd128(_mm_cmpeq_epi32(_register, other.naive()));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd128(_mm_cmpeq_epi16(_register, other.naive()));
            }
            else // if constexpr(sizeof(DataType) == 1)
            {
                return Simd128(_mm_cmpeq_epi8(_register, other.naive()));
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator!=(const Simd128 other) const noexcept
    {
        if constexpr (std::is_same_v<DataType, double>)
        {
            return Simd128(_mm_cmpneq_pd(_register, other.naive()));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return Simd128(_mm_cmpneq_ps(_register, other.naive()));
        }
        else
        {
            // TODO: Update to use direction inversion after implementing ~
            // Integrals have no dedicated instruction in sse
            // We have no dedicated ~ operator, so we have use ~a AND 1
            // ~0 -> Inverts all the bits to 1
            const auto one   = _mm_set1_epi32(static_cast<int32_t>(~0));
            const auto eqReg = (*this == other).naive();
            return Simd128(_mm_andnot_si128(eqReg, one));
        }
    }



    /**************************************
     *       COMPARISON OPERATIONS        *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator>(const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_cmpgt_pd(_register, other.naive()));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_cmpgt_ps(_register, other.naive()));
        }
        else if constexpr (types::IsQWord<DataType>)
        {

            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                // Only SSE4.2 and above have _mm_cmpgt_epi64
                return Simd128(_mm_cmpgt_epi64(_register, other.naive()));
            }
            else
            {
                // Formula A_Hi > B_Hi | ((A_Hi == B_Hi) & A_Lo > B_Lo)
                // For signed numbers the upper lane comparisons are direct,
                // but for lower lanes we need we need to bias it, since the lower 31st bit is not a sign bit
                // which the epi32 comparison expected

                // Move the high bits into the lower lanes
                const auto aHi = _mm_shuffle_epi32(_register, _MM_SHUFFLE(3, 3, 1, 1)); // (A_Hi1, A_Hi1, A_Hi0, A_Hi0)
                const auto bHi =
                    _mm_shuffle_epi32(other.naive(), _MM_SHUFFLE(3, 3, 1, 1)); // (B_Hi1, B_Hi1, B_Hi0, B_Hi0)
                const auto gtHi = _mm_cmpgt_epi32(aHi, bHi);
                const auto eqHi = _mm_cmpeq_epi32(aHi, bHi);

                // Offset the lower portion
                const auto bias      = _mm_set1_epi32(static_cast<uint32_t>(0x80000000));
                const auto biasedALo = _mm_sub_epi32(_register, bias);
                const auto biasedBLo = _mm_sub_epi32(other.naive(), bias);
                const auto gtLo      = _mm_cmpgt_epi32(biasedALo, biasedBLo);
                const auto resLo     = _mm_or_si128(gtHi, _mm_and_si128(eqHi, gtLo));
                // Result is stored in low memory so we need to copy them to high memory
                return Simd128(_mm_shuffle_epi32(resLo, _MM_SHUFFLE(2, 2, 0, 0)));
            }
        }
        else if constexpr (types::IsDWord<DataType>)
        {
            return Simd128(_mm_cmpgt_epi32(_register, other.naive()));
        }
        else if constexpr (types::IsWord<DataType>)
        {
            return Simd128(_mm_cmpgt_epi16(_register, other.naive()));
        }
        else if constexpr (types::IsByte<DataType>)
        {
            return Simd128(_mm_cmpgt_epi8(_register, other.naive()));
        }
        // We don't instruction for comparing unsigned integers
        // so need bias the numbers by the minimum signed integer of respective size
        // and then used signed comparison
        // For signed the range for 8-bit number are -128 to 127
        // and for unsigned int, it's from 0 to 255, but by biasing by -128(0x80),
        // we have changed it to -128 to 127, and thus we can use signed comparison
        // For details see: https://fgiesen.wordpress.com/2016/04/03/sse-mind-the-gap/

        else if constexpr (types::IsUQWord<DataType>)
        {
            // For unsigned integers we need to bias both lower lanes and upper lanes, since both expect a signed
            // bit of for 31st bits
            const auto bias            = _mm_set1_epi32(static_cast<uint32_t>(0x80000000));
            const auto biasedRegisterA = _mm_sub_epi32(_register, bias);
            const auto biasedRegisterB = _mm_sub_epi32(other.naive(), bias);


            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                return Simd128(_mm_cmpgt_epi64(biasedRegisterA, biasedRegisterB));
            }
            else
            {
                // Formula A_Hi > B_Hi | ((A_Hi == B_Hi) & A_Lo > B_Lo)
                const auto gtLo = _mm_cmpgt_epi32(biasedRegisterA, biasedRegisterB); // A_Lo > B_Lo
                const auto aHi =
                    _mm_shuffle_epi32(biasedRegisterA, _MM_SHUFFLE(3, 3, 1, 1)); // (A_Hi1, A_Hi1, A_Hi0, A_Hi0)
                const auto bHi =
                    _mm_shuffle_epi32(biasedRegisterB, _MM_SHUFFLE(3, 3, 1, 1)); // (B_Hi1, B_Hi1, B_Hi0, B_Hi0)
                const auto gtHi = _mm_cmpgt_epi32(aHi, bHi);                     // A_Hi > B_Hi
                const auto eqHi = _mm_cmpeq_epi32(aHi, bHi);                     // (A_Hi == B_Hi)

                const auto resLo = _mm_or_si128(gtHi, _mm_and_si128(eqHi, gtLo));
                // Since we have used epi32 comparison, the lower lanes contain the comparison result
                // So, we need to copy the low bits to the high bits
                return Simd128(_mm_shuffle_epi32(resLo, _MM_SHUFFLE(2, 2, 0, 0)));
            }
        }
        else if constexpr (types::IsUDWord<DataType>)
        {
            const auto bias            = _mm_set1_epi32(static_cast<uint32_t>(0x80000000));
            const auto biasedRegisterA = _mm_sub_epi32(_register, bias);
            const auto biasedRegisterB = _mm_sub_epi32(other.naive(), bias);
            return Simd128(_mm_cmpgt_epi32(biasedRegisterA, biasedRegisterB));
        }
        else if constexpr (types::IsUWord<DataType>)
        {
            const auto bias            = _mm_set1_epi16(static_cast<uint16_t>(0x8000));
            const auto biasedRegisterA = _mm_sub_epi16(_register, bias);
            const auto biasedRegisterB = _mm_sub_epi16(other.naive(), bias);
            return Simd128(_mm_cmpgt_epi16(biasedRegisterA, biasedRegisterB));
        }
        else // if constexpr (types::IsUByte<DataType>)
        {
            const auto bias            = _mm_set1_epi8(static_cast<uint8_t>(0x80));
            const auto biasedRegisterA = _mm_sub_epi8(_register, bias);
            const auto biasedRegisterB = _mm_sub_epi8(other.naive(), bias);
            return Simd128(_mm_cmpgt_epi8(biasedRegisterA, biasedRegisterB));
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::operator>=(
        const Simd128 other) const noexcept
    {
        return ~(*this < other);
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator<(const Simd128 other) const noexcept
    { return other > *this; }

} // namespace falcon
