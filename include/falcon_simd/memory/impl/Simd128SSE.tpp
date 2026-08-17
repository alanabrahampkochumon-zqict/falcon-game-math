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
        static_assert(std::has_single_bit(Lane) && Lane >= 1 && "Invalid Number of Lanes.");


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
                if constexpr (Lane == 1)
                {
                    _register = _mm_load_pd1(data);
                }
                else
                {
                    _register = _mm_load_pd(data);
                }
            }
            else if constexpr (std::is_same_v<DataType, float>)
            {
                if constexpr (Lane == 1)
                {
                    _register = _mm_load_ps1(data);
                }
                else if constexpr (Lane == 2)
                {
                    _register = _mm_castpd_ps(_mm_load_sd(reinterpret_cast<const double*>(data)));
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
                else if constexpr (sizeof(DataType) * Lane == 2)
                {
                    _register = _mm_loadu_si16(data);
                }
                else
                {
                    /// We need to static cast since there is no load func for Bytes
                    _register = _mm_loadu_si16(reinterpret_cast<uint16_t*>(data));
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
                if constexpr (Lane == 1)
                {
                    _mm_store_sd(pBuffer, _register);
                }
                else
                {
                    _mm_store_pd(pBuffer, _register);
                }
            }
            else if constexpr (std::is_same_v<DataType, float>)
            {
                if constexpr (Lane == 1)
                {
                    _mm_store_ss(pBuffer, _register);
                }
                else if constexpr (Lane == 2)
                {
                    _mm_store_sd(reinterpret_cast<double*>(pBuffer), _mm_castps_pd(_register));
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
                else if constexpr (sizeof(DataType) * Lane == 2)
                {
                    _mm_storeu_si16(pBuffer, _register);
                }
                else
                {
                    /// We need to static cast since there is no store func for Bytes
                    /// TODO: Look into this as this can might be problem.
                    _mm_storeu_si16(reinterpret_cast<uint16_t*>(pBuffer), _register);
                }
            }
        }
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
