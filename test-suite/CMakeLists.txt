add_executable(TestSuite)

target_compile_features(TestSuite PRIVATE cxx_std_20)

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