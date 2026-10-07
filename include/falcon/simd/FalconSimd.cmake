include_guard()
set(FALCON_SIMD_DIR ${LIBRARY_ROOT_DIR}/falcon_simd/)

include(${FALCON_SIMD_DIR}core/FalconMemory.cmake)
include(${FALCON_SIMD_DIR}utils/Utils.cmake)

set(FALCON_SIMD_ROOT_HEADERS
        FalconSimd.h
        DoxygenGroups.h
)
list(APPEND FALCON_SIMD_ROOT_HEADERS ${FALCON_SIMD_MEMORY_HEADERS})
list(APPEND FALCON_SIMD_ROOT_HEADERS ${FALCON_SIMD_UTILS_HEADERS})

# We need append the directory since the files are "included" from the root cml of the library
list(TRANSFORM FALCON_SIMD_ROOT_HEADERS PREPEND ${FALCON_SIMD_DIR})