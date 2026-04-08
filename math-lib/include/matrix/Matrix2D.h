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
         * @param[in] m00 The element to insert into row one, column one.
         * @param[in] m01 The element to insert into row one, column two.
         * @param[in] m10 The element to insert into row two, column one.
         * @param[in] m11 The element to insert into row two, column two.
         */
        [[nodiscard]] constexpr Matrix2D(T m00, T m01, T m10, T m11) noexcept;


        /**
         * @brief Initialize a 2x2 matrix from the passed-in vectors as columns.
         *
         * @param[in] col0 The 2D-vector to use as the first column entry.
         * @param[in] col1 The 2D-vector to use as the second column entry.
         */
        [[nodiscard]] constexpr Matrix2D(const Vector2D<T>& col0, const Vector2D<T>& col1) noexcept;


        /**
         * @brief Initialize a diagonal matrix from the passed-in scalar entries.
         *        All non-diagonal elements are initialized to zero.
         *
         * @param[in] d0 The first diagonal entry of the matrix (m00).
         * @param[in] d1 The second diagonal entry of the matrix (m11).
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


        /**
         * @brief Access the column vector at the specified location.
         *        Provide read-write access to the element.
         *
         * @param[in] col The column index of the matrix.
         *
         * @return A reference to the column vector.
         */
        [[nodiscard]] constexpr Vector2D<T>& operator[](std::size_t col) noexcept;


        /**
         * @brief Access the column vector at the specified location (read-only).
         *
         * @param[in] col The column index of the matrix.
         *
         * @return A const reference to the column vector.
         */
        [[nodiscard]] constexpr const Vector2D<T>& operator[](std::size_t col) const noexcept;


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



        /**
         * @addtogroup FGM_Vec3_Equality
         * @{
         */

        /***************************************
         *                                     *
         *             EQUALITY                *
         *                                     *
         ***************************************/

        /**
         * @brief Compare all components of this matrix for equality with another matrix.
         *        Perform a component-wise comparison and returns true only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr bool allEq(const Matrix2D<U>& rhs,
                                           double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                               ? Config::DOUBLE_EPSILON
                                               : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all components of a matrix for equality with another matrix.
         *        Perform a component-wise comparison and returns true only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The matrix to compare.
         * @param[in] rhs     The matrix to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return True if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr static bool allEq(const Matrix2D& lhs, const Matrix2D<U>& rhs,
                                                  double epsilon = (std::is_same_v<T, double> ||
                                                                    std::is_same_v<U, double>)
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) noexcept;

        /**
         * @brief Compare all components of this matrix for equality with another matrix.
         *        Perform a component-wise comparison and returns true if any corresponding elements differ by more
         *        than @p epsilon.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The matrix to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr bool allNeq(const Matrix2D<U>& rhs,
                                           double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                               ? Config::DOUBLE_EPSILON
                                               : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all components of this matrix for equality with another matrix.
         *        Perform a component-wise comparison and returns true if any corresponding elements differ by more
         *        than @p epsilon.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The matrix to compare.
         * @param[in] rhs     The matrix to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr static bool allNeq(const Matrix2D& lhs, const Matrix2D<U>& rhs,
                                                  double epsilon = (std::is_same_v<T, double> ||
                                                                    std::is_same_v<U, double>)
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) noexcept;


        /**
         * @copybrief allEq(const Matrix2D<U>&, double) const noexcept
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The matrix to compare against.
         *
         * @return True if all components are equivalent within the default epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr bool operator==(const Matrix2D<U>& rhs) const noexcept;


        /**
         * @copybrief allNeq(const Vector2D<U>&, double) const noexcept
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The matrix to compare against.
         *
         * @return True if any of the components are not equivalent within the default epsilon.
         */
        //template <Arithmetic U>
        //[[nodiscard]] constexpr bool operator!=(const Matrix2D<U>& rhs) const noexcept;

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


    private:
        Vector2D<T> _data[columns];
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