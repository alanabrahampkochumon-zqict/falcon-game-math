add_executable(FalconSIMDMemoryTests
        Simd128/ArithmeticTests.cpp
        Simd128/ComparisonTests.cpp
        Simd128/ConversionCtorTests.cpp
        Simd128/GetterSetterTests.cpp
        Simd128/LoadStoreTests.cpp
)

target_include_directories(FalconSIMDMemoryTests PRIVATE "${FALCON_SIMD_TEST_ROOT_DIR}/include")

target_link_libraries(
        FalconSIMDMemoryTests
        PRIVATE
        FalconSIMD
        GTest::gtest
        GTest::gtest_main # googletest

        StrictWarnings
        ProjectSanitizers
)

AddCompilerFlag(FalconSIMDMemoryTests PUBLIC ${FALCON_SIMD_MODE}) # Update to compile an executable per flag

if (FALCON_SIMD_COMBINED_TEST_RUN)
    add_test(NAME FalconSIMDMemoryTestSuite COMMAND FalconSIMDMemoryTests)
else ()
    gtest_discover_tests(FalconSIMDMemoryTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
endif ()