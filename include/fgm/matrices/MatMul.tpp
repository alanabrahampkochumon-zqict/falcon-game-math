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

//     template <StrictArithmetic T, StrictArithmetic S>
//     constexpr PromotedMatrix2x3<T, S> operator*(const S scalar, const Matrix2x3<T>& matrix) noexcept
//     { return matrix * scalar; }
//
//
//     template <Arithmetic T>
//     template <StrictArithmetic U>
//         requires StrictSignedness<T, U>
//     constexpr PromotedVector2<T, U> Matrix2x3<T>::operator*(const Vector3<U>& vec) const noexcept
//         requires StrictArithmetic<T>
//     {
//         using R = PromotedValue_t<T, U>;
// #if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
//         // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
//         if constexpr (std::is_floating_point_v<R>)
//         {
//             if (!std::is_constant_evaluated())
//             {
//                 return Vector2<R>(std::fma(static_cast<R>(_data[0][0]), static_cast<R>(vec[0]),
//                                            std::fma(static_cast<R>(_data[1][0]), static_cast<R>(vec[1]),
//                                                     static_cast<R>(_data[2][0]) * static_cast<R>(vec[2]))),
//                                   std::fma(static_cast<R>(_data[0][1]), static_cast<R>(vec[0]),
//                                            std::fma(static_cast<R>(_data[1][1]), static_cast<R>(vec[1]),
//                                                     static_cast<R>(_data[2][1]) * static_cast<R>(vec[2]))));
//             }
//         }
// #endif
//
//         R x = static_cast<R>(_data[0][0]) * static_cast<R>(vec[0]) +
//             static_cast<R>(_data[1][0]) * static_cast<R>(vec[1]) + static_cast<R>(_data[2][0]) * static_cast<R>(vec[2]);
//         R y = static_cast<R>(_data[0][1]) * static_cast<R>(vec[0]) +
//             static_cast<R>(_data[1][1]) * static_cast<R>(vec[1]) + static_cast<R>(_data[2][1]) * static_cast<R>(vec[2]);
//
//         return Vector2<R>(x, y);
//     }
//
//
//     template <StrictArithmetic T, StrictArithmetic U>
//         requires StrictSignedness<T, U>
//     constexpr PromotedVector2<T, U> operator*(const Vector2<T>& vec, const Matrix2x3<U>& matrix) noexcept
//     {
//         using R = PromotedValue_t<T, U>;
// #if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
//         // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
//         if constexpr (std::is_floating_point_v<R>)
//         {
//             if (!std::is_constant_evaluated())
//             {
//                 return Vector2<R>(std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 0)),
//                                            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0))),
//                                   std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 1)),
//                                            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1))));
//             }
//         }
//
// #endif
//         R x = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 0)) +
//             static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0));
//         R y = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 1)) +
//             static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1));
//
//         return Vector2<R>(x, y);
//     }
//
//     template <StrictArithmetic T, StrictArithmetic U>
//         requires StrictSignedness<T, U>
//     constexpr Vector2<T>& operator*=(Vector2<T>& vec, const Matrix2x3<U>& matrix) noexcept
//     {
//         using R = PromotedValue_t<T, U>;
// #if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
//         // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
//         if constexpr (std::is_floating_point_v<R>)
//         {
//             if (!std::is_constant_evaluated())
//             {
//                 R x = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 0)),
//                                static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0)));
//                 R y = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 1)),
//                                static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1)));
//
//                 vec.x() = static_cast<T>(x);
//                 vec.y() = static_cast<T>(y);
//
//                 return vec;
//             }
//         }
// #endif
//         R x = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 0)) +
//             static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0));
//         R y = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 1)) +
//             static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1));
//
//         vec.x() = static_cast<T>(x);
//         vec.y() = static_cast<T>(y);
//
//         return vec;
//     }
//
//
//     template <Arithmetic T>
//     template <StrictArithmetic U>
//         requires StrictSignedness<T, U>
//     constexpr PromotedMatrix2x3<T, U> Matrix2x3<T>::operator*(const Matrix3<U>& rhs) const noexcept
//         requires StrictArithmetic<T>
//     {
//         const auto m00 = _data[0][0] * rhs(0, 0) + _data[0][1] * rhs(0, 1) + _data[0][2] * rhs(0, 2);
//         const auto m01 = _data[0][0] * rhs(0, 0) + _data[0][1] * rhs(0, 1) + _data[0][2] * rhs(0, 2);
//         const auto m02 = _data[0][0] * rhs(0, 0) + _data[0][1] * rhs(0, 1) + _data[0][2] * rhs(0, 2);
//         const auto m10 = _data[0][0] * rhs(0, 0) + _data[0][1] * rhs(0, 1) + _data[0][2] * rhs(0, 2);
//         const auto m11 = _data[0][0] * rhs(0, 0) + _data[0][1] * rhs(0, 1) + _data[0][2] * rhs(0, 2);
//         const auto m12 = _data[0][0] * rhs(0, 0) + _data[0][1] * rhs(0, 1) + _data[0][2] * rhs(0, 2);
//         return Matrix2x3{m00, m01, m02, m10, m11, m12};
//     }
//
//
//     template <StrictArithmetic T, StrictArithmetic U>
//         requires StrictSignedness<T, U>
//     constexpr Vector3<T> operator*(Vector2<T>& vec, const Matrix2x3<U>& matrix) noexcept
//     {}
//
//     template <StrictArithmetic T, StrictArithmetic U>
//         requires StrictSignedness<T, U>
//     constexpr PromotedMatrix2x3<T, U> operator*(const Matrix2<T>& matrixA, const Matrix2x3<U>& matrixB) noexcept
//     {}
}