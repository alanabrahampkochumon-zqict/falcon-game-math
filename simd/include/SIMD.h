#pragma once
/**
 * @file SIMD.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Architecture-agnostic SIMD abstractions and feature detection macros
 *
 * @par Configuration
 * Define FORCE_SSE to turn on SSE, even if hardware supports newer instructions
 * Similar options include FORCE_AVX512, FORCE_AVX2, FORCE_SSE, and FORCE_SCALAR which will completely turn off SIMD.
 * @note Even if flags are specified, it will only default to the max that the CPU architecture supports
 *
 * @par Compiler note
 * Make sure compiler flags are turned on:
 * -mavx2 (GCC/Clang) or /arch:AVX2(MSVC) for turning on AVX2 support
 * -mavx512 (GCC/Clang) or /arch:AVX512 (MSVC) for turning on AVX512 supported.
 * @note If you compile using the supplied CMakeList.txt, then, it will turn on the flag supported by the CPU.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDUtils.h"

#include <concepts>
#include <cstddef>
#include <immintrin.h>


/**************************************
 *                                    *
 *            PREPROCESSORS           *
 *                                    *
 **************************************/
#if defined(FORCE_AVX512) && defined(__AVX512F__)
    #define FALCON_AVX512_SUPPORTED
#endif

#if (defined(FORCE_AVX2) && defined(__AVX2__)) || defined(FALCON_AVX512_SUPPORTED)
    #define FALCON_AVX2_SUPPORTED
#endif

#if (defined(FORCE_AVX) && defined(__AVX__)) || defined(FALCON_AVX2_SUPPORTED)
    #define FALCON_AVX_SUPPORTED
#endif

#if (defined(FORCE_SSE) && (defined(__SSE__) || defined(__SSE4_1__) || defined(_M_X64))) ||                            \
    defined(FALCON_AVX_SUPPORTED)
    #define FALCON_SSE_SUPPORTED
#endif

#if !(defined(FORCE_SCALAR)) && defined(FALCON_SSE_SUPPORTED)
    #define FALCON_SIMD_SUPPORTED
#endif


#if !defined(FORCE_AVX512) && !defined(FORCE_AVX2) && !defined(FORCE_AVX) && !defined(FORCE_SSE) &&                    \
    !defined(FORCE_SCALAR)
    #ifdef __AVX512F__
        #define FALCON_AVX512_SUPPORTED
    #endif

    #ifdef __AVX2__
        #define FALCON_AVX2_SUPPORTED
    #endif

    #ifdef __AVX__
        #define FALCON_AVX_SUPPORTED
    #endif

    #if defined(__SSE__) || defined(__SSE4_1__) || defined(_M_X64)
        #define FALCON_SSE_SUPPORTED
        #define FALCON_SIMD_SUPPORTED // If at least SSE is supported, then SIMD will be available.
    #endif
#endif

#ifdef FALCON_AVX512_SUPPORTED
    #define MAX_HARDWARE_ALIGNMENT = 64;
#elif defined(FALCON_AVX2_SUPPORTED) || defined(FALCON_AVX_SUPPORTED)
    #define MAX_HARDWARE_ALIGNMENT = 32;
#elif defined(FALCON_SSE_SUPPORTED)
    #define MAX_HARDWARE_ALIGNMENT = 16;
#else
    #define MAX_HARDWARE_ALIGNMENT = 0;
#endif



/**************************************
 *                                    *
 *           SIMD Registers           *
 *                                    *
 **************************************/
namespace falcon::simd
{
    template <typename T, std::size_t RegWidth>
    struct RegisterMap;


    template <>
    struct RegisterMap<float, 16>
    {
        using type = __m128;
    };

    template <>
    struct RegisterMap<double, 16>
    {
        using type = __m128d;
    };

    template <std::integral T>
    struct RegisterMap<T, 16>
    {
        using type = __m128i;
    };

    template <>
    struct RegisterMap<float, 32>
    {
        using type = __m256;
    };

    template <>
    struct RegisterMap<double, 32>
    {
        using type = __m256d;
    };

    template <std::integral T>
    struct RegisterMap<T, 32>
    {
        using type = __m256i;
    };

    template <>
    struct RegisterMap<float, 64>
    {
        using type = __m512;
    };

    template <>
    struct RegisterMap<double, 64>
    {
        using type = __m512d;
    };

    template <std::integral T>
    struct RegisterMap<T, 64>
    {
        using type = __m512i;
    };

    #if defined(MAX_ALIGNMENT) && MAX_ALIGNMENT > 0
        const PackingParams packingParams = calculatePackedSize(TotalBytes, MAX_ALIGNMENT);
    #endif



} // namespace falcon::simd