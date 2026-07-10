add_executable(FalconSIMDTest)
set_target_properties(FalconSIMDTest PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconSIMDTest PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconSIMDTest PROPERTIES CXX_EXTENSIONS OFF)

add_subdirectory(utils)

target_sources(
        FalconSIMDTest
        PRIVATE
        RegisterTypeTests.cpp
)

target_compile_options(FalconSIMDTest INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

target_precompile_headers(
        FalconSIMDTest PRIVATE
        <gtest/gtest.h>
        <iostream>
        <limits>
        <concepts>
        <cstddef>
        <type_traits>
)

target_link_libraries(
        FalconSIMDTest
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
        FalconSIMDTest
        PRIVATE
        include
)


include(GoogleTest)
gtest_discover_tests(FalconSIMDTest DISCOVERY_MODE PRE_TEST)

set_target_properties(FalconSIMDUtilTests PROPERTIES FOLDER "Test Intermediates/Falcon SIMD")