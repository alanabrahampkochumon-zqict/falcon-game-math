#pragma once
/**
 * @file MatrixUtils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 16, 2026
 *
 * @brief Diagnostic and validation utilities for Matrix types.
 *        Provides specialized testing helpers and assertion wrappers for @ref Matrix2D,
 *        @ref Matrix3D, and @ref Matrix4D to ensure numerical stability and
 *        geometric correctness across the fgm library.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cmath>
#include <common/MathTraits.h>
#include <gtest/gtest.h>
#include <matrix/Matrix2D.h>
#include <matrix/Matrix3D.h>


namespace testutils
{

    /**
     * @addtogroup Matrix_Utils
     * @{
     */

    /**
     * @brief Perform a component-wise strict equality comparison between two matrices of the same dimensions.
     *
     * @tparam T The numeric type of the expected matrix components.
     * @tparam U The numeric type of the actual matrix components.
     *
     * @param expected The matrix serving as the reference for comparison.
     * @param actual The matrix being evaluated.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the matrices are out of the @p tolerance range.
     * @note Triggers an assertion failure if matrix dimensions are mismatched.
     */
    template <fgm::Matrix T, fgm::Matrix U>
    void EXPECT_MAT_EQ(const T& expected, const U& actual)
    {
        using ValueType = T::value_type;

        static_assert(T::rows == U::rows && T::columns == U::columns,
                      "Matrices must of the same dimension, e.g: 3x3 and 3x3");

        for (std::size_t i = 0; i < T::rows; ++i)
            for (std::size_t j = 0; j < T::columns; ++j)
                if constexpr (std::is_same_v<ValueType, double>)
                    EXPECT_DOUBLE_EQ(expected(i, j), static_cast<ValueType>(actual(i, j)));
                else if constexpr (std::is_same_v<ValueType, float>)
                    EXPECT_FLOAT_EQ(expected(i, j), static_cast<ValueType>(actual(i, j)));
                else
                    EXPECT_EQ(expected(i, j), static_cast<ValueType>(actual(i, j)));
    }


    /**
     * @brief Performs a component-wise approximate equality comparison using an absolute epsilon.
     *
     * @tparam T The numeric type of the expected matrix components.
     * @tparam U The numeric type of the actual matrix components.
     *
     * @param expected The matrix serving as the ground truth.
     * @param actual The matrix being evaluated.
     * @param tolerance The maximum allowable absolute difference between components.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the matrices are out of the @p tolerance range.
     * @note Triggers an assertion failure if matrix dimensions are mismatched.
     */
    template <fgm::Matrix T, fgm::Matrix U>
    void EXPECT_MAT_NEAR(const T& expected, const U& actual, double tolerance = 1e-5)
    {

        using ValueType = T::value_type;
        static_assert(T::rows == U::rows && T::columns == U::columns,
                      "Matrices must of the same dimension, e.g: 3x3 and 3x3");

        for (std::size_t i = 0; i < T::rows; ++i)
            for (std::size_t j = 0; j < T::columns; ++j)
                EXPECT_NEAR(expected(i, j), static_cast<ValueType>(actual(i, j)), tolerance);
    }


    /**
     * @brief Validates that the provided matrix conforms to an identity matrix within a standard epsilon.
     *
     * @tparam T The numeric type of the matrix components.
     *
     * @param actual The matrix to verify as an identity matrix.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the matrix is not identity.
     * @note Triggers an assertion failure if matrix dimensions are mismatched.
     */
    template <fgm::Matrix T>
    void EXPECT_MAT_IDENTITY(const T& actual)
    {
        using ValueType = T::value_type;
        EXPECT_EQ(T::rows, T::columns) << "Identity matrices must be square(e.g: 3x3)\n";

        for (std::size_t i = 0; i < T::rows; ++i)
            for (std::size_t j = 0; j < T::columns; ++j)
                if constexpr (std::is_same_v<ValueType, double>)
                    EXPECT_DOUBLE_EQ(i == j, actual(i, j));
                else if constexpr (std::is_same_v<ValueType, float>)
                    EXPECT_FLOAT_EQ(i == j, actual(i, j));
                else
                    EXPECT_EQ(i == j, actual(i, j));
    }


    /**
     * @brief Validates that the provided matrix conforms to a zero matrix within a standard epsilon.
     *
     * @tparam T The numeric type of the expected matrix components.
     *
     * @param actual The matrix to verify as a zero matrix.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the matrix is not a zero matrix.
     * @note Triggers an assertion failure if matrix dimensions are mismatched.
     */
    template <fgm::Matrix T>
    void EXPECT_MAT_ZERO(const T& actual)
    {
        using ValueType = T::value_type;

        for (std::size_t i = 0; i < T::rows; ++i)
            for (std::size_t j = 0; j < T::columns; ++j)
                if constexpr (std::is_same_v<ValueType, double>)
                    EXPECT_DOUBLE_EQ(0.0, actual(i, j));
                else if constexpr (std::is_same_v<ValueType, float>)
                    EXPECT_FLOAT_EQ(0.0f, actual(i, j));
                else
                    EXPECT_EQ(ValueType(0), actual(i, j));
    }


    /**
     * @brief Validates that the provided matrix conforms to an infinity matrix.
     * 
     * @tparam T The numeric type of the expected matrix components.
     *
     * @param actual The matrix to verify as an infinity matrix.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the matrix is not an infinity matrix.
     * @note Triggers an assertion failure if matrix dimensions are mismatched.
     */
    template <fgm::Matrix T>
    void EXPECT_MAT_INF(const T& actual)
    {
        for (std::size_t i = 0; i < T::rows; ++i)
            for (std::size_t j = 0; j < T::columns; ++j)
                EXPECT_TRUE(std::isinf(actual(i, j)));
    }

    /** @} */

} // namespace testutils

// TODO: Deprecated Remove after refactor
namespace testutils::Matrix3D
{

    static unsigned int SIZE = 9;
    static unsigned int ROW_SIZE = 3;

    template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>,
              typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    void EXPECT_MAT_EQ(fgm::Matrix3D<T> expected, fgm::Matrix3D<U> actual)
    {
        for (unsigned int i = 0; i < SIZE; i++)
        {
            if constexpr (std::is_same_v<T, float>)
            {
                EXPECT_FLOAT_EQ(expected(i / ROW_SIZE, i % ROW_SIZE),
                                static_cast<T>(actual(i / ROW_SIZE, i % ROW_SIZE)));
            }
            else if (std::is_same_v<T, double>)
            {
                EXPECT_DOUBLE_EQ(expected(i / ROW_SIZE, i % ROW_SIZE),
                                 static_cast<T>(actual(i / ROW_SIZE, i % ROW_SIZE)));
            }
            else
            {
                EXPECT_EQ(expected(i / ROW_SIZE, i % ROW_SIZE), static_cast<T>(actual(i / ROW_SIZE, i % ROW_SIZE)));
            }
        }
    }
    // TODO: Add checks for precision

    template <typename T, typename U, typename = std::enable_if_t<std::is_floating_point_v<T>>,
              typename = std::enable_if_t<std::is_floating_point_v<U>>>
    void EXPECT_MAT_NEAR(fgm::Matrix3D<T> expected, fgm::Matrix3D<U> actual, double tolerance = 1e-5)
    {
        if (std::is_same_v<T, double> &&
            tolerance == 1e-5) // Hacky trick for only upgrading if user hasn't changed from default tolerance.
            tolerance = 1e-11;

        for (unsigned int i = 0; i < SIZE; i++)
        {
            EXPECT_NEAR(expected(i / ROW_SIZE, i % ROW_SIZE), actual(i / ROW_SIZE, i % ROW_SIZE), tolerance);
        }
    }

    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    void EXPECT_MAT_IDENTITY(fgm::Matrix3D<T> actual)
    {
        for (unsigned int i = 0; i < SIZE; i++)
        {
            T currentValue = static_cast<T>(i / ROW_SIZE == i % ROW_SIZE);
            if constexpr (std::is_same_v<T, float>)
            {
                EXPECT_FLOAT_EQ(currentValue, actual(i / ROW_SIZE, i % ROW_SIZE));
            }
            else if (std::is_same_v<T, double>)
            {
                EXPECT_DOUBLE_EQ(currentValue, actual(i / ROW_SIZE, i % ROW_SIZE));
            }
            else
            {
                EXPECT_EQ(currentValue, actual(i / ROW_SIZE, i % ROW_SIZE));
            }
        }
    }

    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    void EXPECT_MAT_ZERO(fgm::Matrix3D<T> actual)
    {

        for (unsigned int i = 0; i < SIZE; i++)
        {
            if constexpr (std::is_same_v<T, float>)
            {
                EXPECT_FLOAT_EQ(T(0), actual(i / ROW_SIZE, i % ROW_SIZE));
            }
            else if (std::is_same_v<T, double>)
            {
                EXPECT_DOUBLE_EQ(T(0), actual(i / ROW_SIZE, i % ROW_SIZE));
            }
            else
            {
                EXPECT_EQ(T(0), actual(i / ROW_SIZE, i % ROW_SIZE));
            }
        }
    }

    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    void EXPECT_MAT_INF(fgm::Matrix3D<T> actual)
    {

        for (unsigned int i = 0; i < SIZE; i++)
        {
            EXPECT_TRUE(std::isinf(actual(i / ROW_SIZE, i % ROW_SIZE)));
        }
    }
} // namespace testutils::Matrix3D

namespace testutils::Matrix2D
{

    static unsigned int SIZE = 4;
    static unsigned int ROW_SIZE = 2;

    template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>,
              typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    void EXPECT_MAT_EQ(fgm::Matrix2D<T> expected, fgm::Matrix2D<U> actual)
    {

        for (unsigned int i = 0; i < SIZE; i++)
        {
            if constexpr (std::is_same_v<T, float>)
            {
                EXPECT_FLOAT_EQ(expected(i / ROW_SIZE, i % ROW_SIZE),
                                static_cast<T>(actual(i / ROW_SIZE, i % ROW_SIZE)));
            }
            else if (std::is_same_v<T, double>)
            {
                EXPECT_DOUBLE_EQ(expected(i / ROW_SIZE, i % ROW_SIZE),
                                 static_cast<T>(actual(i / ROW_SIZE, i % ROW_SIZE)));
            }
            else
            {
                EXPECT_EQ(expected(i / ROW_SIZE, i % ROW_SIZE), static_cast<T>(actual(i / ROW_SIZE, i % ROW_SIZE)));
            }
        }
    }

    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    void EXPECT_MAT_IDENTITY(fgm::Matrix2D<T> actual)
    {
        for (unsigned int i = 0; i < SIZE; i++)
        {
            T currentValue = static_cast<T>(i / ROW_SIZE == i % ROW_SIZE);
            if constexpr (std::is_same_v<T, float>)
            {
                EXPECT_FLOAT_EQ(currentValue, actual(i / ROW_SIZE, i % ROW_SIZE));
            }
            else if (std::is_same_v<T, double>)
            {
                EXPECT_DOUBLE_EQ(currentValue, actual(i / ROW_SIZE, i % ROW_SIZE));
            }
            else
            {
                EXPECT_EQ(currentValue, actual(i / ROW_SIZE, i % ROW_SIZE));
            }
        }
    }

    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    void EXPECT_MAT_ZERO(fgm::Matrix2D<T> actual)
    {

        for (unsigned int i = 0; i < SIZE; i++)
        {
            if constexpr (std::is_same_v<T, float>)
            {
                EXPECT_FLOAT_EQ(T(0), actual(i / ROW_SIZE, i % ROW_SIZE));
            }
            else if (std::is_same_v<T, double>)
            {
                EXPECT_DOUBLE_EQ(T(0), actual(i / ROW_SIZE, i % ROW_SIZE));
            }
            else
            {
                EXPECT_EQ(T(0), actual(i / ROW_SIZE, i % ROW_SIZE));
            }
        }
    }

    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    void EXPECT_MAT_INF(fgm::Matrix2D<T> actual)
    {

        for (unsigned int i = 0; i < SIZE; i++)
        {
            EXPECT_TRUE(std::isinf(actual(i / ROW_SIZE, i % ROW_SIZE)));
        }
    }
} // namespace testutils::Matrix2D
