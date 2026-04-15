#pragma once

#include "Matrix2D.h"

#include <cassert>
#include <cmath>
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




    /***************************************
     *                                     *
     *             EQUALITY                *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix2D<T>::allEq(const Matrix2D<U>& rhs, const double epsilon) const noexcept
    {
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


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr PromotedVector2D<T, U> Matrix2D<T>::operator*(const Vector2D<U>& vec) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA IS ALIVE AND COMPILING!" // For checking if FMA execution path is active.
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




    template <StrictArithmetic T, StrictArithmetic S>
    constexpr PromotedMatrix2D<T, S> operator*(const S scalar, const Matrix2D<T>& mat) noexcept
    {
        return mat * scalar;
    }


    template <StrictArithmetic T, StrictArithmetic U>
    constexpr PromotedVector2D<T, U> operator*(const Vector2D<T>& vec, const Matrix2D<U>& mat) noexcept
    {
        using R = std::common_type_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA IS ALIVE AND COMPILING!" // For checking if FMA execution path is active.
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
        // #error "FMA IS ALIVE AND COMPILING!" // For checking if FMA execution path is active.
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
    constexpr Matrix2D<Magnitude<std::common_type_t<T, S>>> Matrix2D<T>::operator/(const S& scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<std::common_type_t<T, S>>;

        assert(std::abs(R(scalar)) > fgm::Config::EPSILON<R> &&
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

        assert(std::abs(R(scalar)) > fgm::Config::EPSILON<R> &&
               "Matrix division by zero"); // TODO: Change to custom assert and add custom abs

        R factor = R(1) / static_cast<R>(scalar);

        _data[0][0] = static_cast<T>(static_cast<R>(_data[0][0]) * factor);
        _data[1][0] = static_cast<T>(static_cast<R>(_data[1][0]) * factor);
        _data[0][1] = static_cast<T>(static_cast<R>(_data[0][1]) * factor);
        _data[1][1] = static_cast<T>(static_cast<R>(_data[1][1]) * factor);
        return *this;
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
        assert(determinant() > fgm::Config::EPSILON<R> &&
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
    constexpr bool Matrix2D<T>::hasInf(const Matrix2D& mat) noexcept {return mat.hasInf();}


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

} // namespace fgm
