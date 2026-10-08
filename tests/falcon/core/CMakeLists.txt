add_executable(FalconCoreTestSuite)
set_target_properties(FalconCoreTestSuite PROPERTIES CXX_STANDARD 20)
set_target_properties(FalconCoreTestSuite PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FalconCoreTestSuite PROPERTIES CXX_EXTENSIONS OFF)

target_sources(
        FalconCoreTestSuite
        PRIVATE
        traits/TypeHelpersTests.cpp
)

target_compile_options(FalconCoreTestSuite INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

target_precompile_headers(
        FalconCoreTestSuite
        PUBLIC

        <gtest/gtest.h>
        <limits>
        <concepts>
        <cstddef>
        <type_traits>
)

target_link_libraries(FalconCoreTestSuite PRIVATE FalconTestSetup)

include(GoogleTest)
if (FGM_COMBINED_TEST_RUN)
    add_test(NAME FalconCoreTestSuite COMMAND FGMCommonTests)
else ()
    gtest_discover_tests(FalconCoreTestSuite DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
endif ()