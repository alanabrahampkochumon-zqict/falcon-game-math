add_executable(MathTestSuite)

target_compile_features(MathTestSuite PRIVATE cxx_std_20)

set(IncludeDir "include/")
set(SetupFiles "Vector2DTestSetup.h;Vector3DTestSetup.h;Vector4DTestSetup.h;DoxygenGroups.h;MatrixTestSetup.h;CommonSetup.h;")
list(TRANSFORM SetupFiles PREPEND ${IncludeDir})

# Vector Test Sources
set(Vector4DTestDir "src/vectors/vector4d/")
set(Vector4DTestFiles "AccessAndMutationTests.cpp;ArithmeticOperationTests.cpp;BooleanBitOperationTests.cpp;ComparisonTests.cpp;ConstantsTests.cpp;InitializationTests.cpp;TypeConversionTests.cpp;AliasTests.cpp;EqualityTests.cpp;ProductTests.cpp;MagnitudeTests.cpp;ProjectionTests.cpp;NormalizationTests.cpp;RejectionTests.cpp;StringRepresentationTests.cpp;UtilityTests.cpp;SwizzlingTests.cpp;PNormTests.cpp;DistanceTests.cpp;")
list(TRANSFORM Vector4DTestFiles PREPEND ${Vector4DTestDir})

set(Vector3DTestDir "src/vectors/vector3d/")
set(Vector3DTestFiles "AccessAndMutationTests.cpp;ArithmeticOperationTests.cpp;BooleanBitOperationTests.cpp;ComparisonTests.cpp;ConstantsTests.cpp;InitializationTests.cpp;TypeConversionTests.cpp;AliasTests.cpp;EqualityTests.cpp;ProductTests.cpp;MagnitudeTests.cpp;ProjectionTests.cpp;NormalizationTests.cpp;RejectionTests.cpp;StringRepresentationTests.cpp;UtilityTests.cpp;SwizzlingTests.cpp;PNormTests.cpp;DistanceTests.cpp;")
list(TRANSFORM Vector3DTestFiles PREPEND ${Vector3DTestDir})

set(Vector2DTestDir "src/vectors/vector2d/")
set(Vector2DTestFiles "AccessAndMutationTests.cpp;ArithmeticOperationTests.cpp;BooleanBitOperationTests.cpp;ComparisonTests.cpp;ConstantsTests.cpp;InitializationTests.cpp;TypeConversionTests.cpp;AliasTests.cpp;EqualityTests.cpp;ProductTests.cpp;MagnitudeTests.cpp;ProjectionTests.cpp;NormalizationTests.cpp;RejectionTests.cpp;StringRepresentationTests.cpp;UtilityTests.cpp;SwizzlingTests.cpp;PNormTests.cpp;DistanceTests.cpp;")
list(TRANSFORM Vector2DTestFiles PREPEND ${Vector2DTestDir})


# Matrix Test Sources
set(Matrix2x2TestDir "src/matrix/matrix2x2/")
set(Matrix2x2TestFiles "InitializationTests.cpp;TypeConversionTests.cpp;AccessAndMutationTests.cpp;EqualityTests.cpp;AdditionTests.cpp;SubtractionTests.cpp;MultiplicationTests.cpp;DeterminantTests.cpp;DivisionTests.cpp;TransposeTests.cpp;InverseTests.cpp;ConstantTests.cpp;UtilityTests.cpp;AliasTests.cpp;StringRepresentationTests.cpp;TraceTests.cpp;TransformationFactoryTests.cpp;")
list(TRANSFORM Matrix2x2TestFiles PREPEND ${Matrix2x2TestDir})

set(Matrix3x3TestDir "src/matrix/matrix3x3/")
set(Matrix3x3TestFiles "InitializationTests.cpp;AccessAndMutationTests.cpp;TypeConversionTests.cpp;ConstantTests.cpp;UtilityTests.cpp;EqualityTests.cpp;AdditionTests.cpp;SubtractionTests.cpp;MultiplicationTests.cpp;DivisionTests.cpp;DeterminantTests.cpp;TransposeTests.cpp;InverseTests.cpp;TraceTests.cpp;StringRepresentationTests.cpp;AliasTests.cpp;")
list(TRANSFORM Matrix3x3TestFiles PREPEND ${Matrix3x3TestDir})

set(Matrix4x4TestDir "src/matrix/matrix4x4/")
set(Matrix4x4TestFiles "InitializationTests.cpp;AccessAndMutationTests.cpp;TypeConversionTests.cpp;ConstantTests.cpp;UtilityTests.cpp;EqualityTests.cpp;AdditionTests.cpp;SubtractionTests.cpp;MultiplicationTests.cpp;DivisionTests.cpp;TransposeTests.cpp;DeterminantTests.cpp;TraceTests.cpp;InverseTests.cpp;StringRepresentationTests.cpp;AliasTests.cpp;")
list(TRANSFORM Matrix4x4TestFiles PREPEND ${Matrix4x4TestDir})


set(MathCommonDir "src/common/")
set(MathCommonTestFiles "OperationStatusTests.cpp;WrapperTests.cpp;MathTraitTests.cpp;TrivialTypeTests.cpp;UtilsTests.cpp;")
list(TRANSFORM MathCommonTestFiles PREPEND ${MathCommonDir})

set(UtilityDirectory "include/utils/")
set(Utilities "FloatEquals.h;MatrixUtils.h;VectorUtils.h;TypeUtils.h;")
list(TRANSFORM Utilities PREPEND ${UtilityDirectory})

set(GenericTestFiles "HeaderAliasTests.cpp")
list(TRANSFORM GenericTestFiles PREPEND "src/")

target_sources(
        MathTestSuite
        PRIVATE
        ${Vector2DTestFiles}
        ${Vector3DTestFiles}
        ${Vector4DTestFiles}
        ${Matrix2x2TestFiles}
        ${Matrix3x3TestFiles}
        ${Matrix4x4TestFiles}
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
        "${CMAKE_CURRENT_SOURCE_DIR}/${IncludeDir}"
        PREFIX "Header Files"
        FILES
        ${SetupFiles}
        ${Utilities}
)

source_group(
        TREE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        PREFIX "Source Files"
        FILES
        ${Vector2DTestFiles}
        ${Vector3DTestFiles}
        ${Vector4DTestFiles}
        ${Matrix2x2TestFiles}
        ${Matrix3x3TestFiles}
        ${Matrix4x4TestFiles}
        ${MathCommonTestFiles}
        ${GenericTestFiles}
)