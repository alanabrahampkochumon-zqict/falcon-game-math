#pragma once
/**
 * @file Point3.h
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief 3D point representation with a implicit w values of 1 <x, y, z, 1>.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vec3.h"

namespace fgm
{
    template <StrictArithmetic T>
    struct Point3: Vec3<T>
    {

        /**
         * @addtogroup FGM_Point3_Init
         * @{
         */

        /// @brief @ref fgm::Vec3 CTORs
        using Vec3<T>::Vec3;

        /** @} */
    };


    /** @brief Template deduction guide for Point3 */
    template <typename T>
        requires StrictArithmetic<T>
    Point3(T, T) -> Point3<T>;

} // namespace fgm


#include "Point3.tpp"
