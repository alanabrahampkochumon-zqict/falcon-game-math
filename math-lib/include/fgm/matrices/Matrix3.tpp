#pragma once
/**
 * @file Matrix3.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: February 15, 2026
 *
 * @brief @ref Matrix3 template implementation.
 * @details This file contains the definitions of the template members declared in Matrix3.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wbitwise-instead-of-logical"
#endif

namespace fgm
{

    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Matrix3<T>::Matrix3(const T m00, const T m01, const T m02, const T m10, const T m11, const T m12,
                                  const T m20, const T m21, const T m22) noexcept
        : _data{ Vector3{ T(m00), T(m10), T(m20) }, Vector3{ T(m01), T(m11), T(m21) },
                 Vector3{ T(m02), T(m12), T(m22) } }
    {}


    template <Arithmetic T>
    constexpr Matrix3<T>::Matrix3(const Vector3<T>& col0, const Vector3<T>& col1, const Vector3<T>& col2) noexcept
        : _data{ col0, col1, col2 }
    {}


    template <Arithmetic T>
    constexpr Matrix3<T>::Matrix3(T d0, T d1, T d2) noexcept
        : _data{ Vector3{ T(d0), T(0), T(0) }, Vector3{ T(0), T(d1), T(0) }, Vector3{ T(0), T(0), T(d2) } }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Matrix3<T>::Matrix3(const Matrix3<U>& other) noexcept
    {
        (*this)(0, 0) = static_cast<T>(other(0, 0));
        (*this)(0, 1) = static_cast<T>(other(0, 1));
        (*this)(0, 2) = static_cast<T>(other(0, 2));
        (*this)(1, 0) = static_cast<T>(other(1, 0));
        (*this)(1, 1) = static_cast<T>(other(1, 1));
        (*this)(1, 2) = static_cast<T>(other(1, 2));
        (*this)(2, 0) = static_cast<T>(other(2, 0));
        (*this)(2, 1) = static_cast<T>(other(2, 1));
        (*this)(2, 2) = static_cast<T>(other(2, 2));
    }



    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Vector3<T>& Matrix3<T>::operator[](const std::size_t col) noexcept
    {
        FGM_ASSERT_MSG(col < columns, fgm::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col];
    }


    template <Arithmetic T>
    constexpr const Vector3<T>& Matrix3<T>::operator[](const std::size_t col) const noexcept
    {
        FGM_ASSERT_MSG(col < columns, fgm::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col];
    }


    template <Arithmetic T>
    constexpr T& Matrix3<T>::operator()(const std::size_t row, const std::size_t col) noexcept
    {
        FGM_ASSERT_MSG(col < columns || row < rows, fgm::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col][row];
    }


    template <Arithmetic T>
    constexpr const T& Matrix3<T>::operator()(const std::size_t row, const std::size_t col) const noexcept
    {
        FGM_ASSERT_MSG(col < columns || row < rows, fgm::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col][row];
    }


    /***************************************
     *                                     *
     *             EQUALITY                *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Matrix3<T>::allEq(const Matrix3<U>& rhs, const double epsilon) const noexcept
    {
        // MSVC's constexpr evaluator incorrectly yields true for NaN relational comparisons.
        // To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
        // if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
#ifdef _MSC_VER
        if (std::is_constant_evaluated())
        {
            if (hasNaN() || rhs.hasNaN())
            {
                return false;
            }
        }
#endif
        return _data[0].allEq(rhs[0], epsilon) && _data[1].allEq(rhs[1], epsilon) && _data[2].allEq(rhs[2], epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Matrix3<T>::allEq(const Matrix3& lhs, const Matrix3<U>& rhs, const double epsilon) noexcept
    {
        return lhs.allEq(rhs, epsilon);
    }

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Matrix3<T>::anyNeq(const Matrix3<U>& rhs, const double epsilon) const noexcept
    {
        // MSVC's constexpr evaluator incorrectly yields true for NaN relational comparisons.
        // To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
        // if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
#ifdef _MSC_VER
        if (std::is_constant_evaluated())
        {
            if (hasNaN() || rhs.hasNaN())
            {
                return true;
            }
        }
#endif
        return _data[0].anyNeq(rhs[0], epsilon) || _data[1].anyNeq(rhs[1], epsilon) || _data[2].anyNeq(rhs[2], epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Matrix3<T>::anyNeq(const Matrix3& lhs, const Matrix3<U>& rhs, const double epsilon) noexcept
    {
        return lhs.anyNeq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Matrix3<T>::operator==(const Matrix3<U>& rhs) const noexcept
    {
        return allEq(rhs);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    constexpr bool Matrix3<T>::operator!=(const Matrix3<U>& rhs) const noexcept
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
        requires StrictSignedness<T, U>
    constexpr PromotedMatrix3<T, U> Matrix3<T>::operator+(const Matrix3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Matrix3<R>(_data[0] + rhs[0], _data[1] + rhs[1], _data[2] + rhs[2]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    Matrix3<T>& Matrix3<T>::operator+=(const Matrix3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] += rhs[0];
        _data[1] += rhs[1];
        _data[2] += rhs[2];
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedMatrix3<T, U> Matrix3<T>::operator-(const Matrix3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Matrix3<R>(_data[0] - rhs[0], _data[1] - rhs[1], _data[2] - rhs[2]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Matrix3<T>& Matrix3<T>::operator-=(const Matrix3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] -= rhs[0];
        _data[1] -= rhs[1];
        _data[2] -= rhs[2];
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedMatrix3<T, S> Matrix3<T>::operator*(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        return Matrix3<R>(scalar * _data[0], scalar * _data[1], scalar * _data[2]);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Matrix3<T>& Matrix3<T>::operator*=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] *= scalar;
        _data[1] *= scalar;
        _data[2] *= scalar;
        return *this;
    }


    template <StrictArithmetic T, StrictArithmetic S>
    constexpr PromotedMatrix3<T, S> operator*(const S scalar, const Matrix3<T>& matrix) noexcept
    {
        return matrix * scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedVector3<T, U> Matrix3<T>::operator*(const Vector3<U>& vec) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>)
        {
            if (!std::is_constant_evaluated())
            {
                return Vector3<R>(std::fma(static_cast<R>(_data[0][0]), static_cast<R>(vec[0]),
                                           std::fma(static_cast<R>(_data[1][0]), static_cast<R>(vec[1]),
                                                    static_cast<R>(_data[2][0]) * static_cast<R>(vec[2]))),
                                  std::fma(static_cast<R>(_data[0][1]), static_cast<R>(vec[0]),
                                           std::fma(static_cast<R>(_data[1][1]), static_cast<R>(vec[1]),
                                                    static_cast<R>(_data[2][1]) * static_cast<R>(vec[2]))),
                                  std::fma(static_cast<R>(_data[0][2]), static_cast<R>(vec[0]),
                                           std::fma(static_cast<R>(_data[1][2]), static_cast<R>(vec[1]),
                                                    static_cast<R>(_data[2][2]) * static_cast<R>(vec[2]))));
            }
        }
#endif
        R x = static_cast<R>(_data[0][0]) * static_cast<R>(vec[0]) +
            static_cast<R>(_data[1][0]) * static_cast<R>(vec[1]) + static_cast<R>(_data[2][0]) * static_cast<R>(vec[2]);

        R y = static_cast<R>(_data[0][1]) * static_cast<R>(vec[0]) +
            static_cast<R>(_data[1][1]) * static_cast<R>(vec[1]) + static_cast<R>(_data[2][1]) * static_cast<R>(vec[2]);

        R z = static_cast<R>(_data[0][2]) * static_cast<R>(vec[0]) +
            static_cast<R>(_data[1][2]) * static_cast<R>(vec[1]) + static_cast<R>(_data[2][2]) * static_cast<R>(vec[2]);

        return Vector3<R>(x, y, z);
    }


    template <StrictArithmetic T, StrictArithmetic U>
    constexpr PromotedVector3<T, U> operator*(const Vector3<T>& vec, const Matrix3<U>& matrix) noexcept
    {
        using R = PromotedValue_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>)
        {
            if (!std::is_constant_evaluated())
            {
                return Vector3<R>(std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 0)), // x
                                           std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 0)),
                                                    static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 0)))),
                                  std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 1)), // y
                                           std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 1)),
                                                    static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 1)))),
                                  std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 2)), // z
                                           std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 2)),
                                                    static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 2)))));
            }
        }

#endif
        R x = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 0)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 0));

        R y = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 1)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 1));

        R z = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 2)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 2)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 2));

        return Vector3<R>(x, y, z);
    }


    template <StrictArithmetic T, StrictArithmetic U>
    constexpr Vector3<T>& operator*=(Vector3<T>& vec, const Matrix3<U>& matrix) noexcept
    {
        using R = PromotedValue_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>)
        {
            if (!std::is_constant_evaluated())
            {
                R x = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 0)),
                               std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 0)),
                                        static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 0))));
                R y = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 1)),
                               std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 1)),
                                        static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 1))));
                R z = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 2)),
                               std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 2)),
                                        static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 2))));

                vec.x() = static_cast<T>(x);
                vec.y() = static_cast<T>(y);
                vec.z() = static_cast<T>(z);

                return vec;
            }
        }
#endif
        R x = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 0)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 0));

        R y = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 1)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 1));

        R z = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 2)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 2)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 2));

        vec.x() = static_cast<T>(x);
        vec.y() = static_cast<T>(y);
        vec.z() = static_cast<T>(z);

        return vec;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedMatrix3<T, U> Matrix3<T>::operator*(const Matrix3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Matrix3<R>(*this * rhs[0], *this * rhs[1], *this * rhs[2]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Matrix3<T>& Matrix3<T>::operator*=(const Matrix3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        const auto mat = *this * rhs;
        _data[0]       = static_cast<Vector3<T>>(mat[0]);
        _data[1]       = static_cast<Vector3<T>>(mat[1]);
        _data[2]       = static_cast<Vector3<T>>(mat[2]);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedMatrix3<T, S> Matrix3<T>::operator/(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            FGM_ASSERT_MSG(fgm::abs(R(scalar)) > Config::EPSILON<R>, messages::assertion::MAT_DIV_BY_ZERO);
            R factor = R(1) / static_cast<R>(scalar);
            return Matrix3<R>(_data[0] * factor, _data[1] * factor, _data[2] * factor);
        }
        else
        {
            FGM_ASSERT_MSG(scalar != S(0), messages::assertion::MAT_DIV_BY_ZERO);
            R tScalar = static_cast<R>(scalar);
            return Matrix3<R>(_data[0] / tScalar, _data[1] / tScalar, _data[2] / tScalar);
        }
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Matrix3<T>& Matrix3<T>::operator/=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<PromotedValue_t<T, S>>;

        FGM_ASSERT_MSG(fgm::abs(R(scalar)) > Config::EPSILON<R>, messages::assertion::MAT_DIV_BY_ZERO);

        R factor = R(1) / static_cast<R>(scalar);

        _data[0][0] = static_cast<T>(static_cast<R>(_data[0][0]) * factor);
        _data[1][0] = static_cast<T>(static_cast<R>(_data[1][0]) * factor);
        _data[2][0] = static_cast<T>(static_cast<R>(_data[2][0]) * factor);
        _data[0][1] = static_cast<T>(static_cast<R>(_data[0][1]) * factor);
        _data[1][1] = static_cast<T>(static_cast<R>(_data[1][1]) * factor);
        _data[2][1] = static_cast<T>(static_cast<R>(_data[2][1]) * factor);
        _data[0][2] = static_cast<T>(static_cast<R>(_data[0][2]) * factor);
        _data[1][2] = static_cast<T>(static_cast<R>(_data[1][2]) * factor);
        _data[2][2] = static_cast<T>(static_cast<R>(_data[2][2]) * factor);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedMatrix3<T, S> Matrix3<T>::safeDiv(const S scalar, const Matrix3& fallback) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (fgm::abs(scalar) <= std::numeric_limits<R>::epsilon() || fgm::isnan(scalar) || hasNaN())
            {
                return Matrix3<R>(fallback);
            }
        }
        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                return Matrix3<R>(fallback);
            }
        }

        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedMatrix3<T, S> Matrix3<T>::safeDiv(const Matrix3& mat, const S scalar,
                                                        const Matrix3& fallback) noexcept
        requires StrictArithmetic<T>
    {
        return mat.safeDiv(scalar, fallback);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedMatrix3<T, S> Matrix3<T>::tryDiv(const S scalar, OperationStatus& status,
                                                       const Matrix3& fallback) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            // TODO: Check || vs | with benchmarks
            // Theoretically the slowest method since NaN checks are performed before division by zero
            if (static_cast<int>(hasNaN()) | static_cast<int>(fgm::isnan(scalar)))
            {
                status = OperationStatus::NANOPERAND;
                return Matrix3<R>(fallback);
            }
            if (fgm::abs(scalar) <= std::numeric_limits<R>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return Matrix3<R>(fallback);
            }
        }

        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return Matrix3<R>(fallback);
            }
        }


        status = OperationStatus::SUCCESS;
        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr PromotedMatrix3<T, S> Matrix3<T>::tryDiv(const Matrix3& mat, const S scalar, OperationStatus& status,
                                                       const Matrix3& fallback) noexcept
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
    constexpr T Matrix3<T>::determinant() const noexcept
        requires SignedStrictArithmetic<T>
    {
        /**
         * @note The documentation shows the determinant of a Matrix stored in row major,
         *       but the implementation uses column major, so row and column indices are swapped,
         *       although it will not affect the final value, as det(A) == det(A^T).
         */
        return _data[0][0] * (_data[1][1] * _data[2][2] - _data[2][1] * _data[1][2]) -
            _data[1][0] * (_data[0][1] * _data[2][2] - _data[0][2] * _data[2][1]) +
            _data[2][0] * (_data[0][1] * _data[1][2] - _data[0][2] * _data[1][1]);
    }


    template <Arithmetic T>
    constexpr T Matrix3<T>::determinant(const Matrix3& matrix) noexcept
        requires SignedStrictArithmetic<T>
    {
        return matrix.determinant();
    }


    template <Arithmetic T>
    constexpr Matrix3<T> Matrix3<T>::transpose() const noexcept
    {
        /**
         * @note Although the code doesn't seem to transpose, since we are storing in column major order
         *       _data[row][col] actually gives _data[col][row]
         */
        return Matrix3(_data[0][0], _data[0][1], _data[0][2], _data[1][0], _data[1][1], _data[1][2], _data[2][0],
                       _data[2][1], _data[2][2]);
    }


    template <Arithmetic T>
    constexpr Matrix3<T> Matrix3<T>::transpose(const Matrix3& matrix) noexcept
    {
        return matrix.transpose();
    }


    template <Arithmetic T>
    constexpr Matrix3<Magnitude<T>> Matrix3<T>::inverse() const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        const auto row0 = static_cast<Vector3<R>>(_data[1].cross(_data[2])); // b X c
        const auto row1 = static_cast<Vector3<R>>(_data[2].cross(_data[0])); // c X a
        const auto row2 = static_cast<Vector3<R>>(_data[0].cross(_data[1])); // a X b

        // Since the cross product is already computed, it takes less operation compared to calling determinant.
        R det = _data[0].dot(row0); // a.(b X c) Scalar triple product
        FGM_ASSERT_MSG(fgm::abs(det) > Config::EPSILON<R>, messages::assertion::MAT_DET_DIV_BY_ZERO);

        R factor = R(1) / det;
        return Matrix3<R>(factor * row0.x(), factor * row0.y(), factor * row0.z(), factor * row1.x(), factor * row1.y(),
                          factor * row1.z(), factor * row2.x(), factor * row2.y(), factor * row2.z());
    }


    template <Arithmetic T>
    constexpr Matrix3<Magnitude<T>> Matrix3<T>::inverse(const Matrix3& matrix) noexcept
        requires SignedStrictArithmetic<T>
    {
        return matrix.inverse();
    }


    template <Arithmetic T>
    constexpr Matrix3<Magnitude<T>> Matrix3<T>::safeInverse(const Matrix3& fallback) const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        const auto row0 = static_cast<Vector3<R>>(_data[1].cross(_data[2])); // b X c
        const auto row1 = static_cast<Vector3<R>>(_data[2].cross(_data[0])); // c X a
        const auto row2 = static_cast<Vector3<R>>(_data[0].cross(_data[1])); // a X b

        // Since the cross product is already computed, it takes less operation compared to calling determinant.
        R det = _data[0].dot(row0); // a.(b X c) Scalar triple product


        if constexpr (std::is_floating_point_v<T>)
        {
            if (hasNaN() || fgm::abs(det) <= std::numeric_limits<T>::epsilon())
            {
                return Matrix3<R>(fallback);
            }
        }
        if constexpr (std::is_integral_v<T>)
        {
            if (det == 0)
            {
                return Matrix3<R>(fallback);
            }
        }

        R factor = R(1) / det;
        return Matrix3<R>(factor * row0.x(), factor * row0.y(), factor * row0.z(), factor * row1.x(), factor * row1.y(),
                          factor * row1.z(), factor * row2.x(), factor * row2.y(), factor * row2.z());
    }


    template <Arithmetic T>
    constexpr Matrix3<Magnitude<T>> Matrix3<T>::safeInverseOf(const Matrix3& matrix, const Matrix3& fallback) noexcept
        requires SignedStrictArithmetic<T>
    {
        return matrix.safeInverse(fallback);
    }


    template <Arithmetic T>
    constexpr Matrix3<Magnitude<T>> Matrix3<T>::tryInverse(OperationStatus& status,
                                                           const Matrix3& fallback) const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        const auto row0 = static_cast<Vector3<R>>(_data[1].cross(_data[2])); // b X c
        const auto row1 = static_cast<Vector3<R>>(_data[2].cross(_data[0])); // c X a
        const auto row2 = static_cast<Vector3<R>>(_data[0].cross(_data[1])); // a X b

        // Since the cross product is already computed, it takes less operation compared to calling determinant.
        R det = _data[0].dot(row0); // a.(b X c) Scalar triple product

        if constexpr (std::is_floating_point_v<T>)
        {
            if (hasNaN())
            {
                status = OperationStatus::NANOPERAND;
                return Matrix3<R>(fallback);
            }
            if (fgm::abs(det) <= std::numeric_limits<T>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return Matrix3<R>(fallback);
            }
        }

        if constexpr (std::is_integral_v<T>)
        {
            if (det == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return Matrix3<R>(fallback);
            }
        }


        status   = OperationStatus::SUCCESS;
        R factor = R(1) / det;
        return Matrix3<R>(factor * row0.x(), factor * row0.y(), factor * row0.z(), factor * row1.x(), factor * row1.y(),
                          factor * row1.z(), factor * row2.x(), factor * row2.y(), factor * row2.z());
    }


    template <Arithmetic T>
    constexpr Matrix3<Magnitude<T>> Matrix3<T>::tryInverseOf(const Matrix3& matrix, OperationStatus& status,
                                                             const Matrix3& fallback) noexcept
        requires SignedStrictArithmetic<T>
    {
        return matrix.tryInverse(status, fallback);
    }


    template <Arithmetic T>
    constexpr T Matrix3<T>::trace() const noexcept
        requires StrictArithmetic<T>
    {
        return _data[0][0] + _data[1][1] + _data[2][2];
    }


    template <Arithmetic T>
    constexpr T Matrix3<T>::trace(const Matrix3& matrix) noexcept
        requires StrictArithmetic<T>
    {
        return matrix.trace();
    }




    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr bool Matrix3<T>::hasInf() const noexcept
    {
        return _data[0].hasInf() || _data[1].hasInf() || _data[2].hasInf();
    }


    template <Arithmetic T>
    constexpr bool Matrix3<T>::hasInf(const Matrix3& matrix) noexcept
    {
        return matrix.hasInf();
    }


    template <Arithmetic T>
    constexpr bool Matrix3<T>::hasNaN() const noexcept
    {
        return _data[0].hasNaN() || _data[1].hasNaN() || _data[2].hasNaN();
    }


    template <Arithmetic T>
    constexpr bool Matrix3<T>::hasNaN(const Matrix3& matrix) noexcept
    {
        return matrix.hasNaN();
    }



    /**************************************
     *                                    *
     *       TRANSFORMATION FACTORIES     *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <std::floating_point U>
    constexpr Matrix3<T> Matrix3<T>::makeRotationX(U angle) noexcept
        requires SignedStrictArithmetic<T>
    {
        using R  = PromotedValue_t<T, U>;
        R cosine = std::cos(angle);
        R sine   = std::sin(angle);
#ifdef FGM_LEFT_HANDED
        return Matrix3{ T(1), T(0), T(0), T(0), cosine, sine, T(0), -sine, cosine };
#else
        return Matrix3{ T(1), T(0), T(0), T(0), cosine, -sine, T(0), sine, cosine };
#endif
    }


    template <Arithmetic T>
    template <std::floating_point U>
    constexpr Matrix3<T> Matrix3<T>::makeRotationY(U angle) noexcept
        requires SignedStrictArithmetic<T>
    {
        using R  = PromotedValue_t<T, U>;
        R cosine = std::cos(angle);
        R sine   = std::sin(angle);
#ifdef FGM_LEFT_HANDED
        return Matrix3{ cosine, T(0), -sine, T(0), T(1), T(0), sine, T(0), cosine };
#else
        return Matrix3{ cosine, T(0), sine, T(0), T(1), T(0), -sine, T(0), cosine };
#endif
    }


    template <Arithmetic T>
    template <std::floating_point U>
    constexpr Matrix3<T> Matrix3<T>::makeRotationZ(U angle) noexcept
        requires SignedStrictArithmetic<T>
    {
        using R  = PromotedValue_t<T, U>;
        R cosine = std::cos(angle);
        R sine   = std::sin(angle);

#ifdef FGM_LEFT_HANDED
        return Matrix3{ cosine, sine, T(0), -sine, cosine, T(0), T(0), T(0), T(1) };
#else
        return Matrix3{ cosine, -sine, T(0), sine, cosine, T(0), T(0), T(0), T(1) };
#endif
    }


    template <Arithmetic T>
    constexpr Matrix3<T> Matrix3<T>::makeScale(T scale) noexcept
        requires StrictArithmetic<T>
    {
        return Matrix3{ scale, T(0), T(0), T(0), scale, T(0), T(0), T(0), scale };
    }


    template <Arithmetic T>
    constexpr Matrix3<T> Matrix3<T>::makeScale(T scaleX, T scaleY, T scaleZ) noexcept
        requires StrictArithmetic<T>
    {
        return Matrix3{ scaleX, T(0), T(0), T(0), scaleY, T(0), T(0), T(0), scaleZ };
    }

} // namespace fgm



#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
