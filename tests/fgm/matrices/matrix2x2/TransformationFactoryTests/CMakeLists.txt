add_library(Matrix2TransformTests OBJECT)

target_sources(
        Matrix2TransformTests PRIVATE
        ReflectionTests.cpp
        RotationTests.cpp
        ScaleTests.cpp
        ShearTests.cpp
)

target_include_directories(
        Matrix2TransformTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${FGM_TEST_ROOT_DIR}/include
)

target_link_libraries(
        Matrix2TransformTests PRIVATE
        FGM
        GTest::gtest
        GTest::gtest_main # googletest
)