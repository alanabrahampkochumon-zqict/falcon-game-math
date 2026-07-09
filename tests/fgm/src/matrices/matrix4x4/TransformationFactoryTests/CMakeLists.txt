add_library(Matrix4x4TransformTests OBJECT)

target_sources(
        Matrix4x4TransformTests
        PRIVATE
            AffineTests.cpp
            ReflectionTests.cpp
            RotationTests.cpp
            ScaleTests.cpp
            ShearTests.cpp
            TranslationTests.cpp
)

target_include_directories(
        Matrix4x4TransformTests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${TEST_ROOT_DIR}/include
)

target_link_libraries(
        Matrix4x4TransformTests
        PRIVATE
            MathLib
            GTest::gtest
            GTest::gtest_main # googletest
)