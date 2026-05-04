
set(IncludeDirectory "Include/")
set(HeaderFiles "SIMD.h;SIMDUtils.h;DoxygenGroups.h")
list(TRANSFORM HeaderFiles PREPEND ${IncludeDirectory})

set(TemplateFiles "SIMD.tpp")
list(TRANSFORM TemplateFiles PREPEND ${IncludeDirectory})


add_library(FalconSIMD INTERFACE ${HeaderFiles} ${TemplateFiles})

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

source_group("Header Files" ${HeaderFiles})
source_group("Template Files" ${TemplateFiles})
