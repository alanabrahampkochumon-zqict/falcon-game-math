#pragma once
/**
 * @file Vector4D.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 26, 2026
 *
 * @brief Templated 4D Vector supporting integral, floating-point, and boolean types.
 *
 * @todo Provides a high-performance vector implementation with SIMD acceleration
 * and support for component-wise operations.
 *
 * @tparam T Type of @ref Vector4D components. Must satisfy @ref Arithmetic.
 *
 * @note Arithmetic operations are restricted to numeric types via @ref StrictArithmetic.
 *
 * @par Configuration
 * - Define `ENABLE_FGM_SHADER_OPERATORS` to enable comparison operators (`,`, `<`, etc.).
 *   Even if disabled, functional comparisons like @ref gt remain available.
 * - Define `FORCE_SCALAR` to disable SIMD optimizations (enabled by default on supported hardware).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vector2D.h"
#include "Vector3D.h"

#include <cstddef>
#include <ostream>

// TODO: Zero, One, Inf, -Inf, Nan, X, Y, Z, W

namespace fgm
{
    template <Arithmetic T>
    struct Vector4D
    {
        using value_type = T;

        static constexpr std::size_t dimension = 4; ///< Vector Dimension

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


        /**
         * @brief Initialize @ref fgm::Vector4D with zeros.
         */
        Vector4D();


        /**
         * @brief Initialize @ref fgm::Vector4D with passed in values.
         * @param[in]  v1 First entry of @ref fgm::Vector4D.
         * @param[in]  v2 Second entry of @ref fgm::Vector4D.
         * @param[in]  v3 Third entry of @ref fgm::Vector4D.
         * @param[in]  v4 Fourth entry of @ref fgm::Vector4D.
         */
        Vector4D(T v1, T v2, T v3, T v4);


        /**
         * @brief Initialize @ref fgm::Vector4D with 2 @ref Vector2D.
         * @param[in]  vec1 First two entries of @ref fgm::Vector4D.
         * @param[in]  vec2 Last two entries of @ref fgm::Vector4D.
         */
        Vector4D(Vector2D<T> vec1, Vector2D<T> vec2);


        /**
         * @brief Initialize @ref fgm::Vector4D with 1 @ref Vector3D and 1 T value.
         * @param[in]  vec First three entries of @ref fgm::Vector4D.
         * @param[in]  v Last entry for @ref fgm::Vector4D.
         */
        Vector4D(Vector3D<T> vec, T v);


        /**
         * @brief Initialize @ref fgm::Vector4D with 1 T value and 1 @ref Vector3D.
         * @param[in]  vec First three entries of @ref fgm::Vector4D.
         * @param[in]  v Last entry for @ref fgm::Vector4D.
         */
        Vector4D(T v, Vector3D<T> vec);


        /**
         * @brief Initialize @ref fgm::Vector4D from another @ref fgm::Vector4D of a different type.
         * @tparam U Numeric type of the source vector.
         * @param[in]  other Source vector to be converted.
         */
        template <Arithmetic U>
        Vector4D(const Vector4D<U>& other);




        /*************************************
         *                                   *
         *            ACCESSORS              *
         *                                   *
         *************************************/


        /**
         * @brief Accesses the component at the specified location.
         * Provides read-write access to the element.
         *
         * @param[in]  i Index of the vector component.
         * @return Reference to the vector component.
         */
        T& operator[](std::size_t i);


        /**
         * @brief Accesses the element at the specified location (read-only).
         *
         * @param[in]  i Index of the vector component.
         * @return A const reference to the vector component.
         */
        const T& operator[](std::size_t i) const;




        /***************************************
         *                                     *
         *             EQUALITY                *
         *                                     *
         ***************************************/


        /**
         * @brief Compare all components of this vector for equality with another vector.
         * Performs a component-wise comparison and returns true only if every element pair
         * satisfies the equality condition within the given @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         * @param[in] other The vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *            Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return True if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
        bool allEq(const Vector4D<U>& other,
                   double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>) ? DOUBLE_EPSILON
                                                                                             : FLOAT_EPSILON) const;


        /**
         * @copybrief allEq(const Vector4D<U>&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         * @param[in]  vecA First vector to compare.
         * @param[in]  vecB Second vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *            Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return True if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
        static bool allEq(const Vector4D& vecA, const Vector4D<U>& vecB,
                          double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>) ? DOUBLE_EPSILON
                                                                                                    : FLOAT_EPSILON);

        /**
         * @brief Compare components for inequality across two vectors.
         * Performs a component-wise comparison and returns true if any of the pair satisfies inequality condition
         * within the given @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref neq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         * @param[in] other The vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *            Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return True if any of the components are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
        bool allNeq(const Vector4D<U>& other,
                    double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>) ? DOUBLE_EPSILON
                                                                                              : FLOAT_EPSILON) const;


        /**
         * @copybrief allNeq(const Vector4D<U>&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref neq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         * @param[in]  vecA First vector to compare.
         * @param[in]  vecB Second vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *            Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return True if any of the components are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
        static bool allNeq(const Vector4D& vecA, const Vector4D<U>& vecB,
                           double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>) ? DOUBLE_EPSILON
                                                                                                     : FLOAT_EPSILON);

        /**
         * @copybrief allEq(const Vector4D<U>&, double) const
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         * @param[in] other The vector to compare against.
         * @return True if all components are equivalent within the default epsilon.
         */
        template <Arithmetic U>
        bool operator==(const Vector4D<U>& other) const;


        /**
         * @copybrief allNeq(const Vector4D<U>&, double) const
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         * @param[in] other The vector to compare against.
         * @return True if any of the components are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
        bool operator!=(const Vector4D<U>& other) const;


        /**
         * @brief Perform component-wise equality check.
         * Compares each component pair and returns a boolean mask.
         *
         * @note To obtain a single scalar result, use @ref allEq or @ref operator==.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         * @param[in] other The vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *            Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        Vector4D<bool> eq(const Vector4D<U>& other,
                          double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                              ? DOUBLE_EPSILON
                              : FLOAT_EPSILON) const;


        /**
         * @copybrief eq(const Vector4D<U>&, double) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         * @param[in]  vecA First vector to compare.
         * @param[in]  vecB Second vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *            Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        static Vector4D<bool> eq(const Vector4D& vecA, const Vector4D<U>& vecB,
                                 double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                     ? DOUBLE_EPSILON
                                     : FLOAT_EPSILON);

        /**
         * @brief Perform component-wise inequality check.
         * Compares each component pair and returns a boolean mask.
         *
         * @note To obtain a single scalar result, use @ref allNeq or @ref operator!=.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         * @param[in] other The vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *            Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        Vector4D<bool> neq(const Vector4D<U>& other,
                           double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                               ? DOUBLE_EPSILON
                               : FLOAT_EPSILON) const;


        /**
         * @copybrief neq(const Vector4D<U>&, double) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         * @param[in]  vecA First vector to compare.
         * @param[in]  vecB Second vector to compare against.
         * @param[in] epsilon Maximum allowable difference for `std::floating_point` types.
         *            Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
        static Vector4D<bool> neq(const Vector4D& vecA, const Vector4D<U>& vecB,
                                  double epsilon = (std::is_same_v<T, double> || std::is_same_v<U, double>)
                                      ? DOUBLE_EPSILON
                                      : FLOAT_EPSILON);




        /***************************************
         *                                     *
         *            COMPARISONS              *
         *                                     *
         ***************************************/

        /**
         * @brief Perform component-wise greater-than comparison.
         * Compares each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] other The vector to compare against.
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        Vector4D<bool> gt(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        /**
         * @copybrief gt(const Vector4D<U>&) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in]  vecA First vector to compare.
         * @param[in]  vecB Second vector to compare against.
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        static Vector4D<bool> gt(const Vector4D& vecA, const Vector4D<U>& vecB)
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than-or-equal comparison.
         * Compares each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] other The vector to compare against.
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        Vector4D<bool> gte(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;


        /**
         * @copybrief gte(const Vector4D<U>&) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in]  vecA First vector to compare.
         * @param[in]  vecB Second vector to compare against.
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        static Vector4D<bool> gte(const Vector4D& vecA, const Vector4D<U>& vecB)
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than comparison.
         * Compares each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] other The vector to compare against.
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        Vector4D<bool> lt(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;


        /**
         * @copybrief lt(const Vector4D<U>&) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in]  vecA First vector to compare.
         * @param[in]  vecB Second vector to compare against.
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        static Vector4D<bool> lt(const Vector4D& vecA, const Vector4D<U>& vecB)
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than-or-equal comparison.
         * Compares each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] other The vector to compare against.
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        Vector4D<bool> lte(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;

        /**
         * @copybrief lt(const Vector4D<U>&) const
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in]  vecA First vector to compare.
         * @param[in]  vecB Second vector to compare against.
         * @return A @ref Vector4D<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
        static Vector4D<bool> lte(const Vector4D& vecA, const Vector4D<U>& vecB)
            requires StrictArithmetic<T>;


#ifdef ENABLE_FGM_SHADER_OPERATORS

        /**
         * @copydoc gt(const Vector4D<U>&) const
         */
        template <StrictArithmetic U>
        Vector4D<bool> operator>(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;


        /**
         * @copydoc gte(const Vector4D<U>&) const
         */
        template <StrictArithmetic U>
        Vector4D<bool> operator>=(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;


        /**
         * @copydoc lt(const Vector4D<U>&) const
         */
        template <StrictArithmetic U>
        Vector4D<bool> operator<(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;


        /**
         * @copydoc lte(const Vector4D<U>&) const
         */
        template <StrictArithmetic U>
        Vector4D<bool> operator<=(const Vector4D<U>& other) const
            requires StrictArithmetic<T>;
#endif




        /***************************************
         *                                     *
         *      BOOLEAN BITWISE OPERATORS      *
         *                                     *
         ***************************************/

        /**
         * @brief Perform component-wise logical AND.
         * Computes the conjunction of each component pair.
         *
         * @note Only available for @ref bVec4 and vectors with `bool` value_type.
         *
         * @param[in] other The vector to combine with.
         * @return A @ref Vector4D<bool> mask containing the results of component-wise AND.
         */
        Vector4D<bool> operator&(const Vector4D<bool>& other) const
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise logical OR.
         * Computes the disjunction of each component pair.
         *
         * @note Only available for @ref bVec4 and vectors with `bool` value_type.
         *
         * @param[in] other The vector to combine with.
         * @return A @ref Vector4D<bool> mask containing the results of component-wise OR.
         */
        Vector4D<bool> operator|(const Vector4D<bool>& other) const
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise logical NOT.
         * Inverts each boolean component and returns a new @ref Vector4D<bool>.
         *
         * @note Only available for @ref bVec4 and vectors with `bool` value_type.
         *
         * @return A @ref Vector4D<bool> with inverted values.
         */
        Vector4D<bool> operator!() const
            requires std::is_same_v<T, bool>;




        /*************************************
         *                                   *
         *      ARITHMETIC OPERATORS         *
         *                                   *
         *************************************/


        /**
         * @brief Add two vectors component-wise.
         * Computes the sum of each component pair and returns a new vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] other The vector to add.
         * @return A new @ref Vector4D containing the component-wise sum.
         */
        template <StrictArithmetic U>
        auto operator+(const Vector4D<U>& other) const -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;


        /**
         * @brief Add another vector to this vector component-wise.
         * Performs an in-place addition of @p other to the current instance.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] other The vector to add.
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic U>
        Vector4D& operator+=(const Vector4D<U>& other)
            requires StrictArithmetic<T>;



        /**
         * @brief Subtract two vectors component-wise.
         * Computes the difference between each component pair and returns a new vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] other The vector to subtract.
         * @return A new @ref Vector4D containing the component-wise difference.
         */
        template <StrictArithmetic U>
        auto operator-(const Vector4D<U>& other) const -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;


        /**
         * @brief Subtract another vector from this vector component-wise.
         * Performs an in-place subtraction of @p other from the current instance.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] other The vector to subtract.
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic U>
        Vector4D& operator-=(const Vector4D<U>& other)
            requires StrictArithmetic<T>;


        /**
         * @brief Scale the vector by a scalar value.
         * Multiplies each component of the vector by @p scalar and returns a new vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         * @param[in] scalar The value to scale by.
         * @return A new @ref Vector4D scaled by @p scalar.
         */
        template <StrictArithmetic S>
        auto operator*(S scalar) const -> Vector4D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;


        /**
         * @brief Scale this vector in-place by a scalar value.
         * Performs an in-place multiplication of each component by @p scalar.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         * @param[in] scalar The value to scale by.
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic S>
        Vector4D& operator*=(S scalar)
            requires StrictArithmetic<T>;


        /**
         * @brief Scale the vector by a scalar value.
         * Divides each component of the vector by @p scalar and returns a new vector.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @warning Does not check for division by zero. @p scalar should be non-zero.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         * @param[in] scalar The value to scale by.
         * @return A new @ref Vector4D scaled by @p scalar.
         */
        template <StrictArithmetic S>
        auto operator/(S scalar) const -> Vector4D<std::common_type_t<T, S>>
            requires StrictArithmetic<T>;


        /**
         * @brief Scale this vector in-place by a scalar value.
         * Performs an in-place division of each component by @p scalar.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @warning Does not check for division by zero. @p scalar should be non-zero.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         * @param[in] scalar The value to scale by.
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic S>
        Vector4D& operator/=(S scalar)
            requires StrictArithmetic<T>;




        /*************************************
         *                                   *
         *        VECTOR DOT PRODUCT         *
         *                                   *
         *************************************/


        /**
         * @brief Calculate the dot product with another vector.
         * Computes the scalar product: \f$ \mathbf{a} \cdot \mathbf{b} = \sum_{i=1}^{4} a_i b_i \f$.
         *
         * @note Promotes the result to the `std::common_type_t` of `T` and `U`.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] other The vector to compute the dot product with.
         * @return The scalar dot product of the two vectors.
         */
        template <StrictArithmetic U>
        auto dot(const Vector4D<U>& other) const -> std::common_type_t<T, U>
            requires StrictArithmetic<T>;


        /**
         * @brief @copybrief dot(const Vector4D<U>&) const
         * Static wrapper that computes \f$ \mathbf{vecA} \cdot \mathbf{vecB} \f$.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] vecA First vector to perform the dot product on.
         * @param[in] vecB Second vector to perform the dot product on.
         * @return The scalar dot product of @p vecA and @p vecB.
         */
        template <StrictArithmetic U>
        static auto dot(const Vector4D& vecA, const Vector4D<U>& vecB) -> std::common_type_t<T, U>
            requires StrictArithmetic<T>;




        /*************************************
         *                                   *
         *         VECTOR MAGNITUDE          *
         *                                   *
         *************************************/

        /**
         * @brief Calculate the magnitude (length) of the vector.
         * Computes the Euclidean norm: \f$ \|\mathbf{v}\| = \sqrt{\mathbf{v} \cdot \mathbf{v}} \f$.
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @return The scalar magnitude of the vector.
         */
        Magnitude<T> mag() const
            requires StrictArithmetic<T>;

        /**
         * @brief @copybrief mag() const
         * Static wrapper that computes \f$ \|\mathbf{vec}\| \f$.
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[in] vec The vector to compute the magnitude of.
         * @return The scalar magnitude of @p vec.
         */
        static Magnitude<T> mag(const Vector4D& vec)
            requires StrictArithmetic<T>;




        /*************************************
         *                                   *
         *       VECTOR NORMALIZATION        *
         *                                   *
         *************************************/


        /**
         * @brief Calculate the normalized (unit) form of the vector.
         * Computes the unit vector in the same direction: \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         * @warning Does not check for zero-length vectors. @ref mag() must be non-zero.
         *
         * @return A new @ref Vector4D with a magnitude of 1.0.
         */
        Vector4D<Magnitude<T>> normalize() const
            requires StrictArithmetic<T>;

        /**
         * @brief @copybrief normalize() const
         * Static wrapper that computes the unit vector \f$ \mathbf{\hat{v}} \f$.
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[in] vec The vector to normalize.
         * @return A new @ref Vector4D with a magnitude of 1.0.
         */
        static Vector4D<Magnitude<T>> normalize(const Vector4D& vec)
            requires StrictArithmetic<T>;




        /*************************************
         *                                   *
         *        VECTOR PROJECTION          *
         *                                   *
         *************************************/

        /**
         * @brief Project this vector onto another vector.
         * Computes the orthogonal projection: \f$ \text{proj}_{\mathbf{b}} \mathbf{a} = \frac{\mathbf{a} \cdot
         * \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b} \f$.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] onto The vector to project onto.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         * @return The projected @ref Vector4D.
         */
        template <StrictArithmetic U>
        auto project(const Vector4D<U>& onto, bool ontoNormalized = false) const -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;


        /**
         * @brief @copybrief project(const Vector4D<U>&, bool) const
         * Static wrapper for orthogonal projection of @p vector onto @p onto.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] vector The vector to be projected.
         * @param[in] onto The vector to project onto.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         * @return The projected @ref Vector4D.
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
         * @brief Compute the vector rejection of this vector from another.
         * Computes the component of the vector perpendicular to @p onto:
         * \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] onto The vector to reject from.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         * @return The perpendicular @ref Vector4D component.
         */
        template <StrictArithmetic U>
        auto reject(const Vector4D<U>& onto, bool ontoNormalized = false) const -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;


        /**
         * @brief @copybrief reject(const Vector4D<U>&, bool) const
         * Static wrapper for computing the perpendicular component of @p vector relative to @p onto.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         * @param[in] vector The vector to be rejected.
         * @param[in] onto The vector to reject from.
         * @param[in] ontoNormalized Optimization flag. Set to `true` if @p onto is already a unit vector.
         * @return The perpendicular @ref Vector4D component.
         */
        template <StrictArithmetic U>
        static auto reject(const Vector4D& vector, const Vector4D<U>& onto, bool ontoNormalized = false)
            -> Vector4D<std::common_type_t<T, U>>
            requires StrictArithmetic<T>;


        /** 
         * @brief Write the vector to an output stream.
         * Formats the vector as <x, y, z, w> string representation for debugging or logging.
         *
         * @tparam T Numeric type of the matrix.
         * @param os The output stream to write to.
         * @param vector The vector to be streamed.
         * @return A reference to the output stream @p os.
         */
        friend std::ostream& operator<<(std::ostream& os, const Vector4D& vector);
    };




    /*************************************
     *                                   *
     *       NON-MEMBER FUNCTIONS        *
     *                                   *
     *************************************/


    /**
     * @brief Scale the vector by a scalar value.
     * Multiplies @p scalar by each component of the vector and returns a new vector.
     *
     * @note Promotes the result to the `std::common_type_t` of `T` and `S`.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
     * @param[in]  scalar The value to scale by.
     * @param[in]  vector The vector to scale[RHS].
     * @return A new @ref Vector4D scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    auto operator*(S scalar, const Vector4D<T>& vector) -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>;




    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/
    using bVec4 = Vector4D<bool>;                ///< bool vector
    using iVec4 = Vector4D<int>;                 ///< int vector
    using uVec4 = Vector4D<unsigned int>;        ///< unsigned int vector
    using vec4 = Vector4D<float>;                ///< float vector
    using lVec4 = Vector4D<long long>;           ///< long long vector
    using dVec4 = Vector4D<double>;              ///< double vector
    using ulVec4 = Vector4D<unsigned long long>; ///< unsigned long long vector

} // namespace fgm


#include "Vector4D.tpp"