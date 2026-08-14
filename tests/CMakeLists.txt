# For faster CI/CD unit-tests on push are only run with essential types rather than the full type permutation.
option(NONCOMPREHENSIVE "Run Unit tests with essential type matrix only")
set(ENV{FALCON_SIMD_TEST_FLAG} "AUTO") # SIMD Test Flags for Falcon Math Suite

# Add Project Sanitizers to Gtest
if (TARGET gtest AND (FGM_TESTS OR FALCON_SIMD_TESTS))
    target_link_libraries(gtest PRIVATE ProjectSanitizers)
    target_link_libraries(gmock PRIVATE ProjectSanitizers)
    target_link_libraries(gtest_main PRIVATE ProjectSanitizers)
endif ()


#----------------------------------
# Falcon Game Math(FGM) Test Setup
#----------------------------------
add_library(FGMTestSetup INTERFACE)
target_link_libraries(FGMTestSetup INTERFACE
        FGM
        GTest::gtest
        GTest::gtest_main
        StrictWarnings
        ProjectSanitizers
)
target_compile_definitions(FGMTestSetup INTERFACE $<$<CONFIG:Debug>:ENABLE_DEBUG_TESTS>)

if (NONCOMPREHENSIVE)
    message(STATUS "[FGM]: Running only non-comprehensive tests")
    target_compile_definitions(FGMTestSetup INTERFACE NONCOMPREHENSIVE)
    target_compile_definitions(FGMTestSetup INTERFACE $ENV{FALCON_SIMD_TEST_FLAG})
endif ()

if (FGM_TESTS)
    message("[FGM]: Game Math Tests are enabled")
    add_subdirectory(fgm)
endif ()


#----------------------------------
# Falcon SIMD Test Setup
#----------------------------------
add_library(FalconSimdTestSetup INTERFACE)
target_link_libraries(FalconSimdTestSetup INTERFACE
        FalconSIMD
        GTest::gtest
        GTest::gtest_main
        StrictWarnings
        ProjectSanitizers
)
# TODO: Add simd vectorization flags to this project


if (FALCON_SIMD_TESTS)
    message("[FGM]: SIMD tests are enabled")
    add_subdirectory(falcon_simd)
endif ()
