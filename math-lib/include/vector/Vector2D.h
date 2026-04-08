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

        using value_type = T;

        static constexpr std::size_t dimension = 2;

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

        /**************************************
         *                                    *
         *        SPATIAL COORDINATES         *
         *                                    *
         **************************************/

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


        /**************************************
         *                                    *
         *           STP COORDINATES          *
         *                                    *
         **************************************/

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


        /**************************************
         *                                    *
         *         COLOR COORDINATES          *
         *                                    *
         **************************************/

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


        /**************************************
         *                                    *
         *              INDEXING              *
         *                                    *
         **************************************/

        /**
         * @brief Access the element at the specified location (read-only).
         *        Provide read-write access to the element.
         *
         * @param[in] idx The index of the vector component.
         *
         * @return A reference to the vector component.
         */
        constexpr T& operator[](std::size_t idx) noexcept;


        /**
         * @brief Access the element at the specified location (read-only).
         *
         * @param[in] idx The index of the vector component.
         *
         * @return A copy of the vector component.
         */
        constexpr const T& operator[](std::size_t idx) const noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Vec3_Swizzle
         * @{
         */

        /**
         * @brief Constructs a new vector by rearranging, duplicating, or isolating components of the current vector.
         *
         * @note Bounds checking for the provided indices is strictly enforced at compile-time.
         *       Providing an out-of-bounds index will result in a compilation error, guaranteeing zero runtime
         *       overhead.
         *
         * @tparam Indices The component indices used to construct the new vector.
         *                 @see @ref fgm::axis, @ref fgm::colors, and @ref fgm::stp for available swizzle aliases.
         *
         * @return A new vector containing the requested components or the component if @p Indices is 1.
         *         The dimension of the returned vector perfectly matches the number of indices provided.
         */
        template <std::size_t... Indices>
        [[nodiscard("Swizzling returns a new vector and does not mutate the original.")]]
        constexpr auto swizzle() const noexcept;


        /**
         * @brief Constructs a new vector by rearranging, duplicating, or isolating components of the given vector.
         *
         * @note Bounds checking for the provided indices is strictly enforced at compile-time.
         *       Providing an out-of-bounds index will result in a compilation error, guaranteeing zero runtime
         *       overhead.
         *
         * @tparam Indices The component indices used to construct the new vector.
         *                 @see @ref fgm::axis, @ref fgm::colors, and @ref fgm::stp for available swizzle aliases.
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
         *        Performs a component-wise comparison and returns true if any corresponding elements differ by more
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
        [[nodiscard]] constexpr Vector2D operator&(const Vector2D& rhs) const noexcept
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
        constexpr Vector2D& operator&=(const Vector2D& rhs) noexcept
            requires std::is_same_v<T, bool>;


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
        [[nodiscard]] constexpr Vector2D operator|(const Vector2D& rhs) const noexcept
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
        constexpr Vector2D& operator|=(const Vector2D& rhs) noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise logical NOT.
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

        /*************************************
         *                                   *
         *      ARITHMETIC OPERATORS         *
         *                                   *
         *************************************/

        /**
         * @brief Add two vectors component-wise.
         *        Compute the sum of each component pair and returns a new vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to add.
         *
         * @return A new @ref Vector2D containing the component-wise sum.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto operator+(const Vector2D<U>& rhs) const noexcept
            -> Vector2D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;


        /**
         * @brief Add another vector to this vector component-wise.
         *        Perform an in-place addition of @p rhs to the current instance.
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
        constexpr Vector2D& operator+=(const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Subtract two vectors component-wise.
         *        Compute the difference between each component pair and returns a new vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to subtract.
         *
         * @return A new @ref Vector2D containing the component-wise difference.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto operator-(const Vector2D<U>& rhs) const noexcept
            -> Vector2D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;


        /**
         * @brief Subtract another vector from this vector component-wise.
         *        Perform an in-place substraction of @p rhs from the current instance.
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
        constexpr Vector2D& operator-=(const Vector2D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform a component-wise inversion.
         *        Invert the sign of each component and returns a new @ref Vector2D<T>.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @return A new @ref fgm::Vector2D with inverted components.
         */
        [[nodiscard]] constexpr Vector2D operator-() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Scale the vector by a scalar value.
         *        Multiply each component of the vector by @p scalar and returns a new vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Vector2D scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr auto operator*(S scalar) const noexcept -> Vector2D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;


        /**
         * @brief Scale this vector in-place by a scalar value.
         *        Perform an in-place multiplication of each component by @p scalar.
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
         * @brief Divide the vector by a scalar value.
         *        Divide each component of the vector by @p scalar and returns a new vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @warning Does not check for division by zero. @p scalar should be non-zero.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Vector2D scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr auto operator/(S scalar) const noexcept -> Vector2D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;


        /**
         * @brief Divide this vector in-place by a scalar value.
         *        Perform an in-place division of each component by @p scalar.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @warning Does not check for division by zero. @p scalar should be non-zero.
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
         * @brief Safely divide each component of this vector by a scalar value.
         *        Divide each component of the vector by @p scalar and returns the newly computed vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref fgm::StrictArithmetic.
         * @note Returns a zero-vector if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref fgm::StrictArithmetic.
         *
         * @param[in] scalar The value to divide the vector components by.
         *
         * @return A new @ref Vector2D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr auto safeDiv(S scalar) const noexcept -> Vector2D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely divide each component of a vector by a scalar value.
         *        Divide each component of the vector by @p scalar and returns the newly computed vector.
         *
         * @note Promote the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref fgm::StrictArithmetic.
         * @note Returns a zero-vector if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref fgm::StrictArithmetic.
         *
         * @param[in] vec The vector to divide.
         * @param[in] scalar The value to divide the vector components by.
         *
         * @return A new @ref Vector2D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr static auto safeDiv(const Vector2D& vec, S scalar) noexcept
            -> Vector2D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely divide this vector by a scalar value and set @p status to the division operation result.
         *        Divides each component of the vector by @p scalar and returns the newly computed vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref fgm::StrictArithmetic.
         * @note Returns a zero-vector if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
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
        [[nodiscard]] constexpr auto tryDiv(S scalar, OperationStatus& status) const noexcept
            -> Vector2D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely divide a vector by a scalar value and set @p status to the division operation result.
         *        Divides each component of the vector by @p scalar and returns the newly computed vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref fgm::StrictArithmetic.
         * @note Returns a zero-vector if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
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
        [[nodiscard]] static constexpr auto tryDiv(const Vector2D& vec, S scalar, OperationStatus& status) noexcept
            -> Vector2D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FGM_Vec2_Product
         * @{
         */

        /*************************************
         *                                   *
         *        VECTOR DOT PRODUCT         *
         *                                   *
         *************************************/

        /**
         * @brief Calculate the dot product of this vector with another vector.
         *        Compute the scalar product: \f$ \mathbf{a} \cdot \mathbf{b} = \sum_{i=1}^{4} a_i b_i \f$.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compute the dot product with.
         *
         * @return The scalar dot product of the two vectors.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto dot(const Vector2D<U>& rhs) const noexcept -> std::common_type_t<T, U>
            requires StrictArithmetic<T>;


        /**
         * @brief Calculate the dot product of a vector with another vector.
         *        Compute the scalar product: \f$ \mathbf{a} \cdot \mathbf{b} = \sum_{i=1}^{4} a_i b_i \f$.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
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
        [[nodiscard]] constexpr static auto dot(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
            -> std::common_type_t<T, U>
            requires StrictArithmetic<T>;



        /*************************************
         *                                   *
         *       VECTOR CROSS PRODUCT        *
         *                                   *
         *************************************/

        /**
         * @brief Calculate the pseudo-cross product of this vector with another vector.
         *        Compute the vector product: \f$ \mathbf{a}\times\mathbf{b} = (x_1\cdot y_2 - x_2\cdot y_1) \f$.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compute the cross product with.
         *
         * @return The pseudo-cross cross product of the two vectors.
         */
        template <Arithmetic U>
        constexpr auto cross(const Vector2D<U>& rhs) const noexcept -> std::common_type_t<T, U>;


        /**
         * @brief Calculate the pseudo-cross of a vector with another vector.
         *        Compute the vector product: \f$ \mathbf{a}\times\mathbf{b} = (x_1\cdot y_2 - x_2\cdot y_1) \f$.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The vector to compute the cross product with.
         * @param[in] rhs The vector to compute the cross product with.
         *
         * @return The pseudo-cross product of the two vectors.
         */
        template <Arithmetic U>
        constexpr static auto cross(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept -> std::common_type_t<T, U>;

        /** @} */


        /**
         * @addtogroup FGM_Vec2_Mag
         * @{
         */

        /*************************************
         *                                   *
         *         VECTOR MAGNITUDE          *
         *                                   *
         *************************************/

        /**
         * @brief Calculate the magnitude (length) of this vector.
         *        Compute the Euclidean norm: \f$ \|\mathbf{v}\| = \sqrt{\mathbf{v} \cdot \mathbf{v}} \f$.
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @return The scalar magnitude of the vector.
         */
        [[nodiscard]] constexpr Magnitude<T> mag() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Calculate the magnitude (length) of a vector.
         *        Compute the Euclidean norm: \f$ \|\mathbf{v}\| = \sqrt{\mathbf{v} \cdot \mathbf{v}} \f$.
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[in] vec The vector to compute the magnitude of.
         *
         * @return The scalar magnitude of @p vec.
         */
        [[nodiscard]] constexpr static Magnitude<T> mag(const Vector2D& vec) noexcept
            requires StrictArithmetic<T>;


        /*************************************
         *                                   *
         *       VECTOR NORMALIZATION        *
         *                                   *
         *************************************/

        /**
         * @brief Calculate the normalized (unit) form of this vector.
         *        Compute the unit vector in the same direction: \f$ \mathbf{\hat{v}} =
         *        \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @warning Does not check for zero-length vectors. @ref mag() must be non-zero.
         *
         * @return A new @ref Vector2D with a magnitude of 1.0.
         */
        [[nodiscard]] constexpr Vector2D<Magnitude<T>> normalize() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Calculate the normalized (unit) form of the vector.
         *        Compute the unit vector in the same direction: \f$ \mathbf{\hat{v}} =
         *        \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[in] vec The vector to normalize.
         *
         * @return A new @ref Vector2D with a magnitude of 1.0.
         */
        [[nodiscard]] constexpr static Vector2D<Magnitude<T>> normalize(const Vector2D& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Safely calculate the normalized (unit) form of this vector.
         *        Compute the unit vector in the same direction: \f$ \mathbf{\hat{v}} =
         *        \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @return A @ref fgm::Vector2D with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if this vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vector2D<Magnitude<T>> safeNormalize() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Safely calculate the normalized (unit) form of the vector.
         *        Compute the unit vector in the same direction: \f$ \mathbf{\hat{v}} =
         *        \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[in] vec The vector to be normalized.
         *
         * @return A @ref fgm::Vector2D with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr static Vector2D<Magnitude<T>> safeNormalize(const Vector2D& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Safely calculate the normalized (unit) form of this vector and
         *        set @p status to the normalization operation result.
         *        Compute the unit vector in the same direction: \f$ \mathbf{\hat{v}} =
         *        \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$.
         *
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
         * @brief Safely calculate the normalized (unit) form of the vector and
         *        set @p status to the normalization operation result.
         *        Compute the unit vector in the same direction: \f$ \mathbf{\hat{v}} =
         *        \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$.
         *
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
        [[nodiscard]] constexpr static Vector2D<Magnitude<T>> tryNormalize(const Vector2D& vec,
                                                                           OperationStatus& status) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FGM_Vec2_Proj
         * @{
         */

        /*************************************
         *                                   *
         *        VECTOR PROJECTION          *
         *                                   *
         *************************************/

        /**
         * @brief Project this vector onto another vector.
         *        Compute the orthogonal projection: \f$ \text{proj}_{\mathbf{b}} \mathbf{a} = \frac{\mathbf{a} \cdot
         *        \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto           The vector to project onto.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         *
         * @return The projected @ref Vector2D.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto project(const Vector2D<U>& onto, bool ontoNormalized = false) const noexcept
            -> Vector2D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief Project a vector onto another vector.
         *        Compute the orthogonal projection: \f$ \text{proj}_{\mathbf{b}} \mathbf{a} = \frac{\mathbf{a} \cdot
         *        \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec            The vector to project.
         * @param[in] onto           The vector to project onto.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         *
         * @return The projected @ref Vector2D.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static auto project(const Vector2D& vec, const Vector2D<U>& onto,
                                                    bool ontoNormalized = false) noexcept
            -> Vector2D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely project this vector onto another vector.
         *        Compute the orthogonal projection: \f$ \text{proj}_{\mathbf{b}} \mathbf{a} = \frac{\mathbf{a} \cdot
         *        \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto           The vector to project onto.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         *
         * @return The projected @ref Vector2D or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto safeProject(const Vector2D<U>& onto, bool ontoNormalized = false) const noexcept
            -> Vector2D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely project a vector onto another vector.
         *        Compute the orthogonal projection: \f$ \text{proj}_{\mathbf{b}} \mathbf{a} = \frac{\mathbf{a} \cdot
         *        \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec            The vector to project.
         * @param[in] onto           The vector to project onto.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         *
         * @return The projected @ref Vector2D or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static auto safeProject(const Vector2D& vec, const Vector2D<U>& onto,
                                                        bool ontoNormalized = false) noexcept
            -> Vector2D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely project this vector onto another vector and set @p status to the projection operation result.
         *        Compute the orthogonal projection: \f$ \text{proj}_{\mathbf{b}} \mathbf{a} = \frac{\mathbf{a} \cdot
         *        \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto           The vector to project onto.
         * @param[out] status        The status flag to store the status of the current operation result.
         *                           For details on status codes see @ref OperationStatus.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         *
         * @return The projected @ref Vector2D or a zero-vector if projected onto a zero-length vector or if either
         *         vector has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto tryProject(const Vector2D<U>& onto, OperationStatus& status,
                                                bool ontoNormalized = false) const noexcept
            -> Vector2D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely project a vector onto another vector and set @p status to the projection operation result.
         *        Compute the orthogonal projection: \f$ \text{proj}_{\mathbf{b}} \mathbf{a} = \frac{\mathbf{a} \cdot
         *        \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec            The vector to project.
         * @param[in] onto           The vector to project onto.
         * @param[out] status        The status flag to store the status of the current operation result.
         *                           For details on status codes see @ref OperationStatus.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         *
         * @return The projected @ref Vector2D or a zero-vector if projected onto a zero-length vector or if either
         *         vector has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static auto tryProject(const Vector2D& vec, const Vector2D<U>& onto,
                                                       OperationStatus& status, bool ontoNormalized = false) noexcept
            -> Vector2D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;



        /*************************************
         *                                   *
         *         VECTOR REJECTION          *
         *                                   *
         *************************************/

        /**
         * @brief Compute the vector rejection of this vector from another.
         *        Compute the component of the vector perpendicular to @p onto:
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from           The vector to reject from.
         * @param[in] fromNormalized Optimization flag. Set to `true` if @p from is already a unit vector.
         *
         * @return The perpendicular @ref Vector2D component.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto reject(const Vector2D<U>& from, bool fromNormalized = false) const noexcept
            -> Vector2D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the vector rejection of a vector from another.
         *        Compute the component of the vector perpendicular to @p onto:
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vector         The vector to be rejected.
         * @param[in] from           The vector to reject from.
         * @param[in] fromNormalized Optimization flag. Set to `true` if @p from is already a unit vector.
         *
         * @return The perpendicular @ref Vector2D component.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static auto reject(const Vector2D& vector, const Vector2D<U>& from,
                                                   bool fromNormalized = false) noexcept
            -> Vector2D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely compute rejection of this vector from another vector.
         *        Compute the component of the vector perpendicular to @p onto:
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from           The vector to reject from.
         * @param[in] fromNormalized Optimization flag. Set to `true` if @p from is already a unit vector.
         *
         * @return The perpendicular @ref Vector2D component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto safeReject(const Vector2D<U>& from, bool fromNormalized = false) const noexcept
            -> Vector2D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely compute rejection of a vector from another vector.
         *        Compute the component of the vector perpendicular to @p onto:
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec            The vector to reject.
         * @param[in] from           The vector to reject from.
         * @param[in] fromNormalized Optimization flag. Set to `true` if @p from is already a unit vector.
         *
         * @return The perpendicular @ref Vector2D component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static auto safeReject(const Vector2D& vec, const Vector2D<U>& from,
                                                       bool fromNormalized = false) noexcept
            -> Vector2D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely compute rejection of this vector from another vector and
         *        set @p status to the result of rejection operation.
         *        Compute the component of the vector perpendicular to @p onto:
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from           The vector to reject from
         * @param[out] status        The status flag to store the status of the current operation result.
         *                           For details on status codes see @ref OperationStatus.
         * @param[in] fromNormalized Optimization flag. Set to `true` if @p from is already a unit vector.
         *
         * @return The perpendicular @ref Vector2D component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto tryReject(const Vector2D<U>& from, OperationStatus& status,
                                               bool fromNormalized = false) const noexcept
            -> Vector2D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely compute rejection of a vector from another vector and
         *        set @p status to the result of rejection operation.
         *        Compute the component of the vector perpendicular to @p onto:
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec            The vector to reject.
         * @param[in] from           The vector to reject from.
         * @param[out] status        The status flag to store the status of the current operation result.
         *                           For details on status codes see @ref OperationStatus.
         * @param[in] fromNormalized Optimization flag. Set to `true` if @p from is already a unit vector.
         *
         * @return The perpendicular @ref Vector2D component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static auto tryReject(const Vector2D& vec, const Vector2D<U>& from,
                                                      OperationStatus& status, bool fromNormalized = false) noexcept
            -> Vector2D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FGM_Vec2_Utils
         * @{
         */

        /**
         * @brief Check if any component of this vector is an IEEE 754 infinity.
         *
         * @note Always returns false for integral types.
         *
         * @return True if at least one component is positive or negative infinity.
         */
        [[nodiscard]] constexpr bool hasInf() const noexcept;


        /**
         * @brief Check if any component of a vector is an IEEE 754 infinity.
         *
         * @note Always returns false for integral types.
         *
         * @param vec The vector to evaluate for indefinite components.
         *
         * @return True if at least one component is positive or negative infinity.
         */
        [[nodiscard]] constexpr static bool hasInf(const Vector2D& vec) noexcept;


        /**
         * @brief Check if any component of this vector is an IEEE NaN(Not-a-Number).
         *
         * @note Always returns false for integral types.
         *
         * @return True if at least one component is NaN.
         */
        [[nodiscard]] constexpr bool hasNaN() const noexcept;


        /**
         * @brief Check if any component of this vector is an IEEE NaN(Not-a-Number).
         *
         * @note Always returns false for integral types.
         *
         * @param vec The vector to evaluate for indefinite components.
         *
         * @return True if at least one component is NaN.
         */
        [[nodiscard]] constexpr static bool hasNaN(const Vector2D& vec) noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Vec2_Log
         * @{
         */

        /**
         * @brief Write the vector to an output stream.
         *        Format the vector as <x, y> string representation for debugging or logging.
         *
         * @tparam T Numeric type of the vector.
         *
         * @param os     The output stream to write to.
         * @param vector The vector to be streamed.
         *
         * @return A reference to the output stream @p os.
         */
        constexpr friend std::ostream& operator<<(std::ostream& os, const Vector2D& vector)
        {
            const std::streamsize oldPrecision = os.precision();
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
        T _data[dimension];
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
     * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
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
    [[nodiscard]] constexpr auto operator*(S scalar, const Vector2D<T>& vector) noexcept
        -> Vector2D<std::common_type_t<T, S>>
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

    using bVec2 = Vector2D<bool>;                ///< `bool` vector
    using iVec2 = Vector2D<int>;                 ///< `int` vector
    using uVec2 = Vector2D<unsigned int>;        ///< `unsigned int` vector
    using vec2 = Vector2D<float>;                ///< `float` vector
    using lVec2 = Vector2D<long long>;           ///< `long long` vector
    using dVec2 = Vector2D<double>;              ///< `double` vector
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

    /** @} */


} // namespace fgm


#include "Vector2D.tpp"