include_guard()

set(FGM_LIBRARY_DIR ${LIBRARY_ROOT_DIR}/fgm)

include(${FGM_LIBRARY_DIR}/common/Common.cmake)
include(${FGM_LIBRARY_DIR}/matrices/Matrices.cmake)
include(${FGM_LIBRARY_DIR}/vectors/Vectors.cmake)

set(FGM_LIBRARY_ROOT_FILES
        Mat
        Vec
        DoxygenGroups.h
)

set(FGM_HEADERS ${FGM_COMMON_HEADERS} ${FGM_VEC_HEADERS} ${FGM_MAT_HEADERS} ${FGM_LIBRARY_ROOT_FILES})
list(TRANSFORM FGM_HEADERS PREPEND fgm/)
