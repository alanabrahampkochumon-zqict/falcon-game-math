cmake_minimum_required(VERSION 3.25)

project(FalconGameMath LANGUAGES CXX)

add_library(StrictWarnings INTERFACE)
add_library(ProjectSanitizers INTERFACE)

# Clang Formatter
find_program(CLANG_FORMATTER NAMES clang-format)
find_program(CLANG_TIDY_EXE NAMES clang-tidy)

if(CLANG_FORMATTER)
    file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h *.cxx *.hxx *.hpp *.cc *.hh *.tpp *.inl)

    add_custom_target(format
        COMMAND ${CLANG_FORMATTER} -i -style=file ${ALL_SOURCE_FILES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Formatting source files..."
    )
else()
    message(WARNING "clang-format not found")
endif()

if(CLANG_TIDY_EXE)
    # Create a custom target that you manually trigger
    add_custom_target(
        lint
        COMMAND ${CMAKE_COMMAND} -E echo "Running Clang-Tidy on MathLib..."
        COMMAND run-clang-tidy -p ${CMAKE_BINARY_DIR} -header-filter=.*
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running static analysis..."
    )
else()
    message(WARNING "clang-tidy not found")
endif()

option(CMAKE_EXPORT_COMPILE_COMMANDS ON)


option(ENABLE_STRICT "Enable ASan and Strict Warnings" OFF) # To turn on ASan, use cmake -D

# Doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
    message(STATUS "Doxygen found!")
    doxygen_add_docs(
        docs
        ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating documentation with doxygen..."
        CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        ALL
    )
else()
    message(WARN "Doxygen not found! Skipping documentation generation.")
endif()


# Turn on solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Enables Strict Warnings and Debug-only ASan
if(ENABLE_STRICT)
    message(STATUS "Configuring Strict Warnings (ASan enabled for Debug builds only)")
    if(MSVC AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(StrictWarnings INTERFACE $<$<CONFIG:Debug>:/fsanitize=address;/Zi>)
        target_link_options(StrictWarnings INTERFACE $<$<CONFIG:Debug>:/INCREMENTAL:NO>)
    else()
        target_compile_options(StrictWarnings INTERFACE $<$<CONFIG:Debug>:-fsanitize=address;-fno-omit-frame-pointer>)
        target_link_options(StrictWarnings INTERFACE $<$<CONFIG:Debug>:-fsanitize=address>)
    endif()

    if(MSVC AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(StrictWarnings INTERFACE
            $<$<COMPILE_LANGUAGE:CXX>:/WX;/W4;/permissive-;/fp:strict>
        )
    else()
        target_compile_options(StrictWarnings INTERFACE
            $<$<COMPILE_LANGUAGE:CXX>:-Wall;-Wextra;-Werror;-pedantic-errors>
            $<$<CXX_COMPILER_ID:Clang>:-Wno-c++98-compat;-Wno-c++98-compat-pedantic;-Wno-pre-c++14-compat;-Wno-pre-c++17-compat;-Wno-c++20-compat>
            $<$<CXX_COMPILER_ID:AppleClang>:-Wno-c++98-compat;-Wno-c++98-compat-pedantic;-Wno-pre-c++14-compat;-Wno-pre-c++17-compat;-Wno-c++20-compat>
        )
    endif()
endif()

# Multi-processor compilation
if(MSVC AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Enabling Multiprocessor compilation on MSVC")
    add_compile_options("/MP")
endif()

include(dependencies.cmake)
if(TARGET gtest)
    target_link_libraries(gtest PRIVATE ProjectSanitizers)
    target_link_libraries(gmock PRIVATE ProjectSanitizers)
    target_link_libraries(gtest_main PRIVATE ProjectSanitizers)
endif()

include(simdcheck.cmake)

add_subdirectory(math-lib)
add_subdirectory(playground)
add_subdirectory(test-suite)
add_subdirectory(simd)

target_compile_features(TestSuite PRIVATE cxx_std_20)
target_compile_features(FalconSIMD INTERFACE cxx_std_20)
target_compile_features(MathLib INTERFACE cxx_std_20)
target_compile_features(Playground PRIVATE cxx_std_20)


target_link_libraries(TestSuite PRIVATE StrictWarnings ProjectSanitizers)
target_link_libraries(FalconSIMD INTERFACE StrictWarnings ProjectSanitizers)
target_link_libraries(MathLib INTERFACE StrictWarnings ProjectSanitizers)
target_link_libraries(Playground PRIVATE StrictWarnings ProjectSanitizers)

set_target_properties(
    docs format lint
    PROPERTIES FOLDER "Dev Utilities"
)

AddSIMDCompilerFlag(TestSuite)


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Playground)