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
    /**
     * @brief Test Fixture for Simd128 load and store operations.
     */
    template <typename>
    class Simd128LoadStoreTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd128LoadStoreTests, Simd128RegisterTypeHints);

} // namespace


TYPED_TEST(Simd128LoadStoreTests, LoadAligned_LoadsAndStoresDataWithoutCorruption)
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

TYPED_TEST(Simd128LoadStoreTests, Broadcast_StoresASingleValueIntoTheRegister)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    Type data = Type(7);
    falcon::Simd128_t<Type, Lane> reg;
    reg.broadcast(data);

    std::vector<Type> result{};
    result.resize(Lane);

    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        if constexpr (std::is_same_v<Type, double>)
        {
            EXPECT_DOUBLE_EQ(data, result[i]);
        }
        else if constexpr (std::is_same_v<Type, float>)
        {
            EXPECT_FLOAT_EQ(data, result[i]);
        }
        else
        {
            EXPECT_EQ(data, result[i]);
        }
    }
}


TYPED_TEST(Simd128LoadStoreTests, SetZero_ZeroesOutTheRegister)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    falcon::Simd128_t<Type, Lane> reg;
    reg.setZero();

    std::vector<Type> result{};
    result.resize(Lane);

    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        if constexpr (std::is_same_v<Type, double>)
        {
            EXPECT_DOUBLE_EQ(Type(0), result[i]);
        }
        else if constexpr (std::is_same_v<Type, float>)
        {
            EXPECT_FLOAT_EQ(Type(0), result[i]);
        }
        else
        {
            EXPECT_EQ(Type(0), result[i]);
        }
    }
}
