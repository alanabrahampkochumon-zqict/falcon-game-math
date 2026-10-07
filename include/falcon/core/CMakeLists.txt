add_library(FalconCore INTERFACE
        traits/TypeHelpers.h

        Preprocessors.h
        DoxygenGroups.h
)
set_target_properties(FalconCore PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

# TODO: Remove internal target linkages(as this can fail on builds not running in strict mode)
target_link_libraries(FalconCore INTERFACE
        ${PROJECT_NAME}-StrictWarnings
        ${PROJECT_NAME}-ProjectSanitizers
)

target_include_directories(FalconCore INTERFACE ${FALCON_LIBRARY_ROOT_DIR})