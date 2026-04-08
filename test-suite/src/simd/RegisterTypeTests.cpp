/**
 * @file RegisterTypeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 10, 2026
 *
 * @brief Verifies @ref falcon::simd::RegisterMap correctly maps register depending on the data type and size(bytes).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
class RegisterMapTest: public ::testing::Test
{};
TYPED_TEST_SUITE(RegisterMapTest, SupportedSIMDIntegralTypes);



/**
 * @addtogroup T_Reg_Type
 * @{
 */

/** @brief Verify that the `float` @ref falcon::simd::RegisterMap maps to correct SIMD register. */
TEST(RegisterMapTest, FloatMapsToCorrectSIMDIntrinsics)
{
    // Float with alignment of 16 correctly maps to __m128
    ::testing::StaticAssertTypeEq<falcon::simd::RegisterMap<float, 16>::type, __m128>();

    // Float with alignment of 32 correctly maps to __m256
    ::testing::StaticAssertTypeEq<falcon::simd::RegisterMap<float, 32>::type, __m256>();

    // Float with alignment of 64 correctly maps to __m512
    ::testing::StaticAssertTypeEq<falcon::simd::RegisterMap<float, 64>::type, __m512>();
}


/** @brief Verify that the `double` @ref falcon::simd::RegisterMap maps to correct SIMD register. */
TEST(RegisterMapTest, DoubleMapsToCorrectSIMDIntrinsics)
{
    // Double with alignment of 16 correctly maps to __m128
    ::testing::StaticAssertTypeEq<falcon::simd::RegisterMap<double, 16>::type, __m128d>();

    // Double with alignment of 32 correctly maps to __m256
    ::testing::StaticAssertTypeEq<falcon::simd::RegisterMap<double, 32>::type, __m256d>();

    // Double with alignment of 64 correctly maps to __m512
    ::testing::StaticAssertTypeEq<falcon::simd::RegisterMap<double, 64>::type, __m512d>();
}


/** @brief Verify that `integral` @ref falcon::simd::RegisterMap maps to correct SIMD register. */
TYPED_TEST(RegisterMapTest, IntegralsMapToCorrectSIMDIntrinsics)
{
    // Double with alignment of 16 correctly maps to __m128
    ::testing::StaticAssertTypeEq<typename falcon::simd::RegisterMap<TypeParam, 16>::type, __m128i>();

    // Double with alignment of 32 correctly maps to __m256
    ::testing::StaticAssertTypeEq<typename falcon::simd::RegisterMap<TypeParam, 32>::type, __m256i>();

    // Double with alignment of 64 correctly maps to __m512
    ::testing::StaticAssertTypeEq<typename falcon::simd::RegisterMap<TypeParam, 64>::type, __m512i>();
}

/** @} */