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
        Vec2TestSetup.h
        Vec3TestSetup.h
        Vec4TestSetup.h
        DoxygenGroups.h
        Mat2TestSetup.h
        Mat2x3TestSetup.h
        Mat2x4TestSetup.h
        Mat3TestSetup.h
        Mat3x2TestSetup.h
        Mat4TestSetup.h
        CommonSetup.h
)
list(TRANSFORM SetupHeaderFiles PREPEND ${FGM_ROOT_INCLUDE_DIR})

set(TestUtilities "FloatEquals.h;MatrixUtils.h;VectorUtils.h;TypeUtils.h;")
list(TRANSFORM TestUtilities PREPEND ${UTILS_DIR})

add_subdirectory(common)
add_subdirectory(vectors/point2)
add_subdirectory(vectors/point3)
add_subdirectory(vectors/vec2)
add_subdirectory(vectors/vec3)
add_subdirectory(vectors/vec4)
add_subdirectory(matrices/mat2)
add_subdirectory(matrices/mat2x3)
add_subdirectory(matrices/mat2x4)
add_subdirectory(matrices/mat3)
add_subdirectory(matrices/mat3x2)
add_subdirectory(matrices/mat3x4)
add_subdirectory(matrices/mat4)
add_subdirectory(matrices/mat4x2)
add_subdirectory(matrices/mat4x3)
add_subdirectory(matrices/transform4)
add_subdirectory(matrices/extra)
add_subdirectory(quaternions)

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
        Point2Tests
        Point3Tests
        Vec2Tests
        Vec3Tests
        Vec4Tests
        Mat2Tests
        Mat2TransformTests
        Mat2x3Tests
        Mat2x4Tests
        Mat3Tests
        Mat3TransformTests
        Mat3x2Tests
        Mat3x4Tests
        Mat4Tests
        Mat4x2Tests
        Mat4x3Tests
        Mat4TransformTests
        MatrixExtraOpTests
        Transform4Tests
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
        Vec2Tests
        Vec3Tests
        Vec4Tests
        Mat2Tests
        Mat2TransformTests
        Mat3Tests
        Mat3TransformTests
        Mat4Tests
        Mat4TransformTests
        PROPERTIES FOLDER "Test Intermediates/FGM"
)