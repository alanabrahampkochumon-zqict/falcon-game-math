# For faster CI/CD unit-tests on push are only run with essential types rather than the full type permutation.
option(NONCOMPREHENSIVE "Run Unit tests with essential type matrix only")
add_library(NonComprehensiveTestMode INTERFACE)

# Add Project Sanitizers to Gtest
if (TARGET gtest)
    target_link_libraries(gtest PRIVATE ProjectSanitizers)
    target_link_libraries(gmock PRIVATE ProjectSanitizers)
    target_link_libraries(gtest_main PRIVATE ProjectSanitizers)
endif ()

add_subdirectory(fgm)
add_subdirectory(falcon_simd)

if (NONCOMPREHENSIVE)
    message(STATUS "[FGM]: Running only non-comprehensive tests")
    target_compile_definitions(NonComprehensiveTestMode INTERFACE NONCOMPREHENSIVE)
endif ()

AddSIMDCompilerFlag(FGMTestSuite)
