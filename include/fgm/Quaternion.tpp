#pragma once
#include "common/Types.h"
/**
 * @file Quaternion.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 1, 2026
 *
 * @brief Implementation of member function declared in Quaternion.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace fgm
{

    /**************************************
     *                                    *
     *            INITIALIZERS            *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FGM_INLINE constexpr Quaternion<T>::Quaternion(const T x, const T y, const T z, const T w) noexcept
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
        _data[3] = w;
    }


    template <Arithmetic T>
    FGM_INLINE constexpr Quaternion<T>::Quaternion(const Vec3<T>& complex, T real) noexcept
    {
        _data[0] = complex.x();
        _data[1] = complex.y();
        _data[2] = complex.z();
        _data[3] = real;
    }


    template <Arithmetic T>
    FGM_INLINE constexpr Quaternion<T>::Quaternion(T real, const Vec3<T>& complex) noexcept
    {
        _data[0] = complex.x();
        _data[1] = complex.y();
        _data[2] = complex.z();
        _data[3] = real;
    }


    template <Arithmetic T>
    template <Arithmetic U>
    FGM_INLINE constexpr Quaternion<T>::Quaternion(const Quaternion<U>& other) noexcept
    {
        this->x() = static_cast<T>(other.x());
        this->y() = static_cast<T>(other.y());
        this->z() = static_cast<T>(other.z());
        this->w() = static_cast<T>(other.w());
    }



    /**************************************
     *                                    *
     *             ACCESSORS              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FGM_INLINE constexpr T Quaternion<T>::x() const noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T& Quaternion<T>::x() noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T Quaternion<T>::y() const noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T& Quaternion<T>::y() noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T Quaternion<T>::z() const noexcept
    { return _data[2]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T& Quaternion<T>::z() noexcept
    { return _data[2]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T Quaternion<T>::w() const noexcept
    { return _data[3]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T& Quaternion<T>::w() noexcept
    { return _data[3]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T Quaternion<T>::i() const noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T& Quaternion<T>::i() noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T Quaternion<T>::j() const noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T& Quaternion<T>::j() noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T Quaternion<T>::k() const noexcept
    { return _data[2]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T& Quaternion<T>::k() noexcept
    { return _data[2]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T Quaternion<T>::s() const noexcept
    { return _data[3]; }


    template <Arithmetic T>
    FGM_INLINE constexpr T& Quaternion<T>::s() noexcept
    { return _data[3]; }


    template <Arithmetic T>
    FGM_INLINE constexpr Vec3<T> Quaternion<T>::getVectorPart() const noexcept
    { return Vec3<T>{ _data[0], _data[1], _data[2] }; }


    template <Arithmetic T>
    FGM_INLINE constexpr T Quaternion<T>::getScalarPart() const noexcept
    { return _data[3]; }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedQuaternion<T, U> Quaternion<T>::operator+(const Quaternion<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Quaternion<R>{ R(_data[0] + rhs.i()), R(_data[1] + rhs.j()), R(_data[2] + rhs.k()),
                              R(_data[3] + rhs.s()) };
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] = static_cast<T>(_data[0] + rhs.i());
        _data[1] = static_cast<T>(_data[1] + rhs.j());
        _data[2] = static_cast<T>(_data[2] + rhs.k());
        _data[3] = static_cast<T>(_data[3] + rhs.s());

        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedQuaternion<T, U> Quaternion<T>::operator-(const Quaternion<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Quaternion<R>{ R(_data[0] - rhs.i()), R(_data[1] - rhs.j()), R(_data[2] - rhs.k()),
                              R(_data[3] - rhs.s()) };
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] = static_cast<T>(_data[0] - rhs.i());
        _data[1] = static_cast<T>(_data[1] - rhs.j());
        _data[2] = static_cast<T>(_data[2] - rhs.k());
        _data[3] = static_cast<T>(_data[3] - rhs.s());

        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
        requires StrictSignedness<T, S>
    FGM_INLINE constexpr PromotedQuaternion<T, S> Quaternion<T>::operator*(S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        return Quaternion<R>{ R(_data[0] * scalar), R(_data[1] * scalar), R(_data[2] * scalar), R(_data[3] * scalar) };
    }


    template <StrictArithmetic T, StrictArithmetic S>
        requires StrictSignedness<T, S>
    FGM_INLINE constexpr PromotedQuaternion<T, S> operator*(S scalar, const Quaternion<T>& quat) noexcept
    { return quat * scalar; }


    template <Arithmetic T>
    template <StrictArithmetic S>
        requires StrictSignedness<T, S>
    FGM_INLINE constexpr Quaternion<T>& Quaternion<T>::operator*=(S scalar) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] = static_cast<T>(_data[0] * scalar);
        _data[1] = static_cast<T>(_data[1] * scalar);
        _data[2] = static_cast<T>(_data[2] * scalar);
        _data[3] = static_cast<T>(_data[3] * scalar);

        return *this;
    }



    /**************************************
     *         QUATERNION ALGEBRA         *
     **************************************/

    template <Arithmetic T>
    FGM_INLINE constexpr Quaternion<T> Quaternion<T>::conjugate() const noexcept
        requires SignedStrictArithmetic<T>
    { return Quaternion{ T(-_data[0]), T(-_data[1]), T(-_data[2]), T(_data[3]) }; }


    template <Arithmetic T>
    FGM_INLINE constexpr Quaternion<T> Quaternion<T>::conjugate(const Quaternion& quat) noexcept
        requires SignedStrictArithmetic<T>
    { return quat.conjugate(); }


    template <Arithmetic T>
    FGM_INLINE constexpr Magnitude<T> Quaternion<T>::mag() const noexcept
        requires StrictArithmetic<T>
    {
        // TODO: Update to use fgm::sqrt
        return Magnitude<T>(std::sqrt(this->dot(*this)));
    }


    template <Arithmetic T>
    FGM_INLINE constexpr Magnitude<T> Quaternion<T>::mag(const Quaternion& quat) noexcept
        requires StrictArithmetic<T>
    { return quat.mag(); }



    /**************************************
     *           VECTOR ALGEBRA           *
     **************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedQuaternion<T, U> Quaternion<T>::operator*(const Quaternion<U>& other) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Quaternion<R>{
            R(this->w() * other.x() + this->x() * other.w() + this->y() * other.z() - this->z() * other.y()),
            R(this->w() * other.y() - this->x() * other.z() + this->y() * other.w() + this->z() * other.x()),
            R(this->w() * other.z() + this->x() * other.y() - this->y() * other.x() + this->z() * other.w()),
            R(this->w() * other.w() - this->x() * other.x() - this->y() * other.y() - this->z() * other.z())
        };
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<U>& other) noexcept
        requires StrictArithmetic<T>
    {

        // We need an intermediate since every quaternion components participate
        // in determining each component of result.
        auto intermediate = (*this) * other;
        *this             = static_cast<Quaternion<T>>(intermediate);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedValue_t<T, U> Quaternion<T>::dot(const Quaternion<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return R(x() * rhs.x() + y() * rhs.y() + z() * rhs.z() + w() * rhs.w());
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedValue_t<T, U> Quaternion<T>::dot(const Quaternion& lhs,
                                                                  const Quaternion<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.dot(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic S>
        requires StrictSignedness<T, S>
    FGM_INLINE constexpr PromotedQuaternion<T, S> Quaternion<T>::operator/(S scalar) const noexcept
        requires StrictArithmetic<T>
    {

        using R = PromotedValue_t<T, S>;


        if constexpr (std::is_floating_point_v<R>)
        {
            FGM_ASSERT_MSG(fgm::abs(scalar) >= fgm::Config::EPSILON<R>, fgm::messages::assertion::QUAT_DIV_BY_ZERO);
            FGM_ASSERT_MSG(!fgm::isnan(scalar) && !this->hasNaN(), fgm::messages::assertion::QUAT_HAS_NAN);

            R factor = R(1) / static_cast<R>(scalar);
            return Quaternion<R>(_data[0] * factor, _data[1] * factor, _data[2] * factor, _data[3] * factor);
        }
        else
        {
            FGM_ASSERT_MSG(fgm::abs(scalar) != R(0), fgm::messages::assertion::QUAT_DIV_BY_ZERO);
            R tScalar = static_cast<R>(scalar);
            return Quaternion<R>(_data[0] / tScalar, _data[1] / tScalar, _data[2] / tScalar, _data[3] / tScalar);
        }
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
        requires StrictSignedness<T, S>
    FGM_INLINE constexpr Quaternion<T>& Quaternion<T>::operator/=(S scalar) noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            FGM_ASSERT_MSG(fgm::abs(scalar) > fgm::Config::EPSILON<S>, fgm::messages::assertion::QUAT_DIV_BY_ZERO);
            FGM_ASSERT_MSG(!fgm::isnan(scalar) && !this->hasNaN(), fgm::messages::assertion::QUAT_HAS_NAN);

            R factor = R(1) / static_cast<R>(scalar);

            _data[0] = static_cast<T>(factor * _data[0]);
            _data[1] = static_cast<T>(factor * _data[1]);
            _data[2] = static_cast<T>(factor * _data[2]);
            _data[3] = static_cast<T>(factor * _data[3]);
        }
        else
        {
            FGM_ASSERT_MSG(fgm::abs(scalar) != R(0), fgm::messages::assertion::QUAT_DIV_BY_ZERO);
            _data[0] = static_cast<T>(_data[0] / static_cast<R>(scalar));
            _data[1] = static_cast<T>(_data[1] / static_cast<R>(scalar));
            _data[2] = static_cast<T>(_data[2] / static_cast<R>(scalar));
            _data[3] = static_cast<T>(_data[3] / static_cast<R>(scalar));
        }

        return *this;
    }


    template <Arithmetic T>
    FGM_INLINE constexpr Quaternion<T> Quaternion<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    { return Quaternion{ T(-_data[0]), T(-_data[1]), T(-_data[2]), T(-_data[3]) }; }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr bool Quaternion<T>::allEq(const Quaternion<U>& rhs, double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return x() == rhs.x() && y() == rhs.y() && z() == rhs.z() && w() == rhs.w();
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
            return (x() == rhs.x() || fgm::abs(x() - rhs.x()) <= epsilon) &&
                   (y() == rhs.y() || fgm::abs(y() - rhs.y()) <= epsilon) &&
                   (z() == rhs.z() || fgm::abs(z() - rhs.z()) <= epsilon) &&
                   (w() == rhs.w() || fgm::abs(w() - rhs.w()) <= epsilon);
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr bool Quaternion<T>::allEq(const Quaternion& lhs, const Quaternion<U>& rhs,
                                                   double epsilon) noexcept
    { return lhs.allEq(rhs, epsilon); }



    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FGM_INLINE constexpr bool Quaternion<T>::hasInf() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return fgm::isinf(_data[0]) || fgm::isinf(_data[1]) || fgm::isinf(_data[2]) || fgm::isinf(_data[3]);
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    FGM_INLINE constexpr bool Quaternion<T>::hasInf(const Quaternion& quat) noexcept
    { return quat.hasInf(); }


    template <Arithmetic T>
    FGM_INLINE constexpr bool Quaternion<T>::hasNaN() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return fgm::isnan(_data[0]) || fgm::isnan(_data[1]) || fgm::isnan(_data[2]) || fgm::isnan(_data[3]);
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    FGM_INLINE constexpr bool Quaternion<T>::hasNaN(const Quaternion& quat) noexcept
    { return quat.hasNaN(); }


} // namespace fgm
