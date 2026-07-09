add_library(Matrix3x3Tests OBJECT)

target_sources(
        Matrix3x3Tests PRIVATE
        AccessAndMutationTests.cpp
        AdditionTests.cpp
        AliasTests.cpp
        ConstantTests.cpp
        DeterminantTests.cpp
        DivisionTests.cpp
        EqualityTests.cpp
        InitializationTests.cpp
        InverseTests.cpp
        MultiplicationTests.cpp
        StringRepresentationTests.cpp
        SubtractionTests.cpp
        TraceTests.cpp
        TransposeTests.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp
)

target_include_directories(
        Matrix3x3Tests PRIVATE
        ${TEST_ROOT_DIR}/include
)

add_subdirectory(TransformationFactoryTests)

target_link_libraries(
        Matrix3x3Tests PRIVATE
        MathLib
        GTest::gtest
        GTest::gtest_main

        # Submodules
        Matrix3x3TransformTests
)