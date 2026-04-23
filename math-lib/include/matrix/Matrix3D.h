#pragma once
/**
 * @file Matrix3D.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 15, 2026
 *
 * @brief Templated 3x3 Matrix supporting integral, floating-point, and boolean types.
 *
 * @details Provide high-performance 3x3 matrix implementation with SIMD acceleration
 *          and support for element-wise operations.
 *
 * @note Arithmetic operations are limited to numeric types via `StrictArithmetic` concept.
 * @note Matrices utilize a strict column-major internal memory layout. To align with standard mathematical notations,
 *       scalar constructors accept elements in row-major reading order. Vector-based constructors and array-style
 *       access (operator[]) operate directly on columns.
 * @note FGM uses **Right-Handed** coordinate system by default. To use **Left-Handed** coordinate system define
 *       `FGM_LEFT_HANDED` preprocessor macro.
 *
 * @par Configuration
 *      Define `FORCE_SCALAR` to turn off SIMD which is on by default on supported hardware.
 *      Define `FGM_LEFT_HANDED` to configure library to use left-handed coordinated system.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "vector/Vector3D.h"

#include <cstddef>

namespace fgm
{
    template <Arithmetic T>
    struct Matrix3D
    {
        /**
         * @addtogroup FGM_Mat3x3_Members
         * @{
         */

        using value_type = T; ///< The numeric type of the vector components.

        static constexpr std::size_t columns = 3; ///< Matrix column count.
        static constexpr std::size_t rows = 3; ///< Matrix row count.

        /** @} */

    //private:
    //    union {
    //        T elements[3][3];
    //        Vector3D<T> columns[3];
    //    };

    public:
        /**
         * @addtogroup FGM_Mat3x3_Init
         * @{
         */

        /** @brief Initialize a 3x3 identity matrix. */
        [[nodiscard]] constexpr Matrix3D() noexcept;


        /**
         * @brief Initialize a 3x3 matrix from the passed-in scalar elements.
         *
         * @param[in] m00 The element to insert into row one, column one.
         * @param[in] m01 The element to insert into row one, column two.
         * @param[in] m02 The element to insert into row one, column three.
         * @param[in] m10 The element to insert into row two, column one.
         * @param[in] m11 The element to insert into row two, column two.
         * @param[in] m12 The element to insert into row two, column three.
         * @param[in] m20 The element to insert into row three, column one.
         * @param[in] m21 The element to insert into row three, column two.
         * @param[in] m22 The element to insert into row three, column three.
         */
        [[nodiscard]] constexpr Matrix3D(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22) noexcept;


        /**
         * @brief Initialize a 3x3 matrix from the passed-in vectors as columns.
         *
         * @param[in] col0 The 3D-vector to use as the first column entry.
         * @param[in] col1 The 3D-vector to use as the second column entry.
         * @param[in] col2 The 3D-vector to use as the third column entry.
         */
        [[nodiscard]] constexpr Matrix3D(const Vector3D<T>& col0, const Vector3D<T>& col1,
                                         const Vector3D<T>& col2) noexcept;


        /**
         * @brief Initialize a diagonal matrix from the passed-in scalar entries.
         *        All non-diagonal elements are initialized to zero.
         *
         * @param[in] d0 The first diagonal entry of the matrix (m00).
         * @param[in] d1 The second diagonal entry of the matrix (m11).
         * @param[in] d2 The third diagonal entry of the matrix (m11).
         */
        [[nodiscard]] constexpr Matrix3D(T d0, T d1, T d2) noexcept;


        /**
         * @brief Initialize @ref Matrix3D from another @ref Matrix3D of a different type.
         *
         * @tparam U Numeric type of the source matrix.
         *
         * @param[in] other The source matrix to be converted.
         */
        template <Arithmetic U>
        [[nodiscard]] explicit constexpr Matrix3D(const Matrix3D<U>& other) noexcept;


        /**
         * @brief Access the column vector at the specified location.
         *        Provide read-write access to the element.
         *
         * @param[in] col The column index of the matrix.
         *
         * @return A reference to the column vector.
         */
        [[nodiscard]] constexpr Vector3D<T>& operator[](std::size_t col) noexcept;


        /**
         * @brief Access the column vector at the specified location (read-only).
         *
         * @param[in] col The column index of the matrix.
         *
         * @return A const reference to the column vector.
         */
        [[nodiscard]] constexpr const Vector3D<T>& operator[](std::size_t col) const noexcept;


        /**
         * @brief Access the element at the specified row, column index.
         *        Provide read-write access to the element.
         *
         * @param[in] row The row index of the matrix entry.
         * @param[in] col The column index of the matrix entry.
         *
         * @return A reference to the element at row, col.
         */
        [[nodiscard]] constexpr T& operator()(std::size_t row, std::size_t col) noexcept;


        /**
         * @brief Access the element at the specified row, column index (read-only).
         *
         * @param[in] row The row index of the matrix entry.
         * @param[in] col The column index of the matrix entry.
         *
         * @return A const reference to the element at row, col.
         */
        [[nodiscard]] constexpr const T& operator()(std::size_t row, std::size_t col) const noexcept;

        /** @} */



        // template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>> // Added 'typename' and ', int'
        // Matrix3D(const Matrix3D<S>& other)
        //{
        //	columns[0] = Vector3D<T>(other[0]);
        //	columns[1] = Vector3D<T>(other[1]);
        //	columns[2] = Vector3D<T>(other[2]);
        // }


        //    Vector3D<T>& operator[](size_t index);
        //    const Vector3D<T>& operator[](size_t index) const;

        //    T& operator()(size_t row, size_t col);
        //    const T& operator()(size_t row, size_t col) const;


        //    // Math Operators
        //    template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        //    auto operator+(const Matrix3D<S>& other) const -> Matrix3D<std::common_type_t<T, S>>;

        //    template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        //    Matrix3D& operator+=(const Matrix3D<S>& other);


        //    template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        //    auto operator-(const Matrix3D<S>& other) const -> Matrix3D<std::common_type_t<T, S>>;

        //    template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        //    Matrix3D& operator-=(const Matrix3D<S>& other);


        //    template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        //    auto operator*(const S& scalar) const -> Matrix3D<std::common_type_t<T, S>>;

        //    template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        //    Matrix3D& operator*=(const S& scalar);


        //    template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        //    auto operator*(const Vector3D<S>& vec) const -> Vector3D<std::common_type_t<T, S>>;


        //    template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        //    auto operator*(const Matrix3D<S>& other) const -> Matrix3D<std::common_type_t<T, S>>;

        //    /**
        //     * Multiplies a matrix by a matrix with *= operator.
        //     * NOTE: Not recommended for game engine, since it involves object copying.
        //     * RECOMMENDED: Use Mat * Mat
        //     * @tparam S Type of the other Matrix
        //     * @param other The matrix to be multiplied with.
        //     * @return Matrix on which *= is called, but with new values
        //     */
        //    template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        //    Matrix3D& operator*=(const Matrix3D<S>& other);


        //    template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        //    auto operator/(const S& scalar) const -> Matrix3D<std::common_type_t<T, S>>;

        //    template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        //    Matrix3D& operator/=(const S& scalar);

        //    // Determinants
        //    // Calculates the determinant for the current Matrix3D.
        //    T determinant() const;

        //    // Static wrapper for Matrix 3D determinants.
        //    static T determinant(const Matrix3D& matrix);

        //    // Transpose
        //    Matrix3D transpose() const;

        //    static Matrix3D transpose(const Matrix3D& matrix);

        //    // Matrix Inverse
        //    Matrix3D inverse() const;

        //    static Matrix3D inverse(const Matrix3D& matrix);

    private:
        Vector3D<T> _data[columns];
    };

    // template <typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<T>>,
    //           typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    // auto operator*(const S& scalar, const Matrix3D<T>& matrix) -> Matrix3D<std::common_type_t<T, S>>;

    ///**
    // * Multiplies a Vector3D by a Matrix3D.
    // * NOTE: This operation transposes the 3x1 vector to a 1x3 vector(matrix), and may not be desirable in engine
    // code.
    // * @tparam T Type for matrix values
    // * @tparam S Type for vector values
    // * @param vec vector to be multiplied.
    // * @param mat matrix to be multiplied against.
    // * @return a new Vector3D transposed(row major form)
    // */
    // template <typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<T>>,
    //          typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    // auto operator*(const Vector3D<S>& vec, const Matrix3D<T>& mat) -> Vector3D<std::common_type_t<T, S>>;

    ///**
    // * Multiplies a Vector3D by a Matrix3D.
    // * NOTE: This operation transposes the 3x1 vector to a 1x3 vector(matrix), and may not be desirable in engine
    // code.
    // * NOTE: This operation returns a new vector so it is strictly for testing purposes and completeness and is
    // not
    // * desirable to be used in game engine.
    // * @tparam T Type for matrix values
    // * @tparam S Type for vector values
    // * @param vec vector to be multiplied.
    // * @param mat matrix to be multiplied against.
    // * @return the passed in vector
    // */
    // template <typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<T>>,
    //          typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    // auto operator*=(Vector3D<S>& vec, const Matrix3D<T>& mat) -> Vector3D<std::common_type_t<T, S>>;




}; // namespace fgm

#include "Matrix3D.tpp"