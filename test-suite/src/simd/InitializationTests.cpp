// #include <SIMD.h>
// #include <gtest/gtest.h>
//
// struct ScalarBackend
//{
// };
// struct SSEBackend
//{
// };
// struct AVXBackend
//{
// };
// struct AVX2Backend
//{
// };
// struct AVX512Backend
//{
// };
//
//// 2. A mock version of what your SIMD.h wrapper functions might look like.
//// You specialize these templates so the test can call them uniformly.
// template <typename Backend>
// void SimdSetZero(float* out);
// template <typename Backend>
// void SimdBroadcast(float* out, float val);
//
//// --- SCALAR IMPLEMENTATIONS ---
// template <>
// void SimdSetZero<ScalarBackend>(float* out)
//{
//     for (int i = 0; i < 8; ++i)
//         out[i] = 0.0f;
// }
// template <>
// void SimdBroadcast<ScalarBackend>(float* out, float val)
//{
//     for (int i = 0; i < 8; ++i)
//         out[i] = val;
// }
//
//// --- AVX2 IMPLEMENTATIONS ---
// template <>
// void SimdSetZero<AVX2Backend>(float* out)
//{
//     __m256 vec = _mm256_setzero_ps();
//     _mm256_storeu_ps(out, vec); // storeu = unaligned store (safe for testing)
// }
// template <>
// void SimdBroadcast<AVX2Backend>(float* out, float val)
//{
//     __m256 vec = _mm256_set1_ps(val);
//     _mm256_storeu_ps(out, vec);
// }
//
//// 3. The Test Fixture
// template <typename BackendType>
// class SimdInitTest: public ::testing::Test
//{
//     protected:
//     // 32-byte aligned array to hold 8 floats safely
//     alignas(32) float data[8];
//
//     void SetUp() override
//     {
//         // Fill with garbage data before each test to ensure our SIMD actually overwrites it
//         for (int i = 0; i < 8; ++i)
//             data[i] = -999.0f;
//     }
// };
//
//// 4. Register the types you want to test
// using SimdBackends = ::testing::Types<ScalarBackend, AVX2Backend>;
// TYPED_TEST_SUITE(SimdInitTest, SimdBackends);
//
//// 5. The Tests!
// TYPED_TEST(SimdInitTest, SetsAllLanesToZero)
//{
//     // Call the function using the current backend type
//     SimdSetZero<TypeParam>(this->data);
//
//     for (int i = 0; i < 8; ++i)
//     {
//         EXPECT_FLOAT_EQ(this->data[i], 0.0f);
//     }
// }
//
// TYPED_TEST(SimdInitTest, BroadcastsSingleValueToAllLanes)
//{
//     float test_val = 42.5f;
//     SimdBroadcast<TypeParam>(this->data, test_val);
//
//     for (int i = 0; i < 8; ++i)
//     {
//         EXPECT_FLOAT_EQ(this->data[i], test_val);
//     }
// }
