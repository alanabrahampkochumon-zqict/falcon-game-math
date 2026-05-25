/**
 * @file MathTraits.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 25, 2026
 *
 * @brief Verify that all fgm math concepts constraints to expected types.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <array>
#include <common/MathTraits.h>
#include <cstdint>
#include <vector>


/**
 * @addtogroup T_Math_Traits
 * @{
 */

namespace
{
    /** @brief Verify that @ref fgm::Arithmetic concept constraints integrals and floating point types. */
    namespace
    {
        static_assert(fgm::Arithmetic<uint8_t> == true);
        static_assert(fgm::Arithmetic<uint16_t> == true);
        static_assert(fgm::Arithmetic<uint32_t> == true);
        static_assert(fgm::Arithmetic<uint64_t> == true);

        static_assert(fgm::Arithmetic<int8_t> == true);
        static_assert(fgm::Arithmetic<int16_t> == true);
        static_assert(fgm::Arithmetic<int32_t> == true);
        static_assert(fgm::Arithmetic<int64_t> == true);

        static_assert(fgm::Arithmetic<float> == true);
        static_assert(fgm::Arithmetic<double> == true);
        static_assert(fgm::Arithmetic<bool> == true);

        static_assert(fgm::Arithmetic<std::vector<int>> == false);
        static_assert(fgm::Arithmetic<std::array<int, 5>> == false);

    } // namespace


    /**
     * @brief Verify that @ref fgm::SignedStrictArithmetic concept constraints signed integrals
     *        and floating point types.
     */
    namespace
    {
        static_assert(fgm::SignedStrictArithmetic<uint8_t> == false);
        static_assert(fgm::SignedStrictArithmetic<uint16_t> == false);
        static_assert(fgm::SignedStrictArithmetic<uint32_t> == false);
        static_assert(fgm::SignedStrictArithmetic<uint64_t> == false);
        static_assert(fgm::SignedStrictArithmetic<bool> == false);

        static_assert(fgm::SignedStrictArithmetic<int8_t> == true);
        static_assert(fgm::SignedStrictArithmetic<int16_t> == true);
        static_assert(fgm::SignedStrictArithmetic<int32_t> == true);
        static_assert(fgm::SignedStrictArithmetic<int64_t> == true);

        static_assert(fgm::SignedStrictArithmetic<float> == true);
        static_assert(fgm::SignedStrictArithmetic<double> == true);
    } // namespace


    /**
     * @brief Verify that @ref fgm::StrictArithmetic concept constraints all signed integrals
     *        and floating point types except `bool`.
     */
    namespace
    {
        static_assert(fgm::StrictArithmetic<uint8_t> == true);
        static_assert(fgm::StrictArithmetic<uint16_t> == true);
        static_assert(fgm::StrictArithmetic<uint32_t> == true);
        static_assert(fgm::StrictArithmetic<uint64_t> == true);

        static_assert(fgm::StrictArithmetic<int8_t> == true);
        static_assert(fgm::StrictArithmetic<int16_t> == true);
        static_assert(fgm::StrictArithmetic<int32_t> == true);
        static_assert(fgm::StrictArithmetic<int64_t> == true);

        static_assert(fgm::StrictArithmetic<float> == true);
        static_assert(fgm::StrictArithmetic<double> == true);

        static_assert(fgm::StrictArithmetic<bool> == false);

    } // namespace


    /** @brief Verify that @ref fgm::WeakArithmetic concept constraints integrals and floating point types. */
    namespace
    {
        static_assert(fgm::WeakArithmetic<uint8_t> == true);
        static_assert(fgm::WeakArithmetic<uint16_t> == true);
        static_assert(fgm::WeakArithmetic<uint32_t> == true);
        static_assert(fgm::WeakArithmetic<uint64_t> == true);

        static_assert(fgm::WeakArithmetic<int8_t> == true);
        static_assert(fgm::WeakArithmetic<int16_t> == true);
        static_assert(fgm::WeakArithmetic<int32_t> == true);
        static_assert(fgm::WeakArithmetic<int64_t> == true);

        static_assert(fgm::WeakArithmetic<float> == true);
        static_assert(fgm::WeakArithmetic<double> == true);
        static_assert(fgm::WeakArithmetic<bool> == true);

        static_assert(fgm::WeakArithmetic<std::vector<int>> == false);
        static_assert(fgm::WeakArithmetic<std::array<int, 5>> == false);

    } // namespace


    /** @brief Verify that @ref fgm::StrictSignedness concept constraints two types of similar signedness. */
    namespace
    {
        // Unsigned types
        static_assert(fgm::StrictSignedness<uint8_t, uint8_t> == true);
        static_assert(fgm::StrictSignedness<uint16_t, uint8_t> == true);
        static_assert(fgm::StrictSignedness<uint32_t, uint8_t> == true);
        static_assert(fgm::StrictSignedness<uint64_t, uint8_t> == true);

        static_assert(fgm::StrictSignedness<uint16_t, uint16_t> == true);
        static_assert(fgm::StrictSignedness<uint32_t, uint16_t> == true);
        static_assert(fgm::StrictSignedness<uint64_t, uint16_t> == true);

        static_assert(fgm::StrictSignedness<uint32_t, uint32_t> == true);
        static_assert(fgm::StrictSignedness<uint64_t, uint32_t> == true);

        static_assert(fgm::StrictSignedness<uint64_t, uint64_t> == true);

        static_assert(fgm::StrictSignedness<uint8_t, float> == false);
        static_assert(fgm::StrictSignedness<uint16_t, float> == false);
        static_assert(fgm::StrictSignedness<uint32_t, float> == false);
        static_assert(fgm::StrictSignedness<uint64_t, float> == false);

        static_assert(fgm::StrictSignedness<uint8_t, double> == false);
        static_assert(fgm::StrictSignedness<uint16_t, double> == false);
        static_assert(fgm::StrictSignedness<uint32_t, double> == false);
        static_assert(fgm::StrictSignedness<uint64_t, double> == false);


        // Signed types
        static_assert(fgm::StrictSignedness<int8_t, int8_t> == true);
        static_assert(fgm::StrictSignedness<int16_t, int8_t> == true);
        static_assert(fgm::StrictSignedness<int32_t, int8_t> == true);
        static_assert(fgm::StrictSignedness<int64_t, int8_t> == true);

        static_assert(fgm::StrictSignedness<int16_t, int16_t> == true);
        static_assert(fgm::StrictSignedness<int32_t, int16_t> == true);
        static_assert(fgm::StrictSignedness<int64_t, int16_t> == true);

        static_assert(fgm::StrictSignedness<int32_t, int32_t> == true);
        static_assert(fgm::StrictSignedness<int64_t, int32_t> == true);

        static_assert(fgm::StrictSignedness<int64_t, int64_t> == true);

        static_assert(fgm::StrictSignedness<int8_t, float> == true);
        static_assert(fgm::StrictSignedness<int16_t, float> == true);
        static_assert(fgm::StrictSignedness<int32_t, float> == true);
        static_assert(fgm::StrictSignedness<int64_t, float> == true);

        static_assert(fgm::StrictSignedness<int8_t, double> == true);
        static_assert(fgm::StrictSignedness<int16_t, double> == true);
        static_assert(fgm::StrictSignedness<int32_t, double> == true);
        static_assert(fgm::StrictSignedness<int64_t, double> == true);

        // Mixed types
        static_assert(fgm::StrictSignedness<uint8_t, int8_t> == false);
        static_assert(fgm::StrictSignedness<uint16_t, int8_t> == false);
        static_assert(fgm::StrictSignedness<uint32_t, int8_t> == false);
        static_assert(fgm::StrictSignedness<uint64_t, int8_t> == false);

        static_assert(fgm::StrictSignedness<uint8_t, int16_t> == false);
        static_assert(fgm::StrictSignedness<uint16_t, int16_t> == false);
        static_assert(fgm::StrictSignedness<uint32_t, int16_t> == false);
        static_assert(fgm::StrictSignedness<uint64_t, int16_t> == false);

        static_assert(fgm::StrictSignedness<uint8_t, int32_t> == false);
        static_assert(fgm::StrictSignedness<uint16_t, int32_t> == false);
        static_assert(fgm::StrictSignedness<uint32_t, int32_t> == false);
        static_assert(fgm::StrictSignedness<uint64_t, int32_t> == false);

        static_assert(fgm::StrictSignedness<uint8_t, int64_t> == false);
        static_assert(fgm::StrictSignedness<uint16_t, int64_t> == false);
        static_assert(fgm::StrictSignedness<uint32_t, int64_t> == false);
        static_assert(fgm::StrictSignedness<uint64_t, int64_t> == false);

    } // namespace

} // namespace

/** @} */
