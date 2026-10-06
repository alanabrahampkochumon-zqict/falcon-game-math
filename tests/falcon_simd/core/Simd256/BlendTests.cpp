/**
 * @file BlendTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: October 06, 2026
 *
 * @brief Verifies Simd256 blending operations.
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
 * @addtogroup T_SIMD256_Shuffle
 * @{
 */

namespace
{
    using namespace simd::testing;

    // Test param to pass in a combination matrix for testing blend function.
    // since gtest doesn't natively support parameterized typed test(where you can pass in parameters against a type
    // vector)
    template <typename T, size_t Lanes, Array<T, Lanes> first, Array<T, Lanes> second, Array<T, Lanes> mask,
              Array<T, Lanes> expected>
    struct Simd256BlendTestParam
    {
        using Type                            = T;
        static constexpr size_t REGISTER_SIZE = 256;
        static constexpr size_t LaneCount     = Lanes;
        static constexpr auto First           = first;
        static constexpr auto Second          = second;
        static constexpr auto Mask            = mask;
        static constexpr auto Expected        = expected;
        const char* TypeName                  = typeid(Type).name();

        // TODO: Fix pretty function not being used.
        friend std::ostream& operator<<(std::ostream& os, const Simd256BlendTestParam& param)
        { return os << "Simd256BlendTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }

        // friend void PrintTo(const Simd256BlendTestParam& param, std::ostream* os)
        // { *os << "Simd256BlendTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }
    };

    // clang-format off
    using Simd256BlendTestTypeHints = testing::Types<
        // Unsigned types
        // Uint8t
        Simd256BlendTestParam<
            U8, 32,
            Array<U8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
            Array<U8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
            Array<U8, 32>{
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<U8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 }
        >,
        Simd256BlendTestParam<
            U8, 32,
            Array<U8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
            Array<U8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
            Array<U8, 32>{
                ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>,
                ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>
            },
            Array<U8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 }
        >,
        Simd256BlendTestParam<
            U8, 32,
            Array<U8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
            Array<U8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
            Array<U8, 32>{
                ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0,
                ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0
            },
            Array<U8, 32>{ 107, 14, 5, 47, 97, 38, 28, 40, 87, 73, 127, 24, 62, 40, 65, 21, 10, 43, 87, 29, 88, 28, 96, 110, 60, 26, 74, 30, 76, 67, 74, 113 }
        >,
        Simd256BlendTestParam<
                U8, 32,
                Array<U8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
                Array<U8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
                Array<U8, 32>{
                    0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>,
                    0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>,
                },
                Array<U8, 32>{ 105, 43, 68, 57, 127, 118, 32, 4, 117, 8, 19, 2, 85, 126, 59, 71, 39, 86, 16, 79, 94, 66, 69, 2, 58, 76, 7, 32, 89, 93, 1, 105 }
        >,

        // Uint16t
        Simd256BlendTestParam<
            U16, 16,
            Array<U16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
            Array<U16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 },
            Array<U16, 16>{
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<U16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 }
        >,
        Simd256BlendTestParam<
            U16, 16,
            Array<U16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
            Array<U16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71},
            Array<U16, 16>{
                ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>
            },
            Array<U16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 }
        >,
        Simd256BlendTestParam<
            U16, 16,
            Array<U16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
            Array<U16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 },
            Array<U16, 16>{
                ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0
            },
            Array<U16, 16>{ 107, 14, 5, 47, 97, 38, 28, 40, 87, 73, 127, 24, 62, 40, 65, 21 }
        >,
        Simd256BlendTestParam<
                U16, 16,
                Array<U16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
                Array<U16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 },
                Array<U16, 16>{
                    0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>
                },
                Array<U16, 16>{ 105, 43, 68, 57, 127, 118, 32, 4, 117, 8, 19, 2, 85, 126, 59, 71 }
        >,

        // Uint32t
        Simd256BlendTestParam<
            U32, 8,
            Array<U32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<U32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<U32, 8>{
                0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<U32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 }
        >,
        Simd256BlendTestParam<
            U32, 8,
            Array<U32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<U32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<U32, 8>{
                ONE<U32>, ONE<U32>, ONE<U32>, ONE<U32>, ONE<U32>, ONE<U32>, ONE<U32>, ONE<U32>
            },
            Array<U32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 }
        >,
        Simd256BlendTestParam<
            U32, 8,
            Array<U32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<U32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<U32, 8>{
                ONE<U32>, 0, ONE<U32>, 0, ONE<U32>, 0, ONE<U32>, 0
            },
            Array<U32, 8>{ 107, 14, 5, 47, 97, 38, 28, 40 }
        >,
        Simd256BlendTestParam<
                U32, 8,
                Array<U32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
                Array<U32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
                Array<U32, 8>{
                    0, ONE<U32>, 0, ONE<U32>, 0, ONE<U32>, 0, ONE<U32>
                },
                Array<U32, 8>{ 105, 43, 68, 57, 127, 118, 32, 4 }
        >,

        // Uint64t
        Simd256BlendTestParam<
            U64, 4,
            Array<U64, 4>{ 105, 14, 64, 47 },
            Array<U64, 4>{ 107, 43, 5, 57 },
            Array<U64, 4>{ 0, 0, 0, 0 },
            Array<U64, 4>{ 105, 14, 64, 47 }
        >,
        Simd256BlendTestParam<
            U64, 4,
            Array<U64, 4>{ 105, 14, 64, 47 },
            Array<U64, 4>{ 107, 43, 5, 57 },
            Array<U64, 4>{ ONE<U64>, ONE<U64>, ONE<U64>, ONE<U64> },
            Array<U64, 4>{ 107, 43, 5, 57 }
        >,
        Simd256BlendTestParam<
            U64, 4,
            Array<U64, 4>{ 105, 14, 64, 47 },
            Array<U64, 4>{ 107, 43, 5, 57 },
            Array<U64, 4>{ ONE<U64>, 0, ONE<U64>, 0 },
            Array<U64, 4>{ 107, 14, 5, 47 }
        >,
        Simd256BlendTestParam<
                U64, 4,
                Array<U64, 4>{ 105, 14, 64, 47 },
                Array<U64, 4>{ 107, 43, 5, 57 },
                Array<U64, 4>{ 0, ONE<U64>, 0, ONE<U64> },
                Array<U64, 4>{ 105, 43, 64, 57 }
        >,

        // Signed types
        // Int8t
        Simd256BlendTestParam<
            I8, 32,
            Array<I8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
            Array<I8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
            Array<I8, 32>{
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<I8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 }
        >,
        Simd256BlendTestParam<
            I8, 32,
            Array<I8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
            Array<I8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
            Array<I8, 32>{
                ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>,
                ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>
            },
            Array<I8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 }
        >,
        Simd256BlendTestParam<
            I8, 32,
            Array<I8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
            Array<I8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
            Array<I8, 32>{
                ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0,
                ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0
            },
            Array<I8, 32>{ 107, 14, 5, 47, 97, 38, 28, 40, 87, 73, 127, 24, 62, 40, 65, 21, 10, 43, 87, 29, 88, 28, 96, 110, 60, 26, 74, 30, 76, 67, 74, 113 }
        >,
        Simd256BlendTestParam<
                I8, 32,
                Array<I8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
                Array<I8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
                Array<I8, 32>{
                    0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>,
                    0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>,
                },
                Array<I8, 32>{ 105, 43, 68, 57, 127, 118, 32, 4, 117, 8, 19, 2, 85, 126, 59, 71, 39, 86, 16, 79, 94, 66, 69, 2, 58, 76, 7, 32, 89, 93, 1, 105 }
        >,

        // Int16t
        Simd256BlendTestParam<
            I16, 16,
            Array<I16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
            Array<I16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 },
            Array<I16, 16>{
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<I16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 }
        >,
        Simd256BlendTestParam<
            I16, 16,
            Array<I16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
            Array<I16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71},
            Array<I16, 16>{
                ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>
            },
            Array<I16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 }
        >,
        Simd256BlendTestParam<
            I16, 16,
            Array<I16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
            Array<I16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 },
            Array<I16, 16>{
                ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0
            },
            Array<I16, 16>{ 107, 14, 5, 47, 97, 38, 28, 40, 87, 73, 127, 24, 62, 40, 65, 21 }
        >,
        Simd256BlendTestParam<
                I16, 16,
                Array<I16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
                Array<I16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 },
                Array<I16, 16>{
                    0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>
                },
                Array<I16, 16>{ 105, 43, 68, 57, 127, 118, 32, 4, 117, 8, 19, 2, 85, 126, 59, 71 }
        >,

        // Int32t
        Simd256BlendTestParam<
            I32, 8,
            Array<I32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<I32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<I32, 8>{
                0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<I32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 }
        >,
        Simd256BlendTestParam<
            I32, 8,
            Array<I32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<I32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<I32, 8>{
                ONE<I32>, ONE<I32>, ONE<I32>, ONE<I32>, ONE<I32>, ONE<I32>, ONE<I32>, ONE<I32>
            },
            Array<I32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 }
        >,
        Simd256BlendTestParam<
            I32, 8,
            Array<I32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<I32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<I32, 8>{
                ONE<I32>, 0, ONE<I32>, 0, ONE<I32>, 0, ONE<I32>, 0
            },
            Array<I32, 8>{ 107, 14, 5, 47, 97, 38, 28, 40 }
        >,
        Simd256BlendTestParam<
                I32, 8,
                Array<I32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
                Array<I32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
                Array<I32, 8>{
                    0, ONE<I32>, 0, ONE<I32>, 0, ONE<I32>, 0, ONE<I32>
                },
                Array<I32, 8>{ 105, 43, 68, 57, 127, 118, 32, 4 }
        >,

        // Int64t
        Simd256BlendTestParam<
            I64, 4,
            Array<I64, 4>{ 105, 14, 64, 47 },
            Array<I64, 4>{ 107, 43, 5, 57 },
            Array<I64, 4>{ 0, 0, 0, 0 },
            Array<I64, 4>{ 105, 14, 64, 47 }
        >,
        Simd256BlendTestParam<
            I64, 4,
            Array<I64, 4>{ 105, 14, 64, 47 },
            Array<I64, 4>{ 107, 43, 5, 57 },
            Array<I64, 4>{ ONE<I64>, ONE<I64>, ONE<I64>, ONE<I64> },
            Array<I64, 4>{ 107, 43, 5, 57 }
        >,
        Simd256BlendTestParam<
            I64, 4,
            Array<I64, 4>{ 105, 14, 64, 47 },
            Array<I64, 4>{ 107, 43, 5, 57 },
            Array<I64, 4>{ ONE<I64>, 0, ONE<I64>, 0 },
            Array<I64, 4>{ 107, 14, 5, 47 }
        >,
        Simd256BlendTestParam<
                I64, 4,
                Array<I64, 4>{ 105, 14, 64, 47 },
                Array<I64, 4>{ 107, 43, 5, 57 },
                Array<I64, 4>{ 0, ONE<I64>, 0, ONE<I64> },
                Array<I64, 4>{ 105, 43, 64, 57 }
        >,

        // Floating point types
        // FP32
        Simd256BlendTestParam<
            FP32, 8,
            Array<FP32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<FP32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<FP32, 8>{
                0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<FP32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 }
        >,
        Simd256BlendTestParam<
            FP32, 8,
            Array<FP32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<FP32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<FP32, 8>{
                ONE<FP32>, ONE<FP32>, ONE<FP32>, ONE<FP32>, ONE<FP32>, ONE<FP32>, ONE<FP32>, ONE<FP32>
            },
            Array<FP32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 }
        >,
        Simd256BlendTestParam<
            FP32, 8,
            Array<FP32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<FP32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<FP32, 8>{
                ONE<FP32>, 0, ONE<FP32>, 0, ONE<FP32>, 0, ONE<FP32>, 0
            },
            Array<FP32, 8>{ 107, 14, 5, 47, 97, 38, 28, 40 }
        >,
        Simd256BlendTestParam<
                FP32, 8,
                Array<FP32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
                Array<FP32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
                Array<FP32, 8>{
                    0, ONE<FP32>, 0, ONE<FP32>, 0, ONE<FP32>, 0, ONE<FP32>
                },
                Array<FP32, 8>{ 105, 43, 68, 57, 127, 118, 32, 4 }
        >,

        // FP64
        Simd256BlendTestParam<
            FP64, 4,
            Array<FP64, 4>{ 105, 14, 64, 47 },
            Array<FP64, 4>{ 107, 43, 5, 57 },
            Array<FP64, 4>{ 0, 0, 0, 0 },
            Array<FP64, 4>{ 105, 14, 64, 47 }
        >,
        Simd256BlendTestParam<
            FP64, 4,
            Array<FP64, 4>{ 105, 14, 64, 47 },
            Array<FP64, 4>{ 107, 43, 5, 57 },
            Array<FP64, 4>{ ONE<FP64>, ONE<FP64>, ONE<FP64>, ONE<FP64> },
            Array<FP64, 4>{ 107, 43, 5, 57 }
        >,
        Simd256BlendTestParam<
            FP64, 4,
            Array<FP64, 4>{ 105, 14, 64, 47 },
            Array<FP64, 4>{ 107, 43, 5, 57 },
            Array<FP64, 4>{ ONE<FP64>, 0, ONE<FP64>, 0 },
            Array<FP64, 4>{ 107, 14, 5, 47 }
        >,
        Simd256BlendTestParam<
                FP64, 4,
                Array<FP64, 4>{ 105, 14, 64, 47 },
                Array<FP64, 4>{ 107, 43, 5, 57 },
                Array<FP64, 4>{ 0, ONE<FP64>, 0, ONE<FP64> },
                Array<FP64, 4>{ 105, 43, 64, 57 }
        >
    >;
    // clang-format on


    /// @brief Test fixture for Simd256 blending operations.
    template <typename>
    class Simd256BlendTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd256BlendTests, Simd256BlendTestTypeHints);

} // namespace


TYPED_TEST(Simd256BlendTests, BlendingWithMaskReturnsRegisterWithCorrectValues)
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
    falcon::Simd256_t<Type, Lanes> regA{}, regB{}, mask{};
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

// TODO: Add const blend
// TODO: Add internal make blendmask32

/** @} */

#endif
