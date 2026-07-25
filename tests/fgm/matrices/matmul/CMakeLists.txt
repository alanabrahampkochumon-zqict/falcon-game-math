add_library(MatrixMultiplicationTests OBJECT)

target_sources(
        MatrixMultiplicationTests PRIVATE
        Mat2x3.cpp
        Mat2x4.cpp
        Mat3x2.cpp
        Mat3x4.cpp
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