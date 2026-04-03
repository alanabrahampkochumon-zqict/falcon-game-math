add_executable(TestSuite)

target_compile_features(TestSuite PRIVATE cxx_std_20)

# target_compile_options(TestSuite PRIVATE # TODO: Change to the compile target
#     $<$<CXX_COMPILER_ID:MSVC>:/W4;/wd4201;/wd26495;/wd26439>
#     $<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wpedantic;-Wno-gnu-anonymous-struct;-Werror;>
#     $<$<CXX_COMPILER_ID:Clang>:-Wall;-Wextra;-Wpedantic;-Wno-gnu-anonymous-struct;-Werror;>
# )

# TODO: Refactor math files into math directory of src

set(IncludeDir "include/")
set(SetupFiles "Vector3DTestSetup.h;Vector4DTestSetup.h;SIMDTestSetup.h;DoxygenGroups.h")
list(TRANSFORM SetupFiles PREPEND ${IncludeDir})

# Vector Test Sources
set(Vector4DTestDir "src/math/vectors/vector4d/")
set(Vector4DTestFiles "AccessAndMutationTests.cpp;ArithmeticOperationTests.cpp;BooleanBitOperationTests.cpp;ComparisonTests.cpp;ConstantsTests.cpp;InitializationTests.cpp;TypeConversionTests.cpp;AliasTests.cpp;EqualityTests.cpp;ProductTests.cpp;MagnitudeTests.cpp;ProjectionTests.cpp;NormalizationTests.cpp;RejectionTests.cpp;StringRepresentationTests.cpp;UtilityTests.cpp;")
list(TRANSFORM Vector4DTestFiles PREPEND ${Vector4DTestDir})

# Vector Test Sources
set(Vector3DTestDir "src/math/vectors/vector3d/")
set(Vector3DTestFiles "AccessAndMutationTests.cpp;InitializationTests.cpp;TypeConversionTests.cpp;EqualityTests.cpp;BooleanBitOperationTests.cpp;ComparisonTests.cpp;ArithmeticOperationTests.cpp;AliasTests.cpp;ConstantsTests.cpp;UtilityTests.cpp;ProductTests.cpp;MagnitudeTests.cpp;")
list(TRANSFORM Vector3DTestFiles PREPEND ${Vector3DTestDir})


set(VectorTestDirectory "src/math/vectors/") # TODO: Remove after migration to different test
set(VectorTestFiles Vector2DTests.cpp Vector3DTests.cpp)
list(TRANSFORM VectorTestFiles PREPEND ${VectorTestDirectory})

# Matrix Test Sources
set(MatrixTestDirectory "src/math/matrix/")
set(MatrixTestFiles Matrix2DTests.cpp Matrix3DTests.cpp Matrix4DTests.cpp )
list(TRANSFORM MatrixTestFiles PREPEND ${MatrixTestDirectory})

set(MathCommonDir "src/math/common/")
set(MathCommonTestFiles "OperationStatusTests.cpp")
list(TRANSFORM MathCommonTestFiles PREPEND ${MathCommonDir})

set(UtilityDirectory "include/utils/")
set(Utilities "FloatEquals.h;MatrixUtils.h;VectorUtils.h")
list(TRANSFORM Utilities PREPEND ${UtilityDirectory})

set(SimdTestDirectory "src/simd/")
set(SimdTestFiles "RegisterTypeTests.cpp;AdditionTests.cpp;InitializationTests.cpp;SimdUtilsTests.cpp")
list(TRANSFORM SimdTestFiles PREPEND ${SimdTestDirectory})

target_sources(
    TestSuite
    PRIVATE
        ${Vector3DTestFiles}
        ${Vector4DTestFiles}
        ${VectorTestFiles}
        ${MatrixTestFiles}
        ${SimdTestFiles}
        ${MathCommonTestFiles}
    
    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${HeaderDirectory}
    FILES
        ${SetupFiles}
        ${Utilities}
)

target_compile_options(TestSuite INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict>)

target_precompile_headers(
    TestSuite
    PRIVATE
    <gtest/gtest.h>
    <iostream>
    <limits>
    <concepts>
    <cstddef>
    <type_traits>
)

target_link_libraries(
    TestSuite
    PRIVATE
    MathLib
    FalconSIMD
    GTest::gtest_main # googletest
)

target_include_directories(
    TestSuite
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()

include(GoogleTest)
gtest_discover_tests(TestSuite DISCOVERY_MODE PRE_TEST)

source_group (
    TREE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    PREFIX "Source Files"
    FILES
    ${Vector3DTestFiles}
    ${Vector4DTestFiles}
    ${VectorTestFiles}
    ${MatrixTestFiles}
    ${SimdTestFiles}
    ${MathCommonTestFiles}
)