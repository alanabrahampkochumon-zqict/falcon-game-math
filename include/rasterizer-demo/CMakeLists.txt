add_executable(RasterizerDemo)
target_compile_features(RasterizerDemo PRIVATE cxx_std_20)

# Directories
set(SourceDir "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(HeaderDir "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(ParserDir "${HeaderDir}parsers/")

# Files
set(SourceFiles "main.cpp;")
list(TRANSFORM SourceFiles PREPEND ${SourceDir})

set(HeaderFiles "Application.h;Mesh.h;Renderer.h")
list(TRANSFORM HeaderFiles PREPEND ${HeaderDir})

set(ParserFiles "ObjectParser.h")
list(TRANSFORM ParserFiles PREPEND ${ParserDir})

target_sources(
        RasterizerDemo
        PRIVATE
        ${SourceFiles}

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${HeaderDir}
        FILES ${HeaderFiles} ${ParserFiles}
)

target_include_directories(
        RasterizerDemo
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)


target_link_libraries(
        RasterizerDemo
        PRIVATE
        FGM
        SDL3::SDL3
        fast_float
)

# Copy models directory to the build directory
add_custom_command(
        TARGET RasterizerDemo
        POST_BUILD
        # Create the directory
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:RasterizerDemo>/models"
        # Copy files into the target directory
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/models"
        "$<TARGET_FILE_DIR:RasterizerDemo>/models"

        COMMENT "Copying models to build directory"
)