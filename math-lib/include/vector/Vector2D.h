#pragma once
/**
 * @file Vector2D.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 24, 2026
 *
 * @brief Templated 2D Vector supporting integral, floating-point, and boolean types.
 *
 * @details Provides a high-performance vector implementation with SIMD acceleration
 *          and support for component-wise operations.
 *
 * @note Arithmetic operations are limited to numeric types via `StrictArithmetic` concept.
 *
 * @par Configuration
 * Define `ENABLE_FGM_SHADER_OPERATORS` to enable comparison operators (>, <, etc.).
 * Even if disabled, functional comparisons like `greaterThan()` remain available.
 * Define `FORCE_SCALAR` to turn off SIMD which is on by default on supported hardware.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "common/MathTraits.h"
#include "common/Constants.h"
#include "common/Config.h"

#include <type_traits>



namespace fgm
{
    template <Arithmetic T>
    struct Vector2D
    {

        /**
         * @addtogroup FGM_Vec2_Members
         * @{
         */

        using value_type = T;

        static constexpr std::size_t dimension = 2;

        union {
            struct
            {
                T x; ///< X-axis component
                T y; ///< Y-axis component
            };
            struct
            {
                T r; ///< Red channel
                T g; ///< Green channel
            };
            struct
            {
                T s; ///< S-coordinate
                T t; ///< T-coordinate
            };

            T elements[dimension];
        };

        /** @} */



        /**
         * @addtogroup FGM_Vec2_Init
         * @{
         */

        /*************************************
         *                                   *
         *            INITIALIZERS           *
         *                                   *
         *************************************/

        /** @brief Initialize @ref Vector2D with zeros. */
        [[nodiscard]] constexpr Vector2D() noexcept;


        /**
         * @brief Initialize @ref Vector2D with passed in values.
         *
         * @param[in] v1 The first entry of @ref Vector2D.
         * @param[in] v2 The second entry of @ref Vector2D.
         */
        [[nodiscard]] constexpr Vector2D(T v1, T v2) noexcept;


        /**
         * @brief Initialize @ref Vector2D from another @ref Vector2D of a different type.
         *
         * @tparam U Numeric type of the source vector.
         *
         * @param[in] other The source vector to be converted.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr Vector2D(const Vector2D<U>& other) noexcept;


        /*************************************
         *                                   *
         *            ACCESSORS              *
         *                                   *
         *************************************/

        /**
         * @brief Access the component at the specified location.
         *        Provide read-write access to the element.
         *
         * @param[in] i The index of the vector component.
         *
         * @return A reference to the vector component.
         */
        constexpr T& operator[](std::size_t i) noexcept;


        /**
         * @brief Access the element at the specified location (read-only).
         *
         * @param[in] i The index of the vector component.
         *
         * @return A const reference to the vector component.
         */
        constexpr const T& operator[](std::size_t i) const noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Vec2_Equality
         * @{
         */

        /***************************************
         *                                     *
         *             EQUALITY                *
         *                                     *
         ***************************************/

        /**
         * @brief Compare all components of this vector for equality with another vector.
         *        Perform a component-wise comparison and returns true only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr bool allEq(const Vector2D<U>& rhs,
                                           double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                               ? Config::DOUBLE_EPSILON
                                               : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @copybrief allEq(const Vector2D<U>&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return True if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr static bool allEq(const Vector2D& lhs, const Vector2D<U>& rhs,
                                                  double epsilon = (std::is_same_v<T, double> ||
                                                                    std::is_same_v<U, double>)
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) noexcept;


        /**
         * @brief Compare components for inequality across two vectors.
         *        Perform a component-wise comparison and returns true if any of the pair satisfies inequality condition
         *        within the given @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref neq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if any of the components are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr bool allNeq(const Vector2D<U>& rhs,
                                            double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                                ? Config::DOUBLE_EPSILON
                                                : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @copybrief allNeq(const Vector2D<U>&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref neq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if any of the components are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr static bool allNeq(const Vector2D& lhs, const Vector2D<U>& rhs,
                                                   double epsilon = (std::is_same_v<T, double> ||
                                                                     std::is_same_v<U, double>)
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) noexcept;


        /**
         * @copybrief allEq(const Vector2D<U>&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return True if all components are equivalent within the default epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr bool operator==(const Vector2D<U>& rhs) const noexcept;


        /**
         * @copybrief allNeq(const Vector2D<U>&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return True if any of the components are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr bool operator!=(const Vector2D<U>& rhs) const noexcept;


        /**
         * @brief Perform component-wise equality check.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note To obtain a single scalar result, use @ref allEq or @ref operator==.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr Vector2D<bool> eq(const Vector2D<U>& rhs,
                                                  double epsilon = (std::is_same_v<T, double> ||
                                                                    std::is_same_v<U, double>)
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @copybrief eq(const Vector2D<U>&, double) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr static Vector2D<bool> eq(const Vector2D& lhs, const Vector2D<U>& rhs,
                                                         double epsilon = (std::is_same_v<T, double> ||
                                                                           std::is_same_v<U, double>)
                                                             ? Config::DOUBLE_EPSILON
                                                             : Config::FLOAT_EPSILON) noexcept;


        /**
         * @brief Perform component-wise inequality check.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note To obtain a single scalar result, use @ref allNeq or @ref operator!=.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr Vector2D<bool> neq(const Vector2D<U>& rhs,
                                                   double epsilon = (std::is_same_v<T, double> ||
                                                                     std::is_same_v<U, double>)
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @copybrief neq(const Vector2D<U>&, double) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr static Vector2D<bool> neq(const Vector2D& lhs, const Vector2D<U>& rhs,
                                                          double epsilon = (std::is_same_v<T, double> ||
                                                                            std::is_same_v<U, double>)
                                                              ? Config::DOUBLE_EPSILON
                                                              : Config::FLOAT_EPSILON) noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Vec2_Comparison
         * @{
         */

        /***************************************
         *                                     *
         *            COMPARISONS              *
         *                                     *
         ***************************************/

        /**
         * @brief Perform component-wise greater-than comparison.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector2D<bool> gt(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copybrief gt(const Vector2D<U>&) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static Vector2D<bool> gt(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than-or-equal comparison.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector2D<bool> gte(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copybrief gte(const Vector2D<U>&) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static Vector2D<bool> gte(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than comparison.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to compiler-level
         *       constant folding bugs. Runtime execution remains IEEE 754 compliant under /fp:strict.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector2D<bool> lt(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copybrief lt(const Vector2D<U>&) const
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to compiler-level
         *       constant folding bugs. Runtime execution remains IEEE 754 compliant under /fp:strict
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static Vector2D<bool> lt(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than-or-equal comparison.
         *        Compares each component pair and returns a boolean mask.
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to compiler-level
         *       constant folding bugs. Runtime execution remains IEEE 754 compliant under /fp:strict
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector2D<bool> lte(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copybrief lte(const Vector2D<U>&) const
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to compiler-level
         *       constant folding bugs. Runtime execution remains IEEE 754 compliant under /fp:strict
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static Vector2D<bool> lte(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


#ifdef ENABLE_FGM_SHADER_OPERATORS

        /**
         * @copydoc gt(const Vector2D<U>&) const
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector2D<bool> operator>(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc gte(const Vector2D<U>&) const
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector2D<bool> operator>=(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc lt(const Vector2D<U>&) const
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector2D<bool> operator<(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc lte(const Vector2D<U>&) const
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector2D<bool> operator<=(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;
#endif

        /** @} */




        /**
         * @addtogroup FGM_Vec2_Bitwise
         * @{
         */

        /***************************************
         *                                     *
         *      BOOLEAN BITWISE OPERATORS      *
         *                                     *
         ***************************************/

        /**
         * @brief Perform component-wise logical AND.
         *        Compute the conjunction of each component pair.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A @ref Vector2D<bool> mask containing the results of component-wise AND.
         */
        [[nodiscard]] constexpr Vector2D<bool> operator&(const Vector2D<bool>& rhs) const noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise logical AND.
         *        Compute the conjunction of each component pair in-place and update the calling vector.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A reference to this vector (*this).
         */
        constexpr Vector2D<bool>& operator&=(const Vector2D<bool>& rhs) noexcept;


        /**
         * @brief Perform component-wise logical OR.
         *        Compute the disjunction of each component pair.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A @ref Vector2D<bool> mask containing the results of component-wise OR.
         */
        [[nodiscard]] constexpr Vector2D<bool> operator|(const Vector2D<bool>& rhs) const noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise logical OR.
         *        Compute the disjunction of each component pair in-place and update the calling vector.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A reference to this vector (*this).
         */
        constexpr Vector2D<bool>& operator|=(const Vector2D<bool>& rhs) noexcept;


        /**
         * @brief Perform component-wise logical NOT.
         *        Invert each boolean component and returns a new @ref Vector2D<bool>.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @return A @ref Vector2D<bool> with inverted values.
         */
        [[nodiscard]] constexpr Vector2D<bool> operator!() const noexcept
            requires std::is_same_v<T, bool>;

        /** @} */



        /*************************************
         *                                   *
         *      ARITHMETIC OPERATORS         *
         *                                   *
         *************************************/

        template <Arithmetic U>
        auto operator+(const Vector2D<U>& other) const -> Vector2D<std::common_type_t<U, T>>;

        template <Arithmetic U>
        Vector2D& operator+=(const Vector2D<U>& other);

        template <Arithmetic U>
        auto operator-(const Vector2D<U>& other) const -> Vector2D<std::common_type_t<T, U>>;

        template <Arithmetic U>
        Vector2D& operator-=(const Vector2D<U>& other);

        template <Arithmetic S>
        auto operator*(S scalar) const -> Vector2D<std::common_type_t<T, S>>;

        template <Arithmetic S>
        Vector2D& operator*=(S scalar);

        template <Arithmetic S>
        auto operator/(S scalar) const -> Vector2D<std::common_type_t<T, S>>;

        template <Arithmetic S>
        Vector2D& operator/=(S scalar);


        /*************************************
         *                                   *
         *         VECTOR DOT PRODUCT        *
         *                                   *
         *************************************/
        template <Arithmetic U>
        auto dot(const Vector2D<U>& other) const -> std::common_type_t<T, U>;

        template <Arithmetic U>
        static auto dot(const Vector2D& vectorA, const Vector2D<U>& vectorB) -> std::common_type_t<T, U>;


        /*************************************
         *                                   *
         *       VECTOR CROSS PRODUCT        *
         *                                   *
         *************************************/
        template <Arithmetic U>
        auto cross(const Vector2D<U>& other) const -> std::common_type_t<T, U>;

        template <Arithmetic U>
        static auto cross(const Vector2D<T>& vectorA, const Vector2D<U>& vectorB) -> std::common_type_t<T, U>;


        /*************************************
         *                                   *
         *         VECTOR MAGNITUDE          *
         *                                   *
         *************************************/
        T mag() const;


        /*************************************
         *                                   *
         *       VECTOR NORMALIZATION        *
         *                                   *
         *************************************/
        Vector2D normalize() const;


        /*************************************
         *                                   *
         *        VECTOR PROJECTION          *
         *                                   *
         *************************************/

        /**
         * Projects the current vector onto to the `onto` vector.
         * @tparam U Type of the vector to be projected on to (b).
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected
         * onto is normalized.
         * @return Projected vector.
         */
        template <Arithmetic U>
        auto project(const Vector2D<U>& onto, bool ontoNormalized = false) const -> Vector2D<std::common_type_t<T, U>>;

        /**
         * Static wrapper for vector projection.
         * @tparam U Type of the vector to be projected to.
         * @param vector Vector to project.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected
         * onto is normalized.
         * @return Projected vector.
         */
        template <Arithmetic U>
        static auto project(const Vector2D& vector, const Vector2D<U>& onto,
                            bool ontoNormalized = false) -> Vector2D<std::common_type_t<T, U>>;


        /*************************************
         *                                   *
         *         VECTOR REJECTION          *
         *                                   *
         *************************************/

        /**
         * Returns the perpendicular component for the current vector after projection to the `onto` vector.
         * @tparam U Type of the vector to be vector projected onto.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected
         * onto is normalized.
         * @return Projected vector.
         */
        template <Arithmetic U>
        auto reject(const Vector2D<U>& onto, bool ontoNormalized = false) const -> Vector2D<std::common_type_t<T, U>>;

        /**
         * Returns the perpendicular component for the current vector after projection to the `onto` vector.
         * @tparam U Type of the vector to be vector projected onto.
         * @param vector whose rejection(perpendicular) component on to `onto` we need to find.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected
         * onto is normalized.
         * @return Projected vector.
         */
        template <Arithmetic U>
        static auto reject(const Vector2D& vector, const Vector2D<U>& onto,
                           bool ontoNormalized = false) -> Vector2D<std::common_type_t<T, U>>;
    };


    /*************************************
     *                                   *
     *       NON-MEMBER FUNCTIONS        *
     *                                   *
     *************************************/

    template <Arithmetic T, Arithmetic S>
    auto operator*(S scalar, const Vector2D<T>& vector) -> Vector2D<std::common_type_t<S, T>>;


    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/
    using vec2 = Vector2D<float>;
    using dvec2 = Vector2D<double>;
} // namespace fgm

#include "Vector2D.tpp"