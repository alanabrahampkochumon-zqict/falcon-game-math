include_guard()

include(FetchContent)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) # Statically link Gtest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark testing" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Disable benchmark install" FORCE)

set(VENDORS_DIR "Vendors")

# Google Test
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 # release-1.17.0
        SYSTEM
)

FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.5
        SYSTEM
)

FetchContent_Declare(
        sdl3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG d9d5536704d585616d4db3c8ba3c4ff6fc2757e1
        SYSTEM
)

FetchContent_Declare(
        fast_float
        GIT_REPOSITORY https://github.com/fastfloat/fast_float.git
        GIT_TAG v8.2.10
        SYSTEM
)

# Test Harness Dependencies
if (FGM_TESTS)
    FetchContent_MakeAvailable(googletest)
    # Group google_test projects into a "Gtest" folder
    set_target_properties(
            gtest gtest_main gmock gmock_main
            PROPERTIES FOLDER "${VENDORS_DIR}/Google/GTest"
    )

    if (MSVC)
        target_compile_options(gtest PRIVATE /WX- /W0)
        target_compile_options(gtest_main PRIVATE /WX- /W0)
    endif ()
endif ()


# Benchmark Dependencies
if (FGM_BENCHMARK)
    FetchContent_MakeAvailable(googlebenchmark)
    set_target_properties(benchmark benchmark_main PROPERTIES FOLDER "${VENDORS_DIR}/Google/Benchmark")
endif ()


# Rasterizer Dependencies
if (FGM_DEMO_RASTERIZER)
    FetchContent_MakeAvailable(sdl3)
    FetchContent_MakeAvailable(fast_float)
    set_target_properties(SDL3-static SDL3_test PROPERTIES FOLDER "${VENDORS_DIR}/SDL3")
endif ()

