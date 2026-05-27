#pragma once
/**
 * @file Vector2D.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 24, 2026
 *
 * @brief Templated 2D Vector supporting integral, floating-point, and boolean types.
 *
 * @details Provide high-performance 2D vector implementation with SIMD acceleration
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


#include "common/Config.h"
#include "common/Constants.h"
#include "common/MathTraits.h"
#include "common/OperationStatus.h"
#include "common/Types.h"

#include <array>
#include <iomanip>
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

        using value_type = T; ///< The numeric type of the vector components.

        static constexpr std::size_t dimension = 2; ///< The number of components of the vector.

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Init
         * @{
         */

        /**
         * @brief Initialize an uninitialized @ref Vector2D instance.
         *
         * @warning The components are left uninitialized (containing garbage data)
         *          to maximize SIMD optimization and maintain triviality.
         *
         * @note Use value-initialization (`{}`) or the static helper
         *       @ref fgm::vec3d::zero<T> to guarantee a zeroed vector.
         */
        Vector2D() = default;


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
        [[nodiscard]] explicit constexpr Vector2D(const Vector2D<U>& other) noexcept;

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Access
         * @{
         */

        /**
         * @brief Access the element at the first location (read-only).
         * @return A copy of the first vector element.
         */
        [[nodiscard]] constexpr T x() const noexcept;


        /**
         * @brief Access the element at the first location (read-write access).
         * @return A reference to the first element of the vector.
         */
        [[nodiscard]] constexpr T& x() noexcept;


        /**
         * @brief Access the element at the last location (read-only).
         * @return A copy of the last vector element.
         */
        [[nodiscard]] constexpr T y() const noexcept;


        /**
         * @brief Access the element at the last location (read-write access).
         * @return A reference to the last element of the vector.
         */
        [[nodiscard]] constexpr T& y() noexcept;


        /**
         * @brief Access the element at the first location (read-only).
         * @return A copy of the first vector element.
         */
        [[nodiscard]] constexpr T s() const noexcept;


        /**
         * @brief Access the element at the first location (read-write access).
         * @return A reference to the first element of the vector.
         */
        [[nodiscard]] constexpr T& s() noexcept;


        /**
         * @brief Access the element at the last location (read-only).
         * @return A copy of the last vector element.
         */
        [[nodiscard]] constexpr T t() const noexcept;


        /**
         * @brief Access the element at the last location (read-write access).
         * @return A reference to the last element of the vector.
         */
        [[nodiscard]] constexpr T& t() noexcept;


        /**
         * @brief Access the element at the first location (read-only).
         * @return A copy of the first vector element.
         */
        [[nodiscard]] constexpr T r() const noexcept;


        /**
         * @brief Access the element at the first location (read-write access).
         * @return A reference to the first element of the vector.
         */
        [[nodiscard]] constexpr T& r() noexcept;


        /**
         * @brief Access the element at the last location (read-only).
         * @return A copy of the last vector element.
         */
        [[nodiscard]] constexpr T g() const noexcept;


        /**
         * @brief Access the element at the last location (read-write access).
         * @return A reference to the last element of the vector.
         */
        [[nodiscard]] constexpr T& g() noexcept;


        /**
         * @brief Access the element at the specified location (read-only).
         *        Provide read-write access to the element.
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] idx The index of the vector component.
         *
         * @return A reference to the vector component.
         */
        constexpr T& operator[](std::size_t idx) noexcept;


        /**
         * @brief Access the element at the specified location (read-only).
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] idx The index of the vector component.
         *
         * @return A copy of the vector component.
         */
        constexpr const T& operator[](std::size_t idx) const noexcept;

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Swizzle
         * @{
         */

        /**
         * @brief Construct a new vector by rearranging, duplicating, or isolating components of this vector.
         *
         * @note Bounds checking for the provided indices is strictly enforced at compile-time.
         *       Providing an out-of-bounds index will result in a compilation error, guaranteeing zero runtime
         *       overhead.
         *
         * @tparam Indices The component indices used to construct the new vector.
         *                 See @ref fgm::axis, @ref fgm::colors, and @ref fgm::stp for available swizzle aliases.
         *
         * @return A new vector containing the requested components or the component if @p Indices is 1.
         *         The dimension of the returned vector perfectly matches the number of indices provided.
         */
        template <std::size_t... Indices>
        [[nodiscard("Swizzling returns a new vector and does not mutate the original.")]]
        constexpr auto swizzle() const noexcept;


        /**
         * @brief Construct a new vector by rearranging, duplicating, or isolating components of @p vec.
         *
         * @note Bounds checking for the provided indices is strictly enforced at compile-time.
         *       Providing an out-of-bounds index will result in a compilation error, guaranteeing zero runtime
         *       overhead.
         *
         * @tparam Indices The component indices used to construct the new vector.
         *                 See @ref fgm::axis, @ref fgm::colors, and @ref fgm::stp for available swizzle aliases.
         *
         * @param vec The vector to shuffle, rearrange or isolate components.
         *
         * @return A new vector containing the requested components or the component if @p Indices is 1.
         *         The dimension of the returned vector perfectly matches the number of indices provided.
         */
        template <std::size_t... Indices>
        [[nodiscard("Swizzling returns a new vector and does not mutate the original.")]]
        static constexpr auto swizzle(const Vector2D& vec) noexcept;

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Equality
         * @{
         */

        /**
         * @brief Compare all components of this vector with @p rhs vector for equality.
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
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool allEq(const Vector2D<U>& rhs,
                                           double epsilon = std::is_same_v<T, double> || std::is_same_v<U, double>
                                               ? Config::DOUBLE_EPSILON
                                               : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all components of @p lhs vector with @p rhs vector for equality.
         *        Perform a component-wise comparison and returns `true` only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return `true` if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr bool allEq(const Vector2D& lhs, const Vector2D<U>& rhs,
                                                  double epsilon = std::is_same_v<T, double> ||
                                                          std::is_same_v<U, double>
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) noexcept;


        /**
         * @brief Compare all components of this vector with @p rhs vector for inequality.
         *        Perform a component-wise comparison and returns `true` if any corresponding elements differ by more
         *        than @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref neq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return `true` if any of the components are not equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool anyNeq(const Vector2D<U>& rhs,
                                            double epsilon = std::is_same_v<T, double> || std::is_same_v<U, double>
                                                ? Config::DOUBLE_EPSILON
                                                : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all components of @p lhs vector with @p rhs vector for inequality.
         *        Perform a component-wise comparison and returns `true` if any corresponding elements differ by more
         *        than @p epsilon.
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
         * @return `true` if any of the components are not equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr bool anyNeq(const Vector2D& lhs, const Vector2D<U>& rhs,
                                                   double epsilon = std::is_same_v<T, double> ||
                                                           std::is_same_v<U, double>
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
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool operator==(const Vector2D<U>& rhs) const noexcept;


        /**
         * @copybrief anyNeq(const Vector2D<U>&, double) const
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
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool operator!=(const Vector2D<U>& rhs) const noexcept;


        /**
         * @brief Perform component-wise equality check between this vector and @p rhs vector.
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
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Vector2D<bool> eq(const Vector2D<U>& rhs,
                                                  double epsilon = std::is_same_v<T, double> ||
                                                          std::is_same_v<U, double>
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Perform component-wise equality check between @p lhs and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
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
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr Vector2D<bool> eq(const Vector2D& lhs, const Vector2D<U>& rhs,
                                                         double epsilon = std::is_same_v<T, double> ||
                                                                 std::is_same_v<U, double>
                                                             ? Config::DOUBLE_EPSILON
                                                             : Config::FLOAT_EPSILON) noexcept;


        /**
         * @brief Perform component-wise inequality check between this vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note To obtain a single scalar result, use @ref anyNeq or @ref operator!=.
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
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Vector2D<bool> neq(const Vector2D<U>& rhs,
                                                   double epsilon = std::is_same_v<T, double> ||
                                                           std::is_same_v<U, double>
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Perform component-wise inequality check between @p lhs vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
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
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr Vector2D<bool> neq(const Vector2D& lhs, const Vector2D<U>& rhs,
                                                          double epsilon = std::is_same_v<T, double> ||
                                                                  std::is_same_v<U, double>
                                                              ? Config::DOUBLE_EPSILON
                                                              : Config::FLOAT_EPSILON) noexcept;

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Comparison
         * @{
         */

        /**
         * @brief Perform component-wise greater-than comparison between this vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Vector2D<bool> gt(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than comparison between @p lhs vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr Vector2D<bool> gt(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than-or-equal comparison between this vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Vector2D<bool> gte(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than-or-equal comparison between @p lhs vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref Vector2D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr Vector2D<bool> gte(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than comparison between this vector and @p rhs vector.
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
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Vector2D<bool> lt(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than comparison between @p lhs vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
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
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr Vector2D<bool> lt(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than-or-equal comparison between this vector and @p rhs vector.
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
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Vector2D<bool> lte(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than-or-equal comparison between @p lhs vector and @p rhs vector.
         *        Compares each component pair and returns a boolean mask.
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
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr Vector2D<bool> lte(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


#ifdef ENABLE_FGM_SHADER_OPERATORS

        /**
         * @copydoc gt(const Vector2D<U>&) const
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Vector2D<bool> operator>(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc gte(const Vector2D<U>&) const
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Vector2D<bool> operator>=(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc lt(const Vector2D<U>&) const
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Vector2D<bool> operator<(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc lte(const Vector2D<U>&) const
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Vector2D<bool> operator<=(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;
#endif

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Bitwise
         * @{
         */

        /**
         * @brief Perform component-wise logical AND between this vector and @p rhs vector.
         *        Compute the conjunction between each component pair.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A @ref Vector2D<bool> mask containing the results of component-wise AND.
         */
        [[nodiscard]] constexpr Vector2D operator&(const Vector2D& rhs) const noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform an in-place component-wise logical AND between this vector and @p rhs vector.
         *        Compute the conjunction between each component pair in-place and update the calling vector.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A reference to this vector (*this).
         */
        constexpr Vector2D& operator&=(const Vector2D& rhs) noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise logical OR between this vector and @p rhs vector.
         *        Compute the disjunction between each component pair.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A @ref Vector2D<bool> mask containing the results of component-wise OR.
         */
        [[nodiscard]] constexpr Vector2D operator|(const Vector2D& rhs) const noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform an in-place component-wise logical OR between this vector and @p rhs vector.
         *        Compute the disjunction between each component pair in-place and update the calling vector.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A reference to this vector (*this).
         */
        constexpr Vector2D& operator|=(const Vector2D& rhs) noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Apply a component-wise logical NOT on this vector.
         *        Invert each boolean component and returns a new @ref Vector2D<bool>.
         *
         * @note Only available for @ref bVec2 and vectors with `bool` value_type.
         *
         * @return A @ref Vector2D<bool> with inverted values.
         */
        [[nodiscard]] constexpr Vector2D operator!() const noexcept
            requires std::is_same_v<T, bool>;

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Arithmetic
         * @{
         */

        /**
         * @brief Compute the component-wise sum of this vector with @p rhs vector and return a new vector.
         *
         * @note Promotes the result to the wider type using @ref PromotedVector2D<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to add.
         *
         * @return A new @ref Vector2D containing the component-wise sum.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedVector2D<T, U> operator+(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise sum of this vector with @p rhs vector in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to add.
         *
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr Vector2D& operator+=(const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise difference between this vector and @p rhs vector and return a new vector.
         *
         * @note Promotes the result to the wider type using @ref PromotedVector2D<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to subtract.
         *
         * @return A new @ref Vector2D containing the component-wise difference.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedVector2D<T, U> operator-(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise difference between this vector and @p rhs vector in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to subtract.
         *
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr Vector2D& operator-=(const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Apply a component-wise inversion to this vector.
         *        Invert the sign of each component and returns a new @ref Vector2D<T>.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @return A new @ref fgm::Vector2D with inverted components.
         */
        [[nodiscard]] constexpr Vector2D operator-() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the component-wise product between this vector and @p scalar and return a new vector.
         *
         * @note Promotes the result to the wider type using @ref PromotedVector2D<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Vector2D scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedVector2D<T, S> operator*(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise product between this vector and @p scalar in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic S>
        constexpr Vector2D& operator*=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of this vector by @p scalar and return a new vector.
         *
         * @note Promotes the result to the wider type using @ref PromotedVector2D<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Performs assertion for division by zero in **Debug mode**.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Vector2D scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedVector2D<T, S> operator/(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of this vector by @p scalar in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Performs assertion for division by zero in **Debug mode**.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic S>
        constexpr Vector2D& operator/=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of this vector by @p scalar and return a new vector.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN components,
         *       returns a zero vector.
         * @note Promotes the result to the wider type using @ref PromotedVector2D<T, S>.
         * @note Operation is restricted to numeric types via @ref fgm::StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref fgm::StrictArithmetic.
         *
         * @param[in] scalar The value to divide the vector components by.
         *
         * @return A new @ref Vector2D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors contains NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedVector2D<T, S> safeDiv(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of @p vec by @p scalar and return a new vector.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN components,
         *       returns a zero vector.
         * @note Promotes the result to the wider type using @ref PromotedVector2D<T, S>.
         * @note Operation is restricted to numeric types via @ref fgm::StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref fgm::StrictArithmetic.
         *
         * @param[in] vec The vector to divide.
         * @param[in] scalar The value to divide the vector components by.
         *
         * @return A new @ref Vector2D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors contains NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedVector2D<T, S> safeDiv(const Vector2D& vec, S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of this vector by @p scalar, return a new vector,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN components,
         *       returns a zero vector.
         * @note Promotes the result to the wider type using @ref PromotedVector2D<T, S>.
         * @note Operation is restricted to numeric types via @ref fgm::StrictArithmetic.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over mathematical
         *       invalidity (Division by Zero) when reporting status.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref fgm::StrictArithmetic.
         *
         * @param[in] scalar  The value to divide the vector components by.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A new @ref Vector2D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors+ has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedVector2D<T, S> tryDiv(S scalar, OperationStatus& status) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of @p vec by @p scalar, return a new vector,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN components,
         *       returns a zero vector.
         * @note Promotes the result to the wider type using @ref PromotedVector2D<T, S>.
         * @note Operation is restricted to numeric types via @ref fgm::StrictArithmetic.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over mathematical
         *       invalidity (Division by Zero) when reporting status.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref fgm::StrictArithmetic.
         *
         * @param[in] vec     The vector to divide.
         * @param[in] scalar  The value to divide the vector components by.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A new @ref Vector2D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors+ has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedVector2D<T, S> tryDiv(const Vector2D& vec, S scalar,
                                                                     OperationStatus& status) noexcept
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Product
         * @{
         */

        /**
         * @brief Compute the dot product with another vector.
         *        \f$ \mathbf{a} \cdot \mathbf{b} = \sum_{i=1}^{2} a_i b_i \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedValue_t<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compute the dot product with.
         *
         * @return The scalar dot product of the two vectors.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedValue_t<T, U> dot(const Vector2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the dot product of two vectors.
         *        \f$ \mathbf{a} \cdot \mathbf{b} = \sum_{i=1}^{2} a_i b_i \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedValue_t<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The first vector to compute the dot product with.
         * @param[in] rhs The second vector to compute the dot product with.
         *
         * @return The scalar dot product of @p lhs and @p rhs.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedValue_t<T, U> dot(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the 2D pseudo-cross product with another vector.
         *        \f$ \mathbf{a} \times \mathbf{b} = (x_1 \cdot y_2 - x_2 \cdot y_1) \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedValue_t<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compute the cross product with.
         *
         * @return The pseudo-cross cross product of the two vectors.
         */
        template <SignedStrictArithmetic U>
        constexpr PromotedValue_t<T, U> cross(const Vector2D<U>& rhs) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the 2D pseudo-cross product of two vectors.
         *        \f$ \mathbf{a} \times \mathbf{b} = (x_1 \cdot y_2 - x_2 \cdot y_1) \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedValue_t<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The first vector to compute the cross product with.
         * @param[in] rhs The second vector to compute the cross product with.
         *
         * @return The pseudo-cross product of the two vectors.
         */
        template <SignedStrictArithmetic U>
        static constexpr PromotedValue_t<T, U> cross(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
            requires SignedStrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Mag
         * @{
         */

        /**
         * @brief Compute the magnitude (Euclidean Norm) of this vector.
         *        \f$ \|\mathbf{v}\| = \sqrt{\mathbf{v} \cdot \mathbf{v}} \f$
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @return The scalar magnitude of the vector.
         */
        [[nodiscard]] constexpr Magnitude<T> mag() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the magnitude (Euclidean Norm) of @p vec.
         *        \f$ \|\mathbf{v}\| = \sqrt{\mathbf{v} \cdot \mathbf{v}} \f$
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[in] vec The vector to compute the magnitude of.
         *
         * @return The scalar magnitude of @p vec.
         */
        [[nodiscard]] static constexpr Magnitude<T> mag(const Vector2D& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the magnitude square (Euclidean Norm) of this vector.
         *        \f$ \|\mathbf{v}\| = \mathbf{v} \cdot \mathbf{v} \f$
         *
         * @return The scalar magnitude of the vector.
         */
        [[nodiscard]] constexpr T magSq() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the magnitude square (Euclidean Norm) of @p vec.
         *        \f$ \|\mathbf{v}\| = \mathbf{v} \cdot \mathbf{v} \f$
         *
         * @param[in] vec The vector to compute the magnitude of.
         *
         * @return The scalar magnitude of @p vec.
         */
        [[nodiscard]] static constexpr T magSq(const Vector2D& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Manhattan length (L1 Norm) of this vector.
         *        \f$ \|\mathbf{v}\|_1 = |x| + |y| \f$
         *
         * @return The Manhattan length.
         */
        [[nodiscard]] constexpr T manhattanNorm() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Manhattan length (L1 Norm) of @p vec.
         *        \f$ \|\mathbf{v}\|_1 = |x| + |y| \f$
         *
         * @param[in] vec The vector to compute the taxicab norm of.
         *
         * @return The Manhattan length.
         */
        [[nodiscard]] static constexpr T manhattanNorm(const Vector2D& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Chebyshev length (L∞ Norm) of this vector.
         *        \f$ \|\mathbf{v}\|_{\infty} = max(|x|, |y|) \f$
         *
         * @return The Chebyshev length.
         */
        [[nodiscard]] constexpr T chebyshevNorm() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Chebyshev length (L∞ Norm) of @p vec.
         *        \f$ \|\mathbf{v}\|_{\infty} = max(|x|, |y|) \f$
         *
         * @param[in] vec The vector to compute the taxicab norm of.
         *
         * @return The Chebyshev length.
         */
        [[nodiscard]] static constexpr T chebyshevNorm(const Vector2D& vec) noexcept
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Normalize
         * @{
         */

        /**
         * @brief Compute the normalized (unit) form of this vector.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
         *
         * @return A new @ref Vector2D with a magnitude of 1.0.
         */
        [[nodiscard]] constexpr Vector2D<Magnitude<T>> normalize() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the normalized (unit) form of @p vec.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
         *
         * @param[in] vec The vector to normalize.
         *
         * @return A new @ref Vector2D with a magnitude of 1.0.
         */
        [[nodiscard]] static constexpr Vector2D<Magnitude<T>> normalize(const Vector2D& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the normalized (unit) form of this vector.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note This is a safe operation. If the vector's magnitude falls below the internal
         *       epsilon, or if it contains NaN components, division by zero is bypassed.
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @return A @ref Vector2D with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if this vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vector2D<Magnitude<T>> safeNormalize() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the normalized (unit) form of @p vec.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note This is a safe operation. If the vector's magnitude falls below the internal
         *       epsilon, or if it contains NaN components, division by zero is bypassed.
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[in] vec The vector to be normalized.
         *
         * @return A @ref fgm::Vector2D with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr Vector2D<Magnitude<T>> safeNormalize(const Vector2D& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the normalized (unit) form of this vector and
         *        set @p status to the normalization operation result.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note This is a safe operation. If the vector's magnitude falls below the internal
         *       epsilon, or if it contains NaN components, division by zero is bypassed.
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[out] status The status flag to store the status of the current operation result.*
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A @ref fgm::Vector2D with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if this vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vector2D<Magnitude<T>> tryNormalize(OperationStatus& status) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the normalized (unit) form of @p vec and
         *        set @p status to the normalization operation result.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note This is a safe operation. If the vector's magnitude falls below the internal
         *       epsilon, or if it contains NaN components, division by zero is bypassed.
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[in] vec     The vector to be normalized.
         * @param[out] status The status flag to store the status of the current operation result.*
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A @ref fgm::Vector2D with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr Vector2D<Magnitude<T>> tryNormalize(const Vector2D& vec,
                                                                           OperationStatus& status) noexcept
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Proj
         * @{
         */

        /**
         * @brief Project this vector onto the @p onto vector.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note If @p onto is normalized, use @ref projectNorm as it is a faster implementation for unit vectors.
         * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vector2D.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedFloatVector2D<T, U> project(const Vector2D<U>& onto) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project this vector onto the **unit** @p onto vector.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedVector4D<T, U>.
         * @note Only use this method if @p onto is normalized. If not, use @ref project.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vector2D.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedVector2D<T, U> projectNorm(const Vector2D<U>& onto) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project the @p vec vector onto the @p onto vector.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note If @p onto is normalized, use @ref projectNorm as it is a faster implementation for unit vectors.
         * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to project.
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vector2D.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedFloatVector2D<T, U> project(const Vector2D& vec,
                                                                           const Vector2D<U>& onto) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project the @p vec vector onto the **unit** @p onto vector.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note Only use this method if @p onto is normalized. If not, use @ref project.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to project.
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vector2D.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedVector2D<T, U> projectNorm(const Vector2D& vec,
                                                                          const Vector2D<U>& onto) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project this vector onto the @p onto vector.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note If @p onto is normalized, use @ref safeProjectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vector2D or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedFloatVector2D<T, U> safeProject(const Vector2D<U>& onto) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project this vector onto the **unit** @p onto vector.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedVector4D<T, U>.
         * @note Only use this method if @p onto is normalized. If not, use @ref safeProject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto           The vector to project onto.
         *
         * @return The projected @ref Vector2D or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedVector2D<T, U> safeProjectNorm(const Vector2D<U>& onto) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project the @p vec vector onto the @p onto vector.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note If @p onto is normalized, use @ref safeProjectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to project.
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vector2D or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedFloatVector2D<T, U> safeProject(const Vector2D& vec,
                                                                               const Vector2D<U>& onto) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project the @p vec vector onto the **unit** @p onto vector.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedVector4D<T, U>.
         * @note Only use this method if @p onto is normalized. If not, use @ref safeProject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to project.
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref Vector2D or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedVector2D<T, U> safeProjectNorm(const Vector2D& vec,
                                                                              const Vector2D<U>& onto) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project this vector onto the @p onto vector and set @p status to the
         *        projection operation result.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note If @p onto is normalized, use @ref tryProjectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto    The vector to project onto.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The projected @ref Vector2D or a zero-vector if projected onto a zero-length vector or if either
         *         vector has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedFloatVector2D<T, U> tryProject(const Vector2D<U>& onto,
                                                                       OperationStatus& status) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project this vector onto the **unit** @p onto vector and set @p status to the
         *        projection operation result.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedVector4D<T, U>.
         * @note Only use this method if @p onto is normalized. If not, use @ref tryProject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto    The vector to project onto.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The projected @ref Vector2D or a zero-vector if projected onto a zero-length vector or if either
         *         vector has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedVector2D<T, U> tryProjectNorm(const Vector2D<U>& onto,
                                                                      OperationStatus& status) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project the @p vec vector onto the @p onto vector and set @p status to the
         *        projection operation result.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note If @p onto is normalized, use @ref tryProjectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec     The vector to project.
         * @param[in] onto    The vector to project onto.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The projected @ref Vector2D or a zero-vector if projected onto a zero-length vector or if either
         *         vector has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedFloatVector2D<T, U> tryProject(const Vector2D& vec,
                                                                              const Vector2D<U>& onto,
                                                                              OperationStatus& status) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project the @p vec vector onto the **unit** @p onto vector and set @p status to the
         *        projection operation result.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedVector4D<T, U>.
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         * @note Only use this method if @p onto is normalized. If not, use @ref tryProject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec     The vector to project.
         * @param[in] onto    The vector to project onto.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The projected @ref Vector2D or a zero-vector if projected onto a zero-length vector or if either
         *         vector has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedVector2D<T, U> tryProjectNorm(const Vector2D& vec,
                                                                             const Vector2D<U>& onto,
                                                                             OperationStatus& status) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject this vector from the @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note If @p from is normalized, use @ref rejectNorm as it is a faster implementation for unit vectors.
         * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vector2D component.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedFloatVector2D<T, U> reject(const Vector2D<U>& from) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject this vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note Only use this method if @p from is normalized. If not, use @ref reject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vector2D component.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedVector2D<T, U> rejectNorm(const Vector2D<U>& from) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject the @p vec vector from the @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note If @p from is normalized, use @ref rejectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to be rejected.
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vector2D component.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedFloatVector2D<T, U> reject(const Vector2D& vec,
                                                                          const Vector2D<U>& from) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject the @p vec vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedVector4D<T, U>.
         * @note Only use this method if @p from is normalized. If not, use @ref reject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vector The vector to be rejected.
         * @param[in] from   The vector to reject from.
         *
         * @return The perpendicular @ref Vector2D component.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedVector2D<T, U> rejectNorm(const Vector2D& vector,
                                                                         const Vector2D<U>& from) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject this vector from the @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note If @p from is normalized, use @ref safeRejectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vector2D component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedFloatVector2D<T, U> safeReject(const Vector2D<U>& from) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject this vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedVector4D<T, U>.
         * @note Only use this method if @p from is normalized. If not, use @ref safeReject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vector2D component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedVector2D<T, U> safeRejectNorm(const Vector2D<U>& from) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject the @p vec vector from the @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note If @p from is normalized, use @ref safeRejectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to reject.
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vector2D component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedFloatVector2D<T, U> safeReject(const Vector2D& vec,
                                                                              const Vector2D<U>& from) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject the @p vec vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedVector4D<T, U>.
         * @note Only use this method if @p from is normalized. If not, use @ref safeReject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to reject.
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref Vector2D component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedVector2D<T, U> safeRejectNorm(const Vector2D& vec,
                                                                             const Vector2D<U>& from) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject this vector from the @p from vector and set @p status to the result of rejection operation.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note If @p from is normalized, use @ref tryRejectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from    The vector to reject from
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The perpendicular @ref Vector2D component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedFloatVector2D<T, U> tryReject(const Vector2D<U>& from,
                                                                      OperationStatus& status) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject this vector from the **unit** @p from vector and set @p status to the result of
         *        rejection operation.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedVector4D<T, U>.
         * @note Only use this method if @p from is normalized. If not, use @ref tryReject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from    The vector to reject from
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The perpendicular @ref Vector2D component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedVector2D<T, U> tryRejectNorm(const Vector2D<U>& from,
                                                                     OperationStatus& status) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject the @p vec vector from the @p from vector and set @p status to the result of
         *        rejection operation.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatVector4D<T, U>.
         * @note If @p from is normalized, use @ref tryRejectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec     The vector to reject.
         * @param[in] from    The vector to reject from.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The perpendicular @ref Vector2D component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedFloatVector2D<T, U> tryReject(const Vector2D& vec,
                                                                             const Vector2D<U>& from,
                                                                             OperationStatus& status) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject the @p vec vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedVector4D<T, U>.
         * @note Only use this method if @p from is normalized. If not, use @ref tryReject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec     The vector to reject.
         * @param[in] from    The vector to reject from.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The perpendicular @ref Vector2D component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedVector2D<T, U> tryRejectNorm(const Vector2D& vec,
                                                                            const Vector2D<U>& from,
                                                                            OperationStatus& status) noexcept
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Utils
         * @{
         */

        /**
         * @brief Check if any component of this vector is an IEEE 754 infinity.
         *
         * @note Always return false for integral types.
         *
         * @return True if at least one component is positive or negative infinity.
         */
        [[nodiscard]] constexpr bool hasInf() const noexcept;


        /**
         * @brief Check if any component of a vector is an IEEE 754 infinity.
         *
         * @note Always return false for integral types.
         *
         * @param vec The vector to evaluate for indefinite components.
         *
         * @return True if at least one component is positive or negative infinity.
         */
        [[nodiscard]] static constexpr bool hasInf(const Vector2D& vec) noexcept;


        /**
         * @brief Check if any component of this vector is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @return True if at least one component is NaN.
         */
        [[nodiscard]] constexpr bool hasNaN() const noexcept;


        /**
         * @brief Check if any component of this vector is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @param vec The vector to evaluate for indefinite components.
         *
         * @return True if at least one component is NaN.
         */
        [[nodiscard]] static constexpr bool hasNaN(const Vector2D& vec) noexcept;

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Log
         * @{
         */

        /**
         * @brief Write the vector to an output stream.
         *        Format the vector as <x, y> string representation for debugging or logging.
         *
         * @param os     The output stream to write to.
         * @param vector The vector to be streamed.
         *
         * @return A reference to the output stream @p os.
         */
        friend std::ostream& operator<<(std::ostream& os, const Vector2D& vector)
        {
            const std::streamsize oldPrecision     = os.precision();
            const std::ios_base::fmtflags oldFlags = os.flags();

            auto precision = Config::useFullPrecision
                ? std::is_same_v<T, double> ? Config::DOUBLE_PRECISION : Config::FLOAT_PRECISION
                : Config::LOG_PRECISION;
            os << std::setprecision(precision) << std::fixed;
            os << "<" << vector[0] << ", " << vector[1] << ">\n";

            os.precision(oldPrecision);
            os.flags(oldFlags);

            return os;
        }

        /** @} */

    private:
        std::array<T, dimension> _data;
    };


    /*************************************
     *                                   *
     *       NON-MEMBER FUNCTIONS        *
     *                                   *
     *************************************/

    /**
     * @addtogroup FGM_Vec2_Arithmetic
     * @{
     */

    /**
     * @brief Scale the vector by a scalar value.
     *        Multiply @p scalar by each component of the vector and returns a new vector.
     *
     * @note Promotes the result to the wider type using @ref PromotedVector2D<T, S>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] scalar The value to scale by.
     * @param[in] vector The vector to scale[RHS].
     *
     * @return A new @ref Vector2D scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    [[nodiscard]] constexpr PromotedVector2D<T, S> operator*(S scalar, const Vector2D<T>& vector) noexcept
        requires StrictArithmetic<T>;

    /** @} */


    /**
     * @addtogroup FGM_Vec2_Alias
     * @{
     */

    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/

    using bVec2  = Vector2D<bool>;               ///< `bool` vector
    using iVec2  = Vector2D<int>;                ///< `int` vector
    using uVec2  = Vector2D<unsigned int>;       ///< `unsigned int` vector
    using vec2   = Vector2D<float>;              ///< `float` vector
    using lVec2  = Vector2D<long long>;          ///< `long long` vector
    using dVec2  = Vector2D<double>;             ///< `double` vector
    using ulVec2 = Vector2D<unsigned long long>; ///< `unsigned long long` vector

    /** @} */


    /**
     * @addtogroup FGM_Vec2_Const
     * @{
     */

    /*************************************
     *                                   *
     *            CONSTANTS              *
     *                                   *
     *************************************/

    namespace vec2d
    {
        /**
         * @brief A 2D vector with all components set to one (1, 1).
         *
         * @note Only available for @ref fgm::StrictArithmetic types.
         */
        template <StrictArithmetic T>
        inline constexpr Vector2D<T> one = Vector2D<T>(T(1), T(1));


        /**
         * @brief A 2D vector with all components set to zero (0, 0).
         *
         * @note Only available for @ref fgm::StrictArithmetic types.
         */
        template <StrictArithmetic T>
        inline constexpr Vector2D<T> zero = Vector2D<T>(T(0), T(0)); ///< 2D-Vector with all zero-components.


        /**
         * @brief A 2D vector with all components set to positive infinity.
         *
         * @note Only available for `std::floating_point` types.
         */
        template <StrictArithmetic T>
            requires std::floating_point<T>
        inline constexpr Vector2D<T> inf = Vector2D<T>(T(constants::INFINITY_D), T(constants::INFINITY_D));


        /**
         * @brief A 2D vector with all components set to negative infinity.
         *
         * @note Only available for `std::floating_point` types.
         */
        template <StrictArithmetic T>
            requires std::floating_point<T>
        inline constexpr Vector2D<T> infN = Vector2D<T>(T(-constants::INFINITY_D), T(-constants::INFINITY_D));


        /**
         * @brief A 2D vector with all components set to Not-A-Number (NaN).
         *
         * @note Only available for `std::floating_point` types.
         */
        template <StrictArithmetic T>
            requires std::floating_point<T>
        inline constexpr Vector2D<T> nan = Vector2D<T>(T(constants::NaN_D), T(constants::NaN_D));


        /** @brief A 2D unit vector aligned with the positive X-axis (1, 0). */
        template <StrictArithmetic T>
        inline constexpr Vector2D<T> x = Vector2D<T>(T(1), T(0));


        /** @brief A 2D unit vector aligned with the positive Y-axis (0, 1). */
        template <StrictArithmetic T>
        inline constexpr Vector2D<T> y = Vector2D<T>(T(0), T(1));
    } // namespace vec2d


    /** @brief Template deduction guide for Vector2D */
    template <Arithmetic T>
    Vector2D(T, T) -> Vector2D<T>;

    /** @} */
} // namespace fgm


#include "Vector2D.tpp"
