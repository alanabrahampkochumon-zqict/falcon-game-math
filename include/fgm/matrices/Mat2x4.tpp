#pragma once
/**
 * @file Mat2x4.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief @ref Mat2x4 template implementation.
 * @details This file contains the definitions of the template members declared in Mat2x4.h
 *
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "fgm/common/Wrappers.h"

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
    constexpr Mat2x4<T>::Mat2x4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13) noexcept
        : _data{ Vec2<T>(m00, m10), Vec2<T>(m01, m11), Vec2<T>(m02, m12), Vec2<T>(m03, m13) }
    {}


    template <Arithmetic T>
    constexpr Mat2x4<T>::Mat2x4(const Vec2<T>& col0, const Vec2<T>& col1, const Vec2<T>& col2, const Vec2<T>& col3) noexcept
        : _data{ col0, col1, col2, col3 }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr Mat2x4<T>::Mat2x4(const Mat2x4<U>& other) noexcept
    {
        (*this)(0, 0) = static_cast<T>(other(0, 0));
        (*this)(0, 1) = static_cast<T>(other(0, 1));
        (*this)(0, 2) = static_cast<T>(other(0, 2));
        (*this)(0, 3) = static_cast<T>(other(0, 3));
        (*this)(1, 0) = static_cast<T>(other(1, 0));
        (*this)(1, 1) = static_cast<T>(other(1, 1));
        (*this)(1, 2) = static_cast<T>(other(1, 2));
        (*this)(1, 3) = static_cast<T>(other(1, 3));
    }



    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Vec2<T>& Mat2x4<T>::operator[](const std::size_t col) noexcept
    {
        FGM_ASSERT_MSG(col < COLUMNS, fgm::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col];
    }

    template <Arithmetic T>
    constexpr const Vec2<T>& Mat2x4<T>::operator[](const std::size_t col) const noexcept
    {
        FGM_ASSERT_MSG(col < COLUMNS, fgm::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col];
    }

    template <Arithmetic T>
    constexpr T& Mat2x4<T>::operator()(const std::size_t row, const std::size_t col) noexcept
    {
        FGM_ASSERT_MSG(col < COLUMNS && row < ROWS, fgm::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col][row];
    }

    template <Arithmetic T>
    constexpr const T& Mat2x4<T>::operator()(const std::size_t row, const std::size_t col) const noexcept
    {
        FGM_ASSERT_MSG(col < COLUMNS && row < ROWS, fgm::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col][row];
    }


    /***************************************
     *                                     *
     *             EQUALITY                *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Mat2x4<T>::allEq(const Mat2x4<U>& rhs, const double epsilon) const noexcept
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
        return _data[0].allEq(rhs[0], epsilon) && _data[1].allEq(rhs[1], epsilon) && _data[2].allEq(rhs[2], epsilon) && _data[3].allEq(rhs[3], epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Mat2x4<T>::allEq(const Mat2x4& lhs, const Mat2x4<U>& rhs, const double epsilon) noexcept
    { return lhs.allEq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Mat2x4<T>::anyNeq(const Mat2x4<U>& rhs, const double epsilon) const noexcept
    {
        // MSVC's constexpr evaluator incorrectly yields true for NaN relational comparisons.
        // To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
        // if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
#ifdef _MSC_VER
        if (std::is_constant_evaluated())
        {
            if (hasNaN() || rhs.hasNaN())
            {
                return true;
            }
        }
#endif
        return _data[0].anyNeq(rhs[0], epsilon) || _data[1].anyNeq(rhs[1], epsilon) || _data[2].anyNeq(rhs[2], epsilon) || _data[3].anyNeq(rhs[3], epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Mat2x4<T>::anyNeq(const Mat2x4& lhs, const Mat2x4<U>& rhs, const double epsilon) noexcept
    { return lhs.anyNeq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Mat2x4<T>::operator==(const Mat2x4<U>& rhs) const noexcept
    { return allEq(rhs); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Mat2x4<T>::operator!=(const Mat2x4<U>& rhs) const noexcept
    { return anyNeq(rhs); }



    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr bool Mat2x4<T>::hasInf() const noexcept
    { return _data[0].hasInf() || _data[1].hasInf() || _data[2].hasInf()|| _data[3].hasInf(); }


    template <Arithmetic T>
    constexpr bool Mat2x4<T>::hasInf(const Mat2x4& matrix) noexcept
    { return matrix.hasInf(); }


    template <Arithmetic T>
    constexpr bool Mat2x4<T>::hasNaN() const noexcept
    { return _data[0].hasNaN() || _data[1].hasNaN() || _data[2].hasNaN() || _data[3].hasNaN(); }


    template <Arithmetic T>
    constexpr bool Mat2x4<T>::hasNaN(const Mat2x4& matrix) noexcept
    { return matrix.hasNaN(); }


} // namespace fgm


#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
