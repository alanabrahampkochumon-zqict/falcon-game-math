add_executable(FalconSIMDTestSuite)
set_target_properties(FalconSIMDTestSuite PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconSIMDTestSuite PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconSIMDTestSuite PROPERTIES CXX_EXTENSIONS OFF)

add_subdirectory(utils)

target_sources(
        FalconSIMDTestSuite
        PRIVATE
        RegisterTypeTests.cpp
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

target_link_libraries(
        FalconSIMDTestSuite
        PRIVATE
        FGM
        FalconSIMD
        GTest::gtest
        GTest::gtest_main # googletest
        StrictWarnings
        ProjectSanitizers

        FalconSIMDUtilTests
)

target_include_directories(
        FalconSIMDTestSuite
        PRIVATE
        include
)


include(GoogleTest)
gtest_discover_tests(FalconSIMDTestSuite DISCOVERY_MODE PRE_TEST)

set_target_properties(FalconSIMDUtilTests PROPERTIES FOLDER "Test Intermediates/Falcon SIMD")