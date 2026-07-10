/**
 * @file AVX2Test.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 10, 2026
 *
 * @brief Test program for verifying AVX2 support.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <immintrin.h>

int main() {
    const __m256i data = _mm256_setzero_si256();
    const __m256i result = _mm256_abs_epi32(data); // AVX2 specific intrinsic for calculating absolute value of integers
    (void)result;
    return 0;
}