include_guard()

set(FALCON_SIMD_CORE_DIR "core/")

set(FALCON_SIMD_MEMORY_HEADERS
        Simd128.h
        RegisterTraits.h
        x86/Simd128SSE.h
        x86/Simd128SSE.inl
        x86/Simd128X86Math.h
        x86/Simd128X86Math.inl
)
list(TRANSFORM FALCON_SIMD_MEMORY_HEADERS PREPEND ${FALCON_SIMD_CORE_DIR})