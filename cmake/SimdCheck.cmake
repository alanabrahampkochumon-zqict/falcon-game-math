include_guard()

include(CheckCXXSourceRuns)
include(CheckCXXCompilerFlag)

set(TEST_PROG_DIR "${PROJECT_SOURCE_DIR}/cmake/TestPrograms/")
string(RANDOM RANDOM_STR) # Random Suffix is required since the program same config like Clang-Debug LHS may try to access the same variable
set(TEST_COMPILE_DIR "${PROJECT_SOURCE_DIR}/cmake/TestPrograms/build/${CMAKE_CXX_COMPILER_ID}-${CMAKE_BUILD_TYPE}-${RANDOM_STR}")

function(AddCompilerFlag Target Config)
    #--------------------------
    # AUTO SIMD FLAG DETECTION
    #--------------------------
    message(STATUS "COMPILER: ${CMAKE_CXX_COMPILER_ID} MSVC FLAG: ${MSVC}")
    if (Config STREQUAL "AUTO")
        #----------------------------------------
        # SETUP COMPILER FLAGS FOR TEST PROGRAMS
        #----------------------------------------
        if (MSVC)
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
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
                "-DCMAKE_CXX_FLAGS=${TEST_FLAG_AVX512}"
                COMPILE_DEFINITIONS ${TEST_FLAG_AVX512}
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
        #                    RUN_OUTPUT_VARIABLE AVX10_RUN_OUTPUT
        #            )

        message(STATUS "Running AVX2 Tests")
        try_run(
                AVX2_RUNS
                AVX2_COMPILES
                ${TEST_COMPILE_DIR}
                "${TEST_PROG_DIR}/AVX2Test.cpp"
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
                "-DCMAKE_CXX_FLAGS=${TEST_FLAG_AVX2}"
                COMPILE_DEFINITIONS ${TEST_FLAG_AVX2}
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
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
                "-DCMAKE_CXX_FLAGS=${TEST_FLAG_AVX}"
                COMPILE_DEFINITIONS ${TEST_FLAG_AVX}
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
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
                "-DCMAKE_CXX_FLAGS=${TEST_FLAG_SSE4}"
                COMPILE_DEFINITIONS ${TEST_FLAG_SSE4}
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
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
                "-DCMAKE_CXX_FLAGS=${TEST_FLAG_SSE2}"
                COMPILE_DEFINITIONS ${TEST_FLAG_SSE2}
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
                CMAKE_FLAGS
                "-DCMAKE_CXX_STANDARD=17"
                COMPILE_OUTPUT_VARIABLE NEON_COMPILE_OUT
        )
        message(WARNING "ARM COMPILE OUTPUT:\n${NEON_COMPILE_OUT}")
        if (NEON_RUNS EQUAL 0)
            message(STATUS "Neon detection success!")
        else ()
            message(STATUS "Neon detection failed!")
        endif ()

        message(STATUS "COMPILATION")
        message(STATUS "SSE2 ${SSE2_COMPILES}")
        message(STATUS "SSE4 ${SSE4_COMPILES}")
        message(STATUS "AVX ${AVX_COMPILES}")
        message(STATUS "AVX2 ${AVX2_COMPILES}")
        message(STATUS "AVX512 ${AVX512_COMPILES}")
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
    if (MSVC)
        target_compile_options(${Target} PUBLIC ${MSVCCompilerFlag})
    else ()
        target_compile_options(${Target} PUBLIC ${CompilerFlag})
    endif ()
    target_compile_definitions(${Target} PUBLIC ${Config})
endfunction()