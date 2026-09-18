#pragma once
/**
 * @file Vec2.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 15, 2026
 *
 * @brief @ref Vec2 template implementation.
 * @details This file contains the definitions of the template members declared in Vec2.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "fgm/common/Messages.h"
#include "fgm/common/Types.h"
#include "fgm/common/Utils.h"
#include "fgm/common/Wrappers.h"

#include <algorithm>
#include <cmath>
#include <type_traits>


#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wbitwise-instead-of-logical"
#endif


namespace fgm
{
    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T>::Vec2(T v1, T v2) noexcept: _data{ v1, v2 }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    FALCON_INLINE constexpr Vec2<T>::Vec2(const Vec2<U>& other) noexcept
    {
        // Required for clearing the upper lanes.
        // TODO: Update to return a ptr (maybe overload operator*)?
        _data.setZero();
        _data.set(static_cast<T>(other.x()), static_cast<T>(other.y()));
    }


    template <Arithmetic T>
    constexpr Vec2<T>::Vec2(const falcon::Simd128_t<T, DIMENSION>& reg) noexcept: _data{ reg }
    {}

    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    /**************************************
     *                                    *
     *        SPATIAL COORDINATES         *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::x() const noexcept
    { return _data.template getAt<0>(); }


    template <Arithmetic T>
    constexpr Vec2<T>::template ConstIndexableProxy<0> Vec2<T>::x() noexcept
    { return ConstIndexableProxy<0>(*this); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::y() const noexcept
    { return _data.template getAt<1>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T>::template ConstIndexableProxy<1> Vec2<T>::y() noexcept
    { return ConstIndexableProxy<1>(*this); }


    /**************************************
     *                                    *
     *           STP COORDINATES          *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::s() const noexcept
    { return _data.template getAt<0>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T>::template ConstIndexableProxy<0> Vec2<T>::s() noexcept
    { return ConstIndexableProxy<0>(*this); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::t() const noexcept
    { return _data.template getAt<1>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T>::template ConstIndexableProxy<1> Vec2<T>::t() noexcept
    { return ConstIndexableProxy<1>(*this); }


    /**************************************
     *                                    *
     *         COLOR COORDINATES          *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::r() const noexcept
    { return _data.template getAt<0>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T>::template ConstIndexableProxy<0> Vec2<T>::r() noexcept
    { return ConstIndexableProxy<0>(*this); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::g() const noexcept
    { return _data.template getAt<1>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T>::template ConstIndexableProxy<1> Vec2<T>::g() noexcept
    { return ConstIndexableProxy<1>(*this); }


    /**************************************
     *                                    *
     *              INDEXING              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T>::IndexableProxy Vec2<T>::operator[](const std::size_t idx) noexcept
    {
        FALCON_ASSERT_MSG(idx < DIMENSION, fgm::messages::assertion::VEC_OUT_OF_BOUNDS_ACCESS);
        return IndexableProxy(*this, idx);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::operator[](const std::size_t idx) const noexcept
    {
        FALCON_ASSERT_MSG(idx < DIMENSION, fgm::messages::assertion::VEC_OUT_OF_BOUNDS_ACCESS);
        return _data.getAt(idx);
    }

    // TODO: Add swizzling after adding compiletime indexing (get<> and set<>)
    //     /**************************************
    //      *                                    *
    //      *             SWIZZLING              *
    //      *                                    *
    //      **************************************/
    //
    //     template <Arithmetic T>
    //     template <std::size_t... Indices>
    //     FALCON_INLINE constexpr auto Vec2<T>::swizzle() const noexcept
    //     {
    //         constexpr std::size_t swizzleDimension = sizeof...(Indices);
    //
    //         static_assert(((Indices < DIMENSION) && ...), "Index out of bounds!");
    //         static_assert(swizzleDimension > 0 && swizzleDimension <= DIMENSION &&
    //                       "Swizzle must return a scalar, or a 2D vector.");
    //         if constexpr (swizzleDimension == 2)
    //         {
    //             return Vec2(_data[Indices]...);
    //         }
    //         else
    //         {
    //             return T(_data[Indices]...);
    //         }
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <std::size_t... Indices>
    //     FALCON_INLINE constexpr auto Vec2<T>::swizzle(const Vec2& vec) noexcept
    //     { return vec.swizzle<Indices...>(); }
    //
    //
    //     /***************************************
    //      *                                     *
    //      *         EQUALITY (ABSOLUTE)         *
    //      *                                     *
    //      ***************************************/
    //
    //     template <Arithmetic T>
    //     template <Arithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr bool Vec2<T>::allEq(const Vec2& rhs, const double epsilon) const noexcept
    //     {
    //         if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
    //         {
    //             return _data[0] == rhs[0] && _data[1] == rhs[1];
    //         }
    //         else
    //         /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F.
    //         */
    //         {
    // // MSVC's constexpr evaluator incorrectly yields true for NaN relational comparisons.
    // // To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
    // // if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
    // #ifdef _MSC_VER
    //             if (std::is_constant_evaluated())
    //             {
    //                 if (hasNaN() || rhs.hasNaN())
    //                 {
    //                     return false;
    //                 }
    //             }
    // #endif
    //             return (_data[0] == rhs[0] || fgm::abs(_data[0] - rhs[0]) <= epsilon) &&
    //                 (_data[1] == rhs[1] || fgm::abs(_data[1] - rhs[1]) <= epsilon);
    //         }
    //     }
    //
    //     template <Arithmetic T>
    //     template <Arithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr bool Vec2<T>::allEq(const Vec2& lhs, const Vec2& rhs, const double epsilon)
    //     noexcept { return lhs.allEq(rhs, epsilon); }
    //
    //
    //     template <Arithmetic T>
    //     template <Arithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr bool Vec2<T>::anyNeq(const Vec2& rhs, const double epsilon) const noexcept
    //     {
    //         if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
    //         {
    //             return _data[0] != rhs[0] || _data[1] != rhs[1];
    //         }
    //         else
    //         {
    //             /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
    //             return (_data[0] != rhs[0] && !(fgm::abs(_data[0] - rhs[0]) <= epsilon)) ||
    //                 (_data[1] != rhs[1] && !(fgm::abs(_data[1] - rhs[1]) <= epsilon));
    //         }
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <Arithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr bool Vec2<T>::anyNeq(const Vec2& lhs, const Vec2& rhs, const double epsilon)
    //     noexcept { return lhs.anyNeq(rhs, epsilon); }
    //
    //
    /**************************************
     *                                    *
     *         EQUALITY OPERATORS         *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec2<T>::allEq(const Vec2& rhs) const noexcept
    {
        const auto mask = _data == rhs._data;
        return static_cast<bool>(mask.horizontalAnd());
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec2<T>::allEq(const Vec2& lhs, const Vec2& rhs) noexcept
    { return lhs.allEq(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec2<T>::anyNeq(const Vec2& rhs) const noexcept
    {
        const auto mask = _data != rhs._data;
        return static_cast<bool>(mask.horizontalOr());
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec2<T>::anyNeq(const Vec2& lhs, const Vec2& rhs) noexcept
    { return lhs.anyNeq(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec2<T>::operator==(const Vec2& rhs) const noexcept
    { return allEq(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec2<T>::operator!=(const Vec2& rhs) const noexcept
    { return anyNeq(rhs); }


    /***************************************
     *           EQUALITY (MASK)           *
     ***************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::eq(const Vec2& rhs) const noexcept
    { return Vec2<Mask_t<T>>((_data == rhs._data).template cast<Mask_t<T>>()); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::eq(const Vec2& lhs, const Vec2& rhs) noexcept
    { return lhs.eq(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::neq(const Vec2& rhs) const noexcept
    { return Vec2<Mask_t<T>>((_data != rhs._data).template cast<Mask_t<T>>()); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::neq(const Vec2& lhs, const Vec2& rhs) noexcept
    { return lhs.neq(rhs); }



    /***************************************
     *            COMPARISONS              *
     ***************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<typename UInt<T>::type> Vec2<T>::gt(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec2<Mask_t<T>>((_data > rhs._data).template cast<Mask_t<T>>()); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::gt(const Vec2& lhs, const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.gt(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::gte(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec2<Mask_t<T>>((_data >= rhs._data).template cast<Mask_t<T>>()); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::gte(const Vec2& lhs, const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.gte(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::lt(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec2<Mask_t<T>>((_data < rhs._data).template cast<Mask_t<T>>()); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::lt(const Vec2& lhs, const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.lt(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::lte(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec2<Mask_t<T>>((_data <= rhs._data).template cast<Mask_t<T>>()); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::lte(const Vec2& lhs, const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.lte(rhs); }



    /***************************************
     *        COMPARISON OPERATORS         *
     ***************************************/

#ifdef ENABLE_FGM_SHADER_OPERATORS

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::operator>(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->gt(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::operator>=(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->gte(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::operator<(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->lt(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Mask_t<T>> Vec2<T>::operator<=(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->lte(rhs); }

#endif




    /***************************************
     *      BOOLEAN BITWISE OPERATORS      *
     ***************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::operator&(const Vec2& rhs) const noexcept
        requires std::is_same_v<T, bool>
    { return Vec2(_data & rhs._data); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T>& Vec2<T>::operator&=(const Vec2& rhs) noexcept
        requires std::is_same_v<T, bool>
    {
        *this = *this & rhs;
        return *this;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::operator|(const Vec2& rhs) const noexcept
        requires std::is_same_v<T, bool>
    { return Vec2(_data | rhs._data); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T>& Vec2<T>::operator|=(const Vec2& rhs) noexcept
        requires std::is_same_v<T, bool>
    {
        *this = *this & rhs;
        return *this;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::operator!() const noexcept
        requires std::is_same_v<T, bool>
    { return Vec2(~_data); }



    /*************************************
     *                                   *
     *      ARITHMETIC OPERATORS         *
     *                                   *
     *************************************/

    /*************************************
     *            ADDITION               *
     *************************************/

    template <Arithmetic T>
    constexpr Vec2<T> Vec2<T>::operator+(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec2(_data + rhs._data); }


    template <Arithmetic T>
    constexpr Vec2<T>& Vec2<T>::operator+=(const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    {
        *this = *this + rhs;
        return *this;
    }


    /*************************************
     *           SUBTRACTION             *
     *************************************/

    template <Arithmetic T>
    constexpr Vec2<T> Vec2<T>::operator-(const Vec2 rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec2(_data - rhs._data); }


    template <Arithmetic T>
    constexpr Vec2<T>& Vec2<T>::operator-=(const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    {
        *this = *this - rhs;
        return *this;
    }


    /**************************************
     *         INVERT OPERATION           *
     **************************************/

    template <Arithmetic T>
    constexpr Vec2<T> Vec2<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    { return Vec2(-_data); }


    /*************************************
     *           MULTIPLICATION          *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vec2<T> Vec2<T>::operator*(S scalar) const noexcept
        requires StrictArithmetic<T>
    { return Vec2(_data * falcon::Simd128_t<T, DIMENSION>(static_cast<T>(scalar))); }


    template <StrictArithmetic T, StrictArithmetic S>
    constexpr Vec2<T> operator*(S scalar, const Vec2<T>& vector) noexcept
        requires StrictArithmetic<T>
    { return vector * scalar; }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vec2<T>& Vec2<T>::operator*=(S scalar) noexcept
        requires StrictArithmetic<T>
    {
        *this = *this * scalar;
        return *this;
    }


    /*************************************
     *             DIVISION              *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vec2<T> Vec2<T>::operator/(S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            FALCON_ASSERT_MSG(fgm::abs(scalar) >= fgm::Config::EPSILON<T>, fgm::messages::assertion::VEC_DIV_BY_ZERO);
        }
        else
        {
            FALCON_ASSERT_MSG(scalar != 0, fgm::messages::assertion::VEC_DIV_BY_ZERO);
        }
        return Vec2(_data / static_cast<T>(scalar));
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vec2<T>& Vec2<T>::operator/=(S scalar) noexcept
        requires StrictArithmetic<T>
    {
        *this = *this / scalar;
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vec2<T> Vec2<T>::safeDiv(S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            if (hasNaN() | fgm::isnan(scalar) | (fgm::abs(scalar) <= std::numeric_limits<S>::epsilon()))
            {
                return Vec2<T>::zero();
            }
        }
        if constexpr (std::is_integral_v<T>)
        {
            if (scalar == 0)
            {
                return Vec2<T>::zero();
            }
        }

        return *this / scalar;
    }

    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vec2<T> Vec2<T>::safeDiv(const Vec2& vec, S scalar) noexcept
        requires StrictArithmetic<T>
    { return vec.safeDiv(scalar); }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vec2<T> Vec2<T>::tryDiv(S scalar, OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            if (hasNaN() | fgm::isnan(scalar))
            {
                status = OperationStatus::NANOPERAND;
                return Vec2<T>::zero();
            }
            if (fgm::abs(scalar) <= std::numeric_limits<S>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return Vec2<T>::zero();
            }
        }

        if constexpr (std::is_integral_v<T>)
        {
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return Vec2<T>::zero();
            }
        }

        status = OperationStatus::SUCCESS;
        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    constexpr Vec2<T> Vec2<T>::tryDiv(const Vec2& vec, S scalar, OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    { return vec.tryDiv(scalar, status); }


    //     /*************************************
    //      *                                   *
    //      *        VECTOR DOT PRODUCT         *
    //      *                                   *
    //      *************************************/
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedValue_t<T, U> Vec2<T>::dot(const Vec2& rhs) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    // #if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__FMA4__) || defined(__AVX2__)
    //         using R = PromotedValue_t<T, U>;
    //         if constexpr (std::is_floating_point_v<R>)
    //         {
    //             return std::fma(static_cast<R>(_data[0]), static_cast<R>(rhs[0]),
    //                             std::fma(static_cast<R>(_data[1]), static_cast<R>(rhs[1]), T(0)));
    //         }
    //         else
    //         {
    //             return _data[0] * rhs[0] + _data[1] * rhs[1];
    //         }
    // #else
    //         return _data[0] * rhs[0] + _data[1] * rhs[1];
    // #endif
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedValue_t<T, U> Vec2<T>::dot(const Vec2& lhs, const Vec2& rhs) noexcept
    //         requires StrictArithmetic<T>
    //     { return lhs.dot(rhs); }
    //
    //
    //
    //     /*************************************
    //      *                                   *
    //      *        VECTOR INNER PRODUCT       *
    //      *                                   *
    //      *************************************/
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedMat2<T, U> Vec2<T>::tensorProduct(const Vec2& rhs) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         using R = std::common_type_t<T, U>;
    //         return Mat2{ R(this->x() * rhs.x()), R(this->x() * rhs.y()), R(this->y() * rhs.x()), R(this->y() *
    //         rhs.y()) };
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedMat2<T, U> Vec2<T>::tensorProduct(const Vec2& lhs, const Vec2& rhs)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return lhs.tensorProduct(rhs); }
    //
    //
    //     /*************************************
    //      *                                   *
    //      *       VECTOR CROSS PRODUCT        *
    //      *                                   *
    //      *************************************/
    //
    //     template <Arithmetic T>
    //     template <SignedStrictArithmetic U>
    //     FALCON_INLINE constexpr PromotedValue_t<T, U> Vec2<T>::cross(const Vec2& rhs) const noexcept
    //         requires SignedStrictArithmetic<T>
    //     {
    //         using R = PromotedValue_t<T, U>;
    //         return R(_data[0] * rhs[1] - _data[1] * rhs[0]);
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <SignedStrictArithmetic U>
    //     FALCON_INLINE constexpr PromotedValue_t<T, U> Vec2<T>::cross(const Vec2& lhs, const Vec2& rhs) noexcept
    //         requires SignedStrictArithmetic<T>
    //     { return lhs.cross(rhs); }
    //
    //
    //     /*************************************
    //      *                                   *
    //      *         VECTOR MAGNITUDE          *
    //      *                                   *
    //      *************************************/
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr Magnitude<T> Vec2<T>::mag() const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         using M = Magnitude<T>;
    //
    //         M tX = static_cast<M>(_data[0]);
    //         M tY = static_cast<M>(_data[1]);
    //
    //         return sqrt(tX * tX + tY * tY);
    //     }
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr Magnitude<T> Vec2<T>::mag(const Vec2& vec) noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.mag(); }
    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr T Vec2<T>::magSq() const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         // return _data[0] * _data[0] + _data[1] * _data[1];
    //         return this->dot(*this);
    //     }
    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr T Vec2<T>::magSq(const Vec2& vec) noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.magSq(); }
    //
    //
    //     /**************************************
    //      *                                    *
    //      *           MANHATTAN NORM           *
    //      *                                    *
    //      **************************************/
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr T Vec2<T>::manhattanNorm() const noexcept
    //         requires StrictArithmetic<T>
    //     { return fgm::abs(_data[0]) + fgm::abs(_data[1]); }
    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr T Vec2<T>::manhattanNorm(const Vec2& vec) noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.manhattanNorm(); }
    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr T Vec2<T>::chebyshevNorm() const noexcept
    //         requires StrictArithmetic<T>
    //     { return std::max(fgm::abs(_data[0]), fgm::abs(_data[1])); }
    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr T Vec2<T>::chebyshevNorm(const Vec2& vec) noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.chebyshevNorm(); }
    //
    //
    //     /**************************************
    //      *                                    *
    //      *         VECTOR DISTANCE            *
    //      *                                    *
    //      **************************************/
    //
    //     /**************************************
    //      *                                    *
    //      *             EUCLIDEAN              *
    //      *                                    *
    //      **************************************/
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr Magnitude<PromotedValue_t<T, U>> Vec2<T>::dist(const Vec2& rhs) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         using R       = Magnitude<PromotedValue_t<T, U>>;
    //         const auto dx = utils::diffAbs(_data[0], rhs[0]);
    //         const auto dy = utils::diffAbs(_data[1], rhs[1]);
    //         return static_cast<R>(std::sqrt(dx * dx + dy * dy));
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr Magnitude<PromotedValue_t<T, U>> Vec2<T>::dist(const Vec2<U>& lhs, const Vec2<U>&
    //     rhs) noexcept
    //         requires StrictArithmetic<T>
    //     { return lhs.dist(rhs); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedValue_t<T, U> Vec2<T>::distSq(const Vec2& rhs) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         const auto dx = utils::diffAbs(_data[0], rhs[0]);
    //         const auto dy = utils::diffAbs(_data[1], rhs[1]);
    //
    //         return dx * dx + dy * dy;
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedValue_t<T, U> Vec2<T>::distSq(const Vec2<U>& lhs, const Vec2& rhs)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return lhs.distSq(rhs); }
    //
    //
    //
    //     /**************************************
    //      *                                    *
    //      *             MANHATTAN              *
    //      *                                    *
    //      **************************************/
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedValue_t<T, U> Vec2<T>::manhattanDist(const Vec2& rhs) const noexcept
    //         requires StrictArithmetic<T>
    //     { return utils::diffAbs(_data[0], rhs[0]) + utils::diffAbs(_data[1], rhs[1]); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedValue_t<T, U> Vec2<T>::manhattanDist(const Vec2<U>& lhs, const Vec2& rhs)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return lhs.manhattanDist(rhs); }
    //
    //
    //
    //     /**************************************
    //      *                                    *
    //      *             CHEBYSHEV              *
    //      *                                    *
    //      **************************************/
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedValue_t<T, U> Vec2<T>::chebyshevDist(const Vec2& rhs) const noexcept
    //         requires StrictArithmetic<T>
    //     { return std::max(utils::diffAbs(_data[0], rhs[0]), utils::diffAbs(_data[1], rhs[1])); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedValue_t<T, U> Vec2<T>::chebyshevDist(const Vec2<U>& lhs, const Vec2& rhs)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return lhs.chebyshevDist(rhs); }
    //
    //
    //
    //     /*************************************
    //      *                                   *
    //      *       VECTOR NORMALIZATION        *
    //      *                                   *
    //      *************************************/
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr Vec2<Magnitude<T>> Vec2<T>::normalize() const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         const auto magnitude = mag();
    //         FALCON_ASSERT_MSG(magnitude >= fgm::Config::EPSILON<decltype(magnitude)>,
    //                        fgm::messages::assertion::VEC_NORMALIZE_DIV_BY_ZERO);
    //         return *this / magnitude;
    //     }
    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr Vec2<Magnitude<T>> Vec2<T>::normalize(const Vec2& vec) noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.normalize(); }
    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr Vec2<Magnitude<T>> Vec2<T>::safeNormalize() const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         using R     = Magnitude<T>;
    //         R magnitude = mag();
    //         if (fgm::isnan(magnitude))
    //         {
    //             return Vec2<R>::zero();
    //         }
    //         if (magnitude <= Config::EPSILON_SQUARE<R>)
    //         {
    //             return Vec2<R>::zero();
    //         }
    //
    //         return *this / magnitude;
    //     }
    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr Vec2<Magnitude<T>> Vec2<T>::safeNormalize(const Vec2& vec) noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.safeNormalize(); }
    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr Vec2<Magnitude<T>> Vec2<T>::tryNormalize(OperationStatus& status) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         using R     = Magnitude<T>;
    //         R magnitude = mag();
    //         if (fgm::isnan(magnitude))
    //         {
    //             status = OperationStatus::NANOPERAND;
    //             return Vec2<R>::zero();
    //         }
    //         if (magnitude <= Config::EPSILON_SQUARE<R>)
    //         {
    //             status = OperationStatus::DIVISIONBYZERO;
    //             return Vec2<R>::zero();
    //         }
    //
    //         status = OperationStatus::SUCCESS;
    //         return *this / magnitude;
    //     }
    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr Vec2<Magnitude<T>> Vec2<T>::tryNormalize(const Vec2& vec, OperationStatus& status)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.tryNormalize(status); }
    //
    //
    //     /*************************************
    //      *                                   *
    //      *        VECTOR PROJECTION          *
    //      *                                   *
    //      *************************************/
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedFloatVec2<T, U> Vec2<T>::project(const Vec2<U>& onto) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         using R = PromotedValue_t<T, U>;
    //         /** @note Static cast ensures integral type dots don't lose much precision */
    //         const auto b2 = static_cast<Magnitude<R>>(onto.dot(onto));
    //
    //         FALCON_ASSERT_MSG(b2 >= fgm::Config::EPSILON_SQUARE<Magnitude<R>>,
    //                        fgm::messages::assertion::VEC_PROJECT_DIV_BY_ZERO);
    //
    //         return this->dot(onto) / b2 * onto; // a.dot(b) / b.dot(b) * b
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedVec2<T, U> Vec2<T>::projectNorm(const Vec2<U>& onto) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         return this->dot(onto) * onto; // a.dot(b) * b
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedFloatVec2<T, U> Vec2<T>::project(const Vec2& vec, const Vec2<U>& onto)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.project(onto); }
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedVec2<T, U> Vec2<T>::projectNorm(const Vec2& vec, const Vec2<U>& onto)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.projectNorm(onto); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedFloatVec2<T, U> Vec2<T>::safeProject(const Vec2<U>& onto) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         using R       = PromotedValue_t<T, U>;
    //         using MagType = Magnitude<R>;
    //
    //         /** @note Static cast ensures integral type dots don't lose much precision */
    //         const auto ontoSquared = static_cast<MagType>(onto.dot(onto));
    //
    //         if (hasNaN() | fgm::isnan(ontoSquared))
    //         {
    //             return Vec2<MagType>::zero();
    //         }
    //
    //         if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
    //         {
    //             return Vec2<MagType>::zero();
    //         }
    //
    //         return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedVec2<T, U> Vec2<T>::safeProjectNorm(const Vec2<U>& onto) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         using R = PromotedValue_t<T, U>;
    //
    //         if (hasNaN() || onto.hasNaN())
    //         {
    //             return Vec2<R>::zero();
    //         }
    //
    //         return this->dot(onto) * onto;
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedFloatVec2<T, U> Vec2<T>::safeProject(const Vec2& vec, const Vec2<U>& onto)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.safeProject(onto); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedVec2<T, U> Vec2<T>::safeProjectNorm(const Vec2& vec, const Vec2<U>& onto)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.safeProjectNorm(onto); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedFloatVec2<T, U> Vec2<T>::tryProject(const Vec2<U>& onto,
    //                                                                      OperationStatus& status) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         using R       = PromotedValue_t<T, U>;
    //         using MagType = Magnitude<R>;
    //
    //         /** @note Static cast ensures integral type dots don't lose too much precision. */
    //         const auto ontoSquared = static_cast<MagType>(onto.dot(onto));
    //
    //         if (hasNaN() | fgm::isnan(ontoSquared))
    //         {
    //             status = OperationStatus::NANOPERAND;
    //             return Vec2<MagType>::zero();
    //         }
    //
    //         if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
    //         {
    //             status = OperationStatus::DIVISIONBYZERO;
    //             return Vec2<MagType>::zero();
    //         }
    //
    //         status = OperationStatus::SUCCESS;
    //         return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedVec2<T, U> Vec2<T>::tryProjectNorm(const Vec2<U>& onto,
    //                                                                     OperationStatus& status) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         using R       = PromotedValue_t<T, U>;
    //         using MagType = Magnitude<R>;
    //
    //         if (hasNaN() || onto.hasNaN())
    //         {
    //             status = OperationStatus::NANOPERAND;
    //             return Vec2<MagType>::zero();
    //         }
    //
    //         status = OperationStatus::SUCCESS;
    //         return this->dot(onto) * onto;
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedFloatVec2<T, U> Vec2<T>::tryProject(const Vec2& vec, const Vec2<U>& onto,
    //                                                                      OperationStatus& status) noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.tryProject(onto, status); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedVec2<T, U> Vec2<T>::tryProjectNorm(const Vec2& vec, const Vec2<U>& onto,
    //                                                                     OperationStatus& status) noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.tryProjectNorm(onto, status); }
    //
    //
    //     /*************************************
    //      *                                   *
    //      *         VECTOR REJECTION          *
    //      *                                   *
    //      *************************************/
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedFloatVec2<T, U> Vec2<T>::reject(const Vec2<U>& from) const noexcept
    //         requires StrictArithmetic<T>
    //     { return static_cast<PromotedFloatVec2<T, U>>(*this) - this->project(from); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedVec2<T, U> Vec2<T>::rejectNorm(const Vec2<U>& from) const noexcept
    //         requires StrictArithmetic<T>
    //     { return *this - this->projectNorm(from); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedFloatVec2<T, U> Vec2<T>::reject(const Vec2& vec, const Vec2<U>& from)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.reject(from); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedVec2<T, U> Vec2<T>::rejectNorm(const Vec2& vector, const Vec2<U>& from)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return vector.rejectNorm(from); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedFloatVec2<T, U> Vec2<T>::safeReject(const Vec2<U>& from) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         if (hasNaN() || from.hasNaN())
    //         {
    //             return Vec2<Magnitude<PromotedValue_t<T, U>>>::zero();
    //         }
    //
    //         return static_cast<PromotedFloatVec2<T, U>>(*this) - safeProject(from);
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedVec2<T, U> Vec2<T>::safeRejectNorm(const Vec2<U>& from) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         if (hasNaN() || from.hasNaN())
    //         {
    //             return Vec2<PromotedValue_t<T, U>>::zero();
    //         }
    //
    //         return *this - safeProjectNorm(from);
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedFloatVec2<T, U> Vec2<T>::safeReject(const Vec2& vec, const Vec2<U>& from)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.safeReject(from); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedVec2<T, U> Vec2<T>::safeRejectNorm(const Vec2& vec, const Vec2<U>& from)
    //     noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.safeRejectNorm(from); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedFloatVec2<T, U> Vec2<T>::tryReject(const Vec2<U>& from,
    //                                                                     OperationStatus& status) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         if (hasNaN() || from.hasNaN())
    //         {
    //             status = OperationStatus::NANOPERAND;
    //             return Vec2<Magnitude<PromotedValue_t<T, U>>>::zero();
    //         }
    //
    //         return static_cast<PromotedFloatVec2<T, U>>(*this) - this->tryProject(from, status);
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedVec2<T, U> Vec2<T>::tryRejectNorm(const Vec2<U>& from,
    //                                                                    OperationStatus& status) const noexcept
    //         requires StrictArithmetic<T>
    //     {
    //         if (hasNaN() || from.hasNaN())
    //         {
    //             status = OperationStatus::NANOPERAND;
    //             return Vec2<PromotedValue_t<T, U>>::zero();
    //         }
    //
    //         return *this - this->tryProjectNorm(from, status);
    //     }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedFloatVec2<T, U> Vec2<T>::tryReject(const Vec2& vec, const Vec2<U>& from,
    //                                                                     OperationStatus& status) noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.tryReject(from, status); }
    //
    //
    //     template <Arithmetic T>
    //     template <StrictArithmetic U>
    //         requires StrictSignedness<T, U>
    //     FALCON_INLINE constexpr PromotedVec2<T, U> Vec2<T>::tryRejectNorm(const Vec2& vec, const Vec2<U>& from,
    //                                                                    OperationStatus& status) noexcept
    //         requires StrictArithmetic<T>
    //     { return vec.tryRejectNorm(from, status); }
    //
    //
    //     /**************************************
    //      *                                    *
    //      *             UTILITIES              *
    //      *                                    *
    //      **************************************/
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr bool Vec2<T>::hasInf() const noexcept
    //     {
    //         if constexpr (std::is_floating_point_v<T>)
    //         {
    //             return fgm::isinf(_data[0]) | fgm::isinf(_data[1]);
    //         }
    //         else
    //         {
    //             return false;
    //         }
    //     }
    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr bool Vec2<T>::hasInf(const Vec2& vec) noexcept
    //     { return vec.hasInf(); }
    //
    //
    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec2<T>::hasNaN() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            // Since nan is not equal to anything we need to query for nan
            // and use that property to convert from -nan(returned if an entry is nan) to a boolean.
            T isNan = _data.hasNan().horizontalOr();
            return isNan != isNan;
        }
        else
        {
            return false;
        }
    }

    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec2<T>::hasNaN(const Vec2& vec) noexcept
    { return vec.hasNaN(); }
} // namespace fgm

#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
