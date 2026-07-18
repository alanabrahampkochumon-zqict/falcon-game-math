add_library(MatrixMultiplicationTests OBJECT)

target_sources(
        MatrixMultiplicationTests PRIVATE
        Matrix2x3.cpp
)

target_include_directories(
        MatrixMultiplicationTests PRIVATE
        ${FGM_TEST_ROOT_DIR}/include

)


target_link_libraries(
        MatrixMultiplicationTests PRIVATE
        FGM
        GTest::gtest
        GTest::gtest_main
        StrictWarnings
        ProjectSanitizers
        NonComprehensiveTestMode
)