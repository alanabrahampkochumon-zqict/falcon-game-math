add_library(Mat4TransformTests OBJECT)

target_sources(
        Mat4TransformTests
        PRIVATE
        AffineTests.cpp
        ReflectionTests.cpp
        RotationTests.cpp
        ScaleTests.cpp
        ShearTests.cpp
        TranslationTests.cpp
)

target_include_directories(
        Mat4TransformTests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${FGM_TEST_ROOT_DIR}/include
)

target_link_libraries(
        Mat4TransformTests
        PRIVATE
        FGM
        GTest::gtest
        GTest::gtest_main # googletest
        StrictWarnings
        ProjectSanitizers
        NonComprehensiveTestMode
)