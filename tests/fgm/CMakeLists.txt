add_executable(FGMTestSuite)
set_target_properties(FGMTestSuite PROPERTIES CXX_STANDARD 20)
set_target_properties(FGMTestSuite PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FGMTestSuite PROPERTIES CXX_EXTENSIONS OFF)

# Directories
set(FGM_ROOT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(FGM_TEST_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(UTILS_DIR "${FGM_ROOT_INCLUDE_DIR}utils/")


# Files
set(SetupHeaderFiles
        DoxygenGroups.h
        CommonSetup.h
)
list(TRANSFORM SetupHeaderFiles PREPEND ${FGM_ROOT_INCLUDE_DIR})

set(TestUtilities "FloatEquals.h;MatrixUtils.h;VectorUtils.h;TypeUtils.h;")
list(TRANSFORM TestUtilities PREPEND ${UTILS_DIR})

add_subdirectory(common)
add_subdirectory(vectors)
add_subdirectory(quaternions)
add_subdirectory(matrices)

target_sources(
        FGMTestSuite
        PRIVATE
        HeaderAliasTests.cpp

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${FGM_ROOT_INCLUDE_DIR}
        FILES
        ${SetupHeaderFiles}
        ${TestUtilities}
)

target_compile_options(FGMTestSuite INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)


target_link_libraries(
        FGMTestSuite
        PRIVATE
        FGMTestSetup

        # Objs
        CommonTests
)

target_precompile_headers(
        FGMTestSuite
        PRIVATE
        <gtest/gtest.h>
        <iostream>
        <limits>
        <concepts>
        <cstddef>
        <type_traits>
)

target_include_directories(
        FGMTestSuite
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


include(GoogleTest)
gtest_discover_tests(FGMTestSuite DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 180)

source_group(
        TREE
        "${FGM_ROOT_INCLUDE_DIR}"
        PREFIX "Header Files"
        FILES
        ${SetupHeaderFiles}
        ${TestUtilities}
)

source_group(
        TREE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        PREFIX "Source Files"
        FILES
        ${GenericTestFiles}
)


set_target_properties(CommonTests
        PROPERTIES FOLDER "Test Intermediates/FGM"
)