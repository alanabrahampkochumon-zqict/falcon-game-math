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

// TODO: Separate into files for concepts and traits.
namespace fgm
{

    /**
     * @addtogroup FGM_Concepts
     * @{
     */

    /**************************************
     *                                    *
     *         ARITHMETIC CONCEPTS        *
     *                                    *
     **************************************/

    /** @brief Validates that a type is a standard numeric primitive (integral or floating-point). */
    template <typename T>
    concept Arithmetic = std::integral<T> || std::floating_point<T>;


    /**
     * @brief Validates that a type is a signed numeric primitive (integral or floating-point) suitable for linear
     * algebra.
     *
     * @note Excludes `bool` type to ensure logical inversions remain separate from algebraic inversions.
     */
    template <typename T>
    concept SignedStrictArithmetic = (std::signed_integral<T> || std::floating_point<T>) && !std::is_same_v<T, bool>;


    /**
     * @brief Enforces numeric types suitable for linear algebra by explicitly excluding bool.
     *
     * @note Prevents logical types from participating in arithmetic operations like addition or division.
     */
    template <typename T>
    concept StrictArithmetic = Arithmetic<T> && !std::is_same_v<T, bool>;


    /**
     * @brief Detects arithmetic capability after stripping cv-qualifiers and references.
     * @details Uses @ref `std::decay_t` to ensure const T& or T&& types are evaluated by their underlying primitive.
     */
    template <typename T>
    concept WeakArithmetic = std::is_arithmetic_v<std::decay_t<T>>;



    /**************************************
     *                                    *
     *            TYPE TRAITS             *
     *                                    *
     **************************************/

    /** @brief Centralized value promotion logic for all math types. */
    template <Arithmetic T, Arithmetic U>
    using PromoteValue_t = std::common_type_t<T, U>;



    /**************************************
     *                                    *
     *          GAME MATH CONCEPTS        *
     *                                    *
     **************************************/

    /**
     * @brief Defines the requirements for a linear algebraic vector.
     * @details Requires a value_type alias, a static dimension constant, and subscript [] access. The underlying type
     *          must satisfy @ref Arithmetic.
     */
    template <typename T>
    concept Vector = requires(T v, std::size_t i) {
        typename T::value_type;
        { T::dimension } -> std::same_as<const std::size_t&>;
        { v[i] } -> std::convertible_to<typename T::value_type>;
    } && Arithmetic<typename T::value_type>;


    /**
     * @brief Defines the structural requirements for a mathematical matrix.
     * @details Enforces a two-dimensional interface including rows and columns constants, as well as both (r, c) and
     *          [c] access patterns.
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
     * @brief Determines the optimal high-precision type for length calculations.
     * @note Automatically promotes integral types to double to prevent precision loss during square root operations.
     */
    template <typename T>
        requires Arithmetic<T>
    using Magnitude = std::conditional_t<std::is_same_v<T, float>, float, double>;



    /**************************************
     *                                    *
     *       PROMOTED TYPE ALIAS          *
     *                                    *
     **************************************/

    // Forward declarations
    template <Arithmetic T>
    struct Vector2D;

    template <Arithmetic T>
    struct Matrix2D;
    


    /** @brief Alias for @ref Vector2D with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromoteValue_t<T, U>>
    using PromotedVector2D = Vector2D<PromoteValue_t<T, U>>;


    /** @brief Alias for @ref Matrix2D with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromoteValue_t<T, U>>
    using PromotedMatrix2D = Matrix2D<PromoteValue_t<T, U>>;


    /** @brief Alias for @ref Matrix2D with a `value_type` of @ref Magnitude of the wider type. */
    template<Arithmetic T, Arithmetic U>
    using PromotedFloatMatrix2D = Matrix2D<Magnitude<std::common_type_t<T, U>>>;

    /** @} */

} // namespace fgm