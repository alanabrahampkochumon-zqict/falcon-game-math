add_library(FalconSIMD INTERFACE)

set(IncludeDirectory "Include/")
set(HeaderFiles "SIMD.h;SIMDUtils.h")
list(TRANSFORM HeaderFiles PREPEND ${IncludeDirectory})

set(TemplateFiles "SIMD.tpp")
list(TRANSFORM TemplateFiles PREPEND ${IncludeDirectory})

target_compile_options(FalconSIMD INTERFACE # TODO: Change to the compile target
    $<$<CXX_COMPILER_ID:MSVC>:/W4;/wd4201>
    $<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wpedantic;-Wno-gnu-anonymous-struct;-Werror;>
    $<$<CXX_COMPILER_ID:Clang>:-Wall;-Wextra;-Wpedantic;-Wno-gnu-anonymous-struct;-Werror;>
)

target_compile_options(FalconSIMD INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/arch:AVX2>
    $<$<CXX_COMPILER_ID:GNU>:-mavx2>
    $<$<CXX_COMPILER_ID:Clang>:-mavx2>
)

target_sources(
    FalconSIMD
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${IncludeDirectory}
    FILES
    ${HeaderFiles}
    ${TemplateFiles}
)


target_include_directories(
    FalconSIMD
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

add_custom_target(
    SIMD
    ALL
    SOURCES
    ${HeaderFiles}
    ${TemplateFiles}
)

source_group("Header Files" ${HeaderFiles})
source_group("Template Files" ${TemplateFiles})
