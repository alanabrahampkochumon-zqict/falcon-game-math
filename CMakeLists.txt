cmake_minimum_required(VERSION 3.25)
project(CPPMathLib)


# Clang Formatter
find_program(CLANG_FORMATTER NAMES clang-format)

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

# Enables ASan for all the projects globally.
if(ENABLE_STRICT)
    message("Turning ASan on")
    if(MSVC)
        add_compile_options(/fsanitize=address)
    else()
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    endif()
endif()


include(dependencies.cmake)
include(simdcheck.cmake)

add_subdirectory(math-lib)
add_subdirectory(playground)
add_subdirectory(test-suite)
add_subdirectory(simd)

AddSIMDCompilerFlag(TestSuite)


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Playground)