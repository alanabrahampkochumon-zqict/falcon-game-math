add_executable(FalconSIMDUtilTests

        TypeTraitsTests.cpp
        SimdUtilsTests.cpp
)
set_target_properties(FalconSIMDUtilTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconSIMDUtilTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconSIMDUtilTests PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(FalconSIMDUtilTests PRIVATE ${FALCON_SIMD_TEST_ROOT_DIR}/include)

target_link_libraries(
        FalconSIMDUtilTests
        PRIVATE
        FalconSIMD
        GTest::gtest
        GTest::gtest_main # googletest
        ${PROJECT_NAME}-StrictWarnings
        ${PROJECT_NAME}-ProjectSanitizers
        #        NonComprehensiveTestMode
)