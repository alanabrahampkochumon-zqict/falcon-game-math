add_executable(Playground)
target_compile_features(Playground PRIVATE cxx_std_20)

set(SourceDir "src/")
set(SourceFiles "main.cpp;")
list(TRANSFORM SourceFiles PREPEND ${SourceDir})

target_sources(
        Playground
        PRIVATE
        ${SourceDir}
)

target_link_libraries(
        Playground
        PRIVATE
        MathLib
        SDL3::SDL3
)