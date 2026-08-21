add_library(FalconCore INTERFACE
        traits/TypeHelpers.h
        Preprocessors.h

        DoxygenGroups.h
)
target_compile_features(FalconCore INTERFACE cxx_std_20)
target_link_libraries(FalconCore INTERFACE
        StrictWarnings
        ProjectSanitizers
)

target_include_directories(FalconCore INTERFACE ${LIBRARY_ROOT_DIR})