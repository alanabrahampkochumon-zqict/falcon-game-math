#pragma once
/**
 * @file Matrix4D.h
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


#include "common/MathTraits.h"
#include "vector/Vector4D.h"

#include <cstddef>



namespace fgm
{

    template <Arithmetic T>
    struct Matrix4D
    {
        /**
         * @addtogroup FGM_Mat4x4_Members
         * @{
         */

        using value_type = T; ///< The numeric type of the vector components.

        static constexpr std::size_t columns = 4; ///< Matrix column count.
        static constexpr std::size_t rows = 4;    ///< Matrix row count.

        /** @} */



        /**
         * @addtogroup FGM_Mat4x4_Init
         * @{
         */

        /** @brief Initialize a 4x4 identity matrix. */
        [[nodiscard]] constexpr Matrix4D() noexcept;


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
        [[nodiscard]] constexpr Matrix4D(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22,
                                         T m23, T m30, T m31, T m32, T m33) noexcept;


        /**
         * @brief Initialize a 4x4 matrix from the passed-in vectors as columns.
         *
         * @param[in] col0 The 4D-vector to use as the first column entry.
         * @param[in] col1 The 4D-vector to use as the second column entry.
         * @param[in] col2 The 4D-vector to use as the third column entry.
         * @param[in] col3 The 4D-vector to use as the fourth column entry.
         */
        [[nodiscard]] constexpr Matrix4D(const Vector4D<T>& col0, const Vector4D<T>& col1, const Vector4D<T>& col2,
                                         const Vector4D<T>& col3) noexcept;


        /**
         * @brief Initialize a diagonal matrix from the passed-in scalar entries.
         *        All non-diagonal elements are initialized to zero.
         *
         * @param[in] d0 The first diagonal entry of the matrix (m00).
         * @param[in] d1 The second diagonal entry of the matrix (m11).
         * @param[in] d2 The third diagonal entry of the matrix (m22).
         * @param[in] d3 The third diagonal entry of the matrix (m33).
         */
        [[nodiscard]] constexpr Matrix4D(T d0, T d1, T d2, T d3) noexcept;


        /**
         * @brief Initialize @ref Matrix4D from another @ref Matrix4D of a different type.
         *
         * @tparam U Numeric type of the source matrix.
         *
         * @param[in] other The source matrix to be converted.
         */
        template <Arithmetic U>
        [[nodiscard]] explicit constexpr Matrix4D(const Matrix4D<U>& other) noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Mat4x4_Access
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
        [[nodiscard]] constexpr Vector4D<T>& operator[](std::size_t col) noexcept;


        /**
         * @brief Access the column vector at the specified location (read-only).
         *
         * @param[in] col The column index of the matrix.
         *
         * @return A const reference to the column vector.
         */
        [[nodiscard]] constexpr const Vector4D<T>& operator[](std::size_t col) const noexcept;


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
         * @addtogroup T_FGM_Mat4x4_Constant
         * @{
         */

        /**************************************
         *                                    *
         *             CONSTANTS              *
         *                                    *
         **************************************/

        /**
         * @brief A 4D matrix with ones on the main diagonal and zeros elsewhere.
         *
         * @note Only available for @ref StrictArithmetic types.
         *
         * @return A 4 identity matrix.
         */
        [[nodiscard]] static constexpr Matrix4D eye() noexcept;


        /**
         * @brief A 4D matrix with all zero elements.
         *
         * @note Only available for @ref StrictArithmetic types.
         *
         * @return A 4D zero matrix.
         */
        [[nodiscard]] static constexpr Matrix4D zero() noexcept;

        /** @} */

        ///*************************************
        // *                                   *
        // *            ACCESSORS              *
        // *                                   *
        // *************************************/

        // Vector4D<T>& operator[](std::size_t index);
        // const Vector4D<T>& operator[](std::size_t index) const;

        // T& operator()(std::size_t row, std::size_t col);
        // const T& operator()(std::size_t row, std::size_t col) const;


        ///*************************************
        // *                                   *
        // *      ARITHMETIC OPERATORS         *
        // *                                   *
        // *************************************/
        // template <StrictArithmetic U>
        // auto operator+(const Matrix4D<U>& other) const -> Matrix4D<std::common_type_t<T, U>>;

        // template <StrictArithmetic U>
        // Matrix4D& operator+=(const Matrix4D<U>& other);

    private:
        Vector4D<T> _data[columns];
    };



    /**
     * @addtogroup T_FGM_Mat4x4_Constant
     * @{
     */

    /**************************************
     *                                    *
     *             CONSTANTS              *
     *                                    *
     **************************************/

    namespace mat4d
    {
        /**
         * @brief A 4D matrix with ones on the main diagonal and zeros elsewhere.
         *
         * @note Only available for @ref StrictArithmetic types.
         */
        template <StrictArithmetic T>
        inline constexpr Matrix4D<T> eye(T(1), T(0), T(0), T(0), T(0), T(1), T(0), T(0), T(0), T(0), T(1), T(0), T(0),
                                         T(0), T(0), T(1));


        /**
         * @brief A 4D matrix with all zero elements.
         *
         * @note Only available for @ref StrictArithmetic types.
         */
        template <StrictArithmetic T>
        inline constexpr Matrix4D<T> zero(T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0),
                                         T(0), T(0), T(0));

    } // namespace mat3d

    /** @} */

} // namespace fgm

#include "Matrix4D.tpp"