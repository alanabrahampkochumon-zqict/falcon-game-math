add_library(Point2Tests OBJECT)

target_sources(
        Point2Tests PRIVATE
        ArithmeticOperationTests.cpp
        InitializationTests.cpp
)

target_include_directories(
        Point2Tests PRIVATE
        ${FGM_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Point2Tests PRIVATE
        FGMTestSetup
)