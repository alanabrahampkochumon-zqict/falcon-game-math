include_guard()

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

set(TEST_PROG_DIR "${PROJECT_SOURCE_DIR}/cmake/TestPrograms/")
set(TEST_COMPILE_DIR "${PROJECT_SOURCE_DIR}/cmake/TestPrograms/build/${CMAKE_CXX_COMPILER_ID}-${CMAKE_BUILD_TYPE}")


function(AddCompilerFlag Target Config)
    #--------------------------
    # AUTO SIMD FLAG DETECTION
    #--------------------------
    if (Config STREQUAL "AUTO")

        #----------------------------------------
        # SETUP COMPILER FLAGS FOR TEST PROGRAMS
        #----------------------------------------
        if (MSVC AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            set(TEST_FLAG_AVX512 "/arch:AVX512")
            set(TEST_FLAG_AVX2 "/arch:AVX2")
            set(TEST_FLAG_AVX "/arch:AVX")
            set(TEST_FLAG_SSE4 "")
            set(TEST_FLAG_SSE2 "")
        else ()
            # GCC / Clang / AppleClang
            set(TEST_FLAG_AVX512 "-mavx512f")
            set(TEST_FLAG_AVX2 "-mavx2")
            set(TEST_FLAG_AVX "-mavx")
            set(TEST_FLAG_SSE4 "-msse4.2")
            set(TEST_FLAG_SSE2 "-msse2")
        endif ()

        #-------------------
        # TEST PROGRAM RUNS
        #-------------------
        message(STATUS "Running AVX512 Tests")
        try_run(
                AVX512_RUNS
                AVX512_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/AVX512Test.cpp"
                CMAKE_FLAGS "-DCMAKE_CXX_STANDARD=17"
                COMPILE_OPTIONS ${TEST_FLAG_AVX512}
                RUN_OUTPUT_VARIABLE AVX512_COMPILER_OUTPUT
        )
        if (AVX512_RUNS EQUAL 0)
            message(STATUS "AVX512 detection success!")
        else ()
            message(STATUS "AVX512 detection failed!")
        endif ()

        # AVX10 Has to be manually enabled
        #            try_run(
        #                    AVX10_RUNS
        #                    AVX10_COMPILES
        #                    "${PROJECT_SOURCE_DIR}/TestPrograms/build"
        #                    "${TEST_PROG_DIR}/AVX10Test.cpp"
        #                    CMAKE_FLAGS "-DCMAKE_CXX_STANDARD=17"
        #                    RUN_OUTPUT_VARIABLE AVX10_COMPILER_OUTPUT
        #            )

        message(STATUS "Running AVX2 Tests")
        try_run(
                AVX2_RUNS
                AVX2_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/AVX2Test.cpp"
                CMAKE_FLAGS "-DCMAKE_CXX_STANDARD=17"
                COMPILE_OPTIONS ${TEST_FLAG_AVX2}
                RUN_OUTPUT_VARIABLE AVX2_COMPILER_OUTPUT
        )
        if (AVX2_RUNS EQUAL 0)
            message(STATUS "AVX2 detection success!")
        else ()
            message(STATUS "AVX2 detection failed!")
        endif ()

        message(STATUS "Running AVX Tests")
        try_run(
                AVX_RUNS
                AVX_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/AVXTest.cpp"
                CMAKE_FLAGS "-DCMAKE_CXX_STANDARD=17"
                COMPILE_OPTIONS ${TEST_FLAG_AVX}
                RUN_OUTPUT_VARIABLE AVX_COMPILER_OUTPUT
        )
        if (AVX_RUNS EQUAL 0)
            message(STATUS "AVX detection success!")
        else ()
            message(STATUS "AVX detection failed!")
        endif ()

        message(STATUS "Running SSE4 Tests")
        try_run(
                SSE4_RUNS
                SSE4_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/SSE4Test.cpp"
                CMAKE_FLAGS "-DCMAKE_CXX_STANDARD=17"
                COMPILE_OPTIONS ${TEST_FLAG_SSE4}
                RUN_OUTPUT_VARIABLE SSE4_COMPILER_OUTPUT
        )
        if (SSE4_RUNS EQUAL 0)
            message(STATUS "SSE4 detection success!")
        else ()
            message(STATUS "SSE4 detection failed!")
        endif ()

        message(STATUS "Running SSE2 Tests")
        try_run(
                SSE2_RUNS
                SSE2_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/SSETest.cpp"
                CMAKE_FLAGS "-DCMAKE_CXX_STANDARD=17"
                COMPILE_OPTIONS ${TEST_FLAG_SSE2}
                RUN_OUTPUT_VARIABLE SSE2_COMPILER_OUTPUT
        )
        if (SSE2_RUNS EQUAL 0)
            message(STATUS "SSE2 detection success!")
        else ()
            message(STATUS "SSE2 detection failed!")
        endif ()

        message(STATUS "Running ARM Neon Tests")
        try_run(
                NEON_RUNS
                NEON_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/NeonTest.cpp"
                CMAKE_FLAGS "-DCMAKE_CXX_STANDARD=17"
                RUN_OUTPUT_VARIABLE NEON_COMPILER_OUTPUT
        )
        if (NEON_RUNS EQUAL 0)
            message(STATUS "Neon detection success!")
        else ()
            message(STATUS "Neon detection failed!")
        endif ()


        #-----------------------------------------------
        # CONFIGURING CONFIG FLAG BASED ON PROGRAM RUNS
        #-----------------------------------------------
        if (AVX512_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_AVX512)
            #        elseif (AVX10_RUNS)
            #            set(Config FALCON_ENABLE_AVX10)
        elseif (AVX2_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_AVX2)
        elseif (AVX_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_AVX)
        elseif (SSE4_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_SSE4)
        elseif (SSE2_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_SSE2)
        elseif (NEON_RUNS EQUAL 0)
            set(Config FALCON_ENABLE_NEON)
        else ()
            set(Config FALCON_DISABLE_SIMD)
        endif ()
    endif ()


    #----------------------
    # SETUP COMPILER FLAGS
    #----------------------
    if (Config STREQUAL "FALCON_ENABLE_AVX512")
        set(MSVCCompilerFlag "/arch:AVX512")
        set(CompilerFlag "-mavx512f")
        message(STATUS "Turned on AVX512")
    elseif (Config STREQUAL "FALCON_ENABLE_AVX10")
        set(MSVCCompilerFlag "/arch:AVX10.1")
        set(CompilerFlag "-mavx10.1")
        message(STATUS "Turned on AVX10")
    elseif (Config STREQUAL "FALCON_ENABLE_AVX2")
        set(MSVCCompilerFlag "/arch:AVX2")
        set(CompilerFlag "-mavx2")
        message(STATUS "Turned on AVX2")
    elseif (Config STREQUAL "FALCON_ENABLE_AVX")
        set(MSVCCompilerFlag "/arch:AVX")
        set(CompilerFlag "-mavx")
        message(STATUS "Turned on AVX")
    elseif (Config STREQUAL "FALCON_ENABLE_SSE4")
        check_cxx_compiler_flag("/arch:SSE4.2" COMPILER_SUPPORTS_SSE4)
        if (COMPILER_SUPPORTS_SSE4)
            list(APPEND CompilerFlags "/arch:SSE4.2")
        else ()
            list(APPEND CompilerFlags "/arch:AVX")
        endif ()
        set(CompilerFlag "-msse4.2")
        message(STATUS "Turned on SSE4.2")
    elseif (Config STREQUAL "FALCON_ENABLE_SSE2")
        set(MSVCCompilerFlag "/arch:SSE2")
        set(CompilerFlag "-msse2")
        message(STATUS "Turned on SSE2")
    elseif (Config STREQUAL "FALCON_ENABLE_NEON")
        # AARCH64 comes with Neon Mandatory so need to switch flags
        message(STATUS "Turned on ARM Neon")
    elseif (Config STREQUAL "FALCON_DISABLE_SIMD")
        message(STATUS "SIMD is disabled.")
    else ()
        message(WARNING "Unsupported SIMD Flag. Refer docs for supported flags, or use 'AUTO' for automatically detecting based on system.")
        return() # Returning so that the flag will not get added!
    endif ()


    #-------------------------
    # INJECT FLAGS AND MACROS
    #-------------------------

    if (MSVC AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(${Target} PUBLIC ${MSVCCompilerFlag})
    else ()
        target_compile_options(${Target} PUBLIC ${CompilerFlag})
    endif ()
    target_compile_definitions(${Target} PUBLIC ${Config})
endfunction()


function(AddSIMDCompilerFlag Target)
    string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" SYSTEM_ARCH)

    # Arm
    if (SYSTEM_ARCH MATCHES "arm|aarch64")
        message(STATUS "Detected ARM Architecture. Enabling NEON...")
        return()
    endif ()

    if (NOT SYSTEM_ARCH MATCHES "x86_64|amd64|i386|i686")
        message(WARNING "Unknown Architecture: ${SYSTEM_ARCH}. Disabling SIMD.")
        return()
    endif ()

    message(CHECK_START "Running x86 SIMD checks for ${CPU_NAME}")

    set(ProgramNames "SIMD_AVX512_PROG;SIMD_AVX2_PROG;SIMD_AVX_PROG;SIMD_SSE_PROG")
    set(Architectures "AVX-512;AVX2;AVX;SSE")

    if (MSVC)
        check_cxx_compiler_flag("/arch:SSE2" COMPILER_SUPPORTS_SSE)
        set(CompilerFlags "/arch:AVX512;/arch:AVX2;/arch:AVX")
        if (COMPILER_SUPPORTS_SSE)
            list(APPEND CompilerFlags "/arch:SSE2")
        else ()
            list(APPEND CompilerFlags " ")
        endif ()
    else ()
        set(CompilerFlags "-mavx512f;-mavx2;-mavx;-msse4.2")
    endif ()

    set(SIMDSupported False)
    foreach (i RANGE 3)
        list(GET CompilerFlags ${i} Flag)
        list(GET ProgramNames ${i} ProgName)
        list(GET Architectures ${i} Arch)
        set(Program "${${ProgName}}")

        set(CMAKE_REQUIRED_FLAGS ${Flag})
        message(STATUS "Running checks for ${Arch}...")
        check_cxx_source_runs("${Program}" HAS_${Arch})
        unset(CMAKE_REQUIRED_FLAGS)

        if (HAS_${Arch})
            target_compile_options(
                    ${Target} PRIVATE ${Flag}
            )
            message(CHECK_PASS "${CPU_NAME} supports ${Arch}. Enabling ${Arch}...")
            set(SIMDSupported True)
            break()
        endif ()
    endforeach ()
    if (NOT (SIMDSupported))
        message(CHECK_FAIL "${CPU_NAME} doesn't support SIMD instruction set")
    endif ()
endfunction(AddSIMDCompilerFlag)