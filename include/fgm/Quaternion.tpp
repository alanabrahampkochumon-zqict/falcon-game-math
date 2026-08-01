#pragma once
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

} // namespace fgm
