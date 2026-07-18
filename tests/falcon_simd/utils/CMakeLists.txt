add_library(FalconSIMDUtilTests OBJECT)

target_sources(
        FalconSIMDUtilTests PRIVATE
        SimdUtilsTests.cpp
)

target_include_directories(FalconSIMDUtilTests PRIVATE ${FALCON_SIMD_TEST_ROOT_DIR}/include)

target_link_libraries(
        FalconSIMDUtilTests
        PRIVATE
        FalconSIMD
        GTest::gtest
        GTest::gtest_main # googletest
        StrictWarnings
        ProjectSanitizers
        NonComprehensiveTestMode
)