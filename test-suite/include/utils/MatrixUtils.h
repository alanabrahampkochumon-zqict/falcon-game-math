/**
 * @file MatrixUtils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Helper functions for testing Matrices like `Matrix2D`, `Matrix3D` etc.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#pragma once

#include <MathTraits.h>
#include <cmath>
#include <gtest/gtest.h>
#include <matrix/Matrix2D.h>
#include <matrix/Matrix3D.h>

namespace testutils
{
    template <math::Matrix T, math::Matrix U>
    void EXPECT_MAT_EQ(T expected, U actual)
    {
        using ValueType = T::value_type;

        static_assert(T::rows == U::rows && T::columns == U::columns,
                      "Matrices must of the same dimension, e.g: 3x3 and 3x3");

        for (std::size_t i = 0; i < T::rows; ++i)
            for (std::size_t j = 0; j < T::columns; ++j)
                if constexpr (std::is_same_v<ValueType, double>)
                    ASSERT_DOUBLE_EQ(expected(i, j), static_cast<ValueType>(actual(i, j)));
                else if constexpr (std::is_same_v<ValueType, float>)
                    ASSERT_FLOAT_EQ(expected(i, j), static_cast<ValueType>(actual(i, j)));
                else
                    ASSERT_EQ(expected(i, j), static_cast<ValueType>(actual(i, j)));
    }

    template <math::Matrix T, math::Matrix U>
    void EXPECT_MAT_NEAR(T expected, U actual, double tolerance = 1e-5)
    {

        using ValueType = T::value_type;
        static_assert(T::rows == U::rows && T::columns == U::columns,
                      "Matrices must of the same dimension, e.g: 3x3 and 3x3");

        for (std::size_t i = 0; i < T::rows; ++i)
            for (std::size_t j = 0; j < T::columns; ++j)
                EXPECT_NEAR(expected(i, j), static_cast<ValueType>(actual(i, j)), tolerance);
    }

    template <math::Matrix T>
    void EXPECT_MAT_IDENTITY(T actual)
    {
        using ValueType = T::value_type;
        EXPECT_EQ(T::rows, T::columns) << "Identity matrices must be square(e.g: 3x3)\n";

        for (std::size_t i = 0; i < T::rows; ++i)
            for (std::size_t j = 0; j < T::columns; ++j)
                if constexpr (std::is_same_v<ValueType, double>)
                    ASSERT_DOUBLE_EQ(i == j, actual(i, j));
                else if constexpr (std::is_same_v<ValueType, float>)
                    ASSERT_FLOAT_EQ(i == j, actual(i, j));
                else
                    ASSERT_EQ(i == j, actual(i, j));
    }

    template <math::Matrix T>
    void EXPECT_MAT_ZERO(T actual)
    {
        using ValueType = T::value_type;

        for (std::size_t i = 0; i < T::rows; ++i)
            for (std::size_t j = 0; j < T::columns; ++j)
                if constexpr (std::is_same_v<ValueType, double>)
                    ASSERT_DOUBLE_EQ(0.0, actual(i, j));
                else if constexpr (std::is_same_v<ValueType, float>)
                    ASSERT_FLOAT_EQ(0.0f, actual(i, j));
                else
                    ASSERT_EQ(ValueType(0), actual(i, j));
    }

    template <math::Matrix T>
    void EXPECT_MAT_INF(T actual)
    {
        for (std::size_t i = 0; i < T::rows; ++i)
            for (std::size_t j = 0; j < T::columns; ++j)
                EXPECT_TRUE(std::isinf(actual(i, j)));
    }

} // namespace testutils

// TODO: Remove
namespace testutils::Matrix3D
{

    static unsigned int SIZE = 9;
    static unsigned int ROW_SIZE = 3;

    template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>,
              typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    void EXPECT_MAT_EQ(math::Matrix3D<T> expected, math::Matrix3D<U> actual)
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
    void EXPECT_MAT_NEAR(math::Matrix3D<T> expected, math::Matrix3D<U> actual, double tolerance = 1e-5)
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
    void EXPECT_MAT_IDENTITY(math::Matrix3D<T> actual)
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
    void EXPECT_MAT_ZERO(math::Matrix3D<T> actual)
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
    void EXPECT_MAT_INF(math::Matrix3D<T> actual)
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
    void EXPECT_MAT_EQ(math::Matrix2D<T> expected, math::Matrix2D<U> actual)
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
    void EXPECT_MAT_IDENTITY(math::Matrix2D<T> actual)
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
    void EXPECT_MAT_ZERO(math::Matrix2D<T> actual)
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
    void EXPECT_MAT_INF(math::Matrix2D<T> actual)
    {

        for (unsigned int i = 0; i < SIZE; i++)
        {
            EXPECT_TRUE(std::isinf(actual(i / ROW_SIZE, i % ROW_SIZE)));
        }
    }
} // namespace testutils::Matrix2D
