#pragma once
/**
 * @file Simd128SSE.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 13, 2026
 *
 * @brief AVX2 implementation for Simd128.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "falcon_simd/Simd.h"

#include <bit>
#include <emmintrin.h>
#include <xmmintrin.h>
namespace falcon
{
    template <typename DataType>
    struct Simd128<SimdBackend::ARCH_SSE2, DataType>
    {
        using RegisterType = std::conditional_t<std::is_same_v<DataType, double>, __m128d,
                                                std::conditional_t<std::is_same_v<DataType, float>, __m128, __m128i>>;

        static constexpr size_t BUFFER_WIDTH = 128; ///< Width of the register in bits.

        // Don't do this
        // Trap. You dont know the size when store the data
        FALCON_SIMD_INLINE explicit Simd128() = default;

        /**
         * @brief Load data from memory into the SIMD register.
         *
         * @note Data must be aligned to 16 bit boundary.
         *       If the size * Lane cannot saturate the buffer, data will be moved to lower
         *       Example: loadAligned<2>(uint8_t*) will only load the lower 16-bit with the data and fill the rest with
         *       zeroes.
         * @note For floating-point types, single lane will fill the entire buffer with the data.
         *
         * @tparam Lane The number of data lanes. Must be a power of 2 and the total width in bits(size * Lane) must be
         *              less than 128.
         *
         * @param data The data to load.
         */
        template <size_t Lane>
        FALCON_SIMD_API void loadAligned(DataType* data) noexcept
        {
            static_assert(sizeof(DataType) * Lane <= BUFFER_WIDTH && "Invalid size.");
            static_assert(std::has_single_bit(Lane) && Lane >= 1 && "Invalid Number of Lanes.");
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
                    _register = _mm_load_sd(reinterpret_cast<double*>(data));
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
                    _register = _mm_load_si128(data);
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
                    _register = _mm_loadu_si16(static_cast<uint16_t*>(data));
                }
            }
        }


        FALCON_SIMD_INLINE constexpr broadcast(DataType value) noexcept
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
                    _register = _mm_set1_epi64(value);
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


        FALCON_SIMD_INLINE constexpr setZero() noexcept
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


        template<size_t Lane>
        FALCON_SIMD_INLINE constexpr store(DataType* pBuffer) const noexcept;
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



        //
        // FALCON_SIMD_INLINE constexpr DataType* store() const noexcept;
        //
        // FALCON_SIMD_INLINE void loadInt8x2(DataType* data);
        // FALCON_SIMD_INLINE void loadInt8x4(DataType* data);
        // FALCON_SIMD_INLINE void loadInt8x8(DataType* data);
        // FALCON_SIMD_INLINE void loadInt8x16(DataType* data);
        //
        // FALCON_SIMD_INLINE void loadInt16x2(DataType* data);
        // FALCON_SIMD_INLINE void loadInt16x4(DataType* data);
        // FALCON_SIMD_INLINE void loadInt16x8(DataType* data);
        //
        // FALCON_SIMD_INLINE void loadInt32x4(DataType* data);
        //
        // FALCON_SIMD_INLINE void loadInt64x2(DataType* data);
        //
        // FALCON_SIMD_INLINE void loadFP32x2(DataType* data);
        // FALCON_SIMD_INLINE void loadFP32x4(DataType* data);
        //
        // FALCON_SIMD_INLINE void loadFP64x2(DataType* data);
        //
        // FALCON_SIMD_INLINE void storeInt8x2(DataType* buffer);
        // FALCON_SIMD_INLINE void storeInt8x4(DataType* buffer);
        // FALCON_SIMD_INLINE void storeInt8x8(DataType* buffer);
        // FALCON_SIMD_INLINE void storeInt8x16(DataType* buffer);
        //
        // FALCON_SIMD_INLINE void storeInt16x2(DataType* buffer);
        // FALCON_SIMD_INLINE void storeInt16x4(DataType* buffer);
        // FALCON_SIMD_INLINE void storeInt16x8(DataType* buffer);
        //
        // FALCON_SIMD_INLINE void storeInt32x2(DataType* data);
        // FALCON_SIMD_INLINE void storeInt32x4(DataType* data);
        //
        // FALCON_SIMD_INLINE void storeInt64x2(DataType* data);
        //
        // FALCON_SIMD_INLINE void storeFP32x4(DataType* data);
        //
        // FALCON_SIMD_INLINE void storeFP64x2(DataType* data);

    private:
        RegisterType _register;
    };
} // namespace falcon
