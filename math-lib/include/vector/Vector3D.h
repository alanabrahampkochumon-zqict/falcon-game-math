#pragma once
/**
 * @file Vector3D.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 19, 2026
 *
 * @brief Templated 3D Vector supporting integral, floating-point, and boolean types.
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


#include "Vector2D.h"
#include "common/Config.h"
#include "common/Constants.h"
#include "common/OperationStatus.h"

#include <type_traits>


namespace fgm
{
    template <Arithmetic T>
    struct Vector3D
    {
        /**
         * @addtogroup FGM_Vec4_Members
         * @{
         */

        using value_type = T;

        static constexpr std::size_t dimension = 3;

        union {
            struct
            {
                T x; ///< X-axis component
                T y; ///< Y-axis component
                T z; ///< Z-axis component
            };
            struct
            {
                T r; ///< Red channel
                T g; ///< Green channel
                T b; ///< Blue channel
            };
            struct
            {
                T s; ///< S-coordinate
                T t; ///< T-coordinate
                T p; ///< P-coordinate
            };

            T elements[dimension];
        };

        /** @} */



        /**
         * @addtogroup FGM_Vec4_Init
         * @{
         */

        /*************************************
         *                                   *
         *            INITIALIZERS           *
         *                                   *
         *************************************/

        /** @brief Initialize @ref Vector3D with zeros. */
        [[nodiscard]] constexpr Vector3D() noexcept;


        /**
         * @brief Initialize @ref Vector3D with passed in values.
         *
         * @param[in] v1 The first entry of @ref Vector3D.
         * @param[in] v2 The second entry of @ref Vector3D.
         * @param[in] v3 The third entry of @ref Vector3D.
         */
        [[nodiscard]] constexpr Vector3D(T v1, T v2, T v3) noexcept;


        /**
         * @brief Initialize @ref Vector3D with 1 @ref Vector2D and 1 @ref T value.
         *
         * @param[in] vec The first two entries of @ref Vector3D.
         * @param[in] v   The last entry of @ref Vector3D.
         */
        [[nodiscard]] constexpr Vector3D(Vector2D<T> vec, T v) noexcept;


        /**
         * @brief Initialize @ref Vector3D with 1 @ref T value and 1 @ref Vector2D.
         *
         * @param[in] v   The first entry of @ref Vector3D.
         * @param[in] vec The last two entries of @ref Vector3D.
         */
        [[nodiscard]] constexpr Vector3D(T v, Vector2D<T> vec) noexcept;


        /**
         * @brief Initialize @ref Vector3D from another @ref Vector3D of a different type.
         *
         * @tparam U Numeric type of the source vector.
         *
         * @param[in] other The source vector to be converted.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr Vector3D(const Vector3D<U>& other) noexcept;


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
        T& operator[](std::size_t i);


        /**
         * @brief Access the element at the specified location (read-only).
         *
         * @param[in] i The index of the vector component.
         *
         * @return A const reference to the vector component.
         */
        const T& operator[](std::size_t i) const;

        /** @} */



        /**
         * @addtogroup FGM_Vec3_Equality
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
        [[nodiscard]] constexpr bool allEq(const Vector3D<U>& rhs,
                                           double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                               ? Config::DOUBLE_EPSILON
                                               : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @copybrief allEq(const Vector3D<U>&, double) const
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
        [[nodiscard]] constexpr static bool allEq(const Vector3D& lhs, const Vector3D<U>& rhs,
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
        [[nodiscard]] constexpr bool allNeq(const Vector3D<U>& rhs,
                                            double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                                ? Config::DOUBLE_EPSILON
                                                : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @copybrief allNeq(const Vector3D<U>&, double) const
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
        [[nodiscard]] constexpr static bool allNeq(const Vector3D& lhs, const Vector3D<U>& rhs,
                                                   double epsilon = (std::is_same_v<T, double> ||
                                                                     std::is_same_v<U, double>)
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) noexcept;


        /**
         * @copybrief allEq(const Vector3D<U>&, double) const
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
        [[nodiscard]] constexpr bool operator==(const Vector3D<U>& rhs) const noexcept;


        /**
         * @copybrief allNeq(const Vector3D<U>&, double) const
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
        [[nodiscard]] constexpr bool operator!=(const Vector3D<U>& rhs) const noexcept;


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
         * @return A @ref Vector3D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr Vector3D<bool> eq(const Vector3D<U>& rhs,
                                                  double epsilon = (std::is_same_v<T, double> ||
                                                                    std::is_same_v<U, double>)
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @copybrief eq(const Vector3D<U>&, double) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Vector3D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr static Vector3D<bool> eq(const Vector3D& lhs, const Vector3D<U>& rhs,
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
         * @return A @ref Vector3D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr Vector3D<bool> neq(const Vector3D<U>& rhs,
                                                   double epsilon = (std::is_same_v<T, double> ||
                                                                     std::is_same_v<U, double>)
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @copybrief neq(const Vector3D<U>&, double) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Vector3D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr static Vector3D<bool> neq(const Vector3D& lhs, const Vector3D<U>& rhs,
                                                          double epsilon = (std::is_same_v<T, double> ||
                                                                            std::is_same_v<U, double>)
                                                              ? Config::DOUBLE_EPSILON
                                                              : Config::FLOAT_EPSILON) noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Vec4_Comparison
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
         * @return A @ref Vector3D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector3D<bool> gt(const Vector3D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copybrief gt(const Vector3D<U>&) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref Vector3D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static Vector3D<bool> gt(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than-or-equal comparison.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return A @ref Vector3D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector3D<bool> gte(const Vector3D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copybrief gte(const Vector3D<U>&) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref Vector3D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static Vector3D<bool> gte(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
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
         * @return A @ref Vector3D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector3D<bool> lt(const Vector3D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copybrief lt(const Vector3D<U>&) const
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to compiler-level
         *       constant folding bugs. Runtime execution remains IEEE 754 compliant under /fp:strict
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref Vector3D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static Vector3D<bool> lt(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
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
         * @return A @ref Vector3D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector3D<bool> lte(const Vector3D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copybrief lte(const Vector3D<U>&) const
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to compiler-level
         *       constant folding bugs. Runtime execution remains IEEE 754 compliant under /fp:strict
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref Vector3D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static Vector3D<bool> lte(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


#ifdef ENABLE_FGM_SHADER_OPERATORS

        /**
         * @copydoc gt(const Vector3D<U>&) const
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector3D<bool> operator>(const Vector3D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc gte(const Vector3D<U>&) const
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector3D<bool> operator>=(const Vector3D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc lt(const Vector3D<U>&) const
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector3D<bool> operator<(const Vector3D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc lte(const Vector3D<U>&) const
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector3D<bool> operator<=(const Vector3D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;
#endif

        /** @} */



        /**
         * @addtogroup FGM_Vec3_Bitwise
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
         * @note Only available for @ref bVec3 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A @ref Vector3D<bool> mask containing the results of component-wise AND.
         */
        [[nodiscard]] constexpr Vector3D<bool> operator&(const Vector3D<bool>& rhs) const noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise logical AND.
         *        Compute the conjunction of each component pair in-place and update the calling vector.
         *
         * @note Only available for @ref bVec3 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A reference to this vector (*this).
         */
        constexpr Vector3D<bool>& operator&=(const Vector3D<bool>& rhs) noexcept;


        /**
         * @brief Perform component-wise logical OR.
         *        Compute the disjunction of each component pair.
         *
         * @note Only available for @ref bVec3 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A @ref Vector3D<bool> mask containing the results of component-wise OR.
         */
        [[nodiscard]] constexpr Vector3D<bool> operator|(const Vector3D<bool>& rhs) const noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise logical OR.
         *        Compute the disjunction of each component pair in-place and update the calling vector.
         *
         * @note Only available for @ref bVec3 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A reference to this vector (*this).
         */
        constexpr Vector3D<bool>& operator|=(const Vector3D<bool>& rhs) noexcept;


        /**
         * @brief Perform component-wise logical NOT.
         *        Invert each boolean component and returns a new @ref Vector3D<bool>.
         *
         * @note Only available for @ref bVec3 and vectors with `bool` value_type.
         *
         * @return A @ref Vector3D<bool> with inverted values.
         */
        [[nodiscard]] constexpr Vector3D<bool> operator!() const noexcept
            requires std::is_same_v<T, bool>;

        /** @} */



        /**
         * @addtogroup FGM_Vec3_Arithmetic
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
         * @return A new @ref Vector3D containing the component-wise sum.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto operator+(const Vector3D<U>& rhs) const noexcept
            -> Vector3D<std::common_type_t<T, U>>
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
        constexpr Vector3D& operator+=(const Vector3D<U>& rhs) noexcept
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
         * @return A new @ref Vector3D containing the component-wise difference.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto operator-(const Vector3D<U>& rhs) const noexcept
            -> Vector3D<std::common_type_t<T, U>>
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
        constexpr Vector3D& operator-=(const Vector3D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform a component-wise inversion.
         *        Invert the sign of each component and returns a new @ref Vector3D<T>.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @return A new @ref fgm::Vector3D with inverted components.
         */
        [[nodiscard]] constexpr Vector3D operator-() const noexcept
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
         * @return A new @ref Vector3D scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr auto operator*(S scalar) const noexcept -> Vector3D<std::common_type_t<T, S>>
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
        constexpr Vector3D& operator*=(S scalar) noexcept
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
         * @return A new @ref Vector3D scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr auto operator/(S scalar) const noexcept -> Vector3D<std::common_type_t<T, S>>
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
        constexpr Vector3D& operator/=(S scalar) noexcept
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
         * @return A new @ref Vector3D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr auto safeDiv(S scalar) const noexcept -> Vector3D<std::common_type_t<T, S>>
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
         * @return A new @ref Vector3D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr static auto safeDiv(const Vector3D& vec, S scalar) noexcept
            -> Vector3D<std::common_type_t<T, S>>
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
         * @return A new @ref Vector3D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors+ has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr auto tryDiv(S scalar, OperationStatus& status) const noexcept
            -> Vector3D<std::common_type_t<T, S>>
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
         * @return A new @ref Vector3D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors+ has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr auto tryDiv(const Vector3D& vec, S scalar, OperationStatus& status) noexcept
            -> Vector3D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FGM_Vec4_Product
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
        [[nodiscard]] constexpr auto dot(const Vector3D<U>& rhs) const noexcept -> std::common_type_t<T, U>
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
        [[nodiscard]] constexpr static auto dot(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
            -> std::common_type_t<T, U>
            requires StrictArithmetic<T>;



        /*************************************
         *                                   *
         *       VECTOR CROSS PRODUCT        *
         *                                   *
         *************************************/

        /**
         * @brief Calculate the cross product of this vector with another vector.
         *        Compute the vector product: \f$ \mathbf{a}\times\mathbf{b} = (a_2\cdot b_3 - a_3\cdot b_2) - (a_1\cdot
         *                                         b_3 - a_3\cdot b_1) + (a_1\cdot b_2 - a_2\cdot b_1) \f$.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compute the cross product with.
         *
         * @return The vector cross product of the two vectors.
         */
        template <Arithmetic U>
        constexpr auto cross(const Vector3D<U>& rhs) const noexcept -> Vector3D<std::common_type_t<T, U>>;


        /**
         * @brief Calculate the cross product of a vector with another vector.
         *        Compute the vector product: \f$ \mathbf{a}\times\mathbf{b} = (a_2\cdot b_3 - a_3\cdot b_2) - (a_1\cdot
         *                                         b_3 - a_3\cdot b_1) + (a_1\cdot b_2 - a_2\cdot b_1) \f$.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The vector to compute the cross product with.
         * @param[in] rhs The vector to compute the cross product with.
         *
         * @return The vector cross product of the two vectors.
         */
        template <Arithmetic U>
        constexpr static auto cross(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
            -> Vector3D<std::common_type_t<T, U>>;

        /** @} */



        /**
         * @addtogroup FGM_Vec4_Mag
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
        [[nodiscard]] constexpr static Magnitude<T> mag(const Vector3D& vec) noexcept
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
         * @return A new @ref Vector3D with a magnitude of 1.0.
         */
        [[nodiscard]] constexpr Vector3D<Magnitude<T>> normalize() const noexcept
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
         * @return A new @ref Vector3D with a magnitude of 1.0.
         */
        [[nodiscard]] constexpr static Vector3D<Magnitude<T>> normalize(const Vector3D& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Safely calculate the normalized (unit) form of this vector.
         *        Compute the unit vector in the same direction: \f$ \mathbf{\hat{v}} =
         *        \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @return A @ref fgm::Vector3D with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if this vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vector3D<Magnitude<T>> safeNormalize() const noexcept
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
         * @return A @ref fgm::Vector3D with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr static Vector3D<Magnitude<T>> safeNormalize(const Vector3D& vec) noexcept
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
         * @return A @ref fgm::Vector3D with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if this vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr Vector3D<Magnitude<T>> tryNormalize(OperationStatus& status) const noexcept
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
         * @return A @ref fgm::Vector3D with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr static Vector3D<Magnitude<T>> tryNormalize(const Vector3D& vec,
                                                                           OperationStatus& status) noexcept
            requires StrictArithmetic<T>;

        /** @} */

        /** @} */

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
        auto project(const Vector3D<U>& onto, bool ontoNormalized = false) const -> Vector3D<std::common_type_t<T, U>>;

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
        static auto project(const Vector3D& vector, const Vector3D<U>& onto, bool ontoNormalized = false)
            -> Vector3D<std::common_type_t<T, U>>;


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
        auto reject(const Vector3D<U>& onto, bool ontoNormalized = false) const -> Vector3D<std::common_type_t<T, U>>;

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
        static auto reject(const Vector3D& vector, const Vector3D<U>& onto, bool ontoNormalized = false)
            -> Vector3D<std::common_type_t<T, U>>;


        /**
         * @addtogroup FGM_Vec3_Utils
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
        [[nodiscard]] constexpr static bool hasInf(const Vector3D& vec) noexcept;


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
        [[nodiscard]] constexpr static bool hasNaN(const Vector3D& vec) noexcept;

        /** @} */
    };



    /*************************************
     *                                   *
     *       NON-MEMBER FUNCTIONS        *
     *                                   *
     *************************************/

    /**
     * @addtogroup FGM_Vec4_Arithmetic
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
     * @return A new @ref Vector3D scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    [[nodiscard]] constexpr auto operator*(S scalar, const Vector3D<T>& vector) noexcept
        -> Vector3D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>;

    /** @} */



    /**
     * @addtogroup FGM_Vec4_Alias
     * @{
     */

    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/

    using bVec3 = Vector3D<bool>;                ///< `bool` vector
    using iVec3 = Vector3D<int>;                 ///< `int` vector
    using uVec3 = Vector3D<unsigned int>;        ///< `unsigned int` vector
    using vec3 = Vector3D<float>;                ///< `float` vector
    using lVec3 = Vector3D<long long>;           ///< `long long` vector
    using dVec3 = Vector3D<double>;              ///< `double` vector
    using ulVec3 = Vector3D<unsigned long long>; ///< `unsigned long long` vector

    /** @} */



    /**
     * @addtogroup FGM_Vec3_Const
     * @{
     */

    /*************************************
     *                                   *
     *            CONSTANTS              *
     *                                   *
     *************************************/
    namespace vec3d
    {

        /**
         * @brief A 3D vector with all components set to one (1, 1, 1).
         *
         * @note Only available for @ref fgm::StrictArithmetic types.
         */
        template <StrictArithmetic T>
        inline constexpr Vector3D<T> one = Vector3D<T>(T(1), T(1), T(1));


        /**
         * @brief A 3D vector with all components set to zero (0, 0, 0).
         *
         * @note Only available for @ref fgm::StrictArithmetic types.
         */
        template <StrictArithmetic T>
        inline constexpr Vector3D<T> zero = Vector3D<T>(T(0), T(0), T(0)); ///< 3D-Vector with all zero-components.


        /**
         * @brief A 3D vector with all components set to positive infinity.
         *
         * @note Only available for `std::floating_point` types.
         */
        template <StrictArithmetic T>
            requires std::floating_point<T>
        inline constexpr Vector3D<T> inf =
            Vector3D<T>(T(constants::INFINITY_D), T(constants::INFINITY_D), T(constants::INFINITY_D));


        /**
         * @brief A 3D vector with all components set to negative infinity.
         *
         * @note Only available for `std::floating_point` types.
         */
        template <StrictArithmetic T>
            requires std::floating_point<T>
        inline constexpr Vector3D<T> infN =
            Vector3D<T>(T(-constants::INFINITY_D), T(-constants::INFINITY_D), T(-constants::INFINITY_D));


        /**
         * @brief A 3D vector with all components set to Not-A-Number (NaN).
         *
         * @note Only available for `std::floating_point` types.
         */
        template <StrictArithmetic T>
            requires std::floating_point<T>
        inline constexpr Vector3D<T> nan = Vector3D<T>(T(constants::NaN_D), T(constants::NaN_D), T(constants::NaN_D));


        /** @brief A 3D unit vector aligned with the positive X-axis (1, 0, 0). */
        template <StrictArithmetic T>
        inline constexpr Vector3D<T> x = Vector3D<T>(T(1), T(0), T(0));


        /** @brief A 3D unit vector aligned with the positive Y-axis (0, 1, 0). */
        template <StrictArithmetic T>
        inline constexpr Vector3D<T> y = Vector3D<T>(T(0), T(1), T(0));


        /** @brief A 3D unit vector aligned with the positive Z-axis (0, 0, 1). */
        template <StrictArithmetic T>
        inline constexpr Vector3D<T> z = Vector3D<T>(T(0), T(0), T(1));


    } // namespace vec3d

    /** @} */

} // namespace fgm

#include "Vector3D.tpp"