#pragma once
/**
 * @file Matrix2D.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: January 30, 2026
 *
 * @brief @ref Matrix2D template implementation.
 * @details This file contains the definitions of the template members declared in Matrix2D.h
 *
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "Matrix2D.h"
#include "common/Wrappers.tpp"

#include <cassert>
#include <type_traits>
#include <valarray>

namespace fgm
{

    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Matrix2D<T>::Matrix2D() noexcept: _data{ Vector2D<T>(1, 0), Vector2D<T>(0, 1) }
    {}


    template <Arithmetic T>
    constexpr Matrix2D<T>::Matrix2D(const T m00, const T m01, const T m10, const T m11) noexcept
        : _data{ Vector2D<T>(m00, m10), Vector2D<T>(m01, m11) }
    {}


    template <Arithmetic T>
    constexpr Matrix2D<T>::Matrix2D(const Vector2D<T>& col0, const Vector2D<T>& col1) noexcept: _data{ col0, col1 }
    {}


    template <Arithmetic T>
    constexpr Matrix2D<T>::Matrix2D(const T d0, const T d1) noexcept: _data{ Vector2D<T>(d0, 0), Vector2D<T>(0, d1) }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Matrix2D<T>::Matrix2D(const Matrix2D<U>& other) noexcept
    {
        (*this)(0, 0) = static_cast<T>(other(0, 0));
        (*this)(0, 1) = static_cast<T>(other(0, 1));
        (*this)(1, 0) = static_cast<T>(other(1, 0));
        (*this)(1, 1) = static_cast<T>(other(1, 1));
    }



    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Vector2D<T>& Matrix2D<T>::operator[](const std::size_t col) noexcept
    {
        return _data[col];
    }

    template <Arithmetic T>
    constexpr const Vector2D<T>& Matrix2D<T>::operator[](const std::size_t col) const noexcept
    {
        return _data[col];
    }

    template <Arithmetic T>
    constexpr T& Matrix2D<T>::operator()(const std::size_t row, const std::size_t col) noexcept
    {
        return _data[col][row];
    }

    template <Arithmetic T>
    constexpr const T& Matrix2D<T>::operator()(const std::size_t row, const std::size_t col) const noexcept
    {
        return _data[col][row];
    }



    /**************************************
     *                                    *
     *             CONSTANTS              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr Matrix2D<T> Matrix2D<T>::eye() noexcept
    {
        return Matrix2D(T(1), T(1));
    }

    template <Arithmetic T>
    constexpr Matrix2D<T> Matrix2D<T>::zero() noexcept
    {
        return Matrix2D(T(0), T(0));
    }



    /***************************************
     *                                     *
     *             EQUALITY                *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix2D<T>::allEq(const Matrix2D<U>& rhs, const double epsilon) const noexcept
    {
        // MSVC's constexpr evaluator incorrectly yields true for NaN relational comparisons.
        // To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
        // if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
#ifdef _MSC_VER
        if (std::is_constant_evaluated())
            if (hasNaN() || rhs.hasNaN())
                return false;
#endif
        return _data[0].allEq(rhs[0], epsilon) && _data[1].allEq(rhs[1], epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix2D<T>::allEq(const Matrix2D& lhs, const Matrix2D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.allEq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix2D<T>::anyNeq(const Matrix2D<U>& rhs, const double epsilon) const noexcept
    {
        // MSVC's constexpr evaluator incorrectly yields true for NaN relational comparisons.
        // To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
        // if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
#ifdef _MSC_VER
        if (std::is_constant_evaluated())
            if (hasNaN() || rhs.hasNaN())
                return true;
#endif
        return _data[0].anyNeq(rhs[0], epsilon) || _data[1].anyNeq(rhs[1], epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix2D<T>::anyNeq(const Matrix2D& lhs, const Matrix2D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.anyNeq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix2D<T>::operator==(const Matrix2D<U>& rhs) const noexcept
    {
        return allEq(rhs);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix2D<T>::operator!=(const Matrix2D<U>& rhs) const noexcept
    {
        return anyNeq(rhs);
    }



    /**************************************
     *                                    *
     *        ARITHMETIC OPERATORS        *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr PromotedMatrix2D<T, U> Matrix2D<T>::operator+(const Matrix2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Matrix2D<R>(_data[0] + rhs[0], _data[1] + rhs[1]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    Matrix2D<T>& Matrix2D<T>::operator+=(const Matrix2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] += rhs[0];
        _data[1] += rhs[1];
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr PromotedMatrix2D<T, U> Matrix2D<T>::operator-(const Matrix2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Matrix2D<R>(_data[0] - rhs[0], _data[1] - rhs[1]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Matrix2D<T>& Matrix2D<T>::operator-=(const Matrix2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] -= rhs[0];
        _data[1] -= rhs[1];
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedMatrix2D<T, S> Matrix2D<T>::operator*(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        return Matrix2D<R>(scalar * _data[0], scalar * _data[1]);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Matrix2D<T>& Matrix2D<T>::operator*=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] *= scalar;
        _data[1] *= scalar;
        return *this;
    }

    template <StrictArithmetic T, StrictArithmetic S>
    constexpr PromotedMatrix2D<T, S> operator*(const S scalar, const Matrix2D<T>& mat) noexcept
    {
        return mat * scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr PromotedVector2D<T, U> Matrix2D<T>::operator*(const Vector2D<U>& vec) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>)
            if (!std::is_constant_evaluated())
                return Vector2D<R>(std::fma(static_cast<R>(_data[0][0]), static_cast<R>(vec[0]),
                                            static_cast<R>(_data[1][0]) * static_cast<R>(vec[1])),
                                   std::fma(static_cast<R>(_data[0][1]), static_cast<R>(vec[0]),
                                            static_cast<R>(_data[1][1]) * static_cast<R>(vec[1])));
#endif

        R x =
            static_cast<R>(_data[0][0]) * static_cast<R>(vec[0]) + static_cast<R>(_data[1][0]) * static_cast<R>(vec[1]);
        R y =
            static_cast<R>(_data[0][1]) * static_cast<R>(vec[0]) + static_cast<R>(_data[1][1]) * static_cast<R>(vec[1]);

        return Vector2D<R>(x, y);
    }


    template <StrictArithmetic T, StrictArithmetic U>
    constexpr PromotedVector2D<T, U> operator*(const Vector2D<T>& vec, const Matrix2D<U>& mat) noexcept
    {
        using R = std::common_type_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>)
            if (!std::is_constant_evaluated())
                return Vector2D<R>(std::fma(static_cast<R>(vec[0]), static_cast<R>(mat(0, 0)),
                                            static_cast<R>(vec[1]) * static_cast<R>(mat(1, 0))),
                                   std::fma(static_cast<R>(vec[0]), static_cast<R>(mat(0, 1)),
                                            static_cast<R>(vec[1]) * static_cast<R>(mat(1, 1))));

#endif
        R x = static_cast<R>(vec[0]) * static_cast<R>(mat(0, 0)) + static_cast<R>(vec[1]) * static_cast<R>(mat(1, 0));
        R y = static_cast<R>(vec[0]) * static_cast<R>(mat(0, 1)) + static_cast<R>(vec[1]) * static_cast<R>(mat(1, 1));

        return Vector2D<R>(x, y);
    }


    template <StrictArithmetic T, StrictArithmetic U>
    constexpr Vector2D<T>& operator*=(Vector2D<T>& vec, const Matrix2D<U>& mat) noexcept
    {
        using R = std::common_type_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>)
            if (!std::is_constant_evaluated())
            {
                R x = std::fma(static_cast<R>(vec[0]), static_cast<R>(mat(0, 0)),
                               static_cast<R>(vec[1]) * static_cast<R>(mat(1, 0)));
                R y = std::fma(static_cast<R>(vec[0]), static_cast<R>(mat(0, 1)),
                               static_cast<R>(vec[1]) * static_cast<R>(mat(1, 1)));

                vec.x() = static_cast<T>(x);
                vec.y() = static_cast<T>(y);

                return vec;
            }
#endif
        R x = static_cast<R>(vec[0]) * static_cast<R>(mat(0, 0)) + static_cast<R>(vec[1]) * static_cast<R>(mat(1, 0));
        R y = static_cast<R>(vec[0]) * static_cast<R>(mat(0, 1)) + static_cast<R>(vec[1]) * static_cast<R>(mat(1, 1));

        vec.x() = static_cast<T>(x);
        vec.y() = static_cast<T>(y);

        return vec;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr PromotedMatrix2D<T, U> Matrix2D<T>::operator*(const Matrix2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Matrix2D<R>((*this) * rhs[0], (*this) * rhs[1]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Matrix2D<T>& Matrix2D<T>::operator*=(const Matrix2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        const auto mat = (*this) * rhs;
        _data[0] = mat[0];
        _data[1] = mat[1];
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedFloatMatrix2D<T, S> Matrix2D<T>::operator/(const S& scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<std::common_type_t<T, S>>;
        // TODO: Update to use FMGASSERT, refactor tests accordingly
        assert(fgm::abs(R(scalar)) > Config::EPSILON<R> &&
               "Matrix division by zero"); // TODO: Change to custom assert and add custom abs

        R factor = R(1) / static_cast<R>(scalar);
        return Matrix2D<R>(static_cast<R>(_data[0][0]) * factor, static_cast<R>(_data[1][0]) * factor,
                           static_cast<R>(_data[0][1]) * factor, static_cast<R>(_data[1][1]) * factor);
    }



    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Matrix2D<T>& Matrix2D<T>::operator/=(const S& scalar) noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<std::common_type_t<T, S>>;

        assert(fgm::abs(R(scalar)) > Config::EPSILON<R> &&
               "Matrix division by zero"); // TODO: Change to custom assert and add custom abs

        R factor = R(1) / static_cast<R>(scalar);

        _data[0][0] = static_cast<T>(static_cast<R>(_data[0][0]) * factor);
        _data[1][0] = static_cast<T>(static_cast<R>(_data[1][0]) * factor);
        _data[0][1] = static_cast<T>(static_cast<R>(_data[0][1]) * factor);
        _data[1][1] = static_cast<T>(static_cast<R>(_data[1][1]) * factor);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedFloatMatrix2D<T, S> Matrix2D<T>::safeDiv(const S scalar, const Matrix2D& fallback) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
            if (fgm::abs(scalar) <= std::numeric_limits<R>::epsilon() || fgm::isnan(scalar) || hasNaN())
                return Matrix2D<R>(fallback);
        if constexpr (std::is_integral_v<R>)
            if (scalar == 0)
                return Matrix2D<Magnitude<R>>(fallback);

        return (*this) / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedFloatMatrix2D<T, S> Matrix2D<T>::safeDiv(const Matrix2D& mat, const S scalar,
                                                               const Matrix2D<T>& fallback) noexcept
        requires StrictArithmetic<T>
    {
        return mat.safeDiv(scalar, fallback);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedFloatMatrix2D<T, S> Matrix2D<T>::tryDiv(const S scalar, OperationStatus& status,
                                                              const Matrix2D<T>& fallback) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (hasNaN() | fgm::isnan(scalar))
            {
                status = OperationStatus::NANOPERAND;
                return Matrix2D<R>(fallback);
            }
            if (fgm::abs(scalar) <= std::numeric_limits<R>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return Matrix2D<R>(fallback);
            }
        }

        if constexpr (std::is_integral_v<R>)
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return Matrix2D<Magnitude<R>>(fallback);
            }


        status = OperationStatus::SUCCESS;
        return (*this) / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedFloatMatrix2D<T, S> Matrix2D<T>::tryDiv(const Matrix2D& mat, const S scalar,
                                                              OperationStatus& status,
                                                              const Matrix2D& fallback) noexcept
        requires StrictArithmetic<T>
    {
        return mat.tryDiv(scalar, status, fallback);
    }




    /**************************************
     *                                    *
     *           MATRIX ALGEBRA           *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr T Matrix2D<T>::determinant() const noexcept
        requires SignedStrictArithmetic<T>
    {
        return _data[0][0] * _data[1][1] - _data[0][1] * _data[1][0];
    }


    template <Arithmetic T>
    constexpr T Matrix2D<T>::determinant(const Matrix2D<T>& mat) noexcept
        requires SignedStrictArithmetic<T>
    {

        return mat.determinant();
    }


    template <Arithmetic T>
    constexpr Matrix2D<T> Matrix2D<T>::transpose() const noexcept
    {
        // NOTE: _data is a column major vector so _data[0][1] gives element at first row and zeroth column.
        return Matrix2D(_data[0][0], _data[0][1], _data[1][0], _data[1][1]);
    }


    template <Arithmetic T>
    constexpr Matrix2D<T> Matrix2D<T>::transpose(const Matrix2D& mat) noexcept
    {
        return mat.transpose();
    }


    template <Arithmetic T>
    constexpr Matrix2D<Magnitude<T>> Matrix2D<T>::inverse() const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        R det = determinant();
        assert(determinant() > Config::EPSILON<R> &&
               "[Matrix2D Determinant]: Division by zero."); // TODO: Update to custom assert

        R factor = R(1) / det;

        return Matrix2D<R>(static_cast<R>(_data[1][1]) * factor, static_cast<R>(-_data[1][0]) * factor,
                           static_cast<R>(-_data[0][1]) * factor, static_cast<R>(_data[0][0]) * factor);
    }


    template <Arithmetic T>
    constexpr Matrix2D<Magnitude<T>> Matrix2D<T>::inverse(const Matrix2D& matrix) noexcept
        requires SignedStrictArithmetic<T>
    {
        return matrix.inverse();
    }


    template <Arithmetic T>
    constexpr Matrix2D<Magnitude<T>> Matrix2D<T>::safeInverse(const Matrix2D& fallback) const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        T det = determinant();

        if constexpr (std::is_floating_point_v<T>)
            if (hasNaN() || (fgm::abs(det) <= std::numeric_limits<T>::epsilon()))
                return Matrix2D<R>(fallback);
        if constexpr (std::is_integral_v<T>)
            if (det == 0)
                return Matrix2D<R>(fallback);

        return inverse();
    }


    template <Arithmetic T>
    constexpr Matrix2D<Magnitude<T>> Matrix2D<T>::safeInverseOf(const Matrix2D& matrix,
                                                                const Matrix2D& fallback) noexcept
        requires SignedStrictArithmetic<T>
    {
        return matrix.safeInverse(fallback);
    }


    template <Arithmetic T>
    constexpr Matrix2D<Magnitude<T>> Matrix2D<T>::tryInverse(OperationStatus& status,
                                                             const Matrix2D& fallback) const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        T det = determinant();

        if constexpr (std::is_floating_point_v<T>)
        {
            if (hasNaN())
            {
                status = OperationStatus::NANOPERAND;
                return Matrix2D<R>(fallback);
            }
            if (fgm::abs(det) <= std::numeric_limits<T>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return Matrix2D<R>(fallback);
            }
        }

        if constexpr (std::is_integral_v<T>)
            if (det == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return Matrix2D<R>(fallback);
            }


        status = OperationStatus::SUCCESS;
        return inverse();
    }


    template <Arithmetic T>
    constexpr Matrix2D<Magnitude<T>> Matrix2D<T>::tryInverseOf(const Matrix2D& matrix, OperationStatus& status,
                                                               const Matrix2D& fallback) noexcept
        requires SignedStrictArithmetic<T>
    {
        return matrix.tryInverse(status, fallback);
    }


    template <Arithmetic T>
    constexpr T Matrix2D<T>::trace() const noexcept
        requires StrictArithmetic<T>
    {
        return _data[0][0] + _data[1][1];
    }


    template <Arithmetic T>
    constexpr T Matrix2D<T>::trace(const Matrix2D& mat) noexcept
        requires StrictArithmetic<T>
    {
        return mat.trace();
    }



    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr bool Matrix2D<T>::hasInf() const noexcept
    {
        return _data[0].hasInf() || _data[1].hasInf();
    }


    template <Arithmetic T>
    constexpr bool Matrix2D<T>::hasInf(const Matrix2D& mat) noexcept
    {
        return mat.hasInf();
    }


    template <Arithmetic T>
    constexpr bool Matrix2D<T>::hasNaN() const noexcept
    {
        return _data[0].hasNaN() || _data[1].hasNaN();
    }


    template <Arithmetic T>
    constexpr bool Matrix2D<T>::hasNaN(const Matrix2D& mat) noexcept
    {
        return mat.hasNaN();
    }




    /**************************************
     *                                    *
     *       TRANSFORMATION FACTORIES     *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <std::floating_point U>
    constexpr Matrix2D<T> Matrix2D<T>::makeRotation(const U angle) noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        R cos = std::cos(angle);
        R sine = std::sin(angle);
#ifdef FGM_LEFT_HANDED
        return Matrix2D(cos, sine, -sine, cos);
#else
        return Matrix2D(cos, -sine, sine, cos);
#endif
    }


    template <Arithmetic T>
    constexpr Matrix2D<T> Matrix2D<T>::makeScale(const T scale) noexcept
        requires StrictArithmetic<T>
    {
        return Matrix2D(scale, T(0), T(0), scale);
    }


    template <Arithmetic T>
    constexpr Matrix2D<T> Matrix2D<T>::makeScale(const T scaleX, const T scaleY) noexcept
        requires StrictArithmetic<T>
    {
        return Matrix2D(scaleX, T(0), T(0), scaleY);
    }


    template <Arithmetic T>
    constexpr Matrix2D<T> Matrix2D<T>::makeReflection(const bool reflectX, const bool reflectY) noexcept
        requires StrictArithmetic<T>
    {
        return Matrix2D(static_cast<T>(reflectX * -2 + 1), T(0), T(0), static_cast<T>(reflectY * -2 + 1));
    }

} // namespace fgm
