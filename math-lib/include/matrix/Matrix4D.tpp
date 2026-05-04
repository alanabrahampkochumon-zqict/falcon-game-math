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


namespace fgm
{
    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Matrix4D<T>::Matrix4D() noexcept
        : _data{ Vector4D{ T(1), T(0), T(0), T(0) }, Vector4D{ T(0), T(1), T(0), T(0) },
                 Vector4D{ T(0), T(0), T(1), T(0) }, Vector4D{ T(0), T(0), T(0), T(1) } }
    {}


    template <Arithmetic T>
    constexpr Matrix4D<T>::Matrix4D(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23,
                                    T m30, T m31, T m32, T m33) noexcept
        : _data{ Vector4D{ T(m00), T(m10), T(m20), T(m30) }, Vector4D{ T(m01), T(m11), T(m21), T(m31) },
                 Vector4D{ T(m02), T(m12), T(m22), T(m32) }, Vector4D{ T(m03), T(m13), T(m23), T(m33) } }
    {}


    template <Arithmetic T>
    constexpr Matrix4D<T>::Matrix4D(const Vector4D<T>& col0, const Vector4D<T>& col1, const Vector4D<T>& col2,
                                    const Vector4D<T>& col3) noexcept
        : _data{ col0, col1, col2, col3 }
    {}


    template <Arithmetic T>
    constexpr Matrix4D<T>::Matrix4D(T d0, T d1, T d2, T d3) noexcept
        : _data{ Vector4D{ T(d0), T(0), T(0), T(0) }, Vector4D{ T(0), T(d1), T(0), T(0) },
                 Vector4D{ T(0), T(0), T(d2), T(0) }, Vector4D{ T(0), T(0), T(0), T(d3) } }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Matrix4D<T>::Matrix4D(const Matrix4D<U>& other) noexcept
    {
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

    template <Arithmetic T>
    constexpr Vector4D<T>& Matrix4D<T>::operator[](std::size_t col) noexcept
    { return _data[col]; }


    template <Arithmetic T>
    constexpr const Vector4D<T>& Matrix4D<T>::operator[](std::size_t col) const noexcept
    { return _data[col]; }


    template <Arithmetic T>
    constexpr T& Matrix4D<T>::operator()(std::size_t row, std::size_t col) noexcept
    { return _data[col][row]; }


    template <Arithmetic T>
    constexpr const T& Matrix4D<T>::operator()(std::size_t row, std::size_t col) const noexcept
    { return _data[col][row]; }



    /**************************************
     *                                    *
     *             CONSTANTS              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr Matrix4D<T> Matrix4D<T>::eye() noexcept
    { return Matrix4D(T(1), T(1), T(1), T(1)); }


    template <Arithmetic T>
    constexpr Matrix4D<T> Matrix4D<T>::zero() noexcept
    { return Matrix4D(T(0), T(0), T(0), T(0)); }



    /***************************************
     *                                     *
     *             EQUALITY                *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix4D<T>::allEq(const Matrix4D<U>& rhs, double epsilon) const noexcept
    {
        // MSVC's constexpr evaluator incorrectly yields true for NaN relational comparisons.
        // To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
        // if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
#ifdef _MSC_VER
        if (std::is_constant_evaluated())
            if (hasNaN() || rhs.hasNaN())
                return false;
#endif
        return _data[0].allEq(rhs[0], epsilon) && _data[1].allEq(rhs[1], epsilon) && _data[2].allEq(rhs[2], epsilon) &&
            _data[3].allEq(rhs[3], epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix4D<T>::allEq(const Matrix4D& lhs, const Matrix4D<U>& rhs, double epsilon) noexcept
    { return lhs.allEq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix4D<T>::anyNeq(const Matrix4D<U>& rhs, double epsilon) const noexcept
    {
        // MSVC's constexpr evaluator incorrectly yields true for NaN relational comparisons.
        // To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
        // if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
#ifdef _MSC_VER
        if (std::is_constant_evaluated())
            if (hasNaN() || rhs.hasNaN())
                return true;
#endif
        return _data[0].anyNeq(rhs[0], epsilon) || _data[1].anyNeq(rhs[1], epsilon) ||
            _data[2].anyNeq(rhs[2], epsilon) || _data[3].anyNeq(rhs[3], epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix4D<T>::anyNeq(const Matrix4D& lhs, const Matrix4D<U>& rhs, double epsilon) noexcept
    { return lhs.anyNeq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix4D<T>::operator==(const Matrix4D<U>& rhs) const noexcept
    { return allEq(rhs); }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Matrix4D<T>::operator!=(const Matrix4D<U>& rhs) const noexcept
    { return anyNeq(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr PromotedMatrix4D<T, U> Matrix4D<T>::operator+(const Matrix4D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return *this;
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    Matrix4D<T>& Matrix4D<T>::operator+=(const Matrix4D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return *this;
    }


    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr bool Matrix4D<T>::hasInf() const noexcept
    { return _data[0].hasInf() || _data[1].hasInf() || _data[2].hasInf() || _data[3].hasInf(); }


    template <Arithmetic T>
    constexpr bool Matrix4D<T>::hasInf(const Matrix4D& mat) noexcept
    { return mat.hasInf(); }


    template <Arithmetic T>
    constexpr bool Matrix4D<T>::hasNaN() const noexcept
    { return _data[0].hasNaN() || _data[1].hasNaN() || _data[2].hasNaN() || _data[3].hasNaN(); }


    template <Arithmetic T>
    constexpr bool Matrix4D<T>::hasNaN(const Matrix4D& mat) noexcept
    { return mat.hasNaN(); }


    //   template <StrictArithmetic T>
    //   Matrix4D<T>::Matrix4D()
    //   {
    //       // First Column
    //       elements[0][0] = 1;
    //       elements[0][1] = 0;
    //       elements[0][2] = 0;
    //       elements[0][3] = 0;
    //
    //       // Second Column
    //       elements[1][0] = 0;
    //       elements[1][1] = 1;
    //       elements[1][2] = 0;
    //       elements[1][3] = 0;
    //
    //       // Third Column
    //       elements[2][0] = 0;
    //       elements[2][1] = 0;
    //       elements[2][2] = 1;
    //       elements[2][3] = 0;
    //
    //       // Fourth Column
    //       elements[3][0] = 0;
    //       elements[3][1] = 0;
    //       elements[3][2] = 0;
    //       elements[3][3] = 1;
    //   }
    //
    //   template <StrictArithmetic T>
    //   Matrix4D<T>::Matrix4D(T v_0_0, T v_0_1, T v_0_2, T v_0_3, T v_1_0, T v_1_1, T v_1_2, T v_1_3, T v_2_0, T v_2_1,
    //                         T v_2_2, T v_2_3, T v_3_0, T v_3_1, T v_3_2, T v_3_3)
    //   {
    //       // First Column
    //       elements[0][0] = v_0_0;
    //       elements[0][1] = v_1_0;
    //       elements[0][2] = v_2_0;
    //       elements[0][3] = v_3_0;
    //
    //       // Second Column
    //       elements[1][0] = v_0_1;
    //       elements[1][1] = v_1_1;
    //       elements[1][2] = v_2_1;
    //       elements[1][3] = v_3_1;
    //
    //       // Third Column
    //       elements[2][0] = v_0_2;
    //       elements[2][1] = v_1_2;
    //       elements[2][2] = v_2_2;
    //       elements[2][3] = v_3_2;
    //
    //       // Fourth Column
    //       elements[3][0] = v_0_3;
    //       elements[3][1] = v_1_3;
    //       elements[3][2] = v_2_3;
    //       elements[3][3] = v_3_3;
    //   }
    //
    //   template <StrictArithmetic T>
    //   Matrix4D<T>::Matrix4D(Vector4D<T> col0, Vector4D<T> col1, Vector4D<T> col2, Vector4D<T> col3)
    //   {
    //       col_vectors[0] = col0;
    //       col_vectors[1] = col1;
    //       col_vectors[2] = col2;
    //       col_vectors[3] = col3;
    //   }
    //
    //   template <StrictArithmetic T>
    //   template <StrictArithmetic U>
    //   Matrix4D<T>::Matrix4D(const Matrix4D<U>& other)
    //   {
    //       col_vectors[0] = Vector4D<T>(other.col_vectors[0]);
    //       col_vectors[1] = Vector4D<T>(other.col_vectors[1]);
    //       col_vectors[2] = Vector4D<T>(other.col_vectors[2]);
    //       col_vectors[3] = Vector4D<T>(other.col_vectors[3]);
    //   }
    //
    //
    //   /*************************************
    //    *                                   *
    //    *            ACCESSORS              *
    //    *                                   *
    //    *************************************/
    //
    //   template <StrictArithmetic T>
    //   Vector4D<T>& Matrix4D<T>::operator[](std::size_t index)
    //   {
    //       return col_vectors[index];
    //   }
    //
    //   template <StrictArithmetic T>
    //   const Vector4D<T>& Matrix4D<T>::operator[](std::size_t index) const
    //   {
    //       return col_vectors[index];
    //   }
    //
    //   template <StrictArithmetic T>
    //   T& Matrix4D<T>::operator()(std::size_t row, std::size_t col)
    //   {
    //       return elements[col][row];
    //   }
    //
    //   template <StrictArithmetic T>
    //   const T& Matrix4D<T>::operator()(std::size_t row, std::size_t col) const
    //   {
    //       return elements[col][row];
    //   }
    //
    //
    //   /*************************************
    //    *                                   *
    //    *      ARITHMETIC OPERATORS         *
    //    *                                   *
    //    *************************************/
    //
    //   template <StrictArithmetic T>
    //   template <StrictArithmetic U>
    //   auto Matrix4D<T>::operator+(const Matrix4D<U>& other) const -> Matrix4D<std::common_type_t<T, U>>
    //   {
    //       using R = std::common_type_t<T, U>;
    //       return Matrix4D<R>(col_vectors[0] + other.col_vectors[0], col_vectors[1] + other.col_vectors[1],
    //                          col_vectors[2] + other.col_vectors[2], col_vectors[3] + other.col_vectors[3]);
    //   }
    //
    //   template <StrictArithmetic T>
    //   template <StrictArithmetic U>
    //   Matrix4D<T>& Matrix4D<T>::operator+=(const Matrix4D<U>& other)
    //   {
    //       col_vectors[0] += other.col_vectors[0];
    //       col_vectors[1] += other.col_vectors[1];
    //       col_vectors[2] += other.col_vectors[2];
    //       col_vectors[3] += other.col_vectors[3];
    //       return *this;
    //   }

} // namespace fgm
