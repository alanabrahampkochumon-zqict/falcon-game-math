add_executable(Playground)
target_compile_features(Playground PRIVATE cxx_std_20)

set(SourceDir "src/")
set(SourceFiles "main.cpp;")
list(TRANSFORM SourceFiles PREPEND ${SourceDir})

set(HeaderDir "include/")
set(HeaderFiles "Application.h;Mesh.h;Renderer.h")
list(TRANSFORM HeaderFiles PREPEND ${HeaderDir})

set(ParserDir "${HeaderDir}parsers/")
set(ParserFiles "ObjectParser.h")
list(TRANSFORM ParserFiles PREPEND ${ParserDir})

target_sources(
        Playground
        PRIVATE
        ${SourceFiles}

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${HeaderDir}
        FILES ${HeaderFiles} ${ParserFiles}
)

target_include_directories(
        Playground
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)


target_link_libraries(
        Playground
        PRIVATE
        MathLib
        SDL3::SDL3
        fast_float
)

# Copy models directory to the build directory
add_custom_command(
        TARGET Playground
        POST_BUILD
        # Create the directory
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:Playground>/models"
        # Copy files into the target directory
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/models"
        "$<TARGET_FILE_DIR:Playground>/models"

        COMMENT "Copying models to build directory"
)