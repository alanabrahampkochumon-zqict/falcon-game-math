add_library(FalconSIMD INTERFACE
        core/Simd128.h
        core/RegisterTraits.h
        core/x86/Simd128SSE.h
        core/x86/Simd128SSE.inl
        core/x86/Simd256SSE.h
        core/x86/Simd256SSE.inl
        core/x86/Simd128X86Math.h
        core/x86/Simd128X86Math.inl
        core/x86/Simd256X86Math.h
        core/x86/Simd256X86Math.inl

        utils/SIMDUtils.h
        utils/TypeTraits.h
        utils/SimdTraits.h

        FalconSimd.h
        DoxygenGroups.h
)

set_target_properties(FalconSIMD PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
# TODO: REMOVE PROJECT LINKAGE
target_link_libraries(FalconSIMD INTERFACE
        ${PROJECT_NAME}-StrictWarnings
        ${PROJECT_NAME}-ProjectSanitizers
)

target_include_directories(FalconSIMD INTERFACE ${FALCON_LIBRARY_ROOT_DIR})