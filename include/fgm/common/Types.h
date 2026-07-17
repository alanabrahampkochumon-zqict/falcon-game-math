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
    struct Vector2;

    template <Arithmetic T>
    struct Vector3;

    template <Arithmetic T>
    struct Vector4;

    template <Arithmetic T>
    struct Matrix2;

    template <Arithmetic T>
    struct Mat2x3;

    template <Arithmetic T>
    struct Matrix3;

    template <Arithmetic T>
    struct Matrix4;


    /** @brief Alias for @ref Vector2 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedVector2 = Vector2<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Vector2 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedFloatVector2 = Vector2<Magnitude<PromotedValue_t<T, U>>>;


    /** @brief Alias for @ref Vector3 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedVector3 = Vector3<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Vector3 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedFloatVector3 = Vector3<Magnitude<PromotedValue_t<T, U>>>;


    /** @brief Alias for @ref Vector4 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedVector4 = Vector4<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Vector4 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedFloatVector4 = Vector4<Magnitude<PromotedValue_t<T, U>>>;


    /** @brief Alias for @ref Matrix2 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedMatrix2 = Matrix2<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Matrix2 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
    using PromotedFloatMatrix2 = Matrix2<Magnitude<std::common_type_t<T, U>>>;

    /** @brief Alias for @ref Matrix2x3 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedMat2x3 = Mat2x3<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Matrix2x3 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
    using PromotedFloatMatrix2x3 = Mat2x3<Magnitude<std::common_type_t<T, U>>>;


    /** @brief Alias for @ref Matrix3 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedMatrix3 = Matrix3<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Matrix3 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
    using PromotedFloatMatrix3 = Matrix3<Magnitude<std::common_type_t<T, U>>>;


    /** @brief Alias for @ref Matrix4 with promoted value type. */
    template <Arithmetic T, Arithmetic U>
        requires Arithmetic<PromotedValue_t<T, U>>
    using PromotedMatrix4 = Matrix4<PromotedValue_t<T, U>>;


    /** @brief Alias for @ref Matrix4 with a `value_type` of @ref Magnitude of the wider type. */
    template <Arithmetic T, Arithmetic U>
    using PromotedFloatMatrix4 = Matrix4<Magnitude<std::common_type_t<T, U>>>;
} // namespace fgm

/** @} */
