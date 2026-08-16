/**
 * @file LoadStoreTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 16, 2026
 *
 * @brief Verify @ref falcon::Simd128 register loading and storing in a platform agnostic manner.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */
#define FALCON_ENABLE_SSE2

#include "SIMDTestSetup.h"
#include "falcon_simd/memory/Simd128.h"

namespace
{
    template <typename T>
    class Simd128LoadStoreTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd128LoadStoreTests, Simd128RegisterTypeHints);
} // namespace

TYPED_TEST(Simd128LoadStoreTests, RegisterLoadsAndStoresDataWithoutCorruption)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::vector<Type> data{};
    data.resize(Lane);
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i);
    }

    falcon::Simd128_t<Type, Lane> reg;
    reg.loadAligned(data.data());

    std::vector<Type> result{};
    result.resize(Lane);

    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        if constexpr (std::is_same_v<Type, double>)
        {
            EXPECT_DOUBLE_EQ(data[i], result[i]);
        }
        else if constexpr (std::is_same_v<Type, float>)
        {
            EXPECT_FLOAT_EQ(data[i], result[i]);
        }
        else
        {
            EXPECT_EQ(data[i], result[i]);
        }
    }
}
