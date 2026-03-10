add_executable(TestSuite)

target_compile_features(TestSuite PRIVATE cxx_std_20)

# target_compile_options(TestSuite PRIVATE # TODO: Change to the compile target
#     $<$<CXX_COMPILER_ID:MSVC>:/W4;/wd4201;/wd26495;/wd26439>
#     $<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wpedantic;-Wno-gnu-anonymous-struct;-Werror;>
#     $<$<CXX_COMPILER_ID:Clang>:-Wall;-Wextra;-Wpedantic;-Wno-gnu-anonymous-struct;-Werror;>
# )

set(IncludeDirectory "include/")
set(SetupFiles "Vector3DTestSetup.h;Vector4DTestSetup.h;SIMDTestSetup.h")
list(TRANSFORM SetupFiles PREPEND ${IncludeDirectory})

# Vector Test Sources
set(Vector4DTestDirectory "src/vectors/vector4d/")
set(Vector4DTestFiles "AccessAndMutationTests.cpp;ArithmeticOperationTests.cpp;BooleanBitOperationTests.cpp;ComparisonTests.cpp;InitializationTests.cpp;TypeConversionTests.cpp;AliasTests.cpp;EqualityTests.cpp;ProductTests.cpp;MagnitudeTests.cpp;ProjectionTests.cpp")
list(TRANSFORM Vector4DTestFiles PREPEND ${Vector4DTestDirectory})

# Vector Test Sources
set(Vector3DTestDirectory "src/vectors/vector3d/")
set(Vector3DTestFiles "AccessAndMutationTests.cpp;InitializationTests.cpp;")
list(TRANSFORM Vector3DTestFiles PREPEND ${Vector3DTestDirectory})


set(VectorTestDirectory "src/vectors/") # TODO: Remove after migration to different test
set(VectorTestFiles Vector2DTests.cpp Vector3DTests.cpp)
list(TRANSFORM VectorTestFiles PREPEND ${VectorTestDirectory})

# Matrix Test Sources
set(MatrixTestDirectory "src/matrix/")
set(MatrixTestFiles Matrix2DTests.cpp Matrix3DTests.cpp Matrix4DTests.cpp )
list(TRANSFORM MatrixTestFiles PREPEND ${MatrixTestDirectory})

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
    
    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${HeaderDirectory}
    FILES
        ${SetupFiles}
        ${Utilities}
)

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
gtest_discover_tests(TestSuite)

source_group("Source Files\\Vectors\\Vector3D" FILES ${Vector3DTestFiles})
source_group("Source Files\\Vectors\\Vector4D" FILES ${Vector4DTestFiles})
source_group("Source Files\\Vectors" FILES ${VectorTestFiles}) # TODO: Remove after migration
source_group("Source Files\\Matrices" FILES ${MatrixTestFiles})
source_group("Source Files\\Simd" FILES ${SimdTestFiles})