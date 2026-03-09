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


#include <bit>
#include <cstddef>


namespace falcon::simd
{
    struct PackingParams
    {
        std::size_t alignedByteSize;
        std::size_t padding;
        std::size_t packedRegisterWidth;
        std::size_t registerCount;
    };

    /**
     * A calculator function that gives Aligned Byte Size, Padding, Packed Register Width, and Register Count
     * when provided with an unaligned byteSize and maximumAlignment possible.
     * @param totalByteSize Total unaligned byte size.
     * @param maxAlignAs Max possible alignment for a given CPU architecture. 16 for SSE, 32 for AVX and AVX2, and 64
     * for AVX512
     * @return PackedSize containing alignedByteSize, padding, register width and register count.
     */
    constexpr PackingParams calculatePackedSize(std::size_t totalByteSize, std::size_t maxAlignAs)
    {
        if (totalByteSize < 16)
            return PackingParams{ 16, 16 - totalByteSize, 16, 1 };

        const std::size_t packedSize = std::bit_ceil(totalByteSize);
        const std::size_t optimalRegisterWidth = std::min(packedSize, maxAlignAs);
        const std::size_t numRegisters = packedSize / optimalRegisterWidth;

        return PackingParams{ packedSize, packedSize - totalByteSize, optimalRegisterWidth, numRegisters };
    }
} // namespace falcon::simd
