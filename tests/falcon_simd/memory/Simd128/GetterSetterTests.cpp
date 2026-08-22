/**
 * @file GetterSetterTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 22, 2026
 *
 * @brief Verifies Simd128 getters/setters.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"

#include <array>
#include <falcon_simd/memory/Simd128.h>


/**
 * @addtogroup T_SIMD128_Get_Set
 * @{
 */

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)
namespace
{
    /**
     * @brief Test Fixture for Simd128 load and store operations.
     */
    template <typename T>
    class Simd128GetterSettersTests: public testing::Test
    {
    public:
        std::array<typename T::Type, 16> data = { 10, 2, 0, 3, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
    };
    TYPED_TEST_SUITE(Simd128GetterSettersTests, Simd128RegisterTypeHints);

} // namespace

#endif

/** @} */
