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
    constexpr Vector4D<T>::Vector4D(const T v1, const T v2, const T v3, const T v4) noexcept: x(v1), y(v2), z(v3), w(v4)
    {}


    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D(const Vector2D<T>& vec1, const Vector2D<T>& vec2) noexcept
        : x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y)
    {}


    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D(const Vector3D<T>& vec, const T v) noexcept: x(vec.x), y(vec.y), z(vec.z), w(v)
    {}


    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D(const T v, const Vector3D<T>& vec) noexcept: x(v), y(vec.x), z(vec.y), w(vec.z)
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
    constexpr T& Vector4D<T>::operator[](const std::size_t i) noexcept
    {
        return (&x)[i];
    }

    template <Arithmetic T>
    constexpr const T& Vector4D<T>::operator[](const std::size_t i) const noexcept
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
    constexpr bool Vector4D<T>::allEq(const Vector4D<U>& rhs, const double epsilon) const noexcept
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
    constexpr bool Vector4D<T>::allEq(const Vector4D& lhs, const Vector4D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.allEq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector4D<T>::allNeq(const Vector4D<U>& rhs, const double epsilon) const noexcept
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
    constexpr bool Vector4D<T>::allNeq(const Vector4D& lhs, const Vector4D<U>& rhs, const double epsilon) noexcept
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
    constexpr Vector4D<bool> Vector4D<T>::eq(const Vector4D<U>& rhs, const double epsilon) const noexcept
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
    constexpr Vector4D<bool> Vector4D<T>::eq(const Vector4D& lhs, const Vector4D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.eq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector4D<bool> Vector4D<T>::neq(const Vector4D<U>& rhs, const double epsilon) const noexcept
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
    constexpr Vector4D<bool> Vector4D<T>::neq(const Vector4D& lhs, const Vector4D<U>& rhs,
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
        requires SignedStrictArithmetic<T>
    {
        return Vector4D(-x, -y, -z, -w);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector4D<T>::operator*(const S scalar) const noexcept -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        return Vector4D<R>(x * scalar, y * scalar, z * scalar, w * scalar);
    }


    template <StrictArithmetic T, StrictArithmetic S>
    constexpr auto operator*(const S scalar, const Vector4D<T>& vector) noexcept -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        return vector * scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vector4D<T>& Vector4D<T>::operator*=(const S scalar) noexcept
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
    constexpr auto Vector4D<T>::operator/(const S scalar) const noexcept -> Vector4D<std::common_type_t<T, S>>
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
    constexpr Vector4D<T>& Vector4D<T>::operator/=(const S scalar) noexcept
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
            x /= static_cast<T>(scalar);
            y /= static_cast<T>(scalar);
            z /= static_cast<T>(scalar);
            w /= static_cast<T>(scalar);
        }

        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector4D<T>::safeDiv(const S scalar) const noexcept -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
            if (hasNaN() | std::isnan(scalar) | (std::abs(scalar) <= std::numeric_limits<S>::epsilon()))
                return fgm::vec4d::zero<R>;
        if constexpr (std::is_integral_v<R>)
            if (scalar == 0)
                return fgm::vec4d::zero<R>;

        return (*this) / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector4D<T>::safeDiv(const Vector4D& vec, const S scalar) noexcept
        -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        return vec.safeDiv(scalar);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector4D<T>::tryDiv(S scalar, OperationStatus& status) const noexcept
        -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (hasNaN() | std::isnan(scalar))
            {
                status = OperationStatus::NANOPERAND;
                return fgm::vec4d::zero<R>;
            }
            if (std::abs(scalar) <= std::numeric_limits<S>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return fgm::vec4d::zero<R>;
            }
        }

        if constexpr (std::is_integral_v<R>)
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return fgm::vec4d::zero<R>;
            }


        status = OperationStatus::SUCCESS;
        return (*this) / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector4D<T>::tryDiv(const Vector4D& vec, S scalar, OperationStatus& status) noexcept
        -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        return vec.tryDiv(scalar, status);
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
    constexpr Vector4D<Magnitude<T>> Vector4D<T>::normalize() const noexcept
        requires StrictArithmetic<T>
    {
        return *this / mag();
    }


    template <Arithmetic T>
    constexpr Vector4D<Magnitude<T>> Vector4D<T>::normalize(const Vector4D& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.normalize();
    }


    template <Arithmetic T>
    constexpr Vector4D<Magnitude<T>> Vector4D<T>::safeNormalize() const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<T>;
        R magnitude = mag();
        if (std::isnan(magnitude))
            return fgm::vec4d::zero<R>;
        if (magnitude <= Config::EPSILON_SQUARE<R>)
            return fgm::vec4d::zero<R>;

        return *this / magnitude;
    }


    template <Arithmetic T>
    constexpr Vector4D<Magnitude<T>> Vector4D<T>::safeNormalize(const Vector4D& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeNormalize();
    }


    template <Arithmetic T>
    constexpr Vector4D<Magnitude<T>> Vector4D<T>::tryNormalize(OperationStatus& status) const noexcept requires
        StrictArithmetic<T>
    {
        
        using R = Magnitude<T>;
        R magnitude = mag();
        if (std::isnan(magnitude))
        {
            status = OperationStatus::NANOPERAND;
            return fgm::vec4d::zero<R>;
        }
        if (magnitude <= Config::EPSILON_SQUARE<R>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return fgm::vec4d::zero<R>;
        }

        status = OperationStatus::SUCCESS;
        return *this / magnitude;
    }


    template <Arithmetic T>
    constexpr Vector4D<Magnitude<T>> Vector4D<T>::tryNormalize(const Vector4D& vec,
        OperationStatus& status) noexcept requires StrictArithmetic<T>
    {
        return vec.tryNormalize(status);
    }


    /*************************************
     *                                   *
     *        VECTOR PROJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::project(const Vector4D<U>& onto, const bool ontoNormalized) const noexcept
        -> Vector4D<Magnitude<std::common_type_t<T, U>>>
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
    constexpr auto Vector4D<T>::project(const Vector4D& vec, const Vector4D<U>& onto,
                                        const bool ontoNormalized) noexcept
        -> Vector4D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return vec.project(onto, ontoNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::safeProject(const Vector4D<U>& onto, const bool ontoNormalized) const noexcept
        -> Vector4D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        using MagType = Magnitude<R>;
        if (ontoNormalized)
            return this->dot(onto) * onto;

        /** @note Static cast ensures integral type dots don't lose much precision */
        const auto ontoSquared = static_cast<MagType>(onto.dot(onto));

        if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
            return fgm::vec4d::zero<MagType>;

        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::safeProject(const Vector4D& vec, const Vector4D<U>& onto,
                                            const bool ontoNormalized) noexcept
        -> Vector4D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return vec.safeProject(onto, ontoNormalized);
    }



    /*************************************
     *                                   *
     *         VECTOR REJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::reject(const Vector4D<U>& from, const bool fromNormalized) const noexcept
        -> Vector4D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return *this - this->project(from, fromNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::reject(const Vector4D& vector, const Vector4D<U>& from,
                                       const bool fromNormalized) noexcept
        -> Vector4D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return vector.reject(from, fromNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::safeReject(const Vector4D<U>& from, const bool fromNormalized) const noexcept
        -> Vector4D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return *this - safeProject(from, fromNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::safeReject(const Vector4D& vec, const Vector4D<U>& from,
                                           const bool fromNormalized) noexcept
        -> Vector4D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return vec.safeReject(from, fromNormalized);
    }




    /**************************************
     *                                    *
     *             Utilities              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr bool Vector4D<T>::hasInf() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
            return std::isinf(x) | std::isinf(y) | std::isinf(z) | std::isinf(w);
        else
            return false;
    }


    template <Arithmetic T>
    constexpr bool Vector4D<T>::hasInf(const Vector4D& vec) noexcept
    {
        return vec.hasInf();
    }


    template <Arithmetic T>
    constexpr bool Vector4D<T>::hasNaN() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
            return std::isnan(x) | std::isnan(y) | std::isnan(z) | std::isnan(w);
        else
            return false;
    }


    template <Arithmetic T>
    constexpr bool Vector4D<T>::hasNaN(const Vector4D& vec) noexcept
    {
        return vec.hasNaN();
    }

} // namespace fgm
