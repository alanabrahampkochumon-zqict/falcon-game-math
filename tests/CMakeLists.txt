# For faster CI/CD unit-tests on push are only run with essential types rather than the full type permutation.
option(NONCOMPREHENSIVE "Run Unit tests with essential type matrix only")


# Add Project Sanitizers to Gtest
if (TARGET gtest)
    target_link_libraries(gtest PRIVATE ProjectSanitizers)
    target_link_libraries(gmock PRIVATE ProjectSanitizers)
    target_link_libraries(gtest_main PRIVATE ProjectSanitizers)
endif ()

add_subdirectory(fgm)
add_subdirectory(falcon_simd)

if (NONCOMPREHENSIVE)
    target_compile_definitions(FGMTestSuite PRIVATE NONCOMPREHENSIVE)
    target_compile_definitions(FalconSIMDTestSuite PRIVATE NONCOMPREHENSIVE)
endif ()

AddSIMDCompilerFlag(FGMTestSuite)
