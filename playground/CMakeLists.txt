add_executable(Playground)
target_compile_features(Playground PRIVATE cxx_std_20)

target_sources(
        Playground
        PRIVATE
        main.cpp
)

target_link_libraries(
        Playground
        PRIVATE
        MathLib
        SDL3::SDL3
)