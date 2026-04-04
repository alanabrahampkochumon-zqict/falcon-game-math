#pragma once
/**
 * @file Matrix2D.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 30, 2026
 *
 * @brief Templated 2x2 Matrix supporting integral, floating-point, and boolean types.
 *
 * @details Provide high-performance 2x2 matrix implementation with SIMD acceleration
 *          and support for component-wise operations.
 *
 * @note Arithmetic operations are limited to numeric types via `StrictArithmetic` concept.
 * @note Matrices utilize a strict column-major internal memory layout. To align with standard mathematical notations,
 *       scalar constructors accept elements in row-major reading order. Vector-based constructors and array-style access
 *       (operator[]) operate directly on columns.
 *
 * @par Configuration
 * Define `FORCE_SCALAR` to turn off SIMD which is on by default on supported hardware.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "vector/Vector2D.h"

#include <cstddef>
#include <type_traits>

namespace fgm
{
    template <Arithmetic T>
    struct Matrix2D
    {

        /**
         * @addtogroup FGM_Mat2x2_Members
         * @{
         */

        static constexpr std::size_t columns = 2;
        static constexpr std::size_t rows = 2;

        using value_type = T;

    private:
        union {
            Vector2D<T> columnVectors[columns]; ///< 2D vector composition of matrix columns.
            T elements[columns][rows];          ///< Elemental composition of matrix, stored in column-major form.
        };

        /** @} */



    public:
        /**
         * @addtogroup FGM_Mat2x2_Init
         * @{
         */

        /** @brief Initialize a 2x2 identity matrix. */
        [[nodiscard]] constexpr Matrix2D() noexcept;


        /**
         * @brief Initialize a 2x2 matrix from the passed-in scalar elements.
         *
         * @param[in] v_0_0 The element to insert into row one, column one.
         * @param[in] v_0_1 The element to insert into row one, column two.
         * @param[in] v_1_0 The element to insert into row two, column one.
         * @param[in] v_1_1 The element to insert into row two, column two.
         */
        [[nodiscard]] constexpr Matrix2D(T v_0_0, T v_0_1, T v_1_0, T v_1_1) noexcept;


        /**
         * @brief Initialize a 2x2 matrix from the passed-in vectors as columns.
         *
         * @param[in] col0 The 2D-vector to use as the first column entry.
         * @param[in] col1 The 2D-vector to use as the second column entry.
         */
        [[nodiscard]] constexpr Matrix2D(const Vector2D<T>& col0, const Vector2D<T>& col1) noexcept;


        /**
         * @brief Initialize a diagonal matrix from the passed-in scalar entries.
         * All non-diagonal elements are initialized to zero.
         *
         * @param[in] d0 The first diagonal entry of the matrix (v_0_0).
         * @param[in] d1 The second diagonal entry of the matrix (v_1_1).
         */
        [[nodiscard]] constexpr Matrix2D(T d0, T d1) noexcept;


        /**
         * @brief Initialize @ref Matrix2D from another @ref Matrix2D of a different type.
         *
         * @tparam U Numeric type of the source matrix.
         *
         * @param[in] other The source matrix to be converted.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr Matrix2D(const Matrix2D<U>& other) noexcept;

        constexpr Vector2D<T>& operator[](size_t index) noexcept;
        constexpr const Vector2D<T>& operator[](size_t index) const noexcept;

        constexpr T& operator()(size_t row, size_t col) noexcept;
        constexpr const T& operator()(size_t row, size_t col) const noexcept;

        /** @} */

        // Math Operators
        Matrix2D operator+(const Matrix2D& other) const;
        Matrix2D& operator+=(const Matrix2D& other);

        Matrix2D operator-(const Matrix2D& other) const;
        Matrix2D& operator-=(const Matrix2D& other);

        template <StrictArithmetic S>
        Matrix2D operator*(const S& scalar) const;

        template <StrictArithmetic S>
        Matrix2D& operator*=(const S& scalar);

        template <StrictArithmetic S>
        Vector2D<T> operator*(const Vector2D<S>& vec) const;

        template <StrictArithmetic S>
        Matrix2D<T> operator*(const Matrix2D<S>& other) const;

        /**
         * Multiplies a matrix by a matrix with *= operator.
         * @tparam S Type of the other Matrix
         * @param other The matrix to be multiplied with.
         * @return Matrix on which *= is called, but with new values
         */
        template <StrictArithmetic S>
        Matrix2D& operator*=(const Matrix2D<S>& other);

        template <StrictArithmetic S>
        Matrix2D operator/(const S& scalar) const;
        template <StrictArithmetic S>
        Matrix2D& operator/=(const S& scalar);

        // Determinants
        // Calculates the determinant for the current Matrix2D.
        T determinant() const;

        // Static wrapper for Matrix 3D determinants.
        static T determinant(const Matrix2D<T>& matrix);

        // Transpose
        Matrix2D transpose() const;

        static Matrix2D transpose(const Matrix2D& matrix);

        // Matrix Inverse
        Matrix2D inverse() const;

        static Matrix2D inverse(const Matrix2D& matrix);
    };

    template <StrictArithmetic T, StrictArithmetic S>
    Matrix2D<T> operator*(const S& scalar, const Matrix2D<T>& matrix);

    /**
     * Multiplies a Vector2D by a Matrix2D.
     * NOTE: This operation transposes the 3x1 vector to a 1x3 vector(matrix), and may not be desirable in engine code.
     * @tparam T Type for matrix values
     * @tparam S Type for vector values
     * @param vec vector to be multiplied.
     * @param mat matrix to be multiplied against.
     * @return a new Vector2D transposed(row major form)
     */
    template <StrictArithmetic T, StrictArithmetic S>
    Vector2D<T> operator*(const Vector2D<S>& vec, const Matrix2D<T>& mat);

    /**
     * Multiplies a Vector2D by a Matrix2D.
     * NOTE: This operation transposes the 3x1 vector to a 1x3 vector(matrix), and may not be desirable in engine code.
     * NOTE: This operation returns a new vector so it is strictly for testing purposes and completeness and is not
     * desirable to be used in game engine.
     * @tparam T Type for matrix values
     * @tparam S Type for vector values
     * @param vec vector to be multiplied.
     * @param mat matrix to be multiplied against.
     * @return the passed in vector
     */
    template <StrictArithmetic T, StrictArithmetic S>
    Vector2D<T> operator*=(Vector2D<S>& vec, const Matrix2D<T>& mat);


} // namespace fgm

#include "Matrix2D.tpp"