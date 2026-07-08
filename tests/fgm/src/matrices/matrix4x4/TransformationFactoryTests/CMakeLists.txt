add_library(TestMat4Transform OBJECT)

target_sources(
        TestMat4Transform
        PRIVATE
            AffineTests.cpp
            ReflectionTests.cpp
            RotationTests.cpp
            ScaleTests.cpp
            ShearTests.cpp
            TranslationTests.cpp
)

target_include_directories(
        TestMat4Transform
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${TEST_ROOT_DIR}/include
)

target_link_libraries(
        TestMat4Transform
        PRIVATE
            MathLib
            GTest::gtest
            GTest::gtest_main # googletest
)