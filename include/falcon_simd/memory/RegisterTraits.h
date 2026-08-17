#pragma once
/**
 * @file RegisterTraits.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 17, 2026
 *
 * @brief Wrappers for SIMD register instrinsics exposed by C++.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



/**
 * @addtogroup Falcon_Reg
 * @{
 */

namespace falcon::simd::internal
{
#if defined(FALCON_PLATFORM_X86)
    #include <emmintrin.h>
    #include <immintrin.h>

    /**
     * @brief Defines a SSE(1/2/3/4) Register(128-bit) for a given data type.
     *        @note Use @ref SSERegister_t<type> for a shorter syntax.
     */
    template <typename>
    struct SSERegister
    {
        using Type = __m128i;
    };

    template <>
    struct SSERegister<float>
    {
        using Type = __m128;
    };

    template <>
    struct SSERegister<double>
    {
        using Type = __m128d;
    };

    template <typename T>
    using SSERegister_t = SSERegister<T>::Type;


    /**
     * @brief Defines an AVX(2) Register(256-bit) for a given data type.
     *        @note Use @ref AVXRegister_t<type> for a shorter syntax.
     */
    template <typename>
    struct AVXRegister
    {
        using Type = __m256i;
    };

    template <>
    struct AVXRegister<float>
    {
        using Type = __m256;
    };

    template <>
    struct AVXRegister<double>
    {
        using Type = __m256d;
    };

    template <typename T>
    using AVXRegister_t = AVXRegister<T>::Type;



    /**
     * @brief Defines an AVX512 Register(512-bit) for a given data type.
     *        @note Use @ref AVX512Register_t<type> for a shorter syntax.
     */
    template <typename>
    struct AVX512Register
    {
        using Type = __m256i;
    };

    template <>
    struct AVX512Register<float>
    {
        using Type = __m256;
    };

    template <>
    struct AVX512Register<double>
    {
        using Type = __m256d;
    };

    template <typename T>
    using AVX512Register_t = AVX512Register<T>::Type;

#elif defined(FALCON_PLATFORM_ARM)
    // TODO: Add Neon Intrinsics here
#endif
} // namespace falcon::simd::internal

/** @} */
