add_library(Mat4Tests OBJECT)

target_sources(
        Mat4Tests PRIVATE
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
        NegationTests.cpp
        StringRepresentationTests.cpp
        SubtractionTests.cpp
        TraceTests.cpp
        TransposeTests.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp
)

target_include_directories(
        Mat4Tests PRIVATE
        ${FGM_TEST_ROOT_DIR}/include
)

add_subdirectory(TransformationFactoryTests)

target_link_libraries(
        Mat4Tests PRIVATE
        FGM
        GTest::gtest
        GTest::gtest_main
        StrictWarnings
        ProjectSanitizers
        NonComprehensiveTestMode
)