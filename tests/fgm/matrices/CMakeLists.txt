add_executable(FGMMatrixTests)
set_target_properties(FGMMatrixTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FGMMatrixTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FGMMatrixTests PROPERTIES CXX_EXTENSIONS OFF)

target_sources(
        FGMMatrixTests

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${FGM_ROOT_INCLUDE_DIR}
        FILES
        ${SetupHeaderFiles}
        ${TestUtilities}
)

target_compile_options(FGMMatrixTests INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)


add_subdirectory(extra)
add_subdirectory(mat2)
add_subdirectory(mat2x3)
add_subdirectory(mat2x4)
add_subdirectory(mat3)
add_subdirectory(mat3x2)
add_subdirectory(mat3x4)
add_subdirectory(mat4)
add_subdirectory(mat4x2)
add_subdirectory(mat4x3)
add_subdirectory(transform4)

target_link_libraries(
        FGMMatrixTests
        PRIVATE
        FGMTestSetup

        # OBJs
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
        FGMMatrixTests
        REUSE_FROM
        FGMCommonTests
)


include(GoogleTest)

set_target_properties(
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
        PROPERTIES FOLDER "Test Intermediates/FGM"
)


#####################################
## DEATH TESTS

add_executable(FGMMatrixDeathTests
        death-tests/Mat2.cpp
        death-tests/Mat2x3.cpp
        death-tests/Mat2x4.cpp
        death-tests/Mat3.cpp
        death-tests/Mat3x2.cpp
        death-tests/Mat3x4.cpp
        death-tests/Mat4.cpp
        death-tests/Mat4x2.cpp
        death-tests/Transform4.cpp
)
set_target_properties(FGMMatrixDeathTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FGMMatrixDeathTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FGMMatrixDeathTests PROPERTIES CXX_EXTENSIONS OFF)

target_sources(
        FGMMatrixDeathTests

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${FGM_ROOT_INCLUDE_DIR}
        FILES
        ${SetupHeaderFiles}
        ${TestUtilities}
)

target_compile_options(FGMMatrixDeathTests INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)
target_link_libraries(FGMMatrixDeathTests PRIVATE FGMTestSetup)
target_precompile_headers(FGMMatrixDeathTests REUSE_FROM FGMCommonTests)


#### GTEST
include(GoogleTest)
gtest_discover_tests(FGMMatrixTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
gtest_discover_tests(FGMMatrixDeathTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
