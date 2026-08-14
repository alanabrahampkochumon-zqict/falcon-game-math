#pragma once
/**
 * @file Simd128AVX2.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 13, 2026
 *
 * @brief AVX2 implementation for Simd128.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <xmmintrin.h>
namespace falcon
{
    template <typename T>
    struct Register
    {
        using type = __m128;
    };
    template <typename T>
    Simd128<T> Simd128<T>::load(T* buffer)
    {
        Simd128<T> data;
        data._reg = _mm_load_ps(buffer);
        return data;
    }

    template <typename T>
    T* Simd128<T>::store(Simd128 simd)
    {}
} // namespace falcon
