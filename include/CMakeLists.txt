set(LIBRARY_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})


####################
# Falcon Game Math #
####################

# Library Options
option(FGM_FORCE_LEFT_HANDED "Use Left-Handed Coordinate System in FGM")

include(fgm/FGM.cmake)
add_library(FGM INTERFACE ${FGM_HEADERS})
target_compile_features(FGM INTERFACE cxx_std_20)

# NOTE: If this flag is not enabled, then NAN less than and less than or equal comparison will not work properly.
target_compile_options(FGM INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict>)
target_link_libraries(FGM INTERFACE StrictWarnings ProjectSanitizers)

target_include_directories(FGM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

source_group("CMake Files/fgm/" FILES fgm/FGM.cmake fgm/common/Common.cmake fgm/matrices/Matrices.cmake fgm/vectors/Vectors.cmake)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${FGM_HEADERS})

if (FGM_FORCE_LEFT_HANDED)
    message(STATUS "FGM is using Left-Handed Coordinate System")
    target_compile_definitions(FGM INTERFACE FGM_LEFT_HANDED)
else ()
    message(STATUS "FGM is using Right-Handed Coordinate System")
endif ()
target_link_libraries(FGM INTERFACE
        FalconSIMD
        StrictWarnings
        ProjectSanitizers
)


###############
# Falcon SIMD #
###############

include(falcon_simd/FalconSimd.cmake)
add_library(FalconSIMD INTERFACE ${FALCON_SIMD_HEADERS})
target_compile_features(FalconSIMD INTERFACE cxx_std_20)

target_include_directories(FalconSIMD INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

source_group("CMake Files/falcon_simd/" FILES falcon_simd/FalconSimd.cmake falcon_simd/utils/Utils.cmake)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${FALCON_SIMD_HEADERS})
target_link_libraries(FalconSIMD INTERFACE
        StrictWarnings
        ProjectSanitizers
)
