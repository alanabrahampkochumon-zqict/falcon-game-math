#pragma once
/**
 * @file FalconSimd.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 13, 2026
 *
 * @brief Platform/ISA agnostic register type mappings.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */
// FALCON_ENABLE_SSE, SSE2, SSE4
// FALCON_ENABLE_AVX
// FALCON_ENABLE_AVX2
// FALCON_ENABLE_AVX512
// FALCON_ENABLE_AVX10
// FALCON_ENABLE_NEON
// FALCON_ENABLE_SVE
// FALCON_DISABLE_SIMD
// #define FALCON_ENABLE_SSE


#include "utils/Preprocessors.h"

#include <type_traits>

namespace falcon
{
    /**
     * @brief Backends Supported by Falcon SIMD.
     */
    enum class SimdBackend : uint8_t
    {
        ARCH_SSE2,
        ARCH_SSE4,
        ARCH_AVX,
        ARCH_AVX2,
        ARCH_AVX512,
        ARCH_AVX10, // TODO: Future impl
        ARCH_NEON,
        ARCH_UNKNOWN
    };

    // TODO: Test Function
    FALCON_SIMD_INLINE constexpr std::string toString(const SimdBackend backend)
    {
        switch (backend)
        {
            case SimdBackend::ARCH_SSE2:
                return "Streaming SIMD Extensions 2 (SSE2)";
            case SimdBackend::ARCH_SSE4:
                return "Streaming SIMD Extensions 4 (SSE4)";
            case SimdBackend::ARCH_AVX:
                return "Advanced Vector Extensions (AVX)";
            case SimdBackend::ARCH_AVX2:
                return "Advanced Vector Extensions 2 (AVX2)";
            case SimdBackend::ARCH_AVX512:
                return "Advanced Vector Extensions 512 (AVX512)";
            case SimdBackend::ARCH_AVX10:
                return "Advanced Vector Extensions 10 (AVX10)";
            case SimdBackend::ARCH_NEON:
                return "Arm Neon";
            default:
                return "Unsupported SIMD Instruction set";
        }
    }
} // namespace falcon


/// Switch Alignment and Backend Variable based on highest supported backend.
/// ALIGNMENT Gives the maximum alignment required.
/// CURRENT_SIMD_BACKEND The current SIMD backend used by the target application.
#if defined(FALCON_ENABLE_SSE2)

inline constexpr size_t ALIGNMENT          = 16;
inline constexpr size_t SIMD_LANE_WIDTH    = 128;
inline constexpr auto CURRENT_SIMD_BACKEND = falcon::SimdBackend::ARCH_SSE2;

#elif defined(FALCON_ENABLE_SSE4)

inline constexpr size_t ALIGNMENT          = 16;
inline constexpr size_t SIMD_LANE_WIDTH    = 128;
inline constexpr auto CURRENT_SIMD_BACKEND = falcon::SimdBackend::ARCH_SSE4;

#elif defined(FALCON_ENABLE_AVX)

inline constexpr size_t ALIGNMENT          = 32;
inline constexpr size_t SIMD_LANE_WIDTH    = 256;
inline constexpr auto CURRENT_SIMD_BACKEND = falcon::SimdBackend::ARCH_AVX;

#elif defined(FALCON_ENABLE_AVX2)

inline constexpr size_t ALIGNMENT          = 32;
inline constexpr size_t SIMD_LANE_WIDTH    = 256;
inline constexpr auto CURRENT_SIMD_BACKEND = falcon::SimdBackend::ARCH_AVX2;

#elif defined(FALCON_ENABLE_AVX512)

inline constexpr size_t ALIGNMENT          = 64;
inline constexpr size_t SIMD_LANE_WIDTH    = 512;
inline constexpr auto CURRENT_SIMD_BACKEND = falcon::SimdBackend::ARCH_AVX512;

#elif defined(FALCON_ENABLE_AVX10)

inline constexpr size_t ALIGNMENT          = 32;  // TODO: TBD
inline constexpr size_t SIMD_LANE_WIDTH    = 256; // TODO: TBD
inline constexpr auto CURRENT_SIMD_BACKEND = falcon::SimdBackend::ARCH_AVX10;

#elif defined(FALCON_ENABLE_NEON)

inline constexpr size_t ALIGNMENT          = 16;
inline constexpr size_t SIMD_LANE_WIDTH    = 128;
inline constexpr auto CURRENT_SIMD_BACKEND = falcon::SimdBackend::ARCH_NEON;

#else

inline constexpr size_t ALIGNMENT          = 16;
inline constexpr size_t SIMD_LANE_WIDTH    = 64; // GP Register Width on 64-bit machines
inline constexpr auto CURRENT_SIMD_BACKEND = falcon::SimdBackend::ARCH_UNKNOWN;

#endif


/// Library Includes
#include "memory/Simd128.h"
