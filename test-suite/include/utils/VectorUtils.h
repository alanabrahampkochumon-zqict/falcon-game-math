#pragma once
/**
 * @file MatrixUtils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 16, 2026
 *
 * @brief Define helper functions for testing Vectors like @ref fgm::Vector2D, @ref fgm::Vector3D etc.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <MathTraits.h>
#include <cmath>
#include <gtest/gtest.h>
#include <type_traits>
#include <vector/Vector2D.h>
#include <vector/Vector3D.h>
#include <vector/Vector4D.h>

namespace testutils
{

    template <fgm::Vector T, fgm::Vector U>
    void EXPECT_VEC_EQ(const T& expected, const U& actual)
    {
        using ValueType = T::value_type;

        static_assert(T::dimension == U::dimension, "Vectors must have the same dimension (e.g. both 3D)");

        constexpr std::size_t elementCount = T::dimension;

        for (std::size_t i = 0; i < elementCount; ++i)
        {
            if constexpr (std::is_same_v<ValueType, double>)
                EXPECT_NEAR(expected[i], static_cast<ValueType>(actual[i]), fgm::DOUBLE_EPSILON);
            else if constexpr (std::is_floating_point_v<ValueType>)
                EXPECT_NEAR(expected[i], static_cast<ValueType>(actual[i]), fgm::FLOAT_EPSILON);
            else
                EXPECT_EQ(expected[i], static_cast<ValueType>(actual[i]));
        }
    }

    template <fgm::Arithmetic T>
    void EXPECT_VEC_CONTAINS(const fgm::Vector2D<T>& vector, T x, T y)
    {
        if constexpr (std::is_same_v<T, float>)
        {
            EXPECT_FLOAT_EQ(x, vector.x);
            EXPECT_FLOAT_EQ(y, vector.y);
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            EXPECT_DOUBLE_EQ(x, vector.x);
            EXPECT_DOUBLE_EQ(y, vector.y);
        }
        else
        {
            EXPECT_EQ(x, vector.x);
            EXPECT_EQ(y, vector.y);
        }
    }

    template <fgm::Arithmetic T>
    void EXPECT_VEC_CONTAINS(const fgm::Vector3D<T>& vector, T x, T y, T z)
    {
        if constexpr (std::is_same_v<T, float>)
        {
            EXPECT_FLOAT_EQ(x, vector.x);
            EXPECT_FLOAT_EQ(y, vector.y);
            EXPECT_FLOAT_EQ(z, vector.z);
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            EXPECT_DOUBLE_EQ(x, vector.x);
            EXPECT_DOUBLE_EQ(y, vector.y);
            EXPECT_DOUBLE_EQ(z, vector.z);
        }
        else
        {
            EXPECT_EQ(x, vector.x);
            EXPECT_EQ(y, vector.y);
            EXPECT_EQ(z, vector.z);
        }
    }

    template <fgm::Arithmetic T>
    void EXPECT_VEC_CONTAINS(const fgm::Vector4D<T>& vector, T x, T y, T z, T w)
    {
        if constexpr (std::is_same_v<T, float>)
        {
            EXPECT_FLOAT_EQ(x, vector.x);
            EXPECT_FLOAT_EQ(y, vector.y);
            EXPECT_FLOAT_EQ(z, vector.z);
            EXPECT_FLOAT_EQ(w, vector.w);
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            EXPECT_DOUBLE_EQ(x, vector.x);
            EXPECT_DOUBLE_EQ(y, vector.y);
            EXPECT_DOUBLE_EQ(z, vector.z);
            EXPECT_DOUBLE_EQ(w, vector.w);
        }
        else
        {
            EXPECT_EQ(x, vector.x);
            EXPECT_EQ(y, vector.y);
            EXPECT_EQ(z, vector.z);
            EXPECT_EQ(w, vector.w);
        }
    }

    template <fgm::Vector T>
    void EXPECT_VEC_UNIT(const T& vector)
    {
        using ValueType = T::value_type;
        ValueType expected = ValueType(1);

        constexpr std::size_t elementCount = T::dimension;

        for (std::size_t i = 0; i < elementCount; ++i)
        {
            if constexpr (std::is_same_v<ValueType, float>)
            {
                EXPECT_FLOAT_EQ(expected, static_cast<ValueType>(vector[i]));
            }
            else if constexpr (std::is_same_v<ValueType, double>)
            {
                EXPECT_DOUBLE_EQ(expected, static_cast<ValueType>(vector[i]));
            }
            else
            {
                EXPECT_EQ(expected, static_cast<ValueType>(vector[i]));
            }
        }
    }

    template <fgm::Vector T>
    void EXPECT_VEC_ZERO(const T& vector)
    {
        using ValueType = T::value_type;

        constexpr std::size_t elementCount = T::dimension;

        for (std::size_t i = 0; i < elementCount; ++i)
        {
            if constexpr (std::is_same_v<ValueType, float>)
            {
                EXPECT_FLOAT_EQ(0.0f, static_cast<ValueType>(vector[i]));
            }
            else if constexpr (std::is_same_v<ValueType, double>)
            {
                EXPECT_DOUBLE_EQ(0.0, static_cast<ValueType>(vector[i]));
            }
            else
            {
                EXPECT_EQ(ValueType(0), static_cast<ValueType>(vector[i]));
            }
        }
    }

    template <fgm::Vector T>
    void EXPECT_VEC_INF(const T& vector)
    {
        constexpr std::size_t elementCount = T::dimension;
        if (std::is_floating_point_v<T>)
            for (std::size_t i = 0; i < elementCount; ++i)
            {
                EXPECT_TRUE(std::isinf(vector[i]));
            }
        else
            GTEST_SKIP() << "Integral division by zero result in undefined behavior and crashes.";
    }

    template <fgm::StrictArithmetic T>
    void EXPECT_MAG_EQ(T expected, T actual)
    {
        if constexpr (std::is_same_v<T, float>)
            EXPECT_FLOAT_EQ(expected, actual);
        else if constexpr (std::is_floating_point_v<T>)
            EXPECT_DOUBLE_EQ(expected, actual);
        else
            EXPECT_EQ(expected, actual);
    }
} // namespace testutils