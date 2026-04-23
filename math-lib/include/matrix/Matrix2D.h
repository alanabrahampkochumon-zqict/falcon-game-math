#pragma once
/**
 * @file Matrix2D.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 30, 2026
 *
 * @brief Templated 2x2 Matrix supporting integral, floating-point, and boolean types.
 *
 * @details Provide high-performance 2x2 matrix implementation with SIMD acceleration
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


#include "vector/Vector2D.h"

#include <cstddef>
#include <type_traits>

// TODO: Rotate around a point
// TODO: Reflect around line
// TODO: Add makeShear

namespace fgm
{
    template <Arithmetic T>
    struct Matrix2D
    {

        /**
         * @addtogroup FGM_Mat2x2_Members
         * @{
         */

        using value_type = T; ///< The numeric type of the vector components.

        static constexpr std::size_t columns = 2; ///< Matrix column count.
        static constexpr std::size_t rows = 2;    ///< Matrix row count.


        /** @} */

        

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
        [[nodiscard]] explicit constexpr Matrix2D(const Matrix2D<U>& other) noexcept;

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
         * @addtogroup T_FGM_Mat2x2_Constant
         * @{
         */

        /**************************************
         *                                    *
         *             CONSTANTS              *
         *                                    *
         **************************************/

        /**
         * @brief A 2D matrix with ones on the main diagonal and zeros elsewhere.
         *
         * @note Only available for @ref StrictArithmetic types.
         *
         * @return A 2D identity matrix.
         */
        [[nodiscard]] static constexpr Matrix2D eye() noexcept;


        /**
         * @brief A 2D matrix with all zero elements.
         *
         * @note Only available for @ref StrictArithmetic types.
         *
         * @return A 2D zero matrix.
         */
        [[nodiscard]] static constexpr Matrix2D zero() noexcept;

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
         * @brief Compare all elements of this matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all elements are equivalent within @p epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr bool allEq(const Matrix2D<U>& rhs,
                                           double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                               ? Config::DOUBLE_EPSILON
                                               : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all elements of a matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
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
        [[nodiscard]] constexpr static bool allEq(const Matrix2D& lhs, const Matrix2D<U>& rhs,
                                                  double epsilon = (std::is_same_v<T, double> ||
                                                                    std::is_same_v<U, double>)
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) noexcept;


        /**
         * @brief Compare all elements of this matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true if any corresponding elements differ by more
         *        than @p epsilon.
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
        [[nodiscard]] constexpr bool anyNeq(const Matrix2D<U>& rhs,
                                            double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                                ? Config::DOUBLE_EPSILON
                                                : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all elements of this matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true if any corresponding elements differ by more
         *        than @p epsilon.
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
        [[nodiscard]] constexpr static bool anyNeq(const Matrix2D& lhs, const Matrix2D<U>& rhs,
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
         * @return True if all elements are equivalent within the default epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr bool operator==(const Matrix2D<U>& rhs) const noexcept;


        /**
         * @copybrief anyNeq(const Vector2D<U>&, double) const noexcept
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The matrix to compare against.
         *
         * @return True if any of the elements are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
        [[nodiscard]] constexpr bool operator!=(const Matrix2D<U>& rhs) const noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Mat2x2_Arithmetic
         * @{
         */

        /*************************************
         *                                   *
         *       ARITHMETIC OPERATORS        *
         *                                   *
         *************************************/

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
         * @return A new @ref Matrix2D containing the element-wise sum.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr PromotedMatrix2D<T, U> operator+(const Matrix2D<U>& rhs) const noexcept
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
        Matrix2D& operator+=(const Matrix2D<U>& rhs) noexcept
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
         * @return A new @ref Matrix2D containing the element-wise difference.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr PromotedMatrix2D<T, U> operator-(const Matrix2D<U>& rhs) const noexcept
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
        constexpr Matrix2D& operator-=(const Matrix2D<U>& rhs) noexcept
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
         * @return A new @ref Matrix2D scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMatrix2D<T, S> operator*(S scalar) const noexcept
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
        constexpr Matrix2D& operator*=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Transform the **column vector** by this matrix.
         *        Perform the linear transformation: \f$ \begin{bmatrix} a & b \\ c & d \end{bmatrix} \cdot
         *                                           \begin{bmatrix} x \\ y \end{bmatrix}  = \begin{bmatrix} x'
         *                                           \\ y' \end{bmatrix} \f$
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec The column vector to transform.
         *
         * @return A new @ref Vector2D with applied linear transformations.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr PromotedVector2D<T, U> operator*(const Vector2D<U>& vec) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compose this matrix with another to form a new matrix.
         *        Compute the matrix product: \f$ \begin{bmatrix} a & b \\ c & d \end{bmatrix} \cdot \begin{bmatrix} e &
         *                                     f \\ g & h \end{bmatrix}  = \begin{bmatrix} x & y \\ z & w
         *                                     \end{bmatrix} \f$
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to multiply.
         *
         * @return A new @ref Matrix2D containing the composition of linear transformations.
         */
        template <StrictArithmetic U>
        [[nodiscard]] constexpr PromotedMatrix2D<T, U> operator*(const Matrix2D<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compose this matrix with another matrix in-place.
         *        Compute the matrix product: \f$ \begin{bmatrix} a & b \\ c & d \end{bmatrix} \cdot \begin{bmatrix} e &
         *                                        f \\ g & h \end{bmatrix}  = \begin{bmatrix} x & y \\ z & w
         *                                        \end{bmatrix} \f$
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
        constexpr Matrix2D& operator*=(const Matrix2D<U>& rhs) noexcept
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
         * @return A new @ref Matrix2D inverse scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedFloatMatrix2D<T, S> operator/(const S& scalar) const noexcept
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
        constexpr Matrix2D& operator/=(const S& scalar) noexcept
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
         * @return A new @ref Matrix2D resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has a NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedFloatMatrix2D<T, S> safeDiv(
            S scalar, const Matrix2D<T>& fallback = Matrix2D<T>::eye()) const noexcept
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
         * @return A new @ref Matrix2D resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has a NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr static PromotedFloatMatrix2D<T, S> safeDiv(
            const Matrix2D& mat, S scalar, const Matrix2D<T>& fallback = Matrix2D<T>::eye()) noexcept
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
         * @return A new @ref Matrix2D resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedFloatMatrix2D<T, S> tryDiv(
            S scalar, OperationStatus& status, const Matrix2D<T>& fallback = Matrix2D<T>::eye()) const noexcept
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
         * @return A new @ref Matrix2D resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedFloatMatrix2D<T, S> tryDiv(
            const Matrix2D& mat, S scalar, OperationStatus& status,
            const Matrix2D<T>& fallback = Matrix2D<T>::eye()) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FGM_Mat2x2_Algebra
         * @{
         */

        /**
         * @brief Compute the determinant (scaling factor) of this matrix.
         *        Calculate determinant: \f$ \text{det(A)} = \text{a}\cdot\text{d} - \text{b}\cdot\text{c} \f$
         *
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         *
         * @return A non-zero scalar if the matrix is non-singular, else zero.
         */
        [[nodiscard]] constexpr T determinant() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the determinant (scaling factor) of a matrix.
         *        Calculate determinant: \f$ \text{det(A)} = \text{a}\cdot\text{d} - \text{b}\cdot\text{c} \f$
         *
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         *
         * @param mat The matrix to compute the determinant of.
         *
         * @return A non-zero scalar if the matrix is non-singular, else zero.
         */
        static constexpr T determinant(const Matrix2D& mat) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Transpose this matrix by swapping its rows and columns.
         *        Compute transpose: \f$ \begin{bmatrix} a & b \\ c & d \end{bmatrix}\textsuperscript{T}  =
         *                               \begin{bmatrix} a & c \\ b & d \end{bmatrix} \f$
         *
         * @return A new @ref Matrix2D with its elements flipped along the diagonal.
         */
        [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any changes.")]]
        constexpr Matrix2D transpose() const noexcept;


        /**
         * @brief Transpose a matrix by swapping its rows and columns.
         *        Compute transpose: \f$ \begin{bmatrix} a & b \\ c & d \end{bmatrix}\textsuperscript{T}  =
         *                               \begin{bmatrix} a & c \\ b & d \end{bmatrix} \f$
         *
         * @param mat The matrix to transpose.
         *
         * @return A new @ref Matrix2D with its elements flipped along the diagonal.
         */
        [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any changes.")]]
        constexpr static Matrix2D transpose(const Matrix2D& mat) noexcept;


        /**
         * @brief Compute the inverse of this matrix.
         *        Calculate inverse: \f$ \mathbf{A\textsuperscript{-1}} = $ \frac{\text{1}}{\text{det(A)}} \cdot
         *                               \begin{bmatrix} d & -b \\ -c & a \end{bmatrix} $ \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         *
         * @return A new @ref Matrix2D such that \f$ A \cdot \mathbf{A\textsuperscript{-1}} = I \f$.
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any changes.")]]
        constexpr Matrix2D<Magnitude<T>> inverse() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of a matrix.
         *        Calculate inverse: \f$ \mathbf{A\textsuperscript{-1}} = $ \frac{\text{1}}{\text{det(A)}} \cdot
         *                               \begin{bmatrix} d & -b \\ -c & a \end{bmatrix} $ \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         *
         * @param[in] matrix The matrix to invert.
         *
         * @return A new @ref Matrix2D such that \f$ A \cdot \mathbf{A\textsuperscript{-1}} = I \f$.
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any changes.")]]
        constexpr static Matrix2D<Magnitude<T>> inverse(const Matrix2D& matrix) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Safely compute the inverse of this matrix.
         *        Calculate inverse: \f$ \mathbf{A\textsuperscript{-1}} = $ \frac{\text{1}}{\text{det(A)}} \cdot
         *                               \begin{bmatrix} d & -b \\ -c & a \end{bmatrix} $ \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Matrix2D such that \f$ A \cdot \mathbf{A\textsuperscript{-1}} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any changes.")]]
        constexpr Matrix2D<Magnitude<T>> safeInverse(const Matrix2D& fallback = Matrix2D::eye()) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Safely compute the inverse of a matrix.
         *        Calculate inverse: \f$ \mathbf{A\textsuperscript{-1}} = $ \frac{\text{1}}{\text{det(A)}} \cdot
         *                               \begin{bmatrix} d & -b \\ -c & a \end{bmatrix} $ \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[in] matrix   The matrix to invert.
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Matrix2D such that \f$ A \cdot \mathbf{A\textsuperscript{-1}} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any changes.")]]
        static constexpr Matrix2D<Magnitude<T>> safeInverseOf(const Matrix2D& matrix,
                                                              const Matrix2D& fallback = Matrix2D::eye()) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Safely compute the inverse of this matrix and set @p status to the matrix inversion result.
         *        Calculate inverse: \f$ \mathbf{A\textsuperscript{-1}} = $ \frac{\text{1}}{\text{det(A)}} \cdot
         *                               \begin{bmatrix} d & -b \\ -c & a \end{bmatrix} $ \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Matrix2D such that \f$ A \cdot \mathbf{A\textsuperscript{-1}} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any changes.")]]
        constexpr Matrix2D<Magnitude<T>> tryInverse(OperationStatus& status,
                                                    const Matrix2D& fallback = Matrix2D::eye()) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Safely compute the inverse of a matrix and set @p status to the matrix inversion result.
         *        Calculate inverse: \f$ \mathbf{A\textsuperscript{-1}} = $ \frac{\text{1}}{\text{det(A)}} \cdot
         *                               \begin{bmatrix} d & -b \\ -c & a \end{bmatrix} $ \f$
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
         * @return  A new @ref Matrix2D such that \f$ A \cdot \mathbf{A\textsuperscript{-1}} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any changes.")]]
        static constexpr Matrix2D<Magnitude<T>> tryInverseOf(const Matrix2D& matrix, OperationStatus& status,
                                                             const Matrix2D& fallback = Matrix2D::eye()) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the sum of diagonal entries of this matrix.
         *
         * @return The sum of entries along the main diagonal of this matrix.
         */
        [[nodiscard]] constexpr T trace() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the sum of diagonal entries of a matrix.
         *
         * @param mat The matrix whose trace is to be computed.
         *
         * @return The sum of entries along the main diagonal of the given matrix.
         */
        [[nodiscard]] static constexpr T trace(const Matrix2D& mat) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FGM_Mat2x2_Utils
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
        [[nodiscard]] constexpr static bool hasInf(const Matrix2D& mat) noexcept;


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
        [[nodiscard]] constexpr static bool hasNaN(const Matrix2D& mat) noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Mat2x2_Log
         * @{
         */

        /**
         * @brief Write the matrix to an output stream in **row-major** order.
         *        Format the matrix as \f$\begin{bmatrix} a & b \\ c & d \end{bmatrix} \f$ string representation for
         *        debugging or logging.
         *
         * @tparam T Numeric type of the matrix.
         *
         * @param os     The output stream to write to.
         * @param matrix The matrix to be streamed.
         *
         * @return A reference to the output stream @p os.
         */
        constexpr friend std::ostream& operator<<(std::ostream& os, const Matrix2D& matrix)
        {
            const std::streamsize oldPrecision = os.precision();
            const std::ios_base::fmtflags oldFlags = os.flags();

            auto precision = Config::useFullPrecision
                ? std::is_same_v<T, double> ? Config::DOUBLE_PRECISION : Config::FLOAT_PRECISION
                : Config::LOG_PRECISION;
            os << std::setprecision(precision) << std::fixed;
            os << "|" << matrix._data[0][0] << " " << matrix._data[1][0] << "|\n";
            os << "|" << matrix._data[0][1] << " " << matrix._data[1][1] << "|\n";

            os.precision(oldPrecision);
            os.flags(oldFlags);

            return os;
        }

        /** @} */



        /**
         * @addtogroup FGM_Mat2x2_Transforms
         * @{
         */

        /**
         * @brief Construct a 2D rotation matrix for a given angle.
         *
         * @details The layout of the returned matrix adapts to the library's active coordinate system:
         *          - **Right-Handed (Default):** \f$ \begin{bmatrix} \cos(\theta) & -\sin(\theta) \\ \sin(\theta) &
         *                                            \cos(\theta) \end{bmatrix} \f$
         *          - **Left-Handed (FGM_LEFT_HANDED):** \f$ \begin{bmatrix} \cos(\theta) & \sin(\theta)
         *                                                   \\ -\sin(\theta) & \cos(\theta) \end{bmatrix} \f$
         *
         * @note While it is possible to create a rotation matrix of any **signed type**, it is strongly discouraged.
         *       Trigonometric results will be truncated, resulting in severe precision loss and potential zero-matrices
         *       for integral types.
         *
         * @tparam U Numeric type of the angle. Must satisfy `std::floating_point`.
         *
         * @param[in] angle The rotation angle in radians.
         *
         * @return A new @ref Matrix2D representing the linear rotation.
         */
        template <std::floating_point U>
        [[nodiscard]] static constexpr Matrix2D makeRotation(U angle) noexcept
            requires SignedStrictArithmetic<T>;

        /**
         * @brief Construct a uniform scale 2D matrix.
         *
         * @param[in] scale The scale factor.
         *
         * @return A new @ref Matrix2D representing the uniform scale.
         */
        [[nodiscard]] static constexpr Matrix2D makeScale(T scale) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Construct a non-uniform scale 2D matrix.
         *
         * @param[in] scaleX The scale factor in the x-direction.
         * @param[in] scaleY The scale factor in the y-direction.
         *
         * @return A new @ref Matrix2D representing the uniform scale.
         */
        [[nodiscard]] static constexpr Matrix2D makeScale(T scaleX, T scaleY) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Construct a reflection 2D matrix for reflection along coordinate axis(X, Y), and the origin<0, 0>.
         * 
         * @note To construction a reflection matrix around origin, set all axis reflection to true.
         *
         * @param[in] reflectX A flag to whether reflect in the x-direction.
         * @param[in] reflectY A flag to whether reflect in the y-direction.
         *
         * @return A new @ref Matrix2D representing the axis-aligned reflection.
         */
        [[nodiscard]] static constexpr Matrix2D makeReflection(bool reflectX, bool reflectY) noexcept
            requires StrictArithmetic<T>;

        /** @} */


    private:
        Vector2D<T> _data[columns];
    };



    /**
     * @addtogroup FGM_Mat2x2_Alias
     * @{
     */

    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/

    using bMat2 = Matrix2D<bool>;                ///< `bool` matrix
    using iMat2 = Matrix2D<int>;                 ///< `int` matrix
    using uMat2 = Matrix2D<unsigned int>;        ///< `unsigned int` matrix
    using mat2 = Matrix2D<float>;                ///< `float` matrix
    using lMat2 = Matrix2D<long long>;           ///< `long long` matrix
    using dMat2 = Matrix2D<double>;              ///< `double` matrix
    using ulMat2 = Matrix2D<unsigned long long>; ///< `unsigned long long` matrix

    /** @} */



    /**
     * @addtogroup FGM_Mat2x2_Arithmetic
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
     * @return A new @ref Matrix2D scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    [[nodiscard]] constexpr PromotedMatrix2D<T, S> operator*(S scalar, const Matrix2D<T>& mat) noexcept;


    /**
     * @brief Transform the **row vector** by a matrix.
     *        Perform the linear transformation: \f$ \begin{bmatrix} x & y \end{bmatrix} \cdot \begin{bmatrix} a & b
     *                                               \\ c & d \end{bmatrix}  = \begin{bmatrix} x' & y' \end{bmatrix} \f$
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
    static constexpr PromotedVector2D<T, U> operator*(const Vector2D<T>& vec, const Matrix2D<U>& mat) noexcept;


    /**
     * @brief Transform this **row vector** by a matrix.
     *        Perform the linear transformation: \f$ \begin{bmatrix} x & y \end{bmatrix} \cdot \begin{bmatrix} a & b
     *                                               \\ c & d \end{bmatrix}  = \begin{bmatrix} x' & y' \end{bmatrix} \f$
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
    static constexpr Vector2D<T>& operator*=(Vector2D<T>& vec, const Matrix2D<U>& mat) noexcept;

    /** @} */



    /**
     * @addtogroup T_FGM_Mat2x2_Constant
     * @{
     */

    /**************************************
     *                                    *
     *             CONSTANTS              *
     *                                    *
     **************************************/

    namespace mat2d
    {
        /**
         * @brief A 2D matrix with ones on the main diagonal and zeros elsewhere.
         *
         * @note Only available for @ref StrictArithmetic types.
         */
        template <StrictArithmetic T>
        inline constexpr Matrix2D<T> eye(T(1), T(0), T(0), T(1));


        /**
         * @brief A 2D matrix with all zero elements.
         *
         * @note Only available for @ref StrictArithmetic types.
         */
        template <StrictArithmetic T>
        inline constexpr Matrix2D<T> zero(T(0), T(0), T(0), T(0));
    } // namespace mat2d

    /** @} */


} // namespace fgm


#include "Matrix2D.tpp"