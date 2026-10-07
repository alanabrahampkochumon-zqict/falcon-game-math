add_library(FalconGameMath INTERFACE
        common/Config.h
        common/Constants.h
        common/MathTraits.h
        common/Messages.h
        common/OperationStatus.h
        common/Types.h
        common/Utils.h
        common/Utils.tpp
        common/Wrappers.h
        common/Wrappers.tpp

        matrices/Mat2.h
        matrices/Mat2.tpp
        matrices/Mat2x3.h
        matrices/Mat2x3.tpp
        matrices/Mat2x4.h
        matrices/Mat2x4.tpp
        matrices/Mat3x2.h
        matrices/Mat3x2.tpp
        matrices/Mat3.tpp
        matrices/Mat3.h
        matrices/Mat3x4.h
        matrices/Mat3x4.tpp
        matrices/Mat4.h
        matrices/Mat4.tpp
        matrices/Mat4x2.h
        matrices/Mat4x2.tpp
        matrices/Mat4x3.h
        matrices/Mat4x3.tpp
        matrices/extra/Comp.h
        matrices/extra/Comp.tpp
        matrices/extra/Geom.h
        matrices/extra/Geom.tpp
        matrices/Transform4.h
        matrices/Transform4.tpp

        # NON-SIMD CONSTEXPR WRAPPERS
        vectors/CVec2.h
        vectors/CVec2.tpp
        vectors/Point2.h
        vectors/Point2.tpp
        vectors/Point3.h
        vectors/Point3.tpp
        vectors/Vec3.h
        vectors/Vec3.tpp
        vectors/Vec4.h
        vectors/Vec4.tpp

        # SIMD-ACCELERATED WRAPPER
        vectors/Vec2.h
        vectors/Vec2.tpp
)

target_compile_options(FalconGameMath INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict>)
set_target_properties(FalconGameMath PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
# TODO: Remove internal target linkages(as this can fail on builds not running in strict mode)
# TODO: Remove for all targets
target_link_libraries(FalconGameMath INTERFACE
        ${PROJECT_NAME}-StrictWarnings
        ${PROJECT_NAME}-ProjectSanitizers
)

target_include_directories(FalconGameMath INTERFACE ${FALCON_LIBRARY_ROOT_DIR})