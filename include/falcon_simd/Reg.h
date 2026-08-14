#pragma once
/**
 * @file Simd.h
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
#include <type_traits>
// TODO: REMOVE FILE
// #define FALCON_ENABLE_AVX512
// #define FALCON_ENABLE_NEON
#define FALCON_ENABLE_SSE2
#if defined(FALCON_ENABLE_SSE2) || defined(FALCON_ENABLE_SSE4)
    #include <immintrin.h>

template <typename T, size_t BusWidth>
struct RegType
{
    static_assert(BusWidth > 0 && BusWidth % 128 == 0 && BusWidth <= 512,
                  "Invalid Width for Register. Must be 128, 256, 512");
    using type = std::conditional_t<std::is_same_v<T, double>, __m128,
                                    std::conditional_t<std::is_same_v<T, float>, __m128, __m128i>>;
};

#elif defined(FALCON_ENABLE_AVX) || defined(FALCON_ENABLE_AVX2)
    #include <immintrin.h>

template <typename T, size_t BusWidth>
struct RegType
{
    static_assert(BusWidth > 0 && BusWidth % 128 == 0 && BusWidth <= 512,
                  "Invalid width for Register. Must be 128, 256, 512");
    using type = std::conditional_t<std::is_same_v<T, double>, __m128d,
                                    std::conditional_t<std::is_same_v<T, float>, __m128, __m128i>>;
};

template <typename T>
struct RegType<T, 256>
{
    using type = std::conditional_t<std::is_same_v<T, double>, __m256d,
                                    std::conditional_t<std::is_same_v<T, float>, __m256, __m256i>>;
};

template <typename T>
struct RegType<T, 512>
{
    using type = std::conditional_t<std::is_same_v<T, double>, __m256d,
                                    std::conditional_t<std::is_same_v<T, float>, __m256, __m256i>>;
};

#elif defined(FALCON_ENABLE_AVX512)

    #include <immintrin.h>

template <typename T, size_t BusWidth>
struct RegType
{
    static_assert(BusWidth > 0 && BusWidth % 128 == 0 && BusWidth <= 512,
                  "Invalid width for Register. Must be 128, 256, 512");
    using type = std::conditional_t<std::is_same_v<T, double>, __m128d,
                                    std::conditional_t<std::is_same_v<T, float>, __m128, __m128i>>;
};

template <typename T>
struct RegType<T, 256>
{
    using type = std::conditional_t<std::is_same_v<T, double>, __m256d,
                                    std::conditional_t<std::is_same_v<T, float>, __m256, __m256i>>;
};

template <typename T>
struct RegType<T, 512>
{
    using type = std::conditional_t<std::is_same_v<T, double>, __m512,
                                    std::conditional_t<std::is_same_v<T, float>, __m512, __m512i>>;
};

#elif defined(FALCON_ENABLE_AVX10)
// TODO: Types
#elif defined(FALCON_ENABLE_NEON)
// TODO: Types
// template <typename T, size_t BusWidth>
// struct RegType
// {
//     static_assert(BusWidth > 0 && BusWidth % 128 == 0 && BusWidth <= 512,
//                   "Invalid width for Register. Must be 128, 256, 512");
//     using type = std::conditional_t<std::is_same_v<T, double>, __m128d,
//                                     std::conditional_t<std::is_same_v<T, float>, __m128, __m128i>>;
// };
#elif defined(FALCON_ENABLE_SVE)
// TODO: Types
#else
    #include <array>
template <typename T, size_t BusWidth>
struct RegType
{
    static_assert(BusWidth > 0 && BusWidth % 128 == 0 && BusWidth <= 512,
                  "Invalid width for Register. Must be 128, 256, 512");
    using type = std::array<T, BusWidth / sizeof(T)>;
};
#endif
