cmake_host_system_information(
    RESULT CPU_NAME
    QUERY PROCESSOR_NAME
)

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

set(SIMD_AVX2_PROG "
    #include <immintrin.h>

    int main() {
        __m256i data = _mm256_setzero_si256();
        __m256i result = _mm256_abs_epi32(data); // AVX2 specific intrinsic for calculating absolute value of integers
        (void)result;
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

include(CheckCXXSourceRuns)
include(CheckCXXCompilerFlag)

function(AddSIMDCompilerFlag Target)
    message(STATUS "Running SIMD checks for ${CPU_NAME}")

    set(ProgramNames "SIMD_AVX512_PROG;SIMD_AVX2_PROG;SIMD_AVX_PROG;SIMD_SSE_PROG")
    set(Architectures "AVX-512;AVX2;AVX;SSE")

    if (MSVC)
        check_cxx_compiler_flag("/arch:SSE2" COMPILER_SUPPORTS_SSE)
        set(CompilerFlags "/arch:AVX512;/arch:AVX2;/arch:AVX")
        if (COMPILER_SUPPORTS_SSE)
            list(APPEND CompilerFlags "/arch:SSE2")
        else()
            list(APPEND CompilerFlags " ")
        endif()
    else()
        set(CompilerFlags "-mavx512f;-mavx2;-mavx;-msse4.2")
    endif()

    set(SIMDSupported False)
    foreach(i RANGE 3)
        list(GET CompilerFlags ${i} Flag)
        list(GET ProgramNames ${i} ProgName)
        list(GET Architectures ${i} Arch)
        set(Program "${${ProgName}}")

        set(CMAKE_REQUIRED_FLAGS ${Flag})
            message("Running checks for ${Arch}...")
            check_cxx_source_runs("${Program}" HAS_${Arch})
        unset(CMAKE_REQUIRED_FLAGS)

        if(HAS_${Arch})
            target_compile_options(
                ${Target} PRIVATE ${Flag}
            )
            message(STATUS "${CPU_NAME} supports ${Arch}. Enabling ${Arch}...")
            set(SIMDSupported True)
            break()
        endif()
    endforeach()
    if(NOT(SIMDSupported))
        message(WARN "${CPU_NAME} doesn't support SIMD instruction set")
    endif()
endfunction(AddSIMDCompilerFlag)