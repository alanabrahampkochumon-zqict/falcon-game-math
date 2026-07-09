add_library(Matrix3x3TransformTests OBJECT)

target_sources(
        Matrix3x3TransformTests
        PRIVATE
            AffineTests.cpp
            ReflectionTests.cpp
            RotationTests.cpp
            ScaleTests.cpp
            ShearTests.cpp
            TranslationTests.cpp
)

target_include_directories(
        Matrix3x3TransformTests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${TEST_ROOT_DIR}/include
)

target_link_libraries(
        Matrix3x3TransformTests
        PRIVATE
            MathLib
            GTest::gtest
            GTest::gtest_main # googletest
)