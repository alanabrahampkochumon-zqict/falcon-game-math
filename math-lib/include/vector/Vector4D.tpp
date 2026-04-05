#pragma once
/**
 * @file Vector4D.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: January 26, 2026
 *
 * @brief @ref Vector4D template implementation.
 * @details This file contains the definitions of the template members declared in Vector4D.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4D.h"

#include <cassert>
#include <cmath>
#include <type_traits>
// REGEXES
// ([\s*|\(])x([\s*|\)]) -> $1_data[0]$2
// ([\s*|\(])y([\s*|\)]) -> $1_data[1]$2
// ([\s*|\(])z([\s*|\)]) -> $1_data[2]$2
// ([\s*|\(])w([\s*|\)]) -> $1_data[3]$2
// rhs[0] -> rhs[0]
// rhs[1] -> rhs[1]
namespace fgm
{

    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D() noexcept
    {
        _data[0] = T(0);
        _data[1] = T(0);
        _data[2] = T(0);
        _data[3] = T(0);
    }


    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D(const T v1, const T v2, const T v3, const T v4) noexcept
    {
        _data[0] = v1;
        _data[1] = v2;
        _data[2] = v3;
        _data[3] = v4;
    }


    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D(const Vector2D<T>& vec1, const Vector2D<T>& vec2) noexcept
    {
        _data[0] = vec1[0];
        _data[1] = vec1[1];
        _data[2] = vec2[0];
        _data[3] = vec2[1];
    }


    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D(const Vector3D<T>& vec, const T v) noexcept
    {
        _data[0] = vec[0];
        _data[1] = vec[1];
        _data[2] = vec[2];
        _data[3] = v;
    }


    template <Arithmetic T>
    constexpr Vector4D<T>::Vector4D(const T v, const Vector3D<T>& vec) noexcept
    {
        _data[0] = v;
        _data[1] = vec[0];
        _data[2] = vec[1];
        _data[3] = vec[2];
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector4D<T>::Vector4D(const Vector4D<U>& other) noexcept
    {
        _data[0] = static_cast<T>(other[0]);
        _data[1] = static_cast<T>(other[1]);
        _data[2] = static_cast<T>(other[2]);
        _data[3] = static_cast<T>(other[3]);
    }




    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr T Vector4D<T>::x() const noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::x() noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T Vector4D<T>::y() const noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::y() noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T Vector4D<T>::z() const noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::z() noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T Vector4D<T>::w() const noexcept
    {
        return _data[3];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::w() noexcept
    {
        return _data[3];
    }


    template <Arithmetic T>
    constexpr T Vector4D<T>::s() const noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::s() noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T Vector4D<T>::t() const noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::t() noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T Vector4D<T>::p() const noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::p() noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T Vector4D<T>::q() const noexcept
    {
        return _data[3];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::q() noexcept
    {
        return _data[3];
    }


    template <Arithmetic T>
    constexpr T Vector4D<T>::r() const noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::r() noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T Vector4D<T>::g() const noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::g() noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T Vector4D<T>::b() const noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::b() noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T Vector4D<T>::a() const noexcept
    {
        return _data[3];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::a() noexcept
    {
        return _data[3];
    }


    template <Arithmetic T>
    constexpr T& Vector4D<T>::operator[](const std::size_t i) noexcept
    {
        return _data[i];
    }

    template <Arithmetic T>
    constexpr T Vector4D<T>::operator[](const std::size_t i) const noexcept
    {
        return _data[i];
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
            return _data[0] == rhs[0] && _data[1] == rhs[1] && _data[2] == rhs[2] && _data[3] == rhs[3];
        else
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return (_data[0] == rhs[0] || std::abs(_data[0] - rhs[0]) <= epsilon) && (_data[1] == rhs[1] || std::abs(_data[1] - rhs[1]) <= epsilon) &&
                (_data[2] == rhs[2] || std::abs(_data[2] - rhs[2]) <= epsilon) && (_data[3] == rhs[3] || std::abs(_data[3] - rhs[3]) <= epsilon);
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
            return _data[0] != rhs[0] || _data[1] != rhs[1] || _data[2] != rhs[2] || _data[3] != rhs[3];
        else
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return (_data[0] != rhs[0] && !(std::abs(_data[0] - rhs[0]) <= epsilon)) ||
                (_data[1] != rhs[1] && !(std::abs(_data[1] - rhs[1]) <= epsilon)) ||
                (_data[2] != rhs[2] && !(std::abs(_data[2] - rhs[2]) <= epsilon)) || (_data[3] != rhs[3] && !(std::abs(_data[3] - rhs[3]) <= epsilon));
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
            return Vector4D(_data[0] == rhs[0], _data[1] == rhs[1], _data[2] == rhs[2], _data[3] == rhs[3]);
        else
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return Vector4D(
                (_data[0] == rhs[0] || std::abs(_data[0] - rhs[0]) <= epsilon), (_data[1] == rhs[1] || std::abs(_data[1] - rhs[1]) <= epsilon),
                (_data[2] == rhs[2] || std::abs(_data[2] - rhs[2]) <= epsilon), (_data[3] == rhs[3] || std::abs(_data[3] - rhs[3]) <= epsilon));
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
            return Vector4D(_data[0] != rhs[0], _data[1] != rhs[1], _data[2] != rhs[2], _data[3] != rhs[3]);
        else
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return Vector4D<bool>(
                (_data[0] != rhs[0]) && !(std::abs(_data[0] - rhs[0]) <= epsilon), (_data[1] != rhs[1]) && !(std::abs(_data[1] - rhs[1]) <= epsilon),
                (_data[2] != rhs[2]) && !(std::abs(_data[2] - rhs[2]) <= epsilon), (_data[3] != rhs[3]) && !(std::abs(_data[3] - rhs[3]) <= epsilon));
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
        return Vector4D(_data[0] > rhs[0], _data[1] > rhs[1], _data[2] > rhs[2], _data[3] > rhs[3]);
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
        return Vector4D(_data[0] >= rhs[0], _data[1] >= rhs[1], _data[2] >= rhs[2], _data[3] >= rhs[3]);
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
        return Vector4D(_data[0] < rhs[0], _data[1] < rhs[1], _data[2] < rhs[2], _data[3] < rhs[3]);
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
        return Vector4D<bool>(static_cast<R>(_data[0]) <= static_cast<R>(rhs[0]), static_cast<R>(_data[1]) <= static_cast<R>(rhs[1]),
                              static_cast<R>(_data[2]) <= static_cast<R>(rhs[2]), static_cast<R>(_data[3]) <= static_cast<R>(rhs[3]));
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
        return Vector4D(_data[0] & rhs[0], _data[1] & rhs[1], _data[2] & rhs[2], _data[3] & rhs[3]);
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
        return Vector4D(_data[0] | rhs[0], _data[1] | rhs[1], _data[2] | rhs[2], _data[3] | rhs[3]);
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
        return Vector4D(!_data[0], !_data[1], !_data[2], !_data[3]);
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
        return Vector4D<R>(_data[0] + rhs[0], _data[1] + rhs[1], _data[2] + rhs[2], _data[3] + rhs[3]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<T>& Vector4D<T>::operator+=(const Vector4D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] += static_cast<T>(rhs[0]);
        _data[1] += static_cast<T>(rhs[1]);
        _data[2] += static_cast<T>(rhs[2]);
        _data[3] += static_cast<T>(rhs[3]);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::operator-(const Vector4D<U>& rhs) const noexcept -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Vector4D<R>(_data[0] - rhs[0], _data[1] - rhs[1], _data[2] - rhs[2], _data[3] - rhs[3]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector4D<T>& Vector4D<T>::operator-=(const Vector4D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] -= static_cast<T>(rhs[0]);
        _data[1] -= static_cast<T>(rhs[1]);
        _data[2] -= static_cast<T>(rhs[2]);
        _data[3] -= static_cast<T>(rhs[3]);
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
        return Vector4D<R>(_data[0] * scalar, _data[1] * scalar, _data[2] * scalar, _data[3] * scalar);
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

        _data[0] = static_cast<T>(scalar * _data[0]);
        _data[1] = static_cast<T>(scalar * _data[1]);
        _data[2] = static_cast<T>(scalar * _data[2]);
        _data[3] = static_cast<T>(scalar * _data[3]);
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
            return Vector4D<R>(_data[0] * factor, _data[1] * factor, _data[2] * factor, _data[3] * factor);
        }
        else
        {
            assert(scalar != 0 && "Integral division by zero");
            R tScalar = static_cast<R>(scalar);
            return Vector4D<R>(_data[0] / tScalar, _data[1] / tScalar, _data[2] / tScalar, _data[3] / tScalar);
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

            _data[0] = static_cast<T>(factor * _data[0]);
            _data[1] = static_cast<T>(factor * _data[1]);
            _data[2] = static_cast<T>(factor * _data[2]);
            _data[3] = static_cast<T>(factor * _data[3]);
        }
        else
        {
            _data[0] /= static_cast<T>(scalar);
            _data[1] /= static_cast<T>(scalar);
            _data[2] /= static_cast<T>(scalar);
            _data[3] /= static_cast<T>(scalar);
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
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__FMA4__) || defined(__AVX2__)
        using R = std::common_type_t<T, U>;
        if constexpr (std::is_floating_point_v<R>)
            return std::fma(static_cast<R>(_data[0]), static_cast<R>(rhs[0]),
                            std::fma(static_cast<R>(_data[1]), static_cast<R>(rhs[1]),
                                     std::fma(static_cast<R>(_data[2]), static_cast<R>(rhs[2]),
                                              std::fma(static_cast<R>(_data[3]), static_cast<R>(rhs[3]), T(0)))));
        else
            return _data[0] * rhs[0] + _data[1] * rhs[1] + _data[2] * rhs[2] + _data[3] * rhs[3];
#else
        return _data[0] * rhs[0] + _data[1] * rhs[1] + _data[2] * rhs[2] + _data[3] * rhs[3];
#endif
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

        M tX = static_cast<M>(_data[0]);
        M tY = static_cast<M>(_data[1]);
        M tZ = static_cast<M>(_data[2]);
        M tW = static_cast<M>(_data[3]);

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
    constexpr Vector4D<Magnitude<T>> Vector4D<T>::tryNormalize(OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
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
    constexpr Vector4D<Magnitude<T>> Vector4D<T>::tryNormalize(const Vector4D& vec, OperationStatus& status) noexcept
        requires StrictArithmetic<T>
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

        if (hasNaN() | std::isnan(ontoSquared))
            return fgm::vec4d::zero<MagType>;

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


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::tryProject(const Vector4D<U>& onto, OperationStatus& status,
                                           const bool ontoNormalized) const noexcept
        -> Vector4D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        using MagType = Magnitude<R>;

        if (ontoNormalized)
        {
            status = OperationStatus::SUCCESS;
            return this->dot(onto) * onto;
        }

        /** @note Static cast ensures integral type dots don't lose much precision */
        const auto ontoSquared = static_cast<MagType>(onto.dot(onto));

        if (hasNaN() | std::isnan(ontoSquared))
        {
            status = OperationStatus::NANOPERAND;
            return fgm::vec4d::zero<MagType>;
        }

        if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return fgm::vec4d::zero<MagType>;
        }

        status = OperationStatus::SUCCESS;
        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::tryProject(const Vector4D& vec, const Vector4D<U>& onto, OperationStatus& status,
                                           const bool ontoNormalized) noexcept
        -> Vector4D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return vec.tryProject(onto, status, ontoNormalized);
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
        if (hasNaN() || from.hasNaN())
            return fgm::vec4d::zero<std::common_type_t<T, U>>;

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


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::tryReject(const Vector4D<U>& from, OperationStatus& status,
                                          bool fromNormalized) const noexcept
        -> Vector4D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return fgm::vec4d::zero<std::common_type_t<T, U>>;
        }

        return *this - this->tryProject(from, status, fromNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector4D<T>::tryReject(const Vector4D& vec, const Vector4D<U>& from, OperationStatus& status,
                                          bool fromNormalized) noexcept -> Vector4D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return vec.tryReject(from, status, fromNormalized);
    }




    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr bool Vector4D<T>::hasInf() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
            return std::isinf(_data[0]) | std::isinf(_data[1]) | std::isinf(_data[2]) | std::isinf(_data[3]);
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
            return std::isnan(_data[0]) | std::isnan(_data[1]) | std::isnan(_data[2]) | std::isnan(_data[3]);
        else
            return false;
    }


    template <Arithmetic T>
    constexpr bool Vector4D<T>::hasNaN(const Vector4D& vec) noexcept
    {
        return vec.hasNaN();
    }

} // namespace fgm
