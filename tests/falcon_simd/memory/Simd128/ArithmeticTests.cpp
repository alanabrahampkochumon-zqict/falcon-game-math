/**
 * @file LoadStoreTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 18, 2026
 *
 * @brief Verify @ref falcon::Simd128 arithmetics.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "SIMDTestSetup.h"

#include <array>
#include <falcon_simd/memory/Simd128.h>

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)
namespace
{
    /**
     * @brief Test Fixture for Simd128 load and store operations.
     */
    template <typename>
    class Simd128ArithmeticTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd128ArithmeticTests, Simd128RegisterTypeHints);

} // namespace


TYPED_TEST(Simd128ArithmeticTests, BinaryAddOperation_ProducesAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = static_cast<Type>(i * 3);
        rhs[i]      = static_cast<Type>(i * 5);
        expected[i] = static_cast<Type>((i * 3) + (i * 5));
    }

    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA + regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        if constexpr (std::is_same_v<Type, double>)
        {
            EXPECT_DOUBLE_EQ(expected[i], result[i]);
        }
        else if constexpr (std::is_same_v<Type, float>)
        {
            EXPECT_FLOAT_EQ(expected[i], result[i]);
        }
        else
        {
            EXPECT_EQ(expected[i], result[i]);
        }
    }
}


TEST(Simd128ArithmeticTests, BinaryAddOperation_WorksWithMixedNumbers)
{

    alignas(16) std::array<float, 4> lhs{ 1, 5, -2, 0 }, rhs{ -1, 5, -5, -1 }, expected{ 0, 10, -7, -1 }, result{};

    falcon::Simd128_t<float, 4> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    const auto regRes = regA + regB;
    regRes.storeAligned(result.data());


    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128ArithmeticTests, CompoundAddOperation_ProducesAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = static_cast<Type>(i * 3);
        rhs[i]      = static_cast<Type>(i * 5);
        expected[i] = static_cast<Type>((i * 3) + (i * 5));
    }

    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA += regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        if constexpr (std::is_same_v<Type, double>)
        {
            EXPECT_DOUBLE_EQ(expected[i], result[i]);
        }
        else if constexpr (std::is_same_v<Type, float>)
        {
            EXPECT_FLOAT_EQ(expected[i], result[i]);
        }
        else
        {
            EXPECT_EQ(expected[i], result[i]);
        }
    }
}


TEST(Simd128ArithmeticTests, CompoundAddOperation_WorksWithMixedNumbers)
{

    alignas(16) std::array<float, 4> lhs{ 1, 5, -2, 0 }, rhs{ -1, 5, -5, -1 }, expected{ 0, 10, -7, -1 }, result{};

    falcon::Simd128_t<float, 4> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA += regB;
    regA.storeAligned(result.data());


    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128ArithmeticTests, BinarySubtractOperation_ProducesAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = static_cast<Type>(i * 5);
        rhs[i]      = static_cast<Type>(i * 3);
        expected[i] = static_cast<Type>((i * 5) - (i * 3));
    }

    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA - regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        if constexpr (std::is_same_v<Type, double>)
        {
            EXPECT_DOUBLE_EQ(expected[i], result[i]);
        }
        else if constexpr (std::is_same_v<Type, float>)
        {
            EXPECT_FLOAT_EQ(expected[i], result[i]);
        }
        else
        {
            EXPECT_EQ(expected[i], result[i]);
        }
    }
}


TEST(Simd128ArithmeticTests, BinarySubtractOperation_WorksWithMixedNumbers)
{

    alignas(16) std::array<float, 4> lhs{ 1, 5, -2, 0 }, rhs{ -1, 5, -5, -1 }, expected{ 2, 0, 3, 1 }, result{};

    falcon::Simd128_t<float, 4> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    const auto regRes = regA - regB;
    regRes.storeAligned(result.data());


    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128ArithmeticTests, CompoundSubtractOperation_ProducesAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = static_cast<Type>(i * 5);
        rhs[i]      = static_cast<Type>(i * 3);
        expected[i] = static_cast<Type>((i * 5) - (i * 3));
    }

    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA -= regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        if constexpr (std::is_same_v<Type, double>)
        {
            EXPECT_DOUBLE_EQ(expected[i], result[i]);
        }
        else if constexpr (std::is_same_v<Type, float>)
        {
            EXPECT_FLOAT_EQ(expected[i], result[i]);
        }
        else
        {
            EXPECT_EQ(expected[i], result[i]);
        }
    }
}


TEST(Simd128ArithmeticTests, CompoundSubtractOperation_WorksWithMixedNumbers)
{

    alignas(16) std::array<float, 4> lhs{ 1, 5, -2, 0 }, rhs{ -1, 5, -5, -1 }, expected{ 2, 0, 3, 1 }, result{};

    falcon::Simd128_t<float, 4> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA -= regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}

#endif
