option(ENABLE_FGM_DEMO "Enables FGM Demo Application")

add_subdirectory(fgm)
add_subdirectory(simd)

target_compile_features(MathLib INTERFACE cxx_std_20)
target_compile_features(FalconSIMD INTERFACE cxx_std_20)

if (ENABLE_FGM_DEMO)
    message("Demo application is enabled")
    add_subdirectory(playground)
    target_compile_features(Playground PRIVATE cxx_std_20)

    target_link_libraries(Playground PRIVATE StrictWarnings ProjectSanitizers)

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT src/playground)
endif ()

