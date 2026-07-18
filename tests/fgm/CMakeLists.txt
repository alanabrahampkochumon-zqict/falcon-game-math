add_executable(FGMTestSuite)
set_target_properties(FGMTestSuite PROPERTIES CXX_STANDARD 20)
set_target_properties(FGMTestSuite PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FGMTestSuite PROPERTIES CXX_EXTENSIONS OFF)

# Directories
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(FGM_TEST_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(UtilityDirectory "${INCLUDE_DIR}utils/")


# Files
set(SetupFiles
        Vec2TestSetup.h
        Vec3TestSetup.h
        Vec4TestSetup.h
        DoxygenGroups.h
        MatrixTestSetup.h
        Mat2x3TestSetup.h
        Mat2x4TestSetup.h
        CommonSetup.h
)
list(TRANSFORM SetupFiles PREPEND ${INCLUDE_DIR})

set(Utilities "FloatEquals.h;MatrixUtils.h;VectorUtils.h;TypeUtils.h;")
list(TRANSFORM Utilities PREPEND ${UtilityDirectory})

add_subdirectory(common)
add_subdirectory(vectors/vec2)
add_subdirectory(vectors/vec3)
add_subdirectory(vectors/vec4)
add_subdirectory(matrices/matrix2)
add_subdirectory(matrices/matrix2x3)
add_subdirectory(matrices/mat2x4)
add_subdirectory(matrices/matrix4)
add_subdirectory(matrices/matrix3)
add_subdirectory(matrices/matmul)

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
        Vec2Tests
        Vec3Tests
        Vec4Tests
        Mat2Tests
        Mat2x3Tests
        Mat2x4Tests
        Mat2TransformTests
        Mat3Tests
        Mat3TransformTests
        Mat4Tests
        Mat4TransformTests
        MatrixMultiplicationTests
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
        Vec2Tests
        Vec3Tests
        Vec4Tests
        Mat2Tests
        Mat2TransformTests
        Mat3Tests
        Mat3TransformTests
        Mat4Tests
        Mat4TransformTests
        PROPERTIES FOLDER "Test Intermediates/FGM")