#pragma once

#include <cstddef>
#include <immintrin.h>
#include <zmmintrin.h>

/*************************************
 *                                   *
 *            PREPROCESSORS          *
 *                                   *
 *************************************/
 /**
  * Defining FORCE_SSE will turn on SSE_4_1 even if the hardware supports newer instruction set
  * Similar MACROS are FORCE_AVX, FORCE_AVX2, FORCE_AVX512, and FORCE_SCALAR which will turn off SIMD.
  * Although you will be able to see the defined macros, all functions and register types will not be available or substituted with stubs.
  */

#if defined(FORCE_AVX512) && defined(__AVX512F__)
	#define FALCON_AVX512_SUPPORTED
#endif

#if (defined(FORCE_AVX2) && defined(__AVX2__)) || defined(FALCON_AVX512_SUPPORTED)
	#define FALCON_AVX2_SUPPORTED
#endif

#if (defined(FORCE_AVX) && defined(__AVX__)) || defined(FALCON_AVX2_SUPPORTED)
	#define FALCON_AVX_SUPPORTED
#endif

#if (defined(FORCE_SSE) && (defined(__SSE__) || defined(__SSE4_1__) || defined(_M_X64))) || defined(FALCON_AVX_SUPPORTED)
	#define FALCON_SSE_SUPPORTED
#endif

#if !(defined(FORCE_SCALAR)) && defined(FALCON_SSE_SUPPORTED)
	#define FALCON_SIMD_SUPPORTED
#endif

/**
 * Macros will be turned on by system support, if no force command is supplied.
 * Make sure compiler flags are turned on:
 * -mavx2 (GCC/Clang) or /arch:AVX2(MSVC) for turning on AVX2 support
 * -mavx512 (GCC/Clang) or /arch:AVX512 (MSVC) for turning on AVX512 supported.
 */
#if !defined(FORCE_AVX512) && !defined(FORCE_AVX2) && !defined(FORCE_AVX) && !defined(FORCE_SSE) && !defined(FORCE_SCALAR)
	#ifdef __AVX512F__
		#define FALCON_AVX512_SUPPORTED
	#endif

	#ifdef __AVX2__
		#define FALCON_AVX2_SUPPORTED
	#endif

	#ifdef __AVX__
		#define FALCON_AVX_SUPPORTED
	#endif

	#if defined(__SSE__) || defined(__SSE4_1__) || defined(_M_X64)
		#define FALCON_SSE_SUPPORTED
		#define FALCON_SIMD_SUPPORTED // If at least SSE is supported, then SIMD will be available.
	#endif
#endif

namespace falcon::simd
{
	template <typename T>
	struct SIMDReg {};

	template<> struct SIMDReg<int>
	{	
		#if defined(FALCON_AVX512_SUPPORTED)
			using reg = __m512i;
		#elif defined(FALCON_AVX2_SUPPORTED) || defined(FALCON_AVX_SUPPORTED)
			using reg = __m256i;
		elif defined(FALCON_SSE_SUPPORTED)
			using reg = __m128i;
		else
			using reg = {};
		#endif
	};


}