#pragma once
/**
 * @file Vector4D.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: January 26, 2026
 *
 * @brief @ref fgm::Vector4D template implementation.
 * @details This file contains the definitions of the template members declared in Matrix.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cassert>
#include <type_traits>
#include <iomanip>

#include "Config.h"

namespace fgm
{

    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template <Arithmetic T>
    Vector4D<T>::Vector4D(): x(T(0)), y(T(0)), z(T(0)), w(T(0))
    {
    }

    template <Arithmetic T>
    Vector4D<T>::Vector4D(T v1, T v2, T v3, T v4): x(v1), y(v2), z(v3), w(v4)
    {
    }

    template <Arithmetic T>
    Vector4D<T>::Vector4D(Vector2D<T> vec1, Vector2D<T> vec2): x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y)
    {
    }

    template <Arithmetic T>
    Vector4D<T>::Vector4D(Vector3D<T> vec, T v): x(vec.x), y(vec.y), z(vec.z), w(v)
    {
    }


    template <Arithmetic T>
    Vector4D<T>::Vector4D(T v, Vector3D<T> vec): x(v), y(vec.x), z(vec.y), w(vec.z)
    {
    }


    template <Arithmetic T>
    template <Arithmetic U>
    Vector4D<T>::Vector4D(const Vector4D<U>& other)
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)), w(static_cast<T>(other.w))
    {
    }


    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    T& Vector4D<T>::operator[](std::size_t i)
    {
        return (&x)[i];
    }

    template <Arithmetic T>
    const T& Vector4D<T>::operator[](std::size_t i) const
    {
        return (&x)[i];
    }


    /***************************************
     *                                     *
     *             EQUALITY                *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
    bool Vector4D<T>::allEq(const Vector4D<U>& other, double epsilon) const
    {

        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return x == other.x && y == other.y && z == other.z && w == other.w;
        else
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NaN. */
            return (x == other.x || std::abs(x - other.x) <= epsilon) &&
                (y == other.y || std::abs(y - other.y) <= epsilon) &&
                (z == other.z || std::abs(z - other.z) <= epsilon) &&
                (w == other.w || std::abs(w - other.w) <= epsilon);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    bool Vector4D<T>::allEq(const Vector4D& vecA, const Vector4D<U>& vecB, double epsilon)
    {
        return vecA.allEq(vecB, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    bool Vector4D<T>::allNeq(const Vector4D<U>& other, double epsilon) const
    {

        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return x != other.x || y != other.y || z != other.z || w != other.w;
        else
            /** @note Identity check and inverted logic handle NaN and INFINITY per IEEE 754. */
            return (x != other.x && !(std::abs(x - other.x) <= epsilon)) ||
                (y != other.y && !(std::abs(y - other.y) <= epsilon)) ||
                (z != other.z && !(std::abs(z - other.z) <= epsilon)) ||
                (w != other.w && !(std::abs(w - other.w) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    bool Vector4D<T>::allNeq(const Vector4D& vecA, const Vector4D<U>& vecB, double epsilon)
    {
        return vecA.allNeq(vecB, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    bool Vector4D<T>::operator==(const Vector4D<U>& other) const
    {
        return this->allEq(other);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    bool Vector4D<T>::operator!=(const Vector4D<U>& other) const
    {
        return this->allNeq(other);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    Vector4D<bool> Vector4D<T>::eq(const Vector4D<U>& other, double epsilon) const
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return Vector4D(x == other.x, y == other.y, z == other.z, w == other.w);
        else
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NaN. */
            return Vector4D(
                (x == other.x || std::abs(x - other.x) <= epsilon), (y == other.y || std::abs(y - other.y) <= epsilon),
                (z == other.z || std::abs(z - other.z) <= epsilon), (w == other.w || std::abs(w - other.w) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    Vector4D<bool> Vector4D<T>::eq(const Vector4D& vecA, const Vector4D<U>& vecB, double epsilon)
    {
        return vecA.eq(vecB, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    Vector4D<bool> Vector4D<T>::neq(const Vector4D<U>& other, double epsilon) const
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return Vector4D(x != other.x, y != other.y, z != other.z, w != other.w);
        else
            /** @note Identity check and inverted logic handle NaN and INFINITY per IEEE 754. */
            return Vector4D<bool>((x != other.x) && !(std::abs(x - other.x) <= epsilon),
                                  (y != other.y) && !(std::abs(y - other.y) <= epsilon),
                                  (z != other.z) && !(std::abs(z - other.z) <= epsilon),
                                  (w != other.w) && !(std::abs(w - other.w) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    Vector4D<bool> Vector4D<T>::neq(const Vector4D& vecA, const Vector4D<U>& vecB, double epsilon)
    {
        return vecA.neq(vecB, epsilon);
    }


    /***************************************
     *                                     *
     *            COMPARISONS              *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<bool> Vector4D<T>::gt(const Vector4D<U>& other) const
        requires StrictArithmetic<T>
    {
        return Vector4D(x > other.x, y > other.y, z > other.z, w > other.w);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<bool> Vector4D<T>::gt(const Vector4D& vecA, const Vector4D<U>& vecB)
        requires StrictArithmetic<T>
    {
        return vecA.gt(vecB);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<bool> Vector4D<T>::gte(const Vector4D<U>& other) const
        requires StrictArithmetic<T>
    {
        return Vector4D(x >= other.x, y >= other.y, z >= other.z, w >= other.w);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<bool> Vector4D<T>::gte(const Vector4D& vecA, const Vector4D<U>& vecB)
        requires StrictArithmetic<T>
    {
        return vecA.gte(vecB);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<bool> Vector4D<T>::lt(const Vector4D<U>& other) const
        requires StrictArithmetic<T>
    {
        return Vector4D(x < other.x, y < other.y, z < other.z, w < other.w);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<bool> Vector4D<T>::lt(const Vector4D& vecA, const Vector4D<U>& vecB)
        requires StrictArithmetic<T>
    {
        return vecA.lt(vecB);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<bool> Vector4D<T>::lte(const Vector4D<U>& other) const
        requires StrictArithmetic<T>
    {
        return Vector4D(x <= other.x, y <= other.y, z <= other.z, w <= other.w);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<bool> Vector4D<T>::lte(const Vector4D& vecA, const Vector4D<U>& vecB)
        requires StrictArithmetic<T>
    {
        return vecA.lte(vecB);
    }


#ifdef ENABLE_FGM_SHADER_OPERATORS
    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<bool> Vector4D<T>::operator>(const Vector4D<U>& other) const
        requires StrictArithmetic<T>
    {
        return this->gt(other);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<bool> Vector4D<T>::operator>=(const Vector4D<U>& other) const
        requires StrictArithmetic<T>
    {
        return this->gte(other);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<bool> Vector4D<T>::operator<(const Vector4D<U>& other) const
        requires StrictArithmetic<T>
    {
        return this->lt(other);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<bool> Vector4D<T>::operator<=(const Vector4D<U>& other) const
        requires StrictArithmetic<T>
    {
        return this->lte(other);
    }
#endif


    /***************************************
     *                                     *
     *      BOOLEAN BITWISE OPERATORS      *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    Vector4D<bool> Vector4D<T>::operator&(const Vector4D<bool>& other) const
        requires std::is_same_v<T, bool>
    {
        return Vector4D(x & other.x, y & other.y, z & other.z, w & other.w);
    }

    template <Arithmetic T>
    Vector4D<bool> Vector4D<T>::operator|(const Vector4D<bool>& other) const
        requires std::is_same_v<T, bool>
    {
        return Vector4D(x | other.x, y | other.y, z | other.z, w | other.w);
    }

    template <Arithmetic T>
    Vector4D<bool> Vector4D<T>::operator!() const
        requires std::is_same_v<T, bool>
    {
        return Vector4D(!x, !y, !z, !w);
    }


    /*************************************
     *                                   *
     *      ARITHMETIC OPERATORS         *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    auto Vector4D<T>::operator+(const Vector4D<U>& other) const -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Vector4D<R>(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<T>& Vector4D<T>::operator+=(const Vector4D<U>& other)
        requires StrictArithmetic<T>
    {
        x += static_cast<T>(other.x);
        y += static_cast<T>(other.y);
        z += static_cast<T>(other.z);
        w += static_cast<T>(other.w);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    auto Vector4D<T>::operator-(const Vector4D<U>& other) const -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Vector4D<R>(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    Vector4D<T>& Vector4D<T>::operator-=(const Vector4D<U>& other)
        requires StrictArithmetic<T>
    {
        x -= static_cast<T>(other.x);
        y -= static_cast<T>(other.y);
        z -= static_cast<T>(other.z);
        w -= static_cast<T>(other.w);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    auto Vector4D<T>::operator*(S scalar) const -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        return Vector4D<R>(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    template <StrictArithmetic T, StrictArithmetic S>
    auto operator*(S scalar, const Vector4D<T>& vector) -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        return vector * scalar;
    }

    template <Arithmetic T>
    template <StrictArithmetic S>
    Vector4D<T>& Vector4D<T>::operator*=(S scalar)
        requires StrictArithmetic<T>
    {

        x = static_cast<T>(scalar * x);
        y = static_cast<T>(scalar * y);
        z = static_cast<T>(scalar * z);
        w = static_cast<T>(scalar * w);
        return *this;
    }

    template <Arithmetic T>
    template <StrictArithmetic S>
    auto Vector4D<T>::operator/(S scalar) const -> Vector4D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            R factor = R(1) / static_cast<R>(scalar);
            return Vector4D<R>(x * factor, y * factor, z * factor, w * factor);
        }
        else
        {
            assert(scalar != 0 && "Integral division by zero");
            R tScalar = static_cast<R>(scalar);
            return Vector4D<R>(x / tScalar, y / tScalar, z / tScalar, w / tScalar);
        }
    }

    template <Arithmetic T>
    template <StrictArithmetic S>
    Vector4D<T>& Vector4D<T>::operator/=(S scalar)
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            R factor = R(1) / static_cast<R>(scalar);

            x = static_cast<T>(factor * x);
            y = static_cast<T>(factor * y);
            z = static_cast<T>(factor * z);
            w = static_cast<T>(factor * w);
        }
        else
        {
            assert(scalar != 0 && "Integral division by zero");
            x /= static_cast<T>(scalar);
            y /= static_cast<T>(scalar);
            z /= static_cast<T>(scalar);
            w /= static_cast<T>(scalar);
        }

        return *this;
    }


    /*************************************
     *                                   *
     *        VECTOR DOT PRODUCT         *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    auto Vector4D<T>::dot(const Vector4D<U>& other) const -> std::common_type_t<T, U>
        requires StrictArithmetic<T>
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    auto Vector4D<T>::dot(const Vector4D& vecA, const Vector4D<U>& vecB) -> std::common_type_t<T, U>
        requires StrictArithmetic<T>
    {
        return vecA.dot(vecB);
    }


    /*************************************
     *                                   *
     *         VECTOR MAGNITUDE          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    Magnitude<T> Vector4D<T>::mag() const
        requires StrictArithmetic<T>
    {
        using M = Magnitude<T>;

        M tX = static_cast<M>(x);
        M tY = static_cast<M>(y);
        M tZ = static_cast<M>(z);
        M tW = static_cast<M>(w);

        return sqrt(tX * tX + tY * tY + tZ * tZ + tW * tW);
    }

    template <Arithmetic T>
    Magnitude<T> Vector4D<T>::mag(const Vector4D& vec)
        requires StrictArithmetic<T>
    {
        return vec.mag();
    }


    /*************************************
     *                                   *
     *       VECTOR NORMALIZATION        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    Vector4D<Magnitude<T>> Vector4D<T>::normalize() const
        requires StrictArithmetic<T>
    {
        using R = Magnitude<T>;
        R magnitude = mag();

        if constexpr (std::is_same_v<R, double>)
            assert(magnitude > DOUBLE_EPSILON && "Vector4D Normalization : Division by 0");
        else
            assert(magnitude > FLOAT_EPSILON && "Vector4D Normalization : Division by 0");

        return *this / magnitude;
    }

    template <Arithmetic T>
    Vector4D<Magnitude<T>> Vector4D<T>::normalize(const Vector4D& vec)
        requires StrictArithmetic<T>
    {
        return vec.normalize();
    }


    /*************************************
     *                                   *
     *        VECTOR PROJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    auto Vector4D<T>::project(const Vector4D<U>& onto, bool ontoNormalized) const -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        if (ontoNormalized)
            return this->dot(onto) * onto; // a.dot(b) * b
        // Static cast is need to ensure that integral type dots don't lose much precision
        return this->dot(onto) / static_cast<Magnitude<R>>(onto.dot(onto)) * onto; // a.dot(b) / b.dot(b) * b
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    auto Vector4D<T>::project(const Vector4D& vector, const Vector4D<U>& onto, bool ontoNormalized)
        -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        return vector.project(onto, ontoNormalized);
    }


    /*************************************
     *                                   *
     *         VECTOR REJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    auto Vector4D<T>::reject(const Vector4D<U>& onto, bool ontoNormalized) const -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        return *this - this->project(onto, ontoNormalized);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
    auto Vector4D<T>::reject(const Vector4D& vector, const Vector4D<U>& onto, bool ontoNormalized)
        -> Vector4D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        return vector.reject(onto, ontoNormalized);
    }

    template <Arithmetic T>
    std::ostream& operator<<(std::ostream& os, const Vector4D<T>& vector)
    {        
        os << "<";
        Config::LOG_PRECISION<T>
        if constexpr (std::is_same_v<T, double>)
            os << std::setprecision(DOUBLE_EPSILON);
        else if constexpr(std::is_floating_point_v<T>)
            os << std::setprecision(FLOAT_EPSILON);

        os << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w;
        os << ">\n";
        return os;
    }

} // namespace fgm
