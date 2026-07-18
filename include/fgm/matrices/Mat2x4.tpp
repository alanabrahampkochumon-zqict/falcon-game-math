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





} // namespace fgm


#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
