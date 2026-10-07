set(FALCON_CORE_TARGET_NAME FalconCore${FALCON_INTERNAL_TARGET_SUFFIX})
add_library(${FALCON_CORE_TARGET_NAME} INTERFACE
        traits/TypeHelpers.h

        Preprocessors.h
        DoxygenGroups.h
)
set_target_properties(${FALCON_CORE_TARGET_NAME} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

# TODO: Remove internal target linkages(as this can fail on builds not running in strict mode)
target_link_libraries(${FALCON_CORE_TARGET_NAME} INTERFACE
        ${PROJECT_NAME}-StrictWarnings
        ${PROJECT_NAME}-ProjectSanitizers
)

target_include_directories(${FALCON_CORE_TARGET_NAME} INTERFACE ${FALCON_LIBRARY_ROOT_DIR})