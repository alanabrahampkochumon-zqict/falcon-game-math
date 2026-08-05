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

# Add test setup library to make the linking per subdirectory target easy
add_library(FGMTestSetup INTERFACE)
target_link_libraries(FGMTestSetup INTERFACE
        FGM
        GTest::gtest
        GTest::gtest_main
        StrictWarnings
        ProjectSanitizers
)
target_compile_definitions(FGMTestSetup INTERFACE $<$<CONFIG:Debug>:ENABLE_DEBUG_TESTS>)

# TODO: Update Falcon SIMD to use a similar TEST SETUP
if (NONCOMPREHENSIVE)
    message(STATUS "[FGM]: Running only non-comprehensive tests")
    target_compile_definitions(FGMTestSetup INTERFACE NONCOMPREHENSIVE)
endif ()

# AddSIMDCompilerFlag(FGMTestSuite)
