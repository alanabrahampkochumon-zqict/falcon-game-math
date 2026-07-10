cmake_minimum_required(VERSION 3.25)

project(FalconGameMath LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

add_library(StrictWarnings INTERFACE)
add_library(ProjectSanitizers INTERFACE)

set(DevToolsDir "Dev Tools")

# Turn on solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
option(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Custom Options
# Flags for keeping the library lightweight when a consumer imports it
option(FGM_BENCHMARK "Enables FGM Benchmark Suite")
option(FGM_TESTS "Enables FGM Benchmark Suite")
option(FGM_DEMO_RASTERIZER "Enables FGM Demo Rasterizer Application")
option(FGM_DOCS "Enables FGM Documentation Generation")
option(FGM_STRICT_MODE "Enable Strict Warnings" OFF) # Option to enable compiler specific "Warning as Error"
option(FGM_ASAN "Enable ASan" OFF) # Option to enable ASAN # TODO: Fix ASAN


if (FGM_DEMO_RASTERIZER)
    add_subdirectory(apps/rasterizer)
endif ()

include(cmake/ClangFormat.cmake)
include(cmake/ClangTidy.cmake)
include(cmake/Dependencies.cmake)
include(cmake/SimdCheck.cmake)

if (FGM_DOCS)
    include(cmake/Doxygen.cmake)
endif ()

if (FGM_STRICT_MODE)
    include(cmake/StrictMode.cmake)
endif ()

if (FGM_ASAN)
    include(cmake/ASan.cmake)
endif ()

# Multi-processor compilation
if (MSVC AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "[FGM]: Enabling Multiprocessor compilation on MSVC")
    add_compile_options("/MP")
endif ()

# Core Library
add_subdirectory(include)

if (FGM_TESTS)
    message("[FGM]: Tests are enabled")
    add_subdirectory(tests)
endif ()

if (FGM_BENCHMARK)
    message("[FGM]: Benchmarks are enabled")
    add_subdirectory(benchmarks)
endif ()