/**
 * @file BitwiseOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 01, 2026
 *
 * @brief Verify Simd128 bitwise operators(~, |, ^, &, ...)
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "SIMDTestSetup.h"

#include <array>
#include <bit>

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)


/**
 * @addtogroup T_SIMD128_Bit
 * @{
 */

namespace
{
    /// @brief Test fixture for Simd128 bitwise operations.
    template <typename T>
    class Simd128BitwiseOperationTests: public testing::Test
    {
    public:
        std::array<typename T::Type, 16> lhsData;
        std::array<typename T::Type, 16> rhsData;

    protected:
        void SetUp() override
        {
            constexpr auto max = std::numeric_limits<typename T::Type>::max();
            constexpr auto min = std::numeric_limits<typename T::Type>::min();
            lhsData            = { max, min, min, max, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
            rhsData            = { min, max, min, max, 5, 11, 3, 28, 2, 7, 5, 6, 4, 11, 4, 6 };
        }
    };
    TYPED_TEST_SUITE(Simd128BitwiseOperationTests, Simd128RegisterTypeHints);

} // namespace


/// @test Verifies unary NOT(~) returns a matrix with inverted bits.
TYPED_TEST(Simd128BitwiseOperationTests, BitwiseNot_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->lhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected[i] = std::bit_cast<double>(~std::bit_cast<uint64_t>(this->lhsData[i]));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected[i] = std::bit_cast<float>(~std::bit_cast<uint32_t>(this->lhsData[i]));
        }
        else
        {

            expected[i] = ~this->lhsData[i];
        }
    }

    falcon::Simd128_t<Type, Lane> reg;
    reg.loadAligned(data.data());

    auto regRes = ~reg;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128BitwiseOperationTests, BitwiseAnd_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i] = this->lhsData[i];
        rhs[i] = this->rhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected[i] = std::bit_cast<double>(std::bit_cast<uint64_t>(lhs[i]) & std::bit_cast<uint64_t>(rhs[i]));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected[i] = std::bit_cast<float>(std::bit_cast<uint32_t>(lhs[i]) & std::bit_cast<uint32_t>(rhs[i]));
        }
        else
        {
            expected[i] = lhs[i] & rhs[i];
        }
    }

    falcon::Simd128_t<Type, Lane> regA{}, regB{};
    regA.loadAligned(rhs.data());
    regB.loadAligned(lhs.data());

    auto regRes = regA & regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128BitwiseOperationTests, BitwiseOr_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i] = this->lhsData[i];
        rhs[i] = this->rhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected[i] = std::bit_cast<double>(std::bit_cast<uint64_t>(lhs[i]) | std::bit_cast<uint64_t>(rhs[i]));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected[i] = std::bit_cast<float>(std::bit_cast<uint32_t>(lhs[i]) | std::bit_cast<uint32_t>(rhs[i]));
        }
        else
        {
            expected[i] = lhs[i] | rhs[i];
        }
    }

    falcon::Simd128_t<Type, Lane> regA{}, regB{};
    regA.loadAligned(rhs.data());
    regB.loadAligned(lhs.data());

    auto regRes = regA | regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}

/** @} */

#endif
