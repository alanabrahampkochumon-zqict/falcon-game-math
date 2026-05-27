#pragma once
/**
 * @file Vector3D.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: January 19, 2026
 *
 * @brief @ref Vector3D template implementation.
 * @details This file contains the definitions of the template members declared in Vector3D.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <algorithm>



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
    constexpr Vector3D<T>::Vector3D() noexcept: _data{ T(0), T(0), T(0) }
    {}


    template <Arithmetic T>
    constexpr Vector3D<T>::Vector3D(T v1, T v2, T v3) noexcept: _data{ v1, v2, v3 }
    {}


    template <Arithmetic T>
    constexpr Vector3D<T>::Vector3D(Vector2D<T> vec, T v) noexcept: _data{ vec[0], vec[1], v }
    {}


    template <Arithmetic T>
    constexpr Vector3D<T>::Vector3D(T v, Vector2D<T> vec) noexcept: _data{ v, vec[0], vec[1] }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector3D<T>::Vector3D(const Vector3D<U>& other) noexcept
    {
        _data[0] = static_cast<T>(other[0]);
        _data[1] = static_cast<T>(other[1]);
        _data[2] = static_cast<T>(other[2]);
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
    constexpr T Vector3D<T>::x() const noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T& Vector3D<T>::x() noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T Vector3D<T>::y() const noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T& Vector3D<T>::y() noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T Vector3D<T>::z() const noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T& Vector3D<T>::z() noexcept
    {
        return _data[2];
    }


    /**************************************
     *                                    *
     *           STP COORDINATES          *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr T Vector3D<T>::s() const noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T& Vector3D<T>::s() noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T Vector3D<T>::t() const noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T& Vector3D<T>::t() noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T Vector3D<T>::p() const noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T& Vector3D<T>::p() noexcept
    {
        return _data[2];
    }


    /**************************************
     *                                    *
     *         COLOR COORDINATES          *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr T Vector3D<T>::r() const noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T& Vector3D<T>::r() noexcept
    {
        return _data[0];
    }


    template <Arithmetic T>
    constexpr T Vector3D<T>::g() const noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T& Vector3D<T>::g() noexcept
    {
        return _data[1];
    }


    template <Arithmetic T>
    constexpr T Vector3D<T>::b() const noexcept
    {
        return _data[2];
    }


    template <Arithmetic T>
    constexpr T& Vector3D<T>::b() noexcept
    {
        return _data[2];
    }


    /**************************************
     *                                    *
     *              INDEXING              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr T& Vector3D<T>::operator[](const std::size_t idx) noexcept
    {
        FGM_ASSERT_MSG(idx < dimension, fgm::messages::assertion::VEC_OUT_OF_BOUNDS_ACCESS);
        return _data[idx];
    }


    template <Arithmetic T>
    constexpr const T& Vector3D<T>::operator[](const std::size_t idx) const noexcept
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
    constexpr auto Vector3D<T>::swizzle() const noexcept
    {
        constexpr std::size_t swizzleDimension = sizeof...(Indices);

        static_assert(((Indices < dimension) && ...), "Index out of bounds!");
        static_assert(swizzleDimension > 0 && swizzleDimension <= dimension &&
                      "Swizzle must return a scalar, or a 2D, or 3D vector.");
        if constexpr (swizzleDimension == 3)
        {
            return Vector3D(_data[Indices]...);
        }
        else if constexpr (swizzleDimension == 2)
        {
            return Vector2D(_data[Indices]...);
        }
        else
        {
            return T(_data[Indices]...);
        }
    }


    template <Arithmetic T>
    template <std::size_t... Indices>
    constexpr auto Vector3D<T>::swizzle(const Vector3D& vec) noexcept
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
    constexpr bool Vector3D<T>::allEq(const Vector3D<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return _data[0] == rhs[0] && _data[1] == rhs[1] && _data[2] == rhs[2];
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
                (_data[2] == rhs[2] || fgm::abs(_data[2] - rhs[2]) <= epsilon);
        }
    }

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Vector3D<T>::allEq(const Vector3D& lhs, const Vector3D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.allEq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Vector3D<T>::anyNeq(const Vector3D<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return _data[0] != rhs[0] || _data[1] != rhs[1] || _data[2] != rhs[2];
        }
        else
        {
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return (_data[0] != rhs[0] && !(fgm::abs(_data[0] - rhs[0]) <= epsilon)) ||
                (_data[1] != rhs[1] && !(fgm::abs(_data[1] - rhs[1]) <= epsilon)) ||
                (_data[2] != rhs[2] && !(fgm::abs(_data[2] - rhs[2]) <= epsilon));
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Vector3D<T>::anyNeq(const Vector3D& lhs, const Vector3D<U>& rhs, const double epsilon) noexcept
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
    constexpr bool Vector3D<T>::operator==(const Vector3D<U>& rhs) const noexcept
    {
        return this->allEq(rhs);
    }

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Vector3D<T>::operator!=(const Vector3D<U>& rhs) const noexcept
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
    constexpr Vector3D<bool> Vector3D<T>::eq(const Vector3D<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return Vector3D<bool>(_data[0] == rhs[0], _data[1] == rhs[1], _data[2] == rhs[2]);
        }
        else
        {
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return Vector3D<bool>(_data[0] == rhs[0] || fgm::abs(_data[0] - rhs[0]) <= epsilon,
                                  _data[1] == rhs[1] || fgm::abs(_data[1] - rhs[1]) <= epsilon,
                                  _data[2] == rhs[2] || fgm::abs(_data[2] - rhs[2]) <= epsilon);
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::eq(const Vector3D& lhs, const Vector3D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.eq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::neq(const Vector3D<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return Vector3D<bool>(_data[0] != rhs[0], _data[1] != rhs[1], _data[2] != rhs[2]);
        }
        else
        {
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return Vector3D<bool>(_data[0] != rhs[0] && !(fgm::abs(_data[0] - rhs[0]) <= epsilon),
                                  _data[1] != rhs[1] && !(fgm::abs(_data[1] - rhs[1]) <= epsilon),
                                  _data[2] != rhs[2] && !(fgm::abs(_data[2] - rhs[2]) <= epsilon));
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::neq(const Vector3D& lhs, const Vector3D<U>& rhs,
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
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::gt(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector3D<bool>(_data[0] > rhs[0], _data[1] > rhs[1], _data[2] > rhs[2]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::gt(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.gt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::gte(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector3D<bool>(_data[0] >= rhs[0], _data[1] >= rhs[1], _data[2] >= rhs[2]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::gte(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.gte(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::lt(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector3D<bool>(_data[0] < rhs[0], _data[1] < rhs[1], _data[2] < rhs[2]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::lt(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.lt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::lte(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<PromotedValue_t<T, U>>;
        return Vector3D<bool>(static_cast<R>(_data[0]) <= static_cast<R>(rhs[0]),
                              static_cast<R>(_data[1]) <= static_cast<R>(rhs[1]),
                              static_cast<R>(_data[2]) <= static_cast<R>(rhs[2]));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::lte(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
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
    constexpr Vector3D<bool> Vector3D<T>::operator>(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->gt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::operator>=(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->gte(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::operator<(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->lt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<bool> Vector3D<T>::operator<=(const Vector3D<U>& rhs) const noexcept
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
    constexpr Vector3D<T> Vector3D<T>::operator&(const Vector3D& rhs) const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector3D(_data[0] & rhs[0], _data[1] & rhs[1], _data[2] & rhs[2]);
    }


    template <Arithmetic T>
    constexpr Vector3D<T>& Vector3D<T>::operator&=(const Vector3D& rhs) noexcept
        requires std::is_same_v<T, bool>
    {
        *this = *this & rhs;
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector3D<T> Vector3D<T>::operator|(const Vector3D& rhs) const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector3D(_data[0] | rhs[0], _data[1] | rhs[1], _data[2] | rhs[2]);
    }


    template <Arithmetic T>
    constexpr Vector3D<T>& Vector3D<T>::operator|=(const Vector3D& rhs) noexcept
        requires std::is_same_v<T, bool>
    {
        *this = *this & rhs;
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector3D<T> Vector3D<T>::operator!() const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector3D(!_data[0], !_data[1], !_data[2]);
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
    constexpr PromotedVector3D<T, U> Vector3D<T>::operator+(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Vector3D<R>(_data[0] + rhs[0], _data[1] + rhs[1], _data[2] + rhs[2]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<T>& Vector3D<T>::operator+=(const Vector3D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] += static_cast<T>(rhs[0]);
        _data[1] += static_cast<T>(rhs[1]);
        _data[2] += static_cast<T>(rhs[2]);
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
    constexpr PromotedVector3D<T, U> Vector3D<T>::operator-(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Vector3D<R>(_data[0] - rhs[0], _data[1] - rhs[1], _data[2] - rhs[2]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Vector3D<T>& Vector3D<T>::operator-=(const Vector3D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] -= static_cast<T>(rhs[0]);
        _data[1] -= static_cast<T>(rhs[1]);
        _data[2] -= static_cast<T>(rhs[2]);
        return *this;
    }


    /**************************************
     *                                    *
     *         INVERT OPERATION           *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr Vector3D<T> Vector3D<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    {
        return Vector3D(-_data[0], -_data[1], -_data[2]);
    }


    /*************************************
     *                                   *
     *           MULTIPLICATION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedVector3D<T, S> Vector3D<T>::operator*(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        return Vector3D<R>(_data[0] * scalar, _data[1] * scalar, _data[2] * scalar);
    }


    template <StrictArithmetic T, StrictArithmetic S>
    constexpr auto operator*(const S scalar, const Vector3D<T>& vector) noexcept -> Vector3D<PromotedValue_t<T, S>>
        requires StrictArithmetic<T>
    {
        return vector * scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vector3D<T>& Vector3D<T>::operator*=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] = static_cast<T>(scalar * _data[0]);
        _data[1] = static_cast<T>(scalar * _data[1]);
        _data[2] = static_cast<T>(scalar * _data[2]);
        return *this;
    }


    /*************************************
     *                                   *
     *             DIVISION              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedVector3D<T, S> Vector3D<T>::operator/(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            FGM_ASSERT_MSG(fgm::abs(scalar) >= fgm::Config::EPSILON<R>, fgm::messages::assertion::VEC_DIV_BY_ZERO);
            R factor = R(1) / static_cast<R>(scalar);
            return Vector3D<R>(_data[0] * factor, _data[1] * factor, _data[2] * factor);
        }
        else
        {
            FGM_ASSERT_MSG(scalar != 0, fgm::messages::assertion::VEC_DIV_BY_ZERO);
            R tScalar = static_cast<R>(scalar);
            return Vector3D<R>(_data[0] / tScalar, _data[1] / tScalar, _data[2] / tScalar);
        }
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vector3D<T>& Vector3D<T>::operator/=(const S scalar) noexcept
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
        }
        else
        {
            FGM_ASSERT_MSG(scalar != 0, fgm::messages::assertion::VEC_DIV_BY_ZERO);
            _data[0] /= static_cast<T>(scalar);
            _data[1] /= static_cast<T>(scalar);
            _data[2] /= static_cast<T>(scalar);
        }

        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedVector3D<T, S> Vector3D<T>::safeDiv(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (hasNaN() | fgm::isnan(scalar) | (fgm::abs(scalar) <= std::numeric_limits<S>::epsilon()))
            {
                return fgm::vec3d::zero<R>;
            }
        }
        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                return fgm::vec3d::zero<R>;
            }
        }

        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedVector3D<T, S> Vector3D<T>::safeDiv(const Vector3D& vec, const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeDiv(scalar);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedVector3D<T, S> Vector3D<T>::tryDiv(S scalar, OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (hasNaN() | fgm::isnan(scalar))
            {
                status = OperationStatus::NANOPERAND;
                return fgm::vec3d::zero<R>;
            }
            if (fgm::abs(scalar) <= std::numeric_limits<S>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return fgm::vec3d::zero<R>;
            }
        }

        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return fgm::vec3d::zero<R>;
            }
        }


        status = OperationStatus::SUCCESS;
        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedVector3D<T, S> Vector3D<T>::tryDiv(const Vector3D& vec, S scalar,
                                                         OperationStatus& status) noexcept
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
    constexpr auto Vector3D<T>::dot(const Vector3D<U>& rhs) const noexcept -> PromotedValue_t<T, U>
        requires StrictArithmetic<T>
    {
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__FMA4__) || defined(__AVX2__)
        using R = PromotedValue_t<T, U>;
        if constexpr (std::is_floating_point_v<R>)
        {
            if (!std::is_constant_evaluated())
            {
                return std::fma(static_cast<R>(_data[0]), static_cast<R>(rhs[0]),
                                std::fma(static_cast<R>(_data[1]), static_cast<R>(rhs[1]),
                                         std::fma(static_cast<R>(_data[2]), static_cast<R>(rhs[2]), T(0))));
            }
        }
        return _data[0] * rhs[0] + _data[1] * rhs[1] + _data[2] * rhs[2];
#else
        return _data[0] * rhs[0] + _data[1] * rhs[1] + _data[2] * rhs[2];
#endif
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr auto Vector3D<T>::dot(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept -> PromotedValue_t<T, U>
        requires StrictArithmetic<T>
    {
        return lhs.dot(rhs);
    }


    /*************************************
     *                                   *
     *       VECTOR CROSS PRODUCT        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <SignedStrictArithmetic U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::cross(const Vector3D<U>& rhs) const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Vector3D<R>(_data[1] * rhs[2] - _data[2] * rhs[1], _data[2] * rhs[0] - _data[0] * rhs[2],
                           _data[0] * rhs[1] - _data[1] * rhs[0]);
    }


    template <Arithmetic T>
    template <SignedStrictArithmetic U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::cross(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
        requires SignedStrictArithmetic<T>
    {
        return lhs.cross(rhs);
    }


    /*************************************
     *                                   *
     *         VECTOR MAGNITUDE          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Magnitude<T> Vector3D<T>::mag() const noexcept
        requires StrictArithmetic<T>
    {
        using M = Magnitude<T>;

        M tX = static_cast<M>(_data[0]);
        M tY = static_cast<M>(_data[1]);
        M tZ = static_cast<M>(_data[2]);

        return sqrt(tX * tX + tY * tY + tZ * tZ);
    }


    template <Arithmetic T>
    constexpr Magnitude<T> Vector3D<T>::mag(const Vector3D& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.mag();
    }


    template <Arithmetic T>
    constexpr T Vector3D<T>::magSq() const noexcept
        requires StrictArithmetic<T>
    {
        return this->dot(*this);
    }


    template <Arithmetic T>
    constexpr T Vector3D<T>::magSq(const Vector3D& vector) noexcept
        requires StrictArithmetic<T>
    {
        return vector.magSq();
    }


    template <Arithmetic T>
    constexpr T Vector3D<T>::manhattanNorm() const noexcept
        requires StrictArithmetic<T>
    {
        return fgm::abs(_data[0]) + fgm::abs(_data[1]) + fgm::abs(_data[2]);
    }


    template <Arithmetic T>
    constexpr T Vector3D<T>::manhattanNorm(const Vector3D& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.manhattanNorm();
    }


    template <Arithmetic T>
    constexpr T Vector3D<T>::chebyshevNorm() const noexcept
        requires StrictArithmetic<T>
    {
        return std::max({ fgm::abs(_data[0]), fgm::abs(_data[1]), fgm::abs(_data[2]) });
    }


    template <Arithmetic T>
    constexpr T Vector3D<T>::chebyshevNorm(const Vector3D& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.chebyshevNorm();
    }


    /*************************************
     *                                   *
     *       VECTOR NORMALIZATION        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Vector3D<Magnitude<T>> Vector3D<T>::normalize() const noexcept
        requires StrictArithmetic<T>
    {
        const auto magnitude = mag();
        FGM_ASSERT_MSG(magnitude >= fgm::Config::EPSILON<decltype(magnitude)>,
                       fgm::messages::assertion::VEC_NORMALIZE_DIV_BY_ZERO);
        return *this / magnitude;
    }


    template <Arithmetic T>
    constexpr Vector3D<Magnitude<T>> Vector3D<T>::normalize(const Vector3D& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.normalize();
    }


    template <Arithmetic T>
    constexpr Vector3D<Magnitude<T>> Vector3D<T>::safeNormalize() const noexcept
        requires StrictArithmetic<T>
    {
        using R     = Magnitude<T>;
        R magnitude = mag();
        if (fgm::isnan(magnitude))
        {
            return fgm::vec3d::zero<R>;
        }
        if (magnitude <= Config::EPSILON_SQUARE<R>)
        {
            return fgm::vec3d::zero<R>;
        }

        return *this / magnitude;
    }


    template <Arithmetic T>
    constexpr Vector3D<Magnitude<T>> Vector3D<T>::safeNormalize(const Vector3D& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeNormalize();
    }


    template <Arithmetic T>
    constexpr Vector3D<Magnitude<T>> Vector3D<T>::tryNormalize(OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R     = Magnitude<T>;
        R magnitude = mag();
        if (fgm::isnan(magnitude))
        {
            status = OperationStatus::NANOPERAND;
            return fgm::vec3d::zero<R>;
        }
        if (magnitude <= Config::EPSILON_SQUARE<R>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return fgm::vec3d::zero<R>;
        }

        status = OperationStatus::SUCCESS;
        return *this / magnitude;
    }


    template <Arithmetic T>
    constexpr Vector3D<Magnitude<T>> Vector3D<T>::tryNormalize(const Vector3D& vec, OperationStatus& status) noexcept
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
    constexpr PromotedFloatVector3D<T, U> Vector3D<T>::project(const Vector3D<U>& onto) const noexcept
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
    constexpr PromotedVector3D<T, U> Vector3D<T>::projectNorm(const Vector3D<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        return this->dot(onto) * onto; // a.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector3D<T, U> Vector3D<T>::project(const Vector3D& vec, const Vector3D<U>& onto) noexcept
        requires StrictArithmetic<T>
    {
        return vec.project(onto);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::projectNorm(const Vector3D& vec, const Vector3D<U>& onto) noexcept
        requires StrictArithmetic<T>
    {
        return vec.projectNorm(onto);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector3D<T, U> Vector3D<T>::safeProject(const Vector3D<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = PromotedValue_t<T, U>;
        using MagType = Magnitude<R>;

        /** @note Static cast ensures integral type dots don't lose much precision */
        const auto ontoSquared = static_cast<MagType>(onto.dot(onto));

        if (hasNaN() | fgm::isnan(ontoSquared))
        {
            return fgm::vec3d::zero<MagType>;
        }

        if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
        {
            return fgm::vec3d::zero<MagType>;
        }

        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::safeProjectNorm(const Vector3D<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;

        if (hasNaN() || onto.hasNaN())
        {
            return fgm::vec3d::zero<R>;
        }
        return this->dot(onto) * onto;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector3D<T, U> Vector3D<T>::safeProject(const Vector3D& vec,
                                                                   const Vector3D<U>& onto) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeProject(onto);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::safeProjectNorm(const Vector3D& vec, const Vector3D<U>& onto) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeProjectNorm(onto);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector3D<T, U> Vector3D<T>::tryProject(const Vector3D<U>& onto,
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
            return fgm::vec3d::zero<MagType>;
        }

        if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return fgm::vec3d::zero<MagType>;
        }

        status = OperationStatus::SUCCESS;
        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::tryProjectNorm(const Vector3D<U>& onto,
                                                                 OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = PromotedValue_t<T, U>;
        using MagType = Magnitude<R>;

        if (hasNaN() | onto.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return fgm::vec3d::zero<MagType>;
        }
        status = OperationStatus::SUCCESS;
        return this->dot(onto) * onto;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector3D<T, U> Vector3D<T>::tryProject(const Vector3D& vec, const Vector3D<U>& onto,
                                                                  OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    {
        return vec.tryProject(onto, status);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::tryProjectNorm(const Vector3D& vec, const Vector3D<U>& onto,
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
    constexpr PromotedFloatVector3D<T, U> Vector3D<T>::reject(const Vector3D<U>& from) const noexcept
        requires StrictArithmetic<T>
    {
        return static_cast<PromotedFloatVector3D<T, U>>(*this) - this->project(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::rejectNorm(const Vector3D<U>& from) const noexcept
        requires StrictArithmetic<T>
    {
        return *this - this->projectNorm(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector3D<T, U> Vector3D<T>::reject(const Vector3D& vector, const Vector3D<U>& from) noexcept
        requires StrictArithmetic<T>
    {
        return vector.reject(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::rejectNorm(const Vector3D& vector, const Vector3D<U>& from) noexcept
        requires StrictArithmetic<T>
    {
        return vector.rejectNorm(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector3D<T, U> Vector3D<T>::safeReject(const Vector3D<U>& from) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            return fgm::vec3d::zero<Magnitude<PromotedValue_t<T, U>>>;
        }

        return static_cast<PromotedFloatVector3D<T, U>>(*this) - safeProject(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::safeRejectNorm(const Vector3D<U>& from) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            return fgm::vec3d::zero<PromotedValue_t<T, U>>;
        }

        return *this - safeProjectNorm(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector3D<T, U> Vector3D<T>::safeReject(const Vector3D& vec, const Vector3D<U>& from) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeReject(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::safeRejectNorm(const Vector3D& vec, const Vector3D<U>& from) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeRejectNorm(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector3D<T, U> Vector3D<T>::tryReject(const Vector3D<U>& from,
                                                                 OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return fgm::vec3d::zero<Magnitude<PromotedValue_t<T, U>>>;
        }

        return static_cast<PromotedFloatVector3D<T, U>>(*this) - this->tryProject(from, status);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::tryRejectNorm(const Vector3D<U>& from,
                                                                OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return fgm::vec3d::zero<PromotedValue_t<T, U>>;
        }

        return *this - this->tryProjectNorm(from, status);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedFloatVector3D<T, U> Vector3D<T>::tryReject(const Vector3D& vec, const Vector3D<U>& from,
                                                                 OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    {
        return vec.tryReject(from, status);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector3D<T, U> Vector3D<T>::tryRejectNorm(const Vector3D& vec, const Vector3D<U>& from,
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
    constexpr bool Vector3D<T>::hasInf() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return fgm::isinf(_data[0]) | fgm::isinf(_data[1]) | fgm::isinf(_data[2]);
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    constexpr bool Vector3D<T>::hasInf(const Vector3D& vec) noexcept
    {
        return vec.hasInf();
    }


    template <Arithmetic T>
    constexpr bool Vector3D<T>::hasNaN() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return fgm::isnan(_data[0]) | fgm::isnan(_data[1]) | fgm::isnan(_data[2]);
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    constexpr bool Vector3D<T>::hasNaN(const Vector3D& vec) noexcept
    {
        return vec.hasNaN();
    }
} // namespace fgm


#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
