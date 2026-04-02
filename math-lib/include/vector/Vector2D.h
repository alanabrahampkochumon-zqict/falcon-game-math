#pragma once

#include "common/MathTraits.h"

#include <type_traits>

namespace fgm
{
    template <Arithmetic T>
    struct Vector2D
    {

        using value_type = T;

        static constexpr std::size_t dimension = 2;

        union {
            struct
            {
                T x, y;
            };
            struct
            {
                T r, g;
            };
            struct
            {
                T s, t;
            };
            T elements[dimension];
        };

        /*************************************
         *                                   *
         *            INITIALIZERS           *
         *                                   *
         *************************************/

        constexpr Vector2D() noexcept;
        constexpr Vector2D(T v1, T v2) noexcept;

        template <Arithmetic U>
        constexpr Vector2D(const Vector2D<U>& other) noexcept;


        /*************************************
         *                                   *
         *            ACCESSORS              *
         *                                   *
         *************************************/

        constexpr T& operator[](std::size_t i) noexcept;
        constexpr const T& operator[](std::size_t i) const noexcept;


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