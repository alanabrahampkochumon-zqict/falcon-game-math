add_library(Mat2x4Tests OBJECT)

target_sources(
        Mat2x4Tests PRIVATE
        AccessAndMutationTests.cpp
        #        AdditionTests.cpp
        #        DivisionTests.cpp
        EqualityTests.cpp
        InitializationTests.cpp
        #        MultiplicationTests.cpp
        #        StringRepresentationTests.cpp
        #        SubtractionTests.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp
)

target_include_directories(
        Mat2x4Tests PRIVATE
        ${FGM_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Mat2x4Tests PRIVATE
        FGM
        GTest::gtest
        GTest::gtest_main
)