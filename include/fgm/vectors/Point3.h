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
#include "fgm/common/Types.h"


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



        /**
         * @addtogroup FGM_Point3_Arithmetic
         * @{
         */

        /**
         * @brief Compute the sum of this point with a vector(direction).
         *
         * @note Promotes the result to the wider type using @ref PromotedPoint3<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vector The vector to add.
         *
         * @return A new @ref Point3 representing a translated point.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedPoint3<T, U> operator+(const Vec3<U>& vector) const noexcept;


        /**
         * @brief Compute the sum of this point with a vector(direction) in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vector The vector to add.
         *
         * @return A reference to the current Point3 instance (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr Point3& operator+=(const Vec3<U>& vector) noexcept;

        /** @} */
    };



    /** @brief Template deduction guide for Point3 */
    template <typename T>
        requires StrictArithmetic<T>
    Point3(T, T) -> Point3<T>;

} // namespace fgm


#include "Point3.tpp"
