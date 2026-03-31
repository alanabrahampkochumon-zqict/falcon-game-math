#pragma once
/**
 * @file Vector3D.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 19, 2026
 *
 * @brief Templated 3D Vector supporting integral, floating-point and boolean types.
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

#include <type_traits>


namespace fgm
{
    template <Arithmetic T>
    struct Vector3D
    {
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

        /*************************************
         *                                   *
         *            INITIALIZERS           *
         *                                   *
         *************************************/

        constexpr Vector3D() noexcept;
        constexpr Vector3D(T v1, T v2, T v3) noexcept;
        constexpr Vector3D(Vector2D<T> vec, T v) noexcept;

        template <Arithmetic S>
        constexpr Vector3D(const Vector3D<S>& other) noexcept;


        /*************************************
         *                                   *
         *            ACCESSORS              *
         *                                   *
         *************************************/

        T& operator[](std::size_t i);
        const T& operator[](std::size_t i) const;


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
        static auto project(const Vector3D& vector, const Vector3D<U>& onto,
                            bool ontoNormalized = false) -> Vector3D<std::common_type_t<T, U>>;


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
        static auto reject(const Vector3D& vector, const Vector3D<U>& onto,
                           bool ontoNormalized = false) -> Vector3D<std::common_type_t<T, U>>;
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