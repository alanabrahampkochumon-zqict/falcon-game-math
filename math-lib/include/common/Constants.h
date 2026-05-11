#pragma once
/**
 * @file Constants.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 21, 2026
 *
 * @brief Constant definitions of FGM.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <concepts>
#include <limits>
#include <numbers>


/**
 * @addtogroup FGM_Math_Constants
 * @{
 */
namespace fgm::constants
{

    /** @brief Positive infinity for single-precision floats. */
    inline constexpr float INFINITY_F = std::numeric_limits<float>::infinity();

    /** @brief Positive infinity for double-precision floats. */
    inline constexpr double INFINITY_D = std::numeric_limits<double>::infinity();

    /** @brief Quiet Not-a-Number for single-precision floats. */
    inline constexpr float NaN = std::numeric_limits<float>::quiet_NaN();

    /** @brief Quiet Not-a-Number for double-precision floats. */
    inline constexpr double NaN_D = std::numeric_limits<double>::quiet_NaN();

    /** @brief The maximum possible swizzling dimension allowable for @ref fgm::Vector. */
    inline constexpr std::size_t MAX_VECTOR_SWIZZLE_DIMENSION = 4; // TODO: Remove

    /** @brief Standard value for PI. */
    template <std::floating_point T>
    inline constexpr T PI = std::numbers::pi_v<T>;

    /** @brief Standard value for inverse of PI (1/PI). */
    template <std::floating_point T>
    inline constexpr T INV_PI = std::numbers::inv_pi_v<T>;

    /** @brief Standard value for TAU (2.PI). */
    template <std::floating_point T>
    inline constexpr T TAU = std::numbers::pi_v<T> * T(2);

} // namespace fgm::constants


namespace fgm::axis
{
    inline constexpr std::size_t X = 0; ///< Alias for x-coordinate
    inline constexpr std::size_t Y = 1; ///< Alias for y-coordinate
    inline constexpr std::size_t Z = 2; ///< Alias for z-coordinate
    inline constexpr std::size_t W = 3; ///< Alias for w-coordinate
} // namespace fgm::axis


namespace fgm::colors
{
    inline constexpr std::size_t R = 0; ///< Alias for red channel
    inline constexpr std::size_t G = 1; ///< Alias for green channel
    inline constexpr std::size_t B = 2; ///< Alias for blue channel
    inline constexpr std::size_t A = 3; ///< Alias for alpha channel
} // namespace fgm::colors


namespace fgm::stp
{
    inline constexpr std::size_t S = 0; ///< Alias for s-coordinate
    inline constexpr std::size_t T = 1; ///< Alias for t-coordinate
    inline constexpr std::size_t P = 2; ///< Alias for p-coordinate
    inline constexpr std::size_t Q = 3; ///< Alias for q-coordinate
} // namespace fgm::stp

/**
 * @}
 */