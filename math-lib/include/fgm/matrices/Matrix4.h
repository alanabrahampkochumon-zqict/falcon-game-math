#pragma once
/**
 * @file Matrix4.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 15, 2026
 *
 * @brief Templated 4x4 Matrix supporting integral, floating-point, and boolean types.
 *
 * @details Provide high-performance 4x4 matrix implementation with SIMD acceleration
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


#include "fgm/common/MathTraits.h"
#include "fgm/common/Types.h"
#include "fgm/vectors/Vector4.h"

#include <array>
#include <cstdint>



namespace fgm
{

    template <Arithmetic T>
    struct Matrix4
    {
        /**
         * @addtogroup FGM_Mat4x4_Members
         * @{
         */

        using value_type = T; ///< The numeric type of the matrix elements.

        static constexpr std::size_t columns = 4; ///< Matrix column count.
        static constexpr std::size_t rows    = 4; ///< Matrix row count.

        /** @} */



        /**
         * @addtogroup FGM_Mat4x4_Init
         * @{
         */

        /**
         * @brief Initialize an uninitialized @ref Matrix4 instance.
         *
         * @warning The components are left uninitialized (containing garbage data)
         *          to maximize SIMD optimization and maintain triviality.
         *
         * @note Use value-initialization (`{}`) or the static helper
         *       @ref fgm::Matrix4<T>::ZERO() to guarantee a zeroed matrix.
         */
        Matrix4() = default;


        /**
         * @brief Initialize a 4x4 matrix from the passed-in scalar elements.
         *
         * @param[in] m00 The element to insert into row one, column one.
         * @param[in] m01 The element to insert into row one, column two.
         * @param[in] m02 The element to insert into row one, column three.
         * @param[in] m03 The element to insert into row one, column four.
         * @param[in] m10 The element to insert into row two, column one.
         * @param[in] m11 The element to insert into row two, column two.
         * @param[in] m12 The element to insert into row two, column three.
         * @param[in] m13 The element to insert into row two, column four.
         * @param[in] m20 The element to insert into row three, column one.
         * @param[in] m21 The element to insert into row three, column two.
         * @param[in] m22 The element to insert into row three, column three.
         * @param[in] m23 The element to insert into row three, column four.
         * @param[in] m30 The element to insert into row four, column one.
         * @param[in] m31 The element to insert into row four, column two.
         * @param[in] m32 The element to insert into row four, column three.
         * @param[in] m33 The element to insert into row four, column four.
         *
         */
        [[nodiscard]] constexpr Matrix4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22,
                                        T m23, T m30, T m31, T m32, T m33) noexcept;


        /**
         * @brief Initialize a 4x4 matrix from the passed-in vectors as columns.
         *
         * @param[in] col0 The 4D-vector to use as the first column entry.
         * @param[in] col1 The 4D-vector to use as the second column entry.
         * @param[in] col2 The 4D-vector to use as the third column entry.
         * @param[in] col3 The 4D-vector to use as the fourth column entry.
         */
        [[nodiscard]] constexpr Matrix4(const Vector4<T>& col0, const Vector4<T>& col1, const Vector4<T>& col2,
                                        const Vector4<T>& col3) noexcept;


        /**
         * @brief Initialize a diagonal matrix from the passed-in scalar entries.
         *        All non-diagonal elements are initialized to zero.
         *
         * @param[in] d0 The first diagonal entry of the matrix (m00).
         * @param[in] d1 The second diagonal entry of the matrix (m11).
         * @param[in] d2 The third diagonal entry of the matrix (m22).
         * @param[in] d3 The third diagonal entry of the matrix (m33).
         */
        [[nodiscard]] constexpr Matrix4(T d0, T d1, T d2, T d3) noexcept;


        /**
         * @brief Initialize @ref Matrix4 from another @ref Matrix4 of a different type.
         *
         * @tparam U Numeric type of the source matrix.
         *
         * @param[in] other The source matrix to be converted.
         */
        template <Arithmetic U>
        [[nodiscard]] explicit constexpr Matrix4(const Matrix4<U>& other) noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Mat4x4_Access
         * @{
         */

        /**
         * @brief Access the column vector at the specified location (read-write access).
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] col The column index of the matrix.
         *
         * @return A reference to the column vector.
         */
        [[nodiscard]] constexpr Vector4<T>& operator[](std::size_t col) noexcept;


        /**
         * @brief Access the column vector at the specified location (read-only).
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] col The column index of the matrix.
         *
         * @return A const reference to the column vector.
         */
        [[nodiscard]] constexpr const Vector4<T>& operator[](std::size_t col) const noexcept;


        /**
         * @brief Access the element at the specified row, column index (read-write access).
         *
         * @note Performs bounds checking in **DEBUG MODE**.
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
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] row The row index of the matrix entry.
         * @param[in] col The column index of the matrix entry.
         *
         * @return A const reference to the element at row, col.
         */
        [[nodiscard]] constexpr const T& operator()(std::size_t row, std::size_t col) const noexcept;

        /** @} */


        /**
         * @addtogroup FGM_Mat4x4_Equality
         * @{
         */

        /**
         * @brief Compare all elements of this matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @note Implements an explicit constexpr MSVC workaround to ensure IEEE 754 NaN compliance
         *       during static evaluation.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The matrix to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all elements are equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool allEq(const Matrix4<U>& rhs,
                                           double epsilon = std::is_same_v<T, double> || std::is_same_v<U, double>
                                               ? Config::DOUBLE_EPSILON
                                               : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all elements of a matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @note Implements an explicit constexpr MSVC workaround to ensure IEEE 754 NaN compliance
         *       during static evaluation.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The matrix to compare.
         * @param[in] rhs     The matrix to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all elements are equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr bool allEq(const Matrix4& lhs, const Matrix4<U>& rhs,
                                                  double epsilon = std::is_same_v<T, double> ||
                                                          std::is_same_v<U, double>
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) noexcept;


        /**
         * @brief Compare all elements of this matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true if any corresponding elements differ by more
         *        than @p epsilon.
         *
         * @note Implements an explicit constexpr MSVC workaround to ensure IEEE 754 NaN compliance
         *       during static evaluation.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The matrix to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all elements are equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool anyNeq(const Matrix4<U>& rhs,
                                            double epsilon = std::is_same_v<T, double> || std::is_same_v<U, double>
                                                ? Config::DOUBLE_EPSILON
                                                : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all elements of this matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true if any corresponding elements differ by more
         *        than @p epsilon.
         *
         * @note Implements an explicit constexpr MSVC workaround to ensure IEEE 754 NaN compliance
         *       during static evaluation.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The matrix to compare.
         * @param[in] rhs     The matrix to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all elements are equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr bool anyNeq(const Matrix4& lhs, const Matrix4<U>& rhs,
                                                   double epsilon = std::is_same_v<T, double> ||
                                                           std::is_same_v<U, double>
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) noexcept;


        /**
         * @copybrief allEq(const Matrix4<U>&, double) const noexcept
         *
         * @note Implements an explicit constexpr MSVC workaround to ensure IEEE 754 NaN compliance
         *       during static evaluation.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The matrix to compare against.
         *
         * @return True if all elements are equivalent within the default epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool operator==(const Matrix4<U>& rhs) const noexcept;


        /**
         * @copybrief anyNeq(const Matrix4<U>&, double) const noexcept
         *
         * @note Implements an explicit constexpr MSVC workaround to ensure IEEE 754 NaN compliance
         *       during static evaluation.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The matrix to compare against.
         *
         * @return True if any of the elements are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool operator!=(const Matrix4<U>& rhs) const noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Mat4x4_Arithmetic
         * @{
         */

        /**
         * @brief Compute the element-wise sum of this matrix with @p rhs matrix and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMatrix4<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to add.
         *
         * @return A new @ref Matrix4 containing the element-wise sum.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedMatrix4<T, U> operator+(const Matrix4<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise sum of this matrix with @p rhs matrix in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to add.
         *
         * @return A reference to this matrix (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        Matrix4& operator+=(const Matrix4<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise difference between this matrix and @p rhs matrix and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMatrix4<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to subtract.
         *
         * @return A new @ref Matrix4 containing the element-wise difference.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedMatrix4<T, U> operator-(const Matrix4<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise difference between this matrix and @p rhs matrix in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to subtract.
         *
         * @return A reference to this matrix (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr Matrix4& operator-=(const Matrix4<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise product between this matrix and @p scalar and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMatrix4<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Matrix4 scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMatrix4<T, S> operator*(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise product between this matrix and @p scalar in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A reference to this matrix (*this).
         */
        template <StrictArithmetic S>
        constexpr Matrix4& operator*=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Transform the @p Vec **column vector** by this matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                  x \\ y \\ z \\ w
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                  x' \\ y' \\ z' \\ w'
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedVector4<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec The column vector to transform.
         *
         * @return A new @ref Vector4 with applied linear transformations.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedVector4<T, U> operator*(const Vector4<U>& vec) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compose this matrix with @p rhs matrix to form a new matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                 B_{00} & B_{01} & B_{02} & B_{03} \\
         *                 B_{10} & B_{11} & B_{12} & B_{13} \\
         *                 B_{20} & B_{21} & B_{22} & B_{23} \\
         *                 B_{30} & B_{31} & B_{32} & B_{33}
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                 C_{00} & C_{01} & C_{02} & C_{03} \\
         *                 C_{10} & C_{11} & C_{12} & C_{13} \\
         *                 C_{20} & C_{21} & C_{22} & C_{23} \\
         *                 C_{30} & C_{31} & C_{32} & C_{33}
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedMatrix4<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to multiply.
         *
         * @return A new @ref Matrix4 containing the composition of linear transformations.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedMatrix4<T, U> operator*(const Matrix4<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compose this matrix with @p rhs matrix in-place.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                 B_{00} & B_{01} & B_{02} & B_{03} \\
         *                 B_{10} & B_{11} & B_{12} & B_{13} \\
         *                 B_{20} & B_{21} & B_{22} & B_{23} \\
         *                 B_{30} & B_{31} & B_{32} & B_{33}
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                 C_{00} & C_{01} & C_{02} & C_{03} \\
         *                 C_{10} & C_{11} & C_{12} & C_{13} \\
         *                 C_{20} & C_{21} & C_{22} & C_{23} \\
         *                 C_{30} & C_{31} & C_{32} & C_{33}
         *            \end{bmatrix}
         *        \f$
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to multiply.
         *
         * @return A reference to this matrix (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr Matrix4& operator*=(const Matrix4<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of this matrix by @p scalar and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMatrix4<T, S>.
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         * @note Performs assertion for division by zero in **Debug mode**.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Matrix4 inverse scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMatrix4<T, S> operator/(const S& scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of this matrix by @p scalar in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Performs assertion for division by zero in **Debug mode**.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A reference to this matrix (*this).
         */
        template <StrictArithmetic S>
        constexpr Matrix4& operator/=(const S& scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of this matrix by @p scalar and return a new matrix.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMatrix4<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @p fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar   The value to divide the matrix elements by.
         * @param[in] fallback The default matrix to return, when an invalid case is hit like a zero scalar or a NaN
         *                     element.
         *
         * @return A new @ref Matrix4 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has a NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMatrix4<T, S> safeDiv(S scalar,
                                                              const Matrix4& fallback = Matrix4::EYE()) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of @p mat by @p scalar and return a new matrix.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMatrix4<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @p fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] mat      The matrix to divide.
         * @param[in] scalar   The value to divide the matrix elements by.
         * @param[in] fallback The default matrix to return, when an invalid case is hit like a zero scalar or a NaN
         *                     element.
         *
         * @return A new @ref Matrix4 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has a NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedMatrix4<T, S> safeDiv(const Matrix4& mat, S scalar,
                                                                     const Matrix4& fallback = Matrix4::EYE()) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of this matrix by @p scalar, return a new matrix,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMatrix4<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @ref fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over
         mathematical
         *       invalidity (Division by Zero) when reporting status.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar   The value to divide the matrix elements by.
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is hit like a zero scalar or a NaN
         *                     element.
         *
         * @return A new @ref Matrix4 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMatrix4<T, S> tryDiv(S scalar, OperationStatus& status,
                                                             const Matrix4& fallback = Matrix4::EYE()) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of @p Vec by @p scalar, return a new matrix,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedFloatMatrix4<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @ref fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over
         mathematical
         *       invalidity (Division by Zero) when reporting status.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] mat      The matrix to divide.
         * @param[in] scalar   The value to divide the matrix elements by.
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is hit like a zero scalar or a NaN
         *                     element.
         *
         * @return A new @ref Matrix4 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedMatrix4<T, S> tryDiv(const Matrix4& mat, S scalar,
                                                                    OperationStatus& status,
                                                                    const Matrix4& fallback = Matrix4::EYE()) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FGM_Mat4x4_Algebra
         * @{
         */

        /**
         * @brief Compute the determinant (scaling factor) of this matrix.
         *        \f$
         *            \begin{align*}
         *                 \text{det(A)} &= A_{00} \begin{bmatrix}
         *                                              A_{11} & A_{12} & A_{13} \\
         *                                              A_{21} & A_{22} & A_{23} \\
         *                                              A_{31} & A_{32} & A_{33}
         *                                         \end{bmatrix} \\
         *                               &- A_{01} \begin{bmatrix}
         *                                              A_{10} & A_{12} & A_{13} \\
         *                                              A_{20} & A_{22} & A_{23} \\
         *                                              A_{30} & A_{32} & A_{33}
         *                                         \end{bmatrix} \\
         *                               &+ A_{02} \begin{bmatrix}
         *                                              A_{10} & A_{11} & A_{13} \\
         *                                              A_{20} & A_{21} & A_{23} \\
         *                                              A_{30} & A_{31} & A_{33}
         *                                         \end{bmatrix} \\
         *                               &- A_{03} \begin{bmatrix}
         *                                             A_{10} & A_{11} & A_{12} \\
         *                                             A_{20} & A_{21} & A_{22} \\
         *                                             A_{30} & A_{31} & A_{32}
         *                                         \end{bmatrix}
         *            \end{align*}
         *        \f$
         *
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         *
         * @return A non-zero scalar if the matrix is non-singular, else zero.
         */
        [[nodiscard]] constexpr T determinant() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the determinant (scaling factor) of @p matrix.
         *        \f$
         *            \begin{align*}
         *                 \text{det(A)} &= A_{00} \begin{bmatrix}
         *                                              A_{11} & A_{12} & A_{13} \\
         *                                              A_{21} & A_{22} & A_{23} \\
         *                                              A_{31} & A_{32} & A_{33}
         *                                         \end{bmatrix} \\
         *                               &- A_{01} \begin{bmatrix}
         *                                              A_{10} & A_{12} & A_{13} \\
         *                                              A_{20} & A_{22} & A_{23} \\
         *                                              A_{30} & A_{32} & A_{33}
         *                                         \end{bmatrix} \\
         *                               &+ A_{02} \begin{bmatrix}
         *                                              A_{10} & A_{11} & A_{13} \\
         *                                              A_{20} & A_{21} & A_{23} \\
         *                                              A_{30} & A_{31} & A_{33}
         *                                         \end{bmatrix} \\
         *                               &- A_{03} \begin{bmatrix}
         *                                             A_{10} & A_{11} & A_{12} \\
         *                                             A_{20} & A_{21} & A_{22} \\
         *                                             A_{30} & A_{31} & A_{32}
         *                                         \end{bmatrix}
         *            \end{align*}
         *        \f$
         *
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         *
         * @param matrix The matrix to compute the determinant of.
         *
         * @return A non-zero scalar if the matrix is non-singular, else zero.
         */
        static constexpr T determinant(const Matrix4& matrix) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Transpose this matrix by swapping its rows and columns.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix} ^ \top
         *            =
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} & A_{20} & A_{30} \\
         *                 A_{01} & A_{11} & A_{21} & A_{31} \\
         *                 A_{02} & A_{12} & A_{22} & A_{32} \\
         *                 A_{03} & A_{13} & A_{23} & A_{33}
         *            \end{bmatrix}
         *        \f$
         *
         * @return A new @ref Matrix4 with its elements flipped along the diagonal.
         */
        [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Matrix4 transpose() const noexcept;


        /**
         * @brief Transpose @p matrix by swapping its rows and columns.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix} ^ \top
         *            =
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} & A_{20} & A_{30} \\
         *                 A_{01} & A_{11} & A_{21} & A_{31} \\
         *                 A_{02} & A_{12} & A_{22} & A_{32} \\
         *                 A_{03} & A_{13} & A_{23} & A_{33}
         *            \end{bmatrix}
         *        \f$
         *
         * @param matrix The matrix to transpose.
         *
         * @return A new @ref Matrix4 with its elements flipped along the diagonal.
         */
        [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Matrix4 transpose(const Matrix4& matrix) noexcept;


        /**
         * @brief Compute the inverse of this matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                     C_{00} & C_{10} & C_{20} & C_{30} \\
         *                     C_{01} & C_{11} & C_{21} & C_{31} \\
         *                     C_{02} & C_{12} & C_{22} & C_{32} \\
         *                     C_{03} & C_{13} & C_{23} & C_{33}
         *            \end{bmatrix}
         *            \\
         *            \begin{text}
         *                where C_{ij} = [\text{adj}(A)]_{ij} = (-1)^{i+j} \det(M_{ji})
         *            \end{text}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Performs assertion for division by zero (singular matrix) in **Debug mode**.
         *
         * @return A new @ref Matrix4 such that \f$ A \cdot A^{-1} = I \f$.
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Matrix4<Magnitude<T>> inverse() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of a matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                     C_{00} & C_{10} & C_{20} & C_{30} \\
         *                     C_{01} & C_{11} & C_{21} & C_{31} \\
         *                     C_{02} & C_{12} & C_{22} & C_{32} \\
         *                     C_{03} & C_{13} & C_{23} & C_{33}
         *            \end{bmatrix}
         *            \\
         *            \begin{text}
         *                where C_{ij} = [\text{adj}(A)]_{ij} = (-1)^{i+j} \det(M_{ji})
         *            \end{text}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Performs assertion for division by zero (singular matrix) in **Debug mode**.
         *
         * @param[in] matrix The matrix to invert.
         *
         * @return A new @ref Matrix4 such that \f$ A \cdot A^{-1} = I \f$.
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Matrix4<Magnitude<T>> inverse(const Matrix4& matrix) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of this matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                     C_{00} & C_{10} & C_{20} & C_{30} \\
         *                     C_{01} & C_{11} & C_{21} & C_{31} \\
         *                     C_{02} & C_{12} & C_{22} & C_{32} \\
         *                     C_{03} & C_{13} & C_{23} & C_{33}
         *            \end{bmatrix}
         *            \\
         *            \begin{text}
         *                where C_{ij} = [\text{adj}(A)]_{ij} = (-1)^{i+j} \det(M_{ji})
         *            \end{text}
         *        \f$
         * @note If the determinant is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Matrix4 such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Matrix4<Magnitude<T>> safeInverse(const Matrix4& fallback = Matrix4::EYE()) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of @p matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                     C_{00} & C_{10} & C_{20} & C_{30} \\
         *                     C_{01} & C_{11} & C_{21} & C_{31} \\
         *                     C_{02} & C_{12} & C_{22} & C_{32} \\
         *                     C_{03} & C_{13} & C_{23} & C_{33}
         *            \end{bmatrix}
         *            \\
         *            \begin{text}
         *                where C_{ij} = [\text{adj}(A)]_{ij} = (-1)^{i+j} \det(M_{ji})
         *            \end{text}
         *        \f$
         *
         * @note If the determinant is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[in] matrix   The matrix to invert.
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Matrix4 such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Matrix4<Magnitude<T>> safeInverseOf(const Matrix4& matrix,
                                                             const Matrix4& fallback = Matrix4::EYE()) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of this matrix and set @p status to the matrix inversion result.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                     C_{00} & C_{10} & C_{20} & C_{30} \\
         *                     C_{01} & C_{11} & C_{21} & C_{31} \\
         *                     C_{02} & C_{12} & C_{22} & C_{32} \\
         *                     C_{03} & C_{13} & C_{23} & C_{33}
         *            \end{bmatrix}
         *            \\
         *            \begin{text}
         *                where C_{ij} = [\text{adj}(A)]_{ij} = (-1)^{i+j} \det(M_{ji})
         *            \end{text}
         *        \f$
         *
         * @note If the determinant is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Matrix4 such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Matrix4<Magnitude<T>> tryInverse(OperationStatus& status,
                                                   const Matrix4& fallback = Matrix4::EYE()) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Safely compute the inverse of @p matrix and set @p status to the matrix inversion result.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                     C_{00} & C_{10} & C_{20} & C_{30} \\
         *                     C_{01} & C_{11} & C_{21} & C_{31} \\
         *                     C_{02} & C_{12} & C_{22} & C_{32} \\
         *                     C_{03} & C_{13} & C_{23} & C_{33}
         *            \end{bmatrix}
         *            \\
         *            \begin{text}
         *                where C_{ij} = [\text{adj}(A)]_{ij} = (-1)^{i+j} \det(M_{ji})
         *            \end{text}
         *        \f$
         *
         * @note If the determinant is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[in] matrix   The matrix to invert.
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Matrix4 such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Matrix4<Magnitude<T>> tryInverseOf(const Matrix4& matrix, OperationStatus& status,
                                                            const Matrix4& fallback = Matrix4::EYE()) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the sum of diagonal entries of this matrix.
         *
         * @return The sum of entries along the main diagonal of this matrix.
         */
        [[nodiscard]] constexpr T trace() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the sum of diagonal entries of @p matrix.
         *
         * @param matrix The matrix whose trace is to be computed.
         *
         * @return The sum of entries along the main diagonal of the given matrix.
         */
        [[nodiscard]] static constexpr T trace(const Matrix4& matrix) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FGM_Mat4x4_Utils
         * @{
         */

        /**
         * @brief Check if any element of this matrix is an IEEE 754 infinity.
         *
         * @note Always returns false for integral types.
         *
         * @return True if at least one element is positive or negative infinity.
         */
        [[nodiscard]] constexpr bool hasInf() const noexcept;


        /**
         * @brief Check if any element of @p matrix is an IEEE 754 infinity.
         *
         * @note Always returns false for integral types.
         *
         * @param matrix The matrix to evaluate for indefinite elements.
         *
         * @return True if at least one element is positive or negative infinity.
         */
        [[nodiscard]] static constexpr bool hasInf(const Matrix4& matrix) noexcept;


        /**
         * @brief Check if any element of this matrix is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @return True if at least one element is NaN.
         */
        [[nodiscard]] constexpr bool hasNaN() const noexcept;


        /**
         * @brief Check if any element of @p matrix is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @param matrix The matrix to evaluate for indefinite elements.
         *
         * @return True if at least one element is NaN.
         */
        [[nodiscard]] static constexpr bool hasNaN(const Matrix4& matrix) noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Mat3x3_Log
         * @{
         */

        /**
         * @brief Write the matrix to an output stream in **row-major** order.
         *        Format the matrix as
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} & A_{20} & A_{30} \\
         *                 A_{01} & A_{11} & A_{21} & A_{31} \\
         *                 A_{02} & A_{12} & A_{22} & A_{32} \\
         *                 A_{03} & A_{13} & A_{23} & A_{33}
         *            \end{bmatrix}
         *        \f$ string representation for debugging or logging.
         *
         * @param os     The output stream to write to.
         * @param matrix The matrix to be streamed.
         *
         * @return A reference to the output stream @p os.
         */
        friend std::ostream& operator<<(std::ostream& os, const Matrix4& matrix)
        {
            const std::streamsize oldPrecision     = os.precision();
            const std::ios_base::fmtflags oldFlags = os.flags();

            auto precision = Config::useFullPrecision
                ? std::is_same_v<T, double> ? Config::DOUBLE_PRECISION : Config::FLOAT_PRECISION
                : Config::LOG_PRECISION;
            os << std::setprecision(precision) << std::fixed;
            os << "|" << matrix._data[0][0] << " " << matrix._data[1][0] << " " << matrix._data[2][0] << " "
               << matrix._data[3][0] << "|\n";
            os << "|" << matrix._data[0][1] << " " << matrix._data[1][1] << " " << matrix._data[2][1] << " "
               << matrix._data[3][1] << "|\n";
            os << "|" << matrix._data[0][2] << " " << matrix._data[1][2] << " " << matrix._data[2][2] << " "
               << matrix._data[3][2] << "|\n";
            os << "|" << matrix._data[0][3] << " " << matrix._data[1][3] << " " << matrix._data[2][3] << " "
               << matrix._data[3][3] << "|\n";

            os.precision(oldPrecision);
            os.flags(oldFlags);

            return os;
        }

        /** @} */

        /**
         * @addtogroup FGM_Mat4x4_Transforms
         * @{
         */

        /**
         * @brief Construct a 3D affine rotation matrix in the x-axis for a given angle.
         *
         * @details The layout of the returned matrix adapts to the library's active coordinate system:
         *          - **Right-Handed (Default):**
         *            \f$
         *                \begin{bmatrix}
         *                    1 &            0 &            0 & 0 \\
         *                    0 &  cos(\theta) & -sin(\theta) & 0 \\
         *                    0 &  sin(\theta) &  cos(\theta) & 0 \\
         *                    0 &            0 &            0 & 1
         *                \end{bmatrix}
         *            \f$
         *          - **Left-Handed (FGM_LEFT_HANDED):**
         *            \f$
         *                \begin{bmatrix}
         *                    1 &            0 &           0 & 0 \\
         *                    0 &  cos(\theta) & sin(\theta) & 0 \\
         *                    0 & -sin(\theta) & cos(\theta) & 0 \\
         *                    0 &            0 &           0 & 1
         *                \end{bmatrix}
         *            \f$
         *
         * @note While it is possible to create a rotation matrix of any **signed type**, it is strongly discouraged.
         *       Trigonometric results will be truncated, resulting in severe precision loss and potential zero-matrices
         *       for integral types.
         *
         * @tparam U Numeric type of the angle. Must satisfy `std::floating_point`.
         *
         * @param[in] angle The rotation angle in radians.
         *
         * @return A new @ref Matrix4 representing the linear rotation around x-axis.
         */
        template <std::floating_point U>
        [[nodiscard]] static constexpr Matrix4 makeRotationX(U angle) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Construct an affine 3D rotation matrix in the y-axis for a given angle.
         *
         * @details The layout of the returned matrix adapts to the library's active coordinate system:
         *          - **Right-Handed (Default):**
         *            \f$
         *                \begin{bmatrix}
         *                     cos(\theta) & 0 & sin(\theta) & 0 \\
         *                     0           & 1 &           0 & 0 \\
         *                    -sin(\theta) & 0 & cos(\theta) & 0 \\
         *                               0 & 0 &           0 & 1
         *                \end{bmatrix}
         *            \f$
         *          - **Left-Handed (FGM_LEFT_HANDED):**
         *            \f$
         *                \begin{bmatrix}
         *                    cos(\theta) & 0 & -sin(\theta) & 0 \\
         *                    0           & 1 &            0 & 0 \\
         *                    sin(\theta) & 0 &  cos(\theta) & 0 \\
         *                              0 & 0 &            0 & 1
         *                \end{bmatrix}
         *            \f$
         *
         * @note While it is possible to create a rotation matrix of any **signed type**, it is strongly discouraged.
         *       Trigonometric results will be truncated, resulting in severe precision loss and potential zero-matrices
         *       for integral types.
         *
         * @tparam U Numeric type of the angle. Must satisfy `std::floating_point`.
         *
         * @param[in] angle The rotation angle in radians.
         *
         * @return A new @ref Matrix4 representing the linear rotation around y-axis.
         */
        template <std::floating_point U>
        [[nodiscard]] static constexpr Matrix4 makeRotationY(U angle) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Construct an affine 3D rotation matrix in the z-axis for a given angle.
         *
         * @details The layout of the returned matrix adapts to the library's active coordinate system:
         *          - **Right-Handed (Default):**
         *            \f$
         *                \begin{bmatrix}
         *                     cos(\theta) & -sin(\theta) & 0 & 0 \\
         *                     sin(\theta) &  cos(\theta) & 0 & 0 \\
         *                               0 &            0 & 1 & 0 \\
         *                               0 &            0 & 0 & 1
         *                \end{bmatrix}
         *            \f$
         *          - **Left-Handed (FGM_LEFT_HANDED):**
         *            \f$
         *                \begin{bmatrix}
         *                     cos(\theta) & sin(\theta) & 0 & 0 \\
         *                    -sin(\theta) & cos(\theta) & 0 & 0 \\
         *                               0 &           0 & 1 & 0 \\
         *                               0 &           0 & 0 & 1
         *                \end{bmatrix}
         *            \f$
         *
         * @note While it is possible to create a rotation matrix of any **signed type**, it is strongly discouraged.
         *       Trigonometric results will be truncated, resulting in severe precision loss and potential zero-matrices
         *       for integral types.
         *
         * @tparam U Numeric type of the angle. Must satisfy `std::floating_point`.
         *
         * @param[in] angle The rotation angle in radians.
         *
         * @return A new @ref Matrix4 representing the linear rotation around z-axis.
         */
        template <std::floating_point U>
        [[nodiscard]] static constexpr Matrix4 makeRotationZ(U angle) noexcept
            requires SignedStrictArithmetic<T>;

        // /**
        //  * @brief Construct a uniform scale 3D matrix.
        //  *
        //  * @param[in] scale The scale factor.
        //  *
        //  * @return A new @ref Matrix4 representing the uniform scale.
        //  */
        // [[nodiscard]] static constexpr Matrix4 makeScale(T scale) noexcept
        //     requires StrictArithmetic<T>;
        //
        //
        // /**
        //  * @brief Construct a non-uniform scale 3D matrix.
        //  *
        //  * @param[in] scaleX The scale factor in the x-direction.
        //  * @param[in] scaleY The scale factor in the y-direction.
        //  * @param[in] scaleZ The scale factor in the z-direction.
        //  *
        //  * @return A new @ref Matrix4 representing the non-uniform scale.
        //  */
        // [[nodiscard]] static constexpr Matrix4 makeScale(T scaleX, T scaleY, T scaleZ) noexcept
        //     requires StrictArithmetic<T>;


        // /**
        //  * @brief Construct a reflection 3D matrix for reflection along coordinate axis(X, Y), and the origin<0, 0>.
        //  *
        //  * @note To construction a reflection matrix around origin, set all axis reflection to true.
        //  *
        //  * @param[in] reflectX A flag to whether reflect in the x-direction.
        //  * @param[in] reflectY A flag to whether reflect in the y-direction.
        //  *
        //  * @return A new @ref Matrix4 representing the axis-aligned reflection.
        //  */
        // [[nodiscard]] static constexpr Matrix4 reflect(bool reflectX, bool reflectY) noexcept
        //     requires StrictArithmetic<T>;

        /** @} */

        /**
         * @addtogroup T_FGM_Mat4x4_Constant
         * @{
         */

        // NOLINTBEGIN

        /**************************************
         *                                    *
         *             CONSTANTS              *
         *                                    *
         **************************************/

        /**
         * @brief A 4D matrix with ones on the main diagonal and zeros elsewhere.
         *
         * @note Constrained to @ref StrictArithmetic types.
         */
        static constexpr Matrix4 EYE()
            requires fgm::StrictArithmetic<T>
        {
            return Matrix4{ T(1), T(0), T(0), T(0), T(0), T(1), T(0), T(0),
                            T(0), T(0), T(1), T(0), T(0), T(0), T(0), T(1) };
        }


        /**
         * @brief A 4D matrix with all zero elements.
         *
         * @note Constrained to @ref StrictArithmetic types.
         */
        static constexpr Matrix4 ZERO()
            requires fgm::StrictArithmetic<T>
        {
            return Matrix4{ T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0),
                            T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0) };
        }

        // NOLINTEND

        /** @} */

    private:
        std::array<Vector4<T>, columns> _data;
    };



    /**
     * @addtogroup FGM_Ma4x4_Alias
     * @{
     */

    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/

    using Mat4B   = Matrix4<int8_t>;   ///< Signed Byte (8-bit) matrix
    using Mat4UB  = Matrix4<uint8_t>;  ///< Unsigned Byte (8-bit) matrix
    using Mat4I   = Matrix4<int32_t>;  ///< Signed Int (32-bit) matrix
    using Mat4U   = Matrix4<uint32_t>; ///< Unsigned Int (32-bit) matrix
    using Mat4F   = Matrix4<float>;    ///< Single Precision Floating Point (32-bit) matrix
    using Mat4LL  = Matrix4<int64_t>;  ///< Signed Long Long (64-bit) matrix
    using Mat4D   = Matrix4<double>;   ///< Double Precision Floating Point (64-bit) matrix
    using Mat4ULL = Matrix4<uint64_t>; ///< Unsigned Long Long (64-bit) matrix

    /** @} */



    /**************************************
     *                                    *
     *        NON-MEMBER FUNCTIONS        *
     *                                    *
     **************************************/

    /**
     * @addtogroup FGM_Mat4x4_Arithmetic
     * @{
     */

    /**
     * @brief Compute the element-wise product between @p matrix and @p scalar and return a new matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMatrix4<T, S>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] scalar The value to scale by.
     * @param[in] matrix The matrix to scale.
     *
     * @return A new @ref Matrix4 scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    [[nodiscard]] constexpr PromotedMatrix4<T, S> operator*(S scalar, const Matrix4<T>& matrix) noexcept;


    /**
     * @brief Transform the @p Vec **row vector** by @p matrix.
     *        \f$
     *            \begin{bmatrix}
     *                x & y & z & w
     *            \end{bmatrix}
     *            \cdot
     *            \begin{bmatrix}
     *                A_{00} & A_{01} & A_{02} & A_{03} \\
     *                A_{10} & A_{11} & A_{12} & A_{13} \\
     *                A_{20} & A_{21} & A_{22} & A_{23} \\
     *                A_{30} & A_{31} & A_{32} & A_{33}
     *            \end{bmatrix}
     *            =
     *            \begin{bmatrix}
     *                x' & y' & z' & w'
     *            \end{bmatrix}
     *        \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedVector4<T, S>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam T Numeric type of the row vector. Must satisfy @ref StrictArithmetic.
     * @tparam S Numeric type of the transformation matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec    The row vector to transform.
     * @param[in] matrix The transformation matrix.
     *
     * @return The passed-in @p Vec with the transformations applied.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    static constexpr PromotedVector4<T, S> operator*(const Vector4<T>& vec, const Matrix4<S>& matrix) noexcept;


    /**
     * @brief Transform the @p Vec **row vector** by @p matrix.
     *        \f$
     *            \begin{bmatrix}
     *                x & y & z & w
     *            \end{bmatrix}
     *            \cdot
     *            \begin{bmatrix}
     *                A_{00} & A_{01} & A_{02} & A_{03} \\
     *                A_{10} & A_{11} & A_{12} & A_{13} \\
     *                A_{20} & A_{21} & A_{22} & A_{23} \\
     *                A_{30} & A_{31} & A_{32} & A_{33}
     *            \end{bmatrix}
     *            =
     *            \begin{bmatrix}
     *                x' & y' & z' & w'
     *            \end{bmatrix}
     *        \f$
     *
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam T Numeric type of the row vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the transformation matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec    The row vector to transform.
     * @param[in] matrix The transformation matrix.
     *
     * @return The passed-in @p Vec with the transformations applied.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    static constexpr Vector4<T>& operator*=(Vector4<T>& vec, const Matrix4<U>& matrix) noexcept;

    /** @} */



    /** @brief Template deduction guide for Matrix4. */
    template <Arithmetic T, Arithmetic... Args>
    Matrix4(T, Args...) -> Matrix4<T>;

} // namespace fgm

#include "Matrix4.tpp"
