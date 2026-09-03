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
     * @brief Test Fixture for Simd128 getter/setter operations.
     */
    template <typename T>
    class Simd128GetterSetterTests: public testing::Test
    {
    public:
        using Register = falcon::Simd128_t<typename T::Type, T::VALUE>;

        static constexpr auto max                              = std::numeric_limits<typename T::Type>::max();
        static constexpr auto min                              = std::numeric_limits<typename T::Type>::min();
        static constexpr std::array<typename T::Type, 16> data = { max, min, 0, 3,  5,  11, 15, 3,
                                                                   1,   2,   5, 12, 14, 3,  15, 12 };

        /// Testing condition
        template <size_t... Index>
        Register setValuesAndGetRegister(std::index_sequence<Index...>)
        {
            Register reg;
            reg.set(data[Index]...);
            return reg;
        }
    };
    TYPED_TEST_SUITE(Simd128GetterSetterTests, Simd128RegisterTypeHints);

} // namespace


TYPED_TEST(Simd128GetterSetterTests, Set_FillsActiveLanesInCorrectOrder)
{
    using Type                = TypeParam::Type;
    constexpr size_t Lane     = TypeParam::VALUE;
    constexpr size_t MaxLanes = 16 / sizeof(Type);

    /// Grab the register prefilled with values using set
    auto reg = this->setValuesAndGetRegister(std::make_index_sequence<Lane>{});

    alignas(16) std::array<Type, MaxLanes> result{};
    reg.store(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(result[i], this->data[i]);
    }
}


TYPED_TEST(Simd128GetterSetterTests, Set_FillsUnoccupiedSpaceWithZeroes)
{
    using Type                = typename TypeParam::Type;
    constexpr size_t Lane     = TypeParam::VALUE;
    constexpr size_t MaxLanes = 16 / sizeof(Type);

    // If the register is perfectly full (e.g., 4 floats), there is no space to pad.
    // We can tell GTest to automatically skip this specific matrix combination!
    if constexpr (Lane == MaxLanes)
    {
        GTEST_SKIP() << "Register is fully occupied, skipping zero-padding test.";
    }
    else
    {
        auto reg = this->setValuesAndGetRegister(std::make_index_sequence<Lane>{});

        alignas(16) std::array<Type, MaxLanes> result{};
        reg.store(result.data());


        for (size_t i = Lane; i < MaxLanes; ++i)
        {
            EXPECT_EQ(result[i], static_cast<Type>(0));
        }
    }
}


TEST(Simd128GetterSetterTests, Set_CanTakeParametersLessThanLaneSize)
{
    using Type            = uint8_t;
    constexpr size_t Lane = 8;
    falcon::Simd128_t<Type, Lane> reg{};

    reg.set(static_cast<Type>(1), static_cast<Type>(2), static_cast<Type>(3), static_cast<Type>(4),
            static_cast<Type>(5), static_cast<Type>(6), static_cast<Type>(7));
    std::array<Type, Lane> result;
    reg.store(result.data());

    EXPECT_EQ(1, result[0]);
    EXPECT_EQ(2, result[1]);
    EXPECT_EQ(3, result[2]);
    EXPECT_EQ(4, result[3]);
    EXPECT_EQ(5, result[4]);
    EXPECT_EQ(6, result[5]);
    EXPECT_EQ(7, result[6]);
}



TYPED_TEST(Simd128GetterSetterTests, SetZero_FillsTheLanesWithZeroes)
{
    using Type            = typename TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    auto reg = falcon::Simd128_t<Type, Lane>();
    reg.setZero();

    std::array<Type, Lane> result{};
    reg.store(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(static_cast<Type>(0), result[i]);
    }
}


TYPED_TEST(Simd128GetterSetterTests, SetOne_FillsTheLanesWithOnes)
{
    using Type            = typename TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    constexpr auto one    = getAllOnes<Type>();

    auto reg = falcon::Simd128_t<Type, Lane>();
    reg.setOne();

    std::array<Type, Lane> result{};
    reg.store(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        // Floating point types returns -nan which doesn't equal any so we must use
        // bitwise comparison.
        if constexpr (std::is_floating_point_v<Type>)
        {
            EXPECT_TRUE(isEqualBitwise(one, result[i]));
        }
        else
        {
            EXPECT_ANY_EQ(one, result[i]);
        }
    }
}


/// @test Verify that get(index) returns the element at the given index.
TYPED_TEST(Simd128GetterSetterTests, Get_FillsTheLanesWithOnes)
{
    constexpr size_t Lane = TypeParam::VALUE;
    auto reg = this->setValuesAndGetRegister(std::make_index_sequence<Lane>{});

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(this->data[i], reg.get(i));
    }
}

#endif

/** @} */
