set(FALCON_LIBRARY_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(FLCN_LIB_NAME Falcon)

add_subdirectory(falcon/core)
add_subdirectory(falcon/math)
add_subdirectory(falcon/simd)

# Library Options
option(FGM_FORCE_LEFT_HANDED "Use Left-Handed Coordinate System in Falcon Game Math")
add_library(${FLCN_LIB_NAME} INTERFACE
        falcon/Falcon.h
)
add_library(${FLCN_LIB_NAME}:${FLCN_LIB_NAME} ALIAS ${FLCN_LIB_NAME})


target_link_libraries(${FLCN_LIB_NAME} INTERFACE
        FalconCore
        FalconSIMD
        FalconGameMath
)

target_include_directories(${FLCN_LIB_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if (FGM_FORCE_LEFT_HANDED)
    message(STATUS "[Falcon]: Using Left-Handed Coordinate System")
    target_compile_definitions(${FLCN_LIB_NAME} INTERFACE FGM_LEFT_HANDED)
    target_compile_definitions(FalconGameMath INTERFACE FGM_LEFT_HANDED)
else ()
    message(STATUS "[Falcon]: Using Right-Handed Coordinate System")
endif ()

# TODO: Update to an option
target_compile_options(${FLCN_LIB_NAME} INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/fp:strict>)
