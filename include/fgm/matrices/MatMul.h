#pragma once
/**
 * @file MatMul.h
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Defines all uneven matrix multiplication operations.
 *
 * @details Matrix multiplications that are dependent on other matrices like 2x3 with 3x2 matrix are grouped into
 *          uneven multiplication operations.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "../common/Types.h"
#include "../vectors/Vec2.h"
#include "../vectors/Vec3.h"
#include "../vectors/Vec4.h"
#include "Mat2.h"
#include "Mat2x3.h"
#include "Mat2x4.h"
#include "Mat3.h"
#include "Mat3x2.h"
#include "Mat3x4.h"
#include "Mat4.h"
#include "Mat4x2.h"
#include "Mat4x3.h"



/// TODO: Not implemented or tested
// TODO: Add Groups
// TODO: Add Implementation
// Implementations
// 3x3 * 3x2
// 3x3 * 3x4
//
// 4x4 * 4x2
// 4x4 * 4x4
//
// 2x2 * 2x3
// 2x2 * 2x4
//

//       3x2 * 2x1 => 3x1
//       3x2 * 2x2 => 3x2
//       3x2 * 2x3 => 3x3
//       3x2 * 2x4 => 3x4
// 1x3 * 3x2       => 1x2

//       3x4 * 4x1 => 3x1
//       3x4 * 4x2 => 3x2
//       3x4 * 4x3 => 3x3
//       3x4 * 4x4 => 3x4
// 1x3 * 3x4       => 1x4

//       4x2 * 2x1 => 4x1
//       4x2 * 2x2 => 4x2
//       4x2 * 2x3 => 4x3
//       4x2 * 2x4 => 4x4
// 1x4 * 4x2       => 1x2

//       4x3 * 3x1 => 4x1
//       4x3 * 3x2 => 4x2
//       4x3 * 3x3 => 4x3
//       4x3 * 3x4 => 4x4
// 1x4 * 4x3       => 1x3

namespace fgm
{

    /**
     * @addtogroup FGM_Mat2x3_Arithmetic
     * @{
     */

    /**
     * @brief Multiply a 2x3 matrix with a 3D column vector.
     *
     * @note Promotes the result to the wider type using @ref PromotedVector2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] mat The matrix to multiply.
     * @param[in] vec The column vector to multiply with.
     *
     * @return A new 2D column vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedVec2<T, U> operator*(const Mat2x3<T>& mat, const Vec3<U>& vec) noexcept;


    /**
     * @brief Multiply a 2x3 matrix with a 3x2 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2x3 matrix on the left hand side.
     * @param[in] rhs The 3x2 matrix on the right hand side.
     *
     * @return A new 2D matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2<T, U> operator*(const Mat2x3<T>& lhs, const Mat3x2<U>& rhs) noexcept;


    /**
     * @brief Multiply a 2x3 matrix with a 3x3 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2x3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2x3 matrix on the left hand side.
     * @param[in] rhs The 3x3 matrix on the right hand side.
     *
     * @return A new 2x3 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2x3<T, U> operator*(const Mat2x3<T>& lhs, const Mat3<U>& rhs) noexcept;


    /**
     * @brief Multiply a 2x3 matrix with a 3x4 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2x4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2x3 matrix on the left hand side.
     * @param[in] rhs The 3x4 matrix on the right hand side.
     *
     * @return A new 2x4 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2x4<T, U> operator*(const Mat2x3<T>& lhs, const Mat3x4<U>& rhs) noexcept;


    /**
     * @brief Multiply a 2D row vector with a 2x3 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedVec3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec The row vector to multiply.
     * @param[in] mat The matrix to multiply with.
     *
     * @return A new 3D row vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedVec3<T, U> operator*(const Vec2<T>& vec, const Mat2x3<U>& mat) noexcept;

    /** @} */



    /**
     * @addtogroup FGM_Mat2x4_Arithmetic
     * @{
     */

    /**
     * @brief Multiply a 2x4 matrix with a 4D column vector.
     *
     * @note Promotes the result to the wider type using @ref PromotedVector2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] mat The matrix to multiply.
     * @param[in] vec The column vector to multiply with.
     *
     * @return A new 2D column vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedVec2<T, U> operator*(const Mat2x4<T>& mat, const Vec4<U>& vec) noexcept;


    /**
     * @brief Multiply a 2x4 matrix with a 4x2 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2x4 matrix on the left hand side.
     * @param[in] rhs The 4x2 matrix on the right hand side.
     *
     * @return A new 2D matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2<T, U> operator*(const Mat2x4<T>& lhs, const Mat4x2<U>& rhs) noexcept;


    /**
     * @brief Multiply a 2x4 matrix with a 4x3 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2x3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2x4 matrix on the left hand side.
     * @param[in] rhs The 4x3 matrix on the right hand side.
     *
     * @return A new 2x3 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2x3<T, U> operator*(const Mat2x4<T>& lhs, const Mat4x3<U>& rhs) noexcept;


    /**
     * @brief Multiply a 2x4 matrix with a 4x4 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2x4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2x4 matrix on the left hand side.
     * @param[in] rhs The 4x4 matrix on the right hand side.
     *
     * @return A new 2x4 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2x4<T, U> operator*(const Mat2x4<T>& lhs, const Mat4<U>& rhs) noexcept;


    /**
     * @brief Multiply a 2D row vector with a 2x4 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedVec4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec The row vector to multiply.
     * @param[in] mat The matrix to multiply with.
     *
     * @return A new 4D row vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedVec4<T, U> operator*(const Vec2<T>& vec, const Mat2x4<U>& mat) noexcept;

    /** @} */



    /**
     * @addtogroup FGM_Mat3x2_Arithmetic
     * @{
     */

    /** @} */



    /**
     * @addtogroup FGM_Mat3x4_Arithmetic
     * @{
     */

    /** @} */



    /**
     * @addtogroup FGM_Mat4x2_Arithmetic
     * @{
     */

    /** @} */



    /**
     * @addtogroup FGM_Mat4x3_Arithmetic
     * @{
     */

    /** @} */

} // namespace fgm


#include "MatMul.tpp"
