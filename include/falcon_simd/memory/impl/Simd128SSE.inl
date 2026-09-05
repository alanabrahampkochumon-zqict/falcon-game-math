#pragma once
/**
 * @file Simd128SSE.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 03, 2026
 *
 * @brief Implementation of templated functions declared in Simd128SSE.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include <emmintrin.h>
#include <format>

namespace falcon
{

    /**************************************
     *         SETTERS/GETTERS            *
     **************************************/

    template <typename DataType, size_t Lane>
    template <typename... Args>
        requires(sizeof...(Args) <= Lane) && (std::same_as<Args, DataType> && ...)
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                                     Lane>::set(Args... args)

    {
        constexpr auto MaxLanes = 128 / sizeof(DataType);
        // By packing to a compile time array and adding values
        alignas(16) std::array<DataType, MaxLanes> data{ args... };
        loadAligned(data.data());

        return *this;
    }


    template <typename DataType, size_t Lane>
    template <typename DataType2>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::Simd128(
        const Simd128<SimdBackend::ARCH_SSE2, DataType2, Lane>& other)
    {
        if constexpr (types::IsFP64<DataType2>)
        {
            if constexpr (types::IsFP64<DataType>)
            {
                _register = other.naive();
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _register = _mm_cvtpd_ps(other.naive());
            }
            else
            {
                _register = _mm_cvtpd_epi32(other.naive());
            }
        }
        else if constexpr (types::IsFP32<DataType2>)
        {
            if constexpr (types::IsFP64<DataType>)
            {
                _register = _mm_cvtps_pd(other.naive());
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _register = other.naive();
            }
            else
            {
                _register = _mm_cvtps_epi32(other.naive());
            }
        }
        else
        {
            if constexpr (types::IsFP64<DataType>)
            {
                _register = _mm_cvtepi32_pd(other.naive());
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _register = _mm_cvtepi32_ps(other.naive());
            }
            else
            {
                _register = other.naive();
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::loadAligned(DataType* data) noexcept
    {
        // We are using sizes for loading integers since we are storing both signed and unsigned types into the
        // register as bits, with packing.
        if constexpr (types::IsFP64<DataType>)
        {
            _register = _mm_load_pd(data);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (Lane == 2)
            {
                _register = _mm_loadl_pi(_mm_setzero_ps(), reinterpret_cast<const __m64*>(data));
            }
            else
            {
                _register = _mm_load_ps(data);
            }
        }
        else
        {

            if constexpr (sizeof(DataType) * Lane == 16)
            {
                _register = _mm_load_si128(reinterpret_cast<const __m128i*>(data));
            }
            else if constexpr (sizeof(DataType) * Lane == 8)
            {
                _register = _mm_loadu_si64(data);
            }
            else if constexpr (sizeof(DataType) * Lane == 4)
            {
                _register = _mm_loadu_si32(data);
            }
            else // Lane * Size = 2
            {
                _register = _mm_loadu_si16(data);
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::load(DataType* data) noexcept
    {
        // We are using sizes for loading integers since we are storing both signed and unsigned types into the
        // register as bits, with packing.
        if constexpr (types::IsFP64<DataType>)
        {
            _register = _mm_loadu_pd(data);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (Lane == 2)
            {
                _register = _mm_loadl_pi(_mm_setzero_ps(), reinterpret_cast<const __m64*>(data));
            }
            else
            {
                _register = _mm_loadu_ps(data);
            }
        }
        else
        {

            if constexpr (sizeof(DataType) * Lane == 16)
            {
                _register = _mm_loadu_si128(reinterpret_cast<const __m128i*>(data));
            }
            else if constexpr (sizeof(DataType) * Lane == 8)
            {
                _register = _mm_loadu_si64(data);
            }
            else if constexpr (sizeof(DataType) * Lane == 4)
            {
                _register = _mm_loadu_si32(data);
            }
            else // Lane * Size = 2
            {
                _register = _mm_loadu_si16(data);
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::broadcast(DataType value) noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            _register = _mm_set1_pd(value);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            _register = _mm_set1_ps(value);
        }
        else
        {
            if constexpr (sizeof(DataType) == 8)
            {
                _register = _mm_set1_epi64x(value);
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                _register = _mm_set1_epi32(value);
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                _register = _mm_set1_epi16(value);
            }
            else if constexpr (sizeof(DataType) == 1)
            {
                _register = _mm_set1_epi8(value);
            }
        }
    }


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


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::store(
        DataType* pBuffer) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            _mm_storeu_pd(pBuffer, _register);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (Lane == 2)
            {
                _mm_storel_pi(reinterpret_cast<__m64*>(pBuffer), _register);
            }
            else
            {
                _mm_storeu_ps(pBuffer, _register);
            }
        }
        else
        {
            if constexpr (sizeof(DataType) * Lane == 16)
            {
                _mm_storeu_si128(reinterpret_cast<__m128i*>(pBuffer), _register);
            }
            else if constexpr (sizeof(DataType) * Lane == 8)
            {
                _mm_storeu_si64(pBuffer, _register);
            }
            else if constexpr (sizeof(DataType) * Lane == 4)
            {
                _mm_storeu_si32(pBuffer, _register);
            }
            else // Size * Lane == 2
            {
                _mm_storeu_si16(pBuffer, _register);
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::storeAligned(
        DataType* pBuffer) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            _mm_store_pd(pBuffer, _register);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (Lane == 2)
            {
                _mm_storel_pi(reinterpret_cast<__m64*>(pBuffer), _register);
                // _mm_store_sd(reinterpret_cast<double*>(pBuffer), _mm_castps_pd(_register));
            }
            else
            {
                _mm_store_ps(pBuffer, _register);
            }
        }
        else
        {
            if constexpr (sizeof(DataType) * Lane == 16)
            {
                _mm_store_si128(reinterpret_cast<__m128i*>(pBuffer), _register);
            }
            else if constexpr (sizeof(DataType) * Lane == 8)
            {
                _mm_storeu_si64(pBuffer, _register);
            }
            else if constexpr (sizeof(DataType) * Lane == 4)
            {
                _mm_storeu_si32(pBuffer, _register);
            }
            else // Size * Lane == 2
            {
                _mm_storeu_si16(pBuffer, _register);
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::get(
        const size_t index) const noexcept
    {

        // TODO: Extract out message
        // TODO: Add death test
        FALCON_ASSERT_MSG(
            index < Lane,
            std::format("Out of bounds access. Index must be less than {}. But it is currently {}", Lane, index)
                .c_str());

        // We can use the compress and extract trick from CVL2(Agner Fog)
        // But that instruction is available only in AVX512F + AVX512VL
        // https://github.com/vectorclass/version2/blob/master/vectori128.h
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            // 1u << index creates a mask that selects the lane we want to index into
            // Eg: For index 4 the mask is 1 << 4 => 0001 0000 instead of 0000 1000
            auto mask = static_cast<__mmask8>(1u << index);
            if constexpr (types::IsFP64<DataType>)
            {
                auto reg = _mm_maskz_compress_pd(mask, _register);
                return _mm_cvtsd_f64(reg);
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                auto reg = _mm_maskz_compress_ps(mask, _register);
                return _mm_cvtss_f32(reg);
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                auto reg = _mm_maskz_compress_epi64(mask, _register);
                return std::bit_cast<DataType>(_mm_cvtsi128_si64(reg));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                auto reg = _mm_maskz_compress_epi32(mask, _register);
                return std::bit_cast<DataType>(_mm_cvtsi128_si32(reg));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                auto reg = _mm_maskz_compress_epi16(mask, _register);
                return std::bit_cast<DataType>(_mm_cvtsi128_si16(reg));
            }
            else // if constexpr (sizeof(DataType) == 2)
            {
                // Note: epi8 version of maskz_compress require __mmask16 and there is no standalone
                //       variant of cvtsi128 for converting to 8-bit integral
                auto reg = _mm_maskz_compress_epi8(static_cast<__mmask16>(1u << index), _register);
                return static_cast<DataType>(_mm_cvtsi128_si16);
            }
            return static_cast<DataType>(index);
        }
        else
        {
            std::array<DataType, Lane> buffer{};
            store(buffer.data());
            return buffer[index];
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
            return Simd128(_mm_andnot_si128(_register, oneReg.naive()));
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


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::andNot(
        const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_andnot_pd(_register, other.naive()));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_andnot_ps(_register, other.naive()));
        }
        else
        {
            return Simd128(_mm_andnot_si128(_register, other.naive()));
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
     *       ARITHMETIC OPERATIONS        *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator+(const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_add_pd(_register, other.naive()));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_add_ps(_register, other.naive()));
        }
        else
        {
            if constexpr (sizeof(DataType) == 8)
            {
                return Simd128(_mm_add_epi64(_register, other.naive()));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd128(_mm_add_epi32(_register, other.naive()));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd128(_mm_add_epi16(_register, other.naive()));
            }
            else
            {
                return Simd128(_mm_add_epi8(_register, other.naive()));
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator+=(const Simd128 other) noexcept
    {
        *this = *this + other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator-(const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_sub_pd(_register, other.naive()));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_sub_ps(_register, other.naive()));
        }
        else
        {
            if constexpr (sizeof(DataType) == 8)
            {
                return Simd128(_mm_sub_epi64(_register, other.naive()));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd128(_mm_sub_epi32(_register, other.naive()));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd128(_mm_sub_epi16(_register, other.naive()));
            }
            else
            {
                return Simd128(_mm_sub_epi8(_register, other.naive()));
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator-=(const Simd128 other) noexcept
    {
        *this = *this - other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator*(const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_mul_pd(_register, other.naive()));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_mul_ps(_register, other.naive()));
        }
        else
        {
            if constexpr (sizeof(DataType) == 8)
            {

                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
                {
                    return Simd128(_mm_mullo_epi64(_register, other.naive()));
                }
                else if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
                {
                    // Since there are no EPI64 instructions less than AVX512DQ/VL architecture
                    // we need to resort to splitting low and high part and multiplying
                    // We can split a 64-bit number into high and low parts A => A_Lo + A_Hi * 2^32(or << 32)
                    // A * B = A_Lo * B_Lo + A_Lo * B_Hi << 2^32 + A_Hi * B_Lo << 2^32 + A_Hi * B_Hi << 2^64 (zero
                    // so no calculation needed for this part)
                    // (_, A1_Lo * B1_Lo, _, A0_Lo * B0_Lo)
                    __m128i lowProduct = _mm_mullo_epi32(_register, other.naive()); // A_Lo * B_Lo

                    // Swap High and Low lanes
                    // (B1_Hi, B1_Lo, B0_Hi, B0_Lo) => (B1_Lo, B1_Hi, B0_Lo, B0_Hi)
                    __m128i swappedB = _mm_shuffle_epi32(other.naive(), _MM_SHUFFLE(2, 3, 0, 1));

                    // (A1_Hi * B1_Lo , A1_Lo, B1_Hi, A0_Hi * B0_Lo, A0_Lo * B0_Hi)
                    __m128i highLowProduct = _mm_mullo_epi32(_register, swappedB);
                    __m128i zero           = _mm_setzero_si128();

                    // (0, 0, A1_Hi * B1_Lo + A1_Lo, B1_Hi, A0_Hi * B0_Lo + A0_Lo, B0_Hi)
                    __m128i addedProd = _mm_hadd_epi32(zero, highLowProduct);
                    // Shuffle the horizontally added product so that we can add the results together and
                    // form the final values
                    // The first and second to last position for shuffled can be anything as its irrelevant
                    // but since we have zeros at 3 and 2 we can use them so the add will produce a perfect result
                    __m128i shuffledProd = _mm_shuffle_epi32(addedProd, _MM_SHUFFLE(3, 1, 2, 0));

                    return Simd128(_mm_add_epi64(shuffledProd, lowProduct));
                }
                else
                {
                    // Since SSE2 doesn't natively support HAdd, we need to extract the elements and
                    // do direct multiplication
                    // TODO: Update with set/ctor init
                    DataType a[2], b[2];
                    storeAligned(a);
                    other.storeAligned(b);
                    Simd128 result{};
                    alignas(16) DataType resultData[2]{ a[0] * b[0], a[1] * b[1] };
                    result.loadAligned(resultData);
                    return result;
                }
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
                {
                    return Simd128(_mm_mullo_epi32(_register, other.naive()));
                }
                else
                {
                    // Agner Fog's VCL: https://github.com/vectorclass/version2/blob/master/vectori128.h
                    // Since EPU multiplication instruction in SSE2 multiplies only the low part of "64-bit"
                    // integers aka the even lanes we need to shuffle and put the numbers in the odd lane to the
                    // even lanes and perform two separate multiplication and then pack them together
                    __m128i oddA = _mm_shuffle_epi32(_register, _MM_SHUFFLE(3, 3, 1, 1));
                    __m128i oddB = _mm_shuffle_epi32(other.naive(), _MM_SHUFFLE(3, 3, 1, 1));

                    __m128i evenProduct = _mm_mul_epu32(_register, other.naive());
                    __m128i oddProduct  = _mm_mul_epu32(oddA, oddB);

                    // Pack the odd and even register so that their lower part is filled appropriately
                    // G -> Garbage
                    // even(_, 2, _, 0) + odd(_, 3, _, 1) =packed=> Lo(_, _, 1, 0) & Hi(_, _, 3, 2)
                    __m128i packedLowerHalf = _mm_unpacklo_epi32(evenProduct, oddProduct);
                    __m128i packedhighHalf  = _mm_unpackhi_epi32(evenProduct, oddProduct);

                    // Pack the packed 32-bits into 2 64-bit lanes
                    // Lo(_, _, 1, 0) & Hi(_, _, 3, 2) =packed=> (3, 2, 1, 0)
                    return Simd128(_mm_unpacklo_epi64(packedLowerHalf, packedhighHalf));
                }
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd128(_mm_mullo_epi16(_register, other.naive()));
            }
            else
            {
                // Agner Fog's VCL: https://github.com/vectorclass/version2/blob/master/vectori128.h
                /// Split the numbers into even and odd lanes
                /// Since we dont have a problem corrupting the even lanes
                /// we don't need to mask them
                const __m128i oddA = _mm_srli_epi16(_register, 8); // Shift right by 8-bits
                const __m128i oddB = _mm_srli_epi16(other.naive(), 8);

                const __m128i evenProduct = _mm_mullo_epi16(_register, other.naive());
                __m128i oddProduct        = _mm_mullo_epi16(oddA, oddB);

                // Shift the odd product to left to prepare for ORing
                oddProduct = _mm_slli_epi16(oddProduct, 8);

                // OR together with a mask since pure OR can collect the garbage values from even product
                // For blend 0 select first bit from first register and 1 selects bits from second register
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
                {
                    /// 0x5555 translates to 0b010101.. which select the 8-bits from oddReg, then evenReg etc.
                    return Simd128(_mm_mask_mov_epi8(oddProduct, 0x5555, evenProduct));
                }
                else
                {
                    const __m128i mask = _mm_set1_epi16(0x00FF);

                    return Simd128(_mm_or_si128(_mm_and_si128(mask, evenProduct), _mm_andnot_si128(mask, oddProduct)));
                }
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator*=(const Simd128 other) noexcept
    {
        *this = *this * other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::divReg(Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_div_pd(_register, other.naive()));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_div_ps(_register, other.naive()));
        }
        else
        {
            // Since double can have only 53-bits of precision
            // we need to either use the division by constant algorithm by Donald E. Knuth
            // or unload the register do the division with IDIV and load the result to a new register.
            // Latter is implemented here and former for operator/(TODO)
            if constexpr (sizeof(DataType) == 8)
            {
                // The only possible combination for b lane is 2.
                // so we can manually calculate the division for 2 integers without loops
                std::array<DataType, Lane> a{}, b{}, result{};
                store(a.data());
                other.store(b.data());

                result[0] = a[0] / b[0];
                result[1] = a[1] / b[1];

                // TODO: Refactor using ctor inits
                Simd128 reg;
                reg.load(result.data());
                return reg;
            }
            else if constexpr (types::IsDWord<DataType>)
            {
                // Since floats cannot fully represent 32-bit integers
                // we need to unpack them to doubles across 2 registers
                // perform the division and cast back and pack
                const __m128d lowA = _mm_cvtepi32_pd(_register); // (3, 2, 1, 0) => (1, 0)
                const __m128d lowB = _mm_cvtepi32_pd(other.naive());

                // Since epi32_pd takes bytes from lower lane, we need shift the upper bytes to lower lanes by
                // 8-bytes and cast to packed doubles (3, 2, 1, 0) => (_, _, 3, 2) => (3, 2)
                const __m128d highA = _mm_cvtepi32_pd(_mm_srli_si128(_register, 8));
                const __m128d highB = _mm_cvtepi32_pd(_mm_srli_si128(other.naive(), 8));

                // Perform division
                const __m128d resultLow  = _mm_div_pd(lowA, lowB);
                const __m128d resultHigh = _mm_div_pd(highA, highB);

                // Convert back to integers with truncation (cvt"t")
                const __m128i intLow  = _mm_cvttpd_epi32(resultLow);  // (_, _, 1, 0)
                const __m128i intHigh = _mm_cvttpd_epi32(resultHigh); // (_, _, 3, 2)

                // Pack and return
                // Here we can use unpack to "pack" the lower lanes
                return Simd128(_mm_unpacklo_epi64(intLow, intHigh)); // (3, 2, 1, 0)
            }
            else if constexpr (types::IsUDWord<DataType>)
            {
                // Unsigned integer to double packing is only supported on AVX512F/VL
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
                {
                    // Since floats cannot fully represent 32-bit integers
                    // we need to unpack them to doubles across 2 registers
                    // perform the division and cast back and pack
                    const __m128d lowA = _mm_cvtepu32_pd(_register); // (3, 2, 1, 0) => (1, 0)
                    const __m128d lowB = _mm_cvtepu32_pd(other.naive());

                    // Since epi32_pd takes bytes from lower lane, we need shift the upper bytes to lower lanes by
                    // 8-bytes and cast to packed doubles (3, 2, 1, 0) => (_, _, 3, 2) => (3, 2)
                    const __m128d highA = _mm_cvtepu32_pd(_mm_srli_si128(_register, 8));
                    const __m128d highB = _mm_cvtepu32_pd(_mm_srli_si128(other.naive(), 8));

                    // Perform division
                    const __m128d resultLow  = _mm_div_pd(lowA, lowB);
                    const __m128d resultHigh = _mm_div_pd(highA, highB);

                    // Convert back to integers with truncation (cvt"t")
                    const __m128i intLow  = _mm_cvttpd_epu32(resultLow);  // (_, _, 1, 0)
                    const __m128i intHigh = _mm_cvttpd_epu32(resultHigh); // (_, _, 3, 2)

                    // Pack and return
                    // Here we can use unpack to "pack" the lower lanes
                    return Simd128(_mm_unpacklo_epi64(intLow, intHigh)); // (3, 2, 1, 0)
                }
                else
                {
                    std::array<DataType, Lane> a{}, b{}, result{};
                    store(a.data());
                    other.store(b.data());
                    for (size_t i = 0; i < Lane; ++i)
                    {
                        result[i] = a[i] / b[i];
                    }

                    // TODO: Refactor to 1 line with ctor
                    Simd128 data;
                    data.load(result.data());
                    return data;
                }
            }
            else if constexpr (types::IsWord<DataType>)
            {
                // Similar logic to 32-bit integrals but we can use floats since
                // they have 23-bits of precision
                // Due to the lack of direct conversion from epi16 to ps we need to unpack and then convert
                //
                // To sign extend we can pack the register with itself and arithmetic shift to the right by 16 bits
                // which fills the upper lane with 1 if negative
                // Eg: Take -7: 1001 => 1001 1001, which we need to shift by 4 times since that is width of our data
                // 1001 1001 => 1100 1100 => 1110 0110 => 1111 0011 => 1111 1001, which is -7(2's complement)
                const __m128i signExtLowA  = _mm_srai_epi32(_mm_unpacklo_epi16(_register, _register), 16);
                const __m128i signExtLowB  = _mm_srai_epi32(_mm_unpacklo_epi16(other.naive(), other.naive()), 16);
                const __m128i signExtHighA = _mm_srai_epi32(_mm_unpackhi_epi16(_register, _register), 16);
                const __m128i signExtHighB = _mm_srai_epi32(_mm_unpackhi_epi16(other.naive(), other.naive()), 16);

                // Convert to float
                const __m128 lowA  = _mm_cvtepi32_ps(signExtLowA);
                const __m128 lowB  = _mm_cvtepi32_ps(signExtLowB);
                const __m128 highA = _mm_cvtepi32_ps(signExtHighA);
                const __m128 highB = _mm_cvtepi32_ps(signExtHighB);

                // Perform division
                const __m128 resultLow  = _mm_div_ps(lowA, lowB);
                const __m128 resultHigh = _mm_div_ps(highA, highB);

                // Convert to integers
                const __m128i intLow  = _mm_cvttps_epi32(resultLow);  // (Q3, Q2, Q1, Q0)
                const __m128i intHigh = _mm_cvttps_epi32(resultHigh); // (Q7, Q6, Q5, Q4)
                return Simd128(_mm_packs_epi32(intLow, intHigh));
            }
            else if constexpr (types::IsUWord<DataType>)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
                {
                    // Extend the 16 unsigned integrals to 32 bit signed integrals
                    const __m128i extLowA  = _mm_cvtepu16_epi32(_register);
                    const __m128i extLowB  = _mm_cvtepu16_epi32(other.naive());
                    const __m128i extHighA = _mm_cvtepu16_epi32(_mm_srli_si128(_register, 8));
                    const __m128i extHighB = _mm_cvtepu16_epi32(_mm_srli_si128(other.naive(), 8));

                    // Convert to floating point registers
                    const __m128 lowA  = _mm_cvtepi32_ps(extLowA);
                    const __m128 lowB  = _mm_cvtepi32_ps(extLowB);
                    const __m128 highA = _mm_cvtepi32_ps(extHighA);
                    const __m128 highB = _mm_cvtepi32_ps(extHighB);

                    // Perform the division
                    const __m128 resultLow  = _mm_div_ps(lowA, lowB);
                    const __m128 resultHigh = _mm_div_ps(highA, highB);

                    // Convert back to integrals
                    const __m128i intLow  = _mm_cvttps_epi32(resultLow);
                    const __m128i intHigh = _mm_cvttps_epi32(resultHigh);
                    return Simd128(_mm_packus_epi32(intLow, intHigh));
                }
                else
                {
                    // TODO: Add Simd if possible
                    std::array<DataType, Lane> a{}, b{}, result{};
                    store(a.data());
                    other.store(b.data());
                    for (size_t i = 0; i < Lane; ++i)
                    {
                        result[i] = a[i] / b[i];
                    }
                    Simd128 reg;
                    reg.load(result.data());
                    return reg;
                }
            }
            else if constexpr (types::IsByte<DataType>)
            {

                // We have a total of 8 registers containing the unpacked 8 x 8 values L -> Low and H -> High
                // abbreviated to prevent confusion
                __m128i sExtLowAL;
                __m128i sExtLowAH;
                __m128i sExtLowBL;
                __m128i sExtLowBH;
                __m128i sExtHighAL;
                __m128i sExtHighAH;
                __m128i sExtHighBL;
                __m128i sExtHighBH;
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
                {
                    // To convert the 8-bit register from 8-bit to 32-bits directly we need to use
                    // shifts in combination with cvt(only available in SSE4.1 and above)
                    //                (highAH, highAL, lowAH, lowAL)
                    // Shift amount        12,      8,     4,     0
                    sExtLowAL  = _mm_cvtepi8_epi32(_register);
                    sExtLowAH  = _mm_cvtepi8_epi32(_mm_srli_si128(_register, 4));
                    sExtHighAL = _mm_cvtepi8_epi32(_mm_srli_si128(_register, 8));
                    sExtHighAH = _mm_cvtepi8_epi32(_mm_srli_si128(_register, 12));

                    sExtLowBL  = _mm_cvtepi8_epi32(other.naive());
                    sExtLowBH  = _mm_cvtepi8_epi32(_mm_srli_si128(other.naive(), 4));
                    sExtHighBL = _mm_cvtepi8_epi32(_mm_srli_si128(other.naive(), 8));
                    sExtHighBH = _mm_cvtepi8_epi32(_mm_srli_si128(other.naive(), 12));
                }
                else
                {
                    // For processing bytes we need first promoted to word (16-bit registers
                    // and then to qword or 32-bit integral with sign extension
                    // and then to float perform division and pack them back
                    // Sign extend from 8 - 16 bits
                    const __m128i sExtWordLowA  = _mm_srai_epi16(_mm_unpacklo_epi8(_register, _register), 8);
                    const __m128i sExtWordLowB  = _mm_srai_epi16(_mm_unpacklo_epi8(other.naive(), other.naive()), 8);
                    const __m128i sExtWordHighA = _mm_srai_epi16(_mm_unpackhi_epi8(_register, _register), 8);
                    const __m128i sExtWordHighB = _mm_srai_epi16(_mm_unpackhi_epi8(other.naive(), other.naive()), 8);


                    sExtLowAL = _mm_srai_epi32(_mm_unpacklo_epi16(sExtWordLowA, sExtWordLowA), 16);
                    sExtLowAH = _mm_srai_epi32(_mm_unpackhi_epi16(sExtWordLowA, sExtWordLowA), 16);
                    sExtLowBL = _mm_srai_epi32(_mm_unpacklo_epi16(sExtWordLowB, sExtWordLowB), 16);
                    sExtLowBH = _mm_srai_epi32(_mm_unpackhi_epi16(sExtWordLowB, sExtWordLowB), 16);

                    // Sign extend from 16 - 32 bits
                    sExtHighAL = _mm_srai_epi32(_mm_unpacklo_epi16(sExtWordHighA, sExtWordHighA), 16);
                    sExtHighAH = _mm_srai_epi32(_mm_unpackhi_epi16(sExtWordHighA, sExtWordHighA), 16);
                    sExtHighBL = _mm_srai_epi32(_mm_unpacklo_epi16(sExtWordHighB, sExtWordHighB), 16);
                    sExtHighBH = _mm_srai_epi32(_mm_unpackhi_epi16(sExtWordHighB, sExtWordHighB), 16);
                }

                // Convert to 32-bit floats
                const __m128 lowAL = _mm_cvtepi32_ps(sExtLowAL);
                const __m128 lowBL = _mm_cvtepi32_ps(sExtLowBL);
                const __m128 lowAH = _mm_cvtepi32_ps(sExtLowAH);
                const __m128 lowBH = _mm_cvtepi32_ps(sExtLowBH);

                const __m128 highAL = _mm_cvtepi32_ps(sExtHighAL);
                const __m128 highBL = _mm_cvtepi32_ps(sExtHighBL);
                const __m128 highAH = _mm_cvtepi32_ps(sExtHighAH);
                const __m128 highBH = _mm_cvtepi32_ps(sExtHighBH);

                // Perform division
                const __m128 resLowL  = _mm_div_ps(lowAL, lowBL);
                const __m128 resLowH  = _mm_div_ps(lowAH, lowBH);
                const __m128 resHighL = _mm_div_ps(highAL, highBL);
                const __m128 resHighH = _mm_div_ps(highAH, highBH);

                // Convert to 32-bit integral with truncation
                const __m128i iResLowL  = _mm_cvttps_epi32(resLowL);
                const __m128i iResLowH  = _mm_cvttps_epi32(resLowH);
                const __m128i iResHighL = _mm_cvttps_epi32(resHighL);
                const __m128i iResHighH = _mm_cvttps_epi32(resHighH);

                // Unpack to 8 bit register(32->16->8)
                const __m128i iLow  = _mm_packs_epi32(iResLowL, iResLowH);
                const __m128i iHigh = _mm_packs_epi32(iResHighL, iResHighH);

                return Simd128(_mm_packs_epi16(iLow, iHigh));
            }
            else
            {
                __m128i extLowAL;
                __m128i extLowAH;
                __m128i extHighAL;
                __m128i extHighAH;
                __m128i extLowBL;
                __m128i extLowBH;
                __m128i extHighBL;
                __m128i extHighBH;

                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
                {
                    // To convert the 8-bit register from 8-bit to 32-bits directly we need to use
                    // shifts in combination with cvt(only available in SSE4.1 and above)
                    // Register     (highAH, highAL, lowAH, lowAL)
                    // Shift amount      12,      8,     4,     0
                    extLowAL  = _mm_cvtepu8_epi32(_register);
                    extLowAH  = _mm_cvtepu8_epi32(_mm_srli_si128(_register, 4));
                    extHighAL = _mm_cvtepu8_epi32(_mm_srli_si128(_register, 8));
                    extHighAH = _mm_cvtepu8_epi32(_mm_srli_si128(_register, 12));

                    extLowBL  = _mm_cvtepu8_epi32(other.naive());
                    extLowBH  = _mm_cvtepu8_epi32(_mm_srli_si128(other.naive(), 4));
                    extHighBL = _mm_cvtepu8_epi32(_mm_srli_si128(other.naive(), 8));
                    extHighBH = _mm_cvtepu8_epi32(_mm_srli_si128(other.naive(), 12));
                }
                else
                {
                    // To perform unsigned divide we need to first unpack to 8 bits into
                    // 16 and then 32 with zero bits interleaved
                    const __m128i zero = _mm_setzero_si128();
                    // Unpack from 8 bit to 16 bits with zero extension
                    const __m128i extLowA  = _mm_unpacklo_epi8(_register, zero);
                    const __m128i extHighA = _mm_unpackhi_epi8(_register, zero);
                    const __m128i extLowB  = _mm_unpacklo_epi8(other.naive(), zero);
                    const __m128i extHighB = _mm_unpackhi_epi8(other.naive(), zero);

                    // Unpack from 16 bits to 32 bit with zero extension
                    extLowAL  = _mm_unpacklo_epi16(extLowA, zero);
                    extLowAH  = _mm_unpackhi_epi16(extLowA, zero);
                    extHighAL = _mm_unpacklo_epi16(extHighA, zero);
                    extHighAH = _mm_unpackhi_epi16(extHighA, zero);

                    extLowBL  = _mm_unpacklo_epi16(extLowB, zero);
                    extLowBH  = _mm_unpackhi_epi16(extLowB, zero);
                    extHighBL = _mm_unpacklo_epi16(extHighB, zero);
                    extHighBH = _mm_unpackhi_epi16(extHighB, zero);
                }


                // Convert to 32-bit floats
                const __m128 lowAL = _mm_cvtepi32_ps(extLowAL);
                const __m128 lowBL = _mm_cvtepi32_ps(extLowBL);
                const __m128 lowAH = _mm_cvtepi32_ps(extLowAH);
                const __m128 lowBH = _mm_cvtepi32_ps(extLowBH);

                const __m128 highAL = _mm_cvtepi32_ps(extHighAL);
                const __m128 highBL = _mm_cvtepi32_ps(extHighBL);
                const __m128 highAH = _mm_cvtepi32_ps(extHighAH);
                const __m128 highBH = _mm_cvtepi32_ps(extHighBH);

                // Perform division
                const __m128 resLowL  = _mm_div_ps(lowAL, lowBL);
                const __m128 resLowH  = _mm_div_ps(lowAH, lowBH);
                const __m128 resHighL = _mm_div_ps(highAL, highBL);
                const __m128 resHighH = _mm_div_ps(highAH, highBH);

                // Convert to 32-bit integral with truncation
                const __m128i iResLowL  = _mm_cvttps_epi32(resLowL);
                const __m128i iResLowH  = _mm_cvttps_epi32(resLowH);
                const __m128i iResHighL = _mm_cvttps_epi32(resHighL);
                const __m128i iResHighH = _mm_cvttps_epi32(resHighH);


                // Unpack to 8 bit register(32->16->8)
                // Since we are converting from 32 to 8 we can use signed packing
                // for 32-bit to 16-bit since the maximum saturation of 32,767 will never
                // be hit, since the max value for 8-bit is 255
                const __m128i iLow  = _mm_packs_epi32(iResLowL, iResLowH);
                const __m128i iHigh = _mm_packs_epi32(iResHighL, iResHighH);

                return Simd128(_mm_packus_epi16(iLow, iHigh));
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator/(const DataType scalar) const noexcept
    {
        Simd128 divisor;
        divisor.broadcast(scalar);
        return divReg(divisor);
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                       Lane>::operator/=(const DataType scalar) noexcept
    {
        *this = *this / scalar;
        return *this;
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
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator>=(const Simd128 other) const noexcept
    { return ~(*this < other); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator<(const Simd128 other) const noexcept
    { return other > *this; }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator<=(const Simd128 other) const noexcept
    { return ~(*this > other); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::blend(const Simd128 other, const Simd128 mask) const noexcept
    {
        // Blend functions are only available from SSE 4.1
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd128(_mm_blendv_pd(_register, other.naive(), mask.naive()));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd128(_mm_blendv_ps(_register, other.naive(), mask.naive()));
            }
            else
            {
                return Simd128(_mm_blendv_epi8(_register, other.naive(), mask.naive()));
            }
        }
        else
        {
            // Pick from this register whenever value of zero is encountered(~mask) and from other whenever 1 is
            // encountered
            // return *this & ~mask | other & mask;
            return mask.andNot(*this) | other & mask;
        }
    }

} // namespace falcon
