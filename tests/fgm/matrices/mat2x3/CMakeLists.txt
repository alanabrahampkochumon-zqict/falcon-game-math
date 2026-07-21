add_library(Mat2x3Tests OBJECT)

target_sources(
        Mat2x3Tests PRIVATE
        AccessAndMutationTests.cpp
        AdditionTests.cpp
        AliasTests.cpp
        ConstantTests.cpp
        DivisionTests.cpp
        EqualityTests.cpp
        InitializationTests.cpp
        MultiplicationTests.cpp
        NegationTests.cpp
        StringRepresentationTests.cpp
        SubtractionTests.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp
)

target_include_directories(
        Mat2x3Tests PRIVATE
        ${FGM_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Mat2x3Tests PRIVATE
        FGM
        StrictWarnings
        ProjectSanitizers
        GTest::gtest
        GTest::gtest_main
        NonComprehensiveTestMode
)