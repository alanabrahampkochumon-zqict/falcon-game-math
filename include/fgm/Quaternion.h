#pragma once
/**
 * @file Quaternion.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 01, 2026
 *
 * @brief Templated Quaternion supporting integral, floating-point, and boolean types.
 *
 * @details Provides high-performance 4D quaternion implementation with SIMD acceleration
 *          and support for component-wise operations. ::TODO::
 *
 * @tparam T Type of @ref Quaternion components. Must satisfy @ref Arithmetic.
 *
 * @note Arithmetic operations are restricted to numeric types via @ref StrictArithmetic.
 *
 * @par Configuration ::TODO::Update
 * - Define `ENABLE_FGM_SHADER_OPERATORS` to enable comparison operators (`,`, `<`, etc.).
 *   Even if disabled, functional comparisons like @ref gt remain available.
 * - Define `FORCE_SCALAR` to disable SIMD optimizations (enabled by default on supported hardware).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "common/MathTraits.h"
#include "common/PreprocessorDefinitions.h"
#include "vectors/Vec3.h"

#include <array>


namespace fgm
{

    /**
     * @brief Quaternion data structure.
     *
     * @note While a quaternion can be initialized in any order <vector, scalar> or <scalar, vector>,
     *       it strictly follows the <vector, scalar> or <x, y, z, w> order internally.
     *
     * @tparam T The numeric type of the real and complex components. Must satisfy @ref Arithmetic.
     *
     */
    template <Arithmetic T>
    struct Quaternion
    {


        /**
         * @addtogroup FGM_Quaternion_Init
         * @{
         */

        /**
         * @brief Initialize an uninitialized @ref Quaternion instance.
         *
         * @warning The components are left uninitialized (containing garbage data)
         *          to maximize SIMD optimization and maintain triviality.
         *
         * @note Use value-initialization (`{}`) to guarantee a zeroed quaternion.
         */
        Quaternion() = default;


        /**
         * @brief Initialize @ref Quaternion with passed-in values.
         *
         * @param[in] x The first vector component.
         * @param[in] y The second vector component.
         * @param[in] z The third vector component.
         * @param[in] w The scalar component.
         */
        [[nodiscard]] constexpr Quaternion(T x, T y, T z, T w) noexcept;


        /**
         * @brief Initialize @ref Quaternion with a complex and real component.
         *
         * @param[in] complex The complex/vector component.
         * @param[in] real The real/scalar component.
         */
        [[nodiscard]] constexpr Quaternion(const Vec3<T>& complex, T real) noexcept;


        /**
         * @brief Initialize @ref Quaternion with a real and complex component.
         *
         * @param[in] complex The complex/vector component.
         * @param[in] real The real/scalar component.
         */
        [[nodiscard]] constexpr Quaternion(T real, const Vec3<T>& complex) noexcept;

        /** @} */



        /**
         * @addtogroup FGM_Quaternion_Access
         * @{
         */

        /**
         * @brief Get the first vector component.
         */
        [[nodiscard]] constexpr T x() const noexcept;


        /**
         * @brief Get a reference to the first vector component.
         */
        [[nodiscard]] constexpr T& x() noexcept;


        /**
         * @brief Get the second vector component.
         */
        [[nodiscard]] constexpr T y() const noexcept;


        /**
         * @brief Get a reference to the second vector component.
         */
        [[nodiscard]] constexpr T& y() noexcept;


        /**
         * @brief Get the third vector component.
         */
        [[nodiscard]] constexpr T z() const noexcept;


        /**
         * @brief Get a reference to the third vector component.
         */
        [[nodiscard]] constexpr T& z() noexcept;


        /**
         * @brief Get the scalar component (last component).
         */
        [[nodiscard]] constexpr T w() const noexcept;


        /**
         * @brief Get a reference to the scalar component (last component).
         */
        [[nodiscard]] constexpr T& w() noexcept;


        /**
         * @brief Get the first vector component.
         */
        [[nodiscard]] constexpr T i() const noexcept;


        /**
         * @brief Get a reference to the first vector component.
         */
        [[nodiscard]] constexpr T& i() noexcept;


        /**
         * @brief Get the second vector component.
         */
        [[nodiscard]] constexpr T j() const noexcept;


        /**
         * @brief Get a reference to the second vector component.
         */
        [[nodiscard]] constexpr T& j() noexcept;


        /**
         * @brief Get the third vector component.
         */
        [[nodiscard]] constexpr T k() const noexcept;


        /**
         * @brief Get a reference to the third vector component.
         */
        [[nodiscard]] constexpr T& k() noexcept;


        /**
         * @brief Get the scalar component (last component).
         */
        [[nodiscard]] constexpr T s() const noexcept;


        /**
         * @brief Get a reference to the scalar component (last component).
         */
        [[nodiscard]] constexpr T& s() noexcept;

        /** @} */

    private:
        std::array<T, 4> _data;
    };


    /** @brief Template deduction guide for Quaternion. */
    template <typename T>
        requires Arithmetic<T>
    Quaternion(T, T, T, T) -> Quaternion<T>;

    template <typename T>
        requires Arithmetic<T>
    Quaternion(Vec3<T>, T) -> Quaternion<T>;

} // namespace fgm



#include "Quaternion.tpp"
