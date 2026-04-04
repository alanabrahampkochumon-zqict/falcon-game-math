#pragma once
/**
 * @file Vector2D.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: January 24, 2026
 *
 * @brief @ref Vector2D template implementation.
 * @details This file contains the definitions of the template members declared in Vector2D.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2D.h"

#include <type_traits>



namespace fgm
{

    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Vector2D<T>::Vector2D() noexcept: x(T(0)), y(T(0))
    {}


    template <Arithmetic T>
    constexpr Vector2D<T>::Vector2D(T v1, T v2) noexcept: x(v1), y(v2)
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector2D<T>::Vector2D(const Vector2D<U>& other) noexcept
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))
    {}




    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr T& Vector2D<T>::operator[](std::size_t i) noexcept
    {
        return (&x)[i];
    }


    template <Arithmetic T>
    constexpr const T& Vector2D<T>::operator[](std::size_t i) const noexcept
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
    constexpr bool Vector2D<T>::allEq(const Vector2D<U>& rhs, const double epsilon) const noexcept
    {

        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return x == rhs.x && y == rhs.y;
        else
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return (x == rhs.x || std::abs(x - rhs.x) <= epsilon) && (y == rhs.y || std::abs(y - rhs.y) <= epsilon);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector2D<T>::allEq(const Vector2D& lhs, const Vector2D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.allEq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector2D<T>::allNeq(const Vector2D<U>& rhs, const double epsilon) const noexcept
    {

        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return x != rhs.x || y != rhs.y;
        else
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return (x != rhs.x && !(std::abs(x - rhs.x) <= epsilon)) ||
                (y != rhs.y && !(std::abs(y - rhs.y) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector2D<T>::allNeq(const Vector2D& lhs, const Vector2D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.allNeq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector2D<T>::operator==(const Vector2D<U>& rhs) const noexcept
    {
        return this->allEq(rhs);
    }

    template <Arithmetic T>
    template <Arithmetic U>
    constexpr bool Vector2D<T>::operator!=(const Vector2D<U>& rhs) const noexcept
    {
        return this->allNeq(rhs);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::eq(const Vector2D<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return Vector2D(x == rhs.x, y == rhs.y);
        else
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return Vector2D((x == rhs.x || std::abs(x - rhs.x) <= epsilon),
                            (y == rhs.y || std::abs(y - rhs.y) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::eq(const Vector2D& lhs, const Vector2D<U>& rhs, const double epsilon) noexcept
    {
        return lhs.eq(rhs, epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::neq(const Vector2D<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
            return Vector2D(x != rhs.x, y != rhs.y);
        else
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return Vector2D<bool>((x != rhs.x) && !(std::abs(x - rhs.x) <= epsilon),
                                  (y != rhs.y) && !(std::abs(y - rhs.y) <= epsilon));
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::neq(const Vector2D& lhs, const Vector2D<U>& rhs,
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
    constexpr Vector2D<bool> Vector2D<T>::gt(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector2D(x > rhs.x, y > rhs.y);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::gt(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.gt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::gte(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector2D(x >= rhs.x, y >= rhs.y);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::gte(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.gte(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::lt(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return Vector2D(x < rhs.x, y < rhs.y);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::lt(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.lt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::lte(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<std::common_type_t<T, U>>;
        return Vector2D<bool>(static_cast<R>(x) <= static_cast<R>(rhs.x), static_cast<R>(y) <= static_cast<R>(rhs.y));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::lte(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.lte(rhs);
    }


#ifdef ENABLE_FGM_SHADER_OPERATORS

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::operator>(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->gt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::operator>=(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->gte(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::operator<(const Vector2D<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return this->lt(rhs);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<bool> Vector2D<T>::operator<=(const Vector2D<U>& rhs) const noexcept
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
    constexpr Vector2D<bool> Vector2D<T>::operator&(const Vector2D<bool>& rhs) const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector2D(x & rhs.x, y & rhs.y);
    }


    constexpr Vector2D<bool>& Vector2D<bool>::operator&=(const Vector2D<bool>& rhs) noexcept
    {
        (*this) = (*this) & rhs;
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector2D<bool> Vector2D<T>::operator|(const Vector2D<bool>& rhs) const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector2D(x | rhs.x, y | rhs.y);
    }


    template <Arithmetic T>
    constexpr Vector2D<bool>& Vector2D<T>::operator|=(const Vector2D<bool>& rhs) noexcept
    {
        (*this) = (*this) & rhs;
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector2D<bool> Vector2D<T>::operator!() const noexcept
        requires std::is_same_v<T, bool>
    {
        return Vector2D(!x, !y);
    }




    /*************************************
     *                                   *
     *      ARITHMETIC OPERATORS         *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::operator+(const Vector2D<U>& rhs) const noexcept -> Vector2D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Vector2D<R>(x + rhs.x, y + rhs.y);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<T>& Vector2D<T>::operator+=(const Vector2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        x += static_cast<T>(rhs.x);
        y += static_cast<T>(rhs.y);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::operator-(const Vector2D<U>& rhs) const noexcept -> Vector2D<std::common_type_t<T, U>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Vector2D<R>(x - rhs.x, y - rhs.y);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr Vector2D<T>& Vector2D<T>::operator-=(const Vector2D<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        x -= static_cast<T>(rhs.x);
        y -= static_cast<T>(rhs.y);
        return *this;
    }


    template <Arithmetic T>
    constexpr Vector2D<T> Vector2D<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    {
        return Vector2D(-x, -y);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector2D<T>::operator*(const S scalar) const noexcept -> Vector2D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        return Vector2D<R>(x * scalar, y * scalar);
    }


    template <StrictArithmetic T, StrictArithmetic S>
    constexpr auto operator*(const S scalar, const Vector2D<T>& vector) noexcept -> Vector2D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        return vector * scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vector2D<T>& Vector2D<T>::operator*=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {

        x = static_cast<T>(scalar * x);
        y = static_cast<T>(scalar * y);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector2D<T>::operator/(const S scalar) const noexcept -> Vector2D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            R factor = R(1) / static_cast<R>(scalar);
            return Vector2D<R>(x * factor, y * factor);
        }
        else
        {
            assert(scalar != 0 && "Integral division by zero");
            R tScalar = static_cast<R>(scalar);
            return Vector2D<R>(x / tScalar, y / tScalar);
        }
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vector2D<T>& Vector2D<T>::operator/=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            R factor = R(1) / static_cast<R>(scalar);

            x = static_cast<T>(factor * x);
            y = static_cast<T>(factor * y);
        }
        else
        {
            x /= static_cast<T>(scalar);
            y /= static_cast<T>(scalar);
        }

        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector2D<T>::safeDiv(const S scalar) const noexcept -> Vector2D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
            if (hasNaN() | std::isnan(scalar) | (std::abs(scalar) <= std::numeric_limits<S>::epsilon()))
                return fgm::vec2d::zero<R>;
        if constexpr (std::is_integral_v<R>)
            if (scalar == 0)
                return fgm::vec2d::zero<R>;

        return (*this) / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector2D<T>::safeDiv(const Vector2D& vec, const S scalar) noexcept
        -> Vector2D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        return vec.safeDiv(scalar);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector2D<T>::tryDiv(S scalar, OperationStatus& status) const noexcept
        -> Vector2D<std::common_type_t<T, S>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (hasNaN() | std::isnan(scalar))
            {
                status = OperationStatus::NANOPERAND;
                return fgm::vec2d::zero<R>;
            }
            if (std::abs(scalar) <= std::numeric_limits<S>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return fgm::vec2d::zero<R>;
            }
        }

        if constexpr (std::is_integral_v<R>)
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return fgm::vec2d::zero<R>;
            }


        status = OperationStatus::SUCCESS;
        return (*this) / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr auto Vector2D<T>::tryDiv(const Vector2D& vec, S scalar, OperationStatus& status) noexcept
        -> Vector2D<std::common_type_t<T, S>>
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
    constexpr auto Vector2D<T>::dot(const Vector2D<U>& rhs) const noexcept -> std::common_type_t<T, U>
        requires StrictArithmetic<T>
    {
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__FMA4__) || defined(__AVX2__)
        using R = std::common_type_t<T, U>;
        if constexpr (std::is_floating_point_v<R>)
            return std::fma(static_cast<R>(x), static_cast<R>(rhs.x),
                            std::fma(static_cast<R>(y), static_cast<R>(rhs.y), T(0)));
        else
            return x * rhs.x + y * rhs.y;
#else
        return x * rhs.x + y * rhs.y;
#endif
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::dot(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept -> std::common_type_t<T, U>
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
    constexpr auto Vector2D<T>::cross(const Vector2D<U>& rhs) const noexcept -> std::common_type_t<T, U>
    {
        using R = std::common_type_t<T, U>;
        return R(x * rhs.y - y * rhs.x);
    }


    template <Arithmetic T>
    template <Arithmetic U>
    constexpr auto Vector2D<T>::cross(const Vector2D& lhs, const Vector2D<U>& rhs) noexcept
        -> std::common_type_t<T, U>
    {
        return lhs.cross(rhs);
    }




    /*************************************
     *                                   *
     *         VECTOR MAGNITUDE          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    constexpr Magnitude<T> Vector2D<T>::mag() const noexcept
        requires StrictArithmetic<T>
    {
        using M = Magnitude<T>;

        M tX = static_cast<M>(x);
        M tY = static_cast<M>(y);

        return sqrt(tX * tX + tY * tY);
    }

    template <Arithmetic T>
    constexpr Magnitude<T> Vector2D<T>::mag(const Vector2D& vec) noexcept
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
    constexpr Vector2D<Magnitude<T>> Vector2D<T>::normalize() const noexcept
        requires StrictArithmetic<T>
    {
        return (*this) / mag();
    }


    template <Arithmetic T>
    constexpr Vector2D<Magnitude<T>> Vector2D<T>::normalize(const Vector2D& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.normalize();
    }


    template <Arithmetic T>
    constexpr Vector2D<Magnitude<T>> Vector2D<T>::safeNormalize() const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<T>;
        R magnitude = mag();
        if (std::isnan(magnitude))
            return fgm::vec2d::zero<R>;
        if (magnitude <= Config::EPSILON_SQUARE<R>)
            return fgm::vec2d::zero<R>;

        return *this / magnitude;
    }


    template <Arithmetic T>
    constexpr Vector2D<Magnitude<T>> Vector2D<T>::safeNormalize(const Vector2D& vec) noexcept
        requires StrictArithmetic<T>
    {
        return vec.safeNormalize();
    }


    template <Arithmetic T>
    constexpr Vector2D<Magnitude<T>> Vector2D<T>::tryNormalize(OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<T>;
        R magnitude = mag();
        if (std::isnan(magnitude))
        {
            status = OperationStatus::NANOPERAND;
            return fgm::vec2d::zero<R>;
        }
        if (magnitude <= Config::EPSILON_SQUARE<R>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return fgm::vec2d::zero<R>;
        }

        status = OperationStatus::SUCCESS;
        return *this / magnitude;
    }


    template <Arithmetic T>
    constexpr Vector2D<Magnitude<T>> Vector2D<T>::tryNormalize(const Vector2D& vec, OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    {
        return vec.tryNormalize(status);
    }


    
    /*************************************
     *                                   *
     *        VECTOR PROJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::project(const Vector2D<U>& onto, const bool ontoNormalized) const noexcept
        -> Vector2D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        if (ontoNormalized)
            return this->dot(onto) * onto; // a.dot(b) * b

        /** @note Static cast ensures integral type dots don't lose much precision */
        return this->dot(onto) / static_cast<Magnitude<R>>(onto.dot(onto)) * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::project(const Vector2D& vec, const Vector2D<U>& onto,
                                        const bool ontoNormalized) noexcept
        -> Vector2D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return vec.project(onto, ontoNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::safeProject(const Vector2D<U>& onto, const bool ontoNormalized) const noexcept
        -> Vector2D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        using MagType = Magnitude<R>;
        if (ontoNormalized)
            return this->dot(onto) * onto;

        /** @note Static cast ensures integral type dots don't lose much precision */
        const auto ontoSquared = static_cast<MagType>(onto.dot(onto));

        if (hasNaN() | std::isnan(ontoSquared))
            return fgm::vec2d::zero<MagType>;

        if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
            return fgm::vec2d::zero<MagType>;

        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::safeProject(const Vector2D& vec, const Vector2D<U>& onto,
                                            const bool ontoNormalized) noexcept
        -> Vector2D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return vec.safeProject(onto, ontoNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::tryProject(const Vector2D<U>& onto, OperationStatus& status,
                                           const bool ontoNormalized) const noexcept
        -> Vector2D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        using MagType = Magnitude<R>;

        if (ontoNormalized)
        {
            status = OperationStatus::SUCCESS;
            return this->dot(onto) * onto;
        }

        /** @note Static cast ensures integral type dots don't lose much precision */
        const auto ontoSquared = static_cast<MagType>(onto.dot(onto));

        if (hasNaN() | std::isnan(ontoSquared))
        {
            status = OperationStatus::NANOPERAND;
            return fgm::vec2d::zero<MagType>;
        }

        if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return fgm::vec2d::zero<MagType>;
        }
         
        status = OperationStatus::SUCCESS;
        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::tryProject(const Vector2D& vec, const Vector2D<U>& onto, OperationStatus& status,
                                           const bool ontoNormalized) noexcept
        -> Vector2D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return vec.tryProject(onto, status, ontoNormalized);
    }


    
    
    /*************************************
     *                                   *
     *         VECTOR REJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::reject(const Vector2D<U>& from, const bool fromNormalized) const noexcept
        -> Vector2D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return *this - this->project(from, fromNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::reject(const Vector2D& vector, const Vector2D<U>& from,
                                       const bool fromNormalized) noexcept
        -> Vector2D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return vector.reject(from, fromNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::safeReject(const Vector2D<U>& from, const bool fromNormalized) const noexcept
        -> Vector2D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
            return fgm::vec2d::zero<std::common_type_t<T, U>>;

        return *this - safeProject(from, fromNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::safeReject(const Vector2D& vec, const Vector2D<U>& from,
                                           const bool fromNormalized) noexcept
        -> Vector2D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return vec.safeReject(from, fromNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::tryReject(const Vector2D<U>& from, OperationStatus& status,
                                          bool fromNormalized) const noexcept
        -> Vector2D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return fgm::vec2d::zero<std::common_type_t<T, U>>;
        }

        return *this - this->tryProject(from, status, fromNormalized);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
    constexpr auto Vector2D<T>::tryReject(const Vector2D& vec, const Vector2D<U>& from, OperationStatus& status,
                                          bool fromNormalized) noexcept -> Vector2D<Magnitude<std::common_type_t<T, U>>>
        requires StrictArithmetic<T>
    {
        return vec.tryReject(from, status, fromNormalized);
    }




    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    constexpr bool Vector2D<T>::hasInf() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
            return std::isinf(x) | std::isinf(y);
        else
            return false;
    }


    template <Arithmetic T>
    constexpr bool Vector2D<T>::hasInf(const Vector2D& vec) noexcept
    {
        return vec.hasInf();
    }


    template <Arithmetic T>
    constexpr bool Vector2D<T>::hasNaN() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
            return std::isnan(x) | std::isnan(y);
        else
            return false;
    }


    template <Arithmetic T>
    constexpr bool Vector2D<T>::hasNaN(const Vector2D& vec) noexcept
    {
        return vec.hasNaN();
    }

} // namespace fgm