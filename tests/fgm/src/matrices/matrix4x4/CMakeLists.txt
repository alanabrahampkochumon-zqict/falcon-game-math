add_library(Matrix4x4Tests OBJECT)

target_sources(
        Matrix4x4Tests PRIVATE
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
        Matrix4x4Tests PRIVATE
        ${TEST_ROOT_DIR}/include
)

add_subdirectory(TransformationFactoryTests)

target_link_libraries(
        Matrix4x4Tests PRIVATE
        MathLib
        GTest::gtest
        GTest::gtest_main

        # Submodules
        Matrix4x4TransformTests
)