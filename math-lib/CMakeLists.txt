add_library(MathLib INTERFACE)

set_property(TARGET MathLib PROPERTY CXX_STANDARD 20)
set_property(TARGET MathLib PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_options(MathLib INTERFACE # TODO: Change to the compile target
    $<$<CXX_COMPILER_ID:MSVC>:/W4;/wd4201;/wd26495;/wd26439>
    $<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wpedantic;-Wno-gnu-anonymous-struct;-Werror;>
    $<$<CXX_COMPILER_ID:Clang>:-Wall;-Wextra;-Wpedantic;-Wno-gnu-anonymous-struct;-Werror;>
)

target_compile_options(MathLib INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/arch:AVX2>
    $<$<CXX_COMPILER_ID:GNU>:-mavx2>
    $<$<CXX_COMPILER_ID:Clang>:-mavx2>
)

# NOTE: If this flag is not enabled, then NAN less than and less than or equal comparison will not work properly.
target_compile_options(MathLib INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict>)

set(IncludeDirectory "include/")


set(GeneralFiles "SimdTraits.h;DoxygenGroups.h")
list(TRANSFORM GeneralFiles PREPEND ${IncludeDirectory})

set(CommonDirectory "${IncludeDirectory}common/")
set(CommonFiles "MathTraits.h;Config.h;Constants.h;OperationStatus.h")
list(TRANSFORM CommonFiles PREPEND ${CommonDirectory})

set(VectorDirectory "${IncludeDirectory}vector/")
set(VectorHeaderFiles Vector3D.h Vector2D.h Vector4D.h)
list(TRANSFORM VectorHeaderFiles PREPEND ${VectorDirectory})

set(VectorTemplateDefinitionFiles Vector2D.tpp Vector3D.tpp Vector4D.tpp)
list(TRANSFORM VectorTemplateDefinitionFiles PREPEND ${VectorDirectory})

set(MatrixDirectory "${IncludeDirectory}matrix/")
set(MatrixHeaderFiles Matrix2D.h Matrix3D.h Matrix4D.h)
list(TRANSFORM MatrixHeaderFiles PREPEND ${MatrixDirectory})

set(MatrixTemplateDefinitionFiles Matrix2D.tpp Matrix3D.tpp Matrix4D.tpp)
list(TRANSFORM MatrixTemplateDefinitionFiles PREPEND ${MatrixDirectory})


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
        ${CommonFiles}
)


target_include_directories(
    MathLib
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"

)

add_custom_target(
    Math
    ALL
    SOURCES
    ${VectorHeaderFiles}
    ${VectorTemplateDefinitionFiles}
    ${MatrixHeaderFiles}
    ${MatrixTemplateDefinitionFiles}
    ${GeneralFiles}
    ${CommonFiles}
)

source_group("Header Files\\vector" FILES ${VectorHeaderFiles})
source_group("Header Files\\common" FILES ${CommonFiles})
source_group("Template Files\\vector" FILES ${VectorTemplateDefinitionFiles})
source_group("Header Files\\matrix" FILES ${MatrixHeaderFiles})
source_group("Template Files\\matrix" FILES ${MatrixTemplateDefinitionFiles})