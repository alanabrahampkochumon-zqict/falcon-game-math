set(IncludeDirectory "include/")

set(GeneralFiles "SimdTraits.h;DoxygenGroups.h")
list(TRANSFORM GeneralFiles PREPEND ${IncludeDirectory})

set(CommonDirectory "${IncludeDirectory}fgm/common/")
set(CommonHeaderFiles "MathTraits.h;Config.h;Constants.h;OperationStatus.h;Wrappers.h;PreprocessorDefinitions.h;Messages.h;Types.h;Utils.h;Utils.tpp;")
list(TRANSFORM CommonHeaderFiles PREPEND ${CommonDirectory})
set(CommonTemplateFiles "Wrappers.tpp;")
list(TRANSFORM CommonTemplateFiles PREPEND ${CommonDirectory})

set(VectorDirectory "${IncludeDirectory}fgm/vectors/")
set(VectorHeaderFiles Vector3D.h Vector2D.h Vector4D.h)
list(TRANSFORM VectorHeaderFiles PREPEND ${VectorDirectory})

set(VectorTemplateDefinitionFiles Vector2D.tpp Vector3D.tpp Vector4D.tpp)
list(TRANSFORM VectorTemplateDefinitionFiles PREPEND ${VectorDirectory})

set(MatrixDirectory "${IncludeDirectory}fgm/matrices/")
set(MatrixHeaderFiles Matrix2D.h Matrix3D.h Matrix4D.h)
list(TRANSFORM MatrixHeaderFiles PREPEND ${MatrixDirectory})

set(MatrixTemplateDefinitionFiles Matrix2D.tpp Matrix3D.tpp Matrix4D.tpp)
list(TRANSFORM MatrixTemplateDefinitionFiles PREPEND ${MatrixDirectory})

set(HeaderAliasFiles "Vec;Mat")
list(TRANSFORM HeaderAliasFiles PREPEND "${IncludeDirectory}/fgm/")


# To view this target as a Interface Library, we need to pass all the target files.
add_library(MathLib INTERFACE
        ${VectorHeaderFiles}
        ${VectorTemplateDefinitionFiles}
        ${MatrixHeaderFiles}
        ${MatrixTemplateDefinitionFiles}
        ${GeneralFiles}
        ${CommonHeaderFiles}
        ${CommonTemplateFiles}
        ${HeaderAliasFiles}
)

set_property(TARGET MathLib PROPERTY CXX_STANDARD 20)
set_property(TARGET MathLib PROPERTY CXX_STANDARD_REQUIRED ON)

# NOTE: If this flag is not enabled, then NAN less than and less than or equal comparison will not work properly.
target_compile_options(MathLib INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict>)


target_sources(MathLib
        INTERFACE
        FILE_SET HEADERS
        BASE_DIRS ${IncludeDirectory}
        FILES
        ${VectorHeaderFiles}
        ${VectorTemplateDefinitionFiles}
        ${MatrixHeaderFiles}
        ${MatrixTemplateDefinitionFiles}
        ${GeneralFiles}
        ${CommonHeaderFiles}
        ${CommonTemplateFiles}
        ${HeaderAliasFiles}
)


target_include_directories(
        MathLib
        INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"

)

source_group("Header Files" FILES ${GeneralFiles} ${HeaderAliasFiles})
source_group("Header Files\\vectors" FILES ${VectorHeaderFiles})
source_group("Header Files\\common" FILES ${CommonHeaderFiles})
source_group("Header Files\\matrix" FILES ${MatrixHeaderFiles})
source_group("Template Files\\vector" FILES ${VectorTemplateDefinitionFiles})
source_group("Template Files\\matrix" FILES ${MatrixTemplateDefinitionFiles})
source_group("Template Files\\common" FILES ${CommonTemplateFiles})
