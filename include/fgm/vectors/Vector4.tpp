#pragma once
/**
 * @file Vector4.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: January 26, 2026
 *
 * @brief @ref Vector4 template implementation.
 * @details This file contains the definitions of the template members declared in Vector4.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include <algorithm>
#include <cassert>
#include <cmath>
#include <type_traits>


#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wbitwise-instead-of-logical"
#endif

namespace fgm
{
    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Vector4<T>::Vector4(const T v1, const T v2, const T v3, const T v4) noexcept
        : _data{ T(v1), T(v2), T(v3), T(v4) }
    {}


    template <Arithmetic T>
    constexpr Vector4<T>::Vector4(const Vector2<T>& vec1, const Vector2<T>& vec2) noexcept
        : _data{ T(vec1[0]), T(vec1[1]), T(vec2[0]), T(vec2[1]) }
    {}


    template <Arithmetic T>
    constexpr Vector4<T>::Vector4(const Vector3<T>& vec, const T v) noexcept
        : _data{ T(vec[0]), T(vec[1]), T(vec[2]), T(v) }
    {}


    template <Arithmetic T>
    constexpr Vector4<T>::Vector4(const T v, const Vector3<T>& vec) noexcept
        : _data{
              T(v),
              T(vec[0]),
              T(vec[1]),
              T(vec[2]),
          }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector4<T>::Vector4(const Vector4<U>& other) noexcept
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

    /**************************************
     *                                    *
     *        SPATIAL COORDINATES         *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr T Vector4<T>::x() const noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T& Vector4<T>::x() noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::y() const noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T& Vector4<T>::y() noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::z() const noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T& Vector4<T>::z() noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::w() const noexcept
    {
        return _data[3];
    }


    template <Arithmetic T>
    constexpr T& Vector4<T>::w() noexcept
    {
        return _data[3];
    }


    /**************************************
     *                                    *
     *           STP COORDINATES          *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr T Vector4<T>::s() const noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T& Vector4<T>::s() noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::t() const noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T& Vector4<T>::t() noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::p() const noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T& Vector4<T>::p() noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::q() const noexcept
    {
        return _data[3];
    }


    template <Arithmetic T>
    constexpr T& Vector4<T>::q() noexcept
    {
        return _data[3];
    }


    /**************************************
     *                                    *
     *         COLOR COORDINATES          *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr T Vector4<T>::r() const noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T& Vector4<T>::r() noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::g() const noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T& Vector4<T>::g() noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::b() const noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T& Vector4<T>::b() noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::a() const noexcept
    {
        return _data[3];
    }


    template <Arithmetic T>
    constexpr T& Vector4<T>::a() noexcept
    {
        return _data[3];
    }


    /**************************************
     *                                    *
     *              INDEXING              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr T& Vector4<T>::operator[](const std::size_t idx) noexcept
    {
        FGM_ASSERT_MSG(idx < dimension, fgm::messages::assertion::VEC_OUT_OF_BOUNDS_ACCESS);
        return _data[idx];
    }

    template <Arithmetic T>
    constexpr const T& Vector4<T>::operator[](const std::size_t idx) const noexcept
    {
        FGM_ASSERT_MSG(idx < dimension, fgm::messages::assertion::VEC_OUT_OF_BOUNDS_ACCESS);
        return _data[idx];
    }


    /**************************************
     *                                    *
     *             SWIZZLING              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <std::size_t... Indices>
    constexpr auto Vector4<T>::swizzle() const noexcept
    {
        constexpr std::size_t swizzleDimension = sizeof...(Indices);

        static_assert(((Indices < dimension) && ...), "Index out of bounds!");
        static_assert(swizzleDimension > 0 && swizzleDimension <= constants::MAX_VECTOR_SWIZZLE_DIMENSION &&
                      "Swizzle must return a scalar, or a 2D, 3D, or 4D vector.");

        if constexpr (swizzleDimension == 4)
        {
            return Vector4(_data[Indices]...);
        }
        else if constexpr (swizzleDimension == 3)
        {
            return Vector3(_data[Indices]...);
        }
        else if constexpr (swizzleDimension == 2)
        {
            return Vector2(_data[Indices]...);
        }
        else
        {
            return T(_data[Indices]...);
        }
    }


    template <Arithmetic T>
    template <std::size_t... Indices>
    constexpr auto Vector4<T>::swizzle(const Vector4& vec) noexcept
    {
        return vec.swizzle<Indices...>();
    }


    /***************************************
     *                                     *
     *         EQUALITY (ABSOLUTE)         *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Vector4<T>::allEq(const Vector4<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return _data[0] == rhs[0] && _data[1] == rhs[1] && _data[2] == rhs[2] && _data[3] == rhs[3];
        }
        else
        {
// MSVC's constexpr evaluator incorrectly yields true for NaN relational comparisons.
// To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
// if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
#ifdef _MSC_VER
            if (std::is_constant_evaluated())
            {
                if (hasNaN() || rhs.hasNaN())
                {
                    return false;
                }
            }
#endif
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return (_data[0] == rhs[0] || fgm::abs(_data[0] - rhs[0]) <= epsilon) &&
                (_data[1] == rhs[1] || fgm::abs(_data[1] - rhs[1]) <= epsilon) &&
                (_data[2] == rhs[2] || fgm::abs(_data[2] - rhs[2]) <= epsilon) &&
                (_data[3] == rhs[3] || fgm::abs(_data[3] - rhs[3]) <= epsilon);
        }
    }

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Vector4<T>::allEq(const Vector4& lhs, const Vector4<U>& rhs, const double epsilon) noexcept
    {
        return lhs.allEq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Vector4<T>::anyNeq(const Vector4<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return _data[0] != rhs[0] || _data[1] != rhs[1] || _data[2] != rhs[2] || _data[3] != rhs[3];
        }
        else
        {
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return (_data[0] != rhs[0] && !(fgm::abs(_data[0] - rhs[0]) <= epsilon)) ||
                (_data[1] != rhs[1] && !(fgm::abs(_data[1] - rhs[1]) <= epsilon)) ||
                (_data[2] != rhs[2] && !(fgm::abs(_data[2] - rhs[2]) <= epsilon)) ||
                (_data[3] != rhs[3] && !(fgm::abs(_data[3] - rhs[3]) <= epsilon));
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Vector4<T>::anyNeq(const Vector4& lhs, const Vector4<U>& rhs, const double epsilon) noexcept
    {
        return lhs.anyNeq(rhs, epsilon);
    }


    /**************************************
     *                                    *
     *         EQUALITY OPERATORS         *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Vector4<T>::operator==(const Vector4<U>& rhs) const noexcept
    {
        return this->allEq(rhs);
    }

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Vector4<T>::operator!=(const Vector4<U>& rhs) const noexcept
    {
        return this->anyNeq(rhs);
    }


    /***************************************
     *                                     *
     *           EQUALITY (MASK)           *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::eq(const Vector4<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return Vector4<bool>(_data[0] == rhs[0], _data[1] == rhs[1], _data[2] == rhs[2], _data[3] == rhs[3]);
        }
        else
        {
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return Vector4<bool>(_data[0] == rhs[0] || fgm::abs(_data[0] - rhs[0]) <= epsilon,
                                 _data[1] == rhs[1] || fgm::abs(_data[1] - rhs[1]) <= epsilon,
                                 _data[2] == rhs[2] || fgm::abs(_data[2] - rhs[2]) <= epsilon,
                                 _data[3] == rhs[3] || fgm::abs(_data[3] - rhs[3]) <= epsilon);
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::eq(const Vector4& lhs, const Vector4<U>& rhs, const double epsilon) noexcept
    {
        return lhs.eq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::neq(const Vector4<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return Vector4<bool>(_data[0] != rhs[0], _data[1] != rhs[1], _data[2] != rhs[2], _data[3] != rhs[3]);
        }
        else
        {
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return Vector4<bool>(_data[0] != rhs[0] && !(fgm::abs(_data[0] - rhs[0]) <= epsilon),
                                 _data[1] != rhs[1] && !(fgm::abs(_data[1] - rhs[1]) <= epsilon),
                                 _data[2] != rhs[2] && !(fgm::abs(_data[2] - rhs[2]) <= epsilon),
                                 _data[3] != rhs[3] && !(fgm::abs(_data[3] - rhs[3]) <= epsilon));
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::neq(const Vector4& lhs, const Vector4<U>& rhs, const double epsilon) noexcept
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
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::gt(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector4<bool>(_data[0] > rhs[0], _data[1] > rhs[1], _data[2] > rhs[2], _data[3] > rhs[3]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::gt(const Vector4& lhs, const Vector4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.gt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::gte(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector4<bool>(_data[0] >= rhs[0], _data[1] >= rhs[1], _data[2] >= rhs[2], _data[3] >= rhs[3]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::gte(const Vector4& lhs, const Vector4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.gte(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::lt(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector4<bool>(_data[0] < rhs[0], _data[1] < rhs[1], _data[2] < rhs[2], _data[3] < rhs[3]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::lt(const Vector4& lhs, const Vector4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.lt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::lte(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<PromotedValue_t<T, U>>;
        return Vector4<bool>(
            static_cast<R>(_data[0]) <= static_cast<R>(rhs[0]), static_cast<R>(_data[1]) <= static_cast<R>(rhs[1]),
            static_cast<R>(_data[2]) <= static_cast<R>(rhs[2]), static_cast<R>(_data[3]) <= static_cast<R>(rhs[3]));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::lte(const Vector4& lhs, const Vector4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.lte(rhs);
    }


    /***************************************
     *                                     *
     *        COMPARISON OPERATORS         *
     *                                     *
     ***************************************/

#ifdef ENABLE_FGM_SHADER_OPERATORS

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::operator>(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->gt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::operator>=(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->gte(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::operator<(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->lt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<bool> Vector4<T>::operator<=(const Vector4<U>& rhs) const noexcept
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
    constexpr Vector4<T> Vector4<T>::operator&(const Vector4& rhs) const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector4(_data[0] & rhs[0], _data[1] & rhs[1], _data[2] & rhs[2], _data[3] & rhs[3]);
    }

    template <Arithmetic T>
    constexpr Vector4<T>& Vector4<T>::operator&=(const Vector4& rhs) noexcept
        requires std::is_same_v<T, bool>
    {
        *this = *this & rhs;
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector4<T> Vector4<T>::operator|(const Vector4& rhs) const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector4(_data[0] | rhs[0], _data[1] | rhs[1], _data[2] | rhs[2], _data[3] | rhs[3]);
    }


    template <Arithmetic T>
    constexpr Vector4<T>& Vector4<T>::operator|=(const Vector4& rhs) noexcept
        requires std::is_same_v<T, bool>
    {
        *this = *this & rhs;
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector4<T> Vector4<T>::operator!() const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector4(!_data[0], !_data[1], !_data[2], !_data[3]);
    }


    /*************************************
     *                                   *
     *      ARITHMETIC OPERATORS         *
     *                                   *
     *************************************/

    /*************************************
     *                                   *
     *            ADDITION               *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::operator+(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Vector4<R>(_data[0] + rhs[0], _data[1] + rhs[1], _data[2] + rhs[2], _data[3] + rhs[3]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<T>& Vector4<T>::operator+=(const Vector4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] += static_cast<T>(rhs[0]);
        _data[1] += static_cast<T>(rhs[1]);
        _data[2] += static_cast<T>(rhs[2]);
        _data[3] += static_cast<T>(rhs[3]);
        return *this;
    }


    /*************************************
     *                                   *
     *           SUBTRACTION             *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::operator-(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Vector4<R>(_data[0] - rhs[0], _data[1] - rhs[1], _data[2] - rhs[2], _data[3] - rhs[3]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector4<T>& Vector4<T>::operator-=(const Vector4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] -= static_cast<T>(rhs[0]);
        _data[1] -= static_cast<T>(rhs[1]);
        _data[2] -= static_cast<T>(rhs[2]);
        _data[3] -= static_cast<T>(rhs[3]);
        return *this;
    }


    /**************************************
     *                                    *
     *         INVERT OPERATION           *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr Vector4<T> Vector4<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    {
        return Vector4(-_data[0], -_data[1], -_data[2], -_data[3]);
    }


    /*************************************
     *                                   *
     *           MULTIPLICATION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedVector4<T, S> Vector4<T>::operator*(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        return Vector4<R>(_data[0] * scalar, _data[1] * scalar, _data[2] * scalar, _data[3] * scalar);
    }


    template <StrictArithmetic T, StrictArithmetic S>
    constexpr PromotedVector4<T, S> operator*(const S scalar, const Vector4<T>& vector) noexcept
        requires StrictArithmetic<T>
    {
        return vector * scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vector4<T>& Vector4<T>::operator*=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] = static_cast<T>(scalar * _data[0]);
        _data[1] = static_cast<T>(scalar * _data[1]);
        _data[2] = static_cast<T>(scalar * _data[2]);
        _data[3] = static_cast<T>(scalar * _data[3]);
        return *this;
    }


    /*************************************
     *                                   *
     *             DIVISION              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedVector4<T, S> Vector4<T>::operator/(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            FGM_ASSERT_MSG(fgm::abs(scalar) >= fgm::Config::EPSILON<R>, fgm::messages::assertion::VEC_DIV_BY_ZERO);

            R factor = R(1) / static_cast<R>(scalar);
            return Vector4<R>(_data[0] * factor, _data[1] * factor, _data[2] * factor, _data[3] * factor);
        }
        else
        {
            FGM_ASSERT_MSG(scalar != 0, fgm::messages::assertion::VEC_DIV_BY_ZERO);
            R tScalar = static_cast<R>(scalar);
            return Vector4<R>(_data[0] / tScalar, _data[1] / tScalar, _data[2] / tScalar, _data[3] / tScalar);
        }
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vector4<T>& Vector4<T>::operator/=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            FGM_ASSERT_MSG(fgm::abs(scalar) >= fgm::Config::EPSILON<R>, fgm::messages::assertion::VEC_DIV_BY_ZERO);

            R factor = R(1) / static_cast<R>(scalar);

            _data[0] = static_cast<T>(factor * _data[0]);
            _data[1] = static_cast<T>(factor * _data[1]);
            _data[2] = static_cast<T>(factor * _data[2]);
            _data[3] = static_cast<T>(factor * _data[3]);
        }
        else
        {
            FGM_ASSERT_MSG(scalar != 0, fgm::messages::assertion::VEC_DIV_BY_ZERO);

            _data[0] /= static_cast<T>(scalar);
            _data[1] /= static_cast<T>(scalar);
            _data[2] /= static_cast<T>(scalar);
            _data[3] /= static_cast<T>(scalar);
        }

        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedVector4<T, S> Vector4<T>::safeDiv(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (hasNaN() | fgm::isnan(scalar) | (fgm::abs(scalar) <= std::numeric_limits<S>::epsilon()))
            {
                return fgm::Vector4<R>::zero();
            }
        }
        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                return fgm::Vector4<R>::zero();
            }
        }

        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedVector4<T, S> Vector4<T>::safeDiv(const Vector4& vec, const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeDiv(scalar);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedVector4<T, S> Vector4<T>::tryDiv(S scalar, OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (hasNaN() | fgm::isnan(scalar))
            {
                status = OperationStatus::NANOPERAND;
                return fgm::Vector4<R>::zero();
            }
            if (fgm::abs(scalar) <= std::numeric_limits<S>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return fgm::Vector4<R>::zero();
            }
        }

        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return fgm::Vector4<R>::zero();
            }
        }


        status = OperationStatus::SUCCESS;
        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedVector4<T, S> Vector4<T>::tryDiv(const Vector4& vec, S scalar, OperationStatus& status) noexcept
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
        requires StrictSignedness<T, U>
    constexpr PromotedValue_t<T, U> Vector4<T>::dot(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__FMA4__) || defined(__AVX2__)
        using R = PromotedValue_t<T, U>;
        if constexpr (std::is_floating_point_v<R>)
        {
            return std::fma(static_cast<R>(_data[0]), static_cast<R>(rhs[0]),
                            std::fma(static_cast<R>(_data[1]), static_cast<R>(rhs[1]),
                                     std::fma(static_cast<R>(_data[2]), static_cast<R>(rhs[2]),
                                              std::fma(static_cast<R>(_data[3]), static_cast<R>(rhs[3]), T(0)))));
        }
        else
        {
            return _data[0] * rhs[0] + _data[1] * rhs[1] + _data[2] * rhs[2] + _data[3] * rhs[3];
        }
#else
        return _data[0] * rhs[0] + _data[1] * rhs[1] + _data[2] * rhs[2] + _data[3] * rhs[3];
#endif
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedValue_t<T, U> Vector4<T>::dot(const Vector4& lhs, const Vector4<U>& rhs) noexcept
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
    constexpr Magnitude<T> Vector4<T>::mag() const noexcept
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
    constexpr Magnitude<T> Vector4<T>::mag(const Vector4& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.mag();
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::magSq() const noexcept
        requires StrictArithmetic<T>
    {
        return this->dot(*this);
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::magSq(const Vector4& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.magSq();
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::manhattanNorm() const noexcept
        requires StrictArithmetic<T>
    {
        return fgm::abs(_data[0]) + fgm::abs(_data[1]) + fgm::abs(_data[2]) + fgm::abs(_data[3]);
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::manhattanNorm(const Vector4& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.manhattanNorm();
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::chebyshevNorm() const noexcept
        requires StrictArithmetic<T>
    {
        return std::max({ fgm::abs(_data[0]), fgm::abs(_data[1]), fgm::abs(_data[2]), fgm::abs(_data[3]) });
    }


    template <Arithmetic T>
    constexpr T Vector4<T>::chebyshevNorm(const Vector4& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.chebyshevNorm();
    }



    /**************************************
     *                                    *
     *         VECTOR DISTANCE            *
     *                                    *
     **************************************/

    /**************************************
     *                                    *
     *             EUCLIDEAN              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Magnitude<PromotedValue_t<T, U>> Vector4<T>::dist(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = Magnitude<PromotedValue_t<T, U>>;
        const auto dx = utils::diffAbs(_data[0], rhs[0]);
        const auto dy = utils::diffAbs(_data[1], rhs[1]);
        const auto dz = utils::diffAbs(_data[2], rhs[2]);
        const auto dw = utils::diffAbs(_data[3], rhs[3]);
        return static_cast<R>(std::sqrt(dx * dx + dy * dy + dz * dz + dw * dw));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Magnitude<PromotedValue_t<T, U>> Vector4<T>::dist(const Vector4<U>& lhs, const Vector4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.dist(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedValue_t<T, U> Vector4<T>::distSq(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        const auto dx = utils::diffAbs(_data[0], rhs[0]);
        const auto dy = utils::diffAbs(_data[1], rhs[1]);
        const auto dz = utils::diffAbs(_data[2], rhs[2]);
        const auto dw = utils::diffAbs(_data[3], rhs[3]);

        return dx * dx + dy * dy + dz * dz + dw * dw;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedValue_t<T, U> Vector4<T>::distSq(const Vector4<U>& lhs, const Vector4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.distSq(rhs);
    }



    /**************************************
     *                                    *
     *             MANHATTAN              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedValue_t<T, U> Vector4<T>::manhattanDist(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return utils::diffAbs(_data[0], rhs[0]) + utils::diffAbs(_data[1], rhs[1]) + utils::diffAbs(_data[2], rhs[2]) +
            utils::diffAbs(_data[3], rhs[3]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedValue_t<T, U> Vector4<T>::manhattanDist(const Vector4<U>& lhs, const Vector4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.manhattanDist(rhs);
    }



    /**************************************
     *                                    *
     *             CHEBYSHEV              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedValue_t<T, U> Vector4<T>::chebyshevDist(const Vector4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return std::max(std::max(utils::diffAbs(_data[0], rhs[0]), utils::diffAbs(_data[1], rhs[1])),
                        std::max(utils::diffAbs(_data[2], rhs[2]), utils::diffAbs(_data[3], rhs[3])));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedValue_t<T, U> Vector4<T>::chebyshevDist(const Vector4<U>& lhs, const Vector4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.chebyshevDist(rhs);
    }



    /*************************************
     *                                   *
     *       VECTOR NORMALIZATION        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Vector4<Magnitude<T>> Vector4<T>::normalize() const noexcept
        requires StrictArithmetic<T>
    {
        const auto magnitude = mag();
        FGM_ASSERT_MSG(magnitude >= fgm::Config::EPSILON<decltype(magnitude)>,
                       fgm::messages::assertion::VEC_NORMALIZE_DIV_BY_ZERO);
        return *this / magnitude;
    }


    template <Arithmetic T>
    constexpr Vector4<Magnitude<T>> Vector4<T>::normalize(const Vector4& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.normalize();
    }


    template <Arithmetic T>
    constexpr Vector4<Magnitude<T>> Vector4<T>::safeNormalize() const noexcept
        requires StrictArithmetic<T>
    {
        using R     = Magnitude<T>;
        R magnitude = mag();
        if (fgm::isnan(magnitude))
        {
            return fgm::Vector4<R>::zero();
        }
        if (magnitude <= Config::EPSILON_SQUARE<R>)
        {
            return fgm::Vector4<R>::zero();
        }

        return *this / magnitude;
    }


    template <Arithmetic T>
    constexpr Vector4<Magnitude<T>> Vector4<T>::safeNormalize(const Vector4& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeNormalize();
    }


    template <Arithmetic T>
    constexpr Vector4<Magnitude<T>> Vector4<T>::tryNormalize(OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R     = Magnitude<T>;
        R magnitude = mag();
        if (fgm::isnan(magnitude))
        {
            status = OperationStatus::NANOPERAND;
            return fgm::Vector4<R>::zero();
        }
        if (magnitude <= Config::EPSILON_SQUARE<R>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return fgm::Vector4<R>::zero();
        }

        status = OperationStatus::SUCCESS;
        return *this / magnitude;
    }


    template <Arithmetic T>
    constexpr Vector4<Magnitude<T>> Vector4<T>::tryNormalize(const Vector4& vec, OperationStatus& status) noexcept
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
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector4<T, U> Vector4<T>::project(const Vector4<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        /** @note Static cast ensures integral type dots don't lose much precision */
        const auto b2 = static_cast<Magnitude<R>>(onto.dot(onto));
        FGM_ASSERT_MSG(b2 >= fgm::Config::EPSILON_SQUARE<Magnitude<R>>,
                       fgm::messages::assertion::VEC_PROJECT_DIV_BY_ZERO);

        return this->dot(onto) / b2 * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::projectNorm(const Vector4<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        return this->dot(onto) * onto; // a.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector4<T, U> Vector4<T>::project(const Vector4& vec, const Vector4<U>& onto) noexcept
        requires StrictArithmetic<T>
    {
        return vec.project(onto);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::projectNorm(const Vector4& vec, const Vector4<U>& onto) noexcept
        requires StrictArithmetic<T>
    {
        return vec.projectNorm(onto);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector4<T, U> Vector4<T>::safeProject(const Vector4<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = PromotedValue_t<T, U>;
        using MagType = Magnitude<R>;

        /** @note Static cast ensures integral type dots don't lose much precision */
        const auto ontoSquared = static_cast<MagType>(onto.dot(onto));

        if (hasNaN() | fgm::isnan(ontoSquared))
        {
            return fgm::Vector4<MagType>::zero();
        }

        if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
        {
            return fgm::Vector4<MagType>::zero();
        }

        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::safeProjectNorm(const Vector4<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;

        if (hasNaN() || onto.hasNaN())
        {
            return fgm::Vector4<R>::zero();
        }
        return this->dot(onto) * onto;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector4<T, U> Vector4<T>::safeProject(const Vector4& vec, const Vector4<U>& onto) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeProject(onto);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::safeProjectNorm(const Vector4& vec, const Vector4<U>& onto) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeProjectNorm(onto);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector4<T, U> Vector4<T>::tryProject(const Vector4<U>& onto,
                                                                OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = PromotedValue_t<T, U>;
        using MagType = Magnitude<R>;

        /** @note Static cast ensures integral type dots don't lose much precision */
        const auto ontoSquared = static_cast<MagType>(onto.dot(onto));

        if (hasNaN() | fgm::isnan(ontoSquared))
        {
            status = OperationStatus::NANOPERAND;
            return fgm::Vector4<MagType>::zero();
        }

        if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return fgm::Vector4<MagType>::zero();
        }

        status = OperationStatus::SUCCESS;
        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::tryProjectNorm(const Vector4<U>& onto,
                                                               OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;

        if (hasNaN() || onto.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return fgm::Vector4<R>::zero();
        }

        status = OperationStatus::SUCCESS;
        return this->dot(onto) * onto;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector4<T, U> Vector4<T>::tryProject(const Vector4& vec, const Vector4<U>& onto,
                                                                OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    {
        return vec.tryProject(onto, status);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::tryProjectNorm(const Vector4& vec, const Vector4<U>& onto,
                                                               OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    {
        return vec.tryProjectNorm(onto, status);
    }


    /*************************************
     *                                   *
     *         VECTOR REJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector4<T, U> Vector4<T>::reject(const Vector4<U>& from) const noexcept
        requires StrictArithmetic<T>
    {
        return static_cast<PromotedFloatVector4<T, U>>(*this) - this->project(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::rejectNorm(const Vector4<U>& from) const noexcept
        requires StrictArithmetic<T>
    {
        return *this - this->projectNorm(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector4<T, U> Vector4<T>::reject(const Vector4& vector, const Vector4<U>& from) noexcept
        requires StrictArithmetic<T>
    {
        return vector.reject(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::rejectNorm(const Vector4& vector, const Vector4<U>& from) noexcept
        requires StrictArithmetic<T>
    {
        return vector.rejectNorm(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector4<T, U> Vector4<T>::safeReject(const Vector4<U>& from) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            return fgm::Vector4<Magnitude<PromotedValue_t<T, U>>>::zero();
        }

        return static_cast<PromotedFloatVector4<T, U>>(*this) - safeProject(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::safeRejectNorm(const Vector4<U>& from) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            return fgm::Vector4<PromotedValue_t<T, U>>::zero();
        }

        return *this - safeProjectNorm(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector4<T, U> Vector4<T>::safeReject(const Vector4& vec, const Vector4<U>& from) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeReject(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::safeRejectNorm(const Vector4& vec, const Vector4<U>& from) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeRejectNorm(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector4<T, U> Vector4<T>::tryReject(const Vector4<U>& from,
                                                               OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return fgm::Vector4<Magnitude<PromotedValue_t<T, U>>>::zero();
        }

        return static_cast<PromotedFloatVector4<T, U>>(*this) - this->tryProject(from, status);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::tryRejectNorm(const Vector4<U>& from,
                                                              OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return fgm::Vector4<PromotedValue_t<T, U>>::zero();
        }

        return *this - this->tryProjectNorm(from, status);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector4<T, U> Vector4<T>::tryReject(const Vector4& vec, const Vector4<U>& from,
                                                               OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    {
        return vec.tryReject(from, status);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector4<T, U> Vector4<T>::tryRejectNorm(const Vector4& vec, const Vector4<U>& from,
                                                              OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    {
        return vec.tryRejectNorm(from, status);
    }


    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr bool Vector4<T>::hasInf() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return fgm::isinf(_data[0]) | fgm::isinf(_data[1]) | fgm::isinf(_data[2]) | fgm::isinf(_data[3]);
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    constexpr bool Vector4<T>::hasInf(const Vector4& vec) noexcept
    {
        return vec.hasInf();
    }


    template <Arithmetic T>
    constexpr bool Vector4<T>::hasNaN() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return fgm::isnan(_data[0]) | fgm::isnan(_data[1]) | fgm::isnan(_data[2]) | fgm::isnan(_data[3]);
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    constexpr bool Vector4<T>::hasNaN(const Vector4& vec) noexcept
    {
        return vec.hasNaN();
    }
} // namespace fgm


#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
