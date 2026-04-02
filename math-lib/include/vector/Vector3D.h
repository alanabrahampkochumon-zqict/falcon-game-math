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



        /*************************************
         *                                   *
         *      ARITHMETIC OPERATORS         *
         *                                   *
         *************************************/

        template <Arithmetic U>
        auto operator+(const Vector3D<U>& other) const -> Vector3D<std::common_type_t<T, U>>;

        template <Arithmetic U>
        Vector3D& operator+=(const Vector3D<U>& other);

        template <Arithmetic U>
        auto operator-(const Vector3D<U>& other) const -> Vector3D<std::common_type_t<T, U>>;

        template <Arithmetic U>
        Vector3D& operator-=(const Vector3D<U>& other);

        template <Arithmetic S>
        auto operator*(S scalar) const -> Vector3D<std::common_type_t<T, S>>;

        template <Arithmetic S>
        Vector3D& operator*=(S scalar);

        template <Arithmetic S>
        auto operator/(S scalar) const -> Vector3D<std::common_type_t<T, S>>;

        template <Arithmetic S>
        Vector3D& operator/=(S scalar);


        /*************************************
         *                                   *
         *       VECTOR DOT PRODUCT          *
         *                                   *
         *************************************/
        template <Arithmetic U>
        auto dot(const Vector3D<U>& other) const -> std::common_type_t<T, U>;

        template <Arithmetic U>
        static auto dot(const Vector3D& vecA, const Vector3D<U>& vecB) -> std::common_type_t<T, U>;


        /*************************************
         *                                   *
         *       VECTOR CROSS PRODUCT        *
         *                                   *
         *************************************/
        template <Arithmetic U>
        auto cross(const Vector3D<U>& other) const -> Vector3D<std::common_type_t<T, U>>;

        template <Arithmetic U>
        static auto cross(const Vector3D& vecA, const Vector3D<U>& vecB) -> Vector3D<std::common_type_t<T, U>>;


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
        Vector3D normalize() const;


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
    };

    /*************************************
     *                                   *
     *       NON-MEMBER FUNCTIONS        *
     *                                   *
     *************************************/
    template <Arithmetic T, Arithmetic S>
    auto operator*(S scalar, const Vector3D<T>& vector) -> Vector3D<std::common_type_t<T, S>>;

    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/
    using vec3 = Vector3D<float>;
    using dvec3 = Vector3D<double>;

} // namespace fgm

#include "Vector3D.tpp"