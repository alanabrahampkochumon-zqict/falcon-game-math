#pragma once
/**
 * @file Transform4.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Implementation of member functions declared in Transform4.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "fgm/common/PreprocessorDefinitions.h"


namespace fgm
{

    template <StrictArithmetic T>
    FGM_INLINE constexpr Transform4<T>::Transform4(const T m00, const T m01, const T m02, const T m03, const T m10,
                                                   const T m11, const T m12, const T m13, const T m20, const T m21,
                                                   const T m22, const T m23) noexcept
        : Mat4<T>{ m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, T(0), T(0), T(0), T(1) }
    {}


    template <StrictArithmetic T>
    FGM_INLINE constexpr Transform4<T>::Transform4(const Vec3<T>& firstAxis, const Vec3<T>& secondAxis,
                                                   const Vec3<T>& thirdAxis, const Point3<T>& origin) noexcept
        : Mat4<T>{ firstAxis.x(), secondAxis.x(), thirdAxis.x(), origin.x(),
                   firstAxis.y(), secondAxis.y(), thirdAxis.y(), origin.y(),
                   firstAxis.z(), secondAxis.z(), thirdAxis.z(), origin.z(),
                   T(0),          T(0),           T(0),          T(1) }
    {}


    template <StrictArithmetic T>
    template <StrictArithmetic U>
    FGM_INLINE constexpr Transform4<T>::Transform4(const Transform4<U>& other) noexcept
    {
        (*this)(0, 0) = static_cast<T>(other(0, 0));
        (*this)(0, 1) = static_cast<T>(other(0, 1));
        (*this)(0, 2) = static_cast<T>(other(0, 2));
        (*this)(0, 3) = static_cast<T>(other(0, 3));
        (*this)(1, 0) = static_cast<T>(other(1, 0));
        (*this)(1, 1) = static_cast<T>(other(1, 1));
        (*this)(1, 2) = static_cast<T>(other(1, 2));
        (*this)(1, 3) = static_cast<T>(other(1, 3));
        (*this)(2, 0) = static_cast<T>(other(2, 0));
        (*this)(2, 1) = static_cast<T>(other(2, 1));
        (*this)(2, 2) = static_cast<T>(other(2, 2));
        (*this)(2, 3) = static_cast<T>(other(2, 3));
    }



    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <StrictArithmetic T>
    FGM_INLINE constexpr Vec3<T>& Transform4<T>::operator[](std::size_t col) noexcept
    {
        FGM_ASSERT_MSG(col < COLUMNS, fgm::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return *reinterpret_cast<Vec3<T>*>(&(this->_data[col]));
    }


    template <StrictArithmetic T>
    FGM_INLINE constexpr const auto Transform4<T>::operator[](std::size_t col) const noexcept
    {
        FGM_ASSERT_MSG(col < COLUMNS, fgm::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        if (std::is_constant_evaluated())
        {
            return this->_data[col].template swizzle<axis::X, axis::Y, axis::Z>();
        }
        else
        {
            return *reinterpret_cast<const Vec3<T>*>(&(this->_data[col]));
        }
    }


    template <StrictArithmetic T>
    FGM_INLINE constexpr T& Transform4<T>::operator()(std::size_t row, std::size_t col) noexcept
    {
        FGM_ASSERT_MSG(col < COLUMNS && row < ROWS, fgm::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return this->_data[col][row];
    }


    template <StrictArithmetic T>
    FGM_INLINE constexpr const T& Transform4<T>::operator()(std::size_t row, std::size_t col) const noexcept
    {
        FGM_ASSERT_MSG(col < COLUMNS && row < ROWS, fgm::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return this->_data[col][row];
    }


    /**************************************
     *                                    *
     *           MATRIX ALGEBRA           *
     *                                    *
     **************************************/

    template <StrictArithmetic T>
    FGM_INLINE constexpr Transform4<Magnitude<T>> Transform4<T>::inverse() const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        auto a = static_cast<Vec3<R>>((*this)[0]);
        auto b = static_cast<Vec3<R>>((*this)[1]);
        auto c = static_cast<Vec3<R>>((*this)[2]);
        auto d = static_cast<Vec3<R>>((*this)[3]);

        auto s = a.cross(b);
        auto t = c.cross(d);

        FGM_ASSERT_MSG(fgm::abs(s.dot(c)) > Config::EPSILON<R>, messages::assertion::MAT_INV_ZERO_DETERMINANT);

        R invDet = R(1) / s.dot(c);
        s *= invDet;
        t *= invDet;
        auto v = c * invDet;

        auto r0 = b.cross(v);
        auto r1 = v.cross(a);

        return Transform4<R>{ r0.x(), r0.y(),   r0.z(), -b.dot(t), r1.x(), r1.y(),
                              r1.z(), a.dot(t), s.x(),  s.y(),     s.z(),  -d.dot(s) };
    }


    template <StrictArithmetic T>
    FGM_INLINE constexpr Transform4<Magnitude<T>> Transform4<T>::inverse(const Transform4& transform) noexcept
        requires SignedStrictArithmetic<T>
    { return transform.inverse(); }

} // namespace fgm
