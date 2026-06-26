add_executable(SIMDTestSuite)
target_compile_features(SIMDTestSuite PRIVATE cxx_std_20)


# Directories
set(IncludeDir "include/")
set(UtilityDir "${IncludeDir}utils/")
set(SourceDir "src/")

# Files
set(SetupFiles "CommonSetup.h;SIMDTestSetup.h;DoxygenGroups.h")
list(TRANSFORM SetupFiles PREPEND ${IncludeDir})

set(Utilities "FloatEquals.h;TypeUtils.h")
list(TRANSFORM Utilities PREPEND ${UtilityDir})

set(SimdTestFiles "RegisterTypeTests.cpp;AdditionTests.cpp;InitializationTests.cpp;SimdUtilsTests.cpp;")
list(TRANSFORM SimdTestFiles PREPEND ${SourceDir})


target_sources(
        SIMDTestSuite
        PRIVATE
        ${SimdTestFiles}

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${HeaderDir}
        FILES
        ${SetupFiles}
        ${Utilities}
)

target_compile_options(SIMDTestSuite INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

target_precompile_headers(
        SIMDTestSuite
        PRIVATE
        <gtest/gtest.h>
        <iostream>
        <limits>
        <concepts>
        <cstddef>
        <type_traits>
)

target_link_libraries(
        SIMDTestSuite
        PRIVATE
        MathLib
        FalconSIMD
        GTest::gtest
        GTest::gtest_main # googletest
)

target_include_directories(
        SIMDTestSuite
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


include(GoogleTest)
gtest_discover_tests(SIMDTestSuite DISCOVERY_MODE PRE_TEST)

source_group(
        TREE
        "${CMAKE_CURRENT_SOURCE_DIR}/${IncludeDir}"
        PREFIX "Header Files"
        FILES
        ${SetupFiles}
        ${Utilities}
)

source_group(
        TREE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        PREFIX "Source Files"
        FILES
        ${SimdTestFiles}
)