#pragma once
/**
 * @file Simd128SSE.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 13, 2026
 *
 * @brief SSE2 implementation for Simd128.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../RegisterTraits.h"
#include "falcon_simd/FalconSimd.h"

#include <bit>
#include <emmintrin.h>
#include <immintrin.h>
#include <type_traits>
#include <xmmintrin.h>

namespace falcon
{
    /**
     * @brief 128-bit Simd Register specialized for SSE2/4.1 architecture.
     *
     * @tparam DataType The word-width/data type of the register.
     * @tparam Lane     The number of data lanes. Must be a power of 2 and the total width in bits(size * Lane) must be
     *                  less than 128.
     */
    template <typename DataType, size_t Lane>
    struct Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>
    {

        static constexpr size_t BUFFER_WIDTH = 128;      ///< Width of the register in bits.
        using ValueType                      = DataType; ///< The internal data type of this Register.
        static constexpr size_t LaneCount    = Lane;     ///< Number of Lanes of current SIMD128 Register

        static_assert(sizeof(DataType) * Lane <= BUFFER_WIDTH && "Invalid size.");
        static_assert(std::has_single_bit(Lane) && Lane > 1 && "Invalid Number of Lanes.");


        // TODO: Update
        FALCON_SIMD_INLINE constexpr explicit Simd128() = default;


        /**
         * @brief Load data from memory into the SIMD register.
         *
         * @note Data must be aligned to 16 bit boundary.
         *       If the size * Lane cannot saturate the buffer, data will be moved to lower
         *       Example: loadAligned<2>(uint8_t*) will only load the lower 16-bit with the data and fill the rest with
         *       zeroes.
         * @note For floating-point types, single lane will fill the entire buffer with the data.
         *
         * @param data The data to load.
         */
        FALCON_SIMD_INLINE constexpr void loadAligned(DataType* data) noexcept
        {
            // We are using sizes for loading integers since we are storing both signed and unsigned types into the
            // register as bits, with packing.
            if constexpr (std::is_same_v<DataType, double>)
            {
                _register = _mm_load_pd(data);
            }
            else if constexpr (std::is_same_v<DataType, float>)
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


        /**
         * @brief Broadcast single value across the whole simd register.
         *
         * @details
         *        Fills the entire register lane with the same value, i.e, for 32-bit floats, all the 4 lanes will
         *        contain the same @p value.
         * @param value The value to broadcast.
         */
        FALCON_SIMD_INLINE constexpr void broadcast(DataType value) noexcept
        {
            if constexpr (std::is_same_v<DataType, double>)
            {
                _register = _mm_set1_pd(value);
            }
            else if constexpr (std::is_same_v<DataType, float>)
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


        /**
         * @brief Zero out the register.
         */
        FALCON_SIMD_INLINE constexpr void setZero() noexcept
        {
            if constexpr (std::is_same_v<DataType, double>)
            {
                _register = _mm_setzero_pd();
            }
            else if constexpr (std::is_same_v<DataType, float>)
            {
                _register = _mm_setzero_ps();
            }
            else
            {
                _register = _mm_setzero_si128();
            }
        }


        /**
         * @brief Dump the current register value into a 16-byte aligned buffer.
         *
         * @param pBuffer The buffer to write the data to.
         */
        FALCON_SIMD_INLINE constexpr void storeAligned(DataType* pBuffer) const noexcept
        {
            if constexpr (std::is_same_v<DataType, double>)
            {
                _mm_store_pd(pBuffer, _register);
            }
            else if constexpr (std::is_same_v<DataType, float>)
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


        /// @brief Initialize a Simd128 with the supplied register.
        FALCON_SIMD_INLINE explicit constexpr Simd128(simd::internal::SSERegister_t<DataType> reg): _register(reg) {}


        /**
         * @brief Convert a register from one data type to another.
         *
         * @note The number of lanes must match.
         * @note Converting between data types of unmatched size, like from `uint8_t` to `double` and performing
         *       operations on them may yield undesired outcome due to the pure intrinsic casts used.
         *
         * @tparam DataType2 The data type of the incoming register.
         * @param other      The register to conform to the current register type.
         */
        template <typename DataType2>
        FALCON_SIMD_INLINE explicit constexpr Simd128(const Simd128<SimdBackend::ARCH_SSE2, DataType2, Lane>& other)
        {
            if constexpr (std::is_same_v<DataType2, double>)
            {
                if constexpr (std::is_same_v<DataType, double>)
                {
                    _register = other.naive();
                }
                else if constexpr (std::is_same_v<DataType, float>)
                {
                    _register = _mm_cvtpd_ps(other.naive());
                }
                else
                {
                    _register = _mm_cvtpd_epi32(other.naive());
                }
            }
            else if constexpr (std::is_same_v<DataType2, float>)
            {
                if constexpr (std::is_same_v<DataType, double>)
                {
                    _register = _mm_cvtps_pd(other.naive());
                }
                else if constexpr (std::is_same_v<DataType, float>)
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
                if constexpr (std::is_same_v<DataType, double>)
                {
                    _register = _mm_cvtepi32_pd(other.naive());
                }
                else if constexpr (std::is_same_v<DataType, float>)
                {
                    _register = _mm_cvtepi32_ps(other.naive());
                }
                else
                {
                    _register = other.naive();
                }
            }
        }


        /**
         * @brief Add two registers together and return a new register.
         *
         * @note Register arithmetic to limited is same data types and lanes.
         *
         * @param other The register to add.
         *
         * @return A new register with the sum elements from this register and @p other.
         */
        FALCON_SIMD_INLINE Simd128 operator+(const Simd128 other)
        {
            if constexpr (std::is_same_v<DataType, double>)
            {
                return Simd128(_mm_add_pd(_register, other.naive()));
            }
            else if constexpr (std::is_same_v<DataType, float>)
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


        /**
         * @brief Add contents of this register with @p other in-place.
         *
         * @note Register arithmetic to limited is same data types and lanes.
         *
         * @param other The register to add.
         *
         * @return A reference to the this register with sum.
         */
        FALCON_SIMD_INLINE Simd128& operator+=(const Simd128 other)
        {
            *this = *this + other;
            return *this;
        }


        /**
         * @brief Subtract two registers and return a new register.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to subtract.
         * @return A new register with the difference between elements of this register and @p other.
         */
        FALCON_SIMD_INLINE Simd128 operator-(const Simd128 other)
        {
            if constexpr (std::is_same_v<DataType, double>)
            {
                return Simd128(_mm_sub_pd(_register, other.naive()));
            }
            else if constexpr (std::is_same_v<DataType, float>)
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


        /**
         * @brief Subtract contents of this register from @p other in-place.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to subtract.
         *
         * @return A reference to the this register with difference.
         */
        FALCON_SIMD_INLINE Simd128 operator-=(const Simd128 other)
        {
            *this = *this - other;
            return *this;
        }

        /**
         * @brief Multiply two registers and return a new register.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to multiply.
         * @return A new register with the product of elements of this register and @p other.
         */
        FALCON_SIMD_INLINE Simd128 operator*(const Simd128 other)
        {
            if constexpr (std::is_same_v<DataType, double>)
            {
                return Simd128(_mm_mul_pd(_register, other.naive()));
            }
            else if constexpr (std::is_same_v<DataType, float>)
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
                        // return Simd128(); // TODO:
                        return Simd128(_mm_sub_epi64(_register, other.naive()));
                    }
                    else
                    {
                        return Simd128(_mm_sub_epi64(_register, other.naive()));
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
                        // Since EPU multiplication instruction in SSE2 multiplies only the low part of "64-bit"
                        // integers aka the even lanes we need to shuffle and put the numbers in the odd lane to the
                        // even lanes and perform two separate multiplication and then pack them together
                        __m128i oddA = _mm_shuffle_epi32(_register, _MM_SHUFFLE(3, 3, 1, 1));
                        __m128i oddB = _mm_shuffle_epi32(other.naive(), _MM_SHUFFLE(3, 3, 1, 1));

                        __m128i evenProduct = _mm_mul_epu32(_register, other.naive());
                        __m128i oddProduct  = _mm_mul_epu32(oddA, oddB);

                        // Pack the odd and even register so that their lower part is filled appropriately
                        // G -> Garbage
                        // even(G, 2, G, 0) + odd(G, 3, G, 1) =packed=> Lo(G, G, 1, 0) & Hi(G, G, 3, 2)
                        __m128i packedLowerHalf  = _mm_unpacklo_epi32(evenProduct, oddProduct);
                        __m128i packedHigherHalf = _mm_unpackhi_epi32(evenProduct, oddProduct);

                        // Pack the packed 32-bits into 2 64-bit lanes
                        // Lo(G, G, 1, 0) & Hi(G, G, 3, 2) =packed=> (3, 2, 1, 0)
                        return Simd128(_mm_unpacklo_epi64(packedLowerHalf, packedHigherHalf));
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
                        return Simd128(_mm_blendv_epi8(oddProduct, evenProduct, mask));
                    }
                }
            }
        }

        // TODO: Add Packing and Unpacking



        /// TODO: Add tests for these

        /// @brief Get the internal register used by Simd128
        FALCON_SIMD_INLINE constexpr simd::internal::SSERegister_t<DataType> naive() const noexcept
        { return _register; }

        // template <typename... Args>
        // FALCON_SIMD_INLINE constexpr explicit set(Args... data) const noexcept; // Analogous to setting

        /// Given for completion sake
        /// Note: Each lane is considered the native width of the datatype
        /// The operation will get the data, mutate it and set it into register, which can be expensive
        /// so it highly recommended to not use this operation
        /// TODO: Implementation Later
        // FALCON_SIMD_INLINE constexpr setAt(size_t index, const DataType data) const noexcept;
        //
        // FALCON_SIMD_INLINE constexpr getAt(size_t index) const noexcept;

    private:
        simd::internal::SSERegister_t<DataType> _register;
    };

} // namespace falcon
