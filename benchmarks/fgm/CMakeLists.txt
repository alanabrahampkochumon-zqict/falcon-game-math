add_executable(FALCONBenchmark)
set_target_properties(FALCONBenchmark PROPERTIES CXX_STANDARD 20)
set_target_properties(FALCONBenchmark PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FALCONBenchmark PROPERTIES CXX_EXTENSIONS OFF)

target_sources(FALCONBenchmark PRIVATE
        SampleBenchmark.cpp
)

target_precompile_headers(
        FALCONBenchmark
        PRIVATE
        <benchmark/benchmark.h>
)

target_link_libraries(
        FALCONBenchmark
        PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
        Falcon::Falcon

        ${PROJECT_NAME}-StrictWarnings
        ${PROJECT_NAME}-ProjectSanitizers
)
