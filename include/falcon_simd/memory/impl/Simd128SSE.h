#pragma once
/**
 * @file Simd128SSE.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 13, 2026
 *
 * @brief SSE2 implementation for Simd128.
 *
 * @details 128-bit SIMD register wrapper for x64-based systems.
 *          Support for faster instruction in higher instruction sets like AVX2 or AVX512
 *          is checked inside implementation, and this only common interface for 128-bit
 *          register for the x86-64 ISA. Note, there is no distinction made between SSE3,
 *          SSE4.1, SSE4.2, and the library expects a baseline of SSE4.2 but provides
 *          SSE2 implementation for backwards-compatibility.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../RegisterTraits.h"
#include "falcon_core/Preprocessors.h"
#include "falcon_core/traits/TypeHelpers.h"
#include "falcon_simd/utils/TypeTraits.h"

#include <array>
#include <bit>
#include <emmintrin.h>
#include <immintrin.h>
#include <span>
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


        constexpr explicit Simd128() = default;

        /**
         * @brief Initialize a 128-bit SIMD register with @p data.
         *
         * @tparam Args The numeric type of @p data. Must match the register's datatype.
         * @param data  The values to initialize the register with.
         *
         * @note If only a single argument is provided then the value will be broadcasted across the entire register.
         *       The number of values provided must be less than or equal to the total register lanes. If
         *       the number of values is less than the lanes, values will be inserted into the lower lanes,
         *       and rest filled with zeroes.
         */
        template <typename... Args>
            requires(SimdSafeConvertible<Args, DataType> && ...)
        constexpr explicit Simd128(Args... data) noexcept;


        /**
         * @brief Initialize a 128-bit SIMD register with values from a std::container(std::array, std::vector).
         *
         * @param values The values to fill the register with.
         *
         * @warning The container must be aligned to 16-byte boundary. For unaligned data,
         *          use @ref load to load data manually.
         */
        constexpr explicit Simd128(std::span<const DataType> values) noexcept;


        /**
         * @brief Initialize a 128-bit SIMD register with a raw memory buffer.
         *
         * @note Passing in a buffer with allocated size less than @p Lane * @p sizeof(DataType)
         *       can cause segmentation faults.
         *
         * @param buffer The starting address of the values to fill the register with.
         *
         * @warning @p buffer must be aligned to 16-byte boundary. For unaligned data,
         *          use @ref load to load data manually.
         */
        constexpr explicit Simd128(const DataType* buffer) noexcept;


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
        constexpr void loadAligned(const DataType* data) noexcept;


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
        constexpr void load(const DataType* data) noexcept;


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
        constexpr void store(DataType* pBuffer) const noexcept;


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
        constexpr void storeAligned(DataType* pBuffer) const noexcept;

        /**
         * Get the value at @p index.
         *
         * @param index The index of the register. Must be between 0 and Lane - 1.
         *
         * @note For indices known at compile-time, use get<Index>() as it is faster
         *       due to the availability of direct hardware intrinsic.
         *
         * @return The value at index [read-only].
         *
         * @relatedalso setAt(size_t, DataType)
         * @relatedalso getAt<size_t>()
         * @relatedalso setAt<size_t>(DataType)
         */
        [[nodiscard]] constexpr DataType getAt(size_t index) const noexcept;
        // TODO: Migrate runtime getAt to use a switch expression if it's faster

        /**
         * Set the value at @p index to @p value.
         *
         * @param index The index of the register. Must be between 0 and Lane - 1.
         * @param value The value to set.
         *
         * @note For indices known at compile-time, use set<Index>(value) as it is faster
         *       due to the availability of direct hardware intrinsic.
         *
         * @relatedalso getAt(size_t)
         * @relatedalso getAt<size_t>()
         * @relatedalso setAt<size_t>(DataType)
         */
        constexpr void setAt(size_t index, DataType value) noexcept;

        /**
         * Get the value at @p index.
         *
         * @tparam Index The index of the register. Must be between 0 and Lane - 1.
         *
         * @note For indices known at compile-time, use get<Index>() as it is faster
         *       due to the availability of direct hardware intrinsic.
         *
         * @return The value at index [read-only].
         *
         * @relatedalso getAt(size_t)
         * @relatedalso setAt(size_t, DataType)
         * @relatedalso setAt<size_t>(DataType)
         */
        template <size_t Index>
            requires(Index < Lane)
        [[nodiscard]] constexpr DataType getAt() const noexcept;


        ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        ///    BITWISE OPERATIONS
        ///+=+=+=+=+=+=+=+=+=+=+=+=+=

        /// @brief Perform bitwise NOT on the entire register.
        [[nodiscard]] constexpr Simd128 operator~() const noexcept;

        /// @brief Perform bitwise AND between this register and @p other.
        [[nodiscard]] constexpr Simd128 operator&(Simd128 other) const noexcept;

        /// @brief Perform bitwise OR between this register and @p other.
        [[nodiscard]] constexpr Simd128 operator|(Simd128 other) const noexcept;

        /// @brief Perform bitwise OR between this register and @p other.
        [[nodiscard]] constexpr Simd128 operator^(Simd128 other) const noexcept;

        /// @brief Perform a bitwise `and_not` combination between this register and @p other.
        /// @note  Faster than manually doing (~RegA & RegB) since this executes only a single SIMD instruction.
        [[nodiscard]] constexpr Simd128 andNot(Simd128 other) const noexcept;


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
        [[nodiscard]] constexpr Simd128 operator+(Simd128 other) const noexcept;


        /**
         * @brief Add contents of this register with @p other in-place.
         *
         * @note Register arithmetic to limited is same data types and lanes.
         *
         * @param other The register to add.
         *
         * @return A reference to the this register with sum.
         */
        constexpr Simd128& operator+=(Simd128 other) noexcept;


        /**
         * @brief Subtract two registers and return a new register.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to subtract.
         * @return A new register with the difference between elements of this register and @p other.
         */
        [[nodiscard]] constexpr Simd128 operator-(Simd128 other) const noexcept;


        /**
         * @brief Subtract contents of this register from @p other in-place.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to subtract.
         *
         * @return A reference to the this register with difference.
         */
        constexpr Simd128& operator-=(Simd128 other) noexcept;


        /**
         * @brief Multiply two registers and return a new register.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to multiply.
         * @return A new register with the product of elements of this register and @p other.
         */
        [[nodiscard]] constexpr Simd128 operator*(Simd128 other) const noexcept;


        /**
         * @brief Multiply contents of this register with @p other in-place.
         *
         * @note Register arithmetic is limited to same data types and lanes.
         *
         * @param other The register to multiply.
         *
         * @return A reference to the this register with products.
         */
        constexpr Simd128& operator*=(Simd128 other) noexcept;


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
        [[nodiscard]] constexpr Simd128 divReg(Simd128 other) const noexcept;


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
        [[nodiscard]] constexpr Simd128 operator/(DataType scalar) const noexcept;


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
        constexpr Simd128& operator/=(DataType scalar) noexcept;


        // TODO: Add masked variants comparison AVX512(__mmask) and emulate


        ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        ///   COMPARISON/EQUALITY
        ///+=+=+=+=+=+=+=+=+=+=+=+=+=

        [[nodiscard]] constexpr Simd128 operator==(Simd128 other) const noexcept;

        [[nodiscard]] constexpr Simd128 operator!=(Simd128 other) const noexcept;

        [[nodiscard]] constexpr Simd128 operator>(Simd128 other) const noexcept;

        [[nodiscard]] constexpr Simd128 operator>=(Simd128 other) const noexcept;

        [[nodiscard]] constexpr Simd128 operator<(Simd128 other) const noexcept;

        [[nodiscard]] constexpr Simd128 operator<=(Simd128 other) const noexcept;

        /**
         * @brief Perform a logical left shift on this register by @p count.
         *
         * @warning If @p count is known at compile time then it is recommended to use
         *          @ref shiftLeft<uint32_t> as it is faster.
         *
         * @return A new 128-bit register with shifted values.
         *
         * @relatedalso operator<<=(uint32_t)
         * @relatedalso operator>>(uint32_t)
         * @relatedalso operator>>=(uint32_t)
         * @relatedalso shiftRightLogical(uint32_t)
         * @relatedalso shiftLeft<uint32_t>()
         * @relatedalso shiftRightArithmetic<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        [[nodiscard]] constexpr Simd128 operator<<(uint32_t count) const noexcept;


        /**
         * @brief Perform a logical left shift on this register by @p count in-place.
         *
         * @warning If @p count is known at compile time then it is recommended to use
         *          @ref shiftLeft<uint32_t> as it is faster.
         *
         * @return A reference to this register.
         *
         * @relatedalso operator<<(uint32_t)
         * @relatedalso operator>>(uint32_t)
         * @relatedalso operator>>=(uint32_t)
         * @relatedalso shiftRightLogical(uint32_t)
         * @relatedalso shiftLeft<uint32_t>()
         * @relatedalso shiftRightArithmetic<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        constexpr Simd128& operator<<=(uint32_t count) noexcept;


        /**
         * @brief Perform a arithmetic/logical(type dependent) right shift by @p count and return a new register.
         *
         * @warning If @p count is known at compile time then it is recommended to use @ref shiftRight<Count> as
         *          it is faster.
         *
         * @return A new 128-bit register with shifted values.
         *
         * @relatedalso operator<<(uint32_t)
         * @relatedalso operator<<=(uint32_t)
         * @relatedalso operator>>=(uint32_t)
         * @relatedalso shiftRightLogical(uint32_t)
         * @relatedalso shiftLeft<uint32_t>()
         * @relatedalso shiftRightArithmetic<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        [[nodiscard]] constexpr Simd128 operator>>(uint32_t count) const noexcept;


        /**
         * @brief Perform a arithmetic/logical(type dependent) right shift on this register by @p count.
         *
         * @warning If @p count is known at compile time then it is recommended to use
         *          @ref shiftRightArithmetic<uint32_t> as it is faster.
         *
         * @return A reference to this register.
         *
         * @relatedalso operator<<(uint32_t)
         * @relatedalso operator<<=(uint32_t)
         * @relatedalso operator>>(uint32_t)
         * @relatedalso shiftRightLogical(uint32_t)
         * @relatedalso shiftLeft<uint32_t>()
         * @relatedalso shiftRightArithmetic<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        constexpr Simd128& operator>>=(uint32_t count) noexcept;


        /**
         * @brief Perform a logical right shift (zero extension) on this register and return a new register.
         *
         * @warning If @p count is known at compile time then it is recommended to use
         *          @ref shiftRightLogical<uint32_t> as it is faster.
         *
         * @return A new 128-bit register with shifted values.
         *
         * @relatedalso operator<<(uint32_t)
         * @relatedalso operator<<=(uint32_t)
         * @relatedalso operator>>(uint32_t)
         * @relatedalso operator>>=(uint32_t)
         * @relatedalso shiftLeft<uint32_t>()
         * @relatedalso shiftRightArithmetic<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        [[nodiscard]] constexpr Simd128 shiftRightLogical(uint32_t count) const noexcept;


        /**
         * @brief Perform a logical left shift on this register by a compile time constant, @p Count.
         *
         * @tparam Count The shift amount.
         *
         * @relatedalso operator<<(uint32_t)
         * @relatedalso operator<<=(uint32_t)
         * @relatedalso operator>>(uint32_t)
         * @relatedalso operator>>=(uint32_t)
         * @relatedalso shiftRightLogical(uint32_t)
         * @relatedalso shiftRightArithmetic<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        template <uint32_t Count>
        [[nodiscard]] constexpr Simd128 shiftLeft() const noexcept;


        /**
         * @brief Perform a arithmetic right shift on this register by a compile time constant, @p Count.
         *
         * @tparam Count The shift amount.
         *
         * @relatedalso operator<<(uint32_t)
         * @relatedalso operator<<=(uint32_t)
         * @relatedalso operator>>(uint32_t)
         * @relatedalso operator>>=(uint32_t)
         * @relatedalso shiftRightLogical(uint32_t)
         * @relatedalso shiftLeft<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        template <uint32_t Count>
        [[nodiscard]] constexpr Simd128 shiftRightArithmetic() const noexcept;


        /**
         * @brief Perform a logical right shift on this register by a compile time constant, @p Count.
         *
         * @tparam Count The shift amount.
         *
         * @relatedalso operator<<(uint32_t)
         * @relatedalso operator<<=(uint32_t)
         * @relatedalso operator>>(uint32_t)
         * @relatedalso operator>>=(uint32_t)
         * @relatedalso shiftRightLogical(uint32_t)
         * @relatedalso shiftLeft<uint32_t>()
         * @relatedalso shiftRightLogical<uint32_t>()
         */
        template <uint32_t Count>
        [[nodiscard]] constexpr Simd128 shiftRightLogical() const noexcept;


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

        /**
         * Shuffle the values as per given index.
         *
         * @tparam ShuffleIndex The indices to use for shuffling. Only accepts values from 0 to Lane - 1.
         *                      Must be specified from lower index to higher index,
         *                      i.e, <0, 1, 2, 3> returns the same register.
         *
         * @return A new Simd register with shuffled values.
         */
        template <uint8_t... ShuffleIndex>
        constexpr Simd128 shuffle() const noexcept;


        /// TODO: Add test for naive
        /// @brief Get the internal register used by Simd128
        FALCON_INLINE constexpr simd::internal::SSERegister_t<DataType> naive() const noexcept { return _register; }
        /// TODO: Operator* as a way to get the native register

    private:
        simd::internal::SSERegister_t<DataType> _register;

        ///+=+=+=+=+=+=+=+=+=+=+=+=+=
        ///         HELPERS
        ///+=+=+=+=+=+=+=+=+=+=+=+=+=

        /// Perform a logical right shift on the 128-bit register composed of Byte values.
        static constexpr __m128i _mm_srl_epi8_custom(__m128i reg, uint32_t count) noexcept;


        /// Perform a arithmetic right shift on the 128-bit register composed of Quad Word (64-bit integral) values.
        static constexpr __m128i _mm_sra_epi64_custom(__m128i reg, uint32_t count) noexcept;


        /// @brief Perform a logical left shift on the 128-bit register composed of Byte values by a constant known
        ///        at compile time.
        /// @tparam Count The shift amount.
        template <uint32_t Count>
        static constexpr __m128i _mm_slli_epi8_custom(__m128i reg) noexcept;


        /// @brief Perform a arithmetic right shift on the 128-bit register composed of Quad Word (64-bit integral)
        /// values
        ///        by a constant known at compile time.
        /// @tparam Count The shift amount.
        template <uint32_t Count>
        static constexpr __m128i _mm_srai_epi64_custom(__m128i reg) noexcept;


        /// @brief Perform a logical left right on the 128-bit register composed of Byte values by a constant known
        ///        at compile time.
        /// @tparam Count The shift amount.
        template <uint32_t Count>
        static constexpr __m128i _mm_srli_epi8_custom(__m128i reg) noexcept;


        /// @brief Perform a arithmetic left right on the 128-bit register composed of Byte values by a constant known
        ///        at compile time.
        /// @tparam Count The shift amount.
        template <uint32_t Count>
        static constexpr __m128i _mm_srai_epi8_custom(__m128i reg) noexcept;
    };



} // namespace falcon

#include "Simd128SSE.inl"
