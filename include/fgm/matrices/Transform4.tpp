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

} // namespace fgm
