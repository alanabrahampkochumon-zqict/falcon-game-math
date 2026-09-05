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
#include "falcon_core/Preprocessors.h"
#include "falcon_core/traits/TypeHelpers.h"

#include <array>
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
        constexpr explicit Simd128() = default;


        /**
         * @brief Set the register with the given values in the lower lanes filling the unfilled lanes with zeroes.
         *
         * @note Internally the register gets filled from the bottom to top, but when used with store
         *       to retrieve the value, the values will be identical.
         *       REGISTER VIEW SET(1, 2) => [0, 0, 2, 1] => STORE() => [1, 2]
         *
         * @tparam Args The numeric type of arguments. Must be less than the maximum lane size.
         *
         * @param args The data to put in the register.
         *
         * @return A reference to this register.
         */
        template <typename... Args>
            requires(sizeof...(Args) <= Lane) && (std::same_as<Args, DataType> && ...)
        constexpr Simd128& set(Args... args);


        /// @brief Initialize a Simd128 with the supplied register.
        explicit constexpr Simd128(simd::internal::SSERegister_t<DataType> reg): _register(reg) {}


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
        explicit constexpr Simd128(const Simd128<SimdBackend::ARCH_SSE2, DataType2, Lane>& other);


        /**
         * @brief Load data from memory into the SIMD register.
         *
         * @note Data must be aligned to 16 bit boundary.
         *       If the size * Lane cannot saturate the buffer, data will be moved to lower lanes.
         *       Example: loadAligned<2>(uint8_t*) will only load the lower 16-bit with the data and fill the rest with
         *       zeroes.
         *
         * @param data The data to load.
         */
        constexpr void loadAligned(DataType* data) noexcept;


        /**
         * @brief Load data from memory into the SIMD register.
         *
         * @note Can work with unaligned memory.
         *       If the size * Lane cannot saturate the buffer, data will be moved to lower lanes.
         *       Example: loadAligned<2>(uint8_t*) will only load the lower 16-bit with the data and fill the rest with
         *       zeroes.
         *
         * @param data The data to load.
         *
         * @relatedalso loadAligned(DataType*)
         * @relatedalso store(DataType*)
         * @relatedalso storeAligned(DataType*)
         * @relatedalso broadcast(DataType)
         * @relatedalso setZero()
         */
        constexpr void load(DataType* data) noexcept;


        /**
         * @brief Broadcast single value across the whole simd register.
         *
         * @details
         *        Fills the entire register lane with the same value, i.e, for 32-bit floats, all the 4 lanes will
         *        contain the same @p value.
         * @param value The value to broadcast.
         *
         * @relatedalso load(DataType*)
         * @relatedalso loadAligned(DataType*)
         * @relatedalso store(DataType*)
         * @relatedalso storeAligned(DataType*)
         * @relatedalso setZero()
         */
        constexpr void broadcast(DataType value) noexcept;


        /**
         * @brief Zero out the register.
         *
         * @relatedalso load(DataType*)
         * @relatedalso loadAligned(DataType*)
         * @relatedalso store(DataType*)
         * @relatedalso storeAligned(DataType*)
         * @relatedalso broadcast(DataType)
         * @relatedalso setOne()
         */
        constexpr void setZero() noexcept;


        /**
         * @brief Get a register filled with ones.
         *
         * @relatedalso load(DataType*)
         * @relatedalso loadAligned(DataType*)
         * @relatedalso store(DataType*)
         * @relatedalso storeAligned(DataType*)
         * @relatedalso broadcast(DataType)
         * @relatedalso setZero()
         */
        constexpr void setOne() noexcept;


        /**
         * @brief Store the current register value buffer.
         *
         * @note The provided buffer must have enough size to hold the data.
         * @note The buffer only fills upto the lane size of the register. This means that if you pass-in
         *       an array of big enough to hold 4 int32_t but the Lane is 2, then it will only fill the
         *       upper two elements, i.e [0, 1, _, _]
         *
         * @param pBuffer The buffer to write the data to.
         *
         * @relatedalso load(DataType*)
         * @relatedalso loadAligned(DataType*)
         * @relatedalso storeAligned(DataType*)
         * @relatedalso broadcast(DataType)
         * @relatedalso setZero()
         */
        FALCON_INLINE constexpr void store(DataType* pBuffer) const noexcept;


        /**
         * @brief Store the current register values into a 16-byte aligned buffer.
         *
         * @note The provided buffer must have enough size to hold the data.
         *
         * @param pBuffer The buffer to write the data to.
         *
         * @relatedalso load(DataType*)
         * @relatedalso loadAligned(DataType*)
         * @relatedalso store(DataType*)
         * @relatedalso broadcast(DataType)
         * @relatedalso setZero()
         */
        FALCON_INLINE constexpr void storeAligned(DataType* pBuffer) const noexcept;

        /**
         *
         * @param index Get the value at @p index.
         * @note Index must be less than the Lane - 1.
         *
         * @return The value at index [read-only].
         */
        constexpr DataType get(size_t index) const noexcept;


        ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        ///    BITWISE OPERATIONS
        ///+=+=+=+=+=+=+=+=+=+=+=+=+=

        /// @brief Perform bitwise NOT on the entire register.
        constexpr Simd128 operator~() const noexcept;

        /// @brief Perform bitwise AND between this register and @p other.
        constexpr Simd128 operator&(Simd128 other) const noexcept;

        /// @brief Perform bitwise OR between this register and @p other.
        constexpr Simd128 operator|(Simd128 other) const noexcept;

        /// @brief Perform bitwise OR between this register and @p other.
        constexpr Simd128 operator^(Simd128 other) const noexcept;

        /// @brief Perform a bitwise `and_not` combination between this register and @p other.
        /// @note  Faster than manually doing (~RegA & RegB) since this executes only a single SIMD instruction.
        constexpr Simd128 andNot(Simd128 other) const noexcept;


        ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        ///   ARITHMETIC OPERATIONS
        ///+=+=+=+=+=+=+=+=+=+=+=+=+=

        /**
         * @brief Add two registers together and return a new register.
         *
         * @note Register arithmetic to limited is same data types and lanes.
         *
         * @param other The register to add.
         *
         * @return A new register with the sum elements from this register and @p other.
         */
        [[nodiscard]] FALCON_INLINE Simd128 operator+(const Simd128 other) const noexcept
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


        /**
         * @brief Add contents of this register with @p other in-place.
         *
         * @note Register arithmetic to limited is same data types and lanes.
         *
         * @param other The register to add.
         *
         * @return A reference to the this register with sum.
         */
        FALCON_INLINE Simd128& operator+=(const Simd128 other) noexcept
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
        [[nodiscard]] FALCON_INLINE Simd128 operator-(const Simd128 other) const noexcept
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


        /**
         * @brief Subtract contents of this register from @p other in-place.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to subtract.
         *
         * @return A reference to the this register with difference.
         */
        FALCON_INLINE Simd128& operator-=(const Simd128 other) noexcept
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
        [[nodiscard]] FALCON_INLINE Simd128 operator*(const Simd128 other) const noexcept
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

                        return Simd128(
                            _mm_or_si128(_mm_and_si128(mask, evenProduct), _mm_andnot_si128(mask, oddProduct)));
                    }
                }
            }
        }



        /**
         * @brief Multiply contents of this register with @p other in-place.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to multiply.
         *
         * @return A reference to the this register with products.
         */
        FALCON_INLINE Simd128& operator*=(const Simd128 other) noexcept
        {
            *this = *this * other;
            return *this;
        }


        /**
         * @brief Divide contents of this register by another register(@p other).
         *
         * @note Register arithmetic is limited to same data types and lanes.
         * @note Direct SIMD operations are limited to floating-point numbers only.
         *       Therefore the operations for integrals are emulated by converting them to floating points, but some
         *       integrals like for `uint64_t` and `int64_t` are fully scalar since converting them to floating point
         *       can lead to precision loss due to the 53-bit maximum precision of double precision float point numbers.
         *
         * @note For division with same divisor it is faster to use operator/ or operator/= which implements division
         *       by constant from Hackers Delight. (TODO)
         *
         * @param other The register containing the divisors.
         *
         * @return A new register with the quotient.
         *
         * @relatedalso operator/(const DataType)
         * @relatedalso operator/=(const DataType)
         */
        [[nodiscard]] FALCON_INLINE Simd128 divReg(const Simd128 other) const noexcept
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
                        const __m128i sExtWordLowA = _mm_srai_epi16(_mm_unpacklo_epi8(_register, _register), 8);
                        const __m128i sExtWordLowB = _mm_srai_epi16(_mm_unpacklo_epi8(other.naive(), other.naive()), 8);
                        const __m128i sExtWordHighA = _mm_srai_epi16(_mm_unpackhi_epi8(_register, _register), 8);
                        const __m128i sExtWordHighB =
                            _mm_srai_epi16(_mm_unpackhi_epi8(other.naive(), other.naive()), 8);


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


        /**
         * @brief Divide contents of this register by a @p scalar.
         * @todo Update to use division by constant and update readme
         *
         * @note Register arithmetic is limited to same data types and lanes.
         * @note For integral division with different divisors @ref divReg may be
         *       faster.
         *
         * @param scalar The divisor.
         *
         * @return A new register with the quotient.
         *
         * @relatedalso divReg(const Simd128)
         * @relatedalso operator/=(const DataType)
         */
        [[nodiscard]] FALCON_INLINE Simd128 operator/(const DataType scalar) const noexcept
        {
            Simd128 divisor;
            divisor.broadcast(scalar);
            return divReg(divisor);
        }


        /**
         * @brief Divide contents of this register by a @p scalar in-place.
         * @todo Update to use division by constant and update readme
         *
         * @note Register arithmetic is limited to same data types and lanes.
         * @note For integral division with different divisors @ref divReg may be
         *       faster.
         *
         * @param scalar The divisor.
         *
         * @return A reference to the this register with products.
         *
         * @relatedalso divReg(const Simd128)
         * @relatedalso operator/(const DataType)
         */
        FALCON_INLINE Simd128& operator/=(const DataType scalar) noexcept
        {
            *this = *this / scalar;
            return *this;
        }

        // TODO: Move arithmetic ops to inl file and mark as constexpr


        // TODO: Add masked variants comparison AVX512(__mmask) and emulate


        ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        ///   COMPARISON/EQUALITY
        ///+=+=+=+=+=+=+=+=+=+=+=+=+=

        [[nodiscard]] constexpr Simd128 operator==(Simd128 other) const noexcept;

        [[nodiscard]] constexpr Simd128 operator!=(Simd128 other) const noexcept;

        [[nodiscard]] constexpr Simd128 operator>(Simd128 other) const noexcept;

        // A >= B => !(A < B) same as (A > B) | (A == B) but saves a lot of cpu cycles.
        [[nodiscard]] constexpr Simd128 operator>=(Simd128 other) const noexcept;

        // A < B => B > A
        [[nodiscard]] constexpr Simd128 operator<(Simd128 other) const noexcept;

        // A <= B => ~(A > B)
        [[nodiscard]] constexpr Simd128 operator<=(Simd128 other) const noexcept;


        ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        ///   MASKING/BLENDING
        ///+=+=+=+=+=+=+=+=+=+=+=+=+=

        /**
         * @brief Selectively blend values from this register and @p other using the @p mask.
         *
         * @code
         * // Masking sample
         * this  -> 0x ff 23 15 81
         * other -> 0x 32 3f ed 55
         * mask  -> 0x ff 00 ff 00
         * ret   -> 0x 32 23 ed 81
         * @endcode
         *
         * @param other The register whose values are selected when mask is 0b11..11 or 0xf..f.
         * @param mask  The mask to use for blending.
         *
         * @return Return a new register with blended values.
         */
        constexpr Simd128 blend(Simd128 other, Simd128 mask) const noexcept;

        /// TODO: Add tests for these ctor and getter
        /// TODO: Add test for naive
        /// @brief Get the internal register used by Simd128
        FALCON_INLINE constexpr simd::internal::SSERegister_t<DataType> naive() const noexcept { return _register; }

        // template <typename... Args>
        // FALCON_INLINE constexpr explicit set(Args... data) const noexcept; // Analogous to setting

        /// Given for completion sake
        /// Note: Each lane is considered the native width of the datatype
        /// The operation will get the data, mutate it and set it into register, which can be expensive
        /// so it highly recommended to not use this operation
        /// TODO: Implementation Later
        /// TODO: Add constexpr variant to get (useful for .x, .y, ...)
        // FALCON_INLINE constexpr setAt(size_t index, const DataType data) const noexcept;
        //
        // FALCON_INLINE constexpr getAt(size_t index) const noexcept;

    private:
        simd::internal::SSERegister_t<DataType> _register;
    };


} // namespace falcon

#include "Simd128SSE.inl"
