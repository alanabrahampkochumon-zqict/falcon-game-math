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


#include <concepts>
/**
 * @addtogroup Falcon_SIMD_128
 * @{
 */

// TODO: REMOVE EXPLORATION CONCEPT BASED INHERITANCE
template <typename T, typename Scalar>
concept Simd128C = requires(T t, Scalar s) {
    { T::load(t) } -> std::same_as<T>;
    { t.store() } -> std::same_as<Scalar*>;
};


void doSomething(Simd128C data)
{
    Simd128C<int, int>::load(0);
}

namespace falcon
{

    template <typename T>
    concept RegType = requires(T t) {
        { T::type };
    };

    template <typename T>
    struct Simd128
    {
        RegType<T>::type _reg;

        static Simd128 load(T* buffer);

        T* store(Simd128 simd);

        // zero
        // set_zero
        // set_all
        // set(
        // operator+
        // operator-
    };

} // namespace falcon

#include "impl/Simd128AVX2.tpp"

/** @} */
