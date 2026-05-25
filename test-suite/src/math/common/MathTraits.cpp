/**
 * @file MathTraits.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 25, 2026
 *
 * @brief Verify that all fgm math concepts constraints to expected types.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <common/MathTraits.h>
#include <cstdint>


namespace
{


    /** @brief Verify @ref fgm::StrictSignedness concept constraints two types of similar signedness. */
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
    }

} // namespace
