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
        Matrix2D();
        Matrix2D(T v_0_0, T v_0_1, T v_1_0, T v_1_1);
        Matrix2D(Vector2D<T> col0, Vector2D<T> col1);

        template <Arithmetic S>
        Matrix2D(const Matrix2D& other);

        Vector2D<T>& operator[](size_t index);
        const Vector2D<T>& operator[](size_t index) const;

        T& operator()(size_t row, size_t col);
        const T& operator()(size_t row, size_t col) const;

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