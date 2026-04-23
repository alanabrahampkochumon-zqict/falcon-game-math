#pragma once
/**
 * @file Matrix3D.tpp
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
    constexpr Matrix3D<T>::Matrix3D() noexcept
        : _data{ Vector3D{ T(1), T(0), T(0) }, Vector3D{ T(0), T(1), T(0) }, Vector3D{ T(0), T(0), T(1) } }
    {}


    template <Arithmetic T>
    constexpr Matrix3D<T>::Matrix3D(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22) noexcept
        : _data{ Vector3D{ T(m00), T(m10), T(m20) }, Vector3D{ T(m01), T(m11), T(m21) },
                 Vector3D{ T(m02), T(m12), T(m22) } }
    {}


    template <Arithmetic T>
    constexpr Matrix3D<T>::Matrix3D(const Vector3D<T>& col0, const Vector3D<T>& col1, const Vector3D<T>& col2) noexcept
        : _data{ col0, col1, col2 }
    {}


    template <Arithmetic T>
    constexpr Matrix3D<T>::Matrix3D(T d0, T d1, T d2) noexcept
        : _data{ Vector3D{ T(d0), T(0), T(0) }, Vector3D{ T(0), T(d1), T(0) }, Vector3D{ T(0), T(0), T(d2) } }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Matrix3D<T>::Matrix3D(const Matrix3D<U>& other) noexcept
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
    constexpr Vector3D<T>& Matrix3D<T>::operator[](std::size_t col) noexcept
    {
        return _data[col];
    }


    template <Arithmetic T>
    constexpr const Vector3D<T>& Matrix3D<T>::operator[](std::size_t col) const noexcept
    {
        return _data[col];
    }


    template <Arithmetic T>
    constexpr T& Matrix3D<T>::operator()(std::size_t row, std::size_t col) noexcept
    {
        return _data[col][row];
    }


    template <Arithmetic T>
    constexpr const T& Matrix3D<T>::operator()(std::size_t row, std::size_t col) const noexcept
    {
        return _data[col][row];
    }



    /**************************************
     *                                    *
     *             CONSTANTS              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr Matrix3D<T> Matrix3D<T>::eye() noexcept
    {
        return Matrix3D(T(1), T(1), T(1));
    }


    template <Arithmetic T>
    constexpr Matrix3D<T> Matrix3D<T>::zero() noexcept
    {
        return Matrix3D(T(0), T(0), T(0));
    }


    // template <typename T>
    // Matrix3D<T>::Matrix3D()
    //{
    //     // Column Major
    //     // First Column
    //     elements[0][0] = T(1);
    //     elements[0][1] = T(0);
    //     elements[0][2] = T(0);

    //    // Second Column
    //    elements[1][0] = T(0);
    //    elements[1][1] = T(1);
    //    elements[1][2] = T(0);

    //    // Third Column
    //    elements[2][0] = T(0);
    //    elements[2][1] = T(0);
    //    elements[2][2] = T(1);
    //}

    // template <typename T>
    // Matrix3D<T>::Matrix3D(T v_0_0, T v_0_1, T v_0_2, T v_1_0, T v_1_1, T v_1_2, T v_2_0, T v_2_1, T v_2_2)
    //{
    //     // Column Major
    //     // First Column
    //     elements[0][0] = v_0_0;
    //     elements[0][1] = v_1_0;
    //     elements[0][2] = v_2_0;

    //    // Second Column
    //    elements[1][0] = v_0_1;
    //    elements[1][1] = v_1_1;
    //    elements[1][2] = v_2_1;

    //    // Third Column
    //    elements[2][0] = v_0_2;
    //    elements[2][1] = v_1_2;
    //    elements[2][2] = v_2_2;
    //}

    // template <typename T>
    // Matrix3D<T>::Matrix3D(Vector3D<T> col0, Vector3D<T> col1, Vector3D<T> col2)
    //{
    //     columns[0] = col0;
    //     columns[1] = col1;
    //     columns[2] = col2;
    // }

    // template <typename T>
    // template <typename S, typename>
    // Matrix3D<T>::Matrix3D(const Matrix3D<S>& other)
    //{
    //     columns[0] = Vector3D<T>(other[0]);
    //     columns[1] = Vector3D<T>(other[1]);
    //     columns[2] = Vector3D<T>(other[2]);
    // }

    ///**
    // * Stores a <Vector3D> instance to the specified column of the matrix.
    // * @param index column index of the matrix.
    // * @return alias to the layout of the memory that stores the vector.
    // */
    // template <typename T>
    // Vector3D<T>& Matrix3D<T>::operator[](size_t index)
    //{
    //    return columns[index];
    //}

    ///**
    // * Retrieves <Vector3D> instance from a specific column of the matrix.
    // * @param index column index of the matrix.
    // * @return alias to the layout of the memory that stores the vector.
    // */
    // template <typename T>
    // const Vector3D<T>& Matrix3D<T>::operator[](size_t index) const
    //{
    //    return columns[index];
    //}

    // template <typename T>
    // T& Matrix3D<T>::operator()(size_t row, size_t col)
    //{
    //     // We swap the rows and columns since internally we use column major order.
    //     return elements[col][row];
    // }

    // template <typename T>
    // const T& Matrix3D<T>::operator()(size_t row, size_t col) const
    //{
    //     // We swap the rows and columns since internally we use column major order.
    //     return elements[col][row];
    // }

    /*************************************
     *                                   *
     *         MATH OPERATIONS           *
     *                                   *
     *************************************/

    //    template <typename T>
    //    template <typename S, typename>
    //    auto Matrix3D<T>::operator+(const Matrix3D<S>& other) const -> Matrix3D<std::common_type_t<T, S>>
    //    {
    //        // Commented out for profiling
    //        // Since `this` elements[0] is the first column, we need to take the rows first (this[c][r]) and add them
    //        to the
    //        // r,c value of other to get the r,c value for the new matrix return Matrix3D(
    //        //	// First Row
    //        //	elements[0][0] + other(0, 0), elements[1][0] + other(0, 1), elements[2][0] + other(0, 2),
    //        //	// Second Row
    //        //	elements[0][1] + other(1, 0), elements[1][1] + other(1, 1), elements[2][1] + other(1,2),
    //        //	// Third Row
    //        //	elements[0][2] + other(2, 0), elements[1][2] + other(2, 1), elements[2][2] + other(2,2)
    //        //);
    //
    //        // Using Vector3D ops
    //        using R = std::common_type_t<T, S>;
    //        return Matrix3D<R>(columns[0] + other[0], columns[1] + other[1], columns[2] + other[2]);
    //    }
    //
    //    template <typename T>
    //    template <typename S, typename>
    //    Matrix3D<T>& Matrix3D<T>::operator+=(const Matrix3D<S>& other)
    //    {
    //        // NOTE: Commented out for profiling
    //        //// First Row
    //        // elements[0][0] += other(0, 0);
    //        // elements[1][0] += other(0, 1);
    //        // elements[2][0] += other(0, 2);
    //        //// Second Row
    //        // elements[0][1] += other(1, 0);
    //        // elements[1][1] += other(1, 1);
    //        // elements[2][1] += other(1, 2);
    //        //// Third Row
    //        // elements[0][2] += other(2, 0);
    //        // elements[1][2] += other(2, 1);
    //        // elements[2][2] += other(2, 2);
    //
    //        columns[0] += other[0];
    //        columns[1] += other[1];
    //        columns[2] += other[2];
    //
    //        return *this;
    //    }
    //
    //    template <typename T>
    //    template <typename S, typename>
    //    auto Matrix3D<T>::operator-(const Matrix3D<S>& other) const -> Matrix3D<std::common_type_t<T, S>>
    //    {
    //        // NOTE: Commented out for profiling
    //        // Since `this` elements[0] is the first column, we need to take the rows first (this[c][r]) and add them
    //        to the
    //        // r,c value of other to get the r,c value for the new matrix return Matrix3D(
    //        //     // First Row
    //        //     elements[0][0] - other(0, 0), elements[1][0] - other(0, 1), elements[2][0] - other(0, 2),
    //        //     // Second Row
    //        //     elements[0][1] - other(1, 0), elements[1][1] - other(1, 1), elements[2][1] - other(1, 2),
    //        //     // Third Row
    //        //     elements[0][2] - other(2, 0), elements[1][2] - other(2, 1), elements[2][2] - other(2, 2));
    //
    //        // Using Vector3D ops
    //        using R = std::common_type_t<T, S>;
    //        return Matrix3D<R>(columns[0] - other[0], columns[1] - other[1], columns[2] - other[2]);
    //    }
    //
    //    template <typename T>
    //    template <typename S, typename>
    //    Matrix3D<T>& Matrix3D<T>::operator-=(const Matrix3D<S>& other)
    //    {
    //        // NOTE: Commented out for profiling
    //        //// First Row
    //        // elements[0][0] -= other(0, 0);
    //        // elements[1][0] -= other(0, 1);
    //        // elements[2][0] -= other(0, 2);
    //        //// Second Row
    //        // elements[0][1] -= other(1, 0);
    //        // elements[1][1] -= other(1, 1);
    //        // elements[2][1] -= other(1, 2);
    //        //// Third Row
    //        // elements[0][2] -= other(2, 0);
    //        // elements[1][2] -= other(2, 1);
    //        // elements[2][2] -= other(2, 2);
    //
    //        // Using Vector3D ops
    //        columns[0] -= other[0];
    //        columns[1] -= other[1];
    //        columns[2] -= other[2];
    //
    //        return *this;
    //    }
    //
    //    template <typename T>
    //    template <typename S, typename>
    //    auto Matrix3D<T>::operator*(const S& scalar) const -> Matrix3D<std::common_type_t<T, S>>
    //    {
    //        using R = std::common_type_t<T, S>;
    //        return Matrix3D<R>(columns[0] * scalar, columns[1] * scalar, columns[2] * scalar);
    //    }
    //
    //    template <typename T, typename S, typename, typename>
    //    auto operator*(const S& scalar, const Matrix3D<T>& matrix) -> Matrix3D<std::common_type_t<T, S>>
    //    {
    //        return Matrix3D(matrix[0] * scalar, matrix[1] * scalar, matrix[2] * scalar);
    //    }
    //
    //    template <typename T, typename S, typename, typename>
    //    auto operator*(const Vector3D<S>& vec, const Matrix3D<T>& mat) -> Vector3D<std::common_type_t<T, S>>
    //    {
    //        return Vector3D(Vector3D<T>::dot(vec, mat[0]), Vector3D<T>::dot(vec, mat[1]), Vector3D<T>::dot(vec,
    //        mat[2]));
    //    }
    //
    //    template <typename T, typename S, typename, typename>
    //    auto operator*=(Vector3D<S>& vec, const Matrix3D<T>& mat) -> Vector3D<std::common_type_t<T, S>>
    //    {
    //        vec = Vector3D(Vector3D<T>::dot(vec, mat[0]), Vector3D<T>::dot(vec, mat[1]), Vector3D<T>::dot(vec,
    //        mat[2])); return vec;
    //    }
    //
    //    template <typename T>
    //    template <typename S, typename>
    //    Matrix3D<T>& Matrix3D<T>::operator*=(const S& scalar)
    //    {
    //        columns[0] = columns[0] * scalar;
    //        columns[1] = columns[1] * scalar;
    //        columns[2] = columns[2] * scalar;
    //        return *this;
    //    }
    //
    //    template <typename T>
    //    template <typename S, typename>
    //    auto Matrix3D<T>::operator*(const Vector3D<S>& vec) const -> Vector3D<std::common_type_t<T, S>>
    //    {
    //        return Vector3D(elements[0][0] * vec.x() + elements[1][0] * vec.y() + elements[2][0] * vec.z(), // First
    //        Row * Vec
    //                        elements[0][1] * vec.x() + elements[1][1] * vec.y() + elements[2][1] * vec.z(), // Second
    //                        Row * Vec elements[0][2] * vec.x() + elements[1][2] * vec.y() + elements[2][2] * vec.z()
    //                        // Third Row * Vec
    //        );
    //    }
    //
    //    template <typename T>
    //    template <typename S, typename>
    //    auto Matrix3D<T>::operator*(const Matrix3D<S>& other) const -> Matrix3D<std::common_type_t<T, S>>
    //    {
    //        // TODO: Profiling
    //        // return Matrix3D(
    //        //	// First Row * Columns
    //        //	elements[0][0] * other(0, 0) + elements[1][0] * other(1, 0) + elements[2][0] * other(2, 0),
    //        elements[0][0] *
    //        // other(0, 1) + elements[1][0] * other(1, 1) + elements[2][0] * other(2, 1), elements[0][0] * other(0, 2)
    //        +
    //        // elements[1][0] * other(1, 2) + elements[2][0] * other(2, 2),
    //        //	// Second Row * Columns
    //        //	elements[0][1] * other(0, 0) + elements[1][1] * other(1, 0) + elements[2][1] * other(2, 0),
    //        elements[0][1] *
    //        // other(0, 1) + elements[1][1] * other(1, 1) + elements[2][1] * other(2, 1), elements[0][1] * other(0, 2)
    //        +
    //        // elements[1][1] * other(1, 2) + elements[2][1] * other(2, 2),
    //        //	// Third Row * Columns
    //        //	elements[0][2] * other(0, 0) + elements[1][2] * other(1, 0) + elements[2][2] * other(2, 0),
    //        elements[0][2] *
    //        // other(0, 1) + elements[1][2] * other(1, 1) + elements[2][2] * other(2, 1), elements[0][2] * other(0, 2)
    //        +
    //        // elements[1][2] * other(1, 2) + elements[2][2] * other(2, 2)
    //        //);
    //        using R = std::common_type_t<T, S>;
    //        return Matrix3D<R>(
    //            // Matrix * First Column Vector
    //            (*this) * other[0],
    //            // Matrix * Second Column Vector
    //            (*this) * other[1],
    //            // Matrix * Third Column Vector
    //            (*this) * other[2]);
    //    }
    //
    //    template <typename T>
    //    template <typename S, typename>
    //    Matrix3D<T>& Matrix3D<T>::operator*=(const Matrix3D<S>& other)
    //    {
    //        return *this = (*this) * other;
    //    }
    //
    // #pragma warning(push)
    // #pragma warning(disable : 4723) // Suppress division by zero
    //    template <typename T>
    //    template <typename S, typename>
    //    auto Matrix3D<T>::operator/(const S& scalar) const -> Matrix3D<std::common_type_t<T, S>>
    //    {
    //        using R = std::common_type_t<T, S>;
    //        R factor = R(1) / static_cast<R>(scalar);
    //        return Matrix3D<R>(columns[0] * factor, columns[1] * factor, columns[2] * factor);
    //    }
    // #pragma warning(pop)
    //
    //    template <typename T>
    //    template <typename S, typename>
    //    Matrix3D<T>& Matrix3D<T>::operator/=(const S& scalar)
    //    {
    //        using R = std::common_type_t<T, S>;
    //        R factor = R(1) / static_cast<R>(scalar);
    //
    //        columns[0] *= factor;
    //        columns[1] *= factor;
    //        columns[2] *= factor;
    //
    //        return *this;
    //    }
    //
    //    template <typename T>
    //    T Matrix3D<T>::determinant() const
    //    {
    //        // Evaluated along first column
    //        return elements[0][0] * (elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1]) -
    //            elements[0][1] * (elements[1][0] * elements[2][2] - elements[1][2] * elements[2][0]) +
    //            elements[0][2] * (elements[1][0] * elements[2][1] - elements[1][1] * elements[2][0]);
    //    }
    //
    //    template <typename T>
    //    T Matrix3D<T>::determinant(const Matrix3D<T>& matrix)
    //    {
    //        return matrix.determinant();
    //    }
    //
    //    template <typename T>
    //    Matrix3D<T> Matrix3D<T>::transpose() const
    //    {
    //        return Matrix3D(elements[0][0], elements[0][1], elements[0][2], elements[1][0], elements[1][1],
    //        elements[1][2],
    //                        elements[2][0], elements[2][1], elements[2][2]);
    //    }
    //
    //    template <typename T>
    //    Matrix3D<T> Matrix3D<T>::transpose(const Matrix3D<T>& matrix)
    //    {
    //        return matrix.transpose();
    //    }
    //
    //    template <typename T>
    //    Matrix3D<T> Matrix3D<T>::inverse() const
    //    {
    //        const T det = this->determinant();
    //        // Handle Non-Invertible Matrices
    //        if (std::abs(det) <= 1e-6f)
    //            return Matrix3D();
    //
    //        // 1 / det(M) * [b cross c, c cross a, a cross b]^T
    //        const T factor = T(1) / det;
    //
    //        const Vector3D<T> col1 = columns[1].cross(columns[2]);
    //        const Vector3D<T> col2 = columns[2].cross(columns[0]);
    //        const Vector3D<T> col3 = columns[0].cross(columns[1]);
    //
    //        return factor *
    //            Matrix3D(col1.x(), col1.y(), col1.z(), col2.x(), col2.y(), col2.z(), col3.x(), col3.y(), col3.z());
    //
    //        // NOTE: Left for profiling
    //        // return factor * Matrix3D<T>(
    //        //	columns[1].cross(columns[2]), // Col 0
    //        //	columns[2].cross(columns[0]), // Col 1
    //        //	columns[0].cross(columns[1]) // Col 2
    //        //).transpose();
    //    }
    //
    //    template <typename T>
    //    Matrix3D<T> Matrix3D<T>::inverse(const Matrix3D& matrix)
    //    {
    //        return matrix.inverse();
    //    }
} // namespace fgm
