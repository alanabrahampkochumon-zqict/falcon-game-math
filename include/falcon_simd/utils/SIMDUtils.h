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


#include <algorithm>
#include <bit>
#include <type_traits>
#include <cstddef>

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


} // namespace falcon::simd
