#pragma once
/**
 * @file Vector4D.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 26, 2026
 *
 * @brief Templated 4D Vector supporting integral, floating-point and boolean types.
 * @note Arithmetic operations are limited to numeric types via `StrictArithmetic` concept.
 *
 * @par Configuration
 * Define `ENABLE_FGM_SHADER_OPERATORS` to enable comparison operators (>, <, etc.).
 * Even if disabled, functional comparisons like `greaterThan()` remain available.
 * Define `FORCE_SCALAR` to turn off SIMD which is on by default on supported hardware.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2D.h"
#include "Vector3D.h"

#include <cstddef>


namespace math
{
    template <Arithmetic T>
    struct Vector4D
    {
        using value_type = T;

        static constexpr std::size_t dimension = 4;

        union {
            struct
            {
                T x; ///< X-axis component
                T y; ///< Y-axis component
                T z; ///< Z-axis component
                T w; ///< W-axis (homogeneous) component
            };
            struct
            {
                T r; ///< Red channel
                T g; ///< Green channel
                T b; ///< Blue channel
                T a; ///< Alpha channel
            };
            struct
            {
                T s; ///< S-coordinate
                T t; ///< T-coordinate
                T p; ///< P-coordinate
                T q; ///< Q-coordinate
            };

            T elements[dimension];
        };


        /*************************************
         *                                   *
         *            INITIALIZERS           *
         *                                   *
         *************************************/

        Vector4D();
        Vector4D(T v1, T v2, T v3, T v4);
        Vector4D(Vector2D<T> vec1, Vector2D<T> vec2);
        Vector4D(Vector3D<T> vec, T v);

        template <Arithmetic U>
        Vector4D(const Vector4D<U>& other);


        /*************************************
         *                                   *
         *            ACCESSORS              *
         *                                   *
         *************************************/

        T& operator[](std::size_t i);
        const T& operator[](std::size_t i) const;


        /***************************************
         *                                     *
         *             EQUALITY                *
         *                                     *
         ***************************************/

        /**
         * @brief Checks the equality of all the vector elements.
         * @note For Vector<bool> mask use `neq` for inequality and `eq` for equality.
         *
         * @tparam U type of the `Vector4D` being compared against.
         * @param other `Vector4D` to check equality against.
         * @param epsilon Epsilon to use for comparison. Only affects `std::floating_point` types.
         * @returns vector equality result.
         */
        template <Arithmetic U>
        bool allEq(const Vector4D<U>& other,
                    double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>) ? DOUBLE_EPSILON: FLOAT_EPSILON) const;


        /**
         * @brief Static wrapper for `Vector4D` equality checks.
         * @note For Vector<bool> mask use `neq` for inequality and `eq` for equality.
         *
         * @tparam U type of the `Vector4D` being compared against.
         * @param vecA `Vector4D` being compared.
         * @param vecB `Vector4D` being compared against.
         * @param epsilon Epsilon to use for comparison. Only affects `std::floating_point` types.
         * @returns vector equality result.
         */
        template <Arithmetic U>
        static bool allEq(const Vector4D& vecA, const Vector4D<U>& vecB,
                           double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>) ? DOUBLE_EPSILON: FLOAT_EPSILON);


        /**
         * @brief Equality operator overload for vector comparison, that check for equality of entire vectors.
         * @note For Vector<bool> mask use `eq`.
         * @tparam U type of the `Vector4D` being compared against.
         * @param other `Vector4D` being compared against.
         * @return vector equality result.
         */
        template <Arithmetic U>
        bool operator==(const Vector4D<U>& other) const;


        /**
         * @brief Inequality operator overload for vector comparison, that check for inequality of entire vectors.
         * @note For Vector<bool> mask use `neq`.
         *
         * @tparam U type of the `Vector4D` being compared against.
         * @param other `Vector4D` being compared against.
         * @return vector equality result.
         */
        template <Arithmetic U>
        bool operator!=(const Vector4D<U>& other) const;


        /**
         *
         * @note All comparisons except equality operator(==), inequality operator(!=), and `allEq` performs element-wise comparison.
         *
         */


        /**
         * @brief Performs component-wise equality and returns a Vector<bool> mask.
         * @note For bool result use `allEq` or equality operators(==, !=).
         *
         * @tparam U type of the `Vector4D` being compared against.
         * @param other `Vector4D` to check equality against.
         * @param epsilon Epsilon to use for comparison. Only affects `std::floating_point` types.
         * @returns component-wise boolean mask.
         */
        template <Arithmetic U>
        Vector4D<bool> eq(const Vector4D<U>& other,
                   double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>) ? DOUBLE_EPSILON
                                                                                             : FLOAT_EPSILON) const;

        /**
         * @brief Static wrapper for `eq`.
         * @note For bool result use `allEq` or equality operators(==, !=).
         *
         * @tparam U type of the `Vector4D` being compared against.
         * @param vecA `Vector4D` being compared.
         * @param vecB `Vector4D` being compared against.
         * @param epsilon Epsilon to use for comparison. Only affects `std::floating_point` types.
         * @returns component-wise boolean mask.
         */
        template <Arithmetic U>
        static Vector4D<bool> eq(const Vector4D& vecA, const Vector4D<U>& vecB,
                          double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                              ? DOUBLE_EPSILON
                              : FLOAT_EPSILON);


        /***************************************
         *                                     *
         *            COMPARISONS              *
         *                                     *
         ***************************************/

        template <StrictArithmetic U>
        Vector4D<bool> gt(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        static Vector4D<bool> gt(const Vector4D& vecA, const Vector4D<U>& vecB)
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        Vector4D<bool> gte(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        static Vector4D<bool> gte(const Vector4D& vecA, const Vector4D<U>& vecB)
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        Vector4D<bool> lt(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        static Vector4D<bool> lt(const Vector4D& vecA, const Vector4D<U>& vecB)
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        Vector4D<bool> lte(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        static Vector4D<bool> lte(const Vector4D& vecA, const Vector4D<U>& vecB)
            requires StrictArithmetic<T>;

#ifdef ENABLE_FGM_SHADER_OPERATORS
        template <StrictArithmetic U>
        Vector4D<bool> operator>(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        Vector4D<bool> operator>=(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        Vector4D<bool> operator<(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        Vector4D<bool> operator<=(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;
#endif

        /***************************************
         *                                     *
         *      BOOLEAN BITWISE OPERATORS      *
         *                                     *
         ***************************************/

        Vector4D<bool> operator&(const Vector4D<bool>& other) const
            requires std::is_same_v<T, bool>;

        Vector4D<bool> operator|(const Vector4D<bool>& other) const
            requires std::is_same_v<T, bool>;

        Vector4D<bool> operator!() const
            requires std::is_same_v<T, bool>;


        /*************************************
         *                                   *
         *      ARITHMETIC OPERATORS         *
         *                                   *
         *************************************/

        template <StrictArithmetic U>
        auto operator+(const Vector4D<U>& other) const -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        Vector4D& operator+=(const Vector4D<U>& other)
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        auto operator-(const Vector4D<U>& other) const -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;
        template <StrictArithmetic U>
        Vector4D& operator-=(const Vector4D<U>& other)
            requires StrictArithmetic<T>;

        template <StrictArithmetic S>
        auto operator*(S scalar) const -> Vector4D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;

        template <StrictArithmetic S>
        Vector4D& operator*=(S scalar)
            requires StrictArithmetic<T>;

        template <StrictArithmetic S>
        auto operator/(S scalar) const -> Vector4D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;

        template <StrictArithmetic S>
        Vector4D& operator/=(S scalar)
            requires StrictArithmetic<T>;


        /*************************************
         *                                   *
         *        VECTOR DOT PRODUCT         *
         *                                   *
         *************************************/

        template <StrictArithmetic U>
        auto dot(const Vector4D<U>& other) const -> std::common_type_t<T, U>
            requires StrictArithmetic<T>;

        template <StrictArithmetic U>
        static auto dot(const Vector4D& vecA, const Vector4D<U>& vecB) -> std::common_type_t<T, U>
            requires StrictArithmetic<T>;


        /*************************************
         *                                   *
         *         VECTOR MAGNITUDE          *
         *                                   *
         *************************************/

        /**
         * Returns the magnitude of the vector.
         * @returns If the type of T float, then a float is returned, else a float.
         */
        Magnitude<T> mag() const
            requires StrictArithmetic<T>;
        static Magnitude<T> mag(const Vector4D& vec)
            requires StrictArithmetic<T>;


        /*************************************
         *                                   *
         *       VECTOR NORMALIZATION        *
         *                                   *
         *************************************/

        /**
         * Returns a normalized vector.
         * @note Vector will be type promoted to math::Magnitude's type.
         * @returns normalized floating point vector.
         */
        Vector4D<Magnitude<T>> normalize() const
            requires StrictArithmetic<T>;
        static Vector4D<Magnitude<T>> normalize(const Vector4D& vec)
            requires StrictArithmetic<T>;


        /*************************************
         *                                   *
         *        VECTOR PROJECTION          *
         *                                   *
         *************************************/

        /**
         * Projects the current vector onto to the `onto` vector.
         * @tparam U Type of the vector to be projected on to (b).
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the calculation by ignoring the division, given the vector that
         * is projected onto is normalized.
         * @returns Projected vector.
         */
        template <StrictArithmetic U>
        auto project(const Vector4D<U>& onto, bool ontoNormalized = false) const -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;

        /**
         * Static wrapper for vector projection.
         * @tparam U Type of the vector to be projected to.
         * @param vector Vector to project.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the calculation by ignoring the division, given the vector that
         * is projected onto is normalized.
         * @returns Projected vector.
         */
        template <StrictArithmetic U>
        static auto project(const Vector4D& vector, const Vector4D<U>& onto, bool ontoNormalized = false)
            -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;


        /*************************************
         *                                   *
         *         VECTOR REJECTION          *
         *                                   *
         *************************************/

        /**
         * Returns the perpendicular component for the current vector after projection to the `onto` vector.
         * @tparam U Type of the vector to be vector projected onto.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the calculation by ignoring the division, given the vector that
         * is projected onto is normalized.
         * @returns Projected vector.
         */
        template <StrictArithmetic U>
        auto reject(const Vector4D<U>& onto, bool ontoNormalized = false) const -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;


        /**
         * Returns the perpendicular component for the current vector after projection to the `onto` vector.
         * @tparam U Type of the vector to be vector projected onto.
         * @param vector whose rejection(perpendicular) component on to `onto` we need to find.
         * @param onto Vector to be projected onto.
         * @param ontoNormalized A flag for optimizing the calculation by ignoring the division, given the vector that
         * is projected onto is normalized.
         * @returns Projected vector.
         */
        template <StrictArithmetic U>
        static auto reject(const Vector4D& vector, const Vector4D<U>& onto, bool ontoNormalized = false)
            -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;
    };


    /*************************************
     *                                   *
     *       NON-MEMBER FUNCTIONS        *
     *                                   *
     *************************************/
    template <StrictArithmetic T, StrictArithmetic S>
    auto operator*(S scalar, const Vector4D<T>& vector) -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>;


    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/
    using bVec4 = Vector4D<bool>;
    using iVec4 = Vector4D<int>;
    using uVec4 = Vector4D<unsigned int>;
    using vec4 = Vector4D<float>;
    using lVec4 = Vector4D<long long>;
    using dVec4 = Vector4D<double>;
    using ulVec4 = Vector4D<unsigned long long>;

} // namespace math

#include "Vector4D.tpp"