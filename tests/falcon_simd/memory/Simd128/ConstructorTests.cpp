/**
 * @file ConstructorTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 08, 2026
 *
 * @brief Verifies Simd128 constructors.
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
 * @addtogroup T_SIMD128_Cmp
 * @{
 */


namespace
{
    // using namespace simd::testing;
    //
    // /// Test param for constructor initialization with parameter pack.
    // // since gtest doesn't natively support parameterized typed test(where you can pass in parameters against a type
    // // vector)
    // template <typename T, size_t Lanes, size_t Count, Array<T, Count> Data>
    // struct Simd128CtorParamPackTestParams
    // {
    //     using Type                            = T;
    //     static constexpr Array<T, Count> data = Data;
    //     static constexpr size_t count         = Count;
    //     static constexpr size_t REGISTER_SIZE = 128;
    //     static constexpr size_t LaneCount     = Lanes;
    //     const char* TypeName                  = typeid(Type).name();
    //
    //     // TODO: Fix pretty function not being used.
    //     friend std::ostream& operator<<(std::ostream& os, const Simd128CtorParamPackTestParams& param)
    //     {
    //         return os << "Simd128CtorParamPackTestParams(Type=" << param.TypeName << ", Lanes" << param.LaneCount
    //                   << ")";
    //     }
    //
    //     // friend void PrintTo(const Simd128CtorParamPackTestParams& param, std::ostream* os)
    //     // { *os << "Simd128CtorParamPackTestParams(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")";
    //     }
    // };
    //
    // using Simd128ParamPackCtorTypeHints =
    //     testing::Types<Simd128CtorParamPackTestParams<U8, 2, 1, std::array<U8, 1>{ { 1 } }>>;
    //
    //
    // /// @brief Test fixture for Simd128 constructor init with variable number of parameters(>1).
    // template <typename>
    // class Simd128CtorParamPackTests: public testing::Test
    // {};
    // TYPED_TEST_SUITE(Simd128CtorParamPackTests, Simd128ParamPackCtorTypeHints);
} // namespace


// TYPED_TEST(Simd128CtorParamPackTests, CtorInitializesTheRegisterWithTheValues)
// {
//     // Get all the parameters from the types
//     using Type                          = TypeParam::Type;
//     constexpr size_t Lanes              = TypeParam::LaneCount;
//     constexpr size_t ArrSize            = TypeParam::count;
//     constexpr Array<Type, ArrSize> data = TypeParam::data;
//
//     falcon::Simd128_t<Type, Lanes>(data.begin(), data.end());
//
//     // Create the register and load them
//     // Note: While const cast is not recommended in such a situation since the underlying buffer
//     //       non-const, we can cast this as internally the load function doesn't mutate the parameters.
//     // Since we can't directly access the parameter pack
//     // we need to use call it using a lambda nad integer_sequence
//     auto execShuffle = [data]<uint8_t... I>(std::integer_sequence<uint8_t, I...>) {
//         falcon::Simd128_t<Type, Lanes> reg{};
//         reg.load(const_cast<Type*>(data.data()));
//         return reg.template shuffle<I...>();
//     };
//
//     // Perform the shuffling
//     Array<Type, Lanes> result{};
//     auto resultReg = execShuffle(typename TypeParam::IndexSequence{});
//     resultReg.store(result.data());
//
//     // Compare and assert the result.
//     for (size_t i = 0; i < Lanes; ++i)
//     {
//         EXPECT_ANY_EQ(expected[i], result[i]);
//     }
// }
//


/// @test Verifies that Simd128 can be constructed with variable arguments.
/// @note The Simd register expects integral args of datatype and since there is not direct static cast we need to use
///       a helper lambda that takes in a __VA_ARGS__ and static cast each element with parameter args.
    #define TEST_SIMD128_VARG_CTOR(TestNameSuffix, DataType, Lanes, ...)                                               \
        TEST(Simd128VarargsCtorTests, InitializesWith_##TestNameSuffix)                                                \
        {                                                                                                              \
            DataType inputData[]{ __VA_ARGS__ };                                                                       \
            constexpr size_t size = sizeof(inputData) / sizeof(DataType);                                              \
            DataType outputData[Lanes]{};                                                                              \
            auto getSimd = [](auto... args) {                                                                          \
                return falcon::Simd128_t<DataType, Lanes>{ static_cast<DataType>(args)... };                           \
            };                                                                                                         \
            falcon::Simd128_t<DataType, Lanes> reg = getSimd(__VA_ARGS__);                                             \
            reg.store(outputData);                                                                                     \
                                                                                                                       \
            for (size_t i = 0; i < size; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(inputData[i], outputData[i]);                                                            \
            }                                                                                                          \
        }


using namespace simd::testing;
// namespace
// {
//     #include <type_traits>
//
//     [[maybe_unused]] falcon::Simd128_t<uint64_t, 2> reg2{ 1ull, 2ull };
//     [[maybe_unused]] falcon::Simd128_t<uint64_t, 2> reg3{ 1ull, 2ull };
//     assert(std::is_same_v<decltype(reg2.naive()), __m128i>);
// } // namespace
//
// // Uint8_t
TEST_SIMD128_VARG_CTOR(Uint8_2Lanes_2Arguments, U8, 2, max<U8>, min<U8>)
TEST_SIMD128_VARG_CTOR(Uint8_4Lanes_2Arguments, U8, 4, max<U8>, min<U8>)
TEST_SIMD128_VARG_CTOR(Uint8_4Lanes_3Arguments, U8, 4, max<U8>, min<U8>, 64)
TEST_SIMD128_VARG_CTOR(Uint8_4Lanes_4Arguments, U8, 4, max<U8>, min<U8>, 64, 32)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_2Arguments, U8, 8, max<U8>, min<U8>)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_3Arguments, U8, 8, max<U8>, min<U8>, 64)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_4Arguments, U8, 8, max<U8>, min<U8>, 64, 32)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_5Arguments, U8, 8, max<U8>, min<U8>, 64, 32, 16)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_6Arguments, U8, 8, max<U8>, min<U8>, 64, 32, 16, 8)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_7Arguments, U8, 8, max<U8>, min<U8>, 64, 32, 16, 8, 4)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_8Arguments, U8, 8, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_2Arguments, U8, 16, max<U8>, min<U8>)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_3Arguments, U8, 16, max<U8>, min<U8>, 64)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_4Arguments, U8, 16, max<U8>, min<U8>, 64, 32)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_5Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_6Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_7Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_8Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_9Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_10Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_11Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_12Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 4)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_13Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_14Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6, 8)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_15Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6, 8, 15)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_16Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6, 8, 15, 17)
// Uint16_t
TEST_SIMD128_VARG_CTOR(Uint16_2Lanes_2Arguments, U16, 2, max<U16>, min<U16>)
TEST_SIMD128_VARG_CTOR(Uint16_4Lanes_2Arguments, U16, 4, max<U16>, min<U16>)
TEST_SIMD128_VARG_CTOR(Uint16_4Lanes_3Arguments, U16, 4, max<U16>, min<U16>, 64)
TEST_SIMD128_VARG_CTOR(Uint16_4Lanes_4Arguments, U16, 4, max<U16>, min<U16>, 64, 32)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_2Arguments, U16, 8, max<U16>, min<U16>)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_3Arguments, U16, 8, max<U16>, min<U16>, 64)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_4Arguments, U16, 8, max<U16>, min<U16>, 64, 32)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_5Arguments, U16, 8, max<U16>, min<U16>, 64, 32, 16)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_6Arguments, U16, 8, max<U16>, min<U16>, 64, 32, 16, 8)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_7Arguments, U16, 8, max<U16>, min<U16>, 64, 32, 16, 8, 4)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_8Arguments, U16, 8, max<U16>, min<U16>, 64, 32, 16, 8, 4, 2)
// Uint32_t
TEST_SIMD128_VARG_CTOR(Uint32_2Lanes_2Arguments, U32, 2, max<U32>, min<U32>)
TEST_SIMD128_VARG_CTOR(Uint32_4Lanes_2Arguments, U32, 4, max<U32>, min<U32>)
TEST_SIMD128_VARG_CTOR(Uint32_4Lanes_3Arguments, U32, 4, max<U32>, min<U32>, 64)
TEST_SIMD128_VARG_CTOR(Uint32_4Lanes_4Arguments, U32, 4, max<U32>, min<U32>, 64, 32)
// Uint64_t
TEST_SIMD128_VARG_CTOR(Uint64_2Lanes_2Arguments, U64, 2, max<U64>, min<U64>)

// Int8_t
TEST_SIMD128_VARG_CTOR(Int8_2Lanes_2Arguments, I8, 2, max<I8>, min<I8>)
TEST_SIMD128_VARG_CTOR(Int8_4Lanes_2Arguments, I8, 4, max<I8>, min<I8>)
TEST_SIMD128_VARG_CTOR(Int8_4Lanes_3Arguments, I8, 4, max<I8>, min<I8>, 64)
TEST_SIMD128_VARG_CTOR(Int8_4Lanes_4Arguments, I8, 4, max<I8>, min<I8>, 64, 32)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_2Arguments, I8, 8, max<I8>, min<I8>)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_3Arguments, I8, 8, max<I8>, min<I8>, 64)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_4Arguments, I8, 8, max<I8>, min<I8>, 64, 32)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_5Arguments, I8, 8, max<I8>, min<I8>, 64, 32, 16)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_6Arguments, I8, 8, max<I8>, min<I8>, 64, 32, 16, 8)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_7Arguments, I8, 8, max<I8>, min<I8>, 64, 32, 16, 8, 4)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_8Arguments, I8, 8, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_2Arguments, I8, 16, max<I8>, min<I8>)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_3Arguments, I8, 16, max<I8>, min<I8>, 64)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_4Arguments, I8, 16, max<I8>, min<I8>, 64, 32)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_5Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_6Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_7Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_8Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_9Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_10Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_11Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_12Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 4)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_13Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_14Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6, 8)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_15Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6, 8, 15)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_16Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6, 8, 15, 17)
// Int16_t
TEST_SIMD128_VARG_CTOR(Int16_2Lanes_2Arguments, I16, 2, max<I16>, min<I16>)
TEST_SIMD128_VARG_CTOR(Int16_4Lanes_2Arguments, I16, 4, max<I16>, min<I16>)
TEST_SIMD128_VARG_CTOR(Int16_4Lanes_3Arguments, I16, 4, max<I16>, min<I16>, 64)
TEST_SIMD128_VARG_CTOR(Int16_4Lanes_4Arguments, I16, 4, max<I16>, min<I16>, 64, 32)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_2Arguments, I16, 8, max<I16>, min<I16>)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_3Arguments, I16, 8, max<I16>, min<I16>, 64)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_4Arguments, I16, 8, max<I16>, min<I16>, 64, 32)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_5Arguments, I16, 8, max<I16>, min<I16>, 64, 32, 16)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_6Arguments, I16, 8, max<I16>, min<I16>, 64, 32, 16, 8)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_7Arguments, I16, 8, max<I16>, min<I16>, 64, 32, 16, 8, 4)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_8Arguments, I16, 8, max<I16>, min<I16>, 64, 32, 16, 8, 4, 2)
// Int32_t
TEST_SIMD128_VARG_CTOR(Int32_2Lanes_2Arguments, I32, 2, max<I32>, min<I32>)
TEST_SIMD128_VARG_CTOR(Int32_4Lanes_2Arguments, I32, 4, max<I32>, min<I32>)
TEST_SIMD128_VARG_CTOR(Int32_4Lanes_3Arguments, I32, 4, max<I32>, min<I32>, 64)
TEST_SIMD128_VARG_CTOR(Int32_4Lanes_4Arguments, I32, 4, max<I32>, min<I32>, 64, 32)
// Int64_t
TEST_SIMD128_VARG_CTOR(Int64_2Lanes_2Arguments, I64, 2, max<I64>, min<I64>)

// FP32
TEST_SIMD128_VARG_CTOR(FP32_2Lanes_2Arguments, FP32, 2, max<FP32>, min<FP32>)
TEST_SIMD128_VARG_CTOR(FP32_4Lanes_2Arguments, FP32, 4, max<FP32>, min<FP32>)
TEST_SIMD128_VARG_CTOR(FP32_4Lanes_3Arguments, FP32, 4, max<FP32>, min<FP32>, 64.1234f)
TEST_SIMD128_VARG_CTOR(FP32_4Lanes_4Arguments, FP32, 4, max<FP32>, min<FP32>, 64.1234f, 32.9899f)
// FP64
TEST_SIMD128_VARG_CTOR(FP64_2Lanes_2Arguments, FP64, 2, max<FP64>, min<FP64>)

// TODO: Add single argument broadcast test

#endif
/** @} */
