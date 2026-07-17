#pragma once
/**
 * @file MatMul.h
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Defines all uneven matrix multiplication operations.
 *
 * @details Matrix multiplications that are dependent on other matrices like 2x3 with 3x2 matrix are grouped into
 *          uneven multiplication operations.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Mat2x3.h"
#include "Matrix2.h"
#include "Matrix3.h"
#include "Matrix4.h"

// TODO: Use transpose from here
//     /**
//      * @addtogroup FGM_Mat2x3_Algebra
//      * @{
//      */
//
//     /**
//      * @brief Transpose this matrix by swapping its rows and columns.
//      *        \f$
//      *            \begin{bmatrix}
//      *                 A_{00} & A_{01} \\
//      *                 A_{10} & A_{11}
//      *            \end{bmatrix} ^ \top
//      *            =
//      *            \begin{bmatrix}
//      *                 A_{00} & A_{10} \\
//      *                 A_{01} & A_{11}
//      *            \end{bmatrix}
//      *        \f$
//      *
//      * @return A new @ref Mat2x3 with its elements flipped along the diagonal.
//      */
//     [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any change.")]]
//     constexpr Mat2x3 transpose() const noexcept;
//
//
//     /**
//      * @brief Transpose @p matrix by swapping its rows and columns.
//      *        \f$
//      *            \begin{bmatrix}
//      *                 A_{00} & A_{01} \\
//      *                 A_{10} & A_{11}
//      *            \end{bmatrix} ^ \top
//      *            =
//      *            \begin{bmatrix}
//      *                 A_{00} & A_{10} \\
//      *                 A_{01} & A_{11}
//      *            \end{bmatrix}
//      *        \f$
//      *
//      * @param matrix The matrix to transpose.
//      *
//      * @return A new @ref Mat2x3 with its elements flipped along the diagonal.
//      */
//     [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any change.")]]
//     static constexpr Mat2x3 transpose(const Mat2x3& matrix) noexcept;
//
//     /** @} */


//
//
//
//     /**
//      * @addtogroup FGM_Mat2x3_Log
//      * @{
//      */
//
//     /**
//      * @brief Write the matrix to an output stream in **row-major** order.
//      *        Format the matrix as
//      *        \f$
//      *            \begin{bmatrix}
//      *                 A_{00} & A_{10} \\
//      *                 A_{01} & A_{11}
//      *            \end{bmatrix}
//      *        \f$ string representation for debugging or logging.
//      *
//      * @param os     The output stream to write to.
//      * @param matrix The matrix to be streamed.
//      *
//      * @return A reference to the output stream @p os.
//      */
//     friend std::ostream& operator<<(std::ostream& os, const Mat2x3& matrix)
//     {
//         const std::streamsize oldPrecision     = os.precision();
//         const std::ios_base::fmtflags oldFlags = os.flags();
//
//         auto precision = Config::useFullPrecision
//             ? std::is_same_v<T, double> ? Config::DOUBLE_PRECISION : Config::FLOAT_PRECISION
//             : Config::LOG_PRECISION;
//         os << std::setprecision(precision) << std::fixed;
//         os << "|" << matrix._data[0][0] << " " << matrix._data[1][0] << "|\n";
//         os << "|" << matrix._data[0][1] << " " << matrix._data[1][1] << "|\n";
//
//         os.precision(oldPrecision);
//         os.flags(oldFlags);
//
//         return os;
//     }
//
//     /** @} */
//


/// TODO: Not implemented or tested
// TODO: Add Groups
// TODO: Add Implementation
// Implementations
//       2x3 * 3x1 => 2x1
//       2x3 * 3x2 => 2x2
//       2x3 * 3x3 => 2x3
//       2x3 * 3x4 => 2x4
// 1x2 * 2x3       => 1x3

//       2x4 * 4x1 => 2x1
//       2x4 * 4x2 => 2x2
//       2x4 * 4x3 => 2x3
//       2x4 * 4x4 => 2x4
// 1x2 * 2x4       => 1x4

//       3x2 * 2x1 => 3x1
//       3x2 * 2x2 => 3x2
//       3x2 * 2x3 => 3x3
//       3x2 * 2x4 => 3x4
// 1x3 * 3x2       => 1x2

//       3x4 * 4x1 => 3x1
//       3x4 * 4x2 => 3x2
//       3x4 * 4x3 => 3x3
//       3x4 * 4x4 => 3x4
// 1x3 * 3x4       => 1x4

//       4x2 * 2x1 => 4x1
//       4x2 * 2x2 => 4x2
//       4x2 * 2x3 => 4x3
//       4x2 * 2x4 => 4x4
// 1x4 * 4x2       => 1x2

//       4x3 * 3x1 => 4x1
//       4x3 * 3x2 => 4x2
//       4x3 * 3x3 => 4x3
//       4x3 * 3x4 => 4x4
// 1x4 * 4x3       => 1x3

namespace fgm
{

    // /**
    //  * @brief Transform the @p Vec **column vector** by this matrix.
    //  *        \f$
    //  *            \begin{bmatrix}
    //  *                 A_{00} & A_{01} & A_{02} \\
    //  *                 A_{10} & A_{11} & A_{12}
    //  *            \end{bmatrix}
    //  *            \cdot
    //  *            \begin{bmatrix}
    //  *                  x \\ y \\ z
    //  *            \end{bmatrix}
    //  *            =
    //  *            \begin{bmatrix}
    //  *                  x' \\ y'
    //  *            \end{bmatrix}
    //  *        \f$
    //  *
    //  * @note Promotes the result to the wider type using @ref PromotedVector2<T, U>.
    //  * @note Operation is restricted to numeric types via @ref StrictArithmetic.
    //  *
    //  * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
    //  *
    //  * @param[in] vec The column vector to transform.
    //  *
    //  * @return A new @ref Vector2 with applied linear transformations.
    //  */
    // template <StrictArithmetic U>
    //     requires StrictSignedness<T, U>
    // [[nodiscard]] constexpr PromotedVector2<T, U> operator*(const Vector3<U>& vec) const noexcept
    //     requires StrictArithmetic<T>;
    //
    //
    // /**
    //  * @brief Compose this matrix with 3x2 @p rhs matrix to form a new 2x2 matrix.
    //  *        \f$
    //  *            \begin{bmatrix}
    //  *                 A_{00} & A_{01} & A_{02} \\
    //  *                 A_{10} & A_{11} & A_{12}
    //  *            \end{bmatrix}
    //  *            \cdot
    //  *            \begin{bmatrix}
    //  *                 B_{00} & B_{01} B_{02} \\
    //  *                 B_{10} & B_{11} B_{12} \\
    //  *                 B_{20} & B_{21} B_{22}
    //  *            \end{bmatrix}
    //  *            =
    //  *            \begin{bmatrix}
    //  *                 A_{00} & A_{01} & A_{02} \\
    //  *                 A_{10} & A_{11} & A_{12}
    //  *            \end{bmatrix}
    //  *        \f$
    //  *
    //  * @note Operation is restricted to numeric types via @ref StrictArithmetic.
    //  *
    //  * @note Promotes the result to the wider type using @ref PromotedMatrix2x3<T, U>.
    //  * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
    //  *
    //  * @param[in] rhs The matrix to multiply.
    //  *
    //  * @return A new @ref Matrix2x3 containing the composition of linear transformations.
    //  */
    // template <StrictArithmetic U>
    //     requires StrictSignedness<T, U>
    // [[nodiscard]] constexpr PromotedMatrix2x3<T, U> operator*(const Matrix3<U>& rhs) const noexcept
    //     requires StrictArithmetic<T>;
    //
    //
    // // TODO: Add 3x2 and 3x4 matrix multiplication
    // // /**
    // //  * @brief Compose this matrix with 3x2 @p rhs matrix to form a new 2x2 matrix.
    // //  *        \f$
    // //  *            \begin{bmatrix}
    // //  *                 A_{00} & A_{01} & A_{02} \\
    // //  *                 A_{10} & A_{11} & A_{12}
    // //  *            \end{bmatrix}
    // //  *            \cdot
    // //  *            \begin{bmatrix}
    // //  *                 B_{00} & B_{01} \\
    // //  *                 B_{10} & B_{11} \\
    // //  *                 B_{20} & B_{21}
    // //  *            \end{bmatrix}
    // //  *            =
    // //  *            \begin{bmatrix}
    // //  *                 C_{00} & C_{01} \\
    // //  *                 C_{10} & C_{11}
    // //  *            \end{bmatrix}
    // //  *        \f$
    // //  *
    // //  * @note Operation is restricted to numeric types via @ref StrictArithmetic.
    // //  *
    // //  * @note Promotes the result to the wider type using @ref PromotedMatrix2<T, U>.
    // //  * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
    // //  *
    // //  * @param[in] rhs The matrix to multiply.
    // //  *
    // //  * @return A new @ref Matrix2 containing the composition of linear transformations.
    // //  */
    // // template <StrictArithmetic U>
    // //     requires StrictSignedness<T, U>
    // // [[nodiscard]] constexpr PromotedMatrix2<T, U> operator*(const Matrix3x2<U>& rhs) const noexcept
    // //     requires StrictArithmetic<T>;
    //
    //
    // // /**
    // //  * @brief Compose this matrix with 3x4 @p rhs matrix to form a new 2x4 matrix.
    // //  *        \f$
    // //  *            \begin{bmatrix}
    // //  *                 A_{00} & A_{01} & A_{02} \\
    // //  *                 A_{10} & A_{11} & A_{12}
    // //  *            \end{bmatrix}
    // //  *            \cdot
    // //  *            \begin{bmatrix}
    // //  *                 B_{00} & B_{01} & B_{02} & B_{03} \\
    // //  *                 B_{10} & B_{11} & B_{12} & B_{13} \\
    // //  *                 B_{20} & B_{21} & B_{22} & B_{23}
    // //  *            \end{bmatrix}
    // //  *            =
    // //  *            \begin{bmatrix}
    // //  *                 C_{00} & C_{01} & C_{02} \\
    // //  *                 C_{10} & C_{11} & C_{12} \\
    // //  *                 C_{20} & C_{21} & C_{22}
    // //  *            \end{bmatrix}
    // //  *        \f$
    // //  *
    // //  * @note Operation is restricted to numeric types via @ref StrictArithmetic.
    // //  *
    // //  * @note Promotes the result to the wider type using @ref PromotedMatrix2x4<T, U>.
    // //  * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
    // //  *
    // //  * @param[in] rhs The matrix to multiply.
    // //  *
    // //  * @return A new @ref Matrix2x4 containing the composition of linear transformations.
    // //  */
    // // template <StrictArithmetic U>
    // //     requires StrictSignedness<T, U>
    // // [[nodiscard]] constexpr PromotedMatrix2x4<T, U> operator*(const Matrix3x4<U>& rhs) const noexcept
    // //     requires StrictArithmetic<T>;
    //
    //
    // /**
    //  * @brief Multiply the @p Vec **row vector** by @p matrix.
    //  *        Perform the linear transformation:
    //  *        \f$
    //  *            \begin{bmatrix}
    //  *                x & y
    //  *            \end{bmatrix}
    //  *            \cdot
    //  *            \begin{bmatrix}
    //  *                A_{00} & A_{01} & A_{02} \\
    //  *                A_{10} & A_{11} & A_{12}
    //  *            \end{bmatrix}
    //  *            =
    //  *            \begin{bmatrix}
    //  *                x' & y' & z'
    //  *            \end{bmatrix}
    //  *        \f$
    //  *
    //  * @note Operation is restricted to numeric types via @ref StrictArithmetic.
    //  *
    //  * @tparam T Numeric type of the row vector. Must satisfy @ref StrictArithmetic.
    //  * @tparam U Numeric type of the matrix. Must satisfy @ref StrictArithmetic.
    //  *
    //  * @param[in] vec    The row vector.
    //  * @param[in] matrix The matrix to multiply by.
    //  *
    //  * @return A 3D row vector.
    //  */
    // template <StrictArithmetic T, StrictArithmetic U>
    //     requires StrictSignedness<T, U>
    // static constexpr Vector3<T> operator*(Vector2<T>& vec, const Matrix2x3<U>& matrix) noexcept;
    //
    //
    // /**
    //  * @brief Multiply a 2x2 matrix with a 2x3 matrix.
    //  *        \f$
    //  *            \begin{bmatrix}
    //  *                B_{00} & B_{01} \\
    //  *                B_{10} & B_{11}
    //  *            \end{bmatrix}
    //  *            \cdot
    //  *            \begin{bmatrix}
    //  *                B_{00} & B_{01} & B_{02} \\
    //  *                B_{10} & B_{11} & B_{12}
    //  *            \end{bmatrix}
    //  *            =
    //  *            \begin{bmatrix}
    //  *                C_{00} & C_{01} & C_{02} \\
    //  *                C_{10} & C_{11} & C_{12}
    //  *            \end{bmatrix}
    //  *        \f$
    //  *
    //  * @note Promotes the result to the wider type using @ref PromotedVector2<T, U>.
    //  * @note Operation is restricted to numeric types via @ref StrictArithmetic.
    //  *
    //  * @tparam T Numeric type of the row vector. Must satisfy @ref StrictArithmetic.
    //  * @tparam U Numeric type of the transformation matrix. Must satisfy @ref StrictArithmetic.
    //  *
    //  * @param[in] matrixA The first matrix.
    //  * @param[in] matrixB The second matrix.
    //  *
    //  * @return A 2x3 Matrix composed of @p matrixA and @p matrixB.
    //  */
    // template <StrictArithmetic T, StrictArithmetic U>
    //     requires StrictSignedness<T, U>
    // static constexpr PromotedMatrix2x3<T, U> operator*(const Matrix2<T>& matrixA, const Matrix2x3<U>& matrixB)
    // noexcept;
    //
    //
    // // /**
    // //  * @brief Multiply a 2x2 matrix with a 2x3 matrix.
    // //  *        \f$
    // //  *            \begin{bmatrix}
    // //  *                B_{00} & B_{01} \\
    // //  *                B_{10} & B_{11} \\
    // //  *                B_{20} & B_{21}
    // //  *            \end{bmatrix}
    // //  *            \cdot
    // //  *            \begin{bmatrix}
    // //  *                B_{00} & B_{01} & B_{02} \\
    // //  *                B_{10} & B_{11} & B_{12}
    // //  *            \end{bmatrix}
    // //  *            =
    // //  *            \begin{bmatrix}
    // //  *                C_{00} & C_{01} & C_{02} \\
    // //  *                C_{10} & C_{11} & C_{12} \\
    // //  *                C_{20} & C_{21} & C_{22}
    // //  *            \end{bmatrix}
    // //  *        \f$
    // //  *
    // //  * @note Promotes the result to the wider type using @ref PromotedVector2<T, U>.
    // //  * @note Operation is restricted to numeric types via @ref StrictArithmetic.
    // //  *
    // //  * @tparam T Numeric type of the row vector. Must satisfy @ref StrictArithmetic.
    // //  * @tparam U Numeric type of the transformation matrix. Must satisfy @ref StrictArithmetic.
    // //  *
    // //  * @param[in] matrixA The first matrix.
    // //  * @param[in] matrixB The second matrix.
    // //  *
    // //  * @return A 3D Matrix composed of @p matrixA and @p matrixB.
    // //  */
    // // template <StrictArithmetic T, StrictArithmetic U>
    // //     requires StrictSignedness<T, U>
    // // static constexpr PromotedMatrix3<T, U> operator*(const Matrix3x2<T>& matrixA, const Matrix2x3<U>& matrixB)
    // // noexcept;
    //
    //
    //
    // // /**
    // //  * @brief Multiply a 2x2 matrix with a 2x3 matrix.
    // //  *        \f$
    // //  *            \begin{bmatrix}
    // //  *                B_{00} & B_{01} \\
    // //  *                B_{10} & B_{11} \\
    // //  *                B_{20} & B_{21} \\
    // //  *                B_{30} & B_{31}
    // //  *            \end{bmatrix}
    // //  *            \cdot
    // //  *            \begin{bmatrix}
    // //  *                B_{00} & B_{01} & B_{02} \\
    // //  *                B_{10} & B_{11} & B_{12}
    // //  *            \end{bmatrix}
    // //  *            =
    // //  *            \begin{bmatrix}
    // //  *                C_{00} & C_{01} & C_{02} C_{03} \\
    // //  *                C_{10} & C_{11} & C_{12} C_{13} \\
    // //  *                C_{20} & C_{21} & C_{22} C_{23}
    // //  *            \end{bmatrix}
    // //  *        \f$
    // //  *
    // //  * @note Promotes the result to the wider type using @ref PromotedVector2<T, U>.
    // //  * @note Operation is restricted to numeric types via @ref StrictArithmetic.
    // //  *
    // //  * @tparam T Numeric type of the row vector. Must satisfy @ref StrictArithmetic.
    // //  * @tparam U Numeric type of the transformation matrix. Must satisfy @ref StrictArithmetic.
    // //  *
    // //  * @param[in] matrixA The first matrix.
    // //  * @param[in] matrixB The second matrix.
    // //  *
    // //  * @return A 4x3 Matrix composed of @p matrixA and @p matrixB.
    // //  */
    // // template <StrictArithmetic T, StrictArithmetic U>
    // //     requires StrictSignedness<T, U>
    // // static constexpr PromotedMatrix4x3<T, U> operator*(const Matrix4x2<T>& matrixA, const Matrix2x3<U>& matrixB)
    // // noexcept;

} // namespace fgm


#include "MatMul.tpp"
