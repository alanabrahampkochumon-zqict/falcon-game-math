add_executable(Playground)
target_compile_features(Playground PRIVATE cxx_std_20)

set(SourceDir "src/")
set(SourceFiles "main.cpp;")
list(TRANSFORM SourceFiles PREPEND ${SourceDir})

set(HeaderDir "include/")
set(HeaderFiles "Application.h")
list(TRANSFORM HeaderFiles PREPEND ${HeaderDir})

target_sources(
        Playground
        PRIVATE
        ${SourceFiles}

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${HeaderDir}
        FILES ${HeaderFiles}
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
)