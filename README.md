[![Unit Tests](https://github.com/alanabrahampkochumon-zqict/falcon-game-math/actions/workflows/unit-tests.yml/badge.svg)](https://github.com/alanabrahampkochumon-zqict/falcon-game-math/actions/workflows/unit-tests.yml)

# Falcon Game Math

High performance math library written in modern C++. *Requires C++20 or above*

## Requirements

* <a href="https://cmake.org/download/" target="_blank">CMake 3.26</a> or above
* <a href="https://cmake.org/download/" target="_blank">Git</a>

## CMake Options

### General

- ENABLE_FGM_DEMO Enables FGM Demo Application
- ENABLE_FGM_DOCS Enables FGM Documentation Generation

### Testing and Benchmarks

- ENABLE_FGM_BENCHMARK Enables FGM Benchmark Suite
- ENABLE_FGM_TEST: Enable FGM Unit Tests
- NONCOMPREHENSIVE: Run Unit tests with essential type matrix only

## How to run

1. Generate project files using
    ```bash
        cmake -B build -DENABLE_FGM_DEMO
    ```

2. Run the build using commandline
    ```bash
        cmake --build build
        ./build/playground/Debug/Playground.exe # To Run the playground
    ```
   OR
   Run it in Visual Studio or your IDE of choice.

## References

- <a href="https://foundationsofgameenginedev.com/" target="_blank">Eric Lengyel's Foundations of Game Engine
  Development
  Series</a>
- <a href="https://gamemath.com/" target="_blank">3D Math Primer for Graphics and Game Engine Development</a>
