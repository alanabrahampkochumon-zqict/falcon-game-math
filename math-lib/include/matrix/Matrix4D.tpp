#pragma once
/**
 * @file Matrix4D.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: February 15, 2026
 *
 * @brief @ref Matrix3D template implementation.
 * @details This file contains the definitions of the template members declared in Matrix3D.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wbitwise-instead-of-logical"
#endif

namespace fgm {
    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template<Arithmetic T>
    constexpr Matrix4D<T>::Matrix4D() noexcept
        : _data{
            Vector4D{T(1), T(0), T(0), T(0)}, Vector4D{T(0), T(1), T(0), T(0)},
            Vector4D{T(0), T(0), T(1), T(0)}, Vector4D{T(0), T(0), T(0), T(1)}
        } {}


    template<Arithmetic T>
    constexpr Matrix4D<T>::Matrix4D(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23,
                                    T m30, T m31, T m32, T m33) noexcept
        : _data{
            Vector4D{T(m00), T(m10), T(m20), T(m30)}, Vector4D{T(m01), T(m11), T(m21), T(m31)},
            Vector4D{T(m02), T(m12), T(m22), T(m32)}, Vector4D{T(m03), T(m13), T(m23), T(m33)}
        } {}


    template<Arithmetic T>
    constexpr Matrix4D<T>::Matrix4D(const Vector4D<T> &col0, const Vector4D<T> &col1, const Vector4D<T> &col2,
                                    const Vector4D<T> &col3) noexcept
        : _data{col0, col1, col2, col3} {}


    template<Arithmetic T>
    constexpr Matrix4D<T>::Matrix4D(T d0, T d1, T d2, T d3) noexcept
        : _data{
            Vector4D{T(d0), T(0), T(0), T(0)}, Vector4D{T(0), T(d1), T(0), T(0)},
            Vector4D{T(0), T(0), T(d2), T(0)}, Vector4D{T(0), T(0), T(0), T(d3)}
        } {}


    template<Arithmetic T>
    template<Arithmetic U>
    constexpr Matrix4D<T>::Matrix4D(const Matrix4D<U> &other) noexcept {
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
        (*this)(3, 0) = static_cast<T>(other(3, 0));
        (*this)(3, 1) = static_cast<T>(other(3, 1));
        (*this)(3, 2) = static_cast<T>(other(3, 2));
        (*this)(3, 3) = static_cast<T>(other(3, 3));
    }


    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template<Arithmetic T>
    constexpr Vector4D<T> &Matrix4D<T>::operator[](std::size_t col) noexcept {
        return _data[col];
    }


    template<Arithmetic T>
    constexpr const Vector4D<T> &Matrix4D<T>::operator[](std::size_t col) const noexcept {
        return _data[col];
    }


    template<Arithmetic T>
    constexpr T &Matrix4D<T>::operator()(std::size_t row, std::size_t col) noexcept {
        return _data[col][row];
    }


    template<Arithmetic T>
    constexpr const T &Matrix4D<T>::operator()(std::size_t row, std::size_t col) const noexcept {
        return _data[col][row];
    }


    /**************************************
     *                                    *
     *             CONSTANTS              *
     *                                    *
     **************************************/

    template<Arithmetic T>
    constexpr Matrix4D<T> Matrix4D<T>::eye() noexcept {
        return Matrix4D(T(1), T(1), T(1), T(1));
    }


    template<Arithmetic T>
    constexpr Matrix4D<T> Matrix4D<T>::zero() noexcept {
        return Matrix4D(T(0), T(0), T(0), T(0));
    }


    /***************************************
     *                                     *
     *             EQUALITY                *
     *                                     *
     ***************************************/

    template<Arithmetic T>
    template<Arithmetic U>
    constexpr bool Matrix4D<T>::allEq(const Matrix4D<U> &rhs, double epsilon) const noexcept {
        // MSVC's constexpr evaluator incorrectly yields true for NaN relational comparisons.
        // To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
        // if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
        #ifdef _MSC_VER
        if (std::is_constant_evaluated()) {
            if (hasNaN() || rhs.hasNaN()) {
                return false;
            }
        }
        #endif
        return _data[0].allEq(rhs[0], epsilon) && _data[1].allEq(rhs[1], epsilon) && _data[2].allEq(rhs[2], epsilon) &&
               _data[3].allEq(rhs[3], epsilon);
    }


    template<Arithmetic T>
    template<Arithmetic U>
    constexpr bool Matrix4D<T>::allEq(const Matrix4D &lhs, const Matrix4D<U> &rhs, double epsilon) noexcept {
        return lhs.allEq(rhs, epsilon);
    }


    template<Arithmetic T>
    template<Arithmetic U>
    constexpr bool Matrix4D<T>::anyNeq(const Matrix4D<U> &rhs, double epsilon) const noexcept {
        // MSVC's constexpr evaluator incorrectly yields true for NaN relational comparisons.
        // To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
        // if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
        #ifdef _MSC_VER
        if (std::is_constant_evaluated()) {
            if (hasNaN() || rhs.hasNaN()) {
                return true;
            }
        }
        #endif
        return _data[0].anyNeq(rhs[0], epsilon) || _data[1].anyNeq(rhs[1], epsilon) ||
               _data[2].anyNeq(rhs[2], epsilon) || _data[3].anyNeq(rhs[3], epsilon);
    }


    template<Arithmetic T>
    template<Arithmetic U>
    constexpr bool Matrix4D<T>::anyNeq(const Matrix4D &lhs, const Matrix4D<U> &rhs, double epsilon) noexcept {
        return lhs.anyNeq(rhs, epsilon);
    }


    template<Arithmetic T>
    template<Arithmetic U>
    constexpr bool Matrix4D<T>::operator==(const Matrix4D<U> &rhs) const noexcept {
        return allEq(rhs);
    }


    template<Arithmetic T>
    template<Arithmetic U>
    constexpr bool Matrix4D<T>::operator!=(const Matrix4D<U> &rhs) const noexcept {
        return anyNeq(rhs);
    }


    /**************************************
     *                                    *
     *        ARITHMETIC OPERATORS        *
     *                                    *
     **************************************/

    template<Arithmetic T>
    template<StrictArithmetic U>
    constexpr PromotedMatrix4D<T, U> Matrix4D<T>::operator+(const Matrix4D<U> &rhs) const noexcept
        requires StrictArithmetic<T> {
        using R = PromotedValue_t<T, U>;
        return Matrix4D<R>(_data[0] + rhs[0], _data[1] + rhs[1], _data[2] + rhs[2], _data[3] + rhs[3]);
    }

    template<Arithmetic T>
    template<StrictArithmetic U>
    Matrix4D<T> &Matrix4D<T>::operator+=(const Matrix4D<U> &rhs) noexcept
        requires StrictArithmetic<T> {
        _data[0] += rhs[0];
        _data[1] += rhs[1];
        _data[2] += rhs[2];
        _data[3] += rhs[3];
        return *this;
    }


    template<Arithmetic T>
    template<StrictArithmetic U>
    constexpr PromotedMatrix4D<T, U> Matrix4D<T>::operator-(const Matrix4D<U> &rhs) const noexcept
        requires StrictArithmetic<T> {
        using R = PromotedValue_t<T, U>;
        return Matrix4D<R>(_data[0] - rhs[0], _data[1] - rhs[1], _data[2] - rhs[2], _data[3] - rhs[3]);
    }


    template<Arithmetic T>
    template<StrictArithmetic U>
    constexpr Matrix4D<T> &Matrix4D<T>::operator-=(const Matrix4D<U> &rhs) noexcept
        requires StrictArithmetic<T> {
        _data[0] -= rhs[0];
        _data[1] -= rhs[1];
        _data[2] -= rhs[2];
        _data[3] -= rhs[3];
        return *this;
    }


    template<Arithmetic T>
    template<StrictArithmetic S>
    constexpr PromotedMatrix4D<T, S> Matrix4D<T>::operator*(S scalar) const noexcept
        requires StrictArithmetic<T> {
        using R = PromotedValue_t<T, S>;
        return Matrix4D<R>(scalar * _data[0], scalar * _data[1], scalar * _data[2], scalar * _data[3]);
    }


    template<StrictArithmetic T, StrictArithmetic S>
    constexpr PromotedMatrix4D<T, S> operator*(S scalar, const Matrix4D<T> &matrix) noexcept {
        return matrix * scalar;
    }


    template<Arithmetic T>
    template<StrictArithmetic S>
    constexpr Matrix4D<T> &Matrix4D<T>::operator*=(S scalar) noexcept
        requires StrictArithmetic<T> {
        _data[0] *= scalar;
        _data[1] *= scalar;
        _data[2] *= scalar;
        _data[3] *= scalar;
        return *this;
    }


    template<Arithmetic T>
    template<StrictArithmetic U>
    constexpr PromotedVector4D<T, U> Matrix4D<T>::operator*(const Vector4D<U> &vec) const noexcept
        requires StrictArithmetic<T> {
        using R = PromotedValue_t<T, U>;
        #if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>) {
            if (!std::is_constant_evaluated()) {
                return Vector4D<R>(
                    std::fma(static_cast<R>(_data[0][0]), static_cast<R>(vec[0]),
                             std::fma(static_cast<R>(_data[1][0]), static_cast<R>(vec[1]),
                                      std::fma(static_cast<R>(_data[2][0]), static_cast<R>(vec[2]),
                                               static_cast<R>(_data[3][0]) * static_cast<R>(vec[3])))), // x
                    std::fma(static_cast<R>(_data[0][1]), static_cast<R>(vec[0]),
                             std::fma(static_cast<R>(_data[1][1]), static_cast<R>(vec[1]),
                                      std::fma(static_cast<R>(_data[2][1]), static_cast<R>(vec[2]),
                                               static_cast<R>(_data[3][1]) * static_cast<R>(vec[3])))), // y
                    std::fma(static_cast<R>(_data[0][2]), static_cast<R>(vec[0]),
                             std::fma(static_cast<R>(_data[1][2]), static_cast<R>(vec[1]),
                                      std::fma(static_cast<R>(_data[2][2]), static_cast<R>(vec[2]),
                                               static_cast<R>(_data[3][2]) * static_cast<R>(vec[3])))), // z
                    std::fma(static_cast<R>(_data[0][3]), static_cast<R>(vec[0]),
                             std::fma(static_cast<R>(_data[1][3]), static_cast<R>(vec[1]),
                                      std::fma(static_cast<R>(_data[2][3]), static_cast<R>(vec[2]),
                                               static_cast<R>(_data[3][3]) * static_cast<R>(vec[3]))))); // w
            }
        }
        #endif
        R x = static_cast<R>(_data[0][0]) * static_cast<R>(vec[0]) +
              static_cast<R>(_data[1][0]) * static_cast<R>(vec[1]) +
              static_cast<R>(_data[2][0]) * static_cast<R>(vec[2]) + static_cast<R>(_data[3][0]) * static_cast<R>(vec[
                  3]);

        R y = static_cast<R>(_data[0][1]) * static_cast<R>(vec[0]) +
              static_cast<R>(_data[1][1]) * static_cast<R>(vec[1]) +
              static_cast<R>(_data[2][1]) * static_cast<R>(vec[2]) + static_cast<R>(_data[3][1]) * static_cast<R>(vec[
                  3]);

        R z = static_cast<R>(_data[0][2]) * static_cast<R>(vec[0]) +
              static_cast<R>(_data[1][2]) * static_cast<R>(vec[1]) +
              static_cast<R>(_data[2][2]) * static_cast<R>(vec[2]) + static_cast<R>(_data[3][2]) * static_cast<R>(vec[
                  3]);

        R w = static_cast<R>(_data[0][3]) * static_cast<R>(vec[0]) +
              static_cast<R>(_data[1][3]) * static_cast<R>(vec[1]) +
              static_cast<R>(_data[2][3]) * static_cast<R>(vec[2]) + static_cast<R>(_data[3][3]) * static_cast<R>(vec[
                  3]);

        return Vector4D<R>(x, y, z, w);
    }


    template<StrictArithmetic T, StrictArithmetic U>
    constexpr PromotedVector4D<T, U> operator*(const Vector4D<T> &vec, const Matrix4D<U> &matrix) noexcept {
        using R = PromotedValue_t<T, U>;
        #if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>) {
            if (!std::is_constant_evaluated()) {
                return Vector4D<R>(std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 0)),
                                            std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 0)),
                                                     std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 0)),
                                                              static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 0))))),
                                   std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 1)),
                                            std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 1)),
                                                     std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 1)),
                                                              static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 1))))),
                                   std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 2)),
                                            std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 2)),
                                                     std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 2)),
                                                              static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 2))))),
                                   std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 3)),
                                            std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 3)),
                                                     std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 3)),
                                                              static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 3))))));
            }
        }

        #endif
        R x = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 0)) +
              static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0)) +
              static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 0)) +
              static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 0));

        R y = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 1)) +
              static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1)) +
              static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 1)) +
              static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 1));

        R z = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 2)) +
              static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 2)) +
              static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 2)) +
              static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 2));

        R w = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 3)) +
              static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 3)) +
              static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 3)) +
              static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 3));

        return Vector4D<R>(x, y, z, w);
    }


    template<StrictArithmetic T, StrictArithmetic U>
    constexpr Vector4D<T> &operator*=(Vector4D<T> &vec, const Matrix4D<U> &matrix) noexcept {
        using R = PromotedValue_t<T, U>;
        #if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>) {
            if (!std::is_constant_evaluated()) {
                R x = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 0)),
                               std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 0)),
                                        std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 0)),
                                                 static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 0)))));
                R y = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 1)),
                               std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 1)),
                                        std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 1)),
                                                 static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 1)))));
                R z = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 2)),
                               std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 2)),
                                        std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 2)),
                                                 static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 2)))));
                R w = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 3)),
                               std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 3)),
                                        std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 3)),
                                                 static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 3)))));

                vec.x() = static_cast<T>(x);
                vec.y() = static_cast<T>(y);
                vec.z() = static_cast<T>(z);
                vec.w() = static_cast<T>(w);

                return vec;
            }
        }
        #endif
        R x = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 0)) +
              static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0)) +
              static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 0)) +
              static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 0));

        R y = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 1)) +
              static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1)) +
              static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 1)) +
              static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 1));

        R z = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 2)) +
              static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 2)) +
              static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 2)) +
              static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 2));

        R w = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 3)) +
              static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 3)) +
              static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 3)) +
              static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 3));

        vec.x() = static_cast<T>(x);
        vec.y() = static_cast<T>(y);
        vec.z() = static_cast<T>(z);
        vec.w() = static_cast<T>(w);

        return vec;
    }


    template<Arithmetic T>
    template<StrictArithmetic U>
    constexpr PromotedMatrix4D<T, U> Matrix4D<T>::operator*(const Matrix4D<U> &rhs) const noexcept
        requires StrictArithmetic<T> {
        using R = PromotedValue_t<T, U>;
        return Matrix4D<R>(*this * rhs[0], *this * rhs[1], *this * rhs[2], *this * rhs[3]);
    }

    template<Arithmetic T>
    template<StrictArithmetic U>
    constexpr Matrix4D<T> &Matrix4D<T>::operator*=(const Matrix4D<U> &rhs) noexcept
        requires StrictArithmetic<T> {
        const auto mat = *this * rhs;
        _data[0] = static_cast<Vector4D<T>>(mat[0]);
        _data[1] = static_cast<Vector4D<T>>(mat[1]);
        _data[2] = static_cast<Vector4D<T>>(mat[2]);
        _data[3] = static_cast<Vector4D<T>>(mat[3]);
        return *this;
    }


    template<Arithmetic T>
    template<StrictArithmetic S>
    constexpr PromotedMatrix4D<T, S> Matrix4D<T>::operator/(const S &scalar) const noexcept
        requires StrictArithmetic<T> {
        using R = PromotedValue_t<T, S>;
        if constexpr (std::is_floating_point_v<R>) {
            FGM_ASSERT_MSG(fgm::abs(R(scalar)) > Config::EPSILON<R>, messages::assertion::MAT_DIV_BY_ZERO);
            R factor = R(1) / static_cast<R>(scalar);
            return Matrix4D<R>(_data[0] * factor, _data[1] * factor, _data[2] * factor, _data[3] * factor);
        } else {
            FGM_ASSERT_MSG(scalar != S(0), messages::assertion::MAT_DIV_BY_ZERO);
            R tScalar = static_cast<R>(scalar);
            return Matrix4D<R>(_data[0] / tScalar, _data[1] / tScalar, _data[2] / tScalar, _data[3] / tScalar);
        }
    }


    template<Arithmetic T>
    template<StrictArithmetic S>
    constexpr Matrix4D<T> &Matrix4D<T>::operator/=(const S &scalar) noexcept
        requires StrictArithmetic<T> {
        using R = Magnitude<PromotedValue_t<T, S> >;

        FGM_ASSERT_MSG(fgm::abs(R(scalar)) > Config::EPSILON<R>, messages::assertion::MAT_DIV_BY_ZERO);

        R factor = R(1) / static_cast<R>(scalar);

        _data[0][0] = static_cast<T>(static_cast<R>(_data[0][0]) * factor);
        _data[1][0] = static_cast<T>(static_cast<R>(_data[1][0]) * factor);
        _data[2][0] = static_cast<T>(static_cast<R>(_data[2][0]) * factor);
        _data[3][0] = static_cast<T>(static_cast<R>(_data[3][0]) * factor);
        _data[0][1] = static_cast<T>(static_cast<R>(_data[0][1]) * factor);
        _data[1][1] = static_cast<T>(static_cast<R>(_data[1][1]) * factor);
        _data[2][1] = static_cast<T>(static_cast<R>(_data[2][1]) * factor);
        _data[3][1] = static_cast<T>(static_cast<R>(_data[3][1]) * factor);
        _data[0][2] = static_cast<T>(static_cast<R>(_data[0][2]) * factor);
        _data[1][2] = static_cast<T>(static_cast<R>(_data[1][2]) * factor);
        _data[2][2] = static_cast<T>(static_cast<R>(_data[2][2]) * factor);
        _data[3][2] = static_cast<T>(static_cast<R>(_data[3][2]) * factor);
        _data[0][3] = static_cast<T>(static_cast<R>(_data[0][3]) * factor);
        _data[1][3] = static_cast<T>(static_cast<R>(_data[1][3]) * factor);
        _data[2][3] = static_cast<T>(static_cast<R>(_data[2][3]) * factor);
        _data[3][3] = static_cast<T>(static_cast<R>(_data[3][3]) * factor);

        return *this;
    }


    template<Arithmetic T>
    template<StrictArithmetic S>
    constexpr PromotedMatrix4D<T, S> Matrix4D<T>::safeDiv(S scalar, const Matrix4D &fallback) const noexcept
        requires StrictArithmetic<T> {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>) {
            if (fgm::abs(scalar) <= std::numeric_limits<R>::epsilon() || fgm::isnan(scalar) || hasNaN()) {
                return Matrix4D<R>(fallback);
            }
        }
        if constexpr (std::is_integral_v<R>) {
            if (scalar == 0) {
                return Matrix4D<R>(fallback);
            }
        }

        return *this / scalar;
    }


    template<Arithmetic T>
    template<StrictArithmetic S>
    constexpr PromotedMatrix4D<T, S> Matrix4D<T>::safeDiv(const Matrix4D &mat, S scalar,
                                                          const Matrix4D &fallback) noexcept
        requires StrictArithmetic<T> {
        return mat.safeDiv(scalar, fallback);
    }


    template<Arithmetic T>
    template<StrictArithmetic S>
    constexpr PromotedMatrix4D<T, S> Matrix4D<T>::tryDiv(S scalar, OperationStatus &status,
                                                         const Matrix4D &fallback) const noexcept
        requires StrictArithmetic<T> {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>) {
            // TODO: Check || vs | with benchmarks
            // Theoretically the slowest method since NaN checks are performed before division by zero
            if (static_cast<int>(hasNaN()) | static_cast<int>(fgm::isnan(scalar))) {
                status = OperationStatus::NANOPERAND;
                return Matrix4D<R>(fallback);
            }
            if (fgm::abs(scalar) <= std::numeric_limits<R>::epsilon()) {
                status = OperationStatus::DIVISIONBYZERO;
                return Matrix4D<R>(fallback);
            }
        }

        if constexpr (std::is_integral_v<R>) {
            if (scalar == 0) {
                status = OperationStatus::DIVISIONBYZERO;
                return Matrix4D<R>(fallback);
            }
        }

        status = OperationStatus::SUCCESS;
        return *this / scalar;
    }


    template<Arithmetic T>
    template<StrictArithmetic S>
    constexpr PromotedMatrix4D<T, S> Matrix4D<T>::tryDiv(const Matrix4D &mat, S scalar, OperationStatus &status,
                                                         const Matrix4D &fallback) noexcept
        requires StrictArithmetic<T> {
        return mat.tryDiv(scalar, status, fallback);
    }


    /**************************************
     *                                    *
     *           MATRIX ALGEBRA           *
     *                                    *
     **************************************/

    template<Arithmetic T>
    constexpr T Matrix4D<T>::determinant() const noexcept
        requires SignedStrictArithmetic<T> {
        // TODO: Replace with fgm::swizzle after factor implementation
        auto a = _data[0].template swizzle<axis::X, axis::Y, axis::Z>();
        auto b = _data[1].template swizzle<axis::X, axis::Y, axis::Z>();
        auto c = _data[2].template swizzle<axis::X, axis::Y, axis::Z>();
        auto d = _data[3].template swizzle<axis::X, axis::Y, axis::Z>();

        auto x = _data[0][3];
        auto y = _data[1][3];
        auto z = _data[2][3];
        auto w = _data[3][3];

        auto s = a.cross(b);
        auto t = c.cross(d);
        auto u = y * a - x * b;
        auto v = w * c - z * d;

        return s.dot(v) + t.dot(u);
    }


    template<Arithmetic T>
    constexpr T Matrix4D<T>::determinant(const Matrix4D &matrix) noexcept
        requires SignedStrictArithmetic<T> {
        return matrix.determinant();
    }


    template<Arithmetic T>
    constexpr Matrix4D<T> Matrix4D<T>::transpose() const noexcept {
        /**
         * @note Although the code doesn't seem to transpose, since we are storing in column major order
         *       _data[row][col] actually gives _data[col][row]
         */
        return Matrix4D(_data[0][0], _data[0][1], _data[0][2], _data[0][3], _data[1][0], _data[1][1], _data[1][2],
                        _data[1][3], _data[2][0], _data[2][1], _data[2][2], _data[2][3], _data[3][0], _data[3][1],
                        _data[3][2], _data[3][3]);
    }


    template<Arithmetic T>
    constexpr Matrix4D<T> Matrix4D<T>::transpose(const Matrix4D &matrix) noexcept {
        return matrix.transpose();
    }


    template<Arithmetic T>
    constexpr Matrix4D<Magnitude<T> > Matrix4D<T>::inverse() const noexcept
        requires SignedStrictArithmetic<T> {
        using R = Magnitude<T>;

        auto a = static_cast<Vector3D<R>>(_data[0].template swizzle<axis::X, axis::Y, axis::Z>());
        auto b = static_cast<Vector3D<R>>(_data[1].template swizzle<axis::X, axis::Y, axis::Z>());
        auto c = static_cast<Vector3D<R>>(_data[2].template swizzle<axis::X, axis::Y, axis::Z>());
        auto d = _data[3].template swizzle<axis::X, axis::Y, axis::Z>();

        auto x = _data[0][3];
        auto y = _data[1][3];
        auto z = _data[2][3];
        auto w = _data[3][3];

        auto s = static_cast<Vector3D<R>>(a.cross(b));
        auto t = c.cross(d);
        auto u = y * a - x * b;
        auto v = w * c - z * d;

        auto det = s.dot(v) + t.dot(u);
        FGM_ASSERT_MSG(fgm::abs(det) > Config::EPSILON<R>, messages::assertion::MAT_INV_ZERO_DETERMINANT);

        auto invDet = R(1) / det;

        s *= invDet;
        t *= invDet;
        u *= invDet;
        v *= invDet;

        auto row0 = b.cross(v) + t * y;
        auto row1 = v.cross(a) - t * x;
        auto row2 = d.cross(u) + s * w;
        auto row3 = u.cross(c) - s * z;

        return Matrix4D<R>(row0.x(), row0.y(), row0.z(), -b.dot(t), row1.x(), row1.y(), row1.z(), a.dot(t), row2.x(),
                           row2.y(), row2.z(), -d.dot(s), row3.x(), row3.y(), row3.z(), c.dot(s));
    }


    template<Arithmetic T>
    constexpr Matrix4D<Magnitude<T> > Matrix4D<T>::inverse(const Matrix4D &matrix) noexcept
        requires SignedStrictArithmetic<T> {
        return matrix.inverse();
    }


    template<Arithmetic T>
    constexpr Matrix4D<Magnitude<T> > Matrix4D<T>::safeInverse(const Matrix4D &fallback) const noexcept
        requires SignedStrictArithmetic<T> {
        using R = Magnitude<T>;

        auto a = static_cast<Vector3D<R>>(_data[0].template swizzle<axis::X, axis::Y, axis::Z>());
        auto b = static_cast<Vector3D<R>>(_data[1].template swizzle<axis::X, axis::Y, axis::Z>());
        auto c = static_cast<Vector3D<R>>(_data[2].template swizzle<axis::X, axis::Y, axis::Z>());
        auto d = _data[3].template swizzle<axis::X, axis::Y, axis::Z>();

        auto x = _data[0][3];
        auto y = _data[1][3];
        auto z = _data[2][3];
        auto w = _data[3][3];

        auto s = static_cast<Vector3D<R>>(a.cross(b));
        auto t = c.cross(d);
        auto u = y * a - x * b;
        auto v = w * c - z * d;

        auto det = s.dot(v) + t.dot(u);

        if constexpr (std::is_floating_point_v<T>) {
            if (hasNaN() || fgm::abs(det) <= std::numeric_limits<T>::epsilon()) {
                return Matrix4D<R>(fallback);
            }
        }
        if constexpr (std::is_integral_v<T>) {
            if (det == 0) {
                return Matrix4D<R>(fallback);
            }
        }

        auto invDet = R(1) / det;

        s *= invDet;
        t *= invDet;
        u *= invDet;
        v *= invDet;

        auto row0 = b.cross(v) + t * y;
        auto row1 = v.cross(a) - t * x;
        auto row2 = d.cross(u) + s * w;
        auto row3 = u.cross(c) - s * z;

        return Matrix4D<R>(row0.x(), row0.y(), row0.z(), -b.dot(t), row1.x(), row1.y(), row1.z(), a.dot(t), row2.x(),
                           row2.y(), row2.z(), -d.dot(s), row3.x(), row3.y(), row3.z(), c.dot(s));
    }


    template<Arithmetic T>
    constexpr Matrix4D<Magnitude<T> > Matrix4D<T>::safeInverseOf(const Matrix4D &matrix,
                                                                 const Matrix4D &fallback) noexcept
        requires SignedStrictArithmetic<T> {
        return matrix.safeInverse(fallback);
    }


    template<Arithmetic T>
    constexpr Matrix4D<Magnitude<T> > Matrix4D<T>::tryInverse(OperationStatus &status,
                                                              const Matrix4D &fallback) const noexcept
        requires SignedStrictArithmetic<T> {
        using R = Magnitude<T>;

        auto a = static_cast<Vector3D<R>>(_data[0].template swizzle<axis::X, axis::Y, axis::Z>());
        auto b = static_cast<Vector3D<R>>(_data[1].template swizzle<axis::X, axis::Y, axis::Z>());
        auto c = static_cast<Vector3D<R>>(_data[2].template swizzle<axis::X, axis::Y, axis::Z>());
        auto d = _data[3].template swizzle<axis::X, axis::Y, axis::Z>();

        auto x = _data[0][3];
        auto y = _data[1][3];
        auto z = _data[2][3];
        auto w = _data[3][3];

        auto s = static_cast<Vector3D<R>>(a.cross(b));
        auto t = c.cross(d);
        auto u = y * a - x * b;
        auto v = w * c - z * d;

        auto det = s.dot(v) + t.dot(u);

        if constexpr (std::is_floating_point_v<T>) {
            if (hasNaN()) {
                status = OperationStatus::NANOPERAND;
                return Matrix4D<R>(fallback);
            }
            if (fgm::abs(det) <= std::numeric_limits<T>::epsilon()) {
                status = OperationStatus::DIVISIONBYZERO;
                return Matrix4D<R>(fallback);
            }
        }

        auto invDet = R(1) / det;

        s *= invDet;
        t *= invDet;
        u *= invDet;
        v *= invDet;

        auto row0 = b.cross(v) + t * y;
        auto row1 = v.cross(a) - t * x;
        auto row2 = d.cross(u) + s * w;
        auto row3 = u.cross(c) - s * z;

        status = OperationStatus::SUCCESS;
        return Matrix4D<R>(row0.x(), row0.y(), row0.z(), -b.dot(t), row1.x(), row1.y(), row1.z(), a.dot(t), row2.x(),
                           row2.y(), row2.z(), -d.dot(s), row3.x(), row3.y(), row3.z(), c.dot(s));
    }


    template<Arithmetic T>
    constexpr Matrix4D<Magnitude<T> > Matrix4D<T>::tryInverseOf(const Matrix4D &matrix, OperationStatus &status,
                                                                const Matrix4D &fallback) noexcept
        requires SignedStrictArithmetic<T> {
        return matrix.tryInverse(status, fallback);
    }


    template<Arithmetic T>
    constexpr T Matrix4D<T>::trace() const noexcept
        requires StrictArithmetic<T> {
        return _data[0][0] + _data[1][1] + _data[2][2] + _data[3][3];
    }


    template<Arithmetic T>
    constexpr T Matrix4D<T>::trace(const Matrix4D &matrix) noexcept
        requires StrictArithmetic<T> {
        return matrix.trace();
    }


    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template<Arithmetic T>
    constexpr bool Matrix4D<T>::hasInf() const noexcept {
        return _data[0].hasInf() || _data[1].hasInf() || _data[2].hasInf() || _data[3].hasInf();
    }


    template<Arithmetic T>
    constexpr bool Matrix4D<T>::hasInf(const Matrix4D &matrix) noexcept {
        return matrix.hasInf();
    }


    template<Arithmetic T>
    constexpr bool Matrix4D<T>::hasNaN() const noexcept {
        return _data[0].hasNaN() || _data[1].hasNaN() || _data[2].hasNaN() || _data[3].hasNaN();
    }


    template<Arithmetic T>
    constexpr bool Matrix4D<T>::hasNaN(const Matrix4D &matrix) noexcept {
        return matrix.hasNaN();
    }
} // namespace fgm


#if defined(__clang__)
#pragma clang diagnostic pop
#endif
