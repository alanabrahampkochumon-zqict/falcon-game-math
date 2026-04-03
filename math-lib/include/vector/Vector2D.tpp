#pragma once
/**
 * @file Vector2D.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: January 24, 2026
 *
 * @brief @ref Vector2D template implementation.
 * @details This file contains the definitions of the template members declared in Vector2D.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2D.h"

#include <type_traits>



namespace fgm
{

    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Vector2D<T>::Vector2D() noexcept: x(T(0)), y(T(0))
    {}


    template <Arithmetic T>
    constexpr Vector2D<T>::Vector2D(T v1, T v2) noexcept: x(v1), y(v2)
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector2D<T>::Vector2D(const Vector2D<U>& other) noexcept
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))
    {}




    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr T& Vector2D<T>::operator[](std::size_t i) noexcept
    {
        return (&x)[i];
    }


    template <Arithmetic T>
    constexpr const T& Vector2D<T>::operator[](std::size_t i) const noexcept
    {
        return (&x)[i];
    }




    /***************************************
     *                                     *
     *             EQUALITY                *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector2D<T>::allEq(const Vector2D<U>& rhs, const double epsilon) const noexcept
    {

        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return x == rhs.x && y == rhs.y;
        else
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return (x == rhs.x || std::abs(x - rhs.x) <= epsilon) && (y == rhs.y || std::abs(y - rhs.y) <= epsilon);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector2D<T>::allEq(const Vector2D& lhs, const Vector2D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.allEq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector2D<T>::allNeq(const Vector2D<U>& rhs, const double epsilon) const noexcept
    {

        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return x != rhs.x || y != rhs.y;
        else
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return (x != rhs.x && !(std::abs(x - rhs.x) <= epsilon)) ||
                (y != rhs.y && !(std::abs(y - rhs.y) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector2D<T>::allNeq(const Vector2D& lhs, const Vector2D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.allNeq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector2D<T>::operator==(const Vector2D<U>& rhs) const noexcept
    {
        return this->allEq(rhs);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector2D<T>::operator!=(const Vector2D<U>& rhs) const noexcept
    {
        return this->allNeq(rhs);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::eq(const Vector2D<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return Vector2D(x == rhs.x, y == rhs.y);
        else
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return Vector2D((x == rhs.x || std::abs(x - rhs.x) <= epsilon),
                            (y == rhs.y || std::abs(y - rhs.y) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::eq(const Vector2D& lhs, const Vector2D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.eq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::neq(const Vector2D<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return Vector2D(x != rhs.x, y != rhs.y);
        else
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return Vector2D<bool>((x != rhs.x) && !(std::abs(x - rhs.x) <= epsilon),
                                  (y != rhs.y) && !(std::abs(y - rhs.y) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::neq(const Vector2D& lhs, const Vector2D<U>& rhs,
                                              const double epsilon) noexcept
    {
        return lhs.neq(rhs, epsilon);
    }




    /***************************************
     *                                     *
     *            COMPARISONS              *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::gt(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector2D(x > rhs.x, y > rhs.y);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::gt(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.gt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::gte(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector2D(x >= rhs.x, y >= rhs.y);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::gte(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.gte(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::lt(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector2D(x < rhs.x, y < rhs.y);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::lt(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.lt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::lte(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<std::common_type_t<T, U>>;
        return Vector2D<bool>(static_cast<R>(x) <= static_cast<R>(rhs.x), static_cast<R>(y) <= static_cast<R>(rhs.y));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::lte(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.lte(rhs);
    }


#ifdef ENABLE_FGM_SHADER_OPERATORS

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::operator>(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->gt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::operator>=(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->gte(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::operator<(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->lt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::operator<=(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->lte(rhs);
    }

#endif



    /*************************************
     *                                   *
     *      ARITHMETIC OPERATORS         *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <Arithmetic S>
    auto Vector2D<T>::operator+(const Vector2D<S>& other) const -> Vector2D<std::common_type_t<S, T>>
    {
        using R = std::common_type_t<T, S>;
        return Vector2D<R>(x + other.x, y + other.y);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    Vector2D<T>& Vector2D<T>::operator+=(const Vector2D<U>& other)
    {
        x += static_cast<T>(other.x);
        y += static_cast<T>(other.y);
        return *this;
    }

    template <Arithmetic T>
    template <Arithmetic U>
    auto Vector2D<T>::operator-(const Vector2D<U>& other) const -> Vector2D<std::common_type_t<T, U>>
    {
        using R = std::common_type_t<T, U>;
        return Vector2D<R>(x - other.x, y - other.y);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    Vector2D<T>& Vector2D<T>::operator-=(const Vector2D<U>& other)
    {
        x -= static_cast<T>(other.x);
        y -= static_cast<T>(other.y);
        return *this;
    }

    template <Arithmetic T>
    template <Arithmetic S>
    auto Vector2D<T>::operator*(S scalar) const -> Vector2D<std::common_type_t<T, S>>
    {
        using R = std::common_type_t<T, S>;
        return Vector2D<R>(x * scalar, y * scalar);
    }

    template <Arithmetic T, Arithmetic S>
    auto operator*(S scalar, const Vector2D<T>& vector) -> Vector2D<std::common_type_t<S, T>>
    {
        return vector * scalar;
    }

    template <Arithmetic T>
    template <Arithmetic S>
    Vector2D<T>& Vector2D<T>::operator*=(S scalar)
    {
        x = static_cast<T>(scalar * x);
        y = static_cast<T>(scalar * y);
        return *this;
    }

    template <Arithmetic T>
    template <Arithmetic S>
    auto Vector2D<T>::operator/(S scalar) const -> Vector2D<std::common_type_t<T, S>>
    {
        using R = std::common_type_t<T, S>;
        R factor = R(1) / static_cast<R>(scalar);
        return Vector2D<R>(x * factor, y * factor);
    }

    template <Arithmetic T>
    template <Arithmetic S>
    Vector2D<T>& Vector2D<T>::operator/=(S scalar)
    {
        using R = std::common_type_t<T, S>;
        R factor = R(1) / static_cast<R>(scalar);
        x = static_cast<T>(factor * x);
        y = static_cast<T>(factor * y);
        return *this;
    }



    /*************************************
     *                                   *
     *        VECTOR DOT PRODUCT         *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <Arithmetic S>
    auto Vector2D<T>::dot(const Vector2D<S>& other) const -> std::common_type_t<T, S>
    {
        return x * other.x + y * other.y;
    }

    template <Arithmetic T>
    template <Arithmetic U>
    auto Vector2D<T>::dot(const Vector2D& vectorA, const Vector2D<U>& vectorB) -> std::common_type_t<T, U>
    {
        return vectorA.dot(vectorB);
    }


    /*************************************
     *                                   *
     *       VECTOR CROSS PRODUCT        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <Arithmetic U>
    auto Vector2D<T>::cross(const Vector2D<U>& other) const -> std::common_type_t<T, U>
    {
        return x * other.y - y * other.x;
    }

    template <Arithmetic T>
    template <Arithmetic U>
    auto Vector2D<T>::cross(const Vector2D<T>& vectorA, const Vector2D<U>& vectorB) -> std::common_type_t<T, U>
    {
        return vectorA.cross(vectorB);
    }


    /*************************************
     *                                   *
     *         VECTOR MAGNITUDE          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    T Vector2D<T>::mag() const
    {
        return sqrt(x * x + y * y);
    }


    /*************************************
     *                                   *
     *       VECTOR NORMALIZATION        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    Vector2D<T> Vector2D<T>::normalize() const
    {
        return (*this) / this->mag();
    }


    /*************************************
     *                                   *
     *        VECTOR PROJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <Arithmetic U>
    auto Vector2D<T>::project(const Vector2D<U>& onto, bool ontoNormalized) const -> Vector2D<std::common_type_t<T, U>>
    {
        if (ontoNormalized)
        {
            // Pb||a^ = dot(a, b) * b;
            return this->dot(onto) * onto;
        }
        else
        {
            // Pb||a = dot(a, b)/dot(b,b) * b;
            return this->dot(onto) / onto.dot(onto) * onto;
        }
    }

    template <Arithmetic T>
    template <Arithmetic U>
    auto Vector2D<T>::project(const Vector2D& vector, const Vector2D<U>& onto, bool ontoNormalized)
        -> Vector2D<std::common_type_t<T, U>>
    {
        return vector.project(onto, ontoNormalized);
    }


    /*************************************
     *                                   *
     *         VECTOR REJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <Arithmetic U>
    auto Vector2D<T>::reject(const Vector2D<U>& onto, bool ontoNormalized) const -> Vector2D<std::common_type_t<T, U>>
    {
        return *this - this->project(onto, ontoNormalized);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    auto Vector2D<T>::reject(const Vector2D& vector, const Vector2D<U>& onto, bool ontoNormalized)
        -> Vector2D<std::common_type_t<T, U>>
    {
        return vector.reject(onto, ontoNormalized);
    }
} // namespace fgm