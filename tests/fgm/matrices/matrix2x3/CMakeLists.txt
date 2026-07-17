add_library(Matrix2x3Tests OBJECT)

target_sources(
        Matrix2x3Tests PRIVATE
        AccessAndMutationTests.cpp
        AdditionTests.cpp
        EqualityTests.cpp
        InitializationTests.cpp
        SubtractionTests.cpp
        UtilityTests.cpp
)

target_include_directories(
        Matrix2x3Tests PRIVATE
        ${FGM_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Matrix2x3Tests PRIVATE
        FGM
        GTest::gtest
        GTest::gtest_main
)