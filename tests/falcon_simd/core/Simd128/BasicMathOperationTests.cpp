/**
 * @file BasicMathOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 18, 2026
 *
 * @brief Verifies basic math operations like abs, min, max.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"

/**
 * @addtogroup T_SIMD128_Math
 * @{
 */

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)
namespace
{
    /**
     * @brief Test Fixture for Simd128 basic math operations like min, max, abs etc.
     */
    template <typename T>
    class Simd128BasicMathTests: public testing::Test
    {
    public:
        static constexpr auto max          = std::numeric_limits<typename T::Type>::max();
        static constexpr auto min          = std::numeric_limits<typename T::Type>::min();
        std::array<typename T::Type, 16> a = { max, min, max, min, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
        std::array<typename T::Type, 16> b = {
            min == 0 ? 1 : min, max, max, min == 0 ? 1 : min, 2, 3, 3, 4, 2, 2, 6, 3, 7, 5, 4, 6
        };
        // TODO: Add separate data for abs.
    };
    TYPED_TEST_SUITE(Simd128BasicMathTests, Simd128RegisterTypeHints);

} // namespace



TYPED_TEST(Simd128BasicMathTests, Min_ReturnsARegisterWithMinimumValuesFromEitherRegister)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->a[i];
        rhs[i]      = this->b[i];
        expected[i] = std::min(lhs[i], rhs[i]);
    }

    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = falcon::min(regA, regB);

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


#endif

/** @} */
