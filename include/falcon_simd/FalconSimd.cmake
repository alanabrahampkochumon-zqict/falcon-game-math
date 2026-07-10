include_guard()


set(FALCON_SIMD_DIR ${LIBRARY_ROOT_DIR}/falcon_simd/)
set(FALCON_SIMD_ROOT_HEADERS
        SIMD.h
        SIMD.tpp
        SIMDMemory.h
        SIMDMemory.tpp

        DoxygenGroups.h
)

include(${FALCON_SIMD_DIR}utils/Utils.cmake)

set(FALCON_SIMD_HEADERS ${FALCON_SIMD_ROOT_HEADERS} ${FALCON_SIMD_UTILS_HEADERS})
list(TRANSFORM FALCON_SIMD_HEADERS PREPEND ${FALCON_SIMD_DIR})




#add_library(FalconSIMD INTERFACE)
#
## Directories
#set(IncludeDir "${CMAKE_CURRENT_SOURCE_DIR}/include/")
#set(UtilityDir "${IncludeDir}utils/")
#set(SIMDDir "${IncludeDir}simd/")
#
## Files
#set(UtilityFiles "SIMDUtils.h")
#list(TRANSFORM UtilityFiles PREPEND ${UtilityDir})
#
#set(SIMDHeaderFiles "SIMD.h;SIMDMemory.h;")
#list(TRANSFORM SIMDHeaderFiles PREPEND ${SIMDDir})
#
#set(SIMDTemplateFiles "SIMD.tpp;SIMDMemory.tpp")
#list(TRANSFORM SIMDTemplateFiles PREPEND ${SIMDDir})
#
#
#target_compile_options(FalconSIMD INTERFACE # TODO: Change to the compile target
#        $<$<CXX_COMPILER_ID:MSVC>:/W4;/wd4201;/wd26495;/wd26439>
#        $<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wpedantic;-Wno-gnu-anonymous-struct;-Werror;>
#        $<$<CXX_COMPILER_ID:Clang>:-Wall;-Wextra;-Wpedantic;-Wno-gnu-anonymous-struct;-Werror;>
#)
#
#target_compile_options(FalconSIMD INTERFACE
#        $<$<CXX_COMPILER_ID:MSVC>:/arch:AVX2>
#        $<$<CXX_COMPILER_ID:GNU>:-mavx2>
#        $<$<CXX_COMPILER_ID:Clang>:-mavx2>
#)
#
#target_sources(
#        FalconSIMD
#        INTERFACE
#        FILE_SET HEADERS
#        BASE_DIRS ${IncludeDirectory}
#        FILES
#        ${UtilityFiles}
#        ${SIMDHeaderFiles}
#        ${SIMDTemplateFiles}
#)
#
#
#target_include_directories(
#        FalconSIMD
#        INTERFACE
#        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
#        "$<INSTALL_INTERFACE:include>"
#)
#
#add_custom_target(
#        SIMD
#        ALL
#        SOURCES
#        ${DocFiles}
#        ${UtilityFiles}
#        ${SIMDHeaderFiles}
#        ${SIMDTemplateFiles}
#)
#
#source_group(
#        TREE
#        "${CMAKE_CURRENT_SOURCE_DIR}/${IncludeDirectory}"
#        PREFIX "Header Files"
#        FILES
#        ${SIMDHeaderFiles}
#        ${UtilityFiles}
#)
#
#source_group(
#        TREE
#        "${CMAKE_CURRENT_SOURCE_DIR}/${DocsDir}"
#        PREFIX "Documentation Files"
#        FILES
#        ${DocFiles}
#)
#
#source_group(
#        TREE
#        "${CMAKE_CURRENT_SOURCE_DIR}/${IncludeDirectory}"
#        PREFIX "Template Files"
#        FILES
#        ${SIMDTemplateFiles}
#)