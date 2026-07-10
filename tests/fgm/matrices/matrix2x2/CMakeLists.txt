add_library(Matrix2Tests OBJECT)

target_sources(
        Matrix2Tests PRIVATE
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
        Matrix2Tests PRIVATE
        ${TEST_ROOT_DIR}/include
)

add_subdirectory(TransformationFactoryTests)

target_link_libraries(
        Matrix2Tests PRIVATE
        FGM
        GTest::gtest
        GTest::gtest_main
)