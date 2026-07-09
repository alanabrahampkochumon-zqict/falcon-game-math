add_executable(MathTestSuite)
target_compile_features(MathTestSuite PRIVATE cxx_std_20)

# Directories
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(TEST_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(UtilityDirectory "${INCLUDE_DIR}utils/")


# Files
set(SetupFiles "Vector2TestSetup.h;Vector3TestSetup.h;Vector4TestSetup.h;DoxygenGroups.h;MatrixTestSetup.h;CommonSetup.h;")
list(TRANSFORM SetupFiles PREPEND ${INCLUDE_DIR})

set(Utilities "FloatEquals.h;MatrixUtils.h;VectorUtils.h;TypeUtils.h;")
list(TRANSFORM Utilities PREPEND ${UtilityDirectory})

add_subdirectory(common)
add_subdirectory(vectors/vector2d)
add_subdirectory(vectors/vector3d)
add_subdirectory(vectors/vector4d)
add_subdirectory(matrices/matrix2x2)
add_subdirectory(matrices/matrix4x4)
add_subdirectory(matrices/matrix3x3)

target_sources(
        MathTestSuite
        PRIVATE
        HeaderAliasTests.cpp

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${HeaderDirectory}
        FILES
        ${SetupFiles}
        ${Utilities}
)

target_compile_options(MathTestSuite INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

target_precompile_headers(
        MathTestSuite
        PRIVATE
        <gtest/gtest.h>
        <iostream>
        <limits>
        <concepts>
        <cstddef>
        <type_traits>
)

target_link_libraries(
        MathTestSuite
        PRIVATE
        MathLib
        FalconSIMD
        GTest::gtest
        GTest::gtest_main # googletest
        # Testing CML

        CommonTests
        Vector2Tests
        Vector3Tests
        Vector4Tests
        Matrix2Tests
        Matrix2TransformTests
        Matrix3Tests
        Matrix3TransformTests
        Matrix4Tests
        Matrix4TransformTests
)

target_include_directories(
        MathTestSuite
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


include(GoogleTest)
gtest_discover_tests(MathTestSuite DISCOVERY_MODE PRE_TEST)

source_group(
        TREE
        "${INCLUDE_DIR}"
        PREFIX "Header Files"
        FILES
        ${SetupFiles}
        ${Utilities}
)

source_group(
        TREE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        PREFIX "Source Files"
        FILES
        ${GenericTestFiles}
)