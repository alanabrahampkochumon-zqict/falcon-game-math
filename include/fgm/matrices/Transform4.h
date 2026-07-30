#pragma once
/**
 * @file Transform4.h
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Specialization of @ref Mat4 used for 3D transformations with the inherent assumption that
 *        Row 4 is <0, 0, 0, 1>.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4.h"
#include "fgm/vectors/Point3.h"


namespace fgm
{
    template <StrictArithmetic T>
    struct Transform4: Mat4<T>
    {

        /**
         * @addtogroup FGM_Transform4_Init
         * @{
         */

        /**
         * @brief Initialize a @ref Transform4 instance with uninitialized(garbage) values.
         *
         * @warning The components are left uninitialized (containing garbage data)
         *          to maximize SIMD optimization and maintain triviality.
         *
         * @note Use value-initialization (`{}`) to guarantee a zeroed matrix.
         */
        Transform4() = default;


        /**
         * @brief Initialize a 4D transformation matrix from the passed-in scalar elements.
         *
         * @param[in] m00 The element to insert into row one, column one.
         * @param[in] m01 The element to insert into row one, column two.
         * @param[in] m02 The element to insert into row one, column three.
         * @param[in] m03 The element to insert into row one, column four.
         * @param[in] m10 The element to insert into row two, column one.
         * @param[in] m11 The element to insert into row two, column two.
         * @param[in] m12 The element to insert into row two, column three.
         * @param[in] m13 The element to insert into row two, column four.
         * @param[in] m20 The element to insert into row three, column one.
         * @param[in] m21 The element to insert into row three, column two.
         * @param[in] m22 The element to insert into row three, column three.
         * @param[in] m23 The element to insert into row three, column four.
         *
         */
        [[nodiscard]] constexpr Transform4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22,
                                           T m23) noexcept;


        /**
         * @brief Initialize a 4D transformation matrix from the passed-in axis and a point of origin.
         *
         * @param[in] firstAxis  The 3D-vector to use as the first orthogonal axis.
         * @param[in] secondAxis The 3D-vector to use as the second orthogonal axis.
         * @param[in] thirdAxis  The 3D-vector to use as the third orthogonal axis.
         * @param[in] origin     The origin point.
         */
        [[nodiscard]] constexpr Transform4(const Vec3<T>& firstAxis, const Vec3<T>& secondAxis,
                                           const Vec3<T>& thirdAxis, const Point3<T>& origin) noexcept;

        /** @} */
    };

} // namespace fgm


#include "Transform4.tpp"
