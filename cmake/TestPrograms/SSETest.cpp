/**
 * @file SSETest.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 10, 2026
 *
 * @brief Test program for verifying SSE support.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <xmmintrin.h>

int main()
{
    float data[4] = {0};
    const __m128 a = _mm_setzero_ps();
    _mm_storeu_ps(data, a);
    return 0;
}