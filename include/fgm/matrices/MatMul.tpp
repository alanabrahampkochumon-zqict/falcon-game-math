#pragma once
/**
 * @file MatMul.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Implementation of functions defined in MatMul.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace fgm
{

    /**************************************
     *                                    *
     *            MATRIX 2x3              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedVec2<T, U> operator*(const Mat2x3<T>& mat, const Vec3<U>& vec) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec2{ R(mat[0].x() * vec.x() + mat[1].x() * vec.y() + mat[2].x() * vec.z()),
                     R(mat[0].y() * vec.x() + mat[1].y() * vec.y() + mat[2].y() * vec.z()) };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat2<T, U> operator*(const Mat2x3<T>& lhs, const Mat3x2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2{ // Row 1
                     R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0)),
                     R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1)),
                     // Row 2
                     R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0)),
                     R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat2x3<T, U> operator*(const Mat2x3<T>& lhs, const Mat3<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2x3{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1)),
                       R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1)),
                       R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat2x4<T, U> operator*(const Mat2x3<T>& lhs, const Mat3x4<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2x4{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1)),
                       R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2)),
                       R(lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3) + lhs(0, 2) * rhs(2, 3)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1)),
                       R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2)),
                       R(lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3) + lhs(1, 2) * rhs(2, 3))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedVec3<T, U> operator*(const Vec2<T>& vec, const Mat2x3<U>& mat) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec3{ R(vec.x() * mat(0, 0) + vec.y() * mat(1, 0)), R(vec.x() * mat(0, 1) + vec.y() * mat(1, 1)),
                     R(vec.x() * mat(0, 2) + vec.y() * mat(1, 2)) };
    }



    /**************************************
     *                                    *
     *            MATRIX 2x4              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedVec2<T, U> operator*(const Mat2x4<T>& mat, const Vec4<U>& vec) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec2{ R(mat[0].x() * vec.x() + mat[1].x() * vec.y() + mat[2].x() * vec.z() + mat[3].x() * vec.w()),
                     R(mat[0].y() * vec.x() + mat[1].y() * vec.y() + mat[2].y() * vec.z() + mat[3].y() * vec.w()) };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat2<T, U> operator*(const Mat2x4<T>& lhs, const Mat4x2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2{ // Row 1
                     R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
                     R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
                     // Row 2
                     R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
                     R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat2x3<T, U> operator*(const Mat2x4<T>& lhs, const Mat4x3<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2x3{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
                       R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2) + lhs(0, 3) * rhs(3, 2)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1)),
                       R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat2x4<T, U> operator*(const Mat2x4<T>& lhs, const Mat4<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2x4{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
                       R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2) + lhs(0, 3) * rhs(3, 2)),
                       R(lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3) + lhs(0, 2) * rhs(2, 3) + lhs(0, 3) * rhs(3, 3)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1)),
                       R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2)),
                       R(lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3) + lhs(1, 2) * rhs(2, 3) + lhs(1, 3) * rhs(3, 3))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedVec4<T, U> operator*(const Vec2<T>& vec, const Mat2x4<U>& mat) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec4{ R(vec.x() * mat(0, 0) + vec.y() * mat(1, 0)), R(vec.x() * mat(0, 1) + vec.y() * mat(1, 1)),
                     R(vec.x() * mat(0, 2) + vec.y() * mat(1, 2)), R(vec.x() * mat(0, 3) + vec.y() * mat(1, 3)) };
    }



    /**************************************
     *                                    *
     *            MATRIX 3x2              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedVec3<T, U> operator*(const Mat3x2<T>& mat, const Vec2<U>& vec) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec3{ R(mat[0].x() * vec.x() + mat[1].x() * vec.y()), R(mat[0].y() * vec.x() + mat[1].y() * vec.y()),
                     R(mat[0].z() * vec.x() + mat[1].z() * vec.y()) };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat3x2<T, U> operator*(const Mat3x2<T>& lhs, const Mat2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3x2{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0)), R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0)), R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)),
            // Row 3
            R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0)), R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat3<T, U> operator*(const Mat3x2<T>& lhs, const Mat2x3<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3{ // Row 1
                     R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0)), R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1)),
                     R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2)),
                     // Row 2
                     R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0)), R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)),
                     R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2)),
                     // Row 3
                     R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0)), R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1)),
                     R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat3x4<T, U> operator*(const Mat3x2<T>& lhs, const Mat2x4<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3x4{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0)), R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1)),
            R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2)), R(lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0)), R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)),
            R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2)), R(lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3)),
            // Row 3
            R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0)), R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1)),
            R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2)), R(lhs(2, 0) * rhs(0, 3) + lhs(2, 1) * rhs(1, 3))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedVec2<T, U> operator*(const Vec3<T>& vec, const Mat3x2<U>& mat) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec2{ R(vec.x() * mat(0, 0) + vec.y() * mat(1, 0) + vec.z() * mat(2, 0)),
                     R(vec.x() * mat(0, 1) + vec.y() * mat(1, 1) + vec.z() * mat(2, 1)) };
    }



    /**************************************
     *                                    *
     *            MATRIX 3x4              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedVec3<T, U> operator*(const Mat3x4<T>& mat, const Vec4<U>& vec) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec3{ R(mat[0].x() * vec.x() + mat[1].x() * vec.y() + mat[2].x() * vec.z() + mat[3].x() * vec.w()),
                     R(mat[0].y() * vec.x() + mat[1].y() * vec.y() + mat[2].y() * vec.z() + mat[3].y() * vec.w()),
                     R(mat[0].z() * vec.x() + mat[1].z() * vec.y() + mat[2].z() * vec.z() + mat[3].z() * vec.w()) };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat3x2<T, U> operator*(const Mat3x4<T>& lhs, const Mat4x2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3x2{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1)),
                       // Row 3
                       R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0) + lhs(2, 3) * rhs(3, 0)),
                       R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1) + lhs(2, 3) * rhs(3, 1))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat3<T, U> operator*(const Mat3x4<T>& lhs, const Mat4x3<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
            R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
            R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2) + lhs(0, 3) * rhs(3, 2)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
            R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1)),
            R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2)),
            // Row 2
            R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0) + lhs(2, 3) * rhs(3, 0)),
            R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1) + lhs(2, 3) * rhs(3, 1)),
            R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2) + lhs(2, 3) * rhs(3, 2)),
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat3x4<T, U> operator*(const Mat3x4<T>& lhs, const Mat4<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3x4{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
                       R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2) + lhs(0, 3) * rhs(3, 2)),
                       R(lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3) + lhs(0, 2) * rhs(2, 3) + lhs(0, 3) * rhs(3, 3)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1)),
                       R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2)),
                       R(lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3) + lhs(1, 2) * rhs(2, 3) + lhs(1, 3) * rhs(3, 3)),
                       // Row 3
                       R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0) + lhs(2, 3) * rhs(3, 0)),
                       R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1) + lhs(2, 3) * rhs(3, 1)),
                       R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2) + lhs(2, 3) * rhs(3, 2)),
                       R(lhs(2, 0) * rhs(0, 3) + lhs(2, 1) * rhs(1, 3) + lhs(2, 2) * rhs(2, 3) + lhs(2, 3) * rhs(3, 3))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedVec4<T, U> operator*(const Vec3<T>& vec, const Mat3x4<U>& mat) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec4{ R(vec.x() * mat(0, 0) + vec.y() * mat(1, 0) + vec.z() * mat(2, 0)),
                     R(vec.x() * mat(0, 1) + vec.y() * mat(1, 1) + vec.z() * mat(2, 1)),
                     R(vec.x() * mat(0, 2) + vec.y() * mat(1, 2) + vec.z() * mat(2, 2)),
                     R(vec.x() * mat(0, 3) + vec.y() * mat(1, 3) + vec.z() * mat(2, 3)) };
    }



    /**************************************
     *                                    *
     *            MATRIX 4x2              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedVec4<T, U> operator*(const Mat4x2<T>& mat, const Vec2<U>& vec) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec4{ R(mat[0].x() * vec.x() + mat[1].x() * vec.y()), R(mat[0].y() * vec.x() + mat[1].y() * vec.y()),
                     R(mat[0].z() * vec.x() + mat[1].z() * vec.y()), R(mat[0].w() * vec.x() + mat[1].w() * vec.y()) };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FGM_INLINE constexpr PromotedMat4x2<T, U> operator*(const Mat4x2<T>& lhs, const Mat2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat4x2{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0)), R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0)), R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)),
            // Row 3
            R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0)), R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1)),
            // Row 4
            R(lhs(3, 0) * rhs(0, 0) + lhs(3, 1) * rhs(1, 0)), R(lhs(3, 0) * rhs(0, 1) + lhs(3, 1) * rhs(1, 1))
        };
    }

} // namespace fgm
