add_executable(MathTestSuite)
target_compile_features(MathTestSuite PRIVATE cxx_std_20)


# Directories
set(IncludeDir "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(SourceDir "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(TEST_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(VectorDir "${SourceDir}vectors/")
set(Vector2TestDir "${VectorDir}vector2d/")
set(Vector3TestDir "${VectorDir}vector3d/")
set(Vector4TestDir "${VectorDir}vector4d/")

set(MatrixDir "${SourceDir}matrices/")
set(Matrix2x2TestDir "${MatrixDir}matrix2x2/")

set(UtilityDirectory "${IncludeDir}utils/")
set(MathCommonDir "${SourceDir}common/")


# Files
set(SetupFiles "Vector2TestSetup.h;Vector3TestSetup.h;Vector4TestSetup.h;DoxygenGroups.h;MatrixTestSetup.h;CommonSetup.h;")
list(TRANSFORM SetupFiles PREPEND ${IncludeDir})

# Vector
set(Vector4TestFiles
        "AccessAndMutationTests.cpp;ArithmeticOperationTests.cpp;BooleanBitOperationTests.cpp;"
        "ComparisonTests.cpp;ConstantsTests.cpp;InitializationTests.cpp;TypeConversionTests.cpp;AliasTests.cpp;"
        "EqualityTests.cpp;ProductTests.cpp;MagnitudeTests.cpp;ProjectionTests.cpp;NormalizationTests.cpp;"
        "RejectionTests.cpp;StringRepresentationTests.cpp;UtilityTests.cpp;SwizzlingTests.cpp;PNormTests.cpp;DistanceTests.cpp;"
)
list(TRANSFORM Vector4TestFiles PREPEND ${Vector4TestDir})

set(Vector3TestFiles
        "AccessAndMutationTests.cpp;ArithmeticOperationTests.cpp;BooleanBitOperationTests.cpp;"
        "ComparisonTests.cpp;ConstantsTests.cpp;InitializationTests.cpp;TypeConversionTests.cpp;AliasTests.cpp;"
        "EqualityTests.cpp;ProductTests.cpp;MagnitudeTests.cpp;ProjectionTests.cpp;NormalizationTests.cpp;"
        "RejectionTests.cpp;StringRepresentationTests.cpp;UtilityTests.cpp;SwizzlingTests.cpp;PNormTests.cpp;DistanceTests.cpp;"
)
list(TRANSFORM Vector3TestFiles PREPEND ${Vector3TestDir})

set(Vector2TestFiles
        "AccessAndMutationTests.cpp;ArithmeticOperationTests.cpp;BooleanBitOperationTests.cpp;"
        "ComparisonTests.cpp;ConstantsTests.cpp;InitializationTests.cpp;TypeConversionTests.cpp;AliasTests.cpp;"
        "EqualityTests.cpp;ProductTests.cpp;MagnitudeTests.cpp;ProjectionTests.cpp;NormalizationTests.cpp;"
        "RejectionTests.cpp;StringRepresentationTests.cpp;UtilityTests.cpp;SwizzlingTests.cpp;PNormTests.cpp;DistanceTests.cpp;"
)
list(TRANSFORM Vector2TestFiles PREPEND ${Vector2TestDir})



set(MathCommonTestFiles "OperationStatusTests.cpp;WrapperTests.cpp;MathTraitTests.cpp;TrivialTypeTests.cpp;UtilsTests.cpp;")
list(TRANSFORM MathCommonTestFiles PREPEND ${MathCommonDir})

set(Utilities "FloatEquals.h;MatrixUtils.h;VectorUtils.h;TypeUtils.h;")
list(TRANSFORM Utilities PREPEND ${UtilityDirectory})

set(GenericTestFiles "HeaderAliasTests.cpp")
list(TRANSFORM GenericTestFiles PREPEND "${SourceDir}")

# TODO: Refactor when Folder based CML
add_subdirectory(src/matrices/matrix2x2)
add_subdirectory(src/matrices/matrix4x4)
add_subdirectory(src/matrices/matrix3x3)

target_sources(
        MathTestSuite
        PRIVATE
        ${Vector2TestFiles}
        ${Vector3TestFiles}
        ${Vector4TestFiles}
        ${MathCommonTestFiles}
        ${GenericTestFiles}

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
        "${IncludeDir}"
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
        ${Vector2TestFiles}
        ${Vector3TestFiles}
        ${Vector4TestFiles}
        ${MathCommonTestFiles}
        ${GenericTestFiles}
)