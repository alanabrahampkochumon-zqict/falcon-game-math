add_executable(TestSuite)

target_compile_features(TestSuite PRIVATE cxx_std_20)

# target_compile_options(TestSuite PRIVATE # TODO: Change to the compile target
#     $<$<CXX_COMPILER_ID:MSVC>:/W4;/wd4201;/wd26495;/wd26439>
#     $<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wpedantic;-Wno-gnu-anonymous-struct;-Werror;>
#     $<$<CXX_COMPILER_ID:Clang>:-Wall;-Wextra;-Wpedantic;-Wno-gnu-anonymous-struct;-Werror;>
# )

# Vector Test Sources
set(VectorTestDirectory "src/vector/")
set(VectorTestFiles Vector2DTests.cpp Vector3DTests.cpp Vector4DTests.cpp)
list(TRANSFORM VectorTestFiles PREPEND ${VectorTestDirectory})

# Matrix Test Sources
set(MatrixTestDirectory "src/matrix/")
set(MatrixTestFiles Matrix2DTests.cpp Matrix3DTests.cpp Matrix4DTests.cpp )
list(TRANSFORM MatrixTestFiles PREPEND ${MatrixTestDirectory})

set(UtilityDirectory "src/utils/")
set(Utilities "FloatEquals.h;MatrixUtils.h;VectorUtils.h")
list(TRANSFORM Utilities PREPEND ${UtilityDirectory})

set(SimdTestDirectory "src/simd/")
set(SimdTestFiles "AdditionTests.cpp;InitializationTests.cpp;SimdUtilsTests.cpp")
list(TRANSFORM SimdTestFiles PREPEND ${SimdTestDirectory})

target_sources(
    TestSuite
    PRIVATE
        ${VectorTestFiles} ${MatrixTestFiles} ${Utilities} ${SimdTestFiles}
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

enable_testing()

include(GoogleTest)
gtest_discover_tests(TestSuite)

source_group("Source Files\\Vectors" FILES ${VectorTestFiles})
source_group("Source Files\\Matrices" FILES ${MatrixTestFiles})
source_group("Source Files\\Simd" FILES ${SimdTestFiles})