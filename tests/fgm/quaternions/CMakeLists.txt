add_executable(FGMQuaternionsTests
        # Compilation Units
        AccessAndMutationTests.cpp
        InitializationTests.cpp

        # Headers
        include/QuaternionTestSetup.h
)
set_target_properties(FGMQuaternionsTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FGMQuaternionsTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FGMQuaternionsTests PROPERTIES CXX_EXTENSIONS OFF)

target_sources(
        FGMQuaternionsTests

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${FGM_ROOT_INCLUDE_DIR}
        FILES
        ${SetupHeaderFiles}
        ${TestUtilities}
)

target_compile_options(FGMQuaternionsTests INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

target_link_libraries(
        FGMQuaternionsTests
        PRIVATE
        FGMTestSetup
)

target_precompile_headers(
        FGMQuaternionsTests
        PRIVATE
        <gtest/gtest.h>
        <iostream>
        <limits>
        <concepts>
        <cstddef>
        <type_traits>
)


include(GoogleTest)
gtest_discover_tests(FGMQuaternionsTests DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 180)