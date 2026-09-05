/**
 * @file BlendTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 05, 2026
 *
 * @brief Verifies Simd128 blending and shuffling operations.
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
    using namespace simd::testing;

    template <typename T, size_t Lanes, Array<T, Lanes> first, Array<T, Lanes> second, Array<T, Lanes> mask,
              Array<T, Lanes> expected>
    struct Simd128BlendTestParam
    {
        using Type                            = T;
        static constexpr size_t REGISTER_SIZE = 128;
        static constexpr size_t LaneCount     = Lanes;
        static constexpr auto First           = first;
        static constexpr auto Second          = second;
        static constexpr auto Mask            = mask;
        static constexpr auto Expected        = expected;
        const char* TypeName                  = typeid(Type).name();

        // TODO: Fix pretty function not being used.
        friend std::ostream& operator<<(std::ostream& os, const Simd128BlendTestParam& param)
        { return os << "Simd128BlendTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }

        // friend void PrintTo(const Simd128BlendTestParam& param, std::ostream* os)
        // { *os << "Simd128BlendTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }
    };


    using Simd128BlendTestTypeHints = testing::Types<
        // Unsigned types
        Simd128BlendTestParam<U8, 2, Array<U8, 2>{ 100, 24 }, Array<U8, 2>{ 32, 15 }, Array<U8, 2>{ 0, ONE<U8> },
                              Array<U8, 2>{ 100, 15 }>,
        Simd128BlendTestParam<U8, 4, Array<U8, 4>{ 100, 24, 13, 15 }, Array<U8, 4>{ 32, 15, 61, 14 },
                              Array<U8, 4>{ 0, ONE<U8>, ONE<U8>, 0 }, Array<U8, 4>{ 100, 15, 61, 15 }>,
        Simd128BlendTestParam<U8, 8, Array<U8, 8>{ 100, 24, 13, 15, 32, 15, 71, 44 },
                              Array<U8, 8>{ 32, 15, 61, 14, 46, 55, 21, 74 },
                              Array<U8, 8>{ 0, ONE<U8>, ONE<U8>, 0, ONE<U8>, 0, 0, ONE<U8> },
                              Array<U8, 8>{ 100, 15, 61, 15, 46, 15, 71, 74 }>,
        Simd128BlendTestParam<U8, 16, Array<U8, 16>{ 100, 24, 13, 15, 32, 15, 71, 44, 100, 24, 13, 15, 32, 15, 71, 44 },
                              Array<U8, 16>{ 32, 15, 61, 14, 46, 55, 21, 74, 32, 15, 61, 14, 46, 55, 21, 74 },
                              Array<U8, 16>{ 0, ONE<U8>, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, ONE<U8>, 0,
                                             ONE<U8>, 0, 0, ONE<U8>, 0 },
                              Array<U8, 16>{ 100, 15, 61, 15, 46, 15, 21, 44, 32, 15, 13, 14, 32, 15, 21, 44 }>,

        Simd128BlendTestParam<U16, 2, Array<U16, 2>{ 100, 24 }, Array<U16, 2>{ 32, 15 }, Array<U16, 2>{ 0, ONE<U16> },
                              Array<U16, 2>{ 100, 15 }>,
        Simd128BlendTestParam<U16, 4, Array<U16, 4>{ 100, 24, 13, 15 }, Array<U16, 4>{ 32, 15, 61, 14 },
                              Array<U16, 4>{ 0, ONE<U16>, ONE<U16>, 0 }, Array<U16, 4>{ 100, 15, 61, 15 }>,
        Simd128BlendTestParam<U16, 8, Array<U16, 8>{ 100, 24, 13, 15, 32, 15, 71, 44 },
                              Array<U16, 8>{ 32, 15, 61, 14, 46, 55, 21, 74 },
                              Array<U16, 8>{ 0, ONE<U16>, ONE<U16>, 0, ONE<U16>, 0, 0, ONE<U16> },
                              Array<U16, 8>{ 100, 15, 61, 15, 46, 15, 71, 74 }>,

        Simd128BlendTestParam<U32, 2, Array<U32, 2>{ 100, 24 }, Array<U32, 2>{ 32, 15 }, Array<U32, 2>{ 0, ONE<U32> },
                              Array<U32, 2>{ 100, 15 }>,
        Simd128BlendTestParam<U32, 4, Array<U32, 4>{ 100, 24, 13, 15 }, Array<U32, 4>{ 32, 15, 61, 14 },
                              Array<U32, 4>{ 0, ONE<U32>, ONE<U32>, 0 }, Array<U32, 4>{ 100, 15, 61, 15 }>,
        Simd128BlendTestParam<U64, 2, Array<U64, 2>{ 100, 24 }, Array<U64, 2>{ 32, 15 }, Array<U64, 2>{ 0, ONE<U32> },
                              Array<U64, 2>{ 100, 15 }>,
        // Signed types
        Simd128BlendTestParam<I8, 2, Array<I8, 2>{ 100, 24 }, Array<I8, 2>{ 32, 15 }, Array<I8, 2>{ 0, ONE<I8> },
                              Array<I8, 2>{ 100, 15 }>,
        Simd128BlendTestParam<I8, 4, Array<I8, 4>{ 100, 24, 13, 15 }, Array<I8, 4>{ 32, 15, 61, 14 },
                              Array<I8, 4>{ 0, ONE<I8>, ONE<I8>, 0 }, Array<I8, 4>{ 100, 15, 61, 15 }>,
        Simd128BlendTestParam<I8, 8, Array<I8, 8>{ 100, 24, 13, 15, 32, 15, 71, 44 },
                              Array<I8, 8>{ 32, 15, 61, 14, 46, 55, 21, 74 },
                              Array<I8, 8>{ 0, ONE<I8>, ONE<I8>, 0, ONE<I8>, 0, 0, ONE<I8> },
                              Array<I8, 8>{ 100, 15, 61, 15, 46, 15, 71, 74 }>,
        Simd128BlendTestParam<I8, 16, Array<I8, 16>{ 100, 24, 13, 15, 32, 15, 71, 44, 100, 24, 13, 15, 32, 15, 71, 44 },
                              Array<I8, 16>{ 32, 15, 61, 14, 46, 55, 21, 74, 32, 15, 61, 14, 46, 55, 21, 74 },
                              Array<I8, 16>{ 0, ONE<I8>, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, ONE<I8>, 0,
                                             ONE<I8>, 0, 0, ONE<I8>, 0 },
                              Array<I8, 16>{ 100, 15, 61, 15, 46, 15, 21, 44, 32, 15, 13, 14, 32, 15, 21, 44 }>,

        Simd128BlendTestParam<I16, 2, Array<I16, 2>{ 100, 24 }, Array<I16, 2>{ 32, 15 }, Array<I16, 2>{ 0, ONE<I16> },
                              Array<I16, 2>{ 100, 15 }>,
        Simd128BlendTestParam<I16, 4, Array<I16, 4>{ 100, 24, 13, 15 }, Array<I16, 4>{ 32, 15, 61, 14 },
                              Array<I16, 4>{ 0, ONE<I16>, ONE<I16>, 0 }, Array<I16, 4>{ 100, 15, 61, 15 }>,
        Simd128BlendTestParam<I16, 8, Array<I16, 8>{ 100, 24, 13, 15, 32, 15, 71, 44 },
                              Array<I16, 8>{ 32, 15, 61, 14, 46, 55, 21, 74 },
                              Array<I16, 8>{ 0, ONE<I16>, ONE<I16>, 0, ONE<I16>, 0, 0, ONE<I16> },
                              Array<I16, 8>{ 100, 15, 61, 15, 46, 15, 71, 74 }>,

        Simd128BlendTestParam<I32, 2, Array<I32, 2>{ 100, 24 }, Array<I32, 2>{ 32, 15 }, Array<I32, 2>{ 0, ONE<I32> },
                              Array<I32, 2>{ 100, 15 }>,
        Simd128BlendTestParam<I32, 4, Array<I32, 4>{ 100, 24, 13, 15 }, Array<I32, 4>{ 32, 15, 61, 14 },
                              Array<I32, 4>{ 0, ONE<I32>, ONE<I32>, 0 }, Array<I32, 4>{ 100, 15, 61, 15 }>,
        Simd128BlendTestParam<I64, 2, Array<I64, 2>{ 100, 24 }, Array<I64, 2>{ 32, 15 }, Array<I64, 2>{ 0, ONE<I32> },
                              Array<I64, 2>{ 100, 15 }>,

        // Floating point types
        Simd128BlendTestParam<FP32, 2, Array<FP32, 2>{ 100.0f, 24.123849f }, Array<FP32, 2>{ 32.123f, 15.456f },
                              Array<FP32, 2>{ 0, ONE<FP32> }, Array<FP32, 2>{ 100.0f, 15.456f }>,
        Simd128BlendTestParam<FP32, 4, Array<FP32, 4>{ 100.0f, 24.123849f, 13.1234f, 15.482f },
                              Array<FP32, 4>{ 32.123f, 15.456f, 61.512f, 14.256f },
                              Array<FP32, 4>{ 0, ONE<FP32>, ONE<FP32>, 0 },
                              Array<FP32, 4>{ 100.0f, 15.456f, 61.512f, 15.482f }>,
        Simd128BlendTestParam<FP64, 2, Array<FP64, 2>{ 100.0, 24.123849 }, Array<FP64, 2>{ 32.123, 15.456 },
                              Array<FP64, 2>{ 0, ONE<FP64> }, Array<FP64, 2>{ 100.0, 15.456 }>>;

    /// @brief Test fixture for Simd128 blending operations.
    template <typename>
    class Simd128BlendTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd128BlendTests, Simd128BlendTestTypeHints);

} // namespace


TYPED_TEST(Simd128BlendTests, BlendingWithMaskReturnsRegisterWithCorrectValues)
{
    // Get all the parameters from the types
    using Type                            = TypeParam::Type;
    constexpr size_t Lanes                = TypeParam::LaneCount;
    constexpr Array<Type, Lanes> First    = TypeParam::First;
    constexpr Array<Type, Lanes> Second   = TypeParam::Second;
    constexpr Array<Type, Lanes> Mask     = TypeParam::Mask;
    constexpr Array<Type, Lanes> Expected = TypeParam::Expected;

    // Create the register and load them
    // Note: While const cast is not recommended in such a situation since the underlying buffer
    //       non-const, we can cast this as internally the load function doesn't mutate the parameters.
    falcon::Simd128_t<Type, Lanes> regA{}, regB{}, mask{};
    regA.load(const_cast<Type*>(First.data()));
    regB.load(const_cast<Type*>(Second.data()));
    mask.load(const_cast<Type*>(Mask.data()));

    // Perform the blending
    Array<Type, Lanes> result{};
    const auto resultReg = regA.blend(regB, mask);
    resultReg.store(result.data());

    // Compare and assert the result.
    for (size_t i = 0; i < Lanes; ++i)
    {
        EXPECT_ANY_EQ(Expected[i], result[i]);
    }
}

/** @} */

#endif
