add_executable(FGMBenchmark)
set_target_properties(FGMBenchmark PROPERTIES CXX_STANDARD 20)
set_target_properties(FGMBenchmark PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(FGMBenchmark PROPERTIES CXX_EXTENSIONS OFF)

target_sources(FGMBenchmark PRIVATE
        SampleBenchmark.cpp
)

target_precompile_headers(
        FGMBenchmark
        PRIVATE
        <benchmark/benchmark.h>
#        <fgm>
)

target_link_libraries(
        FGMBenchmark
        PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
        FGM

        StrictWarnings
        ProjectSanitizers
)
