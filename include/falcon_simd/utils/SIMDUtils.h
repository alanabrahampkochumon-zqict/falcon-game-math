#pragma once
/**
 * @file SIMDUtils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief SIMD utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "TypeTraits.h"

#include <algorithm>
#include <bit>
#include <cstddef>
#include <type_traits>

namespace falcon::simd
{
    struct PackingParams
    {
        size_t alignedByteSize;
        size_t padding;
        size_t packedRegisterWidth;
        size_t registerCount;
    };

    /**
     * @brief Calculate the aligned Byte Size, padding, packed register width, and number of registers required to store
     *        the given bytes, with a given alignment.
     *
     * @param totalByteSize The total unaligned byte size.
     * @param maxAlignAs    The maximum possible alignment for a given CPU architecture.
     *                      **16 for SSE, 32 for AVX and AVX2, and 64 for AVX512**
     *
     * @return The aligned byte size, additional required padding, target register width,
     *         and number of registers required to pack the given bytes.
     */
    constexpr PackingParams calculatePackedSize(const size_t totalByteSize, const size_t maxAlignAs)
    {
        if (totalByteSize < 16)
        {
            return PackingParams{ 16, 16 - totalByteSize, 16, 1 };
        }

        const size_t packedSize           = std::bit_ceil(totalByteSize);
        const size_t optimalRegisterWidth = std::min(packedSize, maxAlignAs);
        const size_t numRegisters         = packedSize / optimalRegisterWidth;

        return PackingParams{ packedSize, packedSize - totalByteSize, optimalRegisterWidth, numRegisters };
    }


    // TODO: Add tests
    template <typename T>
    constexpr T getAllOnes()
    {
        if constexpr (std::is_integral_v<T>)
        {
            return static_cast<T>(-1);
        }
        else if constexpr (sizeof(T) == 4)
        {
            return std::bit_cast<T>(0xFFFFFFFF);
        }
        else if constexpr (sizeof(T) == 8)
        {
            return std::bit_cast<T>(0xFFFFFFFFFFFFFFFF);
        }
        else
        {
            return 1; // Shouldn't hit this path.
        }
    }



    /**
     * @brief Create a blend mask for 2 lane register selection.
     *
     * @note Mask fills from LSB(Least Significant Bit) to MSB (Most Significant Bit).
     *       The first bool translates to the lower n-bits.
     *
     * @code
     * // int32_t x 4(lane) mask.
     * const auto mask = makeBlendMask32<true, false, true, false>();
     * // 0b11111111000000001111111100000000 or 0xFF00FF00
     * @endcode
     *
     * @return BlendMask with each 16-bits as 0b111..111 if s<n> is true and 0 otherwise.
     */
    template <bool... Mask>
        requires(std::has_single_bit(sizeof...(Mask)) && sizeof...(Mask) > 0)
    constexpr BlendMask32_t makeBlendMask32() noexcept
    {
        constexpr bool maskArr[]{ Mask... };
        constexpr auto paramCount = sizeof...(Mask);

        // Creates the mask with appropriate shifts.
        // We create a mask by selecting an appropriate mask (0b11..11 if true, 0b0 otherwise)
        // and shifting by width required per mask for saturating the full 32-bits.
        // Eg: For a 4 lane register mask, we with the following mask <true, false, true, true>.
        //     That will expand into:
        //     0b11111111 << (0 * 8) | 0b00000000 << (1 * 8) | ob11111111 << (2 * 8) << | 0b00000000 << (3 * 8)
        //     Which will return 0b11111111000000001111111100000000
        auto getMask = [&]<size_t... Indices>(std::index_sequence<Indices...>) {
            if constexpr (paramCount == 32)
            {
                // True Mask 0b1
                return (((maskArr[Indices] ? 0x1 : 0x0) << Indices) | ...);
            }
            else if constexpr (paramCount == 16)
            {
                // True Mask 0b11
                return (((maskArr[Indices] ? 0x3 : 0x0) << (Indices * 2)) | ...);
            }
            else if constexpr (paramCount == 8)
            {
                // True Mask 0b1111
                return (((maskArr[Indices] ? 0xF : 0x0) << (Indices * 4)) | ...);
            }
            else if constexpr (paramCount == 4)
            {
                // True Mask 0b11111111
                return (((maskArr[Indices] ? 0xFF : 0x00) << (Indices * 8)) | ...);
            }
            else if constexpr (paramCount == 2)
            {
                // True Mask 0b1111111111111111
                return (((maskArr[Indices] ? 0xFFFF : 0x0000) << (Indices * 16)) | ...);
            }
            else
            {
                return 0;
            }
        };
        return getMask(std::make_index_sequence<paramCount>());
    }

    // TODO: Make it more generalized later(2, 4, 8, 16...) and various types.

    constexpr uint128_t expandFourFold(BlendMask32_t mask)
    {
        auto expandByFour = [&]<size_t... Index>(size_t Offset, std::index_sequence<Index...>) -> size_t {
            constexpr size_t trueMask  = 0b1111ULL;
            constexpr size_t falseMask = 0b0000ULL;
#define __FLCN_EXP4_MASKED_EXTRACT (0b1ULL << (Index + Offset))
            return ((((mask & __FLCN_EXP4_MASKED_EXTRACT) == __FLCN_EXP4_MASKED_EXTRACT ? trueMask : falseMask)
                     << (Index * 4)) |
                    ...);
#undef __FLCN_EXP4_MASKED_EXTRACT
        };
        return uint128_t{ .upper = expandByFour(16, std::make_index_sequence<16>{}),
                          .lower = expandByFour(0, std::make_index_sequence<16>{}) };
    }


} // namespace falcon::simd
