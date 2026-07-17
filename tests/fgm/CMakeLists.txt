add_executable(FGMTestSuite)
set_target_properties(FGMTestSuite PROPERTIES CXX_STANDARD 20)
set_target_properties(FGMTestSuite PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FGMTestSuite PROPERTIES CXX_EXTENSIONS OFF)

# Directories
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(FGM_TEST_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(UtilityDirectory "${INCLUDE_DIR}utils/")


# Files
set(SetupFiles "Vector2TestSetup.h;Vector3TestSetup.h;Vector4TestSetup.h;DoxygenGroups.h;MatrixTestSetup.h;CommonSetup.h;")
list(TRANSFORM SetupFiles PREPEND ${INCLUDE_DIR})

set(Utilities "FloatEquals.h;MatrixUtils.h;VectorUtils.h;TypeUtils.h;")
list(TRANSFORM Utilities PREPEND ${UtilityDirectory})

add_subdirectory(common)
add_subdirectory(vectors/vector2)
add_subdirectory(vectors/vector3)
add_subdirectory(vectors/vector4)
add_subdirectory(matrices/matrix2)
add_subdirectory(matrices/matrix2x3)
add_subdirectory(matrices/matrix4)
add_subdirectory(matrices/matrix3)

target_sources(
        FGMTestSuite
        PRIVATE
        HeaderAliasTests.cpp

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${HeaderDirectory}
        FILES
        ${SetupFiles}
        ${Utilities}
)

target_compile_options(FGMTestSuite INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

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

target_link_libraries(
        FGMTestSuite
        PRIVATE
        FGM
        FalconSIMD
        GTest::gtest
        GTest::gtest_main # googletest
        StrictWarnings
        ProjectSanitizers

        # Objs
        CommonTests
        Vector2Tests
        Vector3Tests
        Vector4Tests
        Matrix2Tests
        Matrix2x3Tests
        Matrix2TransformTests
        Matrix3Tests
        Matrix3TransformTests
        Matrix4Tests
        Matrix4TransformTests
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

set_target_properties(CommonTests
        Vector2Tests
        Vector3Tests
        Vector4Tests
        Matrix2Tests
        Matrix2TransformTests
        Matrix3Tests
        Matrix3TransformTests
        Matrix4Tests
        Matrix4TransformTests
        PROPERTIES FOLDER "Test Intermediates/FGM")