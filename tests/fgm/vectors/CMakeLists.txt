add_executable(FGMVectorTests)
set_target_properties(FGMVectorTests PROPERTIES CXX_STANDARD 20)
set_target_properties(FGMVectorTests PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FGMVectorTests PROPERTIES CXX_EXTENSIONS OFF)

target_sources(
        FGMVectorTests

        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${FGM_ROOT_INCLUDE_DIR}
        FILES
        ${SetupHeaderFiles}
        ${TestUtilities}
)

target_compile_options(FGMVectorTests INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict;>)


add_subdirectory(point2)
add_subdirectory(point3)
add_subdirectory(vec2)
add_subdirectory(vec3)
add_subdirectory(vec4)

target_link_libraries(
        FGMVectorTests
        PRIVATE
        FGMTestSetup

        # OBJs
        Point2Tests
        Point3Tests
        Vec2Tests
        Vec3Tests
        Vec4Tests
)

target_precompile_headers(
        FGMVectorTests
        REUSE_FROM
        FGMCommonTests
)


include(GoogleTest)
gtest_discover_tests(FGMVectorTests DISCOVERY_MODE POST_BUILD DISCOVERY_TIMEOUT 180)

set_target_properties(
        Point2Tests
        Point3Tests
        Vec2Tests
        Vec3Tests
        Vec4Tests
        PROPERTIES FOLDER "Test Intermediates/FGM"
)