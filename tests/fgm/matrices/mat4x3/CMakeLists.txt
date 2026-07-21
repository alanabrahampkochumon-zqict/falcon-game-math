add_library(Mat4x3Tests OBJECT)

target_sources(
        Mat4x3Tests PRIVATE
        AccessAndMutationTests.cpp
        AdditionTests.cpp
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
        Mat4x3Tests PRIVATE
        ${FGM_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Mat4x3Tests PRIVATE
        FGM
        GTest::gtest
        GTest::gtest_main
        StrictWarnings
        ProjectSanitizers
        NonComprehensiveTestMode
)