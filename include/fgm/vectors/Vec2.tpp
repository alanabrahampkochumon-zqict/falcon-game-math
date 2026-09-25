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


    template <Arithmetic T>
    template <size_t Index>
    FALCON_INLINE constexpr T Vec2<T>::get() const noexcept
    {
        static_assert(Index < DIMENSION && "[Vec2]: Out of bounds access");
        return _data.template getAt<Index>();
    }


    template <Arithmetic T>
    template <size_t Index>
    FALCON_INLINE constexpr T Vec2<T>::get() noexcept
    {
        static_assert(Index < DIMENSION && "[Vec2]: Out of bounds access");
        return _data.template getAt<Index>();
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
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::operator+(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec2(_data + rhs._data); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T>& Vec2<T>::operator+=(const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    {
        *this = *this + rhs;
        return *this;
    }


    /*************************************
     *           SUBTRACTION             *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::operator-(const Vec2 rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec2(_data - rhs._data); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T>& Vec2<T>::operator-=(const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    {
        *this = *this - rhs;
        return *this;
    }


    /**************************************
     *         INVERT OPERATION           *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    { return Vec2(-_data); }


    /*************************************
     *           MULTIPLICATION          *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::operator*(S scalar) const noexcept
        requires StrictArithmetic<T>
    { return Vec2(_data * falcon::Simd128_t<T, DIMENSION>(static_cast<T>(scalar))); }


    template <StrictArithmetic T, StrictArithmetic S>
    FALCON_INLINE constexpr Vec2<T> operator*(S scalar, const Vec2<T>& vector) noexcept
        requires StrictArithmetic<T>
    { return vector * scalar; }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Vec2<T>& Vec2<T>::operator*=(S scalar) noexcept
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
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::operator/(S scalar) const noexcept
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
    FALCON_INLINE constexpr Vec2<T>& Vec2<T>::operator/=(S scalar) noexcept
        requires StrictArithmetic<T>
    {
        *this = *this / scalar;
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::safeDiv(S scalar) const noexcept
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
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::safeDiv(const Vec2& vec, S scalar) noexcept
        requires StrictArithmetic<T>
    { return vec.safeDiv(scalar); }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::tryDiv(S scalar, OperationStatus& status) const noexcept
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
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::tryDiv(const Vec2& vec, S scalar, OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    { return vec.tryDiv(scalar, status); }



    /*************************************
     *        VECTOR DOT PRODUCT         *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::dot([[maybe_unused]] const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        const auto product = _data * rhs._data;
        return product.horizontalAdd();
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::dot(const Vec2& lhs, const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.dot(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::cross(const Vec2& rhs) const noexcept
        requires SignedStrictArithmetic<T>
    {
        // Ax*By - Ay*Bx
        const auto shuffled = rhs._data.template shuffle<1, 0>(); // [By, Bx]
        const auto product  = _data * shuffled;                   // [Ax*By, Ay*Bx]
        return product.horizontalSub();                           // Ax*By - Ay*Bx
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::cross(const Vec2& lhs, const Vec2& rhs) noexcept
        requires SignedStrictArithmetic<T>
    { return lhs.cross(rhs); }



    /**************************************
     *           EUCLIDEAN NORM           *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::mag() const noexcept
        requires StrictArithmetic<T>
    { return static_cast<T>(std::sqrt(magSq())); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::mag(const Vec2& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.mag(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::magSq() const noexcept
        requires StrictArithmetic<T>
    {
        const auto squaredVec = _data * _data;
        return squaredVec.horizontalAdd();
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::magSq(const Vec2& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.magSq(); }


    /**************************************
     *           MANHATTAN NORM           *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::manhattanNorm() const noexcept
        requires StrictArithmetic<T>
    {
        const auto abs = _data.abs();
        return abs.horizontalAdd();
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::manhattanNorm(const Vec2& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.manhattanNorm(); }



    /**************************************
     *           MANHATTAN NORM           *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::chebyshevNorm() const noexcept
        requires StrictArithmetic<T>
    {
        const auto abs = _data.abs();
        return abs.horizontalMax();
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::chebyshevNorm(const Vec2& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.chebyshevNorm(); }



    /**************************************
     *         VECTOR DISTANCE            *
     **************************************/

    /**************************************
     *             EUCLIDEAN              *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::dist(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        // sqrt((x2 - x1)^2 + (y2 - y1)^2)
        return static_cast<T>(std::sqrt(distSq(rhs)));
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::dist(const Vec2& lhs, const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.dist(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::distSq(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        // (x2 - x1)^2 + (y2 - y1)^2
        const auto diff        = rhs._data - _data;
        const auto squaredDiff = diff * diff;
        return squaredDiff.horizontalAdd();
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::distSq(const Vec2& lhs, const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.distSq(rhs); }


    /**************************************
     *             MANHATTAN              *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::manhattanDist(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        // For unsigned integrals taking difference and then abs will cause wrap around
        // when the difference is negative.
        // To circumvent this, we can take both differences and selectively take
        // whichever is greater.
        if constexpr (std::is_signed_v<T>)
        {
            const auto diff = rhs._data - _data;
            const auto abs  = diff.abs();
            return abs.horizontalAdd();
        }
        else
        {
            // For unsigned number we need to manually do diff abs a mask and selection
            // a > b ? a - b : b - a
            const auto diff1 = rhs._data - _data; // b - a
            const auto diff2 = _data - rhs._data; // a - b
            const auto mask  = _data > rhs._data; // a > b
            const auto abs   = diff1.blend(diff2, mask);
            return abs.horizontalAdd();
        }
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::manhattanDist(const Vec2& lhs, const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.manhattanDist(rhs); }



    /**************************************
     *             CHEBYSHEV              *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::chebyshevDist(const Vec2& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        // For unsigned integrals taking difference and then abs will cause wrap around
        // when the difference is negative.
        // To circumvent this, we can take both differences and selectively take
        // whichever is greater.
        if constexpr (std::is_signed_v<T>)
        {
            const auto diff = rhs._data - _data;
            const auto abs  = diff.abs();
            return abs.horizontalMax();
        }
        else
        {
            // For unsigned number we need to manually do diff abs a mask and selection
            // a > b ? a - b : b - a
            const auto diff1 = rhs._data - _data; // b - a
            const auto diff2 = _data - rhs._data; // a - b
            const auto mask  = _data > rhs._data; // a > b
            const auto abs   = diff1.blend(diff2, mask);
            return abs.horizontalMax();
        }
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec2<T>::chebyshevDist(const Vec2& lhs, const Vec2& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.chebyshevDist(rhs); }


    // TODO: Add vec2 inner product after adding Mat2
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

    /*************************************
     *                                   *
     *       VECTOR NORMALIZATION        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Magnitude<T>> Vec2<T>::normalize() const noexcept
        requires FPArithmetic<T>
    {
        const auto magnitude = mag();
        FALCON_ASSERT_MSG(magnitude >= fgm::Config::EPSILON<decltype(magnitude)>,
                          fgm::messages::assertion::VEC_NORMALIZE_DIV_BY_ZERO);
        return *this / magnitude;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Magnitude<T>> Vec2<T>::normalize(const Vec2& vec) noexcept
        requires FPArithmetic<T>
    { return vec.normalize(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Magnitude<T>> Vec2<T>::safeNormalize() const noexcept
        requires FPArithmetic<T>
    {
        T magnitude = mag();
        if (fgm::isnan(magnitude))
        {
            return Vec2<T>::zero();
        }
        if (magnitude <= Config::EPSILON_SQUARE<T>)
        {
            return Vec2<T>::zero();
        }

        return *this / magnitude;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Magnitude<T>> Vec2<T>::safeNormalize(const Vec2& vec) noexcept
        requires FPArithmetic<T>
    { return vec.safeNormalize(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Magnitude<T>> Vec2<T>::tryNormalize(OperationStatus& status) const noexcept
        requires FPArithmetic<T>
    {
        T magnitude = mag();
        if (fgm::isnan(magnitude))
        {
            status = OperationStatus::NANOPERAND;
            return Vec2<T>::zero();
        }
        if (magnitude <= Config::EPSILON_SQUARE<T>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return Vec2<T>::zero();
        }

        status = OperationStatus::SUCCESS;
        return *this / magnitude;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<Magnitude<T>> Vec2<T>::tryNormalize(const Vec2& vec, OperationStatus& status) noexcept
        requires FPArithmetic<T>
    { return vec.tryNormalize(status); }



    /*************************************
     *        VECTOR PROJECTION          *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::project(const Vec2& onto) const noexcept
        requires FPArithmetic<T>
    {
        const auto b2 = onto.dot(onto);
        FALCON_ASSERT_MSG(b2 > fgm::Config::EPSILON_SQUARE<T>, fgm::messages::assertion::VEC_PROJECT_DIV_BY_ZERO);

        return this->dot(onto) / b2 * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::projectNorm(const Vec2& onto) const noexcept
        requires FPArithmetic<T>
    {
        return dot(onto) * onto; // A.B * A
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::project(const Vec2& vec, const Vec2& onto) noexcept
        requires FPArithmetic<T>
    { return vec.project(onto); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::projectNorm(const Vec2& vec, const Vec2& onto) noexcept
        requires FPArithmetic<T>
    { return vec.projectNorm(onto); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::safeProject(const Vec2& onto) const noexcept
        requires FPArithmetic<T>
    {
        const auto ontoSquared = onto.dot(onto);
        if (hasNaN() || fgm::isnan(ontoSquared) || ontoSquared <= Config::EPSILON_SQUARE<T>)
        {
            return Vec2<T>::zero();
        }
        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::safeProjectNorm(const Vec2& onto) const noexcept
        requires FPArithmetic<T>
    {

        if (hasNaN() || onto.hasNaN())
        {
            return Vec2<T>::zero();
        }

        return this->dot(onto) * onto;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::safeProject(const Vec2& vec, const Vec2& onto) noexcept
        requires FPArithmetic<T>
    { return vec.safeProject(onto); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::safeProjectNorm(const Vec2& vec, const Vec2& onto) noexcept
        requires FPArithmetic<T>
    { return vec.safeProjectNorm(onto); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::tryProject(const Vec2& onto, OperationStatus& status) const noexcept
        requires FPArithmetic<T>
    {
        const auto ontoSquared = onto.dot(onto);
        if (hasNaN() || fgm::isnan(ontoSquared))
        {
            status = OperationStatus::NANOPERAND;
            return Vec2<T>::zero();
        }
        if (ontoSquared <= Config::EPSILON_SQUARE<T>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return Vec2<T>::zero();
        }

        status = OperationStatus::SUCCESS;
        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::tryProjectNorm(const Vec2& onto, OperationStatus& status) const noexcept
        requires FPArithmetic<T>
    {
        if (hasNaN() || onto.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return Vec2<T>::zero();
        }
        status = OperationStatus::SUCCESS;
        return this->dot(onto) * onto;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::tryProject(const Vec2& vec, const Vec2& onto,
                                                        OperationStatus& status) noexcept
        requires FPArithmetic<T>
    { return vec.tryProject(onto, status); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::tryProjectNorm(const Vec2& vec, const Vec2& onto,
                                                            OperationStatus& status) noexcept
        requires FPArithmetic<T>
    { return vec.tryProjectNorm(onto, status); }



    /*************************************
     *         VECTOR REJECTION          *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::reject(const Vec2& from) const noexcept
        requires FPArithmetic<T>
    { return *this - this->project(from); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::rejectNorm(const Vec2& from) const noexcept
        requires FPArithmetic<T>
    { return *this - this->projectNorm(from); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::reject(const Vec2& vec, const Vec2& from) noexcept
        requires FPArithmetic<T>
    { return vec.reject(from); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::rejectNorm(const Vec2& vec, const Vec2& from) noexcept
        requires FPArithmetic<T>
    { return vec.rejectNorm(from); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::safeReject(const Vec2& from) const noexcept
        requires FPArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            return Vec2<T>::zero();
        }

        return *this - this->safeProject(from);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::safeRejectNorm(const Vec2& from) const noexcept
        requires FPArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            return Vec2<T>::zero();
        }

        return *this - this->safeProjectNorm(from);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::safeReject(const Vec2& vec, const Vec2& from) noexcept
        requires FPArithmetic<T>
    { return vec.safeReject(from); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::safeRejectNorm(const Vec2& vec, const Vec2& from) noexcept
        requires FPArithmetic<T>
    { return vec.safeRejectNorm(from); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::tryReject(const Vec2& from, OperationStatus& status) const noexcept
        requires FPArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return Vec2<T>::zero();
        }

        return *this - this->tryProject(from, status);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::tryRejectNorm(const Vec2& from, OperationStatus& status) const noexcept
        requires FPArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return Vec2<T>::zero();
        }

        return *this - this->tryProjectNorm(from, status);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::tryReject(const Vec2& vec, const Vec2& from,
                                                       OperationStatus& status) noexcept
        requires FPArithmetic<T>
    { return vec.tryReject(from, status); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> Vec2<T>::tryRejectNorm(const Vec2& vec, const Vec2& from,
                                                           OperationStatus& status) noexcept
        requires FPArithmetic<T>
    { return vec.tryRejectNorm(from, status); }


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
