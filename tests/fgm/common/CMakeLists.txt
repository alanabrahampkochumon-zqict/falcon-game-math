add_executable(FGMCommonTests)

target_sources(
        FGMCommonTests PRIVATE
        MathTraitTests.cpp
        OperationStatusTests.cpp
        TrivialTypeTests.cpp
        UtilsTests.cpp
        WrapperTests.cpp
)

target_include_directories(
        FGMCommonTests PRIVATE
        ${FGM_TEST_ROOT_DIR}/include
)


target_link_libraries(
        FGMCommonTests PRIVATE
        FGMTestSetup
)

include(GoogleTest)
gtest_discover_tests(FGMCommonTests DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 180)