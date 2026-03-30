#pragma once
/**
 * @file Vector4D.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 26, 2026
 *
 * @brief Templated 4D Vector supporting integral, floating-point, and boolean types.
 *
 * @todo Provides a high-performance vector implementation with SIMD acceleration
 *       and support for component-wise operations.
 *
 * @tparam T Type of @ref Vector4D components. Must satisfy @ref Arithmetic.
 *
 * @note Arithmetic operations are restricted to numeric types via @ref StrictArithmetic.
 *
 * @par Configuration
 * - Define `ENABLE_FGM_SHADER_OPERATORS` to enable comparison operators (`,`, `<`, etc.).
 *   Even if disabled, functional comparisons like @ref gt remain available.
 * - Define `FORCE_SCALAR` to disable SIMD optimizations (enabled by default on supported hardware).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vector2D.h"
#include "Vector3D.h"
#include "common/Config.h"
#include "common/Constants.h"
#include "common/MathTraits.h"
#include "common/OperationStatus.h"

#include <cstddef>
#include <iomanip>
#include <ostream>

// TODO: TryDivide, TryNormalize, TryProject, TryReject custom abs function.
// TODO: Make all functions [[nodiscard]]

namespace fgm
{

    template <Arithmetic T>
    struct Vector4D
    {

        /**
         * @addtogroup FGM_Vec4_Members
         * @{
         */

        using value_type = T;

        static constexpr std::size_t dimension = 4; ///< Vector Dimension

        union {
            struct
            {
                T x; ///< X-axis component
                T y; ///< Y-axis component
                T z; ///< Z-axis component
                T w; ///< W-axis (homogeneous) component
            };
            struct
            {
                T r; ///< Red channel
                T g; ///< Green channel
                T b; ///< Blue channel
                T a; ///< Alpha channel
            };
            struct
            {
                T s; ///< S-coordinate
                T t; ///< T-coordinate
                T p; ///< P-coordinate
                T q; ///< Q-coordinate
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

        /** @brief Initialize @ref fgm::Vector4D with zeros. */
        [[nodiscard]] constexpr Vector4D() noexcept;


        /**
         * @brief Initialize @ref fgm::Vector4D with passed in values.
         *
         * @param[in] v1 First entry of @ref fgm::Vector4D.
         * @param[in] v2 Second entry of @ref fgm::Vector4D.
         * @param[in] v3 Third entry of @ref fgm::Vector4D.
         * @param[in] v4 Fourth entry of @ref fgm::Vector4D.
         */
        [[nodiscard]] constexpr Vector4D(T v1, T v2, T v3, T v4) noexcept;


        /**
         * @brief Initialize @ref fgm::Vector4D with 2 @ref Vector2D.
         *
         * @param[in] vec1 First two entries of @ref fgm::Vector4D.
         * @param[in] vec2 Last two entries of @ref fgm::Vector4D.
         */
        [[nodiscard]] constexpr Vector4D(const Vector2D<T>& vec1, const Vector2D<T>& vec2) noexcept;


        /**
         * @brief Initialize @ref fgm::Vector4D with 1 @ref Vector3D and 1 @ref T value.
         *
         * @param[in] vec First three entries of @ref fgm::Vector4D.
         * @param[in] v   Last entry for @ref fgm::Vector4D.
         */
        [[nodiscard]] constexpr Vector4D(const Vector3D<T>& vec, T v) noexcept;


        /**
         * @brief Initialize @ref fgm::Vector4D with 1 T value and 1 @ref Vector3D.
         *
         * @param[in] vec First three entries of @ref fgm::Vector4D.
         * @param[in] v   Last entry for @ref fgm::Vector4D.
         */
        [[nodiscard]] constexpr Vector4D(T v, const Vector3D<T>& vec) noexcept;


        /**
         * @brief Initialize @ref fgm::Vector4D from another @ref fgm::Vector4D of a different type.
         *
         * @tparam U Numeric type of the source vector.
         *
         * @param[in] other Source vector to be converted.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr Vector4D(const Vector4D<U>& other) noexcept;


        /*************************************
         *                                   *
         *            ACCESSORS              *
         *                                   *
         *************************************/

        /**
         * @brief Access the component at the specified location.
         *        Provide read-write access to the element.
         *
         * @param[in] i Index of the vector component.
         *
         * @return Reference to the vector component.
         */
        [[nodiscard]] constexpr T& operator[](std::size_t i) noexcept;


        /**
         * @brief Access the element at the specified location (read-only).
         *
         * @param[in] i Index of the vector component.
         *
         * @return A const reference to the vector component.
         */
        [[nodiscard]] constexpr const T& operator[](std::size_t i) const noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Vec4_Equality
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
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr bool allEq(const Vector4D<U>& rhs,
                                           double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                               ? Config::DOUBLE_EPSILON
                                               : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @copybrief allEq(const Vector4D<U>&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs    First vector to compare.
         * @param[in] rhs    Second vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return True if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr static bool allEq(const Vector4D& lhs, const Vector4D<U>& rhs,
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
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if any of the components are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr bool allNeq(const Vector4D<U>& rhs,
                                            double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                                ? Config::DOUBLE_EPSILON
                                                : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @copybrief allNeq(const Vector4D<U>&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref neq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     First vector to compare.
         * @param[in] rhs     Second vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if any of the components are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr static bool allNeq(const Vector4D& lhs, const Vector4D<U>& rhs,
                                                   double epsilon = (std::is_same_v<T, double> ||
                                                                     std::is_same_v<U, double>)
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) noexcept;


        /**
         * @copybrief allEq(const Vector4D<U>&, double) const
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
        [[nodiscard]] constexpr bool operator==(const Vector4D<U>& rhs) const noexcept;


        /**
         * @copybrief allNeq(const Vector4D<U>&, double) const
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
        [[nodiscard]] constexpr bool operator!=(const Vector4D<U>& rhs) const noexcept;


        /**
         * @brief Perform component-wise equality check.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note To obtain a single scalar result, use @ref allEq or @ref operator==.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs   The vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr Vector4D<bool> eq(const Vector4D<U>& rhs,
                                                  double epsilon = (std::is_same_v<T, double> ||
                                                                    std::is_same_v<U, double>)
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @copybrief eq(const Vector4D<U>&, double) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     First vector to compare.
         * @param[in] rhs     Second vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr static Vector4D<bool> eq(const Vector4D& lhs, const Vector4D<U>& rhs,
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
         * @param[in] rhs   The vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr Vector4D<bool> neq(const Vector4D<U>& rhs,
                                                   double epsilon = (std::is_same_v<T, double> ||
                                                                     std::is_same_v<U, double>)
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @copybrief neq(const Vector4D<U>&, double) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs    First vector to compare.
         * @param[in] rhs    Second vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr static Vector4D<bool> neq(const Vector4D& lhs, const Vector4D<U>& rhs,
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
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector4D<bool> gt(const Vector4D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copybrief gt(const Vector4D<U>&) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs First vector to compare.
         * @param[in]  rhs Second vector to compare against.
         *
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static Vector4D<bool> gt(const Vector4D& lhs, const Vector4D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than-or-equal comparison.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector4D<bool> gte(const Vector4D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copybrief gte(const Vector4D<U>&) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs First vector to compare.
         * @param[in]  rhs Second vector to compare against.
         *
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static Vector4D<bool> gte(const Vector4D& lhs, const Vector4D<U>& rhs) noexcept
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
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector4D<bool> lt(const Vector4D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copybrief lt(const Vector4D<U>&) const
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to compiler-level
         *       constant folding bugs. Runtime execution remains IEEE 754 compliant under /fp:strict
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs First vector to compare.
         * @param[in]  rhs Second vector to compare against.
         *
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static Vector4D<bool> lt(const Vector4D& lhs, const Vector4D<U>& rhs) noexcept
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
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector4D<bool> lte(const Vector4D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copybrief lt(const Vector4D<U>&) const
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to compiler-level
         *       constant folding bugs. Runtime execution remains IEEE 754 compliant under /fp:strict
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs First vector to compare.
         * @param[in]  rhs Second vector to compare against.
         *
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static Vector4D<bool> lte(const Vector4D& lhs, const Vector4D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


#ifdef ENABLE_FGM_SHADER_OPERATORS

        /**
         * @copydoc gt(const Vector4D<U>&) const
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector4D<bool> operator>(const Vector4D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc gte(const Vector4D<U>&) const
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector4D<bool> operator>=(const Vector4D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc lt(const Vector4D<U>&) const
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector4D<bool> operator<(const Vector4D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc lte(const Vector4D<U>&) const
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr Vector4D<bool> operator<=(const Vector4D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;
#endif

        /** @} */



        /**
         * @addtogroup FGM_Vec4_Bitwise
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
         * @note Only available for @ref bVec4 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A @ref Vector4D<bool> mask containing the results of component-wise AND.
         */
        [[nodiscard]] constexpr Vector4D<bool> operator&(const Vector4D<bool>& rhs) const noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise logical AND.
         *        Compute the conjunction of each component pair in-place and update the calling vector.
         *
         * @note Only available for @ref bVec4 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A reference to this vector (*this).
         */
        constexpr Vector4D<bool>& operator&=(const Vector4D<bool>& rhs) noexcept;


        /**
         * @brief Perform component-wise logical OR.
         *        Compute the disjunction of each component pair.
         *
         * @note Only available for @ref bVec4 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A @ref Vector4D<bool> mask containing the results of component-wise OR.
         */
        [[nodiscard]] constexpr Vector4D<bool> operator|(const Vector4D<bool>& rhs) const noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise logical OR.
         *        Compute the disjunction of each component pair in-place and update the calling vector.
         *
         * @note Only available for @ref bVec4 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A reference to this vector (*this).
         */
        constexpr Vector4D<bool>& operator|=(const Vector4D<bool>& rhs) noexcept;


        /**
         * @brief Perform component-wise logical NOT.
         *        Invert each boolean component and returns a new @ref Vector4D<bool>.
         *
         * @note Only available for @ref bVec4 and vectors with `bool` value_type.
         *
         * @return A @ref Vector4D<bool> with inverted values.
         */
        [[nodiscard]] constexpr Vector4D<bool> operator!() const noexcept
            requires std::is_same_v<T, bool>;

        /** @} */



        /**
         * @addtogroup FGM_Vec4_Arithmetic
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
         * @return A new @ref Vector4D containing the component-wise sum.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto operator+(const Vector4D<U>& rhs) const noexcept
            -> Vector4D<std::common_type_t<T, U>>
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
        constexpr Vector4D& operator+=(const Vector4D<U>& rhs) noexcept
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
         * @return A new @ref Vector4D containing the component-wise difference.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto operator-(const Vector4D<U>& rhs) const noexcept
            -> Vector4D<std::common_type_t<T, U>>
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
        constexpr Vector4D& operator-=(const Vector4D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform a component-wise inversion.
         *        Invert the sign of each component and returns a new @ref Vector4D<T>.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @return A new @ref fgm::Vector4D with inverted components.
         */
        [[nodiscard]] constexpr Vector4D operator-() const noexcept
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
         * @return A new @ref Vector4D scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr auto operator*(S scalar) const noexcept -> Vector4D<std::common_type_t<T, S>>
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
        constexpr Vector4D& operator*=(S scalar) noexcept
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
         * @return A new @ref Vector4D scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr auto operator/(S scalar) const noexcept -> Vector4D<std::common_type_t<T, S>>
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
        constexpr Vector4D& operator/=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Safely divides the vector by a scalar value.
         *        Divides each component of the vector by @p scalar and returns the newly computed vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref fgm::StrictArithmetic.
         * @note Returns a zero-vector if dividing by a floating point zero.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref fgm::StrictArithmetic.
         *
         * @param[in] scalar The value to divide the vector components by.
         *
         * @return A new @ref Vector4D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr auto safeDiv(S scalar) const noexcept -> Vector4D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;


        /**
         * @brief Static wrapper for safe scalar division.
         *
         * @copybrief tryDiv(S) const
         *
         * @note Operation is restricted to numeric types via @ref fgm::StrictArithmetic.
         * @note Returns a zero-vector if dividing by a floating point zero.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref fgm::StrictArithmetic.
         *
         * @param[in] vec The vector to divide.
         * @param[in] scalar The value to divide the vector components by.
         *
         * @return A new @ref Vector4D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr static auto safeDiv(const Vector4D& vec, S scalar) noexcept
            -> Vector4D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely divides this vector by a scalar value and set @p status to the division operation result.
         *        Divides each component of the vector by @p scalar and returns the newly computed vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref fgm::StrictArithmetic.
         * @note Returns a zero-vector if dividing by a floating point zero.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref fgm::StrictArithmetic.
         *
         * @param[in] scalar  The value to divide the vector components by.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A new @ref Vector4D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr auto tryDiv(S scalar, OperationStatus& status) const noexcept -> Vector4D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely divides a vector by a scalar value and set @p status to the division operation result.
         *        Divides each component of the vector by @p scalar and returns the newly computed vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref fgm::StrictArithmetic.
         * @note Returns a zero-vector if dividing by a floating point zero.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref fgm::StrictArithmetic.
         *
         * @param[in] vec     The vector to divide.
         * @param[in] scalar  The value to divide the vector components by.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A new @ref Vector4D resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold.
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr auto tryDiv(const Vector4D& vec, S scalar, OperationStatus& status) noexcept
            -> Vector4D<std::common_type_t<T, S>>
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
         * @brief Calculate the dot product with another vector.
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
        [[nodiscard]] constexpr auto dot(const Vector4D<U>& rhs) const noexcept -> std::common_type_t<T, U>
            requires StrictArithmetic<T>;


        /**
         * @brief @copybrief dot(const Vector4D<U>&) const
         * Static wrapper that compute \f$ \mathbf{lhs} \cdot \mathbf{rhs} \f$.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs First vector to perform the dot product on.
         * @param[in] rhs Second vector to perform the dot product on.
         *
         * @return The scalar dot product of @p lhs and @p rhs.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static auto dot(const Vector4D& lhs, const Vector4D<U>& rhs) noexcept
            -> std::common_type_t<T, U>
            requires StrictArithmetic<T>;

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
         * @brief Calculate the magnitude (length) of the vector.
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
         * @brief @copybrief mag() const
         * Static wrapper that compute \f$ \|\mathbf{vec}\| \f$.
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[in] vec The vector to compute the magnitude of.
         *
         * @return The scalar magnitude of @p vec.
         */
        [[nodiscard]] constexpr static Magnitude<T> mag(const Vector4D& vec) noexcept
            requires StrictArithmetic<T>;


        /*************************************
         *                                   *
         *       VECTOR NORMALIZATION        *
         *                                   *
         *************************************/

        /**
         * @brief Calculate the normalized (unit) form of the vector.
         *        Compute the unit vector in the same direction: \f$ \mathbf{\hat{v}} =
         * \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         * @warning Does not check for zero-length vectors. @ref mag() must be non-zero.
         *
         * @return A new @ref Vector4D with a magnitude of 1.0.
         */
        [[nodiscard]] constexpr Vector4D<Magnitude<T>> normalize() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief @copybrief normalize() const
         * Static wrapper that compute the unit vector \f$ \mathbf{\hat{v}} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[in] vec The vector to normalize.
         * @return A new @ref Vector4D with a magnitude of 1.0.
         */
        [[nodiscard]] constexpr static Vector4D<Magnitude<T>> normalize(const Vector4D& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Safely calculate the normalized (unit) form of the vector.
         *        Compute the unit vector in the same direction: \f$ \mathbf{\hat{v}} =
         * \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @return A @ref fgm::Vector4D with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         * epsilon threshold.
         */
        [[nodiscard]] constexpr Vector4D<Magnitude<T>> safeNormalize() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Static wrapper for safe normalization.
         *
         * @copydoc safeNormalize() const
         *
         * @param[in] vec The vector to be normalized.
         */
        [[nodiscard]] constexpr static Vector4D<Magnitude<T>> safeNormalize(const Vector4D& vec) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FGM_Vec4_Proj
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
         * @return The projected @ref Vector4D.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto project(const Vector4D<U>& onto, bool ontoNormalized = false) const noexcept
            -> Vector4D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief Project a vector onto another vector.
         *        Compute the orthogonal projection: \f$ \text{proj}_{\mathbf{b}} \mathbf{a} = \frac{\mathbf{a} \cdot
         *        \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b} \f$.
         * @brief Static wrapper for orthogonal projection of @p vector onto @p onto.
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
         * @return The projected @ref Vector4D.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static auto project(const Vector4D& vec, const Vector4D<U>& onto,
                                                    bool ontoNormalized = false) noexcept
            -> Vector4D<Magnitude<std::common_type_t<T, U>>>
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
         * @return The projected @ref Vector4D or a zero-vector if projected onto a zero-length vector.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto safeProject(const Vector4D<U>& onto, bool ontoNormalized = false) const noexcept
            -> Vector4D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief Safely project a vector onto another vector.
         *        Compute the orthogonal projection: \f$ \text{proj}_{\mathbf{b}} \mathbf{a} = \frac{\mathbf{a} \cdot
         *        \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b} \f$.
         * @brief Static wrapper for safe projection.
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
         * @return The projected @ref Vector4D or a zero-vector if projected onto a zero-length vector.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static auto safeProject(const Vector4D& vec, const Vector4D<U>& onto,
                                                        bool ontoNormalized = false) noexcept
            -> Vector4D<Magnitude<std::common_type_t<T, U>>>
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
         * @return The perpendicular @ref Vector4D component.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto reject(const Vector4D<U>& from, bool fromNormalized = false) const noexcept
            -> Vector4D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;


        /**
         * @brief @copybrief reject(const Vector4D<U>&, bool) const
         * Static wrapper for computing the perpendicular component of @p vector relative to @p onto.
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
         * @return The perpendicular @ref Vector4D component.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static auto reject(const Vector4D& vector, const Vector4D<U>& from,
                                                   bool fromNormalized = false) noexcept
            -> Vector4D<Magnitude<std::common_type_t<T, U>>>
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
         * @return The perpendicular @ref Vector4D component.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr auto safeReject(const Vector4D<U>& from, bool fromNormalized = false) const noexcept
            -> Vector4D<Magnitude<std::common_type_t<T, U>>>
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
         * @return The perpendicular @ref Vector4D component.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr static auto safeReject(const Vector4D& vec, const Vector4D<U>& from,
                                                       bool fromNormalized = false) noexcept
            -> Vector4D<Magnitude<std::common_type_t<T, U>>>
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FGM_Vec4_Utils
         * @{
         */
        
        /**
         * @brief Check if any component of this vector is an IEEE 754 infinity.
         *
         * @note Always returns false for integral types.
         *
         * @return True if at least one component is positive or negative infinity.
         */
        [[nodiscard]] constexpr bool hasInf() noexcept;


        /** @} */



        /**
         * @addtogroup FGM_Vec4_Log
         * @{
         */

        /**
         * @brief Write the vector to an output stream.
         *        Format the vector as <x, y, z, w> string representation for debugging or logging.
         *
         * @tparam T Numeric type of the vector.
         *
         * @param os     The output stream to write to.
         * @param vector The vector to be streamed.
         *
         * @return A reference to the output stream @p os.
         */
        constexpr friend std::ostream& operator<<(std::ostream& os, const Vector4D& vector)
        {
            auto precision = Config::useFullPrecision
                ? std::is_same_v<T, double> ? Config::DOUBLE_PRECISION : Config::FLOAT_PRECISION
                : Config::LOG_PRECISION;
            os << std::setprecision(precision) << std::fixed;
            os << "<" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ">\n";
            return os;
        }

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
     * @return A new @ref Vector4D scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    [[nodiscard]] constexpr auto operator*(S scalar, const Vector4D<T>& vector) noexcept
        -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>;

    /** @} */



    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/

    /**
     * @addtogroup FGM_Vec4_Alias
     * @{
     */

    using bVec4 = Vector4D<bool>;                ///< `bool` vector
    using iVec4 = Vector4D<int>;                 ///< `int` vector
    using uVec4 = Vector4D<unsigned int>;        ///< `unsigned int` vector
    using vec4 = Vector4D<float>;                ///< `float` vector
    using lVec4 = Vector4D<long long>;           ///< `long long` vector
    using dVec4 = Vector4D<double>;              ///< `double` vector
    using ulVec4 = Vector4D<unsigned long long>; ///< `unsigned long long` vector



    /** @} */
    /**
     * @addtogroup FGM_Vec4_Const
     * @{
     */

    /*************************************
     *                                   *
     *            CONSTANTS              *
     *                                   *
     *************************************/
    namespace vec4d
    {

        /**
         * @brief A 4D vector with all components set to one (1, 1, 1, 1).
         *
         * @note Only available for @ref fgm::StrictArithmetic types.
         */
        template <StrictArithmetic T>
        [[nodiscard]] inline constexpr Vector4D<T> one = Vector4D<T>(T(1), T(1), T(1), T(1));


        /**
         * @brief A 4D vector with all components set to zero (0, 0, 0, 0).
         *
         * @note Only available for @ref fgm::StrictArithmetic types.
         */
        template <StrictArithmetic T>
        [[nodiscard]] inline constexpr Vector4D<T> zero =
            Vector4D<T>(T(0), T(0), T(0), T(0)); ///< 4D-Vector with all zero-components.


        /**
         * @brief A 4D vector with all components set to positive infinity.
         *
         * @note Only available for `std::floating_point` types.
         */
        template <StrictArithmetic T>
            requires std::floating_point<T>
        [[nodiscard]] inline constexpr Vector4D<T> inf = Vector4D<T>(
            T(constants::INFINITY_D), T(constants::INFINITY_D), T(constants::INFINITY_D), T(constants::INFINITY_D));


        /**
         * @brief A 4D vector with all components set to negative infinity.
         *
         * @note Only available for `std::floating_point` types.
         */
        template <StrictArithmetic T>
            requires std::floating_point<T>
        [[nodiscard]] inline constexpr Vector4D<T> infN = Vector4D<T>(
            T(-constants::INFINITY_D), T(-constants::INFINITY_D), T(-constants::INFINITY_D), T(-constants::INFINITY_D));


        /**
         * @brief A 4D vector with all components set to Not-A-Number (NaN).
         *
         * @note Only available for `std::floating_point` types.
         */
        template <StrictArithmetic T>
            requires std::floating_point<T>
        [[nodiscard]] inline constexpr Vector4D<T> nan =
            Vector4D<T>(T(constants::NaN_D), T(constants::NaN_D), T(constants::NaN_D), T(constants::NaN_D));


        /** @brief A 4D unit vector aligned with the positive X-axis (1, 0, 0, 0). */
        template <StrictArithmetic T>
        [[nodiscard]] inline constexpr Vector4D<T> x = Vector4D<T>(T(1), T(0), T(0), T(0));


        /** @brief A 4D unit vector aligned with the positive Y-axis (0, 1, 0, 0). */
        template <StrictArithmetic T>
        [[nodiscard]] inline constexpr Vector4D<T> y = Vector4D<T>(T(0), T(1), T(0), T(0));


        /** @brief A 4D unit vector aligned with the positive Z-axis (0, 0, 1, 0). */
        template <StrictArithmetic T>
        [[nodiscard]] inline constexpr Vector4D<T> z = Vector4D<T>(T(0), T(0), T(1), T(0));

        /** @brief A 4D unit vector aligned with the positive W-axis (0, 0, 0, 1). */
        template <StrictArithmetic T>
        [[nodiscard]] inline constexpr Vector4D<T> w = Vector4D<T>(T(0), T(0), T(0), T(1));


    } // namespace vec4d

    /** @} */


} // namespace fgm


#include "Vector4D.tpp"