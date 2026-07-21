#pragma once
/**
 * @file Types.h
 * @author Alan Abraham P Kochumon
 * @date Created on: May 14, 2026
 *
 * @brief Type alias for common types.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "MathTraits.h"



/**
 * @addtogroup FGM_Types
 * @{
 */


/**************************************
 *                                    *
 *       PROMOTED TYPE ALIAS          *
 *                                    *
 **************************************/

namespace fgm
{

    // Forward declarations

    template <Arithmetic T>
    struct Vec2;

    template <Arithmetic T>
    struct Vec3;

    template <Arithmetic T>
    struct Vec4;

    template <Arithmetic T>
    struct Mat2;

    template <Arithmetic T>
    struct Mat2x3;

    template <Arithmetic T>
    struct Mat2x4;

    template <Arithmetic T>
    struct Mat3;

    template <Arithmetic T>
    struct Mat3x2;

    template <Arithmetic T>
    struct Mat3x4;

    template <Arithmetic T>
    struct Mat4x2;

    template <Arithmetic T>
    struct Mat4;


    /** @brief Alias for @ref Vec2 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedVec2 = Vec2<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Vec2 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedFloatVec2 = Vec2<Magnitude<PromotedValue_t<T, U>>>;


    /** @brief Alias for @ref Vec3 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedVec3 = Vec3<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Vec3 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedFloatVec3 = Vec3<Magnitude<PromotedValue_t<T, U>>>;


    /** @brief Alias for @ref Vec4 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedVec4 = Vec4<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Vec4 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedFloatVec4 = Vec4<Magnitude<PromotedValue_t<T, U>>>;


    /** @brief Alias for @ref Mat2 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedMat2 = Mat2<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Mat2 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
    using PromotedFloatMat2 = Mat2<Magnitude<std::common_type_t<T, U>>>;

    /** @brief Alias for @ref Mat2x3 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedMat2x3 = Mat2x3<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Mat2x3 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
    using PromotedFloatMat2x3 = Mat2x3<Magnitude<std::common_type_t<T, U>>>;


    /** @brief Alias for @ref Mat2x4 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedMat2x4 = Mat2x4<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Mat2x4 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
    using PromotedFloatMat2x4 = Mat2x4<Magnitude<std::common_type_t<T, U>>>;


    /** @brief Alias for @ref Mat3 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedMat3 = Mat3<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Mat3 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
    using PromotedFloatMat3 = Mat3<Magnitude<std::common_type_t<T, U>>>;


    /** @brief Alias for @ref Mat3x2 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedMat3x2 = Mat3x2<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Mat3x2 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
    using PromotedFloatMat3x2 = Mat3x2<Magnitude<std::common_type_t<T, U>>>;


    /** @brief Alias for @ref Mat3x4 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedMat3x4 = Mat3x4<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Mat3x4 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
    using PromotedFloatMat3x4 = Mat3x4<Magnitude<std::common_type_t<T, U>>>;


    /** @brief Alias for @ref Mat4x2 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedMat4x2 = Mat4x2<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Mat4x2 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
    using PromotedFloatMat4x2 = Mat4x2<Magnitude<std::common_type_t<T, U>>>;


    /** @brief Alias for @ref Mat4 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedMat4 = Mat4<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Mat4 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
    using PromotedFloatMat4 = Mat4<Magnitude<std::common_type_t<T, U>>>;
} // namespace fgm

/** @} */
