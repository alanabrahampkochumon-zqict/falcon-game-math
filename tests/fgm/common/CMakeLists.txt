add_library(CommonTests OBJECT)

target_sources(
        CommonTests PRIVATE
        MathTraitTests.cpp
        OperationStatusTests.cpp
        TrivialTypeTests.cpp
        UtilsTests.cpp
        WrapperTests.cpp
)

target_include_directories(
        CommonTests PRIVATE
        ${FGM_TEST_ROOT_DIR}/include
)


target_link_libraries(
        CommonTests PRIVATE
        FGM
        GTest::gtest
        GTest::gtest_main
        NonComprehensiveTestMode
)