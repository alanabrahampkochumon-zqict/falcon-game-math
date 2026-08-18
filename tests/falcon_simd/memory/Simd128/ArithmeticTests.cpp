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
// namespace
// {
//     /**
//      * @brief Test Fixture for Simd128 load and store operations.
//      */
//     template <typename>
//     class Simd128ArithmeticTests: public testing::Test
//     {};
//     TYPED_TEST_SUITE(Simd128ArithmeticTests, Simd128RegisterTypeHints);
//
// } // namespace
//
//
// TYPED_TEST(Simd128ArithmeticTests, AddOperation_ProducesAValidResult)
// {
//     using Type            = TypeParam::Type;
//     constexpr size_t Lane = TypeParam::VALUE;
//
//     alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
//     for (size_t i = 0; i < Lane; ++i)
//     {
//         lhs[i] = static_cast<Type>(i * 3);
//         rhs[i] = static_cast<Type>(i * 5);
//         expected[i] = static_cast<Type>((i * 3) + (i * 5));
//     }
//
//     falcon::Simd128_t<Type, Lane> regA, regB;
//     regA.loadAligned(lhs.data());
//     regB.loadAligned(rhs.data());
//
//     auto regRes = regA + regB;
//
//     regRes.storeAligned(result.data());
//
//     for (size_t i = 0; i < Lane; ++i)
//     {
//         if constexpr (std::is_same_v<Type, double>)
//         {
//             EXPECT_DOUBLE_EQ(expected[i], result[i]);
//         }
//         else if constexpr (std::is_same_v<Type, float>)
//         {
//             EXPECT_FLOAT_EQ(expected[i], result[i]);
//         }
//         else
//         {
//             EXPECT_EQ(expected[i], result[i]);
//         }
//     }
// }


#endif
