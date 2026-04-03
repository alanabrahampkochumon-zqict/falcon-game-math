#pragma once
/**
 * @file Vector3D.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: January 19, 2026
 *
 * @brief @ref Vector3D template implementation.
 * @details This file contains the definitions of the template members declared in Vector3D.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


// TODO: Enable strict types using `using R = std::common_type_t<T, U>`

namespace fgm
{


    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Vector3D<T>::Vector3D() noexcept: x(T(0)), y(T(0)), z(T(0))
    {}


    template <Arithmetic T>
    constexpr Vector3D<T>::Vector3D(T v1, T v2, T v3) noexcept: x(v1), y(v2), z(v3)
    {}


    template <Arithmetic T>
    constexpr Vector3D<T>::Vector3D(Vector2D<T> vec, T v) noexcept: x(vec.x), y(vec.y), z(v)
    {}


    template <Arithmetic T>
    constexpr Vector3D<T>::Vector3D(T v, Vector2D<T> vec) noexcept: x(v), y(vec.x), z(vec.y)
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector3D<T>::Vector3D(const Vector3D<U>& other) noexcept
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z))
    {}




    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    T& Vector3D<T>::operator[](std::size_t i)
    {
        return ((&x)[i]);
    }


    template <Arithmetic T>
    const T& Vector3D<T>::operator[](std::size_t i) const
    {
        return ((&x)[i]);
    }




    /***************************************
     *                                     *
     *             EQUALITY                *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector3D<T>::allEq(const Vector3D<U>& rhs, const double epsilon) const noexcept
    {

        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return x == rhs.x && y == rhs.y && z == rhs.z;
        else
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return (x == rhs.x || std::abs(x - rhs.x) <= epsilon) && (y == rhs.y || std::abs(y - rhs.y) <= epsilon) &&
                (z == rhs.z || std::abs(z - rhs.z) <= epsilon);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector3D<T>::allEq(const Vector3D& lhs, const Vector3D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.allEq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector3D<T>::allNeq(const Vector3D<U>& rhs, const double epsilon) const noexcept
    {

        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return x != rhs.x || y != rhs.y || z != rhs.z;
        else
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return (x != rhs.x && !(std::abs(x - rhs.x) <= epsilon)) ||
                (y != rhs.y && !(std::abs(y - rhs.y) <= epsilon)) || (z != rhs.z && !(std::abs(z - rhs.z) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector3D<T>::allNeq(const Vector3D& lhs, const Vector3D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.allNeq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector3D<T>::operator==(const Vector3D<U>& rhs) const noexcept
    {
        return this->allEq(rhs);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector3D<T>::operator!=(const Vector3D<U>& rhs) const noexcept
    {
        return this->allNeq(rhs);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::eq(const Vector3D<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return Vector3D(x == rhs.x, y == rhs.y, z == rhs.z);
        else
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return Vector3D((x == rhs.x || std::abs(x - rhs.x) <= epsilon),
                            (y == rhs.y || std::abs(y - rhs.y) <= epsilon),
                            (z == rhs.z || std::abs(z - rhs.z) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::eq(const Vector3D& lhs, const Vector3D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.eq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::neq(const Vector3D<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return Vector3D(x != rhs.x, y != rhs.y, z != rhs.z);
        else
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return Vector3D<bool>((x != rhs.x) && !(std::abs(x - rhs.x) <= epsilon),
                                  (y != rhs.y) && !(std::abs(y - rhs.y) <= epsilon),
                                  (z != rhs.z) && !(std::abs(z - rhs.z) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::neq(const Vector3D& lhs, const Vector3D<U>& rhs,
                                              const double epsilon) noexcept
    {
        return lhs.neq(rhs, epsilon);
    }




    /***************************************
     *                                     *
     *            COMPARISONS              *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::gt(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector3D(x > rhs.x, y > rhs.y, z > rhs.z);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::gt(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.gt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::gte(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector3D(x >= rhs.x, y >= rhs.y, z >= rhs.z);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::gte(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.gte(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::lt(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector3D(x < rhs.x, y < rhs.y, z < rhs.z);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::lt(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.lt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::lte(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<std::common_type_t<T, U>>;
        return Vector3D<bool>(static_cast<R>(x) <= static_cast<R>(rhs.x), static_cast<R>(y) <= static_cast<R>(rhs.y),
                              static_cast<R>(z) <= static_cast<R>(rhs.z));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::lte(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.lte(rhs);
    }


#ifdef ENABLE_FGM_SHADER_OPERATORS

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::operator>(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->gt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::operator>=(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->gte(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::operator<(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->lt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<bool> Vector3D<T>::operator<=(const Vector3D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->lte(rhs);
    }

#endif




    /***************************************
     *                                     *
     *      BOOLEAN BITWISE OPERATORS      *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    constexpr Vector3D<bool> Vector3D<T>::operator&(const Vector3D<bool>& rhs) const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector3D(x & rhs.x, y & rhs.y, z & rhs.z);
    }


    constexpr Vector3D<bool>& Vector3D<bool>::operator&=(const Vector3D<bool>& rhs) noexcept
    {
        (*this) = (*this) & rhs;
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector3D<bool> Vector3D<T>::operator|(const Vector3D<bool>& rhs) const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector3D(x | rhs.x, y | rhs.y, z | rhs.z);
    }


    template <Arithmetic T>
    constexpr Vector3D<bool>& Vector3D<T>::operator|=(const Vector3D<bool>& rhs) noexcept
    {
        (*this) = (*this) & rhs;
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector3D<bool> Vector3D<T>::operator!() const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector3D(!x, !y, !z);
    }



    /*************************************
     *                                   *
     *      ARITHMETIC OPERATORS         *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector3D<T>::operator+(const Vector3D<U>& rhs) const noexcept -> Vector3D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Vector3D<R>(x + rhs.x, y + rhs.y, z + rhs.z);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<T>& Vector3D<T>::operator+=(const Vector3D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        x += static_cast<T>(rhs.x);
        y += static_cast<T>(rhs.y);
        z += static_cast<T>(rhs.z);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector3D<T>::operator-(const Vector3D<U>& rhs) const noexcept -> Vector3D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Vector3D<R>(x - rhs.x, y - rhs.y, z - rhs.z);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector3D<T>& Vector3D<T>::operator-=(const Vector3D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        x -= static_cast<T>(rhs.x);
        y -= static_cast<T>(rhs.y);
        z -= static_cast<T>(rhs.z);
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector3D<T> Vector3D<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    {
        return Vector3D(-x, -y, -z);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector3D<T>::operator*(const S scalar) const noexcept -> Vector3D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        return Vector3D<R>(x * scalar, y * scalar, z * scalar);
    }


    template <StrictArithmetic T, StrictArithmetic S>
    constexpr auto operator*(const S scalar, const Vector3D<T>& vector) noexcept -> Vector3D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        return vector * scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vector3D<T>& Vector3D<T>::operator*=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {

        x = static_cast<T>(scalar * x);
        y = static_cast<T>(scalar * y);
        z = static_cast<T>(scalar * z);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector3D<T>::operator/(const S scalar) const noexcept -> Vector3D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            R factor = R(1) / static_cast<R>(scalar);
            return Vector3D<R>(x * factor, y * factor, z * factor);
        }
        else
        {
            assert(scalar != 0 && "Integral division by zero");
            R tScalar = static_cast<R>(scalar);
            return Vector3D<R>(x / tScalar, y / tScalar, z / tScalar);
        }
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vector3D<T>& Vector3D<T>::operator/=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            R factor = R(1) / static_cast<R>(scalar);

            x = static_cast<T>(factor * x);
            y = static_cast<T>(factor * y);
            z = static_cast<T>(factor * z);
        }
        else
        {
            x /= static_cast<T>(scalar);
            y /= static_cast<T>(scalar);
            z /= static_cast<T>(scalar);
        }

        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector3D<T>::safeDiv(const S scalar) const noexcept -> Vector3D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
            if (hasNaN() | std::isnan(scalar) | (std::abs(scalar) <= std::numeric_limits<S>::epsilon()))
                return fgm::vec3d::zero<R>;
        if constexpr (std::is_integral_v<R>)
            if (scalar == 0)
                return fgm::vec3d::zero<R>;

        return (*this) / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector3D<T>::safeDiv(const Vector3D& vec, const S scalar) noexcept
        -> Vector3D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        return vec.safeDiv(scalar);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector3D<T>::tryDiv(S scalar, OperationStatus& status) const noexcept
        -> Vector3D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (hasNaN() | std::isnan(scalar))
            {
                status = OperationStatus::NANOPERAND;
                return fgm::vec3d::zero<R>;
            }
            if (std::abs(scalar) <= std::numeric_limits<S>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return fgm::vec3d::zero<R>;
            }
        }

        if constexpr (std::is_integral_v<R>)
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return fgm::vec3d::zero<R>;
            }


        status = OperationStatus::SUCCESS;
        return (*this) / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector3D<T>::tryDiv(const Vector3D& vec, S scalar, OperationStatus& status) noexcept
        -> Vector3D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        return vec.tryDiv(scalar, status);
    }




    /*************************************
     *                                   *
     *        VECTOR DOT PRODUCT         *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector3D<T>::dot(const Vector3D<U>& rhs) const noexcept -> std::common_type_t<T, U>
        requires StrictArithmetic<T>
    {
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__FMA4__) || defined(__AVX2__)
        using R = std::common_type_t<T, U>;
        if constexpr (std::is_floating_point_v<R>)
            return std::fma(static_cast<R>(x), static_cast<R>(rhs.x),
                            std::fma(static_cast<R>(y), static_cast<R>(rhs.y),
                                     std::fma(static_cast<R>(z), static_cast<R>(rhs.z), T(0))));
        else
            return x * rhs.x + y * rhs.y + z * rhs.z;
#else
        return x * rhs.x + y * rhs.y + z * rhs.z;
#endif
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector3D<T>::dot(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept -> std::common_type_t<T, U>
        requires StrictArithmetic<T>
    {
        return lhs.dot(rhs);
    }




    /*************************************
     *                                   *
     *       VECTOR CROSS PRODUCT        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr auto Vector3D<T>::cross(const Vector3D<U>& rhs) const noexcept -> Vector3D<std::common_type_t<T, U>>
    {
        using R = std::common_type_t<T, U>;
        return Vector3D<R>(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr auto Vector3D<T>::cross(const Vector3D& lhs, const Vector3D<U>& rhs) noexcept
        -> Vector3D<std::common_type_t<T, U>>
    {
        return lhs.cross(rhs);
    }




    /*************************************
     *                                   *
     *         VECTOR MAGNITUDE          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Magnitude<T> Vector3D<T>::mag() const noexcept
        requires StrictArithmetic<T>
    {
        using M = Magnitude<T>;

        M tX = static_cast<M>(x);
        M tY = static_cast<M>(y);
        M tZ = static_cast<M>(z);

        return sqrt(tX * tX + tY * tY + tZ * tZ);
    }

    template <Arithmetic T>
    constexpr Magnitude<T> Vector3D<T>::mag(const Vector3D& vec) noexcept
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
    constexpr Vector3D<Magnitude<T>> Vector3D<T>::normalize() const noexcept
        requires StrictArithmetic<T>
    {
        return (*this) / mag();
    }


    template <Arithmetic T>
    constexpr Vector3D<Magnitude<T>> Vector3D<T>::normalize(const Vector3D& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.normalize();
    }


    template <Arithmetic T>
    constexpr Vector3D<Magnitude<T>> Vector3D<T>::safeNormalize() const noexcept
        requires StrictArithmetic<T>
    {
        return normalize();
    }


    template <Arithmetic T>
    constexpr Vector3D<Magnitude<T>> Vector3D<T>::safeNormalize(const Vector3D& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.normalize();
    }


    template <Arithmetic T>
    constexpr Vector3D<Magnitude<T>> Vector3D<T>::tryNormalize(OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        return normalize();
    }


    template <Arithmetic T>
    constexpr Vector3D<Magnitude<T>> Vector3D<T>::tryNormalize(const Vector3D& vec, OperationStatus& status) noexcept
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
    template <Arithmetic U>
    auto Vector3D<T>::project(const Vector3D<U>& onto, bool ontoNormalized) const -> Vector3D<std::common_type_t<T, U>>
    {
        if (ontoNormalized)
        {
            // Pb||a^ = a.dot(b) * b
            return this->dot(onto) * onto;
        }
        else
        {
            // Pb||a^ = a.dot(b) / b.dot(b) * b
            return this->dot(onto) / onto.dot(onto) * onto;
        }
    }

    template <Arithmetic T>
    template <Arithmetic U>
    auto Vector3D<T>::project(const Vector3D& vector, const Vector3D<U>& onto, bool ontoNormalized)
        -> Vector3D<std::common_type_t<T, U>>
    {
        return vector.project(onto, ontoNormalized);
    }


    /*************************************
     *                                   *
     *         VECTOR REJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <Arithmetic U>
    auto Vector3D<T>::reject(const Vector3D<U>& onto, bool ontoNormalized) const -> Vector3D<std::common_type_t<T, U>>
    {
        return *this - this->project(onto, ontoNormalized);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    auto Vector3D<T>::reject(const Vector3D& vector, const Vector3D<U>& onto, bool ontoNormalized)
        -> Vector3D<std::common_type_t<T, U>>
    {
        return vector.reject(onto, ontoNormalized);
    }




    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr bool Vector3D<T>::hasInf() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
            return std::isinf(x) | std::isinf(y) | std::isinf(z);
        else
            return false;
    }


    template <Arithmetic T>
    constexpr bool Vector3D<T>::hasInf(const Vector3D& vec) noexcept
    {
        return vec.hasInf();
    }


    template <Arithmetic T>
    constexpr bool Vector3D<T>::hasNaN() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
            return std::isnan(x) | std::isnan(y) | std::isnan(z);
        else
            return false;
    }


    template <Arithmetic T>
    constexpr bool Vector3D<T>::hasNaN(const Vector3D& vec) noexcept
    {
        return vec.hasNaN();
    }
} // namespace fgm
