#pragma once
/**
 * @file Simd128.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 13, 2026
 *
 * @brief Platform and Type agnostic 128-Bit Register.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "falcon_simd/FalconSimd.h"

#include <concepts>

/**
 * @addtogroup Falcon_SIMD_128
 * @{
 */

namespace falcon
{

    template <typename SIMDReg, typename T>
    concept IsSIMDLoadable = requires(SIMDReg reg, T* buffer) {
        // { reg.load(buffer) };
        // { reg.store() } -> std::same_as<T*>;
        { SIMDReg(buffer) };
    };


    /// Primary Template for Simd128
    template <SimdBackend, typename, size_t>
    struct Simd128;

    // static_assert(IsSIMDLoadable<Simd128_t<float>, float> == true);
} // namespace falcon

#if defined(FALCON_ENABLE_SSE2) || defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_AVX) ||                        \
    defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX10)
    #include "impl/Simd128SSE.tpp"
#endif

namespace falcon
{

#if defined(FALCON_ENABLE_SSE2) || defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_AVX) ||                        \
    defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX10)
    template <typename DataType, size_t Lane>
    using Simd128_t = Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>;
#endif
} // namespace falcon

/** @} */
