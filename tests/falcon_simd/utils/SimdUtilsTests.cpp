/**
 * @file SimdUtilsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 30, 2026
 *
 * @brief Verifies SIMD utilities.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "CommonSetup.h"

#include <falcon_simd/utils/SIMDUtils.h>
#include <gtest/gtest.h>


/**
 * @addtogroup T_SIMD_Utils
 * @{
 */

namespace
{
    /**************************************
     *             TEST SETUP             *
     **************************************/

    struct TestPackingParams
    {
        std::size_t totalByteSize;
        std::size_t alignAs;
        std::size_t expectedByteSize;
        std::size_t padding;
        std::size_t packedRegisterWidth;
        std::size_t registerCount;
    };
    /** @brief Test fixture for register packed size calculation, parameterized by @ref TestPackingParams */
    class PackedSizeCalculatorTests: public testing::TestWithParam<TestPackingParams>
    {};

    /// @brief Test fixture for @ref falcon::expandFourFolds.
    class ExpandFourFoldTests: public testing::TestWithParam<std::pair<falcon::BlendMask32_t, falcon::uint128_t>>
    {};

    INSTANTIATE_TEST_SUITE_P(
        ExpandFourFoldTests, ExpandFourFoldTests,
        testing::Values(
            std::make_pair(0x0000FFFF, falcon::uint128_t{ .upper = 0x0000000000000000, .lower = 0xFFFFFFFFFFFFFFFF }),
            std::make_pair(0xFFFFFFFF, falcon::uint128_t{ .upper = 0xFFFFFFFFFFFFFFFF, .lower = 0xFFFFFFFFFFFFFFFF }),
            std::make_pair(0x00000000, falcon::uint128_t{ .upper = 0x0000000000000000, .lower = 0x0000000000000000 }),
            std::make_pair(0xFFFF0000, falcon::uint128_t{ .upper = 0xFFFFFFFFFFFFFFFF, .lower = 0x0000000000000000 }),
            std::make_pair(0x0F0F0F0F, falcon::uint128_t{ .upper = 0x0000FFFF0000FFFF, .lower = 0x0000FFFF0000FFFF }),
            std::make_pair(0xF0F0F0F0, falcon::uint128_t{ .upper = 0xFFFF0000FFFF0000, .lower = 0xFFFF0000FFFF0000 }),
            std::make_pair(0x79151FEE, falcon::uint128_t{ .upper = 0x0FFFF00F000F0F0F, .lower = 0x000FFFFFFFF0FFF0 }),
            std::make_pair(0x2AC1FC11, falcon::uint128_t{ .upper = 0x00F0F0F0FF00000F, .lower = 0xFFFFFF00000F000F }),
            std::make_pair(0xB8A6A044, falcon::uint128_t{ .upper = 0xF0FFF000F0F00FF0, .lower = 0xF0F000000F000F00 }),
            std::make_pair(0xFE8D8D40, falcon::uint128_t{ .upper = 0xFFFFFFF0F000FF0F, .lower = 0xF000FF0F0F000000 })));

    template <typename>
    class GetAllOnesTests: public testing::Test
    {};

    TYPED_TEST_SUITE(GetAllOnesTests, SupportedArithmeticTypes);

    /**************************************
     *          STATIC TESTS              *
     **************************************/

    namespace static_tests
    {
        using namespace falcon::simd;
        constexpr bool T = true;
        constexpr bool F = false;

        /// @test Verify that @ref falcon::simd::makeBlendMask32 returns a correct mask for 2 booleans
        static_assert(makeBlendMask32<T, F>() == 0x0000FFFF);
        static_assert(makeBlendMask32<F, T>() == 0xFFFF0000);

        /// @test Verify that @ref falcon::simd::makeBlendMask32 returns a correct mask for 4 booleans
        static_assert(makeBlendMask32<T, F, T, F>() == 0x00FF00FF);
        static_assert(makeBlendMask32<F, T, F, T>() == 0xFF00FF00);

        /// @test Verify that @ref falcon::simd::makeBlendMask32 returns a correct mask for 8 booleans
        static_assert(makeBlendMask32<T, F, T, F, T, F, T, F>() == 0x0F0F0F0F);
        static_assert(makeBlendMask32<F, T, F, T, F, T, F, T>() == 0xF0F0F0F0);


        /// @test Verify that @ref falcon::simd::makeBlendMask32 returns a correct mask for 16 booleans
        static_assert(makeBlendMask32<T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F>() == 0x33333333);
        static_assert(makeBlendMask32<F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T>() == 0xCCCCCCCC);

        /// @test Verify that @ref falcon::simd::makeBlendMask32 returns a correct mask for 32 booleans
        static_assert(makeBlendMask32<T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T,
                                      F, T, F, T, F>() == 0x55555555);
        static_assert(makeBlendMask32<F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F,
                                      T, F, T, F, T>() == 0xAAAAAAAA);


        /// @test Verify that @ref falcon::simd::expandFourFold returns a valid value expanded four fold
        static_assert(expandFourFold(0x79151FEE).upper == 0x0FFFF00F000F0F0F);
        static_assert(expandFourFold(0x79151FEE).lower == 0x000FFFFFFFF0FFF0);
        static_assert(expandFourFold(0x0000FFFF).upper == 0x0000000000000000);
        static_assert(expandFourFold(0x0000FFFF).lower == 0xFFFFFFFFFFFFFFFF);
        static_assert(expandFourFold(0xFFFF0000).upper == 0xFFFFFFFFFFFFFFFF);
        static_assert(expandFourFold(0xFFFF0000).lower == 0x0000000000000000);

    } // namespace static_tests

} // namespace


/**
 * @test Verify that the packed size parameter returns the correct aligned byte size, padding, register width
 *        and count.
 */
TEST_P(PackedSizeCalculatorTests, CalculatesCorrectSize)
{
    // Given an arbitrary data type size and total byte size
    const auto [totalByteSize, alignAs, expectedByteSize, expectedPadding, expectedPackedRegisterWidth,
                expectedRegisterCount] = GetParam();

    // When packed size is calculated
    const auto [alignedByteSize, padding, packedRegisterWidth, registerCount] =
        falcon::simd::calculatePackedSize(totalByteSize, alignAs);

    // It gives the nearest packed size and padding
    EXPECT_EQ(expectedByteSize, alignedByteSize);
    EXPECT_EQ(expectedPadding, padding);
    EXPECT_EQ(expectedPackedRegisterWidth, packedRegisterWidth);
    EXPECT_EQ(expectedRegisterCount, registerCount);
}

INSTANTIATE_TEST_SUITE_P(
    PackedSizeCalculatorTestSuite, PackedSizeCalculatorTests,
    ::testing::Values(
        // SSE
        TestPackingParams{ 1, 16, 16, 15, 16, 1 }, TestPackingParams{ 4, 16, 16, 12, 16, 1 },
        TestPackingParams{ 8, 16, 16, 8, 16, 1 }, TestPackingParams{ 12, 16, 16, 4, 16, 1 },
        TestPackingParams{ 16, 16, 16, 0, 16, 1 }, TestPackingParams{ 20, 16, 32, 12, 16, 2 },
        TestPackingParams{ 24, 16, 32, 8, 16, 2 }, TestPackingParams{ 32, 16, 32, 0, 16, 2 },
        TestPackingParams{ 48, 16, 64, 16, 16, 4 }, TestPackingParams{ 56, 16, 64, 8, 16, 4 },
        TestPackingParams{ 64, 16, 64, 0, 16, 4 }, TestPackingParams{ 72, 16, 128, 56, 16, 8 },
        TestPackingParams{ 80, 16, 128, 48, 16, 8 }, TestPackingParams{ 128, 16, 128, 0, 16, 8 },
        TestPackingParams{ 192, 16, 256, 64, 16, 16 }, TestPackingParams{ 256, 16, 256, 0, 16, 16 },
        TestPackingParams{ 512, 16, 512, 0, 16, 32 }, TestPackingParams{ 777, 16, 1024, 247, 16, 64 },
        TestPackingParams{ 1024, 16, 1024, 0, 16, 64 },
        // AVX/AVX2
        TestPackingParams{ 1, 32, 16, 15, 16, 1 }, TestPackingParams{ 4, 32, 16, 12, 16, 1 },
        TestPackingParams{ 8, 32, 16, 8, 16, 1 }, TestPackingParams{ 12, 32, 16, 4, 16, 1 },
        TestPackingParams{ 16, 32, 16, 0, 16, 1 }, TestPackingParams{ 20, 32, 32, 12, 32, 1 },
        TestPackingParams{ 24, 32, 32, 8, 32, 1 }, TestPackingParams{ 32, 32, 32, 0, 32, 1 },
        TestPackingParams{ 48, 32, 64, 16, 32, 2 }, TestPackingParams{ 56, 32, 64, 8, 32, 2 },
        TestPackingParams{ 64, 32, 64, 0, 32, 2 }, TestPackingParams{ 72, 32, 128, 56, 32, 4 },
        TestPackingParams{ 80, 32, 128, 48, 32, 4 }, TestPackingParams{ 128, 32, 128, 0, 32, 4 },
        TestPackingParams{ 192, 32, 256, 64, 32, 8 }, TestPackingParams{ 256, 32, 256, 0, 32, 8 },
        TestPackingParams{ 512, 32, 512, 0, 32, 16 }, TestPackingParams{ 777, 32, 1024, 247, 32, 32 },
        TestPackingParams{ 1024, 32, 1024, 0, 32, 32 },
        // AVX512
        TestPackingParams{ 1, 64, 16, 15, 16, 1 }, TestPackingParams{ 4, 64, 16, 12, 16, 1 },
        TestPackingParams{ 8, 64, 16, 8, 16, 1 }, TestPackingParams{ 12, 64, 16, 4, 16, 1 },
        TestPackingParams{ 16, 64, 16, 0, 16, 1 }, TestPackingParams{ 20, 64, 32, 12, 32, 1 },
        TestPackingParams{ 24, 64, 32, 8, 32, 1 }, TestPackingParams{ 32, 64, 32, 0, 32, 1 },
        TestPackingParams{ 48, 64, 64, 16, 64, 1 }, TestPackingParams{ 56, 64, 64, 8, 64, 1 },
        TestPackingParams{ 64, 64, 64, 0, 64, 1 }, TestPackingParams{ 72, 64, 128, 56, 64, 2 },
        TestPackingParams{ 80, 64, 128, 48, 64, 2 }, TestPackingParams{ 128, 64, 128, 0, 64, 2 },
        TestPackingParams{ 192, 64, 256, 64, 64, 4 }, TestPackingParams{ 256, 64, 256, 0, 64, 4 },
        TestPackingParams{ 512, 64, 512, 0, 64, 8 }, TestPackingParams{ 777, 64, 1024, 247, 64, 16 },
        TestPackingParams{ 1024, 64, 1024, 0, 64, 16 }));



TYPED_TEST(GetAllOnesTests, ReturnsValueWithOneInAllBits)
{
    const auto value = falcon::simd::getAllOnes<TypeParam>();
    if constexpr (std::same_as<double, TypeParam>)
    {
        EXPECT_EQ(0xFFFFFFFFFFFFFFFF, std::bit_cast<uint64_t>(value));
    }
    else if constexpr (std::same_as<float, TypeParam>)
    {
        EXPECT_EQ(0xFFFFFFFF, std::bit_cast<uint32_t>(value));
    }
    else
    {
        EXPECT_EQ(static_cast<TypeParam>(0xFFFFFFFFFFFFFFFF), value);
    }
}


TEST_P(ExpandFourFoldTests, ExpandsEachBitBy4TimesAndReturnsAValidPair)
{
    const auto [blendMask, expectedValue] = GetParam();
    const auto value                      = falcon::simd::expandFourFold(blendMask);
    EXPECT_EQ(expectedValue.upper, value.upper);
    EXPECT_EQ(expectedValue.lower, value.lower);
}



/// =============================== MAKE_BLEND_MASK_32 ===============================

/// @test Verify that makeBlendMask32 returns a correct mask given all mask combinations.
#define TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(TestSuffix, ExpectedMask, ...)                      \
    TEST(MakeBlendMask32Tests, ReturnsValidMask_For##TestSuffix)                                                       \
    { EXPECT_EQ(ExpectedMask, (falcon::simd::makeBlendMask32<__VA_ARGS__>())); }

// Aliasing to make testing easier.
constexpr bool T = true;
constexpr bool F = false;

TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(TwoBoolsWithAllTrue, 0xFFFFFFFF, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(TwoBoolsWithAlternatingTrueFalse, 0x0000FFFF, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(TwoBoolsWithAlternatingFalseTrue, 0xFFFF0000, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(TwoBoolsWithAllFalse, 0x00000000, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(FourBoolsWithAllTrue, 0xFFFFFFFF, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(FourBoolsWithAlternatingTrueFalse, 0x00FF00FF, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(FourBoolsWithAlternatingFalseTrue, 0xFF00FF00, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(FourBoolsWithAllFalse, 0x00000000, F, F, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(EightBoolsWithAllTrue, 0xFFFFFFFF, T, T, T, T, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(EightBoolsWithAlternatingTrueFalse, 0x0F0F0F0F, T, F, T, F,
                                                           T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(EightBoolsWithAlternatingFalseTrue, 0xF0F0F0F0, F, T, F, T,
                                                           F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(EightBoolsWithAllFalse, 0x00000000, F, F, F, F, F, F, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(SixteenBoolsWithAllTrue, 0xFFFFFFFF, T, T, T, T, T, T, T, T,
                                                           T, T, T, T, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(SixteenBoolsWithAlternatingTrueFalse, 0x33333333, T, F, T, F,
                                                           T, F, T, F, T, F, T, F, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(SixteenBoolsWithAlternatingFalseTrue, 0xCCCCCCCC, F, T, F, T,
                                                           F, T, F, T, F, T, F, T, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(SixteenBoolsWithAllFalse, 0x00000000, F, F, F, F, F, F, F, F,
                                                           F, F, F, F, F, F, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(ThirtyTwoBoolsWithAllTrue, 0xFFFFFFFF, T, T, T, T, T, T, T,
                                                           T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
                                                           T, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(ThirtyTwoBoolsWithAlternatingTrueFalse, 0x55555555, T, F, T,
                                                           F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T,
                                                           F, T, F, T, F, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(ThirtyTwoBoolsWithAlternatingFalseTrue, 0xAAAAAAAA, F, T, F,
                                                           T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F,
                                                           T, F, T, F, T, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK_RETURNS_CORRECT_32BIT_MASK(ThirtyTwoBoolsWithAllFalse, 0x00000000, F, F, F, F, F, F, F,
                                                           F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
                                                           F, F, F, F, F)

/// =============================== END MAKE_BLEND_MASK_32 ===============================

/** @} */
