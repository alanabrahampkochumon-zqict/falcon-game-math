/**
 * @file UtilTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 16, 2026
 *
 * @brief Verifies Simd128 utilities like hasNaN or hasInf masked.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"


// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)


/**
 * @addtogroup T_SIMD128_Utils
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /// @brief Test fixture for hasNan utility.
    /// @tparam T The numeric type and Lane of test values.
    template <typename T>
    class Simd128UtilsTests: public testing::Test
    {
    public:
        using Type                = T::Type;
        static constexpr auto max = std::numeric_limits<Type>::max();
        static constexpr auto min = std::numeric_limits<Type>::min();
        // Note: Min is swapped with 1 in b to prevent seh
        std::array<typename T::Type, 16> nanVec, infVec, expectedNanVec, expectedInfVec;

    protected:
        void SetUp() override
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                Type nan       = std::numeric_limits<Type>::quiet_NaN();
                Type inf       = std::numeric_limits<Type>::infinity();
                nanVec         = { nan, -5, nan, 2, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                expectedNanVec = { Type(~0), 0, Type(~0), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                infVec         = { inf, -inf, inf, -inf, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                expectedInfVec = { Type(~0), Type(~0), Type(~0), Type(~0), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            }
            else
            {
                nanVec         = { max, min, max, min, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                infVec         = { max, min, max, min, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                expectedNanVec = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                expectedInfVec = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            }
        }
    };

    TYPED_TEST_SUITE(Simd128UtilsTests, Simd128RegisterTypeHints);

} // namespace


template <typename T>
static constexpr T NaN = std::numeric_limits<T>::quiet_NaN();

template <typename T>
static constexpr T Inf = std::numeric_limits<T>::infinity();

TYPED_TEST(Simd128UtilsTests, HasNaN_ReturnsValidMask)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{}, resultMask;
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->nanVec[i];
    }
    falcon::Simd128_t<Type, Lane> regA{ data };

    auto regRes = regA.hasNan();

    regRes.storeAligned(resultMask.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(this->expectedNanVec[i], resultMask[i]);
    }
}


TYPED_TEST(Simd128UtilsTests, HasInf_ReturnsValidMask)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{}, resultMask;
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->infVec[i];
    }
    falcon::Simd128_t<Type, Lane> regA{ data };

    auto regRes = regA.hasInf();

    regRes.storeAligned(resultMask.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(this->expectedNanVec[i], resultMask[i]);
    }
}



using namespace simd::testing;

/// @test Verify that hasNan returns the correct simd mask for floating point types with various data patterns.
    #define SIMD128_HAS_NAN_TESTS_FP(TestName, Type, Lane, Data, Expected)                                             \
        TEST(HasNaNTests, ReturnsValidMaskGiven_##TestName)                                                            \
        {                                                                                                              \
            falcon::Simd128_t<Type, Lane> regA{ Data };                                                                \
                                                                                                                       \
            alignas(16) std::array<Type, Lane> resultMask{};                                                           \
            auto regRes = regA.hasNan();                                                                               \
            regRes.storeAligned(resultMask.data());                                                                    \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(Expected[i], resultMask[i]);                                                             \
            }                                                                                                          \
        }

constexpr auto DATA_FP32_2LANES_NO_NAN = Array<FP32, 2>{ 1.0f, 2.0f };
constexpr auto RES_FP32_2LANES_NO_NAN  = Array<FP32, 2>{ 0, 0 };
SIMD128_HAS_NAN_TESTS_FP(FP32_2Lanes_NonNaN, FP32, 2, DATA_FP32_2LANES_NO_NAN, RES_FP32_2LANES_NO_NAN)

constexpr auto DATA_FP32_2LANES_FULL_NAN = Array<FP32, 2>{ NaN<FP32>, NaN<FP32> };
constexpr auto RES_FP32_2LANES_FULL_NAN  = Array<FP32, 2>{ NaN<FP32>, NaN<FP32> };
SIMD128_HAS_NAN_TESTS_FP(FP32_2Lanes_FullNaN, FP32, 2, DATA_FP32_2LANES_FULL_NAN, RES_FP32_2LANES_FULL_NAN)

constexpr auto DATA_FP32_2LANES_MIXED_NAN = Array<FP32, 2>{ 1.0f, NaN<FP32> };
constexpr auto RES_FP32_2LANES_MIXED_NAN  = Array<FP32, 2>{ 0, NaN<FP32> };
SIMD128_HAS_NAN_TESTS_FP(FP32_2Lanes_AlternatingNaN, FP32, 2, DATA_FP32_2LANES_MIXED_NAN, RES_FP32_2LANES_MIXED_NAN)

constexpr auto DATA_FP32_4LANES_NO_NAN = Array<FP32, 4>{ 1.0f, 2.0f, 3.0f, 4.0f };
constexpr auto RES_FP32_4LANES_NO_NAN  = Array<FP32, 4>{ 0, 0, 0, 0 };
SIMD128_HAS_NAN_TESTS_FP(FP32_4Lanes_NonNaN, FP32, 4, DATA_FP32_4LANES_NO_NAN, RES_FP32_4LANES_NO_NAN)

constexpr auto DATA_FP32_4LANES_FULL_NAN = Array<FP32, 4>{ NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32> };
constexpr auto RES_FP32_4LANES_FULL_NAN  = Array<FP32, 4>{ NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32> };
SIMD128_HAS_NAN_TESTS_FP(FP32_4Lanes_FullNaN, FP32, 4, DATA_FP32_4LANES_FULL_NAN, RES_FP32_4LANES_FULL_NAN)

constexpr auto DATA_FP32_4LANES_MIXED_NAN = Array<FP32, 4>{ 1.0f, NaN<FP32>, 1.0f, NaN<FP32> };
constexpr auto RES_FP32_4LANES_MIXED_NAN  = Array<FP32, 4>{ 0, NaN<FP32>, 0, NaN<FP32> };
SIMD128_HAS_NAN_TESTS_FP(FP32_4Lanes_AlternatingNaN, FP32, 4, DATA_FP32_4LANES_MIXED_NAN, RES_FP32_4LANES_MIXED_NAN)

constexpr auto DATA_FP64_2LANES_NO_NAN = Array<FP64, 2>{ 1.0f, 2.0f };
constexpr auto RES_FP64_2LANES_NO_NAN  = Array<FP64, 2>{ 0, 0 };
SIMD128_HAS_NAN_TESTS_FP(FP64_2Lanes_NonNaN, FP64, 2, DATA_FP64_2LANES_NO_NAN, RES_FP64_2LANES_NO_NAN)

constexpr auto DATA_FP64_2LANES_FULL_NAN = Array<FP64, 2>{ NaN<FP64>, NaN<FP64> };
constexpr auto RES_FP64_2LANES_FULL_NAN  = Array<FP64, 2>{ NaN<FP64>, NaN<FP64> };
SIMD128_HAS_NAN_TESTS_FP(FP64_2Lanes_FullNaN, FP64, 2, DATA_FP64_2LANES_FULL_NAN, RES_FP64_2LANES_FULL_NAN)

constexpr auto DATA_FP64_2LANES_MIXED_NAN = Array<FP64, 2>{ 1.0f, NaN<FP64> };
constexpr auto RES_FP64_2LANES_MIXED_NAN  = Array<FP64, 2>{ 0, NaN<FP64> };
SIMD128_HAS_NAN_TESTS_FP(FP64_2Lanes_AlternatingNaN, FP64, 2, DATA_FP64_2LANES_MIXED_NAN, RES_FP64_2LANES_MIXED_NAN)



/// @test Verify that hasNan returns the correct simd mask for floating point types with various data patterns.
    #define SIMD128_HAS_INF_TESTS_FP(TestName, Type, Lane, Data, Expected)                                             \
        TEST(HasInfTests, ReturnsValidMaskGiven_##TestName)                                                            \
        {                                                                                                              \
            falcon::Simd128_t<Type, Lane> regA{ Data };                                                                \
                                                                                                                       \
            alignas(16) std::array<Type, Lane> resultMask{};                                                           \
            auto regRes = regA.hasInf();                                                                               \
            regRes.storeAligned(resultMask.data());                                                                    \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(Expected[i], resultMask[i]);                                                             \
            }                                                                                                          \
        }

constexpr auto DATA_FP32_2LANES_NO_INF = Array<FP32, 2>{ 1.0f, 2.0f };
constexpr auto RES_FP32_2LANES_NO_INF  = Array<FP32, 2>{ 0, 0 };
SIMD128_HAS_INF_TESTS_FP(FP32_2Lanes_NonInf, FP32, 2, DATA_FP32_2LANES_NO_INF, RES_FP32_2LANES_NO_INF)

constexpr auto DATA_FP32_2LANES_FULL_INF = Array<FP32, 2>{ Inf<FP32>, -Inf<FP32> };
constexpr auto RES_FP32_2LANES_FULL_INF  = Array<FP32, 2>{ NaN<FP32>, NaN<FP32> };
SIMD128_HAS_INF_TESTS_FP(FP32_2Lanes_FullInf, FP32, 2, DATA_FP32_2LANES_FULL_INF, RES_FP32_2LANES_FULL_INF)

constexpr auto DATA_FP32_2LANES_MIXED_INF = Array<FP32, 2>{ 1.0f, Inf<FP32> };
constexpr auto RES_FP32_2LANES_MIXED_INF  = Array<FP32, 2>{ 0, NaN<FP32> };
SIMD128_HAS_INF_TESTS_FP(FP32_2Lanes_AlternatingInf, FP32, 2, DATA_FP32_2LANES_MIXED_INF, RES_FP32_2LANES_MIXED_INF)

constexpr auto DATA_FP32_4LANES_NO_INF = Array<FP32, 4>{ 1.0f, 2.0f, 3.0f, 4.0f };
constexpr auto RES_FP32_4LANES_NO_INF  = Array<FP32, 4>{ 0, 0, 0, 0 };
SIMD128_HAS_INF_TESTS_FP(FP32_4Lanes_NonInf, FP32, 4, DATA_FP32_4LANES_NO_INF, RES_FP32_4LANES_NO_INF)

constexpr auto DATA_FP32_4LANES_FULL_INF = Array<FP32, 4>{ Inf<FP32>, -Inf<FP32>, Inf<FP32>, -Inf<FP32> };
constexpr auto RES_FP32_4LANES_FULL_INF  = Array<FP32, 4>{ NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32> };
SIMD128_HAS_INF_TESTS_FP(FP32_4Lanes_FullInf, FP32, 4, DATA_FP32_4LANES_FULL_INF, RES_FP32_4LANES_FULL_INF)

constexpr auto DATA_FP32_4LANES_MIXED_INF = Array<FP32, 4>{ 1.0f, -Inf<FP32>, 1.0f, -Inf<FP32> };
constexpr auto RES_FP32_4LANES_MIXED_INF  = Array<FP32, 4>{ 0, NaN<FP32>, 0, NaN<FP32> };
SIMD128_HAS_INF_TESTS_FP(FP32_4Lanes_AlternatingInf, FP32, 4, DATA_FP32_4LANES_MIXED_INF, RES_FP32_4LANES_MIXED_INF)

constexpr auto DATA_FP64_2LANES_NO_INF = Array<FP64, 2>{ 1.0f, 2.0f };
constexpr auto RES_FP64_2LANES_NO_INF  = Array<FP64, 2>{ 0, 0 };
SIMD128_HAS_INF_TESTS_FP(FP64_2Lanes_NonInf, FP64, 2, DATA_FP64_2LANES_NO_INF, RES_FP64_2LANES_NO_INF)

constexpr auto DATA_FP64_2LANES_FULL_INF = Array<FP64, 2>{ -Inf<FP64>, Inf<FP64> };
constexpr auto RES_FP64_2LANES_FULL_INF  = Array<FP64, 2>{ NaN<FP64>, NaN<FP64> };
SIMD128_HAS_INF_TESTS_FP(FP64_2Lanes_FullInf, FP64, 2, DATA_FP64_2LANES_FULL_INF, RES_FP64_2LANES_FULL_INF)

constexpr auto DATA_FP64_2LANES_MIXED_INF = Array<FP64, 2>{ 1.0f, -Inf<FP64> };
constexpr auto RES_FP64_2LANES_MIXED_INF  = Array<FP64, 2>{ 0, NaN<FP64> };
SIMD128_HAS_INF_TESTS_FP(FP64_2Lanes_AlternatingInf, FP64, 2, DATA_FP64_2LANES_MIXED_INF, RES_FP64_2LANES_MIXED_INF)

/** @} */

#endif
