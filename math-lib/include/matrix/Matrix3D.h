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
        static constexpr std::size_t rows = 3;    ///< Matrix row count.

        /** @} */



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

        /** @} */



        /**
         * @addtogroup FGM_Mat3x3_Access
         * @{
         */

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



        /**
         * @addtogroup T_FGM_Mat3x3_Constant
         * @{
         */

        /**************************************
         *                                    *
         *             CONSTANTS              *
         *                                    *
         **************************************/

        /**
         * @brief A 3D matrix with ones on the main diagonal and zeros elsewhere.
         *
         * @note Only available for @ref StrictArithmetic types.
         *
         * @return A 3D identity matrix.
         */
        [[nodiscard]] static constexpr Matrix3D eye() noexcept;


        /**
         * @brief A 3D matrix with all zero elements.
         *
         * @note Only available for @ref StrictArithmetic types.
         *
         * @return A 3D zero matrix.
         */
        [[nodiscard]] static constexpr Matrix3D zero() noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Mat3x3_Equality
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
        [[nodiscard]] constexpr bool allEq(const Matrix3D<U>& rhs,
                                           double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
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
        [[nodiscard]] constexpr static bool allEq(const Matrix3D& lhs, const Matrix3D<U>& rhs,
                                                  double epsilon = (std::is_same_v<T, double> ||
                                                                    std::is_same_v<U, double>)
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
        [[nodiscard]] constexpr bool anyNeq(const Matrix3D<U>& rhs,
                                            double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
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
        [[nodiscard]] constexpr static bool anyNeq(const Matrix3D& lhs, const Matrix3D<U>& rhs,
                                                   double epsilon = (std::is_same_v<T, double> ||
                                                                     std::is_same_v<U, double>)
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) noexcept;


        /**
         * @copybrief allEq(const Matrix3D<U>&, double) const noexcept
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
        [[nodiscard]] constexpr bool operator==(const Matrix3D<U>& rhs) const noexcept;


        /**
         * @copybrief anyNeq(const Vector2D<U>&, double) const noexcept
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
        [[nodiscard]] constexpr bool operator!=(const Matrix3D<U>& rhs) const noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Mat3x3_Arithmetic
         * @{
         */

        /**
         * @brief Add two matrices element-wise.
         *        Compute the sum of each element pair and returns a new matrix.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to add.
         *
         * @return A new @ref Matrix3D containing the element-wise sum.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr PromotedMatrix3D<T, U> operator+(const Matrix3D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Add another matrix to this matrix element-wise.
         *        Perform an in-place addition of @p rhs to the current instance.
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
        Matrix3D& operator+=(const Matrix3D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Subtract two matrices element-wise.
         *        Compute the difference between each element pair and returns a new matrix.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to subtract.
         *
         * @return A new @ref Matrix3D containing the element-wise difference.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr PromotedMatrix3D<T, U> operator-(const Matrix3D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Subtract another matrix from this matrix element-wise.
         *        Perform an in-place substraction of @p rhs from the current instance.
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
        constexpr Matrix3D& operator-=(const Matrix3D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Scale the matrix by a scalar value.
         *        Multiply each element of the matrix by @p scalar and returns a new matrix.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Matrix3D scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMatrix3D<T, S> operator*(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Scale this matrix in-place by a scalar value.
         *        Perform an in-place multiplication of each element by @p scalar.
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
        constexpr Matrix3D& operator*=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Transform the **column vector** by this matrix.
         *        Perform the linear transformation:
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                  x \\ y \\ z
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                  x' \\ y' \\ z'
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec The column vector to transform.
         *
         * @return A new @ref Vector3D with applied linear transformations.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr PromotedVector3D<T, U> operator*(const Vector3D<U>& vec) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compose this matrix with another to form a new matrix.
         *        Compute the matrix product:
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                  B_{00} & B_{01} & B_{02} \\
         *                  B_{10} & B_{11} & B_{12} \\
         *                  B_{20} & B_{21} & B_{22}
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                  C_{00} & C_{01} & C_{02} \\
         *                  C_{10} & C_{11} & B_{12} \\
         *                  C_{20} & C_{21} & C_{22}
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to multiply.
         *
         * @return A new @ref Matrix3D containing the composition of linear transformations.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr PromotedMatrix3D<T, U> operator*(const Matrix3D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compose this matrix with another matrix in-place.
         *        Compute the matrix product:
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                  B_{00} & B_{01} & B_{02} \\
         *                  B_{10} & B_{11} & B_{12} \\
         *                  B_{20} & B_{21} & B_{22}
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                  C_{00} & C_{01} & C_{02} \\
         *                  C_{10} & C_{11} & B_{12} \\
         *                  C_{20} & C_{21} & C_{22}
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to multiply.
         *
         * @return A reference to this matrix (*this).
         */
        template <StrictArithmetic U>
        constexpr Matrix3D& operator*=(const Matrix3D<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Inverse-scale the matrix by a scalar value.
         *        Divide each element of the matrix by @p scalar and returns a new matrix.
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Matrix3D inverse scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedFloatMatrix3D<T, S> operator/(const S& scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Inverse-scale this matrix by a scalar value.
         *        Perform an in-place division of each element by @p scalar.
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
        constexpr Matrix3D& operator/=(const S& scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Safely divide each element of this matrix by a scalar value.
         *        Divide each element of the matrix by @p scalar and returns the newly computed matrix.
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
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
         * @return A new @ref Matrix3D resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has a NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedFloatMatrix3D<T, S> safeDiv(
            S scalar, const Matrix3D& fallback = Matrix3D::eye()) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Safely divide each element of a matrix by a scalar value.
         *        Divide each element of the matrix by @p scalar and returns the newly computed matrix.
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
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
         * @return A new @ref Matrix3D resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has a NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr static PromotedFloatMatrix3D<T, S> safeDiv(
            const Matrix3D& mat, S scalar, const Matrix3D& fallback = Matrix3D::eye()) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Safely divide this matrix by a scalar value and set @p status to the division operation result.
         *        Divides each element of the matrix by @p scalar and returns the newly computed matrix.
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @ref fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over mathematical
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
         * @return A new @ref Matrix3D resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedFloatMatrix3D<T, S> tryDiv(
            S scalar, OperationStatus& status, const Matrix3D& fallback = Matrix3D::eye()) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Safely divide a matrix by a scalar value and set @p status to the division operation result.
         *        Divides each element of the matrix by @p scalar and returns the newly computed matrix.
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @ref fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over mathematical
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
         * @return A new @ref Matrix3D resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedFloatMatrix3D<T, S> tryDiv(
            const Matrix3D& mat, S scalar, OperationStatus& status, const Matrix3D& fallback = Matrix3D::eye()) noexcept
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FGM_Mat3x3_Algebra
         * @{
         */

        /**
         * @brief Compute the determinant (scaling factor) of this matrix.
         *        Calculate determinant:
         *        \f$
         *            \begin{align*}
         *                \text{det(A)} &= A_{00} \cdot (A_{11} \cdot A_{22} - A_{21} \cdot A_{12}) \\
         *                              &- A_{01} \cdot (A_{10} \cdot A_{22} - A_{20} \cdot A_{12}) \\
         *                              &+ A_{02} \cdot (A_{10} \cdot A_{21} - A_{20} \cdot A_{12})
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
         * @brief Compute the determinant (scaling factor) of a matrix.
         *        Calculate determinant:
         *        \f$
         *            \begin{align*}
         *                \text{det(A)} &= A_{00} \cdot (A_{11} \cdot A_{22} - A_{21} \cdot A_{12}) \\
         *                              &- A_{01} \cdot (A_{10} \cdot A_{22} - A_{20} \cdot A_{12}) \\
         *                              &+ A_{02} \cdot (A_{10} \cdot A_{21} - A_{20} \cdot A_{12})
         *            \end{align*}
         *        \f$
         *
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         *
         * @param mat The matrix to compute the determinant of.
         *
         * @return A non-zero scalar if the matrix is non-singular, else zero.
         */
        static constexpr T determinant(const Matrix3D& mat) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Transpose this matrix by swapping its rows and columns.
         *        Compute transpose:
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix} ^ \top
         *            =
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} & A_{20} \\
         *                 A_{01} & A_{11} & A_{21} \\
         *                 A_{02} & A_{12} & A_{22}
         *            \end{bmatrix}
         *        \f$
         *
         * @return A new @ref Matrix3D with its elements flipped along the diagonal.
         */
        [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Matrix3D transpose() const noexcept;


        /**
         * @brief Transpose a matrix by swapping its rows and columns.
         *        Compute transpose:
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix} ^ \top
         *            =
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} & A_{20} \\
         *                 A_{01} & A_{11} & A_{21} \\
         *                 A_{02} & A_{12} & A_{22}
         *            \end{bmatrix}
         *        \f$
         *
         * @param mat The matrix to transpose.
         *
         * @return A new @ref Matrix3D with its elements flipped along the diagonal.
         */
        [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr static Matrix3D transpose(const Matrix3D& mat) noexcept;


        /**
         * @brief Compute the inverse of this matrix.
         *        Calculate inverse:
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 b  \times c \\
         *                 c  \times a \\
         *                 a  \times b
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         *
         * @return A new @ref Matrix3D such that \f$ A \cdot A^{-1} = I \f$.
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Matrix3D<Magnitude<T>> inverse() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of a matrix.
         *        Calculate inverse:
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 b  \times c \\
         *                 c  \times a \\
         *                 a  \times b
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         *
         * @param[in] matrix The matrix to invert.
         *
         * @return A new @ref Matrix3D such that \f$ A \cdot A^{-1} = I \f$.
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr static Matrix3D<Magnitude<T>> inverse(const Matrix3D& matrix) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Safely compute the inverse of this matrix.
         *        Calculate inverse:
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 b  \times c \\
         *                 c  \times a \\
         *                 a  \times b
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Matrix3D such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
         constexpr Matrix3D<Magnitude<T>> safeInverse(const Matrix3D& fallback = Matrix3D::eye()) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Safely compute the inverse of a matrix.
         *        Calculate inverse:
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 b  \times c \\
         *                 c  \times a \\
         *                 a  \times b
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[in] matrix   The matrix to invert.
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Matrix3D such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
         static constexpr Matrix3D<Magnitude<T>> safeInverseOf(const Matrix3D& matrix,
                                                              const Matrix3D& fallback = Matrix3D::eye()) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Safely compute the inverse of this matrix and set @p status to the matrix inversion result.
         *        Calculate inverse:
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 b  \times c \\
         *                 c  \times a \\
         *                 a  \times b
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Matrix3D such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
         constexpr Matrix3D<Magnitude<T>> tryInverse(OperationStatus& status,
                                                    const Matrix3D& fallback = Matrix3D::eye()) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Safely compute the inverse of a matrix and set @p status to the matrix inversion result.
         *        Calculate inverse:
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 b  \times c \\
         *                 c  \times a \\
         *                 a  \times b
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[in] matrix   The matrix to invert.
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Matrix3D such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
         static constexpr Matrix3D<Magnitude<T>> tryInverseOf(const Matrix3D& matrix, OperationStatus& status,
                                                             const Matrix3D& fallback = Matrix3D::eye()) noexcept
            requires SignedStrictArithmetic<T>;


        ///**
        // * @brief Compute the sum of diagonal entries of this matrix.
        // *
        // * @return The sum of entries along the main diagonal of this matrix.
        // */
        //[[nodiscard]] constexpr T trace() const noexcept
        //    requires StrictArithmetic<T>;


        ///**
        // * @brief Compute the sum of diagonal entries of a matrix.
        // *
        // * @param mat The matrix whose trace is to be computed.
        // *
        // * @return The sum of entries along the main diagonal of the given matrix.
        // */
        //[[nodiscard]] static constexpr T trace(const Matrix3D& mat) noexcept
        //    requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FGM_Mat3x3_Utils
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
         * @brief Check if any element of a matrix is an IEEE 754 infinity.
         *
         * @note Always returns false for integral types.
         *
         * @param mat The matrix to evaluate for indefinite elements.
         *
         * @return True if at least one element is positive or negative infinity.
         */
        [[nodiscard]] constexpr static bool hasInf(const Matrix3D& mat) noexcept;


        /**
         * @brief Check if any element of this matrix is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @return True if at least one element is NaN.
         */
        [[nodiscard]] constexpr bool hasNaN() const noexcept;


        /**
         * @brief Check if any element of this matrix is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @param mat The matrix to evaluate for indefinite elements.
         *
         * @return True if at least one element is NaN.
         */
        [[nodiscard]] constexpr static bool hasNaN(const Matrix3D& mat) noexcept;

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



    /**
     * @addtogroup FGM_Mat3x3_Arithmetic
     * @{
     */

    /**************************************
     *                                    *
     *        NON-MEMBER FUNCTIONS        *
     *                                    *
     **************************************/

    /**
     * @brief Scale the matrix by a scalar value.
     *        Multiply each element of the matrix by @p scalar and returns a new matrix.
     *
     * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] scalar The value to scale by.
     * @param[in] mat    The matrix to scale.
     *
     * @return A new @ref Matrix3D scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    [[nodiscard]] constexpr PromotedMatrix3D<T, S> operator*(S scalar, const Matrix3D<T>& mat) noexcept;


    /**
     * @brief Transform the **row vector** by a matrix.
     *        Perform the linear transformation:
     *        \f$
     *            \begin{bmatrix}
     *                x & y & z
     *            \end{bmatrix}
     *            \cdot
     *            \begin{bmatrix}
     *                A_{00} & A_{01} & A_{02} \\
     *                A_{10} & A_{11} & A_{12} \\
     *                A_{20} & A_{21} & A_{22}
     *            \end{bmatrix}
     *            =
     *            \begin{bmatrix}
     *                x' & y' & z'
     *            \end{bmatrix}
     *        \f$
     *
     * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam T Numeric type of the row vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the transformation matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec The row vector to transformed.
     * @param[in] mat The transformation matrix.
     *
     * @return The passed-in @p vec with the transformations applied.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    static constexpr PromotedVector3D<T, U> operator*(const Vector3D<T>& vec, const Matrix3D<U>& mat) noexcept;


    /**
     * @brief Transform this **row vector** by a matrix.
     *        Perform the linear transformation:
     *        \f$
     *            \begin{bmatrix}
     *                x & y & z
     *            \end{bmatrix}
     *            \cdot
     *            \begin{bmatrix}
     *                A_{00} & A_{01} & A_{02} \\
     *                A_{10} & A_{11} & A_{12} \\
     *                A_{20} & A_{21} & A_{22}
     *            \end{bmatrix}
     *            =
     *            \begin{bmatrix}
     *                x' & y' & z'
     *            \end{bmatrix}
     *        \f$
     *
     * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam T Numeric type of the row vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the transformation matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec The row vector to transformed.
     * @param[in] mat The transformation matrix.
     *
     * @return The passed-in @p vec with the transformations applied.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    static constexpr Vector3D<T>& operator*=(Vector3D<T>& vec, const Matrix3D<U>& mat) noexcept;

    /** @} */



    /**
     * @addtogroup T_FGM_Mat3x3_Constant
     * @{
     */

    /**************************************
     *                                    *
     *             CONSTANTS              *
     *                                    *
     **************************************/

    namespace mat3d
    {
        /**
         * @brief A 3D matrix with ones on the main diagonal and zeros elsewhere.
         *
         * @note Only available for @ref StrictArithmetic types.
         */
        template <StrictArithmetic T>
        inline constexpr Matrix3D<T> eye(T(1), T(0), T(0), T(0), T(1), T(0), T(0), T(0), T(1));


        /**
         * @brief A 3D matrix with all zero elements.
         *
         * @note Only available for @ref StrictArithmetic types.
         */
        template <StrictArithmetic T>
        inline constexpr Matrix3D<T> zero(T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0));
    } // namespace mat3d

    /** @} */

}; // namespace fgm


#include "Matrix3D.tpp"