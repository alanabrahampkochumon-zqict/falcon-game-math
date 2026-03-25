#pragma once
/**
 * @file Vector4D.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: January 26, 2026
 *
 * @brief @ref fgm::Vector4D template implementation.
 * @details This file contains the definitions of the template members declared in Vector4D.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4D.h"

#include <cassert>
#include <type_traits>

namespace fgm
{

    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D() noexcept: x(T(0)), y(T(0)), z(T(0)), w(T(0))
    {}


    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D(T v1, T v2, T v3, T v4) noexcept: x(v1), y(v2), z(v3), w(v4)
    {}


    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D(Vector2D<T> vec1, Vector2D<T> vec2) noexcept
        : x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y)
    {}


    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D(Vector3D<T> vec, T v) noexcept: x(vec.x), y(vec.y), z(vec.z), w(v)
    {}


    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D(T v, Vector3D<T> vec) noexcept: x(v), y(vec.x), z(vec.y), w(vec.z)
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector4D<T>::Vector4D(const Vector4D<U>& other) noexcept
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)), w(static_cast<T>(other.w))
    {}




    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr T& Vector4D<T>::operator[](std::size_t i) noexcept
    {
        return (&x)[i];
    }

    template <Arithmetic T>
    constexpr const T& Vector4D<T>::operator[](std::size_t i) const noexcept
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
    constexpr bool Vector4D<T>::allEq(const Vector4D<U>& rhs, double epsilon) const noexcept
    {

        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
        else
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return (x == rhs.x || std::abs(x - rhs.x) <= epsilon) && (y == rhs.y || std::abs(y - rhs.y) <= epsilon) &&
                (z == rhs.z || std::abs(z - rhs.z) <= epsilon) && (w == rhs.w || std::abs(w - rhs.w) <= epsilon);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector4D<T>::allEq(const Vector4D& lhs, const Vector4D<U>& rhs, double epsilon) noexcept
    {
        return lhs.allEq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector4D<T>::allNeq(const Vector4D<U>& rhs, double epsilon) const noexcept
    {

        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
        else
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return (x != rhs.x && !(std::abs(x - rhs.x) <= epsilon)) ||
                (y != rhs.y && !(std::abs(y - rhs.y) <= epsilon)) ||
                (z != rhs.z && !(std::abs(z - rhs.z) <= epsilon)) || (w != rhs.w && !(std::abs(w - rhs.w) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector4D<T>::allNeq(const Vector4D& lhs, const Vector4D<U>& rhs, double epsilon) noexcept
    {
        return lhs.allNeq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector4D<T>::operator==(const Vector4D<U>& rhs) const noexcept
    {
        return this->allEq(rhs);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector4D<T>::operator!=(const Vector4D<U>& rhs) const noexcept
    {
        return this->allNeq(rhs);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::eq(const Vector4D<U>& rhs, double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return Vector4D(x == rhs.x, y == rhs.y, z == rhs.z, w == rhs.w);
        else
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return Vector4D(
                (x == rhs.x || std::abs(x - rhs.x) <= epsilon), (y == rhs.y || std::abs(y - rhs.y) <= epsilon),
                (z == rhs.z || std::abs(z - rhs.z) <= epsilon), (w == rhs.w || std::abs(w - rhs.w) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::eq(const Vector4D& lhs, const Vector4D<U>& rhs, double epsilon) noexcept
    {
        return lhs.eq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::neq(const Vector4D<U>& rhs, double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return Vector4D(x != rhs.x, y != rhs.y, z != rhs.z, w != rhs.w);
        else
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return Vector4D<bool>(
                (x != rhs.x) && !(std::abs(x - rhs.x) <= epsilon), (y != rhs.y) && !(std::abs(y - rhs.y) <= epsilon),
                (z != rhs.z) && !(std::abs(z - rhs.z) <= epsilon), (w != rhs.w) && !(std::abs(w - rhs.w) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::neq(const Vector4D& lhs, const Vector4D<U>& rhs, double epsilon) noexcept
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
    constexpr Vector4D<bool> Vector4D<T>::gt(const Vector4D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector4D(x > rhs.x, y > rhs.y, z > rhs.z, w > rhs.w);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::gt(const Vector4D& lhs, const Vector4D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.gt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::gte(const Vector4D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector4D(x >= rhs.x, y >= rhs.y, z >= rhs.z, w >= rhs.w);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::gte(const Vector4D& lhs, const Vector4D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.gte(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::lt(const Vector4D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector4D(x < rhs.x, y < rhs.y, z < rhs.z, w < rhs.w);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::lt(const Vector4D& lhs, const Vector4D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.lt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::lte(const Vector4D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<std::common_type_t<T, U>>;
        return Vector4D<bool>(static_cast<R>(x) <= static_cast<R>(rhs.x), static_cast<R>(y) <= static_cast<R>(rhs.y),
                              static_cast<R>(z) <= static_cast<R>(rhs.z), static_cast<R>(w) <= static_cast<R>(rhs.w));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::lte(const Vector4D& lhs, const Vector4D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.lte(rhs);
    }


#ifdef ENABLE_FGM_SHADER_OPERATORS

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::operator>(const Vector4D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->gt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::operator>=(const Vector4D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->gte(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::operator<(const Vector4D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->lt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::operator<=(const Vector4D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->lte(rhs);
    }

#endif



    /***************************************
     *                                     *
     *      BOOLEAN BITWISE OPERATORS      *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    constexpr Vector4D<bool> Vector4D<T>::operator&(const Vector4D<bool>& rhs) const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector4D(x & rhs.x, y & rhs.y, z & rhs.z, w & rhs.w);
    }


    constexpr Vector4D<bool>& Vector4D<bool>::operator&=(const Vector4D<bool>& rhs) noexcept
    {
        (*this) = (*this) & rhs;
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector4D<bool> Vector4D<T>::operator|(const Vector4D<bool>& rhs) const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector4D(x | rhs.x, y | rhs.y, z | rhs.z, w | rhs.w);
    }


    template <Arithmetic T>
    constexpr Vector4D<bool>& Vector4D<T>::operator|=(const Vector4D<bool>& rhs) noexcept
    {
        (*this) = (*this) & rhs;
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector4D<bool> Vector4D<T>::operator!() const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector4D(!x, !y, !z, !w);
    }



    /*************************************
     *                                   *
     *      ARITHMETIC OPERATORS         *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::operator+(const Vector4D<U>& rhs) const noexcept -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Vector4D<R>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<T>& Vector4D<T>::operator+=(const Vector4D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        x += static_cast<T>(rhs.x);
        y += static_cast<T>(rhs.y);
        z += static_cast<T>(rhs.z);
        w += static_cast<T>(rhs.w);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::operator-(const Vector4D<U>& rhs) const noexcept -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Vector4D<R>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<T>& Vector4D<T>::operator-=(const Vector4D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        x -= static_cast<T>(rhs.x);
        y -= static_cast<T>(rhs.y);
        z -= static_cast<T>(rhs.z);
        w -= static_cast<T>(rhs.w);
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector4D<T> Vector4D<T>::operator-() const noexcept
        requires StrictArithmetic<T>
    {
        return Vector4D(-x, -y, -z, -w);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector4D<T>::operator*(S scalar) const noexcept -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        return Vector4D<R>(x * scalar, y * scalar, z * scalar, w * scalar);
    }


    template <StrictArithmetic T, StrictArithmetic S>
    constexpr auto operator*(S scalar, const Vector4D<T>& vector) noexcept -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        return vector * scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vector4D<T>& Vector4D<T>::operator*=(S scalar) noexcept
        requires StrictArithmetic<T>
    {

        x = static_cast<T>(scalar * x);
        y = static_cast<T>(scalar * y);
        z = static_cast<T>(scalar * z);
        w = static_cast<T>(scalar * w);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector4D<T>::operator/(S scalar) const -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            R factor = R(1) / static_cast<R>(scalar);
            return Vector4D<R>(x * factor, y * factor, z * factor, w * factor);
        }
        else
        {
            assert(scalar != 0 && "Integral division by zero");
            R tScalar = static_cast<R>(scalar);
            return Vector4D<R>(x / tScalar, y / tScalar, z / tScalar, w / tScalar);
        }
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vector4D<T>& Vector4D<T>::operator/=(S scalar)
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            R factor = R(1) / static_cast<R>(scalar);

            x = static_cast<T>(factor * x);
            y = static_cast<T>(factor * y);
            z = static_cast<T>(factor * z);
            w = static_cast<T>(factor * w);
        }
        else
        {
            assert(scalar != 0 && "Integral division by zero");
            x /= static_cast<T>(scalar);
            y /= static_cast<T>(scalar);
            z /= static_cast<T>(scalar);
            w /= static_cast<T>(scalar);
        }

        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector4D<T>::safeDiv(S scalar) const -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<S>)
            assert(scalar != 0 && "Integral division by zero");
        
        return (*this)/scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector4D<T>::safeDiv(const Vector4D& vec, S scalar) -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        return vec.safeDiv(scalar);
    }



    /*************************************
     *                                   *
     *        VECTOR DOT PRODUCT         *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::dot(const Vector4D<U>& rhs) const noexcept -> std::common_type_t<T, U>
        requires StrictArithmetic<T>
    {
        return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::dot(const Vector4D& lhs, const Vector4D<U>& rhs) noexcept -> std::common_type_t<T, U>
        requires StrictArithmetic<T>
    {
        return lhs.dot(rhs);
    }



    /*************************************
     *                                   *
     *         VECTOR MAGNITUDE          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Magnitude<T> Vector4D<T>::mag() const noexcept
        requires StrictArithmetic<T>
    {
        using M = Magnitude<T>;

        M tX = static_cast<M>(x);
        M tY = static_cast<M>(y);
        M tZ = static_cast<M>(z);
        M tW = static_cast<M>(w);

        return sqrt(tX * tX + tY * tY + tZ * tZ + tW * tW);
    }


    template <Arithmetic T>
    constexpr Magnitude<T> Vector4D<T>::mag(const Vector4D& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.mag();
    }



    /*************************************
     *                                   *
     *       VECTOR NORMALIZATION        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Vector4D<Magnitude<T>> Vector4D<T>::normalize() const
        requires StrictArithmetic<T>
    {
        using R = Magnitude<T>;
        R magnitude = mag();

        if constexpr (std::is_same_v<R, double>)
            assert(magnitude > Config::DOUBLE_EPSILON && "Vector4D Normalization : Division by 0");
        else
            assert(magnitude > Config::FLOAT_EPSILON && "Vector4D Normalization : Division by 0");

        return *this / magnitude;
    }


    template <Arithmetic T>
    constexpr Vector4D<Magnitude<T>> Vector4D<T>::normalize(const Vector4D& vec)
        requires StrictArithmetic<T>
    {
        return vec.normalize();
    }



    /*************************************
     *                                   *
     *        VECTOR PROJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::project(const Vector4D<U>& onto, bool ontoNormalized) const
        -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        if (ontoNormalized)
            return this->dot(onto) * onto; // a.dot(b) * b
        /** @note Static cast ensures integral type dots don't lose much precision */
        return this->dot(onto) / static_cast<Magnitude<R>>(onto.dot(onto)) * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::project(const Vector4D& vector, const Vector4D<U>& onto, bool ontoNormalized)
        -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        return vector.project(onto, ontoNormalized);
    }




    /*************************************
     *                                   *
     *         VECTOR REJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::reject(const Vector4D<U>& from, bool ontoNormalized) const
        -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        return *this - this->project(from, ontoNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::reject(const Vector4D& vector, const Vector4D<U>& from, bool ontoNormalized)
        -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        return vector.reject(from, ontoNormalized);
    }

} // namespace fgm
