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


    template <StrictArithmetic T, StrictArithmetic S>
        requires StrictSignedness<T, S>
    FGM_INLINE constexpr PromotedQuaternion<T, S> operator*(S scalar, const Quaternion<T>& quat) noexcept
    { return quat * scalar; }



} // namespace fgm
