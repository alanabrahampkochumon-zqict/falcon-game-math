add_library(FalconSIMD INTERFACE)

set(SIMDDir "include/simd/")

set(IncludeDirectory "include/")

set(GeneralFiles "SIMDUtils.h;DoxygenGroups.h")
list(TRANSFORM GeneralFiles PREPEND ${IncludeDirectory})

set(UtilityDir "include/utils/")
set(UtilityFiles "SIMDUtils.h")
list(TRANSFORM UtilityFiles PREPEND ${UtilityDir})

set(SIMDHeaderFiles "SIMD.h;SIMDMemory.tpp;")
list(TRANSFORM SIMDHeaderFiles PREPEND ${SIMDDir})

set(SIMDTemplateFiles "SIMD.tpp;SIMDMemory.tpp")
list(TRANSFORM SIMDTemplateFiles PREPEND ${SIMDDir})



target_compile_options(FalconSIMD INTERFACE # TODO: Change to the compile target
    $<$<CXX_COMPILER_ID:MSVC>:/W4;/wd4201;/wd26495;/wd26439>
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
    ${GeneralFiles}
    ${UtilityFiles}
    ${SIMDHeaderFiles}
    ${SIMDTemplateFiles}
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
    ${GeneralFiles}
    ${UtilityFiles}
    ${SIMDHeaderFiles}
    ${SIMDTemplateFiles}
)

source_group (
    TREE
    "${CMAKE_CURRENT_SOURCE_DIR}/${IncludeDirectory}"
    PREFIX "Header Files"
    FILES
    ${SIMDHeaderFiles}
    ${UtilityFiles}
    ${HeaderFiles}
)

source_group (
    TREE
    "${CMAKE_CURRENT_SOURCE_DIR}/${IncludeDirectory}"
    PREFIX "Template Files"
    FILES
    ${SIMDTemplateFiles}
)