option(ENABLE_FGM_TEST "Enable FGM Unit Tests")

# For faster CI/CD unit-tests on push are only run with essential types rather than the full type permutation.
option(NONCOMPREHENSIVE "Run Unit tests with essential type matrix only")

if (ENABLE_FGM_TEST)
    message("Test suite is enabled")

    # Add Project Sanitizers to Gtest
    if (TARGET gtest)
        target_link_libraries(gtest PRIVATE ProjectSanitizers)
        target_link_libraries(gmock PRIVATE ProjectSanitizers)
        target_link_libraries(gtest_main PRIVATE ProjectSanitizers)
    endif ()

    add_subdirectory(fgm)
    add_subdirectory(simd)
    target_compile_features(MathTestSuite PRIVATE cxx_std_20)
    target_compile_features(SIMDTestSuite PRIVATE cxx_std_20)
    target_link_libraries(MathTestSuite PRIVATE StrictWarnings ProjectSanitizers)
    target_link_libraries(SIMDTestSuite PRIVATE StrictWarnings ProjectSanitizers)

    if (NONCOMPREHENSIVE)
        target_compile_definitions(MathTestSuite PRIVATE NONCOMPREHENSIVE)
        target_compile_definitions(SIMDTestSuite PRIVATE NONCOMPREHENSIVE)
    endif ()

    AddSIMDCompilerFlag(MathTestSuite)
endif ()