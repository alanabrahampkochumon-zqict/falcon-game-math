set(FALCON_SIMD_TEST_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(FALCON_SIMD_TEST_ROOT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_executable(FalconSIMDTestSuite)
set_target_properties(FalconSIMDTestSuite PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconSIMDTestSuite PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconSIMDTestSuite PROPERTIES CXX_EXTENSIONS OFF)

add_subdirectory(utils)
add_subdirectory(memory)

target_sources(
        FalconSIMDTestSuite
        PRIVATE
        SimdTests.cpp
)

target_compile_options(FalconSIMDTestSuite INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

target_precompile_headers(
        FalconSIMDTestSuite PRIVATE
        <gtest/gtest.h>
        <iostream>
        <limits>
        <concepts>
        <cstddef>
        <type_traits>
)

target_link_libraries(FalconSIMDTestSuite PRIVATE FalconSimdTestSetup)

target_include_directories(
        FalconSIMDTestSuite
        PRIVATE
        include
)

AddCompilerFlag(FalconSIMDTestSuite AUTO) # Update to compile an executable per flag


include(GoogleTest)
gtest_discover_tests(FalconSIMDTestSuite DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)

set_target_properties(FalconSIMDUtilTests PROPERTIES FOLDER "Test Intermediates/Falcon SIMD")