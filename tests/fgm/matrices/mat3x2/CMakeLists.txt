add_library(Mat3x2Tests OBJECT)

target_sources(
        Mat3x2Tests PRIVATE
        AccessAndMutationTests.cpp
        AdditionTests.cpp
        DivisionTests.cpp
        EqualityTests.cpp
        InitializationTests.cpp
        MultiplicationTests.cpp
        StringRepresentationTests.cpp
        SubtractionTests.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp
)

target_include_directories(
        Mat3x2Tests PRIVATE
        ${FGM_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Mat3x2Tests PRIVATE
        FGM
        GTest::gtest
        GTest::gtest_main
)