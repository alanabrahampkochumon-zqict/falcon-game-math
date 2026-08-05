add_executable(FGMQuaternionsTests
        # Compilation Units
        ArithmeticOperationTests.cpp
        AccessAndMutationTests.cpp
        InitializationTests.cpp
        QuaternionAlgebra.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp
        VectorAlgebraTests.cpp

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
        REUSE_FROM
        FGMCommonTests
)


##############################
# Death Tests

add_executable(FGMQuaternionsDeathTests
        # Compilation Units
        death-tests/ArithmeticOperationDeathTests.cpp

        # Headers
        include/QuaternionTestSetup.h
)
set_target_properties(FGMQuaternionsDeathTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FGMQuaternionsDeathTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FGMQuaternionsDeathTests PROPERTIES CXX_EXTENSIONS OFF)

target_sources(
        FGMQuaternionsDeathTests

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${FGM_ROOT_INCLUDE_DIR}
        FILES
        ${SetupHeaderFiles}
        ${TestUtilities}
)

target_compile_options(FGMQuaternionsDeathTests INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)

target_link_libraries(
        FGMQuaternionsDeathTests
        PRIVATE
        FGMTestSetup
)

target_precompile_headers(
        FGMQuaternionsDeathTests
        REUSE_FROM
        FGMCommonTests
)


include(GoogleTest)
gtest_discover_tests(FGMQuaternionsTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)
gtest_discover_tests(FGMQuaternionsDeathTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)