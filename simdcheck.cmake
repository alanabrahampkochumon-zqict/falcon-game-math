set(SIMD_AVX512_PROG "
    #include <immintrin.h>

    int main()
    {
        float data[16] = {0};
        __m512 a = _mm512_setzero_ps();
        _mm512_storeu_ps(data, a);
        return 0;
    }
")

set(SIMD_AVX_PROG "
    #include <immintrin.h>

    int main()
    {
        float data[8] = {0};
        __m256 a = _mm256_setzero_ps();
        _mm256_storeu_ps(data, a);
        return 0;
    }
")

set(SIMD_SSE_PROG "
    #include <xmmintrin.h>

    int main()
    {
        float data[4] = {0};
        __m128 a = _mm_setzero_ps();
        _mm_storeu_ps(data, a);
        return 0;
    }
")

# TODO: Change to use include(CheckCXXSourceRuns)
include(CheckCXXCompilerFlag)

function (AddSIMDCompilerFlag Target)
    if(MSVC)
        check_cxx_compiler_flag("/arch:AVX" HAS_AVX_SUPPORT)
        check_cxx_compiler_flag("/arch:AVX2" HAS_AVX2_SUPPORT)
        check_cxx_compiler_flag("/arch:AVX512" HAS_AVX512_SUPPORT)

        if(HAS_AVX512_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "/arch:AVX512"
            )
            message(STATUS "Enabled AVX512")
        elseif(HAS_AVX2_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "/arch:AVX2"
            )
            message(STATUS "Enabled AVX2")
        elseif(HAS_AVX_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "/arch:AVX"
            )
            message(STATUS "Enabled AVX")
        elseif(HAS_SSE_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "/arch:SSE"
            )
            message(STATUS "Enabling SSE...")
        else()
            message(STATUS "CPU doesn't support SIMD instruction set")
        endif()
    else()
        check_cxx_compiler_flag("-msse4.1" HAS_SSE_SUPPORT)
        check_cxx_compiler_flag("-mavx" HAS_AVX_SUPPORT)
        check_cxx_compiler_flag("-mavx2" HAS_AVX2_SUPPORT)
        check_cxx_compiler_flag("-mavx512f" HAS_AVX512_SUPPORT)

        if(HAS_AVX512_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "-mavx512f"
            )
            message(STATUS "Enabled AVX512")
        elseif(HAS_AVX2_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "-mavx2"
            )
            message(STATUS "Enabled AVX2")
        elseif(HAS_AVX_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "-mavx"
            )
            message(STATUS "Enabled AVX")
        elseif(HAS_SSE_SUPPORT)
            target_compile_options(
                ${Target} PRIVATE "-msse4.1"
            )
            message(STATUS "Enabling SSE...")
        else()
            message(STATUS "CPU doesn't support SIMD instruction set")
        endif()
    endif()
endfunction(AddSIMDCompilerFlag)

