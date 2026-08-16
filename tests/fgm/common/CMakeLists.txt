add_executable(FGMCommonTests)
set_target_properties(FGMCommonTests PROPERTIES DISABLE_PRECOMPILE_HEADERS OFF)
set_target_properties(FGMCommonTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FGMCommonTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FGMCommonTests PROPERTIES CXX_EXTENSIONS OFF)


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

target_precompile_headers(
        FGMCommonTests
        PUBLIC
        <gtest/gtest.h>
        <iostream>
        <limits>
        <concepts>
        <cstddef>
        <type_traits>
)

include(GoogleTest)

if (FGM_COMBINED_TEST_RUN)
    add_test(NAME FGMCommonTestSuite COMMAND FGMCommonTests)
else ()
    gtest_discover_tests(FGMCommonTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
endif ()
