#pragma once
/**
 * @file MathTraits.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Concepts for Arithmetic, StrictArithmetic, Matrix, and Vector. Also contains EPSILONs for floats and doubles.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <concepts>
#include <cstddef>
#include <type_traits>


namespace fgm
{

    /**************************************
     *                                    *
     *         ARITHMETIC CONCEPTS        *
     *                                    *
     **************************************/

    template <typename T>
    concept Arithmetic = (std::integral<T> || std::floating_point<T>);

    // A stricter concept that doesn't allow bool as datatype
    // Use for operations like +, -, *, / etc.. which are not defined for bool.
    template <typename T>
    concept StrictArithmetic = Arithmetic<T> && !std::is_same_v<T, bool>;

    template <typename T>
    concept weak_arithmetic = std::is_arithmetic_v<std::decay_t<T>>;


    /**************************************
     *                                    *
     *          GAME MATH CONCEPTS        *
     *                                    *
     **************************************/

    /**
     * `Vector` requires a value_type, dimension, [] accessor, and its value_type needs to be `Arithmetic`.
     */
    template <typename T>
    concept Vector = requires(T v, std::size_t i) {
        typename T::value_type;
        { T::dimension } -> std::same_as<const std::size_t&>;
        { v[i] } -> std::convertible_to<typename T::value_type>;
    } && Arithmetic<typename T::value_type>;


    /**
     * @brief `Matrix` requires a value_type, rows, columns, [] accessor, (r, c) accessor, and its value_type needs to
     * be `Arithmetic`.
     */
    template <typename T>
    concept Matrix = requires(T matrix, std::size_t r, std::size_t c) {
        typename T::value_type;
        { T::rows } -> std::same_as<const std::size_t&>;
        { T::columns } -> std::same_as<const std::size_t&>;
        { matrix(r, c) } -> std::convertible_to<typename T::value_type>;
        { matrix[c] };
    } && Arithmetic<typename T::value_type>;


    /**
     * @brief Custom typedef used for vector magnitudes as integral magnitudes can cause imprecision.
     */
    template <typename T>
        requires Arithmetic<T>
    using Magnitude = std::conditional_t<std::is_same_v<T, float>, float, double>;


    /**************************************
     *                                    *
     *            CUSTOM EPSILON          *
     *                                    *
     **************************************/

    inline constexpr double FLOAT_EPSILON = 1e-5;
    inline constexpr double DOUBLE_EPSILON = 1e-12;


} // namespace fgm