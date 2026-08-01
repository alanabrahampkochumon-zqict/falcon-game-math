# Directories
set(FGM_ROOT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(FGM_TEST_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(UTILS_DIR "${FGM_ROOT_INCLUDE_DIR}utils/")


# Files
set(SetupHeaderFiles
        DoxygenGroups.h
        CommonSetup.h
)
list(TRANSFORM SetupHeaderFiles PREPEND ${FGM_ROOT_INCLUDE_DIR})

set(TestUtilities "FloatEquals.h;MatrixUtils.h;VectorUtils.h;TypeUtils.h;")
list(TRANSFORM TestUtilities PREPEND ${UTILS_DIR})

add_subdirectory(common)
add_subdirectory(vectors)
add_subdirectory(quaternions)
add_subdirectory(matrices)

source_group(
        TREE
        "${FGM_ROOT_INCLUDE_DIR}"
        PREFIX "Header Files"
        FILES
        ${SetupHeaderFiles}
        ${TestUtilities}
)


